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
#include "xoico_signature.h"
#include "xoico_compiler.h"
#include "xoico_caleph.h"

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_body_code_s_parse( xoico_body_code_s* o, bcore_source* source )
{
    BLM_INIT();
    if( !o->group ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "xoico_body_code_s: Code has no group assigned." );

    tp_t hash = bcore_tp_init();

    bcore_source_point_s_set( &o->source_point, source );
    XOICO_BLM_SOURCE_PARSE_FA( source, " {" );

    sz_t nest_count = 1;
    bl_t exit_loop = false;
    o->single_line = true;
    o->indentation = 0;

    while( bcore_source_a_parse_bl_fa( source, "#?' '" ) ); // skip leading spaces
    if( bcore_source_a_parse_bl_fa( source, "#?'\n'" ) )
    {
        o->single_line = false;
        while( bcore_source_a_parse_bl_fa( source, "#?' '" ) ) o->indentation++;
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
                hash = bcore_tp_fold_u0( hash, c );
                while( !bcore_source_a_eos( source ) && ((c = bcore_source_a_get_char( source )) != '"') )
                {
                    hash = bcore_tp_fold_u0( hash, c );
                    if( c == '\\' ) hash = bcore_tp_fold_u0( hash, bcore_source_a_get_u0( source ) );
                    if( c == '\n' ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Newline in string literal." );
                }
                c = 0;
            }
            break;

            case '\'': // char literal
            {
                hash = bcore_tp_fold_u0( hash, c );
                while( !bcore_source_a_eos( source ) && ((c = bcore_source_a_get_char( source )) != '\'') )
                {
                    hash = bcore_tp_fold_u0( hash, c );
                    if( c == '\\' ) hash = bcore_tp_fold_u0( hash, bcore_source_a_get_u0( source ) );
                    if( c == '\n' ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Newline in char literal." );
                }
                c = 0;
            }
            break;

            case '/': // comment
            {
                hash = bcore_tp_fold_u0( hash, c );
                if( bcore_source_a_inspect_char( source ) == '/' )
                {
                    while( !bcore_source_a_eos( source ) )
                    {
                        c = bcore_source_a_get_char( source );
                        hash = bcore_tp_fold_u0( hash, c );
                        if( c == '\n' )
                        {
                            for( sz_t i = 0; i < o->indentation; i++ ) { if( !bcore_source_a_parse_bl_fa( source, "#?' '" ) ) break; };
                            break;
                        }
                    }
                }
                else if( bcore_source_a_inspect_char( source ) == '*' )
                {
                    while( !bcore_source_a_eos( source ) )
                    {
                        if( bcore_source_a_parse_bl_fa( source, "#?'*/'" ) )
                        {
                            hash = bcore_tp_fold_sc( hash, "*/" );
                            break;
                        }
                        else
                        {
                            c = bcore_source_a_get_char( source );
                            hash = bcore_tp_fold_u0( hash, c );
                            if( c == '\n' )
                            {
                                for( sz_t i = 0; i < o->indentation; i++ ) { if( !bcore_source_a_parse_bl_fa( source, "#?' '" ) ) break; };
                            }
                        }
                    }
                }
                c = 0;
            }
            break;

            case '\n' :
            {
                o->single_line = false;
                for( sz_t i = 0; i < o->indentation; i++ ) { if( !bcore_source_a_parse_bl_fa( source, "#?' '" ) ) break; };
                break;
            }

            default: break;
        }
        hash = bcore_tp_fold_u0( hash, c );
    }

    o->hash_source = hash;
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

tp_t xoico_body_code_s_get_hash( const xoico_body_code_s* o )
{
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
    hash = bcore_tp_fold_tp( hash, o->hash_source );
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
    if( !o->group ) o->group = group;
    if( o->code )
    {
        if( !o->code->group ) o->code->group = group;
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

    if( o->code    ) hash = bcore_tp_fold_tp( hash, xoico_body_code_s_get_hash( o->code ) );
    hash = bcore_tp_fold_bl( hash, o->go_inline );
    return hash;
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

        if( o->stamp ) st_s_replace_sc_sc( name, "@", o->stamp->st_name.sc );

        tp_t tp_name = typeof( name->sc );

        // if name_buf refers to another body
        if( xoico_compiler_s_is_item( xoico_group_s_get_compiler( o->group ), tp_name ) )
        {
            vc_t item = xoico_compiler_s_get_const_item( xoico_group_s_get_compiler( o->group ), tp_name );
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

    st_s_copy_fa( &o->global_name, "#<sc_t>_#<sc_t>", o->group->st_name.sc, o->name.sc );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_body_s_finalize( xoico_body_s* o )
{
    /* nothing to do */
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_body_s_expand( const xoico_body_s* o, const xoico_signature_s* signature, sz_t indent, bcore_sink* sink )
{
    BLM_INIT();

    const st_s* final_code = NULL;
    st_s* st_out = BLM_CREATE( st_s );

    xoico_cengine* cengine = o->group->source->target->cengine;

    ASSERT( cengine );

    if( o->code )
    {
        if( !o->group ) XOICO_BLM_SOURCE_POINT_PARSE_ERR_FA( &o->source_point, "Body has no group assigned." );
        BLM_TRY( xoico_cengine_a_translate( cengine, o, signature, ( bcore_sink* )st_out ) )
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

