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

#include "xoico_arg.h"
#include "xoico_group.h"
#include "xoico_stamp.h"
#include "xoico_compiler.h"

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_typespec_s_parse( xoico_typespec_s* o, xoico_group_s* group, bcore_source* source )
{
    BLM_INIT();

    xoico_typespec_s_reset( o );

    while( !bcore_source_a_eos( source ) )
    {
        if     ( bcore_source_a_parse_bl_fa( source, " #?'const'"    ) ) o->flag_const = true;
        else if( bcore_source_a_parse_bl_fa( source, " #?'static'"   ) ) o->flag_static = true;
        else if( bcore_source_a_parse_bl_fa( source, " #?'volatile'" ) ) o->flag_volatile = true;
        else if( bcore_source_a_parse_bl_fa( source, " #?'keep'"     ) ) o->flag_keep = true;
        else break;
    }

    bcore_source_a_parse_fa( source, " " );

    xoico_compiler_s* compiler = group->compiler;

    st_s* s = BLM_CREATE( st_s );
    if( bcore_source_a_parse_bl_fa( source, "#?':' " ) )
    {
        xoico_group_s_parse_name_recursive( group, s, source );
        o->type = xoico_compiler_s_entypeof( compiler, s->sc );
    }
    else if( bcore_source_a_parse_bl_fa( source, "#?'@' " ) )
    {
        o->type = TYPEOF_type_object;
    }
    else if( bcore_source_a_parse_bl_fa( source, "#?'$' " ) )
    {
        o->type = TYPEOF_type_deduce;
    }
    else
    {
        XOICO_BLM_SOURCE_PARSE_FA( source, "#name ", s );
        if( s->size == 0 ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Argument: Type expected." );
        o->type = xoico_compiler_s_entypeof( compiler, s->sc );
    }

    while( bcore_source_a_parse_bl_fa( source, "#?'*' " ) ) o->indirection++;

    if( bcore_source_a_parse_bl_fa( source, " #?'restrict' " ) ) o->flag_restrict = true;

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

tp_t xoico_typespec_s_get_hash( const xoico_typespec_s* o )
{
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
    hash = bcore_tp_fold_bl( hash, o->flag_const );
    hash = bcore_tp_fold_bl( hash, o->flag_static );
    hash = bcore_tp_fold_bl( hash, o->flag_volatile );
    hash = bcore_tp_fold_bl( hash, o->flag_restrict );
    hash = bcore_tp_fold_bl( hash, o->flag_keep );
    hash = bcore_tp_fold_tp( hash, o->type );
    hash = bcore_tp_fold_u3( hash, o->indirection );
    return hash;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_typespec_s_relent( xoico_typespec_s* o, xoico_group_s* group, tp_t tp_obj_type )
{
    BLM_INIT();
    if( o->type == TYPEOF_type_object ) o->type = tp_obj_type;
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_typespec_s_expand( const xoico_typespec_s* o, xoico_group_s* group, sc_t sc_obj_type, bcore_sink* sink )
{
    BLM_INIT();
    xoico_compiler_s* compiler = group->compiler;

    tp_t type = o->type;

    if( type == TYPEOF_type_object )
    {
        if( !sc_obj_type ) ERR_fa( "Cannot resolve 'type_object' at this point." );
        type = xoico_compiler_s_entypeof( compiler, sc_obj_type );
    }
    else if( type == TYPEOF_type_deduce )
    {
        ERR_fa( "Cannot resolve 'type_deduce' at this point." );
    }

    st_s* st_type = BLM_A_PUSH( st_s_create_sc( xoico_compiler_s_nameof( compiler, type ) ) );

    sc_t sc_type = st_type->sc;
    if( o->flag_static   ) bcore_sink_a_push_fa( sink, "static " );
    if( o->flag_const    ) bcore_sink_a_push_fa( sink, "const " );
    if( o->flag_volatile ) bcore_sink_a_push_fa( sink, "volatile " );
    bcore_sink_a_push_fa( sink, "#<sc_t>", sc_type );

    for( sz_t i = 0; i < o->indirection; i++ ) bcore_sink_a_push_fa( sink, "*" );
    if( o->flag_restrict ) bcore_sink_a_push_fa( sink, "restrict " );

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

