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

#ifndef XOITE_XOI_OUT_H
#define XOITE_XOI_OUT_H

#include "bcore_control.h"

//To force a rebuild of this target by the plant-compiler, reset the hash key value below to 0.
#define HKEYOF_xoite_xoi_out 2977250247

#define TYPEOF_xoite_xoi_out 3537855440

/**********************************************************************************************************************/
// source: xoite.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoite

#define TYPEOF_xoite 1983985424
#define TYPEOF_xoite_s 2394491754
#define TYPEOF_xoite_name_s 576784544
#define TYPEOF_xoite_forward_s 3158286860
#define TYPEOF_xoite_arg_s 3829723705
#define TYPEOF_xoite_args_s 1271258406
#define TYPEOF_xoite_signature_s 2452024311
#define TYPEOF_xoite_body_s 1114846719
#define TYPEOF_xoite_feature_s 2566336903
#define TYPEOF_xoite_func_s 2980463321
#define TYPEOF_xoite_funcs_s 3228587462
#define TYPEOF_xoite_stamp_s 139668862
#define TYPEOF_xoite_group_s 734934966
#define TYPEOF_xoite_nested_group_s 1872428512
#define TYPEOF_xoite_source_s 324505114
#define TYPEOF_xoite_target_s 4106300314
#define TYPEOF_xoite_compiler_s 392017598
#define BETH_EXPAND_GROUP_xoite \
  BCORE_FORWARD_OBJECT( xoite ); \
  BCORE_FORWARD_OBJECT( xoite_name_s ); \
  BCORE_FORWARD_OBJECT( xoite_forward_s ); \
  BCORE_FORWARD_OBJECT( xoite_arg_s ); \
  BCORE_FORWARD_OBJECT( xoite_args_s ); \
  BCORE_FORWARD_OBJECT( xoite_signature_s ); \
  BCORE_FORWARD_OBJECT( xoite_body_s ); \
  BCORE_FORWARD_OBJECT( xoite_feature_s ); \
  BCORE_FORWARD_OBJECT( xoite_func_s ); \
  BCORE_FORWARD_OBJECT( xoite_funcs_s ); \
  BCORE_FORWARD_OBJECT( xoite_stamp_s ); \
  BCORE_FORWARD_OBJECT( xoite_group_s ); \
  BCORE_FORWARD_OBJECT( xoite_nested_group_s ); \
  BCORE_FORWARD_OBJECT( xoite_source_s ); \
  BCORE_FORWARD_OBJECT( xoite_target_s ); \
  BCORE_FORWARD_OBJECT( xoite_compiler_s ); \
  typedef er_t (*xoite_parse)( xoite* o, bcore_source* source ); \
  typedef tp_t (*xoite_get_hash)( const xoite* o ); \
  typedef sc_t (*xoite_get_global_name_sc)( const xoite* o ); \
  typedef er_t (*xoite_finalize)( xoite* o ); \
  typedef er_t (*xoite_expand_forward)( const xoite* o, sz_t indent, bcore_sink* sink ); \
  typedef er_t (*xoite_expand_indef_typedef)( const xoite* o, sz_t indent, bcore_sink* sink ); \
  typedef er_t (*xoite_expand_spect_declaration)( const xoite* o, sz_t indent, bcore_sink* sink ); \
  typedef er_t (*xoite_expand_spect_definition)( const xoite* o, sz_t indent, bcore_sink* sink ); \
  typedef er_t (*xoite_expand_declaration)( const xoite* o, sz_t indent, bcore_sink* sink ); \
  typedef er_t (*xoite_expand_indef_declaration)( const xoite* o, sz_t indent, bcore_sink* sink ); \
  typedef er_t (*xoite_expand_definition)( const xoite* o, sz_t indent, bcore_sink* sink ); \
  typedef er_t (*xoite_expand_init1)( const xoite* o, sz_t indent, bcore_sink* sink ); \
  BCORE_DECLARE_SPECT( xoite ) \
  { \
      bcore_spect_header_s header; \
      xoite_parse parse; \
      xoite_get_hash get_hash; \
      xoite_get_global_name_sc get_global_name_sc; \
      xoite_finalize finalize; \
      xoite_expand_forward expand_forward; \
      xoite_expand_indef_typedef expand_indef_typedef; \
      xoite_expand_spect_declaration expand_spect_declaration; \
      xoite_expand_spect_definition expand_spect_definition; \
      xoite_expand_declaration expand_declaration; \
      xoite_expand_indef_declaration expand_indef_declaration; \
      xoite_expand_definition expand_definition; \
      xoite_expand_init1 expand_init1; \
  }; \
  static inline xoite* xoite_t_create( tp_t t ) { bcore_trait_assert_satisfied_type( TYPEOF_xoite, t ); return ( xoite* )bcore_inst_t_create( t ); } \
  static inline bl_t xoite_t_is_trait_of( tp_t t ) { return bcore_trait_is_of( t, TYPEOF_xoite ); } \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( xoite ) \
  static inline bl_t xoite_a_is_trait_of( vc_t o ) { return bcore_trait_is_of( o ? *(aware_t*)o : 0, TYPEOF_xoite ); } \
  static inline er_t xoite_p_parse( const xoite_s* __p, xoite* o, bcore_source* source ) { assert( __p->parse ); return __p->parse( o, source ); } \
  static inline er_t xoite_a_parse( xoite* o, bcore_source* source ) { const xoite_s* p = xoite_s_get_aware( o ); assert( p->parse ); return p->parse( o, source ); } \
  static inline bl_t xoite_p_defines_parse( const xoite_s* __p ) { return __p->parse != NULL; } \
  static inline bl_t xoite_a_defines_parse( const xoite* o ) { return xoite_s_get_aware( o )->parse != NULL; } \
  static inline tp_t xoite_p_get_hash( const xoite_s* __p, const xoite* o ) { assert( __p->get_hash ); return __p->get_hash( o ); } \
  static inline tp_t xoite_a_get_hash( const xoite* o ) { const xoite_s* p = xoite_s_get_aware( o ); assert( p->get_hash ); return p->get_hash( o ); } \
  static inline bl_t xoite_p_defines_get_hash( const xoite_s* __p ) { return __p->get_hash != NULL; } \
  static inline bl_t xoite_a_defines_get_hash( const xoite* o ) { return xoite_s_get_aware( o )->get_hash != NULL; } \
  static inline sc_t xoite_p_get_global_name_sc( const xoite_s* __p, const xoite* o ) { assert( __p->get_global_name_sc ); return __p->get_global_name_sc( o ); } \
  static inline sc_t xoite_a_get_global_name_sc( const xoite* o ) { const xoite_s* p = xoite_s_get_aware( o ); assert( p->get_global_name_sc ); return p->get_global_name_sc( o ); } \
  static inline bl_t xoite_p_defines_get_global_name_sc( const xoite_s* __p ) { return __p->get_global_name_sc != NULL; } \
  static inline bl_t xoite_a_defines_get_global_name_sc( const xoite* o ) { return xoite_s_get_aware( o )->get_global_name_sc != NULL; } \
  static inline er_t xoite_p_finalize( const xoite_s* __p, xoite* o ) { assert( __p->finalize ); return __p->finalize( o ); } \
  static inline er_t xoite_a_finalize( xoite* o ) { const xoite_s* p = xoite_s_get_aware( o ); assert( p->finalize ); return p->finalize( o ); } \
  static inline bl_t xoite_p_defines_finalize( const xoite_s* __p ) { return true; } \
  static inline bl_t xoite_a_defines_finalize( const xoite* o ) { return true; } \
  static inline er_t xoite_finalize__( xoite* o ){return 0;} \
  static inline er_t xoite_p_expand_forward( const xoite_s* __p, const xoite* o, sz_t indent, bcore_sink* sink ) { assert( __p->expand_forward ); return __p->expand_forward( o, indent, sink ); } \
  static inline er_t xoite_a_expand_forward( const xoite* o, sz_t indent, bcore_sink* sink ) { const xoite_s* p = xoite_s_get_aware( o ); assert( p->expand_forward ); return p->expand_forward( o, indent, sink ); } \
  static inline bl_t xoite_p_defines_expand_forward( const xoite_s* __p ) { return true; } \
  static inline bl_t xoite_a_defines_expand_forward( const xoite* o ) { return true; } \
  static inline er_t xoite_expand_forward__( const xoite* o, sz_t indent, bcore_sink* sink ){return 0;} \
  static inline er_t xoite_p_expand_indef_typedef( const xoite_s* __p, const xoite* o, sz_t indent, bcore_sink* sink ) { assert( __p->expand_indef_typedef ); return __p->expand_indef_typedef( o, indent, sink ); } \
  static inline er_t xoite_a_expand_indef_typedef( const xoite* o, sz_t indent, bcore_sink* sink ) { const xoite_s* p = xoite_s_get_aware( o ); assert( p->expand_indef_typedef ); return p->expand_indef_typedef( o, indent, sink ); } \
  static inline bl_t xoite_p_defines_expand_indef_typedef( const xoite_s* __p ) { return true; } \
  static inline bl_t xoite_a_defines_expand_indef_typedef( const xoite* o ) { return true; } \
  static inline er_t xoite_expand_indef_typedef__( const xoite* o, sz_t indent, bcore_sink* sink ){return 0;} \
  static inline er_t xoite_p_expand_spect_declaration( const xoite_s* __p, const xoite* o, sz_t indent, bcore_sink* sink ) { assert( __p->expand_spect_declaration ); return __p->expand_spect_declaration( o, indent, sink ); } \
  static inline er_t xoite_a_expand_spect_declaration( const xoite* o, sz_t indent, bcore_sink* sink ) { const xoite_s* p = xoite_s_get_aware( o ); assert( p->expand_spect_declaration ); return p->expand_spect_declaration( o, indent, sink ); } \
  static inline bl_t xoite_p_defines_expand_spect_declaration( const xoite_s* __p ) { return true; } \
  static inline bl_t xoite_a_defines_expand_spect_declaration( const xoite* o ) { return true; } \
  static inline er_t xoite_expand_spect_declaration__( const xoite* o, sz_t indent, bcore_sink* sink ){return 0;} \
  static inline er_t xoite_p_expand_spect_definition( const xoite_s* __p, const xoite* o, sz_t indent, bcore_sink* sink ) { assert( __p->expand_spect_definition ); return __p->expand_spect_definition( o, indent, sink ); } \
  static inline er_t xoite_a_expand_spect_definition( const xoite* o, sz_t indent, bcore_sink* sink ) { const xoite_s* p = xoite_s_get_aware( o ); assert( p->expand_spect_definition ); return p->expand_spect_definition( o, indent, sink ); } \
  static inline bl_t xoite_p_defines_expand_spect_definition( const xoite_s* __p ) { return true; } \
  static inline bl_t xoite_a_defines_expand_spect_definition( const xoite* o ) { return true; } \
  static inline er_t xoite_expand_spect_definition__( const xoite* o, sz_t indent, bcore_sink* sink ){return 0;} \
  static inline er_t xoite_p_expand_declaration( const xoite_s* __p, const xoite* o, sz_t indent, bcore_sink* sink ) { assert( __p->expand_declaration ); return __p->expand_declaration( o, indent, sink ); } \
  static inline er_t xoite_a_expand_declaration( const xoite* o, sz_t indent, bcore_sink* sink ) { const xoite_s* p = xoite_s_get_aware( o ); assert( p->expand_declaration ); return p->expand_declaration( o, indent, sink ); } \
  static inline bl_t xoite_p_defines_expand_declaration( const xoite_s* __p ) { return true; } \
  static inline bl_t xoite_a_defines_expand_declaration( const xoite* o ) { return true; } \
  static inline er_t xoite_expand_declaration__( const xoite* o, sz_t indent, bcore_sink* sink ){return 0;} \
  static inline er_t xoite_p_expand_indef_declaration( const xoite_s* __p, const xoite* o, sz_t indent, bcore_sink* sink ) { assert( __p->expand_indef_declaration ); return __p->expand_indef_declaration( o, indent, sink ); } \
  static inline er_t xoite_a_expand_indef_declaration( const xoite* o, sz_t indent, bcore_sink* sink ) { const xoite_s* p = xoite_s_get_aware( o ); assert( p->expand_indef_declaration ); return p->expand_indef_declaration( o, indent, sink ); } \
  static inline bl_t xoite_p_defines_expand_indef_declaration( const xoite_s* __p ) { return true; } \
  static inline bl_t xoite_a_defines_expand_indef_declaration( const xoite* o ) { return true; } \
  static inline er_t xoite_expand_indef_declaration__( const xoite* o, sz_t indent, bcore_sink* sink ){return 0;} \
  static inline er_t xoite_p_expand_definition( const xoite_s* __p, const xoite* o, sz_t indent, bcore_sink* sink ) { assert( __p->expand_definition ); return __p->expand_definition( o, indent, sink ); } \
  static inline er_t xoite_a_expand_definition( const xoite* o, sz_t indent, bcore_sink* sink ) { const xoite_s* p = xoite_s_get_aware( o ); assert( p->expand_definition ); return p->expand_definition( o, indent, sink ); } \
  static inline bl_t xoite_p_defines_expand_definition( const xoite_s* __p ) { return true; } \
  static inline bl_t xoite_a_defines_expand_definition( const xoite* o ) { return true; } \
  static inline er_t xoite_expand_definition__( const xoite* o, sz_t indent, bcore_sink* sink ){return 0;} \
  static inline er_t xoite_p_expand_init1( const xoite_s* __p, const xoite* o, sz_t indent, bcore_sink* sink ) { assert( __p->expand_init1 ); return __p->expand_init1( o, indent, sink ); } \
  static inline er_t xoite_a_expand_init1( const xoite* o, sz_t indent, bcore_sink* sink ) { const xoite_s* p = xoite_s_get_aware( o ); assert( p->expand_init1 ); return p->expand_init1( o, indent, sink ); } \
  static inline bl_t xoite_p_defines_expand_init1( const xoite_s* __p ) { return true; } \
  static inline bl_t xoite_a_defines_expand_init1( const xoite* o ) { return true; } \
  static inline er_t xoite_expand_init1__( const xoite* o, sz_t indent, bcore_sink* sink ){return 0;}

/**********************************************************************************************************************/
// source: xoite_name.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoite_name

#define TYPEOF_xoite_name 1033424222
#define TYPEOF_xoite_name_s 576784544
#define TYPEOF_xoite_name_s 576784544
#define BETH_EXPAND_ITEM_xoite_name_s \
  BCORE_DECLARE_OBJECT( xoite_name_s ) \
    {aware_t _;st_s name;xoite_group_s* group;bcore_source_point_s source_point;}; \
  er_t xoite_name_s_parse( xoite_name_s* o, bcore_source* source ); \
  tp_t xoite_name_s_get_hash( const xoite_name_s* o ); \
  sc_t xoite_name_s_get_global_name_sc( const xoite_name_s* o ); \
  er_t xoite_name_s_expand_declaration( const xoite_name_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoite_name_s_expand_init1( const xoite_name_s* o, sz_t indent, bcore_sink* sink );
#define BETH_EXPAND_GROUP_xoite_name \
  BCORE_FORWARD_OBJECT( xoite_name ); \
  BCORE_FORWARD_OBJECT( xoite_name_s ); \
  BETH_EXPAND_ITEM_xoite_name_s

/**********************************************************************************************************************/
// source: xoite_forward.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoite_forward

#define TYPEOF_xoite_forward 168516626
#define TYPEOF_xoite_forward_s 3158286860
#define TYPEOF_xoite_forward_s 3158286860
#define BETH_EXPAND_ITEM_xoite_forward_s \
  BCORE_DECLARE_OBJECT( xoite_forward_s ) \
    {aware_t _;st_s name;xoite_group_s* group;bcore_source_point_s source_point;}; \
  er_t xoite_forward_s_parse( xoite_forward_s* o, bcore_source* source ); \
  tp_t xoite_forward_s_get_hash( const xoite_forward_s* o ); \
  sc_t xoite_forward_s_get_global_name_sc( const xoite_forward_s* o ); \
  er_t xoite_forward_s_expand_declaration( const xoite_forward_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoite_forward_s_expand_forward( const xoite_forward_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoite_forward_s_expand_init1( const xoite_forward_s* o, sz_t indent, bcore_sink* sink );
#define BETH_EXPAND_GROUP_xoite_forward \
  BCORE_FORWARD_OBJECT( xoite_forward ); \
  BCORE_FORWARD_OBJECT( xoite_forward_s ); \
  BETH_EXPAND_ITEM_xoite_forward_s

/**********************************************************************************************************************/
// source: xoite_arg.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoite_arg

#define TYPEOF_xoite_arg 1253496079
#define TYPEOF_xoite_arg_s 3829723705
#define TYPEOF_xoite_arg_s 3829723705
#define BETH_EXPAND_ITEM_xoite_arg_s \
  BCORE_DECLARE_OBJECT( xoite_arg_s ) \
    {aware_t _;st_s type;st_s name;xoite_group_s* group;bcore_source_point_s source_point;}; \
  er_t xoite_arg_s_parse( xoite_arg_s* o, bcore_source* source ); \
  tp_t xoite_arg_s_get_hash( const xoite_arg_s* o ); \
  er_t xoite_arg_s_expand( const xoite_arg_s* o, bcore_sink* sink ); \
  er_t xoite_arg_s_expand_name( const xoite_arg_s* o, bcore_sink* sink );
#define BETH_EXPAND_GROUP_xoite_arg \
  BCORE_FORWARD_OBJECT( xoite_arg ); \
  BCORE_FORWARD_OBJECT( xoite_arg_s ); \
  BETH_EXPAND_ITEM_xoite_arg_s

/**********************************************************************************************************************/
// source: xoite_args.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoite_args

#define TYPEOF_xoite_args 433197620
#define TYPEOF_xoite_args_s 1271258406
#define TYPEOF_xoite_args_s 1271258406
#define BETH_EXPAND_ITEM_xoite_args_s \
  BCORE_DECLARE_OBJECT( xoite_args_s ) \
    {aware_t _;BCORE_ARRAY_DYN_SOLID_STATIC_S( xoite_arg_s, );xoite_group_s* group;}; \
  er_t xoite_args_s_parse( xoite_args_s* o, bcore_source* source ); \
  tp_t xoite_args_s_get_hash( const xoite_args_s* o ); \
  er_t xoite_args_s_append( xoite_args_s* o, bcore_source* source ); \
  er_t xoite_args_s_expand( const xoite_args_s* o, bl_t first, bcore_sink* sink ); \
  er_t xoite_args_s_expand_name( const xoite_args_s* o, bl_t first, bcore_sink* sink );
#define BETH_EXPAND_GROUP_xoite_args \
  BCORE_FORWARD_OBJECT( xoite_args ); \
  BCORE_FORWARD_OBJECT( xoite_args_s ); \
  BETH_EXPAND_ITEM_xoite_args_s

/**********************************************************************************************************************/
// source: xoite_signature.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoite_signature

#define TYPEOF_xoite_signature 2184441749
#define TYPEOF_xoite_signature_s 2452024311
#define TYPEOF_xoite_signature_s 2452024311
#define BETH_EXPAND_ITEM_xoite_signature_s \
  BCORE_DECLARE_OBJECT( xoite_signature_s ) \
    {aware_t _;st_s name;st_s global_name;bl_t has_ret;st_s ret_type;xoite_args_s args;tp_t arg_o;xoite_group_s* group;bcore_source_point_s source_point;}; \
  er_t xoite_signature_s_parse( xoite_signature_s* o, bcore_source* source ); \
  tp_t xoite_signature_s_get_hash( const xoite_signature_s* o ); \
  sc_t xoite_signature_s_get_global_name_sc( const xoite_signature_s* o );
#define BETH_EXPAND_GROUP_xoite_signature \
  BCORE_FORWARD_OBJECT( xoite_signature ); \
  BCORE_FORWARD_OBJECT( xoite_signature_s ); \
  BETH_EXPAND_ITEM_xoite_signature_s

/**********************************************************************************************************************/
// source: xoite_body.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoite_body

#define TYPEOF_xoite_body 4233290765
#define TYPEOF_xoite_body_s 1114846719
#define TYPEOF_xoite_body_s 1114846719
#define BETH_EXPAND_ITEM_xoite_body_s \
  BCORE_DECLARE_OBJECT( xoite_body_s ) \
    {aware_t _;st_s name;st_s global_name;st_s code;bl_t go_inline;xoite_group_s* group;bcore_source_point_s source_point;}; \
  tp_t xoite_body_s_get_hash( const xoite_body_s* o ); \
  sc_t xoite_body_s_get_global_name_sc( const xoite_body_s* o ); \
  er_t xoite_body_s_parse_code( xoite_body_s* o, xoite_stamp_s* stamp, bcore_source* source ); \
  er_t xoite_body_s_parse( xoite_body_s* o, xoite_stamp_s* stamp, bcore_source* source ); \
  er_t xoite_body_s_expand( const xoite_body_s* o, sz_t indent, bcore_sink* sink );
#define BETH_EXPAND_GROUP_xoite_body \
  BCORE_FORWARD_OBJECT( xoite_body ); \
  BCORE_FORWARD_OBJECT( xoite_body_s ); \
  BETH_EXPAND_ITEM_xoite_body_s

/**********************************************************************************************************************/
// source: xoite_feature.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoite_feature

#define TYPEOF_xoite_feature 3673423077
#define TYPEOF_xoite_feature_s 2566336903
#define TYPEOF_xoite_feature_s 2566336903
#define BETH_EXPAND_ITEM_xoite_feature_s \
  BCORE_DECLARE_OBJECT( xoite_feature_s ) \
    {aware_t _;st_s name;st_s global_name;st_s default_name;xoite_body_s* default_body;bl_t strict;bl_t flag_p;bl_t flag_t;bl_t flag_a;bl_t flag_r;bl_t has_ret;st_s ret_type;xoite_args_s args;bl_t mutable;xoite_group_s* group;bcore_source_point_s source_point;}; \
  er_t xoite_feature_s_parse( xoite_feature_s* o, bcore_source* source ); \
  tp_t xoite_feature_s_get_hash( const xoite_feature_s* o ); \
  sc_t xoite_feature_s_get_global_name_sc( const xoite_feature_s* o ); \
  er_t xoite_feature_s_expand_indef_typedef( const xoite_feature_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoite_feature_s_expand_spect_declaration( const xoite_feature_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoite_feature_s_expand_indef_declaration( const xoite_feature_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoite_feature_s_expand_definition( const xoite_feature_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoite_feature_s_expand_init1( const xoite_feature_s* o, sz_t indent, bcore_sink* sink );
#define BETH_EXPAND_GROUP_xoite_feature \
  BCORE_FORWARD_OBJECT( xoite_feature ); \
  BCORE_FORWARD_OBJECT( xoite_feature_s ); \
  BETH_EXPAND_ITEM_xoite_feature_s

/**********************************************************************************************************************/
// source: xoite_func.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoite_func

#define TYPEOF_xoite_func 1765923055
#define TYPEOF_xoite_func_s 2980463321
#define TYPEOF_xoite_func_s 2980463321
#define BETH_EXPAND_ITEM_xoite_func_s \
  BCORE_DECLARE_OBJECT( xoite_func_s ) \
    {aware_t _;st_s name;st_s decl;tp_t type;bl_t overloadable;xoite_body_s* body;xoite_group_s* group;bcore_source_point_s source_point;}; \
  tp_t xoite_func_s_get_hash( const xoite_func_s* o ); \
  er_t xoite_func_s_parse( xoite_func_s* o, xoite_group_s* group, xoite_stamp_s* stamp, bcore_source* source ); \
  bl_t xoite_func_s_registerable( const xoite_func_s* o );
#define BETH_EXPAND_GROUP_xoite_func \
  BCORE_FORWARD_OBJECT( xoite_func ); \
  BCORE_FORWARD_OBJECT( xoite_func_s ); \
  BETH_EXPAND_ITEM_xoite_func_s

/**********************************************************************************************************************/
// source: xoite_funcs.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoite_funcs

#define TYPEOF_xoite_funcs 1319632276
#define TYPEOF_xoite_funcs_s 3228587462
#define TYPEOF_xoite_funcs_s 3228587462
#define BETH_EXPAND_ITEM_xoite_funcs_s \
  BCORE_DECLARE_OBJECT( xoite_funcs_s ) \
    {aware_t _;BCORE_ARRAY_DYN_LINK_STATIC_S( xoite_func_s, );}; \
  bl_t xoite_funcs_s_exists( const xoite_funcs_s* o, tp_t type ); \
  sz_t xoite_funcs_s_get_index( const xoite_funcs_s* o, tp_t type ); \
  er_t xoite_funcs_s_replace_fork( xoite_funcs_s* o, sz_t idx, xoite_func_s* func );
#define BETH_EXPAND_GROUP_xoite_funcs \
  BCORE_FORWARD_OBJECT( xoite_funcs ); \
  BCORE_FORWARD_OBJECT( xoite_funcs_s ); \
  BETH_EXPAND_ITEM_xoite_funcs_s

/**********************************************************************************************************************/
// source: xoite_group.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoite_group

#define TYPEOF_xoite_group 1274342404
#define TYPEOF_xoite_group_s 734934966
#define TYPEOF_xoite_group_s 734934966
#define BETH_EXPAND_ITEM_xoite_group_s \
  BCORE_DECLARE_OBJECT( xoite_group_s ) \
    {aware_t _;BCORE_ARRAY_DYN_LINK_STATIC_S( xoite, );st_s name;xoite_group_s* group;st_s trait_name;tp_t hash;bl_t expandable;bl_t has_features;bl_t is_aware;bl_t retrievable;xoite_stamp_s* extending;xoite_funcs_s funcs;xoite_source_s* source;bcore_source_point_s source_point;}; \
  er_t xoite_group_s_parse( xoite_group_s* o, bcore_source* source ); \
  tp_t xoite_group_s_get_hash( const xoite_group_s* o ); \
  sc_t xoite_group_s_get_global_name_sc( const xoite_group_s* o ); \
  er_t xoite_group_s_finalize( xoite_group_s* o ); \
  er_t xoite_group_s_parse_name( xoite_group_s* o, st_s* name, bcore_source* source ); \
  er_t xoite_group_s_parse_name_recursive( xoite_group_s* o, st_s* name, bcore_source* source ); \
  er_t xoite_group_s_expand_declaration( const xoite_group_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoite_group_s_expand_definition( const xoite_group_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoite_group_s_expand_init1( const xoite_group_s* o, sz_t indent, bcore_sink* sink ); \
  xoite_compiler_s* xoite_group_s_get_compiler( const xoite_group_s* o );
#define BETH_EXPAND_GROUP_xoite_group \
  BCORE_FORWARD_OBJECT( xoite_group ); \
  BCORE_FORWARD_OBJECT( xoite_group_s ); \
  BETH_EXPAND_ITEM_xoite_group_s

/**********************************************************************************************************************/
// source: xoite_stamp.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoite_stamp

#define TYPEOF_xoite_stamp 985077724
#define TYPEOF_xoite_stamp_s 139668862
#define TYPEOF_xoite_stamp_s 139668862
#define BETH_EXPAND_ITEM_xoite_stamp_s \
  BCORE_DECLARE_OBJECT( xoite_stamp_s ) \
    {aware_t _;st_s name;st_s trait_name;st_s* self_source;xoite_funcs_s funcs;xoite_group_s* group;bcore_source_point_s source_point;}; \
  tp_t xoite_stamp_s_get_hash( const xoite_stamp_s* o ); \
  sc_t xoite_stamp_s_get_global_name_sc( const xoite_stamp_s* o ); \
  er_t xoite_stamp_s_finalize( xoite_stamp_s* o ); \
  er_t xoite_stamp_s_expand_declaration( const xoite_stamp_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoite_stamp_s_expand_forward( const xoite_stamp_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoite_stamp_s_expand_indef_declaration( const xoite_stamp_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoite_stamp_s_expand_definition( const xoite_stamp_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoite_stamp_s_expand_init1( const xoite_stamp_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoite_stamp_s_parse( xoite_stamp_s* o, xoite_group_s* group, bcore_source* source ); \
  er_t xoite_stamp_s_resolve_chars( const xoite_stamp_s* o, st_s* string ); \
  er_t xoite_stamp_s_make_funcs_overloadable( xoite_stamp_s* o );
#define BETH_EXPAND_GROUP_xoite_stamp \
  BCORE_FORWARD_OBJECT( xoite_stamp ); \
  BCORE_FORWARD_OBJECT( xoite_stamp_s ); \
  BETH_EXPAND_ITEM_xoite_stamp_s

/**********************************************************************************************************************/
// source: xoite_nested_group.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoite_nested_group

#define TYPEOF_xoite_nested_group 2697084318
#define TYPEOF_xoite_nested_group_s 1872428512
#define TYPEOF_xoite_nested_group_s 1872428512
#define BETH_EXPAND_ITEM_xoite_nested_group_s \
  BCORE_DECLARE_OBJECT( xoite_nested_group_s ) \
    {aware_t _;xoite_group_s* group;}; \
  tp_t xoite_nested_group_s_get_hash( const xoite_nested_group_s* o ); \
  er_t xoite_nested_group_s_expand_forward( const xoite_nested_group_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoite_nested_group_s_expand_indef_declaration( const xoite_nested_group_s* o, sz_t indent, bcore_sink* sink );
#define BETH_EXPAND_GROUP_xoite_nested_group \
  BCORE_FORWARD_OBJECT( xoite_nested_group ); \
  BCORE_FORWARD_OBJECT( xoite_nested_group_s ); \
  BETH_EXPAND_ITEM_xoite_nested_group_s

/**********************************************************************************************************************/
// source: xoite_source.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoite_source

#define TYPEOF_xoite_source 4133215040
#define TYPEOF_xoite_source_s 324505114
#define TYPEOF_xoite_source_s 324505114
#define BETH_EXPAND_ITEM_xoite_source_s \
  BCORE_DECLARE_OBJECT( xoite_source_s ) \
    {aware_t _;st_s name;st_s path;tp_t hash;BCORE_ARRAY_DYN_LINK_STATIC_S( xoite_group_s, );xoite_target_s* target;}; \
  er_t xoite_source_s_finalize( xoite_source_s* o ); \
  er_t xoite_source_s_push_group( xoite_source_s* o, xoite_group_s* group ); \
  er_t xoite_source_s_parse( xoite_source_s* o, bcore_source* source ); \
  er_t xoite_source_s_finalize( xoite_source_s* o ); \
  er_t xoite_source_s_expand_declaration( const xoite_source_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoite_source_s_expand_definition( const xoite_source_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoite_source_s_expand_init1( const xoite_source_s* o, sz_t indent, bcore_sink* sink );
#define BETH_EXPAND_GROUP_xoite_source \
  BCORE_FORWARD_OBJECT( xoite_source ); \
  BCORE_FORWARD_OBJECT( xoite_source_s ); \
  BETH_EXPAND_ITEM_xoite_source_s

/**********************************************************************************************************************/
// source: xoite_target.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoite_target

#define TYPEOF_xoite_target 3158170816
#define TYPEOF_xoite_target_s 4106300314
#define TYPEOF_xoite_target_s 4106300314
#define BETH_EXPAND_ITEM_xoite_target_s \
  BCORE_DECLARE_OBJECT( xoite_target_s ) \
    {aware_t _;st_s name;st_s path;BCORE_ARRAY_DYN_LINK_STATIC_S( xoite_source_s, );st_s signal_handler_name;bcore_arr_sz_s dependencies;bl_t flag;bl_t modified;st_s* planted_h;st_s* planted_c;xoite_compiler_s* compiler;}; \
  er_t xoite_target_s_finalize( xoite_target_s* o ); \
  er_t xoite_target_s_parse( xoite_target_s* o, sc_t source_path ); \
  bl_t xoite_target_s_to_be_modified( const xoite_target_s* o ); \
  er_t xoite_target_s_expand_phase1( xoite_target_s* o, bl_t* p_modified ); \
  er_t xoite_target_s_expand_phase2( xoite_target_s* o, bl_t* p_modified ); \
  bl_t xoite_target_s_is_cyclic( xoite_target_s* o );
#define BETH_EXPAND_GROUP_xoite_target \
  BCORE_FORWARD_OBJECT( xoite_target ); \
  BCORE_FORWARD_OBJECT( xoite_target_s ); \
  BETH_EXPAND_ITEM_xoite_target_s

/**********************************************************************************************************************/
// source: xoite_compiler.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoite_compiler

#define TYPEOF_xoite_compiler 676461596
#define TYPEOF_xoite_compiler_s 392017598
#define TYPEOF_xoite_compiler_s 392017598
#define BETH_EXPAND_ITEM_xoite_compiler_s \
  BCORE_DECLARE_OBJECT( xoite_compiler_s ) \
    {aware_t _;BCORE_ARRAY_DYN_LINK_STATIC_S( xoite_target_s, );bcore_hmap_tpvd_s hmap_group;bcore_hmap_tpvd_s hmap_item;bcore_life_s life;bl_t backup_planted_files;bl_t register_plain_functions;bl_t register_signatures;bl_t overwrite_unsigned_planted_files;sz_t verbosity;}; \
  er_t xoite_compiler_s_finalize( xoite_compiler_s* o ); \
  const xoite* xoite_compiler_s_item_get( const xoite_compiler_s* o, tp_t item_id ); \
  bl_t xoite_compiler_s_item_exists( const xoite_compiler_s* o, tp_t item_id ); \
  er_t xoite_compiler_s_item_register( xoite_compiler_s* o, const xoite* item, bcore_source* source ); \
  er_t xoite_compiler_s_group_register( xoite_compiler_s* o, const xoite_group_s* group, bcore_source* source ); \
  er_t xoite_compiler_s_life_a_push( xoite_compiler_s* o, vd_t object ); \
  er_t xoite_compiler_s_check_overwrite( const xoite_compiler_s* o, sc_t file ); \
  er_t xoite_compiler_s_setup( xoite_compiler_s* o ); \
  er_t xoite_compiler_s_compile( xoite_compiler_s* o, sc_t target_name, sc_t source_path, sz_t* p_target_index ); \
  er_t xoite_compiler_s_set_target_signal_handler_name( xoite_compiler_s* o, sz_t target_index, sc_t name ); \
  er_t xoite_compiler_s_set_target_dependencies( xoite_compiler_s* o, sz_t target_index, const bcore_arr_sz_s* dependencies ); \
  er_t xoite_compiler_s_update_planted_files( xoite_compiler_s* o, bl_t* p_modified ); \
  bl_t xoite_compiler_s_update_required( xoite_compiler_s* o ); \
  sz_t xoite_compiler_s_get_verbosity( const xoite_compiler_s* o );
#define BETH_EXPAND_GROUP_xoite_compiler \
  BCORE_FORWARD_OBJECT( xoite_compiler ); \
  BCORE_FORWARD_OBJECT( xoite_compiler_s ); \
  BETH_EXPAND_ITEM_xoite_compiler_s

/**********************************************************************************************************************/
// source: xoite_builder.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoite_builder

#define TYPEOF_xoite_builder 2897218888
#define TYPEOF_xoite_builder_s 1335914290
#define TYPEOF_xoite_builder_target_s 2341769602
#define BETH_EXPAND_ITEM_xoite_builder_target_s \
  BCORE_DECLARE_OBJECT( xoite_builder_target_s ) \
    {aware_t _;st_s* name;st_s* extension;st_s* root;xoite_builder_main_s* main;bcore_arr_st_s dependencies;bcore_arr_st_s sources;st_s* signal_handler;}; \
  void xoite_builder_target_s_source( xoite_builder_target_s* o, bcore_source* source ); \
  er_t xoite_builder_target_s_build( const xoite_builder_target_s* o, sz_t* target_index );
#define TYPEOF_xoite_builder_main_s 1204191458
#define BETH_EXPAND_ITEM_xoite_builder_main_s \
  BCORE_DECLARE_OBJECT( xoite_builder_main_s ) \
    {aware_t _;xoite_compiler_s* compiler;bcore_arr_st_s arr_path;}; \
  void xoite_builder_main_s_init_x( xoite_builder_main_s* o ); \
  er_t xoite_builder_main_s_build_from_file( xoite_builder_main_s* o, sc_t path ); \
  bl_t xoite_builder_main_s_update_required( const xoite_builder_main_s* o ); \
  er_t xoite_builder_main_s_update( const xoite_builder_main_s* o );
#define BETH_EXPAND_GROUP_xoite_builder \
  BCORE_FORWARD_OBJECT( xoite_builder ); \
  BCORE_FORWARD_OBJECT( xoite_builder_target_s ); \
  BCORE_FORWARD_OBJECT( xoite_builder_main_s ); \
  BETH_EXPAND_ITEM_xoite_builder_target_s \
  BETH_EXPAND_ITEM_xoite_builder_main_s

/**********************************************************************************************************************/

vd_t xoite_xoi_out_signal_handler( const bcore_signal_s* o );

#endif // XOITE_XOI_OUT_H
// BETH_PLANT_SIGNATURE 4030433515
