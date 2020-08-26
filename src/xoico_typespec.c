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

er_t xoico_typespec_s_parse( xoico_typespec_s* o, bcore_source* source )
{
    BLM_INIT();
    bcore_source_point_s_set( &o->source_point, source );
    if( bcore_source_a_parse_bl_fa( source, "#?'const' " ) ) o->is_const = true;

    st_s* s = BLM_CREATE( st_s );
    if( bcore_source_a_parse_bl_fa( source, "#?':' " ) )
    {
        xoico_group_s_parse_name_recursive( o->group, s, source );
        o->type = XOICO_ENTYPEOF( s->sc );
    }
    else
    {
        if( bcore_source_a_parse_bl_fa( source, "#?'@' " ) )
        {
            o->type = XOICO_ENTYPEOF( "@" );
            if( bcore_source_a_parse_bl_fa( source, "#?'|' " ) )
            {
                XOICO_BLM_SOURCE_PARSE_FA( source, "#name ", s );
                if( s->size == 0 ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Argument: Type expected." );
                o->alt_type = XOICO_ENTYPEOF( s->sc );
            }
        }
        else
        {
            XOICO_BLM_SOURCE_PARSE_FA( source, "#name ", s );
            if( s->size == 0 ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Argument: Type expected." );
            o->type = XOICO_ENTYPEOF( s->sc );
        }
    }

    while( bcore_source_a_parse_bl_fa( source, "#?'*' " ) ) o->ref_count++;

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

tp_t xoico_typespec_s_get_hash( const xoico_typespec_s* o )
{
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
    hash = bcore_tp_fold_bl( hash, o->is_const );
    hash = bcore_tp_fold_tp( hash, o->type );
    hash = bcore_tp_fold_u3( hash, o->ref_count );
    return hash;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_typespec_s_expand( const xoico_typespec_s* o, const xoico_stamp_s* stamp, bcore_sink* sink )
{
    BLM_INIT();
    if( o->is_const ) bcore_sink_a_push_fa( sink, "const " );
    sc_t sc_type = XOICO_NAMEOF( o->type );
    if( sc_type[ 0 ] == '@' && !stamp ) sc_type = XOICO_NAMEOF( o->alt_type );

    if( sc_type[ 0 ] == '@' )
    {
        st_s* s = BLM_CREATE( st_s );
        if( !stamp )
        {
            XOICO_BLM_SOURCE_POINT_PARSE_ERR_FA
            (
                &o->source_point,
                "'@' cannot be used 'standalone' in this context.\n"
                "You may specify a compatible alternative type using directive '|' : E.g. '@|bcore_inst *"
            );
        }
        else
        {
            st_s_copy_sc( s, stamp->name.sc );
            st_s_push_sc( s, sc_type + 1 );
            bcore_sink_a_push_fa( sink, "#<sc_t>", s->sc );
        }
    }
    else
    {
        bcore_sink_a_push_fa( sink, "#<sc_t>", sc_type );
    }

    for( sz_t i = 0; i < o->ref_count; i++ ) bcore_sink_a_push_fa( sink, "*" );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

