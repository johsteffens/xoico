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
signature bl_t reflectable( const, const xoico_host* host );

stamp : = aware :
{
    tp_t name;                   // declarative name (not global name)
    tp_t global_name;            // function name in c-implementation
    tp_t signature_base_name;
    tp_t signature_global_name;
    tp_t obj_type;

    bl_t expandable = true;
    bl_t overloadable = false;
    bl_t declare_in_expand_forward = true;

    xoico_body_s => body;

    tp_t pre_hash = 0;

    hidden aware xoico_signature_s* signature;

    bcore_source_point_s source_point;

    func :.get_hash;

    func :.reflectable =
    {
        return o.expandable && host.compiler().is_feature( o.signature_global_name );
    };

    func xoico.parse;
    func xoico.finalize;
    func xoico.expand_forward;
    func xoico.expand_declaration;
    func xoico.expand_definition;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

embed "xoico_func.x";

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // XOICO_FUNC_H
