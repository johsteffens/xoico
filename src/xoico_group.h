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

include 'c' "xoico_nested_group.h";

name x_inst_main;

signature er_t push_item_d( m @* o, d xoico* item );
signature er_t parse_name_recursive( c @* o, m bcore_source* source, m st_s* name );
signature er_t expand_declaration(   c @* o, sz_t indent, m bcore_sink* sink );
signature er_t expand_definition(    c @* o, sz_t indent, m bcore_sink* sink );
signature er_t expand_init1(         c @* o, sz_t indent, m bcore_sink* sink );
signature void explicit_embeddings_push( c @* o, m bcore_arr_st_s* arr );

signature m xoico_source_s*   get_source( c @* o );
signature m xoico_target_s*   get_target( c @* o );
signature m xoico_compiler_s* get_compiler( c @* o );

signature c xoico_func_s* get_func( c @* o, tp_t name ); // returns NULL in case name is not a member function

signature c xoico_func_s* get_trait_line_func_from_name( c @* o, tp_t name );


/// source stack to handle includes
stamp :source_stack_s = aware x_array { aware bcore_source -> []; };

stamp :s = aware :
{
    aware xoico => []; // group elements

    private @* parent; // parent group;

    bcore_arr_st_s includes_in_declaration;
    bcore_arr_st_s includes_in_definition;

    /** List of files explicitly included by embed directive.
     *  Used to list all sources contributing to this target in
     *  copyright and license info.
     */
    bcore_arr_st_s explicit_embeddings;

    st_s st_name; // global name
    tp_t tp_name; // global name

    tp_t trait_name = bcore_inst; // trait name
    tp_t pre_hash;

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

    private xoico_stamp_s* extending_stamp; // !=NULL: extends this stamp on subsequent stamps

    xoico_funcs_s funcs; // functions defined inside the group

    private aware xoico_source_s* xoico_source;
    hidden aware  xoico_compiler_s* compiler;

    bcore_source_point_s => source_point;

    hidden bcore_hmap_tpvd_s hmap_feature;
    hidden bcore_hmap_tpvd_s hmap_func;

    func xoico.parse;
    func xoico.get_hash;
    func xoico.get_global_name_tp = { return o.tp_name; };
    func xoico.finalize;
    func xoico.expand_setup =
    {
        foreach( m $* e in o ) try( e.expand_setup( o ) );
        return 0;
    };

    func :.parse_name_recursive;
    func :.expand_declaration;
    func :.expand_definition;
    func :.expand_init1;

    func :.push_item_d =
    {
        o.cast( m x_array* ).push_d( item );
        return 0;
    };

    func (c @* get_trait_group( c @* o )) =
    {
        return ( o.trait_name != o.tp_name ) ? o.compiler.get_group( o.trait_name ) : NULL;
    };

    func :.get_trait_line_func_from_name =
    {
        if( !o ) return NULL;
        c xoico_func_s** p_func = ( const xoico_func_s** )o.hmap_func.get( name );
        return p_func ? *p_func : o.get_trait_group().get_trait_line_func_from_name( name );
    };

    func :.get_func =
    {
        c xoico_func_s** p_func = ( const xoico_func_s** )o.hmap_func.get( name );
        return p_func ? *p_func : NULL;
    };

    func :.explicit_embeddings_push = { foreach( m st_s* st in o.explicit_embeddings ) arr.push_st( st ); };


    func xoico_host.parse_name_st;
    func xoico_host.parse_name_tp;

    func xoico_host.compiler = { return o.compiler; };
    func xoico_host.cengine =
    {
        return o.xoico_source.target.cengine;
    };
    func xoico_host.obj_type = { return o.tp_name; };
    func xoico_host.create_spect_name;

    func xoico.get_source_point = { return o.source_point; };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

embed "xoico_group.x";

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // XOICO_GROUP_H
