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

signature er_t parse( mutable, bcore_source* source );
signature er_t finalize( mutable );
signature er_t expand_declaration( const, sz_t indent, bcore_sink* sink );
signature er_t expand_definition(  const, sz_t indent, bcore_sink* sink );
signature er_t expand_init1(       const, sz_t indent, bcore_sink* sink );

stamp : = aware :
{
    st_s name; // file name excluding directory and extension
    st_s path; // file path excluding extension
    xoico_group_s => [];

    hidden aware xoico_target_s* target;

    func xoico.expand_setup =
    {
        foreach( $* e in o ) e.expand_setup().try();
        return 0;
    };

    func (er_t push_d( mutable, xoico_group_s* group )) =
    {
        o.cast( bcore_array* ).push( sr_asd( group ) );
        return 0;
    };

    func xoico.get_hash =
    {
        tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
        foreach( xoico_group_s* e in o ) hash = bcore_tp_fold_tp( hash, e.get_hash() );
        return hash;
    };

    func :.parse;

    func :.finalize =
    {
        foreach( $* e in o ) e.finalize().try();
        return 0;
    };


    func :.expand_declaration =
    {
        sink.push_fa( "\n" );
        sink.push_fa( "#rn{ }/*#rn{*}*/\n", indent, sz_max( 0, 116 - indent ) );
        sink.push_fa( "#rn{ }// source: #<sc_t>.h\n", indent, o.name.sc );
        foreach( $* e in o ) e.expand_declaration( indent, sink ).try();
        return 0;
    };

    func :.expand_definition =
    {
        sink.push_fa( "\n" );
        sink.push_fa( "#rn{ }/*#rn{*}*/\n", indent, sz_max( 0, 116 - indent ) );
        sink.push_fa( "#rn{ }// source: #<sc_t>.h\n", indent, o.name.sc );
        sink.push_fa( "#rn{ }##include \"#<sc_t>.h\"\n", indent, o.name.sc );
        foreach( $* e in o ) e.expand_definition( indent, sink ).try();
        return 0;
    };

    func :.expand_init1 =
    {
        sink.push_fa( "\n" );
        sink.push_fa( "#rn{ }// #rn{-}\n", indent, sz_max( 0, 80 - indent ) );
        sink.push_fa( "#rn{ }// source: #<sc_t>.h\n", indent, o.name.sc );
        foreach( $* e in o ) e.expand_init1( indent, sink ).try();
        return 0;
    };

};

//----------------------------------------------------------------------------------------------------------------------

func (:) :.parse = (try)
{
    while( !source.eos() )
    {
        xoico_group_s* group = NULL;

        if( source.parse_bl( " #?w'XOILA_DEFINE_GROUP'" ) )
        {
            group = xoico_group_s!.scope();
            o.push_d( group.fork() );
            group.xoico_source = o;
            group.compiler = o.target.compiler;
            source.parse_em_fa( " ( #name, #name", group.st_name.1, group.trait_name.1 );
            if( source.parse_bl( "#?','" ) )
            {
                st_s* include_file = st_s!.scope();
                source.parse_em_fa( " #string )", include_file );
                o.target.explicit_embeddings.push_st( include_file );
                bcore_source* include_source = NULL;
                xoico_embed_file_open( source, include_file.sc, include_source.2 );
                include_source.scope();
                group.parse( include_source );
            }
            else
            {
                source.parse_em_fa( " )" );
                group.parse( source );
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
