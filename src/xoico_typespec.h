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
#ifdef XOILA_SECTION

//----------------------------------------------------------------------------------------------------------------------

signature er_t parse(  m @* o, c xoico_host* host, m bcore_source* source );
signature er_t relent( m @* o, c xoico_host* host, tp_t tp_obj_type );
signature er_t expand( c @* o, c xoico_host* host, m bcore_sink* sink );
signature er_t expand_x( c @* o, c xoico_host* host, m bcore_sink* sink ); // expands in x-format
signature bl_t converts_to( c @* o, c @* b ); // converts to b without a cast

signature void reset( m @* o );

name type_deduce;
name type_object;
name const;
name mutable;
name discardable;
name c;
name m;
name d;

stamp :transient_s = aware :
{
    tp_t class;
    tp_t cast_to_var; // cast to typespec of variable with given name (typically a return typespec of a function)

    func xoico.get_hash =
    {
        tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o._ );
        hash = bcore_tp_fold_tp( hash, o.class );
        return hash;
    };
};

stamp :s = aware :
{
    tp_t type; // possible variable types are TYPEOF_type_deduce and TYPEOF_type_object
    tp_t access_class; // 'const|mutable|discardable'

    :transient_s => transient;

    sz_t indirection;

    bl_t flag_static;
    bl_t flag_volatile;
    bl_t flag_restrict;
    bl_t flag_unaware; // unaware indicates that this type can reference unaware objects (extends range of implicit casts)
    bl_t flag_scope;  // object is in scope
    bl_t flag_addressable = true;  // object can have a pointer ('false' for objects returned by a function)
    bl_t flag_variadic; // variadic arguments

    func xoico.get_hash;
    func     :.parse;
    func     :.relent =
    {
        if( o.type == TYPEOF_type_object ) o.type = tp_obj_type;
        return 0;
    };

    func xoico.convert_transient_types =
    {
        if( o.transient )
        {
            tp_t type = map.get( o.transient.class );
            if( type ) o.type = type;
        }
        return 0;
    };

    func :.expand;
    func :.expand_x;
    func :.converts_to;

    func :.reset =
    {
        o.access_class = 0;
        o.transient =< NULL;
        o.type = 0;
        o.indirection = 0;
        o.flag_static   = false;
        o.flag_volatile = false;
        o.flag_restrict = false;
        o.flag_unaware  = false;
        o.flag_scope    = false;
        o.flag_addressable = true;  // object can have a pointer ('false' for objects returned by a function)
    };

    func ( bl_t is_void( c @* o )) = { return (o.type == 0 || o.type == TYPEOF_void) && o.indirection == 0; };
};

//----------------------------------------------------------------------------------------------------------------------

embed "xoico_typespec.x";

#endif // XOILA_SECTION

/**********************************************************************************************************************/

#endif // XOICO_TYPESPEC_H
