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

#ifndef XOICO_HOST_H
#define XOICO_HOST_H

/**********************************************************************************************************************/

/** Main Interface */

/**********************************************************************************************************************/

#include "xoico.h"

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( xoico_host, bcore_inst )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

include deferred "xoico_compiler.h";

// parses an identifier with namespace-syntax
feature 'a' er_t parse_name_st( const, bcore_source* source, st_s* name ) = { ERR_fa( "Not implemented in '#<sc_t>'.", nameof( o._ ) ); return 0; };

feature 'a' er_t parse_name_tp( const, bcore_source* source, tp_t* name ) = (try)
{
    $* s = st_s!.scope();
    o.parse_name_st( source, s );
    if( s.size == 0 ) return source.parse_error_fa( "Identifier expected." );
    tp_t t = o.compiler().entypeof( s.sc );
    if( name ) name.0 = t;
    return 0;
};

feature 'a' xoico_compiler_s* compiler( const ) = { ERR_fa( "Not implemented in '#<sc_t>'.", nameof( o._ ) ); return NULL; };
feature 'a' xoico_cengine* cengine( const )     = { ERR_fa( "Not implemented in '#<sc_t>'.", nameof( o._ ) ); return NULL; };
feature 'a' tp_t obj_type( const )              = { ERR_fa( "Not implemented in '#<sc_t>'.", nameof( o._ ) ); return 0; };
feature 'a' st_s* create_spect_name( const )    = { ERR_fa( "Not implemented in '#<sc_t>'.", nameof( o._ ) ); return NULL; };
feature 'a' const xoico_transient_map_s* transient_map( const ) = { ERR_fa( "Not implemented in '#<sc_t>'.", nameof( o._ ) ); return NULL; };

feature 'a' sc_t nameof( const, tp_t type ) =
{
    return o.compiler().nameof( type );
};

feature 'a' tp_t entypeof( const, sc_t name ) =
{
    return o.compiler().entypeof( name );
};

//----------------------------------------------------------------------------------------------------------------------

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//----------------------------------------------------------------------------------------------------------------------
// macros

/**********************************************************************************************************************/

#endif // XOICO_HOST_H