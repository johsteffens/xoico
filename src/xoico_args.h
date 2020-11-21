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

#ifndef XOICO_ARGS_H
#define XOICO_ARGS_H

/**********************************************************************************************************************/

#include "xoico.h"
#include "xoico_arg.h"

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( xoico_args, xoico )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp : = aware bcore_array
{
    xoico_arg_s [];
    hidden aware xoico_group_s* group;

    func xoico_arg.is_variadic = { return ( o.size > 0 && o.[ o.size - 1 ].is_variadic() ); };
};

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico.parse = { o.clear(); return o.append( source ); };

func (:) (er_t append( mutable, bcore_source* source )) =
{
    try
    {
        bl_t first = true;
        while( !source.parse_bl( " #=?')' " ) ) // args follow
        {
            if( o.is_variadic() ) return source.parse_error_fa( "Cannot append to variadic argument list." );
            if( !first ) xoico_parse_f( source, " , " );
            $* arg = xoico_arg_s!.scope();
            arg.group = o.group;
            arg.parse( source );
            o.push_d( arg.fork() );
            first = false;
        }
    }
    return 0;
};

func (:) (er_t relent( mutable, tp_t tp_obj_type )) =
{
    foreach( $* arg in o ) arg.relent( tp_obj_type ).try();
    return 0;
};

func (:) (er_t expand( const, bl_t first, sc_t sc_obj_type, bcore_sink* sink )) =
{
    foreach( $* arg in o )
    {
        if( !first ) sink.push_fa( ", " );
        first = false;
        arg.expand( sc_obj_type, sink ).try();
    }
    return 0;
};

func (:) (er_t expand_name( const, bl_t first, bcore_sink* sink )) =
{
    foreach( $* arg in o )
    {
        if( !first ) sink.push_fa( ", " );
        first = false;
        arg.expand_name( sink ).try();
    }
    return 0;
};

func (:) xoico.get_hash =
{
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o._ );
    foreach( $* arg in o ) hash = bcore_tp_fold_tp( hash, arg.get_hash() );
    return hash;
};

//----------------------------------------------------------------------------------------------------------------------

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // XOICO_ARGS_H
