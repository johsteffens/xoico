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

er_t xoico_arg_s_parse( xoico_arg_s* o, bcore_source* source )
{
    BLM_INIT();
    bcore_source_point_s_set( &o->source_point, source );
    BLM_TRY( xoico_typespec_s_parse( &o->typespec, o->group, source ) );

    if( o->typespec.type == TYPEOF_void && o->typespec.indirection == 0 )
    {
        XOICO_BLM_SOURCE_POINT_PARSE_ERR_FA( &o->source_point, "'void' is misplaced here." );
    }

    st_s* s = BLM_CREATE( st_s );

    XOICO_BLM_SOURCE_PARSE_FA( source, "#name ", s );
    if( s->size == 0 ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Argument: Name expected." );

    o->name = XOICO_ENTYPEOF( s->sc );

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

tp_t xoico_arg_s_get_hash( const xoico_arg_s* o )
{
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
    hash = bcore_tp_fold_tp( hash, xoico_typespec_s_get_hash( &o->typespec ) );
    hash = bcore_tp_fold_tp( hash, o->name );
    return hash;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_arg_s_expand_name( const xoico_arg_s* o, bcore_sink* sink )
{
    bcore_sink_a_push_fa( sink, "#<sc_t>", XOICO_NAMEOF( o->name ) );
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_arg_s_relent( xoico_arg_s* o, tp_t tp_obj_type )
{
    return xoico_typespec_s_relent( &o->typespec, o->group, tp_obj_type );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_arg_s_expand( const xoico_arg_s* o, sc_t sc_obj_type, bcore_sink* sink )
{
    BLM_INIT();
    BLM_TRY( xoico_typespec_s_expand( &o->typespec, o->group, sc_obj_type, sink ) );
    bcore_sink_a_push_fa( sink, " " );
    xoico_arg_s_expand_name( o, sink );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

