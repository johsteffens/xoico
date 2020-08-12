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

#ifndef XOICO_ARG_H
#define XOICO_ARG_H

/**********************************************************************************************************************/

#include "xoico.h"

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( xoico_arg, xoico )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signature er_t expand(      const, bcore_sink* sink );
signature er_t expand_name( const, bcore_sink* sink );

stamp : = aware :
{
    st_s st_type;
    st_s st_name;
    tp_t tp_type; // typeof( type portion in st_type ); 0 if st_type holds no valid type
    tp_t tp_name; // typeof( st_name )
    private aware xoico_group_s* group;
    bcore_source_point_s source_point;

    func xoico : parse;
    func xoico : get_hash;

    func : : expand;
    func : : expand_name;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // XOICO_ARG_H
