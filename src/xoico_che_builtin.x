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

func (:)( bl_t is_builtin_func( const, tp_t tp_identifier ) ) =
{
    switch( tp_identifier )
    {
        case TYPEOF_cast :
        case TYPEOF_scope:
        case TYPEOF_fork:
        case TYPEOF_try:
            return true;

        default:
            return false;
    }
};

//----------------------------------------------------------------------------------------------------------------------

func (:)
(
    er_t trans_builtin
    (
        mutable,
        tp_t tp_builtin,
        bcore_source* source,
        const :result* result_expr,
        const xoico_typespec_s* typespec_expr,
        :result* result_out,
        xoico_typespec_s* typespec_out
    )
) =
{ try {
    switch( tp_builtin )
    {
        case TYPEOF_cast : return o.trans_builtin_cast(  source, result_expr, typespec_expr, result_out, typespec_out );
        case TYPEOF_scope: return o.trans_builtin_scope( source, result_expr, typespec_expr, result_out, typespec_out );
        case TYPEOF_fork:  return o.trans_builtin_fork(  source, result_expr, typespec_expr, result_out, typespec_out );
        case TYPEOF_try:   return o.trans_builtin_try(   source, result_expr, typespec_expr, result_out, typespec_out );
        default: return source.parse_error_fa( "Internal error: Invalid builtin type '#<sc_t>'", ifnameof( tp_builtin ) );
    }
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:)
(
    er_t trans_builtin_cast
    (
        mutable,
        bcore_source* source,
        const :result* result_expr,
        const xoico_typespec_s* typespec_expr,
        :result* result_out,
        xoico_typespec_s* typespec_out
    )
) =
{ try {
    if( result_expr ) // member call
    {
        o.parse( source, " ( " );
        result_out.clear();
    }
    else // direct call
    {
        o.parse( source, "cast ( " );
        $* result = :result_create_arr().scope();
        $* typespec = xoico_typespec_s!.scope();
        o.trans_expression( source, result, typespec );
        o.parse( source, " , " );
        typespec_expr = typespec;
        result_expr = result;
    }

    result_out.push_sc( "((" );
    $* typespec_cast = xoico_typespec_s!.scope();

    o.take_typespec( source, typespec_cast, true );

    if( typespec_cast.type == TYPEOF_type_deduce )
    {
        if( !typespec_expr.type )
        {
            return source.parse_error_fa( "Cast-syntax: Deduce requested but expression is intractable." );
        }
        typespec_cast.type = typespec_expr.type;
    }

    o.push_typespec( typespec_cast, result_out );
    result_out.push_sc( ")(" );

    if
    (
        typespec_expr.type &&
        ( typespec_expr.type != TYPEOF_vc_t ) &&
        ( typespec_expr.type != TYPEOF_vd_t ) &&
        ( typespec_expr.type != TYPEOF_sc_t ) &&
        ( typespec_expr.type != TYPEOF_sd_t ) &&
        ( typespec_expr.type != TYPEOF_void )
    )
    {
        o.adapt_expression_indirection( source, typespec_expr, typespec_cast.indirection, result_expr, result_out );
    }
    else
    {
        result_out.push_result_c( result_expr );
    }

    o.parse( source, " )" );
    result_out.push_sc( "))" );

    if( typespec_out ) typespec_out.copy( typespec_cast );

    if( typespec_cast.indirection > typespec_expr.indirection )
    {
        typespec_out.flag_addressable = false;
    }

    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:)
(
    er_t trans_builtin_scope
    (
        mutable,
        bcore_source* source,
        const :result* result_expr,
        const xoico_typespec_s* typespec_expr,
        :result* result_out,
        xoico_typespec_s* typespec_out
    )
) =
{ try {
    bl_t has_arg = false;

    if( result_expr ) // member call
    {
        o.parse( source, " ( " );
        result_out.clear();
        has_arg = !source.parse_bl( "#=?')'" );
    }
    else // direct call
    {
        o.parse( source, "scope ( " );
        $* result = :result_create_arr().scope();
        $* typespec = xoico_typespec_s!.scope();
        o.trans_expression( source, result, typespec );
        typespec_expr = typespec;
        result_expr = result;
        has_arg = source.parse_bl( "#?','" );
    }

    const xoico_typespec_s* typespec_scope = typespec_expr;

    result_out.push_sc( "((" );

    sz_t level = 0;

    if( has_arg )
    {
        o.parse( source, " " );
        tp_t tp_identifier = o.get_identifier( source, true );

        if( o.is_var( tp_identifier ) )
        {
            level = o.stack_var.get_level( tp_identifier );
        }
        else if( tp_identifier == TYPEOF_scope_local )
        {
            level = o.level;
        }
        else if( tp_identifier == TYPEOF_scope_func )
        {
            level = 0;
        }
        else
        {
            return source.parse_error_fa( "scope: identifier '#<sc_t>' does not represent a variable.", o.nameof( tp_identifier ) );
        }
    }

    o.parse( source, " )" );

    if( typespec_scope.type        == 0 ) return source.parse_error_fa( "Operator 'scope': Expression not tractable." );
    if( typespec_scope.indirection != 1 ) return source.parse_error_fa( "Operator 'scope': Expression's indirection != 1." );
    if( typespec_scope.flag_keep )        return source.parse_error_fa( "Operator 'scope': Target is already scoped." );

    o.push_typespec( typespec_scope, result_out );

    if( o.is_group( typespec_scope.type ) )
    {
        result_out.push_fa( ")BLM_LEVEL_A_PUSH(#<sz_t>,", level );
        result_out.push_result_c( result_expr );
        result_out.push_sc( "))" );
    }
    else
    {
        result_out.push_fa( ")BLM_LEVEL_T_PUSH(#<sz_t>,#<sc_t>,", level, o.nameof( typespec_scope.type ) );
        result_out.push_result_c( result_expr );
        result_out.push_sc( "))" );
    }

    o.stack_block.adl.[ level ].use_blm = true;

    if( typespec_out )
    {
        typespec_out.copy( typespec_scope );
        typespec_out.flag_keep = true;
    }

    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:)
(
    er_t trans_builtin_fork
    (
        mutable,
        bcore_source* source,
        const :result* result_expr,
        const xoico_typespec_s* typespec_expr,
        :result* result_out,
        xoico_typespec_s* typespec_out
    )
) =
{ try {
    if( result_expr ) // member call
    {
        o.parse( source, " ( " );
        result_out.clear();
    }
    else // direct call
    {
        o.parse( source, "fork ( " );
        $* result = :result_create_arr().scope();
        $* typespec = xoico_typespec_s!.scope();
        o.trans_expression( source, result, typespec );
        typespec_expr = typespec;
        result_expr = result;
    }

    const xoico_typespec_s* typespec_fork = typespec_expr;

    result_out.push_sc( "((" );

    o.parse( source, " )" );

    if( typespec_fork.type        == 0 ) return source.parse_error_fa( "Operator 'fork': Expression not tractable." );
    if( typespec_fork.indirection != 1 ) return source.parse_error_fa( "Operator 'fork': Expression's indirection != 1." );

    o.push_typespec( typespec_fork, result_out );
    result_out.push_sc( ")bcore_fork(" );
    result_out.push_result_c( result_expr );
    result_out.push_sc( "))" );

    if( typespec_out ) typespec_out.copy( typespec_fork );

    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:)
(
    er_t trans_builtin_try
    (
        mutable,
        bcore_source* source,
        const :result* result_expr,
        const xoico_typespec_s* typespec_expr,
        :result* result_out,
        xoico_typespec_s* typespec_out
    )
) =
{ try {
    if( o.typespec_ret.type != TYPEOF_er_t || o.typespec_ret.indirection != 0 )
    {
        return source.parse_error_fa( "Operator 'try': This operator can only be used in functions returning 'er_t'." );
    }

    if( typespec_out ) typespec_out.reset();

    if( result_expr ) // member call
    {
        o.parse( source, " ( " );
        result_out.clear();
    }
    else // direct call
    {
        o.parse( source, "try " );

        if( source.parse_bl( "#=?'{'" ) ) // try block
        {
            o.try_block_level++;
            o.trans_block( source, result_out, false );
            o.try_block_level--;
            return 0;
        }

        o.parse( source, "( " );
        $* result = :result_create_arr().scope();
        $* typespec = xoico_typespec_s!.scope();
        o.trans_expression( source, result, typespec );
        typespec_expr = typespec;
        result_expr = result;
    }

    const xoico_typespec_s* typespec_try = typespec_expr;

    o.parse( source, " ) ;" );

    if( typespec_try.type != 0 )
    {
        if( typespec_try.type != TYPEOF_er_t ) return source.parse_error_fa( "Operator 'try': Expression must yield er_t." );
        if( typespec_try.indirection != 0    ) return source.parse_error_fa( "Operator 'try': Expression's indirection != 0." );
    }
    else
    {
        // return source.parse_error_fa( "Operator 'try': Expression not tractable." );
    }

    result_out.push_sc( "BLM_TRY(" );
    result_out.push_result_c( result_expr );
    result_out.push_sc( ")" );

    return 0;
} /* try */ };


//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
