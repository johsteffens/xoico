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

#ifndef XOICO_BODY_H
#define XOICO_BODY_H

/**********************************************************************************************************************/

#include "xoico.h"

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( xoico_body, xoico )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signature er_t parse_expression( mutable, bcore_source* source );
signature er_t parse(      mutable, bcore_source* source );
signature er_t finalize(   mutable );
signature er_t expand( const, const xoico_signature_s* signature, sz_t indent, bcore_sink* sink );
signature er_t set_group(  mutable, xoico_group_s* group );
signature er_t set_stamp(  mutable, xoico_stamp_s* stamp );

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :code = aware :
{
    bl_t single_line;
    sz_t indentation;
    tp_t hash_source;

    bcore_source_point_s source_point;

    func     : . parse;
    func xoico . get_hash;

    hidden aware xoico_group_s* group;
    hidden aware xoico_stamp_s* stamp;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp : = aware :
{
    st_s name;
    st_s global_name;

    :code_s => code;

    bl_t go_inline;

    bcore_source_point_s source_point;

    hidden aware xoico_group_s* group; // group refers to the place of original definition
    hidden aware xoico_stamp_s* stamp;

    func xoico . get_hash;
    func xoico . get_global_name_sc;
    func     : . parse_expression;
    func     : . parse;
    func     : . finalize;
    func     : . expand;
    func     : . set_group;
    func     : . set_stamp;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // XOICO_BODY_H
