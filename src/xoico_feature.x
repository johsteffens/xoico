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

func (:) xoico.parse = (try)
{
    $* compiler = o.group.compiler;

    o.source_point.set( source );
    o.strict = source.parse_bl( " #?w'strict' " );

    if( source.parse_bl( " #?|'|" ) )
    {
        st_s* flags = st_s!.scope();
        source.parse_em_fa( " #until'''", flags );
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
        source.parse_em_fa( "' " );
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

    if( source.parse_bl( " #=?'=' " ) )
    {
        if( o.strict ) return source.parse_error_fa( "Feature is 'strict'. Default function would have no effect." );
        o.default_body = xoico_body_s!;
        o.default_body.set_group( o.group );
        o.default_body.parse( source );
        o.st_default_func_name.copy_fa( "#<sc_t>_default", compiler.nameof( o.signature.name ) );
    }
    else if( source.parse_bl( " #?w'extern' " ) )
    {
        st_s* st_name = st_s!.scope();
        source.parse_em_fa( " #name ", st_name );
        if( st_name.size == 0 ) return source.parse_error_fa( "Feature: Default function name expected." );
        o.st_default_func_name.copy_fa( "#<sc_t>_#<sc_t>", compiler.nameof( o.signature.name ), st_name.sc );
    }

    source.parse_em_fa( " ; " );

    o.function_pointer_name = o.signature.global_name;

    o.setup_functions();
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) (er_t setup_functions( mutable )) = (try)
{
    $* compiler = o.group.compiler;
    sc_t sc_name = compiler.nameof( o.signature.name );
    sc_t sc_group_name = o.group.st_name.sc;
    st_s* st_spect_name = o.group.create_spect_name().scope();
    sc_t sc_spect_name = st_spect_name.sc;

    st_s* st_ret_typespec = st_s!.scope();
    o.signature.typespec_ret.expand( o.group, sc_group_name, st_ret_typespec );
    bl_t has_ret = ( o.signature.typespec_ret.type != TYPEOF_void );
    sc_t sc_ret_typespec = st_ret_typespec.sc;
    bl_t flag_const = o->signature.arg_o == TYPEOF_const;

    bl_t always_defined = ( o.strict || o.default_body || o.st_default_func_name.size > 0 );

    if( o.flag_a )
    {
        st_s* st = st_s!.scope();
        st.push_fa( "(#<sc_t> a_#<sc_t>(", sc_ret_typespec, sc_name );
        if( flag_const ) st.push_fa( " const" );
        st.push_fa( " #<sc_t>* o", sc_group_name );
        o.signature.args.expand( false, sc_group_name, st );
        st.push_fa( " )) = (verbatim_C) { " );
        st.push_fa( "const #<sc_t>* p = #<sc_t>_get_aware( o ); ", sc_spect_name, sc_spect_name );
        st.push_fa( "assert( p->#<sc_t> ); ", sc_name );
        if( has_ret ) st.push_fa( "return " );
        st.push_fa( "p->#<sc_t>( o", sc_name );
        o->signature.args.expand_name( false, st );
        st.push_fa( " ); };" );

        xoico_func_s* func = o.push_func_from_sc( st.sc );
        func.declare_in_expand_forward = false;
    }

    if( o.flag_a )
    {
        st_s* st = st_s!.scope();
        st.push_fa( "(bl_t a_defines_#<sc_t>( const @* o )) = ", sc_name );
        if( always_defined )
        {
            st.push_fa( "{ return true; };", sc_name );
        }
        else
        {
            st.push_fa( "{ return #<sc_t>_get_aware( o )->#<sc_t> != NULL; };", sc_spect_name, sc_name );
        }

        xoico_func_s* func = o.push_func_from_sc( st.sc );
        func.declare_in_expand_forward = false;
    }

    if( o.flag_t )
    {
        st_s* st = st_s!.scope();
        st.push_fa( "(#<sc_t> t_#<sc_t>( tp_t type,", sc_ret_typespec, sc_name );

        if( flag_const ) st.push_fa( " const" );
        st.push_fa( " #<sc_t>* o", sc_group_name );
        o->signature.args.expand( false, sc_group_name, st );
        st.push_fa( " )) = (verbatim_C) { " );
        st.push_fa( "const #<sc_t>* p = #<sc_t>_get_typed( type ); ", sc_spect_name, sc_spect_name );
        st.push_fa( "assert( p->#<sc_t> ); ", sc_name );
        if( has_ret ) st.push_fa( "return " );
        st.push_fa( "p->#<sc_t>( o", sc_name );
        o->signature.args.expand_name( false, st );
        st.push_fa( " ); };" );

        xoico_func_s* func = o.push_func_from_sc( st.sc );
        func.declare_in_expand_forward = false;
    }

    if( o->flag_t )
    {
        st_s* st = st_s!.scope();
        st.push_fa( "(bl_t t_defines_#<sc_t>( tp_t type )) = ", sc_name );
        if( always_defined )
        {
            st.push_fa( "{ return true; };", sc_name );
        }
        else
        {
            st.push_fa( "{ return #<sc_t>_get_typed( type )->#<sc_t> != NULL; };", sc_spect_name, sc_name );
        }

        xoico_func_s* func = o.push_func_from_sc( st.sc );
        func.declare_in_expand_forward = false;
    }

    if( o.flag_p )
    {
        st_s* st = st_s!.scope();
        st.push_fa( "(#<sc_t> p_#<sc_t>( const #<sc_t>* p,", sc_ret_typespec, sc_name, sc_spect_name );

        if( flag_const ) st.push_fa( " const" );
        st.push_fa( " #<sc_t>* o", sc_group_name );
        o->signature.args.expand( false, sc_group_name, st );
        st.push_fa( " )) = (verbatim_C) { " );
        st.push_fa( "assert( p->#<sc_t> ); ", sc_name );
        if( has_ret ) st.push_fa( "return " );
        st.push_fa( "p->#<sc_t>( o", sc_name );
        o.signature.args.expand_name( false, st );
        st.push_fa( " ); };" );

        xoico_func_s* func = o.push_func_from_sc( st.sc );
        func.declare_in_expand_forward = false;
    }

    if( o.flag_p )
    {
        st_s* st = st_s!.scope();
        st.push_fa( "(bl_t p_defines_#<sc_t>( const #<sc_t>* p )) = ", sc_name, sc_spect_name );
        if( always_defined )
        {
            st.push_fa( "{ return true; };", sc_name );
        }
        else
        {
            st.push_fa( "{ return p->#<sc_t> != NULL; };", sc_name );
        }

        xoico_func_s* func = o.push_func_from_sc( st.sc );
        func.declare_in_expand_forward = false;
    }

    if( o.flag_r )
    {
        st_s* st = st_s!.scope();
        st.push_fa( "( #<sc_t> r_#<sc_t>(", sc_ret_typespec, sc_name );
        st.push_fa( " const sr_s* o" );
        o.signature.args.expand( false, sc_group_name, st );
        st.push_fa( " )) = (verbatim_C) { " );
        if( !flag_const ) st.push_fa( "ASSERT( !sr_s_is_const( o ) ); " );
        st.push_fa
        (
            "const #<sc_t>* p = (const #<sc_t>*)ch_spect_p( o->p, TYPEOF_#<sc_t> ); ",
            sc_spect_name,
            sc_spect_name,
            sc_spect_name
        );

        st.push_fa( "assert( p->#<sc_t> ); ", sc_name );
        if( has_ret ) st.push_fa( "return " );
        st.push_fa( "p->#<sc_t>( o->o", sc_name );
        o->signature.args.expand_name( false, st );
        st.push_fa( " ); };" );

        xoico_func_s* func = o.push_func_from_sc( st.sc );
        func.declare_in_expand_forward = false;
    }

    if( o.flag_r )
    {
        st_s* st = st_s!.scope();

        st.push_fa( "(bl_t r_defines_#<sc_t>( const sr_s* o )) = ", sc_name );
        if( always_defined )
        {
            st.push_fa( "{ return true; };", sc_name );
        }
        else
        {
            st.push_fa( "{ return ( (#<sc_t>*)ch_spect_p( o->p, TYPEOF_#<sc_t> ) )->#<sc_t> != NULL; };", sc_spect_name, sc_spect_name, sc_name );
        }

        xoico_func_s* func = o.push_func_from_sc( st.sc );
        func.declare_in_expand_forward = false;
    }

    if( o.st_default_func_name.size > 0 )
    {
        st_s* st = st_s!.scope();
        st.push_fa( "(#<sc_t> #<sc_t>(", sc_ret_typespec, o.st_default_func_name.sc );
        if( flag_const ) st.push_fa( " const" );
        st.push_fa( " #<sc_t>* o", sc_group_name );
        o.signature.args.expand( false, sc_group_name, st );
        st.push_fa( " ));" );

        xoico_func_s* func = o.push_func_from_sc( st.sc );
        func.declare_in_expand_forward = false;
        if( o.default_body ) func.body =< o.default_body.fork();
    }

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) (xoico_func_s* push_func_from_sc( mutable, sc_t sc )) =
{
    xoico_func_s* func = o.funcs.push_d( xoico_func_s! );
    func.group = o.group;
    func.parse_sc( sc );
    func.source_point.copy( o.source_point.1 );
    return func;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico.finalize = (try)
{
    $* compiler = o.group.compiler;
    foreach( $* func in o.funcs )
    {
        func.finalize();
        compiler.register_func( func );
    }
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico.expand_forward = (try)
{
    foreach( $* func in o.funcs ) func.expand_forward( indent, sink );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico.expand_indef_typedef = (try)
{
    if( !o.expandable ) return 0;
    xoico_compiler_s* compiler = o.group.compiler;
    sink.push_fa( " \\\n#rn{ }  typedef ", indent );
    o.signature.typespec_ret.expand( o.group, o.group.st_name.sc, sink );
    sink.push_fa( " (*#<sc_t>)(", compiler.nameof( o.function_pointer_name ) );
    if( o.signature.arg_o == TYPEOF_const ) sink.push_fa( " const" );
    sink.push_fa( " #<sc_t>* o", o.group.st_name.sc );
    o.signature.args.expand( false, o.group.st_name.sc, sink );
    sink.push_fa( " );" );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico.expand_spect_declaration = (try)
{
    if( !o.expandable ) return 0;
    xoico_compiler_s* compiler = o.group.compiler;
    sink.push_fa( " \\\n#rn{ }#<sc_t> #<sc_t>;", indent, compiler.nameof( o.function_pointer_name ), compiler.nameof( o.signature.name ) );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico.expand_spect_definition = (try)
{
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
};

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico.expand_indef_declaration = (try)
{
    if( !o.expandable ) return 0;
    foreach( $* func in o->funcs ) func.expand_declaration( indent + 2, sink );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico.expand_definition = (try)
{
    if( !o.expandable ) return 0;
    foreach( $* func in o.funcs ) func.expand_definition( indent, sink );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico.expand_init1 = (try)
{
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
};

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

