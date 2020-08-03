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

#ifndef XOITE_BODY_H
#define XOITE_BODY_H

/**********************************************************************************************************************/

#include "xoite.h"

/**********************************************************************************************************************/

BETH_PLANT_DEFINE_GROUP( xoite_body, xoite )
#ifdef PLANT_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signature er_t parse_code( mutable, xoite_stamp_s* stamp, bcore_source* source );
signature er_t parse(      mutable, xoite_stamp_s* stamp, bcore_source* source );
signature er_t expand(     const, sz_t indent, bcore_sink* sink );

stamp : = aware :
{
    st_s name;
    st_s global_name;
    st_s code;
    bl_t go_inline;

    private xoite_group_s* group;
    bcore_source_point_s source_point;

    func xoite : get_hash;
    func xoite : get_global_name_sc;
    func     : : parse_code;
    func     : : parse;
    func     : : expand;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // PLANT_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // XOITE_BODY_H
