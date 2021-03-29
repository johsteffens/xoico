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

signature er_t parse_func( m @* o, m bcore_source* source );
signature er_t parse_wrap( m @* o, m bcore_source* source );
signature er_t make_funcs_overloadable( m @* o );
signature er_t push_default_funcs( m @* o );
signature c xoico_func_s* get_func_from_name( c @* o, tp_t name ); // returns NULL if not found
signature c xoico_func_s* get_trait_line_func_from_name( c @* o, tp_t name ); // returns NULL if not found


stamp :s = aware :
{
    st_s st_name;
    tp_t tp_name; // typeof( st_name )
    tp_t trait_name;
    bl_t is_aware = true;

    st_s => self_buf;
    st_s => self_source;

    bcore_self_item_s => first_array_item; // !=NULL if stamp has an array; valid after parsing
    bcore_self_s => self; // created in expand_setup
    xoico_funcs_s funcs;
    xoico_wraps_s wraps;

    xoico_transient_map_s transient_map;

    private aware xoico_group_s* group;
    bcore_source_point_s source_point;

    func xoico.get_hash =
    {
        tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
        hash = bcore_tp_fold_sc( hash, o.st_name.sc );
        hash = bcore_tp_fold_sc( hash, o.self_source ? o.self_source.sc : o.self_buf ? o.self_buf.sc : "" );
        hash = bcore_tp_fold_tp( hash, o.funcs.get_hash() );
        return hash;
    };

    func xoico.get_global_name_tp = { return o.tp_name; };
    func xoico.finalize;

    func xoico.expand_setup = { return 0; };
    func xoico.expand_declaration;
    func xoico.expand_forward =
    {
        sink.push_fa( " \\\n#rn{ }BCORE_FORWARD_OBJECT( #<sc_t> );", indent, o.st_name.sc );
        return 0;
    };

    func xoico.expand_indef_declaration =
    {
        sink.push_fa( " \\\n#rn{ }  BETH_EXPAND_ITEM_#<sc_t>", indent, o.st_name.sc );
        return 0;
    };

    func xoico.expand_definition;
    func xoico.expand_init1;

    func xoico.parse;
    func :.parse_func;
    func :.parse_wrap;

    func :.make_funcs_overloadable =
    {
        foreach( m $* func in o.funcs ) func->overloadable = true;
        return 0;
    };

    func :.get_func_from_name = { return o.funcs.get_func_from_name( name ); };

    func :.get_trait_line_func_from_name =
    {
        c $* func = o.funcs.get_func_from_name( name );
        if( !func )
        {
            func = o.group.compiler.get_group( o.trait_name ).get_trait_line_func_from_name( name );
        }
        return func;
    };

    func :.push_default_funcs;

    func xoico_host.parse_name_st = { return o.group.parse_name_st( source, name ); };
    func xoico_host.compiler = { return o.group.compiler; };
    func xoico_host.cengine = { return o.group.cengine(); };
    func xoico_host.obj_type = { return o.tp_name; };
    func xoico_host.transient_map = { return o.transient_map; };

    func xoico.get_source_point = { return o.source_point; };
};

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

/// removes comments, excessive whitespaces; trailing whitespaces; keeps strings but replaces '"' with '\"'
func (d st_s* create_embedded_string( c st_s* s )) =
{
    d st_s* out = st_s!;
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
func (d st_s* create_structured_multiline_string( c sc_t s, sz_t indent )) =
{
    d st_s* out = st_s!;
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

func (:s) (sc_t get_rel_name_sc( c @* o )) =
{
    sc_t group_name = o.group.st_name.sc;
    sc_t stamp_name = o.st_name.sc;

    sz_t i = 0;
    while( group_name[ i ] == stamp_name[ i ] && group_name[ i ] != 0 ) i++;
    if( group_name[ i ] == 0 && stamp_name[ i ] == '_' ) i++;

    return stamp_name + i;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) :.parse_func = (try)
{
    m $* compiler = o.group.compiler;
    m $* func = xoico_func_s!^;
    func.parse( o, source );

    sz_t idx = o.funcs.get_index_from_name( func->name );

    if( idx >= 0 )
    {
        m xoico_func_s* prex_func = o.funcs.[ idx ];
        if( ( prex_func.signature_global_name == func.signature_global_name ) )
        {
            if( !func.body )
            {
                return source.parse_error_fa( "Function '#<sc_t>' has already been declared.", compiler.nameof( func.name ) );
            }
            else if( prex_func.body )
            {
                return func.source_point.parse_error_fa( "Function '#<sc_t>' has already a body.", compiler.nameof( func.name ) );
            }
            else
            {
                o.funcs.replace_d( idx, func.fork() );
            }
        }
        else if( prex_func.overloadable )
        {
            o.funcs.replace_d( idx, func.fork() );
        }
        else
        {
            return func.source_point.parse_error_fa( "Function '#<sc_t>' has already been declared and is not overloadable.", compiler.nameof( func.name ) );
        }
    }
    else
    {
        o.funcs.push_d( func.fork() );
    }

    if( func.signature_global_name == x_inst_main~ ) o.group.xoico_source.target.set_main_function( func );

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) :.parse_wrap = (try)
{
    m $* wrap = xoico_wrap_s!^;
    wrap.parse( o, source );
    o.wraps.push_d( wrap.fork() );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) (er_t parse_extend( m @* o, m bcore_source* source )) = (try)
{
    ASSERT( o.self_buf );

    m $* buf = st_s!^;
    m $* self = bcore_self_s!^;
    self.type = o.tp_name;
    self.trait = o.trait_name;

    source.parse_em_fa( " {" );

    while( !source.eos() && !source.parse_bl( " #?'}'" ) )
    {
        if( source.parse_bl( " #?w'func'" ) )
        {
            o.parse_func( source );
        }
        else if( source.parse_bl( " #?w'wrap'" ) )
        {
            o.parse_wrap( source );
        }
        else
        {
            bl_t exit = false;

            buf.clear();

            while( !exit && !source.eos() )
            {
                u0_t c =  source.get_u0();
                switch( c )
                {
                    case ':':
                    {
                        m st_s* name = st_s!^;
                        o.group.parse_name_recursive( source, name );
                        buf.push_st( name );
                    }
                    break;

                    case '@':
                    {
                        buf.push_st( o.st_name );
                    }
                    break;

                    case ';':
                    {
                        buf.push_char( c );
                        exit = true;
                    }
                    break;

                    default:
                    {
                        buf.push_char( c );
                    }
                    break;
                }
            }

            m $* item = bcore_self_item_s!^;
            er_t er = bcore_self_item_s_parse_src( item, sr_awc( bcore_source_string_s_create_from_string( buf )^^ ), self, false );
            if( bcore_flect_caps_is_array( item->caps ) && !o.first_array_item ) o.first_array_item = item.clone();

            if( er )
            {
                m $* msg = st_s!^;
                bcore_error_pop_st( er.1, msg );
                return source.parse_error_fa( "Reflection parse error:\n#<sc_t>\n", msg.sc );
            }

            o.self_buf.push_st( buf );
        }
    }
    source.parse_em_fa( " ; " );

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) (er_t push_default_func_from_sc( m @* o, sc_t sc )) = (try)
{
    m $* compiler = o.group.compiler;
    m $* func = xoico_func_s!^;
    func.overloadable = false;
    func.expandable = false;

    func.parse_sc( o, sc );

    sz_t idx = o.funcs.get_index_from_signature_global_name( func.signature_global_name );

    if( idx >= 0 )
    {
        return o.source_point.parse_error_fa( "Function '#<sc_t>' conflicts with a default function for this stamp.", compiler.nameof( func.name ) );
    }
    else
    {
        o.funcs.push_d( func.fork() );
    }

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) :.push_default_funcs = (try)
{
    o.push_default_func_from_sc( "bcore_stamp_funcs.init;" );
    o.push_default_func_from_sc( "bcore_stamp_funcs.down;" );
    o.push_default_func_from_sc( "bcore_stamp_funcs.copy;" );
    o.push_default_func_from_sc( "bcore_stamp_funcs.create;" );
    o.push_default_func_from_sc( "bcore_stamp_funcs.discard;" );
    o.push_default_func_from_sc( "bcore_stamp_funcs.clone;" );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) xoico.parse = (try)
{
    m $* compiler = o.group.compiler;
    bl_t verbatim = source.parse_bl( " #?w'verbatim'" );
    o.self_buf =< st_s!;

    m $* st_stamp_name = st_s!^;

    o.source_point.set( source );

    o.group.parse_name_st( source, st_stamp_name );

    if( !st_stamp_name.ends_in_sc( "_s" ) ) return source.parse_error_fa( "Stamp name '#<sc_t>' must end in '_s'.", st_stamp_name->sc );

    source.parse_em_fa( " = " );

    if( source.parse_bl( " #?w'extending'" ) )
    {
        m st_s* templ_name = st_s!^;
        o.group.parse_name_st( source, templ_name );

        if( !templ_name.ends_in_sc( "_s" ) )
        {
            return source.parse_error_fa( "Extending: Stamp name '#<sc_t>' must end in '_s'.", templ_name->sc );
        }

        c xoico* item = compiler.get_const_item( btypeof( templ_name.sc ) );
        if( !item ) return source.parse_error_fa( "Template #<sc_t> not found.", templ_name.sc );
        if( item._ != xoico_stamp_s~ ) return source.parse_error_fa( "Template #<sc_t> is no stamp.", templ_name.sc );
        o.copy( item.cast( m xoico_stamp_s* ) );
    }
    else if( !verbatim && o.group.extending_stamp )
    {
        o.copy( o.group.extending_stamp );
    }
    else
    {
        /// 'is_aware' is true by default
        if      ( source.parse_bl( " #?w'obliv'" ) ) o.is_aware = false;
        else if ( source.parse_bl( " #?w'aware'" ) ) o.is_aware = true;

        m $* st_trait_name = st_s!^;
        o.group.parse_name_st( source, st_trait_name );
        if( st_trait_name.size > 0 )
        {
            o.trait_name = compiler.entypeof( st_trait_name.sc );
        }
        else
        {
            o.trait_name = o.group.tp_name;
        }


        if( source.parse_bl( " #=?'('" ) )
        {
            o.transient_map.parse( o, source );
        }
    }

    o.st_name.copy( st_stamp_name );
    o.tp_name = compiler.entypeof( st_stamp_name.sc );
    o.parse_extend( source );

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) xoico.finalize = (try)
{
    m $* compiler = o.group.compiler;

    // set transient classes for x_array
    if( o.trait_name == x_array~ || o.trait_name == bcore_array~ )
    {
        if( !o.first_array_item )
        {
            return o.source_point.parse_error_fa( "In stamp '#<sc_t>': Tramp is of trait 'x_array' but contains no array", o.st_name.sc );
        }
        o.transient_map.set( compiler.entypeof( "TO" ), o.tp_name );
        if( o.first_array_item.type ) o.transient_map.set( compiler.entypeof( "TE" ), o.first_array_item.type );
    }

    foreach( m $* wrap in o.wraps )
    {
        wrap.finalize( o );
        o.funcs.push_d( wrap.func.fork() );
    }

    foreach( m $* func in o.funcs )
    {
        func.finalize( o );
        if( func.reflectable( o ) ) func.push_flect_decl_to_sink( o, o.self_buf );
        compiler.register_func( func );
    }

    o.self_buf.replace_sc_sc( "@", o.st_name.sc );

    o.self_source =< st_s!;
    o.self_source.push_fa( "#<sc_t> =", o.st_name.sc );
    if( o.is_aware ) o.self_source.push_sc( "aware " );
    o.self_source.push_sc( compiler.nameof( o.trait_name ) );
    o.self_source.push_fa( "{#<st_s*>}", o.self_buf );
    o.self_buf =< NULL;

    o.self =< bcore_self_s_parse_source( bcore_source_string_s_create_from_string( o.self_source )^^.cast( m bcore_source* ), 0, 0, o.group.st_name.sc, false );

    // checking for repetitions in o.self (non-functions)
    m $* hmap_name = bcore_hmap_tp_s!^;
    sz_t self_items = bcore_self_s_items_size( o.self );
    for( sz_t i = 0; i < self_items; i++ )
    {
        c bcore_self_item_s* item = o.self.get_item( i );
        if( item.name && ( item.caps != BCORE_CAPS_EXTERNAL_FUNC ) )
        {
            if( hmap_name.exists( item.name ) )
            {
                return o.source_point.parse_error_fa( "In stamp '#<sc_t>': Repeated use of member name '#<sc_t>'.", o.st_name.sc, compiler.nameof( item.name ) );
            }

            hmap_name.set( item.name );
        }
    }

    // checking for repetitions of function names
//    foreach( m $* func in o.funcs )
//    {
//        if( func.name )
//        {
//            if( hmap_name.exists( func.name ) )
//            {
//                return o.source_point.parse_error_fa( "In stamp '#<sc_t>': Repeated use of member name '#<sc_t>'.", o.st_name.sc, compiler.nameof( func.name ) );
//            }
//
//            hmap_name.set( func.name );
//        }
//    }



    // check validity of trait name
    if( !compiler.is_group( o.trait_name ) )
    {
        return o.source_point.parse_error_fa( "In stamp '#<sc_t>': Trait name '#<sc_t>' is not a group.", o.st_name.sc, compiler.nameof( o.trait_name ) );
    }

    // update retrievability of groups in traitline
    for( tp_t trait_name = o.trait_name; trait_name != 0; )
    {
        xoico_group_s* group = compiler.get_group( trait_name );
        trait_name = group.trait_name != group.tp_name ? group.trait_name : 0;
        if( group.is_retrievable ) group.retrievable_stamps!.push( o.tp_name );
    }

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) xoico.expand_declaration = (try)
{
    sc_t sc_name = o.st_name.sc;

    sink.push_fa( "#rn{ }##define TYPEOF_#<sc_t> 0x#pl16'0'{#X<tp_t>}ull\n", indent, sc_name, btypeof( sc_name ) );

    sink.push_fa( "#rn{ }##define BETH_EXPAND_ITEM_#<sc_t>", indent, sc_name, sc_name );
    sink.push_fa( " \\\n#rn{ }  BCORE_DECLARE_OBJECT( #<sc_t> )", indent, sc_name );
    sink.push_fa( " \\\n" );

    bcore_self_s_struct_body_to_sink_newline_escaped( o.self, indent + 2, sink );
    sink.push_fa( ";" );

    foreach( m $* func in o.funcs ) func.expand_forward( o, indent + 2, sink ); // expands all prototypes
    foreach( m $* func in o.funcs ) func.expand_declaration( o, indent + 2, sink ); // only expands static inline functions

    sink.push_fa( "\n" );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) xoico.expand_definition = (try)
{
    m st_s* embedded_string = o.create_embedded_string( o.self_source )^^;

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

    m st_s* multiline_string = xoico_stamp_create_structured_multiline_string( self_def, indent )^^;
    sink.push_fa( "#<sc_t>;\n", multiline_string.sc );

    foreach( m $* func in o.funcs ) func.expand_definition( o, indent, sink );

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) xoico.expand_init1 = (try)
{
    m $* compiler = o.group.compiler;

    foreach( m $* func in o.funcs )
    {
        if( func.reflectable( host ) )
        {
            c $* signature = func.signature;
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

