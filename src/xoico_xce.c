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

#include "xoico_xce.h"
#include "xoico_group.h"
#include "xoico_stamp.h"
#include "xoico_compiler.h"
#include "xoico_signature.h"

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

/** parses name and enrolls it and returns hash */
tp_t xoico_xce_s_trans_name( xoico_xce_s* o, bcore_source* source, st_s* buf )
{
    BLM_INIT();
    st_s* st_name = BLM_CREATE( st_s );
    bcore_source_a_parse_fa( source, "#name", st_name );
    if( st_name->size == 0 ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Name expected." );
    st_s_push_st( buf, st_name );
    tp_t tp_name = xoico_xce_s_entypeof( o, st_name->sc );
    BLM_RETURNV( tp_t, tp_name );
}

//----------------------------------------------------------------------------------------------------------------------

/** parses number: (all integer, hex and float encodings)*/
tp_t xoico_xce_s_trans_number_literal( xoico_xce_s* o, bcore_source* source, st_s* buf )
{
    BLM_INIT();
    bl_t hex = false;
    if( bcore_source_a_parse_bl_fa( source, "#?'0x'" ) )
    {
        st_s_push_sc( buf, "0x" );
        hex = true;;
    }
    else if( bcore_source_a_parse_bl_fa( source, "#?'0X'" ) )
    {
        st_s_push_sc( buf, "0X" );
        hex = true;;
        while( bcore_source_a_parse_bl_fa( source, "#?(([0]>='0'&&[0]<='9')||([0]>='a'&&[0]<='f')||([0]>='A'&&[0]<='F'))" ) )
        {
            st_s_push_char( buf, bcore_source_a_get_char( source ) );
        }
    }

    if( hex )
    {
        while( bcore_source_a_parse_bl_fa( source, "#?(([0]>='0'&&[0]<='9')||([0]>='a'&&[0]<='f')||([0]>='A'&&[0]<='F'))" ) )
        {
            st_s_push_char( buf, bcore_source_a_get_char( source ) );
        }
    }
    else // decimal
    {
        while( bcore_source_a_parse_bl_fa( source, "#?([0]>='0'&&[0]<='9')" ) )
        {
            st_s_push_char( buf, bcore_source_a_get_char( source ) );
        }
    }

    bl_t fraction = false;

    if( bcore_source_a_parse_bl_fa( source, "#?([0]=='.')" ) )
    {
        st_s_push_char( buf, bcore_source_a_get_char( source ) );
        fraction = true;
    }

    if( fraction )
    {
        while( bcore_source_a_parse_bl_fa( source, "#?([0]>='0'&&[0]<='9')" ) )
        {
            st_s_push_char( buf, bcore_source_a_get_char( source ) );
        }
    }

    bl_t exponent = false;

    if( bcore_source_a_parse_bl_fa( source, "#?([0]=='e'&&[0]=='E')" ) )
    {
        st_s_push_char( buf, bcore_source_a_get_char( source ) );
        exponent = true;
    }

    if( exponent )
    {
        if( bcore_source_a_parse_bl_fa( source, "#?([0]=='+'||[0]=='-')" ) )
        {
            st_s_push_char( buf, bcore_source_a_get_char( source ) );
        }

        while( bcore_source_a_parse_bl_fa( source, "#?([0]>='0'&&[0]<='9')" ) )
        {
            st_s_push_char( buf, bcore_source_a_get_char( source ) );
        }
    }

    // suffix
    while( bcore_source_a_parse_bl_fa( source, "#?([0]=='l'||[0]<='L'[0]=='u'||[0]<='U'[0]=='f'||[0]<='F')" ) )
    {
        st_s_push_char( buf, bcore_source_a_get_char( source ) );
    }

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/** parses whitespaces including comments */
er_t xoico_xce_s_trans_whitespace( xoico_xce_s* o, bcore_source* source, st_s* buf )
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
                st_s_push_char( buf, bcore_source_a_get_char( source ) );
            }
            break;

            case '/':
            {
                if( bcore_source_a_parse_bl_fa( source, "#?'//'" ) )
                {
                    st_s_push_sc( buf, "//" );
                    while( !bcore_source_a_eos( source ) )
                    {
                        char c = bcore_source_a_get_char( source );
                        st_s_push_char( buf, c );
                        if( c == '\n' ) break;
                    }
                }
                else if( bcore_source_a_parse_bl_fa( source, "#?'/*'" ) )
                {
                    st_s_push_sc( buf, "/*" );
                    while( !bcore_source_a_eos( source ) )
                    {
                        if( bcore_source_a_parse_bl_fa( source, "#?'*/'" ) )
                        {
                            st_s_push_sc( buf, "*/" );
                            break;
                        }
                        st_s_push_char( buf, bcore_source_a_get_char( source ) );
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

er_t xoico_xce_s_trans_expression
(
    xoico_xce_s* o,
    bcore_source* source,
    st_s* buf,
    const xoico_typespec_s* in_typespec,
    xoico_typespec_s* out_typespec
)
{
    BLM_INIT();

    BLM_TRY( xoico_xce_s_trans_whitespace( o, source, buf ) );

    if( !in_typespec )
    {
        // identifier
        if( bcore_source_a_parse_bl_fa( source, "#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||[0]=='_'||[0]=='@'||([0]==':'&&(([1]>='A'&&[1]<='Z')||([1]>='a'&&[1]<='z')||[1]=='_')))" ) )
        {
            tp_t tp_name = xoico_xce_s_trans_name( o, source, buf );
            const xoico_typespec_s* typespec = xoico_xce_stack_s_get_typespec( &o->stack, tp_name );
            if( typespec )
            {
                BLM_TRY( xoico_xce_s_trans_expression( o, source, buf, typespec, out_typespec ) );
            }
            else
            {
                BLM_TRY( xoico_xce_s_trans_expression( o, source, buf, NULL, NULL ) );
            }
        }
        // number literal
        else if( bcore_source_a_parse_bl_fa( source, "#?([0]>='0'&&[0]<='9')" ) )
        {
            BLM_TRY( xoico_xce_s_trans_number_literal( o, source, buf ) );
        }
        else if( bcore_source_a_parse_bl_fa( source, "#?'.'" ) )
        {
            st_s_push_fa( buf, "." );
            BLM_TRY( xoico_xce_s_trans_whitespace( o, source, buf ) );
            xoico_xce_s_trans_name( o, source, buf );
            BLM_TRY( xoico_xce_s_trans_expression( o, source, buf, NULL, NULL ) );
        }
        else if( bcore_source_a_parse_bl_fa( source, "#?'->'" ) )
        {
            st_s_push_fa( buf, "->" );
            BLM_TRY( xoico_xce_s_trans_whitespace( o, source, buf ) );
            xoico_xce_s_trans_name( o, source, buf );
            BLM_TRY( xoico_xce_s_trans_expression( o, source, buf, NULL, NULL ) );
        }
    }
    else
    {
        bl_t member_access = bcore_source_a_parse_bl_fa( source, "#?'.'" ) ||
                             bcore_source_a_parse_bl_fa( source, "#?'->'" );
        if( member_access )
        {
            st_s* buf_ = BLM_CREATE( st_s );
            tp_t tp_name = xoico_xce_s_trans_name( o, source, buf_ );
            xoico_compiler_element_info_s* info = BLM_CREATE( xoico_compiler_element_info_s );
            if( xoico_compiler_s_get_type_element_info( o->compiler, in_typespec->type, tp_name, info ) )
            {
                if( info->signature ) // member function
                {
                    if( !bcore_source_a_parse_bl_fa( source, "#?'('" ) ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "'(' expected" );
                    st_s* arg_obj = BLM_CLONE( st_s, buf );

                    const xoico_args_s* args = &info->signature->args;

                    st_s_copy_fa
                    (
                        buf,
                        "#<sc_t>_#<sc_t>( #<sc_t>#<sc_t>",
                        xoico_xce_s_nameof( o, in_typespec->type ),
                        xoico_xce_s_nameof( o, tp_name ),
                        ( in_typespec->indirection == 1 ) ? "" : "&", arg_obj->sc
                    );

                    BFOR_EACH( i, args )
                    {
                        BLM_INIT();
                        const xoico_arg_s* arg = &args->data[ i ];
                        st_s* buf_ = BLM_CREATE( st_s );
                        XOICO_BLM_SOURCE_PARSE_FA( source, " " );
                        if( i > 0 ) bcore_source_a_parse_fa( source, " ," );
                        xoico_typespec_s* typespec = BLM_CREATE( xoico_typespec_s );
                        BLM_TRY( xoico_xce_s_trans_expression( o, source, buf_, NULL, typespec ) );

                        st_s_push_fa( buf, ", " );

                        if( typespec->type )
                        {
                            if( typespec->type != arg->typespec.type )
                            {
                                XOICO_BLM_SOURCE_PARSE_ERR_FA
                                (
                                    source,
                                    "Argument #<sz_t>: Specified type '#<sc_t>' does not match expected type '#<sc_t>'",
                                    i,
                                    xoico_xce_s_nameof( o, typespec->type ),
                                    xoico_xce_s_nameof( o, arg->typespec.type )
                                );
                            }

                            if( typespec->indirection != arg->typespec.indirection )
                            {
                                if( typespec->indirection + 1 == arg->typespec.indirection )
                                {
                                    st_s_push_fa( buf, "&" );
                                }
                                else if( typespec->indirection == arg->typespec.indirection + 1 )
                                {
                                    st_s_push_fa( buf, "*" );
                                }
                                else
                                {
                                    XOICO_BLM_SOURCE_PARSE_ERR_FA
                                    (
                                        source,
                                        "Argument #<sz_t>: Cannot resolve indirection.",
                                        i
                                    );
                                }
                            }
                        }

                        st_s_push_fa( buf, "#<sc_t>", buf_->sc );
                        BLM_DOWN();
                    }

                    XOICO_BLM_SOURCE_PARSE_FA( source, " )" );
                    st_s_push_fa( buf, " )" );

                    BLM_TRY( xoico_xce_s_trans_expression( o, source, buf, &info->signature->typespec_ret, out_typespec ) );
                }
                else // member element
                {
                    st_s_push_fa( buf, "#<sc_t>#<sc_t>", ( in_typespec->indirection == 1 ) ? "->" : ".", buf_->sc );
                    BLM_TRY( xoico_xce_s_trans_expression( o, source, buf, &info->type_info.typespec, out_typespec ) );
                }
            }
            else
            {
                XOICO_BLM_SOURCE_PARSE_ERR_FA
                (
                    source,
                    "type '#<sc_t>' has no member of name '#<sc_t>'",
                    xoico_xce_s_nameof( o, in_typespec->type ),
                    xoico_xce_s_nameof( o, tp_name )
                );
            }
        }
        else
        {
            if( out_typespec ) xoico_typespec_s_copy( out_typespec, in_typespec );
        }
    }

    BLM_TRY( xoico_xce_s_trans_whitespace( o, source, buf ) );

    BLM_RETURNV( er_t, 0 );
}

/**********************************************************************************************************************/

#include "xoico_builder.h"

//----------------------------------------------------------------------------------------------------------------------

static inline er_t selftest2( void )
{
    BLM_INIT();

    xoico_builder_main_s* builder_main = BLM_CREATE( xoico_builder_main_s );
    BLM_TRY( xoico_builder_main_s_build_from_file( builder_main, "src/main_xoico.cfg" ) );
    xoico_compiler_s* compiler = builder_main->compiler;
    xoico_compiler_s_expand_setup( compiler );

    const xoico_signature_s* signature = xoico_compiler_s_get_signature( compiler, xoico_compiler_s_entypeof( compiler, "sim_framesig" ) );
    ASSERT( signature );

//    for( sz_t i = 0; i < compiler->hmap_item.size; i++ )
//    {
//        if( bcore_hmap_tpvd_s_idx_key( &compiler->hmap_item, i ) )
//        {
//            const xoico* p_item = ( const xoico* )bcore_hmap_tpvd_s_idx_val( &compiler->hmap_item, i );
//            if( p_item && p_item->_ == TYPEOF_xoico_stamp_s )
//            {
//                xoico_stamp_s* stamp = ( xoico_stamp_s* )p_item;
//                bcore_msg_fa( "#<sc_t>\n", stamp->name.sc );
//            }
//        }
//    }
//
    xoico_xce_s* xce = BLM_CREATE( xoico_xce_s );
    xce->compiler = bcore_fork( compiler );
    xoico_xce_s_setup( xce, false, 0, 0, &signature->args );

    bcore_source* expression = BLM_A_PUSH( bcore_source_string_s_create_sc( "f2.f1.f0.setup( f1.f0 ).setup( f0 )" ) );
    st_s* buf = BLM_CREATE( st_s );

    BLM_TRY( xoico_xce_s_trans_expression( xce, expression, buf, NULL, NULL ) );

    bcore_msg_fa( "#<sc_t>\n", buf->sc );

    BLM_CREATE( sim_s );
    BLM_CREATE( sim_foo0_s );

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

static inline er_t selftest( void )
{
    BLM_INIT();
    bcore_msg_fa( "xoico_xce: selftest\n" );

    xoico_builder_main_s* builder_main = BLM_CREATE( xoico_builder_main_s );
    BLM_TRY( xoico_builder_main_s_build_from_file( builder_main, "../beth/lib/lib_xoico.cfg" ) );
    xoico_compiler_s* compiler = builder_main->compiler;
    xoico_compiler_s_expand_setup( compiler );

    xoico_compiler_element_info_s* info = BLM_CREATE( xoico_compiler_element_info_s );

    if( xoico_compiler_s_get_type_element_info( compiler, btypeof( "bhvm_mcode_hbase_s" ), btypeof( "push_hm" ), info ) )
    {
        bcore_msg_fa( "member type: #<sc_t>\n", xoico_compiler_s_nameof( compiler, info->type_info.typespec.type ) );
        bcore_msg_fa( "member rc: #<sz_t>\n", info->type_info.typespec.indirection );

        if( info->signature )
        {
            bcore_msg_fa( "signature name: #<sc_t>\n", info->signature->st_name.sc );
        }
    }

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

vd_t xoico_xce_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "xoico_xce" ) ) )
    {
        case TYPEOF_init1:
        {
        }
        break;

        case TYPEOF_selftest:
        {
            selftest2();
            return NULL;
        }
        break;

        default: break;
    }

    return NULL;
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

