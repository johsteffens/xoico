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
    hash = bcore_tp_fold_tp( hash, o.global_name );
    hash = bcore_tp_fold_tp( hash, o.signature_base_name );
    hash = bcore_tp_fold_tp( hash, o.signature_global_name );
    hash = bcore_tp_fold_bl( hash, o.expandable );
    hash = bcore_tp_fold_bl( hash, o.overloadable );
    hash = bcore_tp_fold_bl( hash, o.declare_in_expand_forward );
    if( o.body ) hash = bcore_tp_fold_tp( hash, xoico_body_s_get_hash( o.body ) );
    return hash;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) (er_t freeze_global_name( mutable )) = (try)
{
    if( o.global_name ) return 0;

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
};

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico.parse = (try)
{
    $* compiler = o.group.compiler;

    // global name signature
    tp_t tp_signature_base_name;
    o.source_point.set( source );

    st_s* st_name = st_s!.scope();

    if( source.parse_bl( " #?'('" ) )
    {
        xoico_signature_s* signature = xoico_signature_s!;
        compiler.life_a_push( signature );
        signature.group = o.group;
        signature.stamp = o.stamp;
        signature.parse( host, source );
        source.parse_em_fa( " ) " );

        compiler.register_item( signature, source );

        o.pre_hash = bcore_tp_fold_tp( o.pre_hash, signature.get_hash() );
        tp_signature_base_name = o.stamp ? o.stamp.tp_name : o.group.tp_name;
        st_name.copy_sc( compiler.nameof( signature.name ) );
    }
    else
    {
        if( source.parse_bl( " #?'^'" ) )
        {
            if( !o->stamp ) return source.parse_error_fa( "'^' can only be used inside a stamp." );
            tp_signature_base_name = o.stamp.trait_name;
        }
        else
        {
            $* st = st_s!.scope();
            o.group.parse_name( source, st );
            tp_signature_base_name = compiler.entypeof( st.sc );
        }

        source.parse_em_fa( " ." );
        source.parse_em_fa( " #name", st_name );
    }


    if( st_name->size == 0 ) return source.parse_error_fa( "Function name expected." );
    o.name = compiler.entypeof( st_name.sc );

    o.signature_base_name = tp_signature_base_name;
    o.signature_global_name = compiler.entypeof( st_s_create_fa( "#<sc_t>_#<sc_t>", compiler.nameof( tp_signature_base_name ), st_name.sc ).scope().sc );

    if( source.parse_bl( " #=?'='" ) )
    {
        o.body = xoico_body_s!;
        o.body.set_group( o.group );
        o.body.set_stamp( o.stamp );
        o.body.parse( host, source );
    }

    source.parse_em_fa( " ; " );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) (er_t push_flect_decl_to_sink( const, bcore_sink* sink )) =
{
    $* compiler = o.group.compiler;
    sink.push_sc( "func " );
    if( o.stamp && o.signature_base_name == o.stamp.trait_name )
    {
        sink.push_fa( "^:#<sc_t>", compiler.nameof( o.name ) );
    }
    else
    {
        sink.push_fa( "#<sc_t>:#<sc_t>", compiler.nameof( o.signature_base_name ), compiler.nameof( o.name ) );
    }
    sink.push_sc( ";" );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico.finalize = (try)
{
    xoico_compiler_s* compiler = o.group.compiler;
    o.freeze_global_name();

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
        o.body.finalize( host );
    }

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico.expand_forward = (try)
{
    if( !o->expandable ) return 0;
    if( !o->declare_in_expand_forward ) return 0;

    $* compiler = o.group.compiler;
    sink.push_fa( " \\\n#rn{ }", indent );
    bl_t go_inline = o.body && o.body.go_inline;
    const $* signature = o.signature;
    ASSERT( signature );
    if( go_inline )
    {
        sink.push_fa( "static inline " );
        signature.expand_declaration( host, o.stamp, compiler.nameof( o.global_name ), indent, sink );
    }
    else
    {
        signature.expand_declaration( host, o.stamp, compiler.nameof( o.global_name ), indent, sink );
    }
    sink.push_fa( ";" );

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico.expand_declaration = (try)
{
    if( !o.expandable ) return 0;

    bl_t go_inline = o.body && o.body.go_inline;
    const $* signature = o.signature;
    ASSERT( signature );
    $* compiler = o.group.compiler;

    if( go_inline )
    {
        sink.push_fa( " \\\n#rn{ }", indent );
        sink.push_fa( "static inline " );
        signature.expand_declaration( host, o->stamp, xoico_compiler_s_nameof( compiler, o->global_name ), indent, sink );
        o.body.expand( host, signature, indent, sink );
    }
    else if( !o->declare_in_expand_forward )
    {
        sink.push_fa( " \\\n#rn{ }", indent );
        signature.expand_declaration( host, o->stamp, xoico_compiler_s_nameof( compiler, o->global_name ), indent, sink );
        sink.push_fa( ";" );
    }

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico.expand_definition = (try)
{
    if( !o.expandable ) return 0;
    $* compiler = o.group.compiler;

    const $* signature = o.signature;
    ASSERT( signature );
    if( o.body && !o.body.go_inline )
    {
        sink.push_fa( "\n" );
        sink.push_fa( "#rn{ }", indent );
        signature.expand_declaration( host, o.stamp, compiler.nameof( o.global_name ), indent, sink );
        sink.push_fa( "\n" );
        o.body.expand( host, signature, indent, sink );
        sink.push_fa( "\n" );
    }

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

