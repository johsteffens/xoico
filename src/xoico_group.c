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

#include "xoico_group.h"
#include "xoico_nested_group.h"
#include "xoico_signature.h"
#include "xoico_name.h"
#include "xoico_forward.h"
#include "xoico_feature.h"
#include "xoico_stamp.h"
#include "xoico_source.h"
#include "xoico_target.h"
#include "xoico_compiler.h"

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

sc_t xoico_group_s_get_global_name_sc( const xoico_group_s* o )
{
    return o->name.sc;
}

//----------------------------------------------------------------------------------------------------------------------

tp_t xoico_group_s_get_hash( const xoico_group_s* o )
{
    return o->hash;
}

//----------------------------------------------------------------------------------------------------------------------

st_s* xoico_group_s_create_spect_name( const xoico_group_s* o )
{
    if( o->short_spect_name )
    {
        return st_s_create_fa( "#<sc_t>_s", o->name.sc );
    }
    else
    {
        return st_s_create_fa( "#<sc_t>_spect_s", o->name.sc );
    }
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_group_s_parse_name_recursive( xoico_group_s* o, st_s* name, bcore_source* source )
{
    BLM_INIT();
    if( bcore_source_a_parse_bl_fa( source, "#?':'" ) )
    {
        if( o->group )
        {
            BLM_TRY( xoico_group_s_parse_name_recursive( o->group, name, source ) );
        }
        else
        {
            XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Too many colons: Namespace depth exceeded." );
        }
    }
    else
    {
        st_s_copy( name, &o->name );
        st_s* s = BLM_CREATE( st_s );
        XOICO_BLM_SOURCE_PARSE_FA( source, " #name", s );

        if( s->size > 0 )
        {
            st_s_push_fa( name, "_#<sc_t>", s->sc );
        }
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_group_s_parse_name( xoico_group_s* o, st_s* name, bcore_source* source )
{
    BLM_INIT();
    if( bcore_source_a_parse_bl_fa( source, " #?':'" ) )
    {
        BLM_TRY( xoico_group_s_parse_name_recursive( o, name, source ) );
    }
    else
    {
        XOICO_BLM_SOURCE_PARSE_FA( source, " #name", name );
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_group_s_parse( xoico_group_s* o, bcore_source* source )
{
    BLM_INIT();

    xoico_group_source_stack_s* stack = BLM_CREATE( xoico_group_source_stack_s );
    xoico_group_source_stack_s_push_d( stack, bcore_fork( source ) );

    sc_t group_termination = NULL;

    bcore_source_point_s_set( &o->source_point, source );
    o->hash = bcore_tp_init();
    o->hash = bcore_tp_fold_sc( o->hash, o->name.sc );
    o->hash = bcore_tp_fold_sc( o->hash, o->trait_name.sc );

    if( o->group ) // this group is nested in another group, the group body is enclosed in { ... }
    {
        XOICO_BLM_SOURCE_PARSE_FA( source, " {" );
        group_termination = " #?'}'";
    }
    else // this group is root
    {
        if( bcore_source_a_parse_bl_fa( source, " #?'#ifdef XOILA_SECTION'" ) )
        {
            group_termination = " #?'#endif'";
        }
        else
        {
            group_termination = NULL;
        }
    }

    bl_t extend_stump = false;

    while
    (
        stack->size >= 2 ||
        ( group_termination ? !bcore_source_a_parse_bl_fa( source, group_termination ) : !bcore_source_a_eos( source ) )
    )
    {
        BLM_INIT();
        xoico* item = NULL;

        if( bcore_source_a_eos( source ) )
        {
            if( stack->size >= 2 )
            {
                bcore_source_a_detach( &stack->data[ stack->size - 1 ] );
                source = stack->data[ stack->size - 2 ];
                xoico_group_source_stack_s_set_size( stack, stack->size - 1 );
            }
            else if( group_termination )
            {
                XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Unexpected end of file." );
            }
            else
            {
                BLM_BREAK();
            }
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?w'stamp' " ) )
        {
            xoico_stamp_s* stamp = BLM_CREATE( xoico_stamp_s );
            stamp->group = o->group;
            BLM_TRY( xoico_stamp_s_parse( stamp, o, source ) );
            BLM_TRY( xoico_compiler_s_item_register( xoico_group_s_get_compiler( o ), ( xoico* )stamp, source ) );
            item = ( xoico* )bcore_fork( stamp );
        }

        /// stumps are 'hidden' stamps (not expanded into final code), but they can be used as template
        else if( bcore_source_a_parse_bl_fa( source, " #?w'stump' " ) )
        {
            xoico_stamp_s* stump = BLM_CREATE( xoico_stamp_s );
            BLM_TRY( xoico_stamp_s_parse( stump, o, source ) );
            BLM_TRY( xoico_stamp_s_make_funcs_overloadable( stump ) );
            BLM_TRY( xoico_compiler_s_item_register( xoico_group_s_get_compiler( o ), ( xoico* )stump, source ) );
            BLM_TRY( xoico_compiler_s_life_a_push( xoico_group_s_get_compiler( o ), bcore_fork( stump ) ) );
            if( extend_stump )
            {
                o->extending = stump;
                extend_stump = false;
            }
            item = NULL;
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?w'signature' " ) )
        {
            xoico_signature_s* signature = BLM_CREATE( xoico_signature_s );
            signature->group = o;
            BLM_TRY( xoico_signature_s_parse( signature, source ) );
            XOICO_BLM_SOURCE_PARSE_FA( source, " ; " );
            BLM_TRY( xoico_compiler_s_item_register( xoico_group_s_get_compiler( o ), ( xoico* )signature, source ) );
            item = ( xoico* )bcore_fork( signature );
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?w'body' " ) )
        {
            xoico_body_s* body = BLM_CREATE( xoico_body_s );
            BLM_TRY( xoico_body_s_set_group( body, o ) );
            BLM_TRY( xoico_body_s_parse( body, source ) );
            XOICO_BLM_SOURCE_PARSE_FA( source, " ; " );
            BLM_TRY( xoico_compiler_s_item_register( xoico_group_s_get_compiler( o ), ( xoico* )body, source ) );
            item = ( xoico* )bcore_fork( body );
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?w'feature' " ) )
        {
            xoico_feature_s* feature = BLM_CREATE( xoico_feature_s );
            feature->group = o;
            BLM_TRY( xoico_feature_s_parse( feature, source ) );
            BLM_TRY( xoico_compiler_s_item_register( xoico_group_s_get_compiler( o ), ( xoico* )feature, source ) );
            o->has_features = true;
            if( feature->flag_a ) o->is_aware = true;
            item = ( xoico* )bcore_fork( feature );
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?w'name' " ) )
        {
            xoico_name_s* name = BLM_CREATE( xoico_name_s );
            name->group = o;
            BLM_TRY( xoico_name_s_parse( name, source ) );
            item = ( xoico* )bcore_fork( name );
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?w'type' " ) )
        {
            xoico_name_s* name = BLM_CREATE( xoico_name_s );
            name->group = o;
            BLM_TRY( xoico_name_s_parse( name, source ) );
            item = ( xoico* )bcore_fork( name );
            BLM_TRY( xoico_compiler_s_type_register( xoico_group_s_get_compiler( o ), btypeof( name->name.sc ) ) );
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?w'forward' " ) )
        {
            xoico_forward_s* forward = BLM_CREATE( xoico_forward_s );
            forward->group = o;
            BLM_TRY( xoico_forward_s_parse( forward, source ) );
            item = ( xoico* )bcore_fork( forward );
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?w'extending'" ) )
        {
            o->extending = NULL;
            if( bcore_source_a_parse_bl_fa( source, " #=?';'" ) )
            {
                // just reset o->extending - nothing else
            }
            else if( bcore_source_a_parse_bl_fa( source, " #=?w'stump'" ) )
            {
                extend_stump = true;
            }
            else
            {
                st_s* templ_name = BLM_CREATE( st_s );
                BLM_TRY( xoico_group_s_parse_name( o, templ_name, source ) );
                st_s_push_fa( templ_name, "_s" );
                const xoico* item = xoico_compiler_s_item_get( xoico_group_s_get_compiler( o ), typeof( templ_name->sc ) );
                if( !item ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Template #<sc_t> not found.", templ_name->sc );
                if( *(aware_t*)item != TYPEOF_xoico_stamp_s ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Template #<sc_t> is no stamp.", templ_name->sc );
                o->extending = ( xoico_stamp_s* )item;
                XOICO_BLM_SOURCE_PARSE_FA( source, " ;" );
            }
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?w'func'" ) )
        {
            bcore_source_a_parse_msg_fa( source, "Declaring a group-level function will be repurposed. Use a stump instead." );

            xoico_func_s* func = BLM_CREATE( xoico_func_s );
            func->group = o;
            xoico_func_s_parse( func, NULL, source );
            func->overloadable = true;
            o->hash = bcore_tp_fold_tp( o->hash, xoico_func_s_get_hash( func ) );

            if( xoico_funcs_s_exists_from_type( &o->funcs, func->type ) )
            {
                BLM_TRY( xoico_funcs_s_replace_fork( &o->funcs, xoico_funcs_s_get_index_from_type( &o->funcs, func->type ), func ) );
            }
            else
            {
                bcore_array_a_push( ( bcore_array* )&o->funcs, sr_asd( bcore_fork( func ) ) );
            }
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?w'group' " ) )
        {
            xoico_group_s* group = BLM_CREATE( xoico_group_s );
            BLM_TRY( xoico_source_s_push_group( o->source, bcore_fork( group ) ) );
            group->group       = o;
            group->source      = o->source;
            group->extending   = o->extending;
            group->expandable  = o->expandable;

            BLM_TRY( xoico_group_s_parse_name( o, &group->name, source ) );
            XOICO_BLM_SOURCE_PARSE_FA( source, " =" );

            // flags
            if( bcore_source_a_parse_bl_fa( source, " #?w'retrievable' " ) ) group->retrievable = true;

            BLM_TRY( xoico_group_s_parse_name( o, &group->trait_name, source ) );
            if( group->trait_name.size == 0 ) st_s_copy( &group->trait_name, &o->name );
            BLM_TRY( xoico_group_s_parse( group, source ) );
            XOICO_BLM_SOURCE_PARSE_FA( source, " ; " );
            o->source->hash = bcore_tp_fold_tp( o->source->hash, group->hash );
            BLM_TRY( xoico_compiler_s_group_register( xoico_group_s_get_compiler( o ), group, source ) );
            xoico_nested_group_s* nested_group = BLM_CREATE( xoico_nested_group_s );
            nested_group->group = group;
            item = ( xoico* )bcore_fork( nested_group );
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?w'set' " ) )
        {
            if(      bcore_source_a_parse_bl_fa( source, " #?w'retrievable' "      ) ) o->retrievable = true;
            else if( bcore_source_a_parse_bl_fa( source, " #?w'inexpandable' "     ) ) o->expandable = false;
            else if( bcore_source_a_parse_bl_fa( source, " #?w'short_spect_name' " ) ) o->short_spect_name = true;
            else if( bcore_source_a_parse_bl_fa( source, " #?w'beta' "             ) ) XOICO_BLM_SOURCE_PARSE_FA( source, " = #<tp_t*>", &o->beta );
            XOICO_BLM_SOURCE_PARSE_FA( source, " ;" );
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?w'embed' " ) )
        {
            st_s* folder = BLM_A_PUSH( bcore_file_folder_path( bcore_source_a_get_file( source ) ) );
            if( folder->size == 0 ) st_s_push_char( folder, '.' );
            st_s* include_file = BLM_CREATE( st_s );
            XOICO_BLM_SOURCE_PARSE_FA( source, " #string" , include_file );
            XOICO_BLM_SOURCE_PARSE_FA( source, " ;" );
            bcore_arr_st_s_push_st( &o->source->target->explicit_embeddings, include_file );

            bcore_source* embed_source = NULL;
            BLM_TRY( xoico_embed_file_open( source, include_file->sc, &embed_source ) );

            // check for cyclic inclusions
            BFOR_EACH( i, stack )
            {
                sc_t path = bcore_source_a_get_file( embed_source );
                if( sc_t_equal( path, bcore_source_a_get_file( stack->data[ i ] ) ) )
                {
                    XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Xoico: Cyclic inclusion." );
                }
            }

            xoico_group_source_stack_s_push_d( stack, source = embed_source );
        }
        else
        {
            XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Xoico: syntax error." );
        }

        o->hash = bcore_tp_fold_bl( o->hash, o->retrievable );
        o->hash = bcore_tp_fold_bl( o->hash, o->expandable );
        o->hash = bcore_tp_fold_bl( o->hash, o->short_spect_name );
        o->hash = bcore_tp_fold_tp( o->hash, o->beta );

        if( item )
        {
            o->hash = bcore_tp_fold_tp( o->hash, xoico_a_get_hash( item ) );
            bcore_array_a_push( ( bcore_array* )o, sr_asd( item ) );
        }

        BLM_DOWN();
    }

    if( stack->size > 1 )
    {
        XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Xoico: Unexpected end of group reached." );
    }

    // hash group parameters
    o->hash = bcore_tp_fold_tp( o->hash, o->retrievable ? 1 : 0 );

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_group_s_finalize( xoico_group_s* o )
{
    BLM_INIT();
    for( sz_t i = 0; i < o->size; i++ )
    {
        BLM_TRY( xoico_a_finalize( o->data[ i ] ) );
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_group_s_expand_setup( xoico_group_s* o )
{
    BLM_INIT();
    for( sz_t i = 0; i < o->size; i++ )
    {
        BLM_TRY( xoico_a_expand_setup( o->data[ i ] ) );
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_group_s_expand_forward( const xoico_group_s* o, sz_t indent, bcore_sink* sink )
{
    BLM_INIT();
    if( !o->expandable ) BLM_RETURNV( er_t, 0 );
    bcore_sink_a_push_fa( sink, " \\\n#rn{ }BCORE_FORWARD_OBJECT( #<sc_t> );", indent, o->name.sc );
    for( sz_t i = 0; i < o->size; i++ ) BLM_TRY( xoico_a_expand_forward( o->data[ i ], indent, sink ) );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_group_s_expand_spect_declaration( const xoico_group_s* o, sz_t indent, bcore_sink* sink )
{
    BLM_INIT();
    if( !o->expandable ) BLM_RETURNV( er_t, 0 );
    if( o->short_spect_name )
    {
        bcore_sink_a_push_fa( sink, " \\\n#rn{ }BCORE_DECLARE_SPECT( #<sc_t> )", indent, o->name.sc );
    }
    else
    {
        bcore_sink_a_push_fa( sink, " \\\n#rn{ }XOILA_DECLARE_SPECT( #<sc_t> )", indent, o->name.sc );
    }

    bcore_sink_a_push_fa( sink, " \\\n#rn{ }{", indent );
    bcore_sink_a_push_fa( sink, " \\\n#rn{ }    bcore_spect_header_s header;", indent );
    for( sz_t i = 0; i < o->size; i++ ) BLM_TRY( xoico_a_expand_spect_declaration( o->data[ i ], indent + 4, sink ) );
    bcore_sink_a_push_fa( sink, " \\\n#rn{ }};", indent );

    bcore_sink_a_push_fa( sink, " \\\n#rn{ }static inline #<sc_t>* #<sc_t>_t_create( tp_t t ) { bcore_trait_assert_satisfied_type( TYPEOF_#<sc_t>, t ); return ( #<sc_t>* )bcore_inst_t_create( t ); }", indent, o->name.sc, o->name.sc, o->name.sc, o->name.sc );
    bcore_sink_a_push_fa( sink, " \\\n#rn{ }static inline bl_t #<sc_t>_t_is_trait_of( tp_t t ) { return bcore_trait_is_of( t, TYPEOF_#<sc_t> ); }", indent, o->name.sc, o->name.sc );

    /// some extra functionality for aware types
    if( o->is_aware )
    {
        bcore_sink_a_push_fa( sink, " \\\n#rn{ }BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( #<sc_t> )", indent, o->name.sc );
        bcore_sink_a_push_fa( sink, " \\\n#rn{ }static inline bl_t #<sc_t>_a_is_trait_of( vc_t o ) { return bcore_trait_is_of( o ? *(aware_t*)o : 0, TYPEOF_#<sc_t> ); }", indent, o->name.sc, o->name.sc );
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_group_s_expand_declaration( const xoico_group_s* o, sz_t indent, bcore_sink* sink )
{
    BLM_INIT();

    if( !o->expandable ) BLM_RETURNV( er_t, 0 );

    bcore_sink_a_push_fa( sink, "\n" );
    bcore_sink_a_push_fa( sink, "#rn{ }//#rn{-}\n", indent, sz_max( 0, 118 - indent ) );
    bcore_sink_a_push_fa( sink, "#rn{ }// group: #<sc_t>\n", indent, o->name.sc );

    bcore_sink_a_push_fa( sink, "\n" );
    bcore_sink_a_push_fa( sink, "#rn{ }##define TYPEOF_#<sc_t> 0x#pl16'0'{#X<tp_t>}ull\n", indent, o->name.sc, typeof( o->name.sc ) );

    st_s* st_spect_name = BLM_A_PUSH( xoico_group_s_create_spect_name( o ) );
    sc_t  sc_spect_name = st_spect_name->sc;

    {
        bcore_sink_a_push_fa( sink, "#rn{ }##define TYPEOF_#<sc_t> 0x#pl16'0'{#X<tp_t>}ull\n", indent, sc_spect_name, typeof( sc_spect_name ) );
    }

    for( sz_t i = 0; i < o->size; i++ ) BLM_TRY( xoico_a_expand_declaration( o->data[ i ], indent, sink ) );
    bcore_sink_a_push_fa( sink, "#rn{ }##define BETH_EXPAND_GROUP_#<sc_t>", indent, o->name.sc );

    BLM_TRY( xoico_group_s_expand_forward( o, indent + 2, sink ) );

    if( o->has_features )
    {
        for( sz_t i = 0; i < o->size; i++ ) BLM_TRY( xoico_a_expand_indef_typedef( o->data[ i ], indent, sink ) );
        BLM_TRY( xoico_group_s_expand_spect_declaration( o, indent + 2, sink ) );
    }

    for( sz_t i = 0; i < o->size; i++ ) BLM_TRY( xoico_a_expand_indef_declaration( o->data[ i ], indent, sink ) );

    bcore_sink_a_push_fa( sink, "\n" );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_group_s_expand_spect_definition( const xoico_group_s* o, sz_t indent, bcore_sink* sink )
{
    BLM_INIT();
    if( !o->expandable ) BLM_RETURNV( er_t, 0 );
    bcore_sink_a_push_fa( sink, "\n" );
    if( o->short_spect_name )
    {
        bcore_sink_a_push_fa( sink, "#rn{ }BCORE_DEFINE_SPECT( #<sc_t>, #<sc_t> )\n", indent, o->trait_name.sc, o->name.sc );
    }
    else
    {
        bcore_sink_a_push_fa( sink, "#rn{ }XOILA_DEFINE_SPECT( #<sc_t>, #<sc_t> )\n", indent, o->trait_name.sc, o->name.sc );
    }

    bcore_sink_a_push_fa( sink, "#rn{ }\"{\"\n", indent );
    bcore_sink_a_push_fa( sink, "#rn{ }    \"bcore_spect_header_s header;\"\n", indent );
    for( sz_t i = 0; i < o->size; i++ ) BLM_TRY( xoico_a_expand_spect_definition( o->data[ i ], indent + 4, sink ) );
    bcore_sink_a_push_fa( sink, "#rn{ }\"}\";\n", indent );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_group_s_expand_definition( const xoico_group_s* o, sz_t indent, bcore_sink* sink )
{
    BLM_INIT();
    if( !o->expandable ) BLM_RETURNV( er_t, 0 );
    bcore_sink_a_push_fa( sink, "\n" );
    bcore_sink_a_push_fa( sink, "#rn{ }//#rn{-}\n", indent, sz_max( 0, 118 - indent ) );
    bcore_sink_a_push_fa( sink, "#rn{ }// group: #<sc_t>\n", indent, o->name.sc );
    for( sz_t i = 0; i < o->size; i++ )
    {
        // non-features
        if( *(aware_t*)o->data[ i ] != TYPEOF_xoico_feature_s )
        {
            BLM_TRY( xoico_a_expand_definition( o->data[ i ], indent, sink ) );
        }
    }

    if( o->has_features )
    {
        BLM_TRY( xoico_group_s_expand_spect_definition( o, indent, sink ) );
        for( sz_t i = 0; i < o->size; i++ )
        {
            // just-features
            if( *(aware_t*)o->data[ i ] == TYPEOF_xoico_feature_s )
            {
                BLM_TRY( xoico_a_expand_definition( o->data[ i ], indent, sink ) );
            }
        }
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_group_s_expand_init1( const xoico_group_s* o, sz_t indent, bcore_sink* sink )
{
    BLM_INIT();
    if( !o->expandable ) BLM_RETURNV( er_t, 0 );
    bcore_sink_a_push_fa( sink, "\n" );
    bcore_sink_a_push_fa( sink, "#rn{ }// group: #<sc_t>\n", indent, o->name.sc );
    for( sz_t i = 0; i < o->size; i++ ) BLM_TRY( xoico_a_expand_init1( o->data[ i ], indent, sink ) );

    if( o->has_features )
    {
        if( o->short_spect_name )
        {
            bcore_sink_a_push_fa( sink, "#rn{ }BCORE_REGISTER_SPECT( #<sc_t> );\n", indent, o->name.sc );
        }
        else
        {
            bcore_sink_a_push_fa( sink, "#rn{ }XOILA_REGISTER_SPECT( #<sc_t> );\n", indent, o->name.sc );
        }
    }
    else
    {
        bcore_sink_a_push_fa( sink, "#rn{ }BCORE_REGISTER_TRAIT( #<sc_t>, #<sc_t> );\n", indent, o->name.sc, o->trait_name.sc );
    }

    if( o->retrievable )
    {
        for( sz_t i = 0; i < o->size; i++ )
        {
            if( *(aware_t*)o->data[ i ] == TYPEOF_xoico_stamp_s )
            {
                const xoico_stamp_s* stamp = ( xoico_stamp_s* )o->data[ i ];
                bcore_sink_a_push_fa( sink, "#rn{ }bcore_inst_s_get_typed( TYPEOF_#<sc_t> );\n", indent, stamp->name.sc );
            }
        }
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

xoico_source_s* xoico_group_s_get_source( const xoico_group_s* o )
{
    return o->source;
}

//----------------------------------------------------------------------------------------------------------------------

xoico_target_s* xoico_group_s_get_target( const xoico_group_s* o )
{
    return o->source->target;
}

//----------------------------------------------------------------------------------------------------------------------

xoico_compiler_s* xoico_group_s_get_compiler( const xoico_group_s* o )
{
    //assert( o );
    return o->source->target->compiler;
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

