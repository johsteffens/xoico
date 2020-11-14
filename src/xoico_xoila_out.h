/** This file was generated from xoila source code.
 *  Compiling Agent : xoico_compiler (C) 2020 J.B.Steffens
 *  Last File Update: 2020-11-14T16:41:08Z
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
 *  xoico_che.h
 *  xoico_body.x
 *  xoico_builder.x
 *  xoico_cdaleth.x
 *  xoico_cdaleth_builtin.x
 *  xoico_cdaleth_control.x
 *  xoico_che.x
 *  xoico_che_builtin.x
 *  xoico_che_control.x
 *  xoico_compiler.x
 *  xoico_feature.x
 *  xoico_func.x
 *  xoico_group.x
 *
 */

#ifndef XOICO_XOILA_OUT_H
#define XOICO_XOILA_OUT_H

#include "bcore_control.h"

//To force a rebuild of this target by xoico, reset the hash key value below to 0.
#define HKEYOF_xoico_xoila_out 0x69CBA41D34210905ull

#define TYPEOF_xoico_xoila_out 0xD4054BD559134D0Eull

/**********************************************************************************************************************/
// source: xoico.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico

#define TYPEOF_xoico 0x21E8B04DB3E31F5Dull
#define TYPEOF_xoico_spect_s 0x5D91F496B6479859ull
#define TYPEOF_mutable 0xD3AC3C45566EFDE9ull
#define TYPEOF_const 0x65C9718E19E3DF34ull
#define TYPEOF_void 0x3173C900E37AE1DFull
#define TYPEOF_xoico_name_s 0x72C1E17E15481547ull
#define TYPEOF_xoico_forward_s 0x67CE6DD302FEC85Dull
#define TYPEOF_xoico_arg_s 0xDE77C40AC671BCC8ull
#define TYPEOF_xoico_args_s 0x40F4054E83F33D09ull
#define TYPEOF_xoico_signature_s 0xDCE5A3AFBCD17B0Eull
#define TYPEOF_xoico_body_s 0x12DC29D312AD56E4ull
#define TYPEOF_xoico_feature_s 0x320F5368E957D0A2ull
#define TYPEOF_xoico_func_s 0xA748B4C2243B074Aull
#define TYPEOF_xoico_funcs_s 0x292F82E3F2BEA6D3ull
#define TYPEOF_xoico_stamp_s 0x012D01D78049FAE7ull
#define TYPEOF_xoico_group_s 0x0C561A9D047FE9D3ull
#define TYPEOF_xoico_nested_group_s 0xB4EB0E2A56FB3087ull
#define TYPEOF_xoico_source_s 0x11BBCC12FF458D9Dull
#define TYPEOF_xoico_target_s 0x05A0ECAFABEA8CB1ull
#define TYPEOF_xoico_compiler_s 0xA7C0906C33CBFB69ull
#define TYPEOF_xoico_cengine 0x47E6F800E5D85E41ull
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
  BCORE_FORWARD_OBJECT( xoico_cengine ); \
  er_t xoico_parse_f( bcore_source* source, sc_t format ); \
  er_t xoico_embed_file_open( bcore_source* parent, sc_t file_name, bcore_source** include_source ); \
  typedef er_t (*xoico_parse)( xoico* o, bcore_source* source ); \
  typedef tp_t (*xoico_get_hash)( const xoico* o ); \
  typedef sc_t (*xoico_get_global_name_sc)( const xoico* o ); \
  typedef tp_t (*xoico_get_global_name_tp)( const xoico* o ); \
  typedef er_t (*xoico_finalize)( xoico* o ); \
  typedef er_t (*xoico_expand_setup)( xoico* o ); \
  typedef er_t (*xoico_expand_forward)( const xoico* o, sz_t indent, bcore_sink* sink ); \
  typedef er_t (*xoico_expand_indef_typedef)( const xoico* o, sz_t indent, bcore_sink* sink ); \
  typedef er_t (*xoico_expand_spect_declaration)( const xoico* o, sz_t indent, bcore_sink* sink ); \
  typedef er_t (*xoico_expand_spect_definition)( const xoico* o, sz_t indent, bcore_sink* sink ); \
  typedef er_t (*xoico_expand_declaration)( const xoico* o, sz_t indent, bcore_sink* sink ); \
  typedef er_t (*xoico_expand_indef_declaration)( const xoico* o, sz_t indent, bcore_sink* sink ); \
  typedef er_t (*xoico_expand_definition)( const xoico* o, sz_t indent, bcore_sink* sink ); \
  typedef er_t (*xoico_expand_init1)( const xoico* o, sz_t indent, bcore_sink* sink ); \
  XOILA_DECLARE_SPECT( xoico ) \
  { \
      bcore_spect_header_s header; \
      xoico_parse parse; \
      xoico_get_hash get_hash; \
      xoico_get_global_name_sc get_global_name_sc; \
      xoico_get_global_name_tp get_global_name_tp; \
      xoico_finalize finalize; \
      xoico_expand_setup expand_setup; \
      xoico_expand_forward expand_forward; \
      xoico_expand_indef_typedef expand_indef_typedef; \
      xoico_expand_spect_declaration expand_spect_declaration; \
      xoico_expand_spect_definition expand_spect_definition; \
      xoico_expand_declaration expand_declaration; \
      xoico_expand_indef_declaration expand_indef_declaration; \
      xoico_expand_definition expand_definition; \
      xoico_expand_init1 expand_init1; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( xoico ) \
  static inline er_t xoico_p_parse( const xoico_spect_s* __p, xoico* o, bcore_source* source ) { assert( __p->parse ); return __p->parse( o, source ); } \
  static inline er_t xoico_a_parse( xoico* o, bcore_source* source ) { const xoico_spect_s* p = xoico_spect_s_get_aware( o ); assert( p->parse ); return p->parse( o, source ); } \
  static inline bl_t xoico_p_defines_parse( const xoico_spect_s* __p ) { return __p->parse != NULL; } \
  static inline bl_t xoico_a_defines_parse( const xoico* o ) { return xoico_spect_s_get_aware( o )->parse != NULL; } \
  static inline tp_t xoico_p_get_hash( const xoico_spect_s* __p, const xoico* o ) { assert( __p->get_hash ); return __p->get_hash( o ); } \
  static inline tp_t xoico_a_get_hash( const xoico* o ) { const xoico_spect_s* p = xoico_spect_s_get_aware( o ); assert( p->get_hash ); return p->get_hash( o ); } \
  static inline bl_t xoico_p_defines_get_hash( const xoico_spect_s* __p ) { return __p->get_hash != NULL; } \
  static inline bl_t xoico_a_defines_get_hash( const xoico* o ) { return xoico_spect_s_get_aware( o )->get_hash != NULL; } \
  static inline sc_t xoico_p_get_global_name_sc( const xoico_spect_s* __p, const xoico* o ) { assert( __p->get_global_name_sc ); return __p->get_global_name_sc( o ); } \
  static inline sc_t xoico_a_get_global_name_sc( const xoico* o ) { const xoico_spect_s* p = xoico_spect_s_get_aware( o ); assert( p->get_global_name_sc ); return p->get_global_name_sc( o ); } \
  static inline bl_t xoico_p_defines_get_global_name_sc( const xoico_spect_s* __p ) { return __p->get_global_name_sc != NULL; } \
  static inline bl_t xoico_a_defines_get_global_name_sc( const xoico* o ) { return xoico_spect_s_get_aware( o )->get_global_name_sc != NULL; } \
  static inline tp_t xoico_p_get_global_name_tp( const xoico_spect_s* __p, const xoico* o ) { assert( __p->get_global_name_tp ); return __p->get_global_name_tp( o ); } \
  static inline tp_t xoico_a_get_global_name_tp( const xoico* o ) { const xoico_spect_s* p = xoico_spect_s_get_aware( o ); assert( p->get_global_name_tp ); return p->get_global_name_tp( o ); } \
  static inline bl_t xoico_p_defines_get_global_name_tp( const xoico_spect_s* __p ) { return true; } \
  static inline bl_t xoico_a_defines_get_global_name_tp( const xoico* o ) { return true; } \
  static inline tp_t xoico_get_global_name_tp_default( const xoico* o ){ return  btypeof( xoico_a_get_global_name_sc( o ) );} \
  static inline er_t xoico_p_finalize( const xoico_spect_s* __p, xoico* o ) { assert( __p->finalize ); return __p->finalize( o ); } \
  static inline er_t xoico_a_finalize( xoico* o ) { const xoico_spect_s* p = xoico_spect_s_get_aware( o ); assert( p->finalize ); return p->finalize( o ); } \
  static inline bl_t xoico_p_defines_finalize( const xoico_spect_s* __p ) { return true; } \
  static inline bl_t xoico_a_defines_finalize( const xoico* o ) { return true; } \
  static inline er_t xoico_finalize_default( xoico* o ){ return  0;} \
  static inline er_t xoico_p_expand_setup( const xoico_spect_s* __p, xoico* o ) { assert( __p->expand_setup ); return __p->expand_setup( o ); } \
  static inline er_t xoico_a_expand_setup( xoico* o ) { const xoico_spect_s* p = xoico_spect_s_get_aware( o ); assert( p->expand_setup ); return p->expand_setup( o ); } \
  static inline bl_t xoico_p_defines_expand_setup( const xoico_spect_s* __p ) { return true; } \
  static inline bl_t xoico_a_defines_expand_setup( const xoico* o ) { return true; } \
  static inline er_t xoico_expand_setup_default( xoico* o ){ return  0;} \
  static inline er_t xoico_p_expand_forward( const xoico_spect_s* __p, const xoico* o, sz_t indent, bcore_sink* sink ) { assert( __p->expand_forward ); return __p->expand_forward( o, indent, sink ); } \
  static inline er_t xoico_a_expand_forward( const xoico* o, sz_t indent, bcore_sink* sink ) { const xoico_spect_s* p = xoico_spect_s_get_aware( o ); assert( p->expand_forward ); return p->expand_forward( o, indent, sink ); } \
  static inline bl_t xoico_p_defines_expand_forward( const xoico_spect_s* __p ) { return true; } \
  static inline bl_t xoico_a_defines_expand_forward( const xoico* o ) { return true; } \
  static inline er_t xoico_expand_forward_default( const xoico* o, sz_t indent, bcore_sink* sink ){ return  0;} \
  static inline er_t xoico_p_expand_indef_typedef( const xoico_spect_s* __p, const xoico* o, sz_t indent, bcore_sink* sink ) { assert( __p->expand_indef_typedef ); return __p->expand_indef_typedef( o, indent, sink ); } \
  static inline er_t xoico_a_expand_indef_typedef( const xoico* o, sz_t indent, bcore_sink* sink ) { const xoico_spect_s* p = xoico_spect_s_get_aware( o ); assert( p->expand_indef_typedef ); return p->expand_indef_typedef( o, indent, sink ); } \
  static inline bl_t xoico_p_defines_expand_indef_typedef( const xoico_spect_s* __p ) { return true; } \
  static inline bl_t xoico_a_defines_expand_indef_typedef( const xoico* o ) { return true; } \
  static inline er_t xoico_expand_indef_typedef_default( const xoico* o, sz_t indent, bcore_sink* sink ){ return  0;} \
  static inline er_t xoico_p_expand_spect_declaration( const xoico_spect_s* __p, const xoico* o, sz_t indent, bcore_sink* sink ) { assert( __p->expand_spect_declaration ); return __p->expand_spect_declaration( o, indent, sink ); } \
  static inline er_t xoico_a_expand_spect_declaration( const xoico* o, sz_t indent, bcore_sink* sink ) { const xoico_spect_s* p = xoico_spect_s_get_aware( o ); assert( p->expand_spect_declaration ); return p->expand_spect_declaration( o, indent, sink ); } \
  static inline bl_t xoico_p_defines_expand_spect_declaration( const xoico_spect_s* __p ) { return true; } \
  static inline bl_t xoico_a_defines_expand_spect_declaration( const xoico* o ) { return true; } \
  static inline er_t xoico_expand_spect_declaration_default( const xoico* o, sz_t indent, bcore_sink* sink ){ return  0;} \
  static inline er_t xoico_p_expand_spect_definition( const xoico_spect_s* __p, const xoico* o, sz_t indent, bcore_sink* sink ) { assert( __p->expand_spect_definition ); return __p->expand_spect_definition( o, indent, sink ); } \
  static inline er_t xoico_a_expand_spect_definition( const xoico* o, sz_t indent, bcore_sink* sink ) { const xoico_spect_s* p = xoico_spect_s_get_aware( o ); assert( p->expand_spect_definition ); return p->expand_spect_definition( o, indent, sink ); } \
  static inline bl_t xoico_p_defines_expand_spect_definition( const xoico_spect_s* __p ) { return true; } \
  static inline bl_t xoico_a_defines_expand_spect_definition( const xoico* o ) { return true; } \
  static inline er_t xoico_expand_spect_definition_default( const xoico* o, sz_t indent, bcore_sink* sink ){ return  0;} \
  static inline er_t xoico_p_expand_declaration( const xoico_spect_s* __p, const xoico* o, sz_t indent, bcore_sink* sink ) { assert( __p->expand_declaration ); return __p->expand_declaration( o, indent, sink ); } \
  static inline er_t xoico_a_expand_declaration( const xoico* o, sz_t indent, bcore_sink* sink ) { const xoico_spect_s* p = xoico_spect_s_get_aware( o ); assert( p->expand_declaration ); return p->expand_declaration( o, indent, sink ); } \
  static inline bl_t xoico_p_defines_expand_declaration( const xoico_spect_s* __p ) { return true; } \
  static inline bl_t xoico_a_defines_expand_declaration( const xoico* o ) { return true; } \
  static inline er_t xoico_expand_declaration_default( const xoico* o, sz_t indent, bcore_sink* sink ){ return  0;} \
  static inline er_t xoico_p_expand_indef_declaration( const xoico_spect_s* __p, const xoico* o, sz_t indent, bcore_sink* sink ) { assert( __p->expand_indef_declaration ); return __p->expand_indef_declaration( o, indent, sink ); } \
  static inline er_t xoico_a_expand_indef_declaration( const xoico* o, sz_t indent, bcore_sink* sink ) { const xoico_spect_s* p = xoico_spect_s_get_aware( o ); assert( p->expand_indef_declaration ); return p->expand_indef_declaration( o, indent, sink ); } \
  static inline bl_t xoico_p_defines_expand_indef_declaration( const xoico_spect_s* __p ) { return true; } \
  static inline bl_t xoico_a_defines_expand_indef_declaration( const xoico* o ) { return true; } \
  static inline er_t xoico_expand_indef_declaration_default( const xoico* o, sz_t indent, bcore_sink* sink ){ return  0;} \
  static inline er_t xoico_p_expand_definition( const xoico_spect_s* __p, const xoico* o, sz_t indent, bcore_sink* sink ) { assert( __p->expand_definition ); return __p->expand_definition( o, indent, sink ); } \
  static inline er_t xoico_a_expand_definition( const xoico* o, sz_t indent, bcore_sink* sink ) { const xoico_spect_s* p = xoico_spect_s_get_aware( o ); assert( p->expand_definition ); return p->expand_definition( o, indent, sink ); } \
  static inline bl_t xoico_p_defines_expand_definition( const xoico_spect_s* __p ) { return true; } \
  static inline bl_t xoico_a_defines_expand_definition( const xoico* o ) { return true; } \
  static inline er_t xoico_expand_definition_default( const xoico* o, sz_t indent, bcore_sink* sink ){ return  0;} \
  static inline er_t xoico_p_expand_init1( const xoico_spect_s* __p, const xoico* o, sz_t indent, bcore_sink* sink ) { assert( __p->expand_init1 ); return __p->expand_init1( o, indent, sink ); } \
  static inline er_t xoico_a_expand_init1( const xoico* o, sz_t indent, bcore_sink* sink ) { const xoico_spect_s* p = xoico_spect_s_get_aware( o ); assert( p->expand_init1 ); return p->expand_init1( o, indent, sink ); } \
  static inline bl_t xoico_p_defines_expand_init1( const xoico_spect_s* __p ) { return true; } \
  static inline bl_t xoico_a_defines_expand_init1( const xoico* o ) { return true; } \
  static inline er_t xoico_expand_init1_default( const xoico* o, sz_t indent, bcore_sink* sink ){ return  0;}

/**********************************************************************************************************************/
// source: xoico_name.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_name

#define TYPEOF_xoico_name 0x6D4CB7095C7D7E85ull
#define TYPEOF_xoico_name_spect_s 0x50023928F2D819A1ull
#define TYPEOF_xoico_name_s 0x72C1E17E15481547ull
#define BETH_EXPAND_ITEM_xoico_name_s \
  BCORE_DECLARE_OBJECT( xoico_name_s ) \
  { \
      aware_t _; \
      tp_t name; \
      xoico_group_s* group; \
      bcore_source_point_s source_point; \
  }; \
  er_t xoico_name_s_parse( xoico_name_s* o, bcore_source* source ); \
  tp_t xoico_name_s_get_hash( const xoico_name_s* o ); \
  sc_t xoico_name_s_get_global_name_sc( const xoico_name_s* o ); \
  er_t xoico_name_s_expand_declaration( const xoico_name_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_name_s_expand_init1( const xoico_name_s* o, sz_t indent, bcore_sink* sink );
#define BETH_EXPAND_GROUP_xoico_name \
  BCORE_FORWARD_OBJECT( xoico_name ); \
  BCORE_FORWARD_OBJECT( xoico_name_s ); \
  XOILA_DECLARE_SPECT( xoico_name ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( xoico_name ) \
  BETH_EXPAND_ITEM_xoico_name_s

/**********************************************************************************************************************/
// source: xoico_forward.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_forward

#define TYPEOF_xoico_forward 0x245CC36E5CE3FCEBull
#define TYPEOF_xoico_forward_spect_s 0x44F73E970000ACCBull
#define TYPEOF_xoico_forward_s 0x67CE6DD302FEC85Dull
#define BETH_EXPAND_ITEM_xoico_forward_s \
  BCORE_DECLARE_OBJECT( xoico_forward_s ) \
  { \
      aware_t _; \
      st_s name; \
      xoico_group_s* group; \
      bcore_source_point_s source_point; \
  }; \
  er_t xoico_forward_s_parse( xoico_forward_s* o, bcore_source* source ); \
  tp_t xoico_forward_s_get_hash( const xoico_forward_s* o ); \
  static inline sc_t xoico_forward_s_get_global_name_sc( const xoico_forward_s* o ); \
  er_t xoico_forward_s_expand_declaration( const xoico_forward_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_forward_s_expand_forward( const xoico_forward_s* o, sz_t indent, bcore_sink* sink ); \
  static inline er_t xoico_forward_s_expand_init1( const xoico_forward_s* o, sz_t indent, bcore_sink* sink ); \
  static inline sc_t xoico_forward_s_get_global_name_sc( const xoico_forward_s* o ){ return  o->name.sc;} \
  static inline er_t xoico_forward_s_expand_init1( const xoico_forward_s* o, sz_t indent, bcore_sink* sink ){ return  0;}
#define BETH_EXPAND_GROUP_xoico_forward \
  BCORE_FORWARD_OBJECT( xoico_forward ); \
  BCORE_FORWARD_OBJECT( xoico_forward_s ); \
  XOILA_DECLARE_SPECT( xoico_forward ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( xoico_forward ) \
  BETH_EXPAND_ITEM_xoico_forward_s

/**********************************************************************************************************************/
// source: xoico_typespec.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_typespec

#define TYPEOF_xoico_typespec 0x4DA483D36BB5ED71ull
#define TYPEOF_xoico_typespec_spect_s 0xE434F73B98EB762Dull
#define TYPEOF_type_deduce 0xA6FBF003A76CC00Eull
#define TYPEOF_type_object 0x213393BEF2495D15ull
#define TYPEOF_xoico_typespec_s 0x9BEEEFCA6BCF163Bull
#define BETH_EXPAND_ITEM_xoico_typespec_s \
  BCORE_DECLARE_OBJECT( xoico_typespec_s ) \
  { \
      aware_t _; \
      tp_t type; \
      sz_t indirection; \
      bl_t flag_const; \
      bl_t flag_static; \
      bl_t flag_volatile; \
      bl_t flag_restrict; \
      bl_t flag_keep; \
      bl_t flag_addressable; \
  }; \
  tp_t xoico_typespec_s_get_hash( const xoico_typespec_s* o ); \
  er_t xoico_typespec_s_parse( xoico_typespec_s* o, xoico_group_s* group, bcore_source* source ); \
  er_t xoico_typespec_s_relent( xoico_typespec_s* o, xoico_group_s* group, tp_t tp_obj_type ); \
  er_t xoico_typespec_s_expand( const xoico_typespec_s* o, xoico_group_s* group, sc_t sc_obj_type, bcore_sink* sink ); \
  bl_t xoico_typespec_s_converts_to( const xoico_typespec_s* o, const xoico_typespec_s* b ); \
  void xoico_typespec_s_reset( xoico_typespec_s* o );
#define BETH_EXPAND_GROUP_xoico_typespec \
  BCORE_FORWARD_OBJECT( xoico_typespec ); \
  BCORE_FORWARD_OBJECT( xoico_typespec_s ); \
  XOILA_DECLARE_SPECT( xoico_typespec ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( xoico_typespec ) \
  BETH_EXPAND_ITEM_xoico_typespec_s

/**********************************************************************************************************************/
// source: xoico_arg.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_arg

#define TYPEOF_xoico_arg 0x36BE6A9BF2DBEE36ull
#define TYPEOF_xoico_arg_spect_s 0xC866D39A7B993942ull
#define TYPEOF_xoico_arg_s 0xDE77C40AC671BCC8ull
#define BETH_EXPAND_ITEM_xoico_arg_s \
  BCORE_DECLARE_OBJECT( xoico_arg_s ) \
  { \
      aware_t _; \
      xoico_group_s* group; \
      bcore_source_point_s source_point; \
      xoico_typespec_s typespec; \
      tp_t name; \
  }; \
  er_t xoico_arg_s_parse( xoico_arg_s* o, bcore_source* source ); \
  tp_t xoico_arg_s_get_hash( const xoico_arg_s* o ); \
  er_t xoico_arg_s_relent( xoico_arg_s* o, tp_t tp_obj_type ); \
  er_t xoico_arg_s_expand( const xoico_arg_s* o, sc_t sc_obj_type, bcore_sink* sink ); \
  er_t xoico_arg_s_expand_name( const xoico_arg_s* o, bcore_sink* sink );
#define BETH_EXPAND_GROUP_xoico_arg \
  BCORE_FORWARD_OBJECT( xoico_arg ); \
  BCORE_FORWARD_OBJECT( xoico_arg_s ); \
  XOILA_DECLARE_SPECT( xoico_arg ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( xoico_arg ) \
  BETH_EXPAND_ITEM_xoico_arg_s

/**********************************************************************************************************************/
// source: xoico_args.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_args

#define TYPEOF_xoico_args 0xE17D6BFDABB5DF3Full
#define TYPEOF_xoico_args_spect_s 0xC9AF8F9976CF18EFull
#define TYPEOF_xoico_args_s 0x40F4054E83F33D09ull
#define BETH_EXPAND_ITEM_xoico_args_s \
  BCORE_DECLARE_OBJECT( xoico_args_s ) \
  { \
      aware_t _; \
      BCORE_ARRAY_DYN_SOLID_STATIC_S( xoico_arg_s, ); \
      xoico_group_s* group; \
  }; \
  static inline er_t xoico_args_s_parse( xoico_args_s* o, bcore_source* source ); \
  er_t xoico_args_s_append( xoico_args_s* o, bcore_source* source ); \
  er_t xoico_args_s_relent( xoico_args_s* o, tp_t tp_obj_type ); \
  er_t xoico_args_s_expand( const xoico_args_s* o, bl_t first, sc_t sc_obj_type, bcore_sink* sink ); \
  er_t xoico_args_s_expand_name( const xoico_args_s* o, bl_t first, bcore_sink* sink ); \
  tp_t xoico_args_s_get_hash( const xoico_args_s* o ); \
  static inline xoico_args_s* xoico_args_s_set_space( xoico_args_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_xoico_args_s, ( bcore_array* )o, size ); return o; } \
  static inline xoico_args_s* xoico_args_s_set_size( xoico_args_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_xoico_args_s, ( bcore_array* )o, size ); return o; } \
  static inline xoico_args_s* xoico_args_s_clear( xoico_args_s* o ) { bcore_array_t_set_space( TYPEOF_xoico_args_s, ( bcore_array* )o, 0 ); return o; } \
  static inline xoico_arg_s* xoico_args_s_push_c( xoico_args_s* o, const xoico_arg_s* v ) { bcore_array_t_push( TYPEOF_xoico_args_s, ( bcore_array* )o, sr_twc( TYPEOF_xoico_arg_s, v ) ); return &o->data[ o->size - 1 ]; } \
  static inline xoico_arg_s* xoico_args_s_push_d( xoico_args_s* o,       xoico_arg_s* v ) { bcore_array_t_push( TYPEOF_xoico_args_s, ( bcore_array* )o, sr_tsd( TYPEOF_xoico_arg_s, v ) ); return &o->data[ o->size - 1 ]; } \
  static inline xoico_arg_s* xoico_args_s_push( xoico_args_s* o ) \
  { \
      bcore_array_t_push( TYPEOF_xoico_args_s, ( bcore_array* )o, sr_null() ); \
      return &o->data[ o->size - 1 ]; \
  } \
  static inline er_t xoico_args_s_parse( xoico_args_s* o, bcore_source* source ){ xoico_args_s_clear( o); return  xoico_args_s_append(o,source );}
#define BETH_EXPAND_GROUP_xoico_args \
  BCORE_FORWARD_OBJECT( xoico_args ); \
  BCORE_FORWARD_OBJECT( xoico_args_s ); \
  XOILA_DECLARE_SPECT( xoico_args ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( xoico_args ) \
  BETH_EXPAND_ITEM_xoico_args_s

/**********************************************************************************************************************/
// source: xoico_signature.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_signature

#define TYPEOF_xoico_signature 0x53D29DD556C884CCull
#define TYPEOF_xoico_signature_spect_s 0x53999B11F7357C04ull
#define TYPEOF_xoico_signature_s 0xDCE5A3AFBCD17B0Eull
#define BETH_EXPAND_ITEM_xoico_signature_s \
  BCORE_DECLARE_OBJECT( xoico_signature_s ) \
  { \
      aware_t _; \
      tp_t name; \
      tp_t global_name; \
      xoico_typespec_s typespec_ret; \
      xoico_args_s args; \
      tp_t arg_o; \
      xoico_group_s* group; \
      xoico_stamp_s* stamp; \
      bcore_source_point_s source_point; \
  }; \
  er_t xoico_signature_s_parse( xoico_signature_s* o, bcore_source* source ); \
  tp_t xoico_signature_s_get_hash( const xoico_signature_s* o ); \
  sc_t xoico_signature_s_get_global_name_sc( const xoico_signature_s* o ); \
  er_t xoico_signature_s_relent( xoico_signature_s* o, tp_t tp_obj_type ); \
  er_t xoico_signature_s_expand_declaration( const xoico_signature_s* o, const xoico_stamp_s* stamp, sc_t sc_func_name, sz_t indent, bcore_sink* sink );
#define BETH_EXPAND_GROUP_xoico_signature \
  BCORE_FORWARD_OBJECT( xoico_signature ); \
  BCORE_FORWARD_OBJECT( xoico_signature_s ); \
  XOILA_DECLARE_SPECT( xoico_signature ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( xoico_signature ) \
  BETH_EXPAND_ITEM_xoico_signature_s

/**********************************************************************************************************************/
// source: xoico_body.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_body

#define TYPEOF_xoico_body 0x3F9760E55C8626DAull
#define TYPEOF_xoico_body_spect_s 0x5B466E06B6B28186ull
#define TYPEOF_xoico_body_code_s 0x65495B39D833B530ull
#define BETH_EXPAND_ITEM_xoico_body_code_s \
  BCORE_DECLARE_OBJECT( xoico_body_code_s ) \
  { \
      aware_t _; \
      bl_t single_line; \
      tp_t hash_source; \
      bcore_source_point_s source_point; \
      xoico_group_s* group; \
      xoico_stamp_s* stamp; \
  }; \
  er_t xoico_body_code_s_parse( xoico_body_code_s* o, bcore_source* source ); \
  tp_t xoico_body_code_s_get_hash( const xoico_body_code_s* o );
#define TYPEOF_xoico_body_s 0x12DC29D312AD56E4ull
#define BETH_EXPAND_ITEM_xoico_body_s \
  BCORE_DECLARE_OBJECT( xoico_body_s ) \
  { \
      aware_t _; \
      st_s name; \
      st_s global_name; \
      xoico_body_code_s* code; \
      bl_t go_inline; \
      bcore_source_point_s source_point; \
      xoico_group_s* group; \
      xoico_stamp_s* stamp; \
  }; \
  static inline sc_t xoico_body_s_get_global_name_sc( const xoico_body_s* o ); \
  static inline er_t xoico_body_s_finalize( xoico_body_s* o ); \
  er_t xoico_body_s_set_group( xoico_body_s* o, xoico_group_s* group ); \
  er_t xoico_body_s_set_stamp( xoico_body_s* o, xoico_stamp_s* stamp ); \
  tp_t xoico_body_s_get_hash( const xoico_body_s* o ); \
  er_t xoico_body_s_parse_expression( xoico_body_s* o, bcore_source* source ); \
  er_t xoico_body_s_parse( xoico_body_s* o, bcore_source* source ); \
  er_t xoico_body_s_expand( const xoico_body_s* o, const xoico_signature_s* signature, sz_t indent, bcore_sink* sink ); \
  static inline sc_t xoico_body_s_get_global_name_sc( const xoico_body_s* o ){ return  o->global_name.sc;} \
  static inline er_t xoico_body_s_finalize( xoico_body_s* o ){ return  0;}
#define BETH_EXPAND_GROUP_xoico_body \
  BCORE_FORWARD_OBJECT( xoico_body ); \
  BCORE_FORWARD_OBJECT( xoico_body_code_s ); \
  BCORE_FORWARD_OBJECT( xoico_body_s ); \
  XOILA_DECLARE_SPECT( xoico_body ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( xoico_body ) \
  BETH_EXPAND_ITEM_xoico_body_code_s \
  BETH_EXPAND_ITEM_xoico_body_s

/**********************************************************************************************************************/
// source: xoico_feature.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_feature

#define TYPEOF_xoico_feature 0xBA3331D07ECB3518ull
#define TYPEOF_xoico_feature_spect_s 0xA54B211C161855E0ull
#define TYPEOF_xoico_feature_s 0x320F5368E957D0A2ull
#define BETH_EXPAND_ITEM_xoico_feature_s \
  BCORE_DECLARE_OBJECT( xoico_feature_s ) \
  { \
      aware_t _; \
      xoico_signature_s signature; \
      xoico_func_s* func_a; \
      xoico_func_s* func_a_defines; \
      xoico_func_s* func_t; \
      xoico_func_s* func_t_defines; \
      st_s st_default_func_name; \
      xoico_body_s* default_body; \
      bl_t strict; \
      bl_t flag_p; \
      bl_t flag_t; \
      bl_t flag_a; \
      bl_t flag_r; \
      bl_t expandable; \
      xoico_group_s* group; \
      bcore_source_point_s source_point; \
  }; \
  sc_t xoico_feature_s_get_global_name_sc( const xoico_feature_s* o ); \
  tp_t xoico_feature_s_get_hash( const xoico_feature_s* o ); \
  er_t xoico_feature_s_parse( xoico_feature_s* o, bcore_source* source ); \
  er_t xoico_feature_s_expand_indef_typedef( const xoico_feature_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_feature_s_expand_spect_declaration( const xoico_feature_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_feature_s_expand_spect_definition( const xoico_feature_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_feature_s_expand_indef_declaration( const xoico_feature_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_feature_s_expand_definition( const xoico_feature_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_feature_s_expand_init1( const xoico_feature_s* o, sz_t indent, bcore_sink* sink );
#define BETH_EXPAND_GROUP_xoico_feature \
  BCORE_FORWARD_OBJECT( xoico_feature ); \
  BCORE_FORWARD_OBJECT( xoico_feature_s ); \
  XOILA_DECLARE_SPECT( xoico_feature ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( xoico_feature ) \
  BETH_EXPAND_ITEM_xoico_feature_s

/**********************************************************************************************************************/
// source: xoico_func.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_func

#define TYPEOF_xoico_func 0x18E354C70B63E0D0ull
#define TYPEOF_xoico_func_spect_s 0xE66C0E41140B9DF8ull
#define TYPEOF_xoico_func_s 0xA748B4C2243B074Aull
#define BETH_EXPAND_ITEM_xoico_func_s \
  BCORE_DECLARE_OBJECT( xoico_func_s ) \
  { \
      aware_t _; \
      tp_t name; \
      tp_t global_name; \
      tp_t signature_global_name; \
      st_s flect_decl; \
      bl_t expandable; \
      bl_t overloadable; \
      xoico_body_s* body; \
      tp_t pre_hash; \
      xoico_signature_s* signature; \
      xoico_group_s* group; \
      xoico_stamp_s* stamp; \
      bcore_source_point_s source_point; \
  }; \
  tp_t xoico_func_s_get_hash( const xoico_func_s* o ); \
  er_t xoico_func_s_set_global_name( xoico_func_s* o ); \
  er_t xoico_func_s_parse( xoico_func_s* o, bcore_source* source ); \
  bl_t xoico_func_s_registerable( const xoico_func_s* o ); \
  er_t xoico_func_s_finalize( xoico_func_s* o ); \
  er_t xoico_func_s_expand_forward( const xoico_func_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_func_s_expand_declaration( const xoico_func_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_func_s_expand_definition( const xoico_func_s* o, sz_t indent, bcore_sink* sink );
#define BETH_EXPAND_GROUP_xoico_func \
  BCORE_FORWARD_OBJECT( xoico_func ); \
  BCORE_FORWARD_OBJECT( xoico_func_s ); \
  XOILA_DECLARE_SPECT( xoico_func ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( xoico_func ) \
  BETH_EXPAND_ITEM_xoico_func_s

/**********************************************************************************************************************/
// source: xoico_funcs.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_funcs

#define TYPEOF_xoico_funcs 0xAE29B1385AB6B4F9ull
#define TYPEOF_xoico_funcs_spect_s 0x6E611DE052C94BF5ull
#define TYPEOF_xoico_funcs_s 0x292F82E3F2BEA6D3ull
#define BETH_EXPAND_ITEM_xoico_funcs_s \
  BCORE_DECLARE_OBJECT( xoico_funcs_s ) \
  { \
      aware_t _; \
      BCORE_ARRAY_DYN_LINK_STATIC_S( xoico_func_s, ); \
  }; \
  sz_t xoico_funcs_s_get_index_from_signature_global_name( const xoico_funcs_s* o, tp_t signature_global_name ); \
  bl_t xoico_funcs_s_exists_from_signature_global_name( const xoico_funcs_s* o, tp_t signature_global_name ); \
  sz_t xoico_funcs_s_get_index_from_name( const xoico_funcs_s* o, tp_t name ); \
  bl_t xoico_funcs_s_exists_from_name( const xoico_funcs_s* o, tp_t name ); \
  xoico_func_s* xoico_funcs_s_get_func_from_signature_global_name( const xoico_funcs_s* o, tp_t signature_global_name ); \
  xoico_func_s* xoico_funcs_s_get_func_from_name( const xoico_funcs_s* o, tp_t name ); \
  er_t xoico_funcs_s_replace_fork( xoico_funcs_s* o, sz_t idx, xoico_func_s* func ); \
  er_t xoico_funcs_s_push_d( xoico_funcs_s* o, xoico_func_s* func ); \
  tp_t xoico_funcs_s_get_hash( const xoico_funcs_s* o );
#define BETH_EXPAND_GROUP_xoico_funcs \
  BCORE_FORWARD_OBJECT( xoico_funcs ); \
  BCORE_FORWARD_OBJECT( xoico_funcs_s ); \
  XOILA_DECLARE_SPECT( xoico_funcs ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( xoico_funcs ) \
  BETH_EXPAND_ITEM_xoico_funcs_s

/**********************************************************************************************************************/
// source: xoico_group.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_group

#define TYPEOF_xoico_group 0xF9A247075F113FF9ull
#define TYPEOF_xoico_group_spect_s 0x3DE6C1C7D3A336F5ull
#define TYPEOF_xoico_group_source_stack_s 0x753CECC8CE8A05B2ull
#define BETH_EXPAND_ITEM_xoico_group_source_stack_s \
  BCORE_DECLARE_OBJECT( xoico_group_source_stack_s ) \
  { \
      aware_t _; \
      BCORE_ARRAY_DYN_LINK_STATIC_S( bcore_source, ); \
  }; \
  static inline xoico_group_source_stack_s* xoico_group_source_stack_s_set_space( xoico_group_source_stack_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_xoico_group_source_stack_s, ( bcore_array* )o, size ); return o; } \
  static inline xoico_group_source_stack_s* xoico_group_source_stack_s_set_size( xoico_group_source_stack_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_xoico_group_source_stack_s, ( bcore_array* )o, size ); return o; } \
  static inline xoico_group_source_stack_s* xoico_group_source_stack_s_clear( xoico_group_source_stack_s* o ) { bcore_array_t_set_space( TYPEOF_xoico_group_source_stack_s, ( bcore_array* )o, 0 ); return o; } \
  static inline bcore_source* xoico_group_source_stack_s_push_c( xoico_group_source_stack_s* o, const bcore_source* v ) { bcore_array_t_push( TYPEOF_xoico_group_source_stack_s, ( bcore_array* )o, sr_awc( v ) ); return o->data[ o->size - 1 ]; } \
  static inline bcore_source* xoico_group_source_stack_s_push_d( xoico_group_source_stack_s* o,       bcore_source* v ) { bcore_array_t_push( TYPEOF_xoico_group_source_stack_s, ( bcore_array* )o, sr_asd( v ) ); return o->data[ o->size - 1 ]; } \
  static inline bcore_source* xoico_group_source_stack_s_push_t( xoico_group_source_stack_s* o, tp_t t ) \
  { \
      bcore_trait_assert_satisfied_type( TYPEOF_bcore_source, t ); \
      bcore_array_t_push( TYPEOF_xoico_group_source_stack_s, ( bcore_array* )o, sr_t_create( t ) ); \
      return o->data[ o->size - 1 ]; \
  }
#define TYPEOF_xoico_group_s 0x0C561A9D047FE9D3ull
#define BETH_EXPAND_ITEM_xoico_group_s \
  BCORE_DECLARE_OBJECT( xoico_group_s ) \
  { \
      aware_t _; \
      BCORE_ARRAY_DYN_LINK_STATIC_S( xoico, ); \
      xoico_group_s* parent; \
      bcore_arr_st_s includes_in_declaration; \
      bcore_arr_st_s includes_in_definition; \
      st_s st_name; \
      tp_t tp_name; \
      st_s trait_name; \
      tp_t pre_hash; \
      tp_t beta; \
      bl_t expandable; \
      bl_t retrievable; \
      bl_t short_spect_name; \
      xoico_stamp_s* extending_stamp; \
      xoico_funcs_s funcs; \
      xoico_source_s* xoico_source; \
      xoico_compiler_s* compiler; \
      bcore_source_point_s source_point; \
      bcore_hmap_tpvd_s hmap_feature; \
  }; \
  static inline sc_t xoico_group_s_get_global_name_sc( const xoico_group_s* o ); \
  static inline tp_t xoico_group_s_get_global_name_tp( const xoico_group_s* o ); \
  er_t xoico_group_s_expand_setup( xoico_group_s* o ); \
  er_t xoico_group_s_push_item_d( xoico_group_s* o, xoico* item ); \
  tp_t xoico_group_s_get_hash( const xoico_group_s* o ); \
  st_s* xoico_group_s_create_spect_name( const xoico_group_s* o ); \
  er_t xoico_group_s_parse_name_recursive( xoico_group_s* o, st_s* name, bcore_source* source ); \
  er_t xoico_group_s_parse_name( xoico_group_s* o, st_s* name, bcore_source* source ); \
  er_t xoico_group_s_push_default_feature_from_sc( xoico_group_s* o, sc_t sc ); \
  er_t xoico_group_s_parse_func( xoico_group_s* o, bcore_source* source ); \
  er_t xoico_group_s_parse( xoico_group_s* o, bcore_source* source ); \
  er_t xoico_group_s_finalize( xoico_group_s* o ); \
  er_t xoico_group_s_expand_forward( const xoico_group_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_group_s_expand_spect_declaration( const xoico_group_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_group_s_expand_declaration( const xoico_group_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_group_s_expand_spect_definition( const xoico_group_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_group_s_expand_definition( const xoico_group_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_group_s_expand_init1( const xoico_group_s* o, sz_t indent, bcore_sink* sink ); \
  static inline sc_t xoico_group_s_get_global_name_sc( const xoico_group_s* o ){ return  o->st_name.sc;} \
  static inline tp_t xoico_group_s_get_global_name_tp( const xoico_group_s* o ){ return  o->tp_name;}
#define BETH_EXPAND_GROUP_xoico_group \
  BCORE_FORWARD_OBJECT( xoico_group ); \
  BCORE_FORWARD_OBJECT( xoico_group_source_stack_s ); \
  BCORE_FORWARD_OBJECT( xoico_group_s ); \
  XOILA_DECLARE_SPECT( xoico_group ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( xoico_group ) \
  BETH_EXPAND_ITEM_xoico_group_source_stack_s \
  BETH_EXPAND_ITEM_xoico_group_s

/**********************************************************************************************************************/
// source: xoico_stamp.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_stamp

#define TYPEOF_xoico_stamp 0xB3846155856B6F65ull
#define TYPEOF_xoico_stamp_spect_s 0x032C3E7F429F6881ull
#define TYPEOF_xoico_stamp_s 0x012D01D78049FAE7ull
#define BETH_EXPAND_ITEM_xoico_stamp_s \
  BCORE_DECLARE_OBJECT( xoico_stamp_s ) \
  { \
      aware_t _; \
      st_s st_name; \
      tp_t tp_name; \
      st_s st_trait_name; \
      bl_t is_aware; \
      st_s* self_source; \
      bcore_self_s* self; \
      xoico_funcs_s funcs; \
      xoico_group_s* group; \
      bcore_source_point_s source_point; \
  }; \
  tp_t xoico_stamp_s_get_hash( const xoico_stamp_s* o ); \
  sc_t xoico_stamp_s_get_global_name_sc( const xoico_stamp_s* o ); \
  static inline tp_t xoico_stamp_s_get_global_name_tp( const xoico_stamp_s* o ); \
  er_t xoico_stamp_s_finalize( xoico_stamp_s* o ); \
  er_t xoico_stamp_s_expand_setup( xoico_stamp_s* o ); \
  er_t xoico_stamp_s_expand_declaration( const xoico_stamp_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_stamp_s_expand_forward( const xoico_stamp_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_stamp_s_expand_indef_declaration( const xoico_stamp_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_stamp_s_expand_definition( const xoico_stamp_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_stamp_s_expand_init1( const xoico_stamp_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_stamp_s_parse( xoico_stamp_s* o, bcore_source* source ); \
  er_t xoico_stamp_s_parse_func( xoico_stamp_s* o, bcore_source* source ); \
  er_t xoico_stamp_s_make_funcs_overloadable( xoico_stamp_s* o ); \
  er_t xoico_stamp_s_push_default_funcs( xoico_stamp_s* o ); \
  static inline tp_t xoico_stamp_s_get_global_name_tp( const xoico_stamp_s* o ){ return  o->tp_name;}
#define BETH_EXPAND_GROUP_xoico_stamp \
  BCORE_FORWARD_OBJECT( xoico_stamp ); \
  BCORE_FORWARD_OBJECT( xoico_stamp_s ); \
  XOILA_DECLARE_SPECT( xoico_stamp ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( xoico_stamp ) \
  BETH_EXPAND_ITEM_xoico_stamp_s

/**********************************************************************************************************************/
// source: xoico_nested_group.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_nested_group

#define TYPEOF_xoico_nested_group 0xD97B2B71D0DDAAC5ull
#define TYPEOF_xoico_nested_group_spect_s 0x801A0D33153815E1ull
#define TYPEOF_xoico_nested_group_s 0xB4EB0E2A56FB3087ull
#define BETH_EXPAND_ITEM_xoico_nested_group_s \
  BCORE_DECLARE_OBJECT( xoico_nested_group_s ) \
  { \
      aware_t _; \
      xoico_group_s* group; \
  }; \
  tp_t xoico_nested_group_s_get_hash( const xoico_nested_group_s* o ); \
  er_t xoico_nested_group_s_expand_forward( const xoico_nested_group_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_nested_group_s_expand_indef_declaration( const xoico_nested_group_s* o, sz_t indent, bcore_sink* sink );
#define BETH_EXPAND_GROUP_xoico_nested_group \
  BCORE_FORWARD_OBJECT( xoico_nested_group ); \
  BCORE_FORWARD_OBJECT( xoico_nested_group_s ); \
  XOILA_DECLARE_SPECT( xoico_nested_group ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( xoico_nested_group ) \
  BETH_EXPAND_ITEM_xoico_nested_group_s

/**********************************************************************************************************************/
// source: xoico_source.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_source

#define TYPEOF_xoico_source 0x3D61A07AD269C22Bull
#define TYPEOF_xoico_source_spect_s 0x229EEC3DD4BDE10Bull
#define TYPEOF_xoico_source_s 0x11BBCC12FF458D9Dull
#define BETH_EXPAND_ITEM_xoico_source_s \
  BCORE_DECLARE_OBJECT( xoico_source_s ) \
  { \
      aware_t _; \
      st_s name; \
      st_s path; \
      BCORE_ARRAY_DYN_LINK_STATIC_S( xoico_group_s, ); \
      xoico_target_s* target; \
  }; \
  er_t xoico_source_s_expand_setup( xoico_source_s* o ); \
  er_t xoico_source_s_push_d( xoico_source_s* o, xoico_group_s* group ); \
  tp_t xoico_source_s_get_hash( const xoico_source_s* o ); \
  er_t xoico_source_s_parse( xoico_source_s* o, bcore_source* source ); \
  er_t xoico_source_s_finalize( xoico_source_s* o ); \
  er_t xoico_source_s_expand_declaration( const xoico_source_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_source_s_expand_definition( const xoico_source_s* o, sz_t indent, bcore_sink* sink ); \
  er_t xoico_source_s_expand_init1( const xoico_source_s* o, sz_t indent, bcore_sink* sink );
#define BETH_EXPAND_GROUP_xoico_source \
  BCORE_FORWARD_OBJECT( xoico_source ); \
  BCORE_FORWARD_OBJECT( xoico_source_s ); \
  XOILA_DECLARE_SPECT( xoico_source ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( xoico_source ) \
  BETH_EXPAND_ITEM_xoico_source_s

/**********************************************************************************************************************/
// source: xoico_target.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_target

#define TYPEOF_xoico_target 0x01BDFA196985FBF7ull
#define TYPEOF_xoico_target_spect_s 0x2829234C11A6B927ull
#define TYPEOF_xoico_target_s 0x05A0ECAFABEA8CB1ull
#define BETH_EXPAND_ITEM_xoico_target_s \
  BCORE_DECLARE_OBJECT( xoico_target_s ) \
  { \
      aware_t _; \
      st_s name; \
      st_s path; \
      BCORE_ARRAY_DYN_LINK_STATIC_S( xoico_source_s, ); \
      st_s signal_handler_name; \
      bcore_arr_sz_s dependencies; \
      bl_t flag; \
      bl_t modified; \
      bl_t readonly; \
      st_s* target_h; \
      st_s* target_c; \
      xoico_cengine* cengine; \
      bcore_arr_st_s explicit_embeddings; \
      xoico_compiler_s* compiler; \
  }; \
  er_t xoico_target_s_parse( xoico_target_s* o, sc_t source_path ); \
  bl_t xoico_target_s_to_be_modified( const xoico_target_s* o ); \
  er_t xoico_target_s_finalize( xoico_target_s* o ); \
  er_t xoico_target_s_expand_setup( xoico_target_s* o ); \
  er_t xoico_target_s_expand_phase1( xoico_target_s* o, bl_t* p_modified ); \
  er_t xoico_target_s_expand_phase2( xoico_target_s* o, bl_t* p_modified ); \
  bl_t xoico_target_s_is_cyclic( xoico_target_s* o ); \
  er_t xoico_target_s_set_dependencies( xoico_target_s* o, const bcore_arr_sz_s* dependencies ); \
  void xoico_target_s_push_d( xoico_target_s* o, xoico_source_s* source );
#define BETH_EXPAND_GROUP_xoico_target \
  BCORE_FORWARD_OBJECT( xoico_target ); \
  BCORE_FORWARD_OBJECT( xoico_target_s ); \
  XOILA_DECLARE_SPECT( xoico_target ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( xoico_target ) \
  BETH_EXPAND_ITEM_xoico_target_s

/**********************************************************************************************************************/
// source: xoico_compiler.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_compiler

#define TYPEOF_xoico_compiler 0x4C5D845108D0785Full
#define TYPEOF_xoico_compiler_spect_s 0xF1BE54EC910CD90Full
#define TYPEOF_xoico_compiler_type_info_s 0x90F4E44AF2A1ADD7ull
#define BETH_EXPAND_ITEM_xoico_compiler_type_info_s \
  BCORE_DECLARE_OBJECT( xoico_compiler_type_info_s ) \
  { \
      aware_t _; \
      xoico_typespec_s typespec; \
      xoico* item; \
  };
#define TYPEOF_xoico_compiler_element_info_s 0x2B083548D3276FD7ull
#define BETH_EXPAND_ITEM_xoico_compiler_element_info_s \
  BCORE_DECLARE_OBJECT( xoico_compiler_element_info_s ) \
  { \
      aware_t _; \
      xoico_compiler_type_info_s type_info; \
      xoico_signature_s* signature; \
  };
#define TYPEOF_xoico_compiler_s 0xA7C0906C33CBFB69ull
#define BETH_EXPAND_ITEM_xoico_compiler_s \
  BCORE_DECLARE_OBJECT( xoico_compiler_s ) \
  { \
      aware_t _; \
      BCORE_ARRAY_DYN_LINK_STATIC_S( xoico_target_s, ); \
      bcore_life_s life; \
      bcore_hmap_tpvd_s hmap_group; \
      bcore_hmap_tpvd_s hmap_item; \
      bcore_hmap_tpvd_s hmap_func; \
      bcore_hmap_tp_s hmap_external_type; \
      bcore_hmap_name_s name_map; \
      tp_t target_pre_hash; \
      bl_t work_build_time_into_pre_hash; \
      bl_t register_non_feature_functions; \
      bl_t register_signatures; \
      bl_t overwrite_unsigned_target_files; \
      bl_t always_expand; \
      bl_t dry_run; \
      sz_t verbosity; \
  }; \
  static inline er_t xoico_compiler_s_register_external_type( xoico_compiler_s* o, tp_t type ); \
  static inline bl_t xoico_compiler_s_is_item( const xoico_compiler_s* o, tp_t name ); \
  static inline bl_t xoico_compiler_s_is_group( const xoico_compiler_s* o, tp_t name ); \
  static inline bl_t xoico_compiler_s_is_func( const xoico_compiler_s* o, tp_t name ); \
  bl_t xoico_compiler_s_is_type( const xoico_compiler_s* o, tp_t name ); \
  bl_t xoico_compiler_s_is_stamp( const xoico_compiler_s* o, tp_t name ); \
  bl_t xoico_compiler_s_is_signature( const xoico_compiler_s* o, tp_t name ); \
  bl_t xoico_compiler_s_is_signature_or_feature( const xoico_compiler_s* o, tp_t name ); \
  bl_t xoico_compiler_s_is_feature( const xoico_compiler_s* o, tp_t name ); \
  const xoico* xoico_compiler_s_get_const_item( const xoico_compiler_s* o, tp_t name ); \
  xoico* xoico_compiler_s_get_item( xoico_compiler_s* o, tp_t name ); \
  xoico_stamp_s* xoico_compiler_s_get_stamp( xoico_compiler_s* o, tp_t name ); \
  const xoico_feature_s* xoico_compiler_s_get_feature( const xoico_compiler_s* o, tp_t name ); \
  const xoico_signature_s* xoico_compiler_s_get_signature( const xoico_compiler_s* o, tp_t name ); \
  xoico_group_s* xoico_compiler_s_get_group( xoico_compiler_s* o, tp_t name ); \
  xoico_func_s* xoico_compiler_s_get_func( xoico_compiler_s* o, tp_t name ); \
  er_t xoico_compiler_s_life_a_push( xoico_compiler_s* o, bcore_inst* object ); \
  static inline bl_t xoico_compiler_s_update_required( xoico_compiler_s* o ); \
  static inline sz_t xoico_compiler_s_get_verbosity( const xoico_compiler_s* o ); \
  static inline tp_t xoico_compiler_s_entypeof( xoico_compiler_s* o, sc_t name ); \
  static inline sc_t xoico_compiler_s_nameof( const xoico_compiler_s* o, tp_t type ); \
  void xoico_compiler_s_init_x( xoico_compiler_s* o ); \
  void xoico_compiler_s_push_d( xoico_compiler_s* o, xoico_target_s* target ); \
  er_t xoico_compiler_s_register_group( xoico_compiler_s* o, const xoico_group_s* group ); \
  er_t xoico_compiler_s_register_item( xoico_compiler_s* o, const xoico* item, bcore_source* source ); \
  er_t xoico_compiler_s_register_func( xoico_compiler_s* o, const xoico_func_s* func ); \
  er_t xoico_compiler_s_check_overwrite( const xoico_compiler_s* o, sc_t file ); \
  er_t xoico_compiler_s_parse( xoico_compiler_s* o, sc_t target_name, sc_t source_path, sz_t* p_target_index ); \
  er_t xoico_compiler_s_finalize( xoico_compiler_s* o ); \
  er_t xoico_compiler_s_expand_setup( xoico_compiler_s* o ); \
  bl_t xoico_compiler_s_to_be_modified( const xoico_compiler_s* o ); \
  er_t xoico_compiler_s_expand( xoico_compiler_s* o, bl_t* p_modified ); \
  bl_t xoico_compiler_s_get_self( const xoico_compiler_s* o, tp_t type, const bcore_self_s** self ); \
  bl_t xoico_compiler_s_get_type_info( const xoico_compiler_s* o, tp_t type, xoico_compiler_type_info_s* info ); \
  bl_t xoico_compiler_s_get_type_element_info( const xoico_compiler_s* o, tp_t type, tp_t name, xoico_compiler_element_info_s* info ); \
  bl_t xoico_compiler_s_get_type_array_element_info( const xoico_compiler_s* o, tp_t type, xoico_compiler_element_info_s* info ); \
  er_t xoico_compiler_s_update_target_files( xoico_compiler_s* o, bl_t* p_modified ); \
  static inline er_t xoico_compiler_s_register_external_type( xoico_compiler_s* o, tp_t type ){ bcore_hmap_tp_s_set(&(o->hmap_external_type),type ); return  0;} \
  static inline bl_t xoico_compiler_s_is_item( const xoico_compiler_s* o, tp_t name ){ return  bcore_hmap_tpvd_s_exists(&(o->hmap_item),name );} \
  static inline bl_t xoico_compiler_s_is_group( const xoico_compiler_s* o, tp_t name ){ return  bcore_hmap_tpvd_s_exists(&(o->hmap_group),name );} \
  static inline bl_t xoico_compiler_s_is_func( const xoico_compiler_s* o, tp_t name ){ return  bcore_hmap_tpvd_s_exists(&(o->hmap_func),name );} \
  static inline bl_t xoico_compiler_s_update_required( xoico_compiler_s* o ){ return  xoico_compiler_s_to_be_modified(o);} \
  static inline sz_t xoico_compiler_s_get_verbosity( const xoico_compiler_s* o ){ return  o->verbosity;} \
  static inline tp_t xoico_compiler_s_entypeof( xoico_compiler_s* o, sc_t name ){ return  bcore_hmap_name_s_set_sc( &o->name_map,name );} \
  static inline sc_t xoico_compiler_s_nameof( const xoico_compiler_s* o, tp_t type ){ return  bcore_hmap_name_s_get_sc( &o->name_map,type );}
#define BETH_EXPAND_GROUP_xoico_compiler \
  BCORE_FORWARD_OBJECT( xoico_compiler ); \
  BCORE_FORWARD_OBJECT( xoico_compiler_type_info_s ); \
  BCORE_FORWARD_OBJECT( xoico_compiler_element_info_s ); \
  BCORE_FORWARD_OBJECT( xoico_compiler_s ); \
  bl_t xoico_compiler_is_signed( sc_t file ); \
  XOILA_DECLARE_SPECT( xoico_compiler ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( xoico_compiler ) \
  BETH_EXPAND_ITEM_xoico_compiler_type_info_s \
  BETH_EXPAND_ITEM_xoico_compiler_element_info_s \
  BETH_EXPAND_ITEM_xoico_compiler_s

/**********************************************************************************************************************/
// source: xoico_builder.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_builder

#define TYPEOF_xoico_builder 0x2BA8E9CE5EBF4289ull
#define TYPEOF_xoico_builder_spect_s 0x2AFB714AC45A87C5ull
#define TYPEOF_xoico_builder_arr_target_s 0x5DC3F6669CA63055ull
#define BETH_EXPAND_ITEM_xoico_builder_arr_target_s \
  BCORE_DECLARE_OBJECT( xoico_builder_arr_target_s ) \
  { \
      aware_t _; \
      BCORE_ARRAY_DYN_LINK_STATIC_S( xoico_builder_target_s, ); \
  }; \
  static inline xoico_builder_arr_target_s* xoico_builder_arr_target_s_set_space( xoico_builder_arr_target_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_xoico_builder_arr_target_s, ( bcore_array* )o, size ); return o; } \
  static inline xoico_builder_arr_target_s* xoico_builder_arr_target_s_set_size( xoico_builder_arr_target_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_xoico_builder_arr_target_s, ( bcore_array* )o, size ); return o; } \
  static inline xoico_builder_arr_target_s* xoico_builder_arr_target_s_clear( xoico_builder_arr_target_s* o ) { bcore_array_t_set_space( TYPEOF_xoico_builder_arr_target_s, ( bcore_array* )o, 0 ); return o; } \
  static inline xoico_builder_target_s* xoico_builder_arr_target_s_push_c( xoico_builder_arr_target_s* o, const xoico_builder_target_s* v ) { bcore_array_t_push( TYPEOF_xoico_builder_arr_target_s, ( bcore_array* )o, sr_twc( TYPEOF_xoico_builder_target_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline xoico_builder_target_s* xoico_builder_arr_target_s_push_d( xoico_builder_arr_target_s* o,       xoico_builder_target_s* v ) { bcore_array_t_push( TYPEOF_xoico_builder_arr_target_s, ( bcore_array* )o, sr_tsd( TYPEOF_xoico_builder_target_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline xoico_builder_target_s* xoico_builder_arr_target_s_push( xoico_builder_arr_target_s* o ) \
  { \
      bcore_array_t_push( TYPEOF_xoico_builder_arr_target_s, ( bcore_array* )o, sr_t_create( TYPEOF_xoico_builder_target_s ) ); \
      return o->data[ o->size - 1 ]; \
  }
#define TYPEOF_xoico_builder_target_s 0xDD8996604907B3C5ull
#define BETH_EXPAND_ITEM_xoico_builder_target_s \
  BCORE_DECLARE_OBJECT( xoico_builder_target_s ) \
  { \
      aware_t _; \
      st_s* name; \
      st_s* extension; \
      st_s* root_folder; \
      bl_t readonly; \
      bcore_arr_st_s dependencies; \
      bcore_arr_st_s sources; \
      st_s* signal_handler; \
      xoico_cengine* cengine; \
      xoico_compiler_s* compiler; \
      xoico_builder_target_s* parent_; \
      xoico_builder_target_s* root_; \
      xoico_builder_arr_target_s* dependencies_target_; \
      st_s full_path_; \
      sz_t target_index_; \
      bcore_hmap_tpvd_s* hmap_built_target_; \
  }; \
  void xoico_builder_target_s_source( xoico_builder_target_s* o, bcore_source* source ); \
  const xoico_builder_target_s* xoico_builder_target_s_name_match( const xoico_builder_target_s* o, sc_t name ); \
  void xoico_builder_target_s_push_target_index_to_arr( const xoico_builder_target_s* o, bcore_arr_sz_s* arr ); \
  er_t xoico_builder_target_s_load( xoico_builder_target_s* o, bl_t readonly, sc_t path ); \
  er_t xoico_builder_target_s_build( xoico_builder_target_s* o );
#define TYPEOF_xoico_builder_main_s 0x10B2EBC3A7C03BBDull
#define BETH_EXPAND_ITEM_xoico_builder_main_s \
  BCORE_DECLARE_OBJECT( xoico_builder_main_s ) \
  { \
      aware_t _; \
      xoico_compiler_s* compiler; \
      xoico_builder_target_s* target; \
  }; \
  static inline bl_t xoico_builder_main_s_update_required( const xoico_builder_main_s* o ); \
  er_t xoico_builder_main_s_set_dry_run( xoico_builder_main_s* o, bl_t v ); \
  bl_t xoico_builder_main_s_get_dry_run( const xoico_builder_main_s* o ); \
  er_t xoico_builder_main_s_set_always_expand( xoico_builder_main_s* o, bl_t v ); \
  bl_t xoico_builder_main_s_get_always_expand( const xoico_builder_main_s* o ); \
  er_t xoico_builder_main_s_set_overwrite_unsigned_target_files( xoico_builder_main_s* o, bl_t v ); \
  bl_t xoico_builder_main_s_get_overwrite_unsigned_target_files( const xoico_builder_main_s* o ); \
  er_t xoico_builder_main_s_build_from_file( xoico_builder_main_s* o, sc_t path ); \
  er_t xoico_builder_main_s_update( const xoico_builder_main_s* o ); \
  static inline bl_t xoico_builder_main_s_update_required( const xoico_builder_main_s* o ){ return  xoico_compiler_s_update_required(o->compiler);}
#define BETH_EXPAND_GROUP_xoico_builder \
  BCORE_FORWARD_OBJECT( xoico_builder ); \
  BCORE_FORWARD_OBJECT( xoico_builder_arr_target_s ); \
  BCORE_FORWARD_OBJECT( xoico_builder_target_s ); \
  BCORE_FORWARD_OBJECT( xoico_builder_main_s ); \
  XOILA_DECLARE_SPECT( xoico_builder ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( xoico_builder ) \
  BETH_EXPAND_ITEM_xoico_builder_arr_target_s \
  BETH_EXPAND_ITEM_xoico_builder_target_s \
  BETH_EXPAND_ITEM_xoico_builder_main_s

/**********************************************************************************************************************/
// source: xoico_cengine.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_cengine

#define TYPEOF_xoico_cengine 0x47E6F800E5D85E41ull
#define TYPEOF_xoico_cengine_spect_s 0x42E8CF600B8AE93Dull
#define BETH_EXPAND_GROUP_xoico_cengine \
  BCORE_FORWARD_OBJECT( xoico_cengine ); \
  typedef er_t (*xoico_cengine_translate)( const xoico_cengine* o, const xoico_body_s* body, const xoico_signature_s* signature, bcore_sink* sink ); \
  typedef tp_t (*xoico_cengine_get_hash)( const xoico_cengine* o ); \
  typedef bl_t (*xoico_cengine_is_reserved)( const xoico_cengine* o, tp_t tp_identifier ); \
  XOILA_DECLARE_SPECT( xoico_cengine ) \
  { \
      bcore_spect_header_s header; \
      xoico_cengine_translate translate; \
      xoico_cengine_get_hash get_hash; \
      xoico_cengine_is_reserved is_reserved; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( xoico_cengine ) \
  static inline er_t xoico_cengine_a_translate( const xoico_cengine* o, const xoico_body_s* body, const xoico_signature_s* signature, bcore_sink* sink ) { const xoico_cengine_spect_s* p = xoico_cengine_spect_s_get_aware( o ); assert( p->translate ); return p->translate( o, body, signature, sink ); } \
  static inline bl_t xoico_cengine_a_defines_translate( const xoico_cengine* o ) { return xoico_cengine_spect_s_get_aware( o )->translate != NULL; } \
  static inline tp_t xoico_cengine_a_get_hash( const xoico_cengine* o ) { const xoico_cengine_spect_s* p = xoico_cengine_spect_s_get_aware( o ); assert( p->get_hash ); return p->get_hash( o ); } \
  static inline bl_t xoico_cengine_a_defines_get_hash( const xoico_cengine* o ) { return true; } \
  static inline tp_t xoico_cengine_get_hash_default( const xoico_cengine* o ){ return  bcore_hash_a_get_tp( (bcore_hash*)o );} \
  static inline bl_t xoico_cengine_a_is_reserved( const xoico_cengine* o, tp_t tp_identifier ) { const xoico_cengine_spect_s* p = xoico_cengine_spect_s_get_aware( o ); assert( p->is_reserved ); return p->is_reserved( o, tp_identifier ); } \
  static inline bl_t xoico_cengine_a_defines_is_reserved( const xoico_cengine* o ) { return true; } \
  static inline bl_t xoico_cengine_is_reserved_default( const xoico_cengine* o, tp_t tp_identifier ){ return  false;}

/**********************************************************************************************************************/
// source: xoico_caleph.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_caleph

#define TYPEOF_xoico_caleph 0x63239F765351BC25ull
#define TYPEOF_xoico_caleph_spect_s 0x1C612FBD0B14E041ull
#define TYPEOF_xoico_caleph_s 0x7C8DA7784B2B40A7ull
#define BETH_EXPAND_ITEM_xoico_caleph_s \
  BCORE_DECLARE_OBJECT( xoico_caleph_s ) \
  { \
      aware_t _; \
      bl_t insert_source_reference; \
      xoico_args_s* args; \
      xoico_compiler_s* compiler; \
      xoico_group_s* group; \
      xoico_stamp_s* stamp; \
      tp_t obj_type; \
      bcore_hmap_name_s hmap_name; \
  }; \
  static inline tp_t xoico_caleph_s_entypeof( xoico_caleph_s* o, sc_t name ); \
  sc_t xoico_caleph_s_nameof( xoico_caleph_s* o, tp_t type ); \
  er_t xoico_caleph_s_translate( const xoico_caleph_s* o, const xoico_body_s* body, const xoico_signature_s* signature, bcore_sink* sink ); \
  static inline tp_t xoico_caleph_s_entypeof( xoico_caleph_s* o, sc_t name ){ return  bcore_hmap_name_s_set_sc( &o->hmap_name,name );}
#define BETH_EXPAND_GROUP_xoico_caleph \
  BCORE_FORWARD_OBJECT( xoico_caleph ); \
  BCORE_FORWARD_OBJECT( xoico_caleph_s ); \
  XOILA_DECLARE_SPECT( xoico_caleph ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( xoico_caleph ) \
  BETH_EXPAND_ITEM_xoico_caleph_s

/**********************************************************************************************************************/
// source: xoico_cbeth.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_cbeth

#define TYPEOF_xoico_cbeth 0xDE82C80C9103D0FAull
#define TYPEOF_xoico_cbeth_spect_s 0xF2FB105DEEA1EFA6ull
#define TYPEOF_xoico_cbeth_s 0x217EDBA13CE862C4ull
#define BETH_EXPAND_ITEM_xoico_cbeth_s \
  BCORE_DECLARE_OBJECT( xoico_cbeth_s ) \
  { \
      aware_t _; \
      sc_t obj_type; \
      xoico_args_s* args; \
      xoico_compiler_s* compiler; \
      xoico_cbeth_tn_stack_s stack; \
  }; \
  er_t xoico_cbeth_s_take_block( xoico_cbeth_s* o, bcore_source* source, bcore_sink* sink ); \
  er_t xoico_cbeth_s_take_block_body( xoico_cbeth_s* o, bcore_source* source, bcore_sink* sink ); \
  er_t xoico_cbeth_s_translate( const xoico_cbeth_s* o, const xoico_body_s* body, const xoico_signature_s* signature, bcore_sink* sink );
#define BETH_EXPAND_GROUP_xoico_cbeth \
  BCORE_FORWARD_OBJECT( xoico_cbeth ); \
  BCORE_FORWARD_OBJECT( xoico_cbeth_tn ); \
  BCORE_FORWARD_OBJECT( xoico_cbeth_s ); \
  XOILA_DECLARE_SPECT( xoico_cbeth ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( xoico_cbeth ) \
  BETH_EXPAND_GROUP_xoico_cbeth_tn \
  BETH_EXPAND_ITEM_xoico_cbeth_s

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_cbeth_tn

#define TYPEOF_xoico_cbeth_tn 0xD2EEFEFA7EDDAACDull
#define TYPEOF_xoico_cbeth_tn_spect_s 0x7486836198500909ull
#define TYPEOF_xoico_cbeth_tn_unit_s 0x16252D35C39CBBFAull
#define BETH_EXPAND_ITEM_xoico_cbeth_tn_unit_s \
  BCORE_DECLARE_OBJECT( xoico_cbeth_tn_unit_s ) \
  { \
      tp_t type; \
      tp_t name; \
      sz_t level; \
  };
#define TYPEOF_xoico_cbeth_tn_adl_s 0x5477B7042FFD2CCFull
#define BETH_EXPAND_ITEM_xoico_cbeth_tn_adl_s \
  BCORE_DECLARE_OBJECT( xoico_cbeth_tn_adl_s ) \
  { \
      aware_t _; \
      BCORE_ARRAY_DYN_LINK_STATIC_S( xoico_cbeth_tn_unit_s, ); \
  }; \
  static inline xoico_cbeth_tn_adl_s* xoico_cbeth_tn_adl_s_set_space( xoico_cbeth_tn_adl_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_xoico_cbeth_tn_adl_s, ( bcore_array* )o, size ); return o; } \
  static inline xoico_cbeth_tn_adl_s* xoico_cbeth_tn_adl_s_set_size( xoico_cbeth_tn_adl_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_xoico_cbeth_tn_adl_s, ( bcore_array* )o, size ); return o; } \
  static inline xoico_cbeth_tn_adl_s* xoico_cbeth_tn_adl_s_clear( xoico_cbeth_tn_adl_s* o ) { bcore_array_t_set_space( TYPEOF_xoico_cbeth_tn_adl_s, ( bcore_array* )o, 0 ); return o; } \
  static inline xoico_cbeth_tn_unit_s* xoico_cbeth_tn_adl_s_push_c( xoico_cbeth_tn_adl_s* o, const xoico_cbeth_tn_unit_s* v ) { bcore_array_t_push( TYPEOF_xoico_cbeth_tn_adl_s, ( bcore_array* )o, sr_twc( TYPEOF_xoico_cbeth_tn_unit_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline xoico_cbeth_tn_unit_s* xoico_cbeth_tn_adl_s_push_d( xoico_cbeth_tn_adl_s* o,       xoico_cbeth_tn_unit_s* v ) { bcore_array_t_push( TYPEOF_xoico_cbeth_tn_adl_s, ( bcore_array* )o, sr_tsd( TYPEOF_xoico_cbeth_tn_unit_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline xoico_cbeth_tn_unit_s* xoico_cbeth_tn_adl_s_push( xoico_cbeth_tn_adl_s* o ) \
  { \
      bcore_array_t_push( TYPEOF_xoico_cbeth_tn_adl_s, ( bcore_array* )o, sr_t_create( TYPEOF_xoico_cbeth_tn_unit_s ) ); \
      return o->data[ o->size - 1 ]; \
  }
#define TYPEOF_xoico_cbeth_tn_stack_s 0xAF005D3F7A0594F8ull
#define BETH_EXPAND_ITEM_xoico_cbeth_tn_stack_s \
  BCORE_DECLARE_OBJECT( xoico_cbeth_tn_stack_s ) \
  { \
      aware_t _; \
      xoico_cbeth_tn_adl_s adl; \
      bcore_hmap_name_s name_map; \
  }; \
  xoico_cbeth_tn_stack_s* xoico_cbeth_tn_stack_s_push( xoico_cbeth_tn_stack_s* o, tp_t type, tp_t name, sz_t level ); \
  xoico_cbeth_tn_stack_s* xoico_cbeth_tn_stack_s_push_sc( xoico_cbeth_tn_stack_s* o, sc_t type, sc_t name, sz_t level ); \
  xoico_cbeth_tn_stack_s* xoico_cbeth_tn_stack_s_pop( xoico_cbeth_tn_stack_s* o, sz_t level ); \
  tp_t xoico_cbeth_tn_stack_s_get_type( xoico_cbeth_tn_stack_s* o, tp_t name ); \
  sc_t xoico_cbeth_tn_stack_s_get_type_sc( xoico_cbeth_tn_stack_s* o, sc_t name ); \
  void xoico_cbeth_tn_stack_s_clear( xoico_cbeth_tn_stack_s* o ); \
  void xoico_cbeth_tn_stack_s_init_from_args( xoico_cbeth_tn_stack_s* o, sc_t obj_type, sc_t obj_name, const xoico_args_s* args );
#define BETH_EXPAND_GROUP_xoico_cbeth_tn \
  BCORE_FORWARD_OBJECT( xoico_cbeth_tn ); \
  BCORE_FORWARD_OBJECT( xoico_cbeth_tn_unit_s ); \
  BCORE_FORWARD_OBJECT( xoico_cbeth_tn_adl_s ); \
  BCORE_FORWARD_OBJECT( xoico_cbeth_tn_stack_s ); \
  XOILA_DECLARE_SPECT( xoico_cbeth_tn ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( xoico_cbeth_tn ) \
  BETH_EXPAND_ITEM_xoico_cbeth_tn_unit_s \
  BETH_EXPAND_ITEM_xoico_cbeth_tn_adl_s \
  BETH_EXPAND_ITEM_xoico_cbeth_tn_stack_s

/**********************************************************************************************************************/
// source: xoico_cgimel.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_cgimel

#define TYPEOF_xoico_cgimel 0xEB414677BBBC4D13ull
#define TYPEOF_xoico_cgimel_spect_s 0xE9A5B3268ED6C273ull
#define TYPEOF_static 0xC534816D6D11E97Bull
#define TYPEOF_volatile 0x9575F08FB5A48F0Dull
#define TYPEOF_cast 0xB55E7090E879494Eull
#define TYPEOF_xoico_cgimel_s 0x0A90671DA44B1BD5ull
#define BETH_EXPAND_ITEM_xoico_cgimel_s \
  BCORE_DECLARE_OBJECT( xoico_cgimel_s ) \
  { \
      aware_t _; \
      bl_t verbose; \
      bl_t insert_source_reference; \
      xoico_args_s* args; \
      xoico_compiler_s* compiler; \
      xoico_group_s* group; \
      xoico_stamp_s* stamp; \
      tp_t obj_type; \
      sz_t level; \
      xoico_cgimel_stack_s stack; \
      bcore_hmap_name_s hmap_name; \
  }; \
  static inline tp_t xoico_cgimel_s_entypeof( xoico_cgimel_s* o, sc_t name ); \
  sc_t xoico_cgimel_s_nameof( xoico_cgimel_s* o, tp_t type ); \
  void xoico_cgimel_s_inc_level( xoico_cgimel_s* o ); \
  void xoico_cgimel_s_dec_level( xoico_cgimel_s* o ); \
  void xoico_cgimel_s_push_typedecl( xoico_cgimel_s* o, const xoico_typespec_s* typespec, tp_t name ); \
  er_t xoico_cgimel_s_translate( const xoico_cgimel_s* o, const xoico_body_s* body, const xoico_signature_s* signature, bcore_sink* sink ); \
  static inline tp_t xoico_cgimel_s_entypeof( xoico_cgimel_s* o, sc_t name ){ return  bcore_hmap_name_s_set_sc( &o->hmap_name,name );}
#define BETH_EXPAND_GROUP_xoico_cgimel \
  BCORE_FORWARD_OBJECT( xoico_cgimel ); \
  BCORE_FORWARD_OBJECT( xoico_cgimel_stack ); \
  BCORE_FORWARD_OBJECT( xoico_cgimel_s ); \
  XOILA_DECLARE_SPECT( xoico_cgimel ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( xoico_cgimel ) \
  BETH_EXPAND_GROUP_xoico_cgimel_stack \
  BETH_EXPAND_ITEM_xoico_cgimel_s

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_cgimel_stack

#define TYPEOF_xoico_cgimel_stack 0x2049084FD79A2FCCull
#define TYPEOF_xoico_cgimel_stack_spect_s 0x9C573585D2AA8704ull
#define TYPEOF_xoico_cgimel_stack_unit_s 0xC30CE4D5C6041A25ull
#define BETH_EXPAND_ITEM_xoico_cgimel_stack_unit_s \
  BCORE_DECLARE_OBJECT( xoico_cgimel_stack_unit_s ) \
  { \
      sz_t level; \
      tp_t name; \
      xoico_typespec_s typespec; \
  };
#define TYPEOF_xoico_cgimel_stack_unit_adl_s 0x49CFBD5C09538C81ull
#define BETH_EXPAND_ITEM_xoico_cgimel_stack_unit_adl_s \
  BCORE_DECLARE_OBJECT( xoico_cgimel_stack_unit_adl_s ) \
  { \
      aware_t _; \
      BCORE_ARRAY_DYN_LINK_STATIC_S( xoico_cgimel_stack_unit_s, ); \
  }; \
  static inline xoico_cgimel_stack_unit_adl_s* xoico_cgimel_stack_unit_adl_s_set_space( xoico_cgimel_stack_unit_adl_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_xoico_cgimel_stack_unit_adl_s, ( bcore_array* )o, size ); return o; } \
  static inline xoico_cgimel_stack_unit_adl_s* xoico_cgimel_stack_unit_adl_s_set_size( xoico_cgimel_stack_unit_adl_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_xoico_cgimel_stack_unit_adl_s, ( bcore_array* )o, size ); return o; } \
  static inline xoico_cgimel_stack_unit_adl_s* xoico_cgimel_stack_unit_adl_s_clear( xoico_cgimel_stack_unit_adl_s* o ) { bcore_array_t_set_space( TYPEOF_xoico_cgimel_stack_unit_adl_s, ( bcore_array* )o, 0 ); return o; } \
  static inline xoico_cgimel_stack_unit_s* xoico_cgimel_stack_unit_adl_s_push_c( xoico_cgimel_stack_unit_adl_s* o, const xoico_cgimel_stack_unit_s* v ) { bcore_array_t_push( TYPEOF_xoico_cgimel_stack_unit_adl_s, ( bcore_array* )o, sr_twc( TYPEOF_xoico_cgimel_stack_unit_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline xoico_cgimel_stack_unit_s* xoico_cgimel_stack_unit_adl_s_push_d( xoico_cgimel_stack_unit_adl_s* o,       xoico_cgimel_stack_unit_s* v ) { bcore_array_t_push( TYPEOF_xoico_cgimel_stack_unit_adl_s, ( bcore_array* )o, sr_tsd( TYPEOF_xoico_cgimel_stack_unit_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline xoico_cgimel_stack_unit_s* xoico_cgimel_stack_unit_adl_s_push( xoico_cgimel_stack_unit_adl_s* o ) \
  { \
      bcore_array_t_push( TYPEOF_xoico_cgimel_stack_unit_adl_s, ( bcore_array* )o, sr_t_create( TYPEOF_xoico_cgimel_stack_unit_s ) ); \
      return o->data[ o->size - 1 ]; \
  }
#define TYPEOF_xoico_cgimel_stack_s 0xFC5E532B9F06DE0Eull
#define BETH_EXPAND_ITEM_xoico_cgimel_stack_s \
  BCORE_DECLARE_OBJECT( xoico_cgimel_stack_s ) \
  { \
      aware_t _; \
      xoico_cgimel_stack_unit_adl_s adl; \
  }; \
  static inline xoico_cgimel_stack_s* xoico_cgimel_stack_s_push_unit( xoico_cgimel_stack_s* o, const xoico_cgimel_stack_unit_s* unit ); \
  xoico_cgimel_stack_s* xoico_cgimel_stack_s_pop_level( xoico_cgimel_stack_s* o, sz_t level ); \
  const xoico_typespec_s* xoico_cgimel_stack_s_get_typespec( const xoico_cgimel_stack_s* o, tp_t name ); \
  static inline void xoico_cgimel_stack_s_clear( xoico_cgimel_stack_s* o ); \
  static inline xoico_cgimel_stack_s* xoico_cgimel_stack_s_push_unit( xoico_cgimel_stack_s* o, const xoico_cgimel_stack_unit_s* unit ){ xoico_cgimel_stack_unit_adl_s_push_c( &o->adl, unit );  return  o;} \
  static inline void xoico_cgimel_stack_s_clear( xoico_cgimel_stack_s* o ){ xoico_cgimel_stack_unit_adl_s_clear( &o->adl );}
#define BETH_EXPAND_GROUP_xoico_cgimel_stack \
  BCORE_FORWARD_OBJECT( xoico_cgimel_stack ); \
  BCORE_FORWARD_OBJECT( xoico_cgimel_stack_unit_s ); \
  BCORE_FORWARD_OBJECT( xoico_cgimel_stack_unit_adl_s ); \
  BCORE_FORWARD_OBJECT( xoico_cgimel_stack_s ); \
  XOILA_DECLARE_SPECT( xoico_cgimel_stack ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( xoico_cgimel_stack ) \
  BETH_EXPAND_ITEM_xoico_cgimel_stack_unit_s \
  BETH_EXPAND_ITEM_xoico_cgimel_stack_unit_adl_s \
  BETH_EXPAND_ITEM_xoico_cgimel_stack_s

/**********************************************************************************************************************/
// source: xoico_cdaleth.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_cdaleth

#define TYPEOF_xoico_cdaleth 0x8D0A417495C3CDF7ull
#define TYPEOF_xoico_cdaleth_spect_s 0x07E1CAC1B252CB27ull
#define TYPEOF_static 0xC534816D6D11E97Bull
#define TYPEOF_volatile 0x9575F08FB5A48F0Dull
#define TYPEOF_cast 0xB55E7090E879494Eull
#define TYPEOF_verbatim_C 0x7C0F5E2B3285120Dull
#define TYPEOF_keep 0x585D7CD75CF6F848ull
#define TYPEOF_scope 0xC1074FFBE7EFE44Bull
#define TYPEOF_scope_local 0xC7F69BF78D91B167ull
#define TYPEOF_scope_func 0x5E9151F1091C19BAull
#define TYPEOF_keep_func 0xA74182F52F6E64F7ull
#define TYPEOF_keep_block 0xD904ABF6228783B2ull
#define TYPEOF_fork 0xDD1D0D790C2F1881ull
#define TYPEOF_try 0x570AC119447423EEull
#define TYPEOF_if 0x08B73007B55C3E26ull
#define TYPEOF_else 0x7F2B6C605332DD30ull
#define TYPEOF_while 0xCE87A3885811296Eull
#define TYPEOF_do 0x08915907B53BB494ull
#define TYPEOF_for 0xDCB27818FED9DA90ull
#define TYPEOF_foreach 0x8AD09EA0575C3439ull
#define TYPEOF_switch 0xA5A87AC5B0B379B1ull
#define TYPEOF_case 0xB55E6190E8792FD1ull
#define TYPEOF_default 0xEBADA5168620C5FEull
#define TYPEOF_break 0x93B7591DEBC7CE38ull
#define TYPEOF_return 0xC5C7B983377CAD5Full
#define TYPEOF_xoico_cdaleth_s 0x9E808B0037072EB1ull
#define BETH_EXPAND_ITEM_xoico_cdaleth_s \
  BCORE_DECLARE_OBJECT( xoico_cdaleth_s ) \
  { \
      aware_t _; \
      bl_t verbose; \
      bl_t insert_source_reference; \
      xoico_args_s* args; \
      xoico_typespec_s* typespec_ret; \
      xoico_compiler_s* compiler; \
      xoico_group_s* group; \
      xoico_stamp_s* stamp; \
      tp_t obj_type; \
      sz_t level; \
      sz_t try_block_level; \
      xoico_cdaleth_stack_var_s stack_var; \
      xoico_cdaleth_stack_block_s stack_block; \
      bcore_hmap_name_s hmap_name; \
  }; \
  bl_t xoico_cdaleth_s_is_reserved( const xoico_cdaleth_s* o, tp_t tp_identifier ); \
  static inline tp_t xoico_cdaleth_s_entypeof( xoico_cdaleth_s* o, sc_t name ); \
  sc_t xoico_cdaleth_s_nameof( xoico_cdaleth_s* o, tp_t type ); \
  void xoico_cdaleth_s_init_level0( xoico_cdaleth_s* o ); \
  void xoico_cdaleth_s_inc_block( xoico_cdaleth_s* o ); \
  void xoico_cdaleth_s_dec_block( xoico_cdaleth_s* o ); \
  xoico_cdaleth_stack_block_unit_s* xoico_cdaleth_s_stack_block_get_top_unit( xoico_cdaleth_s* o ); \
  xoico_cdaleth_stack_block_unit_s* xoico_cdaleth_s_stack_block_get_bottom_unit( xoico_cdaleth_s* o ); \
  xoico_cdaleth_stack_block_unit_s* xoico_cdaleth_s_stack_block_get_level_unit( xoico_cdaleth_s* o, sz_t level ); \
  void xoico_cdaleth_s_push_typedecl( xoico_cdaleth_s* o, const xoico_typespec_s* typespec, tp_t name ); \
  static inline bl_t xoico_cdaleth_s_is_type( const xoico_cdaleth_s* o, tp_t name ); \
  static inline bl_t xoico_cdaleth_s_is_group( const xoico_cdaleth_s* o, tp_t name ); \
  static inline bl_t xoico_cdaleth_s_is_stamp( const xoico_cdaleth_s* o, tp_t name ); \
  static inline bl_t xoico_cdaleth_s_is_func( const xoico_cdaleth_s* o, tp_t name ); \
  static inline bl_t xoico_cdaleth_s_is_var( const xoico_cdaleth_s* o, tp_t name ); \
  static inline xoico_group_s* xoico_cdaleth_s_get_group( xoico_cdaleth_s* o, tp_t name ); \
  static inline xoico_stamp_s* xoico_cdaleth_s_get_stamp( xoico_cdaleth_s* o, tp_t name ); \
  static inline xoico_func_s* xoico_cdaleth_s_get_func( xoico_cdaleth_s* o, tp_t name ); \
  bl_t xoico_cdaleth_s_returns_a_value( const xoico_cdaleth_s* o ); \
  er_t xoico_cdaleth_s_parse( const xoico_cdaleth_s* o, bcore_source* source, sc_t format ); \
  er_t xoico_cdaleth_s_trans( const xoico_cdaleth_s* o, bcore_source* source, sc_t format, st_s* buf ); \
  tp_t xoico_cdaleth_s_get_identifier( xoico_cdaleth_s* o, bcore_source* source, bl_t take_from_source ); \
  er_t xoico_cdaleth_s_trans_identifier( xoico_cdaleth_s* o, bcore_source* source, st_s* buf, tp_t* tp_identifier ); \
  er_t xoico_cdaleth_s_trans_number_literal( xoico_cdaleth_s* o, bcore_source* source, st_s* buf ); \
  er_t xoico_cdaleth_s_trans_string_literal( xoico_cdaleth_s* o, bcore_source* source, st_s* buf ); \
  er_t xoico_cdaleth_s_trans_char_literal( xoico_cdaleth_s* o, bcore_source* source, st_s* buf ); \
  er_t xoico_cdaleth_s_trans_whitespace( xoico_cdaleth_s* o, bcore_source* source, st_s* buf ); \
  er_t xoico_cdaleth_s_trans_preprocessor( xoico_cdaleth_s* o, bcore_source* source, st_s* buf ); \
  tp_t xoico_cdaleth_s_trans_inert_operator( xoico_cdaleth_s* o, bcore_source* source, st_s* buf ); \
  er_t xoico_cdaleth_s_adapt_expression( xoico_cdaleth_s* o, bcore_source* source, const xoico_typespec_s* typespec_expr, const xoico_typespec_s* typespec_target, const st_s* expr, st_s* buf ); \
  er_t xoico_cdaleth_s_trans_function_args( xoico_cdaleth_s* o, bcore_source* source, const xoico_signature_s* signature, const st_s* buf_obj_expr, const xoico_typespec_s* typespec_obj_expr, st_s* buf_out ); \
  er_t xoico_cdaleth_s_trans_typespec_member( xoico_cdaleth_s* o, bcore_source* source, st_s* buf, const xoico_typespec_s* in_typespec, xoico_typespec_s* out_typespec ); \
  er_t xoico_cdaleth_s_trans_typespec_array_subscript( xoico_cdaleth_s* o, bcore_source* source, st_s* buf, const xoico_typespec_s* in_typespec, xoico_typespec_s* out_typespec ); \
  er_t xoico_cdaleth_s_trans_typespec_create( xoico_cdaleth_s* o, bcore_source* source, st_s* buf, const xoico_typespec_s* in_typespec, xoico_typespec_s* out_typespec ); \
  er_t xoico_cdaleth_s_trans_typespec_test_presence( xoico_cdaleth_s* o, bcore_source* source, st_s* buf, const xoico_typespec_s* in_typespec, xoico_typespec_s* out_typespec ); \
  er_t xoico_cdaleth_s_trans_typespec_attach( xoico_cdaleth_s* o, bcore_source* source, st_s* buf, const xoico_typespec_s* in_typespec, xoico_typespec_s* out_typespec ); \
  er_t xoico_cdaleth_s_trans_typespec_ternary_branch( xoico_cdaleth_s* o, bcore_source* source, st_s* buf, const xoico_typespec_s* in_typespec, xoico_typespec_s* out_typespec ); \
  er_t xoico_cdaleth_s_trans_typespec_expression( xoico_cdaleth_s* o, bcore_source* source, st_s* buf, const xoico_typespec_s* in_typespec, xoico_typespec_s* out_typespec ); \
  er_t xoico_cdaleth_s_trans_member( xoico_cdaleth_s* o, bcore_source* source, st_s* buf ); \
  er_t xoico_cdaleth_s_try_take_typespec( xoico_cdaleth_s* o, bcore_source* source, xoico_typespec_s* typespec, bl_t require_tractable_type, bl_t* success ); \
  er_t xoico_cdaleth_s_take_typespec( xoico_cdaleth_s* o, bcore_source* source, xoico_typespec_s* typespec, bl_t require_tractable_type ); \
  er_t xoico_cdaleth_s_push_typespec( xoico_cdaleth_s* o, const xoico_typespec_s* typespec, st_s* buf ); \
  er_t xoico_cdaleth_s_trans_type( xoico_cdaleth_s* o, bcore_source* source, st_s* buf, xoico_typespec_s* out_typespec ); \
  er_t xoico_cdaleth_s_trans_func( xoico_cdaleth_s* o, bcore_source* source, st_s* buf, xoico_typespec_s* out_typespec ); \
  er_t xoico_cdaleth_s_trans_ternary_branch( xoico_cdaleth_s* o, bcore_source* source, st_s* buf, xoico_typespec_s* out_typespec ); \
  er_t xoico_cdaleth_s_trans_bracket( xoico_cdaleth_s* o, bcore_source* source, st_s* buf, xoico_typespec_s* out_typespec ); \
  er_t xoico_cdaleth_s_trans_array_subscript( xoico_cdaleth_s* o, bcore_source* source, st_s* buf, xoico_typespec_s* out_typespec ); \
  er_t xoico_cdaleth_s_trans_expression( xoico_cdaleth_s* o, bcore_source* source, st_s* buf_out, xoico_typespec_s* out_typespec ); \
  er_t xoico_cdaleth_s_try_trans_declaration( xoico_cdaleth_s* o, bcore_source* source, st_s* buf_out, bl_t* success ); \
  er_t xoico_cdaleth_s_inspect_variable( xoico_cdaleth_s* o, bcore_source* source ); \
  er_t xoico_cdaleth_s_trans_statement_expression( xoico_cdaleth_s* o, bcore_source* source, st_s* buf ); \
  er_t xoico_cdaleth_s_trans_statement( xoico_cdaleth_s* o, bcore_source* source, st_s* buf ); \
  er_t xoico_cdaleth_s_trans_block_inside( xoico_cdaleth_s* o, bcore_source* source, st_s* buf_out ); \
  er_t xoico_cdaleth_s_trans_block( xoico_cdaleth_s* o, bcore_source* source, st_s* buf, bl_t is_break_ledge ); \
  er_t xoico_cdaleth_s_trans_statement_as_block( xoico_cdaleth_s* o, bcore_source* source, st_s* buf_out, bl_t is_break_ledge ); \
  er_t xoico_cdaleth_s_trans_block_inside_verbatim_c( xoico_cdaleth_s* o, bcore_source* source, st_s* buf ); \
  er_t xoico_cdaleth_s_setup( xoico_cdaleth_s* o, const xoico_body_s* body, const xoico_signature_s* signature ); \
  sz_t xoico_cdaleth_s_assess_indentation( bcore_source* source ); \
  void xoico_cdaleth_s_remove_indentation( st_s* buf, sz_t indentation ); \
  er_t xoico_cdaleth_s_translate( const xoico_cdaleth_s* o, const xoico_body_s* body, const xoico_signature_s* signature, bcore_sink* sink ); \
  bl_t xoico_cdaleth_s_is_builtin_func( const xoico_cdaleth_s* o, tp_t tp_identifier ); \
  er_t xoico_cdaleth_s_trans_builtin( xoico_cdaleth_s* o, tp_t tp_builtin, bcore_source* source, const st_s* buf_expr, const xoico_typespec_s* typespec_expr, st_s* buf_out, xoico_typespec_s* typespec_out ); \
  er_t xoico_cdaleth_s_trans_builtin_cast( xoico_cdaleth_s* o, bcore_source* source, const st_s* buf_expr, const xoico_typespec_s* typespec_expr, st_s* buf_out, xoico_typespec_s* typespec_out ); \
  er_t xoico_cdaleth_s_trans_builtin_scope( xoico_cdaleth_s* o, bcore_source* source, const st_s* buf_expr, const xoico_typespec_s* typespec_expr, st_s* buf_out, xoico_typespec_s* typespec_out ); \
  er_t xoico_cdaleth_s_trans_builtin_fork( xoico_cdaleth_s* o, bcore_source* source, const st_s* buf_expr, const xoico_typespec_s* typespec_expr, st_s* buf_out, xoico_typespec_s* typespec_out ); \
  er_t xoico_cdaleth_s_trans_builtin_try( xoico_cdaleth_s* o, bcore_source* source, const st_s* buf_expr, const xoico_typespec_s* typespec_expr, st_s* buf_out, xoico_typespec_s* typespec_out ); \
  bl_t xoico_cdaleth_s_is_control_name( const xoico_cdaleth_s* o, tp_t tp_identifier ); \
  er_t xoico_cdaleth_s_trans_control( xoico_cdaleth_s* o, tp_t tp_control, bcore_source* source, st_s* buf ); \
  er_t xoico_cdaleth_s_trans_control_for( xoico_cdaleth_s* o, bcore_source* source, st_s* buf ); \
  er_t xoico_cdaleth_s_trans_control_foreach( xoico_cdaleth_s* o, bcore_source* source, st_s* buf ); \
  er_t xoico_cdaleth_s_trans_control_if( xoico_cdaleth_s* o, bcore_source* source, st_s* buf ); \
  er_t xoico_cdaleth_s_trans_control_while( xoico_cdaleth_s* o, bcore_source* source, st_s* buf ); \
  er_t xoico_cdaleth_s_trans_control_do( xoico_cdaleth_s* o, bcore_source* source, st_s* buf ); \
  er_t xoico_cdaleth_s_trans_control_else( xoico_cdaleth_s* o, bcore_source* source, st_s* buf ); \
  er_t xoico_cdaleth_s_trans_control_switch( xoico_cdaleth_s* o, bcore_source* source, st_s* buf ); \
  er_t xoico_cdaleth_s_trans_control_case( xoico_cdaleth_s* o, bcore_source* source, st_s* buf ); \
  er_t xoico_cdaleth_s_trans_control_default( xoico_cdaleth_s* o, bcore_source* source, st_s* buf ); \
  er_t xoico_cdaleth_s_trans_control_break( xoico_cdaleth_s* o, bcore_source* source, st_s* buf ); \
  er_t xoico_cdaleth_s_trans_control_return( xoico_cdaleth_s* o, bcore_source* source, st_s* buf ); \
  static inline tp_t xoico_cdaleth_s_entypeof( xoico_cdaleth_s* o, sc_t name ){ return  bcore_hmap_name_s_set_sc(&(o->hmap_name),name );} \
  static inline bl_t xoico_cdaleth_s_is_type( const xoico_cdaleth_s* o, tp_t name ){ return  xoico_compiler_s_is_type(o->compiler,name );} \
  static inline bl_t xoico_cdaleth_s_is_group( const xoico_cdaleth_s* o, tp_t name ){ return  xoico_compiler_s_is_group(o->compiler,name );} \
  static inline bl_t xoico_cdaleth_s_is_stamp( const xoico_cdaleth_s* o, tp_t name ){ return  xoico_compiler_s_is_stamp(o->compiler,name );} \
  static inline bl_t xoico_cdaleth_s_is_func( const xoico_cdaleth_s* o, tp_t name ){ return  xoico_compiler_s_is_func(o->compiler,name );} \
  static inline bl_t xoico_cdaleth_s_is_var( const xoico_cdaleth_s* o, tp_t name ){ return  xoico_cdaleth_stack_var_s_exists(&(o->stack_var),name );} \
  static inline xoico_group_s* xoico_cdaleth_s_get_group( xoico_cdaleth_s* o, tp_t name ){ return  xoico_compiler_s_get_group(o->compiler,name );} \
  static inline xoico_stamp_s* xoico_cdaleth_s_get_stamp( xoico_cdaleth_s* o, tp_t name ){ return  xoico_compiler_s_get_stamp(o->compiler,name );} \
  static inline xoico_func_s* xoico_cdaleth_s_get_func( xoico_cdaleth_s* o, tp_t name ){ return  xoico_compiler_s_get_func(o->compiler,name );}
#define BETH_EXPAND_GROUP_xoico_cdaleth \
  BCORE_FORWARD_OBJECT( xoico_cdaleth ); \
  BCORE_FORWARD_OBJECT( xoico_cdaleth_stack_var ); \
  BCORE_FORWARD_OBJECT( xoico_cdaleth_stack_block ); \
  BCORE_FORWARD_OBJECT( xoico_cdaleth_s ); \
  XOILA_DECLARE_SPECT( xoico_cdaleth ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( xoico_cdaleth ) \
  BETH_EXPAND_GROUP_xoico_cdaleth_stack_var \
  BETH_EXPAND_GROUP_xoico_cdaleth_stack_block \
  BETH_EXPAND_ITEM_xoico_cdaleth_s

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_cdaleth_stack_var

#define TYPEOF_xoico_cdaleth_stack_var 0xFC261CACAFEB9CC6ull
#define TYPEOF_xoico_cdaleth_stack_var_spect_s 0xA0BF1284603402D2ull
#define TYPEOF_xoico_cdaleth_stack_var_unit_s 0x65EB5514FBC27E3Bull
#define BETH_EXPAND_ITEM_xoico_cdaleth_stack_var_unit_s \
  BCORE_DECLARE_OBJECT( xoico_cdaleth_stack_var_unit_s ) \
  { \
      aware_t _; \
      sz_t level; \
      tp_t name; \
      xoico_typespec_s typespec; \
  };
#define TYPEOF_xoico_cdaleth_stack_var_unit_adl_s 0x28B0FEF7ED9C9673ull
#define BETH_EXPAND_ITEM_xoico_cdaleth_stack_var_unit_adl_s \
  BCORE_DECLARE_OBJECT( xoico_cdaleth_stack_var_unit_adl_s ) \
  { \
      aware_t _; \
      BCORE_ARRAY_DYN_LINK_STATIC_S( xoico_cdaleth_stack_var_unit_s, ); \
  }; \
  static inline xoico_cdaleth_stack_var_unit_adl_s* xoico_cdaleth_stack_var_unit_adl_s_set_space( xoico_cdaleth_stack_var_unit_adl_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_xoico_cdaleth_stack_var_unit_adl_s, ( bcore_array* )o, size ); return o; } \
  static inline xoico_cdaleth_stack_var_unit_adl_s* xoico_cdaleth_stack_var_unit_adl_s_set_size( xoico_cdaleth_stack_var_unit_adl_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_xoico_cdaleth_stack_var_unit_adl_s, ( bcore_array* )o, size ); return o; } \
  static inline xoico_cdaleth_stack_var_unit_adl_s* xoico_cdaleth_stack_var_unit_adl_s_clear( xoico_cdaleth_stack_var_unit_adl_s* o ) { bcore_array_t_set_space( TYPEOF_xoico_cdaleth_stack_var_unit_adl_s, ( bcore_array* )o, 0 ); return o; } \
  static inline xoico_cdaleth_stack_var_unit_s* xoico_cdaleth_stack_var_unit_adl_s_push_c( xoico_cdaleth_stack_var_unit_adl_s* o, const xoico_cdaleth_stack_var_unit_s* v ) { bcore_array_t_push( TYPEOF_xoico_cdaleth_stack_var_unit_adl_s, ( bcore_array* )o, sr_twc( TYPEOF_xoico_cdaleth_stack_var_unit_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline xoico_cdaleth_stack_var_unit_s* xoico_cdaleth_stack_var_unit_adl_s_push_d( xoico_cdaleth_stack_var_unit_adl_s* o,       xoico_cdaleth_stack_var_unit_s* v ) { bcore_array_t_push( TYPEOF_xoico_cdaleth_stack_var_unit_adl_s, ( bcore_array* )o, sr_tsd( TYPEOF_xoico_cdaleth_stack_var_unit_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline xoico_cdaleth_stack_var_unit_s* xoico_cdaleth_stack_var_unit_adl_s_push( xoico_cdaleth_stack_var_unit_adl_s* o ) \
  { \
      bcore_array_t_push( TYPEOF_xoico_cdaleth_stack_var_unit_adl_s, ( bcore_array* )o, sr_t_create( TYPEOF_xoico_cdaleth_stack_var_unit_s ) ); \
      return o->data[ o->size - 1 ]; \
  }
#define TYPEOF_xoico_cdaleth_stack_var_s 0x1D109A7D51C8FC18ull
#define BETH_EXPAND_ITEM_xoico_cdaleth_stack_var_s \
  BCORE_DECLARE_OBJECT( xoico_cdaleth_stack_var_s ) \
  { \
      aware_t _; \
      xoico_cdaleth_stack_var_unit_adl_s adl; \
      bcore_hmap_tpuz_s hmap_name; \
  }; \
  static inline bl_t xoico_cdaleth_stack_var_s_exists( const xoico_cdaleth_stack_var_s* o, tp_t name ); \
  void xoico_cdaleth_stack_var_s_rehash_names( xoico_cdaleth_stack_var_s* o ); \
  xoico_cdaleth_stack_var_s* xoico_cdaleth_stack_var_s_push_unit( xoico_cdaleth_stack_var_s* o, const xoico_cdaleth_stack_var_unit_s* unit ); \
  xoico_cdaleth_stack_var_s* xoico_cdaleth_stack_var_s_pop_level( xoico_cdaleth_stack_var_s* o, sz_t level ); \
  const xoico_typespec_s* xoico_cdaleth_stack_var_s_get_typespec( const xoico_cdaleth_stack_var_s* o, tp_t name ); \
  const sz_t xoico_cdaleth_stack_var_s_get_level( const xoico_cdaleth_stack_var_s* o, tp_t name ); \
  void xoico_cdaleth_stack_var_s_clear( xoico_cdaleth_stack_var_s* o ); \
  static inline bl_t xoico_cdaleth_stack_var_s_exists( const xoico_cdaleth_stack_var_s* o, tp_t name ){ return  bcore_hmap_tpuz_s_exists(&(o->hmap_name),name );}
#define BETH_EXPAND_GROUP_xoico_cdaleth_stack_var \
  BCORE_FORWARD_OBJECT( xoico_cdaleth_stack_var ); \
  BCORE_FORWARD_OBJECT( xoico_cdaleth_stack_var_unit_s ); \
  BCORE_FORWARD_OBJECT( xoico_cdaleth_stack_var_unit_adl_s ); \
  BCORE_FORWARD_OBJECT( xoico_cdaleth_stack_var_s ); \
  XOILA_DECLARE_SPECT( xoico_cdaleth_stack_var ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( xoico_cdaleth_stack_var ) \
  BETH_EXPAND_ITEM_xoico_cdaleth_stack_var_unit_s \
  BETH_EXPAND_ITEM_xoico_cdaleth_stack_var_unit_adl_s \
  BETH_EXPAND_ITEM_xoico_cdaleth_stack_var_s

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_cdaleth_stack_block

#define TYPEOF_xoico_cdaleth_stack_block 0x018CBE73D7FCF11Aull
#define TYPEOF_xoico_cdaleth_stack_block_spect_s 0xFFBA6DB3DBAE38C6ull
#define TYPEOF_xoico_cdaleth_stack_block_unit_s 0x17B0D1A09DFB9D8Full
#define BETH_EXPAND_ITEM_xoico_cdaleth_stack_block_unit_s \
  BCORE_DECLARE_OBJECT( xoico_cdaleth_stack_block_unit_s ) \
  { \
      aware_t _; \
      sz_t level; \
      bl_t use_blm; \
      bl_t break_ledge; \
  };
#define TYPEOF_xoico_cdaleth_stack_block_unit_adl_s 0xC2B1FFFF0323881Full
#define BETH_EXPAND_ITEM_xoico_cdaleth_stack_block_unit_adl_s \
  BCORE_DECLARE_OBJECT( xoico_cdaleth_stack_block_unit_adl_s ) \
  { \
      aware_t _; \
      BCORE_ARRAY_DYN_LINK_STATIC_S( xoico_cdaleth_stack_block_unit_s, ); \
  }; \
  static inline xoico_cdaleth_stack_block_unit_adl_s* xoico_cdaleth_stack_block_unit_adl_s_set_space( xoico_cdaleth_stack_block_unit_adl_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_xoico_cdaleth_stack_block_unit_adl_s, ( bcore_array* )o, size ); return o; } \
  static inline xoico_cdaleth_stack_block_unit_adl_s* xoico_cdaleth_stack_block_unit_adl_s_set_size( xoico_cdaleth_stack_block_unit_adl_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_xoico_cdaleth_stack_block_unit_adl_s, ( bcore_array* )o, size ); return o; } \
  static inline xoico_cdaleth_stack_block_unit_adl_s* xoico_cdaleth_stack_block_unit_adl_s_clear( xoico_cdaleth_stack_block_unit_adl_s* o ) { bcore_array_t_set_space( TYPEOF_xoico_cdaleth_stack_block_unit_adl_s, ( bcore_array* )o, 0 ); return o; } \
  static inline xoico_cdaleth_stack_block_unit_s* xoico_cdaleth_stack_block_unit_adl_s_push_c( xoico_cdaleth_stack_block_unit_adl_s* o, const xoico_cdaleth_stack_block_unit_s* v ) { bcore_array_t_push( TYPEOF_xoico_cdaleth_stack_block_unit_adl_s, ( bcore_array* )o, sr_twc( TYPEOF_xoico_cdaleth_stack_block_unit_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline xoico_cdaleth_stack_block_unit_s* xoico_cdaleth_stack_block_unit_adl_s_push_d( xoico_cdaleth_stack_block_unit_adl_s* o,       xoico_cdaleth_stack_block_unit_s* v ) { bcore_array_t_push( TYPEOF_xoico_cdaleth_stack_block_unit_adl_s, ( bcore_array* )o, sr_tsd( TYPEOF_xoico_cdaleth_stack_block_unit_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline xoico_cdaleth_stack_block_unit_s* xoico_cdaleth_stack_block_unit_adl_s_push( xoico_cdaleth_stack_block_unit_adl_s* o ) \
  { \
      bcore_array_t_push( TYPEOF_xoico_cdaleth_stack_block_unit_adl_s, ( bcore_array* )o, sr_t_create( TYPEOF_xoico_cdaleth_stack_block_unit_s ) ); \
      return o->data[ o->size - 1 ]; \
  }
#define TYPEOF_xoico_cdaleth_stack_block_s 0x2543740CC3FCE924ull
#define BETH_EXPAND_ITEM_xoico_cdaleth_stack_block_s \
  BCORE_DECLARE_OBJECT( xoico_cdaleth_stack_block_s ) \
  { \
      aware_t _; \
      xoico_cdaleth_stack_block_unit_adl_s adl; \
  }; \
  static inline xoico_cdaleth_stack_block_s* xoico_cdaleth_stack_block_s_push( xoico_cdaleth_stack_block_s* o ); \
  static inline xoico_cdaleth_stack_block_s* xoico_cdaleth_stack_block_s_push_unit( xoico_cdaleth_stack_block_s* o, const xoico_cdaleth_stack_block_unit_s* unit ); \
  xoico_cdaleth_stack_block_s* xoico_cdaleth_stack_block_s_pop( xoico_cdaleth_stack_block_s* o ); \
  static inline void xoico_cdaleth_stack_block_s_clear( xoico_cdaleth_stack_block_s* o ); \
  static inline sz_t xoico_cdaleth_stack_block_s_get_size( const xoico_cdaleth_stack_block_s* o ); \
  static inline xoico_cdaleth_stack_block_s* xoico_cdaleth_stack_block_s_push( xoico_cdaleth_stack_block_s* o ){ xoico_cdaleth_stack_block_unit_adl_s_push_d( &(o->adl),xoico_cdaleth_stack_block_unit_s_create() );  return  o;} \
  static inline xoico_cdaleth_stack_block_s* xoico_cdaleth_stack_block_s_push_unit( xoico_cdaleth_stack_block_s* o, const xoico_cdaleth_stack_block_unit_s* unit ){ xoico_cdaleth_stack_block_unit_adl_s_push_c( &(o->adl),unit );  return  o;} \
  static inline void xoico_cdaleth_stack_block_s_clear( xoico_cdaleth_stack_block_s* o ){ xoico_cdaleth_stack_block_unit_adl_s_clear( &(o->adl));} \
  static inline sz_t xoico_cdaleth_stack_block_s_get_size( const xoico_cdaleth_stack_block_s* o ){ return  o->adl.size;}
#define BETH_EXPAND_GROUP_xoico_cdaleth_stack_block \
  BCORE_FORWARD_OBJECT( xoico_cdaleth_stack_block ); \
  BCORE_FORWARD_OBJECT( xoico_cdaleth_stack_block_unit_s ); \
  BCORE_FORWARD_OBJECT( xoico_cdaleth_stack_block_unit_adl_s ); \
  BCORE_FORWARD_OBJECT( xoico_cdaleth_stack_block_s ); \
  XOILA_DECLARE_SPECT( xoico_cdaleth_stack_block ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( xoico_cdaleth_stack_block ) \
  BETH_EXPAND_ITEM_xoico_cdaleth_stack_block_unit_s \
  BETH_EXPAND_ITEM_xoico_cdaleth_stack_block_unit_adl_s \
  BETH_EXPAND_ITEM_xoico_cdaleth_stack_block_s

/**********************************************************************************************************************/
// source: xoico_che.h

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_che

#define TYPEOF_xoico_che 0x2513169BE8C0DB50ull
#define TYPEOF_xoico_che_spect_s 0x3CFA2CC55AF0E878ull
#define TYPEOF_static 0xC534816D6D11E97Bull
#define TYPEOF_volatile 0x9575F08FB5A48F0Dull
#define TYPEOF_cast 0xB55E7090E879494Eull
#define TYPEOF_verbatim_C 0x7C0F5E2B3285120Dull
#define TYPEOF_keep 0x585D7CD75CF6F848ull
#define TYPEOF_scope 0xC1074FFBE7EFE44Bull
#define TYPEOF_scope_local 0xC7F69BF78D91B167ull
#define TYPEOF_scope_func 0x5E9151F1091C19BAull
#define TYPEOF_keep_func 0xA74182F52F6E64F7ull
#define TYPEOF_keep_block 0xD904ABF6228783B2ull
#define TYPEOF_fork 0xDD1D0D790C2F1881ull
#define TYPEOF_try 0x570AC119447423EEull
#define TYPEOF_if 0x08B73007B55C3E26ull
#define TYPEOF_else 0x7F2B6C605332DD30ull
#define TYPEOF_while 0xCE87A3885811296Eull
#define TYPEOF_do 0x08915907B53BB494ull
#define TYPEOF_for 0xDCB27818FED9DA90ull
#define TYPEOF_foreach 0x8AD09EA0575C3439ull
#define TYPEOF_switch 0xA5A87AC5B0B379B1ull
#define TYPEOF_case 0xB55E6190E8792FD1ull
#define TYPEOF_default 0xEBADA5168620C5FEull
#define TYPEOF_break 0x93B7591DEBC7CE38ull
#define TYPEOF_return 0xC5C7B983377CAD5Full
#define TYPEOF_xoico_che_s 0x72C73ADCFF3EA5CAull
#define BETH_EXPAND_ITEM_xoico_che_s \
  BCORE_DECLARE_OBJECT( xoico_che_s ) \
  { \
      aware_t _; \
      bl_t verbose; \
      bl_t insert_source_reference; \
      xoico_compiler_s* compiler; \
      xoico_group_s* group; \
      xoico_stamp_s* stamp; \
      xoico_typespec_s typespec_ret; \
      tp_t member_obj_type; \
      sz_t level; \
      sz_t try_block_level; \
      xoico_che_stack_var_s stack_var; \
      xoico_che_stack_block_s stack_block; \
      bcore_hmap_name_s hmap_name; \
  }; \
  bl_t xoico_che_s_is_reserved( const xoico_che_s* o, tp_t tp_identifier ); \
  static inline tp_t xoico_che_s_entypeof( xoico_che_s* o, sc_t name ); \
  sc_t xoico_che_s_nameof( xoico_che_s* o, tp_t type ); \
  void xoico_che_s_init_level0( xoico_che_s* o ); \
  void xoico_che_s_inc_block( xoico_che_s* o ); \
  void xoico_che_s_dec_block( xoico_che_s* o ); \
  xoico_che_stack_block_unit_s* xoico_che_s_stack_block_get_top_unit( xoico_che_s* o ); \
  xoico_che_stack_block_unit_s* xoico_che_s_stack_block_get_bottom_unit( xoico_che_s* o ); \
  xoico_che_stack_block_unit_s* xoico_che_s_stack_block_get_level_unit( xoico_che_s* o, sz_t level ); \
  void xoico_che_s_push_typedecl( xoico_che_s* o, const xoico_typespec_s* typespec, tp_t name ); \
  void xoico_che_s_typespec_to_sink( xoico_che_s* o, const xoico_typespec_s* typespec, bcore_sink* sink ); \
  static inline bl_t xoico_che_s_is_type( const xoico_che_s* o, tp_t name ); \
  static inline bl_t xoico_che_s_is_group( const xoico_che_s* o, tp_t name ); \
  static inline bl_t xoico_che_s_is_stamp( const xoico_che_s* o, tp_t name ); \
  static inline bl_t xoico_che_s_is_func( const xoico_che_s* o, tp_t name ); \
  static inline bl_t xoico_che_s_is_var( const xoico_che_s* o, tp_t name ); \
  static inline xoico_group_s* xoico_che_s_get_group( xoico_che_s* o, tp_t name ); \
  static inline xoico_stamp_s* xoico_che_s_get_stamp( xoico_che_s* o, tp_t name ); \
  static inline xoico_func_s* xoico_che_s_get_func( xoico_che_s* o, tp_t name ); \
  bl_t xoico_che_s_returns_a_value( const xoico_che_s* o ); \
  er_t xoico_che_s_parse( const xoico_che_s* o, bcore_source* source, sc_t format ); \
  er_t xoico_che_s_trans( const xoico_che_s* o, bcore_source* source, sc_t format, xoico_che_result* result ); \
  tp_t xoico_che_s_get_identifier( xoico_che_s* o, bcore_source* source, bl_t take_from_source ); \
  er_t xoico_che_s_trans_identifier( xoico_che_s* o, bcore_source* source, xoico_che_result* result, tp_t* tp_identifier ); \
  er_t xoico_che_s_trans_number_literal( xoico_che_s* o, bcore_source* source, xoico_che_result* result ); \
  er_t xoico_che_s_trans_string_literal( xoico_che_s* o, bcore_source* source, xoico_che_result* result ); \
  er_t xoico_che_s_trans_char_literal( xoico_che_s* o, bcore_source* source, xoico_che_result* result ); \
  er_t xoico_che_s_trans_whitespace( xoico_che_s* o, bcore_source* source, xoico_che_result* result ); \
  er_t xoico_che_s_trans_preprocessor( xoico_che_s* o, bcore_source* source, xoico_che_result* result ); \
  tp_t xoico_che_s_trans_inert_operator( xoico_che_s* o, bcore_source* source, xoico_che_result* result ); \
  er_t xoico_che_s_adapt_expression_indirection( xoico_che_s* o, bcore_source* source, const xoico_typespec_s* typespec_expr, sz_t target_indirection, const xoico_che_result* result_expr, xoico_che_result* result ); \
  er_t xoico_che_s_adapt_expression( xoico_che_s* o, bcore_source* source, const xoico_typespec_s* typespec_expr, const xoico_typespec_s* typespec_target, const xoico_che_result* result_expr, xoico_che_result* result ); \
  er_t xoico_che_s_trans_function_args( xoico_che_s* o, bcore_source* source, const xoico_signature_s* signature, const xoico_che_result* result_obj_expr, const xoico_typespec_s* typespec_obj_expr, xoico_che_result* result_out ); \
  er_t xoico_che_s_trans_typespec_member( xoico_che_s* o, bcore_source* source, xoico_che_result* result, const xoico_typespec_s* in_typespec, xoico_typespec_s* out_typespec ); \
  er_t xoico_che_s_trans_typespec_array_subscript( xoico_che_s* o, bcore_source* source, xoico_che_result* result, const xoico_typespec_s* in_typespec, xoico_typespec_s* out_typespec ); \
  er_t xoico_che_s_trans_typespec_create( xoico_che_s* o, bcore_source* source, xoico_che_result* result, const xoico_typespec_s* in_typespec, xoico_typespec_s* out_typespec ); \
  er_t xoico_che_s_trans_typespec_test_presence( xoico_che_s* o, bcore_source* source, xoico_che_result* result, const xoico_typespec_s* in_typespec, xoico_typespec_s* out_typespec ); \
  er_t xoico_che_s_trans_typespec_attach( xoico_che_s* o, bcore_source* source, xoico_che_result* result, const xoico_typespec_s* in_typespec, xoico_typespec_s* out_typespec ); \
  er_t xoico_che_s_trans_typespec_ternary_branch( xoico_che_s* o, bcore_source* source, xoico_che_result* result, const xoico_typespec_s* in_typespec, xoico_typespec_s* out_typespec ); \
  er_t xoico_che_s_trans_typespec_expression( xoico_che_s* o, bcore_source* source, xoico_che_result* result, const xoico_typespec_s* in_typespec, xoico_typespec_s* out_typespec ); \
  er_t xoico_che_s_trans_member( xoico_che_s* o, bcore_source* source, xoico_che_result* result ); \
  er_t xoico_che_s_try_take_typespec( xoico_che_s* o, bcore_source* source, xoico_typespec_s* typespec, bl_t require_tractable_type, bl_t* success ); \
  er_t xoico_che_s_take_typespec( xoico_che_s* o, bcore_source* source, xoico_typespec_s* typespec, bl_t require_tractable_type ); \
  er_t xoico_che_s_push_typespec( xoico_che_s* o, const xoico_typespec_s* typespec, xoico_che_result* result ); \
  er_t xoico_che_s_trans_type( xoico_che_s* o, bcore_source* source, xoico_che_result* result, xoico_typespec_s* out_typespec ); \
  er_t xoico_che_s_trans_func( xoico_che_s* o, bcore_source* source, xoico_che_result* result, xoico_typespec_s* out_typespec ); \
  er_t xoico_che_s_trans_ternary_branch( xoico_che_s* o, bcore_source* source, xoico_che_result* result, xoico_typespec_s* out_typespec ); \
  er_t xoico_che_s_trans_bracket( xoico_che_s* o, bcore_source* source, xoico_che_result* result, xoico_typespec_s* out_typespec ); \
  er_t xoico_che_s_trans_array_subscript( xoico_che_s* o, bcore_source* source, xoico_che_result* result, xoico_typespec_s* out_typespec ); \
  er_t xoico_che_s_trans_expression( xoico_che_s* o, bcore_source* source, xoico_che_result* result_out, xoico_typespec_s* out_typespec ); \
  er_t xoico_che_s_try_trans_declaration( xoico_che_s* o, bcore_source* source, xoico_che_result* result_out, bl_t* success ); \
  er_t xoico_che_s_inspect_variable( xoico_che_s* o, bcore_source* source ); \
  er_t xoico_che_s_trans_statement_expression( xoico_che_s* o, bcore_source* source, xoico_che_result* result ); \
  er_t xoico_che_s_trans_statement( xoico_che_s* o, bcore_source* source, xoico_che_result* result ); \
  er_t xoico_che_s_trans_block_inside( xoico_che_s* o, bcore_source* source, xoico_che_result* result_out ); \
  er_t xoico_che_s_trans_block( xoico_che_s* o, bcore_source* source, xoico_che_result* result_out, bl_t is_break_ledge ); \
  er_t xoico_che_s_trans_statement_as_block( xoico_che_s* o, bcore_source* source, xoico_che_result* result_out, bl_t is_break_ledge ); \
  er_t xoico_che_s_trans_block_inside_verbatim_c( xoico_che_s* o, bcore_source* source, xoico_che_result* result ); \
  er_t xoico_che_s_setup( xoico_che_s* o, const xoico_body_s* body, const xoico_signature_s* signature ); \
  sz_t xoico_che_s_assess_indentation( bcore_source* source ); \
  void xoico_che_s_remove_indentation( st_s* string, sz_t indentation ); \
  er_t xoico_che_s_translate_mutable( xoico_che_s* o, const xoico_body_s* body, const xoico_signature_s* signature, bcore_sink* sink ); \
  er_t xoico_che_s_translate( const xoico_che_s* o, const xoico_body_s* body, const xoico_signature_s* signature, bcore_sink* sink ); \
  bl_t xoico_che_s_is_builtin_func( const xoico_che_s* o, tp_t tp_identifier ); \
  er_t xoico_che_s_trans_builtin( xoico_che_s* o, tp_t tp_builtin, bcore_source* source, const xoico_che_result* result_expr, const xoico_typespec_s* typespec_expr, xoico_che_result* result_out, xoico_typespec_s* typespec_out ); \
  er_t xoico_che_s_trans_builtin_cast( xoico_che_s* o, bcore_source* source, const xoico_che_result* result_expr, const xoico_typespec_s* typespec_expr, xoico_che_result* result_out, xoico_typespec_s* typespec_out ); \
  er_t xoico_che_s_trans_builtin_scope( xoico_che_s* o, bcore_source* source, const xoico_che_result* result_expr, const xoico_typespec_s* typespec_expr, xoico_che_result* result_out, xoico_typespec_s* typespec_out ); \
  er_t xoico_che_s_trans_builtin_fork( xoico_che_s* o, bcore_source* source, const xoico_che_result* result_expr, const xoico_typespec_s* typespec_expr, xoico_che_result* result_out, xoico_typespec_s* typespec_out ); \
  er_t xoico_che_s_trans_builtin_try( xoico_che_s* o, bcore_source* source, const xoico_che_result* result_expr, const xoico_typespec_s* typespec_expr, xoico_che_result* result_out, xoico_typespec_s* typespec_out ); \
  bl_t xoico_che_s_is_control_name( const xoico_che_s* o, tp_t tp_identifier ); \
  er_t xoico_che_s_trans_control( xoico_che_s* o, tp_t tp_control, bcore_source* source, xoico_che_result* result ); \
  er_t xoico_che_s_trans_control_for( xoico_che_s* o, bcore_source* source, xoico_che_result* result ); \
  er_t xoico_che_s_trans_control_foreach( xoico_che_s* o, bcore_source* source, xoico_che_result* result ); \
  er_t xoico_che_s_trans_control_if( xoico_che_s* o, bcore_source* source, xoico_che_result* result ); \
  er_t xoico_che_s_trans_control_while( xoico_che_s* o, bcore_source* source, xoico_che_result* result ); \
  er_t xoico_che_s_trans_control_do( xoico_che_s* o, bcore_source* source, xoico_che_result* result ); \
  er_t xoico_che_s_trans_control_else( xoico_che_s* o, bcore_source* source, xoico_che_result* result ); \
  er_t xoico_che_s_trans_control_switch( xoico_che_s* o, bcore_source* source, xoico_che_result* result ); \
  er_t xoico_che_s_trans_control_case( xoico_che_s* o, bcore_source* source, xoico_che_result* result ); \
  er_t xoico_che_s_trans_control_default( xoico_che_s* o, bcore_source* source, xoico_che_result* result ); \
  er_t xoico_che_s_trans_control_break( xoico_che_s* o, bcore_source* source, xoico_che_result* result ); \
  er_t xoico_che_s_trans_control_return( xoico_che_s* o, bcore_source* source, xoico_che_result* result ); \
  static inline tp_t xoico_che_s_entypeof( xoico_che_s* o, sc_t name ){ return  bcore_hmap_name_s_set_sc(&(o->hmap_name),name );} \
  static inline bl_t xoico_che_s_is_type( const xoico_che_s* o, tp_t name ){ return  xoico_compiler_s_is_type(o->compiler,name );} \
  static inline bl_t xoico_che_s_is_group( const xoico_che_s* o, tp_t name ){ return  xoico_compiler_s_is_group(o->compiler,name );} \
  static inline bl_t xoico_che_s_is_stamp( const xoico_che_s* o, tp_t name ){ return  xoico_compiler_s_is_stamp(o->compiler,name );} \
  static inline bl_t xoico_che_s_is_func( const xoico_che_s* o, tp_t name ){ return  xoico_compiler_s_is_func(o->compiler,name );} \
  static inline bl_t xoico_che_s_is_var( const xoico_che_s* o, tp_t name ){ return  xoico_che_stack_var_s_exists(&(o->stack_var),name );} \
  static inline xoico_group_s* xoico_che_s_get_group( xoico_che_s* o, tp_t name ){ return  xoico_compiler_s_get_group(o->compiler,name );} \
  static inline xoico_stamp_s* xoico_che_s_get_stamp( xoico_che_s* o, tp_t name ){ return  xoico_compiler_s_get_stamp(o->compiler,name );} \
  static inline xoico_func_s* xoico_che_s_get_func( xoico_che_s* o, tp_t name ){ return  xoico_compiler_s_get_func(o->compiler,name );}
#define TYPEOF_xoico_che_result_break_s 0x35650767E6F06C8Eull
#define BETH_EXPAND_ITEM_xoico_che_result_break_s \
  BCORE_DECLARE_OBJECT( xoico_che_result_break_s ) \
  { \
      aware_t _; \
      sz_t ledge_level; \
      xoico_che_result_block_s* parent; \
  }; \
  static inline void xoico_che_result_break_s_set_parent_block( xoico_che_result_break_s* o, xoico_che_result_block_s* parent ); \
  er_t xoico_che_result_break_s_to_sink( const xoico_che_result_break_s* o, bcore_sink* sink ); \
  static inline xoico_che_result_break_s* xoico_che_result_break_s_create_setup( sz_t ledge_level ); \
  static inline void xoico_che_result_break_s_set_parent_block( xoico_che_result_break_s* o, xoico_che_result_block_s* parent ){ o->parent = parent;} \
  static inline xoico_che_result_break_s* xoico_che_result_break_s_create_setup( sz_t ledge_level ){ xoico_che_result_break_s* o = xoico_che_result_break_s_create(); o->ledge_level = ledge_level; return  o;}
#define TYPEOF_xoico_che_result_return_s 0x176B383C947A3D15ull
#define BETH_EXPAND_ITEM_xoico_che_result_return_s \
  BCORE_DECLARE_OBJECT( xoico_che_result_return_s ) \
  { \
      aware_t _; \
      xoico_che_result_block_s* parent; \
      xoico_che_result* result_blm; \
      xoico_che_result* result_direct; \
  }; \
  static inline void xoico_che_result_return_s_set_parent_block( xoico_che_result_return_s* o, xoico_che_result_block_s* parent ); \
  er_t xoico_che_result_return_s_to_sink( const xoico_che_result_return_s* o, bcore_sink* sink ); \
  static inline void xoico_che_result_return_s_set_parent_block( xoico_che_result_return_s* o, xoico_che_result_block_s* parent ){ o->parent = parent;}
#define BETH_EXPAND_GROUP_xoico_che \
  BCORE_FORWARD_OBJECT( xoico_che ); \
  BCORE_FORWARD_OBJECT( xoico_che_result ); \
  BCORE_FORWARD_OBJECT( xoico_che_stack_var ); \
  BCORE_FORWARD_OBJECT( xoico_che_stack_block ); \
  BCORE_FORWARD_OBJECT( xoico_che_s ); \
  BCORE_FORWARD_OBJECT( xoico_che_result_break_s ); \
  BCORE_FORWARD_OBJECT( xoico_che_result_return_s ); \
  XOILA_DECLARE_SPECT( xoico_che ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( xoico_che ) \
  BETH_EXPAND_GROUP_xoico_che_result \
  BETH_EXPAND_GROUP_xoico_che_stack_var \
  BETH_EXPAND_GROUP_xoico_che_stack_block \
  BETH_EXPAND_ITEM_xoico_che_s \
  BETH_EXPAND_ITEM_xoico_che_result_break_s \
  BETH_EXPAND_ITEM_xoico_che_result_return_s

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_che_result

#define TYPEOF_xoico_che_result 0xD38086964DD18FECull
#define TYPEOF_xoico_che_result_spect_s 0xC20381F5DAF5CF24ull
#define TYPEOF_xoico_che_result_plain_s 0xC53C452F67E91A15ull
#define BETH_EXPAND_ITEM_xoico_che_result_plain_s \
  BCORE_DECLARE_OBJECT( xoico_che_result_plain_s ) \
  { \
      aware_t _; \
      st_s st; \
  }; \
  static inline xoico_che_result_plain_s* xoico_che_result_plain_s_create_from_st( const st_s* st ); \
  static inline xoico_che_result_plain_s* xoico_che_result_plain_s_create_from_st_d( st_s* st ); \
  static inline xoico_che_result_plain_s* xoico_che_result_plain_s_create_from_sc( sc_t sc ); \
  static inline void xoico_che_result_plain_s_clear( xoico_che_result_plain_s* o ); \
  static inline er_t xoico_che_result_plain_s_push_char( xoico_che_result_plain_s* o, char c ); \
  static inline er_t xoico_che_result_plain_s_push_sc( xoico_che_result_plain_s* o, sc_t sc ); \
  static inline er_t xoico_che_result_plain_s_push_st( xoico_che_result_plain_s* o, const st_s* st ); \
  static inline er_t xoico_che_result_plain_s_to_sink( const xoico_che_result_plain_s* o, bcore_sink* sink ); \
  static inline st_s* xoico_che_result_plain_s_create_st( const xoico_che_result_plain_s* o ); \
  static inline xoico_che_result_plain_s* xoico_che_result_plain_s_create_from_st( const st_s* st ){ xoico_che_result_plain_s* o = xoico_che_result_plain_s_create(); st_s_copy(&(o->st),st ); return  o;} \
  static inline xoico_che_result_plain_s* xoico_che_result_plain_s_create_from_st_d( st_s* st ){ xoico_che_result_plain_s* o = xoico_che_result_plain_s_create(); st_s_copy(&(o->st),st ); st_s_discard(st); return  o;} \
  static inline xoico_che_result_plain_s* xoico_che_result_plain_s_create_from_sc( sc_t sc ){ xoico_che_result_plain_s* o = xoico_che_result_plain_s_create(); st_s_copy_sc( &(o->st),sc ); return  o;} \
  static inline void xoico_che_result_plain_s_clear( xoico_che_result_plain_s* o ){ st_s_clear( &(o->st));} \
  static inline er_t xoico_che_result_plain_s_push_char( xoico_che_result_plain_s* o, char c ){ st_s_push_char( &(o->st),c ); return  0;} \
  static inline er_t xoico_che_result_plain_s_push_sc( xoico_che_result_plain_s* o, sc_t sc ){ st_s_push_sc( &(o->st),sc ); return  0;} \
  static inline er_t xoico_che_result_plain_s_push_st( xoico_che_result_plain_s* o, const st_s* st ){ st_s_push_st( &(o->st),st ); return  0;} \
  static inline er_t xoico_che_result_plain_s_to_sink( const xoico_che_result_plain_s* o, bcore_sink* sink ){ bcore_sink_a_push_string( sink,&o->st );  return  0;} \
  static inline st_s* xoico_che_result_plain_s_create_st( const xoico_che_result_plain_s* o ){ return  st_s_clone(&(o->st));}
#define TYPEOF_xoico_che_result_adl_s 0x5B66C12862213C52ull
#define BETH_EXPAND_ITEM_xoico_che_result_adl_s \
  BCORE_DECLARE_OBJECT( xoico_che_result_adl_s ) \
  { \
      aware_t _; \
      BCORE_ARRAY_DYN_LINK_STATIC_S( xoico_che_result, ); \
  }; \
  static inline xoico_che_result_adl_s* xoico_che_result_adl_s_set_space( xoico_che_result_adl_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_xoico_che_result_adl_s, ( bcore_array* )o, size ); return o; } \
  static inline xoico_che_result_adl_s* xoico_che_result_adl_s_set_size( xoico_che_result_adl_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_xoico_che_result_adl_s, ( bcore_array* )o, size ); return o; } \
  static inline xoico_che_result_adl_s* xoico_che_result_adl_s_clear( xoico_che_result_adl_s* o ) { bcore_array_t_set_space( TYPEOF_xoico_che_result_adl_s, ( bcore_array* )o, 0 ); return o; } \
  static inline xoico_che_result* xoico_che_result_adl_s_push_c( xoico_che_result_adl_s* o, const xoico_che_result* v ) { bcore_array_t_push( TYPEOF_xoico_che_result_adl_s, ( bcore_array* )o, sr_awc( v ) ); return o->data[ o->size - 1 ]; } \
  static inline xoico_che_result* xoico_che_result_adl_s_push_d( xoico_che_result_adl_s* o,       xoico_che_result* v ) { bcore_array_t_push( TYPEOF_xoico_che_result_adl_s, ( bcore_array* )o, sr_asd( v ) ); return o->data[ o->size - 1 ]; } \
  static inline xoico_che_result* xoico_che_result_adl_s_push_t( xoico_che_result_adl_s* o, tp_t t ) \
  { \
      bcore_trait_assert_satisfied_type( TYPEOF_xoico_che_result, t ); \
      bcore_array_t_push( TYPEOF_xoico_che_result_adl_s, ( bcore_array* )o, sr_t_create( t ) ); \
      return o->data[ o->size - 1 ]; \
  }
#define TYPEOF_xoico_che_result_arr_s 0x87AF6693207FCB96ull
#define BETH_EXPAND_ITEM_xoico_che_result_arr_s \
  BCORE_DECLARE_OBJECT( xoico_che_result_arr_s ) \
  { \
      aware_t _; \
      xoico_che_result_adl_s adl; \
  }; \
  static inline void xoico_che_result_arr_s_clear( xoico_che_result_arr_s* o ); \
  xoico_che_result* xoico_che_result_arr_s_last( xoico_che_result_arr_s* o ); \
  xoico_che_result* xoico_che_result_arr_s_last_plain( xoico_che_result_arr_s* o ); \
  static inline er_t xoico_che_result_arr_s_push_char( xoico_che_result_arr_s* o, char c ); \
  static inline er_t xoico_che_result_arr_s_push_sc( xoico_che_result_arr_s* o, sc_t sc ); \
  static inline er_t xoico_che_result_arr_s_push_st( xoico_che_result_arr_s* o, const st_s* st ); \
  static inline xoico_che_result* xoico_che_result_arr_s_push_result_d( xoico_che_result_arr_s* o, xoico_che_result* result ); \
  static inline xoico_che_result* xoico_che_result_arr_s_push_result_c( xoico_che_result_arr_s* o, const xoico_che_result* result ); \
  er_t xoico_che_result_arr_s_to_sink( const xoico_che_result_arr_s* o, bcore_sink* sink ); \
  void xoico_che_result_arr_s_set_parent_block( xoico_che_result_arr_s* o, xoico_che_result_block_s* parent ); \
  static inline void xoico_che_result_arr_s_clear( xoico_che_result_arr_s* o ){ xoico_che_result_adl_s_clear( &(o->adl));} \
  static inline er_t xoico_che_result_arr_s_push_char( xoico_che_result_arr_s* o, char c ){ return  xoico_che_result_a_push_char(xoico_che_result_arr_s_last_plain(o),c );} \
  static inline er_t xoico_che_result_arr_s_push_sc( xoico_che_result_arr_s* o, sc_t sc ){ return  xoico_che_result_a_push_sc(xoico_che_result_arr_s_last_plain(o),sc );} \
  static inline er_t xoico_che_result_arr_s_push_st( xoico_che_result_arr_s* o, const st_s* st ){ return  xoico_che_result_a_push_st(xoico_che_result_arr_s_last_plain(o),st );} \
  static inline xoico_che_result* xoico_che_result_arr_s_push_result_d( xoico_che_result_arr_s* o, xoico_che_result* result ){ return  xoico_che_result_adl_s_push_d( &(o->adl),result );} \
  static inline xoico_che_result* xoico_che_result_arr_s_push_result_c( xoico_che_result_arr_s* o, const xoico_che_result* result ){ return  xoico_che_result_adl_s_push_c( &(o->adl),result );}
#define TYPEOF_xoico_che_result_block_s 0x1B3ECCE6627048A0ull
#define BETH_EXPAND_ITEM_xoico_che_result_block_s \
  BCORE_DECLARE_OBJECT( xoico_che_result_block_s ) \
  { \
      aware_t _; \
      xoico_che_result_arr_s arr; \
      sz_t level; \
      bl_t is_using_blm; \
      bl_t is_root; \
      xoico_che_result_block_s* parent; \
  }; \
  static inline void xoico_che_result_block_s_clear( xoico_che_result_block_s* o ); \
  static inline er_t xoico_che_result_block_s_push_char( xoico_che_result_block_s* o, char c ); \
  static inline er_t xoico_che_result_block_s_push_sc( xoico_che_result_block_s* o, sc_t sc ); \
  static inline er_t xoico_che_result_block_s_push_st( xoico_che_result_block_s* o, const st_s* st ); \
  xoico_che_result* xoico_che_result_block_s_push_result_d( xoico_che_result_block_s* o, xoico_che_result* result ); \
  xoico_che_result* xoico_che_result_block_s_push_result_c( xoico_che_result_block_s* o, const xoico_che_result* result ); \
  static inline er_t xoico_che_result_block_s_to_sink( const xoico_che_result_block_s* o, bcore_sink* sink ); \
  static inline void xoico_che_result_block_s_set_parent_block( xoico_che_result_block_s* o, xoico_che_result_block_s* parent ); \
  bl_t xoico_che_result_block_s_is_using_blm_until_level( const xoico_che_result_block_s* o, sz_t level ); \
  static inline void xoico_che_result_block_s_clear( xoico_che_result_block_s* o ){ xoico_che_result_arr_s_clear(&(o->arr));} \
  static inline er_t xoico_che_result_block_s_push_char( xoico_che_result_block_s* o, char c ){ return  xoico_che_result_arr_s_push_char(&(o->arr),c );} \
  static inline er_t xoico_che_result_block_s_push_sc( xoico_che_result_block_s* o, sc_t sc ){ return  xoico_che_result_arr_s_push_sc(&(o->arr),sc );} \
  static inline er_t xoico_che_result_block_s_push_st( xoico_che_result_block_s* o, const st_s* st ){ return  xoico_che_result_arr_s_push_st(&(o->arr),st );} \
  static inline er_t xoico_che_result_block_s_to_sink( const xoico_che_result_block_s* o, bcore_sink* sink ){ return  xoico_che_result_arr_s_to_sink(&(o->arr),sink );} \
  static inline void xoico_che_result_block_s_set_parent_block( xoico_che_result_block_s* o, xoico_che_result_block_s* parent ){ o->parent = parent;}
#define TYPEOF_xoico_che_result_blm_init_s 0xCA938B3C0BCFAF3Full
#define BETH_EXPAND_ITEM_xoico_che_result_blm_init_s \
  BCORE_DECLARE_OBJECT( xoico_che_result_blm_init_s ) \
  { \
      aware_t _; \
      sz_t level; \
  }; \
  static inline er_t xoico_che_result_blm_init_s_to_sink( const xoico_che_result_blm_init_s* o, bcore_sink* sink ); \
  static inline er_t xoico_che_result_blm_init_s_to_sink( const xoico_che_result_blm_init_s* o, bcore_sink* sink ){ bcore_sink_a_push_fa( sink,"BLM_INIT_LEVEL(#<sz_t>);", o->level ); return  0;}
#define TYPEOF_xoico_che_result_blm_down_s 0x2D9E8B7DBC175C59ull
#define BETH_EXPAND_ITEM_xoico_che_result_blm_down_s \
  BCORE_DECLARE_OBJECT( xoico_che_result_blm_down_s ) \
  { \
      aware_t _; \
  }; \
  static inline er_t xoico_che_result_blm_down_s_to_sink( const xoico_che_result_blm_down_s* o, bcore_sink* sink ); \
  static inline er_t xoico_che_result_blm_down_s_to_sink( const xoico_che_result_blm_down_s* o, bcore_sink* sink ){ bcore_sink_a_push_sc( sink,"BLM_DOWN();" ); return  0;}
#define BETH_EXPAND_GROUP_xoico_che_result \
  BCORE_FORWARD_OBJECT( xoico_che_result ); \
  BCORE_FORWARD_OBJECT( xoico_che_result_plain_s ); \
  BCORE_FORWARD_OBJECT( xoico_che_result_adl_s ); \
  BCORE_FORWARD_OBJECT( xoico_che_result_arr_s ); \
  BCORE_FORWARD_OBJECT( xoico_che_result_block_s ); \
  BCORE_FORWARD_OBJECT( xoico_che_result_blm_init_s ); \
  BCORE_FORWARD_OBJECT( xoico_che_result_blm_down_s ); \
  static inline xoico_che_result* xoico_che_result_create_from_st( const st_s* st ); \
  static inline xoico_che_result* xoico_che_result_create_from_sc( sc_t sc ); \
  static inline xoico_che_result* xoico_che_result_create_arr( void ); \
  xoico_che_result* xoico_che_result_create_block( sz_t level, bl_t is_using_blm ); \
  static inline xoico_che_result* xoico_che_result_create_blm_init( sz_t level ); \
  static inline xoico_che_result* xoico_che_result_create_blm_down( void ); \
  typedef void (*xoico_che_result_clear)( xoico_che_result* o ); \
  typedef er_t (*xoico_che_result_push_char)( xoico_che_result* o, char c ); \
  typedef er_t (*xoico_che_result_push_sc)( xoico_che_result* o, sc_t sc ); \
  typedef er_t (*xoico_che_result_push_st)( xoico_che_result* o, const st_s* st ); \
  typedef xoico_che_result* (*xoico_che_result_push_result_c)( xoico_che_result* o, const xoico_che_result* result ); \
  typedef xoico_che_result* (*xoico_che_result_push_result_d)( xoico_che_result* o, xoico_che_result* result ); \
  typedef er_t (*xoico_che_result_to_sink)( const xoico_che_result* o, bcore_sink* sink ); \
  typedef void (*xoico_che_result_set_parent_block)( xoico_che_result* o, xoico_che_result_block_s* parent ); \
  typedef st_s* (*xoico_che_result_create_st)( const xoico_che_result* o ); \
  XOILA_DECLARE_SPECT( xoico_che_result ) \
  { \
      bcore_spect_header_s header; \
      xoico_che_result_clear clear; \
      xoico_che_result_push_char push_char; \
      xoico_che_result_push_sc push_sc; \
      xoico_che_result_push_st push_st; \
      xoico_che_result_push_result_c push_result_c; \
      xoico_che_result_push_result_d push_result_d; \
      xoico_che_result_to_sink to_sink; \
      xoico_che_result_set_parent_block set_parent_block; \
      xoico_che_result_create_st create_st; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( xoico_che_result ) \
  static inline void xoico_che_result_a_clear( xoico_che_result* o ) { const xoico_che_result_spect_s* p = xoico_che_result_spect_s_get_aware( o ); assert( p->clear ); p->clear( o ); } \
  static inline bl_t xoico_che_result_a_defines_clear( const xoico_che_result* o ) { return true; } \
  static inline void xoico_che_result_clear_default( xoico_che_result* o ){} \
  static inline er_t xoico_che_result_a_push_char( xoico_che_result* o, char c ) { const xoico_che_result_spect_s* p = xoico_che_result_spect_s_get_aware( o ); assert( p->push_char ); return p->push_char( o, c ); } \
  static inline bl_t xoico_che_result_a_defines_push_char( const xoico_che_result* o ) { return true; } \
  static inline er_t xoico_che_result_push_char_default( xoico_che_result* o, char c ){ ERR_fa( "Not implemented." ); return  0;} \
  static inline er_t xoico_che_result_a_push_sc( xoico_che_result* o, sc_t sc ) { const xoico_che_result_spect_s* p = xoico_che_result_spect_s_get_aware( o ); assert( p->push_sc ); return p->push_sc( o, sc ); } \
  static inline bl_t xoico_che_result_a_defines_push_sc( const xoico_che_result* o ) { return true; } \
  static inline er_t xoico_che_result_push_sc_default( xoico_che_result* o, sc_t sc ){ ERR_fa( "Not implemented." ); return  0;} \
  static inline er_t xoico_che_result_a_push_st( xoico_che_result* o, const st_s* st ) { const xoico_che_result_spect_s* p = xoico_che_result_spect_s_get_aware( o ); assert( p->push_st ); return p->push_st( o, st ); } \
  static inline bl_t xoico_che_result_a_defines_push_st( const xoico_che_result* o ) { return true; } \
  static inline er_t xoico_che_result_push_st_default( xoico_che_result* o, const st_s* st ){ ERR_fa( "Not implemented." ); return  0;} \
  static inline xoico_che_result* xoico_che_result_a_push_result_c( xoico_che_result* o, const xoico_che_result* result ) { const xoico_che_result_spect_s* p = xoico_che_result_spect_s_get_aware( o ); assert( p->push_result_c ); return p->push_result_c( o, result ); } \
  static inline bl_t xoico_che_result_a_defines_push_result_c( const xoico_che_result* o ) { return true; } \
  static inline xoico_che_result* xoico_che_result_push_result_c_default( xoico_che_result* o, const xoico_che_result* result ){ ERR_fa( "Not implemented." ); return  NULL;} \
  static inline xoico_che_result* xoico_che_result_a_push_result_d( xoico_che_result* o, xoico_che_result* result ) { const xoico_che_result_spect_s* p = xoico_che_result_spect_s_get_aware( o ); assert( p->push_result_d ); return p->push_result_d( o, result ); } \
  static inline bl_t xoico_che_result_a_defines_push_result_d( const xoico_che_result* o ) { return true; } \
  static inline xoico_che_result* xoico_che_result_push_result_d_default( xoico_che_result* o, xoico_che_result* result ){ ERR_fa( "Not implemented." ); return  NULL;} \
  static inline er_t xoico_che_result_a_to_sink( const xoico_che_result* o, bcore_sink* sink ) { const xoico_che_result_spect_s* p = xoico_che_result_spect_s_get_aware( o ); assert( p->to_sink ); return p->to_sink( o, sink ); } \
  static inline bl_t xoico_che_result_a_defines_to_sink( const xoico_che_result* o ) { return xoico_che_result_spect_s_get_aware( o )->to_sink != NULL; } \
  static inline void xoico_che_result_a_set_parent_block( xoico_che_result* o, xoico_che_result_block_s* parent ) { const xoico_che_result_spect_s* p = xoico_che_result_spect_s_get_aware( o ); assert( p->set_parent_block ); p->set_parent_block( o, parent ); } \
  static inline bl_t xoico_che_result_a_defines_set_parent_block( const xoico_che_result* o ) { return true; } \
  static inline void xoico_che_result_set_parent_block_default( xoico_che_result* o, xoico_che_result_block_s* parent ){} \
  static inline st_s* xoico_che_result_a_create_st( const xoico_che_result* o ) { const xoico_che_result_spect_s* p = xoico_che_result_spect_s_get_aware( o ); assert( p->create_st ); return p->create_st( o ); } \
  static inline bl_t xoico_che_result_a_defines_create_st( const xoico_che_result* o ) { return true; } \
  st_s* xoico_che_result_create_st_default( const xoico_che_result* o ); \
  BETH_EXPAND_ITEM_xoico_che_result_plain_s \
  BETH_EXPAND_ITEM_xoico_che_result_adl_s \
  BETH_EXPAND_ITEM_xoico_che_result_arr_s \
  BETH_EXPAND_ITEM_xoico_che_result_block_s \
  BETH_EXPAND_ITEM_xoico_che_result_blm_init_s \
  BETH_EXPAND_ITEM_xoico_che_result_blm_down_s \
  static inline xoico_che_result* xoico_che_result_create_from_st( const st_s* st ){ xoico_che_result_arr_s* o = xoico_che_result_arr_s_create(); xoico_che_result_arr_s_push_st(o,st ); return  ((xoico_che_result*)(o));} \
  static inline xoico_che_result* xoico_che_result_create_from_sc( sc_t sc ){ xoico_che_result_arr_s* o = xoico_che_result_arr_s_create(); xoico_che_result_arr_s_push_sc(o,sc ); return  ((xoico_che_result*)(o));} \
  static inline xoico_che_result* xoico_che_result_create_arr( void ){ return  ((xoico_che_result*)(xoico_che_result_arr_s_create()));} \
  static inline xoico_che_result* xoico_che_result_create_blm_init( sz_t level ){ xoico_che_result_blm_init_s* o = xoico_che_result_blm_init_s_create(); o->level = level; return  ((xoico_che_result*)(o));} \
  static inline xoico_che_result* xoico_che_result_create_blm_down( void ){ xoico_che_result_blm_down_s* o = xoico_che_result_blm_down_s_create(); return  ((xoico_che_result*)(o));}

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_che_stack_var

#define TYPEOF_xoico_che_stack_var 0xF75B684392B1C239ull
#define TYPEOF_xoico_che_stack_var_spect_s 0x4665A78B9BA34235ull
#define TYPEOF_xoico_che_stack_var_unit_s 0x9BFADBA0594B3466ull
#define BETH_EXPAND_ITEM_xoico_che_stack_var_unit_s \
  BCORE_DECLARE_OBJECT( xoico_che_stack_var_unit_s ) \
  { \
      aware_t _; \
      sz_t level; \
      tp_t name; \
      xoico_typespec_s typespec; \
  };
#define TYPEOF_xoico_che_stack_var_unit_adl_s 0x9CED3741467BD3AAull
#define BETH_EXPAND_ITEM_xoico_che_stack_var_unit_adl_s \
  BCORE_DECLARE_OBJECT( xoico_che_stack_var_unit_adl_s ) \
  { \
      aware_t _; \
      BCORE_ARRAY_DYN_LINK_STATIC_S( xoico_che_stack_var_unit_s, ); \
  }; \
  static inline xoico_che_stack_var_unit_adl_s* xoico_che_stack_var_unit_adl_s_set_space( xoico_che_stack_var_unit_adl_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_xoico_che_stack_var_unit_adl_s, ( bcore_array* )o, size ); return o; } \
  static inline xoico_che_stack_var_unit_adl_s* xoico_che_stack_var_unit_adl_s_set_size( xoico_che_stack_var_unit_adl_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_xoico_che_stack_var_unit_adl_s, ( bcore_array* )o, size ); return o; } \
  static inline xoico_che_stack_var_unit_adl_s* xoico_che_stack_var_unit_adl_s_clear( xoico_che_stack_var_unit_adl_s* o ) { bcore_array_t_set_space( TYPEOF_xoico_che_stack_var_unit_adl_s, ( bcore_array* )o, 0 ); return o; } \
  static inline xoico_che_stack_var_unit_s* xoico_che_stack_var_unit_adl_s_push_c( xoico_che_stack_var_unit_adl_s* o, const xoico_che_stack_var_unit_s* v ) { bcore_array_t_push( TYPEOF_xoico_che_stack_var_unit_adl_s, ( bcore_array* )o, sr_twc( TYPEOF_xoico_che_stack_var_unit_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline xoico_che_stack_var_unit_s* xoico_che_stack_var_unit_adl_s_push_d( xoico_che_stack_var_unit_adl_s* o,       xoico_che_stack_var_unit_s* v ) { bcore_array_t_push( TYPEOF_xoico_che_stack_var_unit_adl_s, ( bcore_array* )o, sr_tsd( TYPEOF_xoico_che_stack_var_unit_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline xoico_che_stack_var_unit_s* xoico_che_stack_var_unit_adl_s_push( xoico_che_stack_var_unit_adl_s* o ) \
  { \
      bcore_array_t_push( TYPEOF_xoico_che_stack_var_unit_adl_s, ( bcore_array* )o, sr_t_create( TYPEOF_xoico_che_stack_var_unit_s ) ); \
      return o->data[ o->size - 1 ]; \
  }
#define TYPEOF_xoico_che_stack_var_s 0x96453649A2A44113ull
#define BETH_EXPAND_ITEM_xoico_che_stack_var_s \
  BCORE_DECLARE_OBJECT( xoico_che_stack_var_s ) \
  { \
      aware_t _; \
      xoico_che_stack_var_unit_adl_s adl; \
      bcore_hmap_tpuz_s hmap_name; \
  }; \
  static inline bl_t xoico_che_stack_var_s_exists( const xoico_che_stack_var_s* o, tp_t name ); \
  void xoico_che_stack_var_s_rehash_names( xoico_che_stack_var_s* o ); \
  xoico_che_stack_var_s* xoico_che_stack_var_s_push_unit( xoico_che_stack_var_s* o, const xoico_che_stack_var_unit_s* unit ); \
  xoico_che_stack_var_s* xoico_che_stack_var_s_pop_level( xoico_che_stack_var_s* o, sz_t level ); \
  const xoico_typespec_s* xoico_che_stack_var_s_get_typespec( const xoico_che_stack_var_s* o, tp_t name ); \
  const sz_t xoico_che_stack_var_s_get_level( const xoico_che_stack_var_s* o, tp_t name ); \
  void xoico_che_stack_var_s_clear( xoico_che_stack_var_s* o ); \
  static inline bl_t xoico_che_stack_var_s_exists( const xoico_che_stack_var_s* o, tp_t name ){ return  bcore_hmap_tpuz_s_exists(&(o->hmap_name),name );}
#define BETH_EXPAND_GROUP_xoico_che_stack_var \
  BCORE_FORWARD_OBJECT( xoico_che_stack_var ); \
  BCORE_FORWARD_OBJECT( xoico_che_stack_var_unit_s ); \
  BCORE_FORWARD_OBJECT( xoico_che_stack_var_unit_adl_s ); \
  BCORE_FORWARD_OBJECT( xoico_che_stack_var_s ); \
  XOILA_DECLARE_SPECT( xoico_che_stack_var ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( xoico_che_stack_var ) \
  BETH_EXPAND_ITEM_xoico_che_stack_var_unit_s \
  BETH_EXPAND_ITEM_xoico_che_stack_var_unit_adl_s \
  BETH_EXPAND_ITEM_xoico_che_stack_var_s

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_che_stack_block

#define TYPEOF_xoico_che_stack_block 0x76EDF8EFC9052609ull
#define TYPEOF_xoico_che_stack_block_spect_s 0x7EE87EF40F9FDB45ull
#define TYPEOF_xoico_che_stack_block_unit_s 0x659D8B2B0B243DF6ull
#define BETH_EXPAND_ITEM_xoico_che_stack_block_unit_s \
  BCORE_DECLARE_OBJECT( xoico_che_stack_block_unit_s ) \
  { \
      aware_t _; \
      sz_t level; \
      bl_t use_blm; \
      bl_t break_ledge; \
  };
#define TYPEOF_xoico_che_stack_block_unit_adl_s 0xA5237D94C1D2339Aull
#define BETH_EXPAND_ITEM_xoico_che_stack_block_unit_adl_s \
  BCORE_DECLARE_OBJECT( xoico_che_stack_block_unit_adl_s ) \
  { \
      aware_t _; \
      BCORE_ARRAY_DYN_LINK_STATIC_S( xoico_che_stack_block_unit_s, ); \
  }; \
  static inline xoico_che_stack_block_unit_adl_s* xoico_che_stack_block_unit_adl_s_set_space( xoico_che_stack_block_unit_adl_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_xoico_che_stack_block_unit_adl_s, ( bcore_array* )o, size ); return o; } \
  static inline xoico_che_stack_block_unit_adl_s* xoico_che_stack_block_unit_adl_s_set_size( xoico_che_stack_block_unit_adl_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_xoico_che_stack_block_unit_adl_s, ( bcore_array* )o, size ); return o; } \
  static inline xoico_che_stack_block_unit_adl_s* xoico_che_stack_block_unit_adl_s_clear( xoico_che_stack_block_unit_adl_s* o ) { bcore_array_t_set_space( TYPEOF_xoico_che_stack_block_unit_adl_s, ( bcore_array* )o, 0 ); return o; } \
  static inline xoico_che_stack_block_unit_s* xoico_che_stack_block_unit_adl_s_push_c( xoico_che_stack_block_unit_adl_s* o, const xoico_che_stack_block_unit_s* v ) { bcore_array_t_push( TYPEOF_xoico_che_stack_block_unit_adl_s, ( bcore_array* )o, sr_twc( TYPEOF_xoico_che_stack_block_unit_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline xoico_che_stack_block_unit_s* xoico_che_stack_block_unit_adl_s_push_d( xoico_che_stack_block_unit_adl_s* o,       xoico_che_stack_block_unit_s* v ) { bcore_array_t_push( TYPEOF_xoico_che_stack_block_unit_adl_s, ( bcore_array* )o, sr_tsd( TYPEOF_xoico_che_stack_block_unit_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline xoico_che_stack_block_unit_s* xoico_che_stack_block_unit_adl_s_push( xoico_che_stack_block_unit_adl_s* o ) \
  { \
      bcore_array_t_push( TYPEOF_xoico_che_stack_block_unit_adl_s, ( bcore_array* )o, sr_t_create( TYPEOF_xoico_che_stack_block_unit_s ) ); \
      return o->data[ o->size - 1 ]; \
  }
#define TYPEOF_xoico_che_stack_block_s 0x820182B10F7DB5A3ull
#define BETH_EXPAND_ITEM_xoico_che_stack_block_s \
  BCORE_DECLARE_OBJECT( xoico_che_stack_block_s ) \
  { \
      aware_t _; \
      xoico_che_stack_block_unit_adl_s adl; \
  }; \
  static inline xoico_che_stack_block_s* xoico_che_stack_block_s_push( xoico_che_stack_block_s* o ); \
  static inline xoico_che_stack_block_s* xoico_che_stack_block_s_push_unit( xoico_che_stack_block_s* o, const xoico_che_stack_block_unit_s* unit ); \
  xoico_che_stack_block_s* xoico_che_stack_block_s_pop( xoico_che_stack_block_s* o ); \
  static inline void xoico_che_stack_block_s_clear( xoico_che_stack_block_s* o ); \
  static inline sz_t xoico_che_stack_block_s_get_size( const xoico_che_stack_block_s* o ); \
  static inline xoico_che_stack_block_s* xoico_che_stack_block_s_push( xoico_che_stack_block_s* o ){ xoico_che_stack_block_unit_adl_s_push_d( &(o->adl),xoico_che_stack_block_unit_s_create() ); return  o;} \
  static inline xoico_che_stack_block_s* xoico_che_stack_block_s_push_unit( xoico_che_stack_block_s* o, const xoico_che_stack_block_unit_s* unit ){ xoico_che_stack_block_unit_adl_s_push_c( &(o->adl),unit ); return  o;} \
  static inline void xoico_che_stack_block_s_clear( xoico_che_stack_block_s* o ){ xoico_che_stack_block_unit_adl_s_clear( &(o->adl));} \
  static inline sz_t xoico_che_stack_block_s_get_size( const xoico_che_stack_block_s* o ){ return  o->adl.size;}
#define BETH_EXPAND_GROUP_xoico_che_stack_block \
  BCORE_FORWARD_OBJECT( xoico_che_stack_block ); \
  BCORE_FORWARD_OBJECT( xoico_che_stack_block_unit_s ); \
  BCORE_FORWARD_OBJECT( xoico_che_stack_block_unit_adl_s ); \
  BCORE_FORWARD_OBJECT( xoico_che_stack_block_s ); \
  XOILA_DECLARE_SPECT( xoico_che_stack_block ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( xoico_che_stack_block ) \
  BETH_EXPAND_ITEM_xoico_che_stack_block_unit_s \
  BETH_EXPAND_ITEM_xoico_che_stack_block_unit_adl_s \
  BETH_EXPAND_ITEM_xoico_che_stack_block_s

/**********************************************************************************************************************/

vd_t xoico_xoila_out_signal_handler( const bcore_signal_s* o );

#endif // XOICO_XOILA_OUT_H
// XOILA_OUT_SIGNATURE 0x84F15EF91C0BD3E6ull
