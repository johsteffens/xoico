/** Author and Copyright 2020 Johannes Bernhard Steffens
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef XOICO_CDALETH_H
#define XOICO_CDALETH_H

#include "xoico_cengine.h"
#include "xoico_body.h"
#include "xoico_args.h"

/**********************************************************************************************************************/

/// C code processor

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( xoico_cdaleth, xoico_cengine )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// stack for variable declarations
group :stack_var = :
{
    stamp :unit = aware bcore_inst
    {
        sz_t level;
        tp_t name;
        xoico_typespec_s typespec;
    };

    stamp :unit_adl = aware bcore_array { :unit_s => []; };

    signature @* push_unit( mutable, const :unit_s* unit );
    signature @* pop_level( mutable, sz_t level ); // pop all units of or above level

    signature bl_t exists( const, tp_t name );
    signature const xoico_typespec_s* get_typespec( const, tp_t name );
    signature const sz_t get_level( const, tp_t name );
    signature void clear( mutable );
    signature void rehash_names( mutable );

    stamp : = aware :
    {
        :unit_adl_s adl;
        bcore_hmap_tpuz_s hmap_name;

        func :.exists = { return o.hmap_name.exists( name ); };

        func :.rehash_names =
        {
            o.hmap_name.clear();
            for( sz_t i = 0; i < o.adl.size; i++ ) o.hmap_name.set( o.adl.[i].name, i );
        };

        func :.push_unit =
        {
            o.adl.push_c( unit );
            o.hmap_name.set( unit->name, o.adl.size - 1 );
            return o;
        };

        func :.pop_level =
        {
            sz_t size = o->adl.size;
            while( size > 0 && o.adl.data[ size - 1 ]->level >= level ) size--;
            o.adl.set_size( size );
            o.rehash_names();
            return o;
        };

        func :.get_typespec =
        {
            uz_t* p_idx = o.hmap_name.get( name );
            if( !p_idx ) return NULL;
            return o.adl.[ *p_idx ].typespec;
        };

        /// returns -1 if not found
        func :.get_level =
        {
            uz_t* p_idx = o.hmap_name.get( name );
            if( !p_idx ) return -1;
            return o.adl.[ *p_idx ].level;
        };

        func :.clear =
        {
            o.adl.clear();
            o.hmap_name.clear();
        };
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// stack for block/level specific data
group :stack_block = :
{
    stamp :unit = aware bcore_inst
    {
        sz_t level; // level of this block
        bl_t use_blm = false;
        bl_t break_ledge = false; // this block represents a break-ledge for a break-command inside this block or higher-level blocks up to the next break-level
    };

    stamp :unit_adl = aware bcore_array { :unit_s => []; };

    signature @* push( mutable );
    signature @* push_unit( mutable, const :unit_s* unit );
    signature @* pop(  mutable );
    signature void clear( mutable );
    signature sz_t get_size( const );

    stamp : = aware :
    {
        :unit_adl_s adl;
        func :.push      = { o.adl.push_d( :unit_s! );  return o; };
        func :.push_unit = { o.adl.push_c( unit );  return o; };

        func :.pop =
        {
            o.adl.set_size( sz_max( o->adl.size - 1, 0 ) );
            return o;
        };

        func :.clear = { o.adl.clear(); };
        func :.get_size = { return o.adl.size; };
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signature tp_t entypeof(  mutable, sc_t name );
signature sc_t nameof(    mutable, tp_t type );
signature void init_level0( mutable );
signature void inc_level( mutable );
signature void dec_level( mutable );
signature void inc_block( mutable );
signature void dec_block( mutable );
signature void push_typedecl( mutable, const xoico_typespec_s* typespec, tp_t name );
signature :stack_block_unit_s* stack_block_get_top_unit( mutable );
signature :stack_block_unit_s* stack_block_get_bottom_unit( mutable );
signature :stack_block_unit_s* stack_block_get_level_unit( mutable, sz_t level );

signature bl_t is_var( const, tp_t name );

name static;
name volatile;
name cast;
name verbatim_C;
name keep;
name scope;
name scope_local;
name scope_func;
name keep_func;
name keep_block;
name fork;
name try;
name if;
name else;
name while;
name do;
name for;
name foreach;
name switch;
name case;
name default;
name break;
name return;

stamp : = aware :
{
    /// parameters

    bl_t verbose = false;

    /// Prepends a commented reference to the xoila source for each function in *xoila_out.c
    bl_t insert_source_reference = true;

    /// runtime data

    hidden xoico_args_s*     args;
    hidden xoico_typespec_s* typespec_ret;
    hidden xoico_compiler_s* compiler;
    hidden xoico_group_s*    group;
    hidden xoico_stamp_s*    stamp;

    tp_t obj_type;

    /// runtime state
    sz_t level;
    sz_t try_block_level;

    :stack_var_s   stack_var;
    :stack_block_s stack_block;

    bcore_hmap_name_s hmap_name;

    func xoico_cengine.translate;

    func xoico_cengine.is_reserved =
    {
        return o.is_builtin_func( tp_identifier ) ||
               o.is_control_name( tp_identifier ) ||
               tp_identifier == TYPEOF_verbatim_C;
    };

    func :.entypeof = { return o.hmap_name.set_sc( name ); };

    func :.nameof   =
    {
        sc_t name = o.hmap_name.get_sc( type );
        if( !name ) name = o.compiler.nameof( type );
        return name;
    };

    func :.init_level0 =
    {
        o.stack_block.clear();
        o.stack_block.push();
        o.level = 0;
    };

    func :.inc_block =
    {
        o.stack_block.push();
        o->level++;
        o.stack_block_get_top_unit().level = o.level;
    };

    func :.dec_block =
    {
        o.stack_var.pop_level( o->level );
        o.level--;
        ASSERT( o.level >= 0 );
        o.stack_block.pop();
    };

    func :.stack_block_get_top_unit =
    {
        return o.stack_block.adl.[ o.stack_block.adl.size - 1 ];
    };

    func :.stack_block_get_bottom_unit =
    {
        return o.stack_block.adl.[ 0 ];
    };

    func :.stack_block_get_level_unit =
    {
        foreach( $* e in o.stack_block.adl ) if( e.level == level ) return e;
        ERR_fa( "Level #<sz_t> not found.", level );
        return NULL;
    };

    func :.push_typedecl =
    {
        :stack_var_unit_s* unit = :stack_var_unit_s!.scope();
        unit.level = o->level;
        unit.name = name;
        unit.typespec.copy( typespec );
        o.stack_var.push_unit( unit );
    };

    func xoico_compiler.is_type  = { return o.compiler.is_type( name ); };
    func xoico_compiler.is_group = { return o.compiler.is_group( name ); };
    func xoico_compiler.is_stamp = { return o.compiler.is_stamp( name ); };
    func xoico_compiler.is_func  = { return o.compiler.is_func( name ); };
    func :.is_var = { return o.stack_var.exists( name ); };

    func xoico_compiler.get_group = { return o.compiler.get_group( name ); };
    func xoico_compiler.get_stamp = { return o.compiler.get_stamp( name ); };
    func xoico_compiler.get_func  = { return o.compiler.get_func( name ); };

    func (bl_t returns_a_value( const )) =
    {
        return ( o.typespec_ret.type != TYPEOF_void ) || ( o.typespec_ret.indirection > 0 );
    };

    func (er_t parse( const, bcore_source* source, sc_t format )) =
    {
        return source.parse_em_fa( format );
    };

    func (er_t trans( const, bcore_source* source, sc_t format, st_s* buf )) =
    {
        try( o.parse( source, format ));
        buf.push_sc( format );
        return 0;
    };

};

embed "xoico_cdaleth.x";
embed "xoico_cdaleth_builtin.x";
embed "xoico_cdaleth_control.x";

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // XOICO_CDALETH_H
