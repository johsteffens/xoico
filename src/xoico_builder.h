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

/**********************************************************************************************************************/

XOI_DEFINE_GROUP( xoico_builder, xoico )
#ifdef PLANT_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// returns index of target
signature er_t build( const, sz_t* target_index );

stamp :target = aware :
{
    st_s => name;                  // target name
    st_s => extension = "xoi_out"; // extension used for xoi output files
    st_s => root;                  // root folder of subsequent file paths (used if they are relative)

    private aware :main_s* main;

    bcore_arr_st_s dependencies;   // dependent target definitions
    bcore_arr_st_s sources;        // array of source files

    /** Function name of principal signal handler for this plant
     *  If not defined, it is assumed that the name is <name>_general_signal_handler
     */
    st_s => signal_handler;

    func bcore_via_call : source =
    {
        if( !o->root )
        {
            o->root = bcore_file_folder_path( bcore_source_a_get_file( source ) );
            st_s_attach( &o->root, bcore_file_path_minimized( o->root->sc ) );
        }
    };

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

signature er_t set_overwrite_unsigned_planted_files( mutable, bl_t v );
signature bl_t get_overwrite_unsigned_planted_files( const );

stamp :main = aware :
{
    xoico_compiler_s => compiler;

    bl_t dry_run = false;

    bcore_arr_st_s arr_path;

    func bcore_inst_call : init_x =
    {
        o->compiler = xoico_compiler_s_create();
        xoico_compiler_s_setup( o->compiler );
    };

    func : :build_from_file;
    func : :update_required;
    func : :update;

    func : :set_dry_run =
    {
        o->dry_run = v;
        return 0;
    };

    func : :get_dry_run =
    {
        return o->dry_run;
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

    func : :set_overwrite_unsigned_planted_files =
    {
        o->compiler->overwrite_unsigned_planted_files = v;
        return 0;
    };

    func : :get_overwrite_unsigned_planted_files =
    {
        return o->compiler->overwrite_unsigned_planted_files;
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // PLANT_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/
/// XOICO Interface Functions

/// build plant from configuration file (thread safe)
er_t xoico_build_from_file( sc_t path );

/// Checks if compiled plants require an update of the corresponding panted files (thread safe)
bl_t xoico_update_required( void );

/// Updates all planted files that require an update; returns true if any file was modified. (thread safe)
er_t xoico_update( bl_t* modified );

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

#endif // XOICO_BUILDER_H
