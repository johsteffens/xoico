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

#ifndef XOICO_BUILDER_H
#define XOICO_BUILDER_H

/**********************************************************************************************************************/

#include "xoico.h"
#include "xoico_target.h"
#include "xoico_compiler.h"
#include "xoico_che.h"

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( xoico_builder, xoico )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// returns index of target
signature er_t load( m @* o, bl_t readonly, sc_t path );
signature er_t build( m @* o );
signature c @* name_match( c @* o, sc_t name );

signature void push_target_index_to_arr( c @* o, m bcore_arr_sz_s* arr );

stamp :arr_target_s = aware x_array { :target_s => []; };

stamp :target_s = aware :
{
    st_s => name;             // unique target name
    st_s => extension = "xo"; // extension used for xoila output files
    st_s => root_folder;      // root folder of subsequent file paths (used if they are relative)
    bl_t readonly;

    bcore_arr_st_s dependencies; // dependent target definitions
    bcore_arr_st_s sources;      // array of source files

    /** Function name of principal signal handler for this target
     *  If not defined, it is assumed that the name is <name>_general_signal_handler
     */
    st_s => signal_handler;

    /// Optional cengine that is to be used in all bodies of this target
    aware xoico_cengine => cengine = xoico_che_s;

    private xoico_compiler_s* compiler;

    // Runtime data
    private @* parent_;
    private @* root_;
    hidden  aware :arr_target_s => dependencies_target_;
    hidden  st_s                   full_path_;
    hidden  sz_t                   target_index_ = -1; // Index for target on the compiler; -1 if this target has no representation
    hidden  bcore_hmap_tpvd_s   => hmap_built_target_; // map of targets that have already been built

    func bcore_via_call.source =
    {
        if( !o->root_folder )
        {
            o->root_folder = bcore_file_folder_path( bcore_source_a_get_file( source ) );
            o.root_folder =< bcore_file_path_minimized( o.root_folder.sc );
        }
    };

    func :.name_match =
    {
        if( o.name && sc_t_equal( name, o.name.sc ) ) return o;
        if( o.parent_ ) return o->parent_.name_match( name );
        return NULL;
    };

    func :.push_target_index_to_arr =
    {
        if( o.target_index_ != -1 )
        {
             arr.push( o.target_index_ );
        }
        else
        {
            foreach( m $* e in o.dependencies_target_ ) e.push_target_index_to_arr( arr );
        }
    };

    func :.load;
    func :.build;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signature er_t build_from_file( m @* o, sc_t path );
signature bl_t update_required( c @* o );
signature er_t update         ( c @* o );

signature er_t set_dry_run( m @* o, bl_t v );
signature bl_t get_dry_run( c @* o );

signature er_t set_always_expand( m @* o, bl_t v );
signature bl_t get_always_expand( c @* o );

signature er_t set_overwrite_unsigned_target_files( m @* o, bl_t v );
signature bl_t get_overwrite_unsigned_target_files( c @* o );

stamp :main_s = aware :
{
    xoico_compiler_s => compiler!;
    :target_s => target;

    func :.build_from_file;
    func :.update_required = { return o.compiler.update_required(); };
    func :.update;

    func :.set_dry_run =
    {
        o.compiler.dry_run = v;
        return 0;
    };

    func :.get_dry_run =
    {
        return o.compiler.dry_run;
    };

    func :.set_always_expand =
    {
        o.compiler.always_expand = v;
        return 0;
    };

    func :.get_always_expand =
    {
        return o.compiler.always_expand;
    };

    func :.set_overwrite_unsigned_target_files =
    {
        o.compiler.overwrite_unsigned_target_files = v;
        return 0;
    };

    func :.get_overwrite_unsigned_target_files =
    {
        return o.compiler.overwrite_unsigned_target_files;
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

embed "xoico_builder.x";

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

#endif // XOICO_BUILDER_H
