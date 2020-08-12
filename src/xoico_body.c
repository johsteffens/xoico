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

#include "xoico_body.h"
#include "xoico_group.h"
#include "xoico_stamp.h"
#include "xoico_compiler.h"
#include "xoico_cengine.h"

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

sc_t xoico_body_s_get_global_name_sc( const xoico_body_s* o )
{
    return o->global_name.sc;
}

//----------------------------------------------------------------------------------------------------------------------

tp_t xoico_body_s_get_hash( const xoico_body_s* o )
{
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
    hash = bcore_tp_fold_sc( hash, o->name.sc );
    hash = bcore_tp_fold_sc( hash, o->code.sc );
    hash = bcore_tp_fold_u0( hash, o->go_inline ? 1 : 0 );

    if( o->apply_cengine )
    {
        hash = bcore_tp_fold_u0( hash, 1 );
    }
    return hash;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_body_s_parse_expression( xoico_body_s* o, xoico_stamp_s* stamp, bcore_source* source );

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_body_s_append( xoico_body_s* o, sz_t indent, const xoico_body_s* body )
{
    BLM_INIT();
    if( body->go_inline )
    {
        st_s_push_fa( &o->code, "#<st_s*>", &body->code );
    }
    else
    {
        st_s* body_code = BLM_A_PUSH( st_s_clone( &body->code ) );
        st_s* newline = BLM_A_PUSH( st_s_create_fa( "\n#rn{ }", indent ) );
        st_s_replace_sc_sc( body_code, "\n", newline->sc );
        st_s_push_fa( &o->code, "#<st_s*>", body_code );
        o->go_inline = false;
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_body_s_parse_code( xoico_body_s* o, xoico_stamp_s* stamp, bcore_source* source )
{
    BLM_INIT();

    st_s_clear( &o->code );

    XOICO_BLM_SOURCE_PARSE_FA( source, " {" );

    sz_t nest_count = 1;
    bl_t exit_loop = false;
    o->go_inline = true;
    sz_t undo_indentation = 0;

    while( bcore_source_a_parse_bl_fa( source, "#?' '" ) ); // skip leading spaces
    if( bcore_source_a_parse_bl_fa( source, "#?'\n'" ) )
    {
        o->go_inline = false;
        while( bcore_source_a_parse_bl_fa( source, "#?' '" ) ) undo_indentation++;
    }

    if( bcore_source_a_parse_bl_fa( source, "#?'$apply_cengine'" ) )
    {
        XOICO_BLM_SOURCE_PARSE_FA( source, " = " );
        if( bcore_source_a_parse_bl_fa( source, "#?'true'" ) )
        {
            o->apply_cengine = true;
        }
        else if( bcore_source_a_parse_bl_fa( source, "#?'false'" ) )
        {
            o->apply_cengine = false;
        }
        else
        {
            XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Syntax error." );
        }
        XOICO_BLM_SOURCE_PARSE_FA( source, " ;" );
    }

    while( !bcore_source_a_eos( source ) && !exit_loop )
    {
        u0_t c = bcore_source_a_get_u0( source );
        switch( c )
        {
            case '{':
            {
                nest_count++;
            }
            break;

            case '}':
            {
                nest_count--;
                if( !nest_count )
                {
                    c = 0;
                    exit_loop = true;
                }
            }
            break;

            case '"': // string literal
            {
                st_s_push_char( &o->code, c );
                bl_t esc = false;
                while( !bcore_source_a_eos( source ) )
                {
                    u0_t c = bcore_source_a_get_u0( source );
                    st_s_push_char( &o->code, c );
                    if( !esc && c == '"' ) break;
                    esc = ( c == '\\' );
                    if( c == '\n' ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Newline in string literal." );
                }
                c = 0;
            }
            break;

            case '\\': // escape
            {
                if( bcore_source_a_parse_bl_fa( source, "#?w'body'" ) ) // embeds another body
                {
                    BLM_INIT();
                    c = 0;
                    sz_t indent = 0;
                    for( sz_t i = o->code.size - 1; i >= 0; i-- )
                    {
                        if( o->code.sc[ i ] == ' ') indent++; else break;
                    }
                    xoico_body_s* body = BLM_CREATE( xoico_body_s );
                    body->group = o->group;
                    BLM_TRY( xoico_body_s_parse_expression( body, stamp, source ) );
                    XOICO_BLM_SOURCE_PARSE_FA( source, " ;" ); // embedded body expression must close with a semicolon
                    BLM_TRY( xoico_body_s_append( o, indent, body ) );
                    BLM_DOWN();
                }
                else
                {
                    c = bcore_source_a_get_u0( source );
                    if( c != ':' ) st_s_push_char( &o->code, '\\' );
                }
            }
            break;

            case '\n' :
            {
                o->go_inline = false;
                for( sz_t i = 0; i < undo_indentation; i++ ) { if( !bcore_source_a_parse_bl_fa( source, "#?' '" ) ) break; };
                break;
            }

            // namespace: if a name, '*' or another ':' follows immediately,
            // ':' is interpreted as namespace-prepend
            // ordinary c-code using ':' should append a whitespace or prepend escape '\:'
            case ':':
            {
                if( bcore_source_a_parse_bl_fa( source, "#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||[0]==':'||[0]=='*'||[0]=='@'||[0]=='$')" ) )
                {
                    BLM_INIT();
                    st_s* name = BLM_CREATE( st_s );
                    BLM_TRY( xoico_group_s_parse_name_recursive( o->group, name, source ) );
                    st_s_push_sc( &o->code, name->sc );
                    c = 0;
                    BLM_DOWN();
                }
            }
            break;

            default: break;
        }
        if( c ) st_s_push_char( &o->code, c );
    }

    // remove trailing spaces and newline
    for( sz_t i = o->code.size - 1; i >= 0; i-- )
    {
        char c = o->code.data[ i ];
        if( c == ' ' || c == '\n' )
        {
            st_s_pop_char( &o->code );
        }
        else
        {
            break;
        }
    }

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_body_s_parse_expression( xoico_body_s* o, xoico_stamp_s* stamp, bcore_source* source )
{
    BLM_INIT();
    if( bcore_source_a_parse_bl_fa( source, " #=?'{'" ) )
    {
        BLM_TRY( xoico_body_s_parse_code( o, stamp, source ) );
    }
    else
    {
        st_s* name = BLM_CREATE( st_s );
        BLM_TRY( xoico_group_s_parse_name( o->group, name, source ) );
        if( name->size == 0 ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Body name expected." );

        if( stamp ) BLM_TRY( xoico_stamp_s_resolve_chars( stamp, name ) );

        tp_t tp_name = typeof( name->sc );
        // if name_buf refers to another body
        if( xoico_compiler_s_item_exists( xoico_group_s_get_compiler( o->group ), tp_name ) )
        {
            vc_t item = xoico_compiler_s_item_get( xoico_group_s_get_compiler( o->group ), tp_name );
            if( *(aware_t*)item == TYPEOF_xoico_body_s )
            {
                const xoico_body_s* body = item;
                st_s_copy( &o->code, &body->code );
                o->go_inline = body->go_inline;
            }
        }
        else
        {
            XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Cannot resolve body name '#<sc_t>'\n", name->sc );
        }
    }

    if( bcore_source_a_parse_bl_fa( source, " #?':'" ) ) // concatenating another body
    {
        if( bcore_source_a_parse_bl_fa( source, "#?(([0]!=' ')&&([0]!='\t')&&([0]!='\n'))" ) )
        {
            XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Whitespace after ':' expected." );
        }
        xoico_body_s* body = BLM_CREATE( xoico_body_s );
        body->group = o->group;
        BLM_TRY( xoico_body_s_parse_expression( body, stamp, source ) );
        st_s_push_char( &o->code, '\n' );
        o->go_inline = false;
        BLM_TRY( xoico_body_s_append( o, 0, body ) );
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/// stamp should be NULL when body is not parsed inside a stamp
er_t xoico_body_s_parse( xoico_body_s* o, xoico_stamp_s* stamp, bcore_source* source )
{
    BLM_INIT();

    st_s* string = BLM_CREATE( st_s );

    bcore_source_point_s_set( &o->source_point, source );

    if( !bcore_source_a_parse_bl_fa( source, " #=?'='" ) )
    {
        XOICO_BLM_SOURCE_PARSE_FA( source, " #name", string );
        if( string->size == 0 ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Body name expected." );
        st_s_push_fa( &o->name, "#<sc_t>", string->sc );
    }

    XOICO_BLM_SOURCE_PARSE_FA( source, " =" );

    BLM_TRY( xoico_body_s_parse_expression( o, stamp, source ) );

    st_s_copy_fa( &o->global_name, "#<sc_t>_#<sc_t>", o->group->name.sc, o->name.sc );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_body_s_expand( const xoico_body_s* o, const xoico_args_s* args, sz_t indent, bcore_sink* sink )
{
    if( o->apply_cengine )
    {
        BLM_INIT();
        bcore_source* source = BLM_A_PUSH( bcore_source_string_s_create_sc( o->code.sc ) );
        st_s* st_out = BLM_CREATE( st_s );
        xoico_cengine_s* engine = BLM_CREATE( xoico_cengine_s );
        engine->args     = bcore_fork( ( xoico_args_s* )args );
        engine->compiler = bcore_fork( xoico_group_s_get_compiler( o->group ) );

        if( xoico_cengine_s_take_block_body( engine, source, ( bcore_sink* )st_out ) )
        {
            er_t id = 0;
            st_s* msg = BLM_CREATE( st_s );
            bcore_error_pop_st( &id, msg );
            XOICO_BLM_SOURCE_POINT_PARSE_ERR_FA
            (
                &o->source_point,
                "\ntext-offset#<sc_t>",
                msg->sc
            );
        }

        bcore_msg_fa( "\n#<sc_t>\n", st_out->sc );

        BLM_DOWN();
    }

    if( o->go_inline )
    {
        bcore_sink_a_push_fa( sink, "{#<sc_t>}", o->code.sc );
    }
    else
    {
        bcore_sink_a_push_fa( sink, "{\n#rn{ }", indent + 4 );
        for( sz_t i = 0; i < o->code.size; i++ )
        {
            char c = o->code.sc[ i ];
            bcore_sink_a_push_char( sink, c );
            if( c == '\n' ) bcore_sink_a_push_fa( sink, "#rn{ }", indent + 4 );
        }
        bcore_sink_a_push_fa( sink, "\n#rn{ }}", indent );
    }
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

