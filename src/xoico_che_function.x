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

/// Processes the argument section '(....)' of a function
func (:s)
(
    er_t trans_function_args
    (
        m @* o,
        m bcore_source* source,
        tp_t object_type,
        c xoico_signature_s* signature,
        c :result* result_object_expr,
        c xoico_typespec_s* typespec_object,
        m :result* result,
        m tp_t* transient_return_type
    )
) = (try)
{
    o.trans( source, "(", result );

    tp_t transient_class = signature.typespec_ret.transient_class;

    if( signature.arg_o )
    {
        if( !result_object_expr )
        {
            m $* result_expr   = :result_create_arr().scope();
            m $* typespec_expr = xoico_typespec_s!^^;
            o.trans_expression( source, result_expr, typespec_expr );
            result_object_expr = result_expr;
            typespec_object = typespec_expr;
            if( signature.args.size > 0 ) source.parse_em_fa( " ," );
        }

        m xoico_typespec_s* typespec_object_adapted = signature.arg_o.typespec.clone().scope();
        typespec_object_adapted.type = object_type ? object_type : typespec_object.type;
        typespec_object_adapted.flag_restrict = false;

        if( typespec_object.type )
        {
            if( transient_class && transient_return_type && ( transient_return_type.0 == 0 ) && ( signature.arg_o.typespec.transient_class == transient_class ) )
            {
                transient_return_type.0 = typespec_object.type;
            }
            o.adapt_expression( source, typespec_object, typespec_object_adapted, result_object_expr, result );
        }
        else
        {
            result.push_result_c( result_object_expr );
        }
        if( signature.args.size > 0 ) result.push_sc( "," );
    }

    c xoico_transient_map_s* transient_map = ( typespec_object ) ? o.get_transient_map( typespec_object.type ) : NULL;

    if( transient_map && transient_class && transient_return_type )
    {
        tp_t type = transient_map.get( transient_class );
        if( type )
        {
            if( !transient_return_type.0 )
            {
                transient_return_type.0 = type;
            }
            else if( transient_return_type.0 != type )
            {
                return source.parse_error_fa( "Object type expected: '#<sc_t>'. Object type passed: '#<sc_t>'.", o.nameof( type ), o.nameof( transient_return_type.0 ) );
            }
        }
    }

    foreach( c $* arg in signature.args )
    {
        if( arg.is_variadic() ) break;

        m $* result_expr = :result_arr_s!^^;
        m $* typespec_expr = xoico_typespec_s!^;
        source.parse_em_fa( " " );

        if( __i > 0 )
        {
            source.parse_em_fa( " ," );
            result.push_sc( "," );
        }

        o.trans_whitespace( source, result_expr );
        if( source.parse_bl( "#?')'" ) ) return source.parse_error_fa( "Function argument '#<sc_t>': No value passed.", o.nameof( arg.name ) );

        o.trans_expression( source, result_expr, typespec_expr );

        if( typespec_expr.type )
        {
            if( arg.typespec.transient_class )
            {
                if( transient_return_type && ( transient_return_type.0 == 0 ) && ( arg.typespec.transient_class == transient_class ) )
                {
                    transient_return_type.0 = typespec_expr.type;
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

            o.adapt_expression( source, typespec_expr, arg.typespec, result_expr, result );
        }
        else
        {
            result.push_result_d( result_expr.fork() );
        }
    }

    if( signature.args.is_variadic() )
    {
        while( !source.eos() && !source.parse_bl( " #=?')'" ) )
        {
            source.parse_em_fa( " ," );
            result.push_sc( "," );
            o.trans_expression( source, result, NULL );
        }
    }

    source.parse_em_fa( " " );
    o.trans( source, ")", result );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s)
(
    er_t trans_function
    (
        m @* o,
        m bcore_source* source,
        c xoico_func_s* func,
        c :result* result_object_expr, // NULL on direct calls
        c xoico_typespec_s* typespec_object, // NULL on direct calls
        m :result* result,
        m xoico_typespec_s* return_typespec
    )
) = (try)
{
    c $* signature = func.signature;

    m $* typespec_ret = signature.typespec_ret.clone().scope( scope_local );
    tp_t transient_return_type = 0;

    m $* result_args = :result_arr_s!^^;
    o.trans_function_args
    (
        source,
        func.obj_type,
        signature,
        result_object_expr,
        typespec_object,
        result_args,
        &transient_return_type
    );

    bl_t cast_return_type = ( transient_return_type != 0 && transient_return_type != typespec_ret.type );

    if( cast_return_type )
    {
        typespec_ret.type = transient_return_type;
        result.push_sc( "((" );
        o.push_typespec( typespec_ret, result );
        result.push_sc( ")(" );
    }

    result.push_sc( o.nameof( func.global_name ) );
    result.push_result_d( result_args.fork() );

    if( cast_return_type )
    {
        result.push_sc( "))" );
    }

    if( return_typespec ) return_typespec.copy( typespec_ret );

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

