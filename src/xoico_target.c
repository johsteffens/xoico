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

#include "xoico_target.h"
#include "xoico_group.h"
#include "xoico_compiler.h"

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_target_s_parse( xoico_target_s* o, sc_t source_path )
{
    BLM_INIT();

    st_s* source_name        = BLM_A_PUSH( bcore_file_strip_extension( bcore_file_name( source_path ) ) );
    st_s* source_folder_path = BLM_A_PUSH( bcore_file_folder_path( source_path ) );
    st_s* source_path_n      = BLM_A_PUSH( st_s_create_fa( "#<sc_t>/#<sc_t>", source_folder_path->sc, source_name->sc ) );
    st_s* source_path_h      = BLM_A_PUSH( st_s_create_fa( "#<sc_t>.h", source_path_n->sc ) );

    bl_t source_exists = false;
    for( sz_t i = 0; i < o->size; i++ )
    {
        if( st_s_equal_st( source_path_n, &o->data[ i ]->path ) )
        {
            source_exists = true;
            break;
        }
    }

    if( !source_exists )
    {
        BLM_INIT();
        xoico_source_s* xsource = BLM_CREATE( xoico_source_s );
        xsource->target = o;

        st_s_copy_sc( &xsource->name, source_name->sc );
        st_s_copy   ( &xsource->path, source_path_n );

        xsource->hash = bcore_tp_init();

        if( bcore_file_exists( source_path_h->sc ) )
        {
            BLM_TRY( xoico_source_s_parse( xsource, BLM_A_PUSH( bcore_file_open_source( source_path_h->sc ) ) ) );
        }

        // parsing *.c files is generally not helpful  (currently plant code can only reside in header files)
        // if( bcore_file_exists( source_path_c->sc ) ) xoico_source_s_parse( xsource, BLM_A_PUSH( bcore_file_open_source( source_path_c->sc ) ) );

        bcore_array_a_push( ( bcore_array* )o, sr_asd( bcore_fork( xsource ) ) );
        BLM_DOWN();
    }

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

tp_t xoico_target_s_get_hash( const xoico_target_s* o )
{
    tp_t hash = bcore_tp_init();

    hash = bcore_tp_fold_tp( hash, o->_ );
    hash = bcore_tp_fold_sc( hash, o->name.sc );

    BFOR_EACH( i, o ) hash = bcore_tp_fold_tp( hash, o->data[ i ]->hash );

    BFOR_EACH( i, &o->dependencies )
    {
        sz_t idx = o->dependencies.data[ i ];
        xoico_target_s* dep_target = o->compiler->data[ idx ];
        hash = bcore_tp_fold_tp( hash, xoico_target_s_get_hash( dep_target ) );
    }

    return hash;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_target_s_finalize( xoico_target_s* o )
{
    BLM_INIT();
    for( sz_t i = 0; i < o->size; i++ ) BLM_TRY( xoico_source_s_finalize( o->data[ i ] ) );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/// returns true if target's dependencies are cyclic
bl_t xoico_target_s_is_cyclic_recursive( xoico_target_s* o )
{
    if( o->flag ) return true;
    o->flag = true;
    BFOR_EACH( i, &o->dependencies )
    {
        sz_t idx = o->dependencies.data[ i ];
        if( xoico_target_s_is_cyclic_recursive( o->compiler->data[ idx ] ) ) return true;
    }
    return false;
}


//----------------------------------------------------------------------------------------------------------------------

/// clears flags in targets
void xoico_compiler_s_clear_flags( xoico_compiler_s* o )
{
    BFOR_EACH( i, o ) o->data[ i ]->flag = false;
}

//----------------------------------------------------------------------------------------------------------------------

bl_t xoico_target_s_is_cyclic( xoico_target_s* o )
{
    xoico_compiler_s_clear_flags( o->compiler );
    bl_t cyclic = xoico_target_s_is_cyclic_recursive( o );
    xoico_compiler_s_clear_flags( o->compiler );
    return cyclic;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_target_s_expand_heading( const xoico_target_s* o, sz_t indent, bcore_sink* sink )
{
    BLM_INIT();
    bcore_sink_a_push_fa( sink, "/** This file was generated from beth-plant source code.\n" );
    bcore_sink_a_push_fa( sink, " *  Compiling Agent : xoico_compiler (C) 2020 J.B.Steffens\n" );
    bcore_sink_a_push_fa( sink, " *  Last File Update: " );
    {
        bcore_cday_utc_s* time = BLM_CREATE( bcore_cday_utc_s );
        bcore_cday_utc_s_from_system( time );
        bcore_cday_utc_s_to_sink( time, sink );
        bcore_sink_a_push_fa( sink, "\n" );
    }

    bcore_sink_a_push_fa( sink, " *\n" );
    bcore_sink_a_push_fa( sink, " *  Copyright and License of this File:\n" );
    bcore_sink_a_push_fa( sink, " *\n" );
    bcore_sink_a_push_fa( sink, " *  Generated code inherits the copyright and license of the underlying beth-plant source code.\n" );
    bcore_sink_a_push_fa( sink, " *  Source code defining this file is distributed across following files:\n" );
    bcore_sink_a_push_fa( sink, " *\n" );

    for( sz_t i = 0; i < o->size; i++ )
    {
        xoico_source_s* source = o->data[ i ];
        bcore_sink_a_push_fa( sink, " *  #<sc_t>.h\n", source->name.sc );
    }
    bcore_sink_a_push_fa( sink, " *\n" );
    bcore_sink_a_push_fa( sink, " */\n" );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_target_s_expand_h( const xoico_target_s* o, sz_t indent, bcore_sink* sink )
{
    BLM_INIT();
    xoico_target_s_expand_heading( o, indent, sink );

    tp_t target_hash = xoico_target_s_get_hash( o );

    st_s* name_upper = BLM_CLONE( st_s, &o->name );
    st_s_set_uppercase( name_upper );

    bcore_sink_a_push_fa( sink, "\n" );
    bcore_sink_a_push_fa( sink, "#rn{ }##ifndef #<sc_t>_H\n", indent, name_upper->sc );
    bcore_sink_a_push_fa( sink, "#rn{ }##define #<sc_t>_H\n", indent, name_upper->sc );

    bcore_sink_a_push_fa( sink, "\n" );
    bcore_sink_a_push_fa( sink, "#rn{ }##include \"bcore_control.h\"\n", indent );

    bcore_sink_a_push_fa( sink, "\n" );

    bcore_sink_a_push_fa( sink, "#rn{ }//To force a rebuild of this target by the plant-compiler, reset the hash key value below to 0.\n", indent, o->name.sc, target_hash );
    bcore_sink_a_push_fa( sink, "#rn{ }##define HKEYOF_#<sc_t> #<tp_t>\n", indent, o->name.sc, target_hash );

    bcore_sink_a_push_fa( sink, "\n" );

    bcore_sink_a_push_fa( sink, "#rn{ }##define TYPEOF_#<sc_t> #<tp_t>\n", indent, o->name.sc, typeof( o->name.sc ) );

    for( sz_t i = 0; i < o->size; i++ ) BLM_TRY( xoico_source_s_expand_declaration( o->data[ i ], indent, sink ) );

    bcore_sink_a_push_fa( sink, "\n" );
    bcore_sink_a_push_fa( sink, "#rn{ }/*#rn{*}*/\n", indent, sz_max( 0, 116 - indent ) );
    bcore_sink_a_push_fa( sink, "\n" );
    bcore_sink_a_push_fa( sink, "#rn{ }vd_t #<sc_t>_signal_handler( const bcore_signal_s* o );\n", indent, o->name.sc );

    bcore_sink_a_push_fa( sink, "\n" );
    bcore_sink_a_push_fa( sink, "#rn{ }##endif // #<sc_t>_H\n", indent, name_upper->sc );

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_target_s_expand_init1( const xoico_target_s* o, sz_t indent, bcore_sink* sink )
{
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_target_s_expand_c( const xoico_target_s* o, sz_t indent, bcore_sink* sink )
{
    BLM_INIT();
    BLM_TRY( xoico_target_s_expand_heading( o, indent, sink ) );

    bcore_sink_a_push_fa( sink, "\n" );
    bcore_sink_a_push_fa( sink, "#rn{ }##include \"#<sc_t>.h\"\n", indent, o->name.sc );
    bcore_sink_a_push_fa( sink, "#rn{ }##include \"bcore_spect.h\"\n", indent );
    bcore_sink_a_push_fa( sink, "#rn{ }##include \"bcore_spect_inst.h\"\n", indent );
    bcore_sink_a_push_fa( sink, "#rn{ }##include \"bcore_sr.h\"\n", indent );
    bcore_sink_a_push_fa( sink, "#rn{ }##include \"bcore_const_manager.h\"\n", indent );

    /// definition section
    bcore_sink_a_push_fa( sink, "\n" );
    for( sz_t i = 0; i < o->size; i++ ) BLM_TRY( xoico_source_s_expand_definition( o->data[ i ], indent, sink ) );

    /// signal section
    bcore_sink_a_push_fa( sink, "\n" );
    bcore_sink_a_push_fa( sink, "#rn{ }/*#rn{*}*/\n", indent, sz_max( 0, 116 - indent ) );
    bcore_sink_a_push_fa( sink, "\n" );

    /// prototypes of signal handlers this target depends on
    BFOR_EACH( i, &o->dependencies )
    {
        const xoico_target_s* target = o->compiler->data[ o->dependencies.data[ i ] ];
        if( target->signal_handler_name.size == 0 ) continue;
        bcore_sink_a_push_fa( sink, "#rn{ }vd_t #<sc_t>( const bcore_signal_s* o );\n", indent, target->signal_handler_name.sc );
    }

    bcore_sink_a_push_fa( sink, "\n" );
    bcore_sink_a_push_fa( sink, "#rn{ }vd_t #<sc_t>_signal_handler( const bcore_signal_s* o )\n", indent, o->name.sc );
    bcore_sink_a_push_fa( sink, "#rn{ }{\n", indent );
    bcore_sink_a_push_fa( sink, "#rn{ }    switch( bcore_signal_s_handle_type( o, typeof( \"#<sc_t>\" ) ) )\n", indent, o->name.sc );
    bcore_sink_a_push_fa( sink, "#rn{ }    {\n", indent );

    bcore_sink_a_push_fa( sink, "#rn{ }        case TYPEOF_init1:\n", indent );
    bcore_sink_a_push_fa( sink, "#rn{ }        {\n", indent );
    BLM_TRY( xoico_target_s_expand_init1( o, indent + 12, sink ) );
    for( sz_t i = 0; i < o->size; i++ ) BLM_TRY( xoico_source_s_expand_init1( o->data[ i ], indent + 12, sink ) );
    bcore_sink_a_push_fa( sink, "#rn{ }        }\n", indent );
    bcore_sink_a_push_fa( sink, "#rn{ }        break;\n", indent );

    if( o->dependencies.size > 0 )
    {
        bcore_sink_a_push_fa( sink, "#rn{ }        case TYPEOF_push_dependencies:\n", indent );
        bcore_sink_a_push_fa( sink, "#rn{ }        {\n", indent );
        bcore_sink_a_push_fa( sink, "#rn{ }            ASSERT( o->object && ( *( aware_t* )o->object ) == TYPEOF_bcore_arr_fp_s );\n", indent );
        bcore_sink_a_push_fa( sink, "#rn{ }            bcore_arr_fp_s* arr_fp = o->object;\n", indent );
        BFOR_EACH( i, &o->dependencies )
        {
            const xoico_target_s* target = o->compiler->data[ o->dependencies.data[ i ] ];
            if( target->signal_handler_name.size == 0 ) continue;
            bcore_sink_a_push_fa( sink, "#rn{ }            bcore_arr_fp_s_push( arr_fp, ( fp_t )#<sc_t> );\n", indent, target->signal_handler_name.sc );
        }
        bcore_sink_a_push_fa( sink, "#rn{ }        }\n", indent );
        bcore_sink_a_push_fa( sink, "#rn{ }        break;\n", indent );
    }

    bcore_sink_a_push_fa( sink, "#rn{ }        default: break;\n", indent );
    bcore_sink_a_push_fa( sink, "#rn{ }    }\n", indent );
    bcore_sink_a_push_fa( sink, "#rn{ }    return NULL;\n", indent );
    bcore_sink_a_push_fa( sink, "#rn{ }}\n", indent );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

bl_t xoico_target_s_to_be_modified( const xoico_target_s* o )
{
    BLM_INIT();
    if( o->compiler->always_expand ) BLM_RETURNV( bl_t, true );

    bl_t to_be_modified = true;

    tp_t target_hash = xoico_target_s_get_hash( o );

    st_s* file_h = BLM_A_PUSH( st_s_create_fa( "#<sc_t>.h", o->path.sc ) );
    if( bcore_file_exists( file_h->sc ) )
    {
        st_s* key_defined = BLM_A_PUSH( st_s_create_fa( "##?'define HKEYOF_#<sc_t>'", o->name.sc ) );
        bcore_source* source = BLM_A_PUSH( bcore_file_open_source( file_h->sc ) );
        while( !bcore_source_a_eos( source ) )
        {
            char c = bcore_source_a_get_u0( source );
            if( c == '#' )
            {
                if( bcore_source_a_parse_bl_fa( source, key_defined->sc ) )
                {
                    tp_t key_val = 0;
                    bcore_source_a_parse_fa( source, " #<tp_t*>", &key_val );
                    to_be_modified = ( key_val != target_hash );
                    break;
                }
            }
        }
    }

    BLM_RETURNV( bl_t, to_be_modified );
}

//----------------------------------------------------------------------------------------------------------------------

/// expands all text files in memory
er_t xoico_target_s_expand_phase1( xoico_target_s* o, bl_t* p_modified )
{
    BLM_INIT();
    st_s_detach( &o->planted_h );
    st_s_detach( &o->planted_c );
    o->modified = false;

    if( xoico_target_s_to_be_modified( o ) )
    {
        o->planted_h = st_s_create();
        o->planted_c = st_s_create();
        if( !o->compiler->dry_run )
        {
            BLM_TRY( xoico_target_s_expand_h( o, 0, ( bcore_sink* )o->planted_h ) );
            BLM_TRY( xoico_target_s_expand_c( o, 0, ( bcore_sink* )o->planted_c ) );
        }
        else
        {
            st_s* buf = BLM_CREATE( st_s );
            BLM_TRY( xoico_target_s_expand_h( o, 0, ( bcore_sink* )buf ) );
            BLM_TRY( xoico_target_s_expand_c( o, 0, ( bcore_sink* )buf ) );
        }
        o->modified = true;
    }

    if( p_modified ) *p_modified = o->modified;

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/// returns true if a file was modified
static er_t write_with_signature( sc_t file, const st_s* data )
{
    BLM_INIT();
    tp_t hash = bcore_tp_fold_sc( bcore_tp_init(), data->sc );
    bcore_sink* sink = BLM_A_PUSH( bcore_file_open_sink( file ) );
    bcore_sink_a_push_data( sink, data->data, data->size );
    bcore_sink_a_push_fa( sink, "// BETH_PLANT_SIGNATURE #pl10 {#<tp_t>}\n", hash );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/// returns true if a file was modified
er_t xoico_target_s_expand_phase2( xoico_target_s* o, bl_t* p_modified )
{
    BLM_INIT();
    if( !o->modified ) BLM_RETURNV( er_t, 0 );

    ASSERT( o->planted_h );
    ASSERT( o->planted_c );

    st_s* file_h = BLM_A_PUSH( st_s_create_fa( "#<sc_t>.h", o->path.sc ) );
    st_s* file_c = BLM_A_PUSH( st_s_create_fa( "#<sc_t>.c", o->path.sc ) );

    BLM_TRY( xoico_compiler_s_check_overwrite( o->compiler, file_h->sc ) );
    BLM_TRY( xoico_compiler_s_check_overwrite( o->compiler, file_c->sc ) );

    bcore_msg_fa( "writing '#<sc_t>'\n", file_h->sc );
    write_with_signature( file_h->sc, o->planted_h );

    bcore_msg_fa( "writing '#<sc_t>'\n", file_c->sc );
    write_with_signature( file_c->sc, o->planted_c );

    if( p_modified ) *p_modified = o->modified;
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

