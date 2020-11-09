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

/** Inspects name and enrolls it and returns hash;
 *  Detects '$' as TYEPOF_type_deduce
 *  Detects '@' as type of class or group
 *  If no identifier could be detected: Returns 0 and leave source unchanged.
 */
func (:) (tp_t get_identifier( mutable, bcore_source* source, bl_t take_from_source )) =
{
    tp_t tp_identifier = 0;
    if( source.parse_bl( "#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||[0]=='_'||[0]=='@'||[0]=='$'||([0]==':'&&([1]!=' '&&[1]!='\t'&&[1]!='\n'&&[1]!='/')))" ) )
    {
        sz_t source_index = take_from_source ? 0 : source.get_index();
        switch( source.inspect_char() )
        {
            case '@':
            {
                source.get_char();
                st_s* st_name = scope( st_s! );
                st_name.copy( o.stamp ? &o.stamp.st_name : &o.group.st_name );
                if( source.parse_bl( "#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||[0]=='_'||([0]>='0'&&[0]<='9'))" ) )
                {
                    o.parse_fa( source, "#:name", st_name );
                }
                tp_identifier = o.entypeof( st_name.sc );
            }
            break;

            case '$':
            {
                source.get_char();
                tp_identifier = TYPEOF_type_deduce;
            }
            break;

            case ':':
            {
                st_s* st_name = scope( st_s! );
                o.group.parse_name( st_name, source );
                tp_identifier = o.entypeof( st_name.sc );
            }
            break;

            default:
            {
                st_s* st_name = scope( st_s! );
                source.parse_fa( "#name", st_name );
                tp_identifier = o.entypeof( st_name.sc );
            }
            break;
        }

        if( !take_from_source ) source.set_index( source_index );
    }

    return tp_identifier;
};

//----------------------------------------------------------------------------------------------------------------------

/** transfers identifier, enrolls it and sets 'tp_identifier' */
func(:) (er_t trans_identifier( mutable, bcore_source* source, st_s* buf /* can be NULL */, tp_t* tp_identifier/* can be NULL */ )) =
{
try
{

    tp_t identifier = o.get_identifier( source, true );
    if( !identifier )
    {
        return o.parse_err_fa( source, "Identifier exected" );
    }
    if( tp_identifier ) *tp_identifier = identifier;
    if( buf ) buf.push_sc( o.nameof( identifier ) );
    return 0;
} // try
};

//----------------------------------------------------------------------------------------------------------------------

/** parses number: (all integer, hex and float encodings)*/
func(:) (er_t trans_number_literal( mutable, bcore_source* source, st_s* buf )) =
{
try
{
    bl_t hex = false;
    if( source.parse_bl( "#?'0x'" ) )
    {
        buf.push_sc( "0x" );
        hex = true;
    }
    else if( source.parse_bl( "#?'0X'" ) )
    {
        buf.push_sc( "0X" );
        hex = true;
    }

    if( hex )
    {
        while( source.parse_bl( "#?(([0]>='0'&&[0]<='9')||([0]>='a'&&[0]<='f')||([0]>='A'&&[0]<='F'))" ) )
        {
            buf.push_char( source.get_char() );
        }
    }
    else // decimal
    {
        while( source.parse_bl( "#?([0]>='0'&&[0]<='9')" ) )
        {
            buf.push_char( source.get_char() );
        }
    }

    bl_t fraction = false;

    if( source.parse_bl( "#?([0]=='.')" ) )
    {
        buf.push_char( source.get_char() );
        fraction = true;
    }

    if( fraction )
    {
        while( source.parse_bl( "#?([0]>='0'&&[0]<='9')" ) )
        {
            buf.push_char( source.get_char() );
        }
    }

    bl_t exponent = false;

    if( source.parse_bl( "#?([0]=='e'&&[0]=='E')" ) )
    {
        buf.push_char( source.get_char() );
        exponent = true;
    }

    if( exponent )
    {
        if( source.parse_bl( "#?([0]=='+'||[0]=='-')" ) )
        {
            buf.push_char( source.get_char() );
        }

        while( source.parse_bl( "#?([0]>='0'&&[0]<='9')" ) )
        {
            buf.push_char( source.get_char() );
        }
    }

    // suffix
    while( source.parse_bl( "#?([0]=='l'||[0]=='L'||[0]=='u'||[0]=='U'||[0]=='f'||[0]=='F')" ) )
    {
        buf.push_char( source.get_char() );
    }

    return 0;
} // try
};

//----------------------------------------------------------------------------------------------------------------------

/// parses string
func (:) (er_t trans_string_literal( mutable, bcore_source* source, st_s* buf )) =
{
try
{
    o.trans( source, "\"", buf );

    while( !source.eos() && !source.parse_bl( "#=?'\"'" ) )
    {
        if( source.parse_bl( "#?'\\'" ) ) buf.push_char( '\\' );
        buf.push_char( source.get_char() );
    }

    o.trans( source, "\"", buf );
    return 0;
} // try
};

//----------------------------------------------------------------------------------------------------------------------

/// character literal
func (:) (er_t trans_char_literal( mutable, bcore_source* source, st_s* buf )) =
{
try
{
    o.trans( source, "'", buf );

    while( !source.eos() && !source.parse_bl( "#=?|'|" ) )
    {
        if( source.parse_bl( "#?'\\'" ) ) buf.push_char( '\\' );
        buf.push_char( source.get_char() );
    }

    o.trans( source, "'", buf );
    return 0;
} // try
};

//----------------------------------------------------------------------------------------------------------------------

/// parses whitespaces including comments
func (:) (er_t trans_whitespace( mutable, bcore_source* source, st_s* buf /* can be NULL */ )) =
{
try
{
    bl_t exit_loop = false;
    while( !exit_loop && !source.eos() )
    {
        char c =  source.inspect_char();
        switch( c )
        {
            case ' ' :
            case '\t':
            case '\n':
            {
                char c =  source.get_char();
                if( buf )  buf.push_char( c );
            }
            break;

            case '/':
            {
                if( source.parse_bl( "#?'//'" ) )
                {
                    if( buf ) buf.push_sc( "//" );
                    while( !source.eos() )
                    {
                        char c =  source.get_char();
                        if( buf ) buf.push_char( c );
                        if( c == '\n' ) break;
                    }
                }
                else if( source.parse_bl( "#?'/*'" ) )
                {
                    if( buf ) buf.push_sc( "/*" );
                    while( !source.eos() )
                    {
                        if( source.parse_bl( "#?'*/'" ) )
                        {
                            if( buf ) buf.push_sc( "*/" );
                            break;
                        }
                        char c =  source.get_char();
                        if( buf ) buf.push_char( c );
                    }
                }
                else
                {
                    exit_loop = true;
                }
            }
            break;

            default:
            {
                exit_loop = true;
            }
            break;
        }
    }
    return 0;
} // try
};

//----------------------------------------------------------------------------------------------------------------------

func (:) (er_t trans_preprocessor( mutable, bcore_source* source, st_s* buf )) =
{
try
{
    o.parse( source, "##" );
    buf.push_sc( "#" );
    while( !source.eos() )
    {
        char c = source.get_char();
        buf.push_char( c );
        if( c == '\\' && source.inspect_char() == '\n' ) buf.push_char( source.get_char() );
        if( c == '\n' ) break;
    }
    return 0;
} // try
};

//----------------------------------------------------------------------------------------------------------------------

// any state; returns !=0 in case an operator was consumed
func (:) (tp_t trans_inert_operator( mutable, bcore_source* source, st_s* buf )) =
{
    switch( source.inspect_char() )
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '=':
        case '>':
        case '<':
        case '!':
        case '|':
        case '&':
        case '^':
        case '~':
        case '%':
        {
            buf.push_char( source.get_char() );
            return 1;
        }
        break;

        default: break;
    }

    return false;
};

//----------------------------------------------------------------------------------------------------------------------

func (:)
(
    er_t adapt_expression
    (
        mutable,
        bcore_source* source,
        const xoico_typespec_s* typespec_expr,
        const xoico_typespec_s* typespec_target,
        const st_s* expr,
        st_s* buf
    )
) =
{
try
{
    if( !typespec_expr.type )
    {
        return o.parse_err_fa
        (
            source,
            "xoico_cdaleth_s_adapt_expression: no type specified.",
            typespec_expr.indirection,
            typespec_target.indirection
        );
    }

    bl_t no_adaptation =
        ( typespec_target.indirection == typespec_expr.indirection ) ||
        ( typespec_expr.type == TYPEOF_vd_t ) ||
        ( typespec_expr.type == TYPEOF_vc_t );

    if( no_adaptation )
    {
        buf.push_fa( "#<st_s*>", expr );
    }
    else if( typespec_target.indirection == typespec_expr.indirection + 1 )
    {
        if( typespec_expr.flag_addressable )
        {
            buf.push_fa( "&(#<st_s*>)", expr );
        }
        else
        {
            return o.parse_err_fa( source, "Increasing indirection: Expression has no address." );
        }
    }
    else if( typespec_target.indirection == typespec_expr.indirection - 1 )
    {
        buf.push_fa( "*(#<st_s*>)", expr );
    }
    else
    {
        return o.parse_err_fa
        (
            source,
            "Cannot adapt from expression's indirection '#<sz_t>' to target indirection '#<sz_t>'.",
            typespec_expr.indirection,
            typespec_target.indirection
        );
    }
    return 0;
} // try
};

//----------------------------------------------------------------------------------------------------------------------

/// Processes the argument section '(....)' of a function
func (:)
(
    er_t trans_function_args
    (
        mutable,
        bcore_source* source,
        const xoico_signature_s* signature,
        const st_s* buf_obj_expr,
        const xoico_typespec_s* typespec_obj_expr,
        st_s* buf_out
    )
) =
{
try
{
    o.trans( source, "(", buf_out );

    if( signature.arg_o )
    {
        if( !buf_obj_expr )
        {
            st_s* buf_expr                  = scope( st_s!, scope_func );
            xoico_typespec_s* typespec_expr = scope( xoico_typespec_s!, scope_func );
            o.trans_expression( source, buf_expr, typespec_expr );
            buf_obj_expr = buf_expr;
            typespec_obj_expr = typespec_expr;
            if( signature.args.size > 0 ) o.parse( source, " ," );
        }

        xoico_typespec_s* typespec_obj_out = scope( typespec_obj_expr.clone() );
        typespec_obj_out.indirection = 1; // first argument of member functions has always indirection 1

        if( typespec_obj_expr.type )
        {
            o.adapt_expression( source, typespec_obj_expr, typespec_obj_out, buf_obj_expr, buf_out );
        }
        else
        {
            buf_out.push_st( buf_obj_expr );
        }
        if( signature.args.size > 0 ) buf_out.push_sc( "," );
    }

    foreach( $* arg in signature.args )
    {
        st_s* buf_expr                  = scope( st_s!, scope_local );
        xoico_typespec_s* typespec_expr = scope( xoico_typespec_s!, scope_local );
        o.parse( source, " " );
        if( __i > 0 ) o.parse( source, " ," );
        o.trans_expression( source, buf_expr, typespec_expr );
        if( __i > 0 ) buf_out.push_sc( "," );
        if( typespec_expr.type )
        {
            o.adapt_expression( source, typespec_expr, &arg.typespec, buf_expr, buf_out );
        }
        else
        {
            buf_out.push_st( buf_expr );
        }
    }

    o.parse( source, " " );
    o.trans( source, ")", buf_out );
    return 0;
} // try
};

//----------------------------------------------------------------------------------------------------------------------

func (:)
(
    er_t trans_typespec_expression
    (
        mutable,
        bcore_source* source,
        st_s* buf,
        const xoico_typespec_s*  in_typespec, // required
              xoico_typespec_s* out_typespec  // optional
    )
) =
{
try
{
    o.trans_whitespace( source, buf );

    if( out_typespec ) out_typespec.type = 0;

    if( source.parse_bl_fa( "#?([0]=='.'||([0]=='-'&&[1]=='>'))" ) )
    {
        if( source.parse_bl_fa( "#?'->'" ) )
        {
            if( in_typespec.indirection != 1 )
            {
                return o.parse_err_fa( source, "Given indirection is '#<sz_t>'. '->' can only be used at indirection '1'.", in_typespec.indirection );
            }
        }
        else
        {
            o.parse( source, "." );
        }
        o.parse( source, " " );
        xoico_compiler_element_info_s* info = scope( xoico_compiler_element_info_s! );
        if( source.parse_bl_fa( "#=?'['" ) || source.parse_bl_fa( "#=?'?['" ) ) // array subscript
        {
            bl_t bounds_check = false;
            if( source.parse_bl_fa( "#=?'?'" ) )
            {
                o.parse( source, "?[" );
                bounds_check = true;
            }
            else
            {
                o.parse( source, "[" );
            }

            if( bounds_check ) return o.parse_err_fa( source, "Bounds check not yet available." );

            if( in_typespec.indirection > 1 )
            {
                return o.parse_err_fa
                (
                    source,
                    "Resolving subscript: Indirection '#<sz_t>' is too large.",
                    in_typespec.indirection
                );
            }

            buf.push_fa( "#<sc_t>data[", ( in_typespec.indirection == 1 ) ? "->" : "." );
            o.trans_expression( source, buf, NULL );
            o.parse( source, "]" );
            buf.push_sc( "]" );

            if( o.compiler.get_type_array_element_info( in_typespec.type, info ) )
            {
                o.trans_typespec_expression( source, buf, &info.type_info.typespec, out_typespec );
            }
            else
            {
                o.trans_expression( source, buf, NULL );
            }
        }
        else // member (object or function)
        {
            st_s* buf_local = scope( st_s! );
            tp_t tp_identifier = 0;
            o.trans_identifier( source, buf_local, &tp_identifier );
            o.trans_whitespace( source, buf_local );

            // builtin functions ...
            if( o.is_builtin_func( tp_identifier ) )
            {
                xoico_typespec_s* typespec_builtin = scope( xoico_typespec_s! );
                o.trans_builtin( tp_identifier, source, buf, in_typespec, buf_local, typespec_builtin );
                buf.copy( buf_local );
                o.trans_typespec_expression( source, buf, typespec_builtin, out_typespec );
            }
            else if( o.compiler.get_type_element_info( in_typespec.type, tp_identifier, info ) )
            {
                if( info.signature ) // member function
                {
                    sc_t sc_func_name = o.nameof( info.type_info.typespec.type );
                    ASSERT( sc_func_name );
                    st_s* arg_obj = scope( buf.clone() );
                    buf.copy_fa( "#<sc_t>", sc_func_name );
                    o.trans_function_args( source, info.signature, arg_obj, in_typespec, buf );
                    o.trans_typespec_expression( source, buf, &info.signature.typespec_ret, out_typespec );
                }
                else // traced member element
                {
                    if( in_typespec.indirection > 1 )
                    {
                        return o.parse_err_fa
                        (
                            source,
                            "Dereferencing #<sc_t>: Indirection '#<sz_t>' is too large.",
                            o.nameof( tp_identifier ),
                            in_typespec.indirection
                        );
                    }
                    buf.push_fa( "#<sc_t>#<sc_t>", ( in_typespec.indirection == 1 ) ? "->" : ".", buf_local.sc );
                    o.trans_typespec_expression( source, buf, &info.type_info.typespec, out_typespec );
                }
            }
            else if( source.parse_bl_fa( "#?'('" ) ) // untraced member function
            {
                st_s* arg_obj = scope( buf.clone() );
                st_s_clear( buf );

                /// Untraced member functions of a group are always treated as 'aware'
                if( o.is_group( in_typespec.type ) )
                {
                    st_s_copy_fa
                    (
                        buf,
                        "#<sc_t>_a_#<sc_t>( ",
                        o.nameof( in_typespec.type ),
                        o.nameof( tp_identifier )
                    );
                }
                else
                {
                    st_s_copy_fa
                    (
                        buf,
                        "#<sc_t>_#<sc_t>( ",
                        o.nameof( in_typespec.type ),
                        o.nameof( tp_identifier )
                    );
                }

                {
                    xoico_typespec_s* typespec_obj = scope( in_typespec.clone() );
                    typespec_obj.indirection = 1; // first argument of member functions
                    o.adapt_expression( source, in_typespec, typespec_obj, arg_obj, buf );
                }

                bl_t first = true;
                o.trans_whitespace( source, buf_local );
                while( !source.eos() )
                {
                    if( source.parse_bl_fa( "#=?')'" ) ) break;

                    st_s* buf_expr = scope( st_s!, scope_local );
                    if( !first ) o.parse( source, "," );
                    o.trans_expression( source, buf_expr, NULL );
                    o.trans_whitespace( source, buf_expr );
                    buf.push_fa( "," );
                    buf.push_fa( "#<sc_t>", buf_expr.sc );
                    first = false;
                }

                o.parse( source, ")" );
                buf.push_sc( ")" );

                o.trans_expression( source, buf, NULL );
            }
            else // untraced member element
            {
                buf.push_fa( "#<sc_t>#<sc_t>", ( in_typespec.indirection == 1 ) ? "->" : ".", buf_local.sc );
                o.trans_expression( source, buf, NULL );
            }
        }
    }
    // array subscript
    else if( source.parse_bl_fa( "#?'['" ) )
    {
        if( in_typespec.indirection == 0 )
        {
            if( in_typespec.type != TYPEOF_sc_t && in_typespec.type != TYPEOF_sd_t )
            {
                return o.parse_err_fa( source, "Array subscript requires indirection >= 1." );
            }
        }
        buf.push_sc( "[" );
        o.trans_expression( source, buf, NULL );
        o.parse( source, "]" );
        buf.push_sc( "]" );

        xoico_typespec_s* typespec = scope( in_typespec.clone() );
        if( in_typespec.type != TYPEOF_sc_t && in_typespec.type != TYPEOF_sd_t )
        {
            typespec.indirection--;
        }
        o.trans_typespec_expression( source, buf, typespec, out_typespec );
    }
    // create if not present
    else if( source.parse_bl_fa( "#?([0]=='!'&&[1]!='=')" ) )
    {
        o.parse( source, "!" );

        //ignore in case indirection is 0;
        if( in_typespec.indirection > 0 )
        {
            if( !( in_typespec.indirection == 1 && in_typespec.flag_addressable ) )
            {
                return o.parse_err_fa( source, "Create-Operator requires lvalue with addressable indirection of 1." );
            }

            if( xoico_cdaleth_s_is_group( o, in_typespec.type ) )
            {
                return o.parse_err_fa( source, "Create-Operator: lvalue is a group." );
            }

            st_s* arg_obj = scope( buf.clone() );
            buf.clear();

            sc_t sc_type = o.nameof( in_typespec.type );
            buf.push_fa( "BCORE_PASS_CREATE(#<sc_t>,#<sc_t>)", sc_type, arg_obj.sc );
        }

        o.trans_typespec_expression( source, buf, in_typespec, out_typespec );
    }
    // test for presence
    else if( source.parse_bl_fa( "#?([0]=='?'&&[1]=='.')" ) )
    {
        o.parse( source, "?" );

        //ignore in case indirection is 0;
        if( in_typespec.indirection > 0 )
        {
            if( in_typespec.indirection != 1 )
            {
                return o.parse_err_fa( source, "Test-Operator requires lvalue with indirection of 1." );
            }

            st_s* arg_obj = scope( buf.clone() );
            st_s_clear( buf );

            sc_t sc_type = o.nameof( in_typespec.type );
            buf.push_fa( "BCORE_PASS_TEST(#<sc_t>,#<sc_t>)", sc_type, arg_obj.sc );
        }

        o.trans_typespec_expression( source, buf, in_typespec, out_typespec );
    }
    // attach (detach)
    else if( source.parse_bl_fa( "#?'=<'" ) )
    {
        if( !( in_typespec.indirection == 1 && in_typespec.flag_addressable ) )
        {
            return o.parse_err_fa( source, "Attach-Operator requires lvalue with addressable indirection of 1" );
        }

        st_s* arg_obj = scope( buf.clone() );
        buf.clear();

        sc_t sc_type = o.nameof( in_typespec.type );
        buf.push_fa( "#<sc_t>", sc_type );

        xoico_typespec_s* typespec_rval = scope( xoico_typespec_s! );
        if( o.is_group( in_typespec.type ) )
        {
            buf.push_sc( "_a" );
            buf.push_fa( "_attach( &(#<sc_t>), (#<sc_t>*)", arg_obj.sc, sc_type );
            buf.push_fa( "(" );
            o.trans_expression( source, buf, typespec_rval );
            buf.push_fa( "))" );
        }
        else
        {
            buf.push_fa( "_attach( &(#<sc_t>), ", arg_obj.sc );
            o.trans_expression( source, buf, typespec_rval );
            buf.push_fa( ")" );
        }

        if( typespec_rval.type && typespec_rval.indirection != 1 )
        {
            return o.parse_err_fa( source, "Attach operator requires rvalue with indirection '1'" );
        }

        if( out_typespec ) out_typespec.copy( in_typespec );
    }
    // ternary branch operator
    else if( source.parse_bl_fa( "#?'?'" ) )
    {
        buf.push_sc( "?" );
        xoico_typespec_s* typespec_true  = scope( xoico_typespec_s! );

        o.trans_expression( source, buf, typespec_true );
        o.parse( source, ": " );
        buf.push_sc( ": " );
        o.trans_expression( source, buf, NULL );

        if( out_typespec && typespec_true.type )
        {
            out_typespec.copy( typespec_true );
            out_typespec.flag_addressable = false;
        }
    }
    else if( out_typespec )
    {
        out_typespec.copy( in_typespec );
    }
    return 0;
} // try
};

//----------------------------------------------------------------------------------------------------------------------

func (:) (er_t trans_member( mutable, bcore_source* source, st_s* buf )) =
{
try
{
    if(      source.parse_bl_fa( "#?'.'"  ) ) buf.push_sc( "." );
    else if( source.parse_bl_fa( "#?'->'" ) ) buf.push_sc( "->" );

    o.trans_whitespace( source, buf );
    tp_t tp_identifier = o.get_identifier( source, false );

    if( o.is_builtin_func( tp_identifier ) )
    {
        return o.parse_err_fa( source, "Expression before '#<sc_t>' not tractable\n", o.nameof( tp_identifier ) );
    }

    o.trans_identifier( source, buf, NULL );
    o.trans_whitespace( source, buf );
    if( source.parse_bl_fa( "#?'('") )
    {
        return o.parse_err_fa( source, "Untraced member function '#<sc_t>'\n", o.nameof( tp_identifier ) );
    }
    return 0;
} // try
};

//----------------------------------------------------------------------------------------------------------------------

/** Tests for typespec
 *  If possible, takes typespec from source, otherwise leaves source unchanged
 */
func (:)
(
    er_t try_take_typespec
    (
        mutable,
        bcore_source* source,
        xoico_typespec_s* typespec,
        bl_t require_tractable_type,
        bl_t* success
    )
) =
{
try
{
    if( success ) *success = false;

    sz_t index = source.get_index();

    o.trans_whitespace( source, NULL );
    tp_t tp_identifier = o.get_identifier( source, true );

    if( !tp_identifier )
    {
        source.set_index( index );
        return 0;
    }

    o.trans_whitespace( source, NULL );

    while
    (
        tp_identifier == TYPEOF_const ||
        tp_identifier == TYPEOF_static ||
        tp_identifier == TYPEOF_volatile ||
        tp_identifier == TYPEOF_keep
    )
    {
        if( tp_identifier == TYPEOF_const    ) typespec.flag_const    = true;
        if( tp_identifier == TYPEOF_static   ) typespec.flag_static   = true;
        if( tp_identifier == TYPEOF_volatile ) typespec.flag_volatile = true;
        if( tp_identifier == TYPEOF_keep     ) typespec.flag_keep     = true;

        // take fails if keyword is actually a function
        if( source.parse_bl_fa( "#?'('" ) )
        {
            source.set_index( index );
            return 0;
        }

        o.trans_identifier( source, NULL, &tp_identifier );
        o.trans_whitespace( source, NULL );
    }

    typespec.type = tp_identifier;
    while( source.parse_bl_fa( "#?'*'" ) )
    {
        typespec.indirection++;
        o.trans_whitespace( source, NULL );
    }

    if( require_tractable_type )
    {
        if( !( tp_identifier == TYPEOF_type_deduce || o.is_type( tp_identifier ) ) )
        {
            source.set_index( index );
            return 0;
        }
    }

    if( success ) *success = true;
    return 0;
} // try
};

//----------------------------------------------------------------------------------------------------------------------

func (:)
(
    er_t take_typespec
    (
        mutable,
        bcore_source* source,
        xoico_typespec_s* typespec,
        bl_t require_tractable_type
    )
) =
{
try
{
    bl_t success = false;
    o.try_take_typespec( source, typespec, require_tractable_type, &success );

    if( !success )
    {
        if( require_tractable_type )
        {
            return o.parse_err_fa( source, "Typespec: Syntax error or intractable type." );
        }
        else
        {
            return o.parse_err_fa( source, "Typespec: Syntax error." );
        }
    }

    return 0;
} // try
};

//----------------------------------------------------------------------------------------------------------------------

func (:)
(
    er_t push_typespec
    (
        mutable,
        const xoico_typespec_s* typespec,
        st_s* buf
    )
) =
{
try
{
    tp_t type = typespec.type;

    if( type == TYPEOF_type_object )
    {
        type = o.obj_type;
    }
    else if( type == TYPEOF_type_deduce )
    {
        ERR_fa( "Cannot resolve 'type_deduce' at this point." );
    }
    else if( type == 0 )
    {
        ERR_fa( "Type is 0." );
    }

    st_s* st_type = scope( cast( st_s_create_sc( o.nameof( type ) ), st_s* ) );

    if( st_type.size == 0 )
    {
        ERR_fa( "Type has no name." );
    }

    sc_t sc_type = st_type.sc;
    if( typespec.flag_static   ) buf.push_fa( "static " );
    if( typespec.flag_const    ) buf.push_fa( "const " );
    if( typespec.flag_volatile ) buf.push_fa( "volatile " );
    st_s_push_fa( buf, "#<sc_t>", sc_type );

    for( sz_t i = 0; i < typespec.indirection; i++ ) buf.push_fa( "*" );
    if( typespec.flag_restrict ) buf.push_fa( "restrict " );

    return 0;
} // try
};

//----------------------------------------------------------------------------------------------------------------------

func (:)
(
    er_t trans_expression
    (
        mutable,
        bcore_source* source,
        st_s* buf_out, // can be NULL
        xoico_typespec_s* out_typespec // optional
    )
) =
{
try
{
    sc_t sc_bl_end_of_expression = "#?([0]==';'||[0]=='{'||[0]=='}'||[0]==')'||[0]==']'||[0]==','||([0]==':'&&([1]==' '||[1]=='\t'||[1]=='\n'||[1]=='/')))";

    o.trans_whitespace( source, buf_out );

    st_s* buf = scope( st_s! );
    bl_t continuation = true;

    if( out_typespec ) out_typespec.reset();

    tp_t tp_identifier = o.get_identifier( source, false );

    if( tp_identifier )
    {
        // examples of builtin functions: scope, cast, try, fork
        if( o.is_builtin_func( tp_identifier ) )
        {
            xoico_typespec_s* typespec_builtin = scope( xoico_typespec_s! );
            o.trans_builtin( tp_identifier, source, NULL, NULL, buf, typespec_builtin );
            o.trans_typespec_expression( source, buf, typespec_builtin, out_typespec );
        }

        else if( tp_identifier == TYPEOF_verbatim_C )
        {
            o.parse( source, "verbatim_C {" );
            o.trans_block_inside_verbatim_c( source, buf );
            o.parse( source, " }" );
        }

        // a control name marks end of expression...
        else if( o.is_control_name( tp_identifier ) )
        {
            continuation = false;
        }

        // identifier represents a registered variable
        else if( o.is_var( tp_identifier ) )
        {
            o.trans_identifier( source, buf, NULL );
            o.trans_whitespace( source, buf );
            const xoico_typespec_s* typespec_var = o.stack_var.get_typespec( tp_identifier );
            o.trans_typespec_expression( source, buf, typespec_var, out_typespec );
        }

        // identifier represents a type known to the compiler
        else if( o.is_type( tp_identifier ) )
        {
            st_s* buf_type = scope( st_s! );
            o.trans_identifier( source, buf_type, NULL );
            o.trans_whitespace( source, buf_type );
            if( source.parse_bl_fa( "#?'!'" ) )
            {
                if( o.is_group( tp_identifier ) )
                {
                    return o.parse_err_fa( source, "Operator '!': lvalue is a group." );
                }
                buf.push_fa( "#<sc_t>_create()", o.nameof( tp_identifier ) );
                xoico_typespec_s* typespec = scope( xoico_typespec_s! );
                typespec.type = tp_identifier;
                typespec.indirection = 1;
                typespec.flag_addressable = false;
                o.trans_typespec_expression( source, buf, typespec, out_typespec );
            }
            else
            {
                buf.push_st( buf_type );
            }
        }

        // identifier represents a (global) function name
        else if( o.is_func( tp_identifier ) )
        {
            o.trans_identifier( source, buf, NULL );
            o.trans_whitespace( source, buf );
            if( source.parse_bl_fa( "#=?'('" ) ) // actual function call
            {
                const xoico_func_s* func = o.get_func( tp_identifier );
                if( !func.signature )
                {
                    return o.parse_err_fa( source, "Function #<sc_t> has no signature.", o.nameof( tp_identifier ) );
                }
                o.trans_function_args( source, func.signature, NULL, NULL, buf );
                o.trans_typespec_expression( source, buf, func.signature.typespec_ret, out_typespec );
            }
        }
        else
        {
            o.trans_identifier( source, buf, NULL );
            o.trans_expression( source, buf, NULL );
        }
    }

    // literals and members
    else if( source.parse_bl_fa( "#?([0]>='0'&&[0]<='9')" ) ) o.trans_number_literal( source, buf );
    else if( source.parse_bl_fa( "#=?'\"'" )                ) o.trans_string_literal( source, buf );
    else if( source.parse_bl_fa( "#=?|'|" )                 ) o.trans_char_literal( source, buf );
    else if( source.parse_bl_fa( "#=?'.'" )                 ) o.trans_member( source, buf );
    else if( source.parse_bl_fa( "#=?'->'" )                ) o.trans_member( source, buf );

    else if( source.parse_bl_fa( "#=?'=<'" )                ) return o.parse_err_fa( source, "Attach operator: Expression not tractable." );
    else if( o.trans_inert_operator( source, buf )          ) {} // inert operators are not interpreted by cdaleth and passed to the c-compiler

    // ternary branch operator
    else if( source.parse_bl_fa( "#?'?'" ) )
    {
        buf.push_sc( "?" );
        o.trans_expression( source, buf, NULL );
        o.trans( source, ": ", buf );
        o.trans_expression( source, buf, NULL );
    }

    // general bracket
    else if( source.parse_bl_fa( "#?'('" ) )
    {
        xoico_typespec_s* typespec_bracket = scope( xoico_typespec_s! );
        buf.push_char( '(' );
        while( !source.eos() )
        {
            o.trans_expression( source, buf, typespec_bracket );
            if     ( source.parse_bl_fa( "#?')'" ) ) break;
            else if( source.parse_bl_fa( "#?','" ) ) buf.push_char( ',' );
            else return o.parse_err_fa( source, "Syntax error in bracket expression." );
            typespec_bracket.type = 0;
        }
        buf.push_char( ')' );
        if( typespec_bracket.type ) o.trans_typespec_expression( source, buf, typespec_bracket, out_typespec );
    }

    // array subscript
    else if( source.parse_bl_fa( "#?'['" ) )
    {
        buf.push_sc( "[" );
        o.trans_expression( source, buf, NULL );
        o.parse( source, "]" );
        buf.push_sc( "]" );
    }

    // end of expression...
    else if( source.parse_bl_fa( sc_bl_end_of_expression ) )
    {
        continuation = false;
    }

    // unhandled
    else
    {
        return o.parse_err_fa( source, "Syntax error after '#<sc_t>'", buf.sc );
    }

    if( continuation )
    {
        if( !source.parse_bl_fa( sc_bl_end_of_expression ) )
        {
            if( out_typespec ) out_typespec.reset();
            o.trans_expression( source, buf, NULL );
        }
    }

    if( buf_out ) buf_out.push_st( buf );

    return 0;
} // try
};

//----------------------------------------------------------------------------------------------------------------------

/** Translates declaration including optional subsequent assignment.
 *  If no declaration was detected, source and buf_out are not modified.
 */
func (:)
(
    er_t try_trans_declaration
    (
        mutable,
        bcore_source* source,
        st_s* buf_out,
        bl_t* success
    )
) =
{
try
{
    if( success ) *success = false;

    xoico_typespec_s* typespec_var = xoico_typespec_s!.scope();

    sz_t index = source.get_index();

    st_s* buf_var = st_s!.scope();

    bl_t success_take_typespec = false;
    o.try_take_typespec( source, typespec_var, true, &success_take_typespec );

    if( !success_take_typespec )
    {
        source.set_index( index );
        return 0;
    }

    o.trans_whitespace( source, buf_var );

    if
    (
        typespec_var.type &&
        source.parse_bl_fa( "#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||[0]=='_')" )
    )
    {
        tp_t tp_identifier = 0;
        o.trans_identifier( source, buf_var, &tp_identifier );
        o.trans_whitespace( source, buf_var );

        bl_t pushed_typedecl = false;

        if( typespec_var.type != TYPEOF_type_deduce )
        {
            o.push_typedecl( typespec_var, tp_identifier );
            pushed_typedecl = true;
        }

        if( source.parse_bl_fa( "#?'='" ) )
        {
            buf_var.push_sc( "=" );
            xoico_typespec_s* typespec_expr = xoico_typespec_s!.scope();
            st_s* buf_expr = st_s!.scope();
            o.trans_expression( source, buf_expr, typespec_expr );

            if( typespec_var.type == TYPEOF_type_deduce )
            {
                if( !typespec_expr.type )
                {
                    return o.parse_err_fa( source, "Declaration-syntax: Deduce requested but expression is intractable." );
                }
                typespec_var.type = typespec_expr.type;
            }

            if( typespec_expr.type )
            {
                o.adapt_expression( source, typespec_expr, typespec_var, buf_expr, buf_var );
            }
            else
            {
                buf_var.push_st( buf_expr );
            }
        }
        else
        {
            if( typespec_var.type == TYPEOF_type_deduce )
            {
                return o.parse_err_fa( source, "Declaration-syntax: Deduce requested without assignment." );
            }
        }

        if( !pushed_typedecl )
        {
            o.push_typedecl( typespec_var, tp_identifier );
            pushed_typedecl = true;
        }

        o.push_typespec( typespec_var, buf_out );
        buf_out.push_char( ' ' );
        buf_out.push_st( buf_var );

        if( success ) *success = true;
    }
    else
    {
        source.set_index( index );
        return 0;
    }

    if( success ) *success = true;

    return 0;
} // try
};

//----------------------------------------------------------------------------------------------------------------------

func(:) (er_t inspect_variable( mutable, bcore_source* source )) =
{
try
{
    o.parse( source, "\?\?" );

    st_s* st        = st_s!.scope();
    st_s* buf_local = st_s!.scope();
    xoico_typespec_s* typespec = xoico_typespec_s!.scope();
    o.parse_fa( source, " #until';' ", st );
    o.parse_fa( source, ";" );
    bcore_msg_fa( " \?? #<sc_t>;\n", st.sc );
    if( o.trans_expression( cast( bcore_source_string_s_create_fa( "#<st_s*>;", st ), bcore_source* ).scope(), buf_local, typespec ) )
    {
        bcore_error_pop_to_sink( BCORE_STDOUT );
        bcore_msg_fa( "\n" );
    }
    else
    {
        if( st.size == 0 ) return o.parse_err_fa( source, "Variable name expected." );
        bcore_msg_fa( "--> #<sc_t>;\n", buf_local.sc );

        if( typespec.type )
        {
            bcore_msg_fa( "Expression yields typespec:\n" );
            bcore_msg_fa( "  const      : #<bl_t>\n", typespec.flag_const );
            bcore_msg_fa( "  type       : #<sc_t>\n", o.nameof( typespec.type ) );
            bcore_msg_fa( "  indirection: #<sz_t>\n", typespec.indirection );
        }
        else
        {
            bcore_msg_fa( "Expression does not yield a typespec.\n" );
        }
    }
    return 0;

} // try
};

//----------------------------------------------------------------------------------------------------------------------

func (:) (er_t trans_statement( mutable, bcore_source* source, st_s* buf )) =
{
try
{
    o.trans_whitespace( source, buf );

    if( source.parse_bl_fa( "#?([0]=='{'||[0]=='#'||[0]==';'||[0]==','||[0]==')'||[0]=='}'||([0]=='?'&&[1]=='?'))" ) )
    {
        char c = source.inspect_char();
        switch( c )
        {
            case '{':
            {
                o.trans_block( source, buf, false );
            }
            break;

            case '#':
            {
                o.trans_preprocessor( source, buf );
            }
            break;

            case ';':
            {
                source.get_char();
                buf.push_char( ';' );
            }
            break;

            case ',':
            {
                source.get_char();
                buf.push_char( ',' );
            }
            break;

            case '?':
            {
                o.inspect_variable( source );
            }
            break;

            case ')':
            {
                return o.parse_err_fa( source, "Unmatched closing bracket." );
            }
            break;

            case '}':
            {
                // nothing (caller is a block-handler)
            }
            break;

            default: break;
        }
    }
    else
    {
        tp_t tp_identifier = o.get_identifier( source, false );

        if( tp_identifier && o.is_control_name( tp_identifier ) )
        {
            o.trans_control( tp_identifier, source, buf );
        }
        else
        {
            bl_t success_declaration = false;
            o.try_trans_declaration( source, buf, &success_declaration );

            if( !success_declaration )
            {
                if( o.try_block_level > 0 )
                {
                    xoico_typespec_s* typespec = xoico_typespec_s!.scope();
                    st_s* buf_expr = st_s!.scope();
                    o.trans_expression( source, buf_expr, typespec );
                    if
                    (
                        ( typespec.type == TYPEOF_er_t ) &&
                        ( typespec.indirection == 0 ) &&
                        ( typespec.flag_addressable == false )
                    )
                    {
                        if( !source.parse_bl_fa( " #?';'" ) )
                        {
                            return o.parse_err_fa( source, "Inside a try-block: Expressions yielding 'er_t' must end with ';'" );
                        }
                        buf.push_fa( "BLM_TRY(#<sc_t>)", buf_expr.sc );
                    }
                    else
                    {
                        buf.push_st( buf_expr );
                    }
                }
                else
                {
                    o.trans_expression( source, buf, NULL );
                }

                o.trans_whitespace( source, buf );

                // ':' between expressions is to be taken literally
                if( source.parse_bl_fa( "#?':'" ) ) buf.push_char( ':' );
            }
        }
    }

    return 0;
}
};

//----------------------------------------------------------------------------------------------------------------------

func (:) (er_t trans_block_inside( mutable, bcore_source* source, st_s* buf_out )) =
{
try
{
    st_s* buf = st_s!.scope();

    while( !source.parse_bl_fa( "#=?'}'" ) && !source.eos() )
    {
        o.trans_statement( source, buf );
    }

    if( o.stack_block_get_top_unit().use_blm )
    {
        buf_out.push_fa( "BLM_INIT_LEVEL(#<sz_t>);", o.level );
        buf_out.push_st( buf );

        if( ( o.level > 0 ) || !o.returns_a_value() )
        {
            buf_out.push_sc( "BLM_DOWN();" );
        }
    }
    else
    {
        buf_out.push_st( buf );
    }

    return 0;
} // try
};

//----------------------------------------------------------------------------------------------------------------------

func (:) (er_t trans_block( mutable, bcore_source* source, st_s* buf, bl_t is_break_ledge )) =
{
try
{
    o.inc_block();
    o.stack_block_get_top_unit().break_ledge = is_break_ledge;
    o.trans_whitespace( source, buf );
    o.trans( source, "{", buf );
    o.trans_block_inside( source, buf );
    o.trans_whitespace( source, buf );
    o.trans( source, "}", buf );
    o.dec_block();
    return 0;
} // try
};

//----------------------------------------------------------------------------------------------------------------------

func (:) (er_t trans_statement_as_block( mutable, bcore_source* source, st_s* buf_out, bl_t is_break_ledge )) =
{
try
{
    st_s* buf = st_s!.scope();

    o.inc_block();
    o.stack_block_get_top_unit().break_ledge = is_break_ledge;

    o.trans_statement( source, buf );
    o.trans_whitespace( source, buf );
    if( source.parse_bl_fa( "#?';'" ) ) buf.push_sc( ";" );

    if( o.stack_block_get_top_unit().use_blm )
    {
        buf_out.push_fa( "{BLM_INIT_LEVEL(#<sz_t>);", o.level );
        buf_out.push_st( buf );
        buf_out.push_sc( "BLM_DOWN();}" );
    }
    else
    {
        buf_out.push_st( buf );
    }

    o.dec_block();
    return 0;
} // try
};

//----------------------------------------------------------------------------------------------------------------------

func (:) (er_t trans_block_inside_verbatim_c( mutable, bcore_source* source, st_s* buf )) =
{
try
{
    o.trans_whitespace( source, buf );
    while( !source.parse_bl_fa( "#=?'}'" ) && !source.eos() )
    {
        switch( source.inspect_char() )
        {
            case '"':
            {
                o.trans_string_literal( source, buf );
            }
            break;

            case '\'':
            {
                o.trans_char_literal( source, buf );
            }
            break;

            case '{':
            {
                buf.push_char( source.get_char() );
                o.trans_block_inside_verbatim_c( source, buf );
                o.parse( source, "}" );
                buf.push_char( '}' );
            }
            break;

            default:
            {
                buf.push_char( source.get_char() );
            }
            break;
        }
        o.trans_whitespace( source, buf );
    }
    return 0;
} // try
};

//----------------------------------------------------------------------------------------------------------------------

func (:) (er_t setup( mutable, const xoico_body_s* body, const xoico_signature_s* signature )) =
{
try
{
    sc_t sc_obj_type = ( signature.arg_o ) ? ( body.stamp ? body.stamp.st_name.sc : body.group.st_name.sc ) : NULL;

    const xoico_args_s* args = &signature.args;

    tp_t obj_type  = ( signature.arg_o == 0 ) ? 0 : o.entypeof( sc_obj_type );
    bl_t obj_const = ( signature.arg_o == TYPEOF_const );
    tp_t obj_name  = o.entypeof( "o" );

    o.args     = args.cast( xoico_args_s* );
    o.typespec_ret = signature.typespec_ret.cast( xoico_typespec_s* );
    o.group    = body.code.group;
    o.stamp    = body.code.stamp;
    o.compiler = body.group.compiler;
    o.obj_type = obj_type;
    o.level    = 0;
    o.try_block_level = 0;
    o.stack_var.clear();
    o.init_level0();

    xoico_cdaleth_stack_var_unit_s* unit = xoico_cdaleth_stack_var_unit_s!.scope();

    if( obj_type )
    {
        unit.typespec.flag_const = obj_const;
        unit.typespec.type = obj_type;
        unit.typespec.indirection = 1;
        unit.name = obj_name;
        unit.level = o.level;
        o.stack_var.push_unit( unit );
        o.hmap_name.set_sc( o.compiler.nameof( obj_type ) );
        o.hmap_name.set_sc( o.compiler.nameof( obj_name ) );
    }

    foreach( $* arg in args )
    {
        if( arg.typespec.type && arg.name )
        {
            unit.typespec.copy( arg.typespec );
            if( obj_type ) unit.typespec.relent( o.group, obj_type );
            unit.name = arg.name;
            unit.level = o.level;
            o.stack_var.push_unit( unit );
            o.hmap_name.set_sc( o.compiler.nameof( arg.typespec.type ) );
            o.hmap_name.set_sc( o.compiler.nameof( arg.name ) );
        }
    }
    return 0;
} // try
};

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico_cengine.translate =
{
try
{
    xoico_cdaleth_s* engine = o.clone().scope();
    engine.setup( body, signature );

    bcore_source* source = cast( bcore_source_point_s_clone_source( &body.code.source_point ), bcore_source* ).scope();

    st_s* buf = st_s!.scope();

    sz_t indent = 0;
    engine.parse( source, " {" );

    while( source.parse_bl_fa( "#?([0]==' '||[0]=='\t')" ) ) { source.get_char(); };
    if( source.parse_bl_fa( "#?'\n'" ) )
    {
        while( source.parse_bl_fa( "#?' '" ) ) indent++;
    }

    engine.trans_block_inside( source, buf );

    engine.parse( source, " }" );

    if( indent > 0 ) buf.replace_st_d_st_d( st_s_create_fa( "\n#rn{ }", indent ), st_s_create_sc( "\n" ) );

    //remove trailing whitespaces
    for( sz_t i = buf.size - 1; i >= 0; i-- )
    {
        if( buf.[ i ] != ' ' && buf.[ i ] != '\t' && buf.[ i ] != '\n' ) break;
        buf.[ i ] = 0;
        buf.size = i;
    }

    if( engine.verbose )
    {
        bcore_sink_a_push_fa( BCORE_STDOUT, "##############################\n" );
        bcore_sink_a_push_fa( BCORE_STDOUT, "#<st_s*>\n", buf );
    }

    if( engine.insert_source_reference && !body.code.single_line )
    {
        sink.push_fa( "// " );
        body.code.source_point.source_reference_to_sink( true, sink );
        sink.push_fa( "\n" );
    }

    sink.push_sc( buf.sc );

    return 0;
} // try
};

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

