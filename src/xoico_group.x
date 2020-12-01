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

func (:) xoico.get_hash =
{
    tp_t hash = o.pre_hash;
    hash = bcore_tp_fold_sc( hash, o.st_name.sc );
    hash = bcore_tp_fold_tp( hash, o.trait_name );
    hash = bcore_tp_fold_bl( hash, o.retrievable );
    hash = bcore_tp_fold_bl( hash, o.expandable );
    hash = bcore_tp_fold_bl( hash, o.short_spect_name );
    hash = bcore_tp_fold_tp( hash, o.beta );
    hash = bcore_tp_fold_tp( hash, o.funcs.get_hash() );
    foreach( $* e in o ) hash = bcore_tp_fold_tp( hash, e.get_hash() );
    foreach( $* e in o.includes_in_declaration ) hash = bcore_tp_fold_sc( hash, e.sc );
    foreach( $* e in o.includes_in_definition  ) hash = bcore_tp_fold_sc( hash, e.sc );
    foreach( $* e in o.explicit_embeddings     ) hash = bcore_tp_fold_sc( hash, e.sc );
    return hash;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) :.create_spect_name =
{
    if( o.short_spect_name )
    {
        return st_s_create_fa( "#<sc_t>_s", o.st_name.sc );
    }
    else
    {
        return st_s_create_fa( "#<sc_t>_spect_s", o.st_name.sc );
    }
};

//----------------------------------------------------------------------------------------------------------------------

func (:) :.parse_name_recursive = (try)
{
    if( source.parse_bl( "#?':'" ) )
    {
        if( o.parent )
        {
            o.parent.parse_name_recursive( name, source );
        }
        else
        {
            return source.parse_error_fa( "Too many colons: Namespace depth exceeded." );
        }
    }
    else
    {
        name.copy( o.st_name );
        st_s* s = st_s!.scope();
        source.parse_em_fa( " #name", s );
        if( s.size > 0 ) name.push_fa( "_#<sc_t>", s.sc );
    }
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) :.parse_name = (try)
{
    if( source.parse_bl( " #?':'" ) )
    {
        o.parse_name_recursive( name, source );
    }
    else
    {
        source.parse_em_fa( " #name", name );
    }

    if( name.size > 0 ) o.compiler.entypeof( name.sc );

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) (er_t push_default_feature_from_sc( mutable, sc_t sc )) = (try)
{
    $* compiler = o.compiler;
    $* feature = xoico_feature_s!.scope();
    feature.expandable = false;
    feature.group = o;
    feature.parse( bcore_source_string_s_create_from_sc( sc ).scope() );

    if( !compiler.is_item( feature.cast( xoico* ).get_global_name_tp() ) )
    {
        foreach( $* func in feature.funcs_return_to_group ) o.funcs.push_d( func.fork() );
        feature.funcs_return_to_group.clear();
        compiler.register_item( feature, o.source_point.source );
        o.hmap_feature.set( feature.signature.name, ( vd_t )feature );
        o.push_item_d( feature.fork() );
    }

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) (er_t parse_func( mutable, bcore_source* source )) = (try)
{
    $* func = xoico_func_s!.scope();
    func.group = o;
    func.stamp = NULL;
    func.parse( source );
    o.push_func_d( func.fork() );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) (er_t push_func_d( mutable, xoico_func_s* func )) = (try)
{
    sz_t idx = o.funcs.get_index_from_name( func.name );

    $* compiler = o.compiler;

    if( idx >= 0 )
    {
        xoico_func_s* prex_func = o.funcs.[ idx ];
        if( ( prex_func.signature_global_name == func.signature_global_name ) )
        {
            if( !func.body )
            {
                return func.source_point.parse_error_fa( "Function '#<sc_t>' has already been declared.", compiler.nameof( func.name ) );
            }
            else if( prex_func.body )
            {
                return func.source_point.parse_error_fa( "Function '#<sc_t>' has already a body.", compiler.nameof( func.name ) );
            }
            else
            {
                o.funcs.replace_fork( idx, func );
            }
        }
        else
        {
            return func.source_point.parse_error_fa( "Function '#<sc_t>' has already been declared.", compiler.nameof( func.name ) );
        }
    }
    else
    {
        o.funcs.push_d( func );
    }

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico.parse = (try)
{
    $* compiler = o.compiler;
    $* stack = xoico_group_source_stack_s!.scope();
    stack.push_d( source.fork() );

    sc_t group_termination = NULL;

    o.source_point.set( source );
    o.pre_hash = bcore_tp_init();
    o.tp_name = compiler.entypeof( o.st_name.sc );

    if( o.parent ) // this group is nested in another group, the group body is enclosed in { ... }
    {
        source.parse_em_fa( " {" );
        group_termination = " #?'}'";
    }
    else // this group is root
    {
        if( source.parse_bl( " #?'#ifdef XOILA_SECTION'" ) )
        {
            group_termination = " #?'#endif'";
        }
        else
        {
            group_termination = NULL;
        }
    }

    bl_t extend_stump = false;

    while
    (
        stack.size >= 2 ||
        ( group_termination ? !source.parse_bl( group_termination ) : !source.eos() )
    )
    {
        if( source.eos() )
        {
            if( stack.size >= 2 )
            {
                stack.[ stack.size - 1 ] =< NULL;
                source = stack.[ stack.size - 2 ];
                stack.set_size( stack.size - 1 );
            }
            else if( group_termination )
            {
                return source.parse_error_fa( "Unexpected end of file." );
            }
            else
            {
                break;
            }
        }
        else if( source.parse_bl( " #?w'stamp' " ) )
        {
            $* stamp = xoico_stamp_s!.scope( scope_local );
            stamp.group = o;
            stamp.parse( source );
            stamp.push_default_funcs();
            compiler.register_item( stamp, source );
            o.push_item_d( stamp.fork() );
        }

        /// stumps are inexpandable stamps. They can be used as template.
        else if( source.parse_bl( " #?w'stump' " ) )
        {
            $* stump = xoico_stamp_s!.scope( scope_local );
            stump.group = o;
            stump.parse( source );
            stump.make_funcs_overloadable();
            compiler.register_item( stump, source );
            compiler.life_a_push( stump.fork() );
            if( extend_stump )
            {
                o.extending_stamp = stump;
                extend_stump = false;
            }
        }
        else if( source.parse_bl( " #?w'signature' " ) )
        {
            $* signature = xoico_signature_s!.scope( scope_local );
            signature.group = o;
            signature.parse( source );
            source.parse_em_fa( " ; " );
            compiler.register_item( signature, source );
            o.push_item_d( signature.fork() );
        }
        else if( bcore_source_a_parse_bl( source, " #?w'body' " ) )
        {
            $* body = xoico_body_s!.scope( scope_local );
            body.set_group( o );
            body.parse( source );
            source.parse_em_fa( " ; " );
            compiler.register_item( body, source );
            o.push_item_d( body.fork() );
        }
        else if( source.parse_bl( " #?w'feature' " ) )
        {
            $* feature = xoico_feature_s!.scope( scope_local );
            feature.group = o;
            feature.parse( source );
            compiler.register_item( feature, source );
            o.hmap_feature.set( feature.signature.name, ( vd_t )feature );
            foreach( $* func in feature.funcs_return_to_group ) o.funcs.push_d( func.fork() );
            feature.funcs_return_to_group.clear();
            o.push_item_d( feature.fork() );
        }
        else if( source.parse_bl( " #?w'func' " ) )
        {
            bl_t is_group_function = true;
            if( source.parse_bl( " #=?'('" ) )
            {
                sz_t index = source.get_index();
                source.parse_em_fa( "(" );
                $* stamp_name = st_s!.scope( scope_local );
                o.parse_name( stamp_name, source );
                if( source.parse_bl( " #?')'" ) )
                {
                    stamp_name.push_sc( "_s" );
                    tp_t tp_stamp_name = btypeof( stamp_name.sc );
                    if( !compiler.is_stamp( tp_stamp_name ) )
                    {
                        return source.parse_error_fa( "Cannot associate type name '#<sc_t>' with a stamp.", stamp_name.sc );
                    }

                    xoico_stamp_s* stamp = compiler.get_stamp( tp_stamp_name );
                    stamp.parse_func( source );
                    o.pre_hash = bcore_tp_fold_tp( o.pre_hash, stamp.get_hash() );
                    is_group_function = false;
                }
                else
                {
                    source.set_index( index );
                    is_group_function = true;
                }
            }

            if( is_group_function )
            {
                o.parse_func( source );
            }
        }
        else if( source.parse_bl( " #?w'name' " ) )
        {
            $* name = xoico_name_s!.scope( scope_local );
            name.group = o;
            name.parse( source );
            o.push_item_d( name.fork() );
        }
        else if( source.parse_bl( " #?w'type' " ) )
        {
            $* name = xoico_name_s!.scope( scope_local );
            name.group = o;
            name.parse( source );
            compiler.register_external_type( name->name );
            o.push_item_d( name.fork() );
        }
        else if( bcore_source_a_parse_bl( source, " #?w'forward' " ) )
        {
            $* forward = xoico_forward_s!.scope( scope_local );
            forward.group = o;
            forward.parse( source );
            o.push_item_d( forward.fork() );
        }
        else if( bcore_source_a_parse_bl( source, " #?w'extending'" ) )
        {
            o.extending_stamp = NULL;
            if( source.parse_bl( " #=?';'" ) )
            {
                // just reset o->extending - nothing else
            }
            else if( source.parse_bl( " #=?w'stump'" ) )
            {
                extend_stump = true;
            }
            else
            {
                $* templ_name = st_s!.scope( scope_local );
                o.parse_name( templ_name, source );
                templ_name.push_fa( "_s" );
                const xoico* item = compiler.get_const_item( typeof( templ_name.sc ) );
                if( !item ) return source.parse_error_fa( "Template #<sc_t> not found.", templ_name.sc );
                if( item._ != TYPEOF_xoico_stamp_s ) return source.parse_error_fa( "Template #<sc_t> is no stamp.", templ_name.sc );
                o.extending_stamp = item.cast( xoico_stamp_s* );
                source.parse_em_fa( " ;" );
            }
        }
        else if( source.parse_bl( " #?w'group' " ) )
        {
            $* group = xoico_group_s!.scope( scope_local );
            o.xoico_source.push_d( group.fork() );
            group.parent = o;
            group.xoico_source = o.xoico_source;
            group.compiler = o.compiler;
            group.extending_stamp = o.extending_stamp;
            group.expandable  = o.expandable;

            o.parse_name( group.st_name, source );
            source.parse_em_fa( " =" );

            // flags
            if( source.parse_bl( " #?w'retrievable' " ) ) group.retrievable = true;

            st_s* st_trait_name = st_s!.scope();

            o.parse_name( st_trait_name, source );
            if( st_trait_name.size == 0 ) st_trait_name.copy( o->st_name );
            group.trait_name = compiler.entypeof( st_trait_name.sc );

            group.parse( source );
            source.parse_em_fa( " ; " );
            compiler.register_group( group );
            xoico_nested_group_s* nested_group = xoico_nested_group_s!.scope( scope_local );
            nested_group.group = group;
            o.push_item_d( nested_group.fork() );
        }
        else if( source.parse_bl( " #?w'set' " ) )
        {
            if(      source.parse_bl( " #?w'retrievable' "      ) ) o.retrievable = true;
            else if( source.parse_bl( " #?w'inexpandable' "     ) ) o.expandable = false;
            else if( source.parse_bl( " #?w'short_spect_name' " ) ) o.short_spect_name = true;
            else if( source.parse_bl( " #?w'beta' "             ) ) source.parse_em_fa( " = #<tp_t*>", o.beta.1 );
            source.parse_em_fa( " ;" );
        }
        else if( source.parse_bl( " #?w'embed' " ) )
        {
            st_s* folder = bcore_file_folder_path( bcore_source_a_get_file( source ) ).scope( scope_local );
            if( folder.size == 0 ) folder.push_char( '.' );
            st_s* embed_file = st_s!.scope( scope_local );
            source.parse_em_fa( " #string" , embed_file );
            source.parse_em_fa( " ;" );
            o.explicit_embeddings.push_st( embed_file );
            bcore_source* embed_source = NULL;
            try( xoico_embed_file_open( source, embed_file.sc, embed_source.1 ) );

            // check for cyclic inclusions
            foreach( $* e in stack )
            {
                sc_t path = embed_source.get_file();
                if( sc_t_equal( path, e.get_file() ) )
                {
                    return source.parse_error_fa( "Xoico: Cyclic inclusion." );
                }
            }

            source = embed_source;
            stack.push_d( source );
        }
        else if( source.parse_bl( " #?w'include' " ) )
        {
            bl_t deferred = source.parse_bl( " #?w'deferred' " );
            st_s* include_file = st_s!.scope( scope_local );
            source.parse_em_fa( " #string" , include_file );
            source.parse_em_fa( " ;" );
            if( deferred )
            {
                o.includes_in_definition.push_st( include_file );
            }
            else
            {
                o.includes_in_declaration.push_st( include_file );
            }
        }
        else
        {
            return source.parse_error_fa( "Xoico: syntax error." );
        }

        source.parse_em_fa( " " );// consume whitespaces
    }

    /// default features
    o.push_default_feature_from_sc( "@* clone( const );" );
    o.push_default_feature_from_sc( "void copy( mutable, const @* src );" );
    o.push_default_feature_from_sc( "void discard( mutable );" );

    if( stack.size > 1 )
    {
        return source.parse_error_fa( "Xoico: Unexpected end of group reached." );
    }

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico.finalize = (try)
{
    foreach( $* e in o ) e.finalize();
    foreach( $* func in o.funcs )
    {
        func.finalize();
        o.compiler.register_func( func );
        o.hmap_func.set( func.name, ( vd_t )func );
    }
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) (er_t expand_forward( const, sz_t indent, bcore_sink* sink )) = (try)
{
    if( !o.expandable ) return 0;
    sink.push_fa( " \\\n#rn{ }BCORE_FORWARD_OBJECT( #<sc_t> );", indent, o.st_name.sc );
    foreach( $* e in o ) e.expand_forward( indent, sink );
    foreach( $* func in o.funcs ) func.expand_forward( indent, sink );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) (er_t expand_spect_declaration( const, sz_t indent, bcore_sink* sink )) = (try)
{
    if( !o.expandable ) return 0;
    if( o.short_spect_name )
    {
        sink.push_fa( " \\\n#rn{ }BCORE_DECLARE_SPECT( #<sc_t> )", indent, o.st_name.sc );
    }
    else
    {
        sink.push_fa( " \\\n#rn{ }XOILA_DECLARE_SPECT( #<sc_t> )", indent, o.st_name.sc );
    }

    sink.push_fa( " \\\n#rn{ }{", indent );
    sink.push_fa( " \\\n#rn{ }    bcore_spect_header_s header;", indent );
    foreach( $* e in o ) e.expand_spect_declaration( indent + 4, sink );
    sink.push_fa( " \\\n#rn{ }};", indent );

    sink.push_fa
    (
        " \\\n#rn{ }"
        "BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( #<sc_t> )",
        indent,
        o->st_name.sc
    );

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) :.expand_declaration = (try)
{
    if( !o.expandable ) return 0;

    sink.push_fa( "\n" );
    sink.push_fa( "#rn{ }//#rn{-}\n", indent, sz_max( 0, 118 - indent ) );
    sink.push_fa("#rn{ }// group: #<sc_t>", indent, o->st_name.sc );
    if( o.explicit_embeddings.size > 0 )
    {
        sink.push_fa("; embeds:" );
        foreach( st_s* st in o.explicit_embeddings ) sink.push_fa(" #<st_s*>", st );
    }
    sink.push_fa("\n" );

    foreach( $* e in o->includes_in_declaration ) sink.push_fa( "##include \"#<sc_t>\"\n", e.sc );

    sink.push_fa( "\n" );
    sink.push_fa( "#rn{ }##define TYPEOF_#<sc_t> 0x#pl16'0'{#X<tp_t>}ull\n", indent, o.st_name.sc, btypeof( o.st_name.sc ) );

    st_s* st_spect_name = xoico_group_s_create_spect_name( o ).scope();
    sc_t  sc_spect_name = st_spect_name->sc;

    sink.push_fa( "#rn{ }##define TYPEOF_#<sc_t> 0x#pl16'0'{#X<tp_t>}ull\n", indent, sc_spect_name, btypeof( sc_spect_name ) );

    foreach( $* e in o ) e.expand_declaration( indent, sink );
    sink.push_fa( "#rn{ }##define BETH_EXPAND_GROUP_#<sc_t>", indent, o.st_name.sc );

    o.expand_forward( indent + 2, sink );

    foreach( $* e in o ) e.expand_indef_typedef( indent, sink );
    o.expand_spect_declaration( indent + 2, sink );

    foreach( $* e in o ) e.expand_indef_declaration( indent, sink );
    foreach( $* func in o->funcs ) func.expand_declaration( indent + 2, sink );

    sink.push_fa( "\n" );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) (er_t expand_spect_definition( const, sz_t indent, bcore_sink* sink )) = (try)
{
    $* compiler = o.compiler;
    if( !o.expandable ) return 0;
    sink.push_fa( "\n" );
    if( o.short_spect_name )
    {
        sink.push_fa( "#rn{ }BCORE_DEFINE_SPECT( #<sc_t>, #<sc_t> )\n", indent, compiler.nameof( o.trait_name ), o.st_name.sc );
    }
    else
    {
        sink.push_fa( "#rn{ }XOILA_DEFINE_SPECT( #<sc_t>, #<sc_t> )\n", indent, compiler.nameof( o.trait_name ), o.st_name.sc );
    }

    sink.push_fa( "#rn{ }\"{\"\n", indent );
    sink.push_fa( "#rn{ }    \"bcore_spect_header_s header;\"\n", indent );
    foreach( $* e in o ) e.expand_spect_definition( indent + 4, sink );
    sink.push_fa( "#rn{ }\"}\";\n", indent );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) :.expand_definition = (try)
{
    if( !o.expandable ) return 0;
    sink.push_fa( "\n" );
    sink.push_fa( "#rn{ }//#rn{-}\n", indent, sz_max( 0, 118 - indent ) );
    sink.push_fa( "#rn{ }// group: #<sc_t>", indent, o.st_name.sc );
    if( o.explicit_embeddings.size > 0 )
    {
        sink.push_fa("; embeds:" );
        foreach( st_s* st in o.explicit_embeddings ) sink.push_fa(" #<st_s*>", st );
    }
    sink.push_fa("\n" );

    foreach( $* e in o.includes_in_definition ) sink.push_fa( "##include \"#<sc_t>\"\n", e.sc );

    // non-features
    foreach( $* e in o ) if( e._ != TYPEOF_xoico_feature_s ) e.expand_definition( indent, sink );

    o.expand_spect_definition( indent, sink );

    // just-features
    foreach( $* e in o ) if( e._ == TYPEOF_xoico_feature_s ) e.expand_definition( indent, sink );

    foreach( $* func in o->funcs ) func.expand_definition( indent, sink );

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) :.expand_init1 = (try)
{
    if( !o.expandable ) return 0;
    sink.push_fa( "\n" );
    sink.push_fa( "#rn{ }// group: #<sc_t>\n", indent, o->st_name.sc );
    foreach( $* e in o ) e.expand_init1( indent, sink );

    if( o.short_spect_name )
    {
        sink.push_fa( "#rn{ }BCORE_REGISTER_SPECT( #<sc_t> );\n", indent, o.st_name.sc );
    }
    else
    {
        sink.push_fa( "#rn{ }XOILA_REGISTER_SPECT( #<sc_t> );\n", indent, o.st_name.sc );
    }

    if( o.retrievable )
    {
        foreach( $* e in o )
        {
            if( e._ == TYPEOF_xoico_stamp_s )
            {
                sink.push_fa( "#rn{ }bcore_inst_s_get_typed( TYPEOF_#<sc_t> );\n", indent, e.cast( xoico_stamp_s* ).st_name.sc );
            }
        }
    }
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

