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

#ifndef XOICO_FUNCS_H
#define XOICO_FUNCS_H

/**********************************************************************************************************************/

#include "xoico.h"
#include "xoico_func.h"

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( xoico_funcs, xoico )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signature bl_t exists_from_type( const, tp_t type );
signature bl_t exists_from_name( const, tp_t name );
signature sz_t get_index_from_type( const, tp_t type ); // returns -1 if not found
signature sz_t get_index_from_name( const, tp_t name ); // returns -1 if not found
signature xoico_func_s* get_func_from_type( const, tp_t type ); // returns NULL if not found
signature xoico_func_s* get_func_from_name( const, tp_t name ); // returns NULL if not found
signature er_t replace_fork( mutable, sz_t idx, xoico_func_s* func );

stamp : = aware :
{
    xoico_func_s => [];
    func : :exists_from_type;
    func : :exists_from_name;
    func : :get_index_from_type;
    func : :get_index_from_name;
    func : :replace_fork;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // XOICO_FUNCS_H
