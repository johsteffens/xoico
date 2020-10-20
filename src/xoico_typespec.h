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

#ifndef XOICO_TYPESPEC_H
#define XOICO_TYPESPEC_H

/**********************************************************************************************************************/

#include "xoico.h"

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( xoico_typespec, xoico )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signature er_t parse( mutable,  xoico_group_s* group, bcore_source* source );
signature er_t relent( mutable, xoico_group_s* group, tp_t tp_obj_type );
signature er_t expand( const, xoico_group_s* group, sc_t sc_obj_type, bcore_sink* sink );
signature void reset( mutable );

name type_deduce;
name type_object;

stamp : = aware :
{
    tp_t type; // possible variable types are TYPEOF_type_deduce and TYPEOF_type_object
    sz_t indirection;

    bl_t flag_const;
    bl_t flag_static;
    bl_t flag_volatile;
    bl_t flag_restrict;
    bl_t flag_keep;
    bl_t flag_addressable = true;  // object can have a pointer ('false' for objects returned by a function)

    func xoico : get_hash;
    func     : : parse;
    func     : : relent;
    func     : : expand;

    func     : : reset =
    {
        o->type = 0;
        o->indirection = 0;
        o->flag_const    = false;
        o->flag_static   = false;
        o->flag_volatile = false;
        o->flag_restrict = false;
        o->flag_keep     = false;
        o->flag_addressable = true;  // object can have a pointer ('false' for objects returned by a function)
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // XOICO_TYPESPEC_H
