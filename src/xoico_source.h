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

#ifndef XOICO_SOURCE_H
#define XOICO_SOURCE_H

/**********************************************************************************************************************/

#include "xoico.h"
#include "xoico_group.h"

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( xoico_source, xoico )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signature er_t push_group( mutable, xoico_group_s* group );
signature er_t parse(      mutable, bcore_source* source );
signature er_t finalize(  mutable );
signature er_t expand_declaration( const, sz_t indent, bcore_sink* sink );
signature er_t expand_definition(  const, sz_t indent, bcore_sink* sink );
signature er_t expand_init1(       const, sz_t indent, bcore_sink* sink );

stamp : = aware :
{
    st_s name; // file name excluding directory and extension
    st_s path; // file path excluding extension
    tp_t hash;
    xoico_group_s => [];

    hidden aware xoico_target_s* target;

    func xoico.expand_setup;

    func :.push_group;
    func :.parse;
    func :.finalize;
    func :.expand_declaration;
    func :.expand_definition;
    func :.expand_init1;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // XOICO_SOURCE_H
