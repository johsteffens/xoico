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

#ifndef XOICO_FORWARD_H
#define XOICO_FORWARD_H

/**********************************************************************************************************************/

#include "xoico.h"

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( xoico_forward, xoico )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :s = aware :
{
    tp_t name; // deemed global
    hidden aware xoico_group_s* group;
    bcore_source_point_s source_point;

    func xoico.parse = (try)
    {
        o.source_point.set( source );
        host.parse_name_tp( source, o.name.1 );
        source.parse_em_fa( " ; " );
        return 0;
    };

    func xoico.get_hash =
    {
        tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o._ );
        hash = bcore_tp_fold_tp( hash, o.name );
        return hash;
    };

    func xoico.get_global_name_tp = { return o->name; };

    func xoico.expand_declaration = (try)
    {
        sink.push_fa( "#rn{ }##define TYPEOF_#<sc_t> 0x#pl16'0'{#X<tp_t>}ull\n", indent, host.nameof( o.name ), o.name );
        return 0;
    };

    func xoico.expand_forward = (try)
    {
        sink.push_fa( " \\\n#rn{ }BCORE_FORWARD_OBJECT( #<sc_t> );", indent, host.nameof( o.name ) );
        return 0;
    };

    func xoico.expand_init1 = { return 0; };

};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // XOICO_FORWARD_H
