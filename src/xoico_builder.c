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

#include "xoico_builder.h"
#include "xoico_group.h"
#include "xoico_compiler.h"

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_builder_main_s_build_from_file_get_target_index( xoico_builder_main_s* o, sc_t path, sz_t* p_target_index );

er_t xoico_builder_target_s_build( const xoico_builder_target_s* o, sz_t* p_target_index )
{
    BLM_INIT();
    bcore_arr_sz_s* dependencies = BLM_CREATE( bcore_arr_sz_s );
    BFOR_EACH( i, &o->dependencies )
    {
        BLM_INIT();
        st_s* file_path = BLM_CREATE( st_s );
        if( o->dependencies.data[ i ]->sc[ 0 ] != '/' )
        {
            if( o->root ) st_s_push_fa( file_path, "#<sc_t>/", o->root->sc );
        }
        st_s_push_fa( file_path, "#<sc_t>", o->dependencies.data[ i ]->sc );
        sz_t target_index = -1;
        BLM_TRY( xoico_builder_main_s_build_from_file_get_target_index( o->main, file_path->sc, &target_index ) );
        if( target_index >= 0 ) bcore_arr_sz_s_push( dependencies, target_index );
        BLM_DOWN();
    }

    sz_t target_index = -1;

    if( !o->name && o->sources.size > 0 )
    {
        ERR_fa( "Plant name is missing." );
    }

    BFOR_EACH( i, &o->sources )
    {
        BLM_INIT();

        st_s* file_path = BLM_CREATE( st_s );
        if( o->sources.data[ i ]->sc[ 0 ] != '/' )
        {
            if( o->root ) st_s_push_fa( file_path, "#<sc_t>/", o->root->sc );
        }
        st_s_push_fa( file_path, "#<sc_t>", o->sources.data[ i ]->sc );

        ASSERT( o->name );
        ASSERT( o->extension );

        st_s* xoi_target_name = BLM_A_PUSH( st_s_create_fa( "#<sc_t>_#<sc_t>", o->name->sc, o->extension->sc ) );

        sz_t index = -1;
        BLM_TRY( xoico_compiler_s_compile( o->main->compiler, xoi_target_name->sc, file_path->sc, &index ) );
        target_index = ( target_index == -1 ) ? index : target_index;
        if( index != target_index )
        {
            ERR_fa
            (
                "Building source '#<sc_t>' in plant '#<sc_t>':\n"
                "Target index mismatch.\n"
                "This problem occurs when a target defines sources from different directories.\n",
                o->sources.data[ i ]->sc,
                o->name->sc
            );
        }

        BLM_DOWN();
    }

    if( target_index >= 0 )
    {
        BLM_TRY( xoico_compiler_s_set_target_dependencies( o->main->compiler, target_index, dependencies ) );
        st_s* signal_handler = BLM_A_PUSH( st_s_create_fa( "#<sc_t>_general_signal_handler", o->name->sc ) );
        if( o->signal_handler ) st_s_copy( signal_handler, o->signal_handler );
        BLM_TRY( xoico_compiler_s_set_target_signal_handler_name( o->main->compiler, target_index, signal_handler->sc ) );
        if( p_target_index ) *p_target_index = target_index;
    }

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// xoico_builder interface functions

er_t xoico_builder_main_s_build_from_file_get_target_index( xoico_builder_main_s* o, sc_t path, sz_t* p_target_index )
{
    BLM_INIT();

    st_s* st_path = BLM_A_PUSH( st_s_create_sc( path ) );
    if( st_path->sc[ 0 ] != '/' )
    {
        st_s* current_folder = BLM_CREATE( st_s );
        bcore_folder_get_current( current_folder );
        st_path = BLM_A_PUSH( st_s_create_fa( "#<sc_t>/#<sc_t>", current_folder->sc, st_path->sc ) );
    }

    st_path = BLM_A_PUSH( bcore_file_path_minimized( st_path->sc ) );

    bl_t new_path = true;

    BFOR_EACH( i, &o->arr_path )
    {
        if( st_s_equal_st( o->arr_path.data[ i ], st_path ) )
        {
            new_path = false;
            break;
        }
    }

    sz_t target_index = -1;

    if( new_path )
    {
        bcore_arr_st_s_push_st( &o->arr_path, st_path );

        if( xoico_compiler_s_get_verbosity( o->compiler ) > 0 )
        {
            bcore_msg_fa( "BETH_PLANT: building #<sc_t>\n", st_path->sc );
        }

        if( !bcore_file_exists( st_path->sc ) )
        {
            bcore_error_push_fa( TYPEOF_general_error, "#<sc_t>: File does not exist or cannot be opened.", st_path->sc );
            BLM_RETURNV( er_t, TYPEOF_general_error );
        }

        xoico_builder_target_s* builder = BLM_CREATE( xoico_builder_target_s );
        builder->main = o;
        bcore_txt_ml_a_from_file( builder, st_path->sc );
        BLM_TRY( xoico_builder_target_s_build( builder, &target_index ) );
    }

    if( p_target_index ) *p_target_index = target_index;

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_builder_main_s_build_from_file( xoico_builder_main_s* o, sc_t path )
{
    return xoico_builder_main_s_build_from_file_get_target_index( o, path, NULL );
}

//----------------------------------------------------------------------------------------------------------------------

bl_t xoico_builder_main_s_update_required( const xoico_builder_main_s* o )
{
    bl_t retv = xoico_compiler_s_update_required( o->compiler );
    return retv;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_builder_main_s_update( const xoico_builder_main_s* o )
{
    if( bcore_error_stack_size() > 0 ) return TYPEOF_error_stack;
    BLM_INIT();
    o->compiler->dry_run = o->dry_run;
    BLM_TRY( xoico_compiler_s_update_planted_files( o->compiler, NULL ) );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/


