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
    feature void clear( mutable )             = {};
    feature er_t push_char( mutable, char c ) = { ERR_fa( "Not implemented." ); return 0; };
    feature er_t push_sc( mutable, sc_t sc )  = { ERR_fa( "Not implemented." ); return 0; };
    feature er_t push_st( mutable, const st_s* st ) = { ERR_fa( "Not implemented." ); return 0; };
    feature :* push_result_c( mutable, const :* result ) = { ERR_fa( "Not implemented." ); return NULL; };
    feature :* push_result_d( mutable, :* result ) = { ERR_fa( "Not implemented." ); return NULL; };
    feature er_t to_sink( const, bcore_sink* sink );

    feature void set_parent_block( mutable, :block_s* parent ) = {};

    feature st_s* create_st( const ) =
    {
        $* st = st_s!;
        o.to_sink( st );
        return st;
    };

//----------------------------------------------------------------------------------------------------------------------

    stamp :plain_s = aware :
    {
        st_s st;

        func (@* create_from_st( const st_s* st ) ) = { $* o = @!; o.st.copy( st ); return o; };
        func (@* create_from_st_d(     st_s* st ) ) = { $* o = @!; o.st.copy( st ); st.discard(); return o; };
        func (@* create_from_sc(       sc_t  sc ) ) = { $* o = @!; o.st.copy_sc( sc ); return o; };

        func :.clear     = { o.st.clear(); };
        func :.push_char = { o.st.push_char( c ); return 0; };
        func :.push_sc   = { o.st.push_sc( sc ); return 0; };
        func :.push_st   = { o.st.push_st( st ); return 0; };
        func :.to_sink   = { sink.push_string( o.st );  return 0; };
        func :.create_st = { return o.st.clone(); };
    };

    func (:* create_from_st( const st_s* st ) ) = { $* o = :arr_s!; o.push_st( st ); return o; };
    func (:* create_from_sc(       sc_t  sc ) ) = { $* o = :arr_s!; o.push_sc( sc ); return o; };

    stamp :adl_s = aware x_array { aware : -> []; }; // !! weak links !!  (if this causes problems revert to strong links)

//----------------------------------------------------------------------------------------------------------------------

    stamp :arr_s = aware :
    {
        :adl_s adl;

        func :.clear = { o.adl.clear(); };

        func (:* last( mutable )) =
        {
            return ( o.adl.size == 0 ) ? o.adl.push_d( :plain_s!.cast( :* ) ) : o.adl.[ o.adl.size - 1 ];
        };

        func (:* last_plain( mutable )) =
        {
            return ( o.last()._ != TYPEOF_:plain_s ) ? o.adl.push_d( :plain_s!.cast( :* ) ) : o.adl.[ o.adl.size - 1 ];
        };

        func :.push_char = { return o.last_plain().push_char( c ); };
        func :.push_sc   = { return o.last_plain().push_sc( sc );  };
        func :.push_st   = { return o.last_plain().push_st( st );  };
        func :.push_result_d = { return o.adl.push_d( result ); };
        func :.push_result_c = { return o.adl.push_c( result ); };

        func :.to_sink =
        {
            foreach( $* e in o.adl ) e.to_sink( sink );
            return 0;
        };

        func :.set_parent_block =
        {
            foreach( $* e in o.adl ) e.set_parent_block( parent );
        };
    };

    func (:* create_arr() ) = { return :arr_s!; };

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
            :* result_pushed = o.arr.push_result_d( result );
            result_pushed.set_parent_block( o );
            return result_pushed;
        };

        func :.push_result_c =
        {
            :* result_pushed = o.arr.push_result_c( result );
            result_pushed.set_parent_block( o );
            return result_pushed;
        };

        func :.to_sink = { return o.arr.to_sink( sink ); };
        func :.set_parent_block = { o.parent = parent; };

        func (bl_t is_using_blm_until_level( const, sz_t level )) =
        {
            if( level > o.level ) return false;
            if( o.is_using_blm ) return true;
            if( o.is_root ) return false;

            ASSERT( o.parent );
            return o.parent.is_using_blm_until_level( level );
        };

    };

    func (:* create_block( sz_t level, bl_t is_using_blm  ) ) =
    {
        $* o = :block_s!;
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

    func (:* create_blm_init( sz_t level ) ) = { $* o = :blm_init_s!; o.level = level; return o; };

//----------------------------------------------------------------------------------------------------------------------

    stamp :blm_down_s = aware :
    {
        func :.to_sink = { sink.push_sc( "BLM_DOWN();" ); return 0; };
    };

    func (:* create_blm_down() ) = { $* o = :blm_down_s!; return o; };

//----------------------------------------------------------------------------------------------------------------------

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

    signature @* push_unit( mutable, const :unit_s* unit );
    signature @* pop_level( mutable, sz_t level ); // pop all units of or above level

    signature bl_t exists( const, tp_t name );
    signature const xoico_typespec_s* get_typespec( const, tp_t name );
    signature const sz_t get_level( const, tp_t name );
    signature void clear( mutable );
    signature void rehash_names( mutable );

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
            uz_t* p_idx = o.hmap_name.get( name );
            if( !p_idx ) return NULL;
            return o.adl.[ p_idx.0 ].typespec;
        };

        /// returns -1 if not found
        func :.get_level =
        {
            uz_t* p_idx = o.hmap_name.get( name );
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

    signature @* push( mutable );
    signature @* push_unit( mutable, const :unit_s* unit );
    signature @* pop(  mutable );
    signature void clear( mutable );
    signature sz_t get_size( const );

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
signature er_t push_typespec( mutable, const xoico_typespec_s* typespec, :result* result );
signature void typespec_to_sink( mutable, const xoico_typespec_s* typespec, bcore_sink* sink );

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
name continue;
name goto;

stamp :s = aware :
{
    /// parameters

    bl_t verbose = false;

    /// Prepends a commented reference to the xoila source for each function in *xoila_out.c
    bl_t insert_source_reference = true;

    /// runtime data

    hidden xoico_host*       host;
    hidden xoico_compiler_s* compiler;

    xoico_typespec_s typespec_ret;

    tp_t member_obj_type; // 0 in case function has no arg_o

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

    func :.push_typespec;
    func :.typespec_to_sink =
    {
        $* result = :result_create_arr().scope();
        o.push_typespec( typespec, result );
        sink.push_sc( result.create_st().scope().sc );
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

    func (bl_t returns_a_value( const )) =
    {
        return ( !( ( o.typespec_ret.type == 0 ) || ( o.typespec_ret.type == TYPEOF_void ) ) ) || ( o.typespec_ret.indirection > 0 );
    };

    func (er_t trans( const, bcore_source* source, sc_t format, :result* result )) =
    {
        try( source.parse_em_fa( format ));
        result.push_sc( format );
        return 0;
    };

};

embed "xoico_che.x";
embed "xoico_che_builtin.x";
embed "xoico_che_control.x";

//----------------------------------------------------------------------------------------------------------------------

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//----------------------------------------------------------------------------------------------------------------------

static inline er_t xoico_che_result_a_push_fv( xoico_che_result* o, sc_t format, va_list args )
{
    st_s* st = st_s_create_fv( format, args );
    er_t ret = xoico_che_result_a_push_st( o, st );
    st_s_discard( st );
    return ret;
}

//----------------------------------------------------------------------------------------------------------------------

static inline er_t xoico_che_result_a_push_fa( xoico_che_result* o, sc_t format, ... )
{
    va_list args;
    va_start( args, format );
    er_t ret = xoico_che_result_a_push_fv( o, format, args );
    va_end( args );
    return ret;
}

//----------------------------------------------------------------------------------------------------------------------

static inline er_t xoico_che_result_a_copy_fv( xoico_che_result* o, sc_t format, va_list args )
{
    xoico_che_result_a_clear( o );
    return xoico_che_result_a_push_fv( o, format, args );
}

//----------------------------------------------------------------------------------------------------------------------

static inline er_t xoico_che_result_a_copy_fa( xoico_che_result* o, sc_t format, ... )
{
    va_list args;
    va_start( args, format );
    er_t ret = xoico_che_result_a_copy_fv( o, format, args );
    va_end( args );
    return ret;
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

#endif // XOICO_CHE_H
