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

#include "xoico_forward.h"
#include "xoico_group.h"

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

sc_t xoico_forward_s_get_global_name_sc( const xoico_forward_s* o )
{
    return o->name.sc;
}

//----------------------------------------------------------------------------------------------------------------------

tp_t xoico_forward_s_get_hash( const xoico_forward_s* o )
{
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
    hash = bcore_tp_fold_sc( hash, o->name.sc );
    return hash;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_forward_s_parse( xoico_forward_s* o, bcore_source* source )
{
    BLM_INIT();
    bcore_source_point_s_set( &o->source_point, source );

    if( bcore_source_a_parse_bl_fa( source, " #?':'" ) )
    {
        st_s* name = BLM_CREATE( st_s );
        XOICO_BLM_SOURCE_PARSE_FA( source, " #name", name );
        st_s_push_fa( &o->name, "#<sc_t>#<sc_t>#<sc_t>", o->group->name.sc, name->sc[ 0 ] ? "_" : "", name->sc );
    }
    else
    {
        XOICO_BLM_SOURCE_PARSE_FA( source, " #name", &o->name );
    }
    if( o->name.size == 0 ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Feature: Name missing." );
    XOICO_BLM_SOURCE_PARSE_FA( source, " ; " );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_forward_s_expand_declaration( const xoico_forward_s* o, sz_t indent, bcore_sink* sink )
{
    bcore_sink_a_push_fa( sink, "#rn{ }##define TYPEOF_#<sc_t> 0x#pl16'0'{#X<tp_t>}ull\n",  indent, o->name.sc, typeof( o->name.sc ) );
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_forward_s_expand_forward( const xoico_forward_s* o, sz_t indent, bcore_sink* sink )
{
    bcore_sink_a_push_fa( sink, " \\\n#rn{ }BCORE_FORWARD_OBJECT( #<sc_t> );", indent, o->name.sc );
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_forward_s_expand_init1( const xoico_forward_s* o, sz_t indent, bcore_sink* sink )
{
//    bcore_sink_a_push_fa( sink, "#rn{ }BCORE_REGISTER_NAME( #<sc_t> );\n", indent, o->name.sc );
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

