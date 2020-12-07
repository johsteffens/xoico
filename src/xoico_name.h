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

#ifndef XOICO_NAME_H
#define XOICO_NAME_H

/**********************************************************************************************************************/

#include "xoico.h"
#include "xoico_compiler.h"

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( xoico_name, xoico )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp : = aware :
{
    tp_t name; // deemed global
    bcore_source_point_s source_point;

    func xoico.parse = (try)
    {
        $* compiler = host.compiler();
        o.source_point.set( source );
        $* st_name = st_s!.scope();
        host.parse_name( source, st_name );
        if( st_name.size == 0 ) return source.parse_error_fa( "Name missing." );
        o.name = compiler.entypeof( st_name.sc );
        source.parse_em_fa( " ; " );
        return 0;
    };

    func xoico.get_hash =
    {
        tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
        hash = bcore_tp_fold_tp( hash, o->name );
        return hash;
    };

    func xoico.get_global_name_tp = { return o.name; };

    func xoico.expand_declaration =
    {
        sink.push_fa( "#rn{ }##define TYPEOF_#<sc_t> 0x#pl16'0'{#X<tp_t>}ull\n", indent, host.compiler().nameof( o.name ), o.name );
        return 0;
    };

    func xoico.expand_init1 =
    {
        sink.push_fa( "#rn{ }BCORE_REGISTER_NAME( #<sc_t> );\n", indent, host.compiler().nameof( o.name ) );
        return 0;
    };
};

//----------------------------------------------------------------------------------------------------------------------

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // XOICO_NAME_H
