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

#ifndef XOICO_GROUP_H
#define XOICO_GROUP_H

/**********************************************************************************************************************/

#include "xoico.h"
#include "xoico_funcs.h"

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( xoico_group, xoico )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signature er_t parse_name(           mutable, st_s* name, bcore_source* source );
signature er_t parse_name_recursive( mutable, st_s* name, bcore_source* source );
signature er_t expand_declaration(   const, sz_t indent, bcore_sink* sink );
signature er_t expand_definition(    const, sz_t indent, bcore_sink* sink );
signature er_t expand_init1(         const, sz_t indent, bcore_sink* sink );
signature st_s* create_spect_name( const );

signature xoico_source_s*   get_source( const );
signature xoico_target_s*   get_target( const );
signature xoico_compiler_s* get_compiler( const );

/// source stack to handle includes
stamp :source_stack = aware bcore_array { aware bcore_source -> []; };

stamp : = aware :
{
    aware xoico => []; // group elements

    st_s st_name; // global name
    tp_t tp_name; // global name

    private :s* group; // parent group;

    st_s trait_name = "bcore_inst"; // trait name
    tp_t hash;

    /** Beta values > 0 represent experimental or transitional states in development
     *  They can be specified using the set directive: e.g. set beta = 1;
     */
    tp_t beta = 0;

    // 'expandable' is set 'false' for groups that is not intended to be expanded into actual code
    // but may contain information referenced in other groups (e.g. global features)
    bl_t expandable = true;

    bl_t retrievable;

    /** Activates using the short perspective type name.
     *  Normally the perspective type of a group is '<group_name>_spect_s'
     *  The short version is '<group_name>_s' can clash with stamp names.
     *  It should only be used for mapping low level perspectives into the xoila framework.
     *  (e.g. in inexpandable groups)
     */
    bl_t short_spect_name;

    private xoico_stamp_s -> extending; // !=NULL: extends this stamp on subsequent stamps

    //xoico_funcs_s funcs; // functions

    private aware xoico_source_s* source;

    bcore_source_point_s source_point;

    hidden bcore_hmap_tpvd_s hmap_feature;

    func xoico :parse;
    func xoico :get_hash;
    func xoico :get_global_name_sc;
    func xoico :get_global_name_tp = { return o->tp_name; };
    func xoico :finalize;
    func xoico :expand_setup;

    func : :create_spect_name;
    func : :parse_name;
    func : :parse_name_recursive;
    func : :expand_declaration;
    func : :expand_definition;
    func : :expand_init1;

    func : :get_source;
    func : :get_target;
    func : :get_compiler;

};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // XOICO_GROUP_H
