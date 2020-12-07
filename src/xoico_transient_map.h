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

/** Maps transient type classes to specific types */

#ifndef XOICO_TRANSIENT_MAP_H
#define XOICO_TRANSIENT_MAP_H

/**********************************************************************************************************************/

#include "xoico.h"

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( xoico_transient_map, xoico )
#ifdef XOILA_SECTION

//----------------------------------------------------------------------------------------------------------------------

stamp :s = aware :
{
    bcore_hmap_tptp_s map;
    func xoico.parse;

    func (@*   set(  mutable, tp_t key, tp_t val )) = { o.map.set( key, val ); return o; };
    func (tp_t get(    const, tp_t key )) = { tp_t* p = o.map.get( key ); return p ? *p : 0; };
    func (bl_t exists( const, tp_t key )) = { return o.map.exists( key ); };
};

//----------------------------------------------------------------------------------------------------------------------

/// ( <key> <value>, <key> <value>, ... )
func (:s) xoico.parse = (try)
{
    o.map.clear();
    xoico_compiler_s* compiler = host.compiler();
    source.parse_em_fa( "( " );
    $* s = st_s!.scope();

    while( !source.eos() )
    {
        source.parse_em_fa( "#name ", s );
        if( s.size == 0 ) return source.parse_error_fa( "Transient class name expected." );
        tp_t key = compiler.entypeof( s.sc );
        source.parse_em_fa( "#name ", s );
        if( s.size == 0 ) return source.parse_error_fa( "Type name expected." );
        tp_t type = compiler.entypeof( s.sc );
        o.map.set( key, type );
        if( source.parse_bl( "#?')' " ) ) break;
        source.parse_em_fa( ", " );
    };

    return 0;
};

// ---------------------------------------------------------------------------------------------------------------------

//embed "xoico_transient_map.x";

#endif // XOILA_SECTION

/**********************************************************************************************************************/

#endif // XOICO_TRANSIENT_MAP_H
