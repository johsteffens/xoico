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

er_t xoico_body_code_s_parse( xoico_body_code_s* o, bcore_source* source )
{
    BLM_INIT();
    if( !o->group ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "xoico_body_code_s: Code has no group assigned." );

    st_s_clear( &o->st );

    XOICO_BLM_SOURCE_PARSE_FA( source, " {" );

    sz_t nest_count = 1;
    bl_t exit_loop = false;
    o->single_line = true;
    sz_t undo_indentation = 0;

    while( bcore_source_a_parse_bl_fa( source, "#?' '" ) ); // skip leading spaces
    if( bcore_source_a_parse_bl_fa( source, "#?'\n'" ) )
    {
        o->single_line = false;
        while( bcore_source_a_parse_bl_fa( source, "#?' '" ) ) undo_indentation++;
    }

    bcore_source_point_s_set( &o->source_point, source );

    // TODO: do not replace code in comments

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
                st_s_push_char( &o->st, c );
                bl_t esc = false;
                while( !bcore_source_a_eos( source ) )
                {
                    u0_t c = bcore_source_a_get_u0( source );
                    st_s_push_char( &o->st, c );
                    if( !esc && c == '"' ) break;
                    esc = ( c == '\\' );
                    if( c == '\n' ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Newline in string literal." );
                }
                c = 0;
            }
            break;

            case '\\': // escape
            {
                c = bcore_source_a_get_u0( source );
                if( c != ':' ) st_s_push_char( &o->st, '\\' );
            }
            break;

            case '\n' :
            {
                o->single_line = false;
                for( sz_t i = 0; i < undo_indentation; i++ ) { if( !bcore_source_a_parse_bl_fa( source, "#?' '" ) ) break; };
                break;
            }

            // namespace: if a name, '*' or another ':' follows immediately,
            // ':' is interpreted as namespace-prepend
            // ordinary c-code using ':' should append a whitespace or prepend escape '\:'
            // Note: ':' must be resolved while parsing, otherwise the wrong group might be assigned to bodies which are to be use elsewhere.
            case ':':
            {
                if( bcore_source_a_parse_bl_fa( source, "#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||[0]==':'||[0]=='*'||[0]=='@')" ) )
                {
                    BLM_INIT();
                    st_s* name = BLM_CREATE( st_s );
                    BLM_TRY( xoico_group_s_parse_name_recursive( o->group, name, source ) );
                    st_s_push_sc( &o->st, name->sc );
                    c = 0;
                    BLM_DOWN();
                }
            }
            break;

            default: break;
        }
        if( c ) st_s_push_char( &o->st, c );
    }

    // remove trailing spaces and newline
    for( sz_t i = o->st.size - 1; i >= 0; i-- )
    {
        char c = o->st.data[ i ];
        if( c == ' ' || c == '\n' )
        {
            st_s_pop_char( &o->st );
        }
        else
        {
            break;
        }
    }

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

tp_t xoico_body_code_s_get_hash( const xoico_body_code_s* o )
{
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
    hash = bcore_tp_fold_sc( hash, o->st.sc );
    return hash;
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

sc_t xoico_body_s_get_global_name_sc( const xoico_body_s* o )
{
    return o->global_name.sc;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_body_s_set_group( xoico_body_s* o, xoico_group_s* group )
{
    o->group = group;
    if( o->code ) o->code->group = group;
    if( xoico_group_s_get_target( o->group )->xflags.apply_cengine )
    {
        o->apply_cengine = *xoico_group_s_get_target( o->group )->xflags.apply_cengine;
    }
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_body_s_set_stamp( xoico_body_s* o, xoico_stamp_s* stamp )
{
    o->stamp = stamp;
    if( o->code ) o->code->stamp = stamp;
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

tp_t xoico_body_s_get_hash( const xoico_body_s* o )
{
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
    hash = bcore_tp_fold_sc( hash, o->name.sc );

    if( o->code )
    {
        hash = bcore_tp_fold_tp( hash, xoico_body_code_s_get_hash( o->code ) );
    }
    hash = bcore_tp_fold_bl( hash, o->go_inline );
    hash = bcore_tp_fold_bl( hash, o->apply_cengine );
    return hash;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_body_s_parse_expression( xoico_body_s* o, bcore_source* source );

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_body_s_append( xoico_body_s* o, sz_t indent, const xoico_body_s* body )
{
    BLM_INIT();
    if( !body->code ) BLM_RETURNV( er_t, 0 );

    if( !o->code ) o->code = xoico_body_code_s_create();

    if( body->go_inline )
    {
        st_s_push_fa( &o->code->st, "#<st_s*>", &body->code->st );
    }
    else
    {
        st_s* body_code = BLM_A_PUSH( st_s_clone( &body->code->st ) );
        st_s* newline = BLM_A_PUSH( st_s_create_fa( "\n#rn{ }", indent ) );
        st_s_replace_sc_sc( body_code, "\n", newline->sc );
        st_s_push_fa( &o->code->st, "#<st_s*>", body_code );
        o->go_inline = false;
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_body_s_parse_expression( xoico_body_s* o, bcore_source* source )
{
    BLM_INIT();

    if( bcore_source_a_parse_bl_fa( source, " #=?'{'" ) )
    {
        xoico_body_code_s_attach( &o->code, xoico_body_code_s_create() );
        o->code->group = o->group;
        o->code->stamp = o->stamp;
        BLM_TRY( xoico_body_code_s_parse( o->code, source ) );
        o->go_inline = o->code->single_line;
    }
    else
    {
        st_s* name = BLM_CREATE( st_s );
        BLM_TRY( xoico_group_s_parse_name( o->group, name, source ) );
        if( name->size == 0 ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Body name expected." );

        if( o->stamp ) BLM_TRY( xoico_stamp_s_resolve_chars( o->stamp, name ) );

        tp_t tp_name = typeof( name->sc );
        // if name_buf refers to another body
        if( xoico_compiler_s_item_exists( xoico_group_s_get_compiler( o->group ), tp_name ) )
        {
            vc_t item = xoico_compiler_s_item_get( xoico_group_s_get_compiler( o->group ), tp_name );
            if( *(aware_t*)item == TYPEOF_xoico_body_s )
            {
                const xoico_body_s* body = item;

                xoico_body_code_s_attach( &o->code, xoico_body_code_s_clone( body->code ) );
                if( o->code )
                {
                    o->code->group = body->code->group;
                    o->code->stamp = body->code->stamp;
                }
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
        BLM_TRY( xoico_body_s_set_group( body, o->group ) );
        BLM_TRY( xoico_body_s_set_stamp( body, o->stamp ) );
        bcore_source_point_s_set( &body->source_point, source );
        BLM_TRY( xoico_body_s_parse_expression( body, source ) );
        if( o->code ) st_s_push_char( &o->code->st, '\n' );
        o->go_inline = false;
        BLM_TRY( xoico_body_s_append( o, 0, body ) );
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/// stamp should be NULL when body is not parsed inside a stamp
er_t xoico_body_s_parse( xoico_body_s* o, bcore_source* source )
{
    BLM_INIT();
    if( !o->group ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Body has no group assigned." );

    st_s* string = BLM_CREATE( st_s );

    bcore_source_point_s_set( &o->source_point, source );

    if( !bcore_source_a_parse_bl_fa( source, " #=?'='" ) )
    {
        XOICO_BLM_SOURCE_PARSE_FA( source, " #name", string );
        if( string->size == 0 ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Body name expected." );
        st_s_push_fa( &o->name, "#<sc_t>", string->sc );
    }

    XOICO_BLM_SOURCE_PARSE_FA( source, " =" );

    BLM_TRY( xoico_body_s_parse_expression( o, source ) );

    st_s_copy_fa( &o->global_name, "#<sc_t>_#<sc_t>", o->group->name.sc, o->name.sc );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/// stamp should be NULL when body is not parsed inside a stamp
er_t xoico_body_s_finalize( xoico_body_s* o )
{
    BLM_INIT();
    BLM_TRY( xoico_stamp_s_resolve_chars( o->stamp, &o->code->st ) );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_body_s_expand( const xoico_body_s* o, sc_t ret_type, sc_t obj_type, const xoico_args_s* args, sz_t indent, bcore_sink* sink )
{
    BLM_INIT();
    const st_s* final_code = o->code ? &o->code->st : BLM_CREATE( st_s );
    st_s* st_out = BLM_CREATE( st_s );
    if( o->apply_cengine && o->code )
    {
        if( !o->group ) XOICO_BLM_SOURCE_POINT_PARSE_ERR_FA( &o->source_point, "Body has no group assigned." );
        bcore_source* source = BLM_A_PUSH( bcore_source_string_s_create_sc( o->code->st.sc ) );
        xoico_cengine_s* engine = BLM_CREATE( xoico_cengine_s );
        engine->ret_type = ret_type;
        engine->obj_type = obj_type;
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
                "\ncengine-error: #<sc_t>\n"
                "\n",
                msg->sc
            );
        }

//        if( !st_s_equal_st( st_out, &o->code ) )
//        {
//            bcore_msg_fa( "#<sc_t>\n", st_out->sc );
//        }

        final_code = st_out;
    }

    if( o->go_inline )
    {
        bcore_sink_a_push_fa( sink, "{#<sc_t>}", final_code->sc );
    }
    else
    {
        bcore_sink_a_push_fa( sink, "{\n#rn{ }", indent + 4 );
        for( sz_t i = 0; i < final_code->size; i++ )
        {
            char c = final_code->sc[ i ];
            bcore_sink_a_push_char( sink, c );
            if( c == '\n' ) bcore_sink_a_push_fa( sink, "#rn{ }", indent + 4 );
        }
        bcore_sink_a_push_fa( sink, "\n#rn{ }}", indent );
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

