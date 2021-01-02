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
    hash = bcore_tp_fold_tp( hash, o.arg_o ? o.arg_o.get_hash() : 0 );
    hash = bcore_tp_fold_tp( hash, o.args.get_hash() );
    return hash;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) :.set_global_name = (try)
{
    o.base_name = host.obj_type();
    o.global_name = host.entypeof( st_s_create_fa( "#<sc_t>_#<sc_t>", host.nameof( o.base_name ), host.nameof( o.name ) ).scope().sc );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) xoico.parse = (try)
{
    $* compiler = host.compiler();
    $* name_buf = st_s!^^;

    if( source.parse_bl( " #?'extending'" ) )
    {
        tp_t tp_name = 0;
        host.parse_name_tp( source, tp_name.1 );
        const $* signature = compiler.get_signature( tp_name );
        if( !signature ) return source.parse_error_fa( "Could not find predefined signature '#<sc_t>'.", host.nameof( tp_name ) );
        o.copy( signature );
        o.source_point.set( source );
        source.parse_em_fa( " #name", name_buf );
        if( name_buf.size == 0 ) return source.parse_error_fa( "Signature name missing." );
        o.name = compiler.entypeof( name_buf.sc );
        source.parse_em_fa( " (" );
        o.args.append( host, source );
        source.parse_em_fa( " )" );
    }
    else
    {
        o.source_point.set( source );
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
            st_s* s = st_s!^^;
            source.parse_em_fa( "#name ", s );
            if( s->size == 0 ) source.parse_error_fa( "Transient class: Identifier expected." );
            transient_class = compiler.entypeof( s->sc );
            source.parse_em_fa( " ) " );
        }

        tp_t tp_arg_o = 0;
        if( source.parse_bl( " #?'mutable' " ) )
        {
            tp_arg_o = TYPEOF_mutable;
        }
        else if( source.parse_bl( " #=?'const'" ) )
        {
            source.parse_em_fa( "const " );
            if( source.parse_bl( "#?([0]==','||[0]==')')" ) )
            {
                tp_arg_o = TYPEOF_const;
            }
            else
            {
                // reset index (non-member functions)
                source.set_index( index );
            }
        }

        if( tp_arg_o )
        {
            if( !source.parse_bl( " #=?')'" ) ) source.parse_em_fa( ", " );
            o.arg_o =< xoico_arg_s!;
            o.arg_o.typespec.type = TYPEOF_type_object;
            o.arg_o.typespec.flag_const = ( tp_arg_o == TYPEOF_const );
            o.arg_o.typespec.indirection = 1;
            o.arg_o.typespec.transient_class = transient_class;
            o.arg_o.name = TYPEOF_o;
        }

        o.args.parse( host, source );
        source.parse_em_fa( " )" );
    }

    o.set_global_name( host );

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) :.expand_declaration = (try)
{
    o.expand_ret( host, sink );
    sink.push_fa( " #<sc_t>( ", sc_func_global_name );

    if( o.arg_o )
    {
        o.arg_o.expand( host, sink );
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
