/** Author and Copyright 2020 Johannes Bernhard Steffens
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file ecdalethpt in compliance with the License.
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

#include "xoico_cdaleth.h"
#include "xoico_caleph.h"
#include "xoico_group.h"
#include "xoico_stamp.h"
#include "xoico_body.h"
#include "xoico_compiler.h"

/**********************************************************************************************************************/

/// Prototypes

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cdaleth_s_trans_statement(  xoico_cdaleth_s* o, bcore_source* source, st_s* buf );
er_t xoico_cdaleth_s_trans_block(      xoico_cdaleth_s* o, bcore_source* source, st_s* buf, bl_t is_break_ledge );
er_t xoico_cdaleth_s_trans_statement_as_block( xoico_cdaleth_s* o, bcore_source* source, st_s* buf_out, bl_t is_break_ledge );
er_t xoico_cdaleth_s_trans_expression( xoico_cdaleth_s* o, bcore_source* source, st_s* buf, xoico_typespec_s* out_typespec /* optional */ );
er_t xoico_cdaleth_s_trans_block_inside_verbatim_c( xoico_cdaleth_s* o, bcore_source* source, st_s* buf );

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cdaleth_s_parse_err_fv( const xoico_cdaleth_s* o, bcore_source* source, sc_t format, va_list args )
{
    return bcore_source_a_parse_err_to_em_fv( source, TYPEOF_parse_error, format, args );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cdaleth_s_parse_err_fa( const xoico_cdaleth_s* o, bcore_source* source, sc_t format, ... )
{
    va_list args;
    va_start( args, format );
    er_t er = xoico_cdaleth_s_parse_err_fv( o, source, format, args );
    va_end( args );
    return er;
}

//----------------------------------------------------------------------------------------------------------------------

bl_t xoico_cdaleth_s_returns_a_value( const xoico_cdaleth_s* o )
{
    return ( o->typespec_ret->type != TYPEOF_void ) || ( o->typespec_ret->indirection > 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/** Inspects name and enrolls it and returns hash;
 *  Detects '$' as TYEPOF_type_deduce
 *  Detects '@' as type of class or group
 *  If no identifier could be detected: Returns 0 and leave source unchanged.
 */
tp_t xoico_cdaleth_s_get_identifier( xoico_cdaleth_s* o, bcore_source* source, bl_t take_from_source )
{
    BLM_INIT();
    tp_t tp_name = 0;
    if( bcore_source_a_parse_bl_fa( source, "#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||[0]=='_'||[0]=='@'||[0]=='$'||([0]==':'&&([1]!=' '&&[1]!='\t'&&[1]!='\n'&&[1]!='/')))" ) )
    {
        sz_t source_index = take_from_source ? 0 : bcore_source_a_get_index( source );
        char c = bcore_source_a_inspect_char( source );
        if( c == '@' )
        {
            bcore_source_a_get_char( source );
            st_s* st_name = BLM_CREATE( st_s );
            st_s_copy( st_name, o->stamp ? &o->stamp->st_name : &o->group->st_name );
            if( bcore_source_a_parse_bl_fa( source, "#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||[0]=='_'||([0]>='0'&&[0]<='9'))" ) )
            {
                bcore_source_a_parse_fa( source, "#:name", st_name );
            }
            tp_name = xoico_cdaleth_s_entypeof( o, st_name->sc );
        }
        else if( c == '$' )
        {
            bcore_source_a_get_char( source );
            tp_name = TYPEOF_type_deduce;
        }
        else if( c == ':' )
        {
            st_s* st_name = BLM_CREATE( st_s );
            xoico_group_s_parse_name( o->group, st_name, source );
            tp_name = xoico_cdaleth_s_entypeof( o, st_name->sc );
        }
        else
        {
            st_s* st_name = BLM_CREATE( st_s );
            bcore_source_a_parse_fa( source, "#name", st_name );
            tp_name = xoico_cdaleth_s_entypeof( o, st_name->sc );
        }
        if( !take_from_source ) bcore_source_a_set_index( source, source_index );
    }

    BLM_RETURNV( tp_t, tp_name );
}

//----------------------------------------------------------------------------------------------------------------------

/** transfers identifier, enrolls it and sets 'tp_identifier' */
er_t xoico_cdaleth_s_trans_identifier( xoico_cdaleth_s* o, bcore_source* source, st_s* buf /* can be NULL */, tp_t* tp_identifier/* can be NULL */ )
{
    BLM_INIT();
    tp_t identifier = xoico_cdaleth_s_get_identifier( o, source, true );
    if( !identifier )
    {
        XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Identifier exected" );
    }
    if( tp_identifier ) *tp_identifier = identifier;
    if( buf ) st_s_push_sc( buf, xoico_cdaleth_s_nameof( o, identifier ) );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/** parses number: (all integer, hex and float encodings)*/
er_t xoico_cdaleth_s_trans_number_literal( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    BLM_INIT();
    bl_t hex = false;
    if( bcore_source_a_parse_bl_fa( source, "#?'0x'" ) )
    {
        st_s_push_sc( buf, "0x" );
        hex = true;
    }
    else if( bcore_source_a_parse_bl_fa( source, "#?'0X'" ) )
    {
        st_s_push_sc( buf, "0X" );
        hex = true;
    }

    if( hex )
    {
        while( bcore_source_a_parse_bl_fa( source, "#?(([0]>='0'&&[0]<='9')||([0]>='a'&&[0]<='f')||([0]>='A'&&[0]<='F'))" ) )
        {
            st_s_push_char( buf, bcore_source_a_get_char( source ) );
        }
    }
    else // decimal
    {
        while( bcore_source_a_parse_bl_fa( source, "#?([0]>='0'&&[0]<='9')" ) )
        {
            st_s_push_char( buf, bcore_source_a_get_char( source ) );
        }
    }

    bl_t fraction = false;

    if( bcore_source_a_parse_bl_fa( source, "#?([0]=='.')" ) )
    {
        st_s_push_char( buf, bcore_source_a_get_char( source ) );
        fraction = true;
    }

    if( fraction )
    {
        while( bcore_source_a_parse_bl_fa( source, "#?([0]>='0'&&[0]<='9')" ) )
        {
            st_s_push_char( buf, bcore_source_a_get_char( source ) );
        }
    }

    bl_t exponent = false;

    if( bcore_source_a_parse_bl_fa( source, "#?([0]=='e'&&[0]=='E')" ) )
    {
        st_s_push_char( buf, bcore_source_a_get_char( source ) );
        exponent = true;
    }

    if( exponent )
    {
        if( bcore_source_a_parse_bl_fa( source, "#?([0]=='+'||[0]=='-')" ) )
        {
            st_s_push_char( buf, bcore_source_a_get_char( source ) );
        }

        while( bcore_source_a_parse_bl_fa( source, "#?([0]>='0'&&[0]<='9')" ) )
        {
            st_s_push_char( buf, bcore_source_a_get_char( source ) );
        }
    }

    // suffix
    while( bcore_source_a_parse_bl_fa( source, "#?([0]=='l'||[0]=='L'||[0]=='u'||[0]=='U'||[0]=='f'||[0]=='F')" ) )
    {
        st_s_push_char( buf, bcore_source_a_get_char( source ) );
    }

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/// parses string
er_t xoico_cdaleth_s_trans_string_literal( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    BLM_INIT();
    XOICO_BLM_SOURCE_PARSE_FA( source, "\"" );
    st_s_push_sc( buf, "\"" );

    while( !bcore_source_a_eos( source ) )
    {
        if( bcore_source_a_parse_bl_fa( source, "#?'\"'" ) )
        {
            st_s_push_sc( buf, "\"" );
            break;
        }

        if( bcore_source_a_parse_bl_fa( source, "#?'\\'" ) )
        {
            st_s_push_sc( buf, "\\" );
            char c = bcore_source_a_inspect_char( source );
            if( c == '"' || c == '\\' )
            {
                st_s_push_char( buf, bcore_source_a_get_char( source ) );
            }
        }
        else
        {
            st_s_push_char( buf, bcore_source_a_get_char( source ) );
        }
    }

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/// character literal
er_t xoico_cdaleth_s_trans_char_literal( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    BLM_INIT();
    XOICO_BLM_SOURCE_PARSE_FA( source, "'" );
    st_s_push_sc( buf, "'" );

    while( !bcore_source_a_eos( source ) )
    {
        if( bcore_source_a_parse_bl_fa( source, "#?\"'\"" ) )
        {
            st_s_push_sc( buf, "'" );
            break;
        }

        if( bcore_source_a_parse_bl_fa( source, "#?'\\'" ) )
        {
            st_s_push_sc( buf, "\\" );
            char c = bcore_source_a_inspect_char( source );
            if( c == '\'' || c == '\\' )
            {
                st_s_push_char( buf, bcore_source_a_get_char( source ) );
            }
        }
        else
        {
            st_s_push_char( buf, bcore_source_a_get_char( source ) );
        }
    }

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/// parses whitespaces including comments
er_t xoico_cdaleth_s_trans_whitespace( xoico_cdaleth_s* o, bcore_source* source, st_s* buf /* can be NULL */ )
{
    bl_t exit_loop = false;
    while( !exit_loop && !bcore_source_a_eos( source ) )
    {
        char c = bcore_source_a_inspect_char( source );
        switch( c )
        {
            case ' ' :
            case '\t':
            case '\n':
            {
                char c = bcore_source_a_get_char( source );
                if( buf ) st_s_push_char( buf, c );
            }
            break;

            case '/':
            {
                if( bcore_source_a_parse_bl_fa( source, "#?'//'" ) )
                {
                    if( buf ) st_s_push_sc( buf, "//" );
                    while( !bcore_source_a_eos( source ) )
                    {
                        char c = bcore_source_a_get_char( source );
                        if( buf ) st_s_push_char( buf, c );
                        if( c == '\n' ) break;
                    }
                }
                else if( bcore_source_a_parse_bl_fa( source, "#?'/*'" ) )
                {
                    if( buf ) st_s_push_sc( buf, "/*" );
                    while( !bcore_source_a_eos( source ) )
                    {
                        if( bcore_source_a_parse_bl_fa( source, "#?'*/'" ) )
                        {
                            if( buf ) st_s_push_sc( buf, "*/" );
                            break;
                        }
                        char c = bcore_source_a_get_char( source );
                        if( buf ) st_s_push_char( buf, c );
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
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cdaleth_s_trans_preprocessor
(
    xoico_cdaleth_s* o,
    bcore_source* source,
    st_s* buf
)
{
    BLM_INIT();
    XOICO_BLM_SOURCE_PARSE_FA( source, "##" );
    st_s_push_fa( buf, "##" );
    while( !bcore_source_a_eos( source ) )
    {
        char c = bcore_source_a_get_char( source );
        st_s_push_char( buf, c );

        if( c == '\\' && bcore_source_a_inspect_char( source ) == '\n' )
        {
            st_s_push_char( buf, bcore_source_a_get_char( source ) );
        }

        if( c == '\n' ) break;
    }

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

// any state; returns !=0 in case an operator was consumed
tp_t xoico_cdaleth_s_trans_operator
(
    xoico_cdaleth_s* o,
    bcore_source* source,
    st_s* buf
)
{
    char c = bcore_source_a_inspect_char( source );

    switch( c )
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
            st_s_push_char( buf, bcore_source_a_get_char( source ) );
            return 1;
        }
        break;

        default: break;
    }

    return false;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cdaleth_s_adapt_expression
(
    xoico_cdaleth_s* o,
    bcore_source* source,
    const xoico_typespec_s* typespec_expr,
    const xoico_typespec_s* typespec_target,
    const st_s* expr,
    st_s* buf
)
{
    BLM_INIT();
    if( !typespec_expr->type )
    {
        XOICO_BLM_SOURCE_PARSE_ERR_FA
        (
            source,
            "xoico_cdaleth_s_adapt_expression: no type specified.",
            typespec_expr->indirection,
            typespec_target->indirection
        );
    }

    bl_t no_adaptation =
        ( typespec_target->indirection == typespec_expr->indirection ) ||
        ( typespec_expr->type == TYPEOF_vd_t ) ||
        ( typespec_expr->type == TYPEOF_vc_t );

    if( no_adaptation )
    {
        st_s_push_fa( buf, "#<st_s*>", expr );
    }
    else if( typespec_target->indirection == typespec_expr->indirection + 1 )
    {
        if( typespec_expr->flag_addressable )
        {
            st_s_push_fa( buf, "&(#<st_s*>)", expr );
        }
        else
        {
            XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Increasing indirection: Expression has no address." );
        }
    }
    else if( typespec_target->indirection == typespec_expr->indirection - 1 )
    {
        st_s_push_fa( buf, "*(#<st_s*>)", expr );
    }
    else
    {
        XOICO_BLM_SOURCE_PARSE_ERR_FA
        (
            source,
            "Cannot adapt from expression's indirection '#<sz_t>' to target indirection '#<sz_t>'.",
            typespec_expr->indirection,
            typespec_target->indirection
        );
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cdaleth_s_trans_typespec_expression
(
    xoico_cdaleth_s* o,
    bcore_source* source,
    st_s* buf,
    const xoico_typespec_s*  in_typespec, // required
          xoico_typespec_s* out_typespec  // optional
)
{
    BLM_INIT();

    BLM_TRY( xoico_cdaleth_s_trans_whitespace( o, source, buf ) );

    if( out_typespec ) out_typespec->type = 0;

    if( bcore_source_a_parse_bl_fa( source, "#?([0]=='.'||([0]=='-'&&[1]=='>'))" ) )
    {
        if( bcore_source_a_parse_bl_fa( source, "#?'->'" ) )
        {
            if( in_typespec->indirection != 1 )
            {
                XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Given indirection is '#<sz_t>'. '->' can only be used at indirection '1'.", in_typespec->indirection );
            }
        }
        else
        {
            XOICO_BLM_SOURCE_PARSE_FA( source, "." );
        }
        XOICO_BLM_SOURCE_PARSE_FA( source, " " );
        xoico_compiler_element_info_s* info = BLM_CREATE( xoico_compiler_element_info_s );
        if( bcore_source_a_parse_bl_fa( source, "#=?'['" ) || bcore_source_a_parse_bl_fa( source, "#=?'?['" ) ) // array subscript
        {
            bl_t bounds_check = false;
            if( bcore_source_a_parse_bl_fa( source, "#=?'?'" ) )
            {
                XOICO_BLM_SOURCE_PARSE_FA( source, "?[" );
                bounds_check = true;
            }
            else
            {
                XOICO_BLM_SOURCE_PARSE_FA( source, "[" );
            }

            if( bounds_check ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Bounds check not yet available." );

            if( in_typespec->indirection > 1 )
            {
                XOICO_BLM_SOURCE_PARSE_ERR_FA
                (
                    source,
                    "Resolving subscript: Indirection '#<sz_t>' is too large.",
                    in_typespec->indirection
                );
            }

            st_s_push_fa( buf, "#<sc_t>data[", ( in_typespec->indirection == 1 ) ? "->" : "." );
            BLM_TRY( xoico_cdaleth_s_trans_expression( o, source, buf, NULL ) );
            XOICO_BLM_SOURCE_PARSE_FA( source, "]" );
            st_s_push_sc( buf, "]" );

            if( xoico_compiler_s_get_type_array_element_info( o->compiler, in_typespec->type, info ) )
            {
                BLM_TRY( xoico_cdaleth_s_trans_typespec_expression( o, source, buf, &info->type_info.typespec, out_typespec ) );
            }
            else
            {
                BLM_TRY( xoico_cdaleth_s_trans_expression( o, source, buf, NULL ) );
            }
        }
        else // member (object or function)
        {
            st_s* buf_ = BLM_CREATE( st_s );
            tp_t tp_identifier = 0;
            BLM_TRY( xoico_cdaleth_s_trans_identifier( o, source, buf_, &tp_identifier ) );
            BLM_TRY( xoico_cdaleth_s_trans_whitespace( o, source, buf_ ) );

            // builtin functions ...
            if( xoico_cdaleth_s_is_builtin_func( o, tp_identifier ) )
            {
                xoico_typespec_s* typespec_builtin = BLM_CREATE( xoico_typespec_s );
                BLM_TRY( xoico_cdaleth_s_trans_builtin( o, tp_identifier, source, buf, in_typespec, buf_, typespec_builtin ) );
                st_s_copy( buf, buf_ );
                BLM_TRY( xoico_cdaleth_s_trans_typespec_expression( o, source, buf, typespec_builtin, out_typespec ) );
            }
            else if( xoico_compiler_s_get_type_element_info( o->compiler, in_typespec->type, tp_identifier, info ) )
            {
                if( info->signature ) // member function
                {
                    if( !bcore_source_a_parse_bl_fa( source, "#?'('" ) ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "'(' expected" );

                    sc_t sc_func_name = xoico_cdaleth_s_nameof( o, info->type_info.typespec.type );
                    ASSERT( sc_func_name );

                    st_s* arg_obj = BLM_CLONE( st_s, buf );
                    st_s_clear( buf );
                    st_s_copy_fa( buf, "#<sc_t>( ", sc_func_name );

                    const xoico_args_s* args = &info->signature->args;

                    if( info->signature->arg_o )
                    {
                        xoico_typespec_s* typespec_obj = BLM_CLONE( xoico_typespec_s, in_typespec );
                        typespec_obj->indirection = 1; // first argument of member functions
                        BLM_TRY( xoico_cdaleth_s_adapt_expression( o, source, in_typespec, typespec_obj, arg_obj, buf ) );
                        if( args->size > 0 ) st_s_push_sc( buf, ", " );
                    }

                    BFOR_EACH( i, args )
                    {
                        BLM_INIT();
                        const xoico_arg_s* arg = &args->data[ i ];
                        st_s* buf_expr = BLM_CREATE( st_s );
                        XOICO_BLM_SOURCE_PARSE_FA( source, " " );
                        if( i > 0 ) XOICO_BLM_SOURCE_PARSE_FA( source, " ," );

                        xoico_typespec_s* typespec_expr = BLM_CREATE( xoico_typespec_s );
                        BLM_TRY( xoico_cdaleth_s_trans_expression( o, source, buf_expr, typespec_expr ) );

                        if( i > 0 ) st_s_push_sc( buf, ", " );

                        if( typespec_expr->type )
                        {
                            BLM_TRY( xoico_cdaleth_s_adapt_expression( o, source, typespec_expr, &arg->typespec, buf_expr, buf ) );
                        }
                        else
                        {
                            st_s_push_st( buf, buf_expr );
                        }

                        BLM_DOWN();
                    }

                    XOICO_BLM_SOURCE_PARSE_FA( source, " )" );
                    st_s_push_sc( buf, ")" );

                    BLM_TRY( xoico_cdaleth_s_trans_typespec_expression( o, source, buf, &info->signature->typespec_ret, out_typespec ) );
                }
                else // traced member element
                {
                    if( in_typespec->indirection > 1 )
                    {
                        XOICO_BLM_SOURCE_PARSE_ERR_FA
                        (
                            source,
                            "Dereferencing #<sc_t>: Indirection '#<sz_t>' is too large.",
                            xoico_cdaleth_s_nameof( o, tp_identifier ),
                            in_typespec->indirection
                        );
                    }
                    st_s_push_fa( buf, "#<sc_t>#<sc_t>", ( in_typespec->indirection == 1 ) ? "->" : ".", buf_->sc );
                    BLM_TRY( xoico_cdaleth_s_trans_typespec_expression( o, source, buf, &info->type_info.typespec, out_typespec ) );
                }
            }
            else if( bcore_source_a_parse_bl_fa( source, "#?'('" ) ) // untraced member function
            {
                st_s* arg_obj = BLM_CLONE( st_s, buf );
                st_s_clear( buf );

                /// Untraced member functions of a group are always treated as 'aware'
                if( xoico_cdaleth_s_is_group( o, in_typespec->type ) )
                {
                    st_s_copy_fa
                    (
                        buf,
                        "#<sc_t>_a_#<sc_t>( ",
                        xoico_cdaleth_s_nameof( o, in_typespec->type ),
                        xoico_cdaleth_s_nameof( o, tp_identifier )
                    );
                }
                else
                {
                    st_s_copy_fa
                    (
                        buf,
                        "#<sc_t>_#<sc_t>( ",
                        xoico_cdaleth_s_nameof( o, in_typespec->type ),
                        xoico_cdaleth_s_nameof( o, tp_identifier )
                    );
                }

                {
                    xoico_typespec_s* typespec_obj = BLM_CLONE( xoico_typespec_s, in_typespec );
                    typespec_obj->indirection = 1; // first argument of member functions
                    BLM_TRY( xoico_cdaleth_s_adapt_expression( o, source, in_typespec, typespec_obj, arg_obj, buf ) );
                }

                bl_t first = true;
                BLM_TRY( xoico_cdaleth_s_trans_whitespace( o, source, buf_ ) );
                while( !bcore_source_a_eos( source ) )
                {
                    if( bcore_source_a_parse_bl_fa( source, "#=?')'" ) ) break;

                    BLM_INIT();
                    st_s* buf_expr = BLM_CREATE( st_s );
                    if( !first ) XOICO_BLM_SOURCE_PARSE_FA( source, "," );
                    BLM_TRY( xoico_cdaleth_s_trans_expression( o, source, buf_expr, NULL ) );
                    BLM_TRY( xoico_cdaleth_s_trans_whitespace( o, source, buf_expr ) );
                    st_s_push_fa( buf, ", " );
                    st_s_push_fa( buf, "#<sc_t>", buf_expr->sc );
                    first = false;
                    BLM_DOWN();
                }

                XOICO_BLM_SOURCE_PARSE_FA( source, ")" );
                st_s_push_sc( buf, ")" );

                BLM_TRY( xoico_cdaleth_s_trans_expression( o, source, buf, NULL ) );
            }
            else // untraced member element
            {
                st_s_push_fa( buf, "#<sc_t>#<sc_t>", ( in_typespec->indirection == 1 ) ? "->" : ".", buf_->sc );
                BLM_TRY( xoico_cdaleth_s_trans_expression( o, source, buf, NULL ) );
            }
        }
    }
    // array subscript
    else if( bcore_source_a_parse_bl_fa( source, "#?'['" ) )
    {
        if( in_typespec->indirection == 0 )
        {
            if( in_typespec->type != TYPEOF_sc_t && in_typespec->type != TYPEOF_sd_t )
            {
                XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Array subscript requires indirection >= 1." );
            }
        }
        st_s_push_sc( buf, "[" );
        BLM_TRY( xoico_cdaleth_s_trans_expression( o, source, buf, NULL ) );
        XOICO_BLM_SOURCE_PARSE_FA( source, "]" );
        st_s_push_sc( buf, "]" );

        xoico_typespec_s* typespec = BLM_CLONE( xoico_typespec_s, in_typespec );
        if( in_typespec->type != TYPEOF_sc_t && in_typespec->type != TYPEOF_sd_t )
        {
            typespec->indirection--;
        }
        BLM_TRY( xoico_cdaleth_s_trans_typespec_expression( o, source, buf, typespec, out_typespec ) );
    }
    // create if not present
    else if( bcore_source_a_parse_bl_fa( source, "#?([0]=='!'&&[1]!='=')" ) )
    {
        XOICO_BLM_SOURCE_PARSE_FA( source, "!" );

        //ignore in case indirection is 0;
        if( in_typespec->indirection > 0 )
        {
            if( !( in_typespec->indirection == 1 && in_typespec->flag_addressable ) )
            {
                XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Create-Operator requires lvalue with addressable indirection of 1." );
            }

            if( xoico_cdaleth_s_is_group( o, in_typespec->type ) )
            {
                XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Create-Operator: lvalue is a group." );
            }

            st_s* arg_obj = BLM_CLONE( st_s, buf );
            st_s_clear( buf );

            sc_t sc_type = xoico_cdaleth_s_nameof( o, in_typespec->type );
            st_s_push_fa( buf, "BCORE_PASS_CREATE(#<sc_t>,#<sc_t>)", sc_type, arg_obj->sc );
        }

        BLM_TRY( xoico_cdaleth_s_trans_typespec_expression( o, source, buf, in_typespec, out_typespec ) );
    }
    // test for presence
    else if( bcore_source_a_parse_bl_fa( source, "#?([0]=='?'&&[1]=='.')" ) )
    {
        XOICO_BLM_SOURCE_PARSE_FA( source, "?" );

        //ignore in case indirection is 0;
        if( in_typespec->indirection > 0 )
        {
            if( in_typespec->indirection != 1 )
            {
                XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Test-Operator requires lvalue with indirection of 1." );
            }

            st_s* arg_obj = BLM_CLONE( st_s, buf );
            st_s_clear( buf );

            sc_t sc_type = xoico_cdaleth_s_nameof( o, in_typespec->type );
            st_s_push_fa( buf, "BCORE_PASS_TEST(#<sc_t>,#<sc_t>)", sc_type, arg_obj->sc );
        }

        BLM_TRY( xoico_cdaleth_s_trans_typespec_expression( o, source, buf, in_typespec, out_typespec ) );
    }
    // attach (detach)
    else if( bcore_source_a_parse_bl_fa( source, "#?'=<'" ) )
    {
        BLM_INIT();
        if( !( in_typespec->indirection == 1 && in_typespec->flag_addressable ) )
        {
            XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Attach-Operator requires lvalue with addressable indirection of 1" );
        }

        st_s* arg_obj = BLM_CLONE( st_s, buf );
        st_s_clear( buf );

        sc_t sc_type = xoico_cdaleth_s_nameof( o, in_typespec->type );
        st_s_push_fa( buf, "#<sc_t>", sc_type );

        xoico_typespec_s* typespec_rval = BLM_CREATE( xoico_typespec_s );
        if( xoico_cdaleth_s_is_group( o, in_typespec->type ) )
        {
            st_s_push_sc( buf, "_a" );
            st_s_push_fa( buf, "_attach( &(#<sc_t>), (#<sc_t>*)", arg_obj->sc, sc_type );
            st_s_push_fa( buf, "(" );
            xoico_cdaleth_s_trans_expression( o, source, buf, typespec_rval );
            st_s_push_fa( buf, "))" );
        }
        else
        {
            st_s_push_fa( buf, "_attach( &(#<sc_t>), ", arg_obj->sc );
            xoico_cdaleth_s_trans_expression( o, source, buf, typespec_rval );
            st_s_push_fa( buf, ")" );
        }

        if( typespec_rval->type && typespec_rval->indirection != 1 )
        {
            XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Attach operator requires rvalue with indirection '1'" );
        }

        if( out_typespec ) xoico_typespec_s_copy( out_typespec, in_typespec );
        BLM_DOWN();
    }
    else if( out_typespec )
    {
        xoico_typespec_s_copy( out_typespec, in_typespec );
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cdaleth_s_trans_member( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    BLM_INIT();
    BLM_TRY( xoico_cdaleth_s_trans_whitespace( o, source, buf ) );
    tp_t tp_name = 0;
    BLM_TRY( xoico_cdaleth_s_trans_identifier( o, source, buf, &tp_name ) );
    BLM_TRY( xoico_cdaleth_s_trans_whitespace( o, source, buf ) );
    if( bcore_source_a_parse_bl_fa( source, "#?'('") )
    {
        XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Untraced member function '#<sc_t>'\n", xoico_cdaleth_s_nameof( o, tp_name ) );
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/** Tests for typespec
 *  If possible, takes typespec from source, otherwise leaves source unchanged
 */
er_t xoico_cdaleth_s_try_take_typespec
(
    xoico_cdaleth_s* o,
    bcore_source* source,
    xoico_typespec_s* typespec,
    bl_t require_tractable_type,
    bl_t* success
)
{
    BLM_INIT();

    if( success ) *success = false;

    sz_t index = bcore_source_a_get_index( source );

    BLM_TRY( xoico_cdaleth_s_trans_whitespace( o, source, NULL ) );
    tp_t tp_name = xoico_cdaleth_s_get_identifier( o, source, true );

    if( !tp_name )
    {
        bcore_source_a_set_index( source, index );
        BLM_RETURNV( er_t, 0 );
    }

    BLM_TRY( xoico_cdaleth_s_trans_whitespace( o, source, NULL ) );

    while( tp_name == TYPEOF_const || tp_name == TYPEOF_static || tp_name == TYPEOF_volatile || tp_name == TYPEOF_keep )
    {
        if( tp_name == TYPEOF_const    ) typespec->flag_const    = true;
        if( tp_name == TYPEOF_static   ) typespec->flag_static   = true;
        if( tp_name == TYPEOF_volatile ) typespec->flag_volatile = true;
        if( tp_name == TYPEOF_keep     ) typespec->flag_keep     = true;

        // take fails if keyword is actually a function
        if( bcore_source_a_parse_bl_fa( source, "#?'('" ) )
        {
            bcore_source_a_set_index( source, index );
            BLM_RETURNV( er_t, 0 );
        }

        BLM_TRY( xoico_cdaleth_s_trans_identifier( o, source, NULL, &tp_name ) );
        BLM_TRY( xoico_cdaleth_s_trans_whitespace( o, source, NULL ) );
    }

    typespec->type = tp_name;
    while( bcore_source_a_parse_bl_fa( source, "#?'*'" ) )
    {
        typespec->indirection++;
        BLM_TRY( xoico_cdaleth_s_trans_whitespace( o, source, NULL ) );
    }

    if( require_tractable_type )
    {
        if( !( tp_name == TYPEOF_type_deduce || xoico_cdaleth_s_is_type( o, tp_name ) ) )
        {
            bcore_source_a_set_index( source, index );
            BLM_RETURNV( er_t, 0 );
        }
    }

    if( success ) *success = true;
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cdaleth_s_take_typespec
(
    xoico_cdaleth_s* o,
    bcore_source* source,
    xoico_typespec_s* typespec,
    bl_t require_tractable_type
)
{
    BLM_INIT();
    bl_t success = false;
    BLM_TRY( xoico_cdaleth_s_try_take_typespec( o, source, typespec, require_tractable_type, &success ) );

    if( !success )
    {
        if( require_tractable_type )
        {
            XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Typespec: Syntax error or intractable type." );
        }
        else
        {
            XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Typespec: Syntax error." );
        }
    }

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cdaleth_s_push_typespec
(
    xoico_cdaleth_s* o,
    const xoico_typespec_s* typespec,
    st_s* buf
)
{
    BLM_INIT();
    tp_t type = typespec->type;

    if( type == TYPEOF_type_object )
    {
        type = o->obj_type;
    }
    else if( type == TYPEOF_type_deduce )
    {
        ERR_fa( "Cannot resolve 'type_deduce' at this point." );
    }
    else if( type == 0 )
    {
        ERR_fa( "Type is 0." );
    }

    st_s* st_type = BLM_A_PUSH( st_s_create_sc( xoico_cdaleth_s_nameof( o, type ) ) );

    if( st_type->size == 0 )
    {
        ERR_fa( "Type has no name." );
    }

    sc_t sc_type = st_type->sc;
    if( typespec->flag_static ) st_s_push_fa( buf, "static " );
    if( typespec->flag_const ) st_s_push_fa( buf, "const " );
    if( typespec->flag_volatile ) st_s_push_fa( buf, "volatile " );
    st_s_push_fa( buf, "#<sc_t>", sc_type );

    for( sz_t i = 0; i < typespec->indirection; i++ ) st_s_push_fa( buf, "*" );
    if( typespec->flag_restrict ) st_s_push_fa( buf, "restrict " );

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/** Translates declaration including optional subsequent assignment.
 *  If no declaration was detected, source and buf_out are not modified.
 */
er_t xoico_cdaleth_s_try_trans_declaration
(
    xoico_cdaleth_s* o,
    bcore_source* source,
    st_s* buf_out,
    bl_t* success
)
{
    BLM_INIT();

    if( success ) *success = false;

    xoico_typespec_s* typespec_var = BLM_CREATE( xoico_typespec_s );

    sz_t index = bcore_source_a_get_index( source );

    st_s* buf_var = BLM_CREATE( st_s );

    bl_t success_take_typespec = false;
    BLM_TRY( xoico_cdaleth_s_try_take_typespec( o, source, typespec_var, true, &success_take_typespec ) );
    if( !success_take_typespec )
    {
        bcore_source_a_set_index( source, index );
        BLM_RETURNV( er_t, 0 );
    }

    BLM_TRY( xoico_cdaleth_s_trans_whitespace( o, source, buf_var ) );

    if
    (
        typespec_var->type &&
        bcore_source_a_parse_bl_fa( source, "#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||[0]=='_')" )
    )
    {
        tp_t tp_name = 0;
        BLM_TRY( xoico_cdaleth_s_trans_identifier( o, source, buf_var, &tp_name ) );
        BLM_TRY( xoico_cdaleth_s_trans_whitespace( o, source, buf_var ) );

        bl_t pushed_typedecl = false;

        if( typespec_var->type != TYPEOF_type_deduce )
        {
            xoico_cdaleth_s_push_typedecl( o, typespec_var, tp_name );
            pushed_typedecl = true;
        }

        if( bcore_source_a_parse_bl_fa( source, "#?'='" ) )
        {
            st_s_push_sc( buf_var, "=" );
            xoico_typespec_s* typespec_expr = BLM_CREATE( xoico_typespec_s );
            st_s* buf_expr = BLM_CREATE( st_s );
            BLM_TRY( xoico_cdaleth_s_trans_expression( o, source, buf_expr, typespec_expr ) );

            if( typespec_var->type == TYPEOF_type_deduce )
            {
                if( !typespec_expr->type )
                {
                    XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Declaration-syntax: Deduce requested but expression is intractable." );
                }
                typespec_var->type = typespec_expr->type;
            }

            if( typespec_expr->type )
            {
                BLM_TRY( xoico_cdaleth_s_adapt_expression( o, source, typespec_expr, typespec_var, buf_expr, buf_var ) );
            }
            else
            {
                st_s_push_st( buf_var, buf_expr );
            }
        }
        else
        {
            if( typespec_var->type == TYPEOF_type_deduce )
            {
                XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Declaration-syntax: Deduce requested without assignment." );
            }
        }

        if( !pushed_typedecl )
        {
            xoico_cdaleth_s_push_typedecl( o, typespec_var, tp_name );
            pushed_typedecl = true;
        }

        xoico_cdaleth_s_push_typespec( o, typespec_var, buf_out );
        st_s_push_char( buf_out, ' ' );
        st_s_push_st( buf_out, buf_var );
        if( success ) *success = true;
    }
    else
    {
        bcore_source_a_set_index( source, index );
        BLM_RETURNV( er_t, 0 );
    }

    if( success ) *success = true;
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cdaleth_s_trans_expression
(
    xoico_cdaleth_s* o,
    bcore_source* source,
    st_s* buf_out, // can be NULL
    xoico_typespec_s* out_typespec // optional
)
{
    BLM_INIT();

    sc_t sc_bl_end_of_expression = "#?([0]==';'||[0]=='{'||[0]=='}'||[0]==')'||[0]==']'||[0]==','||([0]==':'&&([1]==' '||[1]=='\t'||[1]=='\n'||[1]=='/')))";

    BLM_TRY( xoico_cdaleth_s_trans_whitespace( o, source, buf_out ) );

    st_s* buf = BLM_CREATE( st_s );
    bl_t continuation = true;

    if( out_typespec ) xoico_typespec_s_reset( out_typespec );

    tp_t tp_identifier = xoico_cdaleth_s_get_identifier( o, source, false );

    if( tp_identifier )
    {
        if( xoico_cdaleth_s_is_builtin_func( o, tp_identifier ) )
        {
            xoico_typespec_s* typespec_builtin = BLM_CREATE( xoico_typespec_s );
            BLM_TRY( xoico_cdaleth_s_trans_builtin( o, tp_identifier, source, NULL, NULL, buf, typespec_builtin ) );
            xoico_cdaleth_s_trans_typespec_expression( o, source, buf, typespec_builtin, out_typespec );
            continuation = false;
        }

        else if( tp_identifier == TYPEOF_verbatim_C )
        {
            XOICO_BLM_SOURCE_PARSE_FA( source, "verbatim_C {" );
            BLM_TRY( xoico_cdaleth_s_trans_block_inside_verbatim_c( o, source, buf ) );
            XOICO_BLM_SOURCE_PARSE_FA( source, " }" );
        }

        // a control name marks end of expression...
        else if( xoico_cdaleth_s_is_control_name( o, tp_identifier ) )
        {
            continuation = false;
        }
        else if( xoico_cdaleth_s_is_var( o, tp_identifier ) )
        {
            BLM_INIT();
            tp_t tp_name = 0;
            BLM_TRY( xoico_cdaleth_s_trans_identifier( o, source, buf, &tp_name ) );
            BLM_TRY( xoico_cdaleth_s_trans_whitespace( o, source, buf ) );
            const xoico_typespec_s* typespec = xoico_cdaleth_stack_var_s_get_typespec( &o->stack_var, tp_name );
            ASSERT( typespec );
            BLM_TRY( xoico_cdaleth_s_trans_typespec_expression( o, source, buf, typespec, out_typespec ) );
            BLM_DOWN();
        }
        else if( xoico_cdaleth_s_is_type( o, tp_identifier ) )
        {
            st_s* buf_ = BLM_CREATE( st_s );
            BLM_TRY( xoico_cdaleth_s_trans_identifier( o, source, buf_, NULL ) );
            BLM_TRY( xoico_cdaleth_s_trans_whitespace( o, source, buf_ ) );
            if( bcore_source_a_parse_bl_fa( source, "#?'!'" ) )
            {
                if( xoico_cdaleth_s_is_group( o, tp_identifier ) )
                {
                    XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Operator '!': lvalue is a group." );
                }
                st_s_push_fa( buf, "#<sc_t>_create()", xoico_cdaleth_s_nameof( o, tp_identifier ) );
                xoico_typespec_s* typespec = BLM_CREATE( xoico_typespec_s );
                typespec->type = tp_identifier;
                typespec->indirection = 1;
                typespec->flag_addressable = false;
                xoico_cdaleth_s_trans_typespec_expression( o, source, buf, typespec, out_typespec );
                continuation = false;
            }
            else
            {
                st_s_push_st( buf, buf_ );
            }
        }
        else
        {
            BLM_INIT();
            BLM_TRY( xoico_cdaleth_s_trans_identifier( o, source, buf, NULL ) );
            BLM_TRY( xoico_cdaleth_s_trans_expression( o, source, buf, NULL ) );
            BLM_DOWN();
        }
    }

    // number literal
    else if( bcore_source_a_parse_bl_fa( source, "#?([0]>='0'&&[0]<='9')" ) )
    {
        BLM_TRY( xoico_cdaleth_s_trans_number_literal( o, source, buf ) );
    }

    // string literal
    else if( bcore_source_a_parse_bl_fa( source, "#=?'\"'" ) )
    {
        BLM_TRY( xoico_cdaleth_s_trans_string_literal( o, source, buf ) );
    }

    // character literal
    else if( bcore_source_a_parse_bl_fa( source, "#=?\"'\"" ) )
    {
        BLM_TRY( xoico_cdaleth_s_trans_char_literal( o, source, buf ) );
    }

    // member access
    else if( bcore_source_a_parse_bl_fa( source, "#?'.'" ) )
    {
        st_s_push_sc( buf, "." );
        BLM_TRY( xoico_cdaleth_s_trans_member( o, source, buf ) );
    }
    else if( bcore_source_a_parse_bl_fa( source, "#?'->'" ) )
    {
        st_s_push_sc( buf, "->" );
        BLM_TRY( xoico_cdaleth_s_trans_member( o, source, buf ) );
    }

    // attach operator
    else if( bcore_source_a_parse_bl_fa( source, "#?'=<'" ) )
    {
        XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Attach operator: Expression not tractable." );
    }

    // general operator
    else if( xoico_cdaleth_s_trans_operator( o, source, buf ) )
    {
    }

    // ternary branch operator
    else if( bcore_source_a_parse_bl_fa( source, "#?'?'" ) )
    {
        st_s_push_sc( buf, "?" );
        BLM_TRY( xoico_cdaleth_s_trans_expression( o, source, buf, NULL ) );
        XOICO_BLM_SOURCE_PARSE_FA( source, ": " );
        st_s_push_sc( buf, ": " );
        BLM_TRY( xoico_cdaleth_s_trans_expression( o, source, buf, NULL ) );
    }

    // general bracket
    else if( bcore_source_a_parse_bl_fa( source, "#?'('" ) )
    {
        BLM_INIT();
        st_s_push_sc( buf, "(" );

        xoico_typespec_s* typespec = BLM_CREATE( xoico_typespec_s );
        while( !bcore_source_a_eos( source ) )
        {
            BLM_TRY( xoico_cdaleth_s_trans_expression( o, source, buf, typespec ) );
            if( bcore_source_a_parse_bl_fa( source, "#?')'" ) )
            {
                break;
            }
            else if( bcore_source_a_parse_bl_fa( source, "#=?','" ) )
            {
                st_s_push_char( buf, bcore_source_a_get_char( source ) );
            }
            else
            {
                XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Syntax error in bracket expression." );
            }

            typespec->type = 0;
        }
        st_s_push_sc( buf, ")" );

        if( typespec->type ) BLM_TRY( xoico_cdaleth_s_trans_typespec_expression( o, source, buf, typespec, out_typespec ) );

        BLM_DOWN();
    }

    // array subscript
    else if( bcore_source_a_parse_bl_fa( source, "#?'['" ) )
    {
        st_s_push_sc( buf, "[" );
        BLM_TRY( xoico_cdaleth_s_trans_expression( o, source, buf, NULL ) );
        XOICO_BLM_SOURCE_PARSE_FA( source, "]" );
        st_s_push_sc( buf, "]" );
    }

    // end of expression...
    else if( bcore_source_a_parse_bl_fa( source, sc_bl_end_of_expression ) )
    {
        continuation = false;
    }

    // unhandled
    else
    {
        XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Syntax error after '#<sc_t>'", buf->sc );
    }

    if( continuation )
    {
        if( !bcore_source_a_parse_bl_fa( source, sc_bl_end_of_expression ) )
        {
            if( out_typespec ) xoico_typespec_s_reset( out_typespec );
            BLM_TRY( xoico_cdaleth_s_trans_expression( o, source, buf, NULL ) );
        }
    }

    if( buf_out ) st_s_push_st( buf_out, buf );

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cdaleth_s_inspect_variable( xoico_cdaleth_s* o, bcore_source* source )
{
    XOICO_BLM_SOURCE_PARSE_FA( source, "\?\?" );

    BLM_INIT();
    st_s* st   = BLM_CREATE( st_s );
    st_s* buf_ = BLM_CREATE( st_s );
    xoico_typespec_s* typespec = BLM_CREATE( xoico_typespec_s );
    XOICO_BLM_SOURCE_PARSE_FA( source, " #until';' ", st );
    XOICO_BLM_SOURCE_PARSE_FA( source, ";" );
    bcore_msg_fa( " \?? #<sc_t>;\n", st->sc );
    if( xoico_cdaleth_s_trans_expression( o, BLM_A_PUSH( bcore_source_string_s_create_fa( "#<st_s*>;", st ) ), buf_, typespec ) )
    {
        bcore_error_pop_to_sink( BCORE_STDOUT );
        bcore_msg_fa( "\n" );
    }
    else
    {
        if( st->size == 0 ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Variable name expected." )
        bcore_msg_fa( "--> #<sc_t>;\n", buf_->sc );

        if( typespec->type )
        {
            bcore_msg_fa( "Expression yields typespec:\n" );
            bcore_msg_fa( "  const      : #<bl_t>\n", typespec->flag_const );
            bcore_msg_fa( "  type       : #<sc_t>\n", xoico_cdaleth_s_nameof( o, typespec->type ) );
            bcore_msg_fa( "  indirection: #<sz_t>\n", typespec->indirection );
        }
        else
        {
            bcore_msg_fa( "Expression does not yield a typespec.\n" );
        }
    }

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cdaleth_s_trans_statement( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    BLM_INIT();

    BLM_TRY( xoico_cdaleth_s_trans_whitespace( o, source, buf ) );

    if( bcore_source_a_parse_bl_fa( source, "#?([0]=='{'||[0]=='#'||[0]==';'||[0]==','||[0]==')'||[0]=='}'||([0]=='?'&&[1]=='?'))" ) )
    {
        char c = bcore_source_a_inspect_char( source );
        switch( c )
        {
            case '{':
            {
                BLM_TRY( xoico_cdaleth_s_trans_block( o, source, buf, false ) )
            }
            break;

            case '#':
            {
                BLM_TRY( xoico_cdaleth_s_trans_preprocessor( o, source, buf ) );
            }
            break;

            case ';':
            {
                bcore_source_a_get_char( source );
                st_s_push_char( buf, ';' );
            }
            break;

            case ',':
            {
                bcore_source_a_get_char( source );
                st_s_push_char( buf, ',' );
            }
            break;

            case '?':
            {
                BLM_TRY( xoico_cdaleth_s_inspect_variable( o, source ) );
            }
            break;

            case ')':
            {
                XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Unmatched closing bracket." );
            }
            break;

            case '}':
            {
                // nothing
            }
            break;

            default: break;
        }
    }
    else
    {
        tp_t tp_identifier = xoico_cdaleth_s_get_identifier( o, source, false );

        if( tp_identifier && xoico_cdaleth_s_is_control_name( o, tp_identifier ) )
        {
            BLM_TRY( xoico_cdaleth_s_trans_control( o, tp_identifier, source, buf ) );
        }
        else
        {
            BLM_INIT();

            bl_t success_declaration = false;

            BLM_TRY( xoico_cdaleth_s_try_trans_declaration( o, source, buf, &success_declaration ) );
            BLM_TRY( xoico_cdaleth_s_trans_expression( o, source, buf, NULL ) );
            BLM_TRY( xoico_cdaleth_s_trans_whitespace( o, source, buf ) );

            // ':' between expressions is to be taken literally
            if( bcore_source_a_parse_bl_fa( source, "#?':'" ) ) st_s_push_char( buf, ':' );

            BLM_DOWN();
        }
    }

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cdaleth_s_trans_block_inside( xoico_cdaleth_s* o, bcore_source* source, st_s* buf_out )
{
    BLM_INIT();

    st_s* buf = BLM_CREATE( st_s );

    while
    (
        !bcore_source_a_parse_bl_fa( source, "#=?'}'" ) &&
        !bcore_source_a_eos( source )
    )
    {
        BLM_TRY( xoico_cdaleth_s_trans_statement( o, source, buf ) );
    }

    if( xoico_cdaleth_s_stack_block_get_top_unit( o )->use_blm )
    {
        st_s_push_fa( buf_out, "BLM_INIT_LEVEL(#<sz_t>);", o->level );
        st_s_push_st( buf_out, buf );

        if( ( o->level > 0 ) || !xoico_cdaleth_s_returns_a_value( o ) )
        {
            st_s_push_sc( buf_out, "BLM_DOWN();" );
        }
    }
    else
    {
        st_s_push_st( buf_out, buf );
    }

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cdaleth_s_trans_block( xoico_cdaleth_s* o, bcore_source* source, st_s* buf, bl_t is_break_ledge )
{
    BLM_INIT();
    xoico_cdaleth_s_inc_block( o );
    xoico_cdaleth_s_stack_block_get_top_unit( o )->break_ledge = is_break_ledge;
    BLM_TRY( xoico_cdaleth_s_trans_whitespace( o, source, buf ) );

    XOICO_BLM_SOURCE_PARSE_FA( source, "{" );
    st_s_push_char( buf, '{' );

    BLM_TRY( xoico_cdaleth_s_trans_block_inside( o, source, buf ) );

    BLM_TRY( xoico_cdaleth_s_trans_whitespace(   o, source, buf ) );
    XOICO_BLM_SOURCE_PARSE_FA( source, "}" );
    st_s_push_char( buf, '}' );

    xoico_cdaleth_s_dec_block( o );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cdaleth_s_trans_statement_as_block( xoico_cdaleth_s* o, bcore_source* source, st_s* buf_out, bl_t is_break_ledge )
{
    BLM_INIT();
    st_s* buf = BLM_CREATE( st_s );

    xoico_cdaleth_s_inc_block( o );
    xoico_cdaleth_s_stack_block_get_top_unit( o )->break_ledge = is_break_ledge;

    BLM_TRY( xoico_cdaleth_s_trans_statement( o, source, buf ) );
    BLM_TRY( xoico_cdaleth_s_trans_whitespace( o, source, buf ) );
    if( bcore_source_a_parse_bl_fa( source, "#?';'" ) ) st_s_push_sc( buf, ";" );

    if( xoico_cdaleth_s_stack_block_get_top_unit( o )->use_blm )
    {
        st_s_push_fa( buf_out, "{BLM_INIT_LEVEL(#<sz_t>);", o->level );
        st_s_push_st( buf_out, buf );
        st_s_push_sc( buf_out, "BLM_DOWN();}" );
    }
    else
    {
        st_s_push_st( buf_out, buf );
    }

    xoico_cdaleth_s_dec_block( o );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cdaleth_s_trans_block_inside_verbatim_c( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    BLM_INIT();
    BLM_TRY( xoico_cdaleth_s_trans_whitespace( o, source, buf ) );
    while
    (
        !bcore_source_a_parse_bl_fa( source, "#=?'}'" ) &&
        !bcore_source_a_eos( source )
    )
    {
        char c = bcore_source_a_inspect_char( source );
        switch( c )
        {
            case '"':
            {
                BLM_TRY( xoico_cdaleth_s_trans_string_literal( o, source, buf ) );
            }
            break;

            case '\'':
            {
                BLM_TRY( xoico_cdaleth_s_trans_char_literal( o, source, buf ) );
            }
            break;

            case '{':
            {
                st_s_push_char( buf, bcore_source_a_get_char( source ) );
                BLM_TRY( xoico_cdaleth_s_trans_block_inside_verbatim_c( o, source, buf ) );
                XOICO_BLM_SOURCE_PARSE_FA( source, "}" );
                st_s_push_char( buf, '}' );
            }
            break;

            default:
            {
                st_s_push_char( buf, bcore_source_a_get_char( source ) );
            }
            break;
        }
        BLM_TRY( xoico_cdaleth_s_trans_whitespace( o, source, buf ) );
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cdaleth_s_setup( xoico_cdaleth_s* o, const xoico_body_s* body, const xoico_signature_s* signature )
{
    BLM_INIT();
    sc_t sc_obj_type = ( signature->arg_o ) ? ( body->stamp ? body->stamp->st_name.sc : body->group->st_name.sc ) : NULL;

    const xoico_args_s* args = &signature->args;

    tp_t obj_type  = ( signature->arg_o == 0 ) ? 0 : xoico_cdaleth_s_entypeof( o, sc_obj_type );
    bl_t obj_const = ( signature->arg_o == TYPEOF_const );
    tp_t obj_name  = xoico_cdaleth_s_entypeof( o, "o" );

    o->args     = ( xoico_args_s* )args;
    o->typespec_ret = ( xoico_typespec_s* )&signature->typespec_ret;
    o->group    = body->code->group;
    o->stamp    = body->code->stamp;
    o->compiler = xoico_group_s_get_compiler( body->group );
    o->obj_type = obj_type;

    xoico_cdaleth_stack_var_s_clear( &o->stack_var );

    xoico_cdaleth_s_init_level0( o );

    xoico_cdaleth_stack_var_unit_s* unit = BLM_CREATE( xoico_cdaleth_stack_var_unit_s );

    if( obj_type )
    {
        unit->typespec.flag_const = obj_const;
        unit->typespec.type = obj_type;
        unit->typespec.indirection = 1;
        unit->name = obj_name;
        unit->level = o->level;
        xoico_cdaleth_stack_var_s_push_unit( &o->stack_var, unit );
        bcore_hmap_name_s_set_sc( &o->hmap_name, xoico_compiler_s_nameof( o->compiler, obj_type ) );
        bcore_hmap_name_s_set_sc( &o->hmap_name, xoico_compiler_s_nameof( o->compiler, obj_name ) );
    }

    BFOR_EACH( i, args )
    {
        const xoico_arg_s* arg = &args->data[ i ];
        if( arg->typespec.type && arg->name )
        {
            xoico_typespec_s_copy( &unit->typespec, &arg->typespec );
            if( obj_type ) xoico_typespec_s_relent( &unit->typespec, o->group, obj_type );
            unit->name = arg->name;
            unit->level = o->level;
            xoico_cdaleth_stack_var_s_push_unit( &o->stack_var, unit );
            bcore_hmap_name_s_set_sc( &o->hmap_name, xoico_compiler_s_nameof( o->compiler, arg->typespec.type ) );
            bcore_hmap_name_s_set_sc( &o->hmap_name, xoico_compiler_s_nameof( o->compiler, arg->name ) );
        }
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cdaleth_s_translate( const xoico_cdaleth_s* o, const xoico_body_s* body, const xoico_signature_s* signature, bcore_sink* sink )
{
    BLM_INIT();

    xoico_cdaleth_s* engine = BLM_CLONE( xoico_cdaleth_s, o );
    xoico_cdaleth_s_setup( engine, body, signature );

    bcore_source* source = BLM_A_PUSH( bcore_source_point_s_clone_source( &body->code->source_point ) );

    st_s* buf = BLM_CREATE( st_s );

    sz_t indent = 0;
    XOICO_BLM_SOURCE_PARSE_FA( source, " {" );

    while( bcore_source_a_parse_bl_fa( source, "#?([0]==' '||[0]=='\t')" ) ) { bcore_source_a_get_char( source ); };
    if( bcore_source_a_parse_bl_fa( source, "#?'\n'" ) )
    {
        while( bcore_source_a_parse_bl_fa( source, "#?' '" ) ) indent++;
    }

    BLM_TRY( xoico_cdaleth_s_trans_block_inside( engine, source, buf ) );

    XOICO_BLM_SOURCE_PARSE_FA( source, " }" );

    if( indent > 0 ) st_s_replace_st_d_st_d( buf, st_s_create_fa( "\n#rn{ }", indent ), st_s_create_fa( "\n" ) );

    //remove trailing whitespaces
    for( sz_t i = buf->size - 1; i >= 0; i-- )
    {
        if( buf->data[ i ] != ' ' && buf->data[ i ] != '\t' && buf->data[ i ] != '\n' ) break;
        buf->data[ i ] = 0;
        buf->size = i;
    }

    if( o->verbose )
    {
        bcore_sink_a_push_fa( BCORE_STDOUT, "##############################\n" );
        bcore_sink_a_push_fa( BCORE_STDOUT, "#<st_s*>\n", buf );
    }

    if( o->insert_source_reference && !body->code->single_line )
    {
        bcore_sink_a_push_fa( sink, "// " );
        bcore_source_point_s_source_reference_to_sink( &body->code->source_point, true, sink );
        bcore_sink_a_push_fa( sink, "\n" );
    }

    bcore_sink_a_push_sc( sink, buf->sc );

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

