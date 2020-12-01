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

func (:target) :.load = (try)
{
    st_s* st_path = st_s!.scope();
    st_path.copy_sc( path );

    if( st_path->sc[ 0 ] != '/' )
    {
        st_s* current_folder = st_s!.scope();
        bcore_folder_get_current( current_folder );
        st_path = st_s_create_fa( "#<sc_t>/#<sc_t>", current_folder.sc, st_path.sc ).scope();
    }

    st_path = bcore_file_path_minimized( st_path.sc ).scope();

    bcore_txt_ml_a_from_file( o, st_path.sc );
    o->full_path_.copy( st_path );
    if( readonly ) o.readonly = true;

    if( !o.name ) return bcore_error_push_fa( TYPEOF_general_error, "In target file: '#<sc_t>'\nTarget name must be specified.", st_path->sc );

    /// check for dependency cycles
    if( o.parent_ )
    {
        const xoico_builder_target_s* match = o->parent_.name_match( o->name.sc );
        if( match )
        {
            if( match.full_path_.equal_st( o.full_path_ ) )
            {
                return bcore_error_push_fa( TYPEOF_general_error, "In target file: '#<sc_t>'\nCyclic dependency detected.", st_path.sc );
            }
            else
            {
                return bcore_error_push_fa( TYPEOF_general_error, "Same target name '#<sc_t>' used in different target files:\n#<sc_t>\n#<sc_t>", o.name.sc, st_path.sc, match.full_path_.sc );
            }
        }
    }

    foreach( $* e in o.dependencies )
    {
        if( !o.dependencies_target_ ) o.dependencies_target_ = xoico_builder_arr_target_s!;

        st_s* file_path = st_s!.scope( scope_local );
        if( e.sc[ 0 ] != '/' )
        {
            if( o.root_folder ) file_path.push_fa( "#<sc_t>/", o.root_folder.sc );
        }

        bl_t dep_readonly = o.readonly;

        bcore_source* source = bcore_source_string_s_create_sc( e.sc ).scope( scope_local );
        source.parse_em_fa( " #:until':'", file_path );

        /// remove trailing spaces
        while( file_path.sc[ 0 ] == ' ' || file_path.sc[ 0 ] == '\t' ) file_path.pop_char();

        if( bcore_source_a_parse_bl( source, "#?':'" ) )
        {
            if( source.parse_bl( " #?w'readonly'" ) )
            {
                dep_readonly = true;
            }
            else
            {
                return source.parse_error_fa( "Syntax error in dependency declaration." );
            }
        }

        xoico_builder_target_s* target = o->dependencies_target_.push_d( xoico_builder_target_s! );
        target.parent_ = o;

        target.load( dep_readonly, file_path->sc );
    }

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:target) :.build = (try)
{
    if( !o.root_    ) o.root_    = ( o.parent_ ) ? o.parent_.root_    : o;
    if( !o.compiler ) o.compiler = ( o.parent_ ) ? o.parent_.compiler : NULL;

    if( o == o.root_ )
    {
        if( !o.hmap_built_target_ ) o.hmap_built_target_ = bcore_hmap_tpvd_s!;
    }

    ASSERT( o.compiler );
    ASSERT( o.root_ );

    tp_t tp_target_name = bentypeof( o.name.sc );

    foreach( $* e in o.dependencies_target_ ) e.build();

    if( o.root_.hmap_built_target_.exists( tp_target_name ) )
    {
        xoico_builder_target_s* target = o.root_.hmap_built_target_.get( tp_target_name ).cast( xoico_builder_target_s** ).1;
        o.target_index_ = target.target_index_;
        return 0;
    }

    o.root_.hmap_built_target_.set( tp_target_name, ( vd_t )o );

    o.target_index_ = -1;

    bcore_msg_fa( "XOICO: compiling #<sc_t>\n", o.full_path_.sc );

    foreach( $* e in o.sources )
    {
        st_s* file_path = st_s!.scope( scope_local );
        if( e.sc[ 0 ] != '/' )
        {
            if( o.root_folder ) file_path.push_fa( "#<sc_t>/", o.root_folder.sc );
        }
        file_path.push_fa( "#<sc_t>", e.sc );

        ASSERT( o.name );
        ASSERT( o.extension );
        sz_t index = -1;

        o.compiler.parse( o->name->sc, o->extension->sc, file_path.sc, index );

        if( o.target_index_ == -1 ) o.target_index_ = index;
        if( index != o.target_index_ )
        {
            return bcore_error_push_fa
            (
                TYPEOF_general_error,
                "Building source '#<sc_t>' in target '#<sc_t>':\n"
                "Target index mismatch.\n"
                "This problem occurs when a target defines sources from different directories.\n",
                e.sc,
                o.name.sc
            );
        }
    }

    if( o.target_index_ >= 0 )
    {
        ASSERT( o.target_index_ < o.compiler.size );
        bcore_arr_sz_s* dependencies = bcore_arr_sz_s!.scope();
        foreach( $* e in o->dependencies_target_ ) e.push_target_index_to_arr( dependencies );

        xoico_target_s* target = o.compiler.[ o.target_index_ ];

        target.set_dependencies( dependencies );
        st_s* signal_handler = st_s_create_fa( "#<sc_t>_general_signal_handler", o.name.sc ).scope();
        if( o.signal_handler ) signal_handler.copy( o.signal_handler );
        target.signal_handler_name.copy_sc( signal_handler.sc );
        target.readonly = o.readonly;
        target.cengine =< o.cengine.fork();
    }

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

func (:main) :.build_from_file = (try)
{
    o.target =< xoico_builder_target_s!;
    o.target.load( false, path );
    o.target.compiler = o.compiler;
    o.target.build();
    o.compiler.finalize();
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:main) :.update =
{
    if( bcore_error_stack_size() > 0 ) return TYPEOF_error_stack;
    try( o.compiler.update_target_files( NULL ) );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

