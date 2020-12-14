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
func (:s) (tp_t get_identifier( mutable, bcore_source* source, bl_t take_from_source )) =
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
                st_s* st_name = st_s!.scope();
                st_name.copy_sc( o.nameof( o.host.obj_type() ) );
                if( source.parse_bl( "#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||[0]=='_'||([0]>='0'&&[0]<='9'))" ) )
                {
                    source.parse_fa( "#:name", st_name );
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
                o.host.parse_name_tp( source, tp_identifier.1 );
            }
            break;

            default:
            {
                st_s* st_name = st_s!.scope();
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
func(:s) (er_t trans_identifier( mutable, bcore_source* source, :result* result /* can be NULL */, tp_t* tp_identifier/* can be NULL */ )) = (try)
{
    tp_t identifier = o.get_identifier( source, true );
    if( !identifier )
    {
        return source.parse_error_fa( "Identifier exected" );
    }
    if( tp_identifier ) tp_identifier.0 = identifier;
    if( result ) result.push_sc( o.nameof( identifier ) );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

/** parses number: (all integer, hex and float encodings)*/
func(:s) (er_t trans_number_literal( mutable, bcore_source* source, :result* result )) = (try)
{
    bl_t hex = false;
    if( source.parse_bl( "#?'0x'" ) )
    {
        result.push_sc( "0x" );
        hex = true;
    }
    else if( source.parse_bl( "#?'0X'" ) )
    {
        result.push_sc( "0X" );
        hex = true;
    }

    if( hex )
    {
        while( source.parse_bl( "#?(([0]>='0'&&[0]<='9')||([0]>='a'&&[0]<='f')||([0]>='A'&&[0]<='F'))" ) )
        {
            result.push_char( source.get_char() );
        }
    }
    else // decimal
    {
        while( source.parse_bl( "#?([0]>='0'&&[0]<='9')" ) )
        {
            result.push_char( source.get_char() );
        }
    }

    bl_t fraction = false;

    if( source.parse_bl( "#?([0]=='.')" ) )
    {
        result.push_char( source.get_char() );
        fraction = true;
    }

    if( fraction )
    {
        while( source.parse_bl( "#?([0]>='0'&&[0]<='9')" ) )
        {
            result.push_char( source.get_char() );
        }
    }

    bl_t exponent = false;

    if( source.parse_bl( "#?([0]=='e'&&[0]=='E')" ) )
    {
        result.push_char( source.get_char() );
        exponent = true;
    }

    if( exponent )
    {
        if( source.parse_bl( "#?([0]=='+'||[0]=='-')" ) )
        {
            result.push_char( source.get_char() );
        }

        while( source.parse_bl( "#?([0]>='0'&&[0]<='9')" ) )
        {
            result.push_char( source.get_char() );
        }
    }

    // suffix
    while( source.parse_bl( "#?([0]=='l'||[0]=='L'||[0]=='u'||[0]=='U'||[0]=='f'||[0]=='F')" ) )
    {
        result.push_char( source.get_char() );
    }

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

/// parses string
func (:s) (er_t trans_string_literal( mutable, bcore_source* source, :result* result )) = (try)
{
    o.trans( source, "\"", result );

    while( !source.eos() && !source.parse_bl( "#=?'\"'" ) )
    {
        if( source.parse_bl( "#?'\\'" ) ) result.push_char( '\\' );
        result.push_char( source.get_char() );
    }

    o.trans( source, "\"", result );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

/// character literal
func (:s) (er_t trans_char_literal( mutable, bcore_source* source, :result* result )) =
{
try
{
    o.trans( source, "'", result );

    while( !source.eos() && !source.parse_bl( "#=?|'|" ) )
    {
        if( source.parse_bl( "#?'\\'" ) ) result.push_char( '\\' );
        result.push_char( source.get_char() );
    }

    o.trans( source, "'", result );
    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

/// parses whitespaces including comments
func (:s) (er_t trans_whitespace( mutable, bcore_source* source, :result* result /* can be NULL */ )) = (try)
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
                if( result )  result.push_char( c );
            }
            break;

            case '/':
            {
                if( source.parse_bl( "#?'//'" ) )
                {
                    if( result ) result.push_sc( "//" );
                    while( !source.eos() )
                    {
                        char c =  source.get_char();
                        if( result ) result.push_char( c );
                        if( c == '\n' ) break;
                    }
                }
                else if( source.parse_bl( "#?'/*'" ) )
                {
                    if( result ) result.push_sc( "/*" );
                    while( !source.eos() )
                    {
                        if( source.parse_bl( "#?'*/'" ) )
                        {
                            if( result ) result.push_sc( "*/" );
                            break;
                        }
                        char c =  source.get_char();
                        if( result ) result.push_char( c );
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
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) (er_t trans_preprocessor( mutable, bcore_source* source, :result* result )) = (try)
{
    source.parse_em_fa( "##" );
    result.push_sc( "#" );
    while( !source.eos() )
    {
        char c = source.get_char();
        result.push_char( c );
        if( c == '\\' && source.inspect_char() == '\n' ) result.push_char( source.get_char() );
        if( c == '\n' ) break;
    }
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

// any state; returns !=0 in case an operator was consumed
func (:s) (tp_t trans_inert_operator( mutable, bcore_source* source, :result* result )) =
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
            result.push_char( source.get_char() );
            return 1;
        }
        break;

        default: break;
    }

    return false;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) (bl_t trans_operator( mutable, bcore_source* source, :result* result )) =
{
    switch( source.inspect_char() )
    {
        case '+':
        {
            result.push_char( source.get_char() );
            char c = source.inspect_char();
            if( c == '=' || c == '+' ) result.push_char( source.get_char() );
        }
        return true;

        case '-':
        {
            result.push_char( source.get_char() );
            char c = source.inspect_char();
            if( c == '=' || c == '-' ) result.push_char( source.get_char() );
        }
        return true;

        case '*':
        case '/':
        case '=':
        case '!':
        case '^':
        case '%':
        {
            result.push_char( source.get_char() );
            if( source.inspect_char() == '=' ) result.push_char( source.get_char() );
        }
        return true;

        case '>':
        {
            result.push_char( source.get_char() );
            char c = source.inspect_char();
            if( c == '=' || c == '>' ) result.push_char( source.get_char() );
            if( c == '>' && source.inspect_char() == '=' ) result.push_char( source.get_char() );
        }
        return true;

        case '<':
        {
            result.push_char( source.get_char() );
            char c = source.inspect_char();
            if( c == '=' || c == '<' ) result.push_char( source.get_char() );
            if( c == '<' && source.inspect_char() == '=' ) result.push_char( source.get_char() );
        }
        return true;

        case '|':
        {
            result.push_char( source.get_char() );
            char c = source.inspect_char();
            if( c == '=' || c == '|' ) result.push_char( source.get_char() );
        }
        return true;

        case '&':
        {
            result.push_char( source.get_char() );
            char c = source.inspect_char();
            if( c == '=' || c == '&' ) result.push_char( source.get_char() );
        }
        return true;

        case '~':
        {
            result.push_char( source.get_char() );
        }
        return true;

        default: break;
    }

    return false;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s)
(
    er_t adapt_expression_indirection
    (
        mutable,
        bcore_source* source,
        const xoico_typespec_s* typespec_expr,
        sz_t target_indirection,
        const :result* result_expr,
        :result* result
    )
) = (try)
{
    if( target_indirection == typespec_expr.indirection )
    {
        result.push_result_c( result_expr );
    }
    else if( target_indirection == typespec_expr.indirection + 1 )
    {
        if( typespec_expr.flag_addressable )
        {
            result.push_sc( "&(" );
            result.push_result_c( result_expr );
            result.push_sc( ")" );
        }
        else
        {
            return source.parse_error_fa( "Increasing indirection: Expression has no address." );
        }
    }
    else if( target_indirection < typespec_expr.indirection )
    {
        for( sz_t ind = typespec_expr.indirection; ind > target_indirection; ind-- ) result.push_sc( "*" );
        result.push_sc( "(" );
        result.push_result_c( result_expr );
        result.push_sc( ")" );
    }
    else
    {
        return source.parse_error_fa
        (
            "Cannot adapt from expression's indirection '#<sz_t>' to target indirection '#<sz_t>'.",
            typespec_expr.indirection,
            target_indirection
        );
    }
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s)
(
    er_t adapt_expression
    (
        mutable,
        bcore_source* source,
        const xoico_typespec_s* typespec_expr,
        const xoico_typespec_s* typespec_target,
        const :result* result_expr,
        :result* result
    )
) = (try)
{
    if( !typespec_expr.type )
    {
        return source.parse_error_fa
        (
            "xoico_che_s_adapt_expression: no expression type specified.",
            typespec_expr.indirection,
            typespec_target.indirection
        );
    }

    if( !typespec_target.type )
    {
        return source.parse_error_fa
        (
            "xoico_che_s_adapt_expression: no target type specified.",
            typespec_expr.indirection,
            typespec_target.indirection
        );
    }

    if( typespec_target.type == TYPEOF_type_deduce ) return source.parse_error_fa( "adapt_expression: typespec_target is 'type_deduce'" );
    if( typespec_target.type == TYPEOF_type_object ) return source.parse_error_fa( "adapt_expression: typespec_target is 'type_object'" );
    if( typespec_expr.type == TYPEOF_type_deduce ) return source.parse_error_fa( "adapt_expression: typespec_expr is 'type_deduce'" );
    if( typespec_expr.type == TYPEOF_type_object ) return source.parse_error_fa( "adapt_expression: typespec_expr is 'type_object'" );

    bl_t discarding_const =
        ( typespec_expr.flag_const && !typespec_target.flag_const ) &&
        ( typespec_expr.indirection > 0 || typespec_target.indirection > 0 );

    if( discarding_const ) return source.parse_error_fa( "Discarding 'const' qualifier." );

    if( typespec_expr.converts_to( typespec_target ) )
    {
        result.push_result_c( result_expr );
    }
    else
    {
        bl_t implicit_cast = false;
        st_s* fail_msg = NULL;
        if( typespec_target.type != typespec_expr.type )
        {
            if( o.is_group( typespec_target.type ) && typespec_target.indirection == 1 )
            {
                if( o.is_group( typespec_expr.type ) )
                {
                    implicit_cast = true;
                }
                else if( o.is_stamp( typespec_expr.type ) )
                {
                    const xoico_stamp_s* stamp = o.get_stamp( typespec_expr.type );
                    if( stamp.is_aware || typespec_target.flag_unaware )
                    {
                        implicit_cast = true;
                    }
                    else
                    {
                        fail_msg = st_s_create_fa( "'#<sc_t>' is unaware but the target typespec does not explicitly tolerate unaware objects.", o.nameof( typespec_expr.type ) ).scope();
                    }
                }
                else
                {
                    fail_msg = st_s_create_fa( "Source type cannot be classified." ).scope();
                }
            }
            else
            {
                fail_msg = st_s_create_fa( "Target is not a group or target indirection is != 1." ).scope();
            }
        }

        if( fail_msg )
        {
            $* st_typespec_expr = st_s!.scope();
            $* st_typespec_target = st_s!.scope();
            o.typespec_to_sink( typespec_expr, st_typespec_expr );
            o.typespec_to_sink( typespec_target, st_typespec_target );
            $* msg = st_s!.scope();
            msg.push_fa( "Implicit cast from '#<sc_t>' to '#<sc_t>' is not allowed. ", st_typespec_expr.sc, st_typespec_target.sc );
            msg.push_fa( "Reason: #<st_s*>\n", fail_msg );
            return source.parse_error_fa( "#<st_s*>", msg );
        }

        if( implicit_cast )
        {
            result.push_sc( "((" );
            o.push_typespec( typespec_target, result );
            result.push_sc( ")(" );
        }
        o.adapt_expression_indirection( source, typespec_expr, typespec_target.indirection, result_expr, result );
        if( implicit_cast ) result.push_sc( "))" );
    }
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

/// Processes the argument section '(....)' of a function
func (:s)
(
    er_t trans_function_args
    (
        mutable,
        bcore_source* source,
        tp_t object_type,
        const xoico_signature_s* signature,
        const xoico_transient_map_s* transient_map,
        const :result* result_obj_expr,
        const xoico_typespec_s* typespec_obj_expr,
        :result* result_out,
        tp_t* transient_type
    )
) = (try)
{
    o.trans( source, "(", result_out );

    tp_t transient_class = signature.typespec_ret.transient_class;

    if( signature.arg_o )
    {
        if( !result_obj_expr )
        {
            $* result_expr   = :result_create_arr().scope();
            $* typespec_expr = xoico_typespec_s!.scope();
            o.trans_expression( source, result_expr, typespec_expr );
            result_obj_expr = result_expr;
            typespec_obj_expr = typespec_expr;
            if( signature.args.size > 0 ) source.parse_em_fa( " ," );
        }

        xoico_typespec_s* typespec_obj_out = xoico_typespec_s!.scope();
        typespec_obj_out.type = object_type ? object_type : typespec_obj_expr.type;
        typespec_obj_out.flag_const = signature.arg_o == TYPEOF_const;
        typespec_obj_out.indirection = 1; // first argument of a member function has always indirection 1

        if( signature.typed )
        {
            if( typespec_obj_expr.type )
            {
                result_out.push_fa( "TYPEOF_#<sc_t>,", o.nameof( typespec_obj_expr.type ) );
            }
            else
            {
                return source.parse_error_fa( "Function requires a typed object reference but object expression is not tractable." );
            }
        }

        if( typespec_obj_expr.type )
        {
            if( !transient_map ) transient_map = o.get_transient_map( typespec_obj_expr.type );
            if( transient_class && transient_type && ( transient_type.0 == 0 ) && ( signature.arg_o_transient_class == transient_class ) )
            {
                transient_type.0 = typespec_obj_expr.type;
            }
            o.adapt_expression( source, typespec_obj_expr, typespec_obj_out, result_obj_expr, result_out );
        }
        else
        {
            result_out.push_result_c( result_obj_expr );
        }
        if( signature.args.size > 0 ) result_out.push_sc( "," );
    }

    if( transient_map && transient_class && transient_type )
    {
        tp_t type = transient_map.get( transient_class );
        if( type )
        {
            if( !transient_type.0 )
            {
                transient_type.0 = type;
            }
            else if( transient_type.0 != type )
            {
                return source.parse_error_fa( "Object type expected: '#<sc_t>'. Object type passed: '#<sc_t>'.", o.nameof( type ), o.nameof( transient_type.0 ) );
            }
        }
    }

    foreach( const $* arg in signature.args )
    {
        if( arg.is_variadic() ) break;

        $* result_expr = :result_arr_s!.scope();
        $* typespec_expr = xoico_typespec_s!.scope( scope_local );
        source.parse_em_fa( " " );

        if( __i > 0 )
        {
            source.parse_em_fa( " ," );
            result_out.push_sc( "," );
        }

        o.trans_whitespace( source, result_expr );
        if( source.parse_bl( "#?')'" ) ) return source.parse_error_fa( "Function argument '#<sc_t>': No value passed.", o.nameof( arg.name ) );

        o.trans_expression( source, result_expr, typespec_expr );

        if( typespec_expr.type )
        {
            if( arg.typespec.transient_class )
            {
                if( transient_type && ( transient_type.0 == 0 ) && ( arg.typespec.transient_class == transient_class ) )
                {
                    transient_type.0 = typespec_expr.type;
                }

                if( transient_map )
                {
                    tp_t type = transient_map.get( arg.typespec.transient_class );
                    if( type && typespec_expr.type != type )
                    {
                        return source.parse_error_fa( "Function argument '#<sc_t>': Type expected: '#<sc_t>'. Type passed: '#<sc_t>'.", o.nameof( arg.name ), o.nameof( type ), o.nameof( typespec_expr.type ) );
                    }
                }
            }

            o.adapt_expression( source, typespec_expr, arg.typespec, result_expr, result_out );
        }
        else
        {
            result_out.push_result_d( result_expr.fork() );
        }
    }

    if( signature.args.is_variadic() )
    {
        while( !source.eos() && !source.parse_bl( " #=?')'" ) )
        {
            source.parse_em_fa( " ," );
            result_out.push_sc( "," );
            o.trans_expression( source, result_out, NULL );
        }
    }

    source.parse_em_fa( " " );
    o.trans( source, ")", result_out );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s)
(
    er_t trans_typespec_member
    (
        mutable,
        bcore_source* source,
        :result* result,
        const xoico_typespec_s*  in_typespec, // required
              xoico_typespec_s* out_typespec  // optional
    )
) = (try)
{
    if( source.parse_bl( "#?'->'" ) )
    {
        if( in_typespec.indirection != 1 )
        {
            return source.parse_error_fa( "Given indirection is '#<sz_t>'. '->' can only be used at indirection '1'.", in_typespec.indirection );
        }
    }
    else
    {
        source.parse_em_fa( "." );
    }
    source.parse_em_fa( " " );
    xoico_compiler_element_info_s* info = xoico_compiler_element_info_s!.scope();

    char c = source.inspect_char();

    if( c == '*' || c == '&' )
    {
        return source.parse_error_fa( "Postfix operators '&' and '*' are deprecated. Use numeric indirection level.\n" );
    }

    if( c >= '0' && c <= '9' )
    {
        $* typespec_adapted = in_typespec.clone().scope();
        sz_t adapted_indirection = 0;
        source.parse_em_fa( "#<sz_t*>", &adapted_indirection );

        typespec_adapted.indirection = adapted_indirection;

        $* result_adapted = :result_arr_s!.scope();
        result_adapted.push_sc( "(" );
        o.adapt_expression( source, in_typespec, typespec_adapted, result, result_adapted );
        result_adapted.push_sc( ")" );
        result.clear();
        result.push_result_d( result_adapted.fork() );
        o.trans_typespec_expression( source, result, typespec_adapted, out_typespec );
        return 0;
    }

    if( source.parse_bl( "#=?'['" ) || source.parse_bl( "#=?'?['" ) ) // array subscript
    {
        bl_t bounds_check = false;
        if( source.parse_bl( "#=?'?'" ) )
        {
            source.parse_em_fa( "?[" );
            bounds_check = true;
        }
        else
        {
            source.parse_em_fa( "[" );
        }

        if( bounds_check ) return source.parse_error_fa( "Bounds check not yet available." );

        if( in_typespec.indirection > 1 )
        {
            return source.parse_error_fa
            (
                "Resolving subscript: Indirection '#<sz_t>' is too large.",
                in_typespec.indirection
            );
        }

        result.push_fa( "#<sc_t>data[", ( in_typespec.indirection == 1 ) ? "->" : "." );
        o.trans_expression( source, result, NULL );
        source.parse_em_fa( "]" );
        result.push_sc( "]" );

        if( o.compiler.get_type_array_element_info( in_typespec.type, info ) )
        {
            o.trans_typespec_expression( source, result, info.type_info.typespec, out_typespec );
        }
        else
        {
            o.trans_expression( source, result, NULL );
        }
    }
    else // member (object or function)
    {
        $* result_local = :result_create_arr().scope();
        tp_t tp_identifier = 0;
        o.trans_identifier( source, result_local, tp_identifier );
        o.trans_whitespace( source, result_local );

        // builtin functions ...
        if( o.is_builtin_func( tp_identifier ) )
        {
            xoico_typespec_s* typespec_builtin = xoico_typespec_s!.scope();
            o.trans_builtin( tp_identifier, source, result, in_typespec, result_local, typespec_builtin );
            result.copy( result_local );
            o.trans_typespec_expression( source, result, typespec_builtin, out_typespec );
        }
        else if( o.compiler.get_type_element_info( in_typespec.type, tp_identifier, info ) )
        {
            if( info.func ) // member function
            {
                $* func = info.func;
                const $* signature = func.signature;
                tp_t object_type = func.obj_type;
                sc_t sc_func_name = o.nameof( func.global_name );
                ASSERT( sc_func_name );

                $* typespec_ret = signature.typespec_ret.clone().scope();
                tp_t transient_type = 0;

                $* result_arg_obj = result.clone().scope();
                result.clear();
                $* result_args = :result_arr_s!.scope();

                xoico_transient_map_s* transient_map = o.get_transient_map( in_typespec.type );

                o.trans_function_args
                (
                    source,
                    object_type,
                    signature,
                    transient_map,
                    result_arg_obj,
                    in_typespec,
                    result_args,
                    &transient_type
                );

                if( transient_type != 0 )
                {
                    typespec_ret.type = transient_type;
                    result.push_sc( "((" );
                    o.push_typespec( typespec_ret, result );
                    result.push_sc( ")(" );
                }

                result.push_fa( "#<sc_t>", sc_func_name );
                result.push_result_d( result_args.fork() );

                if( transient_type != 0 )
                {
                    result.push_sc( "))" );
                }

                o.trans_typespec_expression( source, result, typespec_ret, out_typespec );
            }
            else // traced member element
            {
                if( in_typespec.indirection > 1 )
                {
                    return source.parse_error_fa
                    (
                        "Dereferencing #<sc_t>: Indirection '#<sz_t>' is too large.",
                        o.nameof( tp_identifier ),
                        in_typespec.indirection
                    );
                }
                result.push_fa( "#<sc_t>", ( in_typespec.indirection == 1 ) ? "->" : "." );
                result.push_result_d( result_local.fork() );

                o.trans_typespec_expression( source, result, info.type_info.typespec, out_typespec );
            }
        }
        else if( source.parse_bl( "#?'('" ) ) // untraced member function
        {
            if( !o.waive_non_member_function ) return source.parse_error_fa( "'#<sc_t>' has no member function '#<sc_t>'.", o.nameof( in_typespec.type ), o.nameof( tp_identifier ) );
            $* result_arg_obj = result.clone().scope();
            result.clear();

            /// Untraced member functions of a group are always treated as 'aware'
            if( o.is_group( in_typespec.type ) )
            {
                result.copy_fa
                (
                    "#<sc_t>_a_#<sc_t>( ",
                    o.nameof( in_typespec.type ),
                    o.nameof( tp_identifier )
                );
            }
            else
            {
                result.copy_fa
                (
                    "#<sc_t>_#<sc_t>( ",
                    o.nameof( in_typespec.type ),
                    o.nameof( tp_identifier )
                );
            }

            {
                xoico_typespec_s* typespec_obj = in_typespec.clone().scope();
                typespec_obj.indirection = 1; // first argument of member functions
                o.adapt_expression( source, in_typespec, typespec_obj, result_arg_obj, result );
            }

            bl_t first = true;
            o.trans_whitespace( source, result_local );
            while( !source.eos() )
            {
                if( source.parse_bl( "#=?')'" ) ) break;

                $* result_expr = :result_create_arr().scope();
                if( !first ) source.parse_em_fa( "," );
                o.trans_expression( source, result_expr, NULL );
                o.trans_whitespace( source, result_expr );
                result.push_fa( "," );
                result.push_result_d( result_expr.fork() );
                first = false;
            }

            source.parse_em_fa( ")" );
            result.push_sc( ")" );

            o.trans_expression( source, result, NULL );
        }
        else // untraced member element
        {
            if( !o.waive_non_member_variable ) return source.parse_error_fa( "'#<sc_t>' has no member '#<sc_t>'.", o.nameof( in_typespec.type ), o.nameof( tp_identifier ) );
            result.push_fa( "#<sc_t>", ( in_typespec.indirection == 1 ) ? "->" : "." );
            result.push_result_d( result_local.fork() );
            o.trans_expression( source, result, NULL );
        }
    }
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s)
(
    er_t trans_typespec_array_subscript
    (
        mutable,
        bcore_source* source,
        :result* result,
        const xoico_typespec_s*  in_typespec, // required
              xoico_typespec_s* out_typespec  // optional
    )
) = (try)
{
    source.parse_em_fa( "[" );

    result.push_sc( "[" );
    o.trans_expression( source, result, NULL );
    source.parse_em_fa( "]" );
    result.push_sc( "]" );

    xoico_typespec_s* typespec = in_typespec.clone().scope();

    if( typespec.indirection == 0 )
    {
        if( in_typespec.type == TYPEOF_sc_t || in_typespec.type == TYPEOF_sd_t )
        {
            typespec.type = TYPEOF_u0_t;
        }
        else
        {
            return source.parse_error_fa( "Array subscript requires indirection >= 1." );
        }
    }
    else
    {
        typespec.indirection--;
    }

    o.trans_typespec_expression( source, result, typespec, out_typespec );

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s)
(
    er_t trans_typespec_create
    (
        mutable,
        bcore_source* source,
        :result* result,
        const xoico_typespec_s*  in_typespec, // required
              xoico_typespec_s* out_typespec  // optional
    )
) = (try)
{
    source.parse_em_fa( "!" );

    //ignore in case indirection is 0;
    if( in_typespec.indirection > 0 )
    {
        if( !( in_typespec.indirection == 1 && in_typespec.flag_addressable ) )
        {
            return source.parse_error_fa( "Create-Operator requires lvalue with addressable indirection of 1." );
        }

        if( xoico_che_s_is_group( o, in_typespec.type ) )
        {
            return source.parse_error_fa( "Create-Operator: lvalue is a group." );
        }

        $* result_arg_obj = result.clone().scope();
        result.clear();

        sc_t sc_type = o.nameof( in_typespec.type );
        result.push_fa( "BCORE_PASS_CREATE(#<sc_t>,", sc_type );
        result.push_result_d( result_arg_obj.fork() );
        result.push_sc( ")" );
    }

    o.trans_typespec_expression( source, result, in_typespec, out_typespec );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s)
(
    er_t trans_typespec_test_presence
    (
        mutable,
        bcore_source* source,
        :result* result,
        const xoico_typespec_s*  in_typespec, // required
              xoico_typespec_s* out_typespec  // optional
    )
) = (try)
{
    source.parse_em_fa( "?" );

    //ignore in case indirection is 0;
    if( in_typespec.indirection > 0 )
    {
        if( in_typespec.indirection != 1 )
        {
            return source.parse_error_fa( "Test-Operator requires lvalue with indirection of 1." );
        }

        $* result_arg_obj = result.clone().scope();
        result.clear();

        sc_t sc_type = o.nameof( in_typespec.type );
        result.push_fa( "BCORE_PASS_TEST(#<sc_t>,", sc_type );
        result.push_result_d( result_arg_obj.fork() );
        result.push_sc( ")" );
    }

    o.trans_typespec_expression( source, result, in_typespec, out_typespec );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s)
(
    er_t trans_typespec_attach
    (
        mutable,
        bcore_source* source,
        :result* result,
        const xoico_typespec_s*  in_typespec, // required
              xoico_typespec_s* out_typespec  // optional
    )
) = (try)
{
    if( !( in_typespec.indirection == 1 && in_typespec.flag_addressable ) )
    {
        return source.parse_error_fa( "Attach-Operator requires lvalue with addressable indirection of 1" );
    }

    source.parse_em_fa( "=<" );

    $* result_arg_obj = result.clone().scope();
    result.clear();

    sc_t sc_type = o.nameof( in_typespec.type );
    result.push_fa( "#<sc_t>", sc_type );

    xoico_typespec_s* typespec_rval = xoico_typespec_s!.scope();
    if( o.is_group( in_typespec.type ) )
    {
        result.push_sc( "_a" );
        result.push_sc( "_attach( &(" );
        result.push_result_d( result_arg_obj.fork() );
        result.push_fa( "), (#<sc_t>*)", sc_type );

        result.push_sc( "(" );
        o.trans_expression( source, result, typespec_rval );
        result.push_sc( "))" );
    }
    else
    {
        result.push_sc( "_attach( &(" );
        result.push_result_d( result_arg_obj.fork() );
        result.push_sc( "), " );
        o.trans_expression( source, result, typespec_rval );
        result.push_sc( ")" );
    }

    if( typespec_rval.type && typespec_rval.indirection != 1 )
    {
        return source.parse_error_fa( "Attach operator requires rvalue with indirection '1'" );
    }

    if( out_typespec ) out_typespec.copy( in_typespec );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s)
(
    er_t trans_typespec_ternary_branch
    (
        mutable,
        bcore_source* source,
        :result* result,
        const xoico_typespec_s*  in_typespec, // required
              xoico_typespec_s* out_typespec  // optional
    )
) = (try)
{
    source.parse_em_fa( "?" );
    result.push_sc( "?" );
    xoico_typespec_s* typespec_true  = xoico_typespec_s!.scope();

    o.trans_expression( source, result, typespec_true );
    source.parse_em_fa( ": " );
    result.push_sc( ": " );
    o.trans_expression( source, result, NULL );

    if( out_typespec && typespec_true.type )
    {
        out_typespec.copy( typespec_true );
        out_typespec.flag_addressable = false;
    }
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s)
(
    er_t trans_typespec_expression
    (
        mutable,
        bcore_source* source,
        :result* result,
        const xoico_typespec_s*  in_typespec, // required
              xoico_typespec_s* out_typespec  // optional
    )
) = (try)
{
    if( out_typespec ) out_typespec.type = 0;
    o.trans_whitespace( source, result );

    u0_t c[ 2 ];
    source.inspect_data( c, sizeof( c ) );

    if( c[0] == '.' || ( c[0] == '-' && c[1] == '>' ) )
    {
        o.trans_typespec_member( source, result, in_typespec, out_typespec );
    }
    else if( c[0] == '[' )
    {
        o.trans_typespec_array_subscript( source, result, in_typespec, out_typespec );
    }
    // create if not present
    else if( c[0] =='!' && c[1] != '=' )
    {
        o.trans_typespec_create( source, result, in_typespec, out_typespec );
    }
    // test for presence
    else if( c[0] == '?' && c[1] == '.' )
    {
        o.trans_typespec_test_presence( source, result, in_typespec, out_typespec );
    }
    // attach (detach)
    else if( c[0] == '=' && c[1] == '<' )
    {
        o.trans_typespec_attach( source, result, in_typespec, out_typespec );
    }
    // ternary branch operator
    else if( c[0] == '?' )
    {
        o.trans_typespec_ternary_branch( source, result, in_typespec, out_typespec );
    }
    else if( out_typespec )
    {
        out_typespec.copy( in_typespec );
    }

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) (er_t trans_member( mutable, bcore_source* source, :result* result )) = (try)
{
    if(      source.parse_bl( "#?'.'"  ) ) result.push_sc( "." );
    else if( source.parse_bl( "#?'->'" ) ) result.push_sc( "->" );

    o.trans_whitespace( source, result );

    char c = source.inspect_char();

    if( c == '*' || c == '&' )
    {
        return source.parse_error_fa( "Postfix operators '&' and '*' are deprecated.\n" );
    }

    if( c >= '0' && c <= '9' )
    {
        return source.parse_error_fa( "Setting indirection: Expression not tractable\n" );
    }

    tp_t tp_identifier = o.get_identifier( source, false );

    if( o.is_builtin_func( tp_identifier ) )
    {
        return source.parse_error_fa( "Expression before '#<sc_t>' not tractable\n", o.nameof( tp_identifier ) );
    }

    o.trans_identifier( source, result, NULL );
    o.trans_whitespace( source, result );
    if( source.parse_bl( "#?'('") )
    {
        return source.parse_error_fa( "Untraced member function '#<sc_t>'\n", o.nameof( tp_identifier ) );
    }

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

/** Tests for typespec
 *  If possible, takes typespec from source, otherwise leaves source unchanged
 */
func (:s)
(
    er_t try_take_typespec
    (
        mutable,
        bcore_source* source,
        xoico_typespec_s* typespec,
        bl_t require_tractable_type,
        bl_t* success
    )
) = (try)
{
    if( success ) success.0 = false;

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
        if( tp_identifier == TYPEOF_scope    ) typespec.flag_scope    = true;

        // take fails if keyword is actually a function
        if( source.parse_bl( "#?'('" ) )
        {
            source.set_index( index );
            return 0;
        }

        o.trans_identifier( source, NULL, tp_identifier );
        o.trans_whitespace( source, NULL );
    }

    typespec.type = tp_identifier;

//    if( source.parse_bl( "#?'.' " ) )
//    {
//        if( !source.parse_bl( "#?([0]>='0'||[0]<='1') " ) ) source.parse_error_fa( "Argument: Indirection literal expected." );
//        sz_t indirection = 0;
//        source.parse_fa( "#<sz_t*> ", indirection.1 );
//        typespec.indirection = indirection;
//    }
//    else
    {
        while( source.parse_bl( "#?'*' " ) ) typespec.indirection++;
    }

    if( require_tractable_type )
    {
        if( !( tp_identifier == TYPEOF_type_deduce || o.is_type( tp_identifier ) ) )
        {
            source.set_index( index );
            return 0;
        }
    }

    if( success ) success.0 = true;
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s)
(
    er_t take_typespec
    (
        mutable,
        bcore_source* source,
        xoico_typespec_s* typespec,
        bl_t require_tractable_type
    )
) = (try)
{
    bl_t success = false;
    o.try_take_typespec( source, typespec, require_tractable_type, success );

    if( !success )
    {
        if( require_tractable_type )
        {
            return source.parse_error_fa( "Typespec: Syntax error or intractable type." );
        }
        else
        {
            return source.parse_error_fa( "Typespec: Syntax error." );
        }
    }

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) :.push_typespec  = (try)
{
    tp_t type = typespec.type;

    if( type == TYPEOF_type_object )
    {
        ERR_fa( "Cannot resolve 'type_object' at this point." );
    }
    else if( type == TYPEOF_type_deduce )
    {
        ERR_fa( "Cannot resolve 'type_deduce' at this point." );
    }
    else if( type == 0 )
    {
        ERR_fa( "Type is 0." );
    }

    st_s* st_type = st_s_create_sc( o.nameof( type ) ).scope();

    if( st_type.size == 0 )
    {
        ERR_fa( "Type '#<tp_t>' has no name.", type );
    }

    sc_t sc_type = st_type.sc;
    if( typespec.flag_static   ) result.push_fa( "static " );
    if( typespec.flag_const    ) result.push_fa( "const " );
    if( typespec.flag_volatile ) result.push_fa( "volatile " );
    result.push_fa( "#<sc_t>", sc_type );

    for( sz_t i = 0; i < typespec.indirection; i++ ) result.push_fa( "*" );
    if( typespec.flag_restrict ) result.push_fa( "restrict " );

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s)
(
    er_t trans_type
    (
        mutable,
        bcore_source* source,
        :result* result, // can be NULL
        xoico_typespec_s* out_typespec // optional
    )
) = (try)
{
    $* result_type = :result_create_arr().scope();
    tp_t tp_identifier;
    o.trans_identifier( source, result_type, tp_identifier );
    o.trans_whitespace( source, result_type );
    if( source.parse_bl( "#?'!'" ) )
    {
        if( o.is_group( tp_identifier ) )
        {
            return source.parse_error_fa( "Operator '!': lvalue is a group." );
        }
        result.push_fa( "#<sc_t>_create()", o.nameof( tp_identifier ) );
        xoico_typespec_s* typespec = xoico_typespec_s!.scope();
        typespec.type = tp_identifier;
        typespec.indirection = 1;
        typespec.flag_addressable = false;
        o.trans_typespec_expression( source, result, typespec, out_typespec );
    }
    else
    {
        result.push_result_d( result_type.fork() );
    }
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s)
(
    er_t trans_func
    (
        mutable,
        bcore_source* source,
        :result* result, // can be NULL
        xoico_typespec_s* out_typespec // optional
    )
) = (try)
{
    tp_t tp_identifier = 0;

    $* result_func = :result_arr_s!.scope();
    o.trans_identifier( source, result_func, tp_identifier );
    o.trans_whitespace( source, result_func );

    if( source.parse_bl( "#=?'('" ) ) // actual function call
    {
        const xoico_func_s* func = o.get_func( tp_identifier );

        if( !func.signature )
        {
            return source.parse_error_fa( "Function #<sc_t> has no signature.", o.nameof( tp_identifier ) );
        }

        const $* signature = func.signature;
        tp_t object_type = func.obj_type;

        $* typespec_ret = signature.typespec_ret.clone().scope( scope_local );
        tp_t transient_type = 0;

        o.trans_function_args
        (
            source,
            object_type,
            signature,
            NULL/*transient_map*/,
            NULL,
            NULL,
            result_func,
            &transient_type
        );

        if( transient_type != 0 )
        {
            typespec_ret.type = transient_type;
            result.push_sc( "((" );
            o.push_typespec( typespec_ret, result );
            result.push_sc( ")(" );
        }

        result.push_result_d( result_func.fork() );

        if( transient_type != 0 )
        {
            result.push_sc( "))" );
        }

        o.trans_typespec_expression( source, result, typespec_ret, out_typespec );
    }
    else
    {
        result.push_result_d( result_func.fork() );
    }

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s)
(
    er_t trans_ternary_branch
    (
        mutable,
        bcore_source* source,
        :result* result, // can be NULL
        xoico_typespec_s* out_typespec // optional
    )
) = (try)
{
    source.parse_em_fa( "?" );
    result.push_sc( "?" );
    o.trans_expression( source, result, NULL );
    o.trans( source, ": ", result );
    o.trans_expression( source, result, NULL );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s)
(
    er_t trans_bracket
    (
        mutable,
        bcore_source* source,
        :result* result, // can be NULL
        xoico_typespec_s* out_typespec // optional
    )
) = (try)
{
    source.parse_em_fa( "(" );
    result.push_char( '(' );
    while( !source.eos() )
    {
        o.trans_expression( source, result, out_typespec );
        if     ( source.parse_bl( "#?')'" ) ) break;
        else if( source.parse_bl( "#?','" ) ) result.push_char( ',' );
        else return source.parse_error_fa( "Syntax error in bracket expression." );
        if( out_typespec ) out_typespec.type = 0;
    }
    result.push_char( ')' );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s)
(
    er_t trans_array_subscript
    (
        mutable,
        bcore_source* source,
        :result* result, // can be NULL
        xoico_typespec_s* out_typespec // optional
    )
) = (try)
{
    source.parse_em_fa( "[" );
    result.push_sc( "[" );
    o.trans_expression( source, result, NULL );
    source.parse_em_fa( "]" );
    result.push_sc( "]" );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s)
(
    er_t trans_expression
    (
        mutable,
        bcore_source* source,
        :result* result_out, // can be NULL
        xoico_typespec_s* out_typespec // optional
    )
) = (try)
{
    sc_t sc_bl_end_of_expression = "#?([0]==';'||[0]=='{'||[0]=='}'||[0]==')'||[0]==']'||[0]==','||([0]==':'&&([1]==' '||[1]=='\t'||[1]=='\n'||[1]=='/')))";

    o.trans_whitespace( source, result_out );

    $* result = :result_create_arr().scope();
    bl_t continuation = true;

    if( out_typespec ) out_typespec.reset();

    tp_t tp_identifier = o.get_identifier( source, false );

    if( tp_identifier )
    {
        // examples of builtin functions: scope, cast, try, fork
        if( o.is_builtin_func( tp_identifier ) )
        {
            xoico_typespec_s* typespec_builtin = xoico_typespec_s!.scope();
            o.trans_builtin( tp_identifier, source, NULL, NULL, result, typespec_builtin );
            o.trans_typespec_expression( source, result, typespec_builtin, out_typespec );
        }

        else if( tp_identifier == TYPEOF_verbatim_C )
        {
            source.parse_em_fa( "verbatim_C {" );
            o.trans_block_inside_verbatim_c( source, result );
            source.parse_em_fa( " }" );
        }

        // a control name marks end of expression...
        else if( o.is_control_name( tp_identifier ) )
        {
            continuation = false;
        }

        // identifier represents a registered variable
        else if( o.is_var( tp_identifier ) )
        {
            o.trans_identifier( source, result, NULL );
            o.trans_whitespace( source, result );
            const xoico_typespec_s* typespec_var = o.stack_var.get_typespec( tp_identifier );
            o.trans_typespec_expression( source, result, typespec_var, out_typespec );
        }

        // identifier represents a type known to the compiler
        else if( o.is_type( tp_identifier ) )
        {
            o.trans_type( source, result, out_typespec );
        }

        // identifier represents a (global) function name
        else if( o.is_func( tp_identifier ) )
        {
            o.trans_func( source, result, out_typespec );
        }
        else // unknown identifier
        {
            o.trans_identifier( source, result, NULL );
            o.trans_whitespace( source, result );

            // assume untraced function call: bracket evaluation without internal type evaluation
            if( source.parse_bl( "#=?'('" ) )
            {
                o.trans_bracket( source, result, NULL );
            }
        }
    }

    // literals and members
    else if( source.parse_bl( "#?([0]>='0'&&[0]<='9')" ) ) o.trans_number_literal( source, result );
    else if( source.parse_bl( "#=?'\"'" )                ) o.trans_string_literal( source, result );
    else if( source.parse_bl( "#=?|'|" )                 ) o.trans_char_literal( source, result );
    else if( source.parse_bl( "#=?'.'" )                 ) o.trans_member( source, result );
    else if( source.parse_bl( "#=?'->'" )                ) o.trans_member( source, result );

    else if( source.parse_bl( "#=?'=<'" )                ) return source.parse_error_fa( "Attach operator: Expression not tractable." );

//    else if( source.parse_bl( "#=?'&'" ) ) return source.parse_error_fa( "Changing indirection: Prefix '&' is disallowed. Use postfix '.&'" );
//    else if( source.parse_bl( "#=?'*'" ) ) return source.parse_error_fa( "Changing indirection: Prefix '*' is disallowed. Use postfix '.*'" );

    else if( o.trans_inert_operator( source, result )       ) {} // inert operators are not interpreted by che and passed to the c-compiler

    // ternary branch operator
    else if( source.parse_bl( "#=?'?'" ) )
    {
        o.trans_ternary_branch( source, result, out_typespec );
    }

    // general bracket
    else if( source.parse_bl( "#=?'('" ) )
    {
        xoico_typespec_s* typespec_bracket = xoico_typespec_s!.scope();
        o.trans_bracket( source, result, typespec_bracket );
        if( typespec_bracket.type ) o.trans_typespec_expression( source, result, typespec_bracket, out_typespec );
    }

    // array subscript
    else if( source.parse_bl( "#=?'['" ) )
    {
        o.trans_array_subscript( source, result, out_typespec );
    }

    // end of expression...
    else if( source.parse_bl( sc_bl_end_of_expression ) )
    {
        continuation = false;
    }

    // unhandled
    else
    {
        return source.parse_error_fa( "Syntax error after '#<sc_t>'", result.create_st().scope().sc );
    }

    if( continuation )
    {
        if( !source.parse_bl( sc_bl_end_of_expression ) )
        {
            if( out_typespec ) out_typespec.reset();


            o.trans_whitespace( source, result );
            o.trans_operator( source, result );


            o.trans_expression( source, result, NULL );
        }
    }

    if( result_out ) result_out.push_result_d( result.fork() );

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

/** Translates declaration including optional subsequent assignment.
 *  If no declaration was detected, source and result_out are not modified.
 */
func (:s)
(
    er_t try_trans_declaration
    (
        mutable,
        bcore_source* source,
        :result* result_out,
        bl_t* success
    )
) = (try)
{
    if( success ) success.0 = false;

    xoico_typespec_s* typespec_var = xoico_typespec_s!.scope();

    sz_t index = source.get_index();

    $* result_var = :result_create_arr().scope();

    bl_t success_take_typespec = false;
    o.try_take_typespec( source, typespec_var, true, success_take_typespec.1 );

    if( !success_take_typespec )
    {
        source.set_index( index );
        return 0;
    }

    o.trans_whitespace( source, result_var );

    if
    (
        typespec_var.type &&
        source.parse_bl( "#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||[0]=='_')" )
    )
    {
        tp_t tp_identifier = 0;
        o.trans_identifier( source, result_var, tp_identifier.1 );
        o.trans_whitespace( source, result_var );

        if( source.parse_bl( "#?'='" ) )
        {
            bl_t pushed_typedecl = false;
            if( typespec_var.type != TYPEOF_type_deduce )
            {
                o.push_typedecl( typespec_var, tp_identifier );
                pushed_typedecl = true;
            }

            result_var.push_sc( "=" );
            xoico_typespec_s* typespec_expr = xoico_typespec_s!.scope();
            $* result_expr = :result_create_arr().scope();
            o.trans_expression( source, result_expr, typespec_expr );

            if( typespec_var.type == TYPEOF_type_deduce )
            {
                if( !typespec_expr.type )
                {
                    return source.parse_error_fa( "Declaration-syntax: Deduce requested but expression is intractable." );
                }
                typespec_var.type = typespec_expr.type;
            }

            if( typespec_expr.type )
            {
                o.adapt_expression( source, typespec_expr, typespec_var, result_expr, result_var );
            }
            else
            {
                result_var.push_result_d( result_expr.fork() );
            }
            o.push_typespec( typespec_var, result_out );
            result_out.push_char( ' ' );
            result_out.push_result_d( result_var.fork() );
            if( !pushed_typedecl ) o.push_typedecl( typespec_var, tp_identifier );
        }
        else if( typespec_var.type == TYPEOF_type_deduce )
        {
            return source.parse_error_fa( "Declaration-syntax: Deduce requested without assignment." );
        }
        else if( source.parse_bl( "#=?'['" ) )
        {
            o.push_typespec( typespec_var, result_out );
            while( source.parse_bl( "#?'['" ) )
            {
                result_var.push_char( '[' );
                o.trans_expression( source, result_var, NULL );
                source.parse_em_fa( "]" );
                result_var.push_char( ']' );
                typespec_var.indirection++;
            }
            result_out.push_char( ' ' );
            result_out.push_result_d( result_var.fork() );
            o.push_typedecl( typespec_var, tp_identifier );
        }
        else
        {
            o.push_typespec( typespec_var, result_out );
            result_out.push_char( ' ' );
            result_out.push_result_d( result_var.fork() );
            o.push_typedecl( typespec_var, tp_identifier );
        }

        if( success ) success.0 = true;
    }
    else
    {
        source.set_index( index );
        return 0;
    }

    if( success ) success.0 = true;

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func(:s) (er_t inspect_variable( mutable, bcore_source* source )) = (try)
{
    source.parse_em_fa( "\?\?" );

    $* st = st_s!.scope();
    $* result_local = :result_create_arr().scope();
    xoico_typespec_s* typespec = xoico_typespec_s!.scope();
    source.parse_em_fa( " #until';' ", st );
    source.parse_em_fa( ";" );
    bcore_msg_fa( " \?? #<sc_t>;\n", st.sc );
    if( o.trans_expression( bcore_source_string_s_create_fa( "#<st_s*>;", st ).scope(), result_local, typespec ) )
    {
        bcore_error_pop_to_sink( BCORE_STDOUT );
        bcore_msg_fa( "\n" );
    }
    else
    {
        if( st.size == 0 ) return source.parse_error_fa( "Variable name expected." );
        bcore_msg_fa( "--> #<sc_t>;\n", result_local.create_st().scope().sc );

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
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) (er_t trans_statement_expression( mutable, bcore_source* source, :result* result )) = (try)
{
    if( o.try_block_level > 0 )
    {
        xoico_typespec_s* typespec = xoico_typespec_s!.scope();
        $* result_expr = :result_create_arr().scope();
        o.trans_expression( source, result_expr, typespec );
        if
        (
            ( typespec.type == TYPEOF_er_t ) &&
            ( typespec.indirection == 0 ) &&
            ( typespec.flag_addressable == false )
        )
        {
            if( !source.parse_bl( " #?';'" ) )
            {
                return source.parse_error_fa( "Inside a try-block: Expressions yielding 'er_t' must end with ';'" );
            }
            result.push_sc( "BLM_TRY(" );
            result.push_result_d( result_expr.fork() );
            result.push_sc( ")" );
        }
        else
        {
            result.push_result_d( result_expr.fork() );
        }
    }
    else
    {
        o.trans_expression( source, result, NULL );
    }

    o.trans_whitespace( source, result );

    // ':' between expressions is to be taken literally
    if( source.parse_bl( "#?':'" ) ) result.push_char( ':' );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) (er_t trans_statement( mutable, bcore_source* source, :result* result )) = (try)
{
    o.trans_whitespace( source, result );

    if( source.parse_bl( "#?([0]=='{'||[0]=='#'||[0]==';'||[0]==','||[0]==')'||[0]=='}'||([0]=='?'&&[1]=='?'))" ) )
    {
        char c = source.inspect_char();
        switch( c )
        {
            case '{':
            {
                o.trans_block( source, result, false );
            }
            break;

            case '#':
            {
                o.trans_preprocessor( source, result );
            }
            break;

            case ';':
            {
                source.get_char();
                result.push_char( ';' );
            }
            break;

            case ',':
            {
                source.get_char();
                result.push_char( ',' );
            }
            break;

            case '?':
            {
                o.inspect_variable( source );
            }
            break;

            case ')':
            {
                return source.parse_error_fa( "Unmatched closing bracket." );
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
            o.trans_control( tp_identifier, source, result );
        }
        else
        {
            bl_t success_declaration = false;
            o.try_trans_declaration( source, result, success_declaration.1 );
            if( !success_declaration ) o.trans_statement_expression( source, result );
        }
    }

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) (er_t trans_block_inside( mutable, bcore_source* source, :result* result_out )) = (try)
{
    $* result = :result_create_arr().scope();

    while( !source.parse_bl( "#=?'}'" ) && !source.eos() )
    {
        o.trans_statement( source, result );
    }

    if( o.stack_block_get_top_unit().use_blm )
    {
        $* result_block = :result_create_block( o.level, true ).scope();

        result_block.push_result_d( :result_create_blm_init( o.level ) );
        result_block.push_result_d( result.fork() );

        if( ( o.level > 0 ) || !o.returns_a_value() )
        {
            result_block.push_result_d( :result_create_blm_down() );
        }

        result_out.push_result_d( result_block.fork() );
    }
    else
    {
        result_out.push_result_d( result.fork() );
    }

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) (er_t trans_block( mutable, bcore_source* source, :result* result_out, bl_t is_break_ledge )) = (try)
{
    o.inc_block();
    $* result = :result_create_arr().scope();
    o.stack_block_get_top_unit().break_ledge = is_break_ledge;
    o.trans_whitespace( source, result );
    o.trans( source, "{", result );
    o.trans_block_inside( source, result );
    o.trans_whitespace( source, result );
    o.trans( source, "}", result );
    result_out.push_result_d( result.fork() );
    o.dec_block();
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) (er_t trans_statement_as_block( mutable, bcore_source* source, :result* result_out, bl_t is_break_ledge )) = (try)
{
    $* result = :result_create_arr().scope();

    o.inc_block();
    o.stack_block_get_top_unit().break_ledge = is_break_ledge;

    o.trans_statement( source, result );
    o.trans_whitespace( source, result );
    if( source.parse_bl( "#?';'" ) ) result.push_sc( ";" );

    if( o.stack_block_get_top_unit().use_blm )
    {
        $* result_block = :result_create_block( o.level, true ).scope();
        result_block.push_result_d( :result_create_blm_init( o.level ) );
        result_block.push_result_d( result.fork() );
        result_block.push_result_d( :result_create_blm_down() );

        result_out.push_sc( "{" );
        result_out.push_result_d( result_block.fork() );
        result_out.push_sc( "}" );
    }
    else
    {
        result_out.push_result_d( result.fork() );
    }

    o.dec_block();
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) (er_t trans_block_inside_verbatim_c( mutable, bcore_source* source, :result* result )) = (try)
{
    o.trans_whitespace( source, result );
    while( !source.parse_bl( "#=?'}'" ) && !source.eos() )
    {
        switch( source.inspect_char() )
        {
            case '"':
            {
                o.trans_string_literal( source, result );
            }
            break;

            case '\'':
            {
                o.trans_char_literal( source, result );
            }
            break;

            case '{':
            {
                result.push_char( source.get_char() );
                o.trans_block_inside_verbatim_c( source, result );
                source.parse_em_fa( "}" );
                result.push_char( '}' );
            }
            break;

            default:
            {
                result.push_char( source.get_char() );
            }
            break;
        }
        o.trans_whitespace( source, result );
    }
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) (er_t setup( mutable, const xoico_host* host, const xoico_signature_s* signature )) = (try)
{
    tp_t host_obj_type = host.obj_type();

    const xoico_args_s* args = signature.args;

    tp_t tp_member_obj_type  = ( signature.arg_o == 0 ) ? 0 : host_obj_type;
    bl_t member_obj_const = ( signature.arg_o == TYPEOF_const );

    o.typespec_ret.copy( signature.typespec_ret );

    o.host     = host.cast( $* );
    o.compiler = host.compiler();
    o.member_obj_type = tp_member_obj_type;
    o.level    = 0;
    o.try_block_level = 0;
    o.stack_var.clear();
    o.init_level0();

    if( signature.typed )
    {
        $* unit = xoico_che_stack_var_unit_s!.scope();
        unit.typespec.type = TYPEOF_tp_t;
        unit.typespec.flag_const = false;
        unit.typespec.indirection = 1;
        unit.name = o.entypeof( "t" );
        unit.level = o.level;
        o.stack_var.push_unit( unit );
        o.hmap_name.set_sc( "tp_t" );
        o.hmap_name.set_sc( "t" );
    }

    if( tp_member_obj_type )
    {
        $* unit = xoico_che_stack_var_unit_s!.scope();
        tp_t tp_member_obj_name  = o.entypeof( "o" );
        unit.typespec.flag_const = member_obj_const;
        unit.typespec.type = tp_member_obj_type;
        unit.typespec.indirection = 1;
        unit.name = tp_member_obj_name;
        unit.level = o.level;
        o.stack_var.push_unit( unit );
        o.hmap_name.set_sc( o.compiler.nameof( tp_member_obj_type ) );
        o.hmap_name.set_sc( o.compiler.nameof( tp_member_obj_name ) );
    }

    foreach( $* arg in args )
    {
        if( arg.typespec.type && arg.name )
        {
            $* unit = xoico_che_stack_var_unit_s!.scope();
            unit.typespec.copy( arg.typespec );
            unit.name = arg.name;
            unit.level = o.level;
            o.stack_var.push_unit( unit );
            o.hmap_name.set_sc( o.compiler.nameof( arg.typespec.type ) );
            o.hmap_name.set_sc( o.compiler.nameof( arg.name ) );
        }
    }
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) (sz_t assess_indentation( bcore_source* source )) =
{
    sz_t index = source.get_index();
    while( !source.eos() ) if( source.get_char() == '\n' ) break;
    sz_t indentation = 0;
    while( !source.eos() )
    {
        if( source.get_char() != ' ' ) break;
        indentation++;
    }
    source.set_index( index );
    return indentation;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) (void remove_indentation( st_s* string, sz_t indentation )) =
{
    ASSERT( string.space >= string.size );

    sz_t j = 0;
    for( sz_t i = 0; i < string.size; i++ )
    {
        char c = string.[ i ];
        string.[ j++ ] = c;
        if( c == '\n' )
        {
            for( sz_t k = 0; k < indentation; k++ )
            {
                if( string.[ i + 1 ] != ' ' ) break;
                i++;
            }
        }
    }

    string.[ j ] = 0;
    string.size = j;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) (er_t translate_mutable( mutable, const xoico_host* host, const xoico_body_s* body, const xoico_signature_s* signature, bcore_sink* sink )) = (try)
{
    o.setup( host, signature );

    bcore_source* source = body.code.source_point.clone_source().scope();

    $* result = :result_create_arr().scope();

    bl_t flag_verbatim_c = false;
    bl_t flag_try = false;

    if( source.parse_bl( " #?'('" ) )
    {
        while( !source.parse_bl( " #?')'" ) )
        {
            if( source.parse_bl( " #?w'try'" ) )
            {
                if( o.typespec_ret.type != TYPEOF_er_t || o.typespec_ret.indirection != 0 )
                {
                    return source.parse_error_fa( "Operator 'try': This operator can only be used in functions returning 'er_t'." );
                }
                flag_try = true;
            }
            else if( source.parse_bl( " #?w'verbatim_C'" ) )
            {
                flag_verbatim_c = true;
            }
            else
            {
                return source.parse_error_fa( "Invalid c-engine expression." );
            }
        }
    }

    source.parse_em_fa( " {" );
    sz_t indentation = 0;
    if( !body.go_inline ) indentation = o.assess_indentation( source );

    if( flag_verbatim_c )
    {
        o.trans_block_inside_verbatim_c( source, result );
    }
    else
    {
        o.try_block_level += flag_try;
        o.trans_block_inside( source, result );
        o.try_block_level -= flag_try;
    }
    source.parse_em_fa( " }" );

    $* result_block = :result_create_block( o.level, o.stack_block_get_bottom_unit().use_blm ).scope();
    result_block.cast( :result_block_s* ).is_root = true;
    result_block.push_result_d( result.fork() );

    st_s* buf = st_s!.scope();
    result_block.to_sink( buf );

    //remove trailing whitespaces
    for( sz_t i = buf.size - 1; i >= 0; i-- )
    {
        if( buf.[ i ] != ' ' && buf.[ i ] != '\t' && buf.[ i ] != '\n' ) break;
        buf.[ i ] = 0;
        buf.size = i;
    }

    if( o.insert_source_reference && !body.code.single_line )
    {
        sink.push_fa( "// " );
        body.code.source_point.source_reference_to_sink( true, sink );
        sink.push_fa( "\n" );
    }

    if( indentation > 0 ) o.remove_indentation( buf, indentation );

    if( o.verbose )
    {
        bcore_sink_a_push_fa( BCORE_STDOUT, "##############################\n" );
        bcore_sink_a_push_fa( BCORE_STDOUT, "#<st_s*>\n", buf );
    }

    sink.push_sc( buf.sc );

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) xoico_cengine.translate =
{
    er_t er = o.clone().scope().translate_mutable( host, body, signature, sink );
    return er;
};

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

