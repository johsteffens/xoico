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

#ifndef XOITE_GROUP_H
#define XOITE_GROUP_H

/**********************************************************************************************************************/

#include "xoite.h"
#include "xoite_funcs.h"

/**********************************************************************************************************************/

BETH_PLANT_DEFINE_GROUP( xoite_group, xoite )
#ifdef PLANT_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signature er_t parse_name(           mutable, st_s* name, bcore_source* source );
signature er_t parse_name_recursive( mutable, st_s* name, bcore_source* source );
signature er_t expand_declaration(   const, sz_t indent, bcore_sink* sink );
signature er_t expand_definition(    const, sz_t indent, bcore_sink* sink );
signature er_t expand_init1(         const, sz_t indent, bcore_sink* sink );
signature xoite_compiler_s* get_compiler( const );

stamp : = aware :
{
    aware xoite => []; // group elements

    st_s name; // global name

    private :s* group; // parent group;

    st_s trait_name = "bcore_inst"; // trait name
    tp_t hash;

    // 'expandable' is set 'false' for groups that is not intended to be expanded into actual code
    // but may contain information referenced in other groups (e.g. global features)
    bl_t expandable = true;
    bl_t has_features;
    bl_t is_aware;
    bl_t retrievable;

    private xoite_stamp_s -> extending; // !=NULL: extends this stamp on subsequent stamps

    xoite_funcs_s  funcs; // functions

    private aware xoite_source_s* source;

    bcore_source_point_s source_point;

    func xoite :parse;
    func xoite :get_hash;
    func xoite :get_global_name_sc;
    func xoite :finalize;

    func : :parse_name;
    func : :parse_name_recursive;
    func : :expand_declaration;
    func : :expand_definition;
    func : :expand_init1;

    func : :get_compiler;

};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // PLANT_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // XOITE_GROUP_H
