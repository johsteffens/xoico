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

#include "xoico_source.h"
#include "xoico_group.h"
#include "xoico_compiler.h"

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_source_s_push_group( xoico_source_s* o, xoico_group_s* group )
{
    bcore_array_a_push( ( bcore_array* )o, sr_asd( group ) );
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_source_s_parse( xoico_source_s* o, bcore_source* source )
{
    BLM_INIT();
    while( !bcore_source_a_eos( source ) )
    {
        xoico_group_s* group = NULL;

        /* deprecated */
        if( bcore_source_a_parse_bl_fa( source, "#?w'PLANT_GROUP'" ) )
        {
            BLM_INIT();
            group = BLM_CREATE( xoico_group_s );
            BLM_TRY( xoico_source_s_push_group( o, bcore_fork( group ) ) );
            group->source = o;
            XOICO_BLM_SOURCE_PARSE_FA( source, " ( #name, #name )", &group->name, &group->trait_name );
            BLM_DOWN();
        }

        /* deprecated */
        else if( bcore_source_a_parse_bl_fa( source, "#?w'BETH_PLANT_GROUP_H'" ) )
        {
            BLM_INIT();
            group = BLM_CREATE( xoico_group_s );
            BLM_TRY( xoico_source_s_push_group( o, bcore_fork( group ) ) );
            group->source = o;
            XOICO_BLM_SOURCE_PARSE_FA( source, " ( #name, #name, #name )", NULL, &group->name, &group->trait_name );
            BLM_DOWN();
        }

        /* deprecated */
        else if( bcore_source_a_parse_bl_fa( source, "#?w'BETH_PLANT_DEFINE_GROUP'" ) )
        {
            BLM_INIT();
            group = BLM_CREATE( xoico_group_s );
            BLM_TRY( xoico_source_s_push_group( o, bcore_fork( group ) ) );
            group->source = o;
            XOICO_BLM_SOURCE_PARSE_FA( source, " ( #name, #name )", &group->name, &group->trait_name );
            BLM_DOWN();
        }

        /* deprecated */
        else if( bcore_source_a_parse_bl_fa( source, "#?w'XOI_DEFINE_GROUP'" ) )
        {
            BLM_INIT();
            group = BLM_CREATE( xoico_group_s );
            BLM_TRY( xoico_source_s_push_group( o, bcore_fork( group ) ) );
            group->source = o;
            XOICO_BLM_SOURCE_PARSE_FA( source, " ( #name, #name )", &group->name, &group->trait_name );
            BLM_DOWN();
        }

        else if( bcore_source_a_parse_bl_fa( source, "#?w'XOILA_DEFINE_GROUP'" ) )
        {
            BLM_INIT();
            group = BLM_CREATE( xoico_group_s );
            BLM_TRY( xoico_source_s_push_group( o, bcore_fork( group ) ) );
            group->source = o;
            XOICO_BLM_SOURCE_PARSE_FA( source, " ( #name, #name )", &group->name, &group->trait_name );
            BLM_DOWN();
        }

        if( group )
        {
            if( group->trait_name.size == 0 ) st_s_copy_sc( &group->trait_name, "bcore_inst" );
            BLM_TRY( xoico_group_s_parse( group, source ) );
            o->hash = bcore_tp_fold_tp( o->hash, group->hash );
            BLM_TRY( xoico_compiler_s_group_register( o->target->compiler, group, source ) );
        }
        else
        {
            bcore_source_a_get_u0( source );
        }
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_source_s_finalize( xoico_source_s* o )
{
    BLM_INIT();
    for( sz_t i = 0; i < o->size; i++ ) BLM_TRY( xoico_group_s_finalize( o->data[ i ] ) );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_source_s_expand_declaration( const xoico_source_s* o, sz_t indent, bcore_sink* sink )
{
    BLM_INIT();
    bcore_sink_a_push_fa( sink, "\n" );
    bcore_sink_a_push_fa( sink, "#rn{ }/*#rn{*}*/\n", indent, sz_max( 0, 116 - indent ) );
    bcore_sink_a_push_fa( sink, "#rn{ }// source: #<sc_t>.h\n", indent, o->name.sc );
    for( sz_t i = 0; i < o->size; i++ ) BLM_TRY( xoico_group_s_expand_declaration( o->data[ i ], indent, sink ) );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_source_s_expand_definition( const xoico_source_s* o, sz_t indent, bcore_sink* sink )
{
    BLM_INIT();
    bcore_sink_a_push_fa( sink, "\n" );
    bcore_sink_a_push_fa( sink, "#rn{ }/*#rn{*}*/\n", indent, sz_max( 0, 116 - indent ) );
    bcore_sink_a_push_fa( sink, "#rn{ }// source: #<sc_t>.h\n", indent, o->name.sc );
    bcore_sink_a_push_fa( sink, "#rn{ }##include \"#<sc_t>.h\"\n", indent, o->name.sc );
    for( sz_t i = 0; i < o->size; i++ ) BLM_TRY( xoico_group_s_expand_definition( o->data[ i ], indent, sink ) );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_source_s_expand_init1( const xoico_source_s* o, sz_t indent, bcore_sink* sink )
{
    BLM_INIT();
    bcore_sink_a_push_fa( sink, "\n" );
    bcore_sink_a_push_fa( sink, "#rn{ }// #rn{-}\n", indent, sz_max( 0, 80 - indent ) );
    bcore_sink_a_push_fa( sink, "#rn{ }// source: #<sc_t>.h\n", indent, o->name.sc );
    for( sz_t i = 0; i < o->size; i++ ) BLM_TRY( xoico_group_s_expand_init1( o->data[ i ], indent, sink ) );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

