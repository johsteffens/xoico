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

func (:)( er_t trans_control( mutable, tp_t tp_control, bcore_source* source, st_s* buf ) ) =
{ try {
    switch( tp_control )
    {
        case TYPEOF_for:     return o.trans_control_for(     source, buf );
        case TYPEOF_foreach: return o.trans_control_foreach( source, buf );
        case TYPEOF_if:      return o.trans_control_if(      source, buf );
        case TYPEOF_else:    return o.trans_control_else(    source, buf );
        case TYPEOF_break:   return o.trans_control_break(   source, buf );
        case TYPEOF_while:   return o.trans_control_while(   source, buf );
        case TYPEOF_do:      return o.trans_control_do(      source, buf );
        case TYPEOF_switch:  return o.trans_control_switch(  source, buf );
        case TYPEOF_case:    return o.trans_control_case(    source, buf );
        case TYPEOF_default: return o.trans_control_default( source, buf );
        case TYPEOF_return:  return o.trans_control_return(  source, buf );
        default: return source.parse_error_fa( "Internal error: Invalid control name '#<sc_t>'", ifnameof( tp_control ) );
    }
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:)( er_t trans_control_for( mutable, bcore_source* source, st_s* buf ) ) =
{ try {
    o.inc_block();
    o.stack_block_get_top_unit().break_ledge = true;
    o.trans( source, "for", buf );
    o.trans_whitespace( source, buf );
    o.trans( source, "(", buf );
    o.trans_statement( source, buf ); // def
    o.trans( source, ";", buf );
    o.trans_expression( source, buf, NULL ); // cond
    o.trans( source, ";", buf );
    o.trans_expression( source, buf, NULL ); // update
    o.trans_whitespace( source, buf );
    o.trans( source, ")", buf );
    o.trans_whitespace( source, buf );
    if( source.parse_bl( "#=?'{'" ) )
    {
        o.trans_block( source, buf, false );
    }
    else
    {
        o.trans_statement_as_block( source, buf, false );
    }
    o.dec_block();
    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

/** foreach( <typespec> var in <arr_expr> ) <foreach-statement>
 *  -->
 * { <typespec> __a = (match)<arr_expr>; for( sz_t __i = 0; __i < __a->size; __i++ ) { <typespec> var = (match)__a->data[ __i ]; <foreach-statement> }  }
 */
func (:)( er_t trans_control_foreach( mutable, bcore_source* source, st_s* buf ) ) =
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
    st_s* buf_arr_expr = scope( st_s! );
    o.trans_expression( source, buf_arr_expr, typespec_arr_expr );

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

    st_s* buf_statement = scope( st_s! );
    if( source.parse_bl( "#=?'{'" ) )
    {
        o.trans_block( source, buf_statement, false );
    }
    else
    {
        o.trans_statement_as_block( source, buf_statement, false );
    }

    buf.push_fa( "{" );

    o.push_typespec( typespec_arr, buf );

    buf.push_fa( " __a=" );
    o.adapt_expression( source, typespec_arr_expr, typespec_arr, buf_arr_expr, buf );
    buf.push_fa( ";" );
    buf.push_fa( "if(__a)for(sz_t __i=0; __i<__a->size; __i++){" );
    o.push_typespec( typespec_var, buf );
    buf.push_fa( " #<sc_t>=", xoico_cdaleth_s_nameof( o, tp_var_name ) );

    st_s* buf_element_expr = scope( cast( st_s_create_sc( "__a->data[__i]" ), st_s* ) );
    o.adapt_expression( source, typespec_element, typespec_var, buf_element_expr, buf );
    buf.push_fa( ";" );

    buf.push_fa( "#<sc_t>", buf_statement.sc );

    buf.push_fa( "}}" );
    o.dec_block();
    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:)( er_t trans_control_if( mutable, bcore_source* source, st_s* buf ) ) =
{ try {
    o.trans( source, "if", buf );
    o.trans_whitespace( source, buf );
    o.trans( source, "(", buf );
    o.trans_expression( source, buf, NULL ); // def
    o.trans( source, ")", buf );
    o.trans_whitespace( source, buf );
    if( source.parse_bl( "#=?'{'" ) )
    {
        o.trans_block( source, buf, false );
    }
    else
    {
        o.trans_statement_as_block( source, buf, false );
    }
    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:)( er_t trans_control_while( mutable, bcore_source* source, st_s* buf ) ) =
{ try {
    o.trans( source, "while", buf );
    o.trans_whitespace( source, buf );
    o.trans( source, "(", buf );
    o.trans_expression( source, buf, NULL ); // def
    o.trans( source, ")", buf );
    o.trans_whitespace( source, buf );
    if( source.parse_bl( "#=?'{'" ) )
    {
        o.trans_block( source, buf, true );
    }
    else
    {
        o.trans_statement_as_block( source, buf, true );
    }
    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:)( er_t trans_control_do( mutable, bcore_source* source, st_s* buf ) ) =
{ try {
    o.trans( source, "do", buf );
    o.trans_whitespace( source, buf );
    if( source.parse_bl( "#=?'{'" ) )
    {
        o.trans_block( source, buf, true );
    }
    else
    {
        o.trans_statement_as_block( source, buf, true );
    }
    o.trans( source, "while", buf );
    o.trans_whitespace( source, buf );
    o.trans( source, "(", buf );
    o.trans_expression( source, buf, NULL ); // def
    o.trans( source, ")", buf );
    o.trans_whitespace( source, buf );
    o.trans( source, ";", buf );
    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:)( er_t trans_control_else( mutable, bcore_source* source, st_s* buf ) ) =
{ try {
    o.trans( source, "else", buf );
    o.trans_whitespace( source, buf );
    if( source.parse_bl( "#=?'{'" ) )
    {
        o.trans_block( source, buf, false );
    }
    else
    {
        o.trans_statement_as_block( source, buf, false );
    }
    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:)( er_t trans_control_switch( mutable, bcore_source* source, st_s* buf ) ) =
{ try {
    o.trans( source, "switch", buf );
    o.trans_whitespace( source, buf );
    o.trans( source, "(", buf );
    o.trans_expression( source, buf, NULL ); // def
    o.trans( source, ")", buf );
    o.trans_whitespace( source, buf );
    o.trans_block( source, buf, true );
    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:)( er_t trans_control_case( mutable, bcore_source* source, st_s* buf ) ) =
{ try {
    o.trans( source, "case", buf );
    o.trans_expression( source, buf, NULL );
    o.trans_whitespace( source, buf );
    o.trans( source, ":", buf );
    o.trans_whitespace( source, buf );
    o.trans_statement_as_block( source, buf, false );

    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:)( er_t trans_control_default( mutable, bcore_source* source, st_s* buf ) ) =
{ try {
    o.trans( source, "default", buf );
    o.trans_whitespace( source, buf );
    o.trans( source, ":", buf );
    o.trans_whitespace( source, buf );
    o.trans_statement_as_block( source, buf, false );
    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:)( er_t trans_control_break( mutable, bcore_source* source, st_s* buf ) ) =
{ try {
    o.parse( source, "break ;" );

    sz_t ledge_level = -1;
    bl_t use_blm = false;

    for( sz_t i = o.stack_block.adl.size - 1; i >= 0; i-- )
    {
        const xoico_cdaleth_stack_block_unit_s* unit = o.stack_block.adl.[ i ];
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
        buf.push_fa( "BLM_BREAK_LEVEL(#<sz_t>);", ledge_level );
    }
    else
    {
        buf.push_sc( "break;" );
    }

    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:)( er_t trans_control_return( mutable, bcore_source* source, st_s* buf ) ) =
{ try {
    o.parse( source, "return" );

    st_s* buf_expr = scope( st_s! );
    xoico_typespec_s* typespec_expr = scope( xoico_typespec_s! );
    const xoico_typespec_s* typespec_ret = o.typespec_ret;

    o.trans_expression( source, buf_expr, typespec_expr );
    o.trans_whitespace( source, buf );
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
            buf.push_sc( "BLM_RETURNV(" );
            o.push_typespec( typespec_ret, buf );
            buf.push_sc( "," );
            if( typespec_expr.type )
            {
                o.adapt_expression( source, typespec_expr, typespec_ret, buf_expr, buf );
            }
            else
            {
                buf.push_st( buf_expr );
            }
            buf.push_sc( ")" );  // do not terminate BLM_RETURNV macro with a semicolon, otherwise if-else statements might not be handled correctly
        }
        else
        {
            buf.push_sc( "BLM_RETURN" );
            buf.push_st( buf_expr );
            buf.push_sc( ";" );
        }
    }
    else
    {
        buf.push_sc( "return " );
        if( typespec_expr.type )
        {
            o.adapt_expression( source, typespec_expr, typespec_ret, buf_expr, buf );
        }
        else
        {
            buf.push_st( buf_expr );
        }
        buf.push_sc( ";" );
    }

    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

