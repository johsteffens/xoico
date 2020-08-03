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

#include "xoite_compiler.h"
#include "xoite_group.h"
#include "xoite_target.h"
#include "xoite_source.h"

/**********************************************************************************************************************/

// TODO: move to a context frame
xoite_compiler_s* xoite_compiler_g = NULL;

//----------------------------------------------------------------------------------------------------------------------

/// returns true if correct signature could be verified
bl_t xoite_compiler_is_signed( sc_t file )
{
    BLM_INIT();
    bcore_source* source = BLM_A_PUSH( bcore_file_open_source( file ) );
    st_s* data = BLM_CREATE( st_s );
    while( !bcore_source_a_eos( source ) ) st_s_push_char( data, bcore_source_a_get_u0( source ) );

    if( data->size < bcore_strlen( "// BETH_PLANT_SIGNATURE" ) ) BLM_RETURNV( bl_t, false );

    sz_t idx = data->size - 1;
    while( idx >= 0 && data->data[ idx ] != '/' ) idx--;
    if( idx > 0 ) idx--;

    if( st_s_find_sc( data, idx, -1, "// BETH_PLANT_SIGNATURE" ) != idx ) BLM_RETURNV( bl_t, false );

    tp_t hash = 0;
    st_s_parse_fa( data, idx, -1, "// BETH_PLANT_SIGNATURE #<tp_t*>", &hash );

    data->data[ idx ] = 0;

    if( hash != bcore_tp_fold_sc( bcore_tp_init(), data->sc ) ) BLM_RETURNV( bl_t, false );

    BLM_RETURNV( bl_t, true );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoite_compiler_s_check_overwrite( const xoite_compiler_s* o, sc_t file )
{
    BLM_INIT();
    if( !bcore_file_exists( file ) ) BLM_RETURNV( er_t, 0 );

    if( !xoite_compiler_is_signed( file ) )
    {
        st_s* s = BLM_CREATE( st_s );
        st_s_push_fa( s, "Planted file #<sc_t>: Signature check failed.\n", file );
        st_s_push_fa( s, "This file might have been created or edited outside the plant framework.\n" );
        if( o->overwrite_unsigned_planted_files )
        {
            st_s_push_fa( s, "Flag 'overwrite_unsigned_planted_files' is 'true'. The file will be overwritten.\n" );
            bcore_sink_a_push_fa( BCORE_STDERR, "\nWARNING: #<sc_t>\n", s->sc );
        }
        else
        {
            st_s_push_fa( s, "The plant compiler has currently no permission to overwrite unsigned planted files.\n" );
            st_s_push_fa( s, "You can fix it in one of following ways:\n" );
            st_s_push_fa( s, "* Rename or move the file.\n" );
            st_s_push_fa( s, "* Allow overwrite by setting flag 'overwrite_unsigned_planted_files' 'true'.\n" );
            BLM_RETURNV( er_t, bcore_error_push_fa( TYPEOF_general_error, "\nERROR: #<sc_t>\n", s->sc ) );
        }
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/// returns false if already registered; checks for collision
er_t xoite_compiler_s_group_register( xoite_compiler_s* o, const xoite_group_s* group, bcore_source* source )
{
    BLM_INIT();
    sc_t global_name = group->name.sc;
    tp_t global_id = typeof( global_name );
    if( bcore_hmap_tpvd_s_exists( &o->hmap_group, global_id ) )
    {
        /// check collision
        const xoite_group_s* group2 = *bcore_hmap_tpvd_s_get( &o->hmap_group, global_id );
        sc_t global_name2 = group2->name.sc;

        if( !sc_t_equal( global_name, global_name2 ) )
        {
            XOITE_BLM_SOURCE_PARSE_ERR_FA( source, "Collision detected: '#<sc_t>' and '#<sc_t>' produce same hash\n", global_name, global_name2 );
        }
        else
        {
            XOITE_BLM_SOURCE_PARSE_ERR_FA( source, "'#<sc_t>' was already registered\n", global_name );
        }
    }
    bcore_hmap_tpvd_s_set( &o->hmap_group, global_id, ( vd_t )group );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/// returns false if already registered; checks for collision
er_t xoite_compiler_s_item_register( xoite_compiler_s* o, const xoite* item, bcore_source* source )
{
    BLM_INIT();
    sc_t global_name = xoite_a_get_global_name_sc( item );
    tp_t global_id = typeof( global_name );
    if( bcore_hmap_tpvd_s_exists( &o->hmap_item, global_id ) )
    {
        /// check collision
        const xoite* item2 = *bcore_hmap_tpvd_s_get( &o->hmap_item, global_id );
        sc_t global_name2 = xoite_a_get_global_name_sc( item2 );
        if( !sc_t_equal( global_name, global_name2 ) )
        {
            XOITE_BLM_SOURCE_PARSE_ERR_FA( source, "Collision detected: '#<sc_t>' and '#<sc_t>' produce same hash\n", global_name, global_name2 );
        }
        else
        {
            XOITE_BLM_SOURCE_PARSE_ERR_FA( source, "'#<sc_t>' was already registered\n", global_name );
        }
    }

    bcore_hmap_tpvd_s_set( &o->hmap_item, global_id, ( vd_t )item );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

bl_t xoite_compiler_s_item_exists( const xoite_compiler_s* o, tp_t item_id )
{
    return bcore_hmap_tpvd_s_exists( &o->hmap_item, item_id );
}

//----------------------------------------------------------------------------------------------------------------------

const xoite* xoite_compiler_s_item_get( const xoite_compiler_s* o, tp_t item_id )
{
    vd_t* ptr = bcore_hmap_tpvd_s_get( &o->hmap_item, item_id );
    return ptr ? ( const xoite* )*ptr : NULL;
}

//----------------------------------------------------------------------------------------------------------------------

/** returns target index */
er_t xoite_compiler_s_parse( xoite_compiler_s* o, sc_t target_name, sc_t source_path, sz_t* p_target_index )
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
        xoite_target_s* target = BLM_CREATE( xoite_target_s );
        target->compiler = o;
        st_s_copy_sc( &target->name, target_name );
        st_s_copy(    &target->path, target_path );
        bcore_array_a_push( ( bcore_array* )o, sr_asd( bcore_fork( target ) ) );
        target_index = o->size - 1;
        BLM_DOWN();
    }

    xoite_target_s* target = o->data[ target_index ];
    BLM_TRY( xoite_target_s_parse( target, source_path ) );

    if( p_target_index ) *p_target_index = target_index;

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoite_compiler_s_finalize( xoite_compiler_s* o )
{
    BLM_INIT();
    for( sz_t i = 0; i < o->size; i++ ) BLM_TRY( xoite_target_s_finalize( o->data[ i ] ) );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/// returns true if a file will be modified in function xoite_compiler_s_expand
bl_t xoite_compiler_s_to_be_modified( const xoite_compiler_s* o )
{
    for( sz_t i = 0; i < o->size; i++ )
    {
        if( xoite_target_s_to_be_modified( o->data[ i ] ) ) return true;
    }
    return false;
}

//----------------------------------------------------------------------------------------------------------------------

/// returns true if a file was modified
er_t xoite_compiler_s_expand( xoite_compiler_s* o, bl_t* p_modified )
{
    BLM_INIT();
    bl_t modified = false;

    for( sz_t i = 0; i < o->size; i++ ) BLM_TRY( xoite_target_s_expand_phase1( o->data[ i ], &modified ) );
    for( sz_t i = 0; i < o->size; i++ ) BLM_TRY( xoite_target_s_expand_phase2( o->data[ i ], &modified ) );

    if( p_modified ) *p_modified = modified;
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/// adds an item to lifetime manager
er_t xoite_compiler_s_life_a_push( xoite_compiler_s* o, vd_t object )
{
    bcore_life_s_push_aware( &o->life, object );
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// xoite interface

//----------------------------------------------------------------------------------------------------------------------

er_t xoite_compiler_setup( void )
{
    BLM_INIT();
    if( !xoite_compiler_g )
    {
        BLM_INIT();
        xoite_compiler_g = xoite_compiler_s_create();
        st_s* dir_name = BLM_CREATE( st_s );
        st_s* cfg_file = BLM_CREATE( st_s );
        bcore_folder_get_current( dir_name );

        if( bcore_file_find_descend( dir_name->sc, ".xoite_compiler.cfg", cfg_file ) )
        {
            bcore_txt_ml_a_from_file( xoite_compiler_g, cfg_file->sc );
            if( xoite_compiler_g->verbosity > 0 ) bcore_msg_fa( "BETH_PLANT: Using '#<sc_t>'\n", cfg_file->sc );
        }
        BLM_DOWN();
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/// returns target index
er_t xoite_compiler_compile( sc_t target_name, sc_t source_path, sz_t* p_target_index )
{
    BLM_INIT();
    if( !xoite_compiler_g ) BLM_TRY( xoite_compiler_setup() );
    BLM_TRY( xoite_compiler_s_parse( xoite_compiler_g, target_name, source_path, p_target_index ) );
    BLM_TRY( xoite_compiler_s_finalize( xoite_compiler_g ) );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoite_compiler_set_target_signal_handler_name( sz_t target_index, sc_t name )
{
    ASSERT( xoite_compiler_g );
    ASSERT( target_index >= 0 && target_index < xoite_compiler_g->size );
    xoite_target_s* target = xoite_compiler_g->data[ target_index ];
    st_s_copy_sc( &target->signal_handler_name, name );
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoite_compiler_set_target_dependencies( sz_t target_index, const bcore_arr_sz_s* dependencies )
{
    ASSERT( xoite_compiler_g );
    ASSERT( target_index >= 0 && target_index < xoite_compiler_g->size );
    xoite_target_s* target = xoite_compiler_g->data[ target_index ];
    bcore_arr_sz_s_copy( &target->dependencies, dependencies );
    if( xoite_target_s_is_cyclic( target ) )
    {
        return bcore_error_push_fa( TYPEOF_general_error, "Cyclic dependencies found in target '#<sc_t>'.", target->name.sc );
    }
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoite_compiler_update_planted_files( bl_t* p_modified )
{
    BLM_INIT();
    ASSERT( xoite_compiler_g );
    bl_t modified = false;
    bl_t verbosity = xoite_compiler_g->verbosity;
    f3_t time = 0;

    ABS_TIME_OF( BLM_TRY( xoite_compiler_s_expand( xoite_compiler_g, &modified ) ), time );
    if( modified )
    {
        if( verbosity > 0 ) bcore_msg_fa( "BETH_PLANT: Expanded in #<f3_t> sec.\n", time );
        if( verbosity > 0 ) bcore_msg_fa( "BETH_PLANT: Files were updated. Rebuild is necessary.\n" );
    }
    xoite_compiler_s_discard( xoite_compiler_g );
    xoite_compiler_g = NULL;
    if( p_modified ) *p_modified = modified;

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

bl_t xoite_compiler_update_required( void )
{
    return xoite_compiler_s_to_be_modified( xoite_compiler_g );
}

//----------------------------------------------------------------------------------------------------------------------

sz_t xoite_compiler_get_verbosity( void )
{
    if( !xoite_compiler_g ) xoite_compiler_setup();
    return xoite_compiler_g->verbosity;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoite_compiler_set_verbosity( sz_t verbosity )
{
    if( !xoite_compiler_g ) xoite_compiler_setup();
    xoite_compiler_g->verbosity = verbosity;
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

