/** Author and Copyright 2020 Johannes Bernhard Steffens
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file ecgimelpt in compliance with the License.
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

#include "xoico_cgimel.h"
#include "xoico_caleph.h"
#include "xoico_group.h"
#include "xoico_stamp.h"
#include "xoico_body.h"
#include "xoico_compiler.h"

/**********************************************************************************************************************/

/// Prototypes

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cgimel_s_trans_statement(  xoico_cgimel_s* o, bcore_source* source, st_s* buf );
er_t xoico_cgimel_s_trans_block(      xoico_cgimel_s* o, bcore_source* source, st_s* buf );
er_t xoico_cgimel_s_trans_expression( xoico_cgimel_s* o, bcore_source* source, st_s* buf, xoico_typespec_s* out_typespec /* optional */ );
er_t xoico_cgimel_s_trans_block_inside_verbatim( xoico_cgimel_s* o, bcore_source* source, st_s* buf );

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

/** parses name and enrolls it and returns hash */
er_t xoico_cgimel_s_trans_name( xoico_cgimel_s* o, bcore_source* source, st_s* buf, tp_t* name )
{
    BLM_INIT();
    char c = bcore_source_a_inspect_char( source );
    st_s* st_name = BLM_CREATE( st_s );
    if( c == '@' )
    {
        bcore_source_a_get_char( source );
        if( !o->stamp ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Ill placed '@'." );
        st_s_push_fa( st_name, "#<sc_t>", o->stamp->name.sc );
        if( bcore_source_a_parse_bl_fa( source, "#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||[0]=='_'||([0]>='0'&&[0]<='9'))" ) )
        {
            bcore_source_a_parse_fa( source, "#:name", st_name );
        }
    }
    else if( c == ':' )
    {
        xoico_group_s_parse_name( o->group, st_name, source );
    }
    else
    {
        bcore_source_a_parse_fa( source, "#name", st_name );
    }

    if( st_name->size == 0 ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Name expected." );
    st_s_push_st( buf, st_name );
    tp_t tp_name = xoico_cgimel_s_entypeof( o, st_name->sc );
    if( name ) *name = tp_name;
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/** parses number: (all integer, hex and float encodings)*/
er_t xoico_cgimel_s_trans_number_literal( xoico_cgimel_s* o, bcore_source* source, st_s* buf )
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
er_t xoico_cgimel_s_trans_string_literal( xoico_cgimel_s* o, bcore_source* source, st_s* buf )
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
er_t xoico_cgimel_s_trans_char_literal( xoico_cgimel_s* o, bcore_source* source, st_s* buf )
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
er_t xoico_cgimel_s_trans_whitespace( xoico_cgimel_s* o, bcore_source* source, st_s* buf )
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
                st_s_push_char( buf, bcore_source_a_get_char( source ) );
            }
            break;

            case '/':
            {
                if( bcore_source_a_parse_bl_fa( source, "#?'//'" ) )
                {
                    st_s_push_sc( buf, "//" );
                    while( !bcore_source_a_eos( source ) )
                    {
                        char c = bcore_source_a_get_char( source );
                        st_s_push_char( buf, c );
                        if( c == '\n' ) break;
                    }
                }
                else if( bcore_source_a_parse_bl_fa( source, "#?'/*'" ) )
                {
                    st_s_push_sc( buf, "/*" );
                    while( !bcore_source_a_eos( source ) )
                    {
                        if( bcore_source_a_parse_bl_fa( source, "#?'*/'" ) )
                        {
                            st_s_push_sc( buf, "*/" );
                            break;
                        }
                        st_s_push_char( buf, bcore_source_a_get_char( source ) );
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

er_t xoico_cgimel_s_trans_preprocessor
(
    xoico_cgimel_s* o,
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
tp_t xoico_cgimel_s_trans_operator
(
    xoico_cgimel_s* o,
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

er_t xoico_cgimel_s_trans_typespec_expression
(
    xoico_cgimel_s* o,
    bcore_source* source,
    st_s* buf,
    const xoico_typespec_s*  in_typespec, // required
          xoico_typespec_s* out_typespec  // optional
)
{
    BLM_INIT();

    BLM_TRY( xoico_cgimel_s_trans_whitespace( o, source, buf ) );

    if( out_typespec ) out_typespec->type = 0;

    bl_t member_access = bcore_source_a_parse_bl_fa( source, "#?'.'" ) ||
                         bcore_source_a_parse_bl_fa( source, "#?'->'" );

    if( member_access )
    {
        st_s* buf_ = BLM_CREATE( st_s );
        tp_t tp_name = 0;
        BLM_TRY( xoico_cgimel_s_trans_name(       o, source, buf_, &tp_name ) );
        BLM_TRY( xoico_cgimel_s_trans_whitespace( o, source, buf_ ) );
        xoico_compiler_element_info_s* info = BLM_CREATE( xoico_compiler_element_info_s );
        if( xoico_compiler_s_get_type_element_info( o->compiler, in_typespec->type, tp_name, info ) )
        {
            if( info->signature ) // member function
            {
                if( !bcore_source_a_parse_bl_fa( source, "#?'('" ) ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "'(' expected" );
                st_s* arg_obj = BLM_CLONE( st_s, buf );

                const xoico_args_s* args = &info->signature->args;

                sc_t func_name = xoico_cgimel_s_nameof( o, info->type_info.typespec.type );
                ASSERT( func_name );

                st_s_copy_fa
                (
                    buf,
                    "#<sc_t>( #<sc_t>#<sc_t>",
                    func_name,
                    ( in_typespec->indirection == 1 ) ? "" : "&",
                    arg_obj->sc
                );

                BFOR_EACH( i, args )
                {
                    BLM_INIT();
                    const xoico_arg_s* arg = &args->data[ i ];
                    st_s* buf_ = BLM_CREATE( st_s );
                    XOICO_BLM_SOURCE_PARSE_FA( source, " " );
                    if( i > 0 ) XOICO_BLM_SOURCE_PARSE_FA( source, " ," );
                    xoico_typespec_s* typespec = BLM_CREATE( xoico_typespec_s );
                    BLM_TRY( xoico_cgimel_s_trans_expression( o, source, buf_, typespec ) );

                    st_s_push_sc( buf, ", " );

                    if( typespec->type )
                    {
                        if( typespec->type != arg->typespec.type )
                        {
                            XOICO_BLM_SOURCE_PARSE_ERR_FA
                            (
                                source,
                                "Argument #<sz_t>: Specified type '#<sc_t>' does not match expected type '#<sc_t>'",
                                i,
                                xoico_cgimel_s_nameof( o, typespec->type ),
                                xoico_cgimel_s_nameof( o, arg->typespec.type )
                            );
                        }

                        if( typespec->indirection != arg->typespec.indirection )
                        {
                            if( typespec->indirection + 1 == arg->typespec.indirection )
                            {
                                st_s_push_sc( buf, "&" );
                            }
                            else if( typespec->indirection == arg->typespec.indirection + 1 )
                            {
                                st_s_push_sc( buf, "*" );
                            }
                            else
                            {
                                XOICO_BLM_SOURCE_PARSE_ERR_FA
                                (
                                    source,
                                    "Argument #<sz_t>: Cannot resolve indirection.",
                                    i
                                );
                            }
                        }
                    }

                    st_s_push_st( buf, buf_ );
                    BLM_DOWN();
                }

                XOICO_BLM_SOURCE_PARSE_FA( source, ")" );
                if( buf->size > 0 && buf->data[ buf->size - 1 ] != ' ' ) st_s_push_sc( buf, " " );
                st_s_push_sc( buf, ")" );

                BLM_TRY( xoico_cgimel_s_trans_typespec_expression( o, source, buf, &info->signature->typespec_ret, out_typespec ) );
            }
            else // traced member element
            {
                if( in_typespec->indirection > 1 )
                {
                    XOICO_BLM_SOURCE_PARSE_ERR_FA
                    (
                        source,
                        "Dereferencing #<sc_t>: Indirection '#<sz_t>' is too large.",
                        xoico_cgimel_s_nameof( o, tp_name ),
                        in_typespec->indirection
                    );
                }
                st_s_push_fa( buf, "#<sc_t>#<sc_t>", ( in_typespec->indirection == 1 ) ? "->" : ".", buf_->sc );
                BLM_TRY( xoico_cgimel_s_trans_typespec_expression( o, source, buf, &info->type_info.typespec, out_typespec ) );
            }
        }
        else if( bcore_source_a_parse_bl_fa( source, "#?'('" ) ) // untraced member function
        {
            st_s* arg_obj = BLM_CLONE( st_s, buf );

            /// Untraced member functions of a group are always treated as 'aware'
            if( xoico_compiler_s_is_group( o->compiler, in_typespec->type ) )
            {
                st_s_copy_fa
                (
                    buf,
                    "#<sc_t>_a_#<sc_t>( #<sc_t>#<sc_t>",
                    xoico_cgimel_s_nameof( o, in_typespec->type ),
                    xoico_cgimel_s_nameof( o, tp_name ),
                    ( in_typespec->indirection == 1 ) ? "" : "&",
                    arg_obj->sc
                );
            }
            else
            {
                st_s_copy_fa
                (
                    buf,
                    "#<sc_t>_#<sc_t>( #<sc_t>#<sc_t>",
                    xoico_cgimel_s_nameof( o, in_typespec->type ),
                    xoico_cgimel_s_nameof( o, tp_name ),
                    ( in_typespec->indirection == 1 ) ? "" : "&",
                    arg_obj->sc
                );
            }

            bl_t first = true;
            BLM_TRY( xoico_cgimel_s_trans_whitespace( o, source, buf_ ) );
            while( !bcore_source_a_eos( source ) )
            {
                if( bcore_source_a_parse_bl_fa( source, "#=?')'" ) ) break;

                BLM_INIT();
                st_s* buf_ = BLM_CREATE( st_s );
                if( !first ) XOICO_BLM_SOURCE_PARSE_FA( source, "," );
                BLM_TRY( xoico_cgimel_s_trans_expression( o, source, buf_, NULL ) );
                BLM_TRY( xoico_cgimel_s_trans_whitespace( o, source, buf_ ) );
                st_s_push_fa( buf, ",#<sc_t>", ( buf_->sc[ 0 ] != ' ' &&  buf_->sc[ 0 ] != '\t' && buf_->sc[ 0 ] != '\n' ) ? " " : "" );
                st_s_push_fa( buf, "#<sc_t>", buf_->sc );
                first = false;
                BLM_DOWN();
            }

            XOICO_BLM_SOURCE_PARSE_FA( source, ")" );
            if( buf->size > 0 && buf->data[ buf->size - 1 ] != ' ' ) st_s_push_sc( buf, " " );
            st_s_push_sc( buf, ")" );

            BLM_TRY( xoico_cgimel_s_trans_expression( o, source, buf, NULL ) );
        }
        else // untraced member element
        {
            st_s_push_fa( buf, "#<sc_t>#<sc_t>", ( in_typespec->indirection == 1 ) ? "->" : ".", buf_->sc );
            BLM_TRY( xoico_cgimel_s_trans_expression( o, source, buf, NULL ) );
        }
    }
    else if( out_typespec )
    {
        xoico_typespec_s_copy( out_typespec, in_typespec );
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cgimel_s_trans_member( xoico_cgimel_s* o, bcore_source* source, st_s* buf )
{
    BLM_INIT();
    BLM_TRY( xoico_cgimel_s_trans_whitespace( o, source, buf ) );
    tp_t tp_name = 0;
    BLM_TRY( xoico_cgimel_s_trans_name( o, source, buf, &tp_name ) );
    BLM_TRY( xoico_cgimel_s_trans_whitespace( o, source, buf ) );
    if( bcore_source_a_parse_bl_fa( source, "#?'('") )
    {
        XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Untraced member function '#<sc_t>'\n", xoico_cgimel_s_nameof( o, tp_name ) );
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cgimel_s_trans_expression
(
    xoico_cgimel_s* o,
    bcore_source* source,
    st_s* buf,
    xoico_typespec_s* out_typespec // optional
)
{
    BLM_INIT();

    bl_t continuation = true;

    if( out_typespec ) out_typespec->type = 0;

    BLM_TRY( xoico_cgimel_s_trans_whitespace( o, source, buf ) );

    // identifier
    if( bcore_source_a_parse_bl_fa( source, "#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||[0]=='_'||[0]=='@'||([0]==':'&&([1]!=' '&&[1]!='\t'&&[1]!='\n'&&[1]!='/')))" ) )
    {
        BLM_INIT();
        tp_t tp_name = 0;
        st_s* buf_ = BLM_CREATE( st_s );
        BLM_TRY( xoico_cgimel_s_trans_name( o, source, buf_, &tp_name ) );
        const xoico_typespec_s* typespec = NULL;
        if( tp_name != TYPEOF_const && tp_name != TYPEOF_static && tp_name != TYPEOF_volatile )
        {
            typespec = xoico_cgimel_stack_s_get_typespec( &o->stack, tp_name );
        }

        if( typespec )
        {
            BLM_TRY( xoico_cgimel_s_trans_typespec_expression( o, source, buf_, typespec, out_typespec ) );
        }
        else
        {
            xoico_typespec_s* typespec = BLM_CREATE( xoico_typespec_s );

            while( tp_name == TYPEOF_const || tp_name == TYPEOF_static || tp_name == TYPEOF_volatile )
            {
                if( tp_name == TYPEOF_const ) typespec->is_const = true;
                BLM_TRY( xoico_cgimel_s_trans_whitespace( o, source, buf_ ) );
                BLM_TRY( xoico_cgimel_s_trans_name( o, source, buf_, &tp_name ) );
            }

            if( xoico_compiler_s_is_type( o->compiler, tp_name ) )
            {
                typespec->type = tp_name;
                BLM_TRY( xoico_cgimel_s_trans_whitespace( o, source, buf_ ) );

                while( bcore_source_a_parse_bl_fa( source, "#?'*'" ) )
                {
                    st_s_push_char( buf_, '*' );

                    typespec->indirection++;
                    BLM_TRY( xoico_cgimel_s_trans_whitespace( o, source, buf_ ) );
                }

                if( bcore_source_a_parse_bl_fa( source, "#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||[0]=='_')" ) )
                {
                    BLM_TRY( xoico_cgimel_s_trans_name( o, source, buf_, &tp_name ) );
                    xoico_cgimel_s_push_typedecl( o, typespec, tp_name );
                }
            }
            else
            {
                BLM_TRY( xoico_cgimel_s_trans_expression( o, source, buf_, NULL ) );
            }
        }
        st_s_push_st( buf, buf_ );
        BLM_DOWN();
    }

    // number literal
    else if( bcore_source_a_parse_bl_fa( source, "#?([0]>='0'&&[0]<='9')" ) )
    {
        BLM_TRY( xoico_cgimel_s_trans_number_literal( o, source, buf ) );
    }

    // string literal
    else if( bcore_source_a_parse_bl_fa( source, "#=?'\"'" ) )
    {
        BLM_TRY( xoico_cgimel_s_trans_string_literal( o, source, buf ) );
    }

    // character literal
    else if( bcore_source_a_parse_bl_fa( source, "#=?\"'\"" ) )
    {
        BLM_TRY( xoico_cgimel_s_trans_char_literal( o, source, buf ) );
    }

    // member access
    else if( bcore_source_a_parse_bl_fa( source, "#?'.'" ) )
    {
        st_s_push_sc( buf, "." );
        BLM_TRY( xoico_cgimel_s_trans_member( o, source, buf ) );
    }
    else if( bcore_source_a_parse_bl_fa( source, "#?'->'" ) )
    {
        st_s_push_sc( buf, "->" );
        BLM_TRY( xoico_cgimel_s_trans_member( o, source, buf ) );
    }

    // general operator
    else if( xoico_cgimel_s_trans_operator( o, source, buf ) )
    {
    }

    // ternary branch operator
    else if( bcore_source_a_parse_bl_fa( source, "#?'?'" ) )
    {
        st_s_push_sc( buf, "?" );
        BLM_TRY( xoico_cgimel_s_trans_expression( o, source, buf, NULL ) );
        XOICO_BLM_SOURCE_PARSE_FA( source, ": " );
        st_s_push_sc( buf, ": " );
        BLM_TRY( xoico_cgimel_s_trans_expression( o, source, buf, NULL ) );
    }

    // general bracket
    else if( bcore_source_a_parse_bl_fa( source, "#?'('" ) )
    {
        st_s_push_sc( buf, "(" );
        while( !bcore_source_a_eos( source ) )
        {
            BLM_TRY( xoico_cgimel_s_trans_expression( o, source, buf, out_typespec ) );
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
        }
        st_s_push_sc( buf, ")" );
    }

    // array subscript
    else if( bcore_source_a_parse_bl_fa( source, "#?'['" ) )
    {
        st_s_push_sc( buf, "[" );
        while( !bcore_source_a_eos( source ) )
        {
            BLM_TRY( xoico_cgimel_s_trans_expression( o, source, buf, out_typespec ) );
            if( bcore_source_a_parse_bl_fa( source, "#?']'" ) )
            {
                break;
            }
            else
            {
                XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Syntax error inside '[]'." );
            }
        }
        st_s_push_sc( buf, "]" );
    }

    // end of expression...
    else if( bcore_source_a_parse_bl_fa( source, "#?([0]==';'||[0]=='{'||[0]=='}'||[0]==')'||[0]==']'||[0]==','||([0]==':'&&([1]==' '||[1]=='\t'||[1]=='\n'||[1]=='/')))" ) )
    {
        continuation = false;
    }

    // unhandled
    else
    {
        XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Syntax error after '#<sc_t>", buf->sc );
    }

    BLM_RETURNV( er_t, continuation ? xoico_cgimel_s_trans_expression( o, source, buf, NULL ) : 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cgimel_s_trans_for_expression( xoico_cgimel_s* o, bcore_source* source, st_s* buf )
{
    BLM_INIT();
    xoico_cgimel_s_inc_level( o );
    XOICO_BLM_SOURCE_PARSE_FA( source, "for" );
    st_s_push_sc( buf, "for" );
    BLM_TRY( xoico_cgimel_s_trans_whitespace( o, source, buf ) );
    XOICO_BLM_SOURCE_PARSE_FA( source, "(" );
    st_s_push_sc( buf, "(" );
    BLM_TRY( xoico_cgimel_s_trans_expression( o, source, buf, NULL ) ); // def
    XOICO_BLM_SOURCE_PARSE_FA( source, ";" );
    st_s_push_sc( buf, ";" );
    BLM_TRY( xoico_cgimel_s_trans_expression( o, source, buf, NULL ) ); // cond
    XOICO_BLM_SOURCE_PARSE_FA( source, ";" );
    st_s_push_sc( buf, ";" );
    BLM_TRY( xoico_cgimel_s_trans_expression( o, source, buf, NULL ) ); // update
    BLM_TRY( xoico_cgimel_s_trans_whitespace( o, source, buf ) );
    XOICO_BLM_SOURCE_PARSE_FA( source, ")" );
    st_s_push_sc( buf, ")" );
    BLM_TRY( xoico_cgimel_s_trans_whitespace( o, source, buf ) );
    if( bcore_source_a_parse_bl_fa( source, "#=?'{'" ) )
    {
        BLM_TRY( xoico_cgimel_s_trans_block( o, source, buf ) )
    }
    else
    {
        BLM_TRY( xoico_cgimel_s_trans_statement( o, source, buf ) )
    }
    xoico_cgimel_s_dec_level( o );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cgimel_s_trans_if_expression( xoico_cgimel_s* o, bcore_source* source, st_s* buf )
{
    BLM_INIT();
    XOICO_BLM_SOURCE_PARSE_FA( source, "if" );
    st_s_push_sc( buf, "if" );
    BLM_TRY( xoico_cgimel_s_trans_whitespace( o, source, buf ) );
    XOICO_BLM_SOURCE_PARSE_FA( source, "(" );
    st_s_push_sc( buf, "(" );
    BLM_TRY( xoico_cgimel_s_trans_expression( o, source, buf, NULL ) ); // def
    XOICO_BLM_SOURCE_PARSE_FA( source, ")" );
    st_s_push_sc( buf, ")" );
    BLM_TRY( xoico_cgimel_s_trans_whitespace( o, source, buf ) );
    if( bcore_source_a_parse_bl_fa( source, "#=?'{'" ) )
    {
        BLM_TRY( xoico_cgimel_s_trans_block( o, source, buf ) )
    }
    else
    {
        BLM_TRY( xoico_cgimel_s_trans_statement( o, source, buf ) )
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cgimel_s_trans_while_expression( xoico_cgimel_s* o, bcore_source* source, st_s* buf )
{
    BLM_INIT();
    XOICO_BLM_SOURCE_PARSE_FA( source, "while" );
    st_s_push_sc( buf, "while" );
    BLM_TRY( xoico_cgimel_s_trans_whitespace( o, source, buf ) );
    XOICO_BLM_SOURCE_PARSE_FA( source, "(" );
    st_s_push_sc( buf, "(" );
    BLM_TRY( xoico_cgimel_s_trans_expression( o, source, buf, NULL ) ); // def
    XOICO_BLM_SOURCE_PARSE_FA( source, ")" );
    st_s_push_sc( buf, ")" );
    BLM_TRY( xoico_cgimel_s_trans_whitespace( o, source, buf ) );
    if( bcore_source_a_parse_bl_fa( source, "#=?'{'" ) )
    {
        BLM_TRY( xoico_cgimel_s_trans_block( o, source, buf ) )
    }
    else
    {
        BLM_TRY( xoico_cgimel_s_trans_statement( o, source, buf ) )
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cgimel_s_trans_else_expression( xoico_cgimel_s* o, bcore_source* source, st_s* buf )
{
    BLM_INIT();
    XOICO_BLM_SOURCE_PARSE_FA( source, "else" );
    st_s_push_sc( buf, "else" );
    BLM_TRY( xoico_cgimel_s_trans_whitespace( o, source, buf ) );
    if( bcore_source_a_parse_bl_fa( source, "#=?'{'" ) )
    {
        BLM_TRY( xoico_cgimel_s_trans_block( o, source, buf ) )
    }
    else
    {
        BLM_TRY( xoico_cgimel_s_trans_statement( o, source, buf ) )
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cgimel_s_trans_statement( xoico_cgimel_s* o, bcore_source* source, st_s* buf )
{
    BLM_INIT();

    BLM_TRY( xoico_cgimel_s_trans_whitespace( o, source, buf ) );
    if( bcore_source_a_parse_bl_fa( source, "#=?'{'" ) )
    {
        BLM_TRY( xoico_cgimel_s_trans_block( o, source, buf ) )
    }
    else if( bcore_source_a_parse_bl_fa( source, "#=?w'for'" ) )
    {
        BLM_TRY( xoico_cgimel_s_trans_for_expression( o, source, buf ) );
    }
    else if( bcore_source_a_parse_bl_fa( source, "#=?w'if'" ) )
    {
        BLM_TRY( xoico_cgimel_s_trans_if_expression( o, source, buf ) );
    }
    else if( bcore_source_a_parse_bl_fa( source, "#=?w'else'" ) )
    {
        BLM_TRY( xoico_cgimel_s_trans_else_expression( o, source, buf ) );
    }
    else if( bcore_source_a_parse_bl_fa( source, "#=?w'while'" ) )
    {
        BLM_TRY( xoico_cgimel_s_trans_while_expression( o, source, buf ) );
    }
    else if( bcore_source_a_parse_bl_fa( source, "#=?w'case'" ) )
    {
        BLM_TRY( xoico_cgimel_s_trans_expression( o, source, buf, NULL ) );
        BLM_TRY( xoico_cgimel_s_trans_whitespace( o, source, buf ) );
        XOICO_BLM_SOURCE_PARSE_FA( source, ": " );
        st_s_push_sc( buf, ": " );
        BLM_TRY( xoico_cgimel_s_trans_statement( o, source, buf ) );
    }
    else if( bcore_source_a_parse_bl_fa( source, "#=?'#'" ) )
    {
        BLM_TRY( xoico_cgimel_s_trans_preprocessor( o, source, buf ) );
    }
    else if( bcore_source_a_parse_bl_fa( source, "#?';'" ) )
    {
        st_s_push_char( buf, ';' );
    }
    else if( bcore_source_a_parse_bl_fa( source, "#?','" ) )
    {
        st_s_push_char( buf, ',' );
    }
    else if( bcore_source_a_parse_bl_fa( source, "#=?'}'" ) )
    {
        // nothing
    }
    else
    {
        BLM_INIT();
        st_s* buf_ = BLM_CREATE( st_s );

        BLM_TRY( xoico_cgimel_s_trans_expression( o, source, buf_, NULL ) );
        st_s_push_st( buf, buf_ );

        BLM_TRY( xoico_cgimel_s_trans_whitespace( o, source, buf ) );
        if( bcore_source_a_parse_bl_fa( source, "#?':'" ) )
        {
            st_s_push_char( buf, ':' );
        }

        //bcore_msg_fa( "\n#<sc_t>\n", buf_->sc );
        BLM_DOWN();
    }

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cgimel_s_trans_block_inside( xoico_cgimel_s* o, bcore_source* source, st_s* buf )
{
    BLM_INIT();
    while
    (
        !bcore_source_a_parse_bl_fa( source, "#=?'}'" ) &&
        !bcore_source_a_eos( source )
    )
    {
        BLM_TRY( xoico_cgimel_s_trans_statement( o, source, buf ) );
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cgimel_s_trans_block( xoico_cgimel_s* o, bcore_source* source, st_s* buf )
{
    BLM_INIT();
    xoico_cgimel_s_inc_level( o );
    BLM_TRY( xoico_cgimel_s_trans_whitespace( o, source, buf ) );

    if( bcore_source_a_parse_bl_fa( source, "#?'{{'" ) )
    {
        st_s_push_char( buf, '{' );
        BLM_TRY( xoico_cgimel_s_trans_block_inside_verbatim( o, source, buf ) );
        BLM_TRY( xoico_cgimel_s_trans_whitespace(   o, source, buf ) );
        XOICO_BLM_SOURCE_PARSE_FA( source, "}}" );
        st_s_push_char( buf, '}' );
    }
    else
    {
        XOICO_BLM_SOURCE_PARSE_FA( source, "{" );
        st_s_push_char( buf, '{' );
        BLM_TRY( xoico_cgimel_s_trans_block_inside( o, source, buf ) );
        BLM_TRY( xoico_cgimel_s_trans_whitespace(   o, source, buf ) );
        XOICO_BLM_SOURCE_PARSE_FA( source, "}" );
        st_s_push_char( buf, '}' );
    }

    xoico_cgimel_s_dec_level( o );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cgimel_s_trans_block_inside_verbatim( xoico_cgimel_s* o, bcore_source* source, st_s* buf )
{
    BLM_INIT();
    BLM_TRY( xoico_cgimel_s_trans_whitespace( o, source, buf ) );
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
                BLM_TRY( xoico_cgimel_s_trans_string_literal( o, source, buf ) );
            }
            break;

            case '\'':
            {
                BLM_TRY( xoico_cgimel_s_trans_char_literal( o, source, buf ) );
            }
            break;

            case '{':
            {
                st_s_push_char( buf, bcore_source_a_get_char( source ) );
                BLM_TRY( xoico_cgimel_s_trans_block_inside_verbatim( o, source, buf ) );
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
        BLM_TRY( xoico_cgimel_s_trans_whitespace( o, source, buf ) );
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cgimel_s_setup( xoico_cgimel_s* o, const xoico_body_s* body, const xoico_signature_s* signature )
{
    BLM_INIT();
    sc_t sc_obj_type = ( signature->arg_o ) ? ( body->stamp ? body->stamp->name.sc : body->group->name.sc ) : NULL;

    const xoico_args_s* args = &signature->args;

    tp_t obj_type  = ( signature->arg_o == 0 ) ? 0 : xoico_cgimel_s_entypeof( o, sc_obj_type );
    bl_t obj_const = ( signature->arg_o == TYPEOF_const );
    tp_t obj_name  = xoico_cgimel_s_entypeof( o, "o" );

    o->args     = ( xoico_args_s* )args;
    o->group    = body->code->group;
    o->stamp    = body->code->stamp;
    o->compiler = xoico_group_s_get_compiler( body->group );
    o->obj_type = obj_type;

    xoico_cgimel_stack_s_clear( &o->stack );
    o->level = 0;

    xoico_cgimel_stack_unit_s* unit = BLM_CREATE( xoico_cgimel_stack_unit_s );

    if( obj_type )
    {
        unit->typespec.is_const = obj_const;
        unit->typespec.type = obj_type;
        unit->typespec.indirection = 1;
        unit->name = obj_name;
        unit->level = 0;
        xoico_cgimel_stack_s_push_unit( &o->stack, unit );
        bcore_hmap_name_s_set_sc( &o->hmap_name, xoico_compiler_s_nameof( o->compiler, obj_type ) );
        bcore_hmap_name_s_set_sc( &o->hmap_name, xoico_compiler_s_nameof( o->compiler, obj_name ) );
    }

    BFOR_EACH( i, args )
    {
        const xoico_arg_s* arg = &args->data[ i ];
        if( arg->typespec.type && arg->name && arg->typespec.indirection == 1 )
        {
            xoico_typespec_s_copy( &unit->typespec, &arg->typespec );
            unit->name = arg->name;
            unit->level = 0;
            xoico_cgimel_stack_s_push_unit( &o->stack, unit );
            bcore_hmap_name_s_set_sc( &o->hmap_name, xoico_compiler_s_nameof( o->compiler, arg->typespec.type ) );
            bcore_hmap_name_s_set_sc( &o->hmap_name, xoico_compiler_s_nameof( o->compiler, arg->name ) );
        }
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cgimel_s_translate( const xoico_cgimel_s* o, const xoico_body_s* body, const xoico_signature_s* signature, bcore_sink* sink )
{
    BLM_INIT();

    if( o->fallback )
    {
        BLM_TRY( xoico_cengine_a_translate( o->fallback, body, signature, sink ) );
    }

    xoico_cgimel_s* gimel = BLM_CLONE( xoico_cgimel_s, o );
    xoico_cgimel_s_setup( gimel, body, signature );

    bcore_source* source = BLM_A_PUSH( bcore_source_point_s_clone_source( &body->code->source_point ) );

//    bcore_source* source = body->code->source_point.source;
//    sz_t source_old_index = bcore_source_a_get_index( source );
//    bcore_source_a_set_index( source, body->code->source_point.index );

    st_s* buf = BLM_CREATE( st_s );

    sz_t indent = 0;
    XOICO_BLM_SOURCE_PARSE_FA( source, " " );
    bl_t verbatim = false;
    if( bcore_source_a_parse_bl_fa( source, "#?'{{'" ) )
    {
        verbatim = true;
    }
    else
    {
        XOICO_BLM_SOURCE_PARSE_FA( source, "{" );
        verbatim = false;
    }

    while( bcore_source_a_parse_bl_fa( source, "#?([0]==' '||[0]=='\t')" ) ) { bcore_source_a_get_char( source ); };
    if( bcore_source_a_parse_bl_fa( source, "#?'\n'" ) )
    {
        while( bcore_source_a_parse_bl_fa( source, "#?' '" ) ) indent++;
    }

    if( verbatim )
    {
        BLM_TRY( xoico_cgimel_s_trans_block_inside_verbatim( gimel, source, buf ) );
    }
    else
    {
        BLM_TRY( xoico_cgimel_s_trans_block_inside( gimel, source, buf ) );
    }

    XOICO_BLM_SOURCE_PARSE_FA( source, " " );

    if( verbatim )
    {
        XOICO_BLM_SOURCE_PARSE_FA( source, "}}" );
    }
    else
    {
        XOICO_BLM_SOURCE_PARSE_FA( source, "}" );
    }

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

    if( !o->fallback )
    {
        bcore_sink_a_push_sc( sink, buf->sc );
    }

//    bcore_source_a_set_index( source, source_old_index );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------


/**********************************************************************************************************************/

