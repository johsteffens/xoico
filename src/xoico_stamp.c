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

#include "xoico_stamp.h"
#include "xoico_group.h"
#include "xoico_feature.h"
#include "xoico_compiler.h"

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

/// removes comments, excessive whitespaces; trailing whitespaces; keeps strings but replaces '"' with '\"'
static st_s* create_embedded_string( const st_s* s )
{
    st_s* out = st_s_create();
    for( sz_t i = 0; i < s->size; i++ )
    {
        if( s->data[ i ] == '/' && s->data[ i + 1 ] == '/' )
        {
            while( i < s->size && s->data[ i ] != '\n' ) i++;
        }
        else if( s->data[ i ] == '/' && s->data[ i + 1 ] == '*' )
        {
            while( i < s->size )
            {
                if( s->data[ i ] == '*' && s->data[ i + 1 ] == '/' )
                {
                    if( out->data[ out->size - 1 ] != ' ' ) st_s_push_char( out, ' ' );
                    i += 2;
                    break;
                }
                i++;
            }
        }
        else if( s->data[ i ] == '"' )
        {
            st_s_push_char( out, '\\' );
            st_s_push_char( out, '"' );
            i++;
            while( i < s->size && s->data[ i ] != '"' ) st_s_push_char( out, s->data[ i++ ] );
            if( s->data[ i ] == '"' )
            {
                st_s_push_char( out, '\\' );
                st_s_push_char( out, '"' );
            }
        }
        else if( s->data[ i ] == '\n' )
        {
            if( out->data[ out->size - 1 ] != ' ' ) st_s_push_char( out, ' ' );
        }
        else if( s->data[ i ] == '\t' )
        {
            if( out->data[ out->size - 1 ] != ' ' ) st_s_push_char( out, ' ' );
        }
        else if( s->data[ i ] == ' ' )
        {
            if( out->data[ out->size - 1 ] != ' ' ) st_s_push_char( out, ' ' );
        }
        else
        {
            st_s_push_char( out, s->data[ i ] );
        }
    }
    if( out->size > 0 && out->data[ out->size - 1 ] == ' ' )
    {
        out->data[ out->size - 1 ] = 0;
        out->size--;
    }
    return out;
}

//----------------------------------------------------------------------------------------------------------------------

/** Creates a structured multiline string for direct code embedding
 *  from an embedded string
 */
static st_s* create_structured_multiline_string( const sc_t s, sz_t indent )
{
    st_s* out = st_s_create();
    sz_t ind = indent;
    bl_t newline = true;
    for( sz_t i = 0; s[ i ] != 0; i++ )
    {
        char c = s[ i ];
        if( c == ';' )
        {
            if( newline ) st_s_push_fa( out, "#rn{ }\"", ind );
            st_s_push_char( out, c );
            st_s_push_fa( out, "\"\n" );
            newline = true;
        }
        else if( c == '{' )
        {
            if( newline )
            {
                st_s_push_fa( out, "#rn{ }\"{\"", ind );
            }
            else
            {
                st_s_push_fa( out, "\"\n#rn{ }\"{\"", ind );
            }
            if( s[ i + 1 ] != 0 ) st_s_push_char( out, '\n' );
            ind += 4;
            newline = true;

        }
        else if( c == '}' )
        {
            ind -= 4;
            if( newline )
            {
                st_s_push_fa( out, "#rn{ }\"}\"", ind );
            }
            else
            {
                st_s_push_fa( out, "\"\n#rn{ }\"}\"", ind );
            }
            if( s[ i + 1 ] != 0 ) st_s_push_char( out, '\n' );
            newline = true;
        }
        else if( c == ' ' )
        {
            if( !newline )
            {
                if( s[ i + 1 ] != ';' && s[ i + 1 ] != '{' && s[ i + 1 ] != '}' && s[ i + 1 ] != 0 )
                {
                    st_s_push_char( out, c );
                }
            }
        }
        else
        {
            if( newline )
            {
                st_s_push_fa( out, "#rn{ }\"", ind );
                newline = false;
            }
            st_s_push_char( out, c );
        }
    }

    if( !newline ) st_s_push_char( out, '"' );
    return out;
}

//----------------------------------------------------------------------------------------------------------------------

sc_t xoico_stamp_s_get_global_name_sc( const xoico_stamp_s* o )
{
    return o->st_name.sc;
}

//----------------------------------------------------------------------------------------------------------------------

sc_t xoico_stamp_s_get_rel_name_sc( const xoico_stamp_s* o )
{
    sc_t group_name = o->group->st_name.sc;
    sc_t stamp_name = o->st_name.sc;

    sz_t i = 0;
    while( group_name[ i ] == stamp_name[ i ] && group_name[ i ] != 0 ) i++;
    if( group_name[ i ] == 0 && stamp_name[ i ] == '_' ) i++;

    return stamp_name + i;
}

//----------------------------------------------------------------------------------------------------------------------

tp_t xoico_stamp_s_get_hash( const xoico_stamp_s* o )
{
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
    hash = bcore_tp_fold_sc( hash, o->st_name.sc );
    hash = bcore_tp_fold_sc( hash, o->self_source->sc );
    hash = bcore_tp_fold_tp( hash, xoico_funcs_s_get_hash( &o->funcs ) );
    return hash;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_stamp_s_parse_func( xoico_stamp_s* o, bcore_source* source )
{
    BLM_INIT();
    xoico_compiler_s* compiler = o->group->compiler;
    xoico_func_s* func = BLM_CREATE( xoico_func_s );
    func->group = o->group;
    func->stamp = o;
    BLM_TRY( xoico_func_s_parse( func, source ) );

    bl_t register_func = xoico_func_s_registerable( func );
    sz_t idx = xoico_funcs_s_get_index_from_name( &o->funcs, func->name );

    if( idx >= 0 )
    {
        xoico_func_s* prex_func = o->funcs.data[ idx ];
        if( ( prex_func->signature_global_name == func->signature_global_name ) )
        {
            if( !func->body )
            {
                XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Function '#<sc_t>' has already been declared.", xoico_compiler_s_nameof( compiler, func->name ) );
            }
            else if( prex_func->body )
            {
                XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Function '#<sc_t>' has already a body.", xoico_compiler_s_nameof( compiler, func->name ) );
            }
            else
            {
                BLM_TRY( xoico_funcs_s_replace_fork( &o->funcs, idx, func ) );
                st_s_replace_sc_sc( o->self_source, prex_func->flect_decl.sc, "" );
            }
        }
        else if( prex_func->overloadable )
        {
            BLM_TRY( xoico_funcs_s_replace_fork( &o->funcs, idx, func ) );
            st_s_replace_sc_sc( o->self_source, prex_func->flect_decl.sc, "" );
        }
        else
        {
            XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Function '#<sc_t>' has already been declared and is not overloadable.", xoico_compiler_s_nameof( compiler, func->name ) );
        }
    }
    else
    {
        xoico_funcs_s_push_d( &o->funcs, bcore_fork( func ) );
    }


    if( register_func )
    {
        bl_t push_brace = false;
        if( o->self_source->size > 0 && o->self_source->sc[ o->self_source->size - 1 ] == '}' )
        {
            o->self_source->size--;
            push_brace = true;
        }
        st_s_push_st( o->self_source, &func->flect_decl );
        if( push_brace ) st_s_push_sc( o->self_source, "}" );
    }

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_stamp_s_parse_extend( xoico_stamp_s* o, bcore_source* source )
{
    BLM_INIT();
    ASSERT( o->self_source );

    XOICO_BLM_SOURCE_PARSE_FA( source, " {" );

    if( o->self_source->size > 0 && o->self_source->sc[ o->self_source->size - 1 ] == '}' )
    {
        o->self_source->size--;
    }
    else
    {
        st_s_push_fa( o->self_source, "{" );
    }

    while( !bcore_source_a_eos( source ) && !bcore_source_a_parse_bl_fa( source, " #?'}'" ) )
    {
        if( bcore_source_a_parse_bl_fa( source, " #?w'func'" ) )
        {
            BLM_TRY( xoico_stamp_s_parse_func( o, source ) );
        }
        else
        {
            bl_t exit = false;
            while( !exit && !bcore_source_a_eos( source ) )
            {
                u0_t c = bcore_source_a_get_u0( source );
                switch( c )
                {
                    case ':':
                    {
                        BLM_INIT();
                        st_s* name = BLM_CREATE( st_s );
                        BLM_TRY( xoico_group_s_parse_name_recursive( o->group, name, source ) );
                        st_s_push_st( o->self_source, name );
                        BLM_DOWN();
                    }
                    break;

                    case ';':
                    {
                        st_s_push_char( o->self_source, c );
                        exit = true;
                    }
                    break;

                    default:
                    {
                        st_s_push_char( o->self_source, c );
                    }
                    break;
                }
            }
        }
    }
    XOICO_BLM_SOURCE_PARSE_FA( source, " ; " );
    st_s_push_sc( o->self_source, "}" );

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_stamp_s_push_default_func_from_sc( xoico_stamp_s* o, sc_t sc )
{
    BLM_INIT();
    xoico_compiler_s* compiler = o->group->compiler;
    xoico_func_s* func = BLM_CREATE( xoico_func_s );
    func->group = o->group;
    func->stamp = o;
    func->overloadable = false;
    func->expandable = false;
    BLM_TRY( xoico_func_s_parse( func, BLM_A_PUSH( bcore_source_string_s_create_sc( sc ) ) ) );

    sz_t idx = xoico_funcs_s_get_index_from_signature_global_name( &o->funcs, func->signature_global_name );

    if( idx >= 0 )
    {
        XOICO_BLM_SOURCE_POINT_PARSE_ERR_FA( &o->source_point, "Function '#<sc_t>' is predefined for all stamps and cannot be overloaded.", xoico_compiler_s_nameof( compiler, func->name ) );
    }
    else
    {
        bcore_array_a_push( ( bcore_array* )&o->funcs, sr_asd( bcore_fork( func ) ) );
    }

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_stamp_s_push_default_funcs( xoico_stamp_s* o )
{
    BLM_INIT();
    BLM_TRY( xoico_stamp_s_push_default_func_from_sc( o, "bcore_stamp_funcs.init;" ) );
    BLM_TRY( xoico_stamp_s_push_default_func_from_sc( o, "bcore_stamp_funcs.down;" ) );
    BLM_TRY( xoico_stamp_s_push_default_func_from_sc( o, "bcore_stamp_funcs.copy;" ) );
    BLM_TRY( xoico_stamp_s_push_default_func_from_sc( o, "bcore_stamp_funcs.discard;" ) );
    BLM_TRY( xoico_stamp_s_push_default_func_from_sc( o, "bcore_stamp_funcs.clone;" ) );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_stamp_s_parse( xoico_stamp_s* o, bcore_source* source )
{
    BLM_INIT();

    xoico_compiler_s* compiler = o->group->compiler;
    bl_t verbatim = bcore_source_a_parse_bl_fa( source, " #?w'verbatim'" );

    st_s_attach( &o->self_source, st_s_create() );

    st_s* stamp_name = BLM_CREATE( st_s );
    st_s* trait_name = BLM_CREATE( st_s );

    bcore_source_point_s_set( &o->source_point, source );

    BLM_TRY( xoico_group_s_parse_name( o->group, stamp_name, source ) );

    if( stamp_name->size >= 2 && sc_t_equ( stamp_name->sc + stamp_name->size - 2, "_s" ) )
    {
        WRN_fa( "Stamp '#<sc_t>' ends in '_s'. In beth, this ending identifies a structure. Using it as stamp name can have side effects. Is this intended?", stamp_name->sc );
    }

    st_s_push_fa( stamp_name, "_s" );

    XOICO_BLM_SOURCE_PARSE_FA( source, " = " );

    if( bcore_source_a_parse_bl_fa( source, " #?w'extending'" ) )
    {
        st_s* templ_name = BLM_CREATE( st_s );
        BLM_TRY( xoico_group_s_parse_name( o->group, templ_name, source ) );
        st_s_push_fa( templ_name, "_s" );
        const xoico* item = xoico_compiler_s_get_const_item( o->group->compiler, typeof( templ_name->sc ) );
        if( !item ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Template #<sc_t> not found.", templ_name->sc );
        if( *(aware_t*)item != TYPEOF_xoico_stamp_s ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Template #<sc_t> is no stamp.", templ_name->sc );
        xoico_stamp_s_copy( o, ( xoico_stamp_s* )item );
    }
    else if( !verbatim && o->group->extending_stamp )
    {
        xoico_stamp_s_copy( o, o->group->extending_stamp );
    }
    else
    {
        st_s_push_fa( o->self_source, "@ =" );

        if( bcore_source_a_parse_bl_fa( source, " #?w'aware'" ) ) st_s_push_sc( o->self_source, "aware " );

        if( bcore_source_a_parse_bl_fa( source, " #?':'" ) )
        {
            st_s_copy( trait_name, &o->group->st_name );
        }
        else
        {
            BLM_TRY( xoico_group_s_parse_name( o->group, trait_name, source ) );
            if( trait_name->size == 0 ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Trait name expected." );
        }

        st_s_copy( &o->st_trait_name, trait_name );
        st_s_push_st( o->self_source, trait_name );
    }

    st_s_copy( &o->st_name, stamp_name );
    o->tp_name = xoico_compiler_s_entypeof( compiler, stamp_name->sc );

    BLM_TRY( xoico_stamp_s_parse_extend( o, source ) );

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_stamp_s_finalize( xoico_stamp_s* o )
{
    BLM_INIT();

    xoico_compiler_s* compiler = o->group->compiler;

    // TODO: move functions declaration in self_source to finalize
    st_s_replace_sc_sc( o->self_source, "@", o->st_name.sc );

    for( sz_t i = 0; i < o->funcs.size; i++ )
    {
        xoico_func_s* func = o->funcs.data[ i ];
        func->group = o->group;
        func->stamp = o;
        BLM_TRY( xoico_func_s_finalize( func ) );
        xoico_compiler_s_register_func( compiler, func );
    }

    bcore_self_s_attach
    (
        &o->self,
        bcore_self_s_parse_source
        (
            BLM_A_PUSH( (bcore_source*)bcore_source_string_s_create_from_string( o->self_source ) ),
            0,
            0,
            o->group->st_name.sc,
            false
        )
    );

    bcore_hmap_tp_s* hmap_name = BLM_CREATE( bcore_hmap_tp_s );

    sz_t self_items = bcore_self_s_items_size( o->self );

    if( self_items > 0 )
    {
        for( sz_t i = 0; i < self_items; i++ )
        {
            const bcore_self_item_s* item = bcore_self_s_get_item( o->self, i );
            if( item->name )
            {
                if( bcore_hmap_tp_s_exists( hmap_name, item->name ) )
                {
                    XOICO_BLM_SOURCE_POINT_PARSE_ERR_FA( &o->source_point, "In stamp '<sc_t>': Repeated use of element name '<sc_t>'.", o->st_name.sc, xoico_compiler_s_nameof( compiler, item->name ) );
                    bcore_hmap_tp_s_set( hmap_name, item->name );
                }
            }
        }
    }

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_stamp_s_expand_setup( xoico_stamp_s* o )
{
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_stamp_s_make_funcs_overloadable( xoico_stamp_s* o )
{
    for( sz_t i = 0; i < o->funcs.size; i++ )
    {
        xoico_func_s* func = o->funcs.data[ i ];
        func->overloadable = true;
    }
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_stamp_s_expand_forward( const xoico_stamp_s* o, sz_t indent, bcore_sink* sink )
{
    bcore_sink_a_push_fa( sink, " \\\n#rn{ }BCORE_FORWARD_OBJECT( #<sc_t> );", indent, o->st_name.sc );
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_stamp_s_expand_indef_declaration( const xoico_stamp_s* o, sz_t indent, bcore_sink* sink )
{
    bcore_sink_a_push_fa( sink, " \\\n#rn{ }  BETH_EXPAND_ITEM_#<sc_t>", indent, o->st_name.sc );
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_stamp_s_expand_declaration( const xoico_stamp_s* o, sz_t indent, bcore_sink* sink )
{
    BLM_INIT();

    sc_t sc_name = o->st_name.sc;

    bcore_sink_a_push_fa( sink, "#rn{ }##define TYPEOF_#<sc_t> 0x#pl16'0'{#X<tp_t>}ull\n", indent, sc_name, typeof( sc_name ) );

    bcore_sink_a_push_fa( sink, "#rn{ }##define BETH_EXPAND_ITEM_#<sc_t>", indent, sc_name, sc_name );
    bcore_sink_a_push_fa( sink, " \\\n#rn{ }  BCORE_DECLARE_OBJECT( #<sc_t> )", indent, sc_name );
    bcore_sink_a_push_fa( sink, " \\\n" );

    bcore_self_s_struct_body_to_sink_newline_escaped( o->self, indent + 2, sink );
    bcore_sink_a_push_fa( sink, ";" );

    for( sz_t i = 0; i < o->funcs.size; i++ ) BLM_TRY( xoico_func_s_expand_forward(     o->funcs.data[ i ], indent + 2, sink ) ); // expands all prototypes

    // expand array
    if( o->self->trait == TYPEOF_bcore_array )
    {
        sz_t items = bcore_self_s_items_size( o->self );
        const bcore_self_item_s* array_item = NULL;
        for( sz_t i = 0; i < items; i++ )
        {
            const bcore_self_item_s* self_item = bcore_self_s_get_item( o->self, i );
            if( bcore_flect_caps_is_array( self_item->caps ) )
            {
                array_item = self_item;
                break;
            }
        }

        if( !array_item )
        {
            XOICO_BLM_SOURCE_POINT_PARSE_ERR_FA( &o->source_point, "Expanding object #<sc_t>: Object is of trait array but contains no array.", sc_name );
        }

        bcore_sink_a_push_fa( sink, " \\\n#rn{ }  static inline #<sc_t>* #<sc_t>_set_space( #<sc_t>* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_#<sc_t>, ( bcore_array* )o, size ); return o; }", indent, sc_name, sc_name, sc_name, sc_name );
        bcore_sink_a_push_fa( sink, " \\\n#rn{ }  static inline #<sc_t>* #<sc_t>_set_size( #<sc_t>* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_#<sc_t>, ( bcore_array* )o, size ); return o; }",   indent, sc_name, sc_name, sc_name, sc_name );
        bcore_sink_a_push_fa( sink, " \\\n#rn{ }  static inline #<sc_t>* #<sc_t>_clear( #<sc_t>* o ) { bcore_array_t_set_space( TYPEOF_#<sc_t>, ( bcore_array* )o, 0 ); return o; }",                   indent, sc_name, sc_name, sc_name, sc_name );

        sc_t  sc_item_name = ifnameof( array_item->name );
        st_s* st_last = BLM_A_PUSH( st_s_create_fa( "o->#<sc_t>#<sc_t>data[ o->#<sc_t>#<sc_t>size - 1 ]", sc_item_name, sc_item_name[ 0 ] ? "_" : "", sc_item_name, sc_item_name[ 0 ] ? "_" : ""  ) );
        sc_t  sc_last = st_last->sc;
        if( array_item->type != 0 && nameof( array_item->type ) != NULL )
        {
            sc_t sc_type = ifnameof( array_item->type );
            if( array_item->caps == BCORE_CAPS_ARRAY_DYN_LINK_AWARE )
            {
                bcore_sink_a_push_fa( sink, " \\\n#rn{ }  static inline #<sc_t>* #<sc_t>_push_c( #<sc_t>* o, const #<sc_t>* v ) { bcore_array_t_push( TYPEOF_#<sc_t>, ( bcore_array* )o, sr_awc( v ) ); return #<sc_t>; }", indent, sc_type, sc_name, sc_name, sc_type, sc_name, sc_last );
                bcore_sink_a_push_fa( sink, " \\\n#rn{ }  static inline #<sc_t>* #<sc_t>_push_d( #<sc_t>* o,       #<sc_t>* v ) { bcore_array_t_push( TYPEOF_#<sc_t>, ( bcore_array* )o, sr_asd( v ) ); return #<sc_t>; }", indent, sc_type, sc_name, sc_name, sc_type, sc_name, sc_last );
                bcore_sink_a_push_fa( sink, " \\\n#rn{ }  static inline #<sc_t>* #<sc_t>_push_t( #<sc_t>* o, tp_t t )", indent, sc_type, sc_name, sc_name );
                bcore_sink_a_push_fa( sink, " \\\n#rn{ }  {", indent );
                bcore_sink_a_push_fa( sink, " \\\n#rn{ }      bcore_trait_assert_satisfied_type( TYPEOF_#<sc_t>, t );",                    indent, sc_type );
                bcore_sink_a_push_fa( sink, " \\\n#rn{ }      bcore_array_t_push( TYPEOF_#<sc_t>, ( bcore_array* )o, sr_t_create( t ) );", indent, sc_name );
                bcore_sink_a_push_fa( sink, " \\\n#rn{ }      return #<sc_t>;", indent, sc_last );
                bcore_sink_a_push_fa( sink, " \\\n#rn{ }  }", indent );
            }
            else if( array_item->caps == BCORE_CAPS_ARRAY_DYN_SOLID_STATIC )
            {
                bcore_sink_a_push_fa( sink, " \\\n#rn{ }  static inline #<sc_t>* #<sc_t>_push_c( #<sc_t>* o, const #<sc_t>* v ) { bcore_array_t_push( TYPEOF_#<sc_t>, ( bcore_array* )o, sr_twc( TYPEOF_#<sc_t>, v ) ); return &#<sc_t>; }", indent, sc_type, sc_name, sc_name, sc_type, sc_name, sc_type, sc_last );
                bcore_sink_a_push_fa( sink, " \\\n#rn{ }  static inline #<sc_t>* #<sc_t>_push_d( #<sc_t>* o,       #<sc_t>* v ) { bcore_array_t_push( TYPEOF_#<sc_t>, ( bcore_array* )o, sr_tsd( TYPEOF_#<sc_t>, v ) ); return &#<sc_t>; }", indent, sc_type, sc_name, sc_name, sc_type, sc_name, sc_type, sc_last );
                bcore_sink_a_push_fa( sink, " \\\n#rn{ }  static inline #<sc_t>* #<sc_t>_push( #<sc_t>* o )", indent, sc_type, sc_name, sc_name );
                bcore_sink_a_push_fa( sink, " \\\n#rn{ }  {", indent );
                bcore_sink_a_push_fa( sink, " \\\n#rn{ }      bcore_array_t_push( TYPEOF_#<sc_t>, ( bcore_array* )o, sr_null() );",   indent, sc_name );
                bcore_sink_a_push_fa( sink, " \\\n#rn{ }      return &#<sc_t>;", indent, sc_last );
                bcore_sink_a_push_fa( sink, " \\\n#rn{ }  }", indent );
            }
            else if( array_item->caps == BCORE_CAPS_ARRAY_DYN_LINK_STATIC )
            {
                bcore_sink_a_push_fa( sink, " \\\n#rn{ }  static inline #<sc_t>* #<sc_t>_push_c( #<sc_t>* o, const #<sc_t>* v ) { bcore_array_t_push( TYPEOF_#<sc_t>, ( bcore_array* )o, sr_twc( TYPEOF_#<sc_t>, v ) ); return #<sc_t>; }", indent, sc_type, sc_name, sc_name, sc_type, sc_name, sc_type, sc_last );
                bcore_sink_a_push_fa( sink, " \\\n#rn{ }  static inline #<sc_t>* #<sc_t>_push_d( #<sc_t>* o,       #<sc_t>* v ) { bcore_array_t_push( TYPEOF_#<sc_t>, ( bcore_array* )o, sr_tsd( TYPEOF_#<sc_t>, v ) ); return #<sc_t>; }", indent, sc_type, sc_name, sc_name, sc_type, sc_name, sc_type, sc_last );
                bcore_sink_a_push_fa( sink, " \\\n#rn{ }  static inline #<sc_t>* #<sc_t>_push( #<sc_t>* o )", indent, sc_type, sc_name, sc_name );
                bcore_sink_a_push_fa( sink, " \\\n#rn{ }  {", indent );
                bcore_sink_a_push_fa( sink, " \\\n#rn{ }      bcore_array_t_push( TYPEOF_#<sc_t>, ( bcore_array* )o, sr_t_create( TYPEOF_#<sc_t> ) );", indent, sc_name, sc_type );
                bcore_sink_a_push_fa( sink, " \\\n#rn{ }      return #<sc_t>;", indent, sc_last );
                bcore_sink_a_push_fa( sink, " \\\n#rn{ }  }", indent );
            }
        }
        else
        {
            if( bcore_flect_caps_is_aware( array_item->caps ) )
            {
                bcore_sink_a_push_fa( sink, " \\\n#rn{ }  static inline void #<sc_t>_push_c( #<sc_t>* o, vc_t v ) { bcore_array_t_push( TYPEOF_#<sc_t>, ( bcore_array* )o, sr_awc( v ) ); }", indent, sc_name, sc_name, sc_name );
                bcore_sink_a_push_fa( sink, " \\\n#rn{ }  static inline void #<sc_t>_push_d( #<sc_t>* o, vd_t v ) { bcore_array_t_push( TYPEOF_#<sc_t>, ( bcore_array* )o, sr_asd( v ) ); }", indent, sc_name, sc_name, sc_name );
            }
        }
    }

    for( sz_t i = 0; i < o->funcs.size; i++ ) BLM_TRY( xoico_func_s_expand_declaration( o->funcs.data[ i ], indent + 2, sink ) ); // only expands static inline functions

    bcore_sink_a_push_fa( sink, "\n" );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_stamp_s_expand_definition( const xoico_stamp_s* o, sz_t indent, bcore_sink* sink )
{
    BLM_INIT();

    st_s* embedded_string = BLM_A_PUSH( create_embedded_string( o->self_source ) );

    // 4095 is the C99-limit for string literals
    if( embedded_string->size > 4095 )
    {
        XOICO_BLM_SOURCE_POINT_PARSE_ERR_FA
        (
            &o->source_point,
            "Reflection embedding failed.\n"
            "The embedded code would require a string literal larger than 4095 characters.\n"
            "This exceeds the limit defined in C99.\n"
        );
    }

    sz_t idx = st_s_find_char( embedded_string, 0, -1, '=' );
    sc_t self_def = "";
    if( idx < embedded_string->size )
    {
        self_def = embedded_string->sc + idx + 1;
    }

    bcore_sink_a_push_fa( sink, "\n" );
    bcore_sink_a_push_fa( sink, "#rn{ }BCORE_DEFINE_OBJECT_INST_P( #<sc_t> )\n", indent, o->st_name.sc );

    st_s* multiline_string = BLM_A_PUSH( create_structured_multiline_string( self_def, indent ) );
    bcore_sink_a_push_fa( sink, "#<sc_t>;\n", multiline_string->sc );

    for( sz_t i = 0; i < o->funcs.size; i++ )
    {
        BLM_TRY( xoico_func_s_expand_definition( o->funcs.data[ i ], indent, sink ) );
    }

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_stamp_s_expand_init1( const xoico_stamp_s* o, sz_t indent, bcore_sink* sink )
{
    BLM_INIT();
    xoico_compiler_s* compiler = o->group->compiler;

    for( sz_t i = 0; i < o->funcs.size; i++ )
    {
        xoico_func_s* func = o->funcs.data[ i ];
        if( !func->expandable ) continue;

        if( xoico_func_s_registerable( func ) )
        {
            const xoico_signature_s* signature = func->signature;
            bcore_sink_a_push_fa
            (
                sink,
                "#rn{ }BCORE_REGISTER_FFUNC( #<sc_t>, #<sc_t>_#<sc_t> );\n",
                indent,
                xoico_compiler_s_nameof( compiler, signature->global_name ),
                o->st_name.sc,
                xoico_compiler_s_nameof( compiler, func->name )
            );
        }
    }
    bcore_sink_a_push_fa( sink, "#rn{ }BCORE_REGISTER_OBJECT( #<sc_t> );\n", indent, o->st_name.sc );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

