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
    o.strict = source.parse_bl( " #?w'strict' " );

    if( source.parse_bl( " #?|'|" ) )
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

    if( source.parse_bl( " #?'=' " ) )
    {
        if( source.parse_bl( " #=?'{' " ) )
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
            try( source.parse_em_fa( " #name ", o.st_default_func_name.1 ) );
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
        o.func_a.signature = o.signature.1;
        o.func_a.source_point.copy( o.source_point.1 );
        compiler.register_func( o.func_a );
    }

    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico.expand_indef_typedef =
{ try {
    if( !o.expandable ) return 0;
    xoico_compiler_s* compiler = o.group.compiler;
    sink.push_fa( " \\\n#rn{ }  typedef ", indent );
    o.signature.typespec_ret.expand( o.group, o.group.st_name.sc, sink );
    sink.push_fa( " (*#<sc_t>_#<sc_t>)(", o.group.st_name.sc, compiler.nameof( o.signature.name ) );
    if( o.signature.arg_o == TYPEOF_const ) sink.push_fa( " const" );
    sink.push_fa( " #<sc_t>* o", o.group.st_name.sc );
    o.signature.args.expand( false, o.group.st_name.sc, sink );
    sink.push_fa( " );" );
    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico.expand_spect_declaration =
{ try {
    if( !o.expandable ) return 0;
    xoico_compiler_s* compiler = o.group.compiler;
    sink.push_fa( " \\\n#rn{ }#<sc_t> #<sc_t>;", indent, compiler.nameof( o.signature.global_name ), compiler.nameof( o.signature.name ) );
    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico.expand_spect_definition =
{ try {
    if( !o.expandable ) return 0;
    xoico_compiler_s* compiler = o.group.compiler;
    sink.push_fa( "#rn{ }\"feature ", indent );
    if( o.strict ) sink.push_fa( "strict " );
    if( o.flag_a ) sink.push_fa( "aware " );

    sink.push_fa( "#<sc_t> : #<sc_t>", o.group.st_name.sc, compiler.nameof( o.signature.name ) );
    if( o.st_default_func_name.size > 0 )
    {
        sink.push_fa( " = #<sc_t>_#<sc_t>", o.group.st_name.sc, o.st_default_func_name.sc );
    }
    sink.push_fa( ";\"\n" );
    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico.expand_indef_declaration =
{ try {
    if( !o.expandable ) return 0;
    xoico_compiler_s* compiler = o.group.compiler;

    sc_t sc_name         = compiler.nameof( o.signature.name );
    sc_t sc_group_name   = o.group.st_name.sc;

    st_s* st_ret_typespec = st_s!.scope();
    st_s* st_spect_name = o.group.create_spect_name().scope();
    sc_t  sc_spect_name = st_spect_name.sc;

    o.signature.typespec_ret.expand( o.group, sc_group_name, st_ret_typespec );
    bl_t has_ret = ( o.signature.typespec_ret.type != TYPEOF_void );

    sc_t sc_ret_typespec = st_ret_typespec.sc;
    sc_t sc_default_func_name = o.st_default_func_name.sc;
    bl_t flag_const = o->signature.arg_o == TYPEOF_const;

    if( o.flag_p )
    {
        sink.push_fa
        (
            " \\\n#rn{ }  static inline #<sc_t> #<sc_t>_p_#<sc_t>( const #<sc_t>* __p,",
            indent,
            sc_ret_typespec,
            sc_group_name,
            sc_name,
            sc_spect_name
        );

        if( flag_const ) sink.push_fa( " const" );
        sink.push_fa( " #<sc_t>* o", sc_group_name );
        o->signature.args.expand( false, sc_group_name, sink );
        sink.push_fa( " ) { " );
        sink.push_fa( "assert( __p->#<sc_t> ); ", sc_name );
        if( has_ret ) sink.push_fa( "return " );
        sink.push_fa( "__p->#<sc_t>( o", sc_name );
        o.signature.args.expand_name( false, sink );
        sink.push_fa( " ); }" );
    }

    if( o.flag_t )
    {
        sink.push_fa
        (
            " \\\n#rn{ }  static inline #<sc_t> #<sc_t>_t_#<sc_t>( tp_t __t,",
            indent,
            sc_ret_typespec,
            sc_group_name,
            sc_name,
            sc_group_name
        );

        if( flag_const ) sink.push_fa( " const" );
        sink.push_fa( " #<sc_t>* o", sc_group_name );
        o->signature.args.expand( false, sc_group_name, sink );
        sink.push_fa( " ) { " );
        sink.push_fa( "const #<sc_t>* p = #<sc_t>_get_typed( __t ); ", sc_spect_name, sc_spect_name );
        sink.push_fa( "assert( p->#<sc_t> ); ", sc_name );
        if( has_ret ) sink.push_fa( "return " );
        sink.push_fa( "p->#<sc_t>( o", sc_name );
        o->signature.args.expand_name( false, sink );
        sink.push_fa( " ); }" );
    }

    if( o.flag_a )
    {
        sink.push_fa
        (
            " \\\n#rn{ }  static inline #<sc_t> #<sc_t>_a_#<sc_t>(",
            indent,
            sc_ret_typespec,
            sc_group_name,
            sc_name
        );

        if( flag_const ) sink.push_fa( " const" );
        sink.push_fa( " #<sc_t>* o", sc_group_name );
        o.signature.args.expand( false, sc_group_name, sink );
        sink.push_fa( " ) { " );
        sink.push_fa( "const #<sc_t>* p = #<sc_t>_get_aware( o ); ", sc_spect_name, sc_spect_name );
        sink.push_fa( "assert( p->#<sc_t> ); ", sc_name );
        if( has_ret ) sink.push_fa( "return " );
        sink.push_fa( "p->#<sc_t>( o", sc_name );
        o->signature.args.expand_name( false, sink );
        sink.push_fa( " ); }" );
    }

    if( o.flag_r )
    {
        sink.push_fa
        (
            " \\\n#rn{ }  static inline #<sc_t> #<sc_t>_r_#<sc_t>(",
            indent,
            sc_ret_typespec,
            sc_group_name,
            sc_name
        );

        sink.push_fa( " const sr_s* o" );
        o.signature.args.expand( false, sc_group_name, sink );
        sink.push_fa( " ) { " );
        if( !flag_const ) sink.push_fa( "ASSERT( !sr_s_is_const( o ) ); ", indent );
        sink.push_fa
        (
            "const #<sc_t>* p = (const #<sc_t>*)ch_spect_p( o->p, TYPEOF_#<sc_t> ); ",
            sc_spect_name,
            sc_spect_name,
            sc_spect_name
        );

        sink.push_fa( "assert( p->#<sc_t> ); ", sc_name );
        if( has_ret ) sink.push_fa( "return " );
        sink.push_fa( "p->#<sc_t>( o->o", sc_name );
        o->signature.args.expand_name( false, sink );
        sink.push_fa( " ); }" );
    }

    if( o.flag_p )
    {
        sink.push_fa
        (
            " \\\n#rn{ }  static inline bl_t #<sc_t>_p_defines_#<sc_t>( const #<sc_t>* __p ) ",
            indent,
            sc_group_name,
            sc_name,
            sc_spect_name
        );

        if( o.strict || o.default_body || o.st_default_func_name.size > 0 )
        {
            sink.push_fa( "{ return true; }", sc_name );
        }
        else
        {
            sink.push_fa( "{ return __p->#<sc_t> != NULL; }", sc_name );
        }
    }

    if( o->flag_t )
    {
        sink.push_fa
        (
            " \\\n#rn{ }  static inline bl_t #<sc_t>_t_defines_#<sc_t>( tp_t __t ) ",
            indent,
            sc_group_name,
            sc_name
        );

        if( o.strict || o.default_body || o.st_default_func_name.size > 0 )
        {
            sink.push_fa( "{ return true; }", sc_name );
        }
        else
        {
            sink.push_fa( "{ return #<sc_t>_get_typed( __t )->#<sc_t> != NULL; }", sc_spect_name, sc_name );
        }
    }

    if( o.flag_a )
    {
        sink.push_fa
        (
            " \\\n#rn{ }  static inline bl_t #<sc_t>_a_defines_#<sc_t>( const #<sc_t>* o ) ",
            indent,
            sc_group_name,
            sc_name,
            sc_group_name
        );

        if( o.strict || o.default_body || o.st_default_func_name.size > 0 )
        {
            sink.push_fa( "{ return true; }", sc_name );
        }
        else
        {
            sink.push_fa( "{ return #<sc_t>_get_aware( o )->#<sc_t> != NULL; }", sc_spect_name, sc_name );
        }
    }

    if( o.flag_r )
    {
        sink.push_fa
        (
            " \\\n#rn{ }  static inline bl_t #<sc_t>_r_defines_#<sc_t>( const sr_s* o ) ",
            indent,
            sc_group_name,
            sc_name
        );

        if( o.strict || o.default_body || o.st_default_func_name.size > 0 )
        {
            sink.push_fa( "{ return true; }", sc_name );
        }
        else
        {
            sink.push_fa( "{ return ( (#<sc_t>*)ch_spect_p( o->p, TYPEOF_#<sc_t> ) )->#<sc_t> != NULL; }", sc_spect_name, sc_spect_name, sc_name );
        }
    }

    if( o.st_default_func_name.size > 0 )
    {
        if( o.default_body && o.default_body.go_inline )
        {
            sink.push_fa
            (
                " \\\n#rn{ }  static inline #<sc_t> #<sc_t>_#<sc_t>(",
                indent,
                sc_ret_typespec,
                sc_group_name,
                sc_default_func_name
            );

            if( flag_const ) sink.push_fa( " const" );
            sink.push_fa( " #<sc_t>* o", sc_group_name );
            o.signature.args.expand( false, sc_group_name, sink );
            sink.push_fa( " )" );
            o.default_body.expand( o.signature.1, indent, sink );
        }
        else
        {
            sink.push_fa( " \\\n#rn{ }  #<sc_t> #<sc_t>_#<sc_t>(", indent, sc_ret_typespec, sc_group_name, sc_default_func_name );
            if( flag_const ) sink.push_fa( " const" );
            sink.push_fa( " #<sc_t>* o", sc_group_name );
            o.signature.args.expand( false, sc_group_name, sink );
            sink.push_fa( " );" );
        }
    }
    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico.expand_definition =
{ try {
    if( !o.expandable ) return 0;
    if( o.default_body && !o.default_body.go_inline )
    {
        sc_t sc_group_name = o.group.st_name.sc;
        st_s* st_ret_typespec = st_s!.scope();
        o.signature.typespec_ret.expand( o->group, sc_group_name, st_ret_typespec );

        sink.push_fa( "\n" );
        sink.push_fa( "\n#<sc_t> #<sc_t>_#<sc_t>(", st_ret_typespec.sc, sc_group_name, o.st_default_func_name.sc );
        if( o.signature.arg_o == TYPEOF_const ) sink.push_fa( " const" );
        sink.push_fa( " #<sc_t>* o", sc_group_name );
        o.signature.args.expand( false, sc_group_name, sink );
        sink.push_fa( " )\n" );
        o.default_body.expand( o.signature.1, indent, sink );
    }
    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico.expand_init1 =
{ try {
    if( !o.expandable ) return 0;
    xoico_compiler_s* compiler = o.group.compiler;
    sc_t sc_global_name = compiler.nameof( o.signature.global_name );

    sink.push_fa( "#rn{ }BCORE_REGISTER_FEATURE( #<sc_t> );\n", indent, sc_global_name );
    if( o.st_default_func_name.size > 0 )
    {
        sink.push_fa
        (
            "#rn{ }BCORE_REGISTER_FFUNC( #<sc_t>, #<sc_t>_#<sc_t> );\n",
            indent,
            sc_global_name,
            o->group->st_name.sc,
            o->st_default_func_name.sc
        );
    }
    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

