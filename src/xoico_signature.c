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

#include "xoico_signature.h"
#include "xoico_group.h"
#include "xoico_compiler.h"

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

sc_t xoico_signature_s_get_global_name_sc( const xoico_signature_s* o )
{
    return o->global_name.sc;
}

//----------------------------------------------------------------------------------------------------------------------

tp_t xoico_signature_s_get_hash( const xoico_signature_s* o )
{
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
    hash = bcore_tp_fold_sc( hash, o->global_name.sc );
    hash = bcore_tp_fold_u0( hash, o->has_ret ? 1 : 0 );
    hash = bcore_tp_fold_sc( hash, o->ret_type.sc );
    hash = bcore_tp_fold_tp( hash, xoico_args_s_get_hash( &o->args ) );
    hash = bcore_tp_fold_tp( hash, o->arg_o );
    return hash;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_signature_s_parse( xoico_signature_s* o, bcore_source* source )
{
    BLM_INIT();

    st_s* name_buf = BLM_CREATE( st_s );
    st_s* name_candidate = BLM_CREATE( st_s );
    st_s_clear( &o->ret_type );

    bcore_source_point_s_set( &o->source_point, source );

    BLM_TRY( xoico_group_s_parse_name( o->group, name_buf, source ) );

    bl_t predefined = false;

    if( !bcore_source_a_parse_bl_fa( source, " #=?'*'" ) )
    {
        if( bcore_source_a_parse_bl_fa( source, " #?':'" ) )
        {
            predefined = true;

            XOICO_BLM_SOURCE_PARSE_FA( source, " #name", name_candidate );
            if( name_buf->size == 0 )
            {
                st_s_push_fa( name_buf, "#<sc_t>_#<sc_t>", o->group->name.sc, name_candidate->sc );
            }
            else
            {
                st_s_push_fa( name_buf, "_#<sc_t>", name_candidate->sc );
            }
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?'@'" ) )
        {
            if( name_buf->size == 0 )
            {
                st_s_push_sc( name_buf, "@" );
            }
            else
            {
                XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Misplaced '@'." );
            }
        }

        tp_t tp_name = typeof( name_buf->sc );

        // if name_buf refers to another signature
        if( xoico_compiler_s_item_exists( xoico_group_s_get_compiler( o->group ), tp_name ) )
        {
            vc_t item = xoico_compiler_s_item_get( xoico_group_s_get_compiler( o->group ), tp_name );
            if( *(aware_t*)item == TYPEOF_xoico_signature_s )
            {
                const xoico_signature_s* signature = item;
                o->has_ret = signature->has_ret;
                st_s_copy( &o->ret_type, &signature->ret_type );
                xoico_args_s_copy( &o->args, &signature->args );
                o->arg_o = signature->arg_o;
                predefined = true;
            }
        }
        else if( predefined )
        {
            XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Syntax error." );
        }
    }

    if( !predefined )
    {
        // get return type
        if( name_buf->size == 0 ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Return type missing." );
        st_s_push_fa( &o->ret_type, "#<sc_t>", name_buf->sc );
        if( st_s_equal_sc( name_buf, "const" ) )
        {
            XOICO_BLM_SOURCE_PARSE_FA( source, " #name", name_buf );
            if( name_buf->size == 0 ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Return type missing." );
            st_s_push_fa( &o->ret_type, " #<sc_t>", name_buf->sc );
        }
        while( bcore_source_a_parse_bl_fa( source, " #?'*'" ) ) st_s_push_char( &o->ret_type, '*' );
    }

    // get name
    XOICO_BLM_SOURCE_PARSE_FA( source, " #name", &o->name );
    if( o->name.size == 0 )
    {
        if( name_candidate->size > 0 )
        {
            st_s_copy( &o->name, name_candidate );
        }
        else
        {
            XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Name missing." );
        }
    }

    o->has_ret = !st_s_equal_sc( &o->ret_type, "void" );

    // get or append args
    o->args.group = o->group;
    if( !predefined )
    {
        XOICO_BLM_SOURCE_PARSE_FA( source, " ( " );
        if(      bcore_source_a_parse_bl_fa(  source, " #?'mutable' " ) ) o->arg_o = TYPEOF_mutable;
        else if( bcore_source_a_parse_bl_fa(  source, " #?'const' "   ) ) o->arg_o = TYPEOF_const;
        else if( bcore_source_a_parse_bl_fa(  source, " #?'plain' "   ) ) o->arg_o = 0;
        else     XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "'plain', mutable' or 'const' expected." );

        BLM_TRY( xoico_args_s_parse( &o->args, source ) );
        XOICO_BLM_SOURCE_PARSE_FA( source, " ) " );
    }
    else if( bcore_source_a_parse_bl_fa( source, " #?'('" ) )
    {
        BLM_TRY( xoico_args_s_append( &o->args, source ) );
        XOICO_BLM_SOURCE_PARSE_FA( source, " ) " );
    }

    st_s_copy_fa( &o->global_name, "#<sc_t>_#<sc_t>", o->group->name.sc, o->name.sc );

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

