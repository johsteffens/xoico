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

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( xoico_builder, xoico )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// returns index of target
signature er_t load( mutable, bl_t readonly, sc_t path );
signature er_t build( mutable );
signature const @* name_match( const, sc_t name );

signature void push_target_index_to_arr( const, bcore_arr_sz_s* arr );

stamp :arr_target = aware bcore_array { :target_s => []; };

stamp :target = aware :
{
    st_s => name;                    // unique target name
    st_s => extension = "xoila_out"; // extension used for xoila output files
    st_s => root_folder;             // root folder of subsequent file paths (used if they are relative)
    bl_t readonly;

    /// xflags affect this target and update dependencies
    xoico_target_xflags_s target_xflags;

    bcore_arr_st_s dependencies; // dependent target definitions
    bcore_arr_st_s sources;      // array of source files

    /** Function name of principal signal handler for this target
     *  If not defined, it is assumed that the name is <name>_general_signal_handler
     */
    st_s => signal_handler;

    // Runtime data
    private :target_s* parent;
    private :target_s* root;
    hidden  aware :arr_target_s => dependencies_target;
    hidden  st_s full_path;
    hidden  xoico_compiler_s -> compiler;
    hidden  sz_t target_index = -1; /// Index for target on the compiler; -1 if this target has no representation
    hidden  bcore_hmap_tpvd_s => hmap_built_target; // map of targets that have already been built

    func bcore_via_call : source =
    {
        if( !o->root_folder )
        {
            o->root_folder = bcore_file_folder_path( bcore_source_a_get_file( source ) );
            st_s_attach( &o->root_folder, bcore_file_path_minimized( o->root_folder->sc ) );
        }
    };

    func : : name_match =
    {
        if( o->name && sc_t_equal( name, o->name->sc ) ) return o;
        if( o->parent ) return @_name_match( o->parent, name );
        return NULL;
    };

    func : : push_target_index_to_arr =
    {
        if( o->target_index != -1 )
        {
             bcore_arr_sz_s_push( arr, o->target_index );
        }
        else
        {
            BFOR_EACH( i, o->dependencies_target ) @_push_target_index_to_arr( o->dependencies_target->data[ i ], arr );
        }
    };

    func : : load;
    func : : build;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signature er_t build_from_file( mutable, sc_t path );
signature bl_t update_required( const );
signature er_t update         ( const );

signature er_t set_dry_run( mutable, bl_t v );
signature bl_t get_dry_run( const );

signature er_t set_always_expand( mutable, bl_t v );
signature bl_t get_always_expand( const );

signature er_t set_overwrite_unsigned_target_files( mutable, bl_t v );
signature bl_t get_overwrite_unsigned_target_files( const );

stamp :main = aware :
{
    xoico_compiler_s => compiler!;
    :target_s => target;

    func : :build_from_file;
    func : :update_required;
    func : :update;

    func : :set_dry_run =
    {
        o->compiler->dry_run = v;
        return 0;
    };

    func : :get_dry_run =
    {
        return o->compiler->dry_run;
    };

    func : :set_always_expand =
    {
        o->compiler->always_expand = v;
        return 0;
    };

    func : :get_always_expand =
    {
        return o->compiler->always_expand;
    };

    func : :set_overwrite_unsigned_target_files =
    {
        o->compiler->overwrite_unsigned_target_files = v;
        return 0;
    };

    func : :get_overwrite_unsigned_target_files =
    {
        return o->compiler->overwrite_unsigned_target_files;
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/
/// XOICO Interface Functions

/// build target from configuration file (thread safe)
er_t xoico_build_from_file( sc_t path );

/// Checks if compiled targets require an update of the corresponding target files (thread safe)
bl_t xoico_update_required( void );

/// Updates all target files that require an update; returns true if any file was modified. (thread safe)
er_t xoico_update( bl_t* modified );

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

vd_t xoico_builder_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // XOICO_BUILDER_H
