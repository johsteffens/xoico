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

#ifndef XOICO_FEATURE_H
#define XOICO_FEATURE_H

/**********************************************************************************************************************/

#include "xoico.h"
#include "xoico_args.h"
#include "xoico_body.h"
#include "xoico_func.h"
#include "xoico_signature.h"

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( xoico_feature, xoico )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp : = aware :
{
    xoico_signature_s signature;

    xoico_funcs_s funcs;

    xoico_func_s => func_a;
//    xoico_func_s => func_a_defines;
//    xoico_func_s => func_t;
//    xoico_func_s => func_t_defines;

    tp_t function_pointer_name; /// name of function pointer as registered in c-code

    st_s st_default_func_name;
    xoico_body_s => default_body;

    bl_t strict;
    bl_t flag_p;
    bl_t flag_t;
    bl_t flag_a;
    bl_t flag_r;
    bl_t expandable = true;

    hidden aware xoico_group_s* group;
    bcore_source_point_s source_point;

    func xoico.parse;
    func xoico.get_hash;
    func xoico.get_global_name_sc =
    {
        return o.group.compiler.nameof( o.signature.global_name );
    };

    func xoico.finalize;
    func xoico.expand_indef_typedef;
    func xoico.expand_spect_declaration;
    func xoico.expand_spect_definition;
    func xoico.expand_indef_declaration;
    func xoico.expand_definition;
    func xoico.expand_init1;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

embed "xoico_feature.x";

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // XOICO_FEATURE_H
