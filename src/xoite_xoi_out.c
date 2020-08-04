/** This file was generated from beth-plant source code.
 *  Compiling Agent : xoite_compiler (C) 2020 J.B.Steffens
 *  Last File Update: 2020-08-03T19:55:29Z
 *
 *  Copyright and License of this File:
 *
 *  Generated code inherits the copyright and license of the underlying beth-plant source code.
 *  Source code defining this file is distributed across following files:
 *
 *  xoite.h
 *  xoite_name.h
 *  xoite_forward.h
 *  xoite_arg.h
 *  xoite_args.h
 *  xoite_signature.h
 *  xoite_body.h
 *  xoite_feature.h
 *  xoite_func.h
 *  xoite_funcs.h
 *  xoite_group.h
 *  xoite_stamp.h
 *  xoite_nested_group.h
 *  xoite_source.h
 *  xoite_target.h
 *  xoite_compiler.h
 *  xoite_builder.h
 *
 */

#include "xoite_xoi_out.h"
#include "bcore_spect.h"
#include "bcore_spect_inst.h"
#include "bcore_sr.h"
#include "bcore_const_manager.h"


/**********************************************************************************************************************/
// source: xoite.h
#include "xoite.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoite

BCORE_DEFINE_SPECT( bcore_inst, xoite )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/
// source: xoite_name.h
#include "xoite_name.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoite_name

BCORE_DEFINE_OBJECT_INST_P( xoite_name_s )
"aware xoite_name"
"{"
    "st_s name;"
    "private aware xoite_group_s* group;"
    "bcore_source_point_s source_point;"
    "func xoite:parse;"
    "func xoite:get_hash;"
    "func xoite:get_global_name_sc;"
    "func xoite:expand_declaration;"
    "func xoite:expand_init1;"
"}";

/**********************************************************************************************************************/
// source: xoite_forward.h
#include "xoite_forward.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoite_forward

BCORE_DEFINE_OBJECT_INST_P( xoite_forward_s )
"aware xoite_forward"
"{"
    "st_s name;"
    "private aware xoite_group_s* group;"
    "bcore_source_point_s source_point;"
    "func xoite:parse;"
    "func xoite:get_hash;"
    "func xoite:get_global_name_sc;"
    "func xoite:expand_declaration;"
    "func xoite:expand_forward;"
    "func xoite:expand_init1;"
"}";

/**********************************************************************************************************************/
// source: xoite_arg.h
#include "xoite_arg.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoite_arg

BCORE_DEFINE_OBJECT_INST_P( xoite_arg_s )
"aware xoite_arg"
"{"
    "st_s type;"
    "st_s name;"
    "private aware xoite_group_s* group;"
    "bcore_source_point_s source_point;"
    "func xoite:parse;"
    "func xoite:get_hash;"
"}";

/**********************************************************************************************************************/
// source: xoite_args.h
#include "xoite_args.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoite_args

BCORE_DEFINE_OBJECT_INST_P( xoite_args_s )
"aware xoite_args"
"{"
    "xoite_arg_s [];"
    "private aware xoite_group_s* group;"
    "func xoite:parse;"
    "func xoite:get_hash;"
"}";

/**********************************************************************************************************************/
// source: xoite_signature.h
#include "xoite_signature.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoite_signature

BCORE_DEFINE_OBJECT_INST_P( xoite_signature_s )
"aware xoite_signature"
"{"
    "st_s name;"
    "st_s global_name;"
    "bl_t has_ret;"
    "st_s ret_type;"
    "xoite_args_s args;"
    "tp_t arg_o;"
    "private aware xoite_group_s* group;"
    "bcore_source_point_s source_point;"
    "func xoite:parse;"
    "func xoite:get_hash;"
    "func xoite:get_global_name_sc;"
"}";

/**********************************************************************************************************************/
// source: xoite_body.h
#include "xoite_body.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoite_body

BCORE_DEFINE_OBJECT_INST_P( xoite_body_s )
"aware xoite_body"
"{"
    "st_s name;"
    "st_s global_name;"
    "st_s code;"
    "bl_t go_inline;"
    "private aware xoite_group_s* group;"
    "bcore_source_point_s source_point;"
    "func xoite:get_hash;"
    "func xoite:get_global_name_sc;"
"}";

/**********************************************************************************************************************/
// source: xoite_feature.h
#include "xoite_feature.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoite_feature

BCORE_DEFINE_OBJECT_INST_P( xoite_feature_s )
"aware xoite_feature"
"{"
    "st_s name;"
    "st_s global_name;"
    "st_s default_name;"
    "xoite_body_s => default_body;"
    "bl_t strict;"
    "bl_t flag_p;"
    "bl_t flag_t;"
    "bl_t flag_a;"
    "bl_t flag_r;"
    "bl_t has_ret;"
    "st_s ret_type;"
    "xoite_args_s args;"
    "bl_t mutable;"
    "private aware xoite_group_s* group;"
    "bcore_source_point_s source_point;"
    "func xoite:parse;"
    "func xoite:get_hash;"
    "func xoite:get_global_name_sc;"
    "func xoite:expand_indef_typedef;"
    "func xoite:expand_spect_declaration;"
    "func xoite:expand_indef_declaration;"
    "func xoite:expand_definition;"
    "func xoite:expand_init1;"
"}";

/**********************************************************************************************************************/
// source: xoite_func.h
#include "xoite_func.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoite_func

BCORE_DEFINE_OBJECT_INST_P( xoite_func_s )
"aware xoite_func"
"{"
    "st_s name;"
    "st_s decl;"
    "tp_t type;"
    "bl_t overloadable = false;"
    "xoite_body_s => body;"
    "private aware xoite_group_s* group;"
    "bcore_source_point_s source_point;"
"}";

/**********************************************************************************************************************/
// source: xoite_funcs.h
#include "xoite_funcs.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoite_funcs

BCORE_DEFINE_OBJECT_INST_P( xoite_funcs_s )
"aware xoite_funcs"
"{"
    "xoite_func_s => [];"
"}";

/**********************************************************************************************************************/
// source: xoite_group.h
#include "xoite_group.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoite_group

BCORE_DEFINE_OBJECT_INST_P( xoite_group_s )
"aware xoite_group"
"{"
    "aware xoite => [];"
    "st_s name;"
    "private xoite_group_s* group;"
    "st_s trait_name = \"bcore_inst\";"
    "tp_t hash;"
    "bl_t expandable = true;"
    "bl_t has_features;"
    "bl_t is_aware;"
    "bl_t retrievable;"
    "private xoite_stamp_s -> extending;"
    "xoite_funcs_s funcs;"
    "private aware xoite_source_s* source;"
    "bcore_source_point_s source_point;"
    "func xoite:parse;"
    "func xoite:get_hash;"
    "func xoite:get_global_name_sc;"
    "func xoite:finalize;"
"}";

/**********************************************************************************************************************/
// source: xoite_stamp.h
#include "xoite_stamp.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoite_stamp

BCORE_DEFINE_OBJECT_INST_P( xoite_stamp_s )
"aware xoite_stamp"
"{"
    "st_s name;"
    "st_s trait_name;"
    "st_s => self_source;"
    "xoite_funcs_s funcs;"
    "private aware xoite_group_s* group;"
    "bcore_source_point_s source_point;"
    "func xoite:get_hash;"
    "func xoite:get_global_name_sc;"
    "func xoite:finalize;"
    "func xoite:expand_declaration;"
    "func xoite:expand_forward;"
    "func xoite:expand_indef_declaration;"
    "func xoite:expand_definition;"
    "func xoite:expand_init1;"
"}";

/**********************************************************************************************************************/
// source: xoite_nested_group.h
#include "xoite_nested_group.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoite_nested_group

BCORE_DEFINE_OBJECT_INST_P( xoite_nested_group_s )
"aware xoite_nested_group"
"{"
    "private xoite_group_s* group;"
    "func xoite:get_hash;"
    "func xoite:expand_forward;"
    "func xoite:expand_indef_declaration;"
"}";

/**********************************************************************************************************************/
// source: xoite_source.h
#include "xoite_source.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoite_source

BCORE_DEFINE_OBJECT_INST_P( xoite_source_s )
"aware xoite_source"
"{"
    "st_s name;"
    "st_s path;"
    "tp_t hash;"
    "xoite_group_s => [];"
    "private aware xoite_target_s* target;"
    "func xoite:finalize;"
"}";

/**********************************************************************************************************************/
// source: xoite_target.h
#include "xoite_target.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoite_target

BCORE_DEFINE_OBJECT_INST_P( xoite_target_s )
"aware xoite_target"
"{"
    "st_s name;"
    "st_s path;"
    "xoite_source_s => [];"
    "func xoite:finalize;"
    "st_s signal_handler_name;"
    "bcore_arr_sz_s dependencies;"
    "bl_t flag;"
    "bl_t modified;"
    "st_s => planted_h;"
    "st_s => planted_c;"
    "private aware xoite_compiler_s* compiler;"
"}";

/**********************************************************************************************************************/
// source: xoite_compiler.h
#include "xoite_compiler.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoite_compiler

BCORE_DEFINE_OBJECT_INST_P( xoite_compiler_s )
"aware xoite_compiler"
"{"
    "hidden xoite_target_s => [];"
    "hidden bcore_hmap_tpvd_s hmap_group;"
    "hidden bcore_hmap_tpvd_s hmap_item;"
    "hidden bcore_life_s life;"
    "bl_t backup_planted_files = true;"
    "bl_t register_plain_functions = true;"
    "bl_t register_signatures = false;"
    "bl_t overwrite_unsigned_planted_files = false;"
    "sz_t verbosity = 1;"
    "func xoite:finalize;"
"}";

/**********************************************************************************************************************/
// source: xoite_builder.h
#include "xoite_builder.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoite_builder

BCORE_DEFINE_OBJECT_INST_P( xoite_builder_target_s )
"aware xoite_builder"
"{"
    "st_s => name;"
    "st_s => extension = \"xoi_out\";"
    "st_s => root;"
    "private aware xoite_builder_main_s* main;"
    "bcore_arr_st_s dependencies;"
    "bcore_arr_st_s sources;"
    "st_s => signal_handler;"
    "func bcore_via_call:source;"
"}";

void xoite_builder_target_s_source( xoite_builder_target_s* o, bcore_source* source )
{
    if( !o->root )
    {
        o->root = bcore_file_folder_path( bcore_source_a_get_file( source ) );
        st_s_attach( &o->root, bcore_file_path_minimized( o->root->sc ) );
    }
}

BCORE_DEFINE_OBJECT_INST_P( xoite_builder_main_s )
"aware xoite_builder"
"{"
    "xoite_compiler_s => compiler;"
    "bcore_arr_st_s arr_path;"
    "func bcore_inst_call:init_x;"
"}";

void xoite_builder_main_s_init_x( xoite_builder_main_s* o )
{
    o->compiler = xoite_compiler_s_create();
    xoite_compiler_s_setup( o->compiler );
}

/**********************************************************************************************************************/

vd_t bcore_general_signal_handler( const bcore_signal_s* o );

vd_t xoite_xoi_out_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "xoite_xoi_out" ) ) )
    {
        case TYPEOF_init1:
        {

            // --------------------------------------------------------------------
            // source: xoite.h

            // group: xoite
            BCORE_REGISTER_FEATURE( xoite_parse );
            BCORE_REGISTER_FEATURE( xoite_get_hash );
            BCORE_REGISTER_FEATURE( xoite_get_global_name_sc );
            BCORE_REGISTER_FEATURE( xoite_finalize );
            BCORE_REGISTER_FFUNC( xoite_finalize, xoite_finalize__ );
            BCORE_REGISTER_FEATURE( xoite_expand_forward );
            BCORE_REGISTER_FFUNC( xoite_expand_forward, xoite_expand_forward__ );
            BCORE_REGISTER_FEATURE( xoite_expand_indef_typedef );
            BCORE_REGISTER_FFUNC( xoite_expand_indef_typedef, xoite_expand_indef_typedef__ );
            BCORE_REGISTER_FEATURE( xoite_expand_spect_declaration );
            BCORE_REGISTER_FFUNC( xoite_expand_spect_declaration, xoite_expand_spect_declaration__ );
            BCORE_REGISTER_FEATURE( xoite_expand_spect_definition );
            BCORE_REGISTER_FFUNC( xoite_expand_spect_definition, xoite_expand_spect_definition__ );
            BCORE_REGISTER_FEATURE( xoite_expand_declaration );
            BCORE_REGISTER_FFUNC( xoite_expand_declaration, xoite_expand_declaration__ );
            BCORE_REGISTER_FEATURE( xoite_expand_indef_declaration );
            BCORE_REGISTER_FFUNC( xoite_expand_indef_declaration, xoite_expand_indef_declaration__ );
            BCORE_REGISTER_FEATURE( xoite_expand_definition );
            BCORE_REGISTER_FFUNC( xoite_expand_definition, xoite_expand_definition__ );
            BCORE_REGISTER_FEATURE( xoite_expand_init1 );
            BCORE_REGISTER_FFUNC( xoite_expand_init1, xoite_expand_init1__ );
            BCORE_REGISTER_SPECT( xoite );

            // --------------------------------------------------------------------
            // source: xoite_name.h

            // group: xoite_name
            BCORE_REGISTER_FFUNC( xoite_parse, xoite_name_s_parse );
            BCORE_REGISTER_FFUNC( xoite_get_hash, xoite_name_s_get_hash );
            BCORE_REGISTER_FFUNC( xoite_get_global_name_sc, xoite_name_s_get_global_name_sc );
            BCORE_REGISTER_FFUNC( xoite_expand_declaration, xoite_name_s_expand_declaration );
            BCORE_REGISTER_FFUNC( xoite_expand_init1, xoite_name_s_expand_init1 );
            BCORE_REGISTER_OBJECT( xoite_name_s );
            BCORE_REGISTER_TRAIT( xoite_name, xoite );

            // --------------------------------------------------------------------
            // source: xoite_forward.h

            // group: xoite_forward
            BCORE_REGISTER_FFUNC( xoite_parse, xoite_forward_s_parse );
            BCORE_REGISTER_FFUNC( xoite_get_hash, xoite_forward_s_get_hash );
            BCORE_REGISTER_FFUNC( xoite_get_global_name_sc, xoite_forward_s_get_global_name_sc );
            BCORE_REGISTER_FFUNC( xoite_expand_declaration, xoite_forward_s_expand_declaration );
            BCORE_REGISTER_FFUNC( xoite_expand_forward, xoite_forward_s_expand_forward );
            BCORE_REGISTER_FFUNC( xoite_expand_init1, xoite_forward_s_expand_init1 );
            BCORE_REGISTER_OBJECT( xoite_forward_s );
            BCORE_REGISTER_TRAIT( xoite_forward, xoite );

            // --------------------------------------------------------------------
            // source: xoite_arg.h

            // group: xoite_arg
            BCORE_REGISTER_FFUNC( xoite_parse, xoite_arg_s_parse );
            BCORE_REGISTER_FFUNC( xoite_get_hash, xoite_arg_s_get_hash );
            BCORE_REGISTER_OBJECT( xoite_arg_s );
            BCORE_REGISTER_TRAIT( xoite_arg, xoite );

            // --------------------------------------------------------------------
            // source: xoite_args.h

            // group: xoite_args
            BCORE_REGISTER_FFUNC( xoite_parse, xoite_args_s_parse );
            BCORE_REGISTER_FFUNC( xoite_get_hash, xoite_args_s_get_hash );
            BCORE_REGISTER_OBJECT( xoite_args_s );
            BCORE_REGISTER_TRAIT( xoite_args, xoite );

            // --------------------------------------------------------------------
            // source: xoite_signature.h

            // group: xoite_signature
            BCORE_REGISTER_FFUNC( xoite_parse, xoite_signature_s_parse );
            BCORE_REGISTER_FFUNC( xoite_get_hash, xoite_signature_s_get_hash );
            BCORE_REGISTER_FFUNC( xoite_get_global_name_sc, xoite_signature_s_get_global_name_sc );
            BCORE_REGISTER_OBJECT( xoite_signature_s );
            BCORE_REGISTER_TRAIT( xoite_signature, xoite );

            // --------------------------------------------------------------------
            // source: xoite_body.h

            // group: xoite_body
            BCORE_REGISTER_FFUNC( xoite_get_hash, xoite_body_s_get_hash );
            BCORE_REGISTER_FFUNC( xoite_get_global_name_sc, xoite_body_s_get_global_name_sc );
            BCORE_REGISTER_OBJECT( xoite_body_s );
            BCORE_REGISTER_TRAIT( xoite_body, xoite );

            // --------------------------------------------------------------------
            // source: xoite_feature.h

            // group: xoite_feature
            BCORE_REGISTER_FFUNC( xoite_parse, xoite_feature_s_parse );
            BCORE_REGISTER_FFUNC( xoite_get_hash, xoite_feature_s_get_hash );
            BCORE_REGISTER_FFUNC( xoite_get_global_name_sc, xoite_feature_s_get_global_name_sc );
            BCORE_REGISTER_FFUNC( xoite_expand_indef_typedef, xoite_feature_s_expand_indef_typedef );
            BCORE_REGISTER_FFUNC( xoite_expand_spect_declaration, xoite_feature_s_expand_spect_declaration );
            BCORE_REGISTER_FFUNC( xoite_expand_indef_declaration, xoite_feature_s_expand_indef_declaration );
            BCORE_REGISTER_FFUNC( xoite_expand_definition, xoite_feature_s_expand_definition );
            BCORE_REGISTER_FFUNC( xoite_expand_init1, xoite_feature_s_expand_init1 );
            BCORE_REGISTER_OBJECT( xoite_feature_s );
            BCORE_REGISTER_TRAIT( xoite_feature, xoite );

            // --------------------------------------------------------------------
            // source: xoite_func.h

            // group: xoite_func
            BCORE_REGISTER_OBJECT( xoite_func_s );
            BCORE_REGISTER_TRAIT( xoite_func, xoite );

            // --------------------------------------------------------------------
            // source: xoite_funcs.h

            // group: xoite_funcs
            BCORE_REGISTER_OBJECT( xoite_funcs_s );
            BCORE_REGISTER_TRAIT( xoite_funcs, xoite );

            // --------------------------------------------------------------------
            // source: xoite_group.h

            // group: xoite_group
            BCORE_REGISTER_FFUNC( xoite_parse, xoite_group_s_parse );
            BCORE_REGISTER_FFUNC( xoite_get_hash, xoite_group_s_get_hash );
            BCORE_REGISTER_FFUNC( xoite_get_global_name_sc, xoite_group_s_get_global_name_sc );
            BCORE_REGISTER_FFUNC( xoite_finalize, xoite_group_s_finalize );
            BCORE_REGISTER_OBJECT( xoite_group_s );
            BCORE_REGISTER_TRAIT( xoite_group, xoite );

            // --------------------------------------------------------------------
            // source: xoite_stamp.h

            // group: xoite_stamp
            BCORE_REGISTER_FFUNC( xoite_get_hash, xoite_stamp_s_get_hash );
            BCORE_REGISTER_FFUNC( xoite_get_global_name_sc, xoite_stamp_s_get_global_name_sc );
            BCORE_REGISTER_FFUNC( xoite_finalize, xoite_stamp_s_finalize );
            BCORE_REGISTER_FFUNC( xoite_expand_declaration, xoite_stamp_s_expand_declaration );
            BCORE_REGISTER_FFUNC( xoite_expand_forward, xoite_stamp_s_expand_forward );
            BCORE_REGISTER_FFUNC( xoite_expand_indef_declaration, xoite_stamp_s_expand_indef_declaration );
            BCORE_REGISTER_FFUNC( xoite_expand_definition, xoite_stamp_s_expand_definition );
            BCORE_REGISTER_FFUNC( xoite_expand_init1, xoite_stamp_s_expand_init1 );
            BCORE_REGISTER_OBJECT( xoite_stamp_s );
            BCORE_REGISTER_TRAIT( xoite_stamp, xoite );

            // --------------------------------------------------------------------
            // source: xoite_nested_group.h

            // group: xoite_nested_group
            BCORE_REGISTER_FFUNC( xoite_get_hash, xoite_nested_group_s_get_hash );
            BCORE_REGISTER_FFUNC( xoite_expand_forward, xoite_nested_group_s_expand_forward );
            BCORE_REGISTER_FFUNC( xoite_expand_indef_declaration, xoite_nested_group_s_expand_indef_declaration );
            BCORE_REGISTER_OBJECT( xoite_nested_group_s );
            BCORE_REGISTER_TRAIT( xoite_nested_group, xoite );

            // --------------------------------------------------------------------
            // source: xoite_source.h

            // group: xoite_source
            BCORE_REGISTER_FFUNC( xoite_finalize, xoite_source_s_finalize );
            BCORE_REGISTER_OBJECT( xoite_source_s );
            BCORE_REGISTER_TRAIT( xoite_source, xoite );

            // --------------------------------------------------------------------
            // source: xoite_target.h

            // group: xoite_target
            BCORE_REGISTER_FFUNC( xoite_finalize, xoite_target_s_finalize );
            BCORE_REGISTER_OBJECT( xoite_target_s );
            BCORE_REGISTER_TRAIT( xoite_target, xoite );

            // --------------------------------------------------------------------
            // source: xoite_compiler.h

            // group: xoite_compiler
            BCORE_REGISTER_FFUNC( xoite_finalize, xoite_compiler_s_finalize );
            BCORE_REGISTER_OBJECT( xoite_compiler_s );
            BCORE_REGISTER_TRAIT( xoite_compiler, xoite );

            // --------------------------------------------------------------------
            // source: xoite_builder.h

            // group: xoite_builder
            BCORE_REGISTER_FFUNC( bcore_via_call_source, xoite_builder_target_s_source );
            BCORE_REGISTER_OBJECT( xoite_builder_target_s );
            BCORE_REGISTER_FFUNC( bcore_inst_call_init_x, xoite_builder_main_s_init_x );
            BCORE_REGISTER_OBJECT( xoite_builder_main_s );
            BCORE_REGISTER_TRAIT( xoite_builder, xoite );
        }
        break;
        case TYPEOF_push_dependencies:
        {
            ASSERT( o->object && ( *( aware_t* )o->object ) == TYPEOF_bcore_arr_fp_s );
            bcore_arr_fp_s* arr_fp = o->object;
            bcore_arr_fp_s_push( arr_fp, ( fp_t )bcore_general_signal_handler );
        }
        break;
        default: break;
    }
    return NULL;
}
// BETH_PLANT_SIGNATURE   10636519
