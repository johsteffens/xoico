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

#include "xoite_group.h"
#include "xoite_nested_group.h"
#include "xoite_signature.h"
#include "xoite_name.h"
#include "xoite_forward.h"
#include "xoite_feature.h"
#include "xoite_stamp.h"
#include "xoite_source.h"
#include "xoite_compiler.h"

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

sc_t xoite_group_s_get_global_name_sc( const xoite_group_s* o )
{
    return o->name.sc;
}

//----------------------------------------------------------------------------------------------------------------------

tp_t xoite_group_s_get_hash( const xoite_group_s* o )
{
    return o->hash;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoite_group_s_parse_name_recursive( xoite_group_s* o, st_s* name, bcore_source* source )
{
    BLM_INIT();
    if( bcore_source_a_parse_bl_fa( source, "#?':'" ) )
    {
        if( o->group )
        {
            BLM_TRY( xoite_group_s_parse_name_recursive( o->group, name, source ) );
        }
        else
        {
            XOITE_BLM_SOURCE_PARSE_ERR_FA( source, "Too many colons: Namespace depth exceeded." );
        }
    }
    else
    {
        st_s_copy( name, &o->name );
        st_s* s = BLM_CREATE( st_s );
        XOITE_BLM_SOURCE_PARSE_FA( source, " #name", s );

        // include certain key-characters in name
        if( bcore_source_a_parse_bl_fa( source, "#?'$'" ) )
        {
            st_s_push_char( s, '$' );
            XOITE_BLM_SOURCE_PARSE_FA( source, " #:name", s );
        }

        if( s->size > 0 )
        {
            st_s_push_fa( name, "_#<sc_t>", s->sc );
        }
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoite_group_s_parse_name( xoite_group_s* o, st_s* name, bcore_source* source )
{
    BLM_INIT();
    if( bcore_source_a_parse_bl_fa( source, " #?':'" ) )
    {
        BLM_TRY( xoite_group_s_parse_name_recursive( o, name, source ) );
    }
    else
    {
        XOITE_BLM_SOURCE_PARSE_FA( source, " #name", name );
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoite_group_s_parse( xoite_group_s* o, bcore_source* source )
{
    BLM_INIT();
    sc_t precode_termination = NULL;

    bcore_source_point_s_set( &o->source_point, source );
    o->hash = bcore_tp_init();
    o->hash = bcore_tp_fold_sc( o->hash, o->name.sc );
    o->hash = bcore_tp_fold_sc( o->hash, o->trait_name.sc );

    if( o->group ) // this group is nested in another group, the group body is enclosed in { ... }
    {
        XOITE_BLM_SOURCE_PARSE_FA( source, " {" );
        precode_termination = " #?'}'";
    }
    else // this group is root, the group body is enclosed in an non-parsable section of c source
    {
        while( !bcore_source_a_eos( source ) )
        {
            if( bcore_source_a_parse_bl_fa( source, "#?'/*'" ) )
            {
                XOITE_BLM_SOURCE_PARSE_FA( source, "#skip'*'" );
                precode_termination = " #?'*/'";
                break;
            }
            else if( bcore_source_a_parse_bl_fa( source, "#?'#ifdef'" ) )
            {
                XOITE_BLM_SOURCE_PARSE_FA( source, " PLANT_SECTION " );
                precode_termination = " #?'#endif'";
                break;
            }

            char c = bcore_source_a_get_u0( source );
            if( c != ' ' && c != '\t' && c != '\n' ) XOITE_BLM_SOURCE_PARSE_ERR_FA( source, "Opening c-style comment '/*' or '#<sc_t>' expected.", "#ifdef PLANT_SECTION" );
        }
    }

    bl_t extend_stump = false;

    while( !bcore_source_a_parse_bl_fa( source, precode_termination ) )
    {
        if( bcore_source_a_eos( source ) ) XOITE_BLM_SOURCE_PARSE_ERR_FA( source, "Closing c-style comment '*/' expected." );

        xoite* item = NULL;

        if( bcore_source_a_parse_bl_fa( source, " #?w'stamp' " ) )
        {
            BLM_INIT();
            xoite_stamp_s* stamp = BLM_CREATE( xoite_stamp_s );
            BLM_TRY( xoite_stamp_s_parse( stamp, o, source ) );
            BLM_TRY( xoite_compiler_s_item_register( xoite_compiler_g, ( xoite* )stamp, source ) );
            item = ( xoite* )bcore_fork( stamp );
            BLM_DOWN();
        }

        /// stumps are 'hidden' stamps (not expanded into final code), but they can be used as template
        else if( bcore_source_a_parse_bl_fa( source, " #?w'stump' " ) )
        {
            BLM_INIT();
            xoite_stamp_s* stump = BLM_CREATE( xoite_stamp_s );
            BLM_TRY( xoite_stamp_s_parse( stump, o, source ) );
            BLM_TRY( xoite_stamp_s_make_funcs_overloadable( stump ) );
            BLM_TRY( xoite_compiler_s_item_register( xoite_compiler_g, ( xoite* )stump, source ) );
            BLM_TRY( xoite_compiler_s_life_a_push( xoite_compiler_g, bcore_fork( stump ) ) );
            if( extend_stump )
            {
                o->extending = stump;
                extend_stump = false;
            }
            item = NULL;
            BLM_DOWN();
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?w'signature' " ) )
        {
            BLM_INIT();
            xoite_signature_s* signature = BLM_CREATE( xoite_signature_s );
            signature->group = o;
            BLM_TRY( xoite_signature_s_parse( signature, source ) );
            XOITE_BLM_SOURCE_PARSE_FA( source, " ; " );
            BLM_TRY( xoite_compiler_s_item_register( xoite_compiler_g, ( xoite* )signature, source ) );
            item = ( xoite* )bcore_fork( signature );
            BLM_DOWN();
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?w'body' " ) )
        {
            BLM_INIT();
            xoite_body_s* body = BLM_CREATE( xoite_body_s );
            body->group = o;
            BLM_TRY( xoite_body_s_parse( body, NULL, source ) );
            XOITE_BLM_SOURCE_PARSE_FA( source, " ; " );
            BLM_TRY( xoite_compiler_s_item_register( xoite_compiler_g, ( xoite* )body, source ) );
            item = ( xoite* )bcore_fork( body );
            BLM_DOWN();
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?w'feature' " ) )
        {
            BLM_INIT();
            xoite_feature_s* feature = BLM_CREATE( xoite_feature_s );
            feature->group = o;
            BLM_TRY( xoite_feature_s_parse( feature, source ) );
            BLM_TRY( xoite_compiler_s_item_register( xoite_compiler_g, ( xoite* )feature, source ) );
            o->has_features = true;
            if( feature->flag_a ) o->is_aware = true;
            item = ( xoite* )bcore_fork( feature );
            BLM_DOWN();
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?w'name' " ) )
        {
            BLM_INIT();
            xoite_name_s* name = BLM_CREATE( xoite_name_s );
            name->group = o;
            BLM_TRY( xoite_name_s_parse( name, source ) );
            item = ( xoite* )bcore_fork( name );
            BLM_DOWN();
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?w'forward' " ) )
        {
            BLM_INIT();
            xoite_forward_s* forward = BLM_CREATE( xoite_forward_s );
            forward->group = o;
            BLM_TRY( xoite_forward_s_parse( forward, source ) );
            item = ( xoite* )bcore_fork( forward );
            BLM_DOWN();
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?w'expandable'" ) )
        {
            XOITE_BLM_SOURCE_PARSE_FA( source, " = " );
            if(      bcore_source_a_parse_bl_fa( source, " #?'true'"  ) ) o->expandable = true;
            else if( bcore_source_a_parse_bl_fa( source, " #?'false'" ) ) o->expandable = false;
            else
            {
                XOITE_BLM_SOURCE_PARSE_ERR_FA( source, "'true' or 'false' expected." );
            }
            XOITE_BLM_SOURCE_PARSE_FA( source, " ; " );
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
                BLM_TRY( xoite_group_s_parse_name( o, templ_name, source ) );
                st_s_push_fa( templ_name, "_s" );
                const xoite* item = xoite_compiler_s_item_get( xoite_compiler_g, typeof( templ_name->sc ) );
                if( !item ) XOITE_BLM_SOURCE_PARSE_ERR_FA( source, "Template #<sc_t> not found.", templ_name->sc );
                if( *(aware_t*)item != TYPEOF_xoite_stamp_s ) XOITE_BLM_SOURCE_PARSE_ERR_FA( source, "Template #<sc_t> is no stamp.", templ_name->sc );
                o->extending = ( xoite_stamp_s* )item;
                XOITE_BLM_SOURCE_PARSE_FA( source, " ;" );
            }
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?w'func'" ) )
        {
            BLM_INIT();
            xoite_func_s* func = BLM_CREATE( xoite_func_s );
            xoite_func_s_parse( func, o, NULL, source );
            func->overloadable = true;
            o->hash = bcore_tp_fold_tp( o->hash, xoite_func_s_get_hash( func ) );

            if( xoite_funcs_s_exists( &o->funcs, func->type ) )
            {
                BLM_TRY( xoite_funcs_s_replace_fork( &o->funcs, xoite_funcs_s_get_index( &o->funcs, func->type ), func ) );
            }
            else
            {
                bcore_array_a_push( ( bcore_array* )&o->funcs, sr_asd( bcore_fork( func ) ) );
            }
            BLM_DOWN();
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?w'group' " ) )
        {
            BLM_INIT();
            xoite_group_s* group = BLM_CREATE( xoite_group_s );
            BLM_TRY( xoite_source_s_push_group( o->source, bcore_fork( group ) ) );
            group->group       = o;
            group->source      = o->source;
            group->extending   = o->extending;
            BLM_TRY( xoite_group_s_parse_name( o, &group->name, source ) );
            XOITE_BLM_SOURCE_PARSE_FA( source, " =" );

            // flags
            if( bcore_source_a_parse_bl_fa( source, " #?w'retrievable' " ) ) group->retrievable = true;

            BLM_TRY( xoite_group_s_parse_name( o, &group->trait_name, source ) );
            if( group->trait_name.size == 0 ) st_s_copy( &group->trait_name, &o->name );
            BLM_TRY( xoite_group_s_parse( group, source ) );
            XOITE_BLM_SOURCE_PARSE_FA( source, " ; " );
            o->source->hash = bcore_tp_fold_tp( o->source->hash, group->hash );
            BLM_TRY( xoite_compiler_s_group_register( xoite_compiler_g, group, source ) );
            xoite_nested_group_s* nested_group = BLM_CREATE( xoite_nested_group_s );
            nested_group->group = group;
            item = ( xoite* )bcore_fork( nested_group );
            BLM_DOWN();
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?w'set' " ) )
        {
            if( bcore_source_a_parse_bl_fa( source, " #?w'retrievable' " ) )
            {
                o->retrievable = true;
            }
            else
            {
                XOITE_BLM_SOURCE_PARSE_ERR_FA( source, "Invalid flag." );
            }

            XOITE_BLM_SOURCE_PARSE_FA( source, " ;" );
        }
        else
        {
            XOITE_BLM_SOURCE_PARSE_ERR_FA( source, "Plant: syntax error." );
        }

        // hash group parameters
        o->hash = bcore_tp_fold_tp( o->hash, o->retrievable ? 1 : 0 );

        if( item )
        {
            o->hash = bcore_tp_fold_tp( o->hash, xoite_a_get_hash( item ) );
            bcore_array_a_push( ( bcore_array* )o, sr_asd( item ) );
        }
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoite_group_s_finalize( xoite_group_s* o )
{
    BLM_INIT();
    for( sz_t i = 0; i < o->size; i++ ) BLM_TRY( xoite_a_finalize( o->data[ i ] ) );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoite_group_s_expand_forward( const xoite_group_s* o, sz_t indent, bcore_sink* sink )
{
    BLM_INIT();
    if( !o->expandable ) BLM_RETURNV( er_t, 0 );
    bcore_sink_a_push_fa( sink, " \\\n#rn{ }BCORE_FORWARD_OBJECT( #<sc_t> );", indent, o->name.sc );
    for( sz_t i = 0; i < o->size; i++ ) BLM_TRY( xoite_a_expand_forward( o->data[ i ], indent, sink ) );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoite_group_s_expand_spect_declaration( const xoite_group_s* o, sz_t indent, bcore_sink* sink )
{
    BLM_INIT();
    if( !o->expandable ) BLM_RETURNV( er_t, 0 );
    bcore_sink_a_push_fa( sink, " \\\n#rn{ }BCORE_DECLARE_SPECT( #<sc_t> )", indent, o->name.sc );
    bcore_sink_a_push_fa( sink, " \\\n#rn{ }{", indent );
    bcore_sink_a_push_fa( sink, " \\\n#rn{ }    bcore_spect_header_s header;", indent );
    for( sz_t i = 0; i < o->size; i++ ) BLM_TRY( xoite_a_expand_spect_declaration( o->data[ i ], indent + 4, sink ) );
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

er_t xoite_group_s_expand_declaration( const xoite_group_s* o, sz_t indent, bcore_sink* sink )
{
    BLM_INIT();

    if( !o->expandable ) BLM_RETURNV( er_t, 0 );

    bcore_sink_a_push_fa( sink, "\n" );
    bcore_sink_a_push_fa( sink, "#rn{ }//#rn{-}\n", indent, sz_max( 0, 118 - indent ) );
    bcore_sink_a_push_fa( sink, "#rn{ }// group: #<sc_t>\n", indent, o->name.sc );

    bcore_sink_a_push_fa( sink, "\n" );
    bcore_sink_a_push_fa( sink, "#rn{ }##define TYPEOF_#<sc_t> #<tp_t>\n", indent, o->name.sc, typeof( o->name.sc ) );

    {
        st_s* spect_name = BLM_A_PUSH( st_s_create_fa( "#<sc_t>_s", o->name.sc ) );
        bcore_sink_a_push_fa( sink, "#rn{ }##define TYPEOF_#<sc_t> #<tp_t>\n", indent, spect_name->sc, typeof( spect_name->sc ) );
    }

    for( sz_t i = 0; i < o->size; i++ ) BLM_TRY( xoite_a_expand_declaration( o->data[ i ], indent, sink ) );
    bcore_sink_a_push_fa( sink, "#rn{ }##define BETH_EXPAND_GROUP_#<sc_t>", indent, o->name.sc );

    BLM_TRY( xoite_group_s_expand_forward( o, indent + 2, sink ) );

    if( o->has_features )
    {
        for( sz_t i = 0; i < o->size; i++ ) BLM_TRY( xoite_a_expand_indef_typedef( o->data[ i ], indent, sink ) );
        BLM_TRY( xoite_group_s_expand_spect_declaration( o, indent + 2, sink ) );
    }

    for( sz_t i = 0; i < o->size; i++ ) BLM_TRY( xoite_a_expand_indef_declaration( o->data[ i ], indent, sink ) );

    bcore_sink_a_push_fa( sink, "\n" );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoite_group_s_expand_spect_definition( const xoite_group_s* o, sz_t indent, bcore_sink* sink )
{
    BLM_INIT();
    if( !o->expandable ) BLM_RETURNV( er_t, 0 );
    bcore_sink_a_push_fa( sink, "\n" );
    bcore_sink_a_push_fa( sink, "#rn{ }BCORE_DEFINE_SPECT( #<sc_t>, #<sc_t> )\n", indent, o->trait_name.sc, o->name.sc );
    bcore_sink_a_push_fa( sink, "#rn{ }\"{\"\n", indent );
    bcore_sink_a_push_fa( sink, "#rn{ }    \"bcore_spect_header_s header;\"\n", indent );
    for( sz_t i = 0; i < o->size; i++ ) BLM_TRY( xoite_a_expand_spect_definition( o->data[ i ], indent + 4, sink ) );
    bcore_sink_a_push_fa( sink, "#rn{ }\"}\";\n", indent );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoite_group_s_expand_definition( const xoite_group_s* o, sz_t indent, bcore_sink* sink )
{
    BLM_INIT();
    if( !o->expandable ) BLM_RETURNV( er_t, 0 );
    bcore_sink_a_push_fa( sink, "\n" );
    bcore_sink_a_push_fa( sink, "#rn{ }//#rn{-}\n", indent, sz_max( 0, 118 - indent ) );
    bcore_sink_a_push_fa( sink, "#rn{ }// group: #<sc_t>\n", indent, o->name.sc );
    for( sz_t i = 0; i < o->size; i++ )
    {
        // non-features
        if( *(aware_t*)o->data[ i ] != TYPEOF_xoite_feature_s )
        {
            BLM_TRY( xoite_a_expand_definition( o->data[ i ], indent, sink ) );
        }
    }

    if( o->has_features )
    {
        BLM_TRY( xoite_group_s_expand_spect_definition( o, indent, sink ) );
        for( sz_t i = 0; i < o->size; i++ )
        {
            // just-features
            if( *(aware_t*)o->data[ i ] == TYPEOF_xoite_feature_s )
            {
                BLM_TRY( xoite_a_expand_definition( o->data[ i ], indent, sink ) );
            }
        }
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoite_group_s_expand_init1( const xoite_group_s* o, sz_t indent, bcore_sink* sink )
{
    BLM_INIT();
    if( !o->expandable ) BLM_RETURNV( er_t, 0 );
    bcore_sink_a_push_fa( sink, "\n" );
    bcore_sink_a_push_fa( sink, "#rn{ }// group: #<sc_t>\n", indent, o->name.sc );
    for( sz_t i = 0; i < o->size; i++ ) BLM_TRY( xoite_a_expand_init1( o->data[ i ], indent, sink ) );

    if( o->has_features )
    {
        bcore_sink_a_push_fa( sink, "#rn{ }BCORE_REGISTER_SPECT( #<sc_t> );\n", indent, o->name.sc );
    }
    else
    {
        bcore_sink_a_push_fa( sink, "#rn{ }BCORE_REGISTER_TRAIT( #<sc_t>, #<sc_t> );\n", indent, o->name.sc, o->trait_name.sc );
    }

    if( o->retrievable )
    {
        for( sz_t i = 0; i < o->size; i++ )
        {
            if( *(aware_t*)o->data[ i ] == TYPEOF_xoite_stamp_s )
            {
                const xoite_stamp_s* stamp = ( xoite_stamp_s* )o->data[ i ];
                bcore_sink_a_push_fa( sink, "#rn{ }bcore_inst_s_get_typed( TYPEOF_#<sc_t> );\n", indent, stamp->name.sc );
            }
        }
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

