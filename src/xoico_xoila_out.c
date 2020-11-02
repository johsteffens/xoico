/** This file was generated from xoila source code.
 *  Compiling Agent : xoico_compiler (C) 2020 J.B.Steffens
 *  Last File Update: 2020-11-02T16:36:37Z
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
 *  xoico_cdaleth.x
 *  xoico_cdaleth_builtin.x
 *  xoico_cdaleth_control.x
 *  xoico_compiler.x
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
    "tp_t name;"
    "tp_t global_name;"
    "xoico_typespec_s typespec_ret;"
    "xoico_args_s args;"
    "tp_t arg_o;"
    "hidden aware xoico_group_s* group;"
    "hidden aware xoico_stamp_s* stamp;"
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
    "xoico_func_s => func_a;"
    "xoico_func_s => func_a_defines;"
    "xoico_func_s => func_t;"
    "xoico_func_s => func_t_defines;"
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
    "tp_t signature_global_name;"
    "st_s flect_decl;"
    "bl_t expandable = true;"
    "bl_t overloadable = false;"
    "xoico_body_s => body;"
    "tp_t pre_hash = 0;"
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
    "hidden bcore_hmap_tpvd_s hmap_func;"
    "hidden bcore_hmap_tp_s hmap_external_type;"
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

bl_t xoico_compiler_s_is_type( const xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:124:5
    if( xoico_compiler_s_is_group( o, name ) ) return  true;
    if( xoico_compiler_s_is_stamp( o, name ) ) return  true;
    if( bcore_hmap_tp_s_exists( &(o->hmap_external_type), name ) ) return  true;
    return  false;
}

bl_t xoico_compiler_s_is_stamp( const xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:132:5
    const xoico* item = xoico_compiler_s_get_const_item( o, name );
    if( item && ( item->_ == TYPEOF_xoico_stamp_s ) ) return  true;
    return  false;
}

bl_t xoico_compiler_s_is_signature( const xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:139:5
    const xoico* item = xoico_compiler_s_get_const_item( o, name );
    if( item && ( item->_ == TYPEOF_xoico_signature_s ) ) return  true;
    return  false;
}

bl_t xoico_compiler_s_is_signature_or_feature( const xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:146:5
    const xoico* item = xoico_compiler_s_get_const_item( o, name );
    if( !item ) return  NULL;
    if( item->_ == TYPEOF_xoico_signature_s || item->_ == TYPEOF_xoico_feature_s ) return  true;
    return  false;
}

bl_t xoico_compiler_s_is_feature( const xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:154:5
    const xoico* item = xoico_compiler_s_get_const_item( o, name );
    if( item && ( item->_ == TYPEOF_xoico_feature_s ) ) return  true;
    return  false;
}

const xoico* xoico_compiler_s_get_const_item( const xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:161:5
    vd_t* ptr = bcore_hmap_tpvd_s_get( &(o->hmap_item), name );
    return  ptr ? ( const xoico* )*ptr : NULL;
}

xoico* xoico_compiler_s_get_item( xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:167:5
    vd_t* ptr = bcore_hmap_tpvd_s_get( &(o->hmap_item), name );
    return  ptr ? ( xoico* )*ptr : NULL;
}

xoico_stamp_s* xoico_compiler_s_get_stamp( xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:173:5
    const xoico* item = xoico_compiler_s_get_const_item( o, name );
    return  ( item ) ? ( item->_ == TYPEOF_xoico_stamp_s ) ? ((xoico_stamp_s*)(item)) : NULL : NULL;
}

const xoico_feature_s* xoico_compiler_s_get_feature( const xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:179:5
    const xoico* item = xoico_compiler_s_get_const_item( o, name );
    return  ( item ) ? ( item->_ == TYPEOF_xoico_feature_s ) ? ((xoico_feature_s*)(item)) : NULL : NULL;
}

const xoico_signature_s* xoico_compiler_s_get_signature( const xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:185:5
    const xoico* item = xoico_compiler_s_get_const_item( o, name );
    if( !item ) return  NULL;
    if( item->_ == TYPEOF_xoico_signature_s ) return  ((xoico_signature_s*)(item));
    if( item->_ == TYPEOF_xoico_feature_s   ) return &( ((xoico_feature_s*)(item))->signature);
    return  NULL;
}

xoico_group_s* xoico_compiler_s_get_group( xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:194:5
    vd_t* ptr = bcore_hmap_tpvd_s_get( &(o->hmap_group), name );
    return  ptr ? ( xoico_group_s* )*ptr : NULL;
}

xoico_func_s* xoico_compiler_s_get_func( xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:200:5
    vd_t* ptr = bcore_hmap_tpvd_s_get( &(o->hmap_func), name );
    return  ptr ? ( xoico_func_s* )*ptr : NULL;
}

void xoico_compiler_s_init_x( xoico_compiler_s* o )
{
    // xoico_compiler.h:223:5
    if( o->work_build_time_into_pre_hash )
    {
        o->target_pre_hash = bcore_tp_fold_sc( o->target_pre_hash, __DATE__ );
        o->target_pre_hash = bcore_tp_fold_sc( o->target_pre_hash, __TIME__ );
    }
}

er_t xoico_compiler_s_register_group( xoico_compiler_s* o, const xoico_group_s* group, bcore_source* source )
{
    // xoico_compiler.x:21:1
    if( bcore_hmap_tpvd_s_exists( &(o->hmap_group), group->tp_name ) )
    {
        return  xoico_compiler_s_parse_err_fa( o, source,  "'#<sc_t>' was already registered\n",  xoico_compiler_s_nameof( o, group->tp_name ) );
    }
    bcore_hmap_tpvd_s_set( &(o->hmap_group), group->tp_name,  ( vd_t )group );
    return  0;
}

er_t xoico_compiler_s_register_item( xoico_compiler_s* o, const xoico* item, bcore_source* source )
{
    // xoico_compiler.x:33:1
    tp_t global_id = xoico_a_get_global_name_tp( item);
    if( bcore_hmap_tpvd_s_exists( &(o->hmap_item), global_id ) )
    {
        return  xoico_compiler_s_parse_err_fa( o, source,  "'#<sc_t>' was already registered\n",  xoico_compiler_s_nameof( o, global_id ) );
    }
    bcore_hmap_tpvd_s_set( &(o->hmap_item), global_id,  ( vd_t )item );
    return  0;
}

er_t xoico_compiler_s_register_func( xoico_compiler_s* o, const xoico_func_s* func, bcore_source* source )
{
    // xoico_compiler.x:46:1
    if( bcore_hmap_tpvd_s_exists( &(o->hmap_func), func->global_name ) )
    {
        return  xoico_compiler_s_parse_err_fa( o, source,  "'#<sc_t>' was already registered\n",  xoico_compiler_s_nameof( o, func->global_name ) );
    }
    
    bcore_hmap_tpvd_s_set( &(o->hmap_func), func->global_name,  ( vd_t )func );
    return  0;
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
    "aware xoico_cengine => cengine = xoico_cdaleth_s;"
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
    if( o->name && sc_t_equal( name, o->name->sc ) ) return  o;
    if( o->parent_ ) return  xoico_builder_target_s_name_match( o->parent_, name );
    return  NULL;
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
    return  0;
}

bl_t xoico_builder_main_s_get_dry_run( const xoico_builder_main_s* o )
{
    // xoico_builder.h:131:5
    return  o->compiler->dry_run;
}

er_t xoico_builder_main_s_set_always_expand( xoico_builder_main_s* o, bl_t v )
{
    // xoico_builder.h:136:5
    o->compiler->always_expand = v;
    return  0;
}

bl_t xoico_builder_main_s_get_always_expand( const xoico_builder_main_s* o )
{
    // xoico_builder.h:142:5
    return  o->compiler->always_expand;
}

er_t xoico_builder_main_s_set_overwrite_unsigned_target_files( xoico_builder_main_s* o, bl_t v )
{
    // xoico_builder.h:147:5
    o->compiler->overwrite_unsigned_target_files = v;
    return  0;
}

bl_t xoico_builder_main_s_get_overwrite_unsigned_target_files( const xoico_builder_main_s* o )
{
    // xoico_builder.h:153:5
    return  o->compiler->overwrite_unsigned_target_files;
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
    "feature aware xoico_cengine : is_reserved = xoico_cengine_is_reserved_default;"
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
    return  name;
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
    return  o;
}

xoico_cbeth_tn_stack_s* xoico_cbeth_tn_stack_s_push_sc( xoico_cbeth_tn_stack_s* o, sc_t type, sc_t name, sz_t level )
{
    // xoico_cbeth.h:68:9
    xoico_cbeth_tn_unit_s* unit = xoico_cbeth_tn_unit_s_create();
    unit->type = bcore_hmap_name_s_set_sc( &o->name_map, type );
    unit->name = bcore_hmap_name_s_set_sc( &o->name_map, name );
    unit->level = level;
    xoico_cbeth_tn_adl_s_push_d( &o->adl, unit );
    return  o;
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
    return  o;
}

tp_t xoico_cbeth_tn_stack_s_get_type( xoico_cbeth_tn_stack_s* o, tp_t name )
{
    // xoico_cbeth.h:90:9
    for( sz_t i = o->adl.size - 1; i >= 0; i-- )
    {
        if( o->adl.data[ i ]->name == name ) return  o->adl.data[ i ]->type;
    }
    return  0;
}

sc_t xoico_cbeth_tn_stack_s_get_type_sc( xoico_cbeth_tn_stack_s* o, sc_t name )
{
    // xoico_cbeth.h:99:9
    return  bcore_hmap_name_s_get_sc( &o->name_map, xoico_cbeth_tn_stack_s_get_type( o, btypeof( name ) ) );
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
    return  name;
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
    return  o;
}

const xoico_typespec_s* xoico_cgimel_stack_s_get_typespec( const xoico_cgimel_stack_s* o, tp_t name )
{
    // xoico_cgimel.h:65:9
    for( sz_t i = o->adl.size - 1; i >= 0; i-- )
    {
        if( o->adl.data[ i ]->name == name ) return  &o->adl.data[ i ]->typespec;
    }
    return  NULL;
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
    "sz_t try_block_level;"
    "xoico_cdaleth_stack_var_s stack_var;"
    "xoico_cdaleth_stack_block_s stack_block;"
    "bcore_hmap_name_s hmap_name;"
    "func xoico_cengine:is_reserved;"
    "func xoico_cengine:translate;"
"}";

bl_t xoico_cdaleth_s_is_reserved( const xoico_cdaleth_s* o, tp_t tp_identifier )
{
    // xoico_cdaleth.h:218:5
    return  xoico_cdaleth_s_is_builtin_func( o, tp_identifier ) ||
           xoico_cdaleth_s_is_control_name( o, tp_identifier ) ||
           tp_identifier == TYPEOF_verbatim_C;
}

sc_t xoico_cdaleth_s_nameof( xoico_cdaleth_s* o, tp_t type )
{
    // xoico_cdaleth.h:227:5
    sc_t name = bcore_hmap_name_s_get_sc( &(o->hmap_name), type );
    if( !name ) name = xoico_compiler_s_nameof( o->compiler, type );
    return  name;
}

void xoico_cdaleth_s_init_level0( xoico_cdaleth_s* o )
{
    // xoico_cdaleth.h:234:5
    xoico_cdaleth_stack_block_s_clear( &(o->stack_block));
    xoico_cdaleth_stack_block_s_push( &(o->stack_block));
    o->level = 0;
}

void xoico_cdaleth_s_inc_block( xoico_cdaleth_s* o )
{
    // xoico_cdaleth.h:241:5
    xoico_cdaleth_stack_block_s_push( &(o->stack_block));
    o->level++;
    xoico_cdaleth_s_stack_block_get_top_unit( o)->level = o->level;
}

void xoico_cdaleth_s_dec_block( xoico_cdaleth_s* o )
{
    // xoico_cdaleth.h:248:5
    xoico_cdaleth_stack_var_s_pop_level( &(o->stack_var), o->level );
    o->level--;
    ASSERT( o->level >= 0 );
    xoico_cdaleth_stack_block_s_pop( &(o->stack_block));
}

xoico_cdaleth_stack_block_unit_s* xoico_cdaleth_s_stack_block_get_top_unit( xoico_cdaleth_s* o )
{
    // xoico_cdaleth.h:256:5
    return  o->stack_block.adl.data[ o->stack_block.adl.size - 1 ];
}

xoico_cdaleth_stack_block_unit_s* xoico_cdaleth_s_stack_block_get_bottom_unit( xoico_cdaleth_s* o )
{
    // xoico_cdaleth.h:261:5
    return  o->stack_block.adl.data[ 0 ];
}

xoico_cdaleth_stack_block_unit_s* xoico_cdaleth_s_stack_block_get_level_unit( xoico_cdaleth_s* o, sz_t level )
{
    // xoico_cdaleth.h:266:5
    {const xoico_cdaleth_stack_block_unit_adl_s* __a=&(o->stack_block.adl );if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_cdaleth_stack_block_unit_s* e=__a->data[__i]; if( e->level == level ) return  e;
    }}ERR_fa( "Level #<sz_t> not found.", level );
    return  NULL;
}

void xoico_cdaleth_s_push_typedecl( xoico_cdaleth_s* o, const xoico_typespec_s* typespec, tp_t name )
{
    // xoico_cdaleth.h:273:5
    BLM_INIT_LEVEL(0);xoico_cdaleth_stack_var_unit_s* unit = ((xoico_cdaleth_stack_var_unit_s*)BLM_LEVEL_T_PUSH(0,xoico_cdaleth_stack_var_unit_s,xoico_cdaleth_stack_var_unit_s_create()));
    unit->level = o->level;
    unit->name = name;
    xoico_typespec_s_copy( &(unit->typespec), typespec );
    xoico_cdaleth_stack_var_s_push_unit( &(o->stack_var), unit );
        BLM_DOWN();
}

bl_t xoico_cdaleth_s_returns_a_value( const xoico_cdaleth_s* o )
{
    // xoico_cdaleth.h:287:5
    return  ( o->typespec_ret->type != TYPEOF_void ) || ( o->typespec_ret->indirection > 0 );
}

er_t xoico_cdaleth_s_parse( const xoico_cdaleth_s* o, bcore_source* source, sc_t format )
{
    // xoico_cdaleth.h:292:5
    return  bcore_source_a_parse_em_fa( source, format );
}

er_t xoico_cdaleth_s_trans( const xoico_cdaleth_s* o, bcore_source* source, sc_t format, st_s* buf )
{
    // xoico_cdaleth.h:297:5
    BLM_TRY(xoico_cdaleth_s_parse( o, source,  format ))
    st_s_push_sc( buf, format );
    return  0;
}

tp_t xoico_cdaleth_s_get_identifier( xoico_cdaleth_s* o, bcore_source* source, bl_t take_from_source )
{
    // xoico_cdaleth.x:26:1
    BLM_INIT_LEVEL(0);tp_t tp_identifier = 0;
    if( bcore_source_a_parse_bl( source, "#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||[0]=='_'||[0]=='@'||[0]=='$'||([0]==':'&&([1]!=' '&&[1]!='\t'&&[1]!='\n'&&[1]!='/')))" ) )
    {
        sz_t source_index = take_from_source ? 0 : bcore_source_a_get_index( source);
        switch( bcore_source_a_inspect_char( source) )
        {
            case '@':
            {
                bcore_source_a_get_char( source);
                st_s* st_name = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create() ));
                st_s_copy( st_name, o->stamp ? &o->stamp->st_name : &o->group->st_name );
                if( bcore_source_a_parse_bl( source, "#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||[0]=='_'||([0]>='0'&&[0]<='9'))" ) )
                {
                    xoico_cdaleth_s_parse_fa( o, source,  "#:name",  st_name );
                }
                tp_identifier = xoico_cdaleth_s_entypeof( o, st_name->sc );
            }
            break;
    
            case '$':
            {
                bcore_source_a_get_char( source);
                tp_identifier = TYPEOF_type_deduce;
            }
            break;
    
            case ':':
            {
                st_s* st_name = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create() ));
                xoico_group_s_parse_name( o->group, st_name,  source );
                tp_identifier = xoico_cdaleth_s_entypeof( o, st_name->sc );
            }
            break;
    
            default:
            {
                st_s* st_name = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create() ));
                bcore_source_a_parse_fa( source, "#name",  st_name );
                tp_identifier = xoico_cdaleth_s_entypeof( o, st_name->sc );
            }
            break;
        }
    
        if( !take_from_source ) bcore_source_a_set_index( source, source_index );
    }
    
    BLM_RETURNV(tp_t, tp_identifier)
}

er_t xoico_cdaleth_s_trans_identifier( xoico_cdaleth_s* o, bcore_source* source, st_s* buf, tp_t* tp_identifier )
{
    // xoico_cdaleth.x:80:1
    {
    
        tp_t identifier = xoico_cdaleth_s_get_identifier( o, source,  true );
        if( !identifier )
        {
            return  xoico_cdaleth_s_parse_err_fa( o, source,  "Identifier exected" );
        }
        if( tp_identifier ) *tp_identifier = identifier;
        if( buf ) st_s_push_sc( buf, xoico_cdaleth_s_nameof( o, identifier ) );
        return  0;
    } // try
}

er_t xoico_cdaleth_s_trans_number_literal( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth.x:99:1
    {
        bl_t hex = false;
        if( bcore_source_a_parse_bl( source, "#?'0x'" ) )
        {
            st_s_push_sc( buf, "0x" );
            hex = true;
        }
        else if( bcore_source_a_parse_bl( source, "#?'0X'" ) )
        {
            st_s_push_sc( buf, "0X" );
            hex = true;
        }
    
        if( hex )
        {
            while( bcore_source_a_parse_bl( source, "#?(([0]>='0'&&[0]<='9')||([0]>='a'&&[0]<='f')||([0]>='A'&&[0]<='F'))" ) )
            {
                st_s_push_char( buf, bcore_source_a_get_char( source) );
            }
        }
        else // decimal
        {
            while( bcore_source_a_parse_bl( source, "#?([0]>='0'&&[0]<='9')" ) )
            {
                st_s_push_char( buf, bcore_source_a_get_char( source) );
            }
        }
    
        bl_t fraction = false;
    
        if( bcore_source_a_parse_bl( source, "#?([0]=='.')" ) )
        {
            st_s_push_char( buf, bcore_source_a_get_char( source) );
            fraction = true;
        }
    
        if( fraction )
        {
            while( bcore_source_a_parse_bl( source, "#?([0]>='0'&&[0]<='9')" ) )
            {
                st_s_push_char( buf, bcore_source_a_get_char( source) );
            }
        }
    
        bl_t exponent = false;
    
        if( bcore_source_a_parse_bl( source, "#?([0]=='e'&&[0]=='E')" ) )
        {
            st_s_push_char( buf, bcore_source_a_get_char( source) );
            exponent = true;
        }
    
        if( exponent )
        {
            if( bcore_source_a_parse_bl( source, "#?([0]=='+'||[0]=='-')" ) )
            {
                st_s_push_char( buf, bcore_source_a_get_char( source) );
            }
    
            while( bcore_source_a_parse_bl( source, "#?([0]>='0'&&[0]<='9')" ) )
            {
                st_s_push_char( buf, bcore_source_a_get_char( source) );
            }
        }
    
        // suffix
        while( bcore_source_a_parse_bl( source, "#?([0]=='l'||[0]=='L'||[0]=='u'||[0]=='U'||[0]=='f'||[0]=='F')" ) )
        {
            st_s_push_char( buf, bcore_source_a_get_char( source) );
        }
    
        return  0;
    } // try
}

er_t xoico_cdaleth_s_trans_string_literal( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth.x:180:1
    {
        BLM_TRY(xoico_cdaleth_s_trans( o, source,  "\"",  buf ))
    
        while( !bcore_source_a_eos( source) && !bcore_source_a_parse_bl( source, "#=?'\"'" ) )
        {
            if( bcore_source_a_parse_bl( source, "#?'\\'" ) ) st_s_push_char( buf, '\\' );
            st_s_push_char( buf, bcore_source_a_get_char( source) );
        }
    
        BLM_TRY(xoico_cdaleth_s_trans( o, source,  "\"",  buf ))
        return  0;
    } // try
}

er_t xoico_cdaleth_s_trans_char_literal( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth.x:200:1
    {
        BLM_TRY(xoico_cdaleth_s_trans( o, source,  "'",  buf ))
    
        while( !bcore_source_a_eos( source) && !bcore_source_a_parse_bl( source, "#=?|'|" ) )
        {
            if( bcore_source_a_parse_bl( source, "#?'\\'" ) ) st_s_push_char( buf, '\\' );
            st_s_push_char( buf, bcore_source_a_get_char( source) );
        }
    
        BLM_TRY(xoico_cdaleth_s_trans( o, source,  "'",  buf ))
        return  0;
    } // try
}

er_t xoico_cdaleth_s_trans_whitespace( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth.x:220:1
    {
        bl_t exit_loop = false;
        while( !exit_loop && !bcore_source_a_eos( source) )
        {
            char c =  bcore_source_a_inspect_char( source);
            switch( c )
            {
                case ' ' :
                case '\t':
                case '\n':
                {
                    char c =  bcore_source_a_get_char( source);
                    if( buf )  st_s_push_char( buf, c );
                }
                break;
    
                case '/':
                {
                    if( bcore_source_a_parse_bl( source, "#?'//'" ) )
                    {
                        if( buf ) st_s_push_sc( buf, "//" );
                        while( !bcore_source_a_eos( source) )
                        {
                            char c =  bcore_source_a_get_char( source);
                            if( buf ) st_s_push_char( buf, c );
                            if( c == '\n' ) break;
                        }
                    }
                    else if( bcore_source_a_parse_bl( source, "#?'/*'" ) )
                    {
                        if( buf ) st_s_push_sc( buf, "/*" );
                        while( !bcore_source_a_eos( source) )
                        {
                            if( bcore_source_a_parse_bl( source, "#?'*/'" ) )
                            {
                                if( buf ) st_s_push_sc( buf, "*/" );
                                break;
                            }
                            char c =  bcore_source_a_get_char( source);
                            if( buf ) st_s_push_char( buf, c );
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
        return  0;
    } // try
}

er_t xoico_cdaleth_s_trans_preprocessor( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth.x:285:1
    {
        BLM_TRY(xoico_cdaleth_s_parse( o, source,  "##" ))
        st_s_push_sc( buf, "#" );
        while( !bcore_source_a_eos( source) )
        {
            char c = bcore_source_a_get_char( source);
            st_s_push_char( buf, c );
            if( c == '\\' && bcore_source_a_inspect_char( source) == '\n' ) st_s_push_char( buf, bcore_source_a_get_char( source) );
            if( c == '\n' ) break;
        }
        return  0;
    } // try
}

tp_t xoico_cdaleth_s_trans_inert_operator( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth.x:305:1
    switch( bcore_source_a_inspect_char( source) )
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
            st_s_push_char( buf, bcore_source_a_get_char( source) );
            return  1;
        }
        break;
    
        default: break;
    }
    
    return  false;
}

er_t xoico_cdaleth_s_adapt_expression( xoico_cdaleth_s* o, bcore_source* source, const xoico_typespec_s* typespec_expr, const xoico_typespec_s* typespec_target, const st_s* expr, st_s* buf )
{
    // xoico_cdaleth.x:347:1
    {
        if( !typespec_expr->type )
        {
            return  xoico_cdaleth_s_parse_err_fa( o, source, 
                "xoico_cdaleth_s_adapt_expression: no type specified.", 
                typespec_expr->indirection, 
                typespec_target->indirection
            );
        }
    
        bl_t no_adaptation =
            ( typespec_target->indirection == typespec_expr->indirection ) ||
            ( typespec_expr->type == TYPEOF_vd_t ) ||
            ( typespec_expr->type == TYPEOF_vc_t );
    
        if( no_adaptation )
        {
            st_s_push_fa( buf, "#<st_s*>",  expr );
        }
        else if( typespec_target->indirection == typespec_expr->indirection + 1 )
        {
            if( typespec_expr->flag_addressable )
            {
                st_s_push_fa( buf, "&(#<st_s*>)",  expr );
            }
            else
            {
                return  xoico_cdaleth_s_parse_err_fa( o, source,  "Increasing indirection: Expression has no address." );
            }
        }
        else if( typespec_target->indirection == typespec_expr->indirection - 1 )
        {
            st_s_push_fa( buf, "*(#<st_s*>)",  expr );
        }
        else
        {
            return  xoico_cdaleth_s_parse_err_fa( o, source, 
                "Cannot adapt from expression's indirection '#<sz_t>' to target indirection '#<sz_t>'.", 
                typespec_expr->indirection, 
                typespec_target->indirection
            );
        }
        return  0;
    } // try
}

er_t xoico_cdaleth_s_trans_typespec_expression( xoico_cdaleth_s* o, bcore_source* source, st_s* buf, const xoico_typespec_s* in_typespec, xoico_typespec_s* out_typespec )
{
    // xoico_cdaleth.x:412:1
    BLM_INIT_LEVEL(0);{
        BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  buf ))
    
        if( out_typespec ) out_typespec->type = 0;
    
        if( bcore_source_a_parse_bl_fa( source, "#?([0]=='.'||([0]=='-'&&[1]=='>'))" ) )
        {
            if( bcore_source_a_parse_bl_fa( source, "#?'->'" ) )
            {
                if( in_typespec->indirection != 1 )
                {
                    return  xoico_cdaleth_s_parse_err_fa( o, source,  "Given indirection is '#<sz_t>'. '->' can only be used at indirection '1'.",  in_typespec->indirection );
                }
            }
            else
            {
                BLM_TRY(xoico_cdaleth_s_parse( o, source,  "." ))
            }
            BLM_TRY(xoico_cdaleth_s_parse( o, source,  " " ))
            xoico_compiler_element_info_s* info = ((xoico_compiler_element_info_s*)BLM_LEVEL_T_PUSH(0,xoico_compiler_element_info_s,xoico_compiler_element_info_s_create() ));
            if( bcore_source_a_parse_bl_fa( source, "#=?'['" ) || bcore_source_a_parse_bl_fa( source, "#=?'?['" ) ) // array subscript
            {
                bl_t bounds_check = false;
                if( bcore_source_a_parse_bl_fa( source, "#=?'?'" ) )
                {
                    BLM_TRY(xoico_cdaleth_s_parse( o, source,  "?[" ))
                    bounds_check = true;
                }
                else
                {
                    BLM_TRY(xoico_cdaleth_s_parse( o, source,  "[" ))
                }
    
                if( bounds_check ) BLM_RETURNV(er_t, xoico_cdaleth_s_parse_err_fa( o, source,  "Bounds check not yet available." ))
    
                if( in_typespec->indirection > 1 )
                {
                    BLM_RETURNV(er_t, xoico_cdaleth_s_parse_err_fa( o, source, 
                        "Resolving subscript: Indirection '#<sz_t>' is too large.", 
                        in_typespec->indirection
                    ))
                }
    
                st_s_push_fa( buf, "#<sc_t>data[",  ( in_typespec->indirection == 1 ) ? "->" : "." );
                BLM_TRY(xoico_cdaleth_s_trans_expression( o, source,  buf,  NULL ))
                BLM_TRY(xoico_cdaleth_s_parse( o, source,  "]" ))
                st_s_push_sc( buf, "]" );
    
                if( xoico_compiler_s_get_type_array_element_info( o->compiler, in_typespec->type,  info ) )
                {
                    BLM_TRY(xoico_cdaleth_s_trans_typespec_expression( o, source,  buf,  &info->type_info.typespec,  out_typespec ))
                }
                else
                {
                    BLM_TRY(xoico_cdaleth_s_trans_expression( o, source,  buf,  NULL ))
                }
            }
            else // member (object or function)
            {
                st_s* buf_local = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create() ));
                tp_t tp_identifier = 0;
                BLM_TRY(xoico_cdaleth_s_trans_identifier( o, source,  buf_local,  &tp_identifier ))
                BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  buf_local ))
    
                // builtin functions ...
                if( xoico_cdaleth_s_is_builtin_func( o, tp_identifier ) )
                {
                    xoico_typespec_s* typespec_builtin = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create() ));
                    BLM_TRY(xoico_cdaleth_s_trans_builtin( o, tp_identifier,  source,  buf,  in_typespec,  buf_local,  typespec_builtin ))
                    st_s_copy( buf, buf_local );
                    BLM_TRY(xoico_cdaleth_s_trans_typespec_expression( o, source,  buf,  typespec_builtin,  out_typespec ))
                }
                else if( xoico_compiler_s_get_type_element_info( o->compiler, in_typespec->type,  tp_identifier,  info ) )
                {
                    if( info->signature ) // member function
                    {
                        if( !bcore_source_a_parse_bl_fa( source, "#?'('" ) ) BLM_RETURNV(er_t, xoico_cdaleth_s_parse_err_fa( o, source,  "'(' expected" ))
    
                        sc_t sc_func_name = xoico_cdaleth_s_nameof( o, info->type_info.typespec.type );
                        ASSERT( sc_func_name );
    
                        st_s* arg_obj = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_clone( buf) ));
                        st_s_clear( buf);
                        st_s_copy_fa( buf, "#<sc_t>( ",  sc_func_name );
    
                        const xoico_args_s* args = &info->signature->args;
    
                        if( info->signature->arg_o )
                        {
                            xoico_typespec_s* typespec_obj = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_clone( in_typespec) ));
                            typespec_obj->indirection = 1; // first argument of member functions
                            BLM_TRY(xoico_cdaleth_s_adapt_expression( o, source,  in_typespec,  typespec_obj,  arg_obj,  buf ))
                            if( args->size > 0 ) st_s_push_sc( buf, ", " );
                        }
    
                        {const xoico_args_s* __a=args ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_arg_s* arg=&(__a->data[__i]);
                        {BLM_INIT_LEVEL(9);
                            st_s* buf_expr = ((st_s*)BLM_LEVEL_T_PUSH(9,st_s,st_s_create()));
                            BLM_TRY(xoico_cdaleth_s_parse( o, source,  " " ))
                            if( __i > 0 ) BLM_TRY(xoico_cdaleth_s_parse( o, source,  " ," ))
    
                            xoico_typespec_s* typespec_expr = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(9,xoico_typespec_s,xoico_typespec_s_create()));
                            BLM_TRY(xoico_cdaleth_s_trans_expression( o, source,  buf_expr,  typespec_expr ))
    
                            if( __i > 0 ) st_s_push_sc( buf, ", " );
    
                            if( typespec_expr->type )
                            {
                                BLM_TRY(xoico_cdaleth_s_adapt_expression( o, source,  typespec_expr,  &arg->typespec,  buf_expr,  buf ))
                            }
                            else
                            {
                                st_s_push_st( buf, buf_expr );
                            }
                        BLM_DOWN();}
    
                        }}BLM_TRY(xoico_cdaleth_s_parse( o, source,  " )" ))
                        st_s_push_sc( buf, ")" );
    
                        BLM_TRY(xoico_cdaleth_s_trans_typespec_expression( o, source,  buf,  &info->signature->typespec_ret,  out_typespec ))
                    }
                    else // traced member element
                    {
                        if( in_typespec->indirection > 1 )
                        {
                            BLM_RETURNV(er_t, xoico_cdaleth_s_parse_err_fa( o, source, 
                                "Dereferencing #<sc_t>: Indirection '#<sz_t>' is too large.", 
                                xoico_cdaleth_s_nameof( o, tp_identifier ), 
                                in_typespec->indirection
                            ))
                        }
                        st_s_push_fa( buf, "#<sc_t>#<sc_t>",  ( in_typespec->indirection == 1 ) ? "->" : ".",  buf_local->sc );
                        BLM_TRY(xoico_cdaleth_s_trans_typespec_expression( o, source,  buf,  &info->type_info.typespec,  out_typespec ))
                    }
                }
                else if( bcore_source_a_parse_bl_fa( source, "#?'('" ) ) // untraced member function
                {
                    st_s* arg_obj = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_clone( buf) ));
                    st_s_clear( buf );
    
                    /// Untraced member functions of a group are always treated as 'aware'
                    if( xoico_cdaleth_s_is_group( o, in_typespec->type ) )
                    {
                        st_s_copy_fa
                        (
                            buf,
                            "#<sc_t>_a_#<sc_t>( ",
                            xoico_cdaleth_s_nameof( o, in_typespec->type ),
                            xoico_cdaleth_s_nameof( o, tp_identifier )
                        );
                    }
                    else
                    {
                        st_s_copy_fa
                        (
                            buf,
                            "#<sc_t>_#<sc_t>( ",
                            xoico_cdaleth_s_nameof( o, in_typespec->type ),
                            xoico_cdaleth_s_nameof( o, tp_identifier )
                        );
                    }
    
                    {
                        xoico_typespec_s* typespec_obj = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_clone( in_typespec) ));
                        typespec_obj->indirection = 1; // first argument of member functions
                        BLM_TRY(xoico_cdaleth_s_adapt_expression( o, source,  in_typespec,  typespec_obj,  arg_obj,  buf ))
                    }
    
                    bl_t first = true;
                    BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  buf_local ))
                    while( !bcore_source_a_eos( source) )
                    {BLM_INIT_LEVEL(6);
                        if( bcore_source_a_parse_bl_fa( source, "#=?')'" ) ) break;
    
                        st_s* buf_expr = ((st_s*)BLM_LEVEL_T_PUSH(6,st_s,st_s_create()));
                        if( !first ) BLM_TRY(xoico_cdaleth_s_parse( o, source,  "," ))
                        BLM_TRY(xoico_cdaleth_s_trans_expression( o, source,  buf_expr,  NULL ))
                        BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  buf_expr ))
                        st_s_push_fa( buf, ", " );
                        st_s_push_fa( buf, "#<sc_t>",  buf_expr->sc );
                        first = false;
                    BLM_DOWN();}
    
                    BLM_TRY(xoico_cdaleth_s_parse( o, source,  ")" ))
                    st_s_push_sc( buf, ")" );
    
                    BLM_TRY(xoico_cdaleth_s_trans_expression( o, source,  buf,  NULL ))
                }
                else // untraced member element
                {
                    st_s_push_fa( buf, "#<sc_t>#<sc_t>",  ( in_typespec->indirection == 1 ) ? "->" : ".",  buf_local->sc );
                    BLM_TRY(xoico_cdaleth_s_trans_expression( o, source,  buf,  NULL ))
                }
            }
        }
        // array subscript
        else if( bcore_source_a_parse_bl_fa( source, "#?'['" ) )
        {
            if( in_typespec->indirection == 0 )
            {
                if( in_typespec->type != TYPEOF_sc_t && in_typespec->type != TYPEOF_sd_t )
                {
                    BLM_RETURNV(er_t, xoico_cdaleth_s_parse_err_fa( o, source,  "Array subscript requires indirection >= 1." ))
                }
            }
            st_s_push_sc( buf, "[" );
            BLM_TRY(xoico_cdaleth_s_trans_expression( o, source,  buf,  NULL ))
            BLM_TRY(xoico_cdaleth_s_parse( o, source,  "]" ))
            st_s_push_sc( buf, "]" );
    
            xoico_typespec_s* typespec = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_clone( in_typespec) ));
            if( in_typespec->type != TYPEOF_sc_t && in_typespec->type != TYPEOF_sd_t )
            {
                typespec->indirection--;
            }
            BLM_TRY(xoico_cdaleth_s_trans_typespec_expression( o, source,  buf,  typespec,  out_typespec ))
        }
        // create if not present
        else if( bcore_source_a_parse_bl_fa( source, "#?([0]=='!'&&[1]!='=')" ) )
        {
            BLM_TRY(xoico_cdaleth_s_parse( o, source,  "!" ))
    
            //ignore in case indirection is 0;
            if( in_typespec->indirection > 0 )
            {
                if( !( in_typespec->indirection == 1 && in_typespec->flag_addressable ) )
                {
                    BLM_RETURNV(er_t, xoico_cdaleth_s_parse_err_fa( o, source,  "Create-Operator requires lvalue with addressable indirection of 1." ))
                }
    
                if( xoico_cdaleth_s_is_group( o, in_typespec->type ) )
                {
                    BLM_RETURNV(er_t, xoico_cdaleth_s_parse_err_fa( o, source,  "Create-Operator: lvalue is a group." ))
                }
    
                st_s* arg_obj = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_clone( buf) ));
                st_s_clear( buf);
    
                sc_t sc_type = xoico_cdaleth_s_nameof( o, in_typespec->type );
                st_s_push_fa( buf, "BCORE_PASS_CREATE(#<sc_t>,#<sc_t>)",  sc_type,  arg_obj->sc );
            }
    
            BLM_TRY(xoico_cdaleth_s_trans_typespec_expression( o, source,  buf,  in_typespec,  out_typespec ))
        }
        // test for presence
        else if( bcore_source_a_parse_bl_fa( source, "#?([0]=='?'&&[1]=='.')" ) )
        {
            BLM_TRY(xoico_cdaleth_s_parse( o, source,  "?" ))
    
            //ignore in case indirection is 0;
            if( in_typespec->indirection > 0 )
            {
                if( in_typespec->indirection != 1 )
                {
                    BLM_RETURNV(er_t, xoico_cdaleth_s_parse_err_fa( o, source,  "Test-Operator requires lvalue with indirection of 1." ))
                }
    
                st_s* arg_obj = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_clone( buf) ));
                st_s_clear( buf );
    
                sc_t sc_type = xoico_cdaleth_s_nameof( o, in_typespec->type );
                st_s_push_fa( buf, "BCORE_PASS_TEST(#<sc_t>,#<sc_t>)",  sc_type,  arg_obj->sc );
            }
    
            BLM_TRY(xoico_cdaleth_s_trans_typespec_expression( o, source,  buf,  in_typespec,  out_typespec ))
        }
        // attach (detach)
        else if( bcore_source_a_parse_bl_fa( source, "#?'=<'" ) )
        {
            if( !( in_typespec->indirection == 1 && in_typespec->flag_addressable ) )
            {
                BLM_RETURNV(er_t, xoico_cdaleth_s_parse_err_fa( o, source,  "Attach-Operator requires lvalue with addressable indirection of 1" ))
            }
    
            st_s* arg_obj = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_clone( buf) ));
            st_s_clear( buf);
    
            sc_t sc_type = xoico_cdaleth_s_nameof( o, in_typespec->type );
            st_s_push_fa( buf, "#<sc_t>",  sc_type );
    
            xoico_typespec_s* typespec_rval = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create() ));
            if( xoico_cdaleth_s_is_group( o, in_typespec->type ) )
            {
                st_s_push_sc( buf, "_a" );
                st_s_push_fa( buf, "_attach( &(#<sc_t>), (#<sc_t>*)",  arg_obj->sc,  sc_type );
                st_s_push_fa( buf, "(" );
                BLM_TRY(xoico_cdaleth_s_trans_expression( o, source,  buf,  typespec_rval ))
                st_s_push_fa( buf, "))" );
            }
            else
            {
                st_s_push_fa( buf, "_attach( &(#<sc_t>), ",  arg_obj->sc );
                BLM_TRY(xoico_cdaleth_s_trans_expression( o, source,  buf,  typespec_rval ))
                st_s_push_fa( buf, ")" );
            }
    
            if( typespec_rval->type && typespec_rval->indirection != 1 )
            {
                BLM_RETURNV(er_t, xoico_cdaleth_s_parse_err_fa( o, source,  "Attach operator requires rvalue with indirection '1'" ))
            }
    
            if( out_typespec ) xoico_typespec_s_copy( out_typespec, in_typespec );
        }
        // ternary branch operator
        else if( bcore_source_a_parse_bl_fa( source, "#?'?'" ) )
        {
            st_s_push_sc( buf, "?" );
            xoico_typespec_s* typespec_true  = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create() ));
    
            BLM_TRY(xoico_cdaleth_s_trans_expression( o, source,  buf,  typespec_true ))
            BLM_TRY(xoico_cdaleth_s_parse( o, source,  ": " ))
            st_s_push_sc( buf, ": " );
            BLM_TRY(xoico_cdaleth_s_trans_expression( o, source,  buf,  NULL ))
    
            if( out_typespec && typespec_true->type )
            {
                xoico_typespec_s_copy( out_typespec, typespec_true );
                out_typespec->flag_addressable = false;
            }
        }
        else if( out_typespec )
        {
            xoico_typespec_s_copy( out_typespec, in_typespec );
        }
        BLM_RETURNV(er_t, 0)
    } // try
}

er_t xoico_cdaleth_s_trans_member( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth.x:749:1
    {
        if(      bcore_source_a_parse_bl_fa( source, "#?'.'"  ) ) st_s_push_sc( buf, "." );
        else if( bcore_source_a_parse_bl_fa( source, "#?'->'" ) ) st_s_push_sc( buf, "->" );
    
        BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  buf ))
        tp_t tp_identifier = xoico_cdaleth_s_get_identifier( o, source,  false );
    
        if( xoico_cdaleth_s_is_builtin_func( o, tp_identifier ) )
        {
            return  xoico_cdaleth_s_parse_err_fa( o, source,  "Expression before '#<sc_t>' not tractable\n",  xoico_cdaleth_s_nameof( o, tp_identifier ) );
        }
    
        BLM_TRY(xoico_cdaleth_s_trans_identifier( o, source,  buf,  NULL ))
        BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  buf ))
        if( bcore_source_a_parse_bl_fa( source, "#?'('") )
        {
            return  xoico_cdaleth_s_parse_err_fa( o, source,  "Untraced member function '#<sc_t>'\n",  xoico_cdaleth_s_nameof( o, tp_identifier ) );
        }
        return  0;
    } // try
}

er_t xoico_cdaleth_s_try_take_typespec( xoico_cdaleth_s* o, bcore_source* source, xoico_typespec_s* typespec, bl_t require_tractable_type, bl_t* success )
{
    // xoico_cdaleth.x:789:1
    {
        if( success ) *success = false;
    
        sz_t index = bcore_source_a_get_index( source);
    
        BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  NULL ))
        tp_t tp_identifier = xoico_cdaleth_s_get_identifier( o, source,  true );
    
        if( !tp_identifier )
        {
            bcore_source_a_set_index( source, index );
            return  0;
        }
    
        BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  NULL ))
    
        while
        (
            tp_identifier == TYPEOF_const ||
            tp_identifier == TYPEOF_static ||
            tp_identifier == TYPEOF_volatile ||
            tp_identifier == TYPEOF_keep
        )
        {
            if( tp_identifier == TYPEOF_const    ) typespec->flag_const    = true;
            if( tp_identifier == TYPEOF_static   ) typespec->flag_static   = true;
            if( tp_identifier == TYPEOF_volatile ) typespec->flag_volatile = true;
            if( tp_identifier == TYPEOF_keep     ) typespec->flag_keep     = true;
    
            // take fails if keyword is actually a function
            if( bcore_source_a_parse_bl_fa( source, "#?'('" ) )
            {
                bcore_source_a_set_index( source, index );
                return  0;
            }
    
            BLM_TRY(xoico_cdaleth_s_trans_identifier( o, source,  NULL,  &tp_identifier ))
            BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  NULL ))
        }
    
        typespec->type = tp_identifier;
        while( bcore_source_a_parse_bl_fa( source, "#?'*'" ) )
        {
            typespec->indirection++;
            BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  NULL ))
        }
    
        if( require_tractable_type )
        {
            if( !( tp_identifier == TYPEOF_type_deduce || xoico_cdaleth_s_is_type( o, tp_identifier ) ) )
            {
                bcore_source_a_set_index( source, index );
                return  0;
            }
        }
    
        if( success ) *success = true;
        return  0;
    } // try
}

er_t xoico_cdaleth_s_take_typespec( xoico_cdaleth_s* o, bcore_source* source, xoico_typespec_s* typespec, bl_t require_tractable_type )
{
    // xoico_cdaleth.x:864:1
    {
        bl_t success = false;
        BLM_TRY(xoico_cdaleth_s_try_take_typespec( o, source,  typespec,  require_tractable_type,  &success ))
    
        if( !success )
        {
            if( require_tractable_type )
            {
                return  xoico_cdaleth_s_parse_err_fa( o, source,  "Typespec: Syntax error or intractable type." );
            }
            else
            {
                return  xoico_cdaleth_s_parse_err_fa( o, source,  "Typespec: Syntax error." );
            }
        }
    
        return  0;
    } // try
}

er_t xoico_cdaleth_s_push_typespec( xoico_cdaleth_s* o, const xoico_typespec_s* typespec, st_s* buf )
{
    // xoico_cdaleth.x:897:1
    BLM_INIT_LEVEL(0);{
        tp_t type = typespec->type;
    
        if( type == TYPEOF_type_object )
        {
            type = o->obj_type;
        }
        else if( type == TYPEOF_type_deduce )
        {
            ERR_fa( "Cannot resolve 'type_deduce' at this point." );
        }
        else if( type == 0 )
        {
            ERR_fa( "Type is 0." );
        }
    
        st_s* st_type = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,((st_s*)(st_s_create_sc( xoico_cdaleth_s_nameof( o, type ) ))) ));
    
        if( st_type->size == 0 )
        {
            ERR_fa( "Type has no name." );
        }
    
        sc_t sc_type = st_type->sc;
        if( typespec->flag_static   ) st_s_push_fa( buf, "static " );
        if( typespec->flag_const    ) st_s_push_fa( buf, "const " );
        if( typespec->flag_volatile ) st_s_push_fa( buf, "volatile " );
        st_s_push_fa( buf, "#<sc_t>", sc_type );
    
        for( sz_t i = 0; i < typespec->indirection; i++ ) st_s_push_fa( buf, "*" );
        if( typespec->flag_restrict ) st_s_push_fa( buf, "restrict " );
    
        BLM_RETURNV(er_t, 0)
    } // try
}

er_t xoico_cdaleth_s_trans_expression( xoico_cdaleth_s* o, bcore_source* source, st_s* buf_out, xoico_typespec_s* out_typespec )
{
    // xoico_cdaleth.x:947:1
    BLM_INIT_LEVEL(0);{
        sc_t sc_bl_end_of_expression = "#?([0]==';'||[0]=='{'||[0]=='}'||[0]==')'||[0]==']'||[0]==','||([0]==':'&&([1]==' '||[1]=='\t'||[1]=='\n'||[1]=='/')))";
    
        BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  buf_out ))
    
        st_s* buf = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create() ));
        bl_t continuation = true;
    
        if( out_typespec ) xoico_typespec_s_reset( out_typespec);
    
        tp_t tp_identifier = xoico_cdaleth_s_get_identifier( o, source,  false );
    
        if( tp_identifier )
        {
            // examples of builtin functions: scope, cast, try, fork
            if( xoico_cdaleth_s_is_builtin_func( o, tp_identifier ) )
            {
                xoico_typespec_s* typespec_builtin = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create() ));
                BLM_TRY(xoico_cdaleth_s_trans_builtin( o, tp_identifier,  source,  NULL,  NULL,  buf,  typespec_builtin ))
                BLM_TRY(xoico_cdaleth_s_trans_typespec_expression( o, source,  buf,  typespec_builtin,  out_typespec ))
                continuation = false;
            }
    
            else if( tp_identifier == TYPEOF_verbatim_C )
            {
                BLM_TRY(xoico_cdaleth_s_parse( o, source,  "verbatim_C {" ))
                BLM_TRY(xoico_cdaleth_s_trans_block_inside_verbatim_c( o, source,  buf ))
                BLM_TRY(xoico_cdaleth_s_parse( o, source,  " }" ))
            }
    
            // a control name marks end of expression...
            else if( xoico_cdaleth_s_is_control_name( o, tp_identifier ) )
            {
                continuation = false;
            }
    
            // identifier represents a registered variable
            else if( xoico_cdaleth_s_is_var( o, tp_identifier ) )
            {
                BLM_TRY(xoico_cdaleth_s_trans_identifier( o, source,  buf,  NULL ))
                BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  buf ))
                const xoico_typespec_s* typespec_var = xoico_cdaleth_stack_var_s_get_typespec( &(o->stack_var), tp_identifier );
                BLM_TRY(xoico_cdaleth_s_trans_typespec_expression( o, source,  buf,  typespec_var,  out_typespec ))
            }
    
            // identifier represents a type known to the compiler
            else if( xoico_cdaleth_s_is_type( o, tp_identifier ) )
            {
                st_s* buf_type = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create() ));
                BLM_TRY(xoico_cdaleth_s_trans_identifier( o, source,  buf_type,  NULL ))
                BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  buf_type ))
                if( bcore_source_a_parse_bl_fa( source, "#?'!'" ) )
                {
                    if( xoico_cdaleth_s_is_group( o, tp_identifier ) )
                    {
                        BLM_RETURNV(er_t, xoico_cdaleth_s_parse_err_fa( o, source,  "Operator '!': lvalue is a group." ))
                    }
                    st_s_push_fa( buf, "#<sc_t>_create()",  xoico_cdaleth_s_nameof( o, tp_identifier ) );
                    xoico_typespec_s* typespec = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create() ));
                    typespec->type = tp_identifier;
                    typespec->indirection = 1;
                    typespec->flag_addressable = false;
                    BLM_TRY(xoico_cdaleth_s_trans_typespec_expression( o, source,  buf,  typespec,  out_typespec ))
                    continuation = false;
                }
                else
                {
                    st_s_push_st( buf, buf_type );
                }
            }
            else
            {
                BLM_TRY(xoico_cdaleth_s_trans_identifier( o, source,  buf,  NULL ))
                BLM_TRY(xoico_cdaleth_s_trans_expression( o, source,  buf,  NULL ))
            }
        }
    
        // literals and members
        else if( bcore_source_a_parse_bl_fa( source, "#?([0]>='0'&&[0]<='9')" ) ) BLM_TRY(xoico_cdaleth_s_trans_number_literal( o, source,  buf ))
        else if( bcore_source_a_parse_bl_fa( source, "#=?'\"'" )                ) BLM_TRY(xoico_cdaleth_s_trans_string_literal( o, source,  buf ))
        else if( bcore_source_a_parse_bl_fa( source, "#=?|'|" )                 ) BLM_TRY(xoico_cdaleth_s_trans_char_literal( o, source,  buf ))
        else if( bcore_source_a_parse_bl_fa( source, "#=?'.'" )                 ) BLM_TRY(xoico_cdaleth_s_trans_member( o, source,  buf ))
        else if( bcore_source_a_parse_bl_fa( source, "#=?'->'" )                ) BLM_TRY(xoico_cdaleth_s_trans_member( o, source,  buf ))
    
        else if( bcore_source_a_parse_bl_fa( source, "#=?'=<'" )                ) BLM_RETURNV(er_t, xoico_cdaleth_s_parse_err_fa( o, source,  "Attach operator: Expression not tractable." ))
        else if( xoico_cdaleth_s_trans_inert_operator( o, source,  buf )          ) {} // inert operators are not interpreted by cdaleth and passed to the c-compiler
    
        // ternary branch operator
        else if( bcore_source_a_parse_bl_fa( source, "#?'?'" ) )
        {
            st_s_push_sc( buf, "?" );
            BLM_TRY(xoico_cdaleth_s_trans_expression( o, source,  buf,  NULL ))
            BLM_TRY(xoico_cdaleth_s_trans( o, source,  ": ",  buf ))
            BLM_TRY(xoico_cdaleth_s_trans_expression( o, source,  buf,  NULL ))
        }
    
        // general bracket
        else if( bcore_source_a_parse_bl_fa( source, "#?'('" ) )
        {
            xoico_typespec_s* typespec_bracket = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create() ));
            st_s_push_char( buf, '(' );
            while( !bcore_source_a_eos( source) )
            {
                BLM_TRY(xoico_cdaleth_s_trans_expression( o, source,  buf,  typespec_bracket ))
                if     ( bcore_source_a_parse_bl_fa( source, "#?')'" ) ) break;
                else if( bcore_source_a_parse_bl_fa( source, "#?','" ) ) st_s_push_char( buf, ',' );
                else BLM_RETURNV(er_t, xoico_cdaleth_s_parse_err_fa( o, source,  "Syntax error in bracket expression." ))
                typespec_bracket->type = 0;
            }
            st_s_push_char( buf, ')' );
            if( typespec_bracket->type ) BLM_TRY(xoico_cdaleth_s_trans_typespec_expression( o, source,  buf,  typespec_bracket,  out_typespec ))
        }
    
        // array subscript
        else if( bcore_source_a_parse_bl_fa( source, "#?'['" ) )
        {
            st_s_push_sc( buf, "[" );
            BLM_TRY(xoico_cdaleth_s_trans_expression( o, source,  buf,  NULL ))
            BLM_TRY(xoico_cdaleth_s_parse( o, source,  "]" ))
            st_s_push_sc( buf, "]" );
        }
    
        // end of expression...
        else if( bcore_source_a_parse_bl_fa( source, sc_bl_end_of_expression ) )
        {
            continuation = false;
        }
    
        // unhandled
        else
        {
            BLM_RETURNV(er_t, xoico_cdaleth_s_parse_err_fa( o, source,  "Syntax error after '#<sc_t>'",  buf->sc ))
        }
    
        if( continuation )
        {
            if( !bcore_source_a_parse_bl_fa( source, sc_bl_end_of_expression ) )
            {
                if( out_typespec ) xoico_typespec_s_reset( out_typespec);
                BLM_TRY(xoico_cdaleth_s_trans_expression( o, source,  buf,  NULL ))
            }
        }
    
        if( buf_out ) st_s_push_st( buf_out, buf );
    
        BLM_RETURNV(er_t, 0)
    } // try
}

er_t xoico_cdaleth_s_try_trans_declaration( xoico_cdaleth_s* o, bcore_source* source, st_s* buf_out, bl_t* success )
{
    // xoico_cdaleth.x:1113:1
    BLM_INIT_LEVEL(0);{
        if( success ) *success = false;
    
        xoico_typespec_s* typespec_var = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
    
        sz_t index = bcore_source_a_get_index( source);
    
        st_s* buf_var = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    
        bl_t success_take_typespec = false;
        BLM_TRY(xoico_cdaleth_s_try_take_typespec( o, source,  typespec_var,  true,  &success_take_typespec ))
    
        if( !success_take_typespec )
        {
            bcore_source_a_set_index( source, index );
            BLM_RETURNV(er_t, 0)
        }
    
        BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  buf_var ))
    
        if
        (
            typespec_var->type &&
            bcore_source_a_parse_bl_fa( source, "#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||[0]=='_')" )
        )
        {
            tp_t tp_identifier = 0;
            BLM_TRY(xoico_cdaleth_s_trans_identifier( o, source,  buf_var,  &tp_identifier ))
            BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  buf_var ))
    
            bl_t pushed_typedecl = false;
    
            if( typespec_var->type != TYPEOF_type_deduce )
            {
                xoico_cdaleth_s_push_typedecl( o, typespec_var,  tp_identifier );
                pushed_typedecl = true;
            }
    
            if( bcore_source_a_parse_bl_fa( source, "#?'='" ) )
            {
                st_s_push_sc( buf_var, "=" );
                xoico_typespec_s* typespec_expr = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
                st_s* buf_expr = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
                BLM_TRY(xoico_cdaleth_s_trans_expression( o, source,  buf_expr,  typespec_expr ))
    
                if( typespec_var->type == TYPEOF_type_deduce )
                {
                    if( !typespec_expr->type )
                    {
                        BLM_RETURNV(er_t, xoico_cdaleth_s_parse_err_fa( o, source,  "Declaration-syntax: Deduce requested but expression is intractable." ))
                    }
                    typespec_var->type = typespec_expr->type;
                }
    
                if( typespec_expr->type )
                {
                    BLM_TRY(xoico_cdaleth_s_adapt_expression( o, source,  typespec_expr,  typespec_var,  buf_expr,  buf_var ))
                }
                else
                {
                    st_s_push_st( buf_var, buf_expr );
                }
            }
            else
            {
                if( typespec_var->type == TYPEOF_type_deduce )
                {
                    BLM_RETURNV(er_t, xoico_cdaleth_s_parse_err_fa( o, source,  "Declaration-syntax: Deduce requested without assignment." ))
                }
            }
    
            if( !pushed_typedecl )
            {
                xoico_cdaleth_s_push_typedecl( o, typespec_var,  tp_identifier );
                pushed_typedecl = true;
            }
    
            BLM_TRY(xoico_cdaleth_s_push_typespec( o, typespec_var,  buf_out ))
            st_s_push_char( buf_out, ' ' );
            st_s_push_st( buf_out, buf_var );
    
            if( success ) *success = true;
        }
        else
        {
            bcore_source_a_set_index( source, index );
            BLM_RETURNV(er_t, 0)
        }
    
        if( success ) *success = true;
    
        BLM_RETURNV(er_t, 0)
    } // try
}

er_t xoico_cdaleth_s_inspect_variable( xoico_cdaleth_s* o, bcore_source* source )
{
    // xoico_cdaleth.x:1213:1
    BLM_INIT_LEVEL(0);{
        BLM_TRY(xoico_cdaleth_s_parse( o, source,  "\?\?" ))
    
        st_s* st        = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
        st_s* buf_local = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
        xoico_typespec_s* typespec = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
        xoico_cdaleth_s_parse_fa( o, source,  " #until';' ",  st );
        xoico_cdaleth_s_parse_fa( o, source,  ";" );
        bcore_msg_fa( " \?? #<sc_t>;\n", st->sc );
        if( xoico_cdaleth_s_trans_expression( o, ((bcore_source*)BLM_LEVEL_A_PUSH(0,((bcore_source*)(bcore_source_string_s_create_fa( "#<st_s*>;", st ))))),  buf_local,  typespec ) )
        {
            bcore_error_pop_to_sink( BCORE_STDOUT );
            bcore_msg_fa( "\n" );
        }
        else
        {
            if( st->size == 0 ) BLM_RETURNV(er_t, xoico_cdaleth_s_parse_err_fa( o, source,  "Variable name expected." ))
            bcore_msg_fa( "--> #<sc_t>;\n", buf_local->sc );
    
            if( typespec->type )
            {
                bcore_msg_fa( "Expression yields typespec:\n" );
                bcore_msg_fa( "  const      : #<bl_t>\n", typespec->flag_const );
                bcore_msg_fa( "  type       : #<sc_t>\n", xoico_cdaleth_s_nameof( o, typespec->type ) );
                bcore_msg_fa( "  indirection: #<sz_t>\n", typespec->indirection );
            }
            else
            {
                bcore_msg_fa( "Expression does not yield a typespec.\n" );
            }
        }
        BLM_RETURNV(er_t, 0)
    
    } // try
}

er_t xoico_cdaleth_s_trans_statement( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth.x:1254:1
    BLM_INIT_LEVEL(0);{
        BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  buf ))
    
        if( bcore_source_a_parse_bl_fa( source, "#?([0]=='{'||[0]=='#'||[0]==';'||[0]==','||[0]==')'||[0]=='}'||([0]=='?'&&[1]=='?'))" ) )
        {
            char c = bcore_source_a_inspect_char( source);
            switch( c )
            {
                case '{':
                {
                    BLM_TRY(xoico_cdaleth_s_trans_block( o, source,  buf,  false ))
                }
                break;
    
                case '#':
                {
                    BLM_TRY(xoico_cdaleth_s_trans_preprocessor( o, source,  buf ))
                }
                break;
    
                case ';':
                {
                    bcore_source_a_get_char( source);
                    st_s_push_char( buf, ';' );
                }
                break;
    
                case ',':
                {
                    bcore_source_a_get_char( source);
                    st_s_push_char( buf, ',' );
                }
                break;
    
                case '?':
                {
                    BLM_TRY(xoico_cdaleth_s_inspect_variable( o, source ))
                }
                break;
    
                case ')':
                {
                    return  xoico_cdaleth_s_parse_err_fa( o, source,  "Unmatched closing bracket." );
                }
                break;
    
                case '}':
                {
                    // nothing (caller is a block-handler)
                }
                break;
    
                default: break;
            }
        }
        else
        {
            tp_t tp_identifier = xoico_cdaleth_s_get_identifier( o, source,  false );
    
            if( tp_identifier && xoico_cdaleth_s_is_control_name( o, tp_identifier ) )
            {
                BLM_TRY(xoico_cdaleth_s_trans_control( o, tp_identifier,  source,  buf ))
            }
            else
            {
                bl_t success_declaration = false;
                BLM_TRY(xoico_cdaleth_s_try_trans_declaration( o, source,  buf,  &success_declaration ))
    
                if( !success_declaration )
                {
                    if( o->try_block_level > 0 )
                    {
                        xoico_typespec_s* typespec = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
                        st_s* buf_expr = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
                        BLM_TRY(xoico_cdaleth_s_trans_expression( o, source,  buf_expr,  typespec ))
                        if
                        (
                            ( typespec->type == TYPEOF_er_t ) &&
                            ( typespec->indirection == 0 ) &&
                            ( typespec->flag_addressable == false )
                        )
                        {
                            if( !bcore_source_a_parse_bl_fa( source, " #?';'" ) )
                            {
                                BLM_RETURNV(er_t, xoico_cdaleth_s_parse_err_fa( o, source,  "Inside a try-block: Expressions yielding 'er_t' must end with ';'" ))
                            }
                            st_s_push_fa( buf, "BLM_TRY(#<sc_t>)",  buf_expr->sc );
                        }
                        else
                        {
                            st_s_push_st( buf, buf_expr );
                        }
                    }
                    else
                    {
                        BLM_TRY(xoico_cdaleth_s_trans_expression( o, source,  buf,  NULL ))
                    }
    
                    BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  buf ))
    
                    // ':' between expressions is to be taken literally
                    if( bcore_source_a_parse_bl_fa( source, "#?':'" ) ) st_s_push_char( buf, ':' );
                }
            }
        }
    
        BLM_RETURNV(er_t, 0)
    }
}

er_t xoico_cdaleth_s_trans_block_inside( xoico_cdaleth_s* o, bcore_source* source, st_s* buf_out )
{
    // xoico_cdaleth.x:1369:1
    BLM_INIT_LEVEL(0);{
        st_s* buf = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    
        while( !bcore_source_a_parse_bl_fa( source, "#=?'}'" ) && !bcore_source_a_eos( source) )
        {
            BLM_TRY(xoico_cdaleth_s_trans_statement( o, source,  buf ))
        }
    
        if( xoico_cdaleth_s_stack_block_get_top_unit( o)->use_blm )
        {
            st_s_push_fa( buf_out, "BLM_INIT_LEVEL(#<sz_t>);",  o->level );
            st_s_push_st( buf_out, buf );
    
            if( ( o->level > 0 ) || !xoico_cdaleth_s_returns_a_value( o) )
            {
                st_s_push_sc( buf_out, "BLM_DOWN();" );
            }
        }
        else
        {
            st_s_push_st( buf_out, buf );
        }
    
        BLM_RETURNV(er_t, 0)
    } // try
}

er_t xoico_cdaleth_s_trans_block( xoico_cdaleth_s* o, bcore_source* source, st_s* buf, bl_t is_break_ledge )
{
    // xoico_cdaleth.x:1401:1
    {
        xoico_cdaleth_s_inc_block( o);
        xoico_cdaleth_s_stack_block_get_top_unit( o)->break_ledge = is_break_ledge;
        BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  buf ))
        BLM_TRY(xoico_cdaleth_s_trans( o, source,  "{",  buf ))
        BLM_TRY(xoico_cdaleth_s_trans_block_inside( o, source,  buf ))
        BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  buf ))
        BLM_TRY(xoico_cdaleth_s_trans( o, source,  "}",  buf ))
        xoico_cdaleth_s_dec_block( o);
        return  0;
    } // try
}

er_t xoico_cdaleth_s_trans_statement_as_block( xoico_cdaleth_s* o, bcore_source* source, st_s* buf_out, bl_t is_break_ledge )
{
    // xoico_cdaleth.x:1419:1
    BLM_INIT_LEVEL(0);{
        st_s* buf = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    
        xoico_cdaleth_s_inc_block( o);
        xoico_cdaleth_s_stack_block_get_top_unit( o)->break_ledge = is_break_ledge;
    
        BLM_TRY(xoico_cdaleth_s_trans_statement( o, source,  buf ))
        BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  buf ))
        if( bcore_source_a_parse_bl_fa( source, "#?';'" ) ) st_s_push_sc( buf, ";" );
    
        if( xoico_cdaleth_s_stack_block_get_top_unit( o)->use_blm )
        {
            st_s_push_fa( buf_out, "{BLM_INIT_LEVEL(#<sz_t>);",  o->level );
            st_s_push_st( buf_out, buf );
            st_s_push_sc( buf_out, "BLM_DOWN();}" );
        }
        else
        {
            st_s_push_st( buf_out, buf );
        }
    
        xoico_cdaleth_s_dec_block( o);
        BLM_RETURNV(er_t, 0)
    } // try
}

er_t xoico_cdaleth_s_trans_block_inside_verbatim_c( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth.x:1450:1
    {
        BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  buf ))
        while( !bcore_source_a_parse_bl_fa( source, "#=?'}'" ) && !bcore_source_a_eos( source) )
        {
            switch( bcore_source_a_inspect_char( source) )
            {
                case '"':
                {
                    BLM_TRY(xoico_cdaleth_s_trans_string_literal( o, source,  buf ))
                }
                break;
    
                case '\'':
                {
                    BLM_TRY(xoico_cdaleth_s_trans_char_literal( o, source,  buf ))
                }
                break;
    
                case '{':
                {
                    st_s_push_char( buf, bcore_source_a_get_char( source) );
                    BLM_TRY(xoico_cdaleth_s_trans_block_inside_verbatim_c( o, source,  buf ))
                    BLM_TRY(xoico_cdaleth_s_parse( o, source,  "}" ))
                    st_s_push_char( buf, '}' );
                }
                break;
    
                default:
                {
                    st_s_push_char( buf, bcore_source_a_get_char( source) );
                }
                break;
            }
            BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  buf ))
        }
        return  0;
    } // try
}

er_t xoico_cdaleth_s_setup( xoico_cdaleth_s* o, const xoico_body_s* body, const xoico_signature_s* signature )
{
    // xoico_cdaleth.x:1494:1
    BLM_INIT_LEVEL(0);{
        sc_t sc_obj_type = ( signature->arg_o ) ? ( body->stamp ? body->stamp->st_name.sc : body->group->st_name.sc ) : NULL;
    
        const xoico_args_s* args = &signature->args;
    
        tp_t obj_type  = ( signature->arg_o == 0 ) ? 0 : xoico_cdaleth_s_entypeof( o, sc_obj_type );
        bl_t obj_const = ( signature->arg_o == TYPEOF_const );
        tp_t obj_name  = xoico_cdaleth_s_entypeof( o, "o" );
    
        o->args     = ((xoico_args_s*)(args));
        o->typespec_ret = ((xoico_typespec_s*)(&(signature->typespec_ret)));
        o->group    = body->code->group;
        o->stamp    = body->code->stamp;
        o->compiler = xoico_group_s_get_compiler( body->group);
        o->obj_type = obj_type;
        o->level    = 0;
        o->try_block_level = 0;
        xoico_cdaleth_stack_var_s_clear( &(o->stack_var));
        xoico_cdaleth_s_init_level0( o);
    
        xoico_cdaleth_stack_var_unit_s* unit = ((xoico_cdaleth_stack_var_unit_s*)BLM_LEVEL_T_PUSH(0,xoico_cdaleth_stack_var_unit_s,xoico_cdaleth_stack_var_unit_s_create()));
    
        if( obj_type )
        {
            unit->typespec.flag_const = obj_const;
            unit->typespec.type = obj_type;
            unit->typespec.indirection = 1;
            unit->name = obj_name;
            unit->level = o->level;
            xoico_cdaleth_stack_var_s_push_unit( &(o->stack_var), unit );
            bcore_hmap_name_s_set_sc( &(o->hmap_name), xoico_compiler_s_nameof( o->compiler, obj_type ) );
            bcore_hmap_name_s_set_sc( &(o->hmap_name), xoico_compiler_s_nameof( o->compiler, obj_name ) );
        }
    
        {const xoico_args_s* __a=args ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_arg_s* arg=&(__a->data[__i]);
        {
            if( arg->typespec.type && arg->name )
            {
                xoico_typespec_s_copy( &(unit->typespec), &(arg->typespec ));
                if( obj_type ) BLM_TRY(xoico_typespec_s_relent( &(unit->typespec), o->group,  obj_type ))
                unit->name = arg->name;
                unit->level = o->level;
                xoico_cdaleth_stack_var_s_push_unit( &(o->stack_var), unit );
                bcore_hmap_name_s_set_sc( &(o->hmap_name), xoico_compiler_s_nameof( o->compiler, arg->typespec.type ) );
                bcore_hmap_name_s_set_sc( &(o->hmap_name), xoico_compiler_s_nameof( o->compiler, arg->name ) );
            }
        }
        }}BLM_RETURNV(er_t, 0)
    } // try
}

er_t xoico_cdaleth_s_translate( const xoico_cdaleth_s* o, const xoico_body_s* body, const xoico_signature_s* signature, bcore_sink* sink )
{
    // xoico_cdaleth.x:1550:1
    BLM_INIT_LEVEL(0);{
        xoico_cdaleth_s* engine = ((xoico_cdaleth_s*)BLM_LEVEL_T_PUSH(0,xoico_cdaleth_s,xoico_cdaleth_s_clone( o)));
        BLM_TRY(xoico_cdaleth_s_setup( engine, body,  signature ))
    
        bcore_source* source = ((bcore_source*)BLM_LEVEL_A_PUSH(0,((bcore_source*)(bcore_source_point_s_clone_source( &body->code->source_point )))));
    
        st_s* buf = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    
        sz_t indent = 0;
        BLM_TRY(xoico_cdaleth_s_parse( engine, source,  " {" ))
    
        while( bcore_source_a_parse_bl_fa( source, "#?([0]==' '||[0]=='\t')" ) ) { bcore_source_a_get_char( source); };
        if( bcore_source_a_parse_bl_fa( source, "#?'\n'" ) )
        {
            while( bcore_source_a_parse_bl_fa( source, "#?' '" ) ) indent++;
        }
    
        BLM_TRY(xoico_cdaleth_s_trans_block_inside( engine, source,  buf ))
    
        BLM_TRY(xoico_cdaleth_s_parse( engine, source,  " }" ))
    
        if( indent > 0 ) st_s_replace_st_d_st_d( buf, st_s_create_fa( "\n#rn{ }", indent ),  st_s_create_fa( "\n" ) );
    
        //remove trailing whitespaces
        for( sz_t i = buf->size - 1; i >= 0; i-- )
        {
            if( buf->data[ i ] != ' ' && buf->data[ i ] != '\t' && buf->data[ i ] != '\n' ) break;
            buf->data[ i ] = 0;
            buf->size = i;
        }
    
        if( engine->verbose )
        {
            bcore_sink_a_push_fa( BCORE_STDOUT, "##############################\n" );
            bcore_sink_a_push_fa( BCORE_STDOUT, "#<st_s*>\n", buf );
        }
    
        if( engine->insert_source_reference && !body->code->single_line )
        {
            bcore_sink_a_push_fa( sink, "// " );
            bcore_source_point_s_source_reference_to_sink( &(body->code->source_point), true,  sink );
            bcore_sink_a_push_fa( sink, "\n" );
        }
    
        bcore_sink_a_push_sc( sink, buf->sc );
    
        BLM_RETURNV(er_t, 0)
    } // try
}

bl_t xoico_cdaleth_s_is_builtin_func( const xoico_cdaleth_s* o, tp_t tp_identifier )
{
    // xoico_cdaleth_builtin.x:21:1
    switch( tp_identifier )
    {
        case TYPEOF_cast :
        case TYPEOF_scope:
        case TYPEOF_fork:
        case TYPEOF_try:
            return  true;
    
        default:
            return  false;
    }
}

er_t xoico_cdaleth_s_trans_builtin( xoico_cdaleth_s* o, tp_t tp_builtin, bcore_source* source, const st_s* buf_expr, const xoico_typespec_s* typespec_expr, st_s* buf_out, xoico_typespec_s* typespec_out )
{
    // xoico_cdaleth_builtin.x:50:1
    {
        switch( tp_builtin )
        {
            case TYPEOF_cast : return  xoico_cdaleth_s_trans_builtin_cast( o, source,  buf_expr,  typespec_expr,  buf_out,  typespec_out );
            case TYPEOF_scope: return  xoico_cdaleth_s_trans_builtin_scope( o, source,  buf_expr,  typespec_expr,  buf_out,  typespec_out );
            case TYPEOF_fork:  return  xoico_cdaleth_s_trans_builtin_fork( o, source,  buf_expr,  typespec_expr,  buf_out,  typespec_out );
            case TYPEOF_try:   return  xoico_cdaleth_s_trans_builtin_try( o, source,  buf_expr,  typespec_expr,  buf_out,  typespec_out );
            default: return  xoico_cdaleth_s_parse_err_fa( o, source,  "Internal error: Invalid builtin type '#<sc_t>'",  ifnameof( tp_builtin ) );
        }
    } // try
}

er_t xoico_cdaleth_s_trans_builtin_cast( xoico_cdaleth_s* o, bcore_source* source, const st_s* buf_expr, const xoico_typespec_s* typespec_expr, st_s* buf_out, xoico_typespec_s* typespec_out )
{
    // xoico_cdaleth_builtin.x:78:1
    BLM_INIT_LEVEL(0);{
        if( buf_expr ) // member call
        {
            BLM_TRY(xoico_cdaleth_s_parse( o, source,  " ( " ))
            st_s_clear( buf_out);
        }
        else // direct call
        {
            BLM_TRY(xoico_cdaleth_s_parse( o, source,  "cast ( " ))
            st_s* buf = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
            xoico_typespec_s* typespec = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
            BLM_TRY(xoico_cdaleth_s_trans_expression( o, source,  buf,  typespec ))
            BLM_TRY(xoico_cdaleth_s_parse( o, source,  " , " ))
            typespec_expr = typespec;
            buf_expr = buf;
        }
    
        st_s_push_sc( buf_out, "((" );
        xoico_typespec_s* typespec_cast = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create() ));
    
        BLM_TRY(xoico_cdaleth_s_take_typespec( o, source,  typespec_cast,  true ))
    
        if( typespec_cast->type == TYPEOF_type_deduce )
        {
            if( !typespec_expr->type )
            {
                BLM_RETURNV(er_t, xoico_cdaleth_s_parse_err_fa( o, source,  "Cast-syntax: Deduce requested but expression is intractable." ))
            }
            typespec_cast->type = typespec_expr->type;
        }
    
        BLM_TRY(xoico_cdaleth_s_push_typespec( o, typespec_cast,  buf_out ))
        st_s_push_sc( buf_out, ")(" );
    
        if( typespec_expr->type )
        {
            BLM_TRY(xoico_cdaleth_s_adapt_expression( o, source,  typespec_expr,  typespec_cast,  buf_expr,  buf_out ))
        }
        else
        {
            st_s_push_st( buf_out, buf_expr );
        }
    
        BLM_TRY(xoico_cdaleth_s_parse( o, source,  " )" ))
        st_s_push_sc( buf_out, "))" );
    
        if( typespec_out ) xoico_typespec_s_copy( typespec_out, typespec_cast );
    
        if( typespec_cast->indirection > typespec_expr->indirection )
        {
            typespec_out->flag_addressable = false;
        }
    
        BLM_RETURNV(er_t, 0)
    } // try
}

er_t xoico_cdaleth_s_trans_builtin_scope( xoico_cdaleth_s* o, bcore_source* source, const st_s* buf_expr, const xoico_typespec_s* typespec_expr, st_s* buf_out, xoico_typespec_s* typespec_out )
{
    // xoico_cdaleth_builtin.x:151:1
    BLM_INIT_LEVEL(0);{
        bl_t has_arg = false;
    
        if( buf_expr ) // member call
        {
            BLM_TRY(xoico_cdaleth_s_parse( o, source,  " ( " ))
            st_s_clear( buf_out);
            has_arg = !bcore_source_a_parse_bl( source, "#=?')'" );
        }
        else // direct call
        {
            BLM_TRY(xoico_cdaleth_s_parse( o, source,  "scope ( " ))
            st_s* buf = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
            xoico_typespec_s* typespec = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
            BLM_TRY(xoico_cdaleth_s_trans_expression( o, source,  buf,  typespec ))
            typespec_expr = typespec;
            buf_expr = buf;
            has_arg = bcore_source_a_parse_bl( source, "#?','" );
        }
    
        const xoico_typespec_s* typespec_scope = typespec_expr;
    
        st_s_push_sc( buf_out, "((" );
    
        sz_t level = 0;
    
        if( has_arg )
        {
            BLM_TRY(xoico_cdaleth_s_parse( o, source,  " " ))
            tp_t tp_identifier = xoico_cdaleth_s_get_identifier( o, source,  true );
    
            if( xoico_cdaleth_s_is_var( o, tp_identifier ) )
            {
                level = xoico_cdaleth_stack_var_s_get_level( &(o->stack_var), tp_identifier );
            }
            else if( tp_identifier == TYPEOF_scope_local )
            {
                level = o->level;
            }
            else if( tp_identifier == TYPEOF_scope_func )
            {
                level = 0;
            }
            else
            {
                BLM_RETURNV(er_t, xoico_cdaleth_s_parse_err_fa( o, source,  "scope: identifier '#<sc_t>' does not represent a variable.",  xoico_cdaleth_s_nameof( o, tp_identifier ) ))
            }
        }
    
        BLM_TRY(xoico_cdaleth_s_parse( o, source,  " )" ))
    
        if( typespec_scope->type        == 0 ) BLM_RETURNV(er_t, xoico_cdaleth_s_parse_err_fa( o, source,  "Operator 'scope': Expression not tractable." ))
        if( typespec_scope->indirection != 1 ) BLM_RETURNV(er_t, xoico_cdaleth_s_parse_err_fa( o, source,  "Operator 'scope': Expression's indirection != 1." ))
        if( typespec_scope->flag_keep )        BLM_RETURNV(er_t, xoico_cdaleth_s_parse_err_fa( o, source,  "Operator 'scope': Target is already scoped." ))
    
        BLM_TRY(xoico_cdaleth_s_push_typespec( o, typespec_scope,  buf_out ))
    
        if( xoico_cdaleth_s_is_group( o, typespec_scope->type ) )
        {
            st_s_push_fa( buf_out, ")BLM_LEVEL_A_PUSH(#<sz_t>,#<sc_t>))",  level,  buf_expr->sc );
        }
        else
        {
            st_s_push_fa( buf_out, ")BLM_LEVEL_T_PUSH(#<sz_t>,#<sc_t>,#<sc_t>))",  level,  xoico_cdaleth_s_nameof( o, typespec_scope->type ),  buf_expr->sc );
        }
    
        o->stack_block.adl.data[ level ]->use_blm = true;
    
        if( typespec_out )
        {
            xoico_typespec_s_copy( typespec_out, typespec_scope );
            typespec_out->flag_keep = true;
        }
    
        BLM_RETURNV(er_t, 0)
    } // try
}

er_t xoico_cdaleth_s_trans_builtin_fork( xoico_cdaleth_s* o, bcore_source* source, const st_s* buf_expr, const xoico_typespec_s* typespec_expr, st_s* buf_out, xoico_typespec_s* typespec_out )
{
    // xoico_cdaleth_builtin.x:245:1
    BLM_INIT_LEVEL(0);{
        if( buf_expr ) // member call
        {
            BLM_TRY(xoico_cdaleth_s_parse( o, source,  " ( " ))
            st_s_clear( buf_out);
        }
        else // direct call
        {
            BLM_TRY(xoico_cdaleth_s_parse( o, source,  "fork ( " ))
            st_s* buf = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
            xoico_typespec_s* typespec = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
            BLM_TRY(xoico_cdaleth_s_trans_expression( o, source,  buf,  typespec ))
            typespec_expr = typespec;
            buf_expr = buf;
        }
    
        const xoico_typespec_s* typespec_fork = typespec_expr;
    
        st_s_push_sc( buf_out, "((" );
    
        BLM_TRY(xoico_cdaleth_s_parse( o, source,  " )" ))
    
        if( typespec_fork->type        == 0 ) BLM_RETURNV(er_t, xoico_cdaleth_s_parse_err_fa( o, source,  "Operator 'fork': Expression not tractable." ))
        if( typespec_fork->indirection != 1 ) BLM_RETURNV(er_t, xoico_cdaleth_s_parse_err_fa( o, source,  "Operator 'fork': Expression's indirection != 1." ))
    
        BLM_TRY(xoico_cdaleth_s_push_typespec( o, typespec_fork,  buf_out ))
        st_s_push_fa( buf_out, ")bcore_fork(#<sc_t>))",  buf_expr->sc );
    
        if( typespec_out ) xoico_typespec_s_copy( typespec_out, typespec_fork );
    
        BLM_RETURNV(er_t, 0)
    } // try
}

er_t xoico_cdaleth_s_trans_builtin_try( xoico_cdaleth_s* o, bcore_source* source, const st_s* buf_expr, const xoico_typespec_s* typespec_expr, st_s* buf_out, xoico_typespec_s* typespec_out )
{
    // xoico_cdaleth_builtin.x:295:1
    BLM_INIT_LEVEL(0);{
        if( o->typespec_ret->type != TYPEOF_er_t || o->typespec_ret->indirection != 0 )
        {
            return  xoico_cdaleth_s_parse_err_fa( o, source,  "Operator 'try': This operator can only be used in functions returning 'er_t'." );
        }
    
        if( typespec_out ) xoico_typespec_s_reset( typespec_out);
    
        if( buf_expr ) // member call
        {
            BLM_TRY(xoico_cdaleth_s_parse( o, source,  " ( " ))
            st_s_clear( buf_out);
        }
        else // direct call
        {
            BLM_TRY(xoico_cdaleth_s_parse( o, source,  "try " ))
    
            if( bcore_source_a_parse_bl( source, "#=?'{'" ) ) // try block
            {
                o->try_block_level++;
                BLM_TRY(xoico_cdaleth_s_trans_block( o, source,  buf_out,  false ))
                o->try_block_level--;
                return  0;
            }
    
            BLM_TRY(xoico_cdaleth_s_parse( o, source,  "( " ))
            st_s* buf = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
            xoico_typespec_s* typespec = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
            BLM_TRY(xoico_cdaleth_s_trans_expression( o, source,  buf,  typespec ))
            typespec_expr = typespec;
            buf_expr = buf;
        }
    
        const xoico_typespec_s* typespec_try = typespec_expr;
    
        BLM_TRY(xoico_cdaleth_s_parse( o, source,  " ) ;" ))
    
        if( typespec_try->type == 0           ) BLM_RETURNV(er_t, xoico_cdaleth_s_parse_err_fa( o, source,  "Operator 'try': Expression not tractable." ))
        if( typespec_try->type != TYPEOF_er_t ) BLM_RETURNV(er_t, xoico_cdaleth_s_parse_err_fa( o, source,  "Operator 'try': Expression must yield er_t." ))
        if( typespec_try->indirection != 0    ) BLM_RETURNV(er_t, xoico_cdaleth_s_parse_err_fa( o, source,  "Operator 'try': Expression's indirection != 0." ))
    
        st_s_push_fa( buf_out, "BLM_TRY(#<sc_t>)",  buf_expr->sc );
    
        BLM_RETURNV(er_t, 0)
    } // try
}

bl_t xoico_cdaleth_s_is_control_name( const xoico_cdaleth_s* o, tp_t tp_identifier )
{
    // xoico_cdaleth_control.x:21:1
    switch( tp_identifier )
    {
        case TYPEOF_for:
        case TYPEOF_foreach:
        case TYPEOF_if:
        case TYPEOF_else:
        case TYPEOF_break:
        case TYPEOF_while:
        case TYPEOF_do:
        case TYPEOF_switch:
        case TYPEOF_case:
        case TYPEOF_default:
        case TYPEOF_return:
            return  true;
    
        default:
            return  false;
    }
}

er_t xoico_cdaleth_s_trans_control( xoico_cdaleth_s* o, tp_t tp_control, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth_control.x:45:1
    {
        switch( tp_control )
        {
            case TYPEOF_for:     return  xoico_cdaleth_s_trans_control_for( o, source,  buf );
            case TYPEOF_foreach: return  xoico_cdaleth_s_trans_control_foreach( o, source,  buf );
            case TYPEOF_if:      return  xoico_cdaleth_s_trans_control_if( o, source,  buf );
            case TYPEOF_else:    return  xoico_cdaleth_s_trans_control_else( o, source,  buf );
            case TYPEOF_break:   return  xoico_cdaleth_s_trans_control_break( o, source,  buf );
            case TYPEOF_while:   return  xoico_cdaleth_s_trans_control_while( o, source,  buf );
            case TYPEOF_do:      return  xoico_cdaleth_s_trans_control_do( o, source,  buf );
            case TYPEOF_switch:  return  xoico_cdaleth_s_trans_control_switch( o, source,  buf );
            case TYPEOF_case:    return  xoico_cdaleth_s_trans_control_case( o, source,  buf );
            case TYPEOF_default: return  xoico_cdaleth_s_trans_control_default( o, source,  buf );
            case TYPEOF_return:  return  xoico_cdaleth_s_trans_control_return( o, source,  buf );
            default: return  xoico_cdaleth_s_parse_err_fa( o, source,  "Internal error: Invalid control name '#<sc_t>'",  ifnameof( tp_control ) );
        }
    } // try
}

er_t xoico_cdaleth_s_trans_control_for( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth_control.x:69:1
    {
        xoico_cdaleth_s_inc_block( o);
        xoico_cdaleth_s_stack_block_get_top_unit( o)->break_ledge = true;
        BLM_TRY(xoico_cdaleth_s_trans( o, source,  "for",  buf ))
        BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  buf ))
        BLM_TRY(xoico_cdaleth_s_trans( o, source,  "(",  buf ))
        BLM_TRY(xoico_cdaleth_s_trans_statement( o, source,  buf )) // def
        BLM_TRY(xoico_cdaleth_s_trans( o, source,  ";",  buf ))
        BLM_TRY(xoico_cdaleth_s_trans_expression( o, source,  buf,  NULL )) // cond
        BLM_TRY(xoico_cdaleth_s_trans( o, source,  ";",  buf ))
        BLM_TRY(xoico_cdaleth_s_trans_expression( o, source,  buf,  NULL )) // update
        BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  buf ))
        BLM_TRY(xoico_cdaleth_s_trans( o, source,  ")",  buf ))
        BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  buf ))
        if( bcore_source_a_parse_bl( source, "#=?'{'" ) )
        {
            BLM_TRY(xoico_cdaleth_s_trans_block( o, source,  buf,  false ))
        }
        else
        {
            BLM_TRY(xoico_cdaleth_s_trans_statement_as_block( o, source,  buf,  false ))
        }
        xoico_cdaleth_s_dec_block( o);
        return  0;
    } // try
}

er_t xoico_cdaleth_s_trans_control_foreach( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth_control.x:105:1
    BLM_INIT_LEVEL(0);{
        xoico_cdaleth_s_inc_block( o);
        xoico_cdaleth_s_stack_block_get_top_unit( o)->break_ledge = true;
        BLM_TRY(xoico_cdaleth_s_parse( o, source,  "foreach ( " ))
    
        xoico_typespec_s* typespec_var = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create() ));
        BLM_TRY(xoico_cdaleth_s_take_typespec( o, source,  typespec_var,  true ))
    
        tp_t tp_var_name = 0;
    
        if( bcore_source_a_parse_bl( source, "#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||[0]=='_')" ) )
        {
            tp_var_name = xoico_cdaleth_s_get_identifier( o, source,  true );
        }
        else
        {
            BLM_RETURNV(er_t, xoico_cdaleth_s_parse_err_fa( o, source,  "Variable name expected." ))
        }
    
        BLM_TRY(xoico_cdaleth_s_parse( o, source,  " in " ))
    
        xoico_typespec_s* typespec_arr_expr = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create() ));
        st_s* buf_arr_expr = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create() ));
        BLM_TRY(xoico_cdaleth_s_trans_expression( o, source,  buf_arr_expr,  typespec_arr_expr ))
    
        if( !typespec_arr_expr->type )
        {
            BLM_RETURNV(er_t, xoico_cdaleth_s_parse_err_fa( o, source,  "Array expression not tractable." ))
        }
    
        xoico_compiler_element_info_s* info = ((xoico_compiler_element_info_s*)BLM_LEVEL_T_PUSH(0,xoico_compiler_element_info_s,xoico_compiler_element_info_s_create() ));
    
        if( !xoico_compiler_s_get_type_array_element_info( o->compiler, typespec_arr_expr->type,  info ) )
        {
            BLM_RETURNV(er_t, xoico_cdaleth_s_parse_err_fa( o, source,  "Expression does not evaluate to an array." ))
        }
    
        xoico_typespec_s* typespec_element = &info->type_info.typespec;
    
        if( typespec_var->type == TYPEOF_type_deduce ) typespec_var->type = typespec_element->type;
    
        BLM_TRY(xoico_cdaleth_s_parse( o, source,  " )" ))
    
        xoico_typespec_s* typespec_arr = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_clone( typespec_arr_expr) ));
        typespec_arr->indirection = 1;
        typespec_arr->flag_const = true;
    
        xoico_typespec_s* typespec_idx = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create() ));
        typespec_idx->type = TYPEOF_sz_t;
    
        xoico_cdaleth_s_push_typedecl( o, typespec_var,  tp_var_name );
        xoico_cdaleth_s_push_typedecl( o, typespec_arr,  xoico_cdaleth_s_entypeof( o, "__a" ) );
        xoico_cdaleth_s_push_typedecl( o, typespec_idx,  xoico_cdaleth_s_entypeof( o, "__i" ) );
    
        st_s* buf_statement = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create() ));
        if( bcore_source_a_parse_bl( source, "#=?'{'" ) )
        {
            BLM_TRY(xoico_cdaleth_s_trans_block( o, source,  buf_statement,  false ))
        }
        else
        {
            BLM_TRY(xoico_cdaleth_s_trans_statement_as_block( o, source,  buf_statement,  false ))
        }
    
        st_s_push_fa( buf, "{" );
    
        BLM_TRY(xoico_cdaleth_s_push_typespec( o, typespec_arr,  buf ))
    
        st_s_push_fa( buf, " __a=" );
        BLM_TRY(xoico_cdaleth_s_adapt_expression( o, source,  typespec_arr_expr,  typespec_arr,  buf_arr_expr,  buf ))
        st_s_push_fa( buf, ";" );
        st_s_push_fa( buf, "if(__a)for(sz_t __i=0; __i<__a->size; __i++){" );
        BLM_TRY(xoico_cdaleth_s_push_typespec( o, typespec_var,  buf ))
        st_s_push_fa( buf, " #<sc_t>=",  xoico_cdaleth_s_nameof( o, tp_var_name ) );
    
        st_s* buf_element_expr = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,((st_s*)(st_s_create_sc( "__a->data[__i]" ))) ));
        BLM_TRY(xoico_cdaleth_s_adapt_expression( o, source,  typespec_element,  typespec_var,  buf_element_expr,  buf ))
        st_s_push_fa( buf, ";" );
    
        st_s_push_fa( buf, "#<sc_t>",  buf_statement->sc );
    
        st_s_push_fa( buf, "}}" );
        xoico_cdaleth_s_dec_block( o);
        BLM_RETURNV(er_t, 0)
    } // try
}

er_t xoico_cdaleth_s_trans_control_if( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth_control.x:197:1
    {
        BLM_TRY(xoico_cdaleth_s_trans( o, source,  "if",  buf ))
        BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  buf ))
        BLM_TRY(xoico_cdaleth_s_trans( o, source,  "(",  buf ))
        BLM_TRY(xoico_cdaleth_s_trans_expression( o, source,  buf,  NULL )) // def
        BLM_TRY(xoico_cdaleth_s_trans( o, source,  ")",  buf ))
        BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  buf ))
        if( bcore_source_a_parse_bl( source, "#=?'{'" ) )
        {
            BLM_TRY(xoico_cdaleth_s_trans_block( o, source,  buf,  false ))
        }
        else
        {
            BLM_TRY(xoico_cdaleth_s_trans_statement_as_block( o, source,  buf,  false ))
        }
        return  0;
    } // try
}

er_t xoico_cdaleth_s_trans_control_while( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth_control.x:221:1
    {
        BLM_TRY(xoico_cdaleth_s_trans( o, source,  "while",  buf ))
        BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  buf ))
        BLM_TRY(xoico_cdaleth_s_trans( o, source,  "(",  buf ))
        BLM_TRY(xoico_cdaleth_s_trans_expression( o, source,  buf,  NULL )) // def
        BLM_TRY(xoico_cdaleth_s_trans( o, source,  ")",  buf ))
        BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  buf ))
        if( bcore_source_a_parse_bl( source, "#=?'{'" ) )
        {
            BLM_TRY(xoico_cdaleth_s_trans_block( o, source,  buf,  true ))
        }
        else
        {
            BLM_TRY(xoico_cdaleth_s_trans_statement_as_block( o, source,  buf,  true ))
        }
        return  0;
    } // try
}

er_t xoico_cdaleth_s_trans_control_do( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth_control.x:245:1
    {
        BLM_TRY(xoico_cdaleth_s_trans( o, source,  "do",  buf ))
        BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  buf ))
        if( bcore_source_a_parse_bl( source, "#=?'{'" ) )
        {
            BLM_TRY(xoico_cdaleth_s_trans_block( o, source,  buf,  true ))
        }
        else
        {
            BLM_TRY(xoico_cdaleth_s_trans_statement_as_block( o, source,  buf,  true ))
        }
        BLM_TRY(xoico_cdaleth_s_trans( o, source,  "while",  buf ))
        BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  buf ))
        BLM_TRY(xoico_cdaleth_s_trans( o, source,  "(",  buf ))
        BLM_TRY(xoico_cdaleth_s_trans_expression( o, source,  buf,  NULL )) // def
        BLM_TRY(xoico_cdaleth_s_trans( o, source,  ")",  buf ))
        BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  buf ))
        BLM_TRY(xoico_cdaleth_s_trans( o, source,  ";",  buf ))
        return  0;
    } // try
}

er_t xoico_cdaleth_s_trans_control_else( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth_control.x:272:1
    {
        BLM_TRY(xoico_cdaleth_s_trans( o, source,  "else",  buf ))
        BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  buf ))
        if( bcore_source_a_parse_bl( source, "#=?'{'" ) )
        {
            BLM_TRY(xoico_cdaleth_s_trans_block( o, source,  buf,  false ))
        }
        else
        {
            BLM_TRY(xoico_cdaleth_s_trans_statement_as_block( o, source,  buf,  false ))
        }
        return  0;
    } // try
}

er_t xoico_cdaleth_s_trans_control_switch( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth_control.x:292:1
    {
        BLM_TRY(xoico_cdaleth_s_trans( o, source,  "switch",  buf ))
        BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  buf ))
        BLM_TRY(xoico_cdaleth_s_trans( o, source,  "(",  buf ))
        BLM_TRY(xoico_cdaleth_s_trans_expression( o, source,  buf,  NULL )) // def
        BLM_TRY(xoico_cdaleth_s_trans( o, source,  ")",  buf ))
        BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  buf ))
        BLM_TRY(xoico_cdaleth_s_trans_block( o, source,  buf,  true ))
        return  0;
    } // try
}

er_t xoico_cdaleth_s_trans_control_case( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth_control.x:309:1
    {
        BLM_TRY(xoico_cdaleth_s_trans( o, source,  "case",  buf ))
        BLM_TRY(xoico_cdaleth_s_trans_expression( o, source,  buf,  NULL ))
        BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  buf ))
        BLM_TRY(xoico_cdaleth_s_trans( o, source,  ":",  buf ))
        BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  buf ))
        BLM_TRY(xoico_cdaleth_s_trans_statement_as_block( o, source,  buf,  false ))
    
        return  0;
    } // try
}

er_t xoico_cdaleth_s_trans_control_default( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth_control.x:326:1
    {
        BLM_TRY(xoico_cdaleth_s_trans( o, source,  "default",  buf ))
        BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  buf ))
        BLM_TRY(xoico_cdaleth_s_trans( o, source,  ":",  buf ))
        BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  buf ))
        BLM_TRY(xoico_cdaleth_s_trans_statement_as_block( o, source,  buf,  false ))
        return  0;
    } // try
}

er_t xoico_cdaleth_s_trans_control_break( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth_control.x:341:1
    {
        BLM_TRY(xoico_cdaleth_s_parse( o, source,  "break ;" ))
    
        sz_t ledge_level = -1;
        bl_t use_blm = false;
    
        for( sz_t i = o->stack_block.adl.size - 1; i >= 0; i-- )
        {
            const xoico_cdaleth_stack_block_unit_s* unit = o->stack_block.adl.data[ i ];
            use_blm = use_blm || unit->use_blm;
            if( unit->break_ledge )
            {
                ledge_level = unit->level;
                break;
            }
        }
    
        if( ledge_level == -1 ) return  xoico_cdaleth_s_parse_err_fa( o, source,  "'break' has no ledge." );
    
        if( use_blm )
        {
            st_s_push_fa( buf, "BLM_BREAK_LEVEL(#<sz_t>);",  ledge_level );
        }
        else
        {
            st_s_push_sc( buf, "break;" );
        }
    
        return  0;
    } // try
}

er_t xoico_cdaleth_s_trans_control_return( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth_control.x:378:1
    BLM_INIT_LEVEL(0);{
        BLM_TRY(xoico_cdaleth_s_parse( o, source,  "return" ))
    
        st_s* buf_expr = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create() ));
        xoico_typespec_s* typespec_expr = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create() ));
        const xoico_typespec_s* typespec_ret = o->typespec_ret;
    
        BLM_TRY(xoico_cdaleth_s_trans_expression( o, source,  buf_expr,  typespec_expr ))
        BLM_TRY(xoico_cdaleth_s_trans_whitespace( o, source,  buf ))
        BLM_TRY(xoico_cdaleth_s_parse( o, source,  ";" ))
    
        if( typespec_expr->type )
        {
            if( !xoico_cdaleth_s_returns_a_value( o) )
            {
                BLM_RETURNV(er_t, xoico_cdaleth_s_parse_err_fa( o, source,  "Function does not return a value." ))
            }
        }
    
        bl_t use_blm = false;
    
        {const xoico_cdaleth_stack_block_unit_adl_s* __a=&(o->stack_block.adl );if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_cdaleth_stack_block_unit_s* e=__a->data[__i];
        {
            if( e->use_blm )
            {
                use_blm = true;
                break;
            }
        }
    
        }}if( use_blm )
        {
            if( xoico_cdaleth_s_returns_a_value( o) )
            {
                st_s_push_sc( buf, "BLM_RETURNV(" );
                BLM_TRY(xoico_cdaleth_s_push_typespec( o, typespec_ret,  buf ))
                st_s_push_sc( buf, "," );
                if( typespec_expr->type )
                {
                    BLM_TRY(xoico_cdaleth_s_adapt_expression( o, source,  typespec_expr,  typespec_ret,  buf_expr,  buf ))
                }
                else
                {
                    st_s_push_st( buf, buf_expr );
                }
                st_s_push_sc( buf, ")" );  // do not terminate BLM_RETURNV macro with a semicolon, otherwise if-else statements might not be handled correctly
            }
            else
            {
                st_s_push_sc( buf, "BLM_RETURN" );
                st_s_push_st( buf, buf_expr );
                st_s_push_sc( buf, ";" );
            }
        }
        else
        {
            st_s_push_sc( buf, "return " );
            if( typespec_expr->type )
            {
                BLM_TRY(xoico_cdaleth_s_adapt_expression( o, source,  typespec_expr,  typespec_ret,  buf_expr,  buf ))
            }
            else
            {
                st_s_push_st( buf, buf_expr );
            }
            st_s_push_sc( buf, ";" );
        }
    
        BLM_RETURNV(er_t, 0)
    } // try
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
    "bcore_hmap_tpuz_s hmap_name;"
"}";

void xoico_cdaleth_stack_var_s_rehash_names( xoico_cdaleth_stack_var_s* o )
{
    // xoico_cdaleth.h:63:9
    bcore_hmap_tpuz_s_clear( &(o->hmap_name));
    for( sz_t i = 0; i < o->adl.size; i++ ) bcore_hmap_tpuz_s_set( &(o->hmap_name), o->adl.data[i]->name,  i );
}

xoico_cdaleth_stack_var_s* xoico_cdaleth_stack_var_s_push_unit( xoico_cdaleth_stack_var_s* o, const xoico_cdaleth_stack_var_unit_s* unit )
{
    // xoico_cdaleth.h:69:9
    xoico_cdaleth_stack_var_unit_adl_s_push_c( &(o->adl), unit );
    bcore_hmap_tpuz_s_set( &(o->hmap_name), unit->name,  o->adl.size - 1 );
    return  o;
}

xoico_cdaleth_stack_var_s* xoico_cdaleth_stack_var_s_pop_level( xoico_cdaleth_stack_var_s* o, sz_t level )
{
    // xoico_cdaleth.h:76:9
    sz_t size = o->adl.size;
    while( size > 0 && o->adl.data[ size - 1 ]->level >= level ) size--;
    xoico_cdaleth_stack_var_unit_adl_s_set_size( &(o->adl), size );
    xoico_cdaleth_stack_var_s_rehash_names( o);
    return  o;
}

const xoico_typespec_s* xoico_cdaleth_stack_var_s_get_typespec( const xoico_cdaleth_stack_var_s* o, tp_t name )
{
    // xoico_cdaleth.h:85:9
    uz_t* p_idx = bcore_hmap_tpuz_s_get( &(o->hmap_name), name );
    if( !p_idx ) return  NULL;
    return &( o->adl.data[ *p_idx ]->typespec);
}

const sz_t xoico_cdaleth_stack_var_s_get_level( const xoico_cdaleth_stack_var_s* o, tp_t name )
{
    // xoico_cdaleth.h:93:9
    uz_t* p_idx = bcore_hmap_tpuz_s_get( &(o->hmap_name), name );
    if( !p_idx ) return  -1;
    return  o->adl.data[ *p_idx ]->level;
}

void xoico_cdaleth_stack_var_s_clear( xoico_cdaleth_stack_var_s* o )
{
    // xoico_cdaleth.h:100:9
    xoico_cdaleth_stack_var_unit_adl_s_clear( &(o->adl));
    bcore_hmap_tpuz_s_clear( &(o->hmap_name));
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
    // xoico_cdaleth.h:134:9
    xoico_cdaleth_stack_block_unit_adl_s_set_size( &(o->adl), sz_max( o->adl.size - 1, 0 ) );
    return  o;
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
            BCORE_REGISTER_FEATURE( xoico_cengine_is_reserved );
            BCORE_REGISTER_FFUNC( xoico_cengine_is_reserved, xoico_cengine_is_reserved_default );
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
            BCORE_REGISTER_NAME( scope );
            BCORE_REGISTER_NAME( scope_local );
            BCORE_REGISTER_NAME( scope_func );
            BCORE_REGISTER_NAME( keep_func );
            BCORE_REGISTER_NAME( keep_block );
            BCORE_REGISTER_NAME( fork );
            BCORE_REGISTER_NAME( try );
            BCORE_REGISTER_NAME( if );
            BCORE_REGISTER_NAME( else );
            BCORE_REGISTER_NAME( while );
            BCORE_REGISTER_NAME( do );
            BCORE_REGISTER_NAME( for );
            BCORE_REGISTER_NAME( foreach );
            BCORE_REGISTER_NAME( switch );
            BCORE_REGISTER_NAME( case );
            BCORE_REGISTER_NAME( default );
            BCORE_REGISTER_NAME( break );
            BCORE_REGISTER_NAME( return );
            BCORE_REGISTER_FFUNC( xoico_cengine_is_reserved, xoico_cdaleth_s_is_reserved );
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
// XOILA_OUT_SIGNATURE 0x79817A94EE2B1F7Aull
