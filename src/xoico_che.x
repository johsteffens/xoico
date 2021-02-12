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

/// stack for variable declarations
group :result = :
{
    feature void clear( m @* o )             = {};
    feature er_t push_char( m @* o, char c )          = (verbatim_C) { ERR_fa( "Not implemented." ); return 0; };
    feature er_t push_sc( m @* o, sc_t sc )           = (verbatim_C) { ERR_fa( "Not implemented." ); return 0; };
    feature er_t push_st( m @* o, c st_s* st )    = (verbatim_C) { ERR_fa( "Not implemented." ); return 0; };
    feature m :* push_result_c( m @* o, c :* result ) = (verbatim_C) { ERR_fa( "Not implemented." ); return NULL; };
    feature m :* push_result_d( m @* o, d :* result ) = (verbatim_C) { ERR_fa( "Not implemented." ); return NULL; };
    feature er_t to_sink( c @* o, m bcore_sink* sink );

    feature void set_parent_block( m @* o, m :block_s* parent ) = {};

    feature d st_s* create_st( c @* o ) =
    {
        d $* st = st_s!;
        o.to_sink( st );
        return st;
    };

//----------------------------------------------------------------------------------------------------------------------

    stamp :plain_s = aware :
    {
        st_s st;

        func (d @* create_from_st(   c st_s* st ) ) = { d $* o = @!; o.st.copy( st ); return o; };
        func (d @* create_from_st_d( d st_s* st ) ) = { d $* o = @!; o.st.copy( st ); st.discard(); return o; };
        func (d @* create_from_sc(     sc_t  sc ) ) = { d $* o = @!; o.st.copy_sc( sc ); return o; };

        func :.clear     = { o.st.clear(); };
        func :.push_char = { o.st.push_char( c ); return 0; };
        func :.push_sc   = { o.st.push_sc( sc ); return 0; };
        func :.push_st   = { o.st.push_st( st ); return 0; };
        func :.to_sink   = { sink.push_string( o.st );  return 0; };
        func :.create_st = { return o.st.clone(); };
    };

    func (d :* create_from_st( c st_s* st ) ) = { d $* o = :arr_s!; o.push_st( st ); return o; };
    func (d :* create_from_sc(   sc_t  sc ) ) = { d $* o = :arr_s!; o.push_sc( sc ); return o; };

    stamp :adl_s = aware x_array { aware : -> []; }; // !! weak links !!  (if this causes problems revert to strong links)

//----------------------------------------------------------------------------------------------------------------------

    stamp :arr_s = aware :
    {
        :adl_s adl;

        func :.clear = { o.adl.clear(); };

        func (m :* last( m @* o )) =
        {
            return ( o.adl.size == 0 ) ? o.adl.push_d( :plain_s! ) : o.adl.[ o.adl.size - 1 ];
        };

        func (m :* last_plain( m @* o )) =
        {
            return ( o.last()._ != TYPEOF_:plain_s ) ? o.adl.push_d( :plain_s! ) : o.adl.[ o.adl.size - 1 ];
        };

        func :.push_char = { return o.last_plain().push_char( c ); };
        func :.push_sc   = { return o.last_plain().push_sc( sc );  };
        func :.push_st   = { return o.last_plain().push_st( st );  };
        func :.push_result_d = { return o.adl.push_d( result ); };
        func :.push_result_c = { return o.adl.push_c( result ); };

        func :.to_sink =
        {
            foreach( m $* e in o.adl ) e.to_sink( sink );
            return 0;
        };

        func :.set_parent_block =
        {
            foreach( m $* e in o.adl ) e.set_parent_block( parent );
        };
    };

    func (d :* create_arr() ) = { return :arr_s!; };

//----------------------------------------------------------------------------------------------------------------------

    stamp :block_s = aware :
    {
        :arr_s arr;
        sz_t level = 0;
        bl_t is_using_blm = false;
        bl_t is_root = false;
        hidden @* parent;
        func :.clear = { o.arr.clear(); };
        func :.push_char = { return o.arr.push_char( c ); };
        func :.push_sc   = { return o.arr.push_sc( sc );  };
        func :.push_st   = { return o.arr.push_st( st );  };

        func :.push_result_d =
        {
            m :* result_pushed = o.arr.push_result_d( result );
            result_pushed.set_parent_block( o );
            return result_pushed;
        };

        func :.push_result_c =
        {
            m :* result_pushed = o.arr.push_result_c( result );
            result_pushed.set_parent_block( o );
            return result_pushed;
        };

        func :.to_sink = { return o.arr.to_sink( sink ); };
        func :.set_parent_block = { o.parent = parent; };

        func (bl_t is_using_blm_until_level( c @* o, sz_t level )) =
        {
            if( level > o.level ) return false;
            if( o.is_using_blm ) return true;
            if( o.is_root ) return false;

            ASSERT( o.parent );
            return o.parent.is_using_blm_until_level( level );
        };

    };

    func (d :* create_block( sz_t level, bl_t is_using_blm  ) ) =
    {
        d $* o = :block_s!;
        o.level = level;
        o.is_using_blm = is_using_blm;
        return o;
    };

//----------------------------------------------------------------------------------------------------------------------

    stamp :blm_init_s = aware :
    {
        sz_t level;
        func :.to_sink = { sink.push_fa( "BLM_INIT_LEVEL(#<sz_t>);", o.level ); return 0; };
    };

    func (d :* create_blm_init( sz_t level ) ) = { d $* o = :blm_init_s!; o.level = level; return o; };

//----------------------------------------------------------------------------------------------------------------------

    stamp :blm_down_s = aware :
    {
        func :.to_sink = { sink.push_sc( "BLM_DOWN();" ); return 0; };
    };

    func (d :* create_blm_down() ) = { d $* o = :blm_down_s!; return o; };

//----------------------------------------------------------------------------------------------------------------------

    func (er_t push_fv( m @* o, sc_t format, va_list args )) =
    {
        d st_s* st = st_s_create_fv( format, args );
        er_t ret = o.push_st( st );
        st_s_discard( st );
        return ret;
    };

//----------------------------------------------------------------------------------------------------------------------

    func( er_t push_fa( m @* o, sc_t format, ... )) =
    {
        va_list args;
        va_start( args, format );
        er_t ret = o.push_fv( format, args );
        va_end( args );
        return ret;
    };

//----------------------------------------------------------------------------------------------------------------------

    func( er_t copy_fv( m @* o, sc_t format, va_list args )) =
    {
        xoico_che_result_a_clear( o );
        return o.push_fv( format, args );
    };

//----------------------------------------------------------------------------------------------------------------------

    func (er_t copy_fa( m @* o, sc_t format, ... )) =
    {
        va_list args;
        va_start( args, format );
        er_t ret = o.copy_fv( format, args );
        va_end( args );
        return ret;
    };
};

/// stack for variable declarations
group :stack_var = :
{
    stamp :unit_s = aware bcore_inst
    {
        sz_t level;
        tp_t name;
        xoico_typespec_s typespec;
    };

    stamp :unit_adl_s = aware x_array { :unit_s => []; };

    signature m @* push_unit( m @* o, c :unit_s* unit );
    signature m @* pop_level( m @* o, sz_t level ); // pop all units of or above level

    signature bl_t exists( c @* o, tp_t name );
    signature c xoico_typespec_s* get_typespec( c @* o, tp_t name );
    signature c sz_t get_level( c @* o, tp_t name );
    signature void clear( m @* o );
    signature void rehash_names( m @* o );

    stamp :s = aware :
    {
        :unit_adl_s adl;
        bcore_hmap_tpuz_s hmap_name;

        func :.exists = { return o.hmap_name.exists( name ); };

        func :.rehash_names =
        {
            o.hmap_name.clear();
            for( sz_t i = 0; i < o.adl.size; i++ ) o.hmap_name.set( o.adl.[i].name, i );
        };

        func :.push_unit =
        {
            o.adl.push_c( unit );
            o.hmap_name.set( unit->name, o.adl.size - 1 );
            return o;
        };

        func :.pop_level =
        {
            sz_t size = o->adl.size;
            while( size > 0 && o.adl.data[ size - 1 ]->level >= level ) size--;
            o.adl.set_size( size );
            o.rehash_names();
            return o;
        };

        func :.get_typespec =
        {
            m uz_t* p_idx = o.hmap_name.get( name );
            if( !p_idx ) return NULL;
            return o.adl.[ p_idx.0 ].typespec;
        };

        /// returns -1 if not found
        func :.get_level =
        {
            m uz_t* p_idx = o.hmap_name.get( name );
            if( !p_idx ) return -1;
            return o.adl.[ p_idx.0 ].level;
        };

        func :.clear =
        {
            o.adl.clear();
            o.hmap_name.clear();
        };
    };
};

//----------------------------------------------------------------------------------------------------------------------

/// stack for block/level specific data
group :stack_block = :
{
    stamp :unit_s = aware bcore_inst
    {
        sz_t level; // level of this block
        bl_t use_blm = false;
        bl_t break_ledge = false; // this block represents a break-ledge for a break-command inside this block or higher-level blocks up to the next break-level
    };

    stamp :unit_adl_s = aware x_array { :unit_s => []; };

    signature m @* push( m @* o );
    signature m @* push_unit( m @* o, c :unit_s* unit );
    signature m @* pop(  m @* o );
    signature void clear( m @* o );
    signature sz_t get_size( c @* o );

    stamp :s = aware :
    {
        :unit_adl_s adl;
        func :.push      = { o.adl.push_d( :unit_s! ); return o; };
        func :.push_unit = { o.adl.push_c( unit ); return o; };

        func :.pop =
        {
            o.adl.set_size( sz_max( o->adl.size - 1, 0 ) );
            return o;
        };

        func :.clear = { o.adl.clear(); };
        func :.get_size = { return o.adl.size; };
    };

};

//----------------------------------------------------------------------------------------------------------------------

signature tp_t entypeof(  m @* o, sc_t name );
signature sc_t nameof(    m @* o, tp_t type );
signature void init_level0( m @* o );
signature void inc_level( m @* o );
signature void dec_level( m @* o );
signature void inc_block( m @* o );
signature void dec_block( m @* o );
signature void push_typedecl( m @* o, c xoico_typespec_s* typespec, tp_t name );
signature m :stack_block_unit_s* stack_block_get_top_unit( m @* o );
signature m :stack_block_unit_s* stack_block_get_bottom_unit( m @* o );
signature m :stack_block_unit_s* stack_block_get_level_unit( m @* o, sz_t level );
signature er_t push_typespec( m @* o, c xoico_typespec_s* typespec, m :result* result );
signature void typespec_to_sink( m @* o, c xoico_typespec_s* typespec, m bcore_sink* sink );

signature bl_t is_var( c @* o, tp_t name );

name static;
name volatile;
name cast;
name verbatim_C;
name keep;
name scope;
name scope_local;
name scope_func;
name keep_func;
name keep_block;
name fork;
name try;
name if;
name else;
name while;
name do;
name for;
name foreach;
name switch;
name case;
name default;
name break;
name return;
name continue;
name goto;
name true;
name false;

stamp :s = aware :
{
    /// parameters

    bl_t verbose = false;

    /// Prepends a commented reference to the xoila source for each function in *xoila_out.c
    bl_t insert_source_reference = true;

    /// purity-control:

    // Condition: identifier specifies an undeclared member variable
    bl_t waive_unknown_member_variable = false;

    // Condition: identifier specifies an undeclared member function
    bl_t waive_unknown_member_function = false;

    // Condition: trans_expression: function identifier is not used in a tractable way (e.g. not as function call).
    bl_t waive_function_in_untraced_context = false;

    // Condition: trans_expression encounters an unknown identifier
    bl_t waive_unknown_identifier = true;

    /// runtime data
    hidden xoico_host*       host;
    hidden xoico_compiler_s* compiler;
    xoico_signature_s => signature;

    /// runtime state

    sz_t level;
    sz_t try_block_level;

    :stack_var_s   stack_var;
    :stack_block_s stack_block;

    bcore_hmap_name_s hmap_name;

    func xoico_cengine.translate;

    func xoico_cengine.is_reserved =
    {
        return o.is_builtin_func( tp_identifier ) ||
               o.is_control_name( tp_identifier ) ||
               tp_identifier == TYPEOF_verbatim_C;
    };

    func :.entypeof = { return o.hmap_name.set_sc( name ); };

    func :.nameof   =
    {
        sc_t name = o.hmap_name.get_sc( type );
        if( !name ) name = o.compiler.nameof( type );
        return name;
    };

    func :.init_level0 =
    {
        o.stack_block.clear();
        o.stack_block.push();
        o.level = 0;
    };

    func :.inc_block =
    {
        o.stack_block.push();
        o->level++;
        o.stack_block_get_top_unit().level = o.level;
    };

    func :.dec_block =
    {
        o.stack_var.pop_level( o->level );
        o.level--;
        ASSERT( o.level >= 0 );
        o.stack_block.pop();
    };

    func :.stack_block_get_top_unit =
    {
        return o.stack_block.adl.[ o.stack_block.adl.size - 1 ];
    };

    func :.stack_block_get_bottom_unit =
    {
        return o.stack_block.adl.[ 0 ];
    };

    func :.stack_block_get_level_unit =
    {
        foreach( m $* e in o.stack_block.adl ) if( e.level == level ) return e;
        ERR_fa( "Level #<sz_t> not found.", level );
        return NULL;
    };

    func :.push_typedecl =
    {
        m :stack_var_unit_s* unit = :stack_var_unit_s!^^;
        unit.level = o->level;
        unit.name = name;
        unit.typespec.copy( typespec );
        o.stack_var.push_unit( unit );
    };

    func :.push_typespec;
    func :.typespec_to_sink =
    {
        m $* result = :result_create_arr()^^;
        o.push_typespec( typespec, result );
        sink.push_sc( result.create_st()^^.sc );
    };

    func xoico_compiler.is_type  = { return o.compiler.is_type( name ); };
    func xoico_compiler.is_group = { return o.compiler.is_group( name ); };
    func xoico_compiler.is_stamp = { return o.compiler.is_stamp( name ); };
    func xoico_compiler.is_func  = { return o.compiler.is_func( name ); };
    func :.is_var = { return o.stack_var.exists( name ); };

    func xoico_compiler.get_group = { return o.compiler.get_group( name ); };
    func xoico_compiler.get_stamp = { return o.compiler.get_stamp( name ); };
    func xoico_compiler.get_func  = { return o.compiler.get_func( name ); };
    func xoico_compiler.get_transient_map = { return o.compiler.get_transient_map( type ); };

    func (bl_t returns_a_value( c @* o )) = { return o.signature.returns_a_value(); };

    func (er_t trans( c @* o, m bcore_source* source, sc_t format, m :result* result )) =
    {
        try( source.parse_em_fa( format ));
        result.push_sc( format );
        return 0;
    };

};

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

/** Inspects name and enrolls it and returns hash;
 *  Detects '$' as TYEPOF_type_deduce
 *  Detects '@' as type of class or group
 *  If no identifier could be detected: Returns 0 and leave source unchanged.
 */
func (:s) (tp_t get_identifier( m @* o, m bcore_source* source, bl_t take_from_source )) =
{
    tp_t tp_identifier = 0;
    if( source.parse_bl( "#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||[0]=='_'||[0]=='@'||[0]=='$'||([0]==':'&&([1]!=' '&&[1]!='\t'&&[1]!='\n'&&[1]!='/')))" ) )
    {
        sz_t source_index = take_from_source ? 0 : source.get_index();
        switch( source.inspect_char() )
        {
            case '@':
            {
                source.get_char();
                m st_s* st_name = st_s!^^;
                st_name.copy_sc( o.nameof( o.host.obj_type() ) );
                if( source.parse_bl( "#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||[0]=='_'||([0]>='0'&&[0]<='9'))" ) )
                {
                    source.parse_fa( "#:name", st_name );
                }
                tp_identifier = o.entypeof( st_name.sc );
            }
            break;

            case '$':
            {
                source.get_char();
                tp_identifier = TYPEOF_type_deduce;
            }
            break;

            case ':':
            {
                o.host.parse_name_tp( source, tp_identifier.1 );
            }
            break;

            default:
            {
                m st_s* st_name = st_s!^^;
                source.parse_fa( "#name", st_name );
                tp_identifier = o.entypeof( st_name.sc );
            }
            break;
        }

        if( !take_from_source ) source.set_index( source_index );
    }

    return tp_identifier;
};

//----------------------------------------------------------------------------------------------------------------------

/** transfers identifier, enrolls it and sets 'tp_identifier' */
func(:s) (er_t trans_identifier( m @* o, m bcore_source* source, m :result* result /* can be NULL */, m tp_t* tp_identifier/* can be NULL */ )) = (try)
{
    tp_t identifier = o.get_identifier( source, true );
    if( !identifier )
    {
        return source.parse_error_fa( "Identifier exected" );
    }
    if( tp_identifier ) tp_identifier.0 = identifier;
    if( result ) result.push_sc( o.nameof( identifier ) );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

/** parses number: (all integer, hex and float encodings)*/
func(:s) (er_t trans_number_literal( m @* o, m bcore_source* source, m :result* result )) = (try)
{
    bl_t hex = false;
    if( source.parse_bl( "#?'0x'" ) )
    {
        result.push_sc( "0x" );
        hex = true;
    }
    else if( source.parse_bl( "#?'0X'" ) )
    {
        result.push_sc( "0X" );
        hex = true;
    }

    if( hex )
    {
        while( source.parse_bl( "#?(([0]>='0'&&[0]<='9')||([0]>='a'&&[0]<='f')||([0]>='A'&&[0]<='F'))" ) )
        {
            result.push_char( source.get_char() );
        }
    }
    else // decimal
    {
        while( source.parse_bl( "#?([0]>='0'&&[0]<='9')" ) )
        {
            result.push_char( source.get_char() );
        }
    }

    bl_t fraction = false;

    if( source.parse_bl( "#?([0]=='.')" ) )
    {
        result.push_char( source.get_char() );
        fraction = true;
    }

    if( fraction )
    {
        while( source.parse_bl( "#?([0]>='0'&&[0]<='9')" ) )
        {
            result.push_char( source.get_char() );
        }
    }

    bl_t exponent = false;

    if( source.parse_bl( "#?([0]=='e'&&[0]=='E')" ) )
    {
        result.push_char( source.get_char() );
        exponent = true;
    }

    if( exponent )
    {
        if( source.parse_bl( "#?([0]=='+'||[0]=='-')" ) )
        {
            result.push_char( source.get_char() );
        }

        while( source.parse_bl( "#?([0]>='0'&&[0]<='9')" ) )
        {
            result.push_char( source.get_char() );
        }
    }

    // suffix
    while( source.parse_bl( "#?([0]=='l'||[0]=='L'||[0]=='u'||[0]=='U'||[0]=='f'||[0]=='F')" ) )
    {
        result.push_char( source.get_char() );
    }

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

/// parses string
func (:s) (er_t trans_string_literal( m @* o, m bcore_source* source, m :result* result )) = (try)
{
    o.trans( source, "\"", result );

    while( !source.eos() && !source.parse_bl( "#=?'\"'" ) )
    {
        if( source.parse_bl( "#?'\\'" ) ) result.push_char( '\\' );
        result.push_char( source.get_char() );
    }

    o.trans( source, "\"", result );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

/// character literal
func (:s) (er_t trans_char_literal( m @* o, m bcore_source* source, m :result* result )) =
{
try
{
    o.trans( source, "'", result );

    while( !source.eos() && !source.parse_bl( "#=?|'|" ) )
    {
        if( source.parse_bl( "#?'\\'" ) ) result.push_char( '\\' );
        result.push_char( source.get_char() );
    }

    o.trans( source, "'", result );
    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

/// parses whitespaces including comments
func (:s) (er_t trans_whitespace( m @* o, m bcore_source* source, m :result* result /* can be NULL */ )) = (try)
{
    bl_t exit_loop = false;
    while( !exit_loop && !source.eos() )
    {
        char c =  source.inspect_char();
        switch( c )
        {
            case ' ' :
            case '\t':
            case '\n':
            {
                char c =  source.get_char();
                if( result )  result.push_char( c );
            }
            break;

            case '/':
            {
                if( source.parse_bl( "#?'//'" ) )
                {
                    if( result ) result.push_sc( "//" );
                    while( !source.eos() )
                    {
                        char c =  source.get_char();
                        if( result ) result.push_char( c );
                        if( c == '\n' ) break;
                    }
                }
                else if( source.parse_bl( "#?'/*'" ) )
                {
                    if( result ) result.push_sc( "/*" );
                    while( !source.eos() )
                    {
                        if( source.parse_bl( "#?'*/'" ) )
                        {
                            if( result ) result.push_sc( "*/" );
                            break;
                        }
                        char c =  source.get_char();
                        if( result ) result.push_char( c );
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
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) (er_t trans_preprocessor( m @* o, m bcore_source* source, m :result* result )) = (try)
{
    source.parse_em_fa( "##" );
    result.push_sc( "#" );
    while( !source.eos() )
    {
        char c = source.get_char();
        result.push_char( c );
        if( c == '\\' && source.inspect_char() == '\n' ) result.push_char( source.get_char() );
        if( c == '\n' ) break;
    }
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

// any state; returns !=0 in case an operator was consumed
func (:s) (tp_t trans_inert_operator( m @* o, m bcore_source* source, m :result* result )) =
{
    switch( source.inspect_char() )
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
            result.push_char( source.get_char() );
            return 1;
        }
        break;

        default: break;
    }

    return false;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) (bl_t trans_operator( m @* o, m bcore_source* source, m :result* result )) =
{
    switch( source.inspect_char() )
    {
        case '+':
        {
            result.push_char( source.get_char() );
            char c = source.inspect_char();
            if( c == '=' || c == '+' ) result.push_char( source.get_char() );
        }
        return true;

        case '-':
        {
            result.push_char( source.get_char() );
            char c = source.inspect_char();
            if( c == '=' || c == '-' ) result.push_char( source.get_char() );
        }
        return true;

        case '*':
        case '/':
        case '=':
        case '!':
        case '^':
        case '%':
        {
            result.push_char( source.get_char() );
            if( source.inspect_char() == '=' ) result.push_char( source.get_char() );
        }
        return true;

        case '>':
        {
            result.push_char( source.get_char() );
            char c = source.inspect_char();
            if( c == '=' || c == '>' ) result.push_char( source.get_char() );
            if( c == '>' && source.inspect_char() == '=' ) result.push_char( source.get_char() );
        }
        return true;

        case '<':
        {
            result.push_char( source.get_char() );
            char c = source.inspect_char();
            if( c == '=' || c == '<' ) result.push_char( source.get_char() );
            if( c == '<' && source.inspect_char() == '=' ) result.push_char( source.get_char() );
        }
        return true;

        case '|':
        {
            result.push_char( source.get_char() );
            char c = source.inspect_char();
            if( c == '=' || c == '|' ) result.push_char( source.get_char() );
        }
        return true;

        case '&':
        {
            result.push_char( source.get_char() );
            char c = source.inspect_char();
            if( c == '=' || c == '&' ) result.push_char( source.get_char() );
        }
        return true;

        case '~':
        {
            result.push_char( source.get_char() );
        }
        return true;

        default: break;
    }

    return false;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s)
(
    er_t adapt_expression_indirection
    (
        m @* o,
        m bcore_source* source,
        c xoico_typespec_s* typespec_expr,
        sz_t target_indirection,
        c :result* result_expr,
        m :result* result
    )
) = (try)
{
    if( target_indirection == typespec_expr.indirection )
    {
        result.push_result_c( result_expr );
    }
    else if( target_indirection == typespec_expr.indirection + 1 )
    {
        if( typespec_expr.flag_addressable )
        {
            result.push_sc( "&(" );
            result.push_result_c( result_expr );
            result.push_sc( ")" );
        }
        else
        {
            return source.parse_error_fa( "Increasing indirection: Expression has no address." );
        }
    }
    else if( target_indirection < typespec_expr.indirection )
    {
        for( sz_t ind = typespec_expr.indirection; ind > target_indirection; ind-- ) result.push_sc( "*" );
        result.push_sc( "(" );
        result.push_result_c( result_expr );
        result.push_sc( ")" );
    }
    else
    {
        return source.parse_error_fa
        (
            "Cannot adapt from expression's indirection '#<sz_t>' to target indirection '#<sz_t>'.",
            typespec_expr.indirection,
            target_indirection
        );
    }
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s)
(
    er_t adapt_expression
    (
        m @* o,
        m bcore_source* source,
        c xoico_typespec_s* typespec_expr,
        c xoico_typespec_s* typespec_target,
        c :result* result_expr,
        m :result* result
    )
) = (try)
{
    if( !typespec_expr.type )
    {
        return source.parse_error_fa
        (
            "xoico_che_s_adapt_expression: no expression type specified.",
            typespec_expr.indirection,
            typespec_target.indirection
        );
    }

    if( !typespec_target.type )
    {
        return source.parse_error_fa
        (
            "xoico_che_s_adapt_expression: no target type specified.",
            typespec_expr.indirection,
            typespec_target.indirection
        );
    }

    if( typespec_target.type == TYPEOF_type_deduce ) return source.parse_error_fa( "adapt_expression: typespec_target is 'type_deduce'" );
    if( typespec_target.type == TYPEOF_type_object ) return source.parse_error_fa( "adapt_expression: typespec_target is 'type_object'" );
    if( typespec_expr.type == TYPEOF_type_deduce ) return source.parse_error_fa( "adapt_expression: typespec_expr is 'type_deduce'" );
    if( typespec_expr.type == TYPEOF_type_object ) return source.parse_error_fa( "adapt_expression: typespec_expr is 'type_object'" );

    bl_t discarding_const =
        ( typespec_expr.access_class == TYPEOF_const && typespec_expr.access_class != typespec_target.access_class ) &&
        ( typespec_expr.indirection > 0 && typespec_target.indirection > 0 );

    if( discarding_const ) return source.parse_error_fa( "Discarding 'const' qualifier." );

    if( typespec_target.access_class == TYPEOF_discardable && typespec_expr.access_class != TYPEOF_discardable )
    {
        return source.parse_error_fa( "Discardable expression expected." );
    }

    if( typespec_expr.converts_to( typespec_target ) )
    {
        result.push_result_c( result_expr );
    }
    else
    {
        bl_t implicit_cast = false;
        m st_s* fail_msg = NULL;
        if( typespec_target.type != typespec_expr.type )
        {
            if( o.is_group( typespec_target.type ) && typespec_target.indirection == 1 )
            {
                if( o.is_group( typespec_expr.type ) )
                {
                    implicit_cast = true;
                }
                else if( o.is_stamp( typespec_expr.type ) )
                {
                    c xoico_stamp_s* stamp = o.get_stamp( typespec_expr.type );
                    if( stamp.is_aware || typespec_target.flag_obliv )
                    {
                        implicit_cast = true;
                    }
                    else
                    {
                        fail_msg = st_s_create_fa( "'#<sc_t>' is obliv but the target typespec does not explicitly tolerate obliv objects.", o.nameof( typespec_expr.type ) )^^;
                    }
                }
                else
                {
                    fail_msg = st_s_create_fa( "Source type cannot be classified." )^^;
                }
            }
            else
            {
                fail_msg = st_s_create_fa( "Target is not a group or target indirection is != 1." )^^;
            }
        }

        if( fail_msg )
        {
            m $* st_typespec_expr = st_s!^^;
            m $* st_typespec_target = st_s!^^;
            o.typespec_to_sink( typespec_expr, st_typespec_expr );
            o.typespec_to_sink( typespec_target, st_typespec_target );
            m $* msg = st_s!^^;
            msg.push_fa( "Implicit cast from '#<sc_t>' to '#<sc_t>' is not allowed. ", st_typespec_expr.sc, st_typespec_target.sc );
            msg.push_fa( "Reason: #<st_s*>\n", fail_msg );
            return source.parse_error_fa( "#<st_s*>", msg );
        }

        if( implicit_cast )
        {
            result.push_sc( "((" );
            o.push_typespec( typespec_target, result );
            result.push_sc( ")(" );
        }
        o.adapt_expression_indirection( source, typespec_expr, typespec_target.indirection, result_expr, result );
        if( implicit_cast ) result.push_sc( "))" );
    }
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) (er_t trans_member( m @* o, m bcore_source* source, m :result* result )) = (try)
{
    if(      source.parse_bl( "#?'.'"  ) ) result.push_sc( "." );
    else if( source.parse_bl( "#?'->'" ) ) result.push_sc( "->" );

    o.trans_whitespace( source, result );

    char c = source.inspect_char();

    if( c == '*' || c == '&' )
    {
        return source.parse_error_fa( "Postfix operators '&' and '*' are deprecated.\n" );
    }

    if( c >= '0' && c <= '9' )
    {
        return source.parse_error_fa( "Setting indirection: Expression not tractable\n" );
    }

    tp_t tp_identifier = o.get_identifier( source, false );

    if( o.is_builtin_func( tp_identifier ) )
    {
        return source.parse_error_fa( "Expression before '#<sc_t>' not tractable\n", o.nameof( tp_identifier ) );
    }

    o.trans_identifier( source, result, NULL );
    o.trans_whitespace( source, result );
    if( source.parse_bl( "#?'('") )
    {
        return source.parse_error_fa( "Untraced member function '#<sc_t>'\n", o.nameof( tp_identifier ) );
    }

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

/** Tests for typespec
 *  If possible, takes typespec from source, otherwise leaves source unchanged
 */
func (:s)
(
    er_t try_take_typespec
    (
        m @* o,
        m bcore_source* source,
        m xoico_typespec_s* typespec,
        bl_t require_tractable_type,
        m bl_t* success
    )
) = (try)
{
    if( success ) success.0 = false;

    sz_t index = source.get_index();

    o.trans_whitespace( source, NULL );
    tp_t tp_identifier = o.get_identifier( source, true );

    if( !tp_identifier )
    {
        source.set_index( index );
        return 0;
    }

    o.trans_whitespace( source, NULL );

    // take fails if identifier is used as function
    if( source.parse_bl( "#?'('" ) )
    {
        source.set_index( index );
        return 0;
    }

    tp_t access_class = 0;

    switch( tp_identifier )
    {
        case TYPEOF_c:
        case TYPEOF_const:
            access_class = TYPEOF_const;
            break;

        case TYPEOF_m:
        case TYPEOF_mutable:
            access_class = TYPEOF_mutable;
            break;

        case TYPEOF_d:
        case TYPEOF_discardable:
            access_class = TYPEOF_discardable;
            break;

        default: break;
    }

    if( access_class )
    {
        tp_identifier = o.get_identifier( source, true );
        if( !tp_identifier )
        {
            source.set_index( index );
            return 0;
        }
        o.trans_whitespace( source, NULL );
    }

    while
    (
        tp_identifier == TYPEOF_static ||
        tp_identifier == TYPEOF_volatile ||
        tp_identifier == TYPEOF_keep
    )
    {
        if( tp_identifier == TYPEOF_static   ) typespec.flag_static   = true;
        if( tp_identifier == TYPEOF_volatile ) typespec.flag_volatile = true;
        if( tp_identifier == TYPEOF_scope    ) typespec.flag_scope    = true;
        o.trans_identifier( source, NULL, tp_identifier );
        o.trans_whitespace( source, NULL );
    }

    typespec.type = tp_identifier;

    if( source.parse_bl( "#?'.' " ) )
    {
        if( !source.parse_bl( "#?([0]>='0'&&[0]<='9') " ) )
        {
            source.set_index( index );
            return 0;
        }

        sz_t indirection = 0;
        source.parse_fa( "#<sz_t*> ", indirection.1 );
        typespec.indirection = indirection;
    }
    else
    {
        while( source.parse_bl( "#?'*' " ) ) typespec.indirection++;
    }

    if( require_tractable_type )
    {
        if( !( tp_identifier == TYPEOF_type_deduce || o.is_type( tp_identifier ) ) )
        {
            source.set_index( index );
            return 0;
        }
    }

    if( source.parse_bl( " #?'^'") ) typespec.flag_scope = true;

    if( source.parse_bl( " #?w'restrict'") ) typespec.flag_restrict = true;

    if( typespec.indirection > 0 && access_class == 0 )
    {
        access_class = TYPEOF_const; // const is default
    }

    typespec.access_class = access_class;

    if( success ) success.0 = true;
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s)
(
    er_t take_typespec
    (
        m @* o,
        m bcore_source* source,
        m xoico_typespec_s* typespec,
        bl_t require_tractable_type
    )
) = (try)
{
    bl_t success = false;
    o.try_take_typespec( source, typespec, require_tractable_type, success );

    if( !success )
    {
        if( require_tractable_type )
        {
            return source.parse_error_fa( "Typespec: Syntax error or intractable type." );
        }
        else
        {
            return source.parse_error_fa( "Typespec: Syntax error." );
        }
    }

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) :.push_typespec  = (try)
{
    tp_t type = typespec.type;

    if( type == TYPEOF_type_object )
    {
        ERR_fa( "Cannot resolve 'type_object' at this point." );
    }
    else if( type == TYPEOF_type_deduce )
    {
        ERR_fa( "Cannot resolve 'type_deduce' at this point." );
    }
    else if( type == 0 )
    {
        ERR_fa( "Type is 0." );
    }

    m st_s* st_type = st_s_create_sc( o.nameof( type ) )^^;

    if( st_type.size == 0 )
    {
        ERR_fa( "Type '#<tp_t>' has no name.", type );
    }

    sc_t sc_type = st_type.sc;
    if( typespec.flag_static   ) result.push_fa( "static " );
    if( typespec.access_class == TYPEOF_const ) result.push_fa( "const " );
    if( typespec.flag_volatile ) result.push_fa( "volatile " );
    result.push_fa( "#<sc_t>", sc_type );

    for( sz_t i = 0; i < typespec.indirection; i++ ) result.push_fa( "*" );
    if( typespec.flag_restrict ) result.push_fa( "restrict " );

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s)
(
    er_t trans_type
    (
        m @* o,
        m bcore_source* source,
        m :result* result, // can be NULL
        m xoico_typespec_s* out_typespec // optional
    )
) = (try)
{
    m $* result_local = :result_create_arr()^^;
    tp_t tp_identifier;
    o.trans_identifier( source, result_local, tp_identifier );
    o.trans_whitespace( source, result_local );
    if( source.parse_bl( "#?'!'" ) )
    {
        if( o.is_group( tp_identifier ) )
        {
            return source.parse_error_fa( "Operator '!': lvalue is a group." );
        }
        result_local.clear();
        result_local.push_fa( "#<sc_t>_create()", o.nameof( tp_identifier ) );

        m xoico_typespec_s* typespec = xoico_typespec_s!^^;
        typespec.type = tp_identifier;
        typespec.indirection = 1;
        typespec.flag_addressable = false;
        typespec.access_class = TYPEOF_discardable;

        if( source.parse_bl( "#=?'^'" ) )
        {
            o.trans_builtin_scope( source, result_local, typespec, result, NULL );
            typespec.access_class = TYPEOF_mutable;
        }
        else
        {
            result.push_result_d( result_local.fork() );
        }

        o.trans_typespec_expression( source, result, typespec, out_typespec );
    }
    else
    {
        result.push_result_d( result_local.fork() );
    }
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s)
(
    er_t trans_ternary_branch
    (
        m @* o,
        m bcore_source* source,
        m :result* result, // can be NULL
        m xoico_typespec_s* out_typespec // optional
    )
) = (try)
{
    source.parse_em_fa( "?" );
    result.push_sc( "?" );
    m xoico_typespec_s* typespec_true  = xoico_typespec_s!^;
    m xoico_typespec_s* typespec_false = xoico_typespec_s!^;

    o.trans_expression( source, result, typespec_true );
    source.parse_em_fa( ": " );
    result.push_sc( ": " );
    o.trans_expression( source, result, typespec_false );

    if( typespec_true.type && typespec_false.type )
    {
        if( typespec_true.type != typespec_false.type )
        {
            source.parse_error_fa
            (
                "Ternary operator: Branches differ in type: ('#<sc_t>' : '#<sc_t>')",
                o.nameof( typespec_true.type ),
                o.nameof( typespec_false.type )
            );
        }

        if( typespec_true.indirection != typespec_false.indirection )
        {
            source.parse_error_fa
            (
                "Ternary operator: Branches differ in levels of indirection: ('#<sz_t>' : '#<sz_t>')",
                typespec_true.indirection,
                typespec_false.indirection
            );
        }
    }

    if( out_typespec && typespec_true.type )
    {
        out_typespec.copy( typespec_true );
        out_typespec.flag_addressable = false;
    }
    return 0;

};

//----------------------------------------------------------------------------------------------------------------------

func (:s)
(
    er_t trans_bracket
    (
        m @* o,
        m bcore_source* source,
        m :result* result, // can be NULL
        m xoico_typespec_s* out_typespec // optional
    )
) = (try)
{
    source.parse_em_fa( "(" );
    result.push_char( '(' );
    while( !source.eos() )
    {
        o.trans_expression( source, result, out_typespec );
        if     ( source.parse_bl( "#?')'" ) ) break;
        else if( source.parse_bl( "#?','" ) ) result.push_char( ',' );
        else return source.parse_error_fa( "Syntax error in bracket expression." );
        if( out_typespec ) out_typespec.type = 0;
    }
    result.push_char( ')' );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s)
(
    er_t trans_array_subscript
    (
        m @* o,
        m bcore_source* source,
        m :result* result, // can be NULL
        m xoico_typespec_s* out_typespec // optional
    )
) = (try)
{
    source.parse_em_fa( "[" );
    result.push_sc( "[" );
    o.trans_expression( source, result, NULL );
    source.parse_em_fa( "]" );
    result.push_sc( "]" );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s)
(
    er_t trans_expression
    (
        m @* o,
        m bcore_source* source,
        m :result* result_out, // can be NULL
        m xoico_typespec_s* out_typespec // optional
    )
) = (try)
{
    sc_t sc_bl_end_of_expression = "#?([0]==';'||[0]=='{'||[0]=='}'||[0]==')'||[0]==']'||[0]==','||([0]=='.'&&[1]=='.')||([0]==':'&&([1]==' '||[1]=='\t'||[1]=='\n'||[1]=='/')))";

    o.trans_whitespace( source, result_out );

    m $* result = :result_create_arr()^^;
    bl_t continuation = true;

    if( out_typespec ) out_typespec.reset();

    tp_t tp_identifier = o.get_identifier( source, false );

    if( tp_identifier )
    {
        // examples of builtin functions: scope, cast, try, fork
        if( o.is_builtin_func( tp_identifier ) )
        {
            m xoico_typespec_s* typespec_builtin = xoico_typespec_s!^^;
            o.trans_builtin( tp_identifier, source, NULL, NULL, result, typespec_builtin );
            o.trans_typespec_expression( source, result, typespec_builtin, out_typespec );
        }

        else if( tp_identifier == TYPEOF_verbatim_C )
        {
            source.parse_em_fa( "verbatim_C {" );
            o.trans_block_inside_verbatim_c( source, result );
            source.parse_em_fa( " }" );
        }

        // a control name marks end of expression...
        else if( o.is_control_name( tp_identifier ) )
        {
            continuation = false;
        }

        // identifier represents a boolean literal
        else if( tp_identifier == TYPEOF_true || tp_identifier == TYPEOF_false )
        {
            o.trans_identifier( source, result, NULL );
            o.trans_whitespace( source, result );
            m $* typespec = xoico_typespec_s!^^;
            typespec.type = TYPEOF_bl_t;
            typespec.indirection = 0;
            typespec.flag_addressable = false;
            o.trans_typespec_expression( source, result, typespec, out_typespec );
        }

        // identifier represents a registered variable
        else if( o.is_var( tp_identifier ) )
        {
            o.trans_identifier( source, result, NULL );
            o.trans_whitespace( source, result );
            c xoico_typespec_s* typespec_var = o.stack_var.get_typespec( tp_identifier );
            o.trans_typespec_expression( source, result, typespec_var, out_typespec );
        }

        // identifier represents a type known to the compiler
        else if( o.is_type( tp_identifier ) )
        {
            o.trans_type( source, result, out_typespec );
        }

        // identifier represents a (global) function name
        else if( o.is_func( tp_identifier ) )
        {
            o.trans_identifier( source, NULL, NULL );
            sz_t source_index = source.get_index();

            if( source.parse_bl( " #=?'('" ) ) // actual function call
            {
                c xoico_func_s* func = o.get_func( tp_identifier );
                m $* typespec_ret = xoico_typespec_s!^^;
                o.trans_function( source, func, NULL, NULL, result, typespec_ret );
                o.trans_typespec_expression( source, result, typespec_ret, out_typespec );
            }
            else // function name used in untraced context
            {
                if( !o.waive_function_in_untraced_context ) return source.parse_error_fa( "Function #<sc_t> used in untraced context.\n.", o.nameof( tp_identifier ) );
                result.push_sc( o.nameof( tp_identifier ) );
                source.set_index( source_index );
                o.trans_whitespace( source, result );
            }
        }
        else // unknown identifier
        {
            if( !o.waive_unknown_identifier ) return source.parse_error_fa( "Unknwon identifier #<sc_t>\n.", o.nameof( tp_identifier ) );
            o.trans_identifier( source, result, NULL );
            o.trans_whitespace( source, result );

            // assume untraced function call: bracket evaluation without internal type evaluation
            if( source.parse_bl( "#=?'('" ) )
            {
                o.trans_bracket( source, result, NULL );
            }
        }
    }

    // end of expression...
    else if( source.parse_bl( sc_bl_end_of_expression ) )
    {
        continuation = false;
    }

    // literals and members
    else if( source.parse_bl( "#?([0]>='0'&&[0]<='9')" ) ) o.trans_number_literal( source, result );
    else if( source.parse_bl( "#=?'\"'" )                ) o.trans_string_literal( source, result );
    else if( source.parse_bl( "#=?|'|" )                 ) o.trans_char_literal( source, result );
    else if( source.parse_bl( "#=?'.'" )                 ) o.trans_member( source, result );
    else if( source.parse_bl( "#=?'->'" )                ) o.trans_member( source, result );

    else if( source.parse_bl( "#=?'=<'" )                ) return source.parse_error_fa( "Attach operator: Expression not tractable." );

    else if( o.trans_inert_operator( source, result )       ) {} // inert operators are not interpreted by che and passed to the c-compiler

    // ternary branch operator
    else if( source.parse_bl( "#=?'?'" ) )
    {
        o.trans_ternary_branch( source, result, out_typespec );
    }

    // general bracket
    else if( source.parse_bl( "#=?'('" ) )
    {
        m xoico_typespec_s* typespec_local = xoico_typespec_s!^^;
        o.trans_bracket( source, result, typespec_local );
        if( typespec_local.type )
        {
            o.trans_typespec_expression( source, result, typespec_local, out_typespec );
        }
    }

    // array subscript
    else if( source.parse_bl( "#=?'['" ) )
    {
        o.trans_array_subscript( source, result, out_typespec );
    }

    // unhandled
    else
    {
        return source.parse_error_fa( "Syntax error after '#<sc_t>'", result.create_st()^^.sc );
    }

    if( continuation )
    {
        if( !source.parse_bl( sc_bl_end_of_expression ) )
        {
            if( out_typespec ) out_typespec.reset();


            o.trans_whitespace( source, result );
            o.trans_operator( source, result );


            o.trans_expression( source, result, NULL );
        }
    }

    if( result_out ) result_out.push_result_d( result.fork() );

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

/** Translates declaration including optional subsequent assignment.
 *  If no declaration was detected, source and result_out are not modified.
 */
func (:s)
(
    er_t try_trans_declaration
    (
        m @* o,
        m bcore_source* source,
        m :result* result_out,
        m bl_t* success
    )
) = (try)
{
    if( success ) success.0 = false;

    m xoico_typespec_s* typespec_var = xoico_typespec_s!^^;

    sz_t index = source.get_index();

    m $* result_var = :result_create_arr()^^;

    bl_t success_take_typespec = false;
    o.try_take_typespec( source, typespec_var, true, success_take_typespec.1 );

    if( !success_take_typespec )
    {
        source.set_index( index );
        return 0;
    }

    o.trans_whitespace( source, result_var );

    if
    (
        typespec_var.type &&
        source.parse_bl( "#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||[0]=='_')" )
    )
    {
        tp_t tp_identifier = 0;
        o.trans_identifier( source, result_var, tp_identifier.1 );
        o.trans_whitespace( source, result_var );

        if( source.parse_bl( "#?'='" ) ) // assignment
        {
            if( typespec_var.flag_scope ) return source.parse_error_fa( "Declaration-syntax: Stack-scope requested with subsequent assignment." );
            bl_t pushed_typedecl = false;
            if( typespec_var.type != TYPEOF_type_deduce )
            {
                o.push_typedecl( typespec_var, tp_identifier );
                pushed_typedecl = true;
            }

            result_var.push_sc( "=" );
            m xoico_typespec_s* typespec_expr = xoico_typespec_s!^^;
            m $* result_expr = :result_create_arr()^^;
            o.trans_expression( source, result_expr, typespec_expr );

            if( typespec_var.type == TYPEOF_type_deduce )
            {
                if( !typespec_expr.type )
                {
                    return source.parse_error_fa( "Declaration-syntax: Deduce requested but expression is intractable." );
                }
                typespec_var.type = typespec_expr.type;
            }

            if( typespec_expr.type )
            {
                if( typespec_expr.access_class != typespec_var.access_class )
                {
                    if( typespec_expr.access_class == TYPEOF_discardable )
                    {
                        return source.parse_error_fa( "Declaration-syntax: Assignment: Conversion discards typespec 'discardable'." );
                    }

                    if( typespec_var.access_class == TYPEOF_discardable )
                    {
                        return source.parse_error_fa( "Declaration-syntax: Assignment: Conversion requires typespec 'discardable'." );
                    }
                }
                o.adapt_expression( source, typespec_expr, typespec_var, result_expr, result_var );
            }
            else
            {
                result_var.push_result_d( result_expr.fork() );
            }
            o.push_typespec( typespec_var, result_out );
            result_out.push_char( ' ' );
            result_out.push_result_d( result_var.fork() );
            if( !pushed_typedecl ) o.push_typedecl( typespec_var, tp_identifier );
        }
        else if( typespec_var.type == TYPEOF_type_deduce )
        {
            return source.parse_error_fa( "Declaration-syntax: Deduce requested without assignment." );
        }
        else if( source.parse_bl( "#=?'['" ) ) // c-style array
        {
            if( typespec_var.flag_scope ) return source.parse_error_fa( "Declaration-syntax: Stack-scope requested on C-style array." );
            o.push_typespec( typespec_var, result_out );
            while( source.parse_bl( "#?'['" ) )
            {
                result_var.push_char( '[' );
                o.trans_expression( source, result_var, NULL );
                source.parse_em_fa( "]" );
                result_var.push_char( ']' );
                typespec_var.indirection++;
            }
            result_out.push_char( ' ' );
            result_out.push_result_d( result_var.fork() );
            o.push_typedecl( typespec_var, tp_identifier );
        }
        else
        {
            o.push_typespec( typespec_var, result_out );
            result_out.push_char( ' ' );
            result_out.push_result_d( result_var.fork() );
            o.push_typedecl( typespec_var, tp_identifier );

            if( typespec_var.flag_scope )
            {
                result_out.push_char( ';' );
                result_out.push_fa( "BLM_T_INIT_SPUSH(#<sc_t>, &#<sc_t>);", o.nameof( typespec_var.type ), o.nameof( tp_identifier ) );
                o.stack_block.adl.[ o.level ].use_blm = true;

                // debug
                if( !source.parse_bl( " #=?';'" ) )
                {
                    m $* result_local = :result_arr_s!^;
                    result_local.push_fa( "#<sc_t>", o.nameof( tp_identifier ) );
                    o.trans_typespec_expression( source, result_local, typespec_var, NULL );
                    result_out.push_result_d( result_local.fork() );
                }
            }
        }

        if( success ) success.0 = true;
    }
    else
    {
        source.set_index( index );
        return 0;
    }

    if( success ) success.0 = true;

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func(:s) (er_t inspect_expression( m @* o, m bcore_source* source )) = (try)
{
    source.parse_em_fa( "\?\?" );

    m $* st = st_s!^^;
    m $* result_local = :result_create_arr()^^;
    m xoico_typespec_s* typespec = xoico_typespec_s!^^;
    source.parse_em_fa( " #until';' ", st );
    source.parse_em_fa( ";" );
    bcore_msg_fa( " \?? #<sc_t>;\n", st.sc );
    if( o.trans_expression( bcore_source_string_s_create_fa( "#<st_s*>;", st )^^, result_local, typespec ) )
    {
        bcore_error_pop_to_sink( BCORE_STDOUT );
        bcore_msg_fa( "\n" );
    }
    else
    {
        if( st.size == 0 ) return source.parse_error_fa( "Variable name expected." );
        bcore_msg_fa( "--> #<sc_t>;\n", result_local.create_st()^^.sc );

        if( typespec.type )
        {
            bcore_msg_fa( "Expression yields typespec:\n" );
            bcore_msg_fa( "  access_class : #<sc_t>\n",  ifnameof( typespec.access_class ) );
            bcore_msg_fa( "  type         : #<sc_t>\n", o.nameof( typespec.type ) );
            bcore_msg_fa( "  indirection  : #<sz_t>\n", typespec.indirection );
        }
        else
        {
            bcore_msg_fa( "Expression does not yield a typespec.\n" );
        }
    }
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) (er_t trans_statement_expression( m @* o, m bcore_source* source, m :result* result )) = (try)
{
    if( o.try_block_level > 0 )
    {
        m xoico_typespec_s* typespec = xoico_typespec_s!^^;
        m $* result_expr = :result_create_arr()^^;
        o.trans_expression( source, result_expr, typespec );
        if
        (
            ( typespec.type == TYPEOF_er_t ) &&
            ( typespec.indirection == 0 ) &&
            ( typespec.flag_addressable == false )
        )
        {
            if( !source.parse_bl( " #?';'" ) )
            {
                return source.parse_error_fa( "Inside a try-block: Expressions yielding 'er_t' must end with ';'" );
            }
            result.push_sc( "BLM_TRY(" );
            result.push_result_d( result_expr.fork() );
            result.push_sc( ")" );
        }
        else
        {
            result.push_result_d( result_expr.fork() );
        }
    }
    else
    {
        o.trans_expression( source, result, NULL );
    }

    o.trans_whitespace( source, result );

    // ':' between expressions is to be taken literally
    if( source.parse_bl( "#?':'" ) ) result.push_char( ':' );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) (er_t trans_statement( m @* o, m bcore_source* source, m :result* result )) = (try)
{
    o.trans_whitespace( source, result );

//    if( source.parse_bl( "#?([0]=='{'||[0]=='#'||[0]==';'||[0]==','||[0]=='.'||[0]==')'||[0]=='}'||([0]=='?'&&[1]=='?'))" ) )
//    {

    bl_t handled = true;

    char c = source.inspect_char();
    switch( c )
    {
        case '{':
        {
            o.trans_block( source, result, false );
        }
        break;

        case '#':
        {
            o.trans_preprocessor( source, result );
        }
        break;

        case ';': /// consume semicolon
        {
            source.get_char();
            result.push_char( ';' );
        }
        break;

        case ',':
        {
            source.get_char();
            result.push_char( ',' );
        }
        break;

        case '?':
        {
            if( source.parse_bl( "#?([1]=='?')" ) )
            {
                o.inspect_expression( source );
            }
            else
            {
                handled = false;
            }
        }
        break;

        case ')':
        {
            return source.parse_error_fa( "Unmatched closing bracket." );
        }
        break;

        case '.':
        {
            return source.parse_error_fa( "Incorrect use of delimiter '.'." );
        }
        break;

        case '}':
        {
            // nothing (caller is a block-handler)
        }
        break;

        default:
        {
            handled = false;
        }
        break;
    }

    if( !handled )
    {
        tp_t tp_identifier = o.get_identifier( source, false );

        if( tp_identifier && o.is_control_name( tp_identifier ) )
        {
            o.trans_control( tp_identifier, source, result );
        }
        else
        {
            bl_t success_declaration = false;
            o.try_trans_declaration( source, result, success_declaration.1 );
            if( !success_declaration ) o.trans_statement_expression( source, result );
        }
    }

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) (er_t trans_block_inside( m @* o, m bcore_source* source, m :result* result_out )) = (try)
{
    m $* result = :result_create_arr()^^;

    while( !source.parse_bl( "#=?'}'" ) && !source.eos() )
    {
        o.trans_statement( source, result );
    }

    if( o.stack_block_get_top_unit().use_blm )
    {
        m $* result_block = :result_create_block( o.level, true )^^;

        result_block.push_result_d( :result_create_blm_init( o.level ) );
        result_block.push_result_d( result.fork() );

        if( ( o.level > 0 ) || !o.returns_a_value() )
        {
            result_block.push_result_d( :result_create_blm_down() );
        }

        result_out.push_result_d( result_block.fork() );
    }
    else
    {
        result_out.push_result_d( result.fork() );
    }

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) (er_t trans_block( m @* o, m bcore_source* source, m :result* result_out, bl_t is_break_ledge )) = (try)
{
    o.inc_block();
    m $* result = :result_create_arr()^^;
    o.stack_block_get_top_unit().break_ledge = is_break_ledge;
    o.trans_whitespace( source, result );
    o.trans( source, "{", result );
    o.trans_block_inside( source, result );
    o.trans_whitespace( source, result );
    o.trans( source, "}", result );
    result_out.push_result_d( result.fork() );
    o.dec_block();
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) (er_t trans_statement_as_block( m @* o, m bcore_source* source, m :result* result_out, bl_t is_break_ledge )) = (try)
{
    m $* result = :result_create_arr()^^;

    o.inc_block();
    o.stack_block_get_top_unit().break_ledge = is_break_ledge;

    o.trans_statement( source, result );
    o.trans_whitespace( source, result );
    if( source.parse_bl( "#?';'" ) ) result.push_sc( ";" );

    if( o.stack_block_get_top_unit().use_blm )
    {
        m $* result_block = :result_create_block( o.level, true )^^;
        result_block.push_result_d( :result_create_blm_init( o.level ) );
        result_block.push_result_d( result.fork() );
        result_block.push_result_d( :result_create_blm_down() );

        result_out.push_sc( "{" );
        result_out.push_result_d( result_block.fork() );
        result_out.push_sc( "}" );
    }
    else
    {
        result_out.push_result_d( result.fork() );
    }

    o.dec_block();
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) (er_t trans_block_inside_verbatim_c( m @* o, m bcore_source* source, m :result* result )) = (try)
{
    o.trans_whitespace( source, result );
    while( !source.parse_bl( "#=?'}'" ) && !source.eos() )
    {
        switch( source.inspect_char() )
        {
            case '"':
            {
                o.trans_string_literal( source, result );
            }
            break;

            case '\'':
            {
                o.trans_char_literal( source, result );
            }
            break;

            case '{':
            {
                result.push_char( source.get_char() );
                o.trans_block_inside_verbatim_c( source, result );
                source.parse_em_fa( "}" );
                result.push_char( '}' );
            }
            break;

            default:
            {
                result.push_char( source.get_char() );
            }
            break;
        }
        o.trans_whitespace( source, result );
    }
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) (er_t setup( m @* o, c xoico_host* host, c xoico_signature_s* signature )) = (try)
{
    o.signature =< signature.clone();
    o.signature.relent( host, host.obj_type() );

    o.host     = host.cast( m $* );
    o.compiler = host.compiler();
    o.level    = 0;
    o.try_block_level = 0;
    o.stack_var.clear();
    o.init_level0();

    if( o.signature.arg_o )
    {
        m $* unit = xoico_che_stack_var_unit_s!^^;
        tp_t tp_member_obj_name  = o.entypeof( "o" );
        unit.typespec.copy( o.signature.arg_o.typespec );
        unit.name = tp_member_obj_name;
        unit.level = o.level;
        o.stack_var.push_unit( unit );
        o.hmap_name.set_sc( o.compiler.nameof( o.signature.arg_o.typespec.type ) );
        o.hmap_name.set_sc( o.compiler.nameof( tp_member_obj_name ) );
    }

    foreach( m $* arg in o.signature.args )
    {
        if( arg.typespec.type && arg.name )
        {
            m $* unit = xoico_che_stack_var_unit_s!^^;
            unit.typespec.copy( arg.typespec );
            unit.name = arg.name;
            unit.level = o.level;
            o.stack_var.push_unit( unit );
            o.hmap_name.set_sc( o.compiler.nameof( arg.typespec.type ) );
            o.hmap_name.set_sc( o.compiler.nameof( arg.name ) );
        }
    }
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) (sz_t assess_indentation( m bcore_source* source )) =
{
    sz_t index = source.get_index();
    while( !source.eos() ) if( source.get_char() == '\n' ) break;
    sz_t indentation = 0;
    while( !source.eos() )
    {
        if( source.get_char() != ' ' ) break;
        indentation++;
    }
    source.set_index( index );
    return indentation;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) (void remove_indentation( m st_s* string, sz_t indentation )) =
{
    ASSERT( string.space >= string.size );

    sz_t j = 0;
    for( sz_t i = 0; i < string.size; i++ )
    {
        char c = string.[ i ];
        string.[ j++ ] = c;
        if( c == '\n' )
        {
            for( sz_t k = 0; k < indentation; k++ )
            {
                if( string.[ i + 1 ] != ' ' ) break;
                i++;
            }
        }
    }

    string.[ j ] = 0;
    string.size = j;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) (er_t translate_mutable( m @* o, c xoico_host* host, c xoico_body_s* body, c xoico_signature_s* signature, m bcore_sink* sink )) = (try)
{
    o.setup( host, signature );

    m bcore_source* source = body.code.source_point.clone_source()^^;

    m $* result = :result_create_arr()^^;

    bl_t flag_verbatim_c = false;
    bl_t flag_try = false;

    if( source.parse_bl( " #?'('" ) )
    {
        while( !source.parse_bl( " #?')'" ) )
        {
            if( source.parse_bl( " #?w'try'" ) )
            {
                if( o.signature.typespec_ret.type != TYPEOF_er_t || o.signature.typespec_ret.indirection != 0 )
                {
                    return source.parse_error_fa( "Operator 'try': This operator can only be used in functions returning 'er_t'." );
                }
                flag_try = true;
            }
            else if( source.parse_bl( " #?w'verbatim_C'" ) )
            {
                flag_verbatim_c = true;
            }
            else
            {
                return source.parse_error_fa( "Invalid c-engine expression." );
            }
        }
    }

    source.parse_em_fa( " {" );
    sz_t indentation = 0;
    if( !body.go_inline ) indentation = o.assess_indentation( source );

    if( flag_verbatim_c )
    {
        o.trans_block_inside_verbatim_c( source, result );
    }
    else
    {
        o.try_block_level += flag_try;
        o.trans_block_inside( source, result );
        o.try_block_level -= flag_try;
    }
    source.parse_em_fa( " }" );

    m $* result_block = :result_create_block( o.level, o.stack_block_get_bottom_unit().use_blm )^^;
    result_block.cast( m :result_block_s* ).is_root = true;
    result_block.push_result_d( result.fork() );

    m st_s* buf = st_s!^^;
    result_block.to_sink( buf );

    //remove trailing whitespaces
    for( sz_t i = buf.size - 1; i >= 0; i-- )
    {
        if( buf.[ i ] != ' ' && buf.[ i ] != '\t' && buf.[ i ] != '\n' ) break;
        buf.[ i ] = 0;
        buf.size = i;
    }

    if( o.insert_source_reference && !body.code.single_line )
    {
        sink.push_fa( "// " );
        body.code.source_point.source_reference_to_sink( true, sink );
        sink.push_fa( "\n" );
    }

    if( indentation > 0 ) o.remove_indentation( buf, indentation );

    if( o.verbose )
    {
        bcore_sink_a_push_fa( BCORE_STDOUT, "##############################\n" );
        bcore_sink_a_push_fa( BCORE_STDOUT, "#<st_s*>\n", buf );
    }

    sink.push_sc( buf.sc );

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) xoico_cengine.translate =
{
    er_t er = o.clone()^^.translate_mutable( host, body, signature, sink );
    return er;
};

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

embed "xoico_che_trans_typespec.x";
embed "xoico_che_function.x";
embed "xoico_che_builtin.x";
embed "xoico_che_control.x";

/**********************************************************************************************************************/

