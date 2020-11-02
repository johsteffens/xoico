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

        if( bcore_source_a_parse_bl_fa( source, " #?w'XOILA_DEFINE_GROUP'" ) )
        {
            BLM_INIT();
            group = BLM_CREATE( xoico_group_s );
            BLM_TRY( xoico_source_s_push_group( o, bcore_fork( group ) ) );
            group->source = o;
            XOICO_BLM_SOURCE_PARSE_FA( source, " ( #name, #name", &group->st_name, &group->trait_name );
            if( bcore_source_a_parse_bl_fa( source, "#?','" ) )
            {
                st_s* include_file = BLM_CREATE( st_s );
                XOICO_BLM_SOURCE_PARSE_FA( source, " #string )", include_file );
                bcore_arr_st_s_push_st( &o->target->explicit_embeddings, include_file );
                bcore_source* include_source = NULL;
                BLM_TRY( xoico_embed_file_open( source, include_file->sc, &include_source ) );
                BLM_TRY( xoico_group_s_parse( group, BLM_A_PUSH( include_source ) ) );
            }
            else
            {
                XOICO_BLM_SOURCE_PARSE_FA( source, " )" );
                BLM_TRY( xoico_group_s_parse( group, source ) );
            }
            BLM_TRY( xoico_compiler_s_register_group( o->target->compiler, group, source ) );
            o->hash = bcore_tp_fold_tp( o->hash, group->hash );
            BLM_DOWN();
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

er_t xoico_source_s_expand_setup( xoico_source_s* o )
{
    BLM_INIT();
    for( sz_t i = 0; i < o->size; i++ ) BLM_TRY( xoico_group_s_expand_setup( o->data[ i ] ) );
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

