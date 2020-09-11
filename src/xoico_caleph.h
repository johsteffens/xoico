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

#ifndef XOICO_CALEPH_H
#define XOICO_CALEPH_H

#include "xoico_cengine.h"
#include "xoico_body.h"
#include "xoico_args.h"

/**********************************************************************************************************************/

/// C code processor

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( xoico_caleph, xoico_cengine )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// type-name-stack
group :tn = :
{
    stamp :unit = bcore_inst
    {
        tp_t type;
        tp_t name;
        sz_t level;
    };

    stamp :adl = aware bcore_array { :unit_s => []; };

    signature @* push( mutable, tp_t type, tp_t name, sz_t level );
    signature @* pop( mutable, sz_t level ); // pop all units of or above level
    signature tp_t get_type( mutable, tp_t name );
    signature @* push_sc( mutable, sc_t type, sc_t name, sz_t level );
    signature sc_t get_type_sc( mutable, sc_t name );  // returns NULL if name is not registered
    signature void clear( mutable );
    signature void init_from_args( mutable, sc_t obj_type, sc_t obj_name, const xoico_args_s* args );

    stamp :stack = aware :
    {
        :adl_s adl;
        bcore_hmap_name_s name_map;

        func : :push =
        {
            :unit_s* unit = :unit_s_create();
            unit->type = type;
            unit->name = name;
            unit->level = level;
            :adl_s_push_d( &o->adl, unit );
            return o;
        };

        func : :push_sc =
        {
            :unit_s* unit = :unit_s_create();
            unit->type = bcore_hmap_name_s_set_sc( &o->name_map, type );
            unit->name = bcore_hmap_name_s_set_sc( &o->name_map, name );
            unit->level = level;
            :adl_s_push_d( &o->adl, unit );
            return o;
        };

        func : :pop =
        {
            sz_t new_size = o->adl.size;
            for( sz_t i = o->adl.size - 1; i >= 0; i-- )
            {
                if( o->adl.data[ i ]->level < level ) break;
                new_size = i;
            }
            :adl_s_set_size( &o->adl, new_size );
            return o;
        };

        func : :get_type =
        {
            for( sz_t i = o->adl.size - 1; i >= 0; i-- )
            {
                if( o->adl.data[ i ]->name == name ) return o->adl.data[ i ]->type;
            }
            return 0;
        };

        func : :get_type_sc =
        {
            return bcore_hmap_name_s_get_sc( &o->name_map, @_get_type( o, btypeof( name ) ) );
        };

        func : :clear =
        {
            bcore_hmap_name_s_clear( &o->name_map );
            :adl_s_clear( &o->adl );
        };

        func : :init_from_args =
        {
            const xoico_compiler_s* compiler = xoico_group_s_get_compiler( args->group );
            @_clear( o );
            if( obj_type ) @_push_sc( o, obj_type, obj_name, 0 );
            BFOR_EACH( i, args )
            {
                sc_t sc_type = xoico_compiler_s_nameof( compiler, args->data[ i ].typespec.type );
                sc_t sc_name = xoico_compiler_s_nameof( compiler, args->data[ i ].name );
                @_push_sc( o, sc_type, sc_name, 0 );
            }
        };
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signature er_t take_block     ( mutable, bcore_source* source, bcore_sink* sink );
signature er_t take_block_body( mutable, bcore_source* source, bcore_sink* sink );

stamp : = aware :
{
    sc_t obj_type;
    xoico_args_s     -> args;
    xoico_compiler_s -> compiler;
    hidden :tn_stack_s stack;

    func : :take_block;
    func : :take_block_body;
    func xoico_cengine : translate;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // XOICO_CALEPH_H
