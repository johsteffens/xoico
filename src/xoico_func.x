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

func (:) :.get_hash =
{
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o._ );
    hash = bcore_tp_fold_tp( hash, o.pre_hash );
    hash = bcore_tp_fold_tp( hash, o.name );
    hash = bcore_tp_fold_sc( hash, o.flect_decl.sc );
    hash = bcore_tp_fold_tp( hash, o.signature_global_name );
    hash = bcore_tp_fold_bl( hash, o.overloadable );
    hash = bcore_tp_fold_bl( hash, o.expandable );
    if( o.body ) hash = bcore_tp_fold_tp( hash, xoico_body_s_get_hash( o.body ) );
    return hash;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) (er_t set_global_name( mutable )) =
{ try {
    st_s* st_global_name = st_s!.scope();

    xoico_compiler_s* compiler = o.group.compiler;
    sc_t sc_name = compiler.nameof( o.name );

    if( o.stamp )
    {
        st_global_name.push_fa( "#<sc_t>_#<sc_t>", o.stamp.st_name.sc, sc_name );
    }
    else
    {
        st_global_name.push_fa( "#<sc_t>_#<sc_t>", o.group.st_name.sc, sc_name );
    }

    o.global_name = compiler.entypeof( st_global_name.sc );
    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:) :.parse =
{ try {
    xoico_compiler_s* compiler = o.group.compiler;

    // global name signature
    st_s* st_type = st_s!.scope();
    o.source_point.set( source );

    o.flect_decl.push_sc( "func " );

    st_s* st_name = st_s!.scope();

    if( source.parse_bl_fa( " #?'('" ) )
    {
        xoico_signature_s* signature = xoico_signature_s!;
        compiler.life_a_push( signature );

        signature.group = o.group;
        signature.stamp = o.stamp;

        signature.parse( source );

        if( signature.arg_o )
        {
            if( !o.stamp ) return source.parse_error_fa( "Signature specifies a member-function. A plain function was expected at this point." );
        }

        try( source.parse_em_fa( " ) " ) );

        compiler.register_item( signature, source );

        o.pre_hash = bcore_tp_fold_tp( o.pre_hash, signature.get_hash() );

        if( o.stamp )
        {
            st_type.copy( &o.stamp.st_name );
        }
        else
        {
            st_type.copy( &o.group.st_name );
        }

        st_name.copy_sc( compiler.nameof( signature.name ) );
        o.flect_decl.push_fa( "#<sc_t>:#<sc_t>", st_type.sc, st_name.sc );
    }
    else
    {
        if( source.parse_bl_fa( " #?'^'" ) )
        {
            if( !o->stamp ) return source.parse_error_fa( "'^' is only inside a stamp allowed." );
            st_type.copy( &o.stamp.st_trait_name );
            o.flect_decl.push_sc( "^" );
        }
        else
        {
            o.group.parse_name( st_type, source );

            if( o.stamp && st_type.equal_st( &o.stamp.st_trait_name ) )
            {
                o.flect_decl.push_fa( "^" );
            }
            else
            {
                o.flect_decl.push_fa( "#<sc_t>", st_type.sc );
            }
        }

        try( source.parse_em_fa( " ." ) );
        o.flect_decl.push_sc( ":" );

        try( source.parse_em_fa( " #name", st_name ) );
    }

    if( st_name->size == 0 ) return source.parse_error_fa( "Function name expected." );
    o.name = compiler.entypeof( st_name.sc );

    o.flect_decl.push_sc( st_name.sc );

    st_type.push_fa( "_#<sc_t>", st_name.sc );

    o.signature_global_name = compiler.entypeof( st_type.sc );
    o.set_global_name();

    if( source.parse_bl_fa( " #=?'='" ) )
    {
        o.body = xoico_body_s!;
        o.body.set_group( o.group );
        o.body.set_stamp( o.stamp );
        o.body.parse( source );
    }

    try( source.parse_em_fa( " ; " ) );
    o.flect_decl.push_sc( ";" );
    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:) :.registerable =
{
    if( !o.expandable ) return false;
    if( o.group.compiler.is_item( o.signature_global_name ) )
    {
        const xoico* item = o.group.compiler.get_const_item( o.signature_global_name );
        if( item._ == TYPEOF_xoico_signature_s )
        {
            if( !o.group.compiler.register_signatures ) return false;
            const xoico_signature_s* signature = item.cast( xoico_signature_s* );
            return ( signature.arg_o != 0 || o.group.compiler.register_non_feature_functions );
        }
        else
        {
            return true;
        }
    }
    else
    {
        return true;
    }
};

//----------------------------------------------------------------------------------------------------------------------

func (:) :.finalize =
{ try {
    xoico_compiler_s* compiler = o.group.compiler;
    o.set_global_name();

    xoico_signature_s* signature = compiler.get_signature( o.signature_global_name ).cast( $* );
    if( !signature )
    {
        return o.source_point.parse_error_fa
        (
            "Function #<sc_t>: Could not find signature #<sc_t>",
            compiler.nameof( o.name ),
            compiler.nameof( o.signature_global_name )
        );
    }

    o.signature = signature;

    if( o.body )
    {
        o.body.set_group( o.group );
        o.body.set_stamp( o.stamp );
        o.body.finalize();
    }

    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico.expand_forward =
{ try {
    if( !o->expandable ) return 0;

    $* compiler = o.group.compiler;
    sink.push_fa( " \\\n#rn{ }", indent );
    bl_t go_inline = o.body && o.body.go_inline;
    const $* signature = o.signature;
    ASSERT( signature );
    if( go_inline )
    {
        sink.push_fa( "static inline " );
        signature.expand_declaration( o.stamp, compiler.nameof( o.global_name ), indent, sink );
    }
    else
    {
        signature.expand_declaration( o.stamp, compiler.nameof( o.global_name ), indent, sink );
    }
    sink.push_fa( ";" );

    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico.expand_declaration =
{ try {
    if( !o.expandable ) return 0;

    bl_t go_inline = o.body && o.body.go_inline;
    const $* signature = o.signature;
    ASSERT( signature );

    if( go_inline )
    {
        $* compiler = o.group.compiler;
        sink.push_fa( " \\\n#rn{ }", indent );
        sink.push_fa( "static inline " );
        signature.expand_declaration( o->stamp, xoico_compiler_s_nameof( compiler, o->global_name ), indent, sink );
        o.body.expand( signature, indent, sink );
    }
    // non-inline functions are already declared in expand_forward

    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico.expand_definition =
{ try {
    if( !o.expandable ) return 0;
    $* compiler = o.group.compiler;

    const $* signature = o.signature;
    ASSERT( signature );
    if( o.body && !o.body.go_inline )
    {
        sink.push_fa( "\n" );
        sink.push_fa( "#rn{ }", indent );
        signature.expand_declaration( o.stamp, compiler.nameof( o.global_name ), indent, sink );
        sink.push_fa( "\n" );
        o.body.expand( signature, indent, sink );
        sink.push_fa( "\n" );
    }

    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

