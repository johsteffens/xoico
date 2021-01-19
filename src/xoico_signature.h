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

#ifndef XOICO_SIGNATURE_H
#define XOICO_SIGNATURE_H

/**********************************************************************************************************************/

#include "xoico.h"
#include "xoico_args.h"

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( xoico_signature, xoico )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

include 'c' "xoico_stamp.h";

signature er_t relent( m @* o, c xoico_host* host, tp_t tp_obj_type );
signature er_t expand_declaration( c @* o, c xoico_host* host, sc_t sc_func_global_name, sz_t indent, m bcore_sink* sink );
signature er_t set_global_name( m @* o, c xoico_host* host );

stamp :s = aware :
{
    tp_t name;
    tp_t base_name;
    tp_t global_name;

    xoico_typespec_s typespec_ret; // return type
    xoico_arg_s => arg_o; // object argument (NULL in case of plain function)
    xoico_args_s args; // e.g.: sz_t a, sz_t b

    bcore_source_point_s source_point;

    func xoico.parse;
    func xoico.get_hash;
    func :.set_global_name;

    func xoico.convert_transient_types = (try)
    {
        if( o.arg_o )
        {
            o.arg_o.convert_transient_types( host, map );
            if
            (
                o.arg_o.typespec.transient &&
                o.typespec_ret.transient &&
                o.arg_o.typespec.transient.class == o.typespec_ret.transient.class
            )
            {
                o.typespec_ret.type = host.obj_type();
            }
        }

        o.args.convert_transient_types( host, map );
        o.typespec_ret.convert_transient_types( host, map );
        return  0;
    };

    func xoico.get_global_name_tp = { return o.global_name; };

    func :.relent = (try)
    {
        if( o.arg_o ) o.arg_o.relent( host, tp_obj_type );
        o.args.relent( host, tp_obj_type );
        o.typespec_ret.relent( host, tp_obj_type );
        return 0;
    };

    func :.expand_declaration;

    func xoico_arg.is_variadic = { return o.args.is_variadic(); };

    func xoico.get_source_point = { return o.source_point; };

    func (bl_t returns_a_value( c @* o )) = { return !o.typespec_ret.is_void(); };

    func (er_t expand_ret( c @* o, c xoico_host* host, m bcore_sink* sink )) = (try)
    {
        o.typespec_ret.expand( host, sink );
        return 0;
    };

    func (er_t expand_ret_x( c @* o, c xoico_host* host, m bcore_sink* sink )) = (try)
    {
        o.typespec_ret.expand_x( host, sink );
        return 0;
    };

    func (c xoico_arg_s* get_arg_by_name( c @* o, tp_t name )) =
    {
        return ( o.arg_o && o.arg_o.name == name ) ? o.arg_o : o.args.get_arg_by_name( name );
    };

};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

embed "xoico_signature.x";

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // XOICO_SIGNATURE_H
