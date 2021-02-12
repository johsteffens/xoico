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

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

signature er_t parse_h( m @* o, c xoico_host* host, m bcore_source* source );
signature er_t parse_x( m @* o, c xoico_host* host, m bcore_source* source, sc_t group_name, sc_t trait_name );

//----------------------------------------------------------------------------------------------------------------------

stamp :s = aware :
{
    st_s name; // file name excluding directory and extension
    st_s path; // file path excluding extension
    st_s ext;  // file extension ( "h" or "x" )
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

    func :.parse_h;
    func :.parse_x;

    func xoico.finalize =
    {
        foreach( m $* e in o ) e.finalize( o ).try();
        return 0;
    };


    func xoico.expand_declaration =
    {
        sink.push_fa( "\n" );
        sink.push_fa( "#rn{ }/*#rn{*}*/\n", indent, sz_max( 0, 116 - indent ) );
        sink.push_fa( "#rn{ }// source: #<sc_t>.#<sc_t>\n", indent, o.name.sc, o.ext.sc );
        foreach( m $* e in o ) e.expand_declaration( indent, sink ).try();
        return 0;
    };

    func xoico.expand_definition =
    {
        sink.push_fa( "\n" );
        sink.push_fa( "#rn{ }/*#rn{*}*/\n", indent, sz_max( 0, 116 - indent ) );
        sink.push_fa( "#rn{ }// source: #<sc_t>.#<sc_t>\n", indent, o.name.sc, o.ext.sc );

        if( o.ext.equal_sc( "h" ) )
        {
            sink.push_fa( "#rn{ }##include \"#<sc_t>.#<sc_t>\"\n", indent, o.name.sc, o.ext.sc );
        }
        foreach( m $* e in o ) e.expand_definition( indent, sink ).try();
        return 0;
    };

    func xoico.expand_init1 =
    {
        sink.push_fa( "\n" );
        sink.push_fa( "#rn{ }// #rn{-}\n", indent, sz_max( 0, 80 - indent ) );
        sink.push_fa( "#rn{ }// source: #<sc_t>.#<sc_t>\n", indent, o.name.sc, o.ext.sc );
        foreach( m $* e in o ) e.expand_init1( indent, sink ).try();
        return 0;
    };

    func xoico.expand_manifesto =
    {
        st_s^ buf;
        foreach( m $* e in o ) e.expand_manifesto( host, indent, buf ).try();

        if( buf.size > 0 )
        {
//            sink.push_fa( "\n" );
//            sink.push_fa( "#rn{ }// #rn{-}\n", indent, sz_max( 0, 80 - indent ) );
//            sink.push_fa( "#rn{ }// source: #<sc_t>.#<sc_t>\n", indent, o.name.sc, o.ext.sc );
            sink.push_sc( buf.sc );
        }

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

func (:s) :.parse_h = (try)
{
    m $* compiler = o.target.compiler;
    while( !source.eos() )
    {
        if( source.parse_bl( " #?w'XOILA_DEFINE_GROUP'" ) )
        {
            m xoico_group_s* group = xoico_group_s!^;
            o.push_d( group.fork() );
            group.xoico_source = o;
            group.compiler = compiler;

            st_s^ st_trait_name;
            source.parse_em_fa( " ( #name , #name", group.st_name.1, st_trait_name.1 );
            group.trait_name = compiler.entypeof( st_trait_name.sc );

            if( source.parse_bl( " #=?','" ) )
            {
                while( source.parse_bl( " #?','" ) )
                {
                    m st_s* embed_file = st_s!^;
                    source.parse_em_fa( " #string", embed_file );
                    d bcore_source* embed_source = NULL;
                    xoico_embed_file_open( source, embed_file.sc, embed_source.2 );
                    embed_source^^;
                    group.explicit_embeddings.push_st( embed_file );
                    group.parse( o, embed_source );
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

func (:s) :.parse_x = (try)
{
    m $* compiler = o.target.compiler;
    m xoico_group_s* group = xoico_group_s!^;
    o.push_d( group.fork() );

    st_s^ st_group_name.copy_sc( group_name );
    st_s^ st_trait_name.copy_sc( trait_name );

    group.xoico_source = o;
    group.compiler = compiler;
    group.st_name.copy( st_group_name );
    group.trait_name = compiler.entypeof( st_trait_name.sc );
    group.is_manifesto = true;
    group.parse( o, source );
    compiler.register_group( group );

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
