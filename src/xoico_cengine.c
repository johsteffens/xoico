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

#include "xoico_cengine.h"
#include "xoico_group.h"
#include "xoico_stamp.h"
#include "xoico_compiler.h"

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

static er_t take_block( xoico_cengine_s* o, sz_t level, bcore_source* source, bcore_sink* sink );

//----------------------------------------------------------------------------------------------------------------------

static void take_char( bcore_source* source, bcore_sink* sink )
{
    bcore_sink_a_push_char( sink, bcore_source_a_get_char( source ) );
}

//----------------------------------------------------------------------------------------------------------------------

static er_t take_line_comment( xoico_cengine_s* o, bcore_source* source, bcore_sink* sink )
{
    BLM_INIT();
    BLM_TRY( bcore_source_a_parse_em_fa( source, "//" ) );
    bcore_sink_a_push_fa( sink, "//" );
    while( !bcore_source_a_eos( source ) )
    {
        char c = bcore_source_a_get_char( source );
        bcore_sink_a_push_char( sink, c );
        if( c == '\n' ) break;
    }

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

static er_t take_block_comment( xoico_cengine_s* o, bcore_source* source, bcore_sink* sink )
{
    BLM_INIT();
    BLM_TRY( bcore_source_a_parse_em_fa( source, "/*" ) );
    bcore_sink_a_push_fa( sink, "/*" );
    bl_t closed = false;
    while( !bcore_source_a_eos( source ) )
    {
        if( bcore_source_a_parse_bl_fa( source, "#?'*/'" ) )
        {
            bcore_sink_a_push_fa( sink, "*/" );
            closed = true;
            break;
        }
        take_char( source, sink );
    }

    if( !closed )
    {
        BLM_RETURNV( er_t, bcore_source_a_parse_err_to_em_fa( source, TYPEOF_general_error, "Unterminated block-comment." ) );
    }

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

static er_t take_whitespace( xoico_cengine_s* o, bcore_source* source, bcore_sink* sink )
{
    BLM_INIT();
    while( !bcore_source_a_eos( source ) )
    {
        char c = bcore_source_a_inspect_char( source );

        if( c == ' ' || c == '\t' || c == '\n' ) // regular whitespace
        {
            take_char( source, sink );
        }
        else if( c == '/' && bcore_source_a_parse_bl_fa( source, "#=?'//'" ) )
        {
            BLM_TRY( take_line_comment( o, source, sink ) );
        }
        else if( c == '/' && bcore_source_a_parse_bl_fa( source, "#=?'/*'" ) )
        {
            BLM_TRY( take_block_comment( o, source, sink ) );
        }
        else
        {
            break;
        }
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

static er_t take_string( xoico_cengine_s* o, bcore_source* source, bcore_sink* sink )
{
    BLM_INIT();
    BLM_TRY( bcore_source_a_parse_em_fa( source, "\"" ) );
    bcore_sink_a_push_char( sink, '"' );
    bl_t closed = false;
    while( !bcore_source_a_eos( source ) )
    {
        char c = bcore_source_a_get_char( source );
        bcore_sink_a_push_char( sink, c );
        if( c == '\\' && bcore_source_a_inspect_char( source ) == '"' )
        {
            take_char( source, sink );
        }
        if( c == '"' )
        {
            closed = true;
            break;
        }
    }

    if( !closed )
    {
        BLM_RETURNV( er_t, bcore_source_a_parse_err_to_em_fa( source, TYPEOF_general_error, "Unterminated string." ) );
    }

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

static er_t take_preprocessor( xoico_cengine_s* o, bcore_source* source, bcore_sink* sink )
{
    BLM_INIT();
    BLM_TRY( bcore_source_a_parse_em_fa( source, "##" ) );
    bcore_sink_a_push_fa( sink, "##" );
    while( !bcore_source_a_eos( source ) )
    {
        char c = bcore_source_a_get_char( source );
        bcore_sink_a_push_char( sink, c );
        if( c == '\\' && bcore_source_a_inspect_char( source ) == '\n' ) take_char( source, sink );
        if( c == '\n' ) break;
    }

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

static er_t take_statement_name( xoico_cengine_s* o, sz_t level, bcore_source* source, bcore_sink* sink )
{
    BLM_INIT();
    st_s* st_name = BLM_CREATE( st_s );
    BLM_TRY( bcore_source_a_parse_em_fa( source, "#name", st_name ) );

    while
    (
        st_s_equal_sc( st_name, "const"    ) ||
        st_s_equal_sc( st_name, "static"   ) ||
        st_s_equal_sc( st_name, "volatile" )
    )
    {
        bcore_sink_a_push_sc( sink, st_name->sc );
        BLM_TRY( take_whitespace( o, source, sink ) );
        BLM_TRY( bcore_source_a_parse_em_fa( source, "#name", st_name ) );
    }

    if( st_name->size == 0 ) BLM_RETURNV( er_t, 0 );

    if( xoico_compiler_s_is_type( o->compiler, btypeof( st_name->sc ) ) )
    {
        bcore_sink_a_push_sc( sink, st_name->sc );
        BLM_TRY( take_whitespace( o, source, sink ) );

        st_s* st_type = BLM_CREATE( st_s );
        st_s_copy( st_type, st_name );
        if( bcore_source_a_parse_bl_fa( source, "#?'*'" ) )
        {
            bcore_sink_a_push_char( sink, '*' );
            BLM_TRY( take_whitespace( o, source, sink ) );
            BLM_TRY( bcore_source_a_parse_em_fa( source, "#name", st_name ) );
            bcore_sink_a_push_sc( sink, st_name->sc );
            if( st_name->size > 0 ) // definition: pointer to a known type
            {
                xoico_cengine_tn_stack_s_push_sc( &o->stack, st_type->sc, st_name->sc, level );
            }
        }
    }
    else
    {
        bl_t no_conversion = true;

        st_s* st_buf = BLM_CREATE( st_s );
        bcore_sink* sink_buf = ( bcore_sink* )st_buf;
        bcore_sink_a_push_sc( sink_buf, st_name->sc );
        BLM_TRY( take_whitespace( o, source, sink_buf ) );

        if( bcore_source_a_parse_bl_fa( source, "#?'->'" ) )
        {
            bcore_sink_a_push_sc( sink_buf, "->" );
            BLM_TRY( take_whitespace( o, source, sink_buf ) );
            st_s* st_fname = BLM_CREATE( st_s );
            BLM_TRY( bcore_source_a_parse_em_fa( source, "#name", st_fname ) );
            bcore_sink_a_push_sc( sink_buf, st_fname->sc );
            BLM_TRY( take_whitespace( o, source, sink_buf ) );
            if( st_fname->size > 0 )
            {
                if( bcore_source_a_parse_bl_fa( source, "#?'('" ) ) // function call
                {
                    bcore_sink_a_push_sc( sink_buf, "(" );
                    sc_t  sc_type = xoico_cengine_tn_stack_s_get_type_sc( &o->stack, st_name->sc );
                    st_s* st_type = BLM_A_PUSH( st_s_create_sc( sc_type ? sc_type : "" ) );
                    if( st_type->size > 0 ) // registered type -> convert function call
                    {
                        /// if type ends in '_s' or '_t' assume a stamp(-like) object ...
                        if
                        (
                               st_type->size >= 2
                            && st_type->sc[ st_type->size - 2 ] == '_'
                            && ( st_type->sc[ st_type->size - 1 ] == 's' || st_type->sc[ st_type->size - 1 ] == 't' )
                        )
                        {
                            bcore_sink_a_push_fa( sink, "#<sc_t>_#<sc_t>( #<sc_t>", st_type->sc, st_fname->sc, st_name->sc );
                        }
                        else /// ... otherwise assume an aware virtual type
                        {
                            bcore_sink_a_push_fa( sink, "#<sc_t>_a_#<sc_t>( #<sc_t>", st_type->sc, st_fname->sc, st_name->sc );
                        }

                        if( bcore_source_a_parse_bl_fa( source, "#?')'" ) ) // no arguments
                        {
                            bcore_sink_a_push_sc( sink, " )" );
                        }
                        else
                        {
                            bcore_sink_a_push_sc( sink, "," ); // arguments follow
                        }
                        BLM_TRY( take_whitespace( o, source, sink ) );

                        no_conversion = false;
                    }
                }
            }
        }

        if( no_conversion ) // no conversion: restore buffer
        {
            bcore_sink_a_push_sc( sink, st_buf->sc );
        }
    }

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

static er_t take_bracket( xoico_cengine_s* o, sz_t level, bcore_source* source, bcore_sink* sink )
{
    BLM_INIT();

    BLM_TRY( take_whitespace( o, source, sink ) );
    BLM_TRY( bcore_source_a_parse_em_fa( source, "(" ) );
    bcore_sink_a_push_char( sink, '(' );

    while( !bcore_source_a_eos( source ) )
    {
        BLM_TRY( take_whitespace( o, source, sink ) );
        char c = bcore_source_a_inspect_char( source );

        if( c == ')' ) // end of bracket
        {
            take_char( source, sink );
            break;
        }
        else if( c == '"' )
        {
            BLM_TRY( take_string( o, source, sink ) );
        }
        else if( c == '(' )
        {
            BLM_TRY( take_bracket( o, level, source, sink ) );
        }
        else if( ( c >= 'A' && c <= 'Z' ) || ( c >= 'a' && c <= 'z' ) || c == '_' )
        {
            BLM_TRY( take_statement_name( o, level, source, sink ) );
        }
        else // simply consume
        {
            take_char( source, sink );
        }
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/** A statement in cengine differs semantically from c-statement
 *  It is used here for code-segmentation.
 */
static er_t take_statement( xoico_cengine_s* o, sz_t level, bcore_source* source, bcore_sink* sink )
{
    BLM_INIT();
    while( !bcore_source_a_eos( source ) )
    {
        BLM_TRY( take_whitespace( o, source, sink ) );
        char c = bcore_source_a_inspect_char( source );

        if( c == '{' ) // end of statement
        {
            break;
        }
        else if( c == ';' ) // end of statement
        {
            take_char( source, sink );
            break;
        }
        else if( c == '"' )
        {
            BLM_TRY( take_string( o, source, sink ) );
        }
        else if( c == '(' )
        {
            BLM_TRY( take_bracket( o, level, source, sink ) );
        }
        else if( ( c >= 'A' && c <= 'Z' ) || ( c >= 'a' && c <= 'z' ) || c == '_' )
        {
            BLM_TRY( take_statement_name( o, level, source, sink ) );
        }
        else
        {
            take_char( source, sink );
        }
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

static er_t take_block_body( xoico_cengine_s* o, sz_t level, bcore_source* source, bcore_sink* sink )
{
    BLM_INIT();
    while( !bcore_source_a_eos( source ) )
    {
        BLM_TRY( take_whitespace( o, source, sink ) );

        char c = bcore_source_a_inspect_char( source );
        if( c == '{' )
        {
            BLM_TRY( take_block( o, level + 1, source, sink ) );
        }
        else if( c == '}' )
        {
            if( level == 0 )
            {
                BLM_RETURNV
                (
                    er_t,
                    bcore_source_a_parse_err_to_em_fa
                    (
                        source,
                        TYPEOF_general_error,
                        "Unexpected closing brace '}' at root level."
                    )
                );
            }
            xoico_cengine_tn_stack_s_pop( &o->stack, level );
            break;
        }
        else if( c == '#' )
        {
            BLM_TRY( take_preprocessor( o, source, sink ) );
        }
        else if( ( c >= 'A' && c <= 'Z' ) || ( c >= 'a' && c <= 'z' ) || c == '_' )
        {
            BLM_TRY( take_statement( o, level, source, sink ) );
        }
        else if( c == '*' || c == ';' )
        {
            take_char( source, sink );
        }
        else
        {
            if( !bcore_source_a_eos( source ) )
            {
                BLM_RETURNV( er_t, bcore_source_a_parse_err_to_em_fa( source, TYPEOF_general_error, "block_body: invalid character '#<char>'.", c ) );
            }
        }
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

static er_t take_block( xoico_cengine_s* o, sz_t level, bcore_source* source, bcore_sink* sink )
{
    BLM_INIT();
    BLM_TRY( take_whitespace( o, source, sink ) );
    BLM_TRY( bcore_source_a_parse_em_fa( source, "{" ) );
    bcore_sink_a_push_char( sink, '{' );
    BLM_TRY( take_block_body( o, level, source, sink ) );
    BLM_TRY( take_whitespace( o, source, sink ) );
    BLM_TRY( bcore_source_a_parse_em_fa( source, "}" ) );
    bcore_sink_a_push_char( sink, '}' );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cengine_s_take_block_body( xoico_cengine_s* o, bcore_source* source, bcore_sink* sink )
{
    xoico_cengine_tn_stack_s_init_from_args( &o->stack, o->obj_type, "o", o->args );
    return take_block_body( o, 0, source, sink );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cengine_s_take_block( xoico_cengine_s* o, bcore_source* source, bcore_sink* sink )
{
    xoico_cengine_tn_stack_s_init_from_args( &o->stack, o->obj_type, "o", o->args );
    return take_block( o, 0, source, sink );
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

