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
#include "xoico_stamp.h"
#include "xoico_group.h"
#include "xoico_compiler.h"

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

sc_t xoico_signature_s_get_global_name_sc( const xoico_signature_s* o )
{
    return o->st_global_name.sc;
}

//----------------------------------------------------------------------------------------------------------------------

tp_t xoico_signature_s_get_hash( const xoico_signature_s* o )
{
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
    hash = bcore_tp_fold_sc( hash, o->st_global_name.sc );
    hash = bcore_tp_fold_tp( hash, xoico_typespec_s_get_hash( &o->typespec_ret ) );
    hash = bcore_tp_fold_tp( hash, xoico_args_s_get_hash( &o->args ) );
    hash = bcore_tp_fold_tp( hash, o->arg_o );
    return hash;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_signature_s_parse( xoico_signature_s* o, bcore_source* source )
{
    BLM_INIT();
    bcore_source_point_s_set( &o->source_point, source );

    if( bcore_source_a_parse_bl_fa( source, " #?'extending'" ) )
    {
        st_s* name_buf = BLM_CREATE( st_s );
        BLM_TRY( xoico_group_s_parse_name( o->group, name_buf, source ) );
        tp_t tp_name = typeof( name_buf->sc );

        const xoico_signature_s* signature = xoico_compiler_s_get_signature( xoico_group_s_get_compiler( o->group ), tp_name );
        if( !signature )
        {
            XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Could not find predefined signature '#<sc_t>'.", name_buf->sc );
        }

        xoico_typespec_s_copy( &o->typespec_ret, &signature->typespec_ret );
        o->typespec_ret.group = o->group;
        xoico_args_s_copy( &o->args, &signature->args );
        o->arg_o = signature->arg_o;

        XOICO_BLM_SOURCE_PARSE_FA( source, " #name", name_buf );
        if( name_buf->size == 0 )  XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Signature name missing." );
        st_s_copy( &o->st_name, name_buf );
        XOICO_BLM_SOURCE_PARSE_FA( source, " (" );
        BLM_TRY( xoico_args_s_append( &o->args, source ) );
        XOICO_BLM_SOURCE_PARSE_FA( source, " )" );
    }
    else
    {
        o->typespec_ret.group = o->group;
        BLM_TRY( xoico_typespec_s_parse( &o->typespec_ret, source ) );

        // get name
        XOICO_BLM_SOURCE_PARSE_FA( source, " #name", &o->st_name );

        // get args
        ASSERT( o->group );
        o->args.group = o->group;

        XOICO_BLM_SOURCE_PARSE_FA( source, " (" );
        if(      bcore_source_a_parse_bl_fa(  source, " #?'mutable' " ) ) o->arg_o = TYPEOF_mutable;
        else if( bcore_source_a_parse_bl_fa(  source, " #?'const' "   ) ) o->arg_o = TYPEOF_const;
        else if( bcore_source_a_parse_bl_fa(  source, " #?'plain' "   ) ) o->arg_o = 0;
        else     XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "'plain', mutable' or 'const' expected." );

        BLM_TRY( xoico_args_s_parse( &o->args, source ) );
        XOICO_BLM_SOURCE_PARSE_FA( source, " )" );
    }

    st_s_copy_fa( &o->st_global_name, "#<sc_t>_#<sc_t>", o->group->name.sc, o->st_name.sc );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_signature_s_expand_declaration( const xoico_signature_s* o, const xoico_stamp_s* stamp, sc_t sc_func_global_name, sz_t indent, bcore_sink* sink )
{
    BLM_INIT();
    sc_t sc_name = stamp->name.sc;
    xoico_typespec_s_expand( &o->typespec_ret, sc_name, sink );
    bcore_sink_a_push_fa( sink, " #<sc_t>( ", sc_func_global_name );

    if( o->arg_o )
    {
        bcore_sink_a_push_fa( sink, "#<sc_t>", ( o->arg_o == TYPEOF_mutable ) ? "" : "const " );
        bcore_sink_a_push_fa( sink, "#<sc_t>* o", sc_name );
        BLM_TRY( xoico_args_s_expand( &o->args, false, sc_name, sink ) );
        bcore_sink_a_push_fa( sink, " )" );
    }
    else
    {
        if( o->args.size > 0 )
        {
            BLM_TRY( xoico_args_s_expand( &o->args, true, sc_name, sink ) );
        }
        else
        {
            bcore_sink_a_push_fa( sink, "void" );
        }
        bcore_sink_a_push_fa( sink, " )" );
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

