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

//bl_t is_alphanumeric( bcore_source* source );
//tp_t get_name( bcore_source* source );
//
//static er_t trans( tp_t type, bcore_source* source, st_s* buf )
//{
//    BLM_INIT();
//    if( is_alphanumeric( source ) )
//    {
//        tp_t id = get_name( source, buf );
//        type = get_type( type, id );
//        trans( type, source, buf );
//    }
//    else if( bcore_source_a_parse_bl_fa( source, "#?'->'" ) ) // member
//    {
//        tp_t id = get_name( source, buf );
//        type = get_member_type( type, id );
//        if( bcore_source_a_parse_bl_fa( source, " #?'('" ) ) // member function
//        {
//            st_s* arg_obj = BLM_CLONE( st_s, buf );
//            bcore_arr_st_s* arr_arg = BLM_CREATE( bcore_arr_st_s );
//            bl_t first = true;
//            while( !bcore_source_a_parse_bl_fa( source, " #?')'" ) )
//            {
//                if( !first ) bcore_source_a_parse_fa( source, " ," );
//                trans( 0, source, bcore_arr_st_s_push_st_d( arr_arg, st_s_create() ) );
//                first = false;
//            }
//            st_s_set_size( buf, 0 );
//            st_s_push_fa( buf, "#<sc_t>( ", get_name_sc( type ) );
//            BFOR_EACH( i, arr_arg )
//            {
//                st_s_push_fa( buf, ", #<sc_t>", arr_arg->data[ i ]->sc );
//            }
//            st_s_push_fa( buf, " )", get_name_sc( type ) );
//        }
//    }
//    else if( bcore_source_a_parse_bl_fa( source, "#?'('" ) ) // function
//    {
//        type = get_return_type( type );
//
//
//
//    }
//    else if( eos || bcore_source_a_parse_bl_fa( source, "#?([0]==','||[0]==';'||[0]==')'||[0]=='}')" ) ) // done
//    {
//        return 0;
//    }
//    else
//    {
//        /// consume whitespace and operators then trans
//    }
//
//    BLM_RETURNV( er_t, 0 );
//}

tp_t xoico_xce_s_trans_name( xoico_xce_s* o, bcore_source* source, st_s* buf )
{
    BLM_INIT();
    st_s* st_name = BLM_CREATE( st_s );
    bcore_source_a_parse_fa( source, "#name", st_name );
    //bcore_msg_fa( "trans_name: #<sc_t>\n", st_name->sc );
    st_s_push_st( buf, st_name );
    tp_t tp_name = xoico_xce_s_entypeof( o, st_name->sc );
    BLM_RETURNV( tp_t, tp_name );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_xce_s_trans_expression
(
    xoico_xce_s* o,
    const xoico_typespec_s* in_typespec,
    bcore_source* source,
    st_s* buf,
    const xoico_typespec_s** out_typespec
)
{
    BLM_INIT();
    if( !in_typespec )
    {
        if( bcore_source_a_parse_bl_fa( source, "#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||[0]=='_')" ) )
        {
            tp_t tp_name = xoico_xce_s_trans_name( o, source, buf );
            const xoico_typespec_s* typespec = xoico_xce_stack_s_get_typespec( &o->stack, tp_name );
            xoico_xce_s_entypeof( o, xoico_compiler_s_nameof( o->compiler, typespec->type ) );
            BLM_TRY( xoico_xce_s_trans_expression( o, typespec, source, buf, out_typespec ) );
        }
    }
    else
    {
        if( bcore_source_a_parse_bl_fa( source, "#?'.'" ) )
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
                        const xoico_typespec_s* typespec = NULL;
                        BLM_TRY( xoico_xce_s_trans_expression( o, NULL, source, buf_, &typespec ) );
                        ASSERT( typespec );

                        st_s_push_fa( buf, ", " );

                        if( typespec )
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

                    //bcore_msg_fa( "typespec_ret: #<sc_t>\n", xoico_compiler_s_nameof( o->compiler, info->signature->typespec_ret.type ) );

                    BLM_TRY( xoico_xce_s_trans_expression( o, &info->signature->typespec_ret, source, buf, out_typespec ) );
                }
                else // member element
                {
                    st_s_push_fa( buf, "#<sc_t>#<sc_t>", ( in_typespec->indirection == 1 ) ? "->" : ".", buf_->sc );
                    BLM_TRY( xoico_xce_s_trans_expression( o, &info->typespec, source, buf, out_typespec ) );
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
            if( out_typespec ) *out_typespec = in_typespec;
        }
    }
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

    BLM_TRY( xoico_xce_s_trans_expression( xce, NULL, expression, buf, NULL ) );

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
        bcore_msg_fa( "member type: #<sc_t>\n", xoico_compiler_s_nameof( compiler, info->typespec.type ) );
        bcore_msg_fa( "member rc: #<sz_t>\n", info->typespec.indirection );

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

