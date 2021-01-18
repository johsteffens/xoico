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

#ifndef XOICO_CHE_H
#define XOICO_CHE_H

#include "xoico_cengine.h"
#include "xoico_body.h"
#include "xoico_args.h"
#include "xoico_transient_map.h"

/**********************************************************************************************************************/

/// C code processor

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( xoico_che, xoico_cengine )
#ifdef XOILA_SECTION

//----------------------------------------------------------------------------------------------------------------------

/// stack for variable declarations
group :result = :
{
    feature void clear( m @* o )             = {};
    feature er_t push_char( m @* o, char c )          = (verbatim_C) { ERR_fa( "Not implemented." ); return 0; };
    feature er_t push_sc( m @* o, sc_t sc )           = (verbatim_C) { ERR_fa( "Not implemented." ); return 0; };
    feature er_t push_st( m @* o, c st_s* st )    = (verbatim_C) { ERR_fa( "Not implemented." ); return 0; };
    feature m :* push_result_c( m @* o, c :* result ) = (verbatim_C) { ERR_fa( "Not implemented." ); return NULL; };
    feature m :* push_result_d( m @* o, d :* result ) = (verbatim_C) { ERR_fa( "Not implemented." ); return NULL; };
    feature er_t to_sink( c @* o, m bcore_sink* sink );

    feature void set_parent_block( m @* o, m :block_s* parent ) = {};

    feature d st_s* create_st( c @* o ) =
    {
        d $* st = st_s!;
        o.to_sink( st );
        return st;
    };

//----------------------------------------------------------------------------------------------------------------------

    stamp :plain_s = aware :
    {
        st_s st;

        func (d @* create_from_st(   c st_s* st ) ) = { d $* o = @!; o.st.copy( st ); return o; };
        func (d @* create_from_st_d( d st_s* st ) ) = { d $* o = @!; o.st.copy( st ); st.discard(); return o; };
        func (d @* create_from_sc(     sc_t  sc ) ) = { d $* o = @!; o.st.copy_sc( sc ); return o; };

        func :.clear     = { o.st.clear(); };
        func :.push_char = { o.st.push_char( c ); return 0; };
        func :.push_sc   = { o.st.push_sc( sc ); return 0; };
        func :.push_st   = { o.st.push_st( st ); return 0; };
        func :.to_sink   = { sink.push_string( o.st );  return 0; };
        func :.create_st = { return o.st.clone(); };
    };

    func (d :* create_from_st( c st_s* st ) ) = { d $* o = :arr_s!; o.push_st( st ); return o; };
    func (d :* create_from_sc(   sc_t  sc ) ) = { d $* o = :arr_s!; o.push_sc( sc ); return o; };

    stamp :adl_s = aware x_array { aware : -> []; }; // !! weak links !!  (if this causes problems revert to strong links)

//----------------------------------------------------------------------------------------------------------------------

    stamp :arr_s = aware :
    {
        :adl_s adl;

        func :.clear = { o.adl.clear(); };

        func (m :* last( m @* o )) =
        {
            return ( o.adl.size == 0 ) ? o.adl.push_d( :plain_s! ) : o.adl.[ o.adl.size - 1 ];
        };

        func (m :* last_plain( m @* o )) =
        {
            return ( o.last()._ != TYPEOF_:plain_s ) ? o.adl.push_d( :plain_s! ) : o.adl.[ o.adl.size - 1 ];
        };

        func :.push_char = { return o.last_plain().push_char( c ); };
        func :.push_sc   = { return o.last_plain().push_sc( sc );  };
        func :.push_st   = { return o.last_plain().push_st( st );  };
        func :.push_result_d = { return o.adl.push_d( result ); };
        func :.push_result_c = { return o.adl.push_c( result ); };

        func :.to_sink =
        {
            foreach( m $* e in o.adl ) e.to_sink( sink );
            return 0;
        };

        func :.set_parent_block =
        {
            foreach( m $* e in o.adl ) e.set_parent_block( parent );
        };
    };

    func (d :* create_arr() ) = { return :arr_s!; };

//----------------------------------------------------------------------------------------------------------------------

    stamp :block_s = aware :
    {
        :arr_s arr;
        sz_t level = 0;
        bl_t is_using_blm = false;
        bl_t is_root = false;
        hidden @* parent;
        func :.clear = { o.arr.clear(); };
        func :.push_char = { return o.arr.push_char( c ); };
        func :.push_sc   = { return o.arr.push_sc( sc );  };
        func :.push_st   = { return o.arr.push_st( st );  };

        func :.push_result_d =
        {
            m :* result_pushed = o.arr.push_result_d( result );
            result_pushed.set_parent_block( o );
            return result_pushed;
        };

        func :.push_result_c =
        {
            m :* result_pushed = o.arr.push_result_c( result );
            result_pushed.set_parent_block( o );
            return result_pushed;
        };

        func :.to_sink = { return o.arr.to_sink( sink ); };
        func :.set_parent_block = { o.parent = parent; };

        func (bl_t is_using_blm_until_level( c @* o, sz_t level )) =
        {
            if( level > o.level ) return false;
            if( o.is_using_blm ) return true;
            if( o.is_root ) return false;

            ASSERT( o.parent );
            return o.parent.is_using_blm_until_level( level );
        };

    };

    func (d :* create_block( sz_t level, bl_t is_using_blm  ) ) =
    {
        d $* o = :block_s!;
        o.level = level;
        o.is_using_blm = is_using_blm;
        return o;
    };

//----------------------------------------------------------------------------------------------------------------------

    stamp :blm_init_s = aware :
    {
        sz_t level;
        func :.to_sink = { sink.push_fa( "BLM_INIT_LEVEL(#<sz_t>);", o.level ); return 0; };
    };

    func (d :* create_blm_init( sz_t level ) ) = { d $* o = :blm_init_s!; o.level = level; return o; };

//----------------------------------------------------------------------------------------------------------------------

    stamp :blm_down_s = aware :
    {
        func :.to_sink = { sink.push_sc( "BLM_DOWN();" ); return 0; };
    };

    func (d :* create_blm_down() ) = { d $* o = :blm_down_s!; return o; };

//----------------------------------------------------------------------------------------------------------------------

    func (er_t push_fv( m @* o, sc_t format, va_list args )) =
    {
        d st_s* st = st_s_create_fv( format, args );
        er_t ret = o.push_st( st );
        st_s_discard( st );
        return ret;
    };

//----------------------------------------------------------------------------------------------------------------------

    func( er_t push_fa( m @* o, sc_t format, ... )) =
    {
        va_list args;
        va_start( args, format );
        er_t ret = o.push_fv( format, args );
        va_end( args );
        return ret;
    };

//----------------------------------------------------------------------------------------------------------------------

    func( er_t copy_fv( m @* o, sc_t format, va_list args )) =
    {
        xoico_che_result_a_clear( o );
        return o.push_fv( format, args );
    };

//----------------------------------------------------------------------------------------------------------------------

    func (er_t copy_fa( m @* o, sc_t format, ... )) =
    {
        va_list args;
        va_start( args, format );
        er_t ret = o.copy_fv( format, args );
        va_end( args );
        return ret;
    };
};

/// stack for variable declarations
group :stack_var = :
{
    stamp :unit_s = aware bcore_inst
    {
        sz_t level;
        tp_t name;
        xoico_typespec_s typespec;
    };

    stamp :unit_adl_s = aware x_array { :unit_s => []; };

    signature m @* push_unit( m @* o, c :unit_s* unit );
    signature m @* pop_level( m @* o, sz_t level ); // pop all units of or above level

    signature bl_t exists( c @* o, tp_t name );
    signature c xoico_typespec_s* get_typespec( c @* o, tp_t name );
    signature c sz_t get_level( c @* o, tp_t name );
    signature void clear( m @* o );
    signature void rehash_names( m @* o );

    stamp :s = aware :
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
            m uz_t* p_idx = o.hmap_name.get( name );
            if( !p_idx ) return NULL;
            return o.adl.[ p_idx.0 ].typespec;
        };

        /// returns -1 if not found
        func :.get_level =
        {
            m uz_t* p_idx = o.hmap_name.get( name );
            if( !p_idx ) return -1;
            return o.adl.[ p_idx.0 ].level;
        };

        func :.clear =
        {
            o.adl.clear();
            o.hmap_name.clear();
        };
    };
};

//----------------------------------------------------------------------------------------------------------------------

/// stack for block/level specific data
group :stack_block = :
{
    stamp :unit_s = aware bcore_inst
    {
        sz_t level; // level of this block
        bl_t use_blm = false;
        bl_t break_ledge = false; // this block represents a break-ledge for a break-command inside this block or higher-level blocks up to the next break-level
    };

    stamp :unit_adl_s = aware x_array { :unit_s => []; };

    signature m @* push( m @* o );
    signature m @* push_unit( m @* o, c :unit_s* unit );
    signature m @* pop(  m @* o );
    signature void clear( m @* o );
    signature sz_t get_size( c @* o );

    stamp :s = aware :
    {
        :unit_adl_s adl;
        func :.push      = { o.adl.push_d( :unit_s! ); return o; };
        func :.push_unit = { o.adl.push_c( unit ); return o; };

        func :.pop =
        {
            o.adl.set_size( sz_max( o->adl.size - 1, 0 ) );
            return o;
        };

        func :.clear = { o.adl.clear(); };
        func :.get_size = { return o.adl.size; };
    };

};

//----------------------------------------------------------------------------------------------------------------------

signature tp_t entypeof(  m @* o, sc_t name );
signature sc_t nameof(    m @* o, tp_t type );
signature void init_level0( m @* o );
signature void inc_level( m @* o );
signature void dec_level( m @* o );
signature void inc_block( m @* o );
signature void dec_block( m @* o );
signature void push_typedecl( m @* o, c xoico_typespec_s* typespec, tp_t name );
signature m :stack_block_unit_s* stack_block_get_top_unit( m @* o );
signature m :stack_block_unit_s* stack_block_get_bottom_unit( m @* o );
signature m :stack_block_unit_s* stack_block_get_level_unit( m @* o, sz_t level );
signature er_t push_typespec( m @* o, c xoico_typespec_s* typespec, m :result* result );
signature void typespec_to_sink( m @* o, c xoico_typespec_s* typespec, m bcore_sink* sink );

signature bl_t is_var( c @* o, tp_t name );

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
name continue;
name goto;
name true;
name false;

stamp :s = aware :
{
    /// parameters

    bl_t verbose = false;

    /// Prepends a commented reference to the xoila source for each function in *xoila_out.c
    bl_t insert_source_reference = true;

    /// purity-control:

    // Condition: identifier specifies an undeclared member variable
    bl_t waive_unknown_member_variable = true;

    // Condition: identifier specifies an undeclared member function
    bl_t waive_unknown_member_function = true;

    // Condition: trans_expression: function identifier is not used in a tractable way (e.g. not as function call).
    bl_t waive_function_in_untraced_context = true;

    // Condition: trans_expression encounters an unknown identifier
    bl_t waive_unknown_identifier = true;

    /// runtime data
    hidden xoico_host*       host;
    hidden xoico_compiler_s* compiler;
    xoico_signature_s => signature;

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
        foreach( m $* e in o.stack_block.adl ) if( e.level == level ) return e;
        ERR_fa( "Level #<sz_t> not found.", level );
        return NULL;
    };

    func :.push_typedecl =
    {
        m :stack_var_unit_s* unit = :stack_var_unit_s!^^;
        unit.level = o->level;
        unit.name = name;
        unit.typespec.copy( typespec );
        o.stack_var.push_unit( unit );
    };

    func :.push_typespec;
    func :.typespec_to_sink =
    {
        m $* result = :result_create_arr()^^;
        o.push_typespec( typespec, result );
        sink.push_sc( result.create_st()^^.sc );
    };

    func xoico_compiler.is_type  = { return o.compiler.is_type( name ); };
    func xoico_compiler.is_group = { return o.compiler.is_group( name ); };
    func xoico_compiler.is_stamp = { return o.compiler.is_stamp( name ); };
    func xoico_compiler.is_func  = { return o.compiler.is_func( name ); };
    func :.is_var = { return o.stack_var.exists( name ); };

    func xoico_compiler.get_group = { return o.compiler.get_group( name ); };
    func xoico_compiler.get_stamp = { return o.compiler.get_stamp( name ); };
    func xoico_compiler.get_func  = { return o.compiler.get_func( name ); };
    func xoico_compiler.get_transient_map = { return o.compiler.get_transient_map( type ); };

    func (bl_t returns_a_value( c @* o )) = { return o.signature.returns_a_value(); };

    func (er_t trans( c @* o, m bcore_source* source, sc_t format, m :result* result )) =
    {
        try( source.parse_em_fa( format ));
        result.push_sc( format );
        return 0;
    };

};

embed "xoico_che.x";
embed "xoico_che_trans_typespec.x";
embed "xoico_che_function.x";
embed "xoico_che_builtin.x";
embed "xoico_che_control.x";

//----------------------------------------------------------------------------------------------------------------------

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

#endif // XOICO_CHE_H
