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

#ifndef XOICO_XCE_H
#define XOICO_XCE_H

#include "xoico.h"
#include "xoico_body.h"
#include "xoico_args.h"

/**********************************************************************************************************************/

/// C code processor

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( xoico_xce, xoico )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// level-type-name-stack
group :ltn = :
{
    signature @* create_ltn( plain, sz_t l, tp_t t, tp_t n );
    stamp :unit = bcore_inst
    {
        sz_t l; tp_t t; tp_t n;

        func : :create_ltn =
        {
            @* u = @_create();
            u->l = l;
            u->t = t;
            u->n = n;
            return u;
        };
    };

    stamp :unit_adl = aware bcore_array { :unit_s => []; };

    signature @* push_ltn( mutable, sz_t l, tp_t t, tp_t n );
    signature @* pop_l(    mutable, sz_t l ); // pop all units of or above level
    signature tp_t get_t(  const, tp_t n );
    signature void clear( mutable );

    stamp :stack = aware :
    {
        :unit_adl_s adl;
        func : :push_ltn = { :unit_adl_s_push_d( &o->adl, :unit_s_create_ltn( l, t, n) );  return o; };
        func : :pop_l =
        {
            sz_t size = o->adl.size;
            while( size > 0 && o->adl.data[ size ]->l >= l ) size--;
            :unit_adl_s_set_size( &o->adl, size );
            return o;
        };

        func : :get_t =
        {
            for( sz_t i = o->adl.size - 1; i >= 0; i-- )
            {
                if( o->adl.data[ i ]->n == n ) return o->adl.data[ i ]->t;
            }
            return 0;
        };

        func : :clear = { :unit_adl_s_clear( &o->adl ); };
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signature tp_t entypeof( mutable, sc_t name );
signature sc_t nameof(   mutable, tp_t type );
signature er_t run( mutable );
signature void push_tn( mutable, tp_t t, tp_t n );
signature er_t setup( mutable, tp_t obj_type, tp_t obj_name, const xoico_args_s* args );

stamp : = aware :
{
    bcore_source     -> source;
    bcore_sink       -> sink;
    xoico_compiler_s -> compiler;

    /// runtime state
    sz_t level;
    :ltn_stack_s stack;
    bcore_hmap_name_s hmap_name;

    func : :entypeof = { return bcore_hmap_name_s_set_sc( &o->hmap_name, name ); };
    func : :nameof   = { return bcore_hmap_name_s_get_sc( &o->hmap_name, type ); };
    func : :push_tn  = { :ltn_stack_s_push_ltn( &o->stack, o->level, t, n ); };

    func: : setup =
    {
        :ltn_stack_s_clear( &o->stack );
        o->level = 0;

        if( obj_type )
        {
            @_push_tn
            (
                o,
                @_entypeof( o, xoico_compiler_s_nameof( o->compiler, obj_type ) ),
                @_entypeof( o, xoico_compiler_s_nameof( o->compiler, obj_name ) )
            );
        }

        BFOR_EACH( i, args )
        {
            const xoico_arg_s* arg = &args->data[ i ];
            if( arg->typespec.type && arg->name && arg->typespec.ref_count == 1 )
            {
                @_push_tn
                (
                    o,
                    @_entypeof( o, xoico_compiler_s_nameof( o->compiler, arg->typespec.type ) ),
                    @_entypeof( o, xoico_compiler_s_nameof( o->compiler, arg->name ) )
                );
            }
        }

        return 0;

    };

};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

vd_t xoico_xce_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // XOICO_XCE_H
