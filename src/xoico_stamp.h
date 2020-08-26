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
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signature er_t resolve_chars( const, st_s* string );
signature er_t parse( mutable, xoico_group_s* group, bcore_source* source );
signature er_t make_funcs_overloadable( mutable );

stamp : = aware :
{
    st_s    name;
    st_s    trait_name;
    st_s => self_source;
    bcore_self_s => self; // created in expand_setup
    xoico_funcs_s funcs;

    private aware xoico_group_s* group;
    bcore_source_point_s source_point;

    func xoico : get_hash;
    func xoico : get_global_name_sc;
    func xoico : finalize;

    func xoico : expand_setup;
    func xoico : expand_declaration;
    func xoico : expand_forward;
    func xoico : expand_indef_declaration;
    func xoico : expand_definition;
    func xoico : expand_init1;

    func : : parse;
    func : : resolve_chars;
    func : : make_funcs_overloadable;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // XOICO_STAMP_H
