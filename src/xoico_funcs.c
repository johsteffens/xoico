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

#include "xoico_funcs.h"
#include "xoico_group.h"

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

/// returns -1 if not found
sz_t xoico_funcs_s_get_index_from_type( const xoico_funcs_s* o, tp_t type )
{
    for( sz_t i = 0; i < o->size; i++ ) if( o->data[ i ]->type == type ) return i;
    return -1;
}

//----------------------------------------------------------------------------------------------------------------------

/// returns -1 if not found
sz_t xoico_funcs_s_get_index_from_name( const xoico_funcs_s* o, tp_t name )
{
    for( sz_t i = 0; i < o->size; i++ ) if( o->data[ i ]->name == name ) return i;
    return -1;
}

//----------------------------------------------------------------------------------------------------------------------

bl_t xoico_funcs_s_exists_from_type( const xoico_funcs_s* o, tp_t type )
{
    return ( xoico_funcs_s_get_index_from_type( o, type ) >= 0 );
}

//----------------------------------------------------------------------------------------------------------------------

bl_t xoico_funcs_s_exists_from_name( const xoico_funcs_s* o, tp_t name )
{
    return ( xoico_funcs_s_get_index_from_name( o, name ) >= 0 );
}

//----------------------------------------------------------------------------------------------------------------------

xoico_func_s* xoico_funcs_s_get_func_from_name( const xoico_funcs_s* o, tp_t name )
{
    sz_t idx = xoico_funcs_s_get_index_from_name( o, name );
    return ( idx >= 0 ) ? o->data[ idx ] : NULL;
}

//----------------------------------------------------------------------------------------------------------------------

xoico_func_s* xoico_funcs_s_get_func_from_type( const xoico_funcs_s* o, tp_t type )
{
    sz_t idx = xoico_funcs_s_get_index_from_type( o, type );
    return ( idx >= 0 ) ? o->data[ idx ] : NULL;
}

//----------------------------------------------------------------------------------------------------------------------

/// replacing by removing old function and appending new function keeping order
er_t xoico_funcs_s_replace_fork( xoico_funcs_s* o, sz_t idx, xoico_func_s* func )
{
    ASSERT( idx >= 0 && idx < o->size );
    xoico_func_s_detach( &o->data[ idx ] );
    for( sz_t i = idx + 1; i < o->size; i++ ) o->data[ i - 1 ] = o->data[ i ];
    o->data[ o->size - 1 ] = bcore_fork( func );
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

