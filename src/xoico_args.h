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

#ifndef XOICO_ARGS_H
#define XOICO_ARGS_H

/**********************************************************************************************************************/

#include "xoico.h"
#include "xoico_arg.h"

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( xoico_args, xoico )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signature er_t append(      mutable, bcore_source* source );
signature er_t relent(      mutable, tp_t tp_obj_type );
signature er_t expand(      const, bl_t first, sc_t sc_obj_type, bcore_sink* sink );
signature er_t expand_name( const, bl_t first, bcore_sink* sink );

stamp : = aware :
{
    xoico_arg_s [];
    hidden aware xoico_group_s* group;

    func xoico . parse;
    func xoico . get_hash;

    func     : . append;
    func     : . relent;
    func     : . expand;
    func     : . expand_name;

};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // XOICO_ARGS_H
