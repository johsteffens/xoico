/** This file was generated from beth-plant source code.
 *  Compiling Agent : xoico_compiler (C) 2020 J.B.Steffens
 *  Last File Update: 2020-08-05T16:32:34Z
 *
 *  Copyright and License of this File:
 *
 *  Generated code inherits the copyright and license of the underlying beth-plant source code.
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
 *
 */

#ifndef XOICO_XOI_OUT_H
#define XOICO_XOI_OUT_H

#include "bcore_control.h"

//To force a rebuild of this target by the plant-compiler, reset the hash key value below to 0.
#define HKEYOF_xoico_xoi_out 1759161549

#define TYPEOF_xoico_xoi_out 2913191625

/**********************************************************************************************************************/
// source: xoico.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico

#define TYPEOF_xoico 1611185117
#define TYPEOF_xoico_s 2129995343
#define TYPEOF_xoico_name_s 3519129831
#define TYPEOF_xoico_forward_s 641783197
#define TYPEOF_xoico_arg_s 2697500904
#define TYPEOF_xoico_args_s 1415489545
#define TYPEOF_xoico_signature_s 818563854
#define TYPEOF_xoico_body_s 832339908
#define TYPEOF_xoico_feature_s 1265401250
#define TYPEOF_xoico_func_s 2664635946
#define TYPEOF_xoico_funcs_s 3506790099
#define TYPEOF_xoico_stamp_s 3712753863
#define TYPEOF_xoico_group_s 2789250547
#define TYPEOF_xoico_nested_group_s 1405676359
#define TYPEOF_xoico_source_s 4260244989
#define TYPEOF_xoico_target_s 3461861713
#define TYPEOF_xoico_compiler_s 2657340073
#define BETH_EXPAND_GROUP_xoico \
  BCORE_FORWARD_OBJECT( xoico ); \
  BCORE_FORWARD_OBJECT( xoico_name_s ); \
  BCORE_FORWARD_OBJECT( xoico_forward_s ); \
  BCORE_FORWARD_OBJECT( xoico_arg_s ); \
  BCORE_FORWARD_OBJECT( xoico_args_s ); \
  BCORE_FORWARD_OBJECT( xoico_signature_s ); \
  BCORE_FORWARD_OBJECT( xoico_body_s ); \
  BCORE_FORWARD_OBJECT( xoico_feature_s ); \
  BCORE_FORWARD_OBJECT( xoico_func_s ); \
  BCORE_FORWARD_OBJECT( xoico_funcs_s ); \
  BCORE_FORWARD_OBJECT( xoico_stamp_s ); \
  BCORE_FORWARD_OBJECT( xoico_group_s ); \
  BCORE_FORWARD_OBJECT( xoico_nested_group_s ); \
  BCORE_FORWARD_OBJECT( xoico_source_s ); \
  BCORE_FORWARD_OBJECT( xoico_target_s ); \
  BCORE_FORWARD_OBJECT( xoico_compiler_s ); \
  typedef er_t (*xoico_parse)( xoico* o, bcore_source* source ); \
  typedef tp_t (*xoico_get_hash)( const xoico* o ); \
  typedef sc_t (*xoico_get_global_name_sc)( const xoico* o ); \
  typedef er_t (*xoico_finalize)( xoico* o ); \
  typedef er_t (*xoico_expand_forward)( const xoico* o, sz_t indent, bcore_sink* sink ); \
  typedef er_t (*xoico_expand_indef_typedef)( const xoico* o, sz_t indent, bcore_sink* sink ); \
  typedef er_t (*xoico_expand_spect_declaration)( const xoico* o, sz_t indent, bcore_sink* sink ); \
  typedef er_t (*xoico_expand_spect_definition)( const xoico* o, sz_t indent, bcore_sink* sink ); \
  typedef er_t (*xoico_expand_declaration)( const xoico* o, sz_t indent, bcore_sink* sink ); \
  typedef er_t (*xoico_expand_indef_declaration)( const xoico* o, sz_t indent, bcore_sink* sink ); \
  typedef er_t (*xoico_expand_definition)( const xoico* o, sz_t indent, bcore_sink* sink ); \
  typedef er_t (*xoico_expand_init1)( const xoico* o, sz_t indent, bcore_sink* sink ); \
  BCORE_DECLARE_SPECT( xoico ) \
  { \
      bcore_spect_header_s header; \
      xoico_parse parse; \
      xoico_get_hash get_hash; \
      xoico_get_global_name_sc get_global_name_sc; \
      xoico_finalize finalize; \
      xoico_expand_forward expand_forward; \
      xoico_expand_indef_typedef expand_indef_typedef; \
      xoico_expand_spect_declaration expand_spect_declaration; \
      xoico_expand_spect_definition expand_spect_definition; \
      xoico_expand_declaration expand_declaration; \
      xoico_expand_indef_declaration expand_indef_declaration; \
      xoico_expand_definition expand_definition; \
      xoico_expand_init1 expand_init1; \
  }; \
  static inline xoico* xoico_t_create( tp_t t ) { bcore_trait_assert_satisfied_type( TYPEOF_xoico, t ); return ( xoico* )bcore_inst_t_create( t ); } \
  static inline bl_t xoico_t_is_trait_of( tp_t t ) { return bcore_trait_is_of( t, TYPEOF_xoico ); } \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( xoico ) \
  static inline bl_t xoico_a_is_trait_of( vc_t o ) { return bcore_trait_is_of( o ? *(aware_t*)o : 0, TYPEOF_xoico ); } \
  static inline er_t xoico_p_parse( const xoico_s* __p, xoico* o, bcore_source* source ) { assert( __p->parse ); return __p->parse( o, source ); } \
  static inline er_t xoico_a_parse( xoico* o, bcore_source* source ) { const xoico_s* p = xoico_s_get_aware( o ); assert( p->parse ); return p->parse( o, source ); } \
  static inline bl_t xoico_p_defines_parse( const xoico_s* __p ) { return __p->parse != NULL; } \
  static inline bl_t xoico_a_defines_parse( const xoico* o ) { return xoico_s_get_aware( o )->parse != NULL; } \
  static inline tp_t xoico_p_get_hash( const xoico_s* __p, const xoico* o ) { assert( __p->get_hash ); return __p->get_hash( o ); } \
  static inline tp_t xoico_a_get_hash( const xoico* o ) { const xoico_s* p = xoico_s_get_aware( o ); assert( p->get_hash ); return p->get_hash( o ); } \
  static inline bl_t xoico_p_defines_get_hash( const xoico_s* __p ) { return __p->get_hash != NULL; } \
  static inline bl_t xoico_a_defines_get_hash( const xoico* o ) { return xoico_s_get_aware( o )->get_hash != NULL; } \
  static inline sc_t xoico_p_get_global_name_sc( const xoico_s* __p, const xoico* o ) { assert( __p->get_global_name_sc ); return __p->get_global_name_sc( o ); } \
  static inline sc_t xoico_a_get_global_name_sc( const xoico* o ) { const xoico_s* p = xoico_s_get_aware( o ); assert( p->get_global_name_sc ); return p->get_global_name_sc( o ); } \
  static inline bl_t xoico_p_defines_get_global_name_sc( const xoico_s* __p ) { return __p->get_global_name_sc != NULL; } \
  static inline bl_t xoico_a_defines_get_global_name_sc( const xoico* o ) { return xoico_s_get_aware( o )->get_global_name_sc != NULL; } \
  static inline er_t xoico_p_finalize( const xoico_s* __p, xoico* o ) { assert( __p->finalize ); return __p->finalize( o ); } \
  static inline er_t xoico_a_finalize( xoico* o ) { const xoico_s* p = xoico_s_get_aware( o ); assert( p->finalize ); return p->finalize( o ); } \
  static inline bl_t xoico_p_defines_finalize( const xoico_s* __p ) { return true; } \
  static inline bl_t xoico_a_defines_finalize( const xoico* o ) { return true; } \
  static inline er_t xoico_finalize__( xoico* o ){return 0;} \
  static inline er_t xoico_p_expand_forward( const xoico_s* __p, const xoico* o, sz_t indent, bcore_sink* sink ) { assert( __p->expand_forward ); return __p->expand_forward( o, indent, sink ); } \
  static inline er_t xoico_a_expand_forward( const xoico* o, sz_t indent, bcore_sink* sink ) { const xoico_s* p = xoico_s_get_aware( o ); assert( p->expand_forward ); return p->expand_forward( o, indent, sink ); } \
  static inline bl_t xoico_p_defines_expand_forward( const xoico_s* __p ) { return true; } \
  static inline bl_t xoico_a_defines_expand_forward( const xoico* o ) { return true; } \
  static inline er_t xoico_expand_forward__( const xoico* o, sz_t indent, bcore_sink* sink ){return 0;} \
  static inline er_t xoico_p_expand_indef_typedef( const xoico_s* __p, const xoico* o, sz_t indent, bcore_sink* sink ) { assert( __p->expand_indef_typedef ); return __p->expand_indef_typedef( o, indent, sink ); } \
  static inline er_t xoico_a_expand_indef_typedef( const xoico* o, sz_t indent, bcore_sink* sink ) { const xoico_s* p = xoico_s_get_aware( o ); assert( p->expand_indef_typedef ); return p->expand_indef_typedef( o, indent, sink ); } \
  static inline bl_t xoico_p_defines_expand_indef_typedef( const xoico_s* __p ) { return true; } \
  static inline bl_t xoico_a_defines_expand_indef_typedef( const xoico* o ) { return true; } \
  static inline er_t xoico_expand_indef_typedef__( const xoico* o, sz_t indent, bcore_sink* sink ){return 0;} \
  static inline er_t xoico_p_expand_spect_declaration( const xoico_s* __p, const xoico* o, sz_t indent, bcore_sink* sink ) { assert( __p->expand_spect_declaration ); return __p->expand_spect_declaration( o, indent, sink ); } \
  static inline er_t xoico_a_expand_spect_declaration( const xoico* o, sz_t indent, bcore_sink* sink ) { const xoico_s* p = xoico_s_get_aware( o ); assert( p->expand_spect_declaration ); return p->expand_spect_declaration( o, indent, sink ); } \
  static inline bl_t xoico_p_defines_expand_spect_declaration( const xoico_s* __p ) { return true; } \
  static inline bl_t xoico_a_defines_expand_spect_declaration( const xoico* o ) { return true; } \
  static inline er_t xoico_expand_spect_declaration__( const xoico* o, sz_t indent, bcore_sink* sink ){return 0;} \
  static inline er_t xoico_p_expand_spect_definition( const xoico_s* __p, const xoico* o, sz_t indent, bcore_sink* sink ) { assert( __p->expand_spect_definition ); return __p->expand_spect_definition( o, indent, sink ); } \
  static inline er_t xoico_a_expand_spect_definition( const xoico* o, sz_t indent, bcore_sink* sink ) { const xoico_s* p = xoico_s_get_aware( o ); assert( p->expand_spect_definition ); return p->expand_spect_definition( o, indent, sink ); } \
  static inline bl_t xoico_p_defines_expand_spect_definition( const xoico_s* __p ) { return true; } \
  static inline bl_t xoico_a_defines_expand_spect_definition( const xoico* o ) { return true; } \
  static inline er_t xoico_expand_spect_definition__( const xoico* o, sz_t indent, bcore_sink* sink ){return 0;} \
  static inline er_t xoico_p_expand_declaration( const xoico_s* __p, const xoico* o, sz_t indent, bcore_sink* sink ) { assert( __p->expand_declaration ); return __p->expand_declaration( o, indent, sink ); } \
  static inline er_t xoico_a_expand_declaration( const xoico* o, sz_t indent, bcore_sink* sink ) { const xoico_s* p = xoico_s_get_aware( o ); assert( p->expand_declaration ); return p->expand_declaration( o, indent, sink ); } \
  static inline bl_t xoico_p_defines_expand_declaration( const xoico_s* __p ) { return true; } \
  static inline bl_t xoico_a_defines_expand_declaration( const xoico* o ) { return true; } \
  static inline er_t xoico_expand_declaration__( const xoico* o, sz_t indent, bcore_sink* sink ){return 0;} \
  static inline er_t xoico_p_expand_indef_declaration( const xoico_s* __p, const xoico* o, sz_t indent, bcore_sink* sink ) { assert( __p->expand_indef_declaration ); return __p->expand_indef_declaration( o, indent, sink ); } \
  static inline er_t xoico_a_expand_indef_declaration( const xoico* o, sz_t indent, bcore_sink* sink ) { const xoico_s* p = xoico_s_get_aware( o ); assert( p->expand_indef_declaration ); return p->expand_indef_declaration( o, indent, sink ); } \
  static inline bl_t xoico_p_defines_expand_indef_declaration( const xoico_s* __p ) { return true; } \
  static inline bl_t xoico_a_defines_expand_indef_declaration( const xoico* o ) { return true; } \
  static inline er_t xoico_expand_indef_declaration__( const xoico* o, sz_t indent, bcore_sink* sink ){return 0;} \
  static inline er_t xoico_p_expand_definition( const xoico_s* __p, const xoico* o, sz_t indent, bcore_sink* sink ) { assert( __p->expand_definition ); return __p->expand_definition( o, indent, sink ); } \
  static inline er_t xoico_a_expand_definition( const xoico* o, sz_t indent, bcore_sink* sink ) { const xoico_s* p = xoico_s_get_aware( o ); assert( p->expand_definition ); return p->expand_definition( o, indent, sink ); } \
  static inline bl_t xoico_p_defines_expand_definition( const xoico_s* __p ) { return true; } \
  static inline bl_t xoico_a_defines_expand_definition( const xoico* o ) { return true; } \
  static inline er_t xoico_expand_definition__( const xoico* o, sz_t indent, bcore_sink* sink ){return 0;} \
  static inline er_t xoico_p_expand_init1( const xoico_s* __p, const xoico* o, sz_t indent, bcore_sink* sink ) { assert( __p->expand_init1 ); return __p->expand_init1( o, indent, sink ); } \
  static inline er_t xoico_a_expand_init1( const xoico* o, sz_t indent, bcore_sink* sink ) { const xoico_s* p = xoico_s_get_aware( o ); assert( p->expand_init1 ); return p->expand_init1( o, indent, sink ); } \
  static inline bl_t xoico_p_defines_expand_init1( const xoico_s* __p ) { return true; } \
  static inline bl_t xoico_a_defines_expand_init1( const xoico* o ) { return true; } \
  static inline er_t xoico_expand_init1__( const xoico* o, sz_t indent, bcore_sink* sink ){return 0;}

/**********************************************************************************************************************/
// source: xoico_name.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_name

#define TYPEOF_xoico_name 531162629
#define TYPEOF_xoico_name_s 3519129831
#define TYPEOF_xoico_name_s 3519129831
#define BETH_EXPAND_ITEM_xoico_name_s \
  BCORE_DECLARE_OBJECT( xoico_name_s ) \
    {aware_t _;st_s name;xoico_group_s* group;bcore_source_point_s source_point;}; \
  er_t xoico_name_s_parse( xoico_name_s* o, bcore_source* source ); \
  tp_t xoico_name_s_get_hash( const xoico_name_s* o ); \
  sc_t xoico_name_s_get_global_name_sc( const xoico_name_s* o ); \
  er_t xoico_name_s_expand_declaration( const xoico_name_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_name_s_expand_init1( const xoico_name_s* o, sz_t indent, bcore_sink* sink );
#define BETH_EXPAND_GROUP_xoico_name \
  BCORE_FORWARD_OBJECT( xoico_name ); \
  BCORE_FORWARD_OBJECT( xoico_name_s ); \
  BETH_EXPAND_ITEM_xoico_name_s

/**********************************************************************************************************************/
// source: xoico_forward.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_forward

#define TYPEOF_xoico_forward 1609058635
#define TYPEOF_xoico_forward_s 641783197
#define TYPEOF_xoico_forward_s 641783197
#define BETH_EXPAND_ITEM_xoico_forward_s \
  BCORE_DECLARE_OBJECT( xoico_forward_s ) \
    {aware_t _;st_s name;xoico_group_s* group;bcore_source_point_s source_point;}; \
  er_t xoico_forward_s_parse( xoico_forward_s* o, bcore_source* source ); \
  tp_t xoico_forward_s_get_hash( const xoico_forward_s* o ); \
  sc_t xoico_forward_s_get_global_name_sc( const xoico_forward_s* o ); \
  er_t xoico_forward_s_expand_declaration( const xoico_forward_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_forward_s_expand_forward( const xoico_forward_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_forward_s_expand_init1( const xoico_forward_s* o, sz_t indent, bcore_sink* sink );
#define BETH_EXPAND_GROUP_xoico_forward \
  BCORE_FORWARD_OBJECT( xoico_forward ); \
  BCORE_FORWARD_OBJECT( xoico_forward_s ); \
  BETH_EXPAND_ITEM_xoico_forward_s

/**********************************************************************************************************************/
// source: xoico_arg.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_arg

#define TYPEOF_xoico_arg 3316412150
#define TYPEOF_xoico_arg_s 2697500904
#define TYPEOF_xoico_arg_s 2697500904
#define BETH_EXPAND_ITEM_xoico_arg_s \
  BCORE_DECLARE_OBJECT( xoico_arg_s ) \
    {aware_t _;st_s type;st_s name;xoico_group_s* group;bcore_source_point_s source_point;}; \
  er_t xoico_arg_s_parse( xoico_arg_s* o, bcore_source* source ); \
  tp_t xoico_arg_s_get_hash( const xoico_arg_s* o ); \
  er_t xoico_arg_s_expand( const xoico_arg_s* o, bcore_sink* sink ); \
  er_t xoico_arg_s_expand_name( const xoico_arg_s* o, bcore_sink* sink );
#define BETH_EXPAND_GROUP_xoico_arg \
  BCORE_FORWARD_OBJECT( xoico_arg ); \
  BCORE_FORWARD_OBJECT( xoico_arg_s ); \
  BETH_EXPAND_ITEM_xoico_arg_s

/**********************************************************************************************************************/
// source: xoico_args.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_args

#define TYPEOF_xoico_args 3010591583
#define TYPEOF_xoico_args_s 1415489545
#define TYPEOF_xoico_args_s 1415489545
#define BETH_EXPAND_ITEM_xoico_args_s \
  BCORE_DECLARE_OBJECT( xoico_args_s ) \
    {aware_t _;BCORE_ARRAY_DYN_SOLID_STATIC_S( xoico_arg_s, );xoico_group_s* group;}; \
  er_t xoico_args_s_parse( xoico_args_s* o, bcore_source* source ); \
  tp_t xoico_args_s_get_hash( const xoico_args_s* o ); \
  er_t xoico_args_s_append( xoico_args_s* o, bcore_source* source ); \
  er_t xoico_args_s_expand( const xoico_args_s* o, bl_t first, bcore_sink* sink ); \
  er_t xoico_args_s_expand_name( const xoico_args_s* o, bl_t first, bcore_sink* sink );
#define BETH_EXPAND_GROUP_xoico_args \
  BCORE_FORWARD_OBJECT( xoico_args ); \
  BCORE_FORWARD_OBJECT( xoico_args_s ); \
  BETH_EXPAND_ITEM_xoico_args_s

/**********************************************************************************************************************/
// source: xoico_signature.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_signature

#define TYPEOF_xoico_signature 2157722668
#define TYPEOF_xoico_signature_s 818563854
#define TYPEOF_xoico_signature_s 818563854
#define BETH_EXPAND_ITEM_xoico_signature_s \
  BCORE_DECLARE_OBJECT( xoico_signature_s ) \
    {aware_t _;st_s name;st_s global_name;bl_t has_ret;st_s ret_type;xoico_args_s args;tp_t arg_o;xoico_group_s* group;bcore_source_point_s source_point;}; \
  er_t xoico_signature_s_parse( xoico_signature_s* o, bcore_source* source ); \
  tp_t xoico_signature_s_get_hash( const xoico_signature_s* o ); \
  sc_t xoico_signature_s_get_global_name_sc( const xoico_signature_s* o );
#define BETH_EXPAND_GROUP_xoico_signature \
  BCORE_FORWARD_OBJECT( xoico_signature ); \
  BCORE_FORWARD_OBJECT( xoico_signature_s ); \
  BETH_EXPAND_ITEM_xoico_signature_s

/**********************************************************************************************************************/
// source: xoico_body.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_body

#define TYPEOF_xoico_body 2227670106
#define TYPEOF_xoico_body_s 832339908
#define TYPEOF_xoico_body_s 832339908
#define BETH_EXPAND_ITEM_xoico_body_s \
  BCORE_DECLARE_OBJECT( xoico_body_s ) \
    {aware_t _;st_s name;st_s global_name;st_s code;bl_t go_inline;xoico_group_s* group;bcore_source_point_s source_point;}; \
  tp_t xoico_body_s_get_hash( const xoico_body_s* o ); \
  sc_t xoico_body_s_get_global_name_sc( const xoico_body_s* o ); \
  er_t xoico_body_s_parse_code( xoico_body_s* o, xoico_stamp_s* stamp, bcore_source* source ); \
  er_t xoico_body_s_parse( xoico_body_s* o, xoico_stamp_s* stamp, bcore_source* source ); \
  er_t xoico_body_s_expand( const xoico_body_s* o, sz_t indent, bcore_sink* sink );
#define BETH_EXPAND_GROUP_xoico_body \
  BCORE_FORWARD_OBJECT( xoico_body ); \
  BCORE_FORWARD_OBJECT( xoico_body_s ); \
  BETH_EXPAND_ITEM_xoico_body_s

/**********************************************************************************************************************/
// source: xoico_feature.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_feature

#define TYPEOF_xoico_feature 1507275896
#define TYPEOF_xoico_feature_s 1265401250
#define TYPEOF_xoico_feature_s 1265401250
#define BETH_EXPAND_ITEM_xoico_feature_s \
  BCORE_DECLARE_OBJECT( xoico_feature_s ) \
    {aware_t _;st_s name;st_s global_name;st_s default_name;xoico_body_s* default_body;bl_t strict;bl_t flag_p;bl_t flag_t;bl_t flag_a;bl_t flag_r;bl_t has_ret;st_s ret_type;xoico_args_s args;bl_t mutable;xoico_group_s* group;bcore_source_point_s source_point;}; \
  er_t xoico_feature_s_parse( xoico_feature_s* o, bcore_source* source ); \
  tp_t xoico_feature_s_get_hash( const xoico_feature_s* o ); \
  sc_t xoico_feature_s_get_global_name_sc( const xoico_feature_s* o ); \
  er_t xoico_feature_s_expand_indef_typedef( const xoico_feature_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_feature_s_expand_spect_declaration( const xoico_feature_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_feature_s_expand_spect_definition( const xoico_feature_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_feature_s_expand_indef_declaration( const xoico_feature_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_feature_s_expand_definition( const xoico_feature_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_feature_s_expand_init1( const xoico_feature_s* o, sz_t indent, bcore_sink* sink );
#define BETH_EXPAND_GROUP_xoico_feature \
  BCORE_FORWARD_OBJECT( xoico_feature ); \
  BCORE_FORWARD_OBJECT( xoico_feature_s ); \
  BETH_EXPAND_ITEM_xoico_feature_s

/**********************************************************************************************************************/
// source: xoico_func.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_func

#define TYPEOF_xoico_func 3908734672
#define TYPEOF_xoico_func_s 2664635946
#define TYPEOF_xoico_func_s 2664635946
#define BETH_EXPAND_ITEM_xoico_func_s \
  BCORE_DECLARE_OBJECT( xoico_func_s ) \
    {aware_t _;st_s name;st_s decl;tp_t type;bl_t overloadable;xoico_body_s* body;xoico_group_s* group;bcore_source_point_s source_point;}; \
  tp_t xoico_func_s_get_hash( const xoico_func_s* o ); \
  er_t xoico_func_s_parse( xoico_func_s* o, xoico_stamp_s* stamp, bcore_source* source ); \
  bl_t xoico_func_s_registerable( const xoico_func_s* o );
#define BETH_EXPAND_GROUP_xoico_func \
  BCORE_FORWARD_OBJECT( xoico_func ); \
  BCORE_FORWARD_OBJECT( xoico_func_s ); \
  BETH_EXPAND_ITEM_xoico_func_s

/**********************************************************************************************************************/
// source: xoico_funcs.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_funcs

#define TYPEOF_xoico_funcs 1701743257
#define TYPEOF_xoico_funcs_s 3506790099
#define TYPEOF_xoico_funcs_s 3506790099
#define BETH_EXPAND_ITEM_xoico_funcs_s \
  BCORE_DECLARE_OBJECT( xoico_funcs_s ) \
    {aware_t _;BCORE_ARRAY_DYN_LINK_STATIC_S( xoico_func_s, );}; \
  bl_t xoico_funcs_s_exists( const xoico_funcs_s* o, tp_t type ); \
  sz_t xoico_funcs_s_get_index( const xoico_funcs_s* o, tp_t type ); \
  er_t xoico_funcs_s_replace_fork( xoico_funcs_s* o, sz_t idx, xoico_func_s* func );
#define BETH_EXPAND_GROUP_xoico_funcs \
  BCORE_FORWARD_OBJECT( xoico_funcs ); \
  BCORE_FORWARD_OBJECT( xoico_funcs_s ); \
  BETH_EXPAND_ITEM_xoico_funcs_s

/**********************************************************************************************************************/
// source: xoico_group.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_group

#define TYPEOF_xoico_group 4176153593
#define TYPEOF_xoico_group_s 2789250547
#define TYPEOF_xoico_group_s 2789250547
#define BETH_EXPAND_ITEM_xoico_group_s \
  BCORE_DECLARE_OBJECT( xoico_group_s ) \
    {aware_t _;BCORE_ARRAY_DYN_LINK_STATIC_S( xoico, );st_s name;xoico_group_s* group;st_s trait_name;tp_t hash;bl_t expandable;bl_t has_features;bl_t is_aware;bl_t retrievable;xoico_stamp_s* extending;xoico_funcs_s funcs;xoico_source_s* source;bcore_source_point_s source_point;}; \
  er_t xoico_group_s_parse( xoico_group_s* o, bcore_source* source ); \
  tp_t xoico_group_s_get_hash( const xoico_group_s* o ); \
  sc_t xoico_group_s_get_global_name_sc( const xoico_group_s* o ); \
  er_t xoico_group_s_finalize( xoico_group_s* o ); \
  er_t xoico_group_s_parse_name( xoico_group_s* o, st_s* name, bcore_source* source ); \
  er_t xoico_group_s_parse_name_recursive( xoico_group_s* o, st_s* name, bcore_source* source ); \
  er_t xoico_group_s_expand_declaration( const xoico_group_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_group_s_expand_definition( const xoico_group_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_group_s_expand_init1( const xoico_group_s* o, sz_t indent, bcore_sink* sink ); \
  xoico_compiler_s* xoico_group_s_get_compiler( const xoico_group_s* o );
#define BETH_EXPAND_GROUP_xoico_group \
  BCORE_FORWARD_OBJECT( xoico_group ); \
  BCORE_FORWARD_OBJECT( xoico_group_s ); \
  BETH_EXPAND_ITEM_xoico_group_s

/**********************************************************************************************************************/
// source: xoico_stamp.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_stamp

#define TYPEOF_xoico_stamp 1853406245
#define TYPEOF_xoico_stamp_s 3712753863
#define TYPEOF_xoico_stamp_s 3712753863
#define BETH_EXPAND_ITEM_xoico_stamp_s \
  BCORE_DECLARE_OBJECT( xoico_stamp_s ) \
    {aware_t _;st_s name;st_s trait_name;st_s* self_source;xoico_funcs_s funcs;xoico_group_s* group;bcore_source_point_s source_point;}; \
  tp_t xoico_stamp_s_get_hash( const xoico_stamp_s* o ); \
  sc_t xoico_stamp_s_get_global_name_sc( const xoico_stamp_s* o ); \
  er_t xoico_stamp_s_finalize( xoico_stamp_s* o ); \
  er_t xoico_stamp_s_expand_declaration( const xoico_stamp_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_stamp_s_expand_forward( const xoico_stamp_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_stamp_s_expand_indef_declaration( const xoico_stamp_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_stamp_s_expand_definition( const xoico_stamp_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_stamp_s_expand_init1( const xoico_stamp_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_stamp_s_parse( xoico_stamp_s* o, xoico_group_s* group, bcore_source* source ); \
  er_t xoico_stamp_s_resolve_chars( const xoico_stamp_s* o, st_s* string ); \
  er_t xoico_stamp_s_make_funcs_overloadable( xoico_stamp_s* o ); \
  void xoico_stamp_s_copy_x( xoico_stamp_s* o );
#define BETH_EXPAND_GROUP_xoico_stamp \
  BCORE_FORWARD_OBJECT( xoico_stamp ); \
  BCORE_FORWARD_OBJECT( xoico_stamp_s ); \
  BETH_EXPAND_ITEM_xoico_stamp_s

/**********************************************************************************************************************/
// source: xoico_nested_group.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_nested_group

#define TYPEOF_xoico_nested_group 577561253
#define TYPEOF_xoico_nested_group_s 1405676359
#define TYPEOF_xoico_nested_group_s 1405676359
#define BETH_EXPAND_ITEM_xoico_nested_group_s \
  BCORE_DECLARE_OBJECT( xoico_nested_group_s ) \
    {aware_t _;xoico_group_s* group;}; \
  tp_t xoico_nested_group_s_get_hash( const xoico_nested_group_s* o ); \
  er_t xoico_nested_group_s_expand_forward( const xoico_nested_group_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_nested_group_s_expand_indef_declaration( const xoico_nested_group_s* o, sz_t indent, bcore_sink* sink );
#define BETH_EXPAND_GROUP_xoico_nested_group \
  BCORE_FORWARD_OBJECT( xoico_nested_group ); \
  BCORE_FORWARD_OBJECT( xoico_nested_group_s ); \
  BETH_EXPAND_ITEM_xoico_nested_group_s

/**********************************************************************************************************************/
// source: xoico_source.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_source

#define TYPEOF_xoico_source 3322080235
#define TYPEOF_xoico_source_s 4260244989
#define TYPEOF_xoico_source_s 4260244989
#define BETH_EXPAND_ITEM_xoico_source_s \
  BCORE_DECLARE_OBJECT( xoico_source_s ) \
    {aware_t _;st_s name;st_s path;tp_t hash;BCORE_ARRAY_DYN_LINK_STATIC_S( xoico_group_s, );xoico_target_s* target;}; \
  er_t xoico_source_s_finalize( xoico_source_s* o ); \
  er_t xoico_source_s_push_group( xoico_source_s* o, xoico_group_s* group ); \
  er_t xoico_source_s_parse( xoico_source_s* o, bcore_source* source ); \
  er_t xoico_source_s_finalize( xoico_source_s* o ); \
  er_t xoico_source_s_expand_declaration( const xoico_source_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_source_s_expand_definition( const xoico_source_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_source_s_expand_init1( const xoico_source_s* o, sz_t indent, bcore_sink* sink );
#define BETH_EXPAND_GROUP_xoico_source \
  BCORE_FORWARD_OBJECT( xoico_source ); \
  BCORE_FORWARD_OBJECT( xoico_source_s ); \
  BETH_EXPAND_ITEM_xoico_source_s

/**********************************************************************************************************************/
// source: xoico_target.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_target

#define TYPEOF_xoico_target 1096935671
#define TYPEOF_xoico_target_s 3461861713
#define TYPEOF_xoico_target_s 3461861713
#define BETH_EXPAND_ITEM_xoico_target_s \
  BCORE_DECLARE_OBJECT( xoico_target_s ) \
    {aware_t _;st_s name;st_s path;BCORE_ARRAY_DYN_LINK_STATIC_S( xoico_source_s, );st_s signal_handler_name;bcore_arr_sz_s dependencies;bl_t flag;bl_t modified;st_s* planted_h;st_s* planted_c;xoico_compiler_s* compiler;}; \
  er_t xoico_target_s_finalize( xoico_target_s* o ); \
  er_t xoico_target_s_parse( xoico_target_s* o, sc_t source_path ); \
  bl_t xoico_target_s_to_be_modified( const xoico_target_s* o ); \
  er_t xoico_target_s_expand_phase1( xoico_target_s* o, bl_t* p_modified ); \
  er_t xoico_target_s_expand_phase2( xoico_target_s* o, bl_t* p_modified ); \
  bl_t xoico_target_s_is_cyclic( xoico_target_s* o );
#define BETH_EXPAND_GROUP_xoico_target \
  BCORE_FORWARD_OBJECT( xoico_target ); \
  BCORE_FORWARD_OBJECT( xoico_target_s ); \
  BETH_EXPAND_ITEM_xoico_target_s

/**********************************************************************************************************************/
// source: xoico_compiler.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_compiler

#define TYPEOF_xoico_compiler 2627246911
#define TYPEOF_xoico_compiler_s 2657340073
#define TYPEOF_xoico_compiler_s 2657340073
#define BETH_EXPAND_ITEM_xoico_compiler_s \
  BCORE_DECLARE_OBJECT( xoico_compiler_s ) \
    {aware_t _;BCORE_ARRAY_DYN_LINK_STATIC_S( xoico_target_s, );bcore_hmap_tpvd_s hmap_group;bcore_hmap_tpvd_s hmap_item;bcore_life_s life;bl_t register_plain_functions;bl_t register_signatures;bl_t overwrite_unsigned_planted_files;bl_t always_expand;bl_t dry_run;sz_t verbosity;}; \
  er_t xoico_compiler_s_finalize( xoico_compiler_s* o ); \
  const xoico* xoico_compiler_s_item_get( const xoico_compiler_s* o, tp_t item_id ); \
  bl_t xoico_compiler_s_item_exists( const xoico_compiler_s* o, tp_t item_id ); \
  er_t xoico_compiler_s_item_register( xoico_compiler_s* o, const xoico* item, bcore_source* source ); \
  er_t xoico_compiler_s_group_register( xoico_compiler_s* o, const xoico_group_s* group, bcore_source* source ); \
  er_t xoico_compiler_s_life_a_push( xoico_compiler_s* o, vd_t object ); \
  er_t xoico_compiler_s_check_overwrite( const xoico_compiler_s* o, sc_t file ); \
  er_t xoico_compiler_s_setup( xoico_compiler_s* o ); \
  er_t xoico_compiler_s_compile( xoico_compiler_s* o, sc_t target_name, sc_t source_path, sz_t* p_target_index ); \
  er_t xoico_compiler_s_set_target_signal_handler_name( xoico_compiler_s* o, sz_t target_index, sc_t name ); \
  er_t xoico_compiler_s_set_target_dependencies( xoico_compiler_s* o, sz_t target_index, const bcore_arr_sz_s* dependencies ); \
  er_t xoico_compiler_s_update_planted_files( xoico_compiler_s* o, bl_t* p_modified ); \
  bl_t xoico_compiler_s_update_required( xoico_compiler_s* o ); \
  sz_t xoico_compiler_s_get_verbosity( const xoico_compiler_s* o );
#define BETH_EXPAND_GROUP_xoico_compiler \
  BCORE_FORWARD_OBJECT( xoico_compiler ); \
  BCORE_FORWARD_OBJECT( xoico_compiler_s ); \
  BETH_EXPAND_ITEM_xoico_compiler_s

/**********************************************************************************************************************/
// source: xoico_builder.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_builder

#define TYPEOF_xoico_builder 3767869353
#define TYPEOF_xoico_builder_s 3780197667
#define TYPEOF_xoico_builder_target_s 3715126149
#define BETH_EXPAND_ITEM_xoico_builder_target_s \
  BCORE_DECLARE_OBJECT( xoico_builder_target_s ) \
    {aware_t _;st_s* name;st_s* extension;st_s* root;xoico_builder_main_s* main;bcore_arr_st_s dependencies;bcore_arr_st_s sources;st_s* signal_handler;}; \
  void xoico_builder_target_s_source( xoico_builder_target_s* o, bcore_source* source ); \
  er_t xoico_builder_target_s_build( const xoico_builder_target_s* o, sz_t* target_index );
#define TYPEOF_xoico_builder_main_s 1265567453
#define BETH_EXPAND_ITEM_xoico_builder_main_s \
  BCORE_DECLARE_OBJECT( xoico_builder_main_s ) \
    {aware_t _;xoico_compiler_s* compiler;bl_t dry_run;bcore_arr_st_s arr_path;}; \
  void xoico_builder_main_s_init_x( xoico_builder_main_s* o ); \
  er_t xoico_builder_main_s_build_from_file( xoico_builder_main_s* o, sc_t path ); \
  bl_t xoico_builder_main_s_update_required( const xoico_builder_main_s* o ); \
  er_t xoico_builder_main_s_update( const xoico_builder_main_s* o ); \
  er_t xoico_builder_main_s_set_dry_run( xoico_builder_main_s* o, bl_t v ); \
  bl_t xoico_builder_main_s_get_dry_run( const xoico_builder_main_s* o ); \
  er_t xoico_builder_main_s_set_always_expand( xoico_builder_main_s* o, bl_t v ); \
  bl_t xoico_builder_main_s_get_always_expand( const xoico_builder_main_s* o ); \
  er_t xoico_builder_main_s_set_overwrite_unsigned_planted_files( xoico_builder_main_s* o, bl_t v ); \
  bl_t xoico_builder_main_s_get_overwrite_unsigned_planted_files( const xoico_builder_main_s* o );
#define BETH_EXPAND_GROUP_xoico_builder \
  BCORE_FORWARD_OBJECT( xoico_builder ); \
  BCORE_FORWARD_OBJECT( xoico_builder_target_s ); \
  BCORE_FORWARD_OBJECT( xoico_builder_main_s ); \
  BETH_EXPAND_ITEM_xoico_builder_target_s \
  BETH_EXPAND_ITEM_xoico_builder_main_s

/**********************************************************************************************************************/

vd_t xoico_xoi_out_signal_handler( const bcore_signal_s* o );

#endif // XOICO_XOI_OUT_H
// BETH_PLANT_SIGNATURE 1082940567
