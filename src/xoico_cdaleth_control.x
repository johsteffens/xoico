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
{
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
        default: XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Internal error: Invalid control name '#<sc_t>'", ifnameof( tp_control ) );
    }
};

//----------------------------------------------------------------------------------------------------------------------

func (:)( er_t trans_control_for( mutable, bcore_source* source, st_s* buf ) ) =
{
    BLM_INIT();
    xoico_cdaleth_s_inc_block( o );
    xoico_cdaleth_s_stack_block_get_top_unit( o )->break_ledge = true;
    XOICO_BLM_SOURCE_PARSE_FA( source, "for" );
    st_s_push_sc( buf, "for" );
    BLM_TRY( xoico_cdaleth_s_trans_whitespace( o, source, buf ) );
    XOICO_BLM_SOURCE_PARSE_FA( source, "(" );
    st_s_push_sc( buf, "(" );
    BLM_TRY( xoico_cdaleth_s_trans_statement( o, source, buf ) ); // def
    XOICO_BLM_SOURCE_PARSE_FA( source, ";" );
    st_s_push_sc( buf, ";" );
    BLM_TRY( xoico_cdaleth_s_trans_expression( o, source, buf, NULL ) ); // cond
    XOICO_BLM_SOURCE_PARSE_FA( source, ";" );
    st_s_push_sc( buf, ";" );
    BLM_TRY( xoico_cdaleth_s_trans_expression( o, source, buf, NULL ) ); // update
    BLM_TRY( xoico_cdaleth_s_trans_whitespace( o, source, buf ) );
    XOICO_BLM_SOURCE_PARSE_FA( source, ")" );
    st_s_push_sc( buf, ")" );
    BLM_TRY( xoico_cdaleth_s_trans_whitespace( o, source, buf ) );
    if( bcore_source_a_parse_bl_fa( source, "#=?'{'" ) )
    {
        BLM_TRY( xoico_cdaleth_s_trans_block( o, source, buf, false ) )
    }
    else
    {
        BLM_TRY( xoico_cdaleth_s_trans_statement_as_block( o, source, buf, false ) )
    }
    xoico_cdaleth_s_dec_block( o );
    BLM_RETURNV( er_t, 0 );
};

//----------------------------------------------------------------------------------------------------------------------

/** foreach( <typespec> var in <arr_expr> ) <foreach-statement>
 *  -->
 * { <typespec> __a = (match)<arr_expr>; for( sz_t __i = 0; __i < __a->size; __i++ ) { <typespec> var = (match)__a->data[ __i ]; <foreach-statement> }  }
 */
func (:)( er_t trans_control_foreach( mutable, bcore_source* source, st_s* buf ) ) =
{
    BLM_INIT();
    xoico_cdaleth_s_inc_block( o );
    xoico_cdaleth_s_stack_block_get_top_unit( o )->break_ledge = true;
    XOICO_BLM_SOURCE_PARSE_FA( source, "foreach ( " );

    xoico_typespec_s* typespec_var = BLM_CREATE( xoico_typespec_s );
    BLM_TRY( xoico_cdaleth_s_take_typespec( o, source, typespec_var, true ) );

    tp_t tp_var_name = 0;

    if( bcore_source_a_parse_bl_fa( source, "#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||[0]=='_')" ) )
    {
        tp_var_name = xoico_cdaleth_s_get_identifier( o, source, true );
    }
    else
    {
        XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Variable name expected." );
    }

    XOICO_BLM_SOURCE_PARSE_FA( source, " in " );

    xoico_typespec_s* typespec_arr_expr = BLM_CREATE( xoico_typespec_s );
    st_s* buf_arr_expr = BLM_CREATE( st_s );
    BLM_TRY( xoico_cdaleth_s_trans_expression( o, source, buf_arr_expr, typespec_arr_expr ) );

    if( !typespec_arr_expr->type )
    {
        XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Array expression not tractable." );
    }

    xoico_compiler_element_info_s* info = BLM_CREATE( xoico_compiler_element_info_s );
    if( !xoico_compiler_s_get_type_array_element_info( o->compiler, typespec_arr_expr->type, info ) )
    {
        XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Expression does not evaluate to an array." );
    }

    xoico_typespec_s* typespec_element = &info->type_info.typespec;

    if( typespec_var->type == TYPEOF_type_deduce ) typespec_var->type = typespec_element->type;

    XOICO_BLM_SOURCE_PARSE_FA( source, " )" );

    xoico_typespec_s* typespec_arr = BLM_A_CLONE( typespec_arr_expr );
    typespec_arr->indirection = 1;
    typespec_arr->flag_const = true;

    xoico_typespec_s* typespec_idx = BLM_CREATE( xoico_typespec_s );
    typespec_idx->type = TYPEOF_sz_t;

    xoico_cdaleth_s_push_typedecl( o, typespec_var, tp_var_name );
    xoico_cdaleth_s_push_typedecl( o, typespec_arr, xoico_cdaleth_s_entypeof( o, "__a" ) );
    xoico_cdaleth_s_push_typedecl( o, typespec_idx, xoico_cdaleth_s_entypeof( o, "__i" ) );

    st_s* buf_statement = BLM_CREATE( st_s );
    if( bcore_source_a_parse_bl_fa( source, "#=?'{'" ) )
    {
        BLM_TRY( xoico_cdaleth_s_trans_block( o, source, buf_statement, false ) );
    }
    else
    {
        BLM_TRY( xoico_cdaleth_s_trans_statement_as_block( o, source, buf_statement, false ) )
    }

    st_s_push_fa( buf, "{" );

    xoico_cdaleth_s_push_typespec( o, typespec_arr, buf );

    st_s_push_fa( buf, " __a=" );
    BLM_TRY( xoico_cdaleth_s_adapt_expression( o, source, typespec_arr_expr, typespec_arr, buf_arr_expr, buf ) );
    st_s_push_fa( buf, ";" );
    st_s_push_fa( buf, "if(__a)for(sz_t __i=0; __i<__a->size; __i++){" );
    xoico_cdaleth_s_push_typespec( o, typespec_var, buf );
    st_s_push_fa( buf, " #<sc_t>=", xoico_cdaleth_s_nameof( o, tp_var_name ) );

    st_s* buf_element_expr = BLM_A_PUSH( st_s_create_sc( "__a->data[__i]" ) );
    BLM_TRY( xoico_cdaleth_s_adapt_expression( o, source, typespec_element, typespec_var, buf_element_expr, buf ) );
    st_s_push_fa( buf, ";" );

    st_s_push_fa( buf, "#<sc_t>", buf_statement->sc );

    st_s_push_fa( buf, "}" );
    st_s_push_fa( buf, "}" );
    xoico_cdaleth_s_dec_block( o );
    BLM_RETURNV( er_t, 0 );
};

//----------------------------------------------------------------------------------------------------------------------

func (:)( er_t trans_control_if( mutable, bcore_source* source, st_s* buf ) ) =
{
    BLM_INIT();
    XOICO_BLM_SOURCE_PARSE_FA( source, "if" );
    st_s_push_sc( buf, "if" );
    BLM_TRY( xoico_cdaleth_s_trans_whitespace( o, source, buf ) );
    XOICO_BLM_SOURCE_PARSE_FA( source, "(" );
    st_s_push_sc( buf, "(" );
    BLM_TRY( xoico_cdaleth_s_trans_expression( o, source, buf, NULL ) ); // def
    XOICO_BLM_SOURCE_PARSE_FA( source, ")" );
    st_s_push_sc( buf, ")" );
    BLM_TRY( xoico_cdaleth_s_trans_whitespace( o, source, buf ) );
    if( bcore_source_a_parse_bl_fa( source, "#=?'{'" ) )
    {
        BLM_TRY( xoico_cdaleth_s_trans_block( o, source, buf, false ) )
    }
    else
    {
        BLM_TRY( xoico_cdaleth_s_trans_statement_as_block( o, source, buf, false ) )
    }
    BLM_RETURNV( er_t, 0 );
};

//----------------------------------------------------------------------------------------------------------------------

func (:)( er_t trans_control_while( mutable, bcore_source* source, st_s* buf ) ) =
{
    BLM_INIT();
    XOICO_BLM_SOURCE_PARSE_FA( source, "while" );
    st_s_push_sc( buf, "while" );
    BLM_TRY( xoico_cdaleth_s_trans_whitespace( o, source, buf ) );
    XOICO_BLM_SOURCE_PARSE_FA( source, "(" );
    st_s_push_sc( buf, "(" );
    BLM_TRY( xoico_cdaleth_s_trans_expression( o, source, buf, NULL ) ); // def
    XOICO_BLM_SOURCE_PARSE_FA( source, ")" );
    st_s_push_sc( buf, ")" );
    BLM_TRY( xoico_cdaleth_s_trans_whitespace( o, source, buf ) );
    if( bcore_source_a_parse_bl_fa( source, "#=?'{'" ) )
    {
        BLM_TRY( xoico_cdaleth_s_trans_block( o, source, buf, true ) );
    }
    else
    {
        BLM_TRY( xoico_cdaleth_s_trans_statement_as_block( o, source, buf, true ) )
    }
    BLM_RETURNV( er_t, 0 );
};

//----------------------------------------------------------------------------------------------------------------------

func (:)( er_t trans_control_do( mutable, bcore_source* source, st_s* buf ) ) =
{
    BLM_INIT();
    XOICO_BLM_SOURCE_PARSE_FA( source, "do" );
    st_s_push_sc( buf, "do" );
    BLM_TRY( xoico_cdaleth_s_trans_whitespace( o, source, buf ) );
    if( bcore_source_a_parse_bl_fa( source, "#=?'{'" ) )
    {
        BLM_TRY( xoico_cdaleth_s_trans_block( o, source, buf, true ) )
    }
    else
    {
        BLM_TRY( xoico_cdaleth_s_trans_statement_as_block( o, source, buf, true ) )
    }
    XOICO_BLM_SOURCE_PARSE_FA( source, "while" );
    st_s_push_sc( buf, "while" );
    BLM_TRY( xoico_cdaleth_s_trans_whitespace( o, source, buf ) );
    XOICO_BLM_SOURCE_PARSE_FA( source, "(" );
    st_s_push_sc( buf, "(" );
    BLM_TRY( xoico_cdaleth_s_trans_expression( o, source, buf, NULL ) ); // def
    XOICO_BLM_SOURCE_PARSE_FA( source, ")" );
    st_s_push_sc( buf, ")" );
    BLM_TRY( xoico_cdaleth_s_trans_whitespace( o, source, buf ) );
    XOICO_BLM_SOURCE_PARSE_FA( source, ";" );
    st_s_push_sc( buf, ";" );
    BLM_RETURNV( er_t, 0 );
};

//----------------------------------------------------------------------------------------------------------------------

func (:)( er_t trans_control_else( mutable, bcore_source* source, st_s* buf ) ) =
{
    BLM_INIT();
    XOICO_BLM_SOURCE_PARSE_FA( source, "else" );
    st_s_push_sc( buf, "else" );
    BLM_TRY( xoico_cdaleth_s_trans_whitespace( o, source, buf ) );
    if( bcore_source_a_parse_bl_fa( source, "#=?'{'" ) )
    {
        BLM_TRY( xoico_cdaleth_s_trans_block( o, source, buf, false ) )
    }
    else
    {
        BLM_TRY( xoico_cdaleth_s_trans_statement_as_block( o, source, buf, false ) )
    }
    BLM_RETURNV( er_t, 0 );
};

//----------------------------------------------------------------------------------------------------------------------

func (:)( er_t trans_control_switch( mutable, bcore_source* source, st_s* buf ) ) =
{
    BLM_INIT();
    XOICO_BLM_SOURCE_PARSE_FA( source, "switch" );
    st_s_push_sc( buf, "switch" );
    BLM_TRY( xoico_cdaleth_s_trans_whitespace( o, source, buf ) );
    XOICO_BLM_SOURCE_PARSE_FA( source, "(" );
    st_s_push_sc( buf, "(" );
    BLM_TRY( xoico_cdaleth_s_trans_expression( o, source, buf, NULL ) ); // def
    XOICO_BLM_SOURCE_PARSE_FA( source, ")" );
    st_s_push_sc( buf, ")" );
    BLM_TRY( xoico_cdaleth_s_trans_whitespace( o, source, buf ) );
    BLM_TRY( xoico_cdaleth_s_trans_block( o, source, buf, true ) );
    BLM_RETURNV( er_t, 0 );
};

//----------------------------------------------------------------------------------------------------------------------

func (:)( er_t trans_control_case( mutable, bcore_source* source, st_s* buf ) ) =
{
    BLM_INIT();
    XOICO_BLM_SOURCE_PARSE_FA( source, "case" );
    st_s_push_sc( buf, "case" );

    BLM_TRY( xoico_cdaleth_s_trans_expression( o, source, buf, NULL ) );
    BLM_TRY( xoico_cdaleth_s_trans_whitespace( o, source, buf ) );
    XOICO_BLM_SOURCE_PARSE_FA( source, ": " );
    st_s_push_sc( buf, ": " );
    BLM_TRY( xoico_cdaleth_s_trans_statement_as_block( o, source, buf, false ) )

    BLM_RETURNV( er_t, 0 );
};

//----------------------------------------------------------------------------------------------------------------------

func (:)( er_t trans_control_default( mutable, bcore_source* source, st_s* buf ) ) =
{
    BLM_INIT();
    XOICO_BLM_SOURCE_PARSE_FA( source, "default :" );
    st_s_push_sc( buf, "default:" );

    BLM_TRY( xoico_cdaleth_s_trans_statement_as_block( o, source, buf, false ) )

    BLM_RETURNV( er_t, 0 );
};

//----------------------------------------------------------------------------------------------------------------------

func (:)( er_t trans_control_break( mutable, bcore_source* source, st_s* buf ) ) =
{
    BLM_INIT();
    XOICO_BLM_SOURCE_PARSE_FA( source, "break ;" );

    sz_t ledge_level = -1;
    bl_t use_blm = false;

    for( sz_t i = o->stack_block.adl.size - 1; i >= 0; i-- )
    {
        const xoico_cdaleth_stack_block_unit_s* unit = o->stack_block.adl.data[ i ];
        use_blm = use_blm || unit->use_blm;
        if( unit->break_ledge )
        {
            ledge_level = unit->level;
            break;
        }
    }

    if( ledge_level == -1 ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "'break' has no ledge." );

    if( use_blm )
    {
        st_s_push_fa( buf, "BLM_BREAK_LEVEL(#<sz_t>);", ledge_level );
    }
    else
    {
        st_s_push_sc( buf, "break;" );
    }

    BLM_RETURNV( er_t, 0 );
};

//----------------------------------------------------------------------------------------------------------------------

func (:)( er_t trans_control_return( mutable, bcore_source* source, st_s* buf ) ) =
{
    BLM_INIT();
    XOICO_BLM_SOURCE_PARSE_FA( source, "return" );

    st_s* buf_expr = BLM_CREATE( st_s );
    xoico_typespec_s* typespec_expr = BLM_CREATE( xoico_typespec_s );
    const xoico_typespec_s* typespec_ret = o->typespec_ret;

    BLM_TRY( xoico_cdaleth_s_trans_expression( o, source, buf_expr, typespec_expr ) );
    BLM_TRY( xoico_cdaleth_s_trans_whitespace( o, source, buf ) );
    XOICO_BLM_SOURCE_PARSE_FA( source, ";" );

    if( typespec_expr->type )
    {
        if( !xoico_cdaleth_s_returns_a_value( o ) )
        {
            XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Function does not return a value." );
        }
    }

    bl_t use_blm = false;

    for( sz_t i = 0; i < o->stack_block.adl.size; i++ )
    {
        if( o->stack_block.adl.data[ i ]->use_blm )
        {
            use_blm = true;
            break;
        }
    }

    if( use_blm )
    {
        if( xoico_cdaleth_s_returns_a_value( o ) )
        {
            st_s_push_sc( buf, "BLM_RETURNV(" );
            BLM_TRY( xoico_cdaleth_s_push_typespec( o, typespec_ret, buf ) );
            st_s_push_sc( buf, "," );
            if( typespec_expr->type )
            {
                BLM_TRY( xoico_cdaleth_s_adapt_expression( o, source, typespec_expr, typespec_ret, buf_expr, buf ) );
            }
            else
            {
                st_s_push_st( buf, buf_expr );
            }
            st_s_push_sc( buf, ");" );
        }
        else
        {
            st_s_push_sc( buf, "BLM_RETURN" );
            st_s_push_st( buf, buf_expr );
            st_s_push_sc( buf, ";" );
        }
    }
    else
    {
        st_s_push_sc( buf, "return " );
        if( typespec_expr->type )
        {
            BLM_TRY( xoico_cdaleth_s_adapt_expression( o, source, typespec_expr, typespec_ret, buf_expr, buf ) );
        }
        else
        {
            st_s_push_st( buf, buf_expr );
        }
        st_s_push_sc( buf, ";" );
    }

    BLM_RETURNV( er_t, 0 );
};

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

