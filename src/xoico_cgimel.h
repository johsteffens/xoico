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

#ifndef XOICO_CGIMEL_H
#define XOICO_CGIMEL_H

#include "xoico_cengine.h"
#include "xoico_body.h"
#include "xoico_args.h"

/**********************************************************************************************************************/

/// C code processor

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( xoico_cgimel, xoico_cengine )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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
        func :.push_unit = { :unit_adl_s_push_c( &o->adl, unit );  return o; };

        func :.pop_level =
        {
            sz_t size = o->adl.size;
            while( size > 0 && o->adl.data[ size - 1 ]->level >= level ) size--;
            :unit_adl_s_set_size( &o->adl, size );
            return o;
        };

        func :.get_typespec =
        {
            for( sz_t i = o->adl.size - 1; i >= 0; i-- )
            {
                if( o->adl.data[ i ]->name == name ) return &o->adl.data[ i ]->typespec;
            }
            return NULL;
        };

        func :.clear = { :unit_adl_s_clear( &o->adl ); };
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signature tp_t entypeof(  mutable, sc_t name );
signature sc_t nameof(    mutable, tp_t type );
signature void inc_level( mutable );
signature void dec_level( mutable );
signature void push_typedecl( mutable, const xoico_typespec_s* typespec, tp_t name );

name static;
name volatile;
name cast;

stamp : = aware :
{
    /// parameters

    bl_t verbose = false;

    /// Prepends a commented reference to the xoila source for each function in *xoila_out.c
    bl_t insert_source_reference = true;

    /// runtime data

    hidden xoico_args_s*     args;
    hidden xoico_compiler_s* compiler;
    hidden xoico_group_s*    group;
    hidden xoico_stamp_s*    stamp;

    tp_t obj_type;

    /// runtime state
    sz_t level;
    :stack_s stack;
    bcore_hmap_name_s hmap_name;

    func :.entypeof = { return bcore_hmap_name_s_set_sc( &o->hmap_name, name ); };
    func :.nameof   =
    {
        sc_t name = bcore_hmap_name_s_get_sc( &o->hmap_name, type );
        if( !name ) name = xoico_compiler_s_nameof( o->compiler, type );
        return name;
    };

    func :.inc_level =
    {
        o->level++;
    };

    func :.dec_level =
    {
        :stack_s_pop_level( &o->stack, o->level );
        o->level--;
    };

    func :.push_typedecl =
    {
        BLM_INIT();
        :stack_unit_s* unit = BLM_CREATE( :stack_unit_s );
        unit->level = o->level;
        unit->name = name;
        xoico_typespec_s_copy( &unit->typespec, typespec );
        :stack_s_push_unit( &o->stack, unit );
        BLM_DOWN();
    };

    func xoico_cengine.translate;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // XOICO_CGIMEL_H
