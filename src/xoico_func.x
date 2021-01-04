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

func (:s) :.get_hash =
{
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o._ );
    hash = bcore_tp_fold_tp( hash, o.pre_hash );
    hash = bcore_tp_fold_tp( hash, o.name );
    hash = bcore_tp_fold_tp( hash, o.global_name );
    hash = bcore_tp_fold_bl( hash, o.expandable );
    hash = bcore_tp_fold_bl( hash, o.overloadable );
    hash = bcore_tp_fold_bl( hash, o.declare_in_expand_forward );
    hash = bcore_tp_fold_tp( hash, o.signature ? o.signature.get_hash() : o.signature_global_name );
    if( o.body ) hash = bcore_tp_fold_tp( hash, xoico_body_s_get_hash( o.body ) );
    return hash;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) (er_t freeze_global_name( m @* o, const xoico_host* host )) = (try)
{
    if( o.global_name ) return 0;
    $* compiler = host.compiler();
    o.global_name = compiler.entypeof( st_s_create_fa( "#<sc_t>_#<sc_t>", compiler.nameof( host.obj_type() ), compiler.nameof( o.name ) ).scope().sc );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) xoico.parse = (try)
{
    $* compiler = host.compiler();

    // global name signature
    o.source_point.set( source );

    if( source.parse_bl( " #?'('" ) )
    {
        xoico_signature_s* signature = xoico_signature_s!;
        signature.parse( host, source );
        source.parse_em_fa( " ) " );

        o.pre_hash = bcore_tp_fold_tp( o.pre_hash, signature.get_hash() );
        o.name = signature.name;
        o.signature_global_name = signature.global_name;

        signature.relent( host, host.obj_type() );
        if( host.defines_transient_map() ) signature.convert_transient_types( host, host.transient_map() );

        o.signature =< signature;
    }
    else
    {
        tp_t tp_signature_base_name;
        st_s* st_name = st_s!^^;

        if( source.parse_bl( " #?'^'" ) )
        {
            if( host._ == TYPEOF_xoico_stamp_s )
            {
                tp_signature_base_name = host.cast( const xoico_stamp_s* ).trait_name;
            }
            else
            {
                return source.parse_error_fa( "'^' can only be used inside a stamp." );
            }
        }
        else
        {
            host.parse_name_tp( source, tp_signature_base_name.1 );
        }

        source.parse_em_fa( " ." );
        source.parse_em_fa( " #name", st_name );

        if( st_name->size == 0 ) return source.parse_error_fa( "Function name expected." );
        o.name = compiler.entypeof( st_name.sc );

        o.signature_global_name = compiler.entypeof( st_s_create_fa( "#<sc_t>_#<sc_t>", compiler.nameof( tp_signature_base_name ), st_name.sc ).scope().sc );

    }


    if( source.parse_bl( " #=?'='" ) ) o.body!.parse( host, source );

    source.parse_em_fa( " ; " );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) (er_t push_flect_decl_to_sink( c @* o, c xoico_host* host, m bcore_sink* sink )) =
{
    $* compiler = host.compiler();
    sink.push_sc( "func " );
    if( host._ == TYPEOF_xoico_stamp_s && o.signature.base_name == host.cast( const xoico_stamp_s* ).trait_name )
    {
        sink.push_fa( "^:#<sc_t>", compiler.nameof( o.name ) );
    }
    else
    {
        sink.push_fa( "#<sc_t>:#<sc_t>", compiler.nameof( o.signature.base_name ), compiler.nameof( o.name ) );
    }
    sink.push_sc( ";" );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) xoico.finalize = (try)
{
    $* compiler = host.compiler();
    o.freeze_global_name( host );
    o.obj_type = host.obj_type();

    if( !o.signature )
    {
        const xoico_signature_s* signature = compiler.get_signature( o.signature_global_name );
        if( !signature )
        {
            return o.source_point.parse_error_fa
            (
                "Function #<sc_t>: Could not find signature #<sc_t>",
                compiler.nameof( o.name ),
                compiler.nameof( o.signature_global_name )
            );
        }

        o.signature = signature.clone();
        o.signature.relent( host, host.obj_type() );
        if( host.defines_transient_map() ) o.signature.convert_transient_types( host, host.transient_map() );
    }
    else
    {
        if( !compiler.is_item( o.signature.get_global_name_tp() ) ) compiler.register_item( o.signature );
    }

    if( o.body ) o.body.finalize( host );

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) xoico.expand_forward = (try)
{
    if( !o->expandable ) return 0;
    if( !o->declare_in_expand_forward ) return 0;

    $* compiler = host.compiler();
    sink.push_fa( " \\\n#rn{ }", indent );
    bl_t go_inline = o.body && o.body.go_inline;
    const $* signature = o.signature;
    ASSERT( signature );
    if( go_inline )
    {
        sink.push_fa( "static inline " );
        signature.expand_declaration( host, compiler.nameof( o.global_name ), indent, sink );
    }
    else
    {
        signature.expand_declaration( host, compiler.nameof( o.global_name ), indent, sink );
    }
    sink.push_fa( ";" );

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) xoico.expand_declaration = (try)
{
    if( !o.expandable ) return 0;

    bl_t go_inline = o.body && o.body.go_inline;
    const $* signature = o.signature;
    ASSERT( signature );
    $* compiler = host.compiler();

    if( go_inline )
    {
        sink.push_fa( " \\\n#rn{ }", indent );
        sink.push_fa( "static inline " );
        signature.expand_declaration( host, xoico_compiler_s_nameof( compiler, o->global_name ), indent, sink );
        o.body.expand( host, signature, indent, sink );
    }
    else if( !o->declare_in_expand_forward )
    {
        sink.push_fa( " \\\n#rn{ }", indent );
        signature.expand_declaration( host, xoico_compiler_s_nameof( compiler, o->global_name ), indent, sink );
        sink.push_fa( ";" );
    }

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) xoico.expand_definition = (try)
{
    if( !o.expandable ) return 0;
    $* compiler = host.compiler();

    const $* signature = o.signature;
    ASSERT( signature );
    if( o.body && !o.body.go_inline )
    {
        sink.push_fa( "\n" );
        sink.push_fa( "#rn{ }", indent );
        signature.expand_declaration( host, compiler.nameof( o.global_name ), indent, sink );
        sink.push_fa( "\n" );
        o.body.expand( host, signature, indent, sink );
        sink.push_fa( "\n" );
    }

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

