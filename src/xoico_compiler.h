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

#ifndef XOICO_COMPILER_H
#define XOICO_COMPILER_H

/**********************************************************************************************************************/

#include "xoico.h"
#include "xoico_target.h"
#include "xoico_typespec.h"

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( xoico_compiler, xoico )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signature const xoico* item_get(       const, tp_t item_id );
signature        bl_t  item_exists(    const, tp_t item_id );
signature        er_t  item_register(  mutable, const xoico* item,          bcore_source* source );

signature        er_t  group_register( mutable, const xoico_group_s* group, bcore_source* source );
signature        er_t  type_register(  mutable, tp_t type );

signature        er_t  life_a_push(    mutable, vd_t object );
signature        er_t  check_overwrite( const,  sc_t file );
signature        bl_t  is_type(         const,  tp_t name ); // check if name represents a registered type (either group name or stamp name)
signature        bl_t  get_self(        const,  tp_t type, const bcore_self_s** self ); // returns success

signature const xoico_signature_s* get_signature( const, tp_t item_id ); // returns NULL in case item-Id cannot be resolved to a signature

stamp :element_info = aware :
{
    xoico_typespec_s typespec;
    xoico_signature_s -> signature;
    func bcore_inst_call : copy_x = { o->signature = src->signature; };

};

signature bl_t  get_type_element_info( const,  tp_t type, tp_t name, :element_info_s* info );

// external interface ...
signature er_t setup                         ( mutable );
signature er_t compile                       ( mutable, sc_t target_name, sc_t source_path, const xoico_target_xflags_s* xflags, sz_t* p_target_index );
signature er_t target_set_readonly           ( mutable, sz_t target_index, bl_t readonly );
signature er_t target_set_signal_handler_name( mutable, sz_t target_index, sc_t name );
signature er_t target_set_dependencies       ( mutable, sz_t target_index, const bcore_arr_sz_s* dependencies );
signature er_t target_update_xflags          ( mutable, sz_t target_index, const xoico_target_xflags_s* xflags );
signature er_t update_target_files           ( mutable, bl_t* p_modified );
signature bl_t update_required               ( mutable );
signature sz_t get_verbosity                 ( const );
signature tp_t entypeof                      ( mutable, sc_t name );
signature sc_t nameof                        ( const,   tp_t type ); // returns null in case type is not registered

stamp : = aware :
{
    hidden xoico_target_s => [];
    hidden bcore_hmap_tpvd_s hmap_group;
    hidden bcore_hmap_tpvd_s hmap_item;
    hidden bcore_hmap_tp_s   hmap_type;  // externally registered types
    hidden bcore_life_s      life;       // lifetime manager for items generation during processing
    hidden bcore_hmap_name_s name_map;   // name manager

    // parameters

    /** target_pre_hash: Changing this value changes the hash of all targets.
     *  Purpose: To force rebuild all targets created by an older compiler.
     *  This is used during development or when a new version changes the
     *  target_out files in a material way.
     */
    tp_t target_pre_hash                 = 17;
    bl_t register_plain_functions        = true;
    bl_t register_signatures             = false;
    bl_t overwrite_unsigned_target_files = false;
    bl_t always_expand                   = false; // true: always expands targets even when the hash has not changed;
    bl_t dry_run                         = false; // dry_run: performs target computation but does not update target files
    sz_t verbosity                       = 1;

    // functions
    func xoico :finalize;
    func xoico :expand_setup;
    func : :item_get;
    func : :item_exists;
    func : :item_register;
    func : :group_register;
    func : :type_register;
    func : :is_type;
    func : :life_a_push;
    func : :check_overwrite;
    func : :get_self;
    func : :get_type_element_info;
    func : :get_signature;

    // external interface ...
    func : :setup;
    func : :compile;
    func : :target_set_signal_handler_name;
    func : :target_set_dependencies; // removes duplicates
    func : :target_set_readonly;
    func : :target_update_xflags;
    func : :update_target_files;
    func : :update_required;
    func : :get_verbosity;

    func : :entypeof = { return bcore_hmap_name_s_set_sc( &o->name_map, name ); };
    func : :nameof   = { return bcore_hmap_name_s_get_sc( &o->name_map, type ); };

};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

#endif // XOICO_COMPILER_H
