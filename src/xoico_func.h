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

#ifndef XOICO_FUNC_H
#define XOICO_FUNC_H

/**********************************************************************************************************************/

#include "xoico.h"
#include "xoico_body.h"

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( xoico_func, xoico )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signature tp_t get_hash( const );
signature er_t parse( mutable, bcore_source* source );
signature er_t finalize(   mutable );
signature bl_t registerable( const );

stamp : = aware :
{
    tp_t name; // declarative name (not global name)
    tp_t global_name; // full implementation name
    tp_t signature_global_name;

    st_s flect_decl; // reflection declaration

    bl_t expandable = true;
    bl_t overloadable = false;
    xoico_body_s => body;

    tp_t pre_hash = 0;

    hidden aware xoico_signature_s* signature;

    hidden aware xoico_group_s* group;
    hidden aware xoico_stamp_s* stamp;

    bcore_source_point_s source_point;

    func :.get_hash;
    func :.parse;
    func :.finalize;
    func :.registerable;
    func xoico.expand_forward;
    func xoico.expand_declaration;
    func xoico.expand_definition;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // XOICO_FUNC_H
