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

#include "xoite_args.h"
#include "xoite_group.h"

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

void xoite_args_s_clear( xoite_args_s* o )
{
    bcore_array_a_set_space( ( bcore_array* ) o, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoite_args_s_parse( xoite_args_s* o, bcore_source* source )
{
    BLM_INIT();
    xoite_args_s_clear( o );
    while( bcore_source_a_parse_bl_fa( source, " #?',' " ) ) // args follow
    {
        xoite_arg_s* arg = BLM_A_PUSH( xoite_arg_s_create() );
        arg->group = o->group;
        BLM_TRY( xoite_arg_s_parse( arg, source ) );
        bcore_array_a_push( ( bcore_array* ) o, sr_awc( arg ) );
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoite_args_s_append( xoite_args_s* o, bcore_source* source )
{
    BLM_INIT();
    bl_t first = true;
    while( !bcore_source_a_parse_bl_fa( source, " #=?')' " ) ) // args follow
    {
        if( !first ) XOITE_BLM_SOURCE_PARSE_FA( source, " , " );
        xoite_arg_s* arg = BLM_A_PUSH( xoite_arg_s_create() );
        arg->group = o->group;
        BLM_TRY( xoite_arg_s_parse( arg, source ) );
        bcore_array_a_push( ( bcore_array* ) o, sr_awc( arg ) );
        first = false;
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoite_args_s_expand( const xoite_args_s* o, bl_t first, bcore_sink* sink )
{
    er_t er = 0;
    for( sz_t i = 0; i < o->size && !er; i++ )
    {
        if( !first ) bcore_sink_a_push_fa( sink, ", " );
        first = false;
        er = xoite_arg_s_expand( &o->data[ i ], sink );
    }
    return er;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoite_args_s_expand_name( const xoite_args_s* o, bl_t first, bcore_sink* sink )
{
    er_t er = 0;
    for( sz_t i = 0; i < o->size && !er; i++ )
    {
        if( !first ) bcore_sink_a_push_fa( sink, ", " );
        first = false;
        er = xoite_arg_s_expand_name( &o->data[ i ], sink );
    }
    return er;
}

//----------------------------------------------------------------------------------------------------------------------

tp_t xoite_args_s_get_hash( const xoite_args_s* o )
{
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
    for( sz_t i = 0; i < o->size; i++ ) hash = bcore_tp_fold_tp( hash, xoite_arg_s_get_hash( &o->data[ i ] ) );
    return hash;
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

