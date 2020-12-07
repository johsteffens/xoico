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

func (:s) xoico.get_hash =
{
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o._ );
    hash = bcore_tp_fold_tp( hash, o.global_name );
    hash = bcore_tp_fold_tp( hash, o.typespec_ret.get_hash() );
    hash = bcore_tp_fold_tp( hash, o.args.get_hash() );
    hash = bcore_tp_fold_bl( hash, o.typed );
    hash = bcore_tp_fold_tp( hash, o.arg_o );
    return hash;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) xoico.parse = (try)
{
    o.source_point.set( source );
    $* compiler = host.compiler();

    $* name_buf = st_s!.scope();

    if( source.parse_bl( " #?'extending'" ) )
    {
        host.parse_name( source, name_buf );
        tp_t tp_name = compiler.entypeof( name_buf.sc );

        const $* signature = compiler.get_signature( tp_name );
        if( !signature )
        {
            return source.parse_error_fa( "Could not find predefined signature '#<sc_t>'.", name_buf.sc );
        }

        o.typespec_ret.copy( signature.typespec_ret );
        o.args.copy( signature.args );
        o.arg_o = signature.arg_o;
        o.typed = signature.typed;

        source.parse_em_fa( " #name", name_buf );
        if( name_buf.size == 0 ) return source.parse_error_fa( "Signature name missing." );
        o.name = compiler.entypeof( name_buf.sc );

        source.parse_em_fa( " (" );
        o.args.append( host, source );
        source.parse_em_fa( " )" );
    }
    else
    {
        o.typespec_ret.parse( host, source );
        o.typespec_ret.flag_addressable = false;

        // get name
        source.parse_em_fa( " #name", name_buf );
        o.name = compiler.entypeof( name_buf.sc );

        source.parse_em_fa( " (" );
        if( source.parse_bl(  " #?'plain' " ) ) source.parse_error_fa( "Use of 'plain' is deprecated. Simply omit this argument." );

        sz_t index = source.get_index();

        tp_t transient_class = 0;
        if( source.parse_bl( "#?'(' " ) )
        {
            st_s* s = st_s!.scope();
            source.parse_em_fa( "#name ", s );
            if( s->size == 0 ) source.parse_error_fa( "Transient class: Identifier expected." );
            transient_class = compiler.entypeof( s->sc );
            source.parse_em_fa( " ) " );
        }


        if( source.parse_bl( " #?'typed' " ) )
        {
            o.typed = true;
        }

        o.arg_o = 0;
        if( source.parse_bl( " #?'mutable' " ) )
        {
            o.arg_o = TYPEOF_mutable;
        }
        else if( source.parse_bl( " #=?'const'" ) )
        {
            source.parse_em_fa( "const " );
            if( source.parse_bl( "#?([0]==','||[0]==')')" ) )
            {
                o.arg_o = TYPEOF_const;
            }
            else
            {
                // reset index (non-member functions)
                source.set_index( index );
            }
        }

        if( o.arg_o )
        {
            if( !source.parse_bl( " #=?')'" ) ) source.parse_em_fa( ", " );
            o.arg_o_transient_class = transient_class;
        }
        else if( o.typed )
        {
            source.parse_error_fa( "'typed' can not be used on plain functions." );
        }

        o.args.parse( host, source );
        source.parse_em_fa( " )" );
    }

    sc_t sc_name = compiler.nameof( o.name );
    name_buf.copy_fa( "#<sc_t>_#<sc_t>", compiler.nameof( host.obj_type() ), sc_name );

    o.global_name = compiler.entypeof( name_buf.sc );

    if( o.typespec_ret.transient_class )
    {
        if( o.typespec_ret.type == TYPEOF_void && o.typespec_ret.indirection == 0 )
        {
            source.parse_error_fa( "'void' can not be a transient type." );
        }
    }

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) :.expand_declaration = (try)
{
    sc_t sc_name = host.compiler().nameof( host.obj_type() );
    o.typespec_ret.expand( host, sink );
    sink.push_fa( " #<sc_t>( ", sc_func_global_name );

    if( o.arg_o )
    {
        if( o.typed ) sink.push_sc( "tp_t t, " );
        sink.push_fa( "#<sc_t>", ( o.arg_o == TYPEOF_mutable ) ? "" : "const " );
        sink.push_fa( "#<sc_t>* o", sc_name );
        o.args.expand( host, false, sink );
        sink.push_fa( " )" );
    }
    else
    {
        if( o.args.size > 0 )
        {
            o.args.expand( host, true, sink );
        }
        else
        {
            sink.push_fa( "void" );
        }
        sink.push_fa( " )" );
    }
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
