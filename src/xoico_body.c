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

#include "xoico_body.h"
#include "xoico_group.h"
#include "xoico_stamp.h"
#include "xoico_signature.h"
#include "xoico_compiler.h"
#include "xoico_caleph.h"

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

/// stamp should be NULL when body is not parsed inside a stamp
er_t xoico_body_s_parse( xoico_body_s* o, bcore_source* source )
{
    BLM_INIT();
    if( !o->group ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Body has no group assigned." );

    st_s* string = BLM_CREATE( st_s );

    bcore_source_point_s_set( &o->source_point, source );

    if( !bcore_source_a_parse_bl_fa( source, " #=?'='" ) )
    {
        XOICO_BLM_SOURCE_PARSE_FA( source, " #name", string );
        if( string->size == 0 ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Body name expected." );
        st_s_push_fa( &o->name, "#<sc_t>", string->sc );
    }

    XOICO_BLM_SOURCE_PARSE_FA( source, " =" );

    BLM_TRY( xoico_body_s_parse_expression( o, source ) );

    st_s_copy_fa( &o->global_name, "#<sc_t>_#<sc_t>", o->group->st_name.sc, o->name.sc );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_body_s_finalize( xoico_body_s* o )
{
    /* nothing to do */
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_body_s_expand( const xoico_body_s* o, const xoico_signature_s* signature, sz_t indent, bcore_sink* sink )
{
    BLM_INIT();

    const st_s* final_code = NULL;
    st_s* st_out = BLM_CREATE( st_s );

    xoico_cengine* cengine = o->group->xoico_source->target->cengine;

    ASSERT( cengine );

    if( o->code )
    {
        if( !o->group ) XOICO_BLM_SOURCE_POINT_PARSE_ERR_FA( &o->source_point, "Body has no group assigned." );
        BLM_TRY( xoico_cengine_a_translate( cengine, o, signature, ( bcore_sink* )st_out ) )
        final_code = st_out;
    }

    if( o->go_inline )
    {
        bcore_sink_a_push_fa( sink, "{#<sc_t>}", final_code->sc );
    }
    else
    {
        bcore_sink_a_push_fa( sink, "{\n#rn{ }", indent + 4 );
        for( sz_t i = 0; i < final_code->size; i++ )
        {
            char c = final_code->sc[ i ];
            bcore_sink_a_push_char( sink, c );
            if( c == '\n' ) bcore_sink_a_push_fa( sink, "#rn{ }", indent + 4 );
        }
        bcore_sink_a_push_fa( sink, "\n#rn{ }}", indent );
    }

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

