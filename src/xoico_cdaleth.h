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

        func : .exists = { return o.hmap_name.exists( name ); };

        func : .rehash_names =
        {
            o.hmap_name.clear();
            for( sz_t i = 0; i < o.adl.size; i++ ) o.hmap_name.set( o.adl.[i].name, i );
        };

        func : .push_unit =
        {
            o.adl.push_c( unit );
            o.hmap_name.set( unit->name, o.adl.size - 1 );
            return o;
        };

        func : .pop_level =
        {
            sz_t size = o->adl.size;
            while( size > 0 && o->adl.data[ size - 1 ]->level >= level ) size--;
            o.adl.set_size( size );
            o.rehash_names();
            return o;
        };

        func : .get_typespec =
        {
            uz_t* p_idx = o.hmap_name.get( name );
            if( !p_idx ) return NULL;
            return o.adl.[ *p_idx ].typespec;
        };

        /// returns -1 if not found
        func : .get_level =
        {
            uz_t* p_idx = o.hmap_name.get( name );
            if( !p_idx ) return -1;
            return o.adl.[ *p_idx ].level;
        };

        func : .clear = { o.adl.clear(); o.hmap_name.clear(); };

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
        func : .push      = { o.adl.push_d( :unit_s! );  return o; };
        func : .push_unit = { o.adl.push_c( unit );  return o; };

        func : .pop =
        {
            o.adl.set_size( sz_max( o->adl.size - 1, 0 ) );
            return o;
        };

        func : .clear = { o.adl.clear(); };
        func : .get_size = { return o.adl.size; };
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

signature bl_t is_type(  const, tp_t name );
signature bl_t is_group( const, tp_t name );
signature bl_t is_stamp( const, tp_t name );
signature bl_t is_var(   const, tp_t name );

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
    :stack_var_s   stack_var;
    :stack_block_s stack_block;

    bcore_hmap_name_s hmap_name;

    func xoico_cengine.translate;

    func xoico_cengine.is_reserved =
    {
        return o.is_builtin_func( tp_identifier ) ||
               o.is_control_name( tp_identifier );
    };

    func : .entypeof = { return bcore_hmap_name_s_set_sc( &o->hmap_name, name ); };

    func : .nameof   =
    {
        sc_t name = bcore_hmap_name_s_get_sc( &o->hmap_name, type );
        if( !name ) name = xoico_compiler_s_nameof( o->compiler, type );
        return name;
    };

    func : .init_level0 =
    {
        :stack_block_s_clear( &o->stack_block );
        :stack_block_s_push( &o->stack_block );
        o->level = 0;
    };

    func : .inc_block =
    {
        o.stack_block.push();
        o->level++;
        o.stack_block_get_top_unit().level = o.level;
    };

    func : .dec_block =
    {
        o.stack_var.pop_level( o->level );
        o.level--;
        ASSERT( o.level >= 0 );
        o.stack_block.pop();
    };

    func : .stack_block_get_top_unit =
    {
        return o.stack_block.adl.[ o.stack_block.adl.size - 1 ];
    };

    func : .stack_block_get_bottom_unit =
    {
        return o.stack_block.adl.[ 0 ];
    };

    func : .stack_block_get_level_unit =
    {
        foreach( $* e in o.stack_block.adl ) if( e.level == level ) return e;
        ERR_fa( "Level #<sz_t> not found.", level );
        return NULL;
    };

    func : .push_typedecl =
    {
        :stack_var_unit_s* unit = scope( :stack_var_unit_s! );
        unit->level = o->level;
        unit->name = name;
        xoico_typespec_s_copy( &unit->typespec, typespec );
        :stack_var_s_push_unit( &o->stack_var, unit );
    };

    func : .is_type  = { return o.compiler.is_type( name ); };
    func : .is_group = { return o.compiler.is_group( name ); };
    func : .is_stamp = { return o.compiler.is_stamp( name ); };
    func : .is_var   = { return o.stack_var.exists( name ); };

    func (tp_t get_identifier( mutable, bcore_source* source, bl_t take_from_source ));
    func (er_t trans_identifier( mutable, bcore_source* source, st_s* buf /* can be NULL */, tp_t* tp_identifier/* can be NULL */ ));
    func (er_t trans_whitespace( mutable, bcore_source* source, st_s* buf /* can be NULL */ ));
    func (er_t trans_statement( mutable, bcore_source* source, st_s* buf ));
    func (er_t trans_block( mutable, bcore_source* source, st_s* buf, bl_t is_break_ledge ));
    func (er_t trans_statement_as_block( mutable, bcore_source* source, st_s* buf_out, bl_t is_break_ledge ));
    func (bl_t returns_a_value( const ));

    func (er_t parse( const, bcore_source* source, sc_t format )) =
    {
        return bcore_source_a_parse_em_fa( source, format );
    };

    func (er_t trans( const, bcore_source* source, sc_t format, st_s* buf )) =
    {
        try( o.parse( source, format ));
        buf.push_sc( format );
        return 0;
    };

    func (bl_t parse_bl( const, bcore_source* source, sc_t format )) =
    {
        return bcore_source_a_parse_bl( source, format );
    };

    func
    (
        er_t trans_expression
        (
            mutable,
            bcore_source* source,
            st_s* buf_out,                 // can be NULL
            xoico_typespec_s* out_typespec // optional
        )
    );

    func
    (
        er_t take_typespec
        (
            mutable,
            bcore_source* source,
            xoico_typespec_s* typespec,
            bl_t require_tractable_type
        )
    );

    func
    (
        er_t push_typespec
        (
            mutable,
            const xoico_typespec_s* typespec,
            st_s* buf
        )
    );

    func
    (
        er_t adapt_expression
        (
            mutable,
            bcore_source* source,
            const xoico_typespec_s* typespec_expr,
            const xoico_typespec_s* typespec_target,
            const st_s* expr,
            st_s* buf
        )
    );
};

embed "xoico_cdaleth_builtin.x";
embed "xoico_cdaleth_control.x";

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

er_t xoico_cdaleth_s_parse_err_fv( const xoico_cdaleth_s* o, bcore_source* source, sc_t format, va_list args );
er_t xoico_cdaleth_s_parse_err_fa( const xoico_cdaleth_s* o, bcore_source* source, sc_t format, ... );

/**********************************************************************************************************************/

#endif // XOICO_CDALETH_H
