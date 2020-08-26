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

/**********************************************************************************************************************/

#include "xoico_builder.h"

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

    if( xoico_compiler_s_get_type_element_info( compiler, btypeof( "bhvm_holor_s" ), btypeof( "s" ), info ) )
    {
        bcore_msg_fa( "member type: #<sc_t>\n", xoico_compiler_s_nameof( compiler, info->type ) );
        bcore_msg_fa( "member rc: #<sz_t>\n", info->reference_depth );
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
            selftest();
            return NULL;
        }
        break;

        default: break;
    }

    return NULL;
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

