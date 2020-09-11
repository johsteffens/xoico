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

er_t xoico_builder_target_s_load( xoico_builder_target_s* o, bl_t readonly, sc_t path )
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

    bcore_txt_ml_a_from_file( o, st_path->sc );
    st_s_copy( &o->full_path_, st_path );
    if( readonly ) o->readonly = true;

    if( !o->name )
    {
        BLM_RETURNV
        (
            er_t,
            bcore_error_push_fa( TYPEOF_general_error, "In target file: '#<sc_t>'\nTarget name must be specified.", st_path->sc );
        );
    }

    /// check for dependency cycles
    if( o->parent_ )
    {
        const xoico_builder_target_s* match = xoico_builder_target_s_name_match( o->parent_, o->name->sc );
        if( match )
        {
            if( st_s_equal_st( &match->full_path_, &o->full_path_ ) )
            {
                BLM_ERR_FA( "In target file: '#<sc_t>'\nCyclic dependency detected.", st_path->sc );
            }
            else
            {
                BLM_ERR_FA( "Same target name '#<sc_t>' used in different target files:\n#<sc_t>\n#<sc_t>", o->name->sc, st_path->sc, match->full_path_.sc );
            }
        }
    }

    BFOR_EACH( i, &o->dependencies )
    {
        BLM_INIT();
        if( !o->dependencies_target_ ) o->dependencies_target_ = xoico_builder_arr_target_s_create();

        st_s* file_path = BLM_CREATE( st_s );
        if( o->dependencies.data[ i ]->sc[ 0 ] != '/' )
        {
            if( o->root_folder ) st_s_push_fa( file_path, "#<sc_t>/", o->root_folder->sc );
        }

        bl_t dep_readonly = o->readonly;

        bcore_source* source = BLM_A_PUSH( bcore_source_string_s_create_sc( o->dependencies.data[ i ]->sc ) );
        BLM_TRY( bcore_source_a_parse_em_fa( source, " #:until':'", file_path ) );

        /// remove trailing spaces
        while( file_path->sc[ 0 ] == ' ' || file_path->sc[ 0 ] == '\t' ) st_s_pop_char( file_path );

        if( bcore_source_a_parse_bl_fa( source, "#?':'" ) )
        {
            if( bcore_source_a_parse_bl_fa( source, " #?w'readonly'" ) )
            {
                dep_readonly = true;
            }
            else
            {
                XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Syntax error in dependency declaration." );
            }
        }

        xoico_builder_target_s* target = xoico_builder_arr_target_s_push_d( o->dependencies_target_, xoico_builder_target_s_create() );
        target->parent_ = o;

        BLM_TRY( xoico_builder_target_s_load( target, dep_readonly, file_path->sc ) );

        BLM_DOWN();
    }

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_builder_target_s_build( xoico_builder_target_s* o )
{
    BLM_INIT();

    if( !o->root_    ) o->root_    = ( o->parent_ ) ? o->parent_->root_     : o;
    if( !o->compiler ) o->compiler = ( o->parent_ ) ? o->parent_->compiler : NULL;

    if( o == o->root_ )
    {
        if( !o->hmap_built_target_ ) o->hmap_built_target_ = bcore_hmap_tpvd_s_create();
    }

    ASSERT( o->compiler );
    ASSERT( o->root_ );

    tp_t tp_target_name = bentypeof( o->name->sc );

    BFOR_EACH( i, o->dependencies_target_ )
    {
        BLM_TRY( xoico_builder_target_s_build( o->dependencies_target_->data[ i ] ) );
    }

    if( bcore_hmap_tpvd_s_exists( o->root_->hmap_built_target_, tp_target_name ) )
    {
        xoico_builder_target_s* target = *bcore_hmap_tpvd_s_get( o->root_->hmap_built_target_, tp_target_name );
        o->target_index_ = target->target_index_;
        BLM_RETURNV( er_t, 0 );
    }

    bcore_hmap_tpvd_s_set( o->root_->hmap_built_target_, tp_target_name, o );

    o->target_index_ = -1;

    bcore_msg_fa( "XOICO: compiling #<sc_t>\n", o->full_path_.sc );

    BFOR_EACH( i, &o->sources )
    {
        BLM_INIT();

        st_s* file_path = BLM_CREATE( st_s );
        if( o->sources.data[ i ]->sc[ 0 ] != '/' )
        {
            if( o->root_folder ) st_s_push_fa( file_path, "#<sc_t>/", o->root_folder->sc );
        }
        st_s_push_fa( file_path, "#<sc_t>", o->sources.data[ i ]->sc );

        ASSERT( o->name );
        ASSERT( o->extension );
        st_s* xoi_target_name = BLM_A_PUSH( st_s_create_fa( "#<sc_t>_#<sc_t>", o->name->sc, o->extension->sc ) );

        sz_t index = -1;
        BLM_TRY( xoico_compiler_s_compile( o->compiler, xoi_target_name->sc, file_path->sc, &index ) );
        if( o->target_index_ == -1 ) o->target_index_ = index;
        if( index != o->target_index_ )
        {
            ERR_fa
            (
                "Building source '#<sc_t>' in target '#<sc_t>':\n"
                "Target index mismatch.\n"
                "This problem occurs when a target defines sources from different directories.\n",
                o->sources.data[ i ]->sc,
                o->name->sc
            );
        }

        BLM_DOWN();
    }

    if( o->target_index_ >= 0 )
    {
        bcore_arr_sz_s* dependencies = BLM_CREATE( bcore_arr_sz_s );
        BFOR_EACH( i, o->dependencies_target_ )
        {
            xoico_builder_target_s_push_target_index_to_arr( o->dependencies_target_->data[ i ], dependencies );
        }

        BLM_TRY( xoico_compiler_s_target_set_dependencies( o->compiler, o->target_index_, dependencies ) );
        st_s* signal_handler = BLM_A_PUSH( st_s_create_fa( "#<sc_t>_general_signal_handler", o->name->sc ) );
        if( o->signal_handler ) st_s_copy( signal_handler, o->signal_handler );
        BLM_TRY( xoico_compiler_s_target_set_signal_handler_name( o->compiler, o->target_index_, signal_handler->sc ) );
        BLM_TRY( xoico_compiler_s_target_set_readonly( o->compiler, o->target_index_, o->readonly ) );
    }

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

bl_t xoico_builder_target_s_update_required( const xoico_builder_target_s* o )
{
    return xoico_compiler_s_update_required( o->compiler );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_builder_target_s_update( const xoico_builder_target_s* o )
{
    if( bcore_error_stack_size() > 0 ) return TYPEOF_error_stack;
    BLM_INIT();
    BLM_TRY( xoico_compiler_s_update_target_files( o->compiler, NULL ) );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// xoico_builder interface functions

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_builder_main_s_build_from_file( xoico_builder_main_s* o, sc_t path )
{
    BLM_INIT();
    xoico_builder_target_s* target = xoico_builder_target_s_create();
    BLM_TRY( xoico_builder_target_s_load( target, false, path ) );
    target->compiler = o->compiler;
    xoico_builder_target_s_attach( &o->target, target );
    BLM_TRY( xoico_builder_target_s_build( o->target ) );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

bl_t xoico_builder_main_s_update_required( const xoico_builder_main_s* o )
{
    return xoico_builder_target_s_update_required( o->target );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_builder_main_s_update( const xoico_builder_main_s* o )
{
    return xoico_builder_target_s_update( o->target );
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

static void selftest( void )
{
}

//----------------------------------------------------------------------------------------------------------------------

vd_t xoico_builder_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "xoico_builder" ) ) )
    {
        case TYPEOF_init1:
        {
        }
        break;

        case TYPEOF_selftest:
        {
            selftest();
            return NULL;
        }
        break;

        default: break;
    }

    return NULL;
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/


