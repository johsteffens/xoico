/** This file was generated from xoila source code.
 *  Compiling Agent : xoico_compiler (C) 2020 J.B.Steffens
 *  Last File Update: 2020-08-17T16:08:51Z
 *
 *  Copyright and License of this File:
 *
 *  Generated code inherits the copyright and license of the underlying xoila source code.
 *  Source code defining this file is distributed across following files:
 *
 *  xoico.h
 *  xoico_name.h
 *  xoico_forward.h
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

BCORE_DEFINE_SPECT( bcore_inst, xoico )
"{"
    "bcore_spect_header_s header;"
    "feature aware xoico : parse;"
    "feature aware xoico : get_hash;"
    "feature aware xoico : get_global_name_sc;"
    "feature aware xoico : finalize = xoico_finalize__;"
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
    "private aware xoico_group_s* group;"
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
    "private aware xoico_group_s* group;"
    "bcore_source_point_s source_point;"
    "func xoico:parse;"
    "func xoico:get_hash;"
    "func xoico:get_global_name_sc;"
    "func xoico:expand_declaration;"
    "func xoico:expand_forward;"
    "func xoico:expand_init1;"
"}";

/**********************************************************************************************************************/
// source: xoico_arg.h
#include "xoico_arg.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_arg

BCORE_DEFINE_OBJECT_INST_P( xoico_arg_s )
"aware xoico_arg"
"{"
    "st_s st_type;"
    "st_s st_name;"
    "tp_t tp_type;"
    "tp_t tp_name;"
    "private aware xoico_group_s* group;"
    "bcore_source_point_s source_point;"
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
    "private aware xoico_group_s* group;"
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
    "st_s name;"
    "st_s global_name;"
    "bl_t has_ret;"
    "st_s ret_type;"
    "xoico_args_s args;"
    "tp_t arg_o;"
    "private aware xoico_group_s* group;"
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

BCORE_DEFINE_OBJECT_INST_P( xoico_body_s )
"aware xoico_body"
"{"
    "st_s name;"
    "st_s global_name;"
    "st_s code;"
    "bl_t go_inline;"
    "bl_t apply_cengine = true;"
    "private aware xoico_group_s* group;"
    "bcore_source_point_s source_point;"
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
    "st_s name;"
    "st_s global_name;"
    "st_s default_name;"
    "xoico_body_s => default_body;"
    "bl_t strict;"
    "bl_t flag_p;"
    "bl_t flag_t;"
    "bl_t flag_a;"
    "bl_t flag_r;"
    "bl_t has_ret;"
    "st_s ret_type;"
    "xoico_args_s args;"
    "bl_t mutable;"
    "private aware xoico_group_s* group;"
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
    "st_s name;"
    "st_s decl;"
    "tp_t type;"
    "bl_t overloadable = false;"
    "xoico_body_s => body;"
    "private aware xoico_group_s* group;"
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
    "bl_t expandable = true;"
    "bl_t has_features;"
    "bl_t is_aware;"
    "bl_t retrievable;"
    "private xoico_stamp_s -> extending;"
    "xoico_funcs_s funcs;"
    "private aware xoico_source_s* source;"
    "bcore_source_point_s source_point;"
    "func xoico:parse;"
    "func xoico:get_hash;"
    "func xoico:get_global_name_sc;"
    "func xoico:finalize;"
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
    "xoico_funcs_s funcs;"
    "private aware xoico_group_s* group;"
    "bcore_source_point_s source_point;"
    "func xoico:get_hash;"
    "func xoico:get_global_name_sc;"
    "func xoico:finalize;"
    "func xoico:expand_declaration;"
    "func xoico:expand_forward;"
    "func xoico:expand_indef_declaration;"
    "func xoico:expand_definition;"
    "func xoico:expand_init1;"
    "func bcore_inst_call:copy_x;"
"}";

void xoico_stamp_s_copy_x( xoico_stamp_s* o )
{
    BFOR_EACH( i, &o->funcs ) o->funcs.data[ i ]->group = o->group;
}

/**********************************************************************************************************************/
// source: xoico_nested_group.h
#include "xoico_nested_group.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_nested_group

BCORE_DEFINE_OBJECT_INST_P( xoico_nested_group_s )
"aware xoico_nested_group"
"{"
    "private xoico_group_s* group;"
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
    "private aware xoico_target_s* target;"
    "func xoico:finalize;"
"}";

/**********************************************************************************************************************/
// source: xoico_target.h
#include "xoico_target.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_target

BCORE_DEFINE_OBJECT_INST_P( xoico_target_s )
"aware xoico_target"
"{"
    "xoico_target_xflags_s xflags;"
    "st_s name;"
    "st_s path;"
    "xoico_source_s => [];"
    "func xoico:finalize;"
    "st_s signal_handler_name;"
    "bcore_arr_sz_s dependencies;"
    "bl_t flag;"
    "bl_t modified;"
    "bl_t readonly;"
    "st_s => target_h;"
    "st_s => target_c;"
    "bcore_arr_st_s explicit_embeddings;"
    "private aware xoico_compiler_s* compiler;"
"}";

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_target_xflags

BCORE_DEFINE_OBJECT_INST_P( xoico_target_xflags_s )
"aware xoico_target_xflags"
"{"
    "bl_t => apply_cengine;"
"}";

void xoico_target_xflags_s_update( xoico_target_xflags_s* o, const xoico_target_xflags_s* xflags )
{
    if( !xflags ) return;
    if( !o->apply_cengine )
    {
        o->apply_cengine = bcore_inst_t_clone( TYPEOF_bl_t, ( bcore_inst* )xflags->apply_cengine );
    }
}

/**********************************************************************************************************************/
// source: xoico_compiler.h
#include "xoico_compiler.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_compiler

BCORE_DEFINE_OBJECT_INST_P( xoico_compiler_s )
"aware xoico_compiler"
"{"
    "hidden xoico_target_s => [];"
    "hidden bcore_hmap_tpvd_s hmap_group;"
    "hidden bcore_hmap_tpvd_s hmap_item;"
    "hidden bcore_hmap_tp_s hmap_type;"
    "hidden bcore_life_s life;"
    "bl_t register_plain_functions = true;"
    "bl_t register_signatures = false;"
    "bl_t overwrite_unsigned_target_files = false;"
    "bl_t always_expand = false;"
    "bl_t dry_run = false;"
    "sz_t verbosity = 1;"
    "func xoico:finalize;"
"}";

/**********************************************************************************************************************/
// source: xoico_builder.h
#include "xoico_builder.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_builder

BCORE_DEFINE_OBJECT_INST_P( xoico_builder_target_s )
"aware xoico_builder"
"{"
    "st_s => name;"
    "st_s => extension = \"xoila_out\";"
    "st_s => root;"
    "xoico_target_xflags_s target_xflags;"
    "private aware xoico_builder_main_s* main;"
    "bcore_arr_st_s dependencies;"
    "bcore_arr_st_s sources;"
    "st_s => signal_handler;"
    "func bcore_via_call:source;"
"}";

void xoico_builder_target_s_source( xoico_builder_target_s* o, bcore_source* source )
{
    if( !o->root )
    {
        o->root = bcore_file_folder_path( bcore_source_a_get_file( source ) );
        st_s_attach( &o->root, bcore_file_path_minimized( o->root->sc ) );
    }
}

BCORE_DEFINE_OBJECT_INST_P( xoico_builder_main_s )
"aware xoico_builder"
"{"
    "xoico_compiler_s => compiler;"
    "bl_t dry_run = false;"
    "bcore_arr_st_s arr_path;"
    "func bcore_inst_call:init_x;"
"}";

void xoico_builder_main_s_init_x( xoico_builder_main_s* o )
{
    o->compiler = xoico_compiler_s_create();
    xoico_compiler_s_setup( o->compiler );
}

er_t xoico_builder_main_s_set_dry_run( xoico_builder_main_s* o, bl_t v )
{
    o->dry_run = v;
    return 0;
}

bl_t xoico_builder_main_s_get_dry_run( const xoico_builder_main_s* o )
{
    return o->dry_run;
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

BCORE_DEFINE_OBJECT_INST_P( xoico_cengine_s )
"aware xoico_cengine"
"{"
    "sc_t ret_type;"
    "sc_t obj_type;"
    "xoico_args_s -> args;"
    "xoico_compiler_s -> compiler;"
    "xoico_cengine_tn_stack_s stack;"
"}";

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_cengine_tn

BCORE_DEFINE_OBJECT_INST_P( xoico_cengine_tn_unit_s )
"bcore_inst"
"{"
    "tp_t type;"
    "tp_t name;"
    "sz_t level;"
"}";

BCORE_DEFINE_OBJECT_INST_P( xoico_cengine_tn_adl_s )
"aware bcore_array"
"{"
    "xoico_cengine_tn_unit_s => [];"
"}";

BCORE_DEFINE_OBJECT_INST_P( xoico_cengine_tn_stack_s )
"aware xoico_cengine_tn"
"{"
    "xoico_cengine_tn_adl_s adl;"
    "bcore_hmap_name_s name_map;"
"}";

xoico_cengine_tn_stack_s* xoico_cengine_tn_stack_s_push( xoico_cengine_tn_stack_s* o, tp_t type, tp_t name, sz_t level )
{
    xoico_cengine_tn_unit_s* unit = xoico_cengine_tn_unit_s_create();
    unit->type = type;
    unit->name = name;
    unit->level = level;
    xoico_cengine_tn_adl_s_push_d( &o->adl, unit );
    return o;
}

xoico_cengine_tn_stack_s* xoico_cengine_tn_stack_s_push_sc( xoico_cengine_tn_stack_s* o, sc_t type, sc_t name, sz_t level )
{
    xoico_cengine_tn_unit_s* unit = xoico_cengine_tn_unit_s_create();
    unit->type = bcore_hmap_name_s_set_sc( &o->name_map, type );
    unit->name = bcore_hmap_name_s_set_sc( &o->name_map, name );
    unit->level = level;
    xoico_cengine_tn_adl_s_push_d( &o->adl, unit );
    return o;
}

xoico_cengine_tn_stack_s* xoico_cengine_tn_stack_s_pop( xoico_cengine_tn_stack_s* o, sz_t level )
{
    sz_t new_size = o->adl.size;
    for( sz_t i = o->adl.size - 1; i >= 0; i-- )
    {
        if( o->adl.data[ i ]->level < level ) break;
        new_size = i;
    }
    xoico_cengine_tn_adl_s_set_size( &o->adl, new_size );
    return o;
}

tp_t xoico_cengine_tn_stack_s_get_type( xoico_cengine_tn_stack_s* o, tp_t name )
{
    for( sz_t i = o->adl.size - 1; i >= 0; i-- )
    {
        if( o->adl.data[ i ]->name == name ) return o->adl.data[ i ]->type;
    }
    return 0;
}

sc_t xoico_cengine_tn_stack_s_get_type_sc( xoico_cengine_tn_stack_s* o, sc_t name )
{
    return bcore_hmap_name_s_get_sc( &o->name_map, xoico_cengine_tn_stack_s_get_type( o, btypeof( name ) ) );
}

void xoico_cengine_tn_stack_s_clear( xoico_cengine_tn_stack_s* o )
{
    bcore_hmap_name_s_clear( &o->name_map );
    xoico_cengine_tn_adl_s_clear( &o->adl );
}

void xoico_cengine_tn_stack_s_init_from_args( xoico_cengine_tn_stack_s* o, sc_t obj_type, sc_t obj_name, const xoico_args_s* args )
{
    xoico_cengine_tn_stack_s_clear( o );
    if( obj_type ) xoico_cengine_tn_stack_s_push_sc( o, obj_type, obj_name, 0 );
    BFOR_EACH( i, args )
    {
        if( args->data[ i ].tp_type && args->data[ i ].tp_name )
        {
            xoico_cengine_tn_stack_s_push_sc( o, args->data[ i ].st_type.sc, args->data[ i ].st_name.sc, 0 );
        }
    }
}

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
            BCORE_REGISTER_SPECT( xoico );

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
            BCORE_REGISTER_OBJECT( xoico_group_s );
            BCORE_REGISTER_TRAIT( xoico_group, xoico );

            // --------------------------------------------------------------------
            // source: xoico_stamp.h

            // group: xoico_stamp
            BCORE_REGISTER_FFUNC( xoico_get_hash, xoico_stamp_s_get_hash );
            BCORE_REGISTER_FFUNC( xoico_get_global_name_sc, xoico_stamp_s_get_global_name_sc );
            BCORE_REGISTER_FFUNC( xoico_finalize, xoico_stamp_s_finalize );
            BCORE_REGISTER_FFUNC( xoico_expand_declaration, xoico_stamp_s_expand_declaration );
            BCORE_REGISTER_FFUNC( xoico_expand_forward, xoico_stamp_s_expand_forward );
            BCORE_REGISTER_FFUNC( xoico_expand_indef_declaration, xoico_stamp_s_expand_indef_declaration );
            BCORE_REGISTER_FFUNC( xoico_expand_definition, xoico_stamp_s_expand_definition );
            BCORE_REGISTER_FFUNC( xoico_expand_init1, xoico_stamp_s_expand_init1 );
            BCORE_REGISTER_FFUNC( bcore_inst_call_copy_x, xoico_stamp_s_copy_x );
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
            BCORE_REGISTER_OBJECT( xoico_source_s );
            BCORE_REGISTER_TRAIT( xoico_source, xoico );

            // --------------------------------------------------------------------
            // source: xoico_target.h

            // group: xoico_target
            BCORE_REGISTER_FFUNC( xoico_finalize, xoico_target_s_finalize );
            BCORE_REGISTER_OBJECT( xoico_target_s );
            BCORE_REGISTER_TRAIT( xoico_target, xoico );

            // group: xoico_target_xflags
            BCORE_REGISTER_OBJECT( xoico_target_xflags_s );
            BCORE_REGISTER_TRAIT( xoico_target_xflags, xoico_target );

            // --------------------------------------------------------------------
            // source: xoico_compiler.h

            // group: xoico_compiler
            BCORE_REGISTER_FFUNC( xoico_finalize, xoico_compiler_s_finalize );
            BCORE_REGISTER_OBJECT( xoico_compiler_s );
            BCORE_REGISTER_TRAIT( xoico_compiler, xoico );

            // --------------------------------------------------------------------
            // source: xoico_builder.h

            // group: xoico_builder
            BCORE_REGISTER_FFUNC( bcore_via_call_source, xoico_builder_target_s_source );
            BCORE_REGISTER_OBJECT( xoico_builder_target_s );
            BCORE_REGISTER_FFUNC( bcore_inst_call_init_x, xoico_builder_main_s_init_x );
            BCORE_REGISTER_OBJECT( xoico_builder_main_s );
            BCORE_REGISTER_TRAIT( xoico_builder, xoico );

            // --------------------------------------------------------------------
            // source: xoico_cengine.h

            // group: xoico_cengine
            BCORE_REGISTER_OBJECT( xoico_cengine_s );
            BCORE_REGISTER_TRAIT( xoico_cengine, xoico );

            // group: xoico_cengine_tn
            BCORE_REGISTER_OBJECT( xoico_cengine_tn_unit_s );
            BCORE_REGISTER_OBJECT( xoico_cengine_tn_adl_s );
            BCORE_REGISTER_OBJECT( xoico_cengine_tn_stack_s );
            BCORE_REGISTER_TRAIT( xoico_cengine_tn, xoico_cengine );
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
// XOILA_OUT_SIGNATURE 0x61C188802D2D2456ull
