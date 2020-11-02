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

#include "xoico_func.h"
#include "xoico_group.h"
#include "xoico_stamp.h"
#include "xoico_signature.h"
#include "xoico_compiler.h"

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

tp_t xoico_func_s_get_hash( const xoico_func_s* o )
{
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
    hash = bcore_tp_fold_tp( hash, o->pre_hash );
    hash = bcore_tp_fold_tp( hash, o->name );
    hash = bcore_tp_fold_sc( hash, o->flect_decl.sc );
    hash = bcore_tp_fold_tp( hash, o->signature_global_name );
    hash = bcore_tp_fold_bl( hash, o->overloadable );
    hash = bcore_tp_fold_bl( hash, o->expandable );
    if( o->body ) hash = bcore_tp_fold_tp( hash, xoico_body_s_get_hash( o->body ) );
    return hash;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_func_s_set_global_name( xoico_func_s* o )
{
    BLM_INIT();
    st_s* st_global_name = BLM_CREATE( st_s );

    xoico_compiler_s* compiler = xoico_group_s_get_compiler( o->group );
    sc_t sc_name = xoico_compiler_s_nameof( compiler, o->name );

    if( o->stamp )
    {
        st_s_push_fa( st_global_name, "#<sc_t>_#<sc_t>", o->stamp->st_name.sc, sc_name );
    }
    else
    {
        st_s_push_fa( st_global_name, "#<sc_t>_#<sc_t>", o->group->st_name.sc, sc_name );
    }

    o->global_name = xoico_compiler_s_entypeof( compiler, st_global_name->sc );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_func_s_parse( xoico_func_s* o, bcore_source* source )
{
    BLM_INIT();

    xoico_compiler_s* compiler = xoico_group_s_get_compiler( o->group );

    // global name signature
    st_s* st_type = BLM_CREATE( st_s );

    bcore_source_point_s_set( &o->source_point, source );

    st_s_push_sc( &o->flect_decl, "func " );

    st_s* st_name = BLM_CREATE( st_s );

    if( bcore_source_a_parse_bl_fa( source, " #?'('" ) )
    {
        xoico_signature_s* signature = xoico_signature_s_create();
        signature->group = o->group;
        signature->stamp = o->stamp;

        BLM_TRY( xoico_signature_s_parse( signature, source ) );
        XOICO_BLM_SOURCE_PARSE_FA( source, " ) " );

        BLM_TRY( xoico_compiler_s_life_a_push( compiler, signature ) );
        BLM_TRY( xoico_compiler_s_register_item( compiler, ( xoico* )signature, source ) );

        o->pre_hash = bcore_tp_fold_tp( o->pre_hash, xoico_signature_s_get_hash( signature ) );

        if( o->stamp )
        {
            st_s_copy( st_type, &o->stamp->st_name );
        }
        else
        {
            st_s_copy( st_type, &o->group->st_name );
        }

        st_s_copy_sc( st_name, xoico_compiler_s_nameof( compiler, signature->name ) );
        st_s_push_fa( &o->flect_decl, "#<sc_t>:#<sc_t>", st_type->sc, st_name->sc );
    }
    else
    {

        if( bcore_source_a_parse_bl_fa( source, " #?'^'" ) )
        {
            if( !o->stamp ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "'^' is only inside a stamp allowed." );
            st_s_copy( st_type, &o->stamp->st_trait_name );
            st_s_push_fa( &o->flect_decl, "^" );
        }
        else
        {
            BLM_TRY( xoico_group_s_parse_name( o->group, st_type, source ) );

            if( o->stamp && st_s_equal_st( st_type, &o->stamp->st_trait_name ) )
            {
                st_s_push_fa( &o->flect_decl, "^" );
            }
            else
            {
                st_s_push_fa( &o->flect_decl, "#<sc_t>", st_type->sc );
            }
        }

        XOICO_BLM_SOURCE_PARSE_FA( source, " ." );
        st_s_push_sc( &o->flect_decl, ":" );

        XOICO_BLM_SOURCE_PARSE_FA( source, " #name", st_name );
    }

    if( st_name->size == 0 ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Function name expected." );
    o->name = xoico_compiler_s_entypeof( compiler, st_name->sc );

    st_s_push_sc( &o->flect_decl, st_name->sc );

    st_s_push_fa( st_type, "_#<sc_t>", st_name->sc );

    o->signature_global_name = xoico_compiler_s_entypeof( compiler, st_type->sc );
    BLM_TRY( xoico_func_s_set_global_name( o ) );

    if( bcore_source_a_parse_bl_fa( source, " #=?'='" ) )
    {
        o->body = xoico_body_s_create();
        BLM_TRY( xoico_body_s_set_group( o->body, o->group ) );
        BLM_TRY( xoico_body_s_set_stamp( o->body, o->stamp ) );
        BLM_TRY( xoico_body_s_parse( o->body, source ) );
    }

    XOICO_BLM_SOURCE_PARSE_FA( source, " ; " );
    st_s_push_sc( &o->flect_decl, ";" );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

bl_t xoico_func_s_registerable( const xoico_func_s* o )
{
    if( !o->expandable ) return false;
    if( xoico_compiler_s_is_item( xoico_group_s_get_compiler( o->group ), o->signature_global_name ) )
    {
        const xoico* item = xoico_compiler_s_get_const_item( xoico_group_s_get_compiler( o->group ), o->signature_global_name );
        if( *(aware_t*)item == TYPEOF_xoico_signature_s )
        {
            if( !xoico_group_s_get_compiler( o->group )->register_signatures ) return false;
            const xoico_signature_s* signature = ( xoico_signature_s* )item;
            return ( signature->arg_o != 0 || xoico_group_s_get_compiler( o->group )->register_non_feature_functions );
        }
        else
        {
            return true;
        }
    }
    else
    {
        return true;
    }
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_func_s_finalize( xoico_func_s* o )
{
    BLM_INIT();
    BLM_TRY( xoico_func_s_set_global_name( o ) );
    if( o->body )
    {
        BLM_TRY( xoico_body_s_set_group( o->body, o->group ) );
        BLM_TRY( xoico_body_s_set_stamp( o->body, o->stamp ) );
        BLM_TRY( xoico_body_s_finalize( o->body ) );
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

