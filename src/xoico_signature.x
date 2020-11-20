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

func (:) xoico.get_hash =
{
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o._ );
    hash = bcore_tp_fold_tp( hash, o.global_name );
    hash = bcore_tp_fold_tp( hash, o.typespec_ret.get_hash() );
    hash = bcore_tp_fold_tp( hash, o.args.get_hash() );
    hash = bcore_tp_fold_tp( hash, o.arg_o );
    return hash;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico.parse =
{ try {
    o.source_point.set( source );
    $* compiler = o.group.compiler;

    $* name_buf = st_s!.scope();

    if( source.parse_bl_fa( " #?'extending'" ) )
    {
        o.group.parse_name( name_buf, source );
        tp_t tp_name = compiler.entypeof( name_buf.sc );

        const $* signature = compiler.get_signature( tp_name );
        if( !signature )
        {
            return source.parse_error_fa( "Could not find predefined signature '#<sc_t>'.", name_buf.sc );
        }

        o.typespec_ret.copy( signature.typespec_ret );
        o.args.copy( signature.args );
        o.arg_o = signature.arg_o;

        source.parse_fa( " #name", name_buf );
        if( name_buf.size == 0 ) return source.parse_error_fa( "Signature name missing." );
        o.name = compiler.entypeof( name_buf.sc );

        source.parse_fa( " (" );
        o.args.append( source );
        source.parse_fa( " )" );
    }
    else
    {
        o.typespec_ret.parse( o.group, source );
        o.typespec_ret.flag_addressable = false;

        // get name
        source.parse_fa( " #name", name_buf );
        o.name = compiler.entypeof( name_buf.sc );

        // get args
        ASSERT( o.group );
        o.args.group = o.group;

        source.parse_fa( " (" );
        if( source.parse_bl_fa(  " #?'plain' " ) ) source.parse_error_fa( "Use of 'plain' is deprecated. Simply omit this argument." );

        o.arg_o = 0;
        if( source.parse_bl_fa( " #?'mutable' " ) )
        {
            o.arg_o = TYPEOF_mutable;
        }
        else if( source.parse_bl_fa( " #=?'const'" ) )
        {
            sz_t index = source.get_index();
            source.parse_fa( "const " );
            if( source.parse_bl_fa( "#?([0]==','||[0]==')')" ) )
            {
                o.arg_o = TYPEOF_const;
            }
            else
            {
                source.set_index( index );
            }
        }

        if( o.arg_o )
        {
            if( !source.parse_bl_fa( " #=?')'" ) ) source.parse_fa( ", " );
        }

        o.args.parse( source );
        source.parse_fa( " )" );
    }

    sc_t sc_name = compiler.nameof( o.name );

    if( o.stamp )
    {
        name_buf.copy_fa( "#<sc_t>_#<sc_t>", o.stamp.st_name.sc, sc_name );
    }
    else
    {
        name_buf.copy_fa( "#<sc_t>_#<sc_t>", o.group.st_name.sc, sc_name );
    }

    o.global_name = compiler.entypeof( name_buf.sc );
    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:) :.expand_declaration =
{ try {
    sc_t sc_name = stamp ? stamp.st_name.sc : o.group.st_name.sc;
    o.typespec_ret.expand( o.group, sc_name, sink );
    sink.push_fa( " #<sc_t>( ", sc_func_global_name );

    if( o.arg_o )
    {
        sink.push_fa( "#<sc_t>", ( o.arg_o == TYPEOF_mutable ) ? "" : "const " );
        sink.push_fa( "#<sc_t>* o", sc_name );
        o.args.expand( false, sc_name, sink );
        sink.push_fa( " )" );
    }
    else
    {
        if( o.args.size > 0 )
        {
            o.args.expand( true, sc_name, sink );
        }
        else
        {
            sink.push_fa( "void" );
        }
        sink.push_fa( " )" );
    }
    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
