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
#include "xoico_typespec.h"

/**********************************************************************************************************************/

/// C code processor

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( xoico_xce, xoico )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// level-type-name-stack
group :stack = :
{
    stamp :unit = bcore_inst
    {
        sz_t level;
        tp_t name;
        xoico_typespec_s typespec;
    };

    stamp :unit_adl = aware bcore_array { :unit_s => []; };

    signature @* push_unit( mutable, const :unit_s* unit );
    signature @* pop_level( mutable, sz_t level ); // pop all units of or above level
    signature const xoico_typespec_s* get_typespec( const, tp_t name );
    signature void clear( mutable );

    stamp : = aware :
    {
        :unit_adl_s adl;
        func : :push_unit = { :unit_adl_s_push_c( &o->adl, unit );  return o; };
        func : :pop_level =
        {
            sz_t size = o->adl.size;
            while( size > 0 && o->adl.data[ size ]->level >= level ) size--;
            :unit_adl_s_set_size( &o->adl, size );
            return o;
        };

        func : :get_typespec =
        {
            for( sz_t i = o->adl.size - 1; i >= 0; i-- )
            {
                if( o->adl.data[ i ]->name == name ) return &o->adl.data[ i ]->typespec;
            }
            return NULL;
        };

        func : :clear = { :unit_adl_s_clear( &o->adl ); };
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signature tp_t entypeof( mutable, sc_t name );
signature sc_t nameof(   mutable, tp_t type );
signature er_t run( mutable );
signature void push_tn( mutable, tp_t t, tp_t n );
signature er_t setup( mutable, bl_t obj_const, tp_t obj_type, tp_t obj_name, const xoico_args_s* args );

stamp : = aware :
{
    xoico_compiler_s -> compiler;

    /// runtime state
    sz_t level;
    :stack_s stack;
    bcore_hmap_name_s hmap_name;

    func : :entypeof = { return bcore_hmap_name_s_set_sc( &o->hmap_name, name ); };
    func : :nameof   = { return bcore_hmap_name_s_get_sc( &o->hmap_name, type ); };

    func: : setup =
    {
        BLM_INIT();
        :stack_s_clear( &o->stack );
        o->level = 0;

        :stack_unit_s* unit = BLM_CREATE( :stack_unit_s );

        if( obj_type )
        {
            unit->typespec.is_const = obj_const;
            unit->typespec.type = obj_type;
            unit->typespec.indirection = 1;
            unit->name = obj_name;
            unit->level = 0;
            :stack_s_push_unit( &o->stack, unit );
            bcore_hmap_name_s_set_sc( &o->hmap_name, xoico_compiler_s_nameof( o->compiler, obj_type ) );
            bcore_hmap_name_s_set_sc( &o->hmap_name, xoico_compiler_s_nameof( o->compiler, obj_name ) );
        }

        BFOR_EACH( i, args )
        {
            const xoico_arg_s* arg = &args->data[ i ];
            if( arg->typespec.type && arg->name && arg->typespec.indirection == 1 )
            {
                xoico_typespec_s_copy( &unit->typespec, &arg->typespec );
                unit->name = arg->name;
                unit->level = 0;
                :stack_s_push_unit( &o->stack, unit );
                bcore_hmap_name_s_set_sc( &o->hmap_name, xoico_compiler_s_nameof( o->compiler, arg->typespec.type ) );
                bcore_hmap_name_s_set_sc( &o->hmap_name, xoico_compiler_s_nameof( o->compiler, arg->name ) );
            }
        }

        BLM_RETURNV( er_t, 0 );
    };

};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

group sim = :
{
    feature 'atpr' @* setup( mutable, const @* src );

    stamp : = aware :
    {
        bl_t bl;
        func : :setup = { return o; };
    };

    stamp :foo0 = aware :
    {
        st_s st;
        func : :setup = { return o; };
    };

    stamp :foo1 = aware :
    {
        :foo0_s f0;
        func : :setup = { return o; };
    };

    stamp :foo2 = aware :
    {
        :foo1_s => f1!;
        :foo2_s => f2;
        func : :setup = { return o; };
    };

    signature er_t framesig( plain, const :foo0_s* f0, const :foo1_s* f1, const :foo2_s* f2 );
};


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

vd_t xoico_xce_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // XOICO_XCE_H
