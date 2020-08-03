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

#include "xoite_func.h"
#include "xoite_group.h"
#include "xoite_stamp.h"
#include "xoite_signature.h"
#include "xoite_compiler.h"

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

tp_t xoite_func_s_get_hash( const xoite_func_s* o )
{
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
    hash = bcore_tp_fold_sc( hash, o->name.sc );
    hash = bcore_tp_fold_sc( hash, o->decl.sc );
    hash = bcore_tp_fold_tp( hash, o->type );
    if( o->body ) hash = bcore_tp_fold_tp( hash, xoite_body_s_get_hash( o->body ) );
    return hash;
}

//----------------------------------------------------------------------------------------------------------------------

/// stamp should be NULL func is not parsed inside a stamp
er_t xoite_func_s_parse( xoite_func_s* o, xoite_group_s* group, xoite_stamp_s* stamp, bcore_source* source )
{
    BLM_INIT();

    /// global name of function
    st_s* type_name = BLM_CREATE( st_s );

    bcore_source_point_s_set( &o->source_point, source );

    st_s_push_sc( &o->decl, "func " );

    if( bcore_source_a_parse_bl_fa( source, " #?'^'" ) )
    {
        if( !stamp ) XOITE_BLM_SOURCE_PARSE_ERR_FA( source, "'^' is only inside a stamp allowed." );
        st_s_copy( type_name, &stamp->trait_name );
        st_s_push_fa( &o->decl, "^" );
    }
    else
    {
        BLM_TRY( xoite_group_s_parse_name( group, type_name, source ) );

        if( stamp && st_s_equal_st( type_name, &stamp->trait_name ) )
        {
            st_s_push_fa( &o->decl, "^" );
        }
        else
        {
            st_s_push_fa( &o->decl, "#<sc_t>", type_name->sc );
        }
    }

    XOITE_BLM_SOURCE_PARSE_FA( source, " :" );
    st_s_push_sc( &o->decl, ":" );

    XOITE_BLM_SOURCE_PARSE_FA( source, " #name", &o->name );
    if( o->name.size == 0 ) XOITE_BLM_SOURCE_PARSE_ERR_FA( source, "Function name expected." );
    st_s_push_sc( &o->decl, o->name.sc );

    st_s_push_fa( type_name, "_#<sc_t>", o->name.sc );
    o->type = typeof( type_name->sc );

    if( bcore_source_a_parse_bl_fa( source, " #=?'='" ) )
    {
        o->body = xoite_body_s_create();
        o->body->group = group;
        BLM_TRY( xoite_body_s_parse( o->body, stamp, source ) );
    }

    XOITE_BLM_SOURCE_PARSE_FA( source, " ; " );
    st_s_push_sc( &o->decl, ";" );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

bl_t xoite_func_s_registerable( const xoite_func_s* o )
{
    if( xoite_compiler_s_item_exists( xoite_compiler_g, o->type ) )
    {
        const xoite* item = xoite_compiler_s_item_get( xoite_compiler_g, o->type );
        if( *(aware_t*)item == TYPEOF_xoite_signature_s )
        {
            if( !xoite_compiler_g->register_signatures ) return false;
            const xoite_signature_s* signature = ( xoite_signature_s* )item;
            return ( signature->arg_o != 0 || xoite_compiler_g->register_plain_functions );
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

/**********************************************************************************************************************/

