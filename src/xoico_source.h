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

#ifndef XOICO_SOURCE_H
#define XOICO_SOURCE_H

/**********************************************************************************************************************/

#include "xoico.h"
#include "xoico_group.h"

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( xoico_source, xoico )
#ifdef XOILA_SECTION

//----------------------------------------------------------------------------------------------------------------------

stamp :s = aware :
{
    st_s name; // file name excluding directory and extension
    st_s path; // file path excluding extension
    xoico_group_s => [];

    hidden aware xoico_target_s* target;

    func xoico.expand_setup =
    {
        foreach( m $* e in o ) e.expand_setup( o ).try();
        return 0;
    };

    func (er_t push_d( m @* o, d xoico_group_s* group )) =
    {
        o.cast( m x_array* ).push_d( group );
        return 0;
    };

    func xoico.get_hash =
    {
        tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
        foreach( m xoico_group_s* e in o ) hash = bcore_tp_fold_tp( hash, e.get_hash() );
        return hash;
    };

    func xoico.parse;

    func xoico.finalize =
    {
        foreach( m $* e in o ) e.finalize( o ).try();
        return 0;
    };


    func xoico.expand_declaration =
    {
        sink.push_fa( "\n" );
        sink.push_fa( "#rn{ }/*#rn{*}*/\n", indent, sz_max( 0, 116 - indent ) );
        sink.push_fa( "#rn{ }// source: #<sc_t>.h\n", indent, o.name.sc );
        foreach( m $* e in o ) e.expand_declaration( indent, sink ).try();
        return 0;
    };

    func xoico.expand_definition =
    {
        sink.push_fa( "\n" );
        sink.push_fa( "#rn{ }/*#rn{*}*/\n", indent, sz_max( 0, 116 - indent ) );
        sink.push_fa( "#rn{ }// source: #<sc_t>.h\n", indent, o.name.sc );
        sink.push_fa( "#rn{ }##include \"#<sc_t>.h\"\n", indent, o.name.sc );
        foreach( m $* e in o ) e.expand_definition( indent, sink ).try();
        return 0;
    };

    func xoico.expand_init1 =
    {
        sink.push_fa( "\n" );
        sink.push_fa( "#rn{ }// #rn{-}\n", indent, sz_max( 0, 80 - indent ) );
        sink.push_fa( "#rn{ }// source: #<sc_t>.h\n", indent, o.name.sc );
        foreach( m $* e in o ) e.expand_init1( indent, sink ).try();
        return 0;
    };

    func xoico_group.explicit_embeddings_push =
    {
        foreach( m $* group in o ) group.explicit_embeddings_push( arr );
    };

    func xoico_host.compiler =
    {
        return o.target.compiler;
    };
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) xoico.parse = (try)
{
    m $* compiler = o.target.compiler;
    while( !source.eos() )
    {
        m xoico_group_s* group = NULL;

        if( source.parse_bl( " #?w'XOILA_DEFINE_GROUP'" ) )
        {
            group = xoico_group_s!^^;
            o.push_d( group.fork() );
            group.xoico_source = o;
            group.compiler = compiler;

            m st_s* st_trait_name = st_s!^^;
            source.parse_em_fa( " ( #name, #name", group.st_name.1, st_trait_name.1 );
            group.trait_name = compiler.entypeof( st_trait_name.sc );

            if( source.parse_bl( " #=?','" ) )
            {
                while( source.parse_bl( " #?','" ) )
                {
                    m st_s* embed_file = st_s!^;
                    source.parse_em_fa( " #string", embed_file );
                    d bcore_source* include_source = NULL;
                    xoico_embed_file_open( source, embed_file.sc, include_source.2 );
                    include_source.scope();
                    group.explicit_embeddings.push_st( embed_file );
                    group.parse( o, include_source );
                }
                source.parse_em_fa( " )" );
            }
            else
            {
                source.parse_em_fa( " )" );
                group.parse( o, source );
            }
            o.target.compiler.register_group( group );
        }
        else
        {
            source.get_u0();
        }
    }
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // XOICO_SOURCE_H
