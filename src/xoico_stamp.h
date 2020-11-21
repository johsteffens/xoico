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

#ifndef XOICO_STAMP_H
#define XOICO_STAMP_H

/**********************************************************************************************************************/

#include "xoico.h"
#include "xoico_funcs.h"

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( xoico_stamp, xoico )
#ifdef XOILA_SECTION

//----------------------------------------------------------------------------------------------------------------------

signature er_t parse( mutable, bcore_source* source );
signature er_t parse_func( mutable, bcore_source* source );
signature er_t make_funcs_overloadable( mutable );
signature er_t push_default_funcs( mutable );

stamp : = aware :
{
    st_s    st_name;
    tp_t    tp_name; // typeof( st_name )
    st_s    st_trait_name;
    bl_t    is_aware;
    st_s => self_source;
    bcore_self_s => self; // created in expand_setup
    xoico_funcs_s funcs;

    private aware xoico_group_s* group;
    bcore_source_point_s source_point;

    func xoico.get_hash =
    {
        tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
        hash = bcore_tp_fold_sc( hash, o.st_name.sc );
        hash = bcore_tp_fold_sc( hash, o.self_source->sc );
        hash = bcore_tp_fold_tp( hash, o.funcs.get_hash() );
        return hash;
    };

    func xoico.get_global_name_sc = { return o.st_name.sc; };
    func xoico.get_global_name_tp = { return o.tp_name; };
    func xoico.finalize;

    func xoico.expand_setup = { return 0; };
    func xoico.expand_declaration;
    func xoico.expand_forward =
    {
        sink.push_fa( " \\\n#rn{ }BCORE_FORWARD_OBJECT( #<sc_t> );", indent, o.st_name.sc );
        return 0;
    };

    func xoico.expand_indef_declaration =
    {
        sink.push_fa( " \\\n#rn{ }  BETH_EXPAND_ITEM_#<sc_t>", indent, o.st_name.sc );
        return 0;
    };

    func xoico.expand_definition;
    func xoico.expand_init1;

    func :.parse;
    func :.parse_func;

    func :.make_funcs_overloadable =
    {
        foreach( $* func in o->funcs ) func->overloadable = true;
        return 0;
    };

    func :.push_default_funcs;
};

//----------------------------------------------------------------------------------------------------------------------

embed "xoico_stamp.x";

#endif // XOILA_SECTION

/**********************************************************************************************************************/

#endif // XOICO_STAMP_H
