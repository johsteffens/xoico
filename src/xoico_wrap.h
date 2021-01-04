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

#ifndef XOICO_WRAP_H
#define XOICO_WRAP_H

/**********************************************************************************************************************/

/** Main Interface */

/**********************************************************************************************************************/

#include "xoico.h"

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( xoico_wrap, bcore_inst )
#ifdef XOILA_SECTION

//----------------------------------------------------------------------------------------------------------------------

stamp :s = aware :
{
    tp_t group_name;
    tp_t func_name;
    bcore_source_point_s source_point;

    xoico_signature_s => signature;
    xoico_func_s => func;

    func xoico.parse = (try)
    {
        source.parse_em_fa( " " );
        host.parse_name_tp( source, o.group_name.1 );
        m $* st = st_s!^^;
        source.parse_em_fa( " . #name ", st );
        if( st.size == 0 ) source.parse_error_fa( "Function name expected." );
        o.func_name = host.entypeof( st.sc );
        source.parse_em_fa( ";" );
        return 0;
    };

    func xoico.finalize = (try)
    {
        m $* compiler = host.compiler();
        const xoico_group_s* group = compiler.get_group( o.group_name );
        if( !group ) o.source_point.parse_error_fa( "Wrap: '#<sc_t>' is not a group.", compiler.nameof( o.group_name ) );
        const xoico_func_s* func = group.get_func( o.func_name );
        if( !func ) o.source_point.parse_error_fa( "Wrap: '#<sc_t>' is not a function in group '#<sc_t>'.", compiler.nameof( o.func_name ), compiler.nameof( o.group_name ) );

        o.signature!;
        o.signature.copy( func.signature );
        o.signature.set_global_name( host );
        o.signature.convert_transient_types( host, host.transient_map() );
        compiler.register_item( o.signature );

        o.func!;
        o.func.name = o.signature.name;
        o.func.signature_global_name = o.signature.global_name;

        m st_s* st = st_s!^^;
        st.push_fa( "={" );
        if( o.signature.returns_a_value() ) st.push_sc( "return " );

        st.push_fa( "#<sc_t>_#<sc_t>(", host.nameof( group.tp_name ), host.nameof( func.name ) );

        if( o.signature.arg_o )
        {
            o.signature.arg_o.expand_name( host, st );
            o.signature.args.expand_name( host, false, st );
        }
        else
        {
            o.signature.args.expand_name( host, true, st );
        }

        st.push_fa( ");};" );

        o.func.body!;
        o.func.body.parse( host, bcore_source_string_s_create_from_sc( st.sc ).scope() );

        return 0;
    };

    func xoico.get_source_point = { return o.source_point; };
};

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

#endif // XOICO_WRAP_H
