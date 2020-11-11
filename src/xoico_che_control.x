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

func (:)( bl_t is_control_name( const, tp_t tp_identifier ) ) =
{
    switch( tp_identifier )
    {
        case TYPEOF_for:
        case TYPEOF_foreach:
        case TYPEOF_if:
        case TYPEOF_else:
        case TYPEOF_break:
        case TYPEOF_while:
        case TYPEOF_do:
        case TYPEOF_switch:
        case TYPEOF_case:
        case TYPEOF_default:
        case TYPEOF_return:
            return true;

        default:
            return false;
    }
};

//----------------------------------------------------------------------------------------------------------------------

func (:)( er_t trans_control( mutable, tp_t tp_control, bcore_source* source, :result* result ) ) =
{ try {
    switch( tp_control )
    {
        case TYPEOF_for:     return o.trans_control_for(     source, result );
        case TYPEOF_foreach: return o.trans_control_foreach( source, result );
        case TYPEOF_if:      return o.trans_control_if(      source, result );
        case TYPEOF_else:    return o.trans_control_else(    source, result );
        case TYPEOF_break:   return o.trans_control_break(   source, result );
        case TYPEOF_while:   return o.trans_control_while(   source, result );
        case TYPEOF_do:      return o.trans_control_do(      source, result );
        case TYPEOF_switch:  return o.trans_control_switch(  source, result );
        case TYPEOF_case:    return o.trans_control_case(    source, result );
        case TYPEOF_default: return o.trans_control_default( source, result );
        case TYPEOF_return:  return o.trans_control_return(  source, result );
        default: return source.parse_error_fa( "Internal error: Invalid control name '#<sc_t>'", ifnameof( tp_control ) );
    }
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:)( er_t trans_control_for( mutable, bcore_source* source, :result* result ) ) =
{ try {
    o.inc_block();
    o.stack_block_get_top_unit().break_ledge = true;
    o.trans( source, "for", result );
    o.trans_whitespace( source, result );
    o.trans( source, "(", result );
    o.trans_statement( source, result ); // def
    o.trans( source, ";", result );
    o.trans_expression( source, result, NULL ); // cond
    o.trans( source, ";", result );
    o.trans_expression( source, result, NULL ); // update
    o.trans_whitespace( source, result );
    o.trans( source, ")", result );
    o.trans_whitespace( source, result );
    if( source.parse_bl( "#=?'{'" ) )
    {
        o.trans_block( source, result, false );
    }
    else
    {
        o.trans_statement_as_block( source, result, false );
    }
    o.dec_block();
    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

/** foreach( <typespec> var in <arr_expr> ) <foreach-statement>
 *  -->
 * { <typespec> __a = (match)<arr_expr>; for( sz_t __i = 0; __i < __a->size; __i++ ) { <typespec> var = (match)__a->data[ __i ]; <foreach-statement> }  }
 */
func (:)( er_t trans_control_foreach( mutable, bcore_source* source, :result* result ) ) =
{ try {
    o.inc_block();
    o.stack_block_get_top_unit().break_ledge = true;
    o.parse( source, "foreach ( " );

    xoico_typespec_s* typespec_var = scope( xoico_typespec_s! );
    o.take_typespec( source, typespec_var, true );

    tp_t tp_var_name = 0;

    if( source.parse_bl( "#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||[0]=='_')" ) )
    {
        tp_var_name = o.get_identifier( source, true );
    }
    else
    {
        return source.parse_error_fa( "Variable name expected." );
    }

    o.parse( source, " in " );

    xoico_typespec_s* typespec_arr_expr = scope( xoico_typespec_s! );
    $* result_arr_expr = :result_create_plain().scope();
    o.trans_expression( source, result_arr_expr, typespec_arr_expr );

    if( !typespec_arr_expr.type )
    {
        return source.parse_error_fa( "Array expression not tractable." );
    }

    xoico_compiler_element_info_s* info = scope( xoico_compiler_element_info_s! );

    if( !o.compiler.get_type_array_element_info( typespec_arr_expr.type, info ) )
    {
        return source.parse_error_fa( "Expression does not evaluate to an array." );
    }

    xoico_typespec_s* typespec_element = &info.type_info.typespec;

    if( typespec_var.type == TYPEOF_type_deduce ) typespec_var.type = typespec_element.type;

    o.parse( source, " )" );

    xoico_typespec_s* typespec_arr = scope( typespec_arr_expr.clone() );
    typespec_arr.indirection = 1;
    typespec_arr.flag_const = true;

    xoico_typespec_s* typespec_idx = scope( xoico_typespec_s! );
    typespec_idx.type = TYPEOF_sz_t;

    o.push_typedecl( typespec_var, tp_var_name );
    o.push_typedecl( typespec_arr, o.entypeof( "__a" ) );
    o.push_typedecl( typespec_idx, o.entypeof( "__i" ) );

    $* result_statement = :result_create_plain().scope();
    if( source.parse_bl( "#=?'{'" ) )
    {
        o.trans_block( source, result_statement, false );
    }
    else
    {
        o.trans_statement_as_block( source, result_statement, false );
    }

    result.push_fa( "{" );

    o.push_typespec( typespec_arr, result );

    result.push_fa( " __a=" );
    o.adapt_expression( source, typespec_arr_expr, typespec_arr, result_arr_expr, result );
    result.push_fa( ";" );
    result.push_fa( "if(__a)for(sz_t __i=0; __i<__a->size; __i++){" );
    o.push_typespec( typespec_var, result );
    result.push_fa( " #<sc_t>=", xoico_che_s_nameof( o, tp_var_name ) );

    $* result_element_expr = :result_create_plain_from_sc( "__a->data[__i]" ).scope();

    o.adapt_expression( source, typespec_element, typespec_var, result_element_expr, result );
    result.push_fa( ";" );

    result.push_result( result_statement );

    result.push_fa( "}}" );
    o.dec_block();
    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:)( er_t trans_control_if( mutable, bcore_source* source, :result* result ) ) =
{ try {
    o.trans( source, "if", result );
    o.trans_whitespace( source, result );
    o.trans( source, "(", result );
    o.trans_expression( source, result, NULL ); // def
    o.trans( source, ")", result );
    o.trans_whitespace( source, result );
    if( source.parse_bl( "#=?'{'" ) )
    {
        o.trans_block( source, result, false );
    }
    else
    {
        o.trans_statement_as_block( source, result, false );
    }
    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:)( er_t trans_control_while( mutable, bcore_source* source, :result* result ) ) =
{ try {
    o.trans( source, "while", result );
    o.trans_whitespace( source, result );
    o.trans( source, "(", result );
    o.trans_expression( source, result, NULL ); // def
    o.trans( source, ")", result );
    o.trans_whitespace( source, result );
    if( source.parse_bl( "#=?'{'" ) )
    {
        o.trans_block( source, result, true );
    }
    else
    {
        o.trans_statement_as_block( source, result, true );
    }
    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:)( er_t trans_control_do( mutable, bcore_source* source, :result* result ) ) =
{ try {
    o.trans( source, "do", result );
    o.trans_whitespace( source, result );
    if( source.parse_bl( "#=?'{'" ) )
    {
        o.trans_block( source, result, true );
    }
    else
    {
        o.trans_statement_as_block( source, result, true );
    }
    o.trans( source, "while", result );
    o.trans_whitespace( source, result );
    o.trans( source, "(", result );
    o.trans_expression( source, result, NULL ); // def
    o.trans( source, ")", result );
    o.trans_whitespace( source, result );
    o.trans( source, ";", result );
    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:)( er_t trans_control_else( mutable, bcore_source* source, :result* result ) ) =
{ try {
    o.trans( source, "else", result );
    o.trans_whitespace( source, result );
    if( source.parse_bl( "#=?'{'" ) )
    {
        o.trans_block( source, result, false );
    }
    else
    {
        o.trans_statement_as_block( source, result, false );
    }
    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:)( er_t trans_control_switch( mutable, bcore_source* source, :result* result ) ) =
{ try {
    o.trans( source, "switch", result );
    o.trans_whitespace( source, result );
    o.trans( source, "(", result );
    o.trans_expression( source, result, NULL ); // def
    o.trans( source, ")", result );
    o.trans_whitespace( source, result );
    o.trans_block( source, result, true );
    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:)( er_t trans_control_case( mutable, bcore_source* source, :result* result ) ) =
{ try {
    o.trans( source, "case", result );
    o.trans_expression( source, result, NULL );
    o.trans_whitespace( source, result );
    o.trans( source, ":", result );
    o.trans_whitespace( source, result );
    o.trans_statement_as_block( source, result, false );
    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:)( er_t trans_control_default( mutable, bcore_source* source, :result* result ) ) =
{ try {
    o.trans( source, "default", result );
    o.trans_whitespace( source, result );
    o.trans( source, ":", result );
    o.trans_whitespace( source, result );
    o.trans_statement_as_block( source, result, false );
    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:)( er_t trans_control_break( mutable, bcore_source* source, :result* result ) ) =
{ try {
    o.parse( source, "break ;" );

    sz_t ledge_level = -1;
    bl_t use_blm = false;

    for( sz_t i = o.stack_block.adl.size - 1; i >= 0; i-- )
    {
        const xoico_che_stack_block_unit_s* unit = o.stack_block.adl.[ i ];
        use_blm = use_blm || unit.use_blm;
        if( unit.break_ledge )
        {
            ledge_level = unit.level;
            break;
        }
    }

    if( ledge_level == -1 ) return source.parse_error_fa( "'break' has no ledge." );

    if( use_blm )
    {
        result.push_fa( "BLM_BREAK_LEVEL(#<sz_t>);", ledge_level );
    }
    else
    {
        result.push_sc( "break;" );
    }

    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:)( er_t trans_control_return( mutable, bcore_source* source, :result* result ) ) =
{ try {
    o.parse( source, "return" );

    $* result_expr = :result_create_plain().scope();
    xoico_typespec_s* typespec_expr = scope( xoico_typespec_s! );
    const xoico_typespec_s* typespec_ret = o.typespec_ret;

    o.trans_expression( source, result_expr, typespec_expr );
    o.trans_whitespace( source, result );
    o.parse( source, ";" );

    if( typespec_expr.type )
    {
        if( !o.returns_a_value() )
        {
            return source.parse_error_fa( "Function does not return a value." );
        }
    }

    bl_t use_blm = false;

    foreach( $* e in o.stack_block.adl )
    {
        if( e.use_blm )
        {
            use_blm = true;
            break;
        }
    }

    if( use_blm )
    {
        if( o.returns_a_value() )
        {
            result.push_sc( "BLM_RETURNV(" );
            o.push_typespec( typespec_ret, result );
            result.push_sc( "," );
            if( typespec_expr.type )
            {
                o.adapt_expression( source, typespec_expr, typespec_ret, result_expr, result );
            }
            else
            {
                result.push_result( result_expr );
            }
            result.push_sc( ")" );  // do not terminate BLM_RETURNV macro with a semicolon, otherwise if-else statements might not be handled correctly
        }
        else
        {
            result.push_sc( "BLM_RETURN" );
            result.push_result( result_expr );
            result.push_sc( ";" );
        }
    }
    else
    {
        result.push_sc( "return " );
        if( typespec_expr.type )
        {
            o.adapt_expression( source, typespec_expr, typespec_ret, result_expr, result );
        }
        else
        {
            result.push_result( result_expr );
        }
        result.push_sc( ";" );
    }

    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

