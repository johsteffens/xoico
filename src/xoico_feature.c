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

#include "xoico_feature.h"
#include "xoico_group.h"
#include "xoico_compiler.h"

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

sc_t xoico_feature_s_get_global_name_sc( const xoico_feature_s* o )
{
    return xoico_compiler_s_nameof( xoico_group_s_get_compiler( o->group ), o->signature.global_name );
}

//----------------------------------------------------------------------------------------------------------------------

tp_t xoico_feature_s_get_hash( const xoico_feature_s* o )
{
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
    hash = bcore_tp_fold_tp( hash, xoico_signature_s_get_hash( &o->signature ) );

    if( o->default_body )
    {
        hash = bcore_tp_fold_tp( hash, xoico_body_s_get_hash( o->default_body ) );
    }

    hash = bcore_tp_fold_u0( hash, o->strict ? 1 : 0 );
    hash = bcore_tp_fold_u0( hash, o->flag_p ? 1 : 0 );
    hash = bcore_tp_fold_u0( hash, o->flag_t ? 1 : 0 );
    hash = bcore_tp_fold_u0( hash, o->flag_a ? 1 : 0 );
    hash = bcore_tp_fold_u0( hash, o->flag_r ? 1 : 0 );
    return hash;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_feature_s_parse( xoico_feature_s* o, bcore_source* source )
{
    BLM_INIT();

    xoico_compiler_s* compiler = xoico_group_s_get_compiler( o->group );

    bcore_source_point_s_set( &o->source_point, source );

    o->strict = bcore_source_a_parse_bl_fa(  source, " #?w'strict' " );

    if( bcore_source_a_parse_bl_fa( source, " #?|'|" ) )
    {
        BLM_INIT();
        st_s* flags = BLM_CREATE( st_s );
        XOICO_BLM_SOURCE_PARSE_FA(  source, " #until'''", flags );
        for( sz_t i = 0; i < flags->size; i++ )
        {
            switch( flags->data[ i ] )
            {
                case 'p': o->flag_p = true; break;
                case 't': o->flag_t = true; break;
                case 'a': o->flag_a = true; break;
                case 'r': o->flag_r = true; break;
                default: XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Feature: Flag '#<char>' not handled. Choose from 'ptar'.", flags->data[ i ] ); break;
            }
        }
        XOICO_BLM_SOURCE_PARSE_FA( source, "' " );
        BLM_DOWN();
    }
    else
    {
        /// the default feature is an aware one
        o->flag_a = true;
    }

    xoico_signature_s* signature = &o->signature;

    signature->group = o->group;
    BLM_TRY( xoico_signature_s_parse( signature, source ) );

    if( !signature->arg_o )
    {
        XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Feature: The first argument must be 'mutable' or 'const'." );
    }

    if( bcore_source_a_parse_bl_fa( source, " #?'=' " ) )
    {
        if( bcore_source_a_parse_bl_fa( source, " #=?'{' " ) )
        {
            if( o->strict ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Feature is 'strict'. Default function would have no effect." );
            o->default_body = xoico_body_s_create();
            BLM_TRY( xoico_body_s_set_group( o->default_body, o->group ) );
            bcore_source_point_s_set( &o->default_body->source_point, source );
            BLM_TRY( xoico_body_s_parse_expression( o->default_body, source ) );
            st_s_copy_fa( &o->st_default_func_name, "#<sc_t>_default", xoico_compiler_s_nameof( compiler, o->signature.name ) );
        }
        else
        {
            if( o->strict )  XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Feature is 'strict'. Default function would have no effect." );
            XOICO_BLM_SOURCE_PARSE_FA( source, " #name ", &o->st_default_func_name );
            if( o->st_default_func_name.size == 0 ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Feature: Default function name expected." );
            if( st_s_equal_sc( &o->st_default_func_name, xoico_compiler_s_nameof( compiler, o->signature.name ) ) )
            {
                XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Feature: Default function name must differ from feature name." );
            }
        }
    }

    XOICO_BLM_SOURCE_PARSE_FA( source, " ; " );

    st_s* name_buf = BLM_CREATE( st_s );

    sc_t sc_name = xoico_compiler_s_nameof( compiler, o->signature.name );
    sc_t sc_group_name = o->group->st_name.sc;

    if( o->flag_a )
    {
        o->func_a = xoico_func_s_create();
        o->func_a->group = o->group;
        o->func_a->name = o->signature.name;
        st_s_copy_fa( name_buf, "#<sc_t>_a_#<sc_t>", sc_group_name, sc_name );
        o->func_a->global_name = xoico_compiler_s_entypeof( compiler, name_buf->sc );
        o->func_a->signature_global_name = o->signature.global_name;
        o->func_a->expandable = false;
        bcore_source_point_s_copy( &o->func_a->source_point, &o->source_point );
        xoico_compiler_s_register_func( compiler, o->func_a, source );
    }

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_feature_s_expand_indef_typedef( const xoico_feature_s* o, sz_t indent, bcore_sink* sink )
{
    if( !o->expandable ) return 0;
    BLM_INIT();

    xoico_compiler_s* compiler = xoico_group_s_get_compiler( o->group );

    bcore_sink_a_push_fa( sink, " \\\n#rn{ }  typedef ", indent );

    xoico_typespec_s_expand( &o->signature.typespec_ret, o->group, o->group->st_name.sc, sink );

    bcore_sink_a_push_fa( sink, " (*#<sc_t>_#<sc_t>)(", o->group->st_name.sc, xoico_compiler_s_nameof( compiler, o->signature.name ) );

    if( o->signature.arg_o == TYPEOF_const ) bcore_sink_a_push_fa( sink, " const" );
    bcore_sink_a_push_fa( sink, " #<sc_t>* o", o->group->st_name.sc );
    BLM_TRY( xoico_args_s_expand( &o->signature.args, false, o->group->st_name.sc, sink ) );
    bcore_sink_a_push_fa( sink, " );" );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_feature_s_expand_spect_declaration( const xoico_feature_s* o, sz_t indent, bcore_sink* sink )
{
    if( !o->expandable ) return 0;
    xoico_compiler_s* compiler = xoico_group_s_get_compiler( o->group );
    bcore_sink_a_push_fa( sink, " \\\n#rn{ }#<sc_t> #<sc_t>;", indent, xoico_compiler_s_nameof( compiler, o->signature.global_name ), xoico_compiler_s_nameof( compiler, o->signature.name ) );
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_feature_s_expand_spect_definition( const xoico_feature_s* o, sz_t indent, bcore_sink* sink )
{
    if( !o->expandable ) return 0;
    xoico_compiler_s* compiler = xoico_group_s_get_compiler( o->group );
    bcore_sink_a_push_fa( sink, "#rn{ }\"feature ", indent );
    if( o->strict ) bcore_sink_a_push_fa( sink, "strict " );
    if( o->flag_a ) bcore_sink_a_push_fa( sink, "aware " );

    bcore_sink_a_push_fa( sink, "#<sc_t> : #<sc_t>", o->group->st_name.sc, xoico_compiler_s_nameof( compiler, o->signature.name ) );
    if( o->st_default_func_name.size > 0 )
    {
        bcore_sink_a_push_fa( sink, " = #<sc_t>_#<sc_t>", o->group->st_name.sc, o->st_default_func_name.sc );
    }
    bcore_sink_a_push_fa( sink, ";\"\n" );
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_feature_s_expand_indef_declaration( const xoico_feature_s* o, sz_t indent, bcore_sink* sink )
{
    if( !o->expandable ) return 0;
    BLM_INIT();
    xoico_compiler_s* compiler = xoico_group_s_get_compiler( o->group );

    sc_t sc_name         = xoico_compiler_s_nameof( compiler, o->signature.name );
    sc_t sc_group_name   = o->group->st_name.sc;

    st_s* st_ret_typespec = BLM_CREATE( st_s );
    st_s* st_spect_name = BLM_A_PUSH( xoico_group_s_create_spect_name( o->group ) );
    sc_t  sc_spect_name = st_spect_name->sc;

    xoico_typespec_s_expand( &o->signature.typespec_ret, o->group, sc_group_name, ( bcore_sink* )st_ret_typespec );
    bl_t has_ret = ( o->signature.typespec_ret.type != TYPEOF_void );

    sc_t sc_ret_typespec = st_ret_typespec->sc;
    sc_t sc_default_func_name = o->st_default_func_name.sc;
    bl_t flag_const = o->signature.arg_o == TYPEOF_const;

    if( o->flag_p )
    {
        bcore_sink_a_push_fa
        (
            sink,
            " \\\n#rn{ }  static inline #<sc_t> #<sc_t>_p_#<sc_t>( const #<sc_t>* __p,",
            indent,
            sc_ret_typespec,
            sc_group_name,
            sc_name,
            sc_spect_name
        );

        if( flag_const ) bcore_sink_a_push_fa( sink, " const" );
        bcore_sink_a_push_fa( sink, " #<sc_t>* o", sc_group_name );
        BLM_TRY( xoico_args_s_expand( &o->signature.args, false, sc_group_name, sink ) );
        bcore_sink_a_push_fa( sink, " ) { " );
        bcore_sink_a_push_fa( sink, "assert( __p->#<sc_t> ); ", sc_name );
        if( has_ret ) bcore_sink_a_push_fa( sink, "return " );
        bcore_sink_a_push_fa( sink, "__p->#<sc_t>( o", sc_name );
        BLM_TRY( xoico_args_s_expand_name( &o->signature.args, false, sink ) );
        bcore_sink_a_push_fa( sink, " ); }" );
    }

    if( o->flag_t )
    {
        bcore_sink_a_push_fa
        (
            sink,
            " \\\n#rn{ }  static inline #<sc_t> #<sc_t>_t_#<sc_t>( tp_t __t,",
            indent,
            sc_ret_typespec,
            sc_group_name,
            sc_name,
            sc_group_name
        );

        if( flag_const ) bcore_sink_a_push_fa( sink, " const" );
        bcore_sink_a_push_fa( sink, " #<sc_t>* o", sc_group_name );
        BLM_TRY( xoico_args_s_expand( &o->signature.args, false, sc_group_name, sink ) );
        bcore_sink_a_push_fa( sink, " ) { " );
        bcore_sink_a_push_fa( sink, "const #<sc_t>* p = #<sc_t>_get_typed( __t ); ", sc_spect_name, sc_spect_name );
        bcore_sink_a_push_fa( sink, "assert( p->#<sc_t> ); ", sc_name );
        if( has_ret ) bcore_sink_a_push_fa( sink, "return " );
        bcore_sink_a_push_fa( sink, "p->#<sc_t>( o", sc_name );
        BLM_TRY( xoico_args_s_expand_name( &o->signature.args, false, sink ) );
        bcore_sink_a_push_fa( sink, " ); }" );
    }

    if( o->flag_a )
    {
        bcore_sink_a_push_fa
        (
            sink,
            " \\\n#rn{ }  static inline #<sc_t> #<sc_t>_a_#<sc_t>(",
            indent,
            sc_ret_typespec,
            sc_group_name,
            sc_name
        );

        if( flag_const ) bcore_sink_a_push_fa( sink, " const" );
        bcore_sink_a_push_fa( sink, " #<sc_t>* o", sc_group_name );
        BLM_TRY( xoico_args_s_expand( &o->signature.args, false, sc_group_name, sink ) );
        bcore_sink_a_push_fa( sink, " ) { " );
        bcore_sink_a_push_fa( sink, "const #<sc_t>* p = #<sc_t>_get_aware( o ); ", sc_spect_name, sc_spect_name );
        bcore_sink_a_push_fa( sink, "assert( p->#<sc_t> ); ", sc_name );
        if( has_ret ) bcore_sink_a_push_fa( sink, "return " );
        bcore_sink_a_push_fa( sink, "p->#<sc_t>( o", sc_name );
        BLM_TRY( xoico_args_s_expand_name( &o->signature.args, false, sink ) );
        bcore_sink_a_push_fa( sink, " ); }" );
    }

    if( o->flag_r )
    {
        bcore_sink_a_push_fa
        (
            sink,
            " \\\n#rn{ }  static inline #<sc_t> #<sc_t>_r_#<sc_t>(",
            indent,
            sc_ret_typespec,
            sc_group_name,
            sc_name
        );

        bcore_sink_a_push_fa( sink, " const sr_s* o" );
        BLM_TRY( xoico_args_s_expand( &o->signature.args, false, sc_group_name, sink ) );
        bcore_sink_a_push_fa( sink, " ) { " );
        if( !flag_const ) bcore_sink_a_push_fa( sink, "ASSERT( !sr_s_is_const( o ) ); ", indent );
        bcore_sink_a_push_fa
        (
            sink,
            "const #<sc_t>* p = (const #<sc_t>*)ch_spect_p( o->p, TYPEOF_#<sc_t> ); ",
            sc_spect_name,
            sc_spect_name,
            sc_spect_name
        );

        bcore_sink_a_push_fa( sink, "assert( p->#<sc_t> ); ", sc_name );
        if( has_ret ) bcore_sink_a_push_fa( sink, "return " );
        bcore_sink_a_push_fa( sink, "p->#<sc_t>( o->o", sc_name );
        BLM_TRY( xoico_args_s_expand_name( &o->signature.args, false, sink ) );
        bcore_sink_a_push_fa( sink, " ); }" );
    }

    if( o->flag_p )
    {
        bcore_sink_a_push_fa
        (
            sink,
            " \\\n#rn{ }  static inline bl_t #<sc_t>_p_defines_#<sc_t>( const #<sc_t>* __p ) ",
            indent,
            sc_group_name,
            sc_name,
            sc_spect_name
        );

        if( o->strict || o->default_body || o->st_default_func_name.size > 0 )
        {
            bcore_sink_a_push_fa( sink, "{ return true; }", sc_name );
        }
        else
        {
            bcore_sink_a_push_fa( sink, "{ return __p->#<sc_t> != NULL; }", sc_name );
        }
    }

    if( o->flag_t )
    {
        bcore_sink_a_push_fa
        (
            sink,
            " \\\n#rn{ }  static inline bl_t #<sc_t>_t_defines_#<sc_t>( tp_t __t ) ",
            indent,
            sc_group_name,
            sc_name
        );

        if( o->strict || o->default_body || o->st_default_func_name.size > 0 )
        {
            bcore_sink_a_push_fa( sink, "{ return true; }", sc_name );
        }
        else
        {
            bcore_sink_a_push_fa( sink, "{ return #<sc_t>_get_typed( __t )->#<sc_t> != NULL; }", sc_spect_name, sc_name );
        }
    }

    if( o->flag_a )
    {
        bcore_sink_a_push_fa
        (
            sink,
            " \\\n#rn{ }  static inline bl_t #<sc_t>_a_defines_#<sc_t>( const #<sc_t>* o ) ",
            indent,
            sc_group_name,
            sc_name,
            sc_group_name
        );

        if( o->strict || o->default_body || o->st_default_func_name.size > 0 )
        {
            bcore_sink_a_push_fa( sink, "{ return true; }", sc_name );
        }
        else
        {
            bcore_sink_a_push_fa( sink, "{ return #<sc_t>_get_aware( o )->#<sc_t> != NULL; }", sc_spect_name, sc_name );
        }
    }

    if( o->flag_r )
    {
        bcore_sink_a_push_fa
        (
            sink,
            " \\\n#rn{ }  static inline bl_t #<sc_t>_r_defines_#<sc_t>( const sr_s* o ) ",
            indent,
            sc_group_name,
            sc_name
        );

        if( o->strict || o->default_body || o->st_default_func_name.size > 0 )
        {
            bcore_sink_a_push_fa( sink, "{ return true; }", sc_name );
        }
        else
        {
            bcore_sink_a_push_fa( sink, "{ return ( (#<sc_t>*)ch_spect_p( o->p, TYPEOF_#<sc_t> ) )->#<sc_t> != NULL; }", sc_spect_name, sc_spect_name, sc_name );
        }
    }

    if( o->st_default_func_name.size > 0 )
    {
        if( o->default_body && o->default_body->go_inline )
        {
            bcore_sink_a_push_fa
            (
                sink,
                " \\\n#rn{ }  static inline #<sc_t> #<sc_t>_#<sc_t>(",
                indent,
                sc_ret_typespec,
                sc_group_name,
                sc_default_func_name
            );

            if( flag_const ) bcore_sink_a_push_fa( sink, " const" );
            bcore_sink_a_push_fa( sink, " #<sc_t>* o", sc_group_name );
            BLM_TRY( xoico_args_s_expand( &o->signature.args, false, sc_group_name, sink ) );
            bcore_sink_a_push_fa( sink, " )" );
            BLM_TRY( xoico_body_s_expand( o->default_body, &o->signature, indent, sink ) );
        }
        else
        {
            bcore_sink_a_push_fa( sink, " \\\n#rn{ }  #<sc_t> #<sc_t>_#<sc_t>(", indent, sc_ret_typespec, sc_group_name, sc_default_func_name );
            if( flag_const ) bcore_sink_a_push_fa( sink, " const" );
            bcore_sink_a_push_fa( sink, " #<sc_t>* o", sc_group_name );
            BLM_TRY( xoico_args_s_expand( &o->signature.args, false, sc_group_name, sink ) );
            bcore_sink_a_push_fa( sink, " );" );
        }
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_feature_s_expand_definition( const xoico_feature_s* o, sz_t indent, bcore_sink* sink )
{
    if( !o->expandable ) return 0;
    BLM_INIT();
    if( o->default_body && !o->default_body->go_inline )
    {
        sc_t sc_group_name = o->group->st_name.sc;
        st_s* st_ret_typespec = BLM_CREATE( st_s );
        xoico_typespec_s_expand( &o->signature.typespec_ret, o->group, sc_group_name, ( bcore_sink* )st_ret_typespec );

        bcore_sink_a_push_fa( sink, "\n" );
        bcore_sink_a_push_fa( sink, "\n#<sc_t> #<sc_t>_#<sc_t>(", st_ret_typespec->sc, sc_group_name, o->st_default_func_name.sc );
        if( o->signature.arg_o == TYPEOF_const ) bcore_sink_a_push_fa( sink, " const" );
        bcore_sink_a_push_fa( sink, " #<sc_t>* o", sc_group_name );
        BLM_TRY( xoico_args_s_expand( &o->signature.args, false, sc_group_name, sink ) );
        bcore_sink_a_push_fa( sink, " )\n" );
        BLM_TRY( xoico_body_s_expand( o->default_body, &o->signature, indent, sink ) );
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_feature_s_expand_init1( const xoico_feature_s* o, sz_t indent, bcore_sink* sink )
{
    if( !o->expandable ) return 0;
    xoico_compiler_s* compiler = xoico_group_s_get_compiler( o->group );
    sc_t sc_global_name = xoico_compiler_s_nameof( compiler, o->signature.global_name );

    bcore_sink_a_push_fa( sink, "#rn{ }BCORE_REGISTER_FEATURE( #<sc_t> );\n", indent, sc_global_name );
    if( o->st_default_func_name.size > 0 )
    {
        bcore_sink_a_push_fa
        (
            sink,
            "#rn{ }BCORE_REGISTER_FFUNC( #<sc_t>, #<sc_t>_#<sc_t> );\n",
            indent,
            sc_global_name,
            o->group->st_name.sc,
            o->st_default_func_name.sc
        );
    }
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

