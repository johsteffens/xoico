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
#ifdef PLANT_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp : = aware :
{
    st_s name;
    st_s global_name;
    bl_t has_ret;        // returns a value
    st_s ret_type;       // return type
    xoico_args_s args;   // e.g.: sz_t a, sz_t b
    tp_t arg_o;          // first argument: mutable | const | 0
    private aware xoico_group_s* group;
    bcore_source_point_s source_point;

    func xoico : parse;
    func xoico : get_hash;
    func xoico : get_global_name_sc;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // PLANT_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // XOICO_SIGNATURE_H
