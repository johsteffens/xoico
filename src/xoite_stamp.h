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

#ifndef XOITE_STAMP_H
#define XOITE_STAMP_H

/**********************************************************************************************************************/

#include "xoite.h"
#include "xoite_funcs.h"

/**********************************************************************************************************************/

BETH_PLANT_DEFINE_GROUP( xoite_stamp, xoite )
#ifdef PLANT_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signature er_t resolve_chars( const, st_s* string );
signature er_t parse( mutable, xoite_group_s* group, bcore_source* source );
signature er_t make_funcs_overloadable( mutable );

stamp : = aware :
{
    st_s    name;
    st_s    trait_name;
    st_s => self_source;
    xoite_funcs_s funcs;

    private aware xoite_group_s* group;
    bcore_source_point_s source_point;

    func xoite : get_hash;
    func xoite : get_global_name_sc;
    func xoite : finalize;

    func xoite : expand_declaration;
    func xoite : expand_forward;
    func xoite : expand_indef_declaration;
    func xoite : expand_definition;
    func xoite : expand_init1;

    func : : parse;
    func : : resolve_chars;
    func : : make_funcs_overloadable;

    func bcore_inst_call : copy_x =
    {
        BFOR_EACH( i, &o->funcs ) o->funcs.data[ i ]->group = o->group;
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // PLANT_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // XOITE_STAMP_H
