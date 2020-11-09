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

func (:code) :.parse =
{
try
{
    if( !o.group ) return source.parse_err_to_em_fa( TYPEOF_parse_error, "xoico_body_code_s: Code has no group assigned." );

    tp_t hash = bcore_tp_init();

    o.source_point.set( source );

    try( source.parse_em_fa( " {" ) );

    sz_t nest_count = 1;
    bl_t exit_loop = false;
    o.single_line = true;
    o.indentation = 0;

    while( source.parse_bl_fa( "#?' '" ) ); // skip leading spaces
    if( source.parse_bl_fa( "#?'\n'" ) )
    {
        o.single_line = false;
        while( source.parse_bl_fa( "#?' '" ) ) o.indentation++;
    }

    while( !source.eos() && !exit_loop )
    {
        u0_t c =  source.get_u0();
        switch( c )
        {
            case '{':
            {
                nest_count++;
            }
            break;

            case '}':
            {
                nest_count--;
                if( !nest_count )
                {
                    c = 0;
                    exit_loop = true;
                }
            }
            break;

            case '"': // string literal
            {
                hash = bcore_tp_fold_u0( hash, c );
                while( !source.eos() && ((c = source.get_char()) != '"') )
                {
                    hash = bcore_tp_fold_u0( hash, c );
                    if( c == '\\' ) hash = bcore_tp_fold_u0( hash, source.get_u0() );
                    if( c == '\n' ) return source.parse_err_to_em_fa( TYPEOF_parse_error, "Newline in string literal." );
                }
                c = 0;
            }
            break;

            case '\'': // char literal
            {
                hash = bcore_tp_fold_u0( hash, c );
                while( !source.eos() && ((c = source.get_char()) != '\'') )
                {
                    hash = bcore_tp_fold_u0( hash, c );
                    if( c == '\\' ) hash = bcore_tp_fold_u0( hash, bcore_source_a_get_u0( source ) );
                    if( c == '\n' ) return source.parse_err_to_em_fa( TYPEOF_parse_error, "Newline in char literal." );
                }
                c = 0;
            }
            break;

            case '/': // comment
            {
                hash = bcore_tp_fold_u0( hash, c );
                if( source.inspect_char() == '/' )
                {
                    while( !source.eos() )
                    {
                        c = source.get_char();
                        hash = bcore_tp_fold_u0( hash, c );
                        if( c == '\n' )
                        {
                            for( sz_t i = 0; i < o.indentation; i++ ) { if( ! source.parse_bl_fa( "#?' '" ) ) break; };
                            break;
                        }
                    }
                }
                else if( source.inspect_char() == '*' )
                {
                    while( !source.eos() )
                    {
                        if( source.parse_bl_fa( "#?'*/'" ) )
                        {
                            hash = bcore_tp_fold_sc( hash, "*/" );
                            break;
                        }
                        else
                        {
                            c = source.get_char();
                            hash = bcore_tp_fold_u0( hash, c );
                            if( c == '\n' )
                            {
                                for( sz_t i = 0; i < o.indentation; i++ ) { if( !source.parse_bl_fa( "#?' '" ) ) break; };
                            }
                        }
                    }
                }
                c = 0;
            }
            break;

            case '\n' :
            {
                o->single_line = false;
                for( sz_t i = 0; i < o.indentation; i++ ) { if( !source.parse_bl_fa( "#?' '" ) ) break; };
                break;
            }

            default: break;
        }
        hash = bcore_tp_fold_u0( hash, c );
    }

    o->hash_source = hash;
    return 0;
} // try
};

//----------------------------------------------------------------------------------------------------------------------

func (:code) xoico.get_hash =
{
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
    hash = bcore_tp_fold_tp( hash, o->hash_source );
    return hash;
};

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

func (:) :.set_group =
{
    if( !o.group ) o.group = group;
    if( o.code && !o.code.group ) o.code.group = group;
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) :.set_stamp =
{
    o.stamp = stamp;
    if( o.code ) o.code.stamp = stamp;
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) xoico.get_hash =
{
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o._ );
    hash = bcore_tp_fold_sc( hash, o.name.sc );
    if( o.code ) hash = bcore_tp_fold_tp( hash, o.code.get_hash() );
    hash = bcore_tp_fold_bl( hash, o->go_inline );
    return hash;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) :.parse_expression =
{
try
{
    if( source.parse_bl_fa( " #=?'{'" ) )
    {
        o.code =< xoico_body_code_s!;
        o.code.group = o.group;
        o.code.stamp = o.stamp;
        o.code.parse( source );
        o.go_inline = o.code.single_line;
    }
    else
    {
        xoico_compiler_s* compiler = o.group.compiler;
        st_s* st_name = st_s!.scope( scope_local );
        o.group.parse_name( st_name, source );

        if( st_name.size == 0 ) return source.parse_err_to_em_fa( TYPEOF_parse_error, "Body name expected." );

        if( o.stamp ) st_name.replace_sc_sc( "@", o.stamp.st_name.sc );

        tp_t tp_name = compiler.entypeof( st_name->sc );

        // if name_buf refers to another body
        if( compiler.is_item( tp_name ) )
        {
            const xoico* item = compiler.get_const_item( tp_name );
            if( item._ == TYPEOF_xoico_body_s )
            {
                const xoico_body_s* body = item.cast( xoico_body_s* );
                o.code =< body.code.clone();
                if( o.code )
                {
                    o.code.group = body.code.group;
                    o.code.stamp = body.code.stamp;
                }
                o.go_inline = body.go_inline;
            }
        }
        else
        {
            return source.parse_err_to_em_fa( TYPEOF_parse_error, "Cannot resolve body name '#<sc_t>'\n", st_name.sc );
        }
    }
    return 0;

} // try
};

//----------------------------------------------------------------------------------------------------------------------

