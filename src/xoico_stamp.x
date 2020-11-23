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

/// removes comments, excessive whitespaces; trailing whitespaces; keeps strings but replaces '"' with '\"'
func (st_s* create_embedded_string( const st_s* s )) =
{
    st_s* out = st_s!;
    for( sz_t i = 0; i < s.size; i++ )
    {
        if( s.[ i ] == '/' && s.[ i + 1 ] == '/' )
        {
            while( i < s.size && s.[ i ] != '\n' ) i++;
        }
        else if( s.[ i ] == '/' && s.[ i + 1 ] == '*' )
        {
            while( i < s.size )
            {
                if( s.[ i ] == '*' && s.[ i + 1 ] == '/' )
                {
                    if( out.[ out.size - 1 ] != ' ' ) out.push_char( ' ' );
                    i += 2;
                    break;
                }
                i++;
            }
        }
        else if( s.[ i ] == '"' )
        {
            out.push_char( '\\' );
            out.push_char( '"' );
            i++;
            while( i < s.size && s.[ i ] != '"' ) out.push_char( s.[ i++ ] );
            if( s.[ i ] == '"' )
            {
                out.push_char( '\\' );
                out.push_char( '"' );
            }
        }
        else if( s.[ i ] == '\n' )
        {
            if( out.[ out.size - 1 ] != ' ' ) out.push_char( ' ' );
        }
        else if( s.[ i ] == '\t' )
        {
            if( out.[ out.size - 1 ] != ' ' ) out.push_char( ' ' );
        }
        else if( s.[ i ] == ' ' )
        {
            if( out.[ out.size - 1 ] != ' ' ) out.push_char( ' ' );
        }
        else
        {
            out.push_char( s.[ i ] );
        }
    }
    if( out.size > 0 && out.[ out.size - 1 ] == ' ' )
    {
        out.[ out.size - 1 ] = 0;
        out.size--;
    }
    return out;
};

//----------------------------------------------------------------------------------------------------------------------

/** Creates a structured multiline string for direct code embedding
 *  from an embedded string
 */
func (st_s* create_structured_multiline_string( const sc_t s, sz_t indent )) =
{
    st_s* out = st_s!;
    sz_t ind = indent;
    bl_t newline = true;
    for( sz_t i = 0; s[ i ] != 0; i++ )
    {
        char c = s[ i ];
        if( c == ';' )
        {
            if( newline ) out.push_fa( "#rn{ }\"", ind );
            out.push_char( c );
            out.push_fa( "\"\n" );
            newline = true;
        }
        else if( c == '{' )
        {
            if( newline )
            {
                out.push_fa( "#rn{ }\"{\"", ind );
            }
            else
            {
                out.push_fa( "\"\n#rn{ }\"{\"", ind );
            }
            if( s[ i + 1 ] != 0 ) out.push_char( '\n' );
            ind += 4;
            newline = true;

        }
        else if( c == '}' )
        {
            ind -= 4;
            if( newline )
            {
                out.push_fa( "#rn{ }\"}\"", ind );
            }
            else
            {
                out.push_fa( "\"\n#rn{ }\"}\"", ind );
            }
            if( s[ i + 1 ] != 0 ) out.push_char( '\n' );
            newline = true;
        }
        else if( c == ' ' )
        {
            if( !newline )
            {
                if( s[ i + 1 ] != ';' && s[ i + 1 ] != '{' && s[ i + 1 ] != '}' && s[ i + 1 ] != 0 )
                {
                    out.push_char( c );
                }
            }
        }
        else
        {
            if( newline )
            {
                out.push_fa( "#rn{ }\"", ind );
                newline = false;
            }
            out.push_char( c );
        }
    }

    if( !newline ) out.push_char( '"' );
    return out;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) (sc_t get_rel_name_sc( const )) =
{
    sc_t group_name = o.group.st_name.sc;
    sc_t stamp_name = o.st_name.sc;

    sz_t i = 0;
    while( group_name[ i ] == stamp_name[ i ] && group_name[ i ] != 0 ) i++;
    if( group_name[ i ] == 0 && stamp_name[ i ] == '_' ) i++;

    return stamp_name + i;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) :.parse_func = (try)
{
    $* compiler = o.group.compiler;
    $* func = xoico_func_s!.scope();
    func.group = o.group;
    func.stamp = o;
    func.parse( source );

    bl_t register_func =  func.registerable();
    sz_t idx = o.funcs.get_index_from_name( func->name );

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
                o->self_source.replace_sc_sc( prex_func.flect_decl.sc, "" );
            }
        }
        else if( prex_func.overloadable )
        {
            o.funcs.replace_fork( idx, func );
            o.self_source.replace_sc_sc( prex_func.flect_decl.sc, "" );
        }
        else
        {
            return source.parse_error_fa( "Function '#<sc_t>' has already been declared and is not overloadable.", compiler.nameof( func.name ) );
        }
    }
    else
    {
        o.funcs.push_d( func.fork() );
    }


    if( register_func )
    {
        bl_t push_brace = false;
        if( o.self_source.size > 0 && o.self_source.sc[ o.self_source.size - 1 ] == '}' )
        {
            o.self_source.size--;
            push_brace = true;
        }
        o.self_source.push_st( func.flect_decl );
        if( push_brace ) o.self_source.push_sc( "}" );
    }

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) (er_t parse_extend( mutable, bcore_source* source )) = (try)
{
    ASSERT( o.self_source );

    source.parse_em_fa( " {" );

    if( o.self_source.size > 0 && o.self_source.sc[ o.self_source->size - 1 ] == '}' )
    {
        o.self_source->size--;
    }
    else
    {
        o.self_source.push_fa( "{" );
    }

    while( !source.eos() && !source.parse_bl( " #?'}'" ) )
    {
        if( source.parse_bl( " #?w'func'" ) )
        {
            o.parse_func( source );
        }
        else
        {
            bl_t exit = false;
            while( !exit && !source.eos() )
            {
                u0_t c =  source.get_u0();
                switch( c )
                {
                    case ':':
                    {
                        st_s* name = st_s!.scope( scope_local );
                        o.group.parse_name_recursive( name, source );
                        o.self_source.push_st( name );
                    }
                    break;

                    case ';':
                    {
                        o.self_source.push_char( c );
                        exit = true;
                    }
                    break;

                    default:
                    {
                        o.self_source.push_char( c );
                    }
                    break;
                }
            }
        }
    }
    source.parse_em_fa( " ; " );
    o.self_source.push_sc( "}" );

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) (er_t push_default_func_from_sc( mutable, sc_t sc )) = (try)
{
    $* compiler = o.group.compiler;
    $* func = xoico_func_s!.scope();
    func.group = o.group;
    func.stamp = o;
    func.overloadable = false;
    func.expandable = false;

    func.parse( bcore_source_string_s_create_sc( sc ).scope() );

    sz_t idx = o.funcs.get_index_from_signature_global_name( func.signature_global_name );

    if( idx >= 0 )
    {
        return o.source_point.parse_error_fa( "Function '#<sc_t>' is predefined for all stamps and cannot be overloaded.", compiler.nameof( func.name ) );
    }
    else
    {
        o.funcs.push_d( func.fork() );
    }

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) :.push_default_funcs = (try)
{
    o.push_default_func_from_sc( "bcore_stamp_funcs.init;" );
    o.push_default_func_from_sc( "bcore_stamp_funcs.down;" );
    o.push_default_func_from_sc( "bcore_stamp_funcs.copy;" );
    o.push_default_func_from_sc( "bcore_stamp_funcs.discard;" );
    o.push_default_func_from_sc( "bcore_stamp_funcs.clone;" );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) :.parse = (try)
{
    $* compiler = o.group.compiler;
    bl_t verbatim = source.parse_bl( " #?w'verbatim'" );
    o.self_source =< st_s!;

    $* stamp_name = st_s!.scope();
    $* trait_name = st_s!.scope();

    o.source_point.set( source );

    o.group.parse_name( stamp_name, source );

    if( stamp_name.size >= 2 && sc_t_equ( stamp_name.sc + stamp_name.size - 2, "_s" ) )
    {
        return o.source_point.parse_error_fa
        (
            "Stamp '#<sc_t>' ends in '_s'."
            "In beth, this ending identifies a structure."
            "Using it as stamp name could have side effects.",
            stamp_name->sc
        );
    }

    st_s_push_fa( stamp_name, "_s" );

    source.parse_em_fa( " = " );

    if( source.parse_bl( " #?w'extending'" ) )
    {
        st_s* templ_name = st_s!.scope();
        o.group.parse_name( templ_name, source );
        templ_name.push_fa( "_s" );
        const xoico* item = compiler.get_const_item( typeof( templ_name.sc ) );
        if( !item ) return source.parse_error_fa( "Template #<sc_t> not found.", templ_name.sc );
        if( item._ != TYPEOF_xoico_stamp_s ) return source.parse_error_fa( "Template #<sc_t> is no stamp.", templ_name.sc );
        o.copy( item.cast( xoico_stamp_s* ) );
    }
    else if( !verbatim && o.group.extending_stamp )
    {
        o.copy( o.group.extending_stamp );
    }
    else
    {
        o.self_source.push_fa( "@ =" );

        if( source.parse_bl( " #?w'aware'" ) )
        {
            o.self_source.push_sc( "aware " );
            o.is_aware = true;
        }

        o.group.parse_name( trait_name, source );
        if( trait_name.size == 0 ) return source.parse_error_fa( "Trait name expected." );

        o.st_trait_name.copy( trait_name );
        o.self_source.push_st( trait_name );
    }

    o.st_name.copy( stamp_name );
    o.tp_name = compiler.entypeof( stamp_name.sc );

    o.parse_extend( source );

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico.finalize = (try)
{
    $* compiler = o.group.compiler;

    // TODO: move functions declaration in self_source to finalize
    o.self_source.replace_sc_sc( "@", o.st_name.sc );

    foreach( $* func in o.funcs )
    {
        func.group = o.group;
        func.stamp = o;
        func.finalize();
        compiler.register_func( func );
    }

    o.self =< bcore_self_s_parse_source( bcore_source_string_s_create_from_string( o.self_source ).scope().cast( bcore_source* ), 0, 0, o.group.st_name.sc, false );

    $* hmap_name = bcore_hmap_tp_s!.scope();

    sz_t self_items = bcore_self_s_items_size( o.self );

    for( sz_t i = 0; i < self_items; i++ )
    {
        const bcore_self_item_s* item = o.self.get_item( i );
        if( item.name )
        {
            if( hmap_name.exists( item.name ) )
            {
                return o.source_point.parse_error_fa( "In stamp '<sc_t>': Repeated use of element name '<sc_t>'.", o.st_name.sc, compiler.nameof( item.name ) );
                hmap_name.set( item.name );
            }
        }
    }

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico.expand_declaration = (try)
{
    sc_t sc_name = o.st_name.sc;

    sink.push_fa( "#rn{ }##define TYPEOF_#<sc_t> 0x#pl16'0'{#X<tp_t>}ull\n", indent, sc_name, typeof( sc_name ) );

    sink.push_fa( "#rn{ }##define BETH_EXPAND_ITEM_#<sc_t>", indent, sc_name, sc_name );
    sink.push_fa( " \\\n#rn{ }  BCORE_DECLARE_OBJECT( #<sc_t> )", indent, sc_name );
    sink.push_fa( " \\\n" );

    o.self.struct_body_to_sink_newline_escaped( indent + 2, sink );
    sink.push_fa( ";" );

    foreach( $* func in o.funcs ) func.expand_forward( indent + 2, sink ); // expands all prototypes

    // expand array
    if( o.self.trait == TYPEOF_bcore_array )
    {
        sz_t items = o.self.items_size();
        const bcore_self_item_s* array_item = NULL;
        for( sz_t i = 0; i < items; i++ )
        {
            const bcore_self_item_s* self_item = o.self.get_item( i );
            if( bcore_flect_caps_is_array( self_item.caps ) )
            {
                array_item = self_item;
                break;
            }
        }

        if( !array_item )
        {
            return o.source_point.parse_error_fa( "Expanding object #<sc_t>: Object is of trait array but contains no array.", sc_name );
        }

        sink.push_fa( " \\\n#rn{ }  static inline #<sc_t>* #<sc_t>_set_space( #<sc_t>* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_#<sc_t>, ( bcore_array* )o, size ); return o; }", indent, sc_name, sc_name, sc_name, sc_name );
        sink.push_fa( " \\\n#rn{ }  static inline #<sc_t>* #<sc_t>_set_size( #<sc_t>* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_#<sc_t>, ( bcore_array* )o, size ); return o; }",   indent, sc_name, sc_name, sc_name, sc_name );
        sink.push_fa( " \\\n#rn{ }  static inline #<sc_t>* #<sc_t>_clear( #<sc_t>* o ) { bcore_array_t_set_space( TYPEOF_#<sc_t>, ( bcore_array* )o, 0 ); return o; }",                   indent, sc_name, sc_name, sc_name, sc_name );

        sc_t  sc_item_name = ifnameof( array_item.name );
        st_s* st_last = st_s_create_fa( "o->#<sc_t>#<sc_t>data[ o->#<sc_t>#<sc_t>size - 1 ]", sc_item_name, sc_item_name[ 0 ] ? "_" : "", sc_item_name, sc_item_name[ 0 ] ? "_" : ""  ).scope();
        sc_t  sc_last = st_last.sc;
        if( array_item.type != 0 && nameof( array_item.type ) != NULL )
        {
            sc_t sc_type = ifnameof( array_item.type );
            if( array_item.caps == BCORE_CAPS_ARRAY_DYN_LINK_AWARE )
            {
                sink.push_fa( " \\\n#rn{ }  static inline #<sc_t>* #<sc_t>_push_c( #<sc_t>* o, const #<sc_t>* v ) { bcore_array_t_push( TYPEOF_#<sc_t>, ( bcore_array* )o, sr_awc( v ) ); return #<sc_t>; }", indent, sc_type, sc_name, sc_name, sc_type, sc_name, sc_last );
                sink.push_fa( " \\\n#rn{ }  static inline #<sc_t>* #<sc_t>_push_d( #<sc_t>* o,       #<sc_t>* v ) { bcore_array_t_push( TYPEOF_#<sc_t>, ( bcore_array* )o, sr_asd( v ) ); return #<sc_t>; }", indent, sc_type, sc_name, sc_name, sc_type, sc_name, sc_last );
                sink.push_fa( " \\\n#rn{ }  static inline #<sc_t>* #<sc_t>_push_t( #<sc_t>* o, tp_t t )", indent, sc_type, sc_name, sc_name );
                sink.push_fa( " \\\n#rn{ }  {", indent );
                sink.push_fa( " \\\n#rn{ }      bcore_trait_assert_satisfied_type( TYPEOF_#<sc_t>, t );",                    indent, sc_type );
                sink.push_fa( " \\\n#rn{ }      bcore_array_t_push( TYPEOF_#<sc_t>, ( bcore_array* )o, sr_t_create( t ) );", indent, sc_name );
                sink.push_fa( " \\\n#rn{ }      return #<sc_t>;", indent, sc_last );
                sink.push_fa( " \\\n#rn{ }  }", indent );
            }
            else if( array_item.caps == BCORE_CAPS_ARRAY_DYN_SOLID_STATIC )
            {
                sink.push_fa( " \\\n#rn{ }  static inline #<sc_t>* #<sc_t>_push_c( #<sc_t>* o, const #<sc_t>* v ) { bcore_array_t_push( TYPEOF_#<sc_t>, ( bcore_array* )o, sr_twc( TYPEOF_#<sc_t>, v ) ); return &#<sc_t>; }", indent, sc_type, sc_name, sc_name, sc_type, sc_name, sc_type, sc_last );
                sink.push_fa( " \\\n#rn{ }  static inline #<sc_t>* #<sc_t>_push_d( #<sc_t>* o,       #<sc_t>* v ) { bcore_array_t_push( TYPEOF_#<sc_t>, ( bcore_array* )o, sr_tsd( TYPEOF_#<sc_t>, v ) ); return &#<sc_t>; }", indent, sc_type, sc_name, sc_name, sc_type, sc_name, sc_type, sc_last );
                sink.push_fa( " \\\n#rn{ }  static inline #<sc_t>* #<sc_t>_push( #<sc_t>* o )", indent, sc_type, sc_name, sc_name );
                sink.push_fa( " \\\n#rn{ }  {", indent );
                sink.push_fa( " \\\n#rn{ }      bcore_array_t_push( TYPEOF_#<sc_t>, ( bcore_array* )o, sr_null() );",   indent, sc_name );
                sink.push_fa( " \\\n#rn{ }      return &#<sc_t>;", indent, sc_last );
                sink.push_fa( " \\\n#rn{ }  }", indent );
            }
            else if( array_item.caps == BCORE_CAPS_ARRAY_DYN_LINK_STATIC )
            {
                sink.push_fa( " \\\n#rn{ }  static inline #<sc_t>* #<sc_t>_push_c( #<sc_t>* o, const #<sc_t>* v ) { bcore_array_t_push( TYPEOF_#<sc_t>, ( bcore_array* )o, sr_twc( TYPEOF_#<sc_t>, v ) ); return #<sc_t>; }", indent, sc_type, sc_name, sc_name, sc_type, sc_name, sc_type, sc_last );
                sink.push_fa( " \\\n#rn{ }  static inline #<sc_t>* #<sc_t>_push_d( #<sc_t>* o,       #<sc_t>* v ) { bcore_array_t_push( TYPEOF_#<sc_t>, ( bcore_array* )o, sr_tsd( TYPEOF_#<sc_t>, v ) ); return #<sc_t>; }", indent, sc_type, sc_name, sc_name, sc_type, sc_name, sc_type, sc_last );
                sink.push_fa( " \\\n#rn{ }  static inline #<sc_t>* #<sc_t>_push( #<sc_t>* o )", indent, sc_type, sc_name, sc_name );
                sink.push_fa( " \\\n#rn{ }  {", indent );
                sink.push_fa( " \\\n#rn{ }      bcore_array_t_push( TYPEOF_#<sc_t>, ( bcore_array* )o, sr_t_create( TYPEOF_#<sc_t> ) );", indent, sc_name, sc_type );
                sink.push_fa( " \\\n#rn{ }      return #<sc_t>;", indent, sc_last );
                sink.push_fa( " \\\n#rn{ }  }", indent );
            }
        }
        else
        {
            if( bcore_flect_caps_is_aware( array_item.caps ) )
            {
                sink.push_fa( " \\\n#rn{ }  static inline void #<sc_t>_push_c( #<sc_t>* o, vc_t v ) { bcore_array_t_push( TYPEOF_#<sc_t>, ( bcore_array* )o, sr_awc( v ) ); }", indent, sc_name, sc_name, sc_name );
                sink.push_fa( " \\\n#rn{ }  static inline void #<sc_t>_push_d( #<sc_t>* o, vd_t v ) { bcore_array_t_push( TYPEOF_#<sc_t>, ( bcore_array* )o, sr_asd( v ) ); }", indent, sc_name, sc_name, sc_name );
            }
        }
    }

    foreach( $* func in o.funcs ) func.expand_declaration( indent + 2, sink ); // only expands static inline functions

    sink.push_fa( "\n" );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico.expand_definition = (try)
{
    st_s* embedded_string = xoico_stamp_create_embedded_string( o.self_source ).scope();

    // 4095 is the C99-limit for string literals
    if( embedded_string.size > 4095 )
    {
        return o.source_point.parse_error_fa
        (
            "Reflection embedding failed. (Stamp is too large)\n"
            "The embedded code would require a string literal larger than 4095 characters.\n"
            "This exceeds the limit defined in C99.\n"
        );
    }

    sz_t idx = embedded_string.find_char( 0, -1, '=' );
    sc_t self_def = "";
    if( idx < embedded_string.size )
    {
        self_def = embedded_string.sc + idx + 1;
    }

    sink.push_fa( "\n" );
    sink.push_fa( "#rn{ }BCORE_DEFINE_OBJECT_INST_P( #<sc_t> )\n", indent, o.st_name.sc );

    st_s* multiline_string = xoico_stamp_create_structured_multiline_string( self_def, indent ).scope();
    sink.push_fa( "#<sc_t>;\n", multiline_string.sc );

    foreach( $* func in o.funcs ) func.expand_definition( indent, sink );

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico.expand_init1 = (try)
{
    $* compiler = o.group.compiler;

    foreach( $* func in o.funcs )
    {
        if( func.expandable && func.registerable() )
        {
            const xoico_signature_s* signature = func.signature;
            sink.push_fa
            (
                "#rn{ }BCORE_REGISTER_FFUNC( #<sc_t>, #<sc_t>_#<sc_t> );\n",
                indent,
                compiler.nameof( signature->global_name ),
                o.st_name.sc,
                compiler.nameof( func.name )
            );
        }
    }
    sink.push_fa( "#rn{ }BCORE_REGISTER_OBJECT( #<sc_t> );\n", indent, o.st_name.sc );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

