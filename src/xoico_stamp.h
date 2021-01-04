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

#ifndef XOICO_STAMP_H
#define XOICO_STAMP_H

/**********************************************************************************************************************/

#include "xoico.h"
#include "xoico_funcs.h"
#include "xoico_wraps.h"
#include "xoico_transient_map.h"

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( xoico_stamp, xoico )
#ifdef XOILA_SECTION

//----------------------------------------------------------------------------------------------------------------------

signature er_t parse_func( m @* o, m bcore_source* source );
signature er_t parse_wrap( m @* o, m bcore_source* source );
signature er_t make_funcs_overloadable( m @* o );
signature er_t push_default_funcs( m @* o );
signature const xoico_func_s* get_func_from_name( c @* o, tp_t name ); // returns NULL if not found
signature const xoico_func_s* get_trait_line_func_from_name( c @* o, tp_t name ); // returns NULL if not found


stamp :s = aware :
{
    st_s    st_name;
    tp_t    tp_name; // typeof( st_name )
    tp_t    trait_name;
    bl_t    is_aware;

    st_s => self_buf;
    st_s => self_source;

    bcore_self_item_s => first_array_item; // !=NULL if stamp has an array; valid after parsing
    bcore_self_s => self; // created in expand_setup
    xoico_funcs_s funcs;
    xoico_wraps_s wraps;

    xoico_transient_map_s transient_map;

    private aware xoico_group_s* group;
    bcore_source_point_s source_point;

    func xoico.get_hash =
    {
        tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
        hash = bcore_tp_fold_sc( hash, o.st_name.sc );
        hash = bcore_tp_fold_sc( hash, o.self_source ? o.self_source.sc : o.self_buf ? o.self_buf.sc : "" );
        hash = bcore_tp_fold_tp( hash, o.funcs.get_hash() );
        return hash;
    };

    func xoico.get_global_name_tp = { return o.tp_name; };
    func xoico.finalize;

    func xoico.expand_setup = { return 0; };
    func xoico.expand_declaration;
    func xoico.expand_forward =
    {
        sink.push_fa( " \\\n#rn{ }BCORE_FORWARD_OBJECT( #<sc_t> );", indent, o.st_name.sc );
        return 0;
    };

    func xoico.expand_indef_declaration =
    {
        sink.push_fa( " \\\n#rn{ }  BETH_EXPAND_ITEM_#<sc_t>", indent, o.st_name.sc );
        return 0;
    };

    func xoico.expand_definition;
    func xoico.expand_init1;

    func xoico.parse;
    func :.parse_func;
    func :.parse_wrap;

    func :.make_funcs_overloadable =
    {
        foreach( m $* func in o.funcs ) func->overloadable = true;
        return 0;
    };

    func :.get_func_from_name = { return o.funcs.get_func_from_name( name ); };

    func :.get_trait_line_func_from_name =
    {
        const $* func = o.funcs.get_func_from_name( name );
        if( !func )
        {
            func = o.group.compiler.get_group( o.trait_name ).get_trait_line_func_from_name( name );
        }
        return func;
    };

    func :.push_default_funcs;

    func xoico_host.parse_name_st = { return o.group.parse_name_st( source, name ); };
    func xoico_host.compiler = { return o.group.compiler; };
    func xoico_host.cengine = { return o.group.cengine(); };
    func xoico_host.obj_type = { return o.tp_name; };
    func xoico_host.transient_map = { return o.transient_map; };

    func xoico.get_source_point = { return o.source_point; };
};

//----------------------------------------------------------------------------------------------------------------------

embed "xoico_stamp.x";

#endif // XOILA_SECTION

/**********************************************************************************************************************/

#endif // XOICO_STAMP_H
