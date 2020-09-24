/** This file was generated from xoila source code.
 *  Compiling Agent : xoico_compiler (C) 2020 J.B.Steffens
 *  Last File Update: 2020-09-24T17:30:04Z
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
 *  xoico_cgimel.h
 *  xoico_xce.h
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
    "feature aware xoico : finalize = xoico_finalize__;"
    "feature aware xoico : expand_setup = xoico_expand_setup__;"
    "feature aware xoico : expand_forward = xoico_expand_forward__;"
    "feature aware xoico : expand_indef_typedef = xoico_expand_indef_typedef__;"
    "feature aware xoico : expand_spect_declaration = xoico_expand_spect_declaration__;"
    "feature aware xoico : expand_spect_definition = xoico_expand_spect_definition__;"
    "feature aware xoico : expand_declaration = xoico_expand_declaration__;"
    "feature aware xoico : expand_indef_declaration = xoico_expand_indef_declaration__;"
    "feature aware xoico : expand_definition = xoico_expand_definition__;"
    "feature aware xoico : expand_init1 = xoico_expand_init1__;"
"}";

/**********************************************************************************************************************/
// source: xoico_name.h
#include "xoico_name.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_name

BCORE_DEFINE_OBJECT_INST_P( xoico_name_s )
"aware xoico_name"
"{"
    "st_s name;"
    "hidden aware xoico_group_s* group;"
    "bcore_source_point_s source_point;"
    "func xoico:parse;"
    "func xoico:get_hash;"
    "func xoico:get_global_name_sc;"
    "func xoico:expand_declaration;"
    "func xoico:expand_init1;"
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

/**********************************************************************************************************************/
// source: xoico_typespec.h
#include "xoico_typespec.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_typespec

BCORE_DEFINE_OBJECT_INST_P( xoico_typespec_s )
"aware xoico_typespec"
"{"
    "bl_t is_const;"
    "tp_t type;"
    "sz_t indirection;"
    "func xoico:get_hash;"
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
    "st_s st;"
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

/**********************************************************************************************************************/
// source: xoico_feature.h
#include "xoico_feature.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_feature

BCORE_DEFINE_OBJECT_INST_P( xoico_feature_s )
"aware xoico_feature"
"{"
    "xoico_signature_s signature;"
    "st_s st_default_name;"
    "xoico_body_s => default_body;"
    "bl_t strict;"
    "bl_t flag_p;"
    "bl_t flag_t;"
    "bl_t flag_a;"
    "bl_t flag_r;"
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
    "bl_t overloadable = false;"
    "xoico_body_s => body;"
    "hidden aware xoico_group_s* group;"
    "hidden aware xoico_stamp_s* stamp;"
    "bcore_source_point_s source_point;"
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
    "st_s name;"
    "private xoico_group_s* group;"
    "st_s trait_name = \"bcore_inst\";"
    "tp_t hash;"
    "tp_t beta = 0;"
    "bl_t expandable = true;"
    "bl_t has_features;"
    "bl_t is_aware;"
    "bl_t retrievable;"
    "bl_t short_spect_name;"
    "private xoico_stamp_s -> extending;"
    "xoico_funcs_s funcs;"
    "private aware xoico_source_s* source;"
    "bcore_source_point_s source_point;"
    "func xoico:parse;"
    "func xoico:get_hash;"
    "func xoico:get_global_name_sc;"
    "func xoico:finalize;"
    "func xoico:expand_setup;"
"}";

/**********************************************************************************************************************/
// source: xoico_stamp.h
#include "xoico_stamp.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_stamp

BCORE_DEFINE_OBJECT_INST_P( xoico_stamp_s )
"aware xoico_stamp"
"{"
    "st_s name;"
    "st_s trait_name;"
    "st_s => self_source;"
    "bcore_self_s => self;"
    "xoico_funcs_s funcs;"
    "private aware xoico_group_s* group;"
    "bcore_source_point_s source_point;"
    "func xoico:get_hash;"
    "func xoico:get_global_name_sc;"
    "func xoico:finalize;"
    "func xoico:expand_setup;"
    "func xoico:expand_declaration;"
    "func xoico:expand_forward;"
    "func xoico:expand_indef_declaration;"
    "func xoico:expand_definition;"
    "func xoico:expand_init1;"
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
    "tp_t target_pre_hash = 30;"
    "bl_t register_plain_functions = true;"
    "bl_t register_signatures = false;"
    "bl_t overwrite_unsigned_target_files = false;"
    "bl_t always_expand = false;"
    "bl_t dry_run = false;"
    "sz_t verbosity = 1;"
    "func xoico:finalize;"
    "func xoico:expand_setup;"
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
    "aware xoico_cengine => cengine = xoico_caleph_s;"
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
    if( !o->root_folder )
    {
        o->root_folder = bcore_file_folder_path( bcore_source_a_get_file( source ) );
        st_s_attach( &o->root_folder, bcore_file_path_minimized( o->root_folder->sc ) );
    }
}

const xoico_builder_target_s* xoico_builder_target_s_name_match( const xoico_builder_target_s* o, sc_t name )
{
    if( o->name && sc_t_equal( name, o->name->sc ) ) return o;
    if( o->parent_ ) return xoico_builder_target_s_name_match( o->parent_, name );
    return NULL;
}

void xoico_builder_target_s_push_target_index_to_arr( const xoico_builder_target_s* o, bcore_arr_sz_s* arr )
{
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
    o->compiler->dry_run = v;
    return 0;
}

bl_t xoico_builder_main_s_get_dry_run( const xoico_builder_main_s* o )
{
    return o->compiler->dry_run;
}

er_t xoico_builder_main_s_set_always_expand( xoico_builder_main_s* o, bl_t v )
{
    o->compiler->always_expand = v;
    return 0;
}

bl_t xoico_builder_main_s_get_always_expand( const xoico_builder_main_s* o )
{
    return o->compiler->always_expand;
}

er_t xoico_builder_main_s_set_overwrite_unsigned_target_files( xoico_builder_main_s* o, bl_t v )
{
    o->compiler->overwrite_unsigned_target_files = v;
    return 0;
}

bl_t xoico_builder_main_s_get_overwrite_unsigned_target_files( const xoico_builder_main_s* o )
{
    return o->compiler->overwrite_unsigned_target_files;
}

/**********************************************************************************************************************/
// source: xoico_cengine.h
#include "xoico_cengine.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_cengine

XOILA_DEFINE_SPECT( xoico, xoico_cengine )
"{"
    "bcore_spect_header_s header;"
    "feature aware xoico_cengine : translate;"
    "feature aware xoico_cengine : get_hash = xoico_cengine_get_hash__;"
"}";

/**********************************************************************************************************************/
// source: xoico_caleph.h
#include "xoico_caleph.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_caleph

BCORE_DEFINE_OBJECT_INST_P( xoico_caleph_s )
"aware xoico_caleph"
"{"
    "sc_t obj_type;"
    "xoico_args_s -> args;"
    "xoico_compiler_s -> compiler;"
    "hidden xoico_caleph_tn_stack_s stack;"
    "func xoico_cengine:translate;"
"}";

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_caleph_tn

BCORE_DEFINE_OBJECT_INST_P( xoico_caleph_tn_unit_s )
"bcore_inst"
"{"
    "tp_t type;"
    "tp_t name;"
    "sz_t level;"
"}";

BCORE_DEFINE_OBJECT_INST_P( xoico_caleph_tn_adl_s )
"aware bcore_array"
"{"
    "xoico_caleph_tn_unit_s => [];"
"}";

BCORE_DEFINE_OBJECT_INST_P( xoico_caleph_tn_stack_s )
"aware xoico_caleph_tn"
"{"
    "xoico_caleph_tn_adl_s adl;"
    "bcore_hmap_name_s name_map;"
"}";

xoico_caleph_tn_stack_s* xoico_caleph_tn_stack_s_push( xoico_caleph_tn_stack_s* o, tp_t type, tp_t name, sz_t level )
{
    xoico_caleph_tn_unit_s* unit = xoico_caleph_tn_unit_s_create();
    unit->type = type;
    unit->name = name;
    unit->level = level;
    xoico_caleph_tn_adl_s_push_d( &o->adl, unit );
    return o;
}

xoico_caleph_tn_stack_s* xoico_caleph_tn_stack_s_push_sc( xoico_caleph_tn_stack_s* o, sc_t type, sc_t name, sz_t level )
{
    xoico_caleph_tn_unit_s* unit = xoico_caleph_tn_unit_s_create();
    unit->type = bcore_hmap_name_s_set_sc( &o->name_map, type );
    unit->name = bcore_hmap_name_s_set_sc( &o->name_map, name );
    unit->level = level;
    xoico_caleph_tn_adl_s_push_d( &o->adl, unit );
    return o;
}

xoico_caleph_tn_stack_s* xoico_caleph_tn_stack_s_pop( xoico_caleph_tn_stack_s* o, sz_t level )
{
    sz_t new_size = o->adl.size;
    for( sz_t i = o->adl.size - 1; i >= 0; i-- )
    {
        if( o->adl.data[ i ]->level < level ) break;
        new_size = i;
    }
    xoico_caleph_tn_adl_s_set_size( &o->adl, new_size );
    return o;
}

tp_t xoico_caleph_tn_stack_s_get_type( xoico_caleph_tn_stack_s* o, tp_t name )
{
    for( sz_t i = o->adl.size - 1; i >= 0; i-- )
    {
        if( o->adl.data[ i ]->name == name ) return o->adl.data[ i ]->type;
    }
    return 0;
}

sc_t xoico_caleph_tn_stack_s_get_type_sc( xoico_caleph_tn_stack_s* o, sc_t name )
{
    return bcore_hmap_name_s_get_sc( &o->name_map, xoico_caleph_tn_stack_s_get_type( o, btypeof( name ) ) );
}

void xoico_caleph_tn_stack_s_clear( xoico_caleph_tn_stack_s* o )
{
    bcore_hmap_name_s_clear( &o->name_map );
    xoico_caleph_tn_adl_s_clear( &o->adl );
}

void xoico_caleph_tn_stack_s_init_from_args( xoico_caleph_tn_stack_s* o, sc_t obj_type, sc_t obj_name, const xoico_args_s* args )
{
    const xoico_compiler_s* compiler = xoico_group_s_get_compiler( args->group );
    xoico_caleph_tn_stack_s_clear( o );
    if( obj_type ) xoico_caleph_tn_stack_s_push_sc( o, obj_type, obj_name, 0 );
    BFOR_EACH( i, args )
    {
        sc_t sc_type = xoico_compiler_s_nameof( compiler, args->data[ i ].typespec.type );
        sc_t sc_name = xoico_compiler_s_nameof( compiler, args->data[ i ].name );
        xoico_caleph_tn_stack_s_push_sc( o, sc_type, sc_name, 0 );
    }
}

/**********************************************************************************************************************/
// source: xoico_cgimel.h
#include "xoico_cgimel.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_cgimel

BCORE_DEFINE_OBJECT_INST_P( xoico_cgimel_s )
"aware xoico_cgimel"
"{"
    "aware xoico_cengine => fallback;"
    "bl_t verbose;"
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
    sc_t name = bcore_hmap_name_s_get_sc( &o->hmap_name, type );
    if( !name ) name = xoico_compiler_s_nameof( o->compiler, type );
    return name;
}

void xoico_cgimel_s_inc_level( xoico_cgimel_s* o )
{
    o->level++;
}

void xoico_cgimel_s_dec_level( xoico_cgimel_s* o )
{
    xoico_cgimel_stack_s_pop_level( &o->stack, o->level );
    o->level--;
}

void xoico_cgimel_s_push_typedecl( xoico_cgimel_s* o, const xoico_typespec_s* typespec, tp_t name )
{
    BLM_INIT();
    xoico_cgimel_stack_unit_s* unit = BLM_CREATE( xoico_cgimel_stack_unit_s );
    unit->level = o->level;
    unit->name = name;
    xoico_typespec_s_copy( &unit->typespec, typespec );
    xoico_cgimel_stack_s_push_unit( &o->stack, unit );
    BLM_DOWN();
}

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
    sz_t size = o->adl.size;
    while( size > 0 && o->adl.data[ size - 1 ]->level >= level ) size--;
    xoico_cgimel_stack_unit_adl_s_set_size( &o->adl, size );
    return o;
}

const xoico_typespec_s* xoico_cgimel_stack_s_get_typespec( const xoico_cgimel_stack_s* o, tp_t name )
{
    for( sz_t i = o->adl.size - 1; i >= 0; i-- )
    {
        if( o->adl.data[ i ]->name == name ) return &o->adl.data[ i ]->typespec;
    }
    return NULL;
}

/**********************************************************************************************************************/
// source: xoico_xce.h
#include "xoico_xce.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_xce

BCORE_DEFINE_OBJECT_INST_P( xoico_xce_s )
"aware xoico_xce"
"{"
    "xoico_compiler_s -> compiler;"
    "sz_t level;"
    "xoico_xce_stack_s stack;"
    "bcore_hmap_name_s hmap_name;"
"}";

sc_t xoico_xce_s_nameof( xoico_xce_s* o, tp_t type )
{
    sc_t name = bcore_hmap_name_s_get_sc( &o->hmap_name, type );
    if( !name ) name = xoico_compiler_s_nameof( o->compiler, type );
    return name;
}

er_t xoico_xce_s_setup( xoico_xce_s* o, bl_t obj_const, tp_t obj_type, tp_t obj_name, const xoico_args_s* args )
{
    BLM_INIT();
    xoico_xce_stack_s_clear( &o->stack );
    o->level = 0;
    
    xoico_xce_stack_unit_s* unit = BLM_CREATE( xoico_xce_stack_unit_s );
    
    if( obj_type )
    {
        unit->typespec.is_const = obj_const;
        unit->typespec.type = obj_type;
        unit->typespec.indirection = 1;
        unit->name = obj_name;
        unit->level = 0;
        xoico_xce_stack_s_push_unit( &o->stack, unit );
        bcore_hmap_name_s_set_sc( &o->hmap_name, xoico_compiler_s_nameof( o->compiler, obj_type ) );
        bcore_hmap_name_s_set_sc( &o->hmap_name, xoico_compiler_s_nameof( o->compiler, obj_name ) );
    }
    
    BFOR_EACH( i, args )
    {
        const xoico_arg_s* arg = &args->data[ i ];
        if( arg->typespec.type && arg->name && arg->typespec.indirection == 1 )
        {
            xoico_typespec_s_copy( &unit->typespec, &arg->typespec );
            unit->name = arg->name;
            unit->level = 0;
            xoico_xce_stack_s_push_unit( &o->stack, unit );
            bcore_hmap_name_s_set_sc( &o->hmap_name, xoico_compiler_s_nameof( o->compiler, arg->typespec.type ) );
            bcore_hmap_name_s_set_sc( &o->hmap_name, xoico_compiler_s_nameof( o->compiler, arg->name ) );
        }
    }
    
    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_xce_stack

BCORE_DEFINE_OBJECT_INST_P( xoico_xce_stack_unit_s )
"bcore_inst"
"{"
    "sz_t level;"
    "tp_t name;"
    "xoico_typespec_s typespec;"
"}";

BCORE_DEFINE_OBJECT_INST_P( xoico_xce_stack_unit_adl_s )
"aware bcore_array"
"{"
    "xoico_xce_stack_unit_s => [];"
"}";

BCORE_DEFINE_OBJECT_INST_P( xoico_xce_stack_s )
"aware xoico_xce_stack"
"{"
    "xoico_xce_stack_unit_adl_s adl;"
"}";

xoico_xce_stack_s* xoico_xce_stack_s_pop_level( xoico_xce_stack_s* o, sz_t level )
{
    sz_t size = o->adl.size;
    while( size > 0 && o->adl.data[ size ]->level >= level ) size--;
    xoico_xce_stack_unit_adl_s_set_size( &o->adl, size );
    return o;
}

const xoico_typespec_s* xoico_xce_stack_s_get_typespec( const xoico_xce_stack_s* o, tp_t name )
{
    for( sz_t i = o->adl.size - 1; i >= 0; i-- )
    {
        if( o->adl.data[ i ]->name == name ) return &o->adl.data[ i ]->typespec;
    }
    return NULL;
}

//----------------------------------------------------------------------------------------------------------------------
// group: sim

BCORE_DEFINE_OBJECT_INST_P( sim_s )
"aware sim"
"{"
    "bl_t bl;"
    "func ^:setup;"
"}";

BCORE_DEFINE_OBJECT_INST_P( sim_foo0_s )
"aware sim"
"{"
    "st_s st;"
    "func ^:setup;"
"}";

BCORE_DEFINE_OBJECT_INST_P( sim_foo1_s )
"aware sim"
"{"
    "sim_foo0_s f0;"
    "func ^:setup;"
"}";

BCORE_DEFINE_OBJECT_INST_P( sim_foo2_s )
"aware sim"
"{"
    "sim_foo1_s => f1!;"
    "sim_foo2_s => f2;"
    "func ^:setup;"
"}";

XOILA_DEFINE_SPECT( xoico_xce, sim )
"{"
    "bcore_spect_header_s header;"
    "feature aware sim : setup;"
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
            BCORE_REGISTER_FEATURE( xoico_finalize );
            BCORE_REGISTER_FFUNC( xoico_finalize, xoico_finalize__ );
            BCORE_REGISTER_FEATURE( xoico_expand_setup );
            BCORE_REGISTER_FFUNC( xoico_expand_setup, xoico_expand_setup__ );
            BCORE_REGISTER_FEATURE( xoico_expand_forward );
            BCORE_REGISTER_FFUNC( xoico_expand_forward, xoico_expand_forward__ );
            BCORE_REGISTER_FEATURE( xoico_expand_indef_typedef );
            BCORE_REGISTER_FFUNC( xoico_expand_indef_typedef, xoico_expand_indef_typedef__ );
            BCORE_REGISTER_FEATURE( xoico_expand_spect_declaration );
            BCORE_REGISTER_FFUNC( xoico_expand_spect_declaration, xoico_expand_spect_declaration__ );
            BCORE_REGISTER_FEATURE( xoico_expand_spect_definition );
            BCORE_REGISTER_FFUNC( xoico_expand_spect_definition, xoico_expand_spect_definition__ );
            BCORE_REGISTER_FEATURE( xoico_expand_declaration );
            BCORE_REGISTER_FFUNC( xoico_expand_declaration, xoico_expand_declaration__ );
            BCORE_REGISTER_FEATURE( xoico_expand_indef_declaration );
            BCORE_REGISTER_FFUNC( xoico_expand_indef_declaration, xoico_expand_indef_declaration__ );
            BCORE_REGISTER_FEATURE( xoico_expand_definition );
            BCORE_REGISTER_FFUNC( xoico_expand_definition, xoico_expand_definition__ );
            BCORE_REGISTER_FEATURE( xoico_expand_init1 );
            BCORE_REGISTER_FFUNC( xoico_expand_init1, xoico_expand_init1__ );
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
            BCORE_REGISTER_TRAIT( xoico_name, xoico );

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
            BCORE_REGISTER_TRAIT( xoico_forward, xoico );

            // --------------------------------------------------------------------
            // source: xoico_typespec.h

            // group: xoico_typespec
            BCORE_REGISTER_FFUNC( xoico_get_hash, xoico_typespec_s_get_hash );
            BCORE_REGISTER_OBJECT( xoico_typespec_s );
            BCORE_REGISTER_TRAIT( xoico_typespec, xoico );

            // --------------------------------------------------------------------
            // source: xoico_arg.h

            // group: xoico_arg
            BCORE_REGISTER_FFUNC( xoico_parse, xoico_arg_s_parse );
            BCORE_REGISTER_FFUNC( xoico_get_hash, xoico_arg_s_get_hash );
            BCORE_REGISTER_OBJECT( xoico_arg_s );
            BCORE_REGISTER_TRAIT( xoico_arg, xoico );

            // --------------------------------------------------------------------
            // source: xoico_args.h

            // group: xoico_args
            BCORE_REGISTER_FFUNC( xoico_parse, xoico_args_s_parse );
            BCORE_REGISTER_FFUNC( xoico_get_hash, xoico_args_s_get_hash );
            BCORE_REGISTER_OBJECT( xoico_args_s );
            BCORE_REGISTER_TRAIT( xoico_args, xoico );

            // --------------------------------------------------------------------
            // source: xoico_signature.h

            // group: xoico_signature
            BCORE_REGISTER_FFUNC( xoico_parse, xoico_signature_s_parse );
            BCORE_REGISTER_FFUNC( xoico_get_hash, xoico_signature_s_get_hash );
            BCORE_REGISTER_FFUNC( xoico_get_global_name_sc, xoico_signature_s_get_global_name_sc );
            BCORE_REGISTER_OBJECT( xoico_signature_s );
            BCORE_REGISTER_TRAIT( xoico_signature, xoico );

            // --------------------------------------------------------------------
            // source: xoico_body.h

            // group: xoico_body
            BCORE_REGISTER_FFUNC( xoico_get_hash, xoico_body_code_s_get_hash );
            BCORE_REGISTER_OBJECT( xoico_body_code_s );
            BCORE_REGISTER_FFUNC( xoico_get_hash, xoico_body_s_get_hash );
            BCORE_REGISTER_FFUNC( xoico_get_global_name_sc, xoico_body_s_get_global_name_sc );
            BCORE_REGISTER_OBJECT( xoico_body_s );
            BCORE_REGISTER_TRAIT( xoico_body, xoico );

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
            BCORE_REGISTER_TRAIT( xoico_feature, xoico );

            // --------------------------------------------------------------------
            // source: xoico_func.h

            // group: xoico_func
            BCORE_REGISTER_OBJECT( xoico_func_s );
            BCORE_REGISTER_TRAIT( xoico_func, xoico );

            // --------------------------------------------------------------------
            // source: xoico_funcs.h

            // group: xoico_funcs
            BCORE_REGISTER_OBJECT( xoico_funcs_s );
            BCORE_REGISTER_TRAIT( xoico_funcs, xoico );

            // --------------------------------------------------------------------
            // source: xoico_group.h

            // group: xoico_group
            BCORE_REGISTER_OBJECT( xoico_group_source_stack_s );
            BCORE_REGISTER_FFUNC( xoico_parse, xoico_group_s_parse );
            BCORE_REGISTER_FFUNC( xoico_get_hash, xoico_group_s_get_hash );
            BCORE_REGISTER_FFUNC( xoico_get_global_name_sc, xoico_group_s_get_global_name_sc );
            BCORE_REGISTER_FFUNC( xoico_finalize, xoico_group_s_finalize );
            BCORE_REGISTER_FFUNC( xoico_expand_setup, xoico_group_s_expand_setup );
            BCORE_REGISTER_OBJECT( xoico_group_s );
            BCORE_REGISTER_TRAIT( xoico_group, xoico );

            // --------------------------------------------------------------------
            // source: xoico_stamp.h

            // group: xoico_stamp
            BCORE_REGISTER_FFUNC( xoico_get_hash, xoico_stamp_s_get_hash );
            BCORE_REGISTER_FFUNC( xoico_get_global_name_sc, xoico_stamp_s_get_global_name_sc );
            BCORE_REGISTER_FFUNC( xoico_finalize, xoico_stamp_s_finalize );
            BCORE_REGISTER_FFUNC( xoico_expand_setup, xoico_stamp_s_expand_setup );
            BCORE_REGISTER_FFUNC( xoico_expand_declaration, xoico_stamp_s_expand_declaration );
            BCORE_REGISTER_FFUNC( xoico_expand_forward, xoico_stamp_s_expand_forward );
            BCORE_REGISTER_FFUNC( xoico_expand_indef_declaration, xoico_stamp_s_expand_indef_declaration );
            BCORE_REGISTER_FFUNC( xoico_expand_definition, xoico_stamp_s_expand_definition );
            BCORE_REGISTER_FFUNC( xoico_expand_init1, xoico_stamp_s_expand_init1 );
            BCORE_REGISTER_OBJECT( xoico_stamp_s );
            BCORE_REGISTER_TRAIT( xoico_stamp, xoico );

            // --------------------------------------------------------------------
            // source: xoico_nested_group.h

            // group: xoico_nested_group
            BCORE_REGISTER_FFUNC( xoico_get_hash, xoico_nested_group_s_get_hash );
            BCORE_REGISTER_FFUNC( xoico_expand_forward, xoico_nested_group_s_expand_forward );
            BCORE_REGISTER_FFUNC( xoico_expand_indef_declaration, xoico_nested_group_s_expand_indef_declaration );
            BCORE_REGISTER_OBJECT( xoico_nested_group_s );
            BCORE_REGISTER_TRAIT( xoico_nested_group, xoico );

            // --------------------------------------------------------------------
            // source: xoico_source.h

            // group: xoico_source
            BCORE_REGISTER_FFUNC( xoico_finalize, xoico_source_s_finalize );
            BCORE_REGISTER_FFUNC( xoico_expand_setup, xoico_source_s_expand_setup );
            BCORE_REGISTER_OBJECT( xoico_source_s );
            BCORE_REGISTER_TRAIT( xoico_source, xoico );

            // --------------------------------------------------------------------
            // source: xoico_target.h

            // group: xoico_target
            BCORE_REGISTER_FFUNC( xoico_finalize, xoico_target_s_finalize );
            BCORE_REGISTER_FFUNC( xoico_expand_setup, xoico_target_s_expand_setup );
            BCORE_REGISTER_OBJECT( xoico_target_s );
            BCORE_REGISTER_TRAIT( xoico_target, xoico );

            // --------------------------------------------------------------------
            // source: xoico_compiler.h

            // group: xoico_compiler
            BCORE_REGISTER_OBJECT( xoico_compiler_type_info_s );
            BCORE_REGISTER_OBJECT( xoico_compiler_element_info_s );
            BCORE_REGISTER_FFUNC( xoico_finalize, xoico_compiler_s_finalize );
            BCORE_REGISTER_FFUNC( xoico_expand_setup, xoico_compiler_s_expand_setup );
            BCORE_REGISTER_OBJECT( xoico_compiler_s );
            BCORE_REGISTER_TRAIT( xoico_compiler, xoico );

            // --------------------------------------------------------------------
            // source: xoico_builder.h

            // group: xoico_builder
            BCORE_REGISTER_OBJECT( xoico_builder_arr_target_s );
            BCORE_REGISTER_FFUNC( bcore_via_call_source, xoico_builder_target_s_source );
            BCORE_REGISTER_OBJECT( xoico_builder_target_s );
            BCORE_REGISTER_OBJECT( xoico_builder_main_s );
            BCORE_REGISTER_TRAIT( xoico_builder, xoico );

            // --------------------------------------------------------------------
            // source: xoico_cengine.h

            // group: xoico_cengine
            BCORE_REGISTER_FEATURE( xoico_cengine_translate );
            BCORE_REGISTER_FEATURE( xoico_cengine_get_hash );
            BCORE_REGISTER_FFUNC( xoico_cengine_get_hash, xoico_cengine_get_hash__ );
            XOILA_REGISTER_SPECT( xoico_cengine );

            // --------------------------------------------------------------------
            // source: xoico_caleph.h

            // group: xoico_caleph
            BCORE_REGISTER_FFUNC( xoico_cengine_translate, xoico_caleph_s_translate );
            BCORE_REGISTER_OBJECT( xoico_caleph_s );
            BCORE_REGISTER_TRAIT( xoico_caleph, xoico_cengine );

            // group: xoico_caleph_tn
            BCORE_REGISTER_OBJECT( xoico_caleph_tn_unit_s );
            BCORE_REGISTER_OBJECT( xoico_caleph_tn_adl_s );
            BCORE_REGISTER_OBJECT( xoico_caleph_tn_stack_s );
            BCORE_REGISTER_TRAIT( xoico_caleph_tn, xoico_caleph );

            // --------------------------------------------------------------------
            // source: xoico_cgimel.h

            // group: xoico_cgimel
            BCORE_REGISTER_NAME( static );
            BCORE_REGISTER_NAME( volatile );
            BCORE_REGISTER_FFUNC( xoico_cengine_translate, xoico_cgimel_s_translate );
            BCORE_REGISTER_OBJECT( xoico_cgimel_s );
            BCORE_REGISTER_TRAIT( xoico_cgimel, xoico_cengine );

            // group: xoico_cgimel_stack
            BCORE_REGISTER_OBJECT( xoico_cgimel_stack_unit_s );
            BCORE_REGISTER_OBJECT( xoico_cgimel_stack_unit_adl_s );
            BCORE_REGISTER_OBJECT( xoico_cgimel_stack_s );
            BCORE_REGISTER_TRAIT( xoico_cgimel_stack, xoico_cgimel );

            // --------------------------------------------------------------------
            // source: xoico_xce.h

            // group: xoico_xce
            BCORE_REGISTER_OBJECT( xoico_xce_s );
            BCORE_REGISTER_TRAIT( xoico_xce, xoico );

            // group: xoico_xce_stack
            BCORE_REGISTER_OBJECT( xoico_xce_stack_unit_s );
            BCORE_REGISTER_OBJECT( xoico_xce_stack_unit_adl_s );
            BCORE_REGISTER_OBJECT( xoico_xce_stack_s );
            BCORE_REGISTER_TRAIT( xoico_xce_stack, xoico_xce );

            // group: sim
            BCORE_REGISTER_FEATURE( sim_setup );
            BCORE_REGISTER_FFUNC( sim_setup, sim_s_setup );
            BCORE_REGISTER_OBJECT( sim_s );
            BCORE_REGISTER_FFUNC( sim_setup, sim_foo0_s_setup );
            BCORE_REGISTER_OBJECT( sim_foo0_s );
            BCORE_REGISTER_FFUNC( sim_setup, sim_foo1_s_setup );
            BCORE_REGISTER_OBJECT( sim_foo1_s );
            BCORE_REGISTER_FFUNC( sim_setup, sim_foo2_s_setup );
            BCORE_REGISTER_OBJECT( sim_foo2_s );
            XOILA_REGISTER_SPECT( sim );
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
// XOILA_OUT_SIGNATURE 0x79715E422312587Aull
