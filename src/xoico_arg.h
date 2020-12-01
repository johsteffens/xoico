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

#ifndef XOICO_ARG_H
#define XOICO_ARG_H

/**********************************************************************************************************************/

#include "xoico.h"
#include "xoico_typespec.h"

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( xoico_arg, xoico )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signature bl_t is_variadic( const );

stamp : = aware :
{
    hidden aware xoico_group_s* group;
    bcore_source_point_s source_point;
    xoico_typespec_s typespec;
    tp_t name;

    func :.is_variadic = { return o.typespec.flag_variadic; };
};

// ---------------------------------------------------------------------------------------------------------------------

func (:) xoico.parse = (try)
{
    xoico_compiler_s* compiler = o.group.compiler;
    o.source_point.set( source );
    o.typespec.parse( o.group, source );

    if( o.typespec.flag_variadic ) return 0;

    if( o.typespec.type == TYPEOF_void && o.typespec.indirection == 0 )
    {
        return o.source_point.parse_error_fa( "'void' is misplaced here." );
    }

    $* s = st_s!.scope();
    source.parse_em_fa( "#name ", s );
    if( s.size == 0 )
    {
        return source.parse_error_fa( "Argument: Name expected." );
    }
    o.name = compiler.entypeof( s.sc );

    return 0;
};

func (:) xoico.get_hash =
{
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o._ );
    hash = bcore_tp_fold_tp( hash, o.typespec.get_hash() );
    hash = bcore_tp_fold_tp( hash, o.name );
    return hash;
};

func (:) (er_t relent( mutable, tp_t tp_obj_type )) =
{
    return o.typespec.relent( o.group, tp_obj_type );
};

func (:) (er_t expand( const, sc_t sc_obj_type, bcore_sink* sink )) =
{
    try( o.typespec.expand( o.group, sc_obj_type, sink ) );
    if( o.name )
    {
        sink.push_fa( " " );
        o.expand_name( sink );
    }
    return 0;
};

func (:) (er_t expand_name( const, bcore_sink* sink )) =
{
    if( !o.name ) return 0;
    sink.push_fa( "#<sc_t>", o.group.compiler.nameof( o.name ) );
    return 0;
};

// ---------------------------------------------------------------------------------------------------------------------

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // XOICO_ARG_H
