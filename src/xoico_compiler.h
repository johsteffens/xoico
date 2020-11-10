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

signature er_t register_item(  mutable, const xoico* item,          bcore_source* source );
signature er_t register_group( mutable, const xoico_group_s* group );
signature er_t register_func(  mutable, const xoico_func_s* func );
signature er_t register_external_type( mutable, tp_t type );

signature bl_t is_item(  const, tp_t name );
signature bl_t is_group( const, tp_t name ); // checks if name represents a registered group
signature bl_t is_func(  const, tp_t name ); // checks if name represents the global name of a function (==name of implementation)
signature bl_t is_stamp( const, tp_t name ); // checks if name represents a registered stamp
signature bl_t is_type(  const, tp_t name ); // checks if name represents a registered type (either group, stamp, or external type)
signature bl_t is_signature( const, tp_t name ); // checks if name represents a registered signature
signature bl_t is_feature( const, tp_t name ); // checks if name represents a registered feature
signature bl_t is_signature_or_feature( const, tp_t name ); // checks if name represents a registered signature or feature

// getters below return NULL in case object was not registered
signature xoico* get_item( mutable, tp_t name );
signature const xoico* get_const_item( const,  tp_t name );
signature xoico_stamp_s* get_stamp( mutable, tp_t name );
signature xoico_func_s*  get_func(  mutable, tp_t name );
signature xoico_group_s* get_group( mutable, tp_t name );
signature const xoico_feature_s* get_feature( const, tp_t name );

/// returns signature in case name represents a signature or feature
signature const xoico_signature_s* get_signature( const, tp_t name );

signature er_t  life_a_push(    mutable, bcore_inst* object );
signature er_t  check_overwrite( const,  sc_t file );
signature bl_t  get_self(        const,  tp_t type, const bcore_self_s** self ); // returns success


stamp :type_info = aware :
{
    xoico_typespec_s typespec;
    hidden xoico* item; // group or stamp
};

stamp :element_info = aware :
{
    :type_info_s type_info;
    xoico_signature_s => signature;
};

signature bl_t get_type_info(               const, tp_t type,            :type_info_s*    info );
signature bl_t get_type_element_info(       const, tp_t type, tp_t name, :element_info_s* info );
signature bl_t get_type_array_element_info( const, tp_t type,            :element_info_s* info );

// external interface ...
signature er_t parse              ( mutable, sc_t target_name, sc_t source_path, sz_t* p_target_index );
signature er_t update_target_files( mutable, bl_t* p_modified );
signature bl_t update_required    ( mutable );
signature sz_t get_verbosity      ( const );
signature tp_t entypeof           ( mutable, sc_t name );
signature sc_t nameof             ( const,   tp_t type );

stamp : = aware :
{
    hidden xoico_target_s => [];
    hidden bcore_life_s life; // lifetime manager for items generation during processing

    hidden bcore_hmap_tpvd_s hmap_group;
    hidden bcore_hmap_tpvd_s hmap_item;
    hidden bcore_hmap_tpvd_s hmap_func;  // maps the global name of a function to the func instance
    hidden bcore_hmap_tp_s   hmap_external_type; // externally registered types
    hidden bcore_hmap_name_s name_map;   // name manager

    // parameters

    /** target_pre_hash: Changing this value changes the hash of all targets.
     *  Purpose: To force rebuild all targets created by an older compiler.
     *  This is used during development or when a new version changes the
     *  target_out files in a material way.
     */
    tp_t target_pre_hash                 = 71;
    bl_t work_build_time_into_pre_hash   = true;
    bl_t register_non_feature_functions  = true;
    bl_t register_signatures             = false;
    bl_t overwrite_unsigned_target_files = false;
    bl_t always_expand                   = false; // true: always expands targets even when the hash has not changed;
    bl_t dry_run                         = false; // dry_run: performs target computation but does not update target files
    sz_t verbosity                       = 1;

    // functions
    func xoico.finalize;
    func xoico.expand_setup;

    func :.register_item;
    func :.register_group;
    func :.register_func;
    func :.register_external_type = { o.hmap_external_type.set( type ); return 0; };

    func :.is_item  = { return o.hmap_item.exists( name ); };
    func :.is_group = { return o.hmap_group.exists( name ); };
    func :.is_func  = { return o.hmap_func.exists( name ); };

    func :.is_type =
    {
        if( o.is_group( name ) ) return true;
        if( o.is_stamp( name ) ) return true;
        if( o.hmap_external_type.exists( name ) ) return true;
        return false;
    };

    func :.is_stamp =
    {
        const xoico* item = o.get_const_item( name );
        if( item && ( item->_ == TYPEOF_xoico_stamp_s ) ) return true;
        return false;
    };

    func :.is_signature =
    {
        const xoico* item = o.get_const_item( name );
        if( item && ( item->_ == TYPEOF_xoico_signature_s ) ) return true;
        return false;
    };

    func :.is_signature_or_feature =
    {
        const xoico* item = o.get_const_item( name );
        if( !item ) return NULL;
        if( item->_ == TYPEOF_xoico_signature_s || item->_ == TYPEOF_xoico_feature_s ) return true;
        return false;
    };

    func :.is_feature =
    {
        const xoico* item = o.get_const_item( name );
        if( item && ( item->_ == TYPEOF_xoico_feature_s ) ) return true;
        return false;
    };

    func :.get_const_item =
    {
        vd_t* ptr = o.hmap_item.get( name );
        return ptr ? ( const xoico* )*ptr : NULL;
    };

    func :.get_item =
    {
        vd_t* ptr = o.hmap_item.get( name );
        return ptr ? ( xoico* )*ptr : NULL;
    };

    func :.get_stamp =
    {
        const xoico* item = o.get_const_item( name );
        return ( item ) ? ( item._ == TYPEOF_xoico_stamp_s ) ? item.cast( xoico_stamp_s* ) : NULL : NULL;
    };

    func :.get_feature =
    {
        const xoico* item = o.get_const_item( name );
        return ( item ) ? ( item._ == TYPEOF_xoico_feature_s ) ? item.cast( xoico_feature_s* ) : NULL : NULL;
    };

    func :.get_signature =
    {
        const xoico* item = o.get_const_item( name );
        if( !item ) return NULL;
        if( item._ == TYPEOF_xoico_signature_s ) return item.cast( xoico_signature_s* );
        if( item._ == TYPEOF_xoico_feature_s   ) return item.cast( xoico_feature_s* ).signature;
        return NULL;
    };

    func :.get_group =
    {
        vd_t* ptr = o.hmap_group.get( name );
        return ptr ? ( xoico_group_s* )*ptr : NULL;
    };

    func :.get_func =
    {
        vd_t* ptr = o.hmap_func.get( name );
        return ptr ? ( xoico_func_s* )*ptr : NULL;
    };

    func :.life_a_push =
    {
        bcore_life_s_push_aware( &o->life, object );
        return 0;
    };

    func :.check_overwrite;
    func :.get_self;
    func :.get_type_info;
    func :.get_type_element_info;
    func :.get_type_array_element_info;

    // external interface ...
    func :.parse;
    func :.update_target_files;
    func :.update_required = { return o.to_be_modified(); };
    func :.get_verbosity = { return o.verbosity; };

    func :.entypeof = { return bcore_hmap_name_s_set_sc( &o->name_map, name ); };
    func :.nameof   = { return bcore_hmap_name_s_get_sc( &o->name_map, type ); };

    func bcore_inst_call.init_x =
    {
        if( o-> work_build_time_into_pre_hash )
        {
            o->target_pre_hash = bcore_tp_fold_sc( o->target_pre_hash, __DATE__ );
            o->target_pre_hash = bcore_tp_fold_sc( o->target_pre_hash, __TIME__ );
        }
    };

    func (void push_d( mutable, xoico_target_s* target )) =
    {
        o.cast( bcore_array* ).push( sr_asd( target ) );
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

embed "xoico_compiler.x";

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

#endif // XOICO_COMPILER_H
