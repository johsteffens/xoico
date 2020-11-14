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
    hash = bcore_tp_fold_sc( hash, o.trait_name.sc );
    hash = bcore_tp_fold_bl( hash, o.retrievable );
    hash = bcore_tp_fold_bl( hash, o.expandable );
    hash = bcore_tp_fold_bl( hash, o.short_spect_name );
    hash = bcore_tp_fold_tp( hash, o.beta );
    hash = bcore_tp_fold_tp( hash, o.funcs.get_hash() );
    foreach( $* e in o ) hash = bcore_tp_fold_tp( hash, e.get_hash() );
    foreach( $* e in o.includes_in_declaration ) hash = bcore_tp_fold_sc( hash, e.sc );
    foreach( $* e in o.includes_in_definition  ) hash = bcore_tp_fold_sc( hash, e.sc );
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

func (:) :.parse_name_recursive =
{ try {
    if( source.parse_bl_fa( "#?':'" ) )
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
        try( source.parse_em_fa( " #name", s ) );
        if( s.size > 0 ) name.push_fa( "_#<sc_t>", s.sc );
    }
    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:) :.parse_name =
{ try {
    if( source.parse_bl_fa( " #?':'" ) )
    {
        o.parse_name_recursive( name, source );
    }
    else
    {
        try( source.parse_em_fa( " #name", name ) );
    }

    if( name.size > 0 ) o.compiler.entypeof( name.sc );

    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:) (er_t push_default_feature_from_sc( mutable, sc_t sc )) =
{ try {
    $* compiler = o.compiler;
    $* feature = xoico_feature_s!.scope();
    feature.expandable = false;
    feature.group = o;
    feature.parse( cast( bcore_source_string_s_create_from_sc( sc ), bcore_source* ).scope() );

    if( !compiler.is_item( feature.cast( xoico* ).get_global_name_tp() ) )
    {
        compiler.register_item( feature.cast( xoico* ), o.source_point.source );
        o.hmap_feature.set( feature.signature.name, ( vd_t )feature );
        o.push_item_d( feature.fork().cast( xoico* ) );
    }

    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:) (er_t parse_func( mutable, bcore_source* source )) =
{ try {
    $* compiler = o.compiler;
    $* func = xoico_func_s!.scope();
    func.group = o;
    func.stamp = NULL;

    func.parse( source );
    sz_t idx = o.funcs.get_index_from_name( func.name );

    if( idx >= 0 )
    {
        xoico_func_s* prex_func = o.funcs.[ idx ];
        if( ( prex_func.signature_global_name == func.signature_global_name ) )
        {
            if( !func.body )
            {
                return source.parse_error_fa( "Function '#<sc_t>' has already been declared.", compiler.nameof( func.name ) );
            }
            else if( prex_func.body )
            {
                return source.parse_error_fa( "Function '#<sc_t>' has already a body.", compiler.nameof( func.name ) );
            }
            else
            {
                o.funcs.replace_fork( idx, func );
            }
        }
        else
        {
            return source.parse_error_fa( "Function '#<sc_t>' has already been declared.", compiler.nameof( func.name ) );
        }
    }
    else
    {
        o.funcs.push_d( func.fork() );
    }

    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico.parse =
{ try {
    $* stack = xoico_group_source_stack_s!.scope();
    stack.push_d( source.fork() );

    sc_t group_termination = NULL;

    o.source_point.set( source );
    o.pre_hash = bcore_tp_init();

    if( o.parent ) // this group is nested in another group, the group body is enclosed in { ... }
    {
        try( source.parse_em_fa( " {" ) );
        group_termination = " #?'}'";
    }
    else // this group is root
    {
        if( source.parse_bl_fa( " #?'#ifdef XOILA_SECTION'" ) )
        {
            group_termination = " #?'#endif'";
        }
        else
        {
            group_termination = NULL;
        }
    }

    bl_t extend_stump = false;

    $* compiler = o.compiler;

    while
    (
        stack.size >= 2 ||
        ( group_termination ? !source.parse_bl_fa( group_termination ) : !source.eos() )
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
        else if( source.parse_bl_fa( " #?w'stamp' " ) )
        {
            $* stamp = xoico_stamp_s!.scope( scope_local );
            stamp.group = o;
            stamp.parse( source );
            stamp.push_default_funcs();
            compiler.register_item( stamp.cast( xoico* ), source );
            o.push_item_d( stamp.fork().cast( xoico* ) );
        }

        /// stumps are inexpandable stamps. They can be used as template.
        else if( source.parse_bl_fa( " #?w'stump' " ) )
        {
            $* stump = xoico_stamp_s!.scope( scope_local );
            stump.group = o;
            stump.parse( source );
            stump.make_funcs_overloadable();
            compiler.register_item( stump.cast( xoico* ), source );
            compiler.life_a_push( stump.fork().cast( bcore_inst* ) );
            if( extend_stump )
            {
                o.extending_stamp = stump;
                extend_stump = false;
            }
        }
        else if( source.parse_bl_fa( " #?w'signature' " ) )
        {
            $* signature = xoico_signature_s!.scope( scope_local );
            signature.group = o;
            signature.parse( source );
            try( source.parse_em_fa( " ; " ) );
            compiler.register_item( signature.cast( xoico* ), source );
            o.push_item_d( signature.fork().cast( xoico* ) );
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?w'body' " ) )
        {
            $* body = xoico_body_s!.scope( scope_local );
            body.set_group( o );
            body.parse( source );
            try( source.parse_em_fa( " ; " ) );
            compiler.register_item( body.cast( xoico* ), source );
            o.push_item_d( body.fork().cast( xoico* ) );
        }
        else if( source.parse_bl_fa( " #?w'feature' " ) )
        {
            $* feature = xoico_feature_s!.scope( scope_local );
            feature.group = o;
            feature.parse( source );
            compiler.register_item( feature.cast( xoico* ), source );
            o.hmap_feature.set( feature.signature.name, ( vd_t )feature );
            o.push_item_d( feature.fork().cast( xoico* ) );
        }
        else if( source.parse_bl_fa( " #?w'func' " ) )
        {
            bl_t is_plain_function = true;
            if( source.parse_bl_fa( " #=?'('" ) )
            {
                sz_t index = source.get_index();
                source.parse_fa( "(" );
                $* stamp_name = st_s!.scope( scope_local );
                o.parse_name( stamp_name, source );
                if( source.parse_bl_fa( " #?')'" ) )
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
                    is_plain_function = false;
                }
                else
                {
                    source.set_index( index );
                    is_plain_function = true;
                }
            }

            if( is_plain_function )
            {
                o.parse_func( source );
            }
        }
        else if( source.parse_bl_fa( " #?w'name' " ) )
        {
            $* name = xoico_name_s!.scope( scope_local );
            name.group = o;
            name.parse( source );
            o.push_item_d( name.fork().cast( xoico* ) );
        }
        else if( source.parse_bl_fa( " #?w'type' " ) )
        {
            $* name = xoico_name_s!.scope( scope_local );
            name.group = o;
            name.parse( source );
            compiler.register_external_type( name->name );
            o.push_item_d( name.fork().cast( xoico* ) );
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?w'forward' " ) )
        {
            $* forward = xoico_forward_s!.scope( scope_local );
            forward.group = o;
            forward.parse( source );
            o.push_item_d( forward.fork().cast( xoico* ) );
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?w'extending'" ) )
        {
            o.extending_stamp = NULL;
            if( source.parse_bl_fa( " #=?';'" ) )
            {
                // just reset o->extending - nothing else
            }
            else if( source.parse_bl_fa( " #=?w'stump'" ) )
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
                try( source.parse_em_fa( " ;" ) );
            }
        }
        else if( source.parse_bl_fa( " #?w'group' " ) )
        {
            $* group = xoico_group_s!.scope( scope_local );
            o.xoico_source.push_d( group.fork() );
            group.parent = o;
            group.xoico_source = o.xoico_source;
            group.compiler = o.compiler;
            group.extending_stamp = o.extending_stamp;
            group.expandable  = o.expandable;

            o.parse_name( &group->st_name, source );
            try( source.parse_em_fa( " =" ) );

            // flags
            if( source.parse_bl_fa( " #?w'retrievable' " ) ) group.retrievable = true;

            o.parse_name( &group->trait_name, source );
            if( group.trait_name.size == 0 ) group.trait_name.copy( o->st_name );
            group.parse( source );
            try( source.parse_em_fa( " ; " ) );
            compiler.register_group( group );
            xoico_nested_group_s* nested_group = xoico_nested_group_s!.scope( scope_local );
            nested_group.group = group;
            o.push_item_d( nested_group.fork().cast( xoico* ) );
        }
        else if( source.parse_bl_fa( " #?w'set' " ) )
        {
            if(      source.parse_bl_fa( " #?w'retrievable' "      ) ) o.retrievable = true;
            else if( source.parse_bl_fa( " #?w'inexpandable' "     ) ) o.expandable = false;
            else if( source.parse_bl_fa( " #?w'short_spect_name' " ) ) o.short_spect_name = true;
            else if( source.parse_bl_fa( " #?w'beta' "             ) ) try( source.parse_em_fa( " = #<tp_t*>", &o->beta ) );
            try( source.parse_em_fa( " ;" ) );
        }
        else if( source.parse_bl_fa( " #?w'embed' " ) )
        {
            st_s* folder = cast( bcore_file_folder_path( bcore_source_a_get_file( source ) ), st_s* ).scope( scope_local );
            if( folder.size == 0 ) folder.push_char( '.' );
            st_s* include_file = st_s!.scope( scope_local );
            try( source.parse_em_fa( " #string" , include_file ) );
            try( source.parse_em_fa( " ;" ) );
            o.xoico_source.target.explicit_embeddings.push_st( include_file );
            bcore_source* embed_source = NULL;
            try( xoico_embed_file_open( source, include_file.sc, &embed_source ) );

            // check for cyclic inclusions
            foreach( $* e in stack )
            {
                sc_t path = embed_source.get_file();
                if( sc_t_equal( path, e.get_file() ) )
                {
                    return source.parse_error_fa( "Xoico: Cyclic inclusion." );
                }
            }

            stack.push_d( source = embed_source );
        }
        else if( source.parse_bl_fa( " #?w'include' " ) )
        {
            bl_t deferred = source.parse_bl_fa( " #?w'deferred' " );
            st_s* include_file = st_s!.scope( scope_local );
            try( source.parse_em_fa( " #string" , include_file ) );
            try( source.parse_em_fa( " ;" ) );
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

        try( source.parse_em_fa( " " ) );// consume whitespaces
    }

    /// default features
    o.push_default_feature_from_sc( "@* clone( const );" );
    o.push_default_feature_from_sc( "void copy( mutable, const @* src );" );
    o.push_default_feature_from_sc( "void discard( mutable );" );

    if( stack.size > 1 )
    {
        return source.parse_error_fa( "Xoico: Unexpected end of group reached." );
    }

    o.tp_name = compiler.entypeof( o.st_name.sc );

    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico.finalize =
{ try {
    foreach( $* e in o ) e.finalize();
    foreach( $* func in o.funcs )
    {
        func.finalize();
        o.compiler.register_func( func );
    }
    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:) (er_t expand_forward( const, sz_t indent, bcore_sink* sink )) =
{ try {
    if( !o.expandable ) return 0;
    sink.push_fa( " \\\n#rn{ }BCORE_FORWARD_OBJECT( #<sc_t> );", indent, o.st_name.sc );
    foreach( $* e in o ) e.expand_forward( indent, sink );
    foreach( $* func in o.funcs ) func.expand_forward( indent, sink );
    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:) (er_t expand_spect_declaration( const, sz_t indent, bcore_sink* sink )) =
{ try {
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
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:) :.expand_declaration =
{ try {
    if( !o.expandable ) return 0;

    sink.push_fa( "\n" );
    sink.push_fa( "#rn{ }//#rn{-}\n", indent, sz_max( 0, 118 - indent ) );
    sink.push_fa("#rn{ }// group: #<sc_t>\n", indent, o->st_name.sc );

    foreach( $* e in o->includes_in_declaration ) sink.push_fa( "##include \"#<sc_t>\"\n", e.sc );

    sink.push_fa( "\n" );
    sink.push_fa( "#rn{ }##define TYPEOF_#<sc_t> 0x#pl16'0'{#X<tp_t>}ull\n", indent, o.st_name.sc, btypeof( o.st_name.sc ) );

    st_s* st_spect_name = cast( xoico_group_s_create_spect_name( o ), st_s* ).scope();
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
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:) (er_t expand_spect_definition( const, sz_t indent, bcore_sink* sink )) =
{ try {
    if( !o.expandable ) return 0;
    sink.push_fa( "\n" );
    if( o.short_spect_name )
    {
        sink.push_fa( "#rn{ }BCORE_DEFINE_SPECT( #<sc_t>, #<sc_t> )\n", indent, o.trait_name.sc, o.st_name.sc );
    }
    else
    {
        sink.push_fa( "#rn{ }XOILA_DEFINE_SPECT( #<sc_t>, #<sc_t> )\n", indent, o.trait_name.sc, o.st_name.sc );
    }

    sink.push_fa( "#rn{ }\"{\"\n", indent );
    sink.push_fa( "#rn{ }    \"bcore_spect_header_s header;\"\n", indent );
    foreach( $* e in o ) e.expand_spect_definition( indent + 4, sink );
    sink.push_fa( "#rn{ }\"}\";\n", indent );
    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:) :.expand_definition =
{ try {
    if( !o.expandable ) return 0;
    sink.push_fa( "\n" );
    sink.push_fa( "#rn{ }//#rn{-}\n", indent, sz_max( 0, 118 - indent ) );
    sink.push_fa( "#rn{ }// group: #<sc_t>\n", indent, o.st_name.sc );

    foreach( $* e in o.includes_in_definition ) sink.push_fa( "##include \"#<sc_t>\"\n", e.sc );

    // non-features
    foreach( $* e in o ) if( e._ != TYPEOF_xoico_feature_s ) e.expand_definition( indent, sink );

    o.expand_spect_definition( indent, sink );

    // just-features
    foreach( $* e in o ) if( e._ == TYPEOF_xoico_feature_s ) e.expand_definition( indent, sink );

    foreach( $* func in o->funcs ) func.expand_definition( indent, sink );

    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:) :.expand_init1 =
{ try {
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
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
