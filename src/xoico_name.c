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

#include "xoico_name.h"
#include "xoico_group.h"

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

sc_t xoico_name_s_get_global_name_sc( const xoico_name_s* o )
{
    xoico_compiler_s* compiler = o->group->compiler;
    return xoico_compiler_s_nameof( compiler, o->name );
}

//----------------------------------------------------------------------------------------------------------------------

tp_t xoico_name_s_get_hash( const xoico_name_s* o )
{
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
    hash = bcore_tp_fold_tp( hash, o->name );
    return hash;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_name_s_parse( xoico_name_s* o, bcore_source* source )
{
    BLM_INIT();
    xoico_compiler_s* compiler = o->group->compiler;
    bcore_source_point_s_set( &o->source_point, source );

    st_s* st_name = BLM_CREATE( st_s );

    if( bcore_source_a_parse_bl_fa( source, " #?':'" ) )
    {
        st_s* name = BLM_CREATE( st_s );
        XOICO_BLM_SOURCE_PARSE_FA( source, " #name", name );
        st_s_push_fa( st_name, "#<sc_t>#<sc_t>#<sc_t>", o->group->st_name.sc, name->sc[ 0 ] ? "_" : "", name->sc );
    }
    else
    {
        XOICO_BLM_SOURCE_PARSE_FA( source, " #name", st_name );
    }
    if( st_name->size == 0 ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Name missing." );

    o->name = xoico_compiler_s_entypeof( compiler, st_name->sc );
    XOICO_BLM_SOURCE_PARSE_FA( source, " ; " );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_name_s_expand_declaration( const xoico_name_s* o, sz_t indent, bcore_sink* sink )
{
    xoico_compiler_s* compiler = o->group->compiler;
    bcore_sink_a_push_fa( sink, "#rn{ }##define TYPEOF_#<sc_t> 0x#pl16'0'{#X<tp_t>}ull\n", indent, xoico_compiler_s_nameof( compiler, o->name ), o->name );
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_name_s_expand_init1( const xoico_name_s* o, sz_t indent, bcore_sink* sink )
{
    xoico_compiler_s* compiler = o->group->compiler;
    bcore_sink_a_push_fa( sink, "#rn{ }BCORE_REGISTER_NAME( #<sc_t> );\n", indent, xoico_compiler_s_nameof( compiler, o->name ) );
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

