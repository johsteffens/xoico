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

stamp : = aware :
{
    st_s name; // deemed global
    hidden aware xoico_group_s* group;
    bcore_source_point_s source_point;

    func xoico.parse =
    { try {
        o.source_point.set( source );
        if( source.parse_bl_fa( " #?':'" ) )
        {
            st_s* name = st_s!.scope();
            try( source.parse_em_fa( " #name", name ) );
            o.name.push_fa( "#<sc_t>#<sc_t>#<sc_t>", o.group.st_name.sc, name.sc[ 0 ] ? "_" : "", name.sc );
        }
        else
        {
            try( source.parse_em_fa( " #name", &o->name ) );
        }
        if( o.name.size == 0 ) return source.parse_error_fa( "Feature: Name missing." );
        try( source.parse_em_fa( " ; " ) );
        return 0;
    } /* try */ };

    func xoico.get_hash =
    {
        tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o._ );
        hash = bcore_tp_fold_sc( hash, o.name.sc );
        return hash;
    };

    func xoico.get_global_name_sc = { return o->name.sc; };

    func xoico.expand_declaration =
    { try {
        sink.push_fa( "#rn{ }##define TYPEOF_#<sc_t> 0x#pl16'0'{#X<tp_t>}ull\n", indent, o.name.sc, btypeof( o.name.sc ) );
        return 0;
    } /* try */ };

    func xoico.expand_forward =
    { try {
        sink.push_fa( " \\\n#rn{ }BCORE_FORWARD_OBJECT( #<sc_t> );", indent, o.name.sc );
        return 0;
    } /* try */ };

    func xoico.expand_init1 = { return 0; };

};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // XOICO_FORWARD_H
