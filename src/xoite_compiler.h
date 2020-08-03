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

#ifndef XOITE_COMPILER_H
#define XOITE_COMPILER_H

/**********************************************************************************************************************/

#include "xoite.h"

/**********************************************************************************************************************/

BETH_PLANT_DEFINE_GROUP( xoite_compiler, xoite )
#ifdef PLANT_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signature const xoite* item_get(       const, tp_t item_id );
signature        bl_t  item_exists(    const, tp_t item_id );
signature        er_t  item_register(  mutable, const xoite* item,          bcore_source* source );
signature        er_t  group_register( mutable, const xoite_group_s* group, bcore_source* source );
signature        er_t  life_a_push(    mutable, vd_t object );
signature        er_t  check_overwrite( const, sc_t file );

stamp : = aware :
{
    hidden xoite_target_s => [];
    hidden bcore_hmap_tpvd_s hmap_group;
    hidden bcore_hmap_tpvd_s hmap_item;
    hidden bcore_life_s      life; // lifetime manager for items generation during processing

    // parameters
    bl_t backup_planted_files             = true;
    bl_t register_plain_functions         = true;
    bl_t register_signatures              = false;
    bl_t overwrite_unsigned_planted_files = false;
    sz_t verbosity                        = 1;

    // functions
    func xoite :finalize;
    func : :item_get;
    func : :item_exists;
    func : :item_register;
    func : :group_register;
    func : :life_a_push;
    func : :check_overwrite;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // PLANT_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// TODO: move to a context frame
extern xoite_compiler_s* xoite_compiler_g;

/**********************************************************************************************************************/
/// xoite compiler global interface  (TODO: work into builder)

//----------------------------------------------------------------------------------------------------------------------

er_t xoite_compiler_setup( void );
er_t xoite_compiler_compile( sc_t target_name, sc_t source_path, sz_t* p_target_index );
er_t xoite_compiler_set_target_signal_handler_name( sz_t target_index, sc_t name );
er_t xoite_compiler_set_target_dependencies( sz_t target_index, const bcore_arr_sz_s* dependencies );
er_t xoite_compiler_update_planted_files( bl_t* p_modified );
bl_t xoite_compiler_update_required( void );
sz_t xoite_compiler_get_verbosity( void );

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

#endif // XOITE_COMPILER_H
