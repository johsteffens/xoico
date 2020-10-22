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

#include "xoico_compiler.h"
#include "xoico_group.h"
#include "xoico_target.h"
#include "xoico_source.h"
#include "xoico_stamp.h"
#include "xoico_funcs.h"
#include "xoico_feature.h"

/**********************************************************************************************************************/

/// returns true if correct signature could be verified
bl_t xoico_compiler_is_signed( sc_t file )
{
    BLM_INIT();
    bcore_source* source = BLM_A_PUSH( bcore_file_open_source( file ) );
    st_s* data = BLM_CREATE( st_s );
    while( !bcore_source_a_eos( source ) ) st_s_push_char( data, bcore_source_a_get_u0( source ) );

    if( data->size < bcore_strlen( "// XOILA_OUT_SIGNATURE" ) ) BLM_RETURNV( bl_t, false );

    sz_t idx = data->size - 1;
    while( idx >= 0 && data->data[ idx ] != '/' ) idx--;
    if( idx > 0 ) idx--;

    if( st_s_find_sc( data, idx, -1, "// XOILA_OUT_SIGNATURE" ) != idx ) BLM_RETURNV( bl_t, false );

    tp_t hash = 0;
    st_s_parse_fa( data, idx, -1, "// XOILA_OUT_SIGNATURE #<tp_t*>", &hash );

    data->data[ idx ] = 0;

    if( hash != bcore_tp_fold_sc( bcore_tp_init(), data->sc ) ) BLM_RETURNV( bl_t, false );

    BLM_RETURNV( bl_t, true );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_compiler_s_check_overwrite( const xoico_compiler_s* o, sc_t file )
{
    BLM_INIT();
    if( !bcore_file_exists( file ) ) BLM_RETURNV( er_t, 0 );

    if( !xoico_compiler_is_signed( file ) )
    {
        st_s* s = BLM_CREATE( st_s );
        st_s_push_fa( s, "Planted file #<sc_t>: Signature check failed.\n", file );
        st_s_push_fa( s, "This file might have been created or edited outside the xoico framework.\n" );
        if( o->overwrite_unsigned_target_files )
        {
            st_s_push_fa( s, "Flag 'overwrite_unsigned_target_files' is 'true'. The file will be overwritten.\n" );
            bcore_sink_a_push_fa( BCORE_STDERR, "\nWARNING: #<sc_t>\n", s->sc );
        }
        else
        {
            st_s_push_fa( s, "Xoico has currently no permission to overwrite unsigned target files.\n" );
            st_s_push_fa( s, "You can fix it in one of following ways:\n" );
            st_s_push_fa( s, "* Rename or (re)move the file.\n" );
            st_s_push_fa( s, "* Use command line flag '-f'.\n" );
            BLM_RETURNV( er_t, bcore_error_push_fa( TYPEOF_general_error, "\nERROR: #<sc_t>\n", s->sc ) );
        }
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/// returns false if already registered; checks for collision
er_t xoico_compiler_s_group_register( xoico_compiler_s* o, const xoico_group_s* group, bcore_source* source )
{
    BLM_INIT();
    if( bcore_hmap_tpvd_s_exists( &o->hmap_group, group->tp_name ) )
    {
        XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "'#<sc_t>' was already registered\n", xoico_compiler_s_nameof( o, group->tp_name ) );
    }
    bcore_hmap_tpvd_s_set( &o->hmap_group, group->tp_name, ( vd_t )group );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/// returns false if already registered;
er_t xoico_compiler_s_item_register( xoico_compiler_s* o, const xoico* item, bcore_source* source )
{
    BLM_INIT();
    tp_t global_id = xoico_a_get_global_name_tp( item );
    if( bcore_hmap_tpvd_s_exists( &o->hmap_item, global_id ) )
    {
        XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "'#<sc_t>' was already registered\n", xoico_compiler_s_nameof( o, global_id ) );
    }

    bcore_hmap_tpvd_s_set( &o->hmap_item, global_id, ( vd_t )item );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/// returns false if already registered;
er_t xoico_compiler_s_type_register( xoico_compiler_s* o, tp_t type )
{
    bcore_hmap_tp_s_set( &o->hmap_type, type );
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

bl_t xoico_compiler_s_is_group( const xoico_compiler_s* o, tp_t name )
{
    if( bcore_hmap_tpvd_s_exists( &o->hmap_group, name ) )
    {
        return true;
    }
    return false;
}

//----------------------------------------------------------------------------------------------------------------------

bl_t xoico_compiler_s_is_stamp( const xoico_compiler_s* o, tp_t name )
{
    if( bcore_hmap_tpvd_s_exists( &o->hmap_item, name ) )
    {
        const xoico* item = xoico_compiler_s_const_item_get( o, name );
        if( item->_ == TYPEOF_xoico_stamp_s ) return true;
    }
    return false;
}

//----------------------------------------------------------------------------------------------------------------------

bl_t xoico_compiler_s_is_type( const xoico_compiler_s* o, tp_t name )
{
    if( xoico_compiler_s_is_stamp( o, name ) ) return true;
    if( xoico_compiler_s_is_group( o, name ) ) return true;
    if( bcore_hmap_tp_s_exists( &o->hmap_type, name ) ) return true;
    return false;
}

//----------------------------------------------------------------------------------------------------------------------

const xoico_signature_s* xoico_compiler_s_get_signature( const xoico_compiler_s* o, tp_t item_id )
{
    const xoico* item = xoico_compiler_s_const_item_get( o, item_id );
    if( item )
    {
        if( *(aware_t*)item == TYPEOF_xoico_feature_s )
        {
            return &( ( xoico_feature_s* )item )->signature;
        }
        else if( *(aware_t*)item == TYPEOF_xoico_signature_s )
        {
            return ( const xoico_signature_s* )item;
        }
    }

    return NULL;
}

//----------------------------------------------------------------------------------------------------------------------

/** returns target index */
er_t xoico_compiler_s_parse( xoico_compiler_s* o, sc_t target_name, sc_t source_path, sz_t* p_target_index )
{
    BLM_INIT();

    st_s* source_folder_path = BLM_A_PUSH( bcore_file_folder_path( source_path ) );
    st_s* target_path        = BLM_A_PUSH( st_s_create_fa( "#<sc_t>/#<sc_t>", source_folder_path->sc, target_name ) );

    sz_t target_index = -1;
    for( sz_t i = 0; i < o->size; i++ )
    {
        if( st_s_equal_st( target_path, &o->data[ i ]->path ) )
        {
            target_index = i;
            break;
        }
    }

    if( target_index == -1 )
    {
        BLM_INIT();
        xoico_target_s* target = BLM_CREATE( xoico_target_s );
        target->compiler = o;
        st_s_copy_sc( &target->name, target_name );
        st_s_copy(    &target->path, target_path );
        bcore_array_a_push( ( bcore_array* )o, sr_asd( bcore_fork( target ) ) );
        target_index = o->size - 1;
        BLM_DOWN();
    }

    xoico_target_s* target = o->data[ target_index ];

    BLM_TRY( xoico_target_s_parse( target, source_path ) );

    if( p_target_index ) *p_target_index = target_index;

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_compiler_s_finalize( xoico_compiler_s* o )
{
    BLM_INIT();
    for( sz_t i = 0; i < o->size; i++ ) BLM_TRY( xoico_target_s_finalize( o->data[ i ] ) );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_compiler_s_expand_setup( xoico_compiler_s* o )
{
    BLM_INIT();
    for( sz_t i = 0; i < o->size; i++ ) BLM_TRY( xoico_target_s_expand_setup( o->data[ i ] ) );

    /* We obtain all names from the global map.
     * This is necessary because names of reflection elements are parsed outside
     * this framework and remembered by the global map.
     */
    bcore_name_push_all( &o->name_map );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/// returns true if a file will be modified in function xoico_compiler_s_expand
bl_t xoico_compiler_s_to_be_modified( const xoico_compiler_s* o )
{
    for( sz_t i = 0; i < o->size; i++ )
    {
        if( xoico_target_s_to_be_modified( o->data[ i ] ) ) return true;
    }
    return false;
}

//----------------------------------------------------------------------------------------------------------------------

/// returns true if a file was modified
er_t xoico_compiler_s_expand( xoico_compiler_s* o, bl_t* p_modified )
{
    BLM_INIT();
    bl_t modified = false;

    BLM_TRY( xoico_compiler_s_expand_setup( o ) );
    for( sz_t i = 0; i < o->size; i++ ) BLM_TRY( xoico_target_s_expand_phase1( o->data[ i ], &modified ) );
    for( sz_t i = 0; i < o->size; i++ ) BLM_TRY( xoico_target_s_expand_phase2( o->data[ i ], &modified ) );

    if( p_modified ) *p_modified = modified;
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/// adds an item to lifetime manager
er_t xoico_compiler_s_life_a_push( xoico_compiler_s* o, vd_t object )
{
    bcore_life_s_push_aware( &o->life, object );
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

bl_t xoico_compiler_s_get_self( const xoico_compiler_s* o, tp_t type, const bcore_self_s** self )
{
    const xoico** p_item = ( const xoico** )bcore_hmap_tpvd_s_get( &o->hmap_item, type );
    if( !p_item ) return false;

    const xoico* item = *p_item;

    if( item->_ == TYPEOF_xoico_stamp_s )
    {
        const xoico_stamp_s* stamp = ( const xoico_stamp_s* )item;
        if( self ) *self = stamp->self;
        return true;
    }

    return false;
}

//----------------------------------------------------------------------------------------------------------------------

bl_t xoico_compiler_s_get_type_info( const xoico_compiler_s* o, tp_t type, xoico_compiler_type_info_s* info )
{
    const xoico** p_item = ( const xoico** )bcore_hmap_tpvd_s_get( &o->hmap_item, type );
    if( !p_item ) return false;
    ASSERT( info );
    const xoico* item = *p_item;

    if( item->_ == TYPEOF_xoico_stamp_s || item->_ == TYPEOF_xoico_group_s )
    {
        info->item = ( xoico* )item;
        info->typespec.type = type;
        return true;
    }

    return false;
}

//----------------------------------------------------------------------------------------------------------------------

bl_t xoico_compiler_s_get_type_element_info( const xoico_compiler_s* o, tp_t type, tp_t name, xoico_compiler_element_info_s* info )
{
    const xoico** p_item = ( const xoico** )bcore_hmap_tpvd_s_get( &o->hmap_item, type );
    bl_t success = false;

    if( !p_item )
    {
        p_item = ( const xoico** )bcore_hmap_tpvd_s_get( &o->hmap_group, type );
        if( !p_item ) return false;
    }

    ASSERT( info );

    const xoico* xoico_item = *p_item;
    info->type_info.item = ( xoico* )xoico_item;

    if( xoico_item->_ == TYPEOF_xoico_stamp_s )
    {
        const xoico_stamp_s* stamp = ( const xoico_stamp_s* )xoico_item;
        const bcore_self_s* self = stamp->self;
        if( !xoico_compiler_s_get_self( o, type, &self ) ) return false;

        const bcore_self_item_s* self_item = bcore_self_s_get_item_by_name( self, name ); // returns NULL in case of no match

        bl_t found = true;
        sz_t indirection = 0;

        if( self_item )
        {
            switch( self_item->caps )
            {
                case BCORE_CAPS_SOLID_STATIC: indirection = 0; break;
                case BCORE_CAPS_LINK_STATIC:  indirection = 1; break;
                case BCORE_CAPS_LINK_TYPED:   indirection = 1; break;
                case BCORE_CAPS_LINK_AWARE:   indirection = 1; break;
                case BCORE_CAPS_POINTER:      indirection = 1; break;
                case BCORE_CAPS_ARRAY_DYN_SOLID_STATIC:
                case BCORE_CAPS_ARRAY_DYN_SOLID_TYPED:
                case BCORE_CAPS_ARRAY_DYN_LINK_STATIC:
                case BCORE_CAPS_ARRAY_DYN_LINK_TYPED:
                case BCORE_CAPS_ARRAY_DYN_LINK_AWARE:
                case BCORE_CAPS_ARRAY_FIX_SOLID_STATIC:
                case BCORE_CAPS_ARRAY_FIX_LINK_STATIC:
                case BCORE_CAPS_ARRAY_FIX_LINK_AWARE:
                {
                    /// arrays are handled separately
                    return false;
                }
                break;

                case BCORE_CAPS_EXTERNAL_FUNC:
                {
                    found = false;
                }
                break;

                default:
                {
                    found = false;
                }
                break;
            }
        }
        else
        {
            found = false;
        }

        info->type_info.typespec.flag_const = false;

        if( !found )
        {
            // try function
            xoico_func_s* func = xoico_funcs_s_get_func_from_name( &stamp->funcs, name );
            if( func )
            {
                info->type_info.typespec.type = func->global_name;
                info->type_info.typespec.indirection = 0;
                const xoico_signature_s* signature = xoico_compiler_s_get_signature( o, func->type );
                info->type_info.typespec.flag_const = ( signature->arg_o == TYPEOF_const );
                xoico_signature_s_attach( &info->signature, xoico_signature_s_clone( signature ) );
                xoico_signature_s_relent( info->signature, self->type );
                success = true;
            }
            else // try generic types
            {
                success = false;
            }
        }
        else
        {
            info->type_info.typespec.type = self_item->type;
            info->type_info.typespec.indirection = indirection;
            info->signature = NULL;
            success = true;
        }
    }
    else if( xoico_item->_ == TYPEOF_xoico_group_s )
    {
        xoico_group_s* group = ( xoico_group_s* )xoico_item;
        if( bcore_hmap_tpvd_s_exists( &group->hmap_feature, name ) )
        {
            info->type_info.typespec.flag_const = false;
            xoico_feature_s* feature = *bcore_hmap_tpvd_s_get( &group->hmap_feature, name );
            if( feature->flag_a )
            {
                const xoico_signature_s* signature = &feature->signature;
                info->type_info.typespec.flag_const = ( signature->arg_o == TYPEOF_const );
                sc_t  st_func_name = xoico_compiler_s_nameof( o, name );
                ASSERT( st_func_name );
                st_s* st_full_func_name = st_s_create_fa( "#<sc_t>_a_#<sc_t>", group->st_name.sc, st_func_name );
                info->type_info.typespec.type = xoico_compiler_s_entypeof( ( xoico_compiler_s* )o, st_full_func_name->sc );
                info->type_info.typespec.indirection = 0;
                xoico_signature_s_attach( &info->signature, xoico_signature_s_clone( signature ) );
                xoico_signature_s_relent( info->signature, group->tp_name );
                st_s_discard( st_full_func_name );
                success = true;
            }
        }
    }

    return success;
}

//----------------------------------------------------------------------------------------------------------------------

bl_t xoico_compiler_s_get_type_array_element_info( const xoico_compiler_s* o, tp_t type, xoico_compiler_element_info_s* info )
{
    const xoico** p_item = ( const xoico** )bcore_hmap_tpvd_s_get( &o->hmap_item, type );
    bl_t success = false;
    if( !p_item ) return false;

    ASSERT( info );

    const xoico* xoico_item = *p_item;
    info->type_info.item = ( xoico* )xoico_item;

    tp_t tp_no_name = btypeof( "" );

    if( xoico_item->_ == TYPEOF_xoico_stamp_s )
    {
        const xoico_stamp_s* stamp = ( const xoico_stamp_s* )xoico_item;
        const bcore_self_s* self = stamp->self;
        if( !xoico_compiler_s_get_self( o, type, &self ) ) return false;

        sz_t items = bcore_self_s_items_size( self );
        const bcore_self_item_s* self_item = NULL;
        for( sz_t i = 0; i < items; i++ )
        {
            const bcore_self_item_s* item = bcore_self_s_get_item( self, i );
            if( item->name == tp_no_name && bcore_flect_caps_is_array( item->caps ) )
            {
                self_item = item;
                break;
            }
        }

        if( self_item )
        {
            sz_t indirection = 0;
            switch( self_item->caps )
            {
                case BCORE_CAPS_ARRAY_DYN_SOLID_STATIC: indirection = 0; break;
                case BCORE_CAPS_ARRAY_DYN_SOLID_TYPED:  indirection = 0; break;
                case BCORE_CAPS_ARRAY_DYN_LINK_STATIC:  indirection = 1; break;
                case BCORE_CAPS_ARRAY_DYN_LINK_TYPED:   indirection = 1; break;
                case BCORE_CAPS_ARRAY_DYN_LINK_AWARE:   indirection = 1; break;
                case BCORE_CAPS_ARRAY_FIX_SOLID_STATIC: indirection = 0; break;
                case BCORE_CAPS_ARRAY_FIX_LINK_STATIC:  indirection = 1; break;
                case BCORE_CAPS_ARRAY_FIX_LINK_AWARE:   indirection = 1; break;

                default:
                {
                    ERR_fa( "Invalid array caps" );
                }
                break;
            }

            info->type_info.typespec.type = self_item->type;
            info->type_info.typespec.indirection = indirection;
            info->signature = NULL;
            success = true;
        }
    }

    return success;
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// xoico interface

//----------------------------------------------------------------------------------------------------------------------

/// returns target index
er_t xoico_compiler_s_compile( xoico_compiler_s* o, sc_t target_name, sc_t source_path, sz_t* p_target_index )
{
    BLM_INIT();
    BLM_TRY( xoico_compiler_s_parse( o, target_name, source_path, p_target_index ) );
    BLM_TRY( xoico_compiler_s_finalize( o ) );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_compiler_s_update_target_files( xoico_compiler_s* o, bl_t* p_modified )
{
    BLM_INIT();
    bl_t modified = false;
    bl_t verbosity = o->verbosity;
    f3_t time = 0;

    ABS_TIME_OF( BLM_TRY( xoico_compiler_s_expand( o, &modified ) ), time );
    if( modified )
    {
        if( verbosity > 0 ) bcore_msg_fa( "XOICO: Expanded in #<f3_t> sec.\n", time );
        if( verbosity > 0 ) bcore_msg_fa( "XOICO: Files were updated. Rebuild is necessary.\n" );
    }

    if( p_modified ) *p_modified = modified;

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

bl_t xoico_compiler_s_update_required( xoico_compiler_s* o )
{
    return xoico_compiler_s_to_be_modified( o );
}

//----------------------------------------------------------------------------------------------------------------------

sz_t xoico_compiler_s_get_verbosity( const xoico_compiler_s* o )
{
    return o->verbosity;
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

