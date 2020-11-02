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

#ifndef XOICO_CALEPH_H
#define XOICO_CALEPH_H

#include "xoico_cengine.h"
#include "xoico_body.h"
#include "xoico_args.h"

/**********************************************************************************************************************/

/// C code processor  (Puce C code)

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( xoico_caleph, xoico_cengine )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signature tp_t entypeof(  mutable, sc_t name );
signature sc_t nameof(    mutable, tp_t type );

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp : = aware :
{
    /// parameters

    bl_t insert_source_reference = true;

    /// runtime data

    hidden xoico_args_s*     args;
    hidden xoico_compiler_s* compiler;
    hidden xoico_group_s*    group;
    hidden xoico_stamp_s*    stamp;

    tp_t obj_type;

    bcore_hmap_name_s hmap_name;

    func :.entypeof = { return bcore_hmap_name_s_set_sc( &o->hmap_name, name ); };
    func :.nameof   =
    {
        sc_t name = bcore_hmap_name_s_get_sc( &o->hmap_name, type );
        if( !name ) name = xoico_compiler_s_nameof( o->compiler, type );
        return name;
    };

    func xoico_cengine.translate;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // XOICO_CALEPH_H
