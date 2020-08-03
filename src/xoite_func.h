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

#ifndef XOITE_FUNC_H
#define XOITE_FUNC_H

/**********************************************************************************************************************/

#include "xoite.h"
#include "xoite_body.h"

/**********************************************************************************************************************/

BETH_PLANT_DEFINE_GROUP( xoite_func, xoite )
#ifdef PLANT_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signature tp_t get_hash( const );
signature er_t parse( mutable, xoite_group_s* group, xoite_stamp_s* stamp, bcore_source* source );
signature bl_t registerable( const );

stamp : = aware :
{
    st_s name;
    st_s decl;
    tp_t type;
    bl_t overloadable = false;
    xoite_body_s => body;
    private xoite_group_s* group;
    bcore_source_point_s source_point;

    func : :get_hash;
    func : :parse;
    func : :registerable;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // PLANT_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // XOITE_FUNC_H
