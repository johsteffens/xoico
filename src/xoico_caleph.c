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

#include "xoico_caleph.h"
#include "xoico_group.h"
#include "xoico_stamp.h"
#include "xoico_body.h"
#include "xoico_compiler.h"

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_caleph_s_trans_whitespace( xoico_caleph_s* o, bcore_source* source, st_s* buf /* can be NULL */ )
{
    bl_t exit_loop = false;
    while( !exit_loop && !bcore_source_a_eos( source ) )
    {
        char c = bcore_source_a_inspect_char( source );
        switch( c )
        {
            case ' ' :
            case '\t':
            case '\n':
            {
                if( buf ) st_s_push_char( buf, bcore_source_a_get_char( source ) );
            }
            break;

            case '/':
            {
                if( bcore_source_a_parse_bl_fa( source, "#?'//'" ) )
                {
                    if( buf ) st_s_push_sc( buf, "//" );
                    while( !bcore_source_a_eos( source ) )
                    {
                        char c = bcore_source_a_get_char( source );
                        if( buf ) st_s_push_char( buf, c );
                        if( c == '\n' ) break;
                    }
                }
                else if( bcore_source_a_parse_bl_fa( source, "#?'/*'" ) )
                {
                    if( buf ) st_s_push_sc( buf, "/*" );
                    while( !bcore_source_a_eos( source ) )
                    {
                        if( bcore_source_a_parse_bl_fa( source, "#?'*/'" ) )
                        {
                            if( buf ) st_s_push_sc( buf, "*/" );
                            break;
                        }
                        if( buf ) st_s_push_char( buf, bcore_source_a_get_char( source ) );
                    }
                }
                else
                {
                    exit_loop = true;
                }
            }
            break;

            default:
            {
                exit_loop = true;
            }
            break;
        }
    }
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

/// parses string
er_t xoico_caleph_s_trans_string_literal( xoico_caleph_s* o, bcore_source* source, st_s* buf )
{
    BLM_INIT();
    XOICO_BLM_SOURCE_PARSE_FA( source, "\"" );
    st_s_push_sc( buf, "\"" );

    while( !bcore_source_a_eos( source ) )
    {
        if( bcore_source_a_parse_bl_fa( source, "#?'\"'" ) )
        {
            st_s_push_sc( buf, "\"" );
            break;
        }

        if( bcore_source_a_parse_bl_fa( source, "#?'\\'" ) )
        {
            st_s_push_sc( buf, "\\" );
            char c = bcore_source_a_inspect_char( source );
            if( c == '"' || c == '\\' )
            {
                st_s_push_char( buf, bcore_source_a_get_char( source ) );
            }
        }
        else
        {
            st_s_push_char( buf, bcore_source_a_get_char( source ) );
        }
    }

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/// character literal
er_t xoico_caleph_s_trans_char_literal( xoico_caleph_s* o, bcore_source* source, st_s* buf )
{
    BLM_INIT();
    XOICO_BLM_SOURCE_PARSE_FA( source, "'" );
    st_s_push_sc( buf, "'" );

    while( !bcore_source_a_eos( source ) )
    {
        if( bcore_source_a_parse_bl_fa( source, "#?\"'\"" ) )
        {
            st_s_push_sc( buf, "'" );
            break;
        }

        if( bcore_source_a_parse_bl_fa( source, "#?'\\'" ) )
        {
            st_s_push_sc( buf, "\\" );
            char c = bcore_source_a_inspect_char( source );
            if( c == '\'' || c == '\\' )
            {
                st_s_push_char( buf, bcore_source_a_get_char( source ) );
            }
        }
        else
        {
            st_s_push_char( buf, bcore_source_a_get_char( source ) );
        }
    }

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_caleph_s_trans_block_inside_verbatim( xoico_caleph_s* o, bcore_source* source, st_s* buf )
{
    BLM_INIT();
    BLM_TRY( xoico_caleph_s_trans_whitespace( o, source, buf ) );
    while
    (
        !bcore_source_a_parse_bl_fa( source, "#=?'}'" ) &&
        !bcore_source_a_eos( source )
    )
    {
        char c = bcore_source_a_inspect_char( source );
        switch( c )
        {
            case '"':
            {
                BLM_TRY( xoico_caleph_s_trans_string_literal( o, source, buf ) );
            }
            break;

            case '\'':
            {
                BLM_TRY( xoico_caleph_s_trans_char_literal( o, source, buf ) );
            }
            break;

            case '{':
            {
                st_s_push_char( buf, bcore_source_a_get_char( source ) );
                BLM_TRY( xoico_caleph_s_trans_block_inside_verbatim( o, source, buf ) );
                XOICO_BLM_SOURCE_PARSE_FA( source, "}" );
                st_s_push_char( buf, '}' );
            }
            break;

            default:
            {
                st_s_push_char( buf, bcore_source_a_get_char( source ) );
            }
            break;
        }
        BLM_TRY( xoico_caleph_s_trans_whitespace( o, source, buf ) );
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_caleph_s_setup( xoico_caleph_s* o, const xoico_body_s* body, const xoico_signature_s* signature )
{
    BLM_INIT();
    sc_t sc_obj_type = ( signature->arg_o ) ? ( body->stamp ? body->stamp->st_name.sc : body->group->st_name.sc ) : NULL;

    const xoico_args_s* args = &signature->args;

    tp_t obj_type  = ( signature->arg_o == 0 ) ? 0 : xoico_caleph_s_entypeof( o, sc_obj_type );
    tp_t obj_name  = xoico_caleph_s_entypeof( o, "o" );

    o->args     = ( xoico_args_s* )args;
    o->group    = body->code->group;
    o->stamp    = body->code->stamp;
    o->compiler = xoico_group_s_get_compiler( body->group );
    o->obj_type = obj_type;

    if( obj_type )
    {
        bcore_hmap_name_s_set_sc( &o->hmap_name, xoico_compiler_s_nameof( o->compiler, obj_type ) );
        bcore_hmap_name_s_set_sc( &o->hmap_name, xoico_compiler_s_nameof( o->compiler, obj_name ) );
    }

    BFOR_EACH( i, args )
    {
        const xoico_arg_s* arg = &args->data[ i ];
        if( arg->typespec.type && arg->name )
        {
            bcore_hmap_name_s_set_sc( &o->hmap_name, xoico_compiler_s_nameof( o->compiler, arg->typespec.type ) );
            bcore_hmap_name_s_set_sc( &o->hmap_name, xoico_compiler_s_nameof( o->compiler, arg->name ) );
        }
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_caleph_s_translate( const xoico_caleph_s* o, const xoico_body_s* body, const xoico_signature_s* signature, bcore_sink* sink )
{
    BLM_INIT();

    xoico_caleph_s* aleph = BLM_CLONE( xoico_caleph_s, o );
    xoico_caleph_s_setup( aleph, body, signature );

    bcore_source* source = BLM_A_PUSH( bcore_source_point_s_clone_source( &body->code->source_point ) );

    st_s* buf = BLM_CREATE( st_s );

    sz_t indent = 0;
    XOICO_BLM_SOURCE_PARSE_FA( source, " {" );

    while( bcore_source_a_parse_bl_fa( source, "#?([0]==' '||[0]=='\t')" ) ) { bcore_source_a_get_char( source ); };
    if( bcore_source_a_parse_bl_fa( source, "#?'\n'" ) )
    {
        while( bcore_source_a_parse_bl_fa( source, "#?' '" ) ) indent++;
    }

    BLM_TRY( xoico_caleph_s_trans_block_inside_verbatim( aleph, source, buf ) );

    XOICO_BLM_SOURCE_PARSE_FA( source, " }" );

    if( indent > 0 ) st_s_replace_st_d_st_d( buf, st_s_create_fa( "\n#rn{ }", indent ), st_s_create_fa( "\n" ) );

    //remove trailing whitespaces
    for( sz_t i = buf->size - 1; i >= 0; i-- )
    {
        if( buf->data[ i ] != ' ' && buf->data[ i ] != '\t' && buf->data[ i ] != '\n' ) break;
        buf->data[ i ] = 0;
        buf->size = i;
    }

    if( o->include_source_reference && !body->code->single_line )
    {
        bcore_sink_a_push_fa( sink, "// " );
        bcore_source_point_s_source_reference_to_sink( &body->code->source_point, true, sink );
        bcore_sink_a_push_fa( sink, "\n" );
    }

    bcore_sink_a_push_sc( sink, buf->sc );

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

