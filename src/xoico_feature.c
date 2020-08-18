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

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

sc_t xoico_feature_s_get_global_name_sc( const xoico_feature_s* o )
{
    return o->global_name.sc;
}

//----------------------------------------------------------------------------------------------------------------------

tp_t xoico_feature_s_get_hash( const xoico_feature_s* o )
{
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
    hash = bcore_tp_fold_sc( hash, o->global_name.sc );
    hash = bcore_tp_fold_sc( hash, o->default_name.sc );
    if( o->default_body )
    {
        hash = bcore_tp_fold_tp( hash, xoico_body_s_get_hash( o->default_body ) );
    }

    hash = bcore_tp_fold_u0( hash, o->strict ? 1 : 0 );
    hash = bcore_tp_fold_u0( hash, o->flag_p ? 1 : 0 );
    hash = bcore_tp_fold_u0( hash, o->flag_t ? 1 : 0 );
    hash = bcore_tp_fold_u0( hash, o->flag_a ? 1 : 0 );
    hash = bcore_tp_fold_u0( hash, o->flag_r ? 1 : 0 );

    hash = bcore_tp_fold_u0( hash, o->has_ret ? 1 : 0 );
    hash = bcore_tp_fold_sc( hash, o->ret_type.sc );
    hash = bcore_tp_fold_tp( hash, xoico_args_s_get_hash( &o->args ) );
    hash = bcore_tp_fold_u0( hash, o->mutable ? 1 : 0 );
    return hash;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_feature_s_parse( xoico_feature_s* o, bcore_source* source )
{
    BLM_INIT();

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
        XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Feature: '<flags>' expected. Example: 'ptar'" );
    }

    xoico_signature_s* signature = BLM_CREATE( xoico_signature_s );

    signature->group = o->group;
    BLM_TRY( xoico_signature_s_parse( signature, source ) );
    st_s_copy( &o->name, &signature->name );
    o->has_ret = signature->has_ret;
    st_s_copy( &o->ret_type, &signature->ret_type );
    xoico_args_s_copy( &o->args, &signature->args );

    if( !signature->arg_o )
    {
        XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Feature: The first argument must be 'mutable' or 'const'." );
    }

    o->mutable = ( signature->arg_o == TYPEOF_mutable );

    if( bcore_source_a_parse_bl_fa( source, " #?'=' " ) )
    {
        if( bcore_source_a_parse_bl_fa( source, " #=?'{' " ) )
        {
            if( o->strict ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Feature is 'strict'. Default function would have no effect." );
            o->default_body = xoico_body_s_create();
            BLM_TRY( xoico_body_s_set_group( o->default_body, o->group ) );
            bcore_source_point_s_set( &o->default_body->source_point, source );
            BLM_TRY( xoico_body_s_parse_expression( o->default_body, source ) );
            st_s_copy_fa( &o->default_name, "#<sc_t>__", o->name.sc );
        }
        else
        {
            if( o->strict )  XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Feature is 'strict'. Default function would have no effect." );
            XOICO_BLM_SOURCE_PARSE_FA( source, " #name ", &o->default_name );
            if( o->default_name.size == 0 ) XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Feature: Default function name expected." );
            if( st_s_equal_st( &o->default_name, &o->name ) )
            {
                XOICO_BLM_SOURCE_PARSE_ERR_FA( source, "Feature: Default function name must differ from feature name." );
            }
        }
    }

    XOICO_BLM_SOURCE_PARSE_FA( source, " ; " );

    st_s_copy_fa( &o->global_name, "#<sc_t>_#<sc_t>", o->group->name.sc, o->name.sc );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_feature_s_expand_indef_typedef( const xoico_feature_s* o, sz_t indent, bcore_sink* sink )
{
    BLM_INIT();
    bcore_sink_a_push_fa( sink, " \\\n#rn{ }  typedef #<sc_t> (*#<sc_t>_#<sc_t>)(", indent, o->ret_type.sc, o->group->name.sc, o->name.sc );
    if( !o->mutable ) bcore_sink_a_push_fa( sink, " const" );
    bcore_sink_a_push_fa( sink, " #<sc_t>* o", o->group->name.sc );
    BLM_TRY( xoico_args_s_expand( &o->args, false, sink ) );
    bcore_sink_a_push_fa( sink, " );" );
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_feature_s_expand_spect_declaration( const xoico_feature_s* o, sz_t indent, bcore_sink* sink )
{
    bcore_sink_a_push_fa( sink, " \\\n#rn{ }#<sc_t> #<sc_t>;", indent, o->global_name.sc, o->name.sc );
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_feature_s_expand_spect_definition( const xoico_feature_s* o, sz_t indent, bcore_sink* sink )
{
    bcore_sink_a_push_fa( sink, "#rn{ }\"feature ", indent );
    if( o->strict ) bcore_sink_a_push_fa( sink, "strict " );
    if( o->flag_a ) bcore_sink_a_push_fa( sink, "aware " );

    bcore_sink_a_push_fa( sink, "#<sc_t> : #<sc_t>", o->group->name.sc, o->name.sc );
    if( o->default_name.size > 0 )
    {
        bcore_sink_a_push_fa( sink, " = #<sc_t>_#<sc_t>", o->group->name.sc, o->default_name.sc );
    }
    bcore_sink_a_push_fa( sink, ";\"\n" );
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_feature_s_expand_indef_declaration( const xoico_feature_s* o, sz_t indent, bcore_sink* sink )
{
    BLM_INIT();
    if( o->flag_p )
    {
        // static inline ret_t feature_p_func( const spect* __p, feature* o, arg_t arg1 ) { assert( __p->func ); return __p->func( o, arg1 ); }
        bcore_sink_a_push_fa( sink, " \\\n#rn{ }  static inline #<sc_t> #<sc_t>_p_#<sc_t>( const #<sc_t>_s* __p,", indent, o->ret_type.sc, o->group->name.sc, o->name.sc, o->group->name.sc );
        if( !o->mutable ) bcore_sink_a_push_fa( sink, " const" );
        bcore_sink_a_push_fa( sink, " #<sc_t>* o", o->group->name.sc );
        BLM_TRY( xoico_args_s_expand( &o->args, false, sink ) );
        bcore_sink_a_push_fa( sink, " ) { " );
        bcore_sink_a_push_fa( sink, "assert( __p->#<sc_t> ); ", o->name.sc );
        if( o->has_ret ) bcore_sink_a_push_fa( sink, "return " );
        bcore_sink_a_push_fa( sink, "__p->#<sc_t>( o", o->name.sc );
        BLM_TRY( xoico_args_s_expand_name( &o->args, false, sink ) );
        bcore_sink_a_push_fa( sink, " ); }" );
    }

    if( o->flag_t )
    {
        // static inline ret_t feature_t_func( tp_t __t, feature* o, arg_t arg1 ) { features_s* p = features_s_get_typed( __t ); assert( p->func ); return features_s_get_typed( __t )->func( o, arg1 ); }
        bcore_sink_a_push_fa( sink, " \\\n#rn{ }  static inline #<sc_t> #<sc_t>_t_#<sc_t>( tp_t __t,", indent, o->ret_type.sc, o->group->name.sc, o->name.sc, o->group->name.sc );
        if( !o->mutable ) bcore_sink_a_push_fa( sink, " const" );
        bcore_sink_a_push_fa( sink, " #<sc_t>* o", o->group->name.sc );
        BLM_TRY( xoico_args_s_expand( &o->args, false, sink ) );
        bcore_sink_a_push_fa( sink, " ) { " );
        bcore_sink_a_push_fa( sink, "const #<sc_t>_s* p = #<sc_t>_s_get_typed( __t ); ", o->group->name.sc, o->group->name.sc );
        bcore_sink_a_push_fa( sink, "assert( p->#<sc_t> ); ", o->name.sc );
        if( o->has_ret ) bcore_sink_a_push_fa( sink, "return " );
        bcore_sink_a_push_fa( sink, "p->#<sc_t>( o", o->name.sc );
        BLM_TRY( xoico_args_s_expand_name( &o->args, false, sink ) );
        bcore_sink_a_push_fa( sink, " ); }" );
    }

    if( o->flag_a )
    {
        // static inline ret_t feature_a_func( feature* o, arg_t arg1 ) { const features_s* p = features_s_get_aware( o ); assert( p->func ); return p->func( o, arg1 ); }
        bcore_sink_a_push_fa( sink, " \\\n#rn{ }  static inline #<sc_t> #<sc_t>_a_#<sc_t>(", indent, o->ret_type.sc, o->group->name.sc, o->name.sc );
        if( !o->mutable ) bcore_sink_a_push_fa( sink, " const" );
        bcore_sink_a_push_fa( sink, " #<sc_t>* o", o->group->name.sc );
        BLM_TRY( xoico_args_s_expand( &o->args, false, sink ) );
        bcore_sink_a_push_fa( sink, " ) { " );
        bcore_sink_a_push_fa( sink, "const #<sc_t>_s* p = #<sc_t>_s_get_aware( o ); ", o->group->name.sc, o->group->name.sc );
        bcore_sink_a_push_fa( sink, "assert( p->#<sc_t> ); ", o->name.sc );
        if( o->has_ret ) bcore_sink_a_push_fa( sink, "return " );
        bcore_sink_a_push_fa( sink, "p->#<sc_t>( o", o->name.sc );
        BLM_TRY( xoico_args_s_expand_name( &o->args, false, sink ) );
        bcore_sink_a_push_fa( sink, " ); }" );
    }

    if( o->flag_r )
    {
        // static inline ret_t feature_r_func( const sr_s* o, arg_t arg1 ) { const features_s* p = (const features_s*)ch_spect_p( o->p, TYPEOF_feature_s ) ); assert( p->func ); return p->func( o->o, arg1 ); }
        bcore_sink_a_push_fa( sink, " \\\n#rn{ }  static inline #<sc_t> #<sc_t>_r_#<sc_t>(", indent, o->ret_type.sc, o->group->name.sc, o->name.sc );
        bcore_sink_a_push_fa( sink, " const sr_s* o" );
        BLM_TRY( xoico_args_s_expand( &o->args, false, sink ) );
        bcore_sink_a_push_fa( sink, " ) { " );
        if( o->mutable ) bcore_sink_a_push_fa( sink, "ASSERT( !sr_s_is_const( o ) ); ", indent );
        bcore_sink_a_push_fa( sink, "const #<sc_t>_s* p = (const #<sc_t>_s*)ch_spect_p( o->p, TYPEOF_#<sc_t>_s ); ", o->group->name.sc, o->group->name.sc, o->group->name.sc );
        bcore_sink_a_push_fa( sink, "assert( p->#<sc_t> ); ", o->name.sc );
        if( o->has_ret ) bcore_sink_a_push_fa( sink, "return " );
        bcore_sink_a_push_fa( sink, "p->#<sc_t>( o->o", o->name.sc );
        BLM_TRY( xoico_args_s_expand_name( &o->args, false, sink ) );
        bcore_sink_a_push_fa( sink, " ); }" );
    }

    if( o->flag_p )
    {
        // static inline bl_t feature_p_defines_func( const spect* __p ) { return __p->func != NULL; }
        bcore_sink_a_push_fa( sink, " \\\n#rn{ }  static inline bl_t #<sc_t>_p_defines_#<sc_t>( const #<sc_t>_s* __p ) ", indent, o->group->name.sc, o->name.sc, o->group->name.sc );
        if( o->strict || o->default_body || o->default_name.size > 0 )
        {
            bcore_sink_a_push_fa( sink, "{ return true; }", o->name.sc );
        }
        else
        {
            bcore_sink_a_push_fa( sink, "{ return __p->#<sc_t> != NULL; }", o->name.sc );
        }
    }

    if( o->flag_t )
    {
        // static inline bl_t feature_t_defines_func( tp_t __t ) { return features_s_get_typed( __t )->func != NULL; }
        bcore_sink_a_push_fa( sink, " \\\n#rn{ }  static inline bl_t #<sc_t>_t_defines_#<sc_t>( tp_t __t ) ", indent, o->group->name.sc, o->name.sc );
        if( o->strict || o->default_body || o->default_name.size > 0 )
        {
            bcore_sink_a_push_fa( sink, "{ return true; }", o->name.sc );
        }
        else
        {
            bcore_sink_a_push_fa( sink, "{ return #<sc_t>_s_get_typed( __t )->#<sc_t> != NULL; }", o->group->name.sc, o->name.sc );
        }
    }

    if( o->flag_a )
    {
        // static inline bl_t feature_a_defines_func( const feature* o) { return features_s_get_aware( o )->func != NULL; }
        bcore_sink_a_push_fa( sink, " \\\n#rn{ }  static inline bl_t #<sc_t>_a_defines_#<sc_t>( const #<sc_t>* o ) ", indent, o->group->name.sc, o->name.sc, o->group->name.sc );
        if( o->strict || o->default_body || o->default_name.size > 0 )
        {
            bcore_sink_a_push_fa( sink, "{ return true; }", o->name.sc );
        }
        else
        {
            bcore_sink_a_push_fa( sink, "{ return #<sc_t>_s_get_aware( o )->#<sc_t> != NULL; }", o->group->name.sc, o->name.sc );
        }
    }

    if( o->flag_r )
    {
        // static inline bl_t feature_r_defines_func( const feature* o) { return features_s_get_typed( o->o_type )->func != NULL; }
        bcore_sink_a_push_fa( sink, " \\\n#rn{ }  static inline bl_t #<sc_t>_r_defines_#<sc_t>( const sr_s* o ) ", indent, o->group->name.sc, o->name.sc );
        if( o->strict || o->default_body || o->default_name.size > 0 )
        {
            bcore_sink_a_push_fa( sink, "{ return true; }", o->name.sc );
        }
        else
        {
            bcore_sink_a_push_fa( sink, "{ return ( (#<sc_t>_s*)ch_spect_p( o->p, TYPEOF_#<sc_t>_s ) )->#<sc_t> != NULL; }", o->group->name.sc, o->group->name.sc, o->name.sc );
        }
    }

    if( o->default_name.size > 0 )
    {
        if( o->default_body && o->default_body->go_inline )
        {
            // ret_t feature_default( feature* o, arg_t arg1 );
            bcore_sink_a_push_fa( sink, " \\\n#rn{ }  static inline #<sc_t> #<sc_t>_#<sc_t>(", indent, o->ret_type.sc, o->group->name.sc, o->default_name.sc );
            if( !o->mutable ) bcore_sink_a_push_fa( sink, " const" );
            bcore_sink_a_push_fa( sink, " #<sc_t>* o", o->group->name.sc );
            BLM_TRY( xoico_args_s_expand( &o->args, false, sink ) );
            bcore_sink_a_push_fa( sink, " )" );
            BLM_TRY( xoico_body_s_expand( o->default_body, o->ret_type.sc, o->group->name.sc, &o->args, indent, sink ) );
        }
        else
        {
            // ret_t feature_default( feature* o, arg_t arg1 );
            bcore_sink_a_push_fa( sink, " \\\n#rn{ }  #<sc_t> #<sc_t>_#<sc_t>(", indent, o->ret_type.sc, o->group->name.sc, o->default_name.sc );
            if( !o->mutable ) bcore_sink_a_push_fa( sink, " const" );
            bcore_sink_a_push_fa( sink, " #<sc_t>* o", o->group->name.sc );
            BLM_TRY( xoico_args_s_expand( &o->args, false, sink ) );
            bcore_sink_a_push_fa( sink, " );" );
        }
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_feature_s_expand_definition( const xoico_feature_s* o, sz_t indent, bcore_sink* sink )
{
    BLM_INIT();
    if( o->default_body && !o->default_body->go_inline )
    {
        // ret_t feature_default( feature* o, arg_t arg1 );
        bcore_sink_a_push_fa( sink, "\n" );
        bcore_sink_a_push_fa( sink, "\n#<sc_t> #<sc_t>_#<sc_t>(", o->ret_type.sc, o->group->name.sc, o->default_name.sc );
        if( !o->mutable ) bcore_sink_a_push_fa( sink, " const" );
        bcore_sink_a_push_fa( sink, " #<sc_t>* o", o->group->name.sc );
        BLM_TRY( xoico_args_s_expand( &o->args, false, sink ) );
        bcore_sink_a_push_fa( sink, " )\n" );
        BLM_TRY( xoico_body_s_expand( o->default_body, o->ret_type.sc, o->group->name.sc, &o->args, indent, sink ) );
    }
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_feature_s_expand_init1( const xoico_feature_s* o, sz_t indent, bcore_sink* sink )
{
    bcore_sink_a_push_fa( sink, "#rn{ }BCORE_REGISTER_FEATURE( #<sc_t> );\n", indent, o->global_name.sc );
    if( o->default_name.size > 0 )
    {
        bcore_sink_a_push_fa( sink, "#rn{ }BCORE_REGISTER_FFUNC( #<sc_t>, #<sc_t>_#<sc_t> );\n", indent, o->global_name.sc, o->group->name.sc, o->default_name.sc );
    }
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

