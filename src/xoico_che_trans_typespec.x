/** Author and Copyright 2021 Johannes Bernhard Steffens
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

func (:s)
(
    er_t trans_typespec_member
    (
        m @* o,
        m bcore_source* source,
        m :result* result,
        c xoico_typespec_s*  in_typespec, // required
        m xoico_typespec_s* out_typespec  // optional
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
    m xoico_compiler_element_info_s* info = xoico_compiler_element_info_s!^^;

    char c = source.inspect_char();

    if( c == '*' || c == '&' )
    {
        return source.parse_error_fa( "Postfix operators '&' and '*' are deprecated. Use numeric indirection level.\n" );
    }

    if( c >= '0' && c <= '9' )
    {
        m $* typespec_adapted = in_typespec.clone()^^;
        sz_t adapted_indirection = 0;
        source.parse_em_fa( "#<sz_t*>", &adapted_indirection );

        typespec_adapted.indirection = adapted_indirection;

        m $* result_adapted = :result_arr_s!^^;
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
        m $* result_local = :result_create_arr()^^;
        tp_t tp_identifier = 0;
        o.trans_identifier( source, result_local, tp_identifier );
        o.trans_whitespace( source, result_local );

        // builtin functions ...
        if( o.is_builtin_func( tp_identifier ) )
        {
            m xoico_typespec_s* typespec_builtin = xoico_typespec_s!^^;
            o.trans_builtin( tp_identifier, source, result, in_typespec, result_local, typespec_builtin );
            result.copy( result_local );
            o.trans_typespec_expression( source, result, typespec_builtin, out_typespec );
        }
        else if( o.compiler.get_type_element_info( in_typespec.type, tp_identifier, info ) )
        {
            if( info.func ) // member function
            {
                m $* typespec_ret = xoico_typespec_s!^^;
                m $* result_object_expr = result.clone()^^;
                result.clear();
                o.trans_function( source, info.func, result_object_expr, in_typespec, result, typespec_ret );
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
            if( !o.waive_unknown_member_function ) return source.parse_error_fa( "'#<sc_t>' has no member function '#<sc_t>'.", o.nameof( in_typespec.type ), o.nameof( tp_identifier ) );
            m $* result_arg_obj = result.clone()^^;
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
                m xoico_typespec_s* typespec_obj = in_typespec.clone()^^;
                typespec_obj.indirection = 1; // first argument of member functions
                o.adapt_expression( source, in_typespec, typespec_obj, result_arg_obj, result );
            }

            bl_t first = true;
            o.trans_whitespace( source, result_local );
            while( !source.eos() )
            {
                if( source.parse_bl( "#=?')'" ) ) break;

                m $* result_expr = :result_create_arr()^^;
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
            if( !o.waive_unknown_member_variable ) return source.parse_error_fa( "'#<sc_t>' has no member '#<sc_t>'.", o.nameof( in_typespec.type ), o.nameof( tp_identifier ) );
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
        m @* o,
        m bcore_source* source,
        m :result* result,
        c xoico_typespec_s*  in_typespec, // required
        m xoico_typespec_s* out_typespec  // optional
    )
) = (try)
{
    source.parse_em_fa( "[" );

    result.push_sc( "[" );
    o.trans_expression( source, result, NULL );
    source.parse_em_fa( "]" );
    result.push_sc( "]" );

    m xoico_typespec_s* typespec = in_typespec.clone()^^;

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
        m @* o,
        m bcore_source* source,
        m :result* result,
        c xoico_typespec_s*  in_typespec, // required
        m xoico_typespec_s* out_typespec  // optional
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

        m $* result_arg_obj = result.clone()^^;
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
        m @* o,
        m bcore_source* source,
        m :result* result,
        c xoico_typespec_s*  in_typespec, // required
        m xoico_typespec_s* out_typespec  // optional
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

        m $* result_arg_obj = result.clone()^^;
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
        m @* o,
        m bcore_source* source,
        m :result* result,
        c xoico_typespec_s*  in_typespec, // required
        m xoico_typespec_s* out_typespec  // optional
    )
) = (try)
{
    if( in_typespec.indirection != 1 )
    {
        return source.parse_error_fa( "Attach-Operator: lvalue with indirection of 1 expected." );
    }

    if( !in_typespec.flag_addressable )
    {
        return source.parse_error_fa( "Attach-Operator: Addressable lvalue expected." );
    }

    source.parse_em_fa( "=<" );

    m $* result_arg_obj = result.clone()^^;
    result.clear();

    sc_t sc_type = o.nameof( in_typespec.type );
    result.push_fa( "#<sc_t>", sc_type );

    m xoico_typespec_s* typespec_rval = xoico_typespec_s!^^;
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

    if( typespec_rval.type )
    {
        if( typespec_rval.indirection != 1 )
        {
            return source.parse_error_fa( "Attach operator: rvalue with indirection '1' expected." );
        }

        if( typespec_rval.access_class != TYPEOF_discardable )
        {
            return source.parse_error_fa( "Attach operator: Discardable rvalue expected." );
        }
    }

    if( out_typespec ) out_typespec.copy( in_typespec );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s)
(
    er_t trans_typespec_assign
    (
        m @* o,
        m bcore_source* source,
        m :result* result,
        c xoico_typespec_s*  in_typespec, // required
        m xoico_typespec_s* out_typespec  // optional
    )
) = (try)
{
    source.parse_em_fa( "=" );
    result.push_sc( "=" );

    if( in_typespec.indirection > 0 && o.is_group( in_typespec.type ) )
    {
        m $* typespec_rval = xoico_typespec_s!^^;
        m $* result_rval = :result_arr_s!^;
        o.trans_expression( source, result_rval, typespec_rval );

        if( o.is_group( typespec_rval.type ) || o.is_stamp( typespec_rval.type ) )
        {
            if( typespec_rval.indirection != in_typespec.indirection )
            {
                return source.parse_error_fa( "Non declarative assignment: Indirection mismatch." );
            }

            if( typespec_rval.type != in_typespec.type )
            {
                o.adapt_expression( source, typespec_rval, in_typespec, result_rval, result );
            }
            else
            {
                result.push_result_d( result_rval.fork() );
            }
        }
        else
        {
            result.push_result_d( result_rval.fork() );
        }
    }
    else
    {
        o.trans_expression( source, result, NULL );
    }

    if( out_typespec ) out_typespec.copy( in_typespec );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s)
(
    er_t trans_typespec_expression
    (
        m @* o,
        m bcore_source* source,
        m :result* result,
        c xoico_typespec_s*  in_typespec, // required
        m xoico_typespec_s* out_typespec  // optional
    )
) = (try)
{
    if( out_typespec ) out_typespec.type = 0;
    o.trans_whitespace( source, result );

    u0_t c[ 2 ];
    source.inspect_data( c, sizeof( c ) );

    if( ( c[0] == '.' && c[1] != '.' ) || ( c[0] == '-' && c[1] == '>' ) )
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
    // assign
    else if( c[0] == '=' && c[1] != '=' )
    {
        o.trans_typespec_assign( source, result, in_typespec, out_typespec );
    }
    // ternary branch operator
    else if( c[0] == '?' )
    {
        o.trans_ternary_branch( source, result, out_typespec );
    }
    // scope
    else if( c[0] == '^' && in_typespec.indirection != 0 ) // for indirection 0 '^' is the xor operator
    {
        m :result* result_local = result.clone()^^;
        result.clear();
        m xoico_typespec_s* typespec_scope = xoico_typespec_s!^;
        o.trans_builtin_scope( source, result_local, in_typespec, result, typespec_scope );
        o.trans_typespec_expression( source, result, typespec_scope, out_typespec );
    }
    else if( out_typespec )
    {
        out_typespec.copy( in_typespec );
    }

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
