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

func (:) :.register_group =
{
    if( o.hmap_group.exists( group.tp_name ) )
    {
        return bcore_source_point_s_parse_error_fa
        (
            &group.source_point,
            "'#<sc_t>' was already registered\n",
            o.nameof( group.tp_name )
        );
    }
    o.hmap_group.set( group.tp_name, ( vd_t )group );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) :.register_item =
{
    tp_t global_id = item.get_global_name_tp();
    if( o.hmap_item.exists( global_id ) )
    {
        return o.parse_err_fa( source, "'#<sc_t>' was already registered\n", o.nameof( global_id ) );
    }
    o.hmap_item.set( global_id, ( vd_t )item );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) :.register_func =
{
    if( o.hmap_func.exists( func.global_name ) )
    {
        return bcore_source_point_s_parse_error_fa
        (
            &func.source_point,
            "'#<sc_t>' was already registered\n",
            o.nameof( func.global_name )
        );
    }

    o.hmap_func.set( func.global_name, ( vd_t )func );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

/// returns true if correct signature could be verified
func (bl_t is_signed( sc_t file )) =
{
    bcore_source* source = BLM_A_PUSH( bcore_file_open_source( file ) );
    st_s* data = st_s!.scope();
    while( !source.eos() ) data.push_char( source.get_u0() );

    if( data.size < bcore_strlen( "// XOILA_OUT_SIGNATURE" ) ) return false;

    sz_t idx = data.size - 1;
    while( idx >= 0 && data.[ idx ] != '/' ) idx--;
    if( idx > 0 ) idx--;

    if( data.find_sc( idx, -1, "// XOILA_OUT_SIGNATURE" ) != idx ) return false;

    tp_t hash = 0;
    data.parse_fa( idx, -1, "// XOILA_OUT_SIGNATURE #<tp_t*>", &hash );

    data.[ idx ] = 0;

    if( hash != bcore_tp_fold_sc( bcore_tp_init(), data.sc ) ) return false;

    return true;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) :.check_overwrite =
{
    if( !bcore_file_exists( file ) ) return 0;

    if( !xoico_compiler_is_signed( file ) )
    {
        st_s* s = st_s!.scope( scope_local );
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

func (:) :.parse =
{
try
{
    st_s* source_folder_path = scope( cast( bcore_file_folder_path( source_path ), st_s* ) );
    st_s* target_path        = scope( cast( st_s_create_fa( "#<sc_t>/#<sc_t>", source_folder_path->sc, target_name ), st_s* ) );

    sz_t target_index = -1;
    for( sz_t i = 0; i < o->size; i++ )
    {
        if( target_path.equal_st( &o.[ i ].path ) )
        {
            target_index = i;
            break;
        }
    }

    if( target_index == -1 )
    {
        xoico_target_s* target = xoico_target_s!;
        target.compiler = o;
        target.name.copy_sc( target_name );
        target.path.copy( target_path );
        o.push_d( target );
        target_index = o->size - 1;
    }

    xoico_target_s* target = o.[ target_index ];
    target.parse( source_path );
    if( p_target_index ) *p_target_index = target_index;

    return 0;
} // try
};

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico.finalize =
{
    try
    {
        for( sz_t i = 0; i < o->size; i++ ) o.[ i ].finalize();
    }
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico.expand_setup =
{
    try
    {
        for( sz_t i = 0; i < o->size; i++ ) o.[ i ].expand_setup();

        /* We obtain all names from the global map.
         * This is necessary because names of reflection elements are parsed outside
         * this framework and remembered by the global map.
         */
        bcore_name_push_all( &o->name_map );
    }

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

/// returns true if a file will be modified in function xoico_compiler_s_expand
func (:) (bl_t to_be_modified( const )) =
{
    for( sz_t i = 0; i < o->size; i++ )
    {
        if( o.[ i ].to_be_modified() ) return true;
    }
    return false;
};

//----------------------------------------------------------------------------------------------------------------------

/// returns true if a file was modified
func (:) (er_t expand( mutable, bl_t* p_modified )) =
{
try
{
    bl_t modified = false;

    o.expand_setup();
    for( sz_t i = 0; i < o->size; i++ ) o.[i].expand_phase1( &modified );
    for( sz_t i = 0; i < o->size; i++ ) o.[i].expand_phase2( &modified );

    if( p_modified ) *p_modified = modified;
    return 0;
} // try
};

//----------------------------------------------------------------------------------------------------------------------

func (:) :.get_self =
{
    const xoico* item = o.get_const_item( type );
    if( !item ) return false;

    if( item->_ == TYPEOF_xoico_stamp_s )
    {
        const xoico_stamp_s* stamp = item.cast( const xoico_stamp_s* );
        if( self ) *self = stamp->self;
        return true;
    }

    return false;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) :.get_type_info =
{
    const xoico* item = o.get_const_item( type );
    if( !item ) return false;
    ASSERT( info );
    if( item->_ == TYPEOF_xoico_stamp_s || item->_ == TYPEOF_xoico_group_s )
    {
        info.item = item.cast( xoico* );
        info.typespec.type = type;
        return true;
    }

    return false;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) :.get_type_element_info =
{
    const xoico* xoico_item = o.get_const_item( type );
    if( !xoico_item )
    {
        xoico_item = o.cast( $* ).get_group( type ).cast( const xoico* );
        if( !xoico_item ) return false;
    }

    bl_t success = false;
    ASSERT( info );
    info->type_info.item = xoico_item.cast( $* );

    if( xoico_item->_ == TYPEOF_xoico_stamp_s )
    {
        const xoico_stamp_s* stamp = xoico_item.cast( const xoico_stamp_s* );
        const bcore_self_s* self = stamp.self;
        const bcore_self_item_s* self_item = self.get_item_by_name( name ); // returns NULL in case of no match

        bl_t found = true;
        sz_t indirection = 0;

        if( self_item )
        {
            switch( self_item.caps )
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

        info.type_info.typespec.flag_const = false;

        if( !found )
        {
            // try function
            xoico_func_s* func = stamp.funcs.get_func_from_name( name );
            if( func )
            {
                info.type_info.typespec.type = func->global_name;
                info.type_info.typespec.indirection = 0;
                const xoico_signature_s* signature = func.signature;
                info.type_info.typespec.flag_const = ( signature->arg_o == TYPEOF_const );
                info.signature =< signature.clone();
                info.signature.relent( self.type );
                success = true;
            }
            else // try generic types
            {
                success = false;
            }
        }
        else
        {
            info.type_info.typespec.type = self_item.type;
            info.type_info.typespec.indirection = indirection;
            info.signature = NULL;
            success = true;
        }
    }
    else if( xoico_item._ == TYPEOF_xoico_group_s )
    {
        xoico_group_s* group = xoico_item.cast( xoico_group_s* );
        if( group.hmap_feature.exists( name ) )
        {
            info.type_info.typespec.flag_const = false;
            xoico_feature_s* feature = *group.hmap_feature.get( name );
            if( feature.flag_a )
            {
                const xoico_signature_s* signature = &feature.signature;
                info.type_info.typespec.flag_const = ( signature->arg_o == TYPEOF_const );
                sc_t  st_func_name = o.nameof( name );
                ASSERT( st_func_name );
                st_s* st_full_func_name = st_s!.scope( scope_local );
                st_full_func_name.copy_fa( "#<sc_t>_a_#<sc_t>", group.st_name.sc, st_func_name );
                info.type_info.typespec.type = o.cast( $* ).entypeof( st_full_func_name->sc );
                info.type_info.typespec.indirection = 0;
                info.signature =< signature.clone();
                info.signature.relent( group.tp_name );
                success = true;
            }
        }
    }

    return success;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) :.get_type_array_element_info =
{
    ASSERT( info );

    const xoico* xoico_item = o.get_const_item( type );
    if( !xoico_item ) return false;
    bl_t success = false;
    info.type_info.item = xoico_item.cast( xoico* );
    tp_t tp_no_name = btypeof( "" );

    if( xoico_item->_ == TYPEOF_xoico_stamp_s )
    {
        const xoico_stamp_s* stamp = xoico_item.cast( const xoico_stamp_s* );
        const bcore_self_s* self = stamp.self;

        sz_t items = self.items_size();
        const bcore_self_item_s* self_item = NULL;
        for( sz_t i = 0; i < items; i++ )
        {
            const bcore_self_item_s* item = self.get_item( i );
            if( item->name == tp_no_name && bcore_flect_caps_is_array( item.caps ) )
            {
                self_item = item;
                break;
            }
        }

        if( self_item )
        {
            sz_t indirection = 0;
            switch( self_item.caps )
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

            info.type_info.typespec.type = self_item.type;
            info.type_info.typespec.indirection = indirection;
            info.signature = NULL;
            success = true;
        }
    }

    return success;
};

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// xoico interface

//----------------------------------------------------------------------------------------------------------------------

func (:) :.update_target_files =
{
    bl_t modified = false;
    bl_t verbosity = o.verbosity;
    f3_t time = 0;

    er_t er = 0;
    ABS_TIME_OF( er = o.expand( &modified ), time );
    try( er );

    if( modified )
    {
        if( verbosity > 0 ) bcore_msg_fa( "XOICO: Expanded in #<f3_t> sec.\n", time );
        if( verbosity > 0 ) bcore_msg_fa( "XOICO: Files were updated. Rebuild is necessary.\n" );
    }

    if( p_modified ) *p_modified = modified;

    return er;
};

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
