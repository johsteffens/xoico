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

signature bl_t exists_from_signature_global_name( const, tp_t signature_global_name );
signature bl_t exists_from_name( const, tp_t name );
signature sz_t get_index_from_signature_global_name( const, tp_t signature_global_name ); // returns -1 if not found
signature sz_t get_index_from_name( const, tp_t name ); // returns -1 if not found
signature xoico_func_s* get_func_from_signature_global_name( const, tp_t signature_global_name ); // returns NULL if not found
signature xoico_func_s* get_func_from_name( const, tp_t name ); // returns NULL if not found
signature er_t replace_fork( mutable, sz_t idx, xoico_func_s* func );
signature er_t push_d( mutable, xoico_func_s* func );
signature tp_t get_hash( const );

stamp : = aware :
{
    xoico_func_s => [];
    func :.exists_from_signature_global_name;
    func :.exists_from_name;
    func :.get_index_from_signature_global_name;
    func :.get_index_from_name;
    func :.get_func_from_signature_global_name;
    func :.get_func_from_name;
    func :.replace_fork;
    func :.push_d = { o.cast( bcore_array* ).push( sr_asd( func ) ); return 0; };
    func :.get_hash =
    {
        tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
        foreach( $* func in o ) hash = bcore_tp_fold_tp( hash, func.get_hash() );
        return hash;
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // XOICO_FUNCS_H
