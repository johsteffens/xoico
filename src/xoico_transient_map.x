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

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

stamp :s = aware :
{
    bcore_hmap_tptp_s map;
    func xoico.parse;

    func (m @* set(    m @* o, tp_t key, tp_t val )) = { o.map.set( key, val ); return o; };
    func (tp_t get(    c @* o, tp_t key )) = { m tp_t* p = o.map.get( key ); return p ? *p : 0; };
    func (bl_t exists( c @* o, tp_t key )) = { return o.map.exists( key ); };
};

//----------------------------------------------------------------------------------------------------------------------

/// ( <key> <value>, <key> <value>, ... )
func (:s) xoico.parse =
{
    o.map.clear();
    m xoico_compiler_s* compiler = host.compiler();
    source.parse_fa( "( " );
    m $* s = st_s!^;

    while( !source.eos() )
    {
        source.parse_fa( "#name ", s );
        if( s.size == 0 ) return source.parse_error_fa( "Transient class name expected." );
        tp_t key = compiler.entypeof( s.sc );
        tp_t type = 0;
        host.parse_name_tp( source, type.1 );
        if( !type ) return source.parse_error_fa( "Type name expected." );
        o.map.set( key, type );
        if( source.parse_bl( "#?')' " ) ) break;
        source.parse_fa( ", " );
    };

    return 0;
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
