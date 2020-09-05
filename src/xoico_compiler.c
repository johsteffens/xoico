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
            st_s_push_fa( s, "* Rename or move the file.\n" );
            st_s_push_fa( s, "* Allow overwrite by setting flag 'overwrite_unsigned_target_files' 'true'.\n" );
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
    sc_t global_name = group->name.sc;
    tp_t global_id = typeof( global_name );
    if( bcore_hmap_tpvd_s_exists( &o->hmap_group, global_id ) )
    {
        /// check collision
        const xoico_group_s* group2 = *bcore_hmap_tpvd_s_get( &o->hmap_group, global_id );
        sc_t global_name2 = group2->name.sc;

        if( !sc_t_equal( global_name, global_name2 ) )
        {
            XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Collision detected: '#<sc_t>' and '#<sc_t>' produce same hash\n", global_name, global_name2 );
        }
        else
        {
            XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "'#<sc_t>' was already registered\n", global_name );
        }
    }
    bcore_hmap_tpvd_s_set( &o->hmap_group, global_id, ( vd_t )group );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/// returns false if already registered; checks for collision
er_t xoico_compiler_s_item_register( xoico_compiler_s* o, const xoico* item, bcore_source* source )
{
    BLM_INIT();
    sc_t global_name = xoico_a_get_global_name_sc( item );
    tp_t global_id = typeof( global_name );
    if( bcore_hmap_tpvd_s_exists( &o->hmap_item, global_id ) )
    {
        /// check collision
        const xoico* item2 = *bcore_hmap_tpvd_s_get( &o->hmap_item, global_id );
        sc_t global_name2 = xoico_a_get_global_name_sc( item2 );
        if( !sc_t_equal( global_name, global_name2 ) )
        {
            XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Collision detected: '#<sc_t>' and '#<sc_t>' produce same hash\n", global_name, global_name2 );
        }
        else
        {
            XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "'#<sc_t>' was already registered\n", global_name );
        }
    }

    bcore_hmap_tpvd_s_set( &o->hmap_item, global_id, ( vd_t )item );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/// returns false if already registered; checks for collision
er_t xoico_compiler_s_type_register( xoico_compiler_s* o, tp_t type )
{
    bcore_hmap_tp_s_set( &o->hmap_type, type );
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

bl_t xoico_compiler_s_item_exists( const xoico_compiler_s* o, tp_t item_id )
{
    return bcore_hmap_tpvd_s_exists( &o->hmap_item, item_id );
}

//----------------------------------------------------------------------------------------------------------------------

bl_t xoico_compiler_s_is_type( const xoico_compiler_s* o, tp_t name )
{
    if( bcore_hmap_tpvd_s_exists( &o->hmap_item, name ) )
    {
        const xoico* item = xoico_compiler_s_item_get( o, name );
        if( item->_ == TYPEOF_xoico_stamp ) return true;
    }
    else if( bcore_hmap_tpvd_s_exists( &o->hmap_group, name ) )
    {
        return true;
    }
    else if( bcore_hmap_tp_s_exists( &o->hmap_type, name ) )
    {
        return true;
    }
    return false;
}

//----------------------------------------------------------------------------------------------------------------------

const xoico* xoico_compiler_s_item_get( const xoico_compiler_s* o, tp_t item_id )
{
    vd_t* ptr = bcore_hmap_tpvd_s_get( &o->hmap_item, item_id );
    return ptr ? ( const xoico* )*ptr : NULL;
}

//----------------------------------------------------------------------------------------------------------------------

const xoico_signature_s* xoico_compiler_s_get_signature( const xoico_compiler_s* o, tp_t item_id )
{
    const xoico* item = xoico_compiler_s_item_get( o, item_id );
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
er_t xoico_compiler_s_parse( xoico_compiler_s* o, sc_t target_name, sc_t source_path, const xoico_target_xflags_s* xflags, sz_t* p_target_index )
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
    xoico_target_s_update_xflags( target, xflags );

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

bl_t xoico_compiler_s_get_type_element_info( const xoico_compiler_s* o, tp_t type, tp_t name, xoico_compiler_element_info_s* info )
{
    const xoico** p_item = ( const xoico** )bcore_hmap_tpvd_s_get( &o->hmap_item, type );
    bl_t success = false;

    if( !p_item ) return false;

    const xoico* item = *p_item;

    if( item->_ == TYPEOF_xoico_stamp_s )
    {
        const xoico_stamp_s* stamp = ( const xoico_stamp_s* )item;
        const bcore_self_s* self = stamp->self;
        if( !xoico_compiler_s_get_self( o, type, &self ) ) return false;

        const bcore_self_item_s* item = bcore_self_s_get_item_by_name( self, name ); // returns NULL in case of no match
        bl_t found = true;
        sz_t indirection = 0;

        if( item )
        {
            switch( item->caps )
            {
                case BCORE_CAPS_SOLID_STATIC: indirection = 0; break;
                case BCORE_CAPS_LINK_STATIC:  indirection = 1; break;
                case BCORE_CAPS_LINK_TYPED:   indirection = 1; break;
                case BCORE_CAPS_LINK_AWARE:   indirection = 1; break;
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
            }
        }
        else
        {
            found = false;
        }

        info->typespec.is_const = false;

        if( !found ) // try function
        {
            xoico_func_s* func = xoico_funcs_s_get_func_from_name( &stamp->funcs, name );
            if( func )
            {
                info->typespec.type = func->global_name;
                info->typespec.indirection = 0;
                xoico_signature_s_attach( &info->signature, xoico_signature_s_clone( ( xoico_signature_s* )xoico_compiler_s_get_signature( o, func->type ) ) );
                xoico_signature_s_relent( info->signature, self->type );
                success = true;
            }
            else
            {
                success = false;
            }
        }
        else
        {
            info->typespec.type = item->type;
            info->typespec.indirection = indirection;
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
er_t xoico_compiler_s_compile( xoico_compiler_s* o, sc_t target_name, sc_t source_path, const xoico_target_xflags_s* xflags, sz_t* p_target_index )
{
    BLM_INIT();
    BLM_TRY( xoico_compiler_s_parse( o, target_name, source_path, xflags, p_target_index ) );
    BLM_TRY( xoico_compiler_s_finalize( o ) );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_compiler_s_target_set_signal_handler_name( xoico_compiler_s* o, sz_t target_index, sc_t name )
{
    ASSERT( target_index >= 0 && target_index < o->size );
    xoico_target_s* target = o->data[ target_index ];
    st_s_copy_sc( &target->signal_handler_name, name );
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_compiler_s_target_set_dependencies( xoico_compiler_s* o, sz_t target_index, const bcore_arr_sz_s* dependencies )
{
    BLM_INIT();
    ASSERT( target_index >= 0 && target_index < o->size );
    xoico_target_s* target = o->data[ target_index ];

    /// sort, remove duplicates, copy
    {
        bcore_arr_sz_s* dst = &target->dependencies;
        bcore_arr_sz_s_set_size( dst, 0 );
        bcore_arr_sz_s* src = bcore_arr_sz_s_sort( BLM_CLONE( bcore_arr_sz_s, dependencies ), 1 );
        BFOR_EACH( i, src ) if( i == 0 || src->data[ i ] != src->data[ i - 1 ] )
        {
            sz_t idx = src->data[ i ];
            ASSERT( idx >= 0 && idx < o->size );
            bcore_arr_sz_s_push( dst, idx );
        }
    }

    if( xoico_target_s_is_cyclic( target ) )
    {
        return bcore_error_push_fa( TYPEOF_general_error, "Cyclic dependencies found in target '#<sc_t>'.", target->name.sc );
    }

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_compiler_s_target_set_readonly( xoico_compiler_s* o, sz_t target_index, bl_t readonly )
{
    ASSERT( target_index >= 0 && target_index < o->size );
    o->data[ target_index ]->readonly = readonly;
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_compiler_s_target_update_xflags( xoico_compiler_s* o, sz_t target_index, const xoico_target_xflags_s* xflags )
{
    ASSERT( target_index >= 0 && target_index < o->size );
    xoico_target_s_update_xflags( o->data[ target_index ], xflags );
    return 0;
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

