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

#ifndef XOICO_BODY_H
#define XOICO_BODY_H

/**********************************************************************************************************************/

#include "xoico.h"

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( xoico_body, xoico )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signature er_t parse_code( mutable, xoico_stamp_s* stamp, bcore_source* source );
signature er_t parse(      mutable, xoico_stamp_s* stamp, bcore_source* source );
signature er_t expand(     const, sc_t ret_type, sc_t obj_type, const xoico_args_s* args, sz_t indent, bcore_sink* sink );
signature er_t set_group(  mutable, xoico_group_s* group );

stamp : = aware :
{
    st_s name;
    st_s global_name;
    st_s code;
    bl_t go_inline;
    bl_t apply_cengine = true;

    /// use set_group to set this variable
    private aware xoico_group_s* group;
    bcore_source_point_s source_point;

    func xoico : get_hash;
    func xoico : get_global_name_sc;
    func     : : parse_code;
    func     : : parse;
    func     : : expand;
    func     : : set_group;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // XOICO_BODY_H
