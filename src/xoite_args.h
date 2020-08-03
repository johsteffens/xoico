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

#ifndef XOITE_ARGS_H
#define XOITE_ARGS_H

/**********************************************************************************************************************/

#include "xoite.h"
#include "xoite_arg.h"

/**********************************************************************************************************************/

BETH_PLANT_DEFINE_GROUP( xoite_args, xoite )
#ifdef PLANT_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signature er_t append(      mutable, bcore_source* source );
signature er_t expand(      const, bl_t first, bcore_sink* sink );
signature er_t expand_name( const, bl_t first, bcore_sink* sink );

stamp : = aware :
{
    xoite_arg_s [];
    private xoite_group_s* group;

    func xoite : parse;
    func xoite : get_hash;

    func     : : append;
    func     : : expand;
    func     : : expand_name;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // PLANT_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // XOITE_ARGS_H
