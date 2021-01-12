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

func (:s) :.register_group =
{
    if( o.hmap_group.exists( group.tp_name ) )
    {
        return bcore_source_point_s_parse_error_fa
        (
            group.source_point,
            "'#<sc_t>' was already registered\n",
            o.nameof( group.tp_name )
        );
    }
    o.hmap_group.set( group.tp_name, ( vd_t )group );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) :.register_item =
{
    tp_t global_id = item.get_global_name_tp();
    if( o.hmap_item.exists( global_id ) )
    {
        return item.get_source_point().parse_error_fa( "'#<sc_t>' was already registered\n", o.nameof( global_id ) );
    }
    o.hmap_item.set( global_id, ( vd_t )item );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) :.register_func =
{
    if( o.hmap_func.exists( func.global_name ) )
    {
        m xoico_func_s* func_registered = o.hmap_func.get( func.global_name ).cast( m xoico_func_s** );

        if( func_registered == func )
        {
            return bcore_source_point_s_parse_error_fa
            (
                func.source_point,
                "Global func name '#<sc_t>' was already registered from same instance.\n",
                o.nameof( func.global_name )
            );
        }
        else
        {
            return bcore_source_point_s_parse_error_fa
            (
                func.source_point,
                "Global func name '#<sc_t>' was already registered from different instance.\n"
                "'#<sc_t>' vs '#<sc_t>'\n",
                o.nameof( func.global_name ),
                o.nameof( func.name ),
                o.nameof( func_registered.name )
            );
        }
    }

    o.hmap_func.set( func.global_name, ( vd_t )func );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

/// returns true if correct signature could be verified
func (bl_t is_signed( sc_t file )) =
{
    m bcore_source* source = bcore_file_open_source( file ).scope();
    m st_s* data = st_s!^^;
    while( !source.eos() ) data.push_char( source.get_u0() );

    if( data.size < bcore_strlen( "// XOILA_OUT_SIGNATURE" ) ) return false;

    sz_t idx = data.size - 1;
    while( idx >= 0 && data.[ idx ] != '/' ) idx--;
    if( idx > 0 ) idx--;

    if( data.find_sc( idx, -1, "// XOILA_OUT_SIGNATURE" ) != idx ) return false;

    tp_t hash = 0;
    data.parse_fa( idx, -1, "// XOILA_OUT_SIGNATURE #<tp_t*>", hash.1 );

    data.[ idx ] = 0;

    if( hash != bcore_tp_fold_sc( bcore_tp_init(), data.sc ) ) return false;

    return true;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) :.check_overwrite =
{
    if( !bcore_file_exists( file ) ) return 0;

    if( !xoico_compiler_is_signed( file ) )
    {
        m st_s* s = st_s!^;
        s.push_fa( "Planted file #<sc_t>: Signature check failed.\n", file );
        s.push_fa( "This file might have been created or edited outside the xoico framework.\n" );
        if( o.overwrite_unsigned_target_files )
        {
            s.push_fa( "Flag 'overwrite_unsigned_target_files' is 'true'. The file will be overwritten.\n" );
            bcore_sink_a_push_fa( BCORE_STDERR, "\nWARNING: #<sc_t>\n", s->sc );
        }
        else
        {
            s.push_fa( "Xoico has currently no permission to overwrite unsigned target files.\n" );
            s.push_fa( "You can fix it in one of following ways:\n" );
            s.push_fa( "* Rename or (re)move the file.\n" );
            s.push_fa( "* Use command line flag '-f'.\n" );
            return bcore_error_push_fa( TYPEOF_general_error, "\nERROR: #<sc_t>\n", s->sc );
        }
    }

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) :.parse = (try)
{
    m st_s* source_folder_path = bcore_file_folder_path( source_path ).scope();
    m st_s* target_path        = st_s_create_fa( "#<sc_t>/#<sc_t>.#<sc_t>", source_folder_path->sc, target_name, target_ext ).scope();

    sz_t target_index = -1;
    for( sz_t i = 0; i < o->size; i++ )
    {
        if( target_path.equal_st( o.[ i ].path ) )
        {
            target_index = i;
            break;
        }
    }

    if( target_index == -1 )
    {
        d xoico_target_s* target = xoico_target_s!;
        target.compiler = o;
        target.name        .copy_fa( "#<sc_t>_#<sc_t>", target_name, target_ext );
        target.include_path.copy_fa( "#<sc_t>.#<sc_t>", target_name, target_ext );
        target.path.copy( target_path );
        o.push_d( target );
        target_index = o->size - 1;
    }

    m xoico_target_s* target = o.[ target_index ];
    target.parse_from_path( source_path );
    if( p_target_index ) p_target_index.0 = target_index;

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) xoico.finalize = (try)
{
    foreach( m $* e in o ) e.finalize( o );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) xoico.expand_setup = (try)
{
    for( sz_t i = 0; i < o->size; i++ ) o.[ i ].expand_setup( o );

    /* We obtain all names from the global map.
     * This is necessary because names of reflection elements are parsed outside
     * this framework and remembered by the global map.
     */
    bcore_name_push_all( o.name_map.1 );

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

/// returns true if a file will be modified in function xoico_compiler_s_expand
func (:s) (bl_t to_be_modified( c @* o )) =
{
    for( sz_t i = 0; i < o->size; i++ )
    {
        if( o.[ i ].to_be_modified() ) return true;
    }
    return false;
};

//----------------------------------------------------------------------------------------------------------------------

/// returns true if a file was modified
func (:s) (er_t expand( m @* o, m bl_t* p_modified )) = (try)
{
    bl_t modified = false;

    o.expand_setup( o );
    for( sz_t i = 0; i < o->size; i++ ) o.[i].expand_phase1( modified.1 );
    for( sz_t i = 0; i < o->size; i++ ) o.[i].expand_phase2( modified.1 );

    if( p_modified ) p_modified.0 = modified;
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) :.get_self =
{
    c xoico* item = o.get_const_item( type );
    if( !item ) return false;

    if( item->_ == TYPEOF_xoico_stamp_s )
    {
        c xoico_stamp_s* stamp = item.cast( c xoico_stamp_s* );
        if( self ) self.1 = stamp->self;
        return true;
    }

    return false;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) :.get_type_info =
{
    c xoico* item = o.get_const_item( type );
    if( !item ) return false;
    ASSERT( info );
    if( item->_ == TYPEOF_xoico_stamp_s || item->_ == TYPEOF_xoico_group_s )
    {
        info.item = item.cast( m $* );
        info.typespec.type = type;
        return true;
    }

    return false;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) :.get_type_element_info =
{
    c xoico* xoico_item = o.get_const_item( type );
    if( !xoico_item )
    {
        xoico_item = o.cast( m $* ).get_group( type ).cast( c xoico* );
        if( !xoico_item ) return false;
    }

    bl_t success = false;
    ASSERT( info );
    info.type_info.item = xoico_item.cast( m $* );

    if( xoico_item->_ == TYPEOF_xoico_stamp_s )
    {
        c xoico_stamp_s* stamp = xoico_item.cast( c xoico_stamp_s* );
        c bcore_self_s* self = stamp.self;
        c bcore_self_item_s* self_item = NULL; // returns NULL in case of no match

        if( ( self_item = self.get_item_by_name( name ) ) )
        {
            if( self_item.caps == BCORE_CAPS_EXTERNAL_FUNC )
            {
                info.func = stamp.get_func_from_name( name ).cast( m $* );
                ASSERT( info.func );
                success = true;
            }
            else if( bcore_flect_caps_is_array_fix( self_item.caps ) )
            {
                info.type_info.typespec.access_class = TYPEOF_mutable;
                info.type_info.typespec.type = self_item.type;
                info.type_info.typespec.indirection = 1;
                success = true;
            }
            else if( !bcore_flect_caps_is_array_dyn( self_item.caps ) ) // dynamic arrays are handled separately
            {
                sz_t indirection = bcore_flect_caps_get_indirection( self_item.caps );
                info.type_info.typespec.type = self_item.type;
                info.type_info.typespec.indirection = indirection;
                info.type_info.typespec.access_class = ( indirection > 0 ) ? TYPEOF_mutable : 0;
                success = true;
            }
        }
        else if( ( info.func = stamp.get_trait_line_func_from_name( name ).cast( m $* ) ) ) /// trait-line function
        {
            success = true;
        }
        else if( ( self_item = bcore_self_s_get_first_anonymous_array_item( self ) ) ) /// builtin elements for arrays
        {
            if( name == TYPEOF_size )
            {
                info.type_info.typespec.type = TYPEOF_uz_t;
                info.type_info.typespec.indirection = 0;
                info.type_info.typespec.access_class = 0;
                success = true;
            }
            else if( name == TYPEOF_space )
            {
                info.type_info.typespec.type = TYPEOF_uz_t;
                info.type_info.typespec.indirection = 0;
                info.type_info.typespec.access_class = 0;
                success = true;
            }
            else if( name == TYPEOF_data )
            {
                info.type_info.typespec.access_class = TYPEOF_mutable;
                info.type_info.typespec.type = self_item.type ? self_item.type : TYPEOF_x_inst;
                info.type_info.typespec.indirection = bcore_flect_caps_get_indirection( self_item.caps ) + 1;
                success = true;
            }
            else if( name == TYPEOF_type )
            {
                if( bcore_flect_caps_is_typed( self_item.caps ) )
                {
                    info.type_info.typespec.type = TYPEOF_tp_t;
                    info.type_info.typespec.indirection = 0;
                    info.type_info.typespec.access_class = 0;
                    success = true;
                }
            }
        }
    }
    else if( xoico_item._ == TYPEOF_xoico_group_s )
    {
        c $* group = xoico_item.cast( m xoico_group_s* );
        if( name == TYPEOF__ ) // group builtin element '_'
        {
            info.type_info.typespec.type = TYPEOF_tp_t;
            info.type_info.typespec.indirection = 0;
            success = true;
        }
        else
        {
            info.func = group.get_trait_line_func_from_name( name ).cast( m $* );
            if( info.func ) success = true;
        }
    }

    return success;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) :.get_type_array_element_info =
{
    ASSERT( info );

    c xoico* xoico_item = o.get_const_item( type );
    if( !xoico_item ) return false;
    bl_t success = false;
    info.type_info.item = xoico_item.cast( m xoico* );

    if( xoico_item->_ == TYPEOF_xoico_stamp_s )
    {
        c xoico_stamp_s* stamp = xoico_item.cast( c xoico_stamp_s* );
        c bcore_self_item_s* self_item = bcore_self_s_get_first_anonymous_array_item( stamp.self );
        if( self_item )
        {
            info.type_info.typespec.type = self_item.type;
            info.type_info.typespec.indirection = bcore_flect_caps_get_indirection( self_item.caps );
            success = true;
        }
    }

    return success;
};

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// xoico interface

//----------------------------------------------------------------------------------------------------------------------

func (:s) :.update_target_files =
{
    bl_t modified = false;
    bl_t verbosity = o.verbosity;
    f3_t time = 0;

    er_t er = 0;
    ABS_TIME_OF( er = o.expand( modified.1 ), time );
    try( er );

    if( modified )
    {
        if( verbosity > 0 ) bcore_msg_fa( "XOICO: Expanded in #<f3_t> sec.\n", time );
        if( verbosity > 0 ) bcore_msg_fa( "XOICO: Files were updated. Rebuild is necessary.\n" );
    }

    if( p_modified ) p_modified.0 = modified;

    return er;
};

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
