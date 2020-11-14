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
{ try {
    if( !o.group ) return source.parse_error_fa( "xoico_body_code_s: Code has no group assigned." );

    tp_t hash = bcore_tp_init();

    o.source_point.set( source );

    try( source.parse_em_fa( " {" ) );

    sz_t nest_count = 1;
    bl_t exit_loop = false;
    o.single_line = true;

    while( source.parse_bl_fa( "#?' '" ) ); // skip leading spaces

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
                    if( c == '\n' ) return source.parse_error_fa( "Newline in string literal." );
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
                    if( c == '\n' ) return source.parse_error_fa( "Newline in char literal." );
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
                            o.single_line = false;
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
                            if( c == '\n' ) o.single_line = false;
                            hash = bcore_tp_fold_u0( hash, c );
                        }
                    }
                }
                c = 0;
            }
            break;

            case '\n' :
            {
                o.single_line = false;
                break;
            }

            default: break;
        }
        hash = bcore_tp_fold_u0( hash, c );
    }

    o.hash_source = hash;
    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:code) xoico.get_hash =
{
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o._ );
    hash = bcore_tp_fold_tp( hash, o.hash_source );
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
    hash = bcore_tp_fold_bl( hash, o.go_inline );
    return hash;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) :.parse_expression =
{ try {
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
        $* st_name = st_s!.scope();
        o.group.parse_name( st_name, source );

        if( st_name.size == 0 ) return source.parse_error_fa( "Body name expected." );

        if( o.stamp ) st_name.replace_sc_sc( "@", o.stamp.st_name.sc );

        tp_t tp_name = compiler.entypeof( st_name.sc );

        // if name_buf refers to another body
        if( compiler.is_item( tp_name ) )
        {
            const xoico* item = compiler.get_const_item( tp_name );
            if( item._ == TYPEOF_xoico_body_s )
            {
                const $* body = item.cast( xoico_body_s* );
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
            return source.parse_error_fa( "Cannot resolve body name '#<sc_t>'\n", st_name.sc );
        }
    }
    return 0;

} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:) :.parse =
{ try {
    if( !o.group ) return source.parse_error_fa( "Body has no group assigned." );
    st_s* string = st_s!.scope();
    o.source_point.set( source );

    if( !source.parse_bl_fa( " #=?'='" ) )
    {
        try( source.parse_em_fa( " #name", string ) );
        if( string.size == 0 ) return source.parse_error_fa( "Body name expected." );
        o.name.push_fa( "#<sc_t>", string.sc );
    }

    try( source.parse_em_fa( " =" ) );
    o.parse_expression( source );
    o.global_name.copy_fa( "#<sc_t>_#<sc_t>", o.group.st_name.sc, o.name.sc );
    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

func (:) :.expand =
{ try {
    const st_s* final_code = NULL;
    st_s* st_out = st_s!.scope();

    xoico_cengine* cengine = o.group.xoico_source.target.cengine;
    ASSERT( cengine );

    if( o.code )
    {
        if( !o.group ) return o.source_point.parse_error_fa( "Body has no group assigned." );
        cengine.translate( o, signature, ( bcore_sink* )st_out );
        final_code = st_out;
    }

    if( o.go_inline )
    {
        sink.push_fa( "{#<sc_t>}", final_code.sc );
    }
    else
    {
        sink.push_fa( "{\n#rn{ }", indent + 4 );
        for( sz_t i = 0; i < final_code.size; i++ )
        {
            char c = final_code.sc[ i ];
            sink.push_char( c );
            if( c == '\n' ) sink.push_fa( "#rn{ }", indent + 4 );
        }
        sink.push_fa( "\n#rn{ }}", indent );
    }
    return 0;
} /* try */ };

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
