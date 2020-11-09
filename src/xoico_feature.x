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
    hash = bcore_tp_fold_tp( hash, o.signature.get_hash() );
    hash = bcore_tp_fold_tp( hash, o.default_body ? o.default_body.get_hash() : 0 );
    hash = bcore_tp_fold_bl( hash, o.strict );
    hash = bcore_tp_fold_bl( hash, o.flag_p );
    hash = bcore_tp_fold_bl( hash, o.flag_t );
    hash = bcore_tp_fold_bl( hash, o.flag_a );
    hash = bcore_tp_fold_bl( hash, o.flag_r );
    return hash;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico.parse =
{ try {
    xoico_compiler_s* compiler = o.group.compiler;

    o.source_point.set( source );
    o.strict = source.parse_bl_fa( " #?w'strict' " );

    if( source.parse_bl_fa( " #?|'|" ) )
    {
        st_s* flags = st_s!.scope();
        try( source.parse_em_fa( " #until'''", flags ) );
        for( sz_t i = 0; i < flags.size; i++ )
        {
            switch( flags.data[ i ] )
            {
                case 'p': o.flag_p = true; break;
                case 't': o.flag_t = true; break;
                case 'a': o.flag_a = true; break;
                case 'r': o.flag_r = true; break;
                default: return source.parse_error_fa( "Feature: Flag '#<char>' not handled. Choose from 'ptar'.", flags.[ i ] );
            }
        }
        try( source.parse_em_fa( "' " ) );
    }
    else
    {
        /// the default feature is an aware one
        o.flag_a = true;
    }

    xoico_signature_s* signature = o.signature;

    signature.group = o.group;
    signature.parse( source );

    if( !signature.arg_o )
    {
        return source.parse_error_fa( "Feature: The first argument must be 'mutable' or 'const'." );
    }

    if( source.parse_bl_fa( " #?'=' " ) )
    {
        if( source.parse_bl_fa( " #=?'{' " ) )
        {
            if( o.strict ) return source.parse_error_fa( "Feature is 'strict'. Default function would have no effect." );
            o.default_body = xoico_body_s!;
            o.default_body.set_group( o.group );
            o.default_body.source_point.set( source );
            o.default_body.parse_expression( source );
            o.st_default_func_name.copy_fa( "#<sc_t>_default", compiler.nameof( o.signature.name ) );
        }
        else
        {
            if( o.strict )  return source.parse_error_fa( "Feature is 'strict'. Default function would have no effect." );
            try( source.parse_em_fa( " #name ", &o.st_default_func_name ) );
            if( o.st_default_func_name.size == 0 ) return source.parse_error_fa( "Feature: Default function name expected." );
            if( o.st_default_func_name.equal_sc( compiler.nameof( o.signature.name ) ) )
            {
                return source.parse_error_fa( "Feature: Default function name must differ from feature name." );
            }
        }
    }

    try( source.parse_em_fa( " ; " ) );

    sc_t sc_name = compiler.nameof( o.signature.name );
    sc_t sc_group_name = o.group.st_name.sc;

    if( o.flag_a )
    {
        o.func_a = xoico_func_s!;
        o.func_a.group = o.group;
        o.func_a.name = o.signature.name;
        st_s* name_buf = st_s!.scope();
        name_buf.copy_fa( "#<sc_t>_a_#<sc_t>", sc_group_name, sc_name );
        o.func_a.global_name = compiler.entypeof( name_buf.sc );
        o.func_a.signature_global_name = o.signature.global_name;
        o.func_a.expandable = false;
        o.func_a.signature = &o.signature;
        o.func_a.source_point.copy( &o.source_point );
        compiler.register_func( o.func_a );
    }

    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

