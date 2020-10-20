/** This file was generated from xoila source code.
 *  Compiling Agent : xoico_compiler (C) 2020 J.B.Steffens
 *  Last File Update: 2020-10-20T14:40:32Z
 *
 *  Copyright and License of this File:
 *
 *  Generated code inherits the copyright and license of the underlying xoila source code.
 *  Source code defining this file is distributed across following files:
 *
 *  xoico.h
 *  xoico_name.h
 *  xoico_forward.h
 *  xoico_typespec.h
 *  xoico_arg.h
 *  xoico_args.h
 *  xoico_signature.h
 *  xoico_body.h
 *  xoico_feature.h
 *  xoico_func.h
 *  xoico_funcs.h
 *  xoico_group.h
 *  xoico_stamp.h
 *  xoico_nested_group.h
 *  xoico_source.h
 *  xoico_target.h
 *  xoico_compiler.h
 *  xoico_builder.h
 *  xoico_cengine.h
 *  xoico_caleph.h
 *  xoico_cbeth.h
 *  xoico_cgimel.h
 *  xoico_cdaleth.h
 *
 */

#include "xoico_xoila_out.h"
#include "bcore_spect.h"
#include "bcore_spect_inst.h"
#include "bcore_sr.h"
#include "bcore_const_manager.h"


/**********************************************************************************************************************/
// source: xoico.h
#include "xoico.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico

XOILA_DEFINE_SPECT( bcore_inst, xoico )
"{"
    "bcore_spect_header_s header;"
    "feature aware xoico : parse;"
    "feature aware xoico : get_hash;"
    "feature aware xoico : get_global_name_sc;"
    "feature aware xoico : get_global_name_tp = xoico_get_global_name_tp_default;"
    "feature aware xoico : finalize = xoico_finalize_default;"
    "feature aware xoico : expand_setup = xoico_expand_setup_default;"
    "feature aware xoico : expand_forward = xoico_expand_forward_default;"
    "feature aware xoico : expand_indef_typedef = xoico_expand_indef_typedef_default;"
    "feature aware xoico : expand_spect_declaration = xoico_expand_spect_declaration_default;"
    "feature aware xoico : expand_spect_definition = xoico_expand_spect_definition_default;"
    "feature aware xoico : expand_declaration = xoico_expand_declaration_default;"
    "feature aware xoico : expand_indef_declaration = xoico_expand_indef_declaration_default;"
    "feature aware xoico : expand_definition = xoico_expand_definition_default;"
    "feature aware xoico : expand_init1 = xoico_expand_init1_default;"
"}";

/**********************************************************************************************************************/
// source: xoico_name.h
#include "xoico_name.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_name

BCORE_DEFINE_OBJECT_INST_P( xoico_name_s )
"aware xoico_name"
"{"
    "tp_t name;"
    "hidden aware xoico_group_s* group;"
    "bcore_source_point_s source_point;"
    "func xoico:parse;"
    "func xoico:get_hash;"
    "func xoico:get_global_name_sc;"
    "func xoico:expand_declaration;"
    "func xoico:expand_init1;"
"}";

XOILA_DEFINE_SPECT( xoico, xoico_name )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/
// source: xoico_forward.h
#include "xoico_forward.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_forward

BCORE_DEFINE_OBJECT_INST_P( xoico_forward_s )
"aware xoico_forward"
"{"
    "st_s name;"
    "hidden aware xoico_group_s* group;"
    "bcore_source_point_s source_point;"
    "func xoico:parse;"
    "func xoico:get_hash;"
    "func xoico:get_global_name_sc;"
    "func xoico:expand_declaration;"
    "func xoico:expand_forward;"
    "func xoico:expand_init1;"
"}";

XOILA_DEFINE_SPECT( xoico, xoico_forward )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/
// source: xoico_typespec.h
#include "xoico_typespec.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_typespec

BCORE_DEFINE_OBJECT_INST_P( xoico_typespec_s )
"aware xoico_typespec"
"{"
    "tp_t type;"
    "sz_t indirection;"
    "bl_t flag_const;"
    "bl_t flag_static;"
    "bl_t flag_volatile;"
    "bl_t flag_restrict;"
    "bl_t flag_keep;"
    "bl_t flag_addressable = true;"
    "func xoico:get_hash;"
"}";

void xoico_typespec_s_reset( xoico_typespec_s* o )
{
    // xoico_typespec.h:54:5
    o->type = 0;
    o->indirection = 0;
    o->flag_const    = false;
    o->flag_static   = false;
    o->flag_volatile = false;
    o->flag_restrict = false;
    o->flag_keep     = false;
    o->flag_addressable = true;  // object can have a pointer ('false' for objects returned by a function)
}

XOILA_DEFINE_SPECT( xoico, xoico_typespec )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/
// source: xoico_arg.h
#include "xoico_arg.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_arg

BCORE_DEFINE_OBJECT_INST_P( xoico_arg_s )
"aware xoico_arg"
"{"
    "hidden aware xoico_group_s* group;"
    "bcore_source_point_s source_point;"
    "xoico_typespec_s typespec;"
    "tp_t name;"
    "func xoico:parse;"
    "func xoico:get_hash;"
"}";

XOILA_DEFINE_SPECT( xoico, xoico_arg )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/
// source: xoico_args.h
#include "xoico_args.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_args

BCORE_DEFINE_OBJECT_INST_P( xoico_args_s )
"aware xoico_args"
"{"
    "xoico_arg_s [];"
    "hidden aware xoico_group_s* group;"
    "func xoico:parse;"
    "func xoico:get_hash;"
"}";

XOILA_DEFINE_SPECT( xoico, xoico_args )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/
// source: xoico_signature.h
#include "xoico_signature.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_signature

BCORE_DEFINE_OBJECT_INST_P( xoico_signature_s )
"aware xoico_signature"
"{"
    "st_s st_name;"
    "st_s st_global_name;"
    "xoico_typespec_s typespec_ret;"
    "xoico_args_s args;"
    "tp_t arg_o;"
    "hidden aware xoico_group_s* group;"
    "bcore_source_point_s source_point;"
    "func xoico:parse;"
    "func xoico:get_hash;"
    "func xoico:get_global_name_sc;"
"}";

XOILA_DEFINE_SPECT( xoico, xoico_signature )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/
// source: xoico_body.h
#include "xoico_body.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_body

BCORE_DEFINE_OBJECT_INST_P( xoico_body_code_s )
"aware xoico_body"
"{"
    "bl_t single_line;"
    "sz_t indentation;"
    "tp_t hash_source;"
    "bcore_source_point_s source_point;"
    "func xoico:get_hash;"
    "hidden aware xoico_group_s* group;"
    "hidden aware xoico_stamp_s* stamp;"
"}";

BCORE_DEFINE_OBJECT_INST_P( xoico_body_s )
"aware xoico_body"
"{"
    "st_s name;"
    "st_s global_name;"
    "xoico_body_code_s => code;"
    "bl_t go_inline;"
    "bcore_source_point_s source_point;"
    "hidden aware xoico_group_s* group;"
    "hidden aware xoico_stamp_s* stamp;"
    "func xoico:get_hash;"
    "func xoico:get_global_name_sc;"
"}";

XOILA_DEFINE_SPECT( xoico, xoico_body )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/
// source: xoico_feature.h
#include "xoico_feature.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_feature

BCORE_DEFINE_OBJECT_INST_P( xoico_feature_s )
"aware xoico_feature"
"{"
    "xoico_signature_s signature;"
    "st_s st_default_func_name;"
    "xoico_body_s => default_body;"
    "bl_t strict;"
    "bl_t flag_p;"
    "bl_t flag_t;"
    "bl_t flag_a;"
    "bl_t flag_r;"
    "bl_t expandable = true;"
    "hidden aware xoico_group_s* group;"
    "bcore_source_point_s source_point;"
    "func xoico:parse;"
    "func xoico:get_hash;"
    "func xoico:get_global_name_sc;"
    "func xoico:expand_indef_typedef;"
    "func xoico:expand_spect_declaration;"
    "func xoico:expand_spect_definition;"
    "func xoico:expand_indef_declaration;"
    "func xoico:expand_definition;"
    "func xoico:expand_init1;"
"}";

XOILA_DEFINE_SPECT( xoico, xoico_feature )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/
// source: xoico_func.h
#include "xoico_func.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_func

BCORE_DEFINE_OBJECT_INST_P( xoico_func_s )
"aware xoico_func"
"{"
    "tp_t name;"
    "tp_t global_name;"
    "tp_t type;"
    "st_s flect_decl;"
    "bl_t expandable = true;"
    "bl_t overloadable = false;"
    "xoico_body_s => body;"
    "hidden aware xoico_group_s* group;"
    "hidden aware xoico_stamp_s* stamp;"
    "bcore_source_point_s source_point;"
"}";

XOILA_DEFINE_SPECT( xoico, xoico_func )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/
// source: xoico_funcs.h
#include "xoico_funcs.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_funcs

BCORE_DEFINE_OBJECT_INST_P( xoico_funcs_s )
"aware xoico_funcs"
"{"
    "xoico_func_s => [];"
"}";

XOILA_DEFINE_SPECT( xoico, xoico_funcs )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/
// source: xoico_group.h
#include "xoico_group.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_group

BCORE_DEFINE_OBJECT_INST_P( xoico_group_source_stack_s )
"aware bcore_array"
"{"
    "aware bcore_source -> [];"
"}";

BCORE_DEFINE_OBJECT_INST_P( xoico_group_s )
"aware xoico_group"
"{"
    "aware xoico => [];"
    "st_s st_name;"
    "tp_t tp_name;"
    "private xoico_group_s* group;"
    "st_s trait_name = \"bcore_inst\";"
    "tp_t hash;"
    "tp_t beta = 0;"
    "bl_t expandable = true;"
    "bl_t retrievable;"
    "bl_t short_spect_name;"
    "private xoico_stamp_s -> extending;"
    "private aware xoico_source_s* source;"
    "bcore_source_point_s source_point;"
    "hidden bcore_hmap_tpvd_s hmap_feature;"
    "func xoico:parse;"
    "func xoico:get_hash;"
    "func xoico:get_global_name_sc;"
    "func xoico:get_global_name_tp;"
    "func xoico:finalize;"
    "func xoico:expand_setup;"
"}";

XOILA_DEFINE_SPECT( xoico, xoico_group )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/
// source: xoico_stamp.h
#include "xoico_stamp.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_stamp

BCORE_DEFINE_OBJECT_INST_P( xoico_stamp_s )
"aware xoico_stamp"
"{"
    "st_s st_name;"
    "tp_t tp_name;"
    "st_s st_trait_name;"
    "st_s => self_source;"
    "bcore_self_s => self;"
    "xoico_funcs_s funcs;"
    "private aware xoico_group_s* group;"
    "bcore_source_point_s source_point;"
    "func xoico:get_hash;"
    "func xoico:get_global_name_sc;"
    "func xoico:get_global_name_tp;"
    "func xoico:finalize;"
    "func xoico:expand_setup;"
    "func xoico:expand_declaration;"
    "func xoico:expand_forward;"
    "func xoico:expand_indef_declaration;"
    "func xoico:expand_definition;"
    "func xoico:expand_init1;"
"}";

XOILA_DEFINE_SPECT( xoico, xoico_stamp )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/
// source: xoico_nested_group.h
#include "xoico_nested_group.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_nested_group

BCORE_DEFINE_OBJECT_INST_P( xoico_nested_group_s )
"aware xoico_nested_group"
"{"
    "hidden xoico_group_s* group;"
    "func xoico:get_hash;"
    "func xoico:expand_forward;"
    "func xoico:expand_indef_declaration;"
"}";

XOILA_DEFINE_SPECT( xoico, xoico_nested_group )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/
// source: xoico_source.h
#include "xoico_source.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_source

BCORE_DEFINE_OBJECT_INST_P( xoico_source_s )
"aware xoico_source"
"{"
    "st_s name;"
    "st_s path;"
    "tp_t hash;"
    "xoico_group_s => [];"
    "hidden aware xoico_target_s* target;"
    "func xoico:finalize;"
    "func xoico:expand_setup;"
"}";

XOILA_DEFINE_SPECT( xoico, xoico_source )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/
// source: xoico_target.h
#include "xoico_target.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_target

BCORE_DEFINE_OBJECT_INST_P( xoico_target_s )
"aware xoico_target"
"{"
    "st_s name;"
    "st_s path;"
    "xoico_source_s => [];"
    "st_s signal_handler_name;"
    "bcore_arr_sz_s dependencies;"
    "bl_t flag;"
    "bl_t modified;"
    "bl_t readonly;"
    "st_s => target_h;"
    "st_s => target_c;"
    "aware xoico_cengine -> cengine;"
    "bcore_arr_st_s explicit_embeddings;"
    "hidden aware xoico_compiler_s* compiler;"
    "func xoico:finalize;"
    "func xoico:expand_setup;"
"}";

XOILA_DEFINE_SPECT( xoico, xoico_target )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/
// source: xoico_compiler.h
#include "xoico_compiler.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_compiler

BCORE_DEFINE_OBJECT_INST_P( xoico_compiler_type_info_s )
"aware xoico_compiler"
"{"
    "xoico_typespec_s typespec;"
    "hidden xoico* item;"
"}";

BCORE_DEFINE_OBJECT_INST_P( xoico_compiler_element_info_s )
"aware xoico_compiler"
"{"
    "xoico_compiler_type_info_s type_info;"
    "xoico_signature_s => signature;"
"}";

BCORE_DEFINE_OBJECT_INST_P( xoico_compiler_s )
"aware xoico_compiler"
"{"
    "hidden xoico_target_s => [];"
    "hidden bcore_hmap_tpvd_s hmap_group;"
    "hidden bcore_hmap_tpvd_s hmap_item;"
    "hidden bcore_hmap_tp_s hmap_type;"
    "hidden bcore_life_s life;"
    "hidden bcore_hmap_name_s name_map;"
    "tp_t target_pre_hash = 71;"
    "bl_t work_build_time_into_pre_hash = true;"
    "bl_t register_non_feature_functions = true;"
    "bl_t register_signatures = false;"
    "bl_t overwrite_unsigned_target_files = false;"
    "bl_t always_expand = false;"
    "bl_t dry_run = false;"
    "sz_t verbosity = 1;"
    "func xoico:finalize;"
    "func xoico:expand_setup;"
    "func bcore_inst_call:init_x;"
"}";

void xoico_compiler_s_init_x( xoico_compiler_s* o )
{
    // xoico_compiler.h:124:5
    if( o->work_build_time_into_pre_hash )
    {
        o->target_pre_hash = bcore_tp_fold_sc( o->target_pre_hash, __DATE__ );
        o->target_pre_hash = bcore_tp_fold_sc( o->target_pre_hash, __TIME__ );
    }
}

XOILA_DEFINE_SPECT( xoico, xoico_compiler )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/
// source: xoico_builder.h
#include "xoico_builder.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_builder

BCORE_DEFINE_OBJECT_INST_P( xoico_builder_arr_target_s )
"aware bcore_array"
"{"
    "xoico_builder_target_s => [];"
"}";

BCORE_DEFINE_OBJECT_INST_P( xoico_builder_target_s )
"aware xoico_builder"
"{"
    "st_s => name;"
    "st_s => extension = \"xoila_out\";"
    "st_s => root_folder;"
    "bl_t readonly;"
    "bcore_arr_st_s dependencies;"
    "bcore_arr_st_s sources;"
    "st_s => signal_handler;"
    "aware xoico_cengine => cengine = xoico_cgimel_s;"
    "private xoico_compiler_s* compiler;"
    "private xoico_builder_target_s* parent_;"
    "private xoico_builder_target_s* root_;"
    "hidden aware xoico_builder_arr_target_s => dependencies_target_;"
    "hidden st_s full_path_;"
    "hidden sz_t target_index_ = -1;"
    "hidden bcore_hmap_tpvd_s => hmap_built_target_;"
    "func bcore_via_call:source;"
"}";

void xoico_builder_target_s_source( xoico_builder_target_s* o, bcore_source* source )
{
    // xoico_builder.h:69:5
    if( !o->root_folder )
    {
        o->root_folder = bcore_file_folder_path( bcore_source_a_get_file( source ) );
        st_s_attach( &o->root_folder, bcore_file_path_minimized( o->root_folder->sc ) );
    }
}

const xoico_builder_target_s* xoico_builder_target_s_name_match( const xoico_builder_target_s* o, sc_t name )
{
    // xoico_builder.h:78:5
    if( o->name && sc_t_equal( name, o->name->sc ) ) return o;
    if( o->parent_ ) return xoico_builder_target_s_name_match( o->parent_, name );
    return NULL;
}

void xoico_builder_target_s_push_target_index_to_arr( const xoico_builder_target_s* o, bcore_arr_sz_s* arr )
{
    // xoico_builder.h:85:5
    if( o->target_index_ != -1 )
    {
         bcore_arr_sz_s_push( arr, o->target_index_ );
    }
    else
    {
        BFOR_EACH( i, o->dependencies_target_ ) xoico_builder_target_s_push_target_index_to_arr( o->dependencies_target_->data[ i ], arr );
    }
}

BCORE_DEFINE_OBJECT_INST_P( xoico_builder_main_s )
"aware xoico_builder"
"{"
    "xoico_compiler_s => compiler!;"
    "xoico_builder_target_s => target;"
"}";

er_t xoico_builder_main_s_set_dry_run( xoico_builder_main_s* o, bl_t v )
{
    // xoico_builder.h:125:5
    o->compiler->dry_run = v;
    return 0;
}

bl_t xoico_builder_main_s_get_dry_run( const xoico_builder_main_s* o )
{
    // xoico_builder.h:131:5
    return o->compiler->dry_run;
}

er_t xoico_builder_main_s_set_always_expand( xoico_builder_main_s* o, bl_t v )
{
    // xoico_builder.h:136:5
    o->compiler->always_expand = v;
    return 0;
}

bl_t xoico_builder_main_s_get_always_expand( const xoico_builder_main_s* o )
{
    // xoico_builder.h:142:5
    return o->compiler->always_expand;
}

er_t xoico_builder_main_s_set_overwrite_unsigned_target_files( xoico_builder_main_s* o, bl_t v )
{
    // xoico_builder.h:147:5
    o->compiler->overwrite_unsigned_target_files = v;
    return 0;
}

bl_t xoico_builder_main_s_get_overwrite_unsigned_target_files( const xoico_builder_main_s* o )
{
    // xoico_builder.h:153:5
    return o->compiler->overwrite_unsigned_target_files;
}

XOILA_DEFINE_SPECT( xoico, xoico_builder )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/
// source: xoico_cengine.h
#include "xoico_cengine.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_cengine

XOILA_DEFINE_SPECT( xoico, xoico_cengine )
"{"
    "bcore_spect_header_s header;"
    "feature aware xoico_cengine : translate;"
    "feature aware xoico_cengine : get_hash = xoico_cengine_get_hash_default;"
"}";

/**********************************************************************************************************************/
// source: xoico_caleph.h
#include "xoico_caleph.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_caleph

BCORE_DEFINE_OBJECT_INST_P( xoico_caleph_s )
"aware xoico_caleph"
"{"
    "bl_t insert_source_reference = true;"
    "hidden xoico_args_s* args;"
    "hidden xoico_compiler_s* compiler;"
    "hidden xoico_group_s* group;"
    "hidden xoico_stamp_s* stamp;"
    "tp_t obj_type;"
    "bcore_hmap_name_s hmap_name;"
    "func xoico_cengine:translate;"
"}";

sc_t xoico_caleph_s_nameof( xoico_caleph_s* o, tp_t type )
{
    // xoico_caleph.h:56:5
    sc_t name = bcore_hmap_name_s_get_sc( &o->hmap_name, type );
    if( !name ) name = xoico_compiler_s_nameof( o->compiler, type );
    return name;
}

XOILA_DEFINE_SPECT( xoico_cengine, xoico_caleph )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/
// source: xoico_cbeth.h
#include "xoico_cbeth.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_cbeth

BCORE_DEFINE_OBJECT_INST_P( xoico_cbeth_s )
"aware xoico_cbeth"
"{"
    "sc_t obj_type;"
    "xoico_args_s -> args;"
    "xoico_compiler_s -> compiler;"
    "hidden xoico_cbeth_tn_stack_s stack;"
    "func xoico_cengine:translate;"
"}";

XOILA_DEFINE_SPECT( xoico_cengine, xoico_cbeth )
"{"
    "bcore_spect_header_s header;"
"}";

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_cbeth_tn

BCORE_DEFINE_OBJECT_INST_P( xoico_cbeth_tn_unit_s )
"bcore_inst"
"{"
    "tp_t type;"
    "tp_t name;"
    "sz_t level;"
"}";

BCORE_DEFINE_OBJECT_INST_P( xoico_cbeth_tn_adl_s )
"aware bcore_array"
"{"
    "xoico_cbeth_tn_unit_s => [];"
"}";

BCORE_DEFINE_OBJECT_INST_P( xoico_cbeth_tn_stack_s )
"aware xoico_cbeth_tn"
"{"
    "xoico_cbeth_tn_adl_s adl;"
    "bcore_hmap_name_s name_map;"
"}";

xoico_cbeth_tn_stack_s* xoico_cbeth_tn_stack_s_push( xoico_cbeth_tn_stack_s* o, tp_t type, tp_t name, sz_t level )
{
    // xoico_cbeth.h:58:9
    xoico_cbeth_tn_unit_s* unit = xoico_cbeth_tn_unit_s_create();
    unit->type = type;
    unit->name = name;
    unit->level = level;
    xoico_cbeth_tn_adl_s_push_d( &o->adl, unit );
    return o;
}

xoico_cbeth_tn_stack_s* xoico_cbeth_tn_stack_s_push_sc( xoico_cbeth_tn_stack_s* o, sc_t type, sc_t name, sz_t level )
{
    // xoico_cbeth.h:68:9
    xoico_cbeth_tn_unit_s* unit = xoico_cbeth_tn_unit_s_create();
    unit->type = bcore_hmap_name_s_set_sc( &o->name_map, type );
    unit->name = bcore_hmap_name_s_set_sc( &o->name_map, name );
    unit->level = level;
    xoico_cbeth_tn_adl_s_push_d( &o->adl, unit );
    return o;
}

xoico_cbeth_tn_stack_s* xoico_cbeth_tn_stack_s_pop( xoico_cbeth_tn_stack_s* o, sz_t level )
{
    // xoico_cbeth.h:78:9
    sz_t new_size = o->adl.size;
    for( sz_t i = o->adl.size - 1; i >= 0; i-- )
    {
        if( o->adl.data[ i ]->level < level ) break;
        new_size = i;
    }
    xoico_cbeth_tn_adl_s_set_size( &o->adl, new_size );
    return o;
}

tp_t xoico_cbeth_tn_stack_s_get_type( xoico_cbeth_tn_stack_s* o, tp_t name )
{
    // xoico_cbeth.h:90:9
    for( sz_t i = o->adl.size - 1; i >= 0; i-- )
    {
        if( o->adl.data[ i ]->name == name ) return o->adl.data[ i ]->type;
    }
    return 0;
}

sc_t xoico_cbeth_tn_stack_s_get_type_sc( xoico_cbeth_tn_stack_s* o, sc_t name )
{
    // xoico_cbeth.h:99:9
    return bcore_hmap_name_s_get_sc( &o->name_map, xoico_cbeth_tn_stack_s_get_type( o, btypeof( name ) ) );
}

void xoico_cbeth_tn_stack_s_clear( xoico_cbeth_tn_stack_s* o )
{
    // xoico_cbeth.h:104:9
    bcore_hmap_name_s_clear( &o->name_map );
    xoico_cbeth_tn_adl_s_clear( &o->adl );
}

void xoico_cbeth_tn_stack_s_init_from_args( xoico_cbeth_tn_stack_s* o, sc_t obj_type, sc_t obj_name, const xoico_args_s* args )
{
    // xoico_cbeth.h:110:9
    const xoico_compiler_s* compiler = xoico_group_s_get_compiler( args->group );
    xoico_cbeth_tn_stack_s_clear( o );
    if( obj_type ) xoico_cbeth_tn_stack_s_push_sc( o, obj_type, obj_name, 0 );
    BFOR_EACH( i, args )
    {
        sc_t sc_type = xoico_compiler_s_nameof( compiler, args->data[ i ].typespec.type );
        sc_t sc_name = xoico_compiler_s_nameof( compiler, args->data[ i ].name );
        xoico_cbeth_tn_stack_s_push_sc( o, sc_type, sc_name, 0 );
    }
}

XOILA_DEFINE_SPECT( xoico_cbeth, xoico_cbeth_tn )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/
// source: xoico_cgimel.h
#include "xoico_cgimel.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_cgimel

BCORE_DEFINE_OBJECT_INST_P( xoico_cgimel_s )
"aware xoico_cgimel"
"{"
    "bl_t verbose = false;"
    "bl_t insert_source_reference = true;"
    "hidden xoico_args_s* args;"
    "hidden xoico_compiler_s* compiler;"
    "hidden xoico_group_s* group;"
    "hidden xoico_stamp_s* stamp;"
    "tp_t obj_type;"
    "sz_t level;"
    "xoico_cgimel_stack_s stack;"
    "bcore_hmap_name_s hmap_name;"
    "func xoico_cengine:translate;"
"}";

sc_t xoico_cgimel_s_nameof( xoico_cgimel_s* o, tp_t type )
{
    // xoico_cgimel.h:114:5
    sc_t name = bcore_hmap_name_s_get_sc( &o->hmap_name, type );
    if( !name ) name = xoico_compiler_s_nameof( o->compiler, type );
    return name;
}

void xoico_cgimel_s_inc_level( xoico_cgimel_s* o )
{
    // xoico_cgimel.h:121:5
    o->level++;
}

void xoico_cgimel_s_dec_level( xoico_cgimel_s* o )
{
    // xoico_cgimel.h:126:5
    xoico_cgimel_stack_s_pop_level( &o->stack, o->level );
    o->level--;
}

void xoico_cgimel_s_push_typedecl( xoico_cgimel_s* o, const xoico_typespec_s* typespec, tp_t name )
{
    // xoico_cgimel.h:132:5
    BLM_INIT();
    xoico_cgimel_stack_unit_s* unit = BLM_CREATE( xoico_cgimel_stack_unit_s );
    unit->level = o->level;
    unit->name = name;
    xoico_typespec_s_copy( &unit->typespec, typespec );
    xoico_cgimel_stack_s_push_unit( &o->stack, unit );
    BLM_DOWN();
}

XOILA_DEFINE_SPECT( xoico_cengine, xoico_cgimel )
"{"
    "bcore_spect_header_s header;"
"}";

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_cgimel_stack

BCORE_DEFINE_OBJECT_INST_P( xoico_cgimel_stack_unit_s )
"bcore_inst"
"{"
    "sz_t level;"
    "tp_t name;"
    "xoico_typespec_s typespec;"
"}";

BCORE_DEFINE_OBJECT_INST_P( xoico_cgimel_stack_unit_adl_s )
"aware bcore_array"
"{"
    "xoico_cgimel_stack_unit_s => [];"
"}";

BCORE_DEFINE_OBJECT_INST_P( xoico_cgimel_stack_s )
"aware xoico_cgimel_stack"
"{"
    "xoico_cgimel_stack_unit_adl_s adl;"
"}";

xoico_cgimel_stack_s* xoico_cgimel_stack_s_pop_level( xoico_cgimel_stack_s* o, sz_t level )
{
    // xoico_cgimel.h:57:9
    sz_t size = o->adl.size;
    while( size > 0 && o->adl.data[ size - 1 ]->level >= level ) size--;
    xoico_cgimel_stack_unit_adl_s_set_size( &o->adl, size );
    return o;
}

const xoico_typespec_s* xoico_cgimel_stack_s_get_typespec( const xoico_cgimel_stack_s* o, tp_t name )
{
    // xoico_cgimel.h:65:9
    for( sz_t i = o->adl.size - 1; i >= 0; i-- )
    {
        if( o->adl.data[ i ]->name == name ) return &o->adl.data[ i ]->typespec;
    }
    return NULL;
}

XOILA_DEFINE_SPECT( xoico_cgimel, xoico_cgimel_stack )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/
// source: xoico_cdaleth.h
#include "xoico_cdaleth.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_cdaleth

BCORE_DEFINE_OBJECT_INST_P( xoico_cdaleth_s )
"aware xoico_cdaleth"
"{"
    "bl_t verbose = false;"
    "bl_t insert_source_reference = true;"
    "hidden xoico_args_s* args;"
    "hidden xoico_typespec_s* typespec_ret;"
    "hidden xoico_compiler_s* compiler;"
    "hidden xoico_group_s* group;"
    "hidden xoico_stamp_s* stamp;"
    "tp_t obj_type;"
    "sz_t level;"
    "xoico_cdaleth_stack_var_s stack_var;"
    "xoico_cdaleth_stack_block_s stack_block;"
    "bcore_hmap_name_s hmap_name;"
    "func xoico_cengine:translate;"
"}";

sc_t xoico_cdaleth_s_nameof( xoico_cdaleth_s* o, tp_t type )
{
    // xoico_cdaleth.h:194:5
    sc_t name = bcore_hmap_name_s_get_sc( &o->hmap_name, type );
    if( !name ) name = xoico_compiler_s_nameof( o->compiler, type );
    return name;
}

void xoico_cdaleth_s_init_level0( xoico_cdaleth_s* o )
{
    // xoico_cdaleth.h:201:5
    xoico_cdaleth_stack_block_s_clear( &o->stack_block );
    xoico_cdaleth_stack_block_s_push( &o->stack_block );
    o->level = 0;
}

void xoico_cdaleth_s_inc_level( xoico_cdaleth_s* o )
{
    // xoico_cdaleth.h:208:5
    o->level++;
}

void xoico_cdaleth_s_inc_block( xoico_cdaleth_s* o )
{
    // xoico_cdaleth.h:213:5
    xoico_cdaleth_stack_block_s_push( &(o->stack_block));
    xoico_cdaleth_s_inc_level( o);
    xoico_cdaleth_s_stack_block_get_top_unit( o)->level = o->level;
}

void xoico_cdaleth_s_dec_level( xoico_cdaleth_s* o )
{
    // xoico_cdaleth.h:220:5
    xoico_cdaleth_stack_var_s_pop_level( &(o->stack_var), o->level );
    o->level--;
    ASSERT( o->level >= 0 );
}

void xoico_cdaleth_s_dec_block( xoico_cdaleth_s* o )
{
    // xoico_cdaleth.h:227:5
    xoico_cdaleth_s_dec_level( o);
    xoico_cdaleth_stack_block_s_pop( &(o->stack_block));
}

xoico_cdaleth_stack_block_unit_s* xoico_cdaleth_s_stack_block_get_top_unit( xoico_cdaleth_s* o )
{
    // xoico_cdaleth.h:233:5
    return o->stack_block.adl.data[ o->stack_block.adl.size - 1 ];
}

void xoico_cdaleth_s_push_typedecl( xoico_cdaleth_s* o, const xoico_typespec_s* typespec, tp_t name )
{
    // xoico_cdaleth.h:238:5
    BLM_INIT();
    xoico_cdaleth_stack_var_unit_s* unit = BLM_CREATE( xoico_cdaleth_stack_var_unit_s );
    unit->level = o->level;
    unit->name = name;
    xoico_typespec_s_copy( &unit->typespec, typespec );
    xoico_cdaleth_stack_var_s_push_unit( &o->stack_var, unit );
    BLM_DOWN();
}

XOILA_DEFINE_SPECT( xoico_cengine, xoico_cdaleth )
"{"
    "bcore_spect_header_s header;"
"}";

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_cdaleth_stack_var

BCORE_DEFINE_OBJECT_INST_P( xoico_cdaleth_stack_var_unit_s )
"aware bcore_inst"
"{"
    "sz_t level;"
    "tp_t name;"
    "xoico_typespec_s typespec;"
"}";

BCORE_DEFINE_OBJECT_INST_P( xoico_cdaleth_stack_var_unit_adl_s )
"aware bcore_array"
"{"
    "xoico_cdaleth_stack_var_unit_s => [];"
"}";

BCORE_DEFINE_OBJECT_INST_P( xoico_cdaleth_stack_var_s )
"aware xoico_cdaleth_stack_var"
"{"
    "xoico_cdaleth_stack_var_unit_adl_s adl;"
    "bcore_hmap_tp_s hmap_name;"
"}";

void xoico_cdaleth_stack_var_s_rehash_names( xoico_cdaleth_stack_var_s* o )
{
    // xoico_cdaleth.h:62:9
    bcore_hmap_tp_s_clear( &(o->hmap_name));
    for( sz_t i = 0; i < o->adl.size; i++ ) bcore_hmap_tp_s_set( &(o->hmap_name), o->adl.data[i]->name );
}

xoico_cdaleth_stack_var_s* xoico_cdaleth_stack_var_s_push_unit( xoico_cdaleth_stack_var_s* o, const xoico_cdaleth_stack_var_unit_s* unit )
{
    // xoico_cdaleth.h:68:9
    xoico_cdaleth_stack_var_unit_adl_s_push_c( &(o->adl), unit );
    bcore_hmap_tp_s_set( &(o->hmap_name), unit->name );
    return o;
}

xoico_cdaleth_stack_var_s* xoico_cdaleth_stack_var_s_pop_level( xoico_cdaleth_stack_var_s* o, sz_t level )
{
    // xoico_cdaleth.h:75:9
    sz_t size = o->adl.size;
    while( size > 0 && o->adl.data[ size - 1 ]->level >= level ) size--;
    xoico_cdaleth_stack_var_unit_adl_s_set_size( &(o->adl), size );
    xoico_cdaleth_stack_var_s_rehash_names( o);
    return o;
}

const xoico_typespec_s* xoico_cdaleth_stack_var_s_get_typespec( const xoico_cdaleth_stack_var_s* o, tp_t name )
{
    // xoico_cdaleth.h:84:9
    for( sz_t i = o->adl.size - 1; i >= 0; i-- )
    {
        if( o->adl.data[ i ]->name == name ) return &o->adl.data[ i ]->typespec;
    }
    return NULL;
}

XOILA_DEFINE_SPECT( xoico_cdaleth, xoico_cdaleth_stack_var )
"{"
    "bcore_spect_header_s header;"
"}";

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_cdaleth_stack_block

BCORE_DEFINE_OBJECT_INST_P( xoico_cdaleth_stack_block_unit_s )
"aware bcore_inst"
"{"
    "sz_t level;"
    "bl_t use_blm = false;"
    "bl_t break_ledge = false;"
"}";

BCORE_DEFINE_OBJECT_INST_P( xoico_cdaleth_stack_block_unit_adl_s )
"aware bcore_array"
"{"
    "xoico_cdaleth_stack_block_unit_s => [];"
"}";

BCORE_DEFINE_OBJECT_INST_P( xoico_cdaleth_stack_block_s )
"aware xoico_cdaleth_stack_block"
"{"
    "xoico_cdaleth_stack_block_unit_adl_s adl;"
"}";

xoico_cdaleth_stack_block_s* xoico_cdaleth_stack_block_s_pop( xoico_cdaleth_stack_block_s* o )
{
    // xoico_cdaleth.h:123:9
    xoico_cdaleth_stack_block_unit_adl_s_set_size( &o->adl, sz_max( o->adl.size - 1, 0 ) );
    return o;
}

XOILA_DEFINE_SPECT( xoico_cdaleth, xoico_cdaleth_stack_block )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/

vd_t bcore_general_signal_handler( const bcore_signal_s* o );

vd_t xoico_xoila_out_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "xoico_xoila_out" ) ) )
    {
        case TYPEOF_init1:
        {

            // --------------------------------------------------------------------
            // source: xoico.h

            // group: xoico
            BCORE_REGISTER_FEATURE( xoico_parse );
            BCORE_REGISTER_FEATURE( xoico_get_hash );
            BCORE_REGISTER_FEATURE( xoico_get_global_name_sc );
            BCORE_REGISTER_FEATURE( xoico_get_global_name_tp );
            BCORE_REGISTER_FFUNC( xoico_get_global_name_tp, xoico_get_global_name_tp_default );
            BCORE_REGISTER_FEATURE( xoico_finalize );
            BCORE_REGISTER_FFUNC( xoico_finalize, xoico_finalize_default );
            BCORE_REGISTER_FEATURE( xoico_expand_setup );
            BCORE_REGISTER_FFUNC( xoico_expand_setup, xoico_expand_setup_default );
            BCORE_REGISTER_FEATURE( xoico_expand_forward );
            BCORE_REGISTER_FFUNC( xoico_expand_forward, xoico_expand_forward_default );
            BCORE_REGISTER_FEATURE( xoico_expand_indef_typedef );
            BCORE_REGISTER_FFUNC( xoico_expand_indef_typedef, xoico_expand_indef_typedef_default );
            BCORE_REGISTER_FEATURE( xoico_expand_spect_declaration );
            BCORE_REGISTER_FFUNC( xoico_expand_spect_declaration, xoico_expand_spect_declaration_default );
            BCORE_REGISTER_FEATURE( xoico_expand_spect_definition );
            BCORE_REGISTER_FFUNC( xoico_expand_spect_definition, xoico_expand_spect_definition_default );
            BCORE_REGISTER_FEATURE( xoico_expand_declaration );
            BCORE_REGISTER_FFUNC( xoico_expand_declaration, xoico_expand_declaration_default );
            BCORE_REGISTER_FEATURE( xoico_expand_indef_declaration );
            BCORE_REGISTER_FFUNC( xoico_expand_indef_declaration, xoico_expand_indef_declaration_default );
            BCORE_REGISTER_FEATURE( xoico_expand_definition );
            BCORE_REGISTER_FFUNC( xoico_expand_definition, xoico_expand_definition_default );
            BCORE_REGISTER_FEATURE( xoico_expand_init1 );
            BCORE_REGISTER_FFUNC( xoico_expand_init1, xoico_expand_init1_default );
            BCORE_REGISTER_NAME( mutable );
            BCORE_REGISTER_NAME( const );
            BCORE_REGISTER_NAME( void );
            XOILA_REGISTER_SPECT( xoico );

            // --------------------------------------------------------------------
            // source: xoico_name.h

            // group: xoico_name
            BCORE_REGISTER_FFUNC( xoico_parse, xoico_name_s_parse );
            BCORE_REGISTER_FFUNC( xoico_get_hash, xoico_name_s_get_hash );
            BCORE_REGISTER_FFUNC( xoico_get_global_name_sc, xoico_name_s_get_global_name_sc );
            BCORE_REGISTER_FFUNC( xoico_expand_declaration, xoico_name_s_expand_declaration );
            BCORE_REGISTER_FFUNC( xoico_expand_init1, xoico_name_s_expand_init1 );
            BCORE_REGISTER_OBJECT( xoico_name_s );
            XOILA_REGISTER_SPECT( xoico_name );

            // --------------------------------------------------------------------
            // source: xoico_forward.h

            // group: xoico_forward
            BCORE_REGISTER_FFUNC( xoico_parse, xoico_forward_s_parse );
            BCORE_REGISTER_FFUNC( xoico_get_hash, xoico_forward_s_get_hash );
            BCORE_REGISTER_FFUNC( xoico_get_global_name_sc, xoico_forward_s_get_global_name_sc );
            BCORE_REGISTER_FFUNC( xoico_expand_declaration, xoico_forward_s_expand_declaration );
            BCORE_REGISTER_FFUNC( xoico_expand_forward, xoico_forward_s_expand_forward );
            BCORE_REGISTER_FFUNC( xoico_expand_init1, xoico_forward_s_expand_init1 );
            BCORE_REGISTER_OBJECT( xoico_forward_s );
            XOILA_REGISTER_SPECT( xoico_forward );

            // --------------------------------------------------------------------
            // source: xoico_typespec.h

            // group: xoico_typespec
            BCORE_REGISTER_NAME( type_deduce );
            BCORE_REGISTER_NAME( type_object );
            BCORE_REGISTER_FFUNC( xoico_get_hash, xoico_typespec_s_get_hash );
            BCORE_REGISTER_OBJECT( xoico_typespec_s );
            XOILA_REGISTER_SPECT( xoico_typespec );

            // --------------------------------------------------------------------
            // source: xoico_arg.h

            // group: xoico_arg
            BCORE_REGISTER_FFUNC( xoico_parse, xoico_arg_s_parse );
            BCORE_REGISTER_FFUNC( xoico_get_hash, xoico_arg_s_get_hash );
            BCORE_REGISTER_OBJECT( xoico_arg_s );
            XOILA_REGISTER_SPECT( xoico_arg );

            // --------------------------------------------------------------------
            // source: xoico_args.h

            // group: xoico_args
            BCORE_REGISTER_FFUNC( xoico_parse, xoico_args_s_parse );
            BCORE_REGISTER_FFUNC( xoico_get_hash, xoico_args_s_get_hash );
            BCORE_REGISTER_OBJECT( xoico_args_s );
            XOILA_REGISTER_SPECT( xoico_args );

            // --------------------------------------------------------------------
            // source: xoico_signature.h

            // group: xoico_signature
            BCORE_REGISTER_FFUNC( xoico_parse, xoico_signature_s_parse );
            BCORE_REGISTER_FFUNC( xoico_get_hash, xoico_signature_s_get_hash );
            BCORE_REGISTER_FFUNC( xoico_get_global_name_sc, xoico_signature_s_get_global_name_sc );
            BCORE_REGISTER_OBJECT( xoico_signature_s );
            XOILA_REGISTER_SPECT( xoico_signature );

            // --------------------------------------------------------------------
            // source: xoico_body.h

            // group: xoico_body
            BCORE_REGISTER_FFUNC( xoico_get_hash, xoico_body_code_s_get_hash );
            BCORE_REGISTER_OBJECT( xoico_body_code_s );
            BCORE_REGISTER_FFUNC( xoico_get_hash, xoico_body_s_get_hash );
            BCORE_REGISTER_FFUNC( xoico_get_global_name_sc, xoico_body_s_get_global_name_sc );
            BCORE_REGISTER_OBJECT( xoico_body_s );
            XOILA_REGISTER_SPECT( xoico_body );

            // --------------------------------------------------------------------
            // source: xoico_feature.h

            // group: xoico_feature
            BCORE_REGISTER_FFUNC( xoico_parse, xoico_feature_s_parse );
            BCORE_REGISTER_FFUNC( xoico_get_hash, xoico_feature_s_get_hash );
            BCORE_REGISTER_FFUNC( xoico_get_global_name_sc, xoico_feature_s_get_global_name_sc );
            BCORE_REGISTER_FFUNC( xoico_expand_indef_typedef, xoico_feature_s_expand_indef_typedef );
            BCORE_REGISTER_FFUNC( xoico_expand_spect_declaration, xoico_feature_s_expand_spect_declaration );
            BCORE_REGISTER_FFUNC( xoico_expand_spect_definition, xoico_feature_s_expand_spect_definition );
            BCORE_REGISTER_FFUNC( xoico_expand_indef_declaration, xoico_feature_s_expand_indef_declaration );
            BCORE_REGISTER_FFUNC( xoico_expand_definition, xoico_feature_s_expand_definition );
            BCORE_REGISTER_FFUNC( xoico_expand_init1, xoico_feature_s_expand_init1 );
            BCORE_REGISTER_OBJECT( xoico_feature_s );
            XOILA_REGISTER_SPECT( xoico_feature );

            // --------------------------------------------------------------------
            // source: xoico_func.h

            // group: xoico_func
            BCORE_REGISTER_OBJECT( xoico_func_s );
            XOILA_REGISTER_SPECT( xoico_func );

            // --------------------------------------------------------------------
            // source: xoico_funcs.h

            // group: xoico_funcs
            BCORE_REGISTER_OBJECT( xoico_funcs_s );
            XOILA_REGISTER_SPECT( xoico_funcs );

            // --------------------------------------------------------------------
            // source: xoico_group.h

            // group: xoico_group
            BCORE_REGISTER_OBJECT( xoico_group_source_stack_s );
            BCORE_REGISTER_FFUNC( xoico_parse, xoico_group_s_parse );
            BCORE_REGISTER_FFUNC( xoico_get_hash, xoico_group_s_get_hash );
            BCORE_REGISTER_FFUNC( xoico_get_global_name_sc, xoico_group_s_get_global_name_sc );
            BCORE_REGISTER_FFUNC( xoico_get_global_name_tp, xoico_group_s_get_global_name_tp );
            BCORE_REGISTER_FFUNC( xoico_finalize, xoico_group_s_finalize );
            BCORE_REGISTER_FFUNC( xoico_expand_setup, xoico_group_s_expand_setup );
            BCORE_REGISTER_OBJECT( xoico_group_s );
            XOILA_REGISTER_SPECT( xoico_group );

            // --------------------------------------------------------------------
            // source: xoico_stamp.h

            // group: xoico_stamp
            BCORE_REGISTER_FFUNC( xoico_get_hash, xoico_stamp_s_get_hash );
            BCORE_REGISTER_FFUNC( xoico_get_global_name_sc, xoico_stamp_s_get_global_name_sc );
            BCORE_REGISTER_FFUNC( xoico_get_global_name_tp, xoico_stamp_s_get_global_name_tp );
            BCORE_REGISTER_FFUNC( xoico_finalize, xoico_stamp_s_finalize );
            BCORE_REGISTER_FFUNC( xoico_expand_setup, xoico_stamp_s_expand_setup );
            BCORE_REGISTER_FFUNC( xoico_expand_declaration, xoico_stamp_s_expand_declaration );
            BCORE_REGISTER_FFUNC( xoico_expand_forward, xoico_stamp_s_expand_forward );
            BCORE_REGISTER_FFUNC( xoico_expand_indef_declaration, xoico_stamp_s_expand_indef_declaration );
            BCORE_REGISTER_FFUNC( xoico_expand_definition, xoico_stamp_s_expand_definition );
            BCORE_REGISTER_FFUNC( xoico_expand_init1, xoico_stamp_s_expand_init1 );
            BCORE_REGISTER_OBJECT( xoico_stamp_s );
            XOILA_REGISTER_SPECT( xoico_stamp );

            // --------------------------------------------------------------------
            // source: xoico_nested_group.h

            // group: xoico_nested_group
            BCORE_REGISTER_FFUNC( xoico_get_hash, xoico_nested_group_s_get_hash );
            BCORE_REGISTER_FFUNC( xoico_expand_forward, xoico_nested_group_s_expand_forward );
            BCORE_REGISTER_FFUNC( xoico_expand_indef_declaration, xoico_nested_group_s_expand_indef_declaration );
            BCORE_REGISTER_OBJECT( xoico_nested_group_s );
            XOILA_REGISTER_SPECT( xoico_nested_group );

            // --------------------------------------------------------------------
            // source: xoico_source.h

            // group: xoico_source
            BCORE_REGISTER_FFUNC( xoico_finalize, xoico_source_s_finalize );
            BCORE_REGISTER_FFUNC( xoico_expand_setup, xoico_source_s_expand_setup );
            BCORE_REGISTER_OBJECT( xoico_source_s );
            XOILA_REGISTER_SPECT( xoico_source );

            // --------------------------------------------------------------------
            // source: xoico_target.h

            // group: xoico_target
            BCORE_REGISTER_FFUNC( xoico_finalize, xoico_target_s_finalize );
            BCORE_REGISTER_FFUNC( xoico_expand_setup, xoico_target_s_expand_setup );
            BCORE_REGISTER_OBJECT( xoico_target_s );
            XOILA_REGISTER_SPECT( xoico_target );

            // --------------------------------------------------------------------
            // source: xoico_compiler.h

            // group: xoico_compiler
            BCORE_REGISTER_OBJECT( xoico_compiler_type_info_s );
            BCORE_REGISTER_OBJECT( xoico_compiler_element_info_s );
            BCORE_REGISTER_FFUNC( xoico_finalize, xoico_compiler_s_finalize );
            BCORE_REGISTER_FFUNC( xoico_expand_setup, xoico_compiler_s_expand_setup );
            BCORE_REGISTER_FFUNC( bcore_inst_call_init_x, xoico_compiler_s_init_x );
            BCORE_REGISTER_OBJECT( xoico_compiler_s );
            XOILA_REGISTER_SPECT( xoico_compiler );

            // --------------------------------------------------------------------
            // source: xoico_builder.h

            // group: xoico_builder
            BCORE_REGISTER_OBJECT( xoico_builder_arr_target_s );
            BCORE_REGISTER_FFUNC( bcore_via_call_source, xoico_builder_target_s_source );
            BCORE_REGISTER_OBJECT( xoico_builder_target_s );
            BCORE_REGISTER_OBJECT( xoico_builder_main_s );
            XOILA_REGISTER_SPECT( xoico_builder );

            // --------------------------------------------------------------------
            // source: xoico_cengine.h

            // group: xoico_cengine
            BCORE_REGISTER_FEATURE( xoico_cengine_translate );
            BCORE_REGISTER_FEATURE( xoico_cengine_get_hash );
            BCORE_REGISTER_FFUNC( xoico_cengine_get_hash, xoico_cengine_get_hash_default );
            XOILA_REGISTER_SPECT( xoico_cengine );

            // --------------------------------------------------------------------
            // source: xoico_caleph.h

            // group: xoico_caleph
            BCORE_REGISTER_FFUNC( xoico_cengine_translate, xoico_caleph_s_translate );
            BCORE_REGISTER_OBJECT( xoico_caleph_s );
            XOILA_REGISTER_SPECT( xoico_caleph );

            // --------------------------------------------------------------------
            // source: xoico_cbeth.h

            // group: xoico_cbeth
            BCORE_REGISTER_FFUNC( xoico_cengine_translate, xoico_cbeth_s_translate );
            BCORE_REGISTER_OBJECT( xoico_cbeth_s );
            XOILA_REGISTER_SPECT( xoico_cbeth );

            // group: xoico_cbeth_tn
            BCORE_REGISTER_OBJECT( xoico_cbeth_tn_unit_s );
            BCORE_REGISTER_OBJECT( xoico_cbeth_tn_adl_s );
            BCORE_REGISTER_OBJECT( xoico_cbeth_tn_stack_s );
            XOILA_REGISTER_SPECT( xoico_cbeth_tn );

            // --------------------------------------------------------------------
            // source: xoico_cgimel.h

            // group: xoico_cgimel
            BCORE_REGISTER_NAME( static );
            BCORE_REGISTER_NAME( volatile );
            BCORE_REGISTER_NAME( cast );
            BCORE_REGISTER_FFUNC( xoico_cengine_translate, xoico_cgimel_s_translate );
            BCORE_REGISTER_OBJECT( xoico_cgimel_s );
            XOILA_REGISTER_SPECT( xoico_cgimel );

            // group: xoico_cgimel_stack
            BCORE_REGISTER_OBJECT( xoico_cgimel_stack_unit_s );
            BCORE_REGISTER_OBJECT( xoico_cgimel_stack_unit_adl_s );
            BCORE_REGISTER_OBJECT( xoico_cgimel_stack_s );
            XOILA_REGISTER_SPECT( xoico_cgimel_stack );

            // --------------------------------------------------------------------
            // source: xoico_cdaleth.h

            // group: xoico_cdaleth
            BCORE_REGISTER_NAME( static );
            BCORE_REGISTER_NAME( volatile );
            BCORE_REGISTER_NAME( cast );
            BCORE_REGISTER_NAME( verbatim_C );
            BCORE_REGISTER_NAME( keep );
            BCORE_REGISTER_NAME( if );
            BCORE_REGISTER_NAME( else );
            BCORE_REGISTER_NAME( while );
            BCORE_REGISTER_NAME( do );
            BCORE_REGISTER_NAME( for );
            BCORE_REGISTER_NAME( switch );
            BCORE_REGISTER_NAME( case );
            BCORE_REGISTER_NAME( break );
            BCORE_REGISTER_NAME( return );
            BCORE_REGISTER_FFUNC( xoico_cengine_translate, xoico_cdaleth_s_translate );
            BCORE_REGISTER_OBJECT( xoico_cdaleth_s );
            XOILA_REGISTER_SPECT( xoico_cdaleth );

            // group: xoico_cdaleth_stack_var
            BCORE_REGISTER_OBJECT( xoico_cdaleth_stack_var_unit_s );
            BCORE_REGISTER_OBJECT( xoico_cdaleth_stack_var_unit_adl_s );
            BCORE_REGISTER_OBJECT( xoico_cdaleth_stack_var_s );
            XOILA_REGISTER_SPECT( xoico_cdaleth_stack_var );

            // group: xoico_cdaleth_stack_block
            BCORE_REGISTER_OBJECT( xoico_cdaleth_stack_block_unit_s );
            BCORE_REGISTER_OBJECT( xoico_cdaleth_stack_block_unit_adl_s );
            BCORE_REGISTER_OBJECT( xoico_cdaleth_stack_block_s );
            XOILA_REGISTER_SPECT( xoico_cdaleth_stack_block );
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
// XOILA_OUT_SIGNATURE 0xAAF67D72C319983Eull
