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

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

func (:s) :.parse_from_path = (try)
{
    st_s* source_name        = bcore_file_strip_extension( bcore_file_name( source_path ) ).scope();
    st_s* source_folder_path = bcore_file_folder_path( source_path ).scope();
    st_s* source_path_n      = st_s_create_fa( "#<sc_t>/#<sc_t>", source_folder_path->sc, source_name->sc ).scope();
    st_s* source_path_h      = st_s_create_fa( "#<sc_t>.h", source_path_n->sc ).scope();

    bl_t source_exists = false;

    foreach( $* e in o )
    {
        if( source_path_n.equal_st( e.path ) )
        {
            source_exists = true;
            break;
        }
    }

    if( !source_exists )
    {
        xoico_source_s* xsource = xoico_source_s!.scope();
        xsource.target = o;

        xsource.name.copy_sc( source_name.sc );
        xsource.path.copy( source_path_n );

        if( bcore_file_exists( source_path_h.sc ) )
        {
            xsource.parse( o, bcore_file_open_source( source_path_h->sc ).scope() );
        }

        o.push_d( xsource.fork() );
    }

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) (tp_t get_hash( const )) =
{
    tp_t hash = bcore_tp_init();

    hash = bcore_tp_fold_tp( hash, o.compiler.target_pre_hash );
    hash = bcore_tp_fold_tp( hash, o._ );
    hash = bcore_tp_fold_sc( hash, o.name.sc );

    if( o.cengine ) hash = bcore_tp_fold_tp( hash, o.cengine.get_hash() );

    foreach( $* e in o ) hash = bcore_tp_fold_tp( hash, e.get_hash() );

    if( o.dependencies.size > 0 )
    {
        $* arr_tp = bcore_arr_tp_s!.scope();

        foreach( $ target_idx in o.dependencies ) arr_tp.push( o.compiler.[ target_idx ].get_hash() );

        // we sort to make the accrued hash independent of the order of dependencies
        arr_tp.sort( 1 );

        foreach( $ tp in arr_tp ) hash = bcore_tp_fold_tp( hash, tp );
    }

    return hash;
};

//----------------------------------------------------------------------------------------------------------------------

/// returns true if target's dependencies are cyclic
func (:s) (bl_t is_cyclic_recursive( mutable )) =
{
    if( o.flag ) return true;
    o.flag = true;
    foreach( sz_t target_idx in o.dependencies ) if( o.compiler.[ target_idx ].is_cyclic_recursive() ) return true;
    o.flag = false;
    return false;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) :.is_cyclic =
{
    o.compiler.clear_flags();
    bl_t cyclic = o.is_cyclic_recursive();
    o.compiler.clear_flags();
    return cyclic;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) :.set_dependencies = (try)
{
    sz_t targets = o.compiler.size;

    /// sort, remove duplicates, copy
    bcore_arr_sz_s* dst = o.dependencies;
    dst.set_size( 0 );
    bcore_arr_sz_s* src = dependencies.clone().scope().sort( 1 );
    for( sz_t i = 0; i < src.size; i++ )
    {
        if( i == 0 || src.[ i ] != src.[ i - 1 ] )
        {
            sz_t idx = src.[ i ];
            ASSERT( idx >= 0 && idx < targets );
            dst.push( idx );
        }
    }

    if( o.is_cyclic() )
    {
        return bcore_error_push_fa( TYPEOF_general_error, "Cyclic dependencies found in target '#<sc_t>'.", o.name.sc );
    }

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) (er_t expand_heading( const, sz_t indent, bcore_sink* sink )) = (try)
{
    bcore_cday_utc_s* time = bcore_cday_utc_s!.scope();
    bcore_cday_utc_s_from_system( time );

    sink.push_fa( "/** This file was generated from xoila source code.\n" );
    sink.push_fa( " *  Compiling Agent : xoico_compiler (C) 2020 J.B.Steffens\n" );
    sink.push_fa( " *  Last File Update: " );
    bcore_cday_utc_s_to_sink( time, sink );
    sink.push_fa( "\n" );
    sink.push_fa( " *\n" );
    sink.push_fa( " *  Copyright and License of this File:\n" );
    sink.push_fa( " *\n" );
    sink.push_fa( " *  Generated code inherits the copyright and license of the underlying xoila source code.\n" );
    sink.push_fa( " *  Source code defining this file is distributed across following files:\n" );
    sink.push_fa( " *\n" );

    foreach( $* e in o ) sink.push_fa( " *  #<sc_t>.h\n", e.name.sc );

    {
        $* arr = bcore_arr_st_s!.scope();
        o.explicit_embeddings_push( arr );
        arr.sort( 1 );
        if( arr.size > 0 )
        {
            st_s* prev_file = NULL;
            foreach( st_s* file in arr )
            {
                if( !file.equal_st( prev_file ) ) sink.push_fa( " *  #<sc_t>\n", file.sc );
                prev_file = file;
            }
        }
    }


    sink.push_fa( " *\n" );
    sink.push_fa( " */\n" );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) (er_t expand_h( const, sz_t indent, bcore_sink* sink )) = (try)
{
    o.expand_heading( indent, sink );

    tp_t target_hash = o.get_hash();

    sink.push_fa( "\n" );
    sink.push_fa( "#rn{ }##ifndef __#<sc_t>_H\n", indent, o.name.sc );
    sink.push_fa( "#rn{ }##define __#<sc_t>_H\n", indent, o.name.sc );

    sink.push_fa( "\n" );
    sink.push_fa( "#rn{ }##include \"bcore_control.h\"\n", indent );

    sink.push_fa( "\n" );

    sink.push_fa( "#rn{ }//To force a rebuild of this target by xoico, reset the hash key value below to 0.\n", indent, o->name.sc, target_hash );
    sink.push_fa( "#rn{ }##define HKEYOF_#<sc_t> 0x#pl16'0'{#X<tp_t>}ull\n", indent, o->name.sc, target_hash );

    sink.push_fa( "\n" );

    sink.push_fa( "#rn{ }##define TYPEOF_#<sc_t> 0x#pl16'0'{#X<tp_t>}ull\n", indent, o->name.sc, typeof( o->name.sc ) );

    foreach( $* e in o ) e.expand_declaration( o, indent, sink );

    sink.push_fa( "\n" );
    sink.push_fa( "#rn{ }/*#rn{*}*/\n", indent, sz_max( 0, 116 - indent ) );
    sink.push_fa( "\n" );
    sink.push_fa( "#rn{ }vd_t #<sc_t>_signal_handler( const bcore_signal_s* o );\n", indent, o.name.sc );

    sink.push_fa( "\n" );
    sink.push_fa( "#rn{ }##endif // __#<sc_t>_H\n", indent, o.name.sc );

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) (er_t expand_init1( const, sz_t indent, bcore_sink* sink )) =
{
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) (er_t expand_c( const, sz_t indent, bcore_sink* sink )) = (try)
{
    o.expand_heading( indent, sink );

    sink.push_fa( "\n" );
    sink.push_fa( "#rn{ }##include \"#<sc_t>.h\"\n", indent, o->include_path.sc );
    sink.push_fa( "#rn{ }##include \"bcore_spect.h\"\n", indent );
    sink.push_fa( "#rn{ }##include \"bcore_spect_inst.h\"\n", indent );
    sink.push_fa( "#rn{ }##include \"bcore_sr.h\"\n", indent );
    sink.push_fa( "#rn{ }##include \"bcore_const_manager.h\"\n", indent );

    /// definition section
    sink.push_fa( "\n" );
    foreach( $* e in o ) e.expand_definition( o, indent, sink );

    /// signal section
    sink.push_fa( "\n" );
    sink.push_fa( "#rn{ }/*#rn{*}*/\n", indent, sz_max( 0, 116 - indent ) );
    sink.push_fa( "\n" );

    /// prototypes of signal handlers this target depends on
    foreach( sz_t target_idx in o->dependencies )
    {
        const xoico_target_s* target = o.compiler.data[ target_idx ];
        if( target.signal_handler_name.size > 0 )
        {
            sink.push_fa( "#rn{ }vd_t #<sc_t>( const bcore_signal_s* o );\n", indent, target.signal_handler_name.sc );
        }
    }

    sink.push_fa( "\n" );
    sink.push_fa( "#rn{ }vd_t #<sc_t>_signal_handler( const bcore_signal_s* o )\n", indent, o.name.sc );
    sink.push_fa( "#rn{ }{\n", indent );
    sink.push_fa( "#rn{ }    switch( bcore_signal_s_handle_type( o, typeof( \"#<sc_t>\" ) ) )\n", indent, o.name.sc );
    sink.push_fa( "#rn{ }    {\n", indent );

    sink.push_fa( "#rn{ }        case TYPEOF_init1:\n", indent );
    sink.push_fa( "#rn{ }        {\n", indent );
    o.expand_init1( indent + 12, sink );
    foreach( $* e in o ) e.expand_init1( o, indent + 12, sink );
    sink.push_fa( "#rn{ }        }\n", indent );
    sink.push_fa( "#rn{ }        break;\n", indent );

    if( o.dependencies.size > 0 )
    {
        sink.push_fa( "#rn{ }        case TYPEOF_push_dependencies:\n", indent );
        sink.push_fa( "#rn{ }        {\n", indent );
        sink.push_fa( "#rn{ }            ASSERT( o->object && ( *( aware_t* )o->object ) == TYPEOF_bcore_arr_fp_s );\n", indent );
        sink.push_fa( "#rn{ }            bcore_arr_fp_s* arr_fp = o->object;\n", indent );
        foreach( sz_t target_idx in o.dependencies )
        {
            const xoico_target_s* target = o.compiler.[ target_idx ];
            if( target.signal_handler_name.size > 0 )
            {
                sink.push_fa( "#rn{ }            bcore_arr_fp_s_push( arr_fp, ( fp_t )#<sc_t> );\n", indent, target.signal_handler_name.sc );
            }
        }
        sink.push_fa( "#rn{ }        }\n", indent );
        sink.push_fa( "#rn{ }        break;\n", indent );
    }

    sink.push_fa( "#rn{ }        default: break;\n", indent );
    sink.push_fa( "#rn{ }    }\n", indent );
    sink.push_fa( "#rn{ }    return NULL;\n", indent );
    sink.push_fa( "#rn{ }}\n", indent );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) :.to_be_modified =
{
    if( o.compiler.always_expand ) return true;

    bl_t to_be_modified = true;

    tp_t target_hash = o.get_hash();

    st_s* file_h = st_s_create_fa( "#<sc_t>.h", o->path.sc ).scope();
    if( bcore_file_exists( file_h.sc ) )
    {
        st_s* key_defined = st_s_create_fa( "##?'define HKEYOF_#<sc_t>'", o.name.sc ).scope();
        bcore_source* source = bcore_file_open_source( file_h->sc ).scope();
        while( !source.eos() )
        {
            char c = source.get_u0();
            if( c == '#' )
            {
                if( source.parse_bl( key_defined.sc ) )
                {
                    tp_t key_val = 0;
                    source.parse_fa( " #<tp_t*>", &key_val );
                    to_be_modified = ( key_val != target_hash );
                    break;
                }
            }
        }
    }

    return to_be_modified;
};

//----------------------------------------------------------------------------------------------------------------------

/// expands all text files in memory
func (:s) :.expand_phase1 = (try)
{
    o.target_h =< NULL;
    o.target_c =< NULL;
    o.modified = false;

    if( o.to_be_modified() )
    {
        o.target_h = st_s!;
        o.target_c = st_s!;
        if( !o.compiler.dry_run )
        {
            o.expand_h( 0, o.target_h );
            o.expand_c( 0, o.target_c );
        }
        else
        {
            st_s* buf = st_s!.scope();
            o.expand_h( 0, buf );
            o.expand_c( 0, buf );
        }
        o.modified = true;
    }

    if( p_modified ) p_modified.0 = o.modified;

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

/// returns true if a file was modified
func (er_t write_with_signature( sc_t file, const st_s* data )) = (try)
{
    tp_t hash = bcore_tp_fold_sc( bcore_tp_init(), data.sc );
    bcore_sink* sink = bcore_file_open_sink( file ).scope();
    sink.push_data( ( vc_t )data.data, data.size );
    sink.push_fa( "// XOILA_OUT_SIGNATURE 0x#pl16'0'{#X<tp_t>}ull\n", hash );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

/// returns true if a file was modified
func (:s) :.expand_phase2 = (try)
{
    if( !o.modified )
    {
        if( p_modified.1 ) p_modified.0 = false;
        return 0;
    }

    ASSERT( o.target_h );
    ASSERT( o.target_c );

    st_s* file_h = st_s_create_fa( "#<sc_t>.h", o.path.sc ).scope();
    st_s* file_c = st_s_create_fa( "#<sc_t>.c", o.path.sc ).scope();

    if( o.readonly )
    {
        bcore_msg_fa( "Affected: #<sc_t>\n", file_h.sc );
        bcore_msg_fa( "Affected: #<sc_t>\n", file_c.sc );
        if( p_modified.1 ) p_modified.0 = false;
    }
    else
    {
        o.compiler.check_overwrite( file_h.sc );
        o.compiler.check_overwrite( file_c.sc );
        bcore_msg_fa( "Writing: #<sc_t>\n", file_h.sc );
        xoico_target_write_with_signature( file_h.sc, o.target_h );
        bcore_msg_fa( "Writing: #<sc_t>\n", file_c.sc );
        xoico_target_write_with_signature( file_c.sc, o.target_c );
        if( p_modified.1 ) p_modified.0 = true;
    }
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

