/** This file was generated from xoila source code.
 *  Compiling Agent : xoico_compiler (C) 2020 J.B.Steffens
 *  Last File Update: 2020-12-07T20:52:09Z
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
 *  xoico_transient_map.h
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
 *  xoico_che.h
 *  xoico_body.x
 *  xoico_builder.x
 *  xoico_che.x
 *  xoico_che_builtin.x
 *  xoico_che_control.x
 *  xoico_compiler.x
 *  xoico_feature.x
 *  xoico_func.x
 *  xoico_group.x
 *  xoico_signature.x
 *  xoico_stamp.x
 *  xoico_target.x
 *  xoico_typespec.x
 *
 */

#include "xoico.xo.h"
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
    "feature aware xoico : get_hash;"
    "feature aware xoico : get_global_name_sc;"
    "feature aware xoico : get_global_name_tp = xoico_get_global_name_tp_default;"
    "feature aware xoico : parse;"
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

er_t xoico_parse_f( bcore_source* source, sc_t format )
{
    // xoico.h:92:1
    
    return  bcore_source_a_parse_em_fa( source,format );
}

er_t xoico_embed_file_open( bcore_source* parent, sc_t file_name, bcore_source** include_source )
{
    // xoico.h:99:102
    BLM_INIT_LEVEL(0);
    st_s* folder = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,bcore_file_folder_path(bcore_source_a_get_file(parent) )));
    if( folder->size == 0 ) st_s_push_char(folder,'.' );
    
    st_s* path = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    if( file_name[ 0 ] == '/' )
    {
        st_s_copy_sc(path,file_name );
    }
    else
    {
        st_s_copy_fa(path,"#<sc_t>/#<sc_t>", folder->sc, file_name );
    }
    
    if( !bcore_file_exists(path->sc ) )
    {
        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(parent,"Xoico: File '#<sc_t>' not found.", path->sc ))
    }
    
    (*(include_source)) = bcore_file_open_source(path->sc );
    BLM_RETURNV(er_t, 0)
}

er_t xoico_parse_sc( xoico* o, const xoico_host* host, sc_t sc )
{
    // xoico.h:126:1
    BLM_INIT_LEVEL(0);
    BLM_RETURNV(er_t, xoico_a_parse(o,host,((bcore_source*)( ((bcore_source_string_s*)BLM_LEVEL_T_PUSH(0,bcore_source_string_s,bcore_source_string_s_create_sc(sc ))) ))))
}

er_t xoico_parse_fa( xoico* o, const xoico_host* host, sc_t format, ... )
{
    // xoico.h:133:1
    BLM_INIT_LEVEL(0);
    va_list args;
    va_start( args, format );
    er_t ret = xoico_a_parse(o,host,((bcore_source*)( ((bcore_source_string_s*)BLM_LEVEL_T_PUSH(0,bcore_source_string_s,bcore_source_string_s_create_fv(format, args ))) )));
    va_end( args );
    BLM_RETURNV(er_t, ret)
}

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_host

XOILA_DEFINE_SPECT( xoico, xoico_host )
"{"
    "bcore_spect_header_s header;"
    "feature aware xoico_host : parse_name = xoico_host_parse_name_default;"
    "feature aware xoico_host : compiler = xoico_host_compiler_default;"
    "feature aware xoico_host : cengine = xoico_host_cengine_default;"
    "feature aware xoico_host : obj_type = xoico_host_obj_type_default;"
    "feature aware xoico_host : create_spect_name = xoico_host_create_spect_name_default;"
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
    "bcore_source_point_s source_point;"
    "func xoico:parse;"
    "func xoico:get_hash;"
    "func xoico:get_global_name_tp;"
    "func xoico:expand_declaration;"
    "func xoico:expand_init1;"
"}";

er_t xoico_name_s_parse( xoico_name_s* o, const xoico_host* host, bcore_source* source )
{
    // xoico_name.h:34:24
    BLM_INIT_LEVEL(0);
    xoico_compiler_s* compiler = xoico_host_a_compiler(host);
    bcore_source_point_s_set(&(o->source_point),source );
    st_s* st_name = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    BLM_TRY(xoico_host_a_parse_name(host,source, st_name ))
    if( st_name->size == 0 ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Name missing." ))
    o->name = xoico_compiler_s_entypeof(compiler,st_name->sc );
    BLM_TRY(bcore_source_a_parse_em_fa(source," ; " ))
    BLM_RETURNV(er_t, 0)
}

tp_t xoico_name_s_get_hash( const xoico_name_s* o )
{
    // xoico_name.h:47:5
    
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
    hash = bcore_tp_fold_tp( hash, o->name );
    return  hash;
}

er_t xoico_name_s_expand_declaration( const xoico_name_s* o, const xoico_host* host, sz_t indent, bcore_sink* sink )
{
    // xoico_name.h:56:5
    
    bcore_sink_a_push_fa(sink,"#rn{ }##define TYPEOF_#<sc_t> 0x#pl16'0'{#X<tp_t>}ull\n", indent, xoico_compiler_s_nameof(xoico_host_a_compiler(host),o->name ), o->name );
    return  0;
}

er_t xoico_name_s_expand_init1( const xoico_name_s* o, const xoico_host* host, sz_t indent, bcore_sink* sink )
{
    // xoico_name.h:62:5
    
    bcore_sink_a_push_fa(sink,"#rn{ }BCORE_REGISTER_NAME( #<sc_t> );\n", indent, xoico_compiler_s_nameof(xoico_host_a_compiler(host),o->name ) );
    return  0;
}

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

er_t xoico_forward_s_parse( xoico_forward_s* o, const xoico_host* host, bcore_source* source )
{
    // xoico_forward.h:34:24
    BLM_INIT_LEVEL(0);
    bcore_source_point_s_set(&(o->source_point),source );
    if( bcore_source_a_parse_bl(source," #?':'" ) )
    {
        st_s* name = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
        BLM_TRY(bcore_source_a_parse_em_fa(source," #name", name ))
        st_s_push_fa(&(o->name),"#<sc_t>#<sc_t>#<sc_t>", o->group->st_name.sc, name->sc[ 0 ] ? "_" : "", name->sc );
    }
    else
    {
        BLM_TRY(bcore_source_a_parse_em_fa(source," #name", (&(o->name)) ))
    }
    if( o->name.size == 0 ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Feature: Name missing." ))
    BLM_TRY(bcore_source_a_parse_em_fa(source," ; " ))
    BLM_RETURNV(er_t, 0)
}

tp_t xoico_forward_s_get_hash( const xoico_forward_s* o )
{
    // xoico_forward.h:53:5
    
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
    hash = bcore_tp_fold_sc( hash, o->name.sc );
    return  hash;
}

er_t xoico_forward_s_expand_declaration( const xoico_forward_s* o, const xoico_host* host, sz_t indent, bcore_sink* sink )
{
    // xoico_forward.h:61:37
    
    bcore_sink_a_push_fa(sink,"#rn{ }##define TYPEOF_#<sc_t> 0x#pl16'0'{#X<tp_t>}ull\n", indent, o->name.sc, btypeof( o->name.sc ) );
    return  0;
}

er_t xoico_forward_s_expand_forward( const xoico_forward_s* o, const xoico_host* host, sz_t indent, bcore_sink* sink )
{
    // xoico_forward.h:67:33
    
    bcore_sink_a_push_fa(sink," \\\n#rn{ }BCORE_FORWARD_OBJECT( #<sc_t> );", indent, o->name.sc );
    return  0;
}

XOILA_DEFINE_SPECT( xoico, xoico_forward )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/
// source: xoico_typespec.h
#include "xoico_typespec.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_typespec; embeds: xoico_typespec.x

BCORE_DEFINE_OBJECT_INST_P( xoico_typespec_s )
"aware xoico_typespec"
"{"
    "tp_t type;"
    "tp_t transient_class;"
    "sz_t indirection;"
    "bl_t flag_const;"
    "bl_t flag_static;"
    "bl_t flag_volatile;"
    "bl_t flag_restrict;"
    "bl_t flag_unaware;"
    "bl_t flag_scope;"
    "bl_t flag_addressable = true;"
    "bl_t flag_variadic;"
    "func xoico:get_hash;"
"}";

er_t xoico_typespec_s_relent( xoico_typespec_s* o, const xoico_host* host, tp_t tp_obj_type )
{
    // xoico_typespec.h:58:5
    
    if( o->type == TYPEOF_type_object ) o->type = tp_obj_type;
    return  0;
}

void xoico_typespec_s_reset( xoico_typespec_s* o )
{
    // xoico_typespec.h:67:5
    
    o->type = 0;
    o->indirection = 0;
    o->flag_const    = false;
    o->flag_static   = false;
    o->flag_volatile = false;
    o->flag_restrict = false;
    o->flag_scope    = false;
    o->flag_addressable = true;  // object can have a pointer ('false' for objects returned by a function)
}

er_t xoico_typespec_s_parse( xoico_typespec_s* o, const xoico_host* host, bcore_source* source )
{
    // xoico_typespec.x:20:20
    BLM_INIT_LEVEL(0);
    xoico_typespec_s_reset(o);
    xoico_compiler_s* compiler = xoico_host_a_compiler(host);
    
    if( bcore_source_a_parse_bl(source,"#?'...' " ) )
    {
        o->flag_variadic = true;
        BLM_RETURNV(er_t, 0)
    }
    
    while( !bcore_source_a_eos(source) )
    {
        if     ( bcore_source_a_parse_bl(source," #?'const'"    ) ) o->flag_const = true;
        else if( bcore_source_a_parse_bl(source," #?'static'"   ) ) o->flag_static = true;
        else if( bcore_source_a_parse_bl(source," #?'volatile'" ) ) o->flag_volatile = true;
        else if( bcore_source_a_parse_bl(source," #?'scope'"    ) ) o->flag_scope = true;
        else if( bcore_source_a_parse_bl(source," #?'unaware'"  ) ) o->flag_unaware = true;
        else break;
    }
    
    BLM_TRY(bcore_source_a_parse_em_fa(source," " ))
    
    if( bcore_source_a_parse_bl(source,"#?'(' " ) )
    {
        st_s* s = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
        BLM_TRY(bcore_source_a_parse_em_fa(source,"#name ", s ))
        if( s->size == 0 ) BLM_TRY(bcore_source_a_parse_error_fa(source,"Transient class: Identifier expected." ))
        o->transient_class = xoico_compiler_s_entypeof( compiler,s->sc );
        BLM_TRY(bcore_source_a_parse_em_fa(source," ) " ))
    }
    
    st_s* s = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    if( bcore_source_a_parse_bl(source,"#=?':'" ) )
    {
        BLM_TRY(xoico_host_a_parse_name(host,source, s ))
        o->type = xoico_compiler_s_entypeof(compiler,s->sc );
        bcore_source_a_parse_fa(source," " );
    }
    else if( bcore_source_a_parse_bl(source,"#?'@' " ) )
    {
        o->type = TYPEOF_type_object;
    }
    else if( bcore_source_a_parse_bl(source,"#?'$' " ) )
    {
        o->type = TYPEOF_type_deduce;
    }
    else
    {
        BLM_TRY(bcore_source_a_parse_em_fa(source,"#name ", s ))
        if( s->size == 0 ) BLM_TRY(bcore_source_a_parse_error_fa(source,"Argument: Type expected." ))
        o->type = xoico_compiler_s_entypeof( compiler,s->sc );
    }
    
    if( bcore_source_a_parse_bl(source,"#?'.' " ) )
    {
        if( !bcore_source_a_parse_bl(source,"#?([0]>='0'||[0]<='1') " ) ) BLM_TRY(bcore_source_a_parse_error_fa(source,"Argument: Indirection literal expected." ))
        sz_t indirection = 0;
        bcore_source_a_parse_fa(source,"#<sz_t*> ", (&(indirection)) );
        o->indirection = indirection;
    }
    else
    {
        while( bcore_source_a_parse_bl(source,"#?'*' " ) ) o->indirection++;
    }
    
    if( bcore_source_a_parse_bl(source," #?'restrict' " ) ) o->flag_restrict = true;
    
    BLM_RETURNV(er_t, 0)
}

tp_t xoico_typespec_s_get_hash( const xoico_typespec_s* o )
{
    // xoico_typespec.x:94:1
    
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
    hash = bcore_tp_fold_bl( hash, o->flag_const );
    hash = bcore_tp_fold_bl( hash, o->flag_static );
    hash = bcore_tp_fold_bl( hash, o->flag_volatile );
    hash = bcore_tp_fold_bl( hash, o->flag_restrict );
    hash = bcore_tp_fold_bl( hash, o->flag_scope );
    hash = bcore_tp_fold_tp( hash, o->type );
    hash = bcore_tp_fold_u3( hash, o->indirection );
    return  hash;
}

er_t xoico_typespec_s_expand( const xoico_typespec_s* o, const xoico_host* host, bcore_sink* sink )
{
    // xoico_typespec.x:108:21
    BLM_INIT_LEVEL(0);
    if( o->flag_variadic )
    {
        bcore_sink_a_push_fa(sink,"..." );
        BLM_RETURNV(er_t, 0)
    }
    
    xoico_compiler_s* compiler = xoico_host_a_compiler(host);
    
    tp_t type = o->type;
    
    if( type == TYPEOF_type_object )
    {
        //if( !sc_obj_type ) ERR_fa( "Cannot resolve 'type_object' at this point." );
        type = xoico_host_a_obj_type(host); //compiler.entypeof( sc_obj_type );
    }
    else if( type == TYPEOF_type_deduce )
    {
        ERR_fa( "Cannot resolve 'type_deduce' at this point." );
    }
    
    st_s* st_type = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create_sc(xoico_compiler_s_nameof(compiler,type ) )));
    
    sc_t sc_type = st_type->sc;
    if( o->flag_static   ) bcore_sink_a_push_fa(sink,"static " );
    if( o->flag_const    ) bcore_sink_a_push_fa(sink,"const " );
    if( o->flag_volatile ) bcore_sink_a_push_fa(sink,"volatile " );
    bcore_sink_a_push_fa(sink,"#<sc_t>", sc_type );
    
    for( sz_t i = 0; i < o->indirection; i++ ) bcore_sink_a_push_fa(sink,"*" );
    if( o->flag_restrict ) bcore_sink_a_push_fa(sink,"restrict " );
    
    BLM_RETURNV(er_t, 0)
}

bl_t xoico_typespec_s_converts_to( const xoico_typespec_s* o, const xoico_typespec_s* b )
{
    // xoico_typespec.x:174:1
    
    if( o->type == b->type )
    {
        if( o->indirection == b->indirection )
        {
            if( o->flag_const )
            {
                return  b->flag_const;
            }
            else
            {
                return  true;
            }
        }
        else
        {
            return  false;
        }
    }
    else
    {
        if( o->indirection == 0 && b->indirection == 0 )
        {
            if( xoico_typespec_is_numeric(o->type ) && xoico_typespec_is_numeric(b->type ) )
            {
                return  true;
            }
            else if( b->type == TYPEOF_vd_t && b->type == TYPEOF_vc_t )
            {
                return  true;
            }
            else
            {
                return  false;
            }
        }
        else if( b->type == TYPEOF_vc_t && b->indirection == 0 )
        {
            if( o->indirection == 1 )
            {
                return  true;
            }
            else
            {
                return  false;
            }
        }
        else if( b->type == TYPEOF_vd_t && b->indirection == 0 )
        {
            if( o->indirection == 1 && !o->flag_const )
            {
                return  true;
            }
            else
            {
                return  false;
            }
        }
        else
        {
            return  false;
        }
    }
}

XOILA_DEFINE_SPECT( xoico, xoico_typespec )
"{"
    "bcore_spect_header_s header;"
"}";

bl_t xoico_typespec_is_numeric( tp_t type )
{
    // xoico_typespec.x:147:1
    
    switch( type )
    {
        case TYPEOF_u0_t: return  true;
        case TYPEOF_u1_t: return  true;
        case TYPEOF_u2_t: return  true;
        case TYPEOF_u3_t: return  true;
        case TYPEOF_s0_t: return  true;
        case TYPEOF_s1_t: return  true;
        case TYPEOF_s2_t: return  true;
        case TYPEOF_s3_t: return  true;
        case TYPEOF_f2_t: return  true;
        case TYPEOF_f3_t: return  true;
        case TYPEOF_sz_t: return  true;
        case TYPEOF_uz_t: return  true;
        case TYPEOF_tp_t: return  true;
        case TYPEOF_er_t: return  true;
        case TYPEOF_bl_t: return  true;
        case TYPEOF_char: return  true;
        default: break;
    }
    return  false;
}

/**********************************************************************************************************************/
// source: xoico_transient_map.h
#include "xoico_transient_map.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_transient_map

BCORE_DEFINE_OBJECT_INST_P( xoico_transient_map_s )
"aware xoico_transient_map"
"{"
    "bcore_hmap_tptp_s map;"
    "func xoico:parse;"
"}";

er_t xoico_transient_map_s_parse( xoico_transient_map_s* o, const xoico_host* host, bcore_source* source )
{
    // xoico_transient_map.h:45:24
    BLM_INIT_LEVEL(0);
    bcore_hmap_tptp_s_clear(&(o->map));
    xoico_compiler_s* compiler = xoico_host_a_compiler(host);
    BLM_TRY(bcore_source_a_parse_em_fa(source,"( " ))
    st_s* s = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    
    while( !bcore_source_a_eos(source) )
    {
        BLM_TRY(bcore_source_a_parse_em_fa(source,"#name ", s ))
        if( s->size == 0 ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Transient class name expected." ))
        tp_t key = xoico_compiler_s_entypeof(compiler,s->sc );
        BLM_TRY(bcore_source_a_parse_em_fa(source,"#name ", s ))
        if( s->size == 0 ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Type name expected." ))
        tp_t type = xoico_compiler_s_entypeof(compiler,s->sc );
        bcore_hmap_tptp_s_set(&(o->map),key, type );
        if( bcore_source_a_parse_bl(source,"#?')' " ) ) break;
        BLM_TRY(bcore_source_a_parse_em_fa(source,", " ))
    };
    
    BLM_RETURNV(er_t, 0)
}

XOILA_DEFINE_SPECT( xoico, xoico_transient_map )
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
    "bcore_source_point_s source_point;"
    "xoico_typespec_s typespec;"
    "tp_t name;"
    "func xoico:parse;"
    "func xoico:get_hash;"
"}";

er_t xoico_arg_s_parse( xoico_arg_s* o, const xoico_host* host, bcore_source* source )
{
    // xoico_arg.h:42:24
    BLM_INIT_LEVEL(0);
    xoico_compiler_s* compiler = xoico_host_a_compiler(host);
    bcore_source_point_s_set(&(o->source_point),source );
    BLM_TRY(xoico_typespec_s_parse(&(o->typespec),host, source ))
    
    if( o->typespec.flag_variadic ) BLM_RETURNV(er_t, 0)
    
    if( o->typespec.type == TYPEOF_void && o->typespec.indirection == 0 )
    {
        BLM_RETURNV(er_t, bcore_source_point_s_parse_error_fa(&(o->source_point),"'void' is misplaced here." ))
    }
    
    st_s* s = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    BLM_TRY(bcore_source_a_parse_em_fa(source,"#name ", s ))
    if( s->size == 0 )
    {
        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Argument: Name expected." ))
    }
    o->name = xoico_compiler_s_entypeof(compiler,s->sc );
    
    BLM_RETURNV(er_t, 0)
}

tp_t xoico_arg_s_get_hash( const xoico_arg_s* o )
{
    // xoico_arg.h:69:1
    
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
    hash = bcore_tp_fold_tp( hash, xoico_typespec_s_get_hash(&(o->typespec)) );
    hash = bcore_tp_fold_tp( hash, o->name );
    return  hash;
}

er_t xoico_arg_s_relent( xoico_arg_s* o, const xoico_host* host, tp_t tp_obj_type )
{
    // xoico_arg.h:79:1
    
    return  xoico_typespec_s_relent(&(o->typespec),host, tp_obj_type );
}

er_t xoico_arg_s_expand( const xoico_arg_s* o, const xoico_host* host, bcore_sink* sink )
{
    // xoico_arg.h:86:1
    
    BLM_TRY(xoico_typespec_s_expand(&(o->typespec),host, sink ) )
    if( o->name )
    {
        bcore_sink_a_push_fa(sink," " );
        xoico_arg_s_expand_name(o,host, sink );
    }
    return  0;
}

er_t xoico_arg_s_expand_name( const xoico_arg_s* o, const xoico_host* host, bcore_sink* sink )
{
    // xoico_arg.h:99:1
    
    if( !o->name ) return  0;
    bcore_sink_a_push_fa(sink,"#<sc_t>", xoico_compiler_s_nameof(xoico_host_a_compiler(host),o->name ) );
    return  0;
}

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
"aware x_array"
"{"
    "xoico_arg_s => [];"
    "func xoico:parse;"
    "func xoico:get_hash;"
"}";

er_t xoico_args_s_append( xoico_args_s* o, const xoico_host* host, bcore_source* source )
{
    // xoico_args.h:39:83
    BLM_INIT_LEVEL(0);
    bl_t first = true;
    while( !bcore_source_a_parse_bl(source," #=?')' " ) ) // args follow
    {
        if( xoico_args_s_is_variadic(o) ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Cannot append to variadic argument list." ))
        if( !first ) BLM_TRY(xoico_parse_f(source, " , " ))
        xoico_arg_s* arg = ((xoico_arg_s*)BLM_LEVEL_T_PUSH(0,xoico_arg_s,xoico_arg_s_create()));
        BLM_TRY(xoico_arg_s_parse(arg,host, source ))
        ((xoico_arg_s*)(x_array_push_d(((x_array*)(o)),((x_inst*)(((xoico_arg_s*)bcore_fork(arg)) )))));
        first = false;
    }
    BLM_RETURNV(er_t, 0)
}

er_t xoico_args_s_relent( xoico_args_s* o, const xoico_host* host, tp_t tp_obj_type )
{
    // xoico_args.h:55:1
    
    {const xoico_args_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_arg_s* arg=__a->data[__i]; BLM_TRY(xoico_arg_s_relent(arg,host, tp_obj_type ))
    }}return  0;
}

er_t xoico_args_s_expand( const xoico_args_s* o, const xoico_host* host, bl_t first, bcore_sink* sink )
{
    // xoico_args.h:61:1
    
    {const xoico_args_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_arg_s* arg=__a->data[__i];
    {
        if( !first ) bcore_sink_a_push_fa(sink,", " );
        first = false;
        BLM_TRY(xoico_arg_s_expand(arg,host, sink ))
    }
    }}return  0;
}

er_t xoico_args_s_expand_name( const xoico_args_s* o, const xoico_host* host, bl_t first, bcore_sink* sink )
{
    // xoico_args.h:72:1
    
    {const xoico_args_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_arg_s* arg=__a->data[__i];
    {
        if( !first ) bcore_sink_a_push_fa(sink,", " );
        first = false;
        BLM_TRY(xoico_arg_s_expand_name(arg,host, sink ))
    }
    }}return  0;
}

tp_t xoico_args_s_get_hash( const xoico_args_s* o )
{
    // xoico_args.h:83:1
    
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
    {const xoico_args_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_arg_s* arg=__a->data[__i]; hash = bcore_tp_fold_tp( hash, xoico_arg_s_get_hash(arg) );}}
    return  hash;
}

XOILA_DEFINE_SPECT( xoico, xoico_args )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/
// source: xoico_signature.h
#include "xoico_signature.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_signature; embeds: xoico_signature.x
#include "xoico_stamp.h"

BCORE_DEFINE_OBJECT_INST_P( xoico_signature_s )
"aware xoico_signature"
"{"
    "tp_t name;"
    "tp_t global_name;"
    "xoico_typespec_s typespec_ret;"
    "xoico_args_s args;"
    "tp_t arg_o;"
    "bl_t typed;"
    "tp_t arg_o_transient_class;"
    "bcore_source_point_s source_point;"
    "func xoico:get_global_name_tp;"
    "func xoico:get_hash;"
    "func xoico:parse;"
"}";

er_t xoico_signature_s_relent( xoico_signature_s* o, const xoico_host* host, tp_t tp_obj_type )
{
    // xoico_signature.h:53:5
    
    BLM_TRY(xoico_args_s_relent(&(o->args),host, tp_obj_type ))
    BLM_TRY(xoico_typespec_s_relent(&(o->typespec_ret),host, tp_obj_type ))
    return  0;
}

tp_t xoico_signature_s_get_hash( const xoico_signature_s* o )
{
    // xoico_signature.x:21:1
    
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
    hash = bcore_tp_fold_tp( hash, o->global_name );
    hash = bcore_tp_fold_tp( hash, xoico_typespec_s_get_hash(&(o->typespec_ret)) );
    hash = bcore_tp_fold_tp( hash, xoico_args_s_get_hash(&(o->args)) );
    hash = bcore_tp_fold_bl( hash, o->typed );
    hash = bcore_tp_fold_tp( hash, o->arg_o );
    return  hash;
}

er_t xoico_signature_s_parse( xoico_signature_s* o, const xoico_host* host, bcore_source* source )
{
    // xoico_signature.x:33:24
    BLM_INIT_LEVEL(0);
    bcore_source_point_s_set(&(o->source_point),source );
    xoico_compiler_s* compiler = xoico_host_a_compiler(host);
    
    st_s* name_buf = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    
    if( bcore_source_a_parse_bl(source," #?'extending'" ) )
    {
        BLM_TRY(xoico_host_a_parse_name(host,source, name_buf ))
        tp_t tp_name = xoico_compiler_s_entypeof(compiler,name_buf->sc );
    
        const xoico_signature_s* signature = xoico_compiler_s_get_signature(compiler,tp_name );
        if( !signature )
        {
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Could not find predefined signature '#<sc_t>'.", name_buf->sc ))
        }
    
        xoico_typespec_s_copy(&(o->typespec_ret),&(signature->typespec_ret ));
        xoico_args_s_copy(&(o->args),&(signature->args ));
        o->arg_o = signature->arg_o;
        o->typed = signature->typed;
    
        BLM_TRY(bcore_source_a_parse_em_fa(source," #name", name_buf ))
        if( name_buf->size == 0 ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Signature name missing." ))
        o->name = xoico_compiler_s_entypeof(compiler,name_buf->sc );
    
        BLM_TRY(bcore_source_a_parse_em_fa(source," (" ))
        BLM_TRY(xoico_args_s_append(&(o->args),host, source ))
        BLM_TRY(bcore_source_a_parse_em_fa(source," )" ))
    }
    else
    {
        BLM_TRY(xoico_typespec_s_parse(&(o->typespec_ret),host, source ))
        o->typespec_ret.flag_addressable = false;
    
        // get name
        BLM_TRY(bcore_source_a_parse_em_fa(source," #name", name_buf ))
        o->name = xoico_compiler_s_entypeof(compiler,name_buf->sc );
    
        BLM_TRY(bcore_source_a_parse_em_fa(source," (" ))
        if( bcore_source_a_parse_bl(source," #?'plain' " ) ) BLM_TRY(bcore_source_a_parse_error_fa(source,"Use of 'plain' is deprecated. Simply omit this argument." ))
    
        sz_t index = bcore_source_a_get_index(source);
    
        tp_t transient_class = 0;
        if( bcore_source_a_parse_bl(source,"#?'(' " ) )
        {
            st_s* s = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
            BLM_TRY(bcore_source_a_parse_em_fa(source,"#name ", s ))
            if( s->size == 0 ) BLM_TRY(bcore_source_a_parse_error_fa(source,"Transient class: Identifier expected." ))
            transient_class = xoico_compiler_s_entypeof(compiler,s->sc );
            BLM_TRY(bcore_source_a_parse_em_fa(source," ) " ))
        }
    
    
        if( bcore_source_a_parse_bl(source," #?'typed' " ) )
        {
            o->typed = true;
        }
    
        o->arg_o = 0;
        if( bcore_source_a_parse_bl(source," #?'mutable' " ) )
        {
            o->arg_o = TYPEOF_mutable;
        }
        else if( bcore_source_a_parse_bl(source," #=?'const'" ) )
        {
            BLM_TRY(bcore_source_a_parse_em_fa(source,"const " ))
            if( bcore_source_a_parse_bl(source,"#?([0]==','||[0]==')')" ) )
            {
                o->arg_o = TYPEOF_const;
            }
            else
            {
                // reset index (non-member functions)
                bcore_source_a_set_index(source,index );
            }
        }
    
        if( o->arg_o )
        {
            if( !bcore_source_a_parse_bl(source," #=?')'" ) ) BLM_TRY(bcore_source_a_parse_em_fa(source,", " ))
            o->arg_o_transient_class = transient_class;
        }
        else if( o->typed )
        {
            BLM_TRY(bcore_source_a_parse_error_fa(source,"'typed' can not be used on plain functions." ))
        }
    
        BLM_TRY(xoico_args_s_parse(&(o->args),host, source ))
        BLM_TRY(bcore_source_a_parse_em_fa(source," )" ))
    }
    
    sc_t sc_name = xoico_compiler_s_nameof(compiler,o->name );
    st_s_copy_fa(name_buf,"#<sc_t>_#<sc_t>", xoico_compiler_s_nameof(compiler,xoico_host_a_obj_type(host) ), sc_name );
    
    o->global_name = xoico_compiler_s_entypeof(compiler,name_buf->sc );
    
    if( o->typespec_ret.transient_class )
    {
        if( o->typespec_ret.type == TYPEOF_void && o->typespec_ret.indirection == 0 )
        {
            BLM_TRY(bcore_source_a_parse_error_fa(source,"'void' can not be a transient type." ))
        }
    }
    
    BLM_RETURNV(er_t, 0)
}

er_t xoico_signature_s_expand_declaration( const xoico_signature_s* o, const xoico_host* host, sc_t sc_func_global_name, sz_t indent, bcore_sink* sink )
{
    // xoico_signature.x:145:33
    
    sc_t sc_name = xoico_compiler_s_nameof(xoico_host_a_compiler(host),xoico_host_a_obj_type(host) );
    BLM_TRY(xoico_typespec_s_expand(&(o->typespec_ret),host, sink ))
    bcore_sink_a_push_fa(sink," #<sc_t>( ", sc_func_global_name );
    
    if( o->arg_o )
    {
        if( o->typed ) bcore_sink_a_push_sc(sink,"tp_t t, " );
        bcore_sink_a_push_fa(sink,"#<sc_t>", ( o->arg_o == TYPEOF_mutable ) ? "" : "const " );
        bcore_sink_a_push_fa(sink,"#<sc_t>* o", sc_name );
        BLM_TRY(xoico_args_s_expand(&(o->args),host, false, sink ))
        bcore_sink_a_push_fa(sink," )" );
    }
    else
    {
        if( o->args.size > 0 )
        {
            BLM_TRY(xoico_args_s_expand(&(o->args),host, true, sink ))
        }
        else
        {
            bcore_sink_a_push_fa(sink,"void" );
        }
        bcore_sink_a_push_fa(sink," )" );
    }
    return  0;
}

XOILA_DEFINE_SPECT( xoico, xoico_signature )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/
// source: xoico_body.h
#include "xoico_body.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_body; embeds: xoico_body.x
#include "xoico_stamp.h"
#include "xoico_cengine.h"

BCORE_DEFINE_OBJECT_INST_P( xoico_body_code_s )
"aware xoico_body"
"{"
    "bl_t single_line;"
    "tp_t hash_source;"
    "bcore_source_point_s source_point;"
    "func xoico:parse;"
    "func xoico:get_hash;"
"}";

er_t xoico_body_code_s_parse( xoico_body_code_s* o, const xoico_host* host, bcore_source* source )
{
    // xoico_body.x:20:28
    
    tp_t hash = bcore_tp_init();
    
    bcore_source_point_s_set(&(o->source_point),source );
    
    if( bcore_source_a_parse_bl(source," #?'('" ) )
    {
        while( !bcore_source_a_eos(source) && bcore_source_a_inspect_char(source) != ')' ) bcore_source_a_get_char(source);
        BLM_TRY(bcore_source_a_parse_em_fa(source,")" ))
    }
    
    BLM_TRY(bcore_source_a_parse_em_fa(source," {" ))
    
    sz_t nest_count = 1;
    bl_t exit_loop = false;
    o->single_line = true;
    
    while( bcore_source_a_parse_bl(source,"#?' '" ) ); // skip leading spaces
    
    while( !bcore_source_a_eos(source) && !exit_loop )
    {
        u0_t c =  bcore_source_a_get_u0(source);
        switch( c )
        {
            case '{':
            {
                nest_count++;
            }
            break;
    
            case '}':
            {
                nest_count--;
                if( !nest_count )
                {
                    c = 0;
                    exit_loop = true;
                }
            }
            break;
    
            case '"': // string literal
            {
                hash = bcore_tp_fold_u0( hash, c );
                while( !bcore_source_a_eos(source) && ((c = bcore_source_a_get_char(source)) != '"') )
                {
                    hash = bcore_tp_fold_u0( hash, c );
                    if( c == '\\' ) hash = bcore_tp_fold_u0( hash, bcore_source_a_get_u0(source) );
                    if( c == '\n' ) return  bcore_source_a_parse_error_fa(source,"Newline in string literal." );
                }
                c = 0;
            }
            break;
    
            case '\'': // char literal
            {
                hash = bcore_tp_fold_u0( hash, c );
                while( !bcore_source_a_eos(source) && ((c = bcore_source_a_get_char(source)) != '\'') )
                {
                    hash = bcore_tp_fold_u0( hash, c );
                    if( c == '\\' ) hash = bcore_tp_fold_u0( hash, bcore_source_a_get_u0( source ) );
                    if( c == '\n' ) return  bcore_source_a_parse_error_fa(source,"Newline in char literal." );
                }
                c = 0;
            }
            break;
    
            case '/': // comment
            {
                hash = bcore_tp_fold_u0( hash, c );
                if( bcore_source_a_inspect_char(source) == '/' )
                {
                    while( !bcore_source_a_eos(source) )
                    {
                        c = bcore_source_a_get_char(source);
                        hash = bcore_tp_fold_u0( hash, c );
                        if( c == '\n' )
                        {
                            o->single_line = false;
                            break;
                        }
                    }
                }
                else if( bcore_source_a_inspect_char(source) == '*' )
                {
                    while( !bcore_source_a_eos(source) )
                    {
                        if( bcore_source_a_parse_bl(source,"#?'*/'" ) )
                        {
                            hash = bcore_tp_fold_sc( hash, "*/" );
                            break;
                        }
                        else
                        {
                            c = bcore_source_a_get_char(source);
                            if( c == '\n' ) o->single_line = false;
                            hash = bcore_tp_fold_u0( hash, c );
                        }
                    }
                }
                c = 0;
            }
            break;
    
            case '\n' :
            {
                o->single_line = false;
                break;
            }
    
            default: break;
        }
        hash = bcore_tp_fold_u0( hash, c );
    }
    
    o->hash_source = hash;
    return  0;
}

tp_t xoico_body_code_s_get_hash( const xoico_body_code_s* o )
{
    // xoico_body.x:143:1
    
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
    hash = bcore_tp_fold_tp( hash, o->hash_source );
    return  hash;
}

BCORE_DEFINE_OBJECT_INST_P( xoico_body_s )
"aware xoico_body"
"{"
    "st_s name;"
    "st_s global_name;"
    "xoico_body_code_s => code;"
    "bl_t go_inline;"
    "bcore_source_point_s source_point;"
    "func xoico:get_global_name_sc;"
    "func xoico:get_hash;"
    "func xoico:parse;"
"}";

tp_t xoico_body_s_get_hash( const xoico_body_s* o )
{
    // xoico_body.x:156:1
    
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
    hash = bcore_tp_fold_sc( hash, o->name.sc );
    if( o->code ) hash = bcore_tp_fold_tp( hash, xoico_body_code_s_get_hash(o->code) );
    hash = bcore_tp_fold_bl( hash, o->go_inline );
    return  hash;
}

er_t xoico_body_s_parse_expression( xoico_body_s* o, const xoico_host* host, bcore_source* source )
{
    // xoico_body.x:166:31
    BLM_INIT_LEVEL(0);
    if( bcore_source_a_parse_bl(source," #=?'{'" ) || bcore_source_a_parse_bl(source," #=?'('" ) )
    {
        xoico_body_code_s_attach( &(o->code ),  xoico_body_code_s_create());
        BLM_TRY(xoico_body_code_s_parse(o->code,host, source ))
        o->go_inline = o->code->single_line;
    }
    else
    {
        xoico_compiler_s* compiler = xoico_host_a_compiler(host);
        st_s* st_name = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
        BLM_TRY(xoico_host_a_parse_name(host,source, st_name ))
    
        if( st_name->size == 0 ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Body name expected." ))
    
        tp_t tp_name = xoico_compiler_s_entypeof(compiler,st_name->sc );
    
        // if name_buf refers to another body
        if( xoico_compiler_s_is_body(compiler,tp_name ) )
        {
            const xoico_body_s* body = xoico_compiler_s_get_body(compiler,tp_name );
            xoico_body_code_s_attach( &(o->code ),  xoico_body_code_s_clone(body->code));
            o->go_inline = body->go_inline;
        }
        else
        {
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Cannot resolve body name '#<sc_t>'\n", st_name->sc ))
        }
    }
    BLM_RETURNV(er_t, 0)
}

er_t xoico_body_s_parse( xoico_body_s* o, const xoico_host* host, bcore_source* source )
{
    // xoico_body.x:201:24
    BLM_INIT_LEVEL(0);
    xoico_compiler_s* compiler = xoico_host_a_compiler(host);
    st_s* string = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    bcore_source_point_s_set(&(o->source_point),source );
    
    if( !bcore_source_a_parse_bl(source," #=?'='" ) )
    {
        BLM_TRY(bcore_source_a_parse_em_fa(source," #name", string ))
        if( string->size == 0 ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Body name expected." ))
        st_s_push_fa(&(o->name),"#<sc_t>", string->sc );
    }
    
    BLM_TRY(bcore_source_a_parse_em_fa(source," =" ))
    
    BLM_TRY(xoico_body_s_parse_expression(o,host, source ))
    st_s_copy_fa(&(o->global_name),"#<sc_t>_#<sc_t>", xoico_compiler_s_nameof(compiler,xoico_host_a_obj_type(host) ), o->name.sc );
    BLM_RETURNV(er_t, 0)
}

er_t xoico_body_s_expand( const xoico_body_s* o, const xoico_host* host, const xoico_signature_s* signature, sz_t indent, bcore_sink* sink )
{
    // xoico_body.x:223:21
    BLM_INIT_LEVEL(0);
    const st_s* final_code = NULL;
    st_s* st_out = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    
    xoico_cengine* cengine = xoico_host_a_cengine(host);
    ASSERT( cengine );
    
    if( o->code )
    {
        BLM_TRY(xoico_cengine_a_translate(cengine,host, o, signature, ( bcore_sink* )st_out ))
        final_code = st_out;
    }
    
    if( o->go_inline )
    {
        bcore_sink_a_push_fa(sink,"{#<sc_t>}", final_code->sc );
    }
    else
    {
        bcore_sink_a_push_fa(sink,"{\n#rn{ }", indent + 4 );
        for( sz_t i = 0; i < final_code->size; i++ )
        {
            char c = final_code->sc[ i ];
            bcore_sink_a_push_char(sink,c );
            if( c == '\n' ) bcore_sink_a_push_fa(sink,"#rn{ }", indent + 4 );
        }
        bcore_sink_a_push_fa(sink,"\n#rn{ }}", indent );
    }
    BLM_RETURNV(er_t, 0)
}

XOILA_DEFINE_SPECT( xoico, xoico_body )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/
// source: xoico_feature.h
#include "xoico_feature.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_feature; embeds: xoico_feature.x

BCORE_DEFINE_OBJECT_INST_P( xoico_feature_s )
"aware xoico_feature"
"{"
    "xoico_signature_s signature;"
    "xoico_funcs_s funcs;"
    "xoico_funcs_s funcs_return_to_group;"
    "tp_t function_pointer_name;"
    "st_s st_default_func_name;"
    "xoico_body_s => default_body;"
    "bl_t strict;"
    "bl_t flag_p;"
    "bl_t flag_t;"
    "bl_t flag_a;"
    "bl_t flag_r;"
    "bl_t expandable = true;"
    "bcore_source_point_s source_point;"
    "func xoico:get_global_name_tp;"
    "func xoico:get_hash;"
    "func xoico:parse;"
    "func xoico:finalize;"
    "func xoico:expand_forward;"
    "func xoico:expand_indef_typedef;"
    "func xoico:expand_spect_declaration;"
    "func xoico:expand_spect_definition;"
    "func xoico:expand_indef_declaration;"
    "func xoico:expand_definition;"
    "func xoico:expand_init1;"
"}";

tp_t xoico_feature_s_get_hash( const xoico_feature_s* o )
{
    // xoico_feature.x:21:1
    
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
    hash = bcore_tp_fold_tp( hash, xoico_signature_s_get_hash(&(o->signature)) );
    hash = bcore_tp_fold_tp( hash, o->default_body ? xoico_body_s_get_hash(o->default_body) : 0 );
    hash = bcore_tp_fold_bl( hash, o->strict );
    hash = bcore_tp_fold_bl( hash, o->flag_p );
    hash = bcore_tp_fold_bl( hash, o->flag_t );
    hash = bcore_tp_fold_bl( hash, o->flag_a );
    hash = bcore_tp_fold_bl( hash, o->flag_r );
    return  hash;
}

er_t xoico_feature_s_parse( xoico_feature_s* o, const xoico_host* host, bcore_source* source )
{
    // xoico_feature.x:35:24
    BLM_INIT_LEVEL(0);
    xoico_compiler_s* compiler = xoico_host_a_compiler(host);
    
    bcore_source_point_s_set(&(o->source_point),source );
    o->strict = bcore_source_a_parse_bl(source," #?w'strict' " );
    
    if( bcore_source_a_parse_bl(source," #?|'|" ) )
    {
        st_s* flags = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
        BLM_TRY(bcore_source_a_parse_em_fa(source," #until'''", flags ))
        for( sz_t i = 0; i < flags->size; i++ )
        {
            switch( flags->data[ i ] )
            {
                case 'p': o->flag_p = true; break;
                case 't': o->flag_t = true; break;
                case 'a': o->flag_a = true; break;
                case 'r': o->flag_r = true; break;
                default: BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Feature: Flag '#<char>' not handled. Choose from 'ptar'.", flags->data[ i ] ))
            }
        }
        BLM_TRY(bcore_source_a_parse_em_fa(source,"' " ))
    }
    else
    {
        /// the default feature is an aware one
        o->flag_a = true;
    }
    
    xoico_signature_s* signature =&( o->signature);
    BLM_TRY(xoico_signature_s_parse(signature,host, source ))
    
    if( !signature->arg_o )
    {
        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Feature: The first argument must be 'mutable' or 'const'." ))
    }
    
    if( bcore_source_a_parse_bl(source," #=?'=' " ) )
    {
        if( o->strict ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Feature is 'strict'. Default function would have no effect." ))
        o->default_body = xoico_body_s_create();
        BLM_TRY(xoico_body_s_parse(o->default_body,host, source ))
        st_s_copy_fa(&(o->st_default_func_name),"#<sc_t>_default", xoico_compiler_s_nameof(compiler,o->signature.name ) );
    }
    else if( bcore_source_a_parse_bl(source," #?w'extern' " ) )
    {
        st_s* st_name = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
        BLM_TRY(bcore_source_a_parse_em_fa(source," #name ", st_name ))
        if( st_name->size == 0 ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Feature: Default function name expected." ))
        st_s_copy_fa(&(o->st_default_func_name),"#<sc_t>_#<sc_t>", xoico_compiler_s_nameof(compiler,o->signature.name ), st_name->sc );
    }
    
    BLM_TRY(bcore_source_a_parse_em_fa(source," ; " ))
    
    o->function_pointer_name = o->signature.global_name;
    
    BLM_TRY(xoico_feature_s_setup_functions(o,host ))
    BLM_RETURNV(er_t, 0)
}

xoico_func_s* xoico_feature_s_create_func_from_sc( const xoico_feature_s* o, const xoico_host* host, sc_t sc )
{
    // xoico_feature.x:99:1
    
    xoico_func_s* func = xoico_func_s_create();
    xoico_parse_sc(((xoico*)(func)),host, sc );
    bcore_source_point_s_copy(&(func->source_point),(&(o->source_point)) );
    return  func;
}

xoico_func_s* xoico_feature_s_push_func_from_sc( xoico_feature_s* o, const xoico_host* host, sc_t sc )
{
    // xoico_feature.x:109:1
    
    return  ((xoico_func_s*)(x_array_push_d(((x_array*)(&(o->funcs))),((x_inst*)(xoico_feature_s_create_func_from_sc(o,host, sc ) )))));
}

er_t xoico_feature_s_setup_functions( xoico_feature_s* o, const xoico_host* host )
{
    // xoico_feature.x:115:70
    BLM_INIT_LEVEL(0);
    xoico_compiler_s* compiler = xoico_host_a_compiler(host);
    sc_t sc_name = xoico_compiler_s_nameof(compiler,o->signature.name );
    sc_t sc_obj_type = xoico_compiler_s_nameof(compiler,xoico_host_a_obj_type(host) );
    sc_t sc_spect_name = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,xoico_host_a_create_spect_name(host)))->sc;
    
    st_s* st_ret_typespec = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    BLM_TRY(xoico_typespec_s_expand(&(o->signature.typespec_ret),host,((bcore_sink*)( st_ret_typespec ))))
    bl_t has_ret = ( o->signature.typespec_ret.type != TYPEOF_void );
    sc_t sc_ret_typespec = st_ret_typespec->sc;
    bl_t flag_const = o->signature.arg_o == TYPEOF_const;
    
    bl_t always_defined = ( o->strict || o->default_body || o->st_default_func_name.size > 0 );
    
    if( o->flag_a )
    {
        st_s* st = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
        st_s_push_fa(st,"(#<sc_t> a_#<sc_t>(", sc_ret_typespec, sc_name );
        st_s_push_fa(st,flag_const ? " const" : " mutable" );
        BLM_TRY(xoico_args_s_expand(&(o->signature.args),host, false,((bcore_sink*)( st ))))
        st_s_push_fa(st," )) = (verbatim_C) { " );
        st_s_push_fa(st,"const #<sc_t>* p = #<sc_t>_get_aware( o ); ", sc_spect_name, sc_spect_name );
        st_s_push_fa(st,"assert( p->#<sc_t> ); ", sc_name );
        if( has_ret ) st_s_push_fa(st,"return " );
        st_s_push_fa(st,"p->#<sc_t>( o", sc_name );
        BLM_TRY(xoico_args_s_expand_name(&(o->signature.args),host, false,((bcore_sink*)( st ))))
        st_s_push_fa(st," ); };" );
    
        xoico_func_s* func = xoico_feature_s_push_func_from_sc(o,host, st->sc );
        func->declare_in_expand_forward = false;
    
        xoico_func_s* func_to_group = xoico_func_s_clone(func);
        xoico_body_s_attach( &(func_to_group->body ),  NULL);
        BLM_TRY(xoico_func_s_freeze_global_name(func_to_group,host )) // set global name before local name is changed
        func_to_group->name = o->signature.name;
        func_to_group->expandable = false;
        ((xoico_func_s*)(x_array_push_d(((x_array*)(&(o->funcs_return_to_group))),((x_inst*)(func_to_group )))));
    }
    
    if( o->flag_a )
    {
        st_s* st = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
        st_s_push_fa(st,"(bl_t a_defines_#<sc_t>( const )) = ", sc_name );
        if( always_defined )
        {
            st_s_push_fa(st,"{ return true; };", sc_name );
        }
        else
        {
            st_s_push_fa(st,"{ return #<sc_t>_get_aware( o )->#<sc_t> != NULL; };", sc_spect_name, sc_name );
        }
    
        xoico_func_s* func = xoico_feature_s_push_func_from_sc(o,host, st->sc );
        func->declare_in_expand_forward = false;
    }
    
    if( o->flag_t )
    {
        st_s* st = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
        st_s_push_fa(st,"(#<sc_t> t_#<sc_t>( typed", sc_ret_typespec, sc_name );
        st_s_push_fa(st,flag_const ? " const" : " mutable" );
        BLM_TRY(xoico_args_s_expand(&(o->signature.args),host, false,((bcore_sink*)( st ))))
        st_s_push_fa(st," )) = (verbatim_C) { " );
        st_s_push_fa(st,"const #<sc_t>* p = #<sc_t>_get_typed( t ); ", sc_spect_name, sc_spect_name );
        st_s_push_fa(st,"assert( p->#<sc_t> ); ", sc_name );
        if( has_ret ) st_s_push_fa(st,"return " );
        st_s_push_fa(st,"p->#<sc_t>( o", sc_name );
        BLM_TRY(xoico_args_s_expand_name(&(o->signature.args),host, false,((bcore_sink*)( st ))))
        st_s_push_fa(st," ); };" );
    
        xoico_func_s* func = xoico_feature_s_push_func_from_sc(o,host, st->sc );
        func->declare_in_expand_forward = false;
    }
    
    if( o->flag_t )
    {
        st_s* st = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
        st_s_push_fa(st,"(bl_t t_defines_#<sc_t>( tp_t t )) = ", sc_name );
        if( always_defined )
        {
            st_s_push_fa(st,"{ return true; };", sc_name );
        }
        else
        {
            st_s_push_fa(st,"{ return #<sc_t>_get_typed( t )->#<sc_t> != NULL; };", sc_spect_name, sc_name );
        }
    
        xoico_func_s* func = xoico_feature_s_push_func_from_sc(o,host, st->sc );
        func->declare_in_expand_forward = false;
    }
    
    if( o->flag_p )
    {
        st_s* st = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
        st_s_push_fa(st,"(#<sc_t> p_#<sc_t>( const #<sc_t>* p,", sc_ret_typespec, sc_name, sc_spect_name );
    
        if( flag_const ) st_s_push_fa(st," const" );
        st_s_push_fa(st," #<sc_t>* o", sc_obj_type );
        BLM_TRY(xoico_args_s_expand(&(o->signature.args),host, false,((bcore_sink*)( st ))))
        st_s_push_fa(st," )) = (verbatim_C) { " );
        st_s_push_fa(st,"assert( p->#<sc_t> ); ", sc_name );
        if( has_ret ) st_s_push_fa(st,"return " );
        st_s_push_fa(st,"p->#<sc_t>( o", sc_name );
        BLM_TRY(xoico_args_s_expand_name(&(o->signature.args),host, false,((bcore_sink*)( st ))))
        st_s_push_fa(st," ); };" );
    
        xoico_func_s* func = xoico_feature_s_push_func_from_sc(o,host, st->sc );
        func->declare_in_expand_forward = false;
    }
    
    if( o->flag_p )
    {
        st_s* st = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
        st_s_push_fa(st,"(bl_t p_defines_#<sc_t>( const #<sc_t>* p )) = ", sc_name, sc_spect_name );
        if( always_defined )
        {
            st_s_push_fa(st,"{ return true; };", sc_name );
        }
        else
        {
            st_s_push_fa(st,"{ return p->#<sc_t> != NULL; };", sc_name );
        }
    
        xoico_func_s* func = xoico_feature_s_push_func_from_sc(o,host, st->sc );
        func->declare_in_expand_forward = false;
    }
    
    if( o->flag_r )
    {
        st_s* st = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
        st_s_push_fa(st,"( #<sc_t> r_#<sc_t>(", sc_ret_typespec, sc_name );
        st_s_push_fa(st," const sr_s* o" );
        BLM_TRY(xoico_args_s_expand(&(o->signature.args),host, false,((bcore_sink*)( st ))))
        st_s_push_fa(st," )) = (verbatim_C) { " );
        if( !flag_const ) st_s_push_fa(st,"ASSERT( !sr_s_is_const( o ) ); " );
        st_s_push_fa(st,"const #<sc_t>* p = (const #<sc_t>*)ch_spect_p( o->p, TYPEOF_#<sc_t> ); ",
            sc_spect_name,
            sc_spect_name,
            sc_spect_name
        );
    
        st_s_push_fa(st,"assert( p->#<sc_t> ); ", sc_name );
        if( has_ret ) st_s_push_fa(st,"return " );
        st_s_push_fa(st,"p->#<sc_t>( o->o", sc_name );
        BLM_TRY(xoico_args_s_expand_name(&(o->signature.args),host, false,((bcore_sink*)( st ))))
        st_s_push_fa(st," ); };" );
    
        xoico_func_s* func = xoico_feature_s_push_func_from_sc(o,host, st->sc );
        func->declare_in_expand_forward = false;
    }
    
    if( o->flag_r )
    {
        st_s* st = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    
        st_s_push_fa(st,"(bl_t r_defines_#<sc_t>( const sr_s* o )) = ", sc_name );
        if( always_defined )
        {
            st_s_push_fa(st,"{ return true; };", sc_name );
        }
        else
        {
            st_s_push_fa(st,"{ return ( (#<sc_t>*)ch_spect_p( o->p, TYPEOF_#<sc_t> ) )->#<sc_t> != NULL; };", sc_spect_name, sc_spect_name, sc_name );
        }
    
        xoico_func_s* func = xoico_feature_s_push_func_from_sc(o,host, st->sc );
        func->declare_in_expand_forward = false;
    }
    
    if( o->st_default_func_name.size > 0 )
    {
        st_s* st = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
        st_s_push_fa(st,"(#<sc_t> #<sc_t>(", sc_ret_typespec, o->st_default_func_name.sc );
        if( flag_const ) st_s_push_fa(st," const" );
        st_s_push_fa(st," #<sc_t>* o", sc_obj_type );
        BLM_TRY(xoico_args_s_expand(&(o->signature.args),host, false,((bcore_sink*)( st ))))
        st_s_push_fa(st," ));" );
    
        xoico_func_s* func = xoico_feature_s_push_func_from_sc(o,host, st->sc );
        func->declare_in_expand_forward = false;
        if( o->default_body ) xoico_body_s_attach( &(func->body ),  ((xoico_body_s*)bcore_fork(o->default_body)));
    }
    
    BLM_RETURNV(er_t, 0)
}

er_t xoico_feature_s_finalize( xoico_feature_s* o, const xoico_host* host )
{
    // xoico_feature.x:306:27
    
    {const xoico_funcs_s* __a=&(o->funcs );if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_func_s* func=__a->data[__i]; BLM_TRY(xoico_func_s_finalize(func,host ))
    }}return  0;
}

er_t xoico_feature_s_expand_forward( const xoico_feature_s* o, const xoico_host* host, sz_t indent, bcore_sink* sink )
{
    // xoico_feature.x:314:33
    
    {const xoico_funcs_s* __a=&(o->funcs );if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_func_s* func=__a->data[__i]; BLM_TRY(xoico_func_s_expand_forward(func,host, indent, sink ))
    }}return  0;
}

er_t xoico_feature_s_expand_indef_typedef( const xoico_feature_s* o, const xoico_host* host, sz_t indent, bcore_sink* sink )
{
    // xoico_feature.x:322:39
    
    if( !o->expandable ) return  0;
    xoico_compiler_s* compiler = xoico_host_a_compiler(host);
    bcore_sink_a_push_fa(sink," \\\n#rn{ }  typedef ", indent );
    BLM_TRY(xoico_typespec_s_expand(&(o->signature.typespec_ret),host, sink ))
    bcore_sink_a_push_fa(sink," (*#<sc_t>)(", xoico_compiler_s_nameof(compiler,o->function_pointer_name ) );
    if( o->signature.arg_o == TYPEOF_const ) bcore_sink_a_push_fa(sink," const" );
    bcore_sink_a_push_fa(sink," #<sc_t>* o", xoico_compiler_s_nameof(compiler,xoico_host_a_obj_type(host) ) );
    BLM_TRY(xoico_args_s_expand(&(o->signature.args),host, false, sink ))
    bcore_sink_a_push_fa(sink," );" );
    return  0;
}

er_t xoico_feature_s_expand_spect_declaration( const xoico_feature_s* o, const xoico_host* host, sz_t indent, bcore_sink* sink )
{
    // xoico_feature.x:338:43
    
    if( !o->expandable ) return  0;
    xoico_compiler_s* compiler = xoico_host_a_compiler(host);
    bcore_sink_a_push_fa(sink," \\\n#rn{ }#<sc_t> #<sc_t>;", indent, xoico_compiler_s_nameof(compiler,o->function_pointer_name ), xoico_compiler_s_nameof(compiler,o->signature.name ) );
    return  0;
}

er_t xoico_feature_s_expand_spect_definition( const xoico_feature_s* o, const xoico_host* host, sz_t indent, bcore_sink* sink )
{
    // xoico_feature.x:348:42
    
    if( !o->expandable ) return  0;
    xoico_compiler_s* compiler = xoico_host_a_compiler(host);
    bcore_sink_a_push_fa(sink,"#rn{ }\"feature ", indent );
    if( o->strict ) bcore_sink_a_push_fa(sink,"strict " );
    if( o->flag_a ) bcore_sink_a_push_fa(sink,"aware " );
    
    bcore_sink_a_push_fa(sink,"#<sc_t> : #<sc_t>", xoico_compiler_s_nameof(compiler,xoico_host_a_obj_type(host) ), xoico_compiler_s_nameof(compiler,o->signature.name ) );
    if( o->st_default_func_name.size > 0 )
    {
        bcore_sink_a_push_fa(sink," = #<sc_t>_#<sc_t>", xoico_compiler_s_nameof(compiler,xoico_host_a_obj_type(host) ), o->st_default_func_name.sc );
    }
    bcore_sink_a_push_fa(sink,";\"\n" );
    return  0;
}

er_t xoico_feature_s_expand_indef_declaration( const xoico_feature_s* o, const xoico_host* host, sz_t indent, bcore_sink* sink )
{
    // xoico_feature.x:367:43
    
    if( !o->expandable ) return  0;
    {const xoico_funcs_s* __a=&(o->funcs );if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_func_s* func=__a->data[__i]; BLM_TRY(xoico_func_s_expand_declaration(func,host, indent + 2, sink ))
    }}return  0;
}

er_t xoico_feature_s_expand_definition( const xoico_feature_s* o, const xoico_host* host, sz_t indent, bcore_sink* sink )
{
    // xoico_feature.x:376:36
    
    if( !o->expandable ) return  0;
    {const xoico_funcs_s* __a=&(o->funcs );if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_func_s* func=__a->data[__i]; BLM_TRY(xoico_func_s_expand_definition(func,host, indent, sink ))
    }}return  0;
}

er_t xoico_feature_s_expand_init1( const xoico_feature_s* o, const xoico_host* host, sz_t indent, bcore_sink* sink )
{
    // xoico_feature.x:385:31
    
    if( !o->expandable ) return  0;
    xoico_compiler_s* compiler = xoico_host_a_compiler(host);
    sc_t sc_global_name = xoico_compiler_s_nameof(compiler,o->signature.global_name );
    
    bcore_sink_a_push_fa(sink,"#rn{ }BCORE_REGISTER_FEATURE( #<sc_t> );\n", indent, sc_global_name );
    if( o->st_default_func_name.size > 0 )
    {
        bcore_sink_a_push_fa(sink,"#rn{ }BCORE_REGISTER_FFUNC( #<sc_t>, #<sc_t>_#<sc_t> );\n",
            indent,
            sc_global_name,
            xoico_compiler_s_nameof(compiler,xoico_host_a_obj_type(host) ),
            o->st_default_func_name.sc
        );
    }
    return  0;
}

XOILA_DEFINE_SPECT( xoico, xoico_feature )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/
// source: xoico_func.h
#include "xoico_func.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_func; embeds: xoico_func.x

BCORE_DEFINE_OBJECT_INST_P( xoico_func_s )
"aware xoico_func"
"{"
    "tp_t name;"
    "tp_t global_name;"
    "tp_t signature_base_name;"
    "tp_t signature_global_name;"
    "tp_t obj_type;"
    "bl_t expandable = true;"
    "bl_t overloadable = false;"
    "bl_t declare_in_expand_forward = true;"
    "xoico_body_s => body;"
    "tp_t pre_hash = 0;"
    "hidden aware xoico_signature_s* signature;"
    "bcore_source_point_s source_point;"
    "func xoico:parse;"
    "func xoico:finalize;"
    "func xoico:expand_forward;"
    "func xoico:expand_declaration;"
    "func xoico:expand_definition;"
"}";

bl_t xoico_func_s_reflectable( const xoico_func_s* o, const xoico_host* host )
{
    // xoico_func.h:55:5
    
    return  o->expandable && xoico_compiler_s_is_feature(xoico_host_a_compiler(host),o->signature_global_name );
}

tp_t xoico_func_s_get_hash( const xoico_func_s* o )
{
    // xoico_func.x:21:1
    
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
    hash = bcore_tp_fold_tp( hash, o->pre_hash );
    hash = bcore_tp_fold_tp( hash, o->name );
    hash = bcore_tp_fold_tp( hash, o->global_name );
    hash = bcore_tp_fold_tp( hash, o->signature_base_name );
    hash = bcore_tp_fold_tp( hash, o->signature_global_name );
    hash = bcore_tp_fold_bl( hash, o->expandable );
    hash = bcore_tp_fold_bl( hash, o->overloadable );
    hash = bcore_tp_fold_bl( hash, o->declare_in_expand_forward );
    if( o->body ) hash = bcore_tp_fold_tp( hash, xoico_body_s_get_hash( o->body ) );
    return  hash;
}

er_t xoico_func_s_freeze_global_name( xoico_func_s* o, const xoico_host* host )
{
    // xoico_func.x:37:73
    BLM_INIT_LEVEL(0);
    if( o->global_name ) BLM_RETURNV(er_t, 0)
    xoico_compiler_s* compiler = xoico_host_a_compiler(host);
    o->global_name = xoico_compiler_s_entypeof(compiler,((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create_fa("#<sc_t>_#<sc_t>", xoico_compiler_s_nameof(compiler,xoico_host_a_obj_type(host) ), xoico_compiler_s_nameof(compiler,o->name ) )))->sc );
    BLM_RETURNV(er_t, 0)
}

er_t xoico_func_s_parse( xoico_func_s* o, const xoico_host* host, bcore_source* source )
{
    // xoico_func.x:47:24
    BLM_INIT_LEVEL(0);
    xoico_compiler_s* compiler = xoico_host_a_compiler(host);
    
    // global name signature
    tp_t tp_signature_base_name;
    bcore_source_point_s_set(&(o->source_point),source );
    
    st_s* st_name = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    
    if( bcore_source_a_parse_bl(source," #?'('" ) )
    {
        xoico_signature_s* signature = xoico_signature_s_create();
        BLM_TRY(xoico_compiler_s_life_a_push(compiler,((bcore_inst*)(signature ))))
        BLM_TRY(xoico_signature_s_parse(signature,host, source ))
        BLM_TRY(bcore_source_a_parse_em_fa(source," ) " ))
    
        BLM_TRY(xoico_compiler_s_register_item(compiler,((const xoico*)(signature)), source ))
    
        o->pre_hash = bcore_tp_fold_tp( o->pre_hash, xoico_signature_s_get_hash(signature) );
        tp_signature_base_name = xoico_host_a_obj_type(host);
        st_s_copy_sc(st_name,xoico_compiler_s_nameof(compiler,signature->name ) );
    }
    else
    {
        if( bcore_source_a_parse_bl(source," #?'^'" ) )
        {
            if( host->_ == TYPEOF_xoico_stamp_s )
            {
                tp_signature_base_name = ((const xoico_stamp_s*)(host))->trait_name;
            }
            else
            {
                BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"'^' can only be used inside a stamp." ))
            }
        }
        else
        {
            st_s* st = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
            BLM_TRY(xoico_host_a_parse_name(host,source, st ))
            tp_signature_base_name = xoico_compiler_s_entypeof(compiler,st->sc );
        }
    
        BLM_TRY(bcore_source_a_parse_em_fa(source," ." ))
        BLM_TRY(bcore_source_a_parse_em_fa(source," #name", st_name ))
    }
    
    
    if( st_name->size == 0 ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Function name expected." ))
    o->name = xoico_compiler_s_entypeof(compiler,st_name->sc );
    
    o->signature_base_name = tp_signature_base_name;
    o->signature_global_name = xoico_compiler_s_entypeof(compiler,((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create_fa("#<sc_t>_#<sc_t>", xoico_compiler_s_nameof(compiler,tp_signature_base_name ), st_name->sc )))->sc );
    
    if( bcore_source_a_parse_bl(source," #=?'='" ) ) BLM_TRY(xoico_body_s_parse(BCORE_PASS_CREATE(xoico_body_s,o->body),host, source ))
    
    BLM_TRY(bcore_source_a_parse_em_fa(source," ; " ))
    BLM_RETURNV(er_t, 0)
}

er_t xoico_func_s_push_flect_decl_to_sink( const xoico_func_s* o, const xoico_host* host, bcore_sink* sink )
{
    // xoico_func.x:110:1
    
    xoico_compiler_s* compiler = xoico_host_a_compiler(host);
    bcore_sink_a_push_sc(sink,"func " );
    if( host->_ == TYPEOF_xoico_stamp_s && o->signature_base_name == ((const xoico_stamp_s*)(host))->trait_name )
    {
        bcore_sink_a_push_fa(sink,"^:#<sc_t>", xoico_compiler_s_nameof(compiler,o->name ) );
    }
    else
    {
        bcore_sink_a_push_fa(sink,"#<sc_t>:#<sc_t>", xoico_compiler_s_nameof(compiler,o->signature_base_name ), xoico_compiler_s_nameof(compiler,o->name ) );
    }
    bcore_sink_a_push_sc(sink,";" );
    return  0;
}

er_t xoico_func_s_finalize( xoico_func_s* o, const xoico_host* host )
{
    // xoico_func.x:127:27
    
    xoico_compiler_s* compiler = xoico_host_a_compiler(host);
    BLM_TRY(xoico_func_s_freeze_global_name(o,host ))
    o->obj_type = xoico_host_a_obj_type(host);
    
    xoico_signature_s* signature = ((xoico_signature_s*)(xoico_compiler_s_get_signature(compiler,o->signature_global_name )));
    if( !signature )
    {
        return  bcore_source_point_s_parse_error_fa(&(o->source_point),"Function #<sc_t>: Could not find signature #<sc_t>",
            xoico_compiler_s_nameof(compiler,o->name ),
            xoico_compiler_s_nameof(compiler,o->signature_global_name )
        );
    }
    
    o->signature = signature;
    
    if( o->body ) BLM_TRY(xoico_body_s_finalize(o->body,host ))
    
    return  0;
}

er_t xoico_func_s_expand_forward( const xoico_func_s* o, const xoico_host* host, sz_t indent, bcore_sink* sink )
{
    // xoico_func.x:153:33
    
    if( !o->expandable ) return  0;
    if( !o->declare_in_expand_forward ) return  0;
    
    xoico_compiler_s* compiler = xoico_host_a_compiler(host);
    bcore_sink_a_push_fa(sink," \\\n#rn{ }", indent );
    bl_t go_inline = o->body && o->body->go_inline;
    const xoico_signature_s* signature = o->signature;
    ASSERT( signature );
    if( go_inline )
    {
        bcore_sink_a_push_fa(sink,"static inline " );
        BLM_TRY(xoico_signature_s_expand_declaration(signature,host, xoico_compiler_s_nameof(compiler,o->global_name ), indent, sink ))
    }
    else
    {
        BLM_TRY(xoico_signature_s_expand_declaration(signature,host, xoico_compiler_s_nameof(compiler,o->global_name ), indent, sink ))
    }
    bcore_sink_a_push_fa(sink,";" );
    
    return  0;
}

er_t xoico_func_s_expand_declaration( const xoico_func_s* o, const xoico_host* host, sz_t indent, bcore_sink* sink )
{
    // xoico_func.x:179:37
    
    if( !o->expandable ) return  0;
    
    bl_t go_inline = o->body && o->body->go_inline;
    const xoico_signature_s* signature = o->signature;
    ASSERT( signature );
    xoico_compiler_s* compiler = xoico_host_a_compiler(host);
    
    if( go_inline )
    {
        bcore_sink_a_push_fa(sink," \\\n#rn{ }", indent );
        bcore_sink_a_push_fa(sink,"static inline " );
        BLM_TRY(xoico_signature_s_expand_declaration(signature,host, xoico_compiler_s_nameof( compiler,o->global_name ), indent, sink ))
        BLM_TRY(xoico_body_s_expand(o->body,host, signature, indent, sink ))
    }
    else if( !o->declare_in_expand_forward )
    {
        bcore_sink_a_push_fa(sink," \\\n#rn{ }", indent );
        BLM_TRY(xoico_signature_s_expand_declaration(signature,host, xoico_compiler_s_nameof( compiler,o->global_name ), indent, sink ))
        bcore_sink_a_push_fa(sink,";" );
    }
    
    return  0;
}

er_t xoico_func_s_expand_definition( const xoico_func_s* o, const xoico_host* host, sz_t indent, bcore_sink* sink )
{
    // xoico_func.x:207:36
    
    if( !o->expandable ) return  0;
    xoico_compiler_s* compiler = xoico_host_a_compiler(host);
    
    const xoico_signature_s* signature = o->signature;
    ASSERT( signature );
    if( o->body && !o->body->go_inline )
    {
        bcore_sink_a_push_fa(sink,"\n" );
        bcore_sink_a_push_fa(sink,"#rn{ }", indent );
        BLM_TRY(xoico_signature_s_expand_declaration(signature,host, xoico_compiler_s_nameof(compiler,o->global_name ), indent, sink ))
        bcore_sink_a_push_fa(sink,"\n" );
        BLM_TRY(xoico_body_s_expand(o->body,host, signature, indent, sink ))
        bcore_sink_a_push_fa(sink,"\n" );
    }
    
    return  0;
}

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
"aware x_array"
"{"
    "xoico_func_s => [];"
"}";

sz_t xoico_funcs_s_get_index_from_signature_global_name( const xoico_funcs_s* o, tp_t signature_global_name )
{
    // xoico_funcs.h:43:5
    
    {const xoico_funcs_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_func_s* e=__a->data[__i]; if( e->signature_global_name == signature_global_name ) return  __i;
    }}return  -1;
}

bl_t xoico_funcs_s_exists_from_signature_global_name( const xoico_funcs_s* o, tp_t signature_global_name )
{
    // xoico_funcs.h:49:5
    
    return  ( xoico_funcs_s_get_index_from_signature_global_name(o,signature_global_name ) >= 0 );
}

sz_t xoico_funcs_s_get_index_from_name( const xoico_funcs_s* o, tp_t name )
{
    // xoico_funcs.h:54:5
    
    {const xoico_funcs_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_func_s* e=__a->data[__i]; if( e->name == name ) return  __i;
    }}return  -1;
}

bl_t xoico_funcs_s_exists_from_name( const xoico_funcs_s* o, tp_t name )
{
    // xoico_funcs.h:60:5
    
    return  ( xoico_funcs_s_get_index_from_name(o,name ) >= 0 );
}

xoico_func_s* xoico_funcs_s_get_func_from_signature_global_name( const xoico_funcs_s* o, tp_t signature_global_name )
{
    // xoico_funcs.h:65:5
    
    sz_t idx = xoico_funcs_s_get_index_from_signature_global_name(o,signature_global_name );
    return  ( idx >= 0 ) ? o->data[ idx ] : NULL;
}

xoico_func_s* xoico_funcs_s_get_func_from_name( const xoico_funcs_s* o, tp_t name )
{
    // xoico_funcs.h:71:5
    
    sz_t idx = xoico_funcs_s_get_index_from_name(o,name );
    return  ( idx >= 0 ) ? o->data[ idx ] : NULL;
}

er_t xoico_funcs_s_replace_fork( xoico_funcs_s* o, sz_t idx, xoico_func_s* func )
{
    // xoico_funcs.h:77:5
    
    ASSERT( idx >= 0 && idx < o->size );
    xoico_func_s_attach( &(o->data[ idx ] ),  NULL);
    for( sz_t i = idx + 1; i < o->size; i++ ) o->data[ i - 1 ] = o->data[ i ];
    o->data[ o->size - 1 ] = ((xoico_func_s*)bcore_fork(func));
    return  0;
}

tp_t xoico_funcs_s_get_hash( const xoico_funcs_s* o )
{
    // xoico_funcs.h:86:5
    
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
    {const xoico_funcs_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_func_s* func=__a->data[__i]; hash = bcore_tp_fold_tp( hash, xoico_func_s_get_hash(func) );}}
    return  hash;
}

XOILA_DEFINE_SPECT( xoico, xoico_funcs )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/
// source: xoico_group.h
#include "xoico_group.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_group; embeds: xoico_group.x
#include "xoico_nested_group.h"

BCORE_DEFINE_OBJECT_INST_P( xoico_group_source_stack_s )
"aware x_array"
"{"
    "aware bcore_source -> [];"
"}";

BCORE_DEFINE_OBJECT_INST_P( xoico_group_s )
"aware xoico_group"
"{"
    "aware xoico => [];"
    "private xoico_group_s* parent;"
    "bcore_arr_st_s includes_in_declaration;"
    "bcore_arr_st_s includes_in_definition;"
    "bcore_arr_st_s explicit_embeddings;"
    "st_s st_name;"
    "tp_t tp_name;"
    "tp_t trait_name = bcore_inst;"
    "tp_t pre_hash;"
    "tp_t beta = 0;"
    "bl_t expandable = true;"
    "bl_t retrievable;"
    "bl_t short_spect_name;"
    "private xoico_stamp_s* extending_stamp;"
    "xoico_funcs_s funcs;"
    "private aware xoico_source_s* xoico_source;"
    "hidden aware xoico_compiler_s* compiler;"
    "bcore_source_point_s source_point;"
    "hidden bcore_hmap_tpvd_s hmap_feature;"
    "hidden bcore_hmap_tpvd_s hmap_func;"
    "func xoico:get_global_name_sc;"
    "func xoico:get_global_name_tp;"
    "func xoico:expand_setup;"
    "func xoico_host:compiler;"
    "func xoico_host:cengine;"
    "func xoico_host:obj_type;"
    "func xoico:get_hash;"
    "func xoico_host:create_spect_name;"
    "func xoico_host:parse_name;"
    "func xoico:parse;"
    "func xoico:finalize;"
"}";

er_t xoico_group_s_expand_setup( xoico_group_s* o, const xoico_host* host )
{
    // xoico_group.h:106:5
    
    {const xoico_group_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico* e=__a->data[__i]; BLM_TRY(xoico_a_expand_setup(e,((const xoico_host*)(o ))) )
    }}return  0;
}

er_t xoico_group_s_push_item_d( xoico_group_s* o, xoico* item )
{
    // xoico_group.h:117:5
    
    bcore_array_a_push( ((bcore_array*)(o)),sr_asd( item ) );
    return  0;
}

const xoico_group_s* xoico_group_s_get_trait_group( const xoico_group_s* o )
{
    // xoico_group.h:123:5
    
    return  ( o->trait_name != o->tp_name ) ? xoico_compiler_s_get_group(o->compiler,o->trait_name ) : NULL;
}

const xoico_func_s* xoico_group_s_get_trait_line_func_from_name( const xoico_group_s* o, tp_t name )
{
    // xoico_group.h:128:5
    
    if( !o ) return  NULL;
    const xoico_func_s** p_func = ( const xoico_func_s** )bcore_hmap_tpvd_s_get(&(o->hmap_func),name );
    return  p_func ? *p_func : xoico_group_s_get_trait_line_func_from_name(xoico_group_s_get_trait_group(o),name );
}

xoico_cengine* xoico_group_s_cengine( const xoico_group_s* o )
{
    // xoico_group.h:140:5
    
    return  o->xoico_source->target->cengine;
}

tp_t xoico_group_s_get_hash( const xoico_group_s* o )
{
    // xoico_group.x:21:1
    
    tp_t hash = o->pre_hash;
    hash = bcore_tp_fold_sc( hash, o->st_name.sc );
    hash = bcore_tp_fold_tp( hash, o->trait_name );
    hash = bcore_tp_fold_bl( hash, o->retrievable );
    hash = bcore_tp_fold_bl( hash, o->expandable );
    hash = bcore_tp_fold_bl( hash, o->short_spect_name );
    hash = bcore_tp_fold_tp( hash, o->beta );
    hash = bcore_tp_fold_tp( hash, xoico_funcs_s_get_hash(&(o->funcs)) );
    {const xoico_group_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico* e=__a->data[__i]; hash = bcore_tp_fold_tp( hash, xoico_a_get_hash(e) );}}
    {const bcore_arr_st_s* __a=&(o->includes_in_declaration );if(__a)for(sz_t __i=0; __i<__a->size; __i++){st_s* e=__a->data[__i]; hash = bcore_tp_fold_sc( hash, e->sc );}}
    {const bcore_arr_st_s* __a=&(o->includes_in_definition  );if(__a)for(sz_t __i=0; __i<__a->size; __i++){st_s* e=__a->data[__i]; hash = bcore_tp_fold_sc( hash, e->sc );}}
    {const bcore_arr_st_s* __a=&(o->explicit_embeddings     );if(__a)for(sz_t __i=0; __i<__a->size; __i++){st_s* e=__a->data[__i]; hash = bcore_tp_fold_sc( hash, e->sc );}}
    return  hash;
}

st_s* xoico_group_s_create_spect_name( const xoico_group_s* o )
{
    // xoico_group.x:40:1
    
    if( o->short_spect_name )
    {
        return  st_s_create_fa("#<sc_t>_s", o->st_name.sc );
    }
    else
    {
        return  st_s_create_fa("#<sc_t>_spect_s", o->st_name.sc );
    }
}

er_t xoico_group_s_parse_name_recursive( const xoico_group_s* o, bcore_source* source, st_s* name )
{
    // xoico_group.x:53:35
    BLM_INIT_LEVEL(0);
    if( bcore_source_a_parse_bl(source,"#?':'" ) )
    {
        if( o->parent )
        {
            BLM_TRY(xoico_group_s_parse_name_recursive(o->parent,source, name ))
        }
        else
        {
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Too many colons: Namespace depth exceeded." ))
        }
    }
    else
    {
        st_s_copy(name,&(o->st_name ));
        st_s* s = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
        BLM_TRY(bcore_source_a_parse_em_fa(source," #name", s ))
        if( s->size > 0 ) st_s_push_fa(name,"_#<sc_t>", s->sc );
    }
    BLM_RETURNV(er_t, 0)
}

er_t xoico_group_s_parse_name( const xoico_group_s* o, bcore_source* source, st_s* name )
{
    // xoico_group.x:78:34
    
    if( bcore_source_a_parse_bl(source," #?':'" ) )
    {
        BLM_TRY(xoico_group_s_parse_name_recursive(o,source, name ))
    }
    else
    {
        BLM_TRY(bcore_source_a_parse_em_fa(source," #name", name ))
    }
    
    if( name->size > 0 ) xoico_compiler_s_entypeof(o->compiler,name->sc );
    
    return  0;
}

er_t xoico_group_s_push_default_feature_from_sc( xoico_group_s* o, sc_t sc )
{
    // xoico_group.x:96:68
    BLM_INIT_LEVEL(0);
    xoico_compiler_s* compiler = o->compiler;
    xoico_feature_s* feature = ((xoico_feature_s*)BLM_LEVEL_T_PUSH(0,xoico_feature_s,xoico_feature_s_create()));
    feature->expandable = false;
    BLM_TRY(xoico_feature_s_parse(feature,((const xoico_host*)(o)),((bcore_source*)( ((bcore_source_string_s*)BLM_LEVEL_T_PUSH(0,bcore_source_string_s,bcore_source_string_s_create_from_sc(sc ))) ))))
    
    if( !xoico_compiler_s_is_item(compiler,xoico_a_get_global_name_tp(((xoico*)(feature))) ) )
    {
        {const xoico_funcs_s* __a=&(feature->funcs_return_to_group );if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_func_s* func=__a->data[__i]; ((xoico_func_s*)(x_array_push_d(((x_array*)(&(o->funcs))),((x_inst*)(((xoico_func_s*)bcore_fork(func)) )))));}}
        ((xoico_funcs_s*)(x_array_clear(((x_array*)(&(feature->funcs_return_to_group))))));
        BLM_TRY(xoico_compiler_s_register_item(compiler,((const xoico*)(feature)), o->source_point.source ))
        bcore_hmap_tpvd_s_set(&(o->hmap_feature),feature->signature.name, ( vd_t )feature );
        BLM_TRY(xoico_group_s_push_item_d(o,((xoico*)(((xoico_feature_s*)bcore_fork(feature)) ))))
    }
    
    BLM_RETURNV(er_t, 0)
}

er_t xoico_group_s_parse_func( xoico_group_s* o, bcore_source* source )
{
    // xoico_group.x:117:63
    BLM_INIT_LEVEL(0);
    xoico_func_s* func = ((xoico_func_s*)BLM_LEVEL_T_PUSH(0,xoico_func_s,xoico_func_s_create()));
    BLM_TRY(xoico_func_s_parse(func,((const xoico_host*)(o)), source ))
    BLM_TRY(xoico_group_s_push_func_d(o,((xoico_func_s*)bcore_fork(func)) ))
    BLM_RETURNV(er_t, 0)
}

er_t xoico_group_s_push_func_d( xoico_group_s* o, xoico_func_s* func )
{
    // xoico_group.x:127:62
    
    sz_t idx = xoico_funcs_s_get_index_from_name(&(o->funcs),func->name );
    
    xoico_compiler_s* compiler = o->compiler;
    
    if( idx >= 0 )
    {
        xoico_func_s* prex_func = o->funcs.data[ idx ];
        if( ( prex_func->signature_global_name == func->signature_global_name ) )
        {
            if( !func->body )
            {
                return  bcore_source_point_s_parse_error_fa(&(func->source_point),"Function '#<sc_t>' has already been declared.", xoico_compiler_s_nameof(compiler,func->name ) );
            }
            else if( prex_func->body )
            {
                return  bcore_source_point_s_parse_error_fa(&(func->source_point),"Function '#<sc_t>' has already a body.", xoico_compiler_s_nameof(compiler,func->name ) );
            }
            else
            {
                BLM_TRY(xoico_funcs_s_replace_fork(&(o->funcs),idx, func ))
            }
        }
        else
        {
            return  bcore_source_point_s_parse_error_fa(&(func->source_point),"Function '#<sc_t>' has already been declared.", xoico_compiler_s_nameof(compiler,func->name ) );
        }
    }
    else
    {
        ((xoico_func_s*)(x_array_push_d(((x_array*)(&(o->funcs))),((x_inst*)(func )))));
    }
    
    return  0;
}

er_t xoico_group_s_parse( xoico_group_s* o, const xoico_host* host, bcore_source* source )
{
    // xoico_group.x:166:24
    BLM_INIT_LEVEL(0);
    xoico_compiler_s* compiler = o->compiler;
    xoico_group_source_stack_s* stack = ((xoico_group_source_stack_s*)BLM_LEVEL_T_PUSH(0,xoico_group_source_stack_s,xoico_group_source_stack_s_create()));
    ((bcore_source*)(x_array_push_d(((x_array*)(stack)),((x_inst*)(((bcore_source*)bcore_fork(source)) )))));
    
    sc_t group_termination = NULL;
    
    bcore_source_point_s_set(&(o->source_point),source );
    o->pre_hash = bcore_tp_init();
    o->tp_name = xoico_compiler_s_entypeof(compiler,o->st_name.sc );
    
    if( o->parent ) // this group is nested in another group, the group body is enclosed in { ... }
    {
        BLM_TRY(bcore_source_a_parse_em_fa(source," {" ))
        group_termination = " #?'}'";
    }
    else // this group is root
    {
        if( bcore_source_a_parse_bl(source," #?'#ifdef XOILA_SECTION'" ) )
        {
            group_termination = " #?'#endif'";
        }
        else
        {
            group_termination = NULL;
        }
    }
    
    bl_t extend_stump = false;
    
    while
    (
        stack->size >= 2 ||
        ( group_termination ? !bcore_source_a_parse_bl(source,group_termination ) : !bcore_source_a_eos(source) )
    )
    {
        if( bcore_source_a_eos(source) )
        {
            if( stack->size >= 2 )
            {
                bcore_source_a_attach( &(stack->data[ stack->size - 1 ] ), (bcore_source*)( NULL));
                source = stack->data[ stack->size - 2 ];
                ((xoico_group_source_stack_s*)(x_array_set_size(((x_array*)(stack)),stack->size - 1 )));
            }
            else if( group_termination )
            {
                BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Unexpected end of file." ))
            }
            else
            {
                break;
            }
        }
        else if( bcore_source_a_parse_bl(source," #?w'stamp' " ) )
        {BLM_INIT_LEVEL(3);
            xoico_stamp_s* stamp = ((xoico_stamp_s*)BLM_LEVEL_T_PUSH(3,xoico_stamp_s,xoico_stamp_s_create()));
            stamp->group = o;
            BLM_TRY(xoico_stamp_s_parse(stamp,((const xoico_host*)(o)), source ))
            BLM_TRY(xoico_stamp_s_push_default_funcs(stamp))
            BLM_TRY(xoico_compiler_s_register_item(compiler,((const xoico*)(stamp)), source ))
            BLM_TRY(xoico_group_s_push_item_d(o,((xoico*)(((xoico_stamp_s*)bcore_fork(stamp)) ))))
        BLM_DOWN();}
    
        /// stumps are inexpandable stamps. They can be used as template.
        else if( bcore_source_a_parse_bl(source," #?w'stump' " ) )
        {BLM_INIT_LEVEL(3);
            xoico_stamp_s* stump = ((xoico_stamp_s*)BLM_LEVEL_T_PUSH(3,xoico_stamp_s,xoico_stamp_s_create()));
            stump->group = o;
            BLM_TRY(xoico_stamp_s_parse(stump,((const xoico_host*)(o)), source ))
            BLM_TRY(xoico_stamp_s_make_funcs_overloadable(stump))
            BLM_TRY(xoico_compiler_s_register_item(compiler,((const xoico*)(stump)), source ))
            BLM_TRY(xoico_compiler_s_life_a_push(compiler,((bcore_inst*)(((xoico_stamp_s*)bcore_fork(stump)) ))))
            if( extend_stump )
            {
                o->extending_stamp = stump;
                extend_stump = false;
            }
        BLM_DOWN();}
        else if( bcore_source_a_parse_bl(source," #?w'signature' " ) )
        {BLM_INIT_LEVEL(3);
            xoico_signature_s* signature = ((xoico_signature_s*)BLM_LEVEL_T_PUSH(3,xoico_signature_s,xoico_signature_s_create()));
            BLM_TRY(xoico_signature_s_parse(signature,((const xoico_host*)(o)), source ))
            BLM_TRY(bcore_source_a_parse_em_fa(source," ; " ))
            BLM_TRY(xoico_compiler_s_register_item(compiler,((const xoico*)(signature)), source ))
            BLM_TRY(xoico_group_s_push_item_d(o,((xoico*)(((xoico_signature_s*)bcore_fork(signature)) ))))
        BLM_DOWN();}
        else if( bcore_source_a_parse_bl( source," #?w'body' " ) )
        {BLM_INIT_LEVEL(3);
            xoico_body_s* body = ((xoico_body_s*)BLM_LEVEL_T_PUSH(3,xoico_body_s,xoico_body_s_create()));
            BLM_TRY(xoico_body_s_parse(body,((const xoico_host*)(o)), source ))
            BLM_TRY(bcore_source_a_parse_em_fa(source," ; " ))
            BLM_TRY(xoico_compiler_s_register_item(compiler,((const xoico*)(body)), source ))
            BLM_TRY(xoico_group_s_push_item_d(o,((xoico*)(((xoico_body_s*)bcore_fork(body)) ))))
        BLM_DOWN();}
        else if( bcore_source_a_parse_bl(source," #?w'feature' " ) )
        {BLM_INIT_LEVEL(3);
            xoico_feature_s* feature = ((xoico_feature_s*)BLM_LEVEL_T_PUSH(3,xoico_feature_s,xoico_feature_s_create()));
            BLM_TRY(xoico_feature_s_parse(feature,((const xoico_host*)(o)), source ))
            BLM_TRY(xoico_compiler_s_register_item(compiler,((const xoico*)(feature)), source ))
            bcore_hmap_tpvd_s_set(&(o->hmap_feature),feature->signature.name, ( vd_t )feature );
            {const xoico_funcs_s* __a=&(feature->funcs_return_to_group );if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_func_s* func=__a->data[__i]; ((xoico_func_s*)(x_array_push_d(((x_array*)(&(o->funcs))),((x_inst*)(((xoico_func_s*)bcore_fork(func)) )))));}}
            ((xoico_funcs_s*)(x_array_clear(((x_array*)(&(feature->funcs_return_to_group))))));
            BLM_TRY(xoico_group_s_push_item_d(o,((xoico*)(((xoico_feature_s*)bcore_fork(feature)) ))))
        BLM_DOWN();}
        else if( bcore_source_a_parse_bl(source," #?w'func' " ) )
        {
            bl_t is_group_function = true;
            if( bcore_source_a_parse_bl(source," #=?'('" ) )
            {BLM_INIT_LEVEL(4);
                sz_t index = bcore_source_a_get_index(source);
                BLM_TRY(bcore_source_a_parse_em_fa(source,"(" ))
                st_s* stamp_name = ((st_s*)BLM_LEVEL_T_PUSH(4,st_s,st_s_create()));
                BLM_TRY(xoico_group_s_parse_name(o,source, stamp_name ))
                if( bcore_source_a_parse_bl(source," #?')'" ) )
                {
                    st_s_push_sc(stamp_name,"_s" );
                    tp_t tp_stamp_name = btypeof( stamp_name->sc );
                    if( !xoico_compiler_s_is_stamp(compiler,tp_stamp_name ) )
                    {
                        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Cannot associate type name '#<sc_t>' with a stamp.", stamp_name->sc ))
                    }
    
                    xoico_stamp_s* stamp = xoico_compiler_s_get_stamp(compiler,tp_stamp_name );
                    BLM_TRY(xoico_stamp_s_parse_func(stamp,source ))
                    o->pre_hash = bcore_tp_fold_tp( o->pre_hash, xoico_stamp_s_get_hash(stamp) );
                    is_group_function = false;
                }
                else
                {
                    bcore_source_a_set_index(source,index );
                    is_group_function = true;
                }
            BLM_DOWN();}
    
            if( is_group_function )
            {
                BLM_TRY(xoico_group_s_parse_func(o,source ))
            }
        }
        else if( bcore_source_a_parse_bl(source," #?w'name' " ) )
        {BLM_INIT_LEVEL(3);
            xoico_name_s* name = ((xoico_name_s*)BLM_LEVEL_T_PUSH(3,xoico_name_s,xoico_name_s_create()));
            BLM_TRY(xoico_name_s_parse(name,((const xoico_host*)(o)), source ))
            BLM_TRY(xoico_group_s_push_item_d(o,((xoico*)(((xoico_name_s*)bcore_fork(name)) ))))
        BLM_DOWN();}
        else if( bcore_source_a_parse_bl(source," #?w'type' " ) )
        {BLM_INIT_LEVEL(3);
            xoico_name_s* name = ((xoico_name_s*)BLM_LEVEL_T_PUSH(3,xoico_name_s,xoico_name_s_create()));
            BLM_TRY(xoico_name_s_parse(name,((const xoico_host*)(o)), source ))
            BLM_TRY(xoico_compiler_s_register_external_type(compiler,name->name ))
            BLM_TRY(xoico_group_s_push_item_d(o,((xoico*)(((xoico_name_s*)bcore_fork(name)) ))))
        BLM_DOWN();}
        else if( bcore_source_a_parse_bl( source," #?w'forward' " ) )
        {BLM_INIT_LEVEL(3);
            xoico_forward_s* forward = ((xoico_forward_s*)BLM_LEVEL_T_PUSH(3,xoico_forward_s,xoico_forward_s_create()));
            forward->group = o;
            BLM_TRY(xoico_forward_s_parse(forward,((const xoico_host*)(o)), source ))
            BLM_TRY(xoico_group_s_push_item_d(o,((xoico*)(((xoico_forward_s*)bcore_fork(forward)) ))))
        BLM_DOWN();}
        else if( bcore_source_a_parse_bl( source," #?w'extending'" ) )
        {
            o->extending_stamp = NULL;
            if( bcore_source_a_parse_bl(source," #=?';'" ) )
            {
                // just reset o->extending - nothing else
            }
            else if( bcore_source_a_parse_bl(source," #=?w'stump'" ) )
            {
                extend_stump = true;
            }
            else
            {BLM_INIT_LEVEL(4);
                st_s* templ_name = ((st_s*)BLM_LEVEL_T_PUSH(4,st_s,st_s_create()));
                BLM_TRY(xoico_group_s_parse_name(o,source, templ_name ))
                st_s_push_fa(templ_name,"_s" );
                const xoico* item = xoico_compiler_s_get_const_item(compiler,typeof( templ_name->sc ) );
                if( !item ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Template #<sc_t> not found.", templ_name->sc ))
                if( item->_ != TYPEOF_xoico_stamp_s ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Template #<sc_t> is no stamp.", templ_name->sc ))
                o->extending_stamp = ((xoico_stamp_s*)(item));
                BLM_TRY(bcore_source_a_parse_em_fa(source," ;" ))
            BLM_DOWN();}
        }
        else if( bcore_source_a_parse_bl(source," #?w'group' " ) )
        {BLM_INIT_LEVEL(3);
            xoico_group_s* group = ((xoico_group_s*)BLM_LEVEL_T_PUSH(3,xoico_group_s,xoico_group_s_create()));
            BLM_TRY(xoico_source_s_push_d(o->xoico_source,((xoico_group_s*)bcore_fork(group)) ))
            group->parent = o;
            group->xoico_source = o->xoico_source;
            group->compiler = o->compiler;
            group->extending_stamp = o->extending_stamp;
            group->expandable  = o->expandable;
    
            BLM_TRY(xoico_group_s_parse_name(o,source,&( group->st_name )))
            BLM_TRY(bcore_source_a_parse_em_fa(source," =" ))
    
            // flags
            if( bcore_source_a_parse_bl(source," #?w'retrievable' " ) ) group->retrievable = true;
    
            st_s* st_trait_name = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    
            BLM_TRY(xoico_group_s_parse_name(o,source, st_trait_name ))
            if( st_trait_name->size == 0 ) st_s_copy(st_trait_name,&(o->st_name ));
            group->trait_name = xoico_compiler_s_entypeof(compiler,st_trait_name->sc );
    
            BLM_TRY(xoico_group_s_parse(group,((const xoico_host*)(o)), source ))
            BLM_TRY(bcore_source_a_parse_em_fa(source," ; " ))
            BLM_TRY(xoico_compiler_s_register_group(compiler,group ))
            xoico_nested_group_s* nested_group = ((xoico_nested_group_s*)BLM_LEVEL_T_PUSH(3,xoico_nested_group_s,xoico_nested_group_s_create()));
            nested_group->group = group;
            BLM_TRY(xoico_group_s_push_item_d(o,((xoico*)(((xoico_nested_group_s*)bcore_fork(nested_group)) ))))
        BLM_DOWN();}
        else if( bcore_source_a_parse_bl(source," #?w'set' " ) )
        {
            if(      bcore_source_a_parse_bl(source," #?w'retrievable' "      ) ) o->retrievable = true;
            else if( bcore_source_a_parse_bl(source," #?w'inexpandable' "     ) ) o->expandable = false;
            else if( bcore_source_a_parse_bl(source," #?w'short_spect_name' " ) ) o->short_spect_name = true;
            else if( bcore_source_a_parse_bl(source," #?w'beta' "             ) ) BLM_TRY(bcore_source_a_parse_em_fa(source," = #<tp_t*>", (&(o->beta)) ))
            BLM_TRY(bcore_source_a_parse_em_fa(source," ;" ))
        }
        else if( bcore_source_a_parse_bl(source," #?w'embed' " ) )
        {BLM_INIT_LEVEL(3);
            st_s* folder = ((st_s*)BLM_LEVEL_T_PUSH(3,st_s,bcore_file_folder_path(bcore_source_a_get_file( source ) )));
            if( folder->size == 0 ) st_s_push_char(folder,'.' );
            st_s* embed_file = ((st_s*)BLM_LEVEL_T_PUSH(3,st_s,st_s_create()));
            BLM_TRY(bcore_source_a_parse_em_fa(source," #string" , embed_file ))
            BLM_TRY(bcore_source_a_parse_em_fa(source," ;" ))
            bcore_arr_st_s_push_st(&(o->explicit_embeddings),embed_file );
            bcore_source* embed_source = NULL;
            BLM_TRY(xoico_embed_file_open(source, embed_file->sc,&( (embed_source) )) )
    
            // check for cyclic inclusions
            {const xoico_group_source_stack_s* __a=stack ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){bcore_source* e=__a->data[__i];
            {
                sc_t path = bcore_source_a_get_file(embed_source);
                if( sc_t_equal( path, bcore_source_a_get_file(e) ) )
                {
                    BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Xoico: Cyclic inclusion." ))
                }
            }
    
            }}source = embed_source;
            ((bcore_source*)(x_array_push_d(((x_array*)(stack)),((x_inst*)(source )))));
        BLM_DOWN();}
        else if( bcore_source_a_parse_bl(source," #?w'include' " ) )
        {BLM_INIT_LEVEL(3);
            bl_t deferred = bcore_source_a_parse_bl(source," #?w'deferred' " );
            st_s* include_file = ((st_s*)BLM_LEVEL_T_PUSH(3,st_s,st_s_create()));
            BLM_TRY(bcore_source_a_parse_em_fa(source," #string" , include_file ))
            BLM_TRY(bcore_source_a_parse_em_fa(source," ;" ))
            if( deferred )
            {
                bcore_arr_st_s_push_st(&(o->includes_in_definition),include_file );
            }
            else
            {
                bcore_arr_st_s_push_st(&(o->includes_in_declaration),include_file );
            }
        BLM_DOWN();}
        else
        {
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Xoico: syntax error." ))
        }
    
        BLM_TRY(bcore_source_a_parse_em_fa(source," " ))// consume whitespaces
    }
    
    /// default features
    BLM_TRY(xoico_group_s_push_default_feature_from_sc(o,"@* clone( const );" ))
    BLM_TRY(xoico_group_s_push_default_feature_from_sc(o,"void copy( mutable, const @* src );" ))
    BLM_TRY(xoico_group_s_push_default_feature_from_sc(o,"void discard( mutable );" ))
    
    if( stack->size > 1 )
    {
        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Xoico: Unexpected end of group reached." ))
    }
    
    BLM_RETURNV(er_t, 0)
}

er_t xoico_group_s_finalize( xoico_group_s* o, const xoico_host* host )
{
    // xoico_group.x:448:27
    
    {const xoico_group_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico* e=__a->data[__i]; BLM_TRY(xoico_a_finalize(e,((const xoico_host*)(o ))))
    }}{const xoico_funcs_s* __a=&(o->funcs );if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_func_s* func=__a->data[__i];
    {
        BLM_TRY(xoico_func_s_finalize(func,((const xoico_host*)(o ))))
        BLM_TRY(xoico_compiler_s_register_func(o->compiler,func ))
        bcore_hmap_tpvd_s_set(&(o->hmap_func),func->name, ( vd_t )func );
    }
    }}return  0;
}

er_t xoico_group_s_expand_forward( const xoico_group_s* o, sz_t indent, bcore_sink* sink )
{
    // xoico_group.x:462:74
    
    if( !o->expandable ) return  0;
    bcore_sink_a_push_fa(sink," \\\n#rn{ }BCORE_FORWARD_OBJECT( #<sc_t> );", indent, o->st_name.sc );
    {const xoico_group_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico* e=__a->data[__i]; BLM_TRY(xoico_a_expand_forward(e,((const xoico_host*)(o)), indent, sink ))
    }}{const xoico_funcs_s* __a=&(o->funcs );if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_func_s* func=__a->data[__i]; BLM_TRY(xoico_func_s_expand_forward(func,((const xoico_host*)(o)), indent, sink ))
    }}return  0;
}

er_t xoico_group_s_expand_spect_declaration( const xoico_group_s* o, sz_t indent, bcore_sink* sink )
{
    // xoico_group.x:473:84
    
    if( !o->expandable ) return  0;
    if( o->short_spect_name )
    {
        bcore_sink_a_push_fa(sink," \\\n#rn{ }BCORE_DECLARE_SPECT( #<sc_t> )", indent, o->st_name.sc );
    }
    else
    {
        bcore_sink_a_push_fa(sink," \\\n#rn{ }XOILA_DECLARE_SPECT( #<sc_t> )", indent, o->st_name.sc );
    }
    
    bcore_sink_a_push_fa(sink," \\\n#rn{ }{", indent );
    bcore_sink_a_push_fa(sink," \\\n#rn{ }    bcore_spect_header_s header;", indent );
    {const xoico_group_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico* e=__a->data[__i]; BLM_TRY(xoico_a_expand_spect_declaration(e,((const xoico_host*)(o)), indent + 4, sink ))
    }}bcore_sink_a_push_fa(sink," \\\n#rn{ }};", indent );
    
    bcore_sink_a_push_fa(sink," \\\n#rn{ }"
        "BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( #<sc_t> )",
        indent,
        o->st_name.sc
    );
    
    return  0;
}

er_t xoico_group_s_expand_declaration( const xoico_group_s* o, sz_t indent, bcore_sink* sink )
{
    // xoico_group.x:503:33
    BLM_INIT_LEVEL(0);
    if( !o->expandable ) BLM_RETURNV(er_t, 0)
    
    bcore_sink_a_push_fa(sink,"\n" );
    bcore_sink_a_push_fa(sink,"#rn{ }//#rn{-}\n", indent, sz_max( 0, 118 - indent ) );
    bcore_sink_a_push_fa(sink,"#rn{ }// group: #<sc_t>", indent, o->st_name.sc );
    if( o->explicit_embeddings.size > 0 )
    {
        bcore_sink_a_push_fa(sink,"; embeds:" );
        {const bcore_arr_st_s* __a=&(o->explicit_embeddings );if(__a)for(sz_t __i=0; __i<__a->size; __i++){st_s* st=__a->data[__i]; bcore_sink_a_push_fa(sink," #<st_s*>", st );}}
    }
    bcore_sink_a_push_fa(sink,"\n" );
    
    {const bcore_arr_st_s* __a=&(o->includes_in_declaration );if(__a)for(sz_t __i=0; __i<__a->size; __i++){st_s* e=__a->data[__i]; bcore_sink_a_push_fa(sink,"##include \"#<sc_t>\"\n", e->sc );}}
    
    bcore_sink_a_push_fa(sink,"\n" );
    bcore_sink_a_push_fa(sink,"#rn{ }##define TYPEOF_#<sc_t> 0x#pl16'0'{#X<tp_t>}ull\n", indent, o->st_name.sc, btypeof( o->st_name.sc ) );
    
    st_s* st_spect_name = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,xoico_group_s_create_spect_name( o )));
    sc_t sc_spect_name = st_spect_name->sc;
    
    bcore_sink_a_push_fa(sink,"#rn{ }##define TYPEOF_#<sc_t> 0x#pl16'0'{#X<tp_t>}ull\n", indent, sc_spect_name, btypeof( sc_spect_name ) );
    
    {const xoico_group_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico* e=__a->data[__i]; BLM_TRY(xoico_a_expand_declaration(e,((const xoico_host*)(o)), indent, sink ))
    }}bcore_sink_a_push_fa(sink,"#rn{ }##define BETH_EXPAND_GROUP_#<sc_t>", indent, o->st_name.sc );
    
    BLM_TRY(xoico_group_s_expand_forward(o,indent + 2, sink ))
    
    {const xoico_group_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico* e=__a->data[__i]; BLM_TRY(xoico_a_expand_indef_typedef(e,((const xoico_host*)(o)), indent, sink ))
    }}BLM_TRY(xoico_group_s_expand_spect_declaration(o,indent + 2, sink ))
    
    {const xoico_group_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico* e=__a->data[__i]; BLM_TRY(xoico_a_expand_indef_declaration(e,((const xoico_host*)(o)), indent, sink ))
    }}{const xoico_funcs_s* __a=&(o->funcs );if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_func_s* func=__a->data[__i]; BLM_TRY(xoico_func_s_expand_declaration(func,((const xoico_host*)(o)), indent + 2, sink ))
    
    }}bcore_sink_a_push_fa(sink,"\n" );
    BLM_RETURNV(er_t, 0)
}

er_t xoico_group_s_expand_spect_definition( const xoico_group_s* o, sz_t indent, bcore_sink* sink )
{
    // xoico_group.x:544:83
    
    xoico_compiler_s* compiler = o->compiler;
    if( !o->expandable ) return  0;
    bcore_sink_a_push_fa(sink,"\n" );
    if( o->short_spect_name )
    {
        bcore_sink_a_push_fa(sink,"#rn{ }BCORE_DEFINE_SPECT( #<sc_t>, #<sc_t> )\n", indent, xoico_compiler_s_nameof(compiler,o->trait_name ), o->st_name.sc );
    }
    else
    {
        bcore_sink_a_push_fa(sink,"#rn{ }XOILA_DEFINE_SPECT( #<sc_t>, #<sc_t> )\n", indent, xoico_compiler_s_nameof(compiler,o->trait_name ), o->st_name.sc );
    }
    
    bcore_sink_a_push_fa(sink,"#rn{ }\"{\"\n", indent );
    bcore_sink_a_push_fa(sink,"#rn{ }    \"bcore_spect_header_s header;\"\n", indent );
    {const xoico_group_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico* e=__a->data[__i]; BLM_TRY(xoico_a_expand_spect_definition(e,((const xoico_host*)(o)), indent + 4, sink ))
    }}bcore_sink_a_push_fa(sink,"#rn{ }\"}\";\n", indent );
    return  0;
}

er_t xoico_group_s_expand_definition( const xoico_group_s* o, sz_t indent, bcore_sink* sink )
{
    // xoico_group.x:567:32
    
    if( !o->expandable ) return  0;
    bcore_sink_a_push_fa(sink,"\n" );
    bcore_sink_a_push_fa(sink,"#rn{ }//#rn{-}\n", indent, sz_max( 0, 118 - indent ) );
    bcore_sink_a_push_fa(sink,"#rn{ }// group: #<sc_t>", indent, o->st_name.sc );
    if( o->explicit_embeddings.size > 0 )
    {
        bcore_sink_a_push_fa(sink,"; embeds:" );
        {const bcore_arr_st_s* __a=&(o->explicit_embeddings );if(__a)for(sz_t __i=0; __i<__a->size; __i++){st_s* st=__a->data[__i]; bcore_sink_a_push_fa(sink," #<st_s*>", st );}}
    }
    bcore_sink_a_push_fa(sink,"\n" );
    
    {const bcore_arr_st_s* __a=&(o->includes_in_definition );if(__a)for(sz_t __i=0; __i<__a->size; __i++){st_s* e=__a->data[__i]; bcore_sink_a_push_fa(sink,"##include \"#<sc_t>\"\n", e->sc );}}
    
    // non-features
    {const xoico_group_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico* e=__a->data[__i]; if( e->_ != TYPEOF_xoico_feature_s ) BLM_TRY(xoico_a_expand_definition(e,((const xoico_host*)(o)), indent, sink ))
    
    }}BLM_TRY(xoico_group_s_expand_spect_definition(o,indent, sink ))
    
    // just-features
    {const xoico_group_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico* e=__a->data[__i]; if( e->_ == TYPEOF_xoico_feature_s ) BLM_TRY(xoico_a_expand_definition(e,((const xoico_host*)(o)), indent, sink ))
    
    }}{const xoico_funcs_s* __a=&(o->funcs );if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_func_s* func=__a->data[__i]; BLM_TRY(xoico_func_s_expand_definition(func,((const xoico_host*)(o)), indent, sink ))
    
    }}return  0;
}

er_t xoico_group_s_expand_init1( const xoico_group_s* o, sz_t indent, bcore_sink* sink )
{
    // xoico_group.x:597:27
    
    if( !o->expandable ) return  0;
    bcore_sink_a_push_fa(sink,"\n" );
    bcore_sink_a_push_fa(sink,"#rn{ }// group: #<sc_t>\n", indent, o->st_name.sc );
    {const xoico_group_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico* e=__a->data[__i]; BLM_TRY(xoico_a_expand_init1(e,((const xoico_host*)(o)), indent, sink ))
    
    }}if( o->short_spect_name )
    {
        bcore_sink_a_push_fa(sink,"#rn{ }BCORE_REGISTER_SPECT( #<sc_t> );\n", indent, o->st_name.sc );
    }
    else
    {
        bcore_sink_a_push_fa(sink,"#rn{ }XOILA_REGISTER_SPECT( #<sc_t> );\n", indent, o->st_name.sc );
    }
    
    if( o->retrievable )
    {
        {const xoico_group_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico* e=__a->data[__i];
        {
            if( e->_ == TYPEOF_xoico_stamp_s )
            {
                bcore_sink_a_push_fa(sink,"#rn{ }bcore_inst_s_get_typed( TYPEOF_#<sc_t> );\n", indent, ((xoico_stamp_s*)(e))->st_name.sc );
            }
        }
    }}}
    return  0;
}

XOILA_DEFINE_SPECT( xoico, xoico_group )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/
// source: xoico_stamp.h
#include "xoico_stamp.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_stamp; embeds: xoico_stamp.x

BCORE_DEFINE_OBJECT_INST_P( xoico_stamp_s )
"aware xoico_stamp"
"{"
    "st_s st_name;"
    "tp_t tp_name;"
    "tp_t trait_name;"
    "bl_t is_aware;"
    "st_s => self_buf;"
    "st_s => self_source;"
    "bcore_self_s => self;"
    "xoico_funcs_s funcs;"
    "xoico_transient_map_s transient_map;"
    "private aware xoico_group_s* group;"
    "bcore_source_point_s source_point;"
    "func xoico:get_hash;"
    "func xoico:get_global_name_sc;"
    "func xoico:get_global_name_tp;"
    "func xoico:expand_setup;"
    "func xoico:expand_forward;"
    "func xoico:expand_indef_declaration;"
    "func xoico_host:parse_name;"
    "func xoico_host:compiler;"
    "func xoico_host:cengine;"
    "func xoico_host:obj_type;"
    "func xoico:parse;"
    "func xoico:finalize;"
    "func xoico:expand_declaration;"
    "func xoico:expand_definition;"
    "func xoico:expand_init1;"
"}";

tp_t xoico_stamp_s_get_hash( const xoico_stamp_s* o )
{
    // xoico_stamp.h:57:5
    
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
    hash = bcore_tp_fold_sc( hash, o->st_name.sc );
    hash = bcore_tp_fold_sc( hash, o->self_source ? o->self_source->sc : o->self_buf ? o->self_buf->sc : "" );
    hash = bcore_tp_fold_tp( hash, xoico_funcs_s_get_hash(&(o->funcs)) );
    return  hash;
}

er_t xoico_stamp_s_expand_forward( const xoico_stamp_s* o, const xoico_host* host, sz_t indent, bcore_sink* sink )
{
    // xoico_stamp.h:72:5
    
    bcore_sink_a_push_fa(sink," \\\n#rn{ }BCORE_FORWARD_OBJECT( #<sc_t> );", indent, o->st_name.sc );
    return  0;
}

er_t xoico_stamp_s_expand_indef_declaration( const xoico_stamp_s* o, const xoico_host* host, sz_t indent, bcore_sink* sink )
{
    // xoico_stamp.h:78:5
    
    bcore_sink_a_push_fa(sink," \\\n#rn{ }  BETH_EXPAND_ITEM_#<sc_t>", indent, o->st_name.sc );
    return  0;
}

er_t xoico_stamp_s_make_funcs_overloadable( xoico_stamp_s* o )
{
    // xoico_stamp.h:90:5
    
    {const xoico_funcs_s* __a=&(o->funcs );if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_func_s* func=__a->data[__i]; func->overloadable = true;}}
    return  0;
}

const xoico_func_s* xoico_stamp_s_get_trait_line_func_from_name( const xoico_stamp_s* o, tp_t name )
{
    // xoico_stamp.h:96:5
    
    const xoico_func_s* func = xoico_funcs_s_get_func_from_name(&(o->funcs),name );
    if( !func )
    {
        func = xoico_group_s_get_trait_line_func_from_name(xoico_compiler_s_get_group(o->group->compiler,o->trait_name ),name );
    }
    return  func;
}

sc_t xoico_stamp_s_get_rel_name_sc( const xoico_stamp_s* o )
{
    // xoico_stamp.x:157:1
    
    sc_t group_name = o->group->st_name.sc;
    sc_t stamp_name = o->st_name.sc;
    
    sz_t i = 0;
    while( group_name[ i ] == stamp_name[ i ] && group_name[ i ] != 0 ) i++;
    if( group_name[ i ] == 0 && stamp_name[ i ] == '_' ) i++;
    
    return  stamp_name + i;
}

er_t xoico_stamp_s_parse_func( xoico_stamp_s* o, bcore_source* source )
{
    // xoico_stamp.x:170:25
    BLM_INIT_LEVEL(0);
    xoico_compiler_s* compiler = o->group->compiler;
    xoico_func_s* func = ((xoico_func_s*)BLM_LEVEL_T_PUSH(0,xoico_func_s,xoico_func_s_create()));
    BLM_TRY(xoico_func_s_parse(func,((const xoico_host*)(o)), source ))
    
    sz_t idx = xoico_funcs_s_get_index_from_name(&(o->funcs),func->name );
    
    if( idx >= 0 )
    {
        xoico_func_s* prex_func = o->funcs.data[ idx ];
        if( ( prex_func->signature_global_name == func->signature_global_name ) )
        {
            if( !func->body )
            {
                BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Function '#<sc_t>' has already been declared.", xoico_compiler_s_nameof(compiler,func->name ) ))
            }
            else if( prex_func->body )
            {
                BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Function '#<sc_t>' has already a body.", xoico_compiler_s_nameof(compiler,func->name ) ))
            }
            else
            {
                BLM_TRY(xoico_funcs_s_replace_fork(&(o->funcs),idx, func ))
            }
        }
        else if( prex_func->overloadable )
        {
            BLM_TRY(xoico_funcs_s_replace_fork(&(o->funcs),idx, func ))
        }
        else
        {
            BLM_RETURNV(er_t, bcore_source_point_s_parse_error_fa(&(func->source_point),"Function '#<sc_t>' has already been declared and is not overloadable.", xoico_compiler_s_nameof(compiler,func->name ) ))
        }
    }
    else
    {
        ((xoico_func_s*)(x_array_push_d(((x_array*)(&(o->funcs))),((x_inst*)(((xoico_func_s*)bcore_fork(func)) )))));
    }
    
    BLM_RETURNV(er_t, 0)
}

er_t xoico_stamp_s_parse_extend( xoico_stamp_s* o, bcore_source* source )
{
    // xoico_stamp.x:215:65
    
    ASSERT( o->self_buf );
    
    BLM_TRY(bcore_source_a_parse_em_fa(source," {" ))
    
    while( !bcore_source_a_eos(source) && !bcore_source_a_parse_bl(source," #?'}'" ) )
    {
        if( bcore_source_a_parse_bl(source," #?w'func'" ) )
        {
            BLM_TRY(xoico_stamp_s_parse_func(o,source ))
        }
        else
        {
            bl_t exit = false;
            while( !exit && !bcore_source_a_eos(source) )
            {
                u0_t c =  bcore_source_a_get_u0(source);
                switch( c )
                {
                    case ':':
                    {BLM_INIT_LEVEL(6);
                        st_s* name = ((st_s*)BLM_LEVEL_T_PUSH(6,st_s,st_s_create()));
                        BLM_TRY(xoico_group_s_parse_name_recursive(o->group,source, name ))
                        st_s_push_st(o->self_buf,name );
                    BLM_DOWN();}
                    break;
    
                    case ';':
                    {
                        st_s_push_char(o->self_buf,c );
                        exit = true;
                    }
                    break;
    
                    default:
                    {
                        st_s_push_char(o->self_buf,c );
                    }
                    break;
                }
            }
        }
    }
    BLM_TRY(bcore_source_a_parse_em_fa(source," ; " ))
    
    return  0;
}

er_t xoico_stamp_s_push_default_func_from_sc( xoico_stamp_s* o, sc_t sc )
{
    // xoico_stamp.x:266:65
    BLM_INIT_LEVEL(0);
    xoico_compiler_s* compiler = o->group->compiler;
    xoico_func_s* func = ((xoico_func_s*)BLM_LEVEL_T_PUSH(0,xoico_func_s,xoico_func_s_create()));
    func->overloadable = false;
    func->expandable = false;
    
    BLM_TRY(xoico_parse_sc(((xoico*)(func)),((const xoico_host*)(o)), sc ))
    
    sz_t idx = xoico_funcs_s_get_index_from_signature_global_name(&(o->funcs),func->signature_global_name );
    
    if( idx >= 0 )
    {
        BLM_RETURNV(er_t, bcore_source_point_s_parse_error_fa(&(o->source_point),"Function '#<sc_t>' conflicts with a default function for this stamp.", xoico_compiler_s_nameof(compiler,func->name ) ))
    }
    else
    {
        ((xoico_func_s*)(x_array_push_d(((x_array*)(&(o->funcs))),((x_inst*)(((xoico_func_s*)bcore_fork(func)) )))));
    }
    
    BLM_RETURNV(er_t, 0)
}

er_t xoico_stamp_s_push_default_funcs( xoico_stamp_s* o )
{
    // xoico_stamp.x:291:33
    
    BLM_TRY(xoico_stamp_s_push_default_func_from_sc(o,"bcore_stamp_funcs.init;" ))
    BLM_TRY(xoico_stamp_s_push_default_func_from_sc(o,"bcore_stamp_funcs.down;" ))
    BLM_TRY(xoico_stamp_s_push_default_func_from_sc(o,"bcore_stamp_funcs.copy;" ))
    BLM_TRY(xoico_stamp_s_push_default_func_from_sc(o,"bcore_stamp_funcs.discard;" ))
    BLM_TRY(xoico_stamp_s_push_default_func_from_sc(o,"bcore_stamp_funcs.clone;" ))
    return  0;
}

er_t xoico_stamp_s_parse( xoico_stamp_s* o, const xoico_host* host, bcore_source* source )
{
    // xoico_stamp.x:303:24
    BLM_INIT_LEVEL(0);
    xoico_compiler_s* compiler = o->group->compiler;
    bl_t verbatim = bcore_source_a_parse_bl(source," #?w'verbatim'" );
    st_s_attach( &(o->self_buf ),  st_s_create());
    
    st_s* st_stamp_name = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    st_s* st_trait_name = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    
    bcore_source_point_s_set(&(o->source_point),source );
    
    BLM_TRY(xoico_group_s_parse_name(o->group,source, st_stamp_name ))
    
    if( st_stamp_name->size < 2 || !sc_t_equ( st_stamp_name->sc + st_stamp_name->size - 2, "_s" ) )
    {
        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Stamp name '#<sc_t>' must end in '_s'.", st_stamp_name->sc ))
    }
    
    //    if( st_stamp_name.size >= 2 && sc_t_equ( st_stamp_name.sc + st_stamp_name.size - 2, "_s" ) )
    //    {
    //        return o.source_point.parse_error_fa
    //        (
    //            "Stamp '#<sc_t>' ends in '_s'."
    //            "In beth, this ending identifies a structure."
    //            "Using it as stamp name could have side effects.",
    //            st_stamp_name->sc
    //        );
    //    }
    //
    //    st_s_push_fa( st_stamp_name, "_s" );
    
    BLM_TRY(bcore_source_a_parse_em_fa(source," = " ))
    
    if( bcore_source_a_parse_bl(source," #?w'extending'" ) )
    {
        st_s* templ_name = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
        BLM_TRY(xoico_group_s_parse_name(o->group,source, templ_name ))
        st_s_push_fa(templ_name,"_s" );
        const xoico* item = xoico_compiler_s_get_const_item(compiler,typeof( templ_name->sc ) );
        if( !item ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Template #<sc_t> not found.", templ_name->sc ))
        if( item->_ != TYPEOF_xoico_stamp_s ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Template #<sc_t> is no stamp.", templ_name->sc ))
        xoico_stamp_s_copy(o,((xoico_stamp_s*)(item)) );
    }
    else if( !verbatim && o->group->extending_stamp )
    {
        xoico_stamp_s_copy(o,o->group->extending_stamp );
    }
    else
    {
        if( bcore_source_a_parse_bl(source," #?w'aware'" ) ) o->is_aware = true;
        BLM_TRY(xoico_group_s_parse_name(o->group,source, st_trait_name ))
        if( st_trait_name->size == 0 ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Trait name expected." ))
        o->trait_name = xoico_compiler_s_entypeof(compiler,st_trait_name->sc );
        if( bcore_source_a_parse_bl(source," #=?'('" ) )
        {
            BLM_TRY(xoico_transient_map_s_parse(&(o->transient_map),((const xoico_host*)(o)), source ))
        }
    }
    
    st_s_copy(&(o->st_name),st_stamp_name );
    o->tp_name = xoico_compiler_s_entypeof(compiler,st_stamp_name->sc );
    BLM_TRY(xoico_stamp_s_parse_extend(o,source ))
    
    BLM_RETURNV(er_t, 0)
}

er_t xoico_stamp_s_finalize( xoico_stamp_s* o, const xoico_host* host )
{
    // xoico_stamp.x:371:27
    BLM_INIT_LEVEL(0);
    xoico_compiler_s* compiler = o->group->compiler;
    
    {const xoico_funcs_s* __a=&(o->funcs );if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_func_s* func=__a->data[__i];
    {
        BLM_TRY(xoico_func_s_finalize(func,((const xoico_host*)(o ))))
        if( xoico_func_s_reflectable(func,host ) ) BLM_TRY(xoico_func_s_push_flect_decl_to_sink(func,host,((bcore_sink*)( o->self_buf ))))
        BLM_TRY(xoico_compiler_s_register_func(compiler,func ))
    }
    
    }}st_s_replace_sc_sc(o->self_buf,"@", o->st_name.sc );
    
    st_s_attach( &(o->self_source ),  st_s_create());
    st_s_push_fa(o->self_source,"#<sc_t> =", o->st_name.sc );
    if( o->is_aware ) st_s_push_sc(o->self_source,"aware " );
    st_s_push_sc(o->self_source,xoico_compiler_s_nameof(compiler,o->trait_name ) );
    st_s_push_fa(o->self_source,"{#<st_s*>}", o->self_buf );
    st_s_attach( &(o->self_buf ),  NULL);
    
    bcore_self_s_attach( &(o->self ),  bcore_self_s_parse_source( ((bcore_source*)(((bcore_source_string_s*)BLM_LEVEL_T_PUSH(0,bcore_source_string_s,bcore_source_string_s_create_from_string(o->self_source ))))), 0, 0, o->group->st_name.sc, false ));
    
    // checking for repetitions in o.self (non-functions)
    bcore_hmap_tp_s* hmap_name = ((bcore_hmap_tp_s*)BLM_LEVEL_T_PUSH(0,bcore_hmap_tp_s,bcore_hmap_tp_s_create()));
    sz_t self_items = bcore_self_s_items_size( o->self );
    for( sz_t i = 0; i < self_items; i++ )
    {
        const bcore_self_item_s* item = bcore_self_s_get_item( o->self,i );
        if( item->name && ( item->caps != BCORE_CAPS_EXTERNAL_FUNC ) )
        {
            if( bcore_hmap_tp_s_exists(hmap_name,item->name ) )
            {
                BLM_RETURNV(er_t, bcore_source_point_s_parse_error_fa(&(o->source_point),"In stamp '#<sc_t>': Repeated use of element name '#<sc_t>'.", o->st_name.sc, xoico_compiler_s_nameof(compiler,item->name ) ))
            }
    
            bcore_hmap_tp_s_set(hmap_name,item->name );
        }
    }
    
    // check validity of trait name
    if( !xoico_compiler_s_is_group(compiler,o->trait_name ) )
    {
        BLM_RETURNV(er_t, bcore_source_point_s_parse_error_fa(&(o->source_point),"In stamp '#<sc_t>': Trait name '#<sc_t>' is not a group.", o->st_name.sc, xoico_compiler_s_nameof(compiler,o->trait_name ) ))
    }
    
    // set transient classes for x_array
    if( o->trait_name == TYPEOF_x_array )
    {
        xoico_transient_map_s_set(&(o->transient_map),xoico_compiler_s_entypeof(compiler,"TO" ), o->tp_name );
        const bcore_self_item_s* array_item = bcore_self_s_get_first_array_item( o->self );
        bl_t is_static = false;
    
        switch( array_item->caps )
        {
            case BCORE_CAPS_ARRAY_DYN_SOLID_STATIC:
            case BCORE_CAPS_ARRAY_DYN_LINK_STATIC:
            case BCORE_CAPS_ARRAY_FIX_SOLID_STATIC:
            case BCORE_CAPS_ARRAY_FIX_LINK_STATIC:
                is_static = true;
                break;
    
            default:
                break;
        }
    
        if( is_static )
        {
            xoico_transient_map_s_set(&(o->transient_map),xoico_compiler_s_entypeof(compiler,"TE" ), array_item->type );
        }
    }
    
    
    BLM_RETURNV(er_t, 0)
}

er_t xoico_stamp_s_expand_declaration( const xoico_stamp_s* o, const xoico_host* host, sz_t indent, bcore_sink* sink )
{
    // xoico_stamp.x:448:37
    BLM_INIT_LEVEL(0);
    sc_t sc_name = o->st_name.sc;
    
    bcore_sink_a_push_fa(sink,"#rn{ }##define TYPEOF_#<sc_t> 0x#pl16'0'{#X<tp_t>}ull\n", indent, sc_name, typeof( sc_name ) );
    
    bcore_sink_a_push_fa(sink,"#rn{ }##define BETH_EXPAND_ITEM_#<sc_t>", indent, sc_name, sc_name );
    bcore_sink_a_push_fa(sink," \\\n#rn{ }  BCORE_DECLARE_OBJECT( #<sc_t> )", indent, sc_name );
    bcore_sink_a_push_fa(sink," \\\n" );
    
    bcore_self_s_struct_body_to_sink_newline_escaped( o->self,indent + 2, sink );
    bcore_sink_a_push_fa(sink,";" );
    
    {const xoico_funcs_s* __a=&(o->funcs );if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_func_s* func=__a->data[__i]; BLM_TRY(xoico_func_s_expand_forward(func,((const xoico_host*)(o)), indent + 2, sink )) // expands all prototypes
    
    // expand array
    }}if( o->self->trait == TYPEOF_bcore_array )
    {
        //return o.source_point.parse_error_fa( "Please use x_array as trait." );
    
        sz_t items = bcore_self_s_items_size( o->self);
        const bcore_self_item_s* array_item = NULL;
        for( sz_t i = 0; i < items; i++ )
        {
            const bcore_self_item_s* self_item = bcore_self_s_get_item( o->self,i );
            if( bcore_flect_caps_is_array( self_item->caps ) )
            {
                array_item = self_item;
                break;
            }
        }
    
        if( !array_item )
        {
            BLM_RETURNV(er_t, bcore_source_point_s_parse_error_fa(&(o->source_point),"Expanding object #<sc_t>: Object is of trait array but contains no array.", sc_name ))
        }
    
        bcore_sink_a_push_fa(sink," \\\n#rn{ }  static inline #<sc_t>* #<sc_t>_set_space( #<sc_t>* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_#<sc_t>, ( bcore_array* )o, size ); return o; }", indent, sc_name, sc_name, sc_name, sc_name );
        bcore_sink_a_push_fa(sink," \\\n#rn{ }  static inline #<sc_t>* #<sc_t>_set_size( #<sc_t>* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_#<sc_t>, ( bcore_array* )o, size ); return o; }",   indent, sc_name, sc_name, sc_name, sc_name );
        bcore_sink_a_push_fa(sink," \\\n#rn{ }  static inline #<sc_t>* #<sc_t>_clear( #<sc_t>* o ) { bcore_array_t_set_space( TYPEOF_#<sc_t>, ( bcore_array* )o, 0 ); return o; }",                   indent, sc_name, sc_name, sc_name, sc_name );
    
        sc_t sc_item_name = ifnameof( array_item->name );
        st_s* st_last = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create_fa("o->#<sc_t>#<sc_t>data[ o->#<sc_t>#<sc_t>size - 1 ]", sc_item_name, sc_item_name[ 0 ] ? "_" : "", sc_item_name, sc_item_name[ 0 ] ? "_" : ""  )));
        sc_t sc_last = st_last->sc;
        if( array_item->type != 0 && nameof( array_item->type ) != NULL )
        {
            sc_t sc_type = ifnameof( array_item->type );
            if( array_item->caps == BCORE_CAPS_ARRAY_DYN_LINK_AWARE )
            {
                bcore_sink_a_push_fa(sink," \\\n#rn{ }  static inline #<sc_t>* #<sc_t>_push_c( #<sc_t>* o, const #<sc_t>* v ) { bcore_array_t_push( TYPEOF_#<sc_t>, ( bcore_array* )o, sr_awc( v ) ); return #<sc_t>; }", indent, sc_type, sc_name, sc_name, sc_type, sc_name, sc_last );
                bcore_sink_a_push_fa(sink," \\\n#rn{ }  static inline #<sc_t>* #<sc_t>_push_d( #<sc_t>* o,       #<sc_t>* v ) { bcore_array_t_push( TYPEOF_#<sc_t>, ( bcore_array* )o, sr_asd( v ) ); return #<sc_t>; }", indent, sc_type, sc_name, sc_name, sc_type, sc_name, sc_last );
                bcore_sink_a_push_fa(sink," \\\n#rn{ }  static inline #<sc_t>* #<sc_t>_push_t( #<sc_t>* o, tp_t t )", indent, sc_type, sc_name, sc_name );
                bcore_sink_a_push_fa(sink," \\\n#rn{ }  {", indent );
                bcore_sink_a_push_fa(sink," \\\n#rn{ }      bcore_trait_assert_satisfied_type( TYPEOF_#<sc_t>, t );",                    indent, sc_type );
                bcore_sink_a_push_fa(sink," \\\n#rn{ }      bcore_array_t_push( TYPEOF_#<sc_t>, ( bcore_array* )o, sr_t_create( t ) );", indent, sc_name );
                bcore_sink_a_push_fa(sink," \\\n#rn{ }      return #<sc_t>;", indent, sc_last );
                bcore_sink_a_push_fa(sink," \\\n#rn{ }  }", indent );
            }
            else if( array_item->caps == BCORE_CAPS_ARRAY_DYN_SOLID_STATIC )
            {
                bcore_sink_a_push_fa(sink," \\\n#rn{ }  static inline #<sc_t>* #<sc_t>_push_c( #<sc_t>* o, const #<sc_t>* v ) { bcore_array_t_push( TYPEOF_#<sc_t>, ( bcore_array* )o, sr_twc( TYPEOF_#<sc_t>, v ) ); return &#<sc_t>; }", indent, sc_type, sc_name, sc_name, sc_type, sc_name, sc_type, sc_last );
                bcore_sink_a_push_fa(sink," \\\n#rn{ }  static inline #<sc_t>* #<sc_t>_push_d( #<sc_t>* o,       #<sc_t>* v ) { bcore_array_t_push( TYPEOF_#<sc_t>, ( bcore_array* )o, sr_tsd( TYPEOF_#<sc_t>, v ) ); return &#<sc_t>; }", indent, sc_type, sc_name, sc_name, sc_type, sc_name, sc_type, sc_last );
                bcore_sink_a_push_fa(sink," \\\n#rn{ }  static inline #<sc_t>* #<sc_t>_push( #<sc_t>* o )", indent, sc_type, sc_name, sc_name );
                bcore_sink_a_push_fa(sink," \\\n#rn{ }  {", indent );
                bcore_sink_a_push_fa(sink," \\\n#rn{ }      bcore_array_t_push( TYPEOF_#<sc_t>, ( bcore_array* )o, sr_null() );",   indent, sc_name );
                bcore_sink_a_push_fa(sink," \\\n#rn{ }      return &#<sc_t>;", indent, sc_last );
                bcore_sink_a_push_fa(sink," \\\n#rn{ }  }", indent );
            }
            else if( array_item->caps == BCORE_CAPS_ARRAY_DYN_LINK_STATIC )
            {
                bcore_sink_a_push_fa(sink," \\\n#rn{ }  static inline #<sc_t>* #<sc_t>_push_c( #<sc_t>* o, const #<sc_t>* v ) { bcore_array_t_push( TYPEOF_#<sc_t>, ( bcore_array* )o, sr_twc( TYPEOF_#<sc_t>, v ) ); return #<sc_t>; }", indent, sc_type, sc_name, sc_name, sc_type, sc_name, sc_type, sc_last );
                bcore_sink_a_push_fa(sink," \\\n#rn{ }  static inline #<sc_t>* #<sc_t>_push_d( #<sc_t>* o,       #<sc_t>* v ) { bcore_array_t_push( TYPEOF_#<sc_t>, ( bcore_array* )o, sr_tsd( TYPEOF_#<sc_t>, v ) ); return #<sc_t>; }", indent, sc_type, sc_name, sc_name, sc_type, sc_name, sc_type, sc_last );
                bcore_sink_a_push_fa(sink," \\\n#rn{ }  static inline #<sc_t>* #<sc_t>_push( #<sc_t>* o )", indent, sc_type, sc_name, sc_name );
                bcore_sink_a_push_fa(sink," \\\n#rn{ }  {", indent );
                bcore_sink_a_push_fa(sink," \\\n#rn{ }      bcore_array_t_push( TYPEOF_#<sc_t>, ( bcore_array* )o, sr_t_create( TYPEOF_#<sc_t> ) );", indent, sc_name, sc_type );
                bcore_sink_a_push_fa(sink," \\\n#rn{ }      return #<sc_t>;", indent, sc_last );
                bcore_sink_a_push_fa(sink," \\\n#rn{ }  }", indent );
            }
        }
        else
        {
            if( bcore_flect_caps_is_aware( array_item->caps ) )
            {
                bcore_sink_a_push_fa(sink," \\\n#rn{ }  static inline void #<sc_t>_push_c( #<sc_t>* o, vc_t v ) { bcore_array_t_push( TYPEOF_#<sc_t>, ( bcore_array* )o, sr_awc( v ) ); }", indent, sc_name, sc_name, sc_name );
                bcore_sink_a_push_fa(sink," \\\n#rn{ }  static inline void #<sc_t>_push_d( #<sc_t>* o, vd_t v ) { bcore_array_t_push( TYPEOF_#<sc_t>, ( bcore_array* )o, sr_asd( v ) ); }", indent, sc_name, sc_name, sc_name );
            }
        }
    }
    
    {const xoico_funcs_s* __a=&(o->funcs );if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_func_s* func=__a->data[__i]; BLM_TRY(xoico_func_s_expand_declaration(func,((const xoico_host*)(o)), indent + 2, sink )) // only expands static inline functions
    
    }}bcore_sink_a_push_fa(sink,"\n" );
    BLM_RETURNV(er_t, 0)
}

er_t xoico_stamp_s_expand_definition( const xoico_stamp_s* o, const xoico_host* host, sz_t indent, bcore_sink* sink )
{
    // xoico_stamp.x:545:36
    BLM_INIT_LEVEL(0);
    st_s* embedded_string = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,xoico_stamp_create_embedded_string(o->self_source )));
    
    // 4095 is the C99-limit for string literals
    if( embedded_string->size > 4095 )
    {
        BLM_RETURNV(er_t, bcore_source_point_s_parse_error_fa(&(o->source_point),"Reflection embedding failed. (Stamp is too large)\n"
            "The embedded code would require a string literal larger than 4095 characters.\n"
            "This exceeds the limit defined in C99.\n"
        ))
    }
    
    sz_t idx = st_s_find_char(embedded_string,0, -1, '=' );
    sc_t self_def = "";
    if( idx < embedded_string->size )
    {
        self_def = embedded_string->sc + idx + 1;
    }
    
    bcore_sink_a_push_fa(sink,"\n" );
    bcore_sink_a_push_fa(sink,"#rn{ }BCORE_DEFINE_OBJECT_INST_P( #<sc_t> )\n", indent, o->st_name.sc );
    
    st_s* multiline_string = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,xoico_stamp_create_structured_multiline_string(self_def, indent )));
    bcore_sink_a_push_fa(sink,"#<sc_t>;\n", multiline_string->sc );
    
    {const xoico_funcs_s* __a=&(o->funcs );if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_func_s* func=__a->data[__i]; BLM_TRY(xoico_func_s_expand_definition(func,((const xoico_host*)(o)), indent, sink ))
    
    }}BLM_RETURNV(er_t, 0)
}

er_t xoico_stamp_s_expand_init1( const xoico_stamp_s* o, const xoico_host* host, sz_t indent, bcore_sink* sink )
{
    // xoico_stamp.x:580:31
    
    xoico_compiler_s* compiler = o->group->compiler;
    
    {const xoico_funcs_s* __a=&(o->funcs );if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_func_s* func=__a->data[__i];
    {
        if( xoico_func_s_reflectable(func,host ) )
        {
            const xoico_signature_s* signature = func->signature;
            bcore_sink_a_push_fa(sink,"#rn{ }BCORE_REGISTER_FFUNC( #<sc_t>, #<sc_t>_#<sc_t> );\n",
                indent,
                xoico_compiler_s_nameof(compiler,signature->global_name ),
                o->st_name.sc,
                xoico_compiler_s_nameof(compiler,func->name )
            );
        }
    }
    }}bcore_sink_a_push_fa(sink,"#rn{ }BCORE_REGISTER_OBJECT( #<sc_t> );\n", indent, o->st_name.sc );
    return  0;
}

XOILA_DEFINE_SPECT( xoico, xoico_stamp )
"{"
    "bcore_spect_header_s header;"
"}";

st_s* xoico_stamp_create_embedded_string( const st_s* s )
{
    // xoico_stamp.x:22:1
    
    st_s* out = st_s_create();
    for( sz_t i = 0; i < s->size; i++ )
    {
        if( s->data[ i ] == '/' && s->data[ i + 1 ] == '/' )
        {
            while( i < s->size && s->data[ i ] != '\n' ) i++;
        }
        else if( s->data[ i ] == '/' && s->data[ i + 1 ] == '*' )
        {
            while( i < s->size )
            {
                if( s->data[ i ] == '*' && s->data[ i + 1 ] == '/' )
                {
                    if( out->data[ out->size - 1 ] != ' ' ) st_s_push_char(out,' ' );
                    i += 2;
                    break;
                }
                i++;
            }
        }
        else if( s->data[ i ] == '"' )
        {
            st_s_push_char(out,'\\' );
            st_s_push_char(out,'"' );
            i++;
            while( i < s->size && s->data[ i ] != '"' ) st_s_push_char(out,s->data[ i++ ] );
            if( s->data[ i ] == '"' )
            {
                st_s_push_char(out,'\\' );
                st_s_push_char(out,'"' );
            }
        }
        else if( s->data[ i ] == '\n' )
        {
            if( out->data[ out->size - 1 ] != ' ' ) st_s_push_char(out,' ' );
        }
        else if( s->data[ i ] == '\t' )
        {
            if( out->data[ out->size - 1 ] != ' ' ) st_s_push_char(out,' ' );
        }
        else if( s->data[ i ] == ' ' )
        {
            if( out->data[ out->size - 1 ] != ' ' ) st_s_push_char(out,' ' );
        }
        else
        {
            st_s_push_char(out,s->data[ i ] );
        }
    }
    if( out->size > 0 && out->data[ out->size - 1 ] == ' ' )
    {
        out->data[ out->size - 1 ] = 0;
        out->size--;
    }
    return  out;
}

st_s* xoico_stamp_create_structured_multiline_string( const sc_t s, sz_t indent )
{
    // xoico_stamp.x:86:1
    
    st_s* out = st_s_create();
    sz_t ind = indent;
    bl_t newline = true;
    for( sz_t i = 0; s[ i ] != 0; i++ )
    {
        char c = s[ i ];
        if( c == ';' )
        {
            if( newline ) st_s_push_fa(out,"#rn{ }\"", ind );
            st_s_push_char(out,c );
            st_s_push_fa(out,"\"\n" );
            newline = true;
        }
        else if( c == '{' )
        {
            if( newline )
            {
                st_s_push_fa(out,"#rn{ }\"{\"", ind );
            }
            else
            {
                st_s_push_fa(out,"\"\n#rn{ }\"{\"", ind );
            }
            if( s[ i + 1 ] != 0 ) st_s_push_char(out,'\n' );
            ind += 4;
            newline = true;
    
        }
        else if( c == '}' )
        {
            ind -= 4;
            if( newline )
            {
                st_s_push_fa(out,"#rn{ }\"}\"", ind );
            }
            else
            {
                st_s_push_fa(out,"\"\n#rn{ }\"}\"", ind );
            }
            if( s[ i + 1 ] != 0 ) st_s_push_char(out,'\n' );
            newline = true;
        }
        else if( c == ' ' )
        {
            if( !newline )
            {
                if( s[ i + 1 ] != ';' && s[ i + 1 ] != '{' && s[ i + 1 ] != '}' && s[ i + 1 ] != 0 )
                {
                    st_s_push_char(out,c );
                }
            }
        }
        else
        {
            if( newline )
            {
                st_s_push_fa(out,"#rn{ }\"", ind );
                newline = false;
            }
            st_s_push_char(out,c );
        }
    }
    
    if( !newline ) st_s_push_char(out,'"' );
    return  out;
}

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

tp_t xoico_nested_group_s_get_hash( const xoico_nested_group_s* o )
{
    // xoico_nested_group.h:32:5
    
    return  o->group ? xoico_group_s_get_hash(o->group) : 0;
}

er_t xoico_nested_group_s_expand_forward( const xoico_nested_group_s* o, const xoico_host* host, sz_t indent, bcore_sink* sink )
{
    // xoico_nested_group.h:37:5
    
    bcore_sink_a_push_fa(sink," \\\n#rn{ }BCORE_FORWARD_OBJECT( #<sc_t> );", indent, o->group->st_name.sc );
    return  0;
}

er_t xoico_nested_group_s_expand_indef_declaration( const xoico_nested_group_s* o, const xoico_host* host, sz_t indent, bcore_sink* sink )
{
    // xoico_nested_group.h:43:5
    
    bcore_sink_a_push_fa(sink," \\\n#rn{ }  BETH_EXPAND_GROUP_#<sc_t>", indent, o->group->st_name.sc );
    return  0;
}

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
    "xoico_group_s => [];"
    "hidden aware xoico_target_s* target;"
    "func xoico:expand_setup;"
    "func xoico:get_hash;"
    "func xoico:finalize;"
    "func xoico:expand_declaration;"
    "func xoico:expand_definition;"
    "func xoico:expand_init1;"
    "func xoico_host:compiler;"
    "func xoico:parse;"
"}";

er_t xoico_source_s_expand_setup( xoico_source_s* o, const xoico_host* host )
{
    // xoico_source.h:40:5
    
    {const xoico_source_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_group_s* e=__a->data[__i]; BLM_TRY(xoico_group_s_expand_setup(e,((const xoico_host*)(o ))))
    }}return  0;
}

er_t xoico_source_s_push_d( xoico_source_s* o, xoico_group_s* group )
{
    // xoico_source.h:46:5
    
    bcore_array_a_push( ((bcore_array*)(o)),sr_asd( group ) );
    return  0;
}

tp_t xoico_source_s_get_hash( const xoico_source_s* o )
{
    // xoico_source.h:52:5
    
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
    {const xoico_source_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_group_s* e=__a->data[__i]; hash = bcore_tp_fold_tp( hash, xoico_group_s_get_hash(e) );}}
    return  hash;
}

er_t xoico_source_s_finalize( xoico_source_s* o, const xoico_host* host )
{
    // xoico_source.h:61:5
    
    {const xoico_source_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_group_s* e=__a->data[__i]; BLM_TRY(xoico_group_s_finalize(e,((const xoico_host*)(o ))))
    }}return  0;
}

er_t xoico_source_s_expand_declaration( const xoico_source_s* o, const xoico_host* host, sz_t indent, bcore_sink* sink )
{
    // xoico_source.h:68:5
    
    bcore_sink_a_push_fa(sink,"\n" );
    bcore_sink_a_push_fa(sink,"#rn{ }/*#rn{*}*/\n", indent, sz_max( 0, 116 - indent ) );
    bcore_sink_a_push_fa(sink,"#rn{ }// source: #<sc_t>.h\n", indent, o->name.sc );
    {const xoico_source_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_group_s* e=__a->data[__i]; BLM_TRY(xoico_group_s_expand_declaration(e,indent, sink ))
    }}return  0;
}

er_t xoico_source_s_expand_definition( const xoico_source_s* o, const xoico_host* host, sz_t indent, bcore_sink* sink )
{
    // xoico_source.h:77:5
    
    bcore_sink_a_push_fa(sink,"\n" );
    bcore_sink_a_push_fa(sink,"#rn{ }/*#rn{*}*/\n", indent, sz_max( 0, 116 - indent ) );
    bcore_sink_a_push_fa(sink,"#rn{ }// source: #<sc_t>.h\n", indent, o->name.sc );
    bcore_sink_a_push_fa(sink,"#rn{ }##include \"#<sc_t>.h\"\n", indent, o->name.sc );
    {const xoico_source_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_group_s* e=__a->data[__i]; BLM_TRY(xoico_group_s_expand_definition(e,indent, sink ))
    }}return  0;
}

er_t xoico_source_s_expand_init1( const xoico_source_s* o, const xoico_host* host, sz_t indent, bcore_sink* sink )
{
    // xoico_source.h:87:5
    
    bcore_sink_a_push_fa(sink,"\n" );
    bcore_sink_a_push_fa(sink,"#rn{ }// #rn{-}\n", indent, sz_max( 0, 80 - indent ) );
    bcore_sink_a_push_fa(sink,"#rn{ }// source: #<sc_t>.h\n", indent, o->name.sc );
    {const xoico_source_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_group_s* e=__a->data[__i]; BLM_TRY(xoico_group_s_expand_init1(e,indent, sink ))
    }}return  0;
}

void xoico_source_s_explicit_embeddings_push( const xoico_source_s* o, bcore_arr_st_s* arr )
{
    // xoico_source.h:96:5
    
    {const xoico_source_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_group_s* group=__a->data[__i]; xoico_group_s_explicit_embeddings_push(group,arr );}}
}

xoico_compiler_s* xoico_source_s_compiler( const xoico_source_s* o )
{
    // xoico_source.h:101:5
    
    return  o->target->compiler;
}

er_t xoico_source_s_parse( xoico_source_s* o, const xoico_host* host, bcore_source* source )
{
    // xoico_source.h:108:24
    BLM_INIT_LEVEL(0);
    xoico_compiler_s* compiler = o->target->compiler;
    while( !bcore_source_a_eos(source) )
    {
        xoico_group_s* group = NULL;
    
        if( bcore_source_a_parse_bl(source," #?w'XOILA_DEFINE_GROUP'" ) )
        {
            group = ((xoico_group_s*)BLM_LEVEL_T_PUSH(0,xoico_group_s,xoico_group_s_create()));
            BLM_TRY(xoico_source_s_push_d(o,((xoico_group_s*)bcore_fork(group)) ))
            group->xoico_source = o;
            group->compiler = compiler;
    
            st_s* st_trait_name = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
            BLM_TRY(bcore_source_a_parse_em_fa(source," ( #name, #name", (&(group->st_name)), (st_trait_name) ))
            group->trait_name = xoico_compiler_s_entypeof(compiler,st_trait_name->sc );
    
            if( bcore_source_a_parse_bl(source,"#?','" ) )
            {
                st_s* embed_file = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
                BLM_TRY(bcore_source_a_parse_em_fa(source," #string )", embed_file ))
                bcore_source* include_source = NULL;
                BLM_TRY(xoico_embed_file_open(source, embed_file->sc, (&(include_source)) ))
                ((bcore_source*)BLM_LEVEL_A_PUSH(0,include_source));
                bcore_arr_st_s_push_st(&(group->explicit_embeddings),embed_file );
                BLM_TRY(xoico_group_s_parse(group,((const xoico_host*)(o)), include_source ))
            }
            else
            {
                BLM_TRY(bcore_source_a_parse_em_fa(source," )" ))
                BLM_TRY(xoico_group_s_parse(group,((const xoico_host*)(o)), source ))
            }
            BLM_TRY(xoico_compiler_s_register_group(o->target->compiler,group ))
        }
        else
        {
            bcore_source_a_get_u0(source);
        }
    }
    BLM_RETURNV(er_t, 0)
}

XOILA_DEFINE_SPECT( xoico, xoico_source )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/
// source: xoico_target.h
#include "xoico_target.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_target; embeds: xoico_target.x

BCORE_DEFINE_OBJECT_INST_P( xoico_target_s )
"aware xoico_target"
"{"
    "st_s name;"
    "st_s include_path;"
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
    "hidden aware xoico_compiler_s* compiler;"
    "func xoico:finalize;"
    "func xoico:expand_setup;"
    "func xoico_host:compiler;"
    "func xoico_host:cengine;"
"}";

er_t xoico_target_s_finalize( xoico_target_s* o, const xoico_host* host )
{
    // xoico_target.h:62:5
    
    {const xoico_target_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_source_s* e=__a->data[__i]; BLM_TRY(xoico_source_s_finalize(e,((const xoico_host*)(o ))))
    }}return  0;
}

er_t xoico_target_s_expand_setup( xoico_target_s* o, const xoico_host* host )
{
    // xoico_target.h:68:5
    
    {const xoico_target_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_source_s* e=__a->data[__i]; BLM_TRY(xoico_source_s_expand_setup(e,((const xoico_host*)(o ))))
    }}return  0;
}

void xoico_target_s_push_d( xoico_target_s* o, xoico_source_s* source )
{
    // xoico_target.h:79:5
    
    bcore_array_a_push( ((bcore_array*)(o)),sr_asd( source ) );
}

void xoico_target_s_explicit_embeddings_push( const xoico_target_s* o, bcore_arr_st_s* arr )
{
    // xoico_target.h:84:5
    
    {const xoico_target_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_source_s* source=__a->data[__i]; xoico_source_s_explicit_embeddings_push(source,arr );}}
}

er_t xoico_target_s_parse_from_path( xoico_target_s* o, sc_t source_path )
{
    // xoico_target.x:20:30
    BLM_INIT_LEVEL(0);
    st_s* source_name        = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,bcore_file_strip_extension(bcore_file_name(source_path ) )));
    st_s* source_folder_path = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,bcore_file_folder_path(source_path )));
    st_s* source_path_n      = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create_fa("#<sc_t>/#<sc_t>", source_folder_path->sc, source_name->sc )));
    st_s* source_path_h      = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create_fa("#<sc_t>.h", source_path_n->sc )));
    
    bl_t source_exists = false;
    
    {const xoico_target_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_source_s* e=__a->data[__i];
    {
        if( st_s_equal_st(source_path_n,&(e->path )) )
        {
            source_exists = true;
            break;
        }
    }
    
    }}if( !source_exists )
    {
        xoico_source_s* xsource = ((xoico_source_s*)BLM_LEVEL_T_PUSH(0,xoico_source_s,xoico_source_s_create()));
        xsource->target = o;
    
        st_s_copy_sc(&(xsource->name),source_name->sc );
        st_s_copy(&(xsource->path),source_path_n );
    
        if( bcore_file_exists(source_path_h->sc ) )
        {
            BLM_TRY(xoico_source_s_parse(xsource,((const xoico_host*)(o)), ((bcore_source*)BLM_LEVEL_A_PUSH(0,bcore_file_open_source(source_path_h->sc ))) ))
        }
    
        xoico_target_s_push_d(o,((xoico_source_s*)bcore_fork(xsource)) );
    }
    
    BLM_RETURNV(er_t, 0)
}

tp_t xoico_target_s_get_hash( const xoico_target_s* o )
{
    // xoico_target.x:60:1
    BLM_INIT_LEVEL(0);
    tp_t hash = bcore_tp_init();
    
    hash = bcore_tp_fold_tp( hash, o->compiler->target_pre_hash );
    hash = bcore_tp_fold_tp( hash, o->_ );
    hash = bcore_tp_fold_sc( hash, o->name.sc );
    
    if( o->cengine ) hash = bcore_tp_fold_tp( hash, xoico_cengine_a_get_hash(o->cengine) );
    
    {const xoico_target_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_source_s* e=__a->data[__i]; hash = bcore_tp_fold_tp( hash, xoico_source_s_get_hash(e) );}}
    
    if( o->dependencies.size > 0 )
    {
        bcore_arr_tp_s* arr_tp = ((bcore_arr_tp_s*)BLM_LEVEL_T_PUSH(0,bcore_arr_tp_s,bcore_arr_tp_s_create()));
    
        {const bcore_arr_sz_s* __a=&(o->dependencies );if(__a)for(sz_t __i=0; __i<__a->size; __i++){sz_t target_idx=__a->data[__i]; bcore_arr_tp_s_push(arr_tp,xoico_target_s_get_hash(o->compiler->data[ target_idx ]) );}}
    
        // we sort to make the accrued hash independent of the order of dependencies
        bcore_arr_tp_s_sort(arr_tp,1 );
    
        {const bcore_arr_tp_s* __a=arr_tp ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){tp_t tp=__a->data[__i]; hash = bcore_tp_fold_tp( hash, tp );}}
    }
    
    BLM_RETURNV(tp_t, hash)
}

bl_t xoico_target_s_is_cyclic_recursive( xoico_target_s* o )
{
    // xoico_target.x:90:1
    
    if( o->flag ) return  true;
    o->flag = true;
    {const bcore_arr_sz_s* __a=&(o->dependencies );if(__a)for(sz_t __i=0; __i<__a->size; __i++){sz_t target_idx=__a->data[__i]; if( xoico_target_s_is_cyclic_recursive(o->compiler->data[ target_idx ]) ) return  true;
    }}o->flag = false;
    return  false;
}

bl_t xoico_target_s_is_cyclic( xoico_target_s* o )
{
    // xoico_target.x:101:1
    
    xoico_compiler_s_clear_flags(o->compiler);
    bl_t cyclic = xoico_target_s_is_cyclic_recursive(o);
    xoico_compiler_s_clear_flags(o->compiler);
    return  cyclic;
}

er_t xoico_target_s_set_dependencies( xoico_target_s* o, const bcore_arr_sz_s* dependencies )
{
    // xoico_target.x:110:31
    BLM_INIT_LEVEL(0);
    sz_t targets = o->compiler->size;
    
    /// sort, remove duplicates, copy
    bcore_arr_sz_s* dst =&( o->dependencies);
    bcore_arr_sz_s_set_size(dst,0 );
    bcore_arr_sz_s* src = bcore_arr_sz_s_sort(((bcore_arr_sz_s*)BLM_LEVEL_T_PUSH(0,bcore_arr_sz_s,bcore_arr_sz_s_clone(dependencies))),1 );
    for( sz_t i = 0; i < src->size; i++ )
    {
        if( i == 0 || src->data[ i ] != src->data[ i - 1 ] )
        {
            sz_t idx = src->data[ i ];
            ASSERT( idx >= 0 && idx < targets );
            bcore_arr_sz_s_push(dst,idx );
        }
    }
    
    if( xoico_target_s_is_cyclic(o) )
    {
        BLM_RETURNV(er_t, bcore_error_push_fa( TYPEOF_general_error, "Cyclic dependencies found in target '#<sc_t>'.", o->name.sc ))
    }
    
    BLM_RETURNV(er_t, 0)
}

er_t xoico_target_s_expand_heading( const xoico_target_s* o, sz_t indent, bcore_sink* sink )
{
    // xoico_target.x:138:74
    BLM_INIT_LEVEL(0);
    bcore_cday_utc_s* time = ((bcore_cday_utc_s*)BLM_LEVEL_T_PUSH(0,bcore_cday_utc_s,bcore_cday_utc_s_create()));
    bcore_cday_utc_s_from_system( time);
    
    bcore_sink_a_push_fa(sink,"/** This file was generated from xoila source code.\n" );
    bcore_sink_a_push_fa(sink," *  Compiling Agent : xoico_compiler (C) 2020 J.B.Steffens\n" );
    bcore_sink_a_push_fa(sink," *  Last File Update: " );
    bcore_cday_utc_s_to_sink( time,sink );
    bcore_sink_a_push_fa(sink,"\n" );
    bcore_sink_a_push_fa(sink," *\n" );
    bcore_sink_a_push_fa(sink," *  Copyright and License of this File:\n" );
    bcore_sink_a_push_fa(sink," *\n" );
    bcore_sink_a_push_fa(sink," *  Generated code inherits the copyright and license of the underlying xoila source code.\n" );
    bcore_sink_a_push_fa(sink," *  Source code defining this file is distributed across following files:\n" );
    bcore_sink_a_push_fa(sink," *\n" );
    
    {const xoico_target_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_source_s* e=__a->data[__i]; bcore_sink_a_push_fa(sink," *  #<sc_t>.h\n", e->name.sc );}}
    
    {
        bcore_arr_st_s* arr = ((bcore_arr_st_s*)BLM_LEVEL_T_PUSH(0,bcore_arr_st_s,bcore_arr_st_s_create()));
        xoico_target_s_explicit_embeddings_push(o,arr );
        bcore_arr_st_s_sort(arr,1 );
        if( arr->size > 0 )
        {
            st_s* prev_file = NULL;
            {const bcore_arr_st_s* __a=arr ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){st_s* file=__a->data[__i];
            {
                if( !st_s_equal_st(file,prev_file ) ) bcore_sink_a_push_fa(sink," *  #<sc_t>\n", file->sc );
                prev_file = file;
            }
        }}}
    }
    
    
    bcore_sink_a_push_fa(sink," *\n" );
    bcore_sink_a_push_fa(sink," */\n" );
    BLM_RETURNV(er_t, 0)
}

er_t xoico_target_s_expand_h( const xoico_target_s* o, sz_t indent, bcore_sink* sink )
{
    // xoico_target.x:180:68
    
    BLM_TRY(xoico_target_s_expand_heading(o,indent, sink ))
    
    tp_t target_hash = xoico_target_s_get_hash(o);
    
    bcore_sink_a_push_fa(sink,"\n" );
    bcore_sink_a_push_fa(sink,"#rn{ }##ifndef __#<sc_t>_H\n", indent, o->name.sc );
    bcore_sink_a_push_fa(sink,"#rn{ }##define __#<sc_t>_H\n", indent, o->name.sc );
    
    bcore_sink_a_push_fa(sink,"\n" );
    bcore_sink_a_push_fa(sink,"#rn{ }##include \"bcore_control.h\"\n", indent );
    
    bcore_sink_a_push_fa(sink,"\n" );
    
    bcore_sink_a_push_fa(sink,"#rn{ }//To force a rebuild of this target by xoico, reset the hash key value below to 0.\n", indent, o->name.sc, target_hash );
    bcore_sink_a_push_fa(sink,"#rn{ }##define HKEYOF_#<sc_t> 0x#pl16'0'{#X<tp_t>}ull\n", indent, o->name.sc, target_hash );
    
    bcore_sink_a_push_fa(sink,"\n" );
    
    bcore_sink_a_push_fa(sink,"#rn{ }##define TYPEOF_#<sc_t> 0x#pl16'0'{#X<tp_t>}ull\n", indent, o->name.sc, typeof( o->name.sc ) );
    
    {const xoico_target_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_source_s* e=__a->data[__i]; BLM_TRY(xoico_source_s_expand_declaration(e,((const xoico_host*)(o)), indent, sink ))
    
    }}bcore_sink_a_push_fa(sink,"\n" );
    bcore_sink_a_push_fa(sink,"#rn{ }/*#rn{*}*/\n", indent, sz_max( 0, 116 - indent ) );
    bcore_sink_a_push_fa(sink,"\n" );
    bcore_sink_a_push_fa(sink,"#rn{ }vd_t #<sc_t>_signal_handler( const bcore_signal_s* o );\n", indent, o->name.sc );
    
    bcore_sink_a_push_fa(sink,"\n" );
    bcore_sink_a_push_fa(sink,"#rn{ }##endif // __#<sc_t>_H\n", indent, o->name.sc );
    
    return  0;
}

er_t xoico_target_s_expand_init1( const xoico_target_s* o, sz_t indent, bcore_sink* sink )
{
    // xoico_target.x:218:1
    
    return  0;
}

er_t xoico_target_s_expand_c( const xoico_target_s* o, sz_t indent, bcore_sink* sink )
{
    // xoico_target.x:224:68
    
    BLM_TRY(xoico_target_s_expand_heading(o,indent, sink ))
    
    bcore_sink_a_push_fa(sink,"\n" );
    bcore_sink_a_push_fa(sink,"#rn{ }##include \"#<sc_t>.h\"\n", indent, o->include_path.sc );
    bcore_sink_a_push_fa(sink,"#rn{ }##include \"bcore_spect.h\"\n", indent );
    bcore_sink_a_push_fa(sink,"#rn{ }##include \"bcore_spect_inst.h\"\n", indent );
    bcore_sink_a_push_fa(sink,"#rn{ }##include \"bcore_sr.h\"\n", indent );
    bcore_sink_a_push_fa(sink,"#rn{ }##include \"bcore_const_manager.h\"\n", indent );
    
    /// definition section
    bcore_sink_a_push_fa(sink,"\n" );
    {const xoico_target_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_source_s* e=__a->data[__i]; BLM_TRY(xoico_source_s_expand_definition(e,((const xoico_host*)(o)), indent, sink ))
    
    /// signal section
    }}bcore_sink_a_push_fa(sink,"\n" );
    bcore_sink_a_push_fa(sink,"#rn{ }/*#rn{*}*/\n", indent, sz_max( 0, 116 - indent ) );
    bcore_sink_a_push_fa(sink,"\n" );
    
    /// prototypes of signal handlers this target depends on
    {const bcore_arr_sz_s* __a=&(o->dependencies );if(__a)for(sz_t __i=0; __i<__a->size; __i++){sz_t target_idx=__a->data[__i];
    {
        const xoico_target_s* target = o->compiler->data[ target_idx ];
        if( target->signal_handler_name.size > 0 )
        {
            bcore_sink_a_push_fa(sink,"#rn{ }vd_t #<sc_t>( const bcore_signal_s* o );\n", indent, target->signal_handler_name.sc );
        }
    }
    
    }}bcore_sink_a_push_fa(sink,"\n" );
    bcore_sink_a_push_fa(sink,"#rn{ }vd_t #<sc_t>_signal_handler( const bcore_signal_s* o )\n", indent, o->name.sc );
    bcore_sink_a_push_fa(sink,"#rn{ }{\n", indent );
    bcore_sink_a_push_fa(sink,"#rn{ }    switch( bcore_signal_s_handle_type( o, typeof( \"#<sc_t>\" ) ) )\n", indent, o->name.sc );
    bcore_sink_a_push_fa(sink,"#rn{ }    {\n", indent );
    
    bcore_sink_a_push_fa(sink,"#rn{ }        case TYPEOF_init1:\n", indent );
    bcore_sink_a_push_fa(sink,"#rn{ }        {\n", indent );
    BLM_TRY(xoico_target_s_expand_init1(o,indent + 12, sink ))
    {const xoico_target_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_source_s* e=__a->data[__i]; BLM_TRY(xoico_source_s_expand_init1(e,((const xoico_host*)(o)), indent + 12, sink ))
    }}bcore_sink_a_push_fa(sink,"#rn{ }        }\n", indent );
    bcore_sink_a_push_fa(sink,"#rn{ }        break;\n", indent );
    
    if( o->dependencies.size > 0 )
    {
        bcore_sink_a_push_fa(sink,"#rn{ }        case TYPEOF_push_dependencies:\n", indent );
        bcore_sink_a_push_fa(sink,"#rn{ }        {\n", indent );
        bcore_sink_a_push_fa(sink,"#rn{ }            ASSERT( o->object && ( *( aware_t* )o->object ) == TYPEOF_bcore_arr_fp_s );\n", indent );
        bcore_sink_a_push_fa(sink,"#rn{ }            bcore_arr_fp_s* arr_fp = o->object;\n", indent );
        {const bcore_arr_sz_s* __a=&(o->dependencies );if(__a)for(sz_t __i=0; __i<__a->size; __i++){sz_t target_idx=__a->data[__i];
        {
            const xoico_target_s* target = o->compiler->data[ target_idx ];
            if( target->signal_handler_name.size > 0 )
            {
                bcore_sink_a_push_fa(sink,"#rn{ }            bcore_arr_fp_s_push( arr_fp, ( fp_t )#<sc_t> );\n", indent, target->signal_handler_name.sc );
            }
        }
        }}bcore_sink_a_push_fa(sink,"#rn{ }        }\n", indent );
        bcore_sink_a_push_fa(sink,"#rn{ }        break;\n", indent );
    }
    
    bcore_sink_a_push_fa(sink,"#rn{ }        default: break;\n", indent );
    bcore_sink_a_push_fa(sink,"#rn{ }    }\n", indent );
    bcore_sink_a_push_fa(sink,"#rn{ }    return NULL;\n", indent );
    bcore_sink_a_push_fa(sink,"#rn{ }}\n", indent );
    return  0;
}

bl_t xoico_target_s_to_be_modified( const xoico_target_s* o )
{
    // xoico_target.x:295:1
    BLM_INIT_LEVEL(0);
    if( o->compiler->always_expand ) BLM_RETURNV(bl_t, true)
    
    bl_t to_be_modified = true;
    
    tp_t target_hash = xoico_target_s_get_hash(o);
    
    st_s* file_h = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create_fa("#<sc_t>.h", o->path.sc )));
    if( bcore_file_exists(file_h->sc ) )
    {
        st_s* key_defined = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create_fa("##?'define HKEYOF_#<sc_t>'", o->name.sc )));
        bcore_source* source = ((bcore_source*)BLM_LEVEL_A_PUSH(0,bcore_file_open_source(file_h->sc )));
        while( !bcore_source_a_eos(source) )
        {
            char c = bcore_source_a_get_u0(source);
            if( c == '#' )
            {
                if( bcore_source_a_parse_bl(source,key_defined->sc ) )
                {
                    tp_t key_val = 0;
                    bcore_source_a_parse_fa(source," #<tp_t*>", &key_val );
                    to_be_modified = ( key_val != target_hash );
                    break;
                }
            }
        }
    }
    
    BLM_RETURNV(bl_t, to_be_modified)
}

er_t xoico_target_s_expand_phase1( xoico_target_s* o, bl_t* p_modified )
{
    // xoico_target.x:329:28
    BLM_INIT_LEVEL(0);
    st_s_attach( &(o->target_h ),  NULL);
    st_s_attach( &(o->target_c ),  NULL);
    o->modified = false;
    
    if( xoico_target_s_to_be_modified(o) )
    {
        o->target_h = st_s_create();
        o->target_c = st_s_create();
        if( !o->compiler->dry_run )
        {
            BLM_TRY(xoico_target_s_expand_h(o,0,((bcore_sink*)( o->target_h ))))
            BLM_TRY(xoico_target_s_expand_c(o,0,((bcore_sink*)( o->target_c ))))
        }
        else
        {
            st_s* buf = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
            BLM_TRY(xoico_target_s_expand_h(o,0,((bcore_sink*)( buf ))))
            BLM_TRY(xoico_target_s_expand_c(o,0,((bcore_sink*)( buf ))))
        }
        o->modified = true;
    }
    
    if( p_modified ) (*(p_modified)) = o->modified;
    
    BLM_RETURNV(er_t, 0)
}

er_t xoico_target_s_expand_phase2( xoico_target_s* o, bl_t* p_modified )
{
    // xoico_target.x:373:28
    BLM_INIT_LEVEL(0);
    if( !o->modified )
    {
        if( (p_modified) ) (*(p_modified)) = false;
        BLM_RETURNV(er_t, 0)
    }
    
    ASSERT( o->target_h );
    ASSERT( o->target_c );
    
    st_s* file_h = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create_fa("#<sc_t>.h", o->path.sc )));
    st_s* file_c = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create_fa("#<sc_t>.c", o->path.sc )));
    
    if( o->readonly )
    {
        bcore_msg_fa( "Affected: #<sc_t>\n", file_h->sc );
        bcore_msg_fa( "Affected: #<sc_t>\n", file_c->sc );
        if( (p_modified) ) (*(p_modified)) = false;
    }
    else
    {
        BLM_TRY(xoico_compiler_s_check_overwrite(o->compiler,file_h->sc ))
        BLM_TRY(xoico_compiler_s_check_overwrite(o->compiler,file_c->sc ))
        bcore_msg_fa( "Writing: #<sc_t>\n", file_h->sc );
        BLM_TRY(xoico_target_write_with_signature(file_h->sc, o->target_h ))
        bcore_msg_fa( "Writing: #<sc_t>\n", file_c->sc );
        BLM_TRY(xoico_target_write_with_signature(file_c->sc, o->target_c ))
        if( (p_modified) ) (*(p_modified)) = true;
    }
    BLM_RETURNV(er_t, 0)
}

XOILA_DEFINE_SPECT( xoico, xoico_target )
"{"
    "bcore_spect_header_s header;"
"}";

er_t xoico_target_write_with_signature( sc_t file, const st_s* data )
{
    // xoico_target.x:361:67
    BLM_INIT_LEVEL(0);
    tp_t hash = bcore_tp_fold_sc( bcore_tp_init(), data->sc );
    bcore_sink* sink = ((bcore_sink*)BLM_LEVEL_A_PUSH(0,bcore_file_open_sink(file )));
    bcore_sink_a_push_data(sink,( vc_t )data->data, data->size );
    bcore_sink_a_push_fa(sink,"// XOILA_OUT_SIGNATURE 0x#pl16'0'{#X<tp_t>}ull\n", hash );
    BLM_RETURNV(er_t, 0)
}

/**********************************************************************************************************************/
// source: xoico_compiler.h
#include "xoico_compiler.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_compiler; embeds: xoico_compiler.x

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
    "hidden xoico_func_s* func;"
"}";

BCORE_DEFINE_OBJECT_INST_P( xoico_compiler_s )
"aware xoico_compiler"
"{"
    "hidden xoico_target_s => [];"
    "hidden bcore_life_s life;"
    "hidden bcore_hmap_tpvd_s hmap_group;"
    "hidden bcore_hmap_tpvd_s hmap_item;"
    "hidden bcore_hmap_tpvd_s hmap_func;"
    "hidden bcore_hmap_tp_s hmap_external_type;"
    "hidden bcore_hmap_name_s name_map;"
    "tp_t target_pre_hash = 71;"
    "bl_t work_build_time_into_pre_hash = true;"
    "bl_t register_signatures = false;"
    "bl_t overwrite_unsigned_target_files = false;"
    "bl_t always_expand = false;"
    "bl_t dry_run = false;"
    "sz_t verbosity = 1;"
    "func bcore_inst_call:init_x;"
    "func xoico:finalize;"
    "func xoico:expand_setup;"
"}";

bl_t xoico_compiler_s_is_type( const xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:128:5
    
    if( xoico_compiler_s_is_group(o,name ) ) return  true;
    if( xoico_compiler_s_is_stamp(o,name ) ) return  true;
    if( bcore_hmap_tp_s_exists(&(o->hmap_external_type),name ) ) return  true;
    return  false;
}

bl_t xoico_compiler_s_is_stamp( const xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:136:5
    
    const xoico* item = xoico_compiler_s_get_const_item(o,name );
    if( item && ( item->_ == TYPEOF_xoico_stamp_s ) ) return  true;
    return  false;
}

bl_t xoico_compiler_s_is_body( const xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:143:5
    
    const xoico* item = xoico_compiler_s_get_const_item(o,name );
    if( item && ( item->_ == TYPEOF_xoico_body_s ) ) return  true;
    return  false;
}

bl_t xoico_compiler_s_is_signature( const xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:150:5
    
    const xoico* item = xoico_compiler_s_get_const_item(o,name );
    if( item && ( item->_ == TYPEOF_xoico_signature_s ) ) return  true;
    return  false;
}

bl_t xoico_compiler_s_is_signature_or_feature( const xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:157:5
    
    const xoico* item = xoico_compiler_s_get_const_item(o,name );
    if( !item ) return  NULL;
    if( item->_ == TYPEOF_xoico_signature_s || item->_ == TYPEOF_xoico_feature_s ) return  true;
    return  false;
}

bl_t xoico_compiler_s_is_feature( const xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:165:5
    
    const xoico* item = xoico_compiler_s_get_const_item(o,name );
    if( item && ( item->_ == TYPEOF_xoico_feature_s ) ) return  true;
    return  false;
}

const xoico* xoico_compiler_s_get_const_item( const xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:172:5
    
    vd_t* ptr = bcore_hmap_tpvd_s_get(&(o->hmap_item),name );
    return  ptr ? ( const xoico* )*ptr : NULL;
}

xoico* xoico_compiler_s_get_item( xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:178:5
    
    vd_t* ptr = bcore_hmap_tpvd_s_get(&(o->hmap_item),name );
    return  ptr ? ( xoico* )*ptr : NULL;
}

xoico_stamp_s* xoico_compiler_s_get_stamp( xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:184:5
    
    const xoico* item = xoico_compiler_s_get_const_item(o,name );
    return  ( item ) ? ( item->_ == TYPEOF_xoico_stamp_s ) ? ((xoico_stamp_s*)(item)) : NULL : NULL;
}

xoico_body_s* xoico_compiler_s_get_body( xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:190:5
    
    const xoico* item = xoico_compiler_s_get_const_item(o,name );
    return  ( item ) ? ( item->_ == TYPEOF_xoico_body_s ) ? ((xoico_body_s*)(item)) : NULL : NULL;
}

const xoico_feature_s* xoico_compiler_s_get_feature( const xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:196:5
    
    const xoico* item = xoico_compiler_s_get_const_item(o,name );
    return  ( item ) ? ( item->_ == TYPEOF_xoico_feature_s ) ? ((xoico_feature_s*)(item)) : NULL : NULL;
}

const xoico_signature_s* xoico_compiler_s_get_signature( const xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:202:5
    
    const xoico* item = xoico_compiler_s_get_const_item(o,name );
    if( !item ) return  NULL;
    if( item->_ == TYPEOF_xoico_signature_s ) return  ((xoico_signature_s*)(item));
    if( item->_ == TYPEOF_xoico_feature_s   ) return &( ((xoico_feature_s*)(item))->signature);
    return  NULL;
}

xoico_group_s* xoico_compiler_s_get_group( xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:211:5
    
    vd_t* ptr = bcore_hmap_tpvd_s_get(&(o->hmap_group),name );
    return  ptr ? ( xoico_group_s* )*ptr : NULL;
}

xoico_transient_map_s* xoico_compiler_s_get_transient_map( xoico_compiler_s* o, tp_t type )
{
    // xoico_compiler.h:217:5
    
    xoico_stamp_s* stamp = xoico_compiler_s_get_stamp(o,type );
    return  stamp ? (&(stamp->transient_map)) : NULL;
}

xoico_func_s* xoico_compiler_s_get_func( xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:223:5
    
    vd_t* ptr = bcore_hmap_tpvd_s_get(&(o->hmap_func),name );
    return  ptr ? ( xoico_func_s* )*ptr : NULL;
}

er_t xoico_compiler_s_life_a_push( xoico_compiler_s* o, bcore_inst* object )
{
    // xoico_compiler.h:229:5
    
    bcore_life_s_push_aware( (&(o->life)), object );
    return  0;
}

void xoico_compiler_s_init_x( xoico_compiler_s* o )
{
    // xoico_compiler.h:250:5
    
    if( o->work_build_time_into_pre_hash )
    {
        o->target_pre_hash = bcore_tp_fold_sc( o->target_pre_hash, __DATE__ );
        o->target_pre_hash = bcore_tp_fold_sc( o->target_pre_hash, __TIME__ );
    }
}

void xoico_compiler_s_push_d( xoico_compiler_s* o, xoico_target_s* target )
{
    // xoico_compiler.h:259:5
    
    bcore_array_a_push( ((bcore_array*)(o)),sr_asd( target ) );
}

er_t xoico_compiler_s_register_group( xoico_compiler_s* o, const xoico_group_s* group )
{
    // xoico_compiler.x:21:1
    
    if( bcore_hmap_tpvd_s_exists(&(o->hmap_group),group->tp_name ) )
    {
        return  bcore_source_point_s_parse_error_fa
        (&(
            group->source_point),"'#<sc_t>' was already registered\n",
            xoico_compiler_s_nameof(o,group->tp_name )
        );
    }
    bcore_hmap_tpvd_s_set(&(o->hmap_group),group->tp_name, ( vd_t )group );
    return  0;
}

er_t xoico_compiler_s_register_item( xoico_compiler_s* o, const xoico* item, bcore_source* source )
{
    // xoico_compiler.x:38:1
    
    tp_t global_id = xoico_a_get_global_name_tp(item);
    if( bcore_hmap_tpvd_s_exists(&(o->hmap_item),global_id ) )
    {
        return  bcore_source_a_parse_error_fa(source,"'#<sc_t>' was already registered\n", xoico_compiler_s_nameof(o,global_id ) );
    }
    bcore_hmap_tpvd_s_set(&(o->hmap_item),global_id, ( vd_t )item );
    return  0;
}

er_t xoico_compiler_s_register_func( xoico_compiler_s* o, const xoico_func_s* func )
{
    // xoico_compiler.x:51:1
    
    if( bcore_hmap_tpvd_s_exists(&(o->hmap_func),func->global_name ) )
    {
        xoico_func_s* func_registered =*( ((xoico_func_s**)(bcore_hmap_tpvd_s_get(&(o->hmap_func),func->global_name ))));
    
        if( func_registered == func )
        {
            return  bcore_source_point_s_parse_error_fa
            (&(
                func->source_point),"Global func name '#<sc_t>' was already registered from same instance.\n",
                xoico_compiler_s_nameof(o,func->global_name )
            );
        }
        else
        {
            return  bcore_source_point_s_parse_error_fa
            (&(
                func->source_point),"Global func name '#<sc_t>' was already registered from different instance.\n"
                "'#<sc_t>' vs '#<sc_t>'\n",
                xoico_compiler_s_nameof(o,func->global_name ),
                xoico_compiler_s_nameof(o,func->name ),
                xoico_compiler_s_nameof(o,func_registered->name )
            );
        }
    }
    
    bcore_hmap_tpvd_s_set(&(o->hmap_func),func->global_name, ( vd_t )func );
    return  0;
}

er_t xoico_compiler_s_check_overwrite( const xoico_compiler_s* o, sc_t file )
{
    // xoico_compiler.x:113:1
    
    if( !bcore_file_exists(file ) ) return  0;
    
    if( !xoico_compiler_is_signed(file ) )
    {BLM_INIT_LEVEL(1);
        st_s* s = ((st_s*)BLM_LEVEL_T_PUSH(1,st_s,st_s_create()));
        st_s_push_fa(s,"Planted file #<sc_t>: Signature check failed.\n", file );
        st_s_push_fa(s,"This file might have been created or edited outside the xoico framework.\n" );
        if( o->overwrite_unsigned_target_files )
        {
            st_s_push_fa(s,"Flag 'overwrite_unsigned_target_files' is 'true'. The file will be overwritten.\n" );
            bcore_sink_a_push_fa( BCORE_STDERR,"\nWARNING: #<sc_t>\n", s->sc );
        }
        else
        {
            st_s_push_fa(s,"Xoico has currently no permission to overwrite unsigned target files.\n" );
            st_s_push_fa(s,"You can fix it in one of following ways:\n" );
            st_s_push_fa(s,"* Rename or (re)move the file.\n" );
            st_s_push_fa(s,"* Use command line flag '-f'.\n" );
            BLM_RETURNV(er_t, bcore_error_push_fa( TYPEOF_general_error, "\nERROR: #<sc_t>\n", s->sc ))
        }
    BLM_DOWN();}
    
    return  0;
}

er_t xoico_compiler_s_parse( xoico_compiler_s* o, sc_t target_name, sc_t target_ext, sc_t source_path, sz_t* p_target_index )
{
    // xoico_compiler.x:141:20
    BLM_INIT_LEVEL(0);
    st_s* source_folder_path = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,bcore_file_folder_path(source_path )));
    st_s* target_path        = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create_fa("#<sc_t>/#<sc_t>.#<sc_t>", source_folder_path->sc, target_name, target_ext )));
    
    sz_t target_index = -1;
    for( sz_t i = 0; i < o->size; i++ )
    {
        if( st_s_equal_st(target_path,&(o->data[ i ]->path )) )
        {
            target_index = i;
            break;
        }
    }
    
    if( target_index == -1 )
    {
        xoico_target_s* target = xoico_target_s_create();
        target->compiler = o;
        st_s_copy_fa(&(target->name        ),"#<sc_t>_#<sc_t>", target_name, target_ext );
        st_s_copy_fa(&(target->include_path),"#<sc_t>.#<sc_t>", target_name, target_ext );
        st_s_copy(&(target->path),target_path );
        xoico_compiler_s_push_d(o,target );
        target_index = o->size - 1;
    }
    
    xoico_target_s* target = o->data[ target_index ];
    BLM_TRY(xoico_target_s_parse_from_path(target,source_path ))
    if( p_target_index ) (*(p_target_index)) = target_index;
    
    BLM_RETURNV(er_t, 0)
}

er_t xoico_compiler_s_finalize( xoico_compiler_s* o, const xoico_host* host )
{
    // xoico_compiler.x:176:27
    
    {const xoico_compiler_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_target_s* e=__a->data[__i]; BLM_TRY(xoico_target_s_finalize(e,((const xoico_host*)(o ))))
    }}return  0;
}

er_t xoico_compiler_s_expand_setup( xoico_compiler_s* o, const xoico_host* host )
{
    // xoico_compiler.x:184:31
    
    for( sz_t i = 0; i < o->size; i++ ) BLM_TRY(xoico_target_s_expand_setup(o->data[ i ],((const xoico_host*)(o ))))
    
    /* We obtain all names from the global map.
     * This is necessary because names of reflection elements are parsed outside
     * this framework and remembered by the global map.
     */
    bcore_name_push_all( (&(o->name_map)) );
    
    return  0;
}

bl_t xoico_compiler_s_to_be_modified( const xoico_compiler_s* o )
{
    // xoico_compiler.x:201:1
    
    for( sz_t i = 0; i < o->size; i++ )
    {
        if( xoico_target_s_to_be_modified(o->data[ i ]) ) return  true;
    }
    return  false;
}

er_t xoico_compiler_s_expand( xoico_compiler_s* o, bl_t* p_modified )
{
    // xoico_compiler.x:212:55
    
    bl_t modified = false;
    
    BLM_TRY(xoico_compiler_s_expand_setup(o,((const xoico_host*)(o ))))
    for( sz_t i = 0; i < o->size; i++ ) BLM_TRY(xoico_target_s_expand_phase1(o->data[i],(&(modified)) ))
    for( sz_t i = 0; i < o->size; i++ ) BLM_TRY(xoico_target_s_expand_phase2(o->data[i],(&(modified)) ))
    
    if( p_modified ) (*(p_modified)) = modified;
    return  0;
}

bl_t xoico_compiler_s_get_self( const xoico_compiler_s* o, tp_t type, const bcore_self_s** self )
{
    // xoico_compiler.x:227:1
    
    const xoico* item = xoico_compiler_s_get_const_item(o,type );
    if( !item ) return  false;
    
    if( item->_ == TYPEOF_xoico_stamp_s )
    {
        const xoico_stamp_s* stamp = ((const xoico_stamp_s*)(item));
        if( self ) (*(self)) = stamp->self;
        return  true;
    }
    
    return  false;
}

bl_t xoico_compiler_s_get_type_info( const xoico_compiler_s* o, tp_t type, xoico_compiler_type_info_s* info )
{
    // xoico_compiler.x:244:1
    
    const xoico* item = xoico_compiler_s_get_const_item(o,type );
    if( !item ) return  false;
    ASSERT( info );
    if( item->_ == TYPEOF_xoico_stamp_s || item->_ == TYPEOF_xoico_group_s )
    {
        info->item = ((xoico*)(item));
        info->typespec.type = type;
        return  true;
    }
    
    return  false;
}

bl_t xoico_compiler_s_get_type_element_info( const xoico_compiler_s* o, tp_t type, tp_t name, xoico_compiler_element_info_s* info )
{
    // xoico_compiler.x:261:1
    
    const xoico* xoico_item = xoico_compiler_s_get_const_item(o,type );
    if( !xoico_item )
    {
        xoico_item = ((const xoico*)(xoico_compiler_s_get_group(((xoico_compiler_s*)(o)),type )));
        if( !xoico_item ) return  false;
    }
    
    bl_t success = false;
    ASSERT( info );
    info->type_info.item = ((xoico*)(xoico_item));
    
    if( xoico_item->_ == TYPEOF_xoico_stamp_s )
    {
        const xoico_stamp_s* stamp = ((const xoico_stamp_s*)(xoico_item));
        const bcore_self_s* self = stamp->self;
        const bcore_self_item_s* self_item = bcore_self_s_get_item_by_name( self,name ); // returns NULL in case of no match
    
        bl_t found = true;
        sz_t indirection = 0;
    
        if( self_item )
        {
            switch( self_item->caps )
            {
                case BCORE_CAPS_SOLID_STATIC: indirection = 0; break;
                case BCORE_CAPS_LINK_STATIC:  indirection = 1; break;
                case BCORE_CAPS_LINK_TYPED:   indirection = 1; break;
                case BCORE_CAPS_LINK_AWARE:   indirection = 1; break;
                case BCORE_CAPS_POINTER:      indirection = 1; break;
                case BCORE_CAPS_ARRAY_DYN_SOLID_STATIC:
                case BCORE_CAPS_ARRAY_DYN_SOLID_TYPED:
                case BCORE_CAPS_ARRAY_DYN_LINK_STATIC:
                case BCORE_CAPS_ARRAY_DYN_LINK_TYPED:
                case BCORE_CAPS_ARRAY_DYN_LINK_AWARE:
                case BCORE_CAPS_ARRAY_FIX_SOLID_STATIC:
                case BCORE_CAPS_ARRAY_FIX_LINK_STATIC:
                case BCORE_CAPS_ARRAY_FIX_LINK_AWARE:
                {
                    /// arrays are handled separately
                    return  false;
                }
                break;
    
                default:
                {
                    found = false;
                }
                break;
            }
        }
        else
        {
            found = false;
        }
    
        info->type_info.typespec.flag_const = false;
    
        if( found )
        {
            info->type_info.typespec.type = self_item->type;
            info->type_info.typespec.indirection = indirection;
            success = true;
        }
        else
        {
            info->func = ((xoico_func_s*)(xoico_stamp_s_get_trait_line_func_from_name(stamp,name )));
            if( info->func ) success = true;
        }
    }
    else if( xoico_item->_ == TYPEOF_xoico_group_s )
    {
        info->func = ((xoico_func_s*)(xoico_group_s_get_trait_line_func_from_name(((xoico_group_s*)(xoico_item)),name )));
        if( info->func ) success = true;
    }
    
    return  success;
}

bl_t xoico_compiler_s_get_type_array_element_info( const xoico_compiler_s* o, tp_t type, xoico_compiler_element_info_s* info )
{
    // xoico_compiler.x:343:1
    
    ASSERT( info );
    
    const xoico* xoico_item = xoico_compiler_s_get_const_item(o,type );
    if( !xoico_item ) return  false;
    bl_t success = false;
    info->type_info.item = ((xoico*)(xoico_item));
    tp_t tp_no_name = btypeof( "" );
    
    if( xoico_item->_ == TYPEOF_xoico_stamp_s )
    {
        const xoico_stamp_s* stamp = ((const xoico_stamp_s*)(xoico_item));
        const bcore_self_s* self = stamp->self;
    
        sz_t items = bcore_self_s_items_size( self);
        const bcore_self_item_s* self_item = NULL;
        for( sz_t i = 0; i < items; i++ )
        {
            const bcore_self_item_s* item = bcore_self_s_get_item( self,i );
            if( item->name == tp_no_name && bcore_flect_caps_is_array( item->caps ) )
            {
                self_item = item;
                break;
            }
        }
    
        if( self_item )
        {
            sz_t indirection = 0;
            switch( self_item->caps )
            {
                case BCORE_CAPS_ARRAY_DYN_SOLID_STATIC: indirection = 0; break;
                case BCORE_CAPS_ARRAY_DYN_SOLID_TYPED:  indirection = 0; break;
                case BCORE_CAPS_ARRAY_DYN_LINK_STATIC:  indirection = 1; break;
                case BCORE_CAPS_ARRAY_DYN_LINK_TYPED:   indirection = 1; break;
                case BCORE_CAPS_ARRAY_DYN_LINK_AWARE:   indirection = 1; break;
                case BCORE_CAPS_ARRAY_FIX_SOLID_STATIC: indirection = 0; break;
                case BCORE_CAPS_ARRAY_FIX_LINK_STATIC:  indirection = 1; break;
                case BCORE_CAPS_ARRAY_FIX_LINK_AWARE:   indirection = 1; break;
    
                default:
                {
                    ERR_fa( "Invalid array caps" );
                }
                break;
            }
    
            info->type_info.typespec.type = self_item->type;
            info->type_info.typespec.indirection = indirection;
            success = true;
        }
    }
    
    return  success;
}

er_t xoico_compiler_s_update_target_files( xoico_compiler_s* o, bl_t* p_modified )
{
    // xoico_compiler.x:407:1
    
    bl_t modified = false;
    bl_t verbosity = o->verbosity;
    f3_t time = 0;
    
    er_t er = 0;
    ABS_TIME_OF( er = xoico_compiler_s_expand(o,(&(modified)) ), time );
    BLM_TRY(er )
    
    if( modified )
    {
        if( verbosity > 0 ) bcore_msg_fa( "XOICO: Expanded in #<f3_t> sec.\n", time );
        if( verbosity > 0 ) bcore_msg_fa( "XOICO: Files were updated. Rebuild is necessary.\n" );
    }
    
    if( p_modified ) (*(p_modified)) = modified;
    
    return  er;
}

XOILA_DEFINE_SPECT( xoico, xoico_compiler )
"{"
    "bcore_spect_header_s header;"
"}";

bl_t xoico_compiler_is_signed( sc_t file )
{
    // xoico_compiler.x:87:1
    BLM_INIT_LEVEL(0);
    bcore_source* source = ((bcore_source*)BLM_LEVEL_A_PUSH(0,bcore_file_open_source(file )));
    st_s* data = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    while( !bcore_source_a_eos(source) ) st_s_push_char(data,bcore_source_a_get_u0(source) );
    
    if( data->size < bcore_strlen( "// XOILA_OUT_SIGNATURE" ) ) BLM_RETURNV(bl_t, false)
    
    sz_t idx = data->size - 1;
    while( idx >= 0 && data->data[ idx ] != '/' ) idx--;
    if( idx > 0 ) idx--;
    
    if( st_s_find_sc(data,idx, -1, "// XOILA_OUT_SIGNATURE" ) != idx ) BLM_RETURNV(bl_t, false)
    
    tp_t hash = 0;
    st_s_parse_fa( data,idx, -1, "// XOILA_OUT_SIGNATURE #<tp_t*>", (&(hash)) );
    
    data->data[ idx ] = 0;
    
    if( hash != bcore_tp_fold_sc( bcore_tp_init(), data->sc ) ) BLM_RETURNV(bl_t, false)
    
    BLM_RETURNV(bl_t, true)
}

/**********************************************************************************************************************/
// source: xoico_builder.h
#include "xoico_builder.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_builder; embeds: xoico_builder.x

BCORE_DEFINE_OBJECT_INST_P( xoico_builder_arr_target_s )
"aware x_array"
"{"
    "xoico_builder_target_s => [];"
"}";

BCORE_DEFINE_OBJECT_INST_P( xoico_builder_target_s )
"aware xoico_builder"
"{"
    "st_s => name;"
    "st_s => extension = \"xo\";"
    "st_s => root_folder;"
    "bl_t readonly;"
    "bcore_arr_st_s dependencies;"
    "bcore_arr_st_s sources;"
    "st_s => signal_handler;"
    "aware xoico_cengine => cengine = xoico_che_s;"
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
        o->root_folder = bcore_file_folder_path(bcore_source_a_get_file( source ) );
        st_s_attach( &(o->root_folder ),  bcore_file_path_minimized(o->root_folder->sc ));
    }
}

const xoico_builder_target_s* xoico_builder_target_s_name_match( const xoico_builder_target_s* o, sc_t name )
{
    // xoico_builder.h:78:5
    
    if( o->name && sc_t_equal( name, o->name->sc ) ) return  o;
    if( o->parent_ ) return  xoico_builder_target_s_name_match(o->parent_,name );
    return  NULL;
}

void xoico_builder_target_s_push_target_index_to_arr( const xoico_builder_target_s* o, bcore_arr_sz_s* arr )
{
    // xoico_builder.h:85:5
    
    if( o->target_index_ != -1 )
    {
         bcore_arr_sz_s_push(arr,o->target_index_ );
    }
    else
    {
        {const xoico_builder_arr_target_s* __a=o->dependencies_target_ ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_builder_target_s* e=__a->data[__i]; xoico_builder_target_s_push_target_index_to_arr(e,arr );}}
    }
}

er_t xoico_builder_target_s_load( xoico_builder_target_s* o, bl_t readonly, sc_t path )
{
    // xoico_builder.x:20:25
    BLM_INIT_LEVEL(0);
    st_s* st_path = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    st_s_copy_sc(st_path,path );
    
    if( st_path->sc[ 0 ] != '/' )
    {
        st_s* current_folder = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
        bcore_folder_get_current( current_folder );
        st_path = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create_fa("#<sc_t>/#<sc_t>", current_folder->sc, st_path->sc )));
    }
    
    st_path = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,bcore_file_path_minimized(st_path->sc )));
    
    bcore_txt_ml_a_from_file( o, st_path->sc );
    st_s_copy(&(o->full_path_),st_path );
    if( readonly ) o->readonly = true;
    
    if( !o->name ) BLM_RETURNV(er_t, bcore_error_push_fa( TYPEOF_general_error, "In target file: '#<sc_t>'\nTarget name must be specified.", st_path->sc ))
    
    /// check for dependency cycles
    if( o->parent_ )
    {
        const xoico_builder_target_s* match = xoico_builder_target_s_name_match(o->parent_,o->name->sc );
        if( match )
        {
            if( st_s_equal_st(&(match->full_path_),&(o->full_path_ )) )
            {
                BLM_RETURNV(er_t, bcore_error_push_fa( TYPEOF_general_error, "In target file: '#<sc_t>'\nCyclic dependency detected.", st_path->sc ))
            }
            else
            {
                BLM_RETURNV(er_t, bcore_error_push_fa( TYPEOF_general_error, "Same target name '#<sc_t>' used in different target files:\n#<sc_t>\n#<sc_t>", o->name->sc, st_path->sc, match->full_path_.sc ))
            }
        }
    }
    
    {const bcore_arr_st_s* __a=&(o->dependencies );if(__a)for(sz_t __i=0; __i<__a->size; __i++){st_s* e=__a->data[__i];
    {BLM_INIT_LEVEL(3);
        if( !o->dependencies_target_ ) o->dependencies_target_ = xoico_builder_arr_target_s_create();
    
        st_s* file_path = ((st_s*)BLM_LEVEL_T_PUSH(3,st_s,st_s_create()));
        if( e->sc[ 0 ] != '/' )
        {
            if( o->root_folder ) st_s_push_fa(file_path,"#<sc_t>/", o->root_folder->sc );
        }
    
        bl_t dep_readonly = o->readonly;
    
        bcore_source* source =((bcore_source*)( ((bcore_source_string_s*)BLM_LEVEL_T_PUSH(3,bcore_source_string_s,bcore_source_string_s_create_sc(e->sc )))));
        BLM_TRY(bcore_source_a_parse_em_fa(source," #:until':'", file_path ))
    
        /// remove trailing spaces
        while( file_path->sc[ 0 ] == ' ' || file_path->sc[ 0 ] == '\t' ) st_s_pop_char(file_path);
    
        if( bcore_source_a_parse_bl( source,"#?':'" ) )
        {
            if( bcore_source_a_parse_bl(source," #?w'readonly'" ) )
            {
                dep_readonly = true;
            }
            else
            {
                BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Syntax error in dependency declaration." ))
            }
        }
    
        xoico_builder_target_s* target = ((xoico_builder_target_s*)(x_array_push_d(((x_array*)(o->dependencies_target_)),((x_inst*)(xoico_builder_target_s_create() )))));
        target->parent_ = o;
    
        BLM_TRY(xoico_builder_target_s_load(target,dep_readonly, file_path->sc ))
    BLM_DOWN();}
    
    }}BLM_RETURNV(er_t, 0)
}

er_t xoico_builder_target_s_build( xoico_builder_target_s* o )
{
    // xoico_builder.x:98:26
    BLM_INIT_LEVEL(0);
    if( !o->root_    ) o->root_    = ( o->parent_ ) ? o->parent_->root_    : o;
    if( !o->compiler ) o->compiler = ( o->parent_ ) ? o->parent_->compiler : NULL;
    
    if( o == o->root_ )
    {
        if( !o->hmap_built_target_ ) o->hmap_built_target_ = bcore_hmap_tpvd_s_create();
    }
    
    ASSERT( o->compiler );
    ASSERT( o->root_ );
    
    tp_t tp_target_name = bentypeof( o->name->sc );
    
    {const xoico_builder_arr_target_s* __a=o->dependencies_target_ ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_builder_target_s* e=__a->data[__i]; BLM_TRY(xoico_builder_target_s_build(e))
    
    }}if( bcore_hmap_tpvd_s_exists(o->root_->hmap_built_target_,tp_target_name ) )
    {
        xoico_builder_target_s* target = (*(((xoico_builder_target_s**)(bcore_hmap_tpvd_s_get(o->root_->hmap_built_target_,tp_target_name )))));
        o->target_index_ = target->target_index_;
        BLM_RETURNV(er_t, 0)
    }
    
    bcore_hmap_tpvd_s_set(o->root_->hmap_built_target_,tp_target_name, ( vd_t )o );
    
    o->target_index_ = -1;
    
    bcore_msg_fa( "XOICO: compiling #<sc_t>\n", o->full_path_.sc );
    
    {const bcore_arr_st_s* __a=&(o->sources );if(__a)for(sz_t __i=0; __i<__a->size; __i++){st_s* e=__a->data[__i];
    {BLM_INIT_LEVEL(3);
        st_s* file_path = ((st_s*)BLM_LEVEL_T_PUSH(3,st_s,st_s_create()));
        if( e->sc[ 0 ] != '/' )
        {
            if( o->root_folder ) st_s_push_fa(file_path,"#<sc_t>/", o->root_folder->sc );
        }
        st_s_push_fa(file_path,"#<sc_t>", e->sc );
    
        ASSERT( o->name );
        ASSERT( o->extension );
        sz_t index = -1;
    
        BLM_TRY(xoico_compiler_s_parse(o->compiler,o->name->sc, o->extension->sc, file_path->sc,&( index )))
    
        if( o->target_index_ == -1 ) o->target_index_ = index;
        if( index != o->target_index_ )
        {
            BLM_RETURNV(er_t, bcore_error_push_fa
            (
                TYPEOF_general_error,
                "Building source '#<sc_t>' in target '#<sc_t>':\n"
                "Target index mismatch.\n"
                "This problem occurs when a target defines sources from different directories.\n",
                e->sc,
                o->name->sc
            ))
        }
    BLM_DOWN();}
    
    }}if( o->target_index_ >= 0 )
    {
        ASSERT( o->target_index_ < o->compiler->size );
        bcore_arr_sz_s* dependencies = ((bcore_arr_sz_s*)BLM_LEVEL_T_PUSH(0,bcore_arr_sz_s,bcore_arr_sz_s_create()));
        {const xoico_builder_arr_target_s* __a=o->dependencies_target_ ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_builder_target_s* e=__a->data[__i]; xoico_builder_target_s_push_target_index_to_arr(e,dependencies );}}
    
        xoico_target_s* target = o->compiler->data[ o->target_index_ ];
    
        BLM_TRY(xoico_target_s_set_dependencies(target,dependencies ))
        st_s* signal_handler = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create_fa("#<sc_t>_general_signal_handler", o->name->sc )));
        if( o->signal_handler ) st_s_copy(signal_handler,o->signal_handler );
        st_s_copy_sc(&(target->signal_handler_name),signal_handler->sc );
        target->readonly = o->readonly;
        xoico_cengine_a_attach( &(target->cengine ), (xoico_cengine*)( ((xoico_cengine*)bcore_fork(o->cengine))));
    }
    
    BLM_RETURNV(er_t, 0)
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

er_t xoico_builder_main_s_build_from_file( xoico_builder_main_s* o, sc_t path )
{
    // xoico_builder.x:183:34
    
    xoico_builder_target_s_attach( &(o->target ),  xoico_builder_target_s_create());
    BLM_TRY(xoico_builder_target_s_load(o->target,false, path ))
    o->target->compiler = o->compiler;
    BLM_TRY(xoico_builder_target_s_build(o->target))
    BLM_TRY(xoico_compiler_s_finalize(o->compiler,((const xoico_host*)(o ))))
    return  0;
}

er_t xoico_builder_main_s_update( const xoico_builder_main_s* o )
{
    // xoico_builder.x:196:1
    
    if( bcore_error_stack_size() > 0 ) return  TYPEOF_error_stack;
    BLM_TRY(xoico_compiler_s_update_target_files(o->compiler,NULL ) )
    return  0;
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
// source: xoico_che.h
#include "xoico_che.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_che; embeds: xoico_che.x xoico_che_builtin.x xoico_che_control.x

BCORE_DEFINE_OBJECT_INST_P( xoico_che_s )
"aware xoico_che"
"{"
    "bl_t verbose = false;"
    "bl_t insert_source_reference = true;"
    "hidden xoico_host* host;"
    "hidden xoico_compiler_s* compiler;"
    "xoico_typespec_s typespec_ret;"
    "tp_t member_obj_type;"
    "sz_t level;"
    "sz_t try_block_level;"
    "xoico_che_stack_var_s stack_var;"
    "xoico_che_stack_block_s stack_block;"
    "bcore_hmap_name_s hmap_name;"
    "func xoico_cengine:is_reserved;"
    "func xoico_cengine:translate;"
"}";

bl_t xoico_che_s_is_reserved( const xoico_che_s* o, tp_t tp_identifier )
{
    // xoico_che.h:374:5
    
    return  xoico_che_s_is_builtin_func(o,tp_identifier ) ||
           xoico_che_s_is_control_name(o,tp_identifier ) ||
           tp_identifier == TYPEOF_verbatim_C;
}

sc_t xoico_che_s_nameof( xoico_che_s* o, tp_t type )
{
    // xoico_che.h:383:5
    
    sc_t name = bcore_hmap_name_s_get_sc(&(o->hmap_name),type );
    if( !name ) name = xoico_compiler_s_nameof(o->compiler,type );
    return  name;
}

void xoico_che_s_init_level0( xoico_che_s* o )
{
    // xoico_che.h:390:5
    
    xoico_che_stack_block_s_clear(&(o->stack_block));
    xoico_che_stack_block_s_push(&(o->stack_block));
    o->level = 0;
}

void xoico_che_s_inc_block( xoico_che_s* o )
{
    // xoico_che.h:397:5
    
    xoico_che_stack_block_s_push(&(o->stack_block));
    o->level++;
    xoico_che_s_stack_block_get_top_unit(o)->level = o->level;
}

void xoico_che_s_dec_block( xoico_che_s* o )
{
    // xoico_che.h:404:5
    
    xoico_che_stack_var_s_pop_level(&(o->stack_var),o->level );
    o->level--;
    ASSERT( o->level >= 0 );
    xoico_che_stack_block_s_pop(&(o->stack_block));
}

xoico_che_stack_block_unit_s* xoico_che_s_stack_block_get_top_unit( xoico_che_s* o )
{
    // xoico_che.h:412:5
    
    return  o->stack_block.adl.data[ o->stack_block.adl.size - 1 ];
}

xoico_che_stack_block_unit_s* xoico_che_s_stack_block_get_bottom_unit( xoico_che_s* o )
{
    // xoico_che.h:417:5
    
    return  o->stack_block.adl.data[ 0 ];
}

xoico_che_stack_block_unit_s* xoico_che_s_stack_block_get_level_unit( xoico_che_s* o, sz_t level )
{
    // xoico_che.h:422:5
    
    {const xoico_che_stack_block_unit_adl_s* __a=&(o->stack_block.adl );if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_che_stack_block_unit_s* e=__a->data[__i]; if( e->level == level ) return  e;
    }}ERR_fa( "Level #<sz_t> not found.", level );
    return  NULL;
}

void xoico_che_s_push_typedecl( xoico_che_s* o, const xoico_typespec_s* typespec, tp_t name )
{
    // xoico_che.h:429:5
    BLM_INIT_LEVEL(0);
    xoico_che_stack_var_unit_s* unit = ((xoico_che_stack_var_unit_s*)BLM_LEVEL_T_PUSH(0,xoico_che_stack_var_unit_s,xoico_che_stack_var_unit_s_create()));
    unit->level = o->level;
    unit->name = name;
    xoico_typespec_s_copy(&(unit->typespec),typespec );
    xoico_che_stack_var_s_push_unit(&(o->stack_var),unit );
    BLM_DOWN();
}

void xoico_che_s_typespec_to_sink( xoico_che_s* o, const xoico_typespec_s* typespec, bcore_sink* sink )
{
    // xoico_che.h:439:5
    BLM_INIT_LEVEL(0);
    xoico_che_result* result = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
    xoico_che_s_push_typespec(o,typespec, result );
    bcore_sink_a_push_sc(sink,((st_s*)BLM_LEVEL_T_PUSH(0,st_s,xoico_che_result_a_create_st(result)))->sc );
    BLM_DOWN();
}

bl_t xoico_che_s_returns_a_value( const xoico_che_s* o )
{
    // xoico_che.h:457:5
    
    return  ( !( ( o->typespec_ret.type == 0 ) || ( o->typespec_ret.type == TYPEOF_void ) ) ) || ( o->typespec_ret.indirection > 0 );
}

er_t xoico_che_s_trans( const xoico_che_s* o, bcore_source* source, sc_t format, xoico_che_result* result )
{
    // xoico_che.h:462:5
    
    BLM_TRY(bcore_source_a_parse_em_fa(source,format ))
    xoico_che_result_a_push_sc(result,format );
    return  0;
}

tp_t xoico_che_s_get_identifier( xoico_che_s* o, bcore_source* source, bl_t take_from_source )
{
    // xoico_che.x:26:1
    BLM_INIT_LEVEL(0);
    tp_t tp_identifier = 0;
    if( bcore_source_a_parse_bl(source,"#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||[0]=='_'||[0]=='@'||[0]=='$'||([0]==':'&&([1]!=' '&&[1]!='\t'&&[1]!='\n'&&[1]!='/')))" ) )
    {
        sz_t source_index = take_from_source ? 0 : bcore_source_a_get_index(source);
        switch( bcore_source_a_inspect_char(source) )
        {
            case '@':
            {
                bcore_source_a_get_char(source);
                st_s* st_name = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
                st_s_copy_sc(st_name,xoico_che_s_nameof(o,xoico_host_a_obj_type(o->host) ) );
                if( bcore_source_a_parse_bl(source,"#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||[0]=='_'||([0]>='0'&&[0]<='9'))" ) )
                {
                    bcore_source_a_parse_fa(source,"#:name", st_name );
                }
                tp_identifier = xoico_che_s_entypeof(o,st_name->sc );
            }
            break;
    
            case '$':
            {
                bcore_source_a_get_char(source);
                tp_identifier = TYPEOF_type_deduce;
            }
            break;
    
            case ':':
            {
                st_s* st_name = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
                xoico_host_a_parse_name(o->host,source, st_name );
                tp_identifier = xoico_che_s_entypeof(o,st_name->sc );
            }
            break;
    
            default:
            {
                st_s* st_name = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
                bcore_source_a_parse_fa(source,"#name", st_name );
                tp_identifier = xoico_che_s_entypeof(o,st_name->sc );
            }
            break;
        }
    
        if( !take_from_source ) bcore_source_a_set_index(source,source_index );
    }
    
    BLM_RETURNV(tp_t, tp_identifier)
}

er_t xoico_che_s_trans_identifier( xoico_che_s* o, bcore_source* source, xoico_che_result* result, tp_t* tp_identifier )
{
    // xoico_che.x:79:141
    
    tp_t identifier = xoico_che_s_get_identifier(o,source, true );
    if( !identifier )
    {
        return  bcore_source_a_parse_error_fa(source,"Identifier exected" );
    }
    if( tp_identifier ) (*(tp_identifier)) = identifier;
    if( result ) BLM_TRY(xoico_che_result_a_push_sc(result,xoico_che_s_nameof(o,identifier ) ))
    return  0;
}

er_t xoico_che_s_trans_number_literal( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che.x:94:89
    
    bl_t hex = false;
    if( bcore_source_a_parse_bl(source,"#?'0x'" ) )
    {
        BLM_TRY(xoico_che_result_a_push_sc(result,"0x" ))
        hex = true;
    }
    else if( bcore_source_a_parse_bl(source,"#?'0X'" ) )
    {
        BLM_TRY(xoico_che_result_a_push_sc(result,"0X" ))
        hex = true;
    }
    
    if( hex )
    {
        while( bcore_source_a_parse_bl(source,"#?(([0]>='0'&&[0]<='9')||([0]>='a'&&[0]<='f')||([0]>='A'&&[0]<='F'))" ) )
        {
            BLM_TRY(xoico_che_result_a_push_char(result,bcore_source_a_get_char(source) ))
        }
    }
    else // decimal
    {
        while( bcore_source_a_parse_bl(source,"#?([0]>='0'&&[0]<='9')" ) )
        {
            BLM_TRY(xoico_che_result_a_push_char(result,bcore_source_a_get_char(source) ))
        }
    }
    
    bl_t fraction = false;
    
    if( bcore_source_a_parse_bl(source,"#?([0]=='.')" ) )
    {
        BLM_TRY(xoico_che_result_a_push_char(result,bcore_source_a_get_char(source) ))
        fraction = true;
    }
    
    if( fraction )
    {
        while( bcore_source_a_parse_bl(source,"#?([0]>='0'&&[0]<='9')" ) )
        {
            BLM_TRY(xoico_che_result_a_push_char(result,bcore_source_a_get_char(source) ))
        }
    }
    
    bl_t exponent = false;
    
    if( bcore_source_a_parse_bl(source,"#?([0]=='e'&&[0]=='E')" ) )
    {
        BLM_TRY(xoico_che_result_a_push_char(result,bcore_source_a_get_char(source) ))
        exponent = true;
    }
    
    if( exponent )
    {
        if( bcore_source_a_parse_bl(source,"#?([0]=='+'||[0]=='-')" ) )
        {
            BLM_TRY(xoico_che_result_a_push_char(result,bcore_source_a_get_char(source) ))
        }
    
        while( bcore_source_a_parse_bl(source,"#?([0]>='0'&&[0]<='9')" ) )
        {
            BLM_TRY(xoico_che_result_a_push_char(result,bcore_source_a_get_char(source) ))
        }
    }
    
    // suffix
    while( bcore_source_a_parse_bl(source,"#?([0]=='l'||[0]=='L'||[0]=='u'||[0]=='U'||[0]=='f'||[0]=='F')" ) )
    {
        BLM_TRY(xoico_che_result_a_push_char(result,bcore_source_a_get_char(source) ))
    }
    
    return  0;
}

er_t xoico_che_s_trans_string_literal( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che.x:172:90
    
    BLM_TRY(xoico_che_s_trans(o,source, "\"", result ))
    
    while( !bcore_source_a_eos(source) && !bcore_source_a_parse_bl(source,"#=?'\"'" ) )
    {
        if( bcore_source_a_parse_bl(source,"#?'\\'" ) ) BLM_TRY(xoico_che_result_a_push_char(result,'\\' ))
        BLM_TRY(xoico_che_result_a_push_char(result,bcore_source_a_get_char(source) ))
    }
    
    BLM_TRY(xoico_che_s_trans(o,source, "\"", result ))
    return  0;
}

er_t xoico_che_s_trans_char_literal( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che.x:190:1
    
    {
        BLM_TRY(xoico_che_s_trans(o,source, "'", result ))
    
        while( !bcore_source_a_eos(source) && !bcore_source_a_parse_bl(source,"#=?|'|" ) )
        {
            if( bcore_source_a_parse_bl(source,"#?'\\'" ) ) BLM_TRY(xoico_che_result_a_push_char(result,'\\' ))
            BLM_TRY(xoico_che_result_a_push_char(result,bcore_source_a_get_char(source) ))
        }
    
        BLM_TRY(xoico_che_s_trans(o,source, "'", result ))
        return  0;
    } /* try */
}

er_t xoico_che_s_trans_whitespace( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che.x:208:104
    
    bl_t exit_loop = false;
    while( !exit_loop && !bcore_source_a_eos(source) )
    {
        char c =  bcore_source_a_inspect_char(source);
        switch( c )
        {
            case ' ' :
            case '\t':
            case '\n':
            {
                char c =  bcore_source_a_get_char(source);
                if( result )  BLM_TRY(xoico_che_result_a_push_char(result,c ))
            }
            break;
    
            case '/':
            {
                if( bcore_source_a_parse_bl(source,"#?'//'" ) )
                {
                    if( result ) BLM_TRY(xoico_che_result_a_push_sc(result,"//" ))
                    while( !bcore_source_a_eos(source) )
                    {
                        char c =  bcore_source_a_get_char(source);
                        if( result ) BLM_TRY(xoico_che_result_a_push_char(result,c ))
                        if( c == '\n' ) break;
                    }
                }
                else if( bcore_source_a_parse_bl(source,"#?'/*'" ) )
                {
                    if( result ) BLM_TRY(xoico_che_result_a_push_sc(result,"/*" ))
                    while( !bcore_source_a_eos(source) )
                    {
                        if( bcore_source_a_parse_bl(source,"#?'*/'" ) )
                        {
                            if( result ) BLM_TRY(xoico_che_result_a_push_sc(result,"*/" ))
                            break;
                        }
                        char c =  bcore_source_a_get_char(source);
                        if( result ) BLM_TRY(xoico_che_result_a_push_char(result,c ))
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
}

er_t xoico_che_s_trans_preprocessor( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che.x:270:88
    
    BLM_TRY(bcore_source_a_parse_em_fa(source,"##" ))
    BLM_TRY(xoico_che_result_a_push_sc(result,"#" ))
    while( !bcore_source_a_eos(source) )
    {
        char c = bcore_source_a_get_char(source);
        BLM_TRY(xoico_che_result_a_push_char(result,c ))
        if( c == '\\' && bcore_source_a_inspect_char(source) == '\n' ) BLM_TRY(xoico_che_result_a_push_char(result,bcore_source_a_get_char(source) ))
        if( c == '\n' ) break;
    }
    return  0;
}

tp_t xoico_che_s_trans_inert_operator( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che.x:288:1
    
    switch( bcore_source_a_inspect_char(source) )
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
            xoico_che_result_a_push_char(result,bcore_source_a_get_char(source) );
            return  1;
        }
        break;
    
        default: break;
    }
    
    return  false;
}

bl_t xoico_che_s_trans_operator( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che.x:319:1
    
    switch( bcore_source_a_inspect_char(source) )
    {
        case '+':
        {
            xoico_che_result_a_push_char(result,bcore_source_a_get_char(source) );
            char c = bcore_source_a_inspect_char(source);
            if( c == '=' || c == '+' ) xoico_che_result_a_push_char(result,bcore_source_a_get_char(source) );
        }
        return  true;
    
        case '-':
        {
            xoico_che_result_a_push_char(result,bcore_source_a_get_char(source) );
            char c = bcore_source_a_inspect_char(source);
            if( c == '=' || c == '-' ) xoico_che_result_a_push_char(result,bcore_source_a_get_char(source) );
        }
        return  true;
    
        case '*':
        case '/':
        case '=':
        case '!':
        case '^':
        case '%':
        {
            xoico_che_result_a_push_char(result,bcore_source_a_get_char(source) );
            if( bcore_source_a_inspect_char(source) == '=' ) xoico_che_result_a_push_char(result,bcore_source_a_get_char(source) );
        }
        return  true;
    
        case '>':
        {
            xoico_che_result_a_push_char(result,bcore_source_a_get_char(source) );
            char c = bcore_source_a_inspect_char(source);
            if( c == '=' || c == '>' ) xoico_che_result_a_push_char(result,bcore_source_a_get_char(source) );
            if( c == '>' && bcore_source_a_inspect_char(source) == '=' ) xoico_che_result_a_push_char(result,bcore_source_a_get_char(source) );
        }
        return  true;
    
        case '<':
        {
            xoico_che_result_a_push_char(result,bcore_source_a_get_char(source) );
            char c = bcore_source_a_inspect_char(source);
            if( c == '=' || c == '<' ) xoico_che_result_a_push_char(result,bcore_source_a_get_char(source) );
            if( c == '<' && bcore_source_a_inspect_char(source) == '=' ) xoico_che_result_a_push_char(result,bcore_source_a_get_char(source) );
        }
        return  true;
    
        case '|':
        {
            xoico_che_result_a_push_char(result,bcore_source_a_get_char(source) );
            char c = bcore_source_a_inspect_char(source);
            if( c == '=' || c == '|' ) xoico_che_result_a_push_char(result,bcore_source_a_get_char(source) );
        }
        return  true;
    
        case '&':
        {
            xoico_che_result_a_push_char(result,bcore_source_a_get_char(source) );
            char c = bcore_source_a_inspect_char(source);
            if( c == '=' || c == '&' ) xoico_che_result_a_push_char(result,bcore_source_a_get_char(source) );
        }
        return  true;
    
        case '~':
        {
            xoico_che_result_a_push_char(result,bcore_source_a_get_char(source) );
        }
        return  true;
    
        default: break;
    }
    
    return  false;
}

er_t xoico_che_s_adapt_expression_indirection( xoico_che_s* o, bcore_source* source, const xoico_typespec_s* typespec_expr, sz_t target_indirection, const xoico_che_result* result_expr, xoico_che_result* result )
{
    // xoico_che.x:409:5
    
    if( target_indirection == typespec_expr->indirection )
    {
        xoico_che_result_a_push_result_c(result,result_expr );
    }
    else if( target_indirection == typespec_expr->indirection + 1 )
    {
        if( typespec_expr->flag_addressable )
        {
            BLM_TRY(xoico_che_result_a_push_sc(result,"&(" ))
            xoico_che_result_a_push_result_c(result,result_expr );
            BLM_TRY(xoico_che_result_a_push_sc(result,")" ))
        }
        else
        {
            return  bcore_source_a_parse_error_fa(source,"Increasing indirection: Expression has no address." );
        }
    }
    else if( target_indirection < typespec_expr->indirection )
    {
        for( sz_t ind = typespec_expr->indirection; ind > target_indirection; ind-- ) BLM_TRY(xoico_che_result_a_push_sc(result,"*" ))
        BLM_TRY(xoico_che_result_a_push_sc(result,"(" ))
        xoico_che_result_a_push_result_c(result,result_expr );
        BLM_TRY(xoico_che_result_a_push_sc(result,")" ))
    }
    else
    {
        return  bcore_source_a_parse_error_fa(source,"Cannot adapt from expression's indirection '#<sz_t>' to target indirection '#<sz_t>'.",
            typespec_expr->indirection,
            target_indirection
        );
    }
    return  0;
}

er_t xoico_che_s_adapt_expression( xoico_che_s* o, bcore_source* source, const xoico_typespec_s* typespec_expr, const xoico_typespec_s* typespec_target, const xoico_che_result* result_expr, xoico_che_result* result )
{
    // xoico_che.x:460:5
    BLM_INIT_LEVEL(0);
    if( !typespec_expr->type )
    {
        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"xoico_che_s_adapt_expression: no expression type specified.",
            typespec_expr->indirection,
            typespec_target->indirection
        ))
    }
    
    if( !typespec_target->type )
    {
        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"xoico_che_s_adapt_expression: no target type specified.",
            typespec_expr->indirection,
            typespec_target->indirection
        ))
    }
    
    if( typespec_target->type == TYPEOF_type_deduce ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"adapt_expression: typespec_target is 'type_deduce'" ))
    if( typespec_target->type == TYPEOF_type_object ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"adapt_expression: typespec_target is 'type_object'" ))
    if( typespec_expr->type == TYPEOF_type_deduce ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"adapt_expression: typespec_expr is 'type_deduce'" ))
    if( typespec_expr->type == TYPEOF_type_object ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"adapt_expression: typespec_expr is 'type_object'" ))
    
    bl_t discarding_const =
        ( typespec_expr->flag_const && !typespec_target->flag_const ) &&
        ( typespec_expr->indirection > 0 || typespec_target->indirection > 0 );
    
    if( discarding_const ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Discarding 'const' qualifier." ))
    
    if( xoico_typespec_s_converts_to(typespec_expr,typespec_target ) )
    {
        xoico_che_result_a_push_result_c(result,result_expr );
    }
    else
    {
        bl_t implicit_cast = false;
        if( typespec_target->type != typespec_expr->type )
        {
            if( xoico_che_s_is_group(o,typespec_target->type ) && typespec_target->indirection == 1 )
            {
                if( xoico_che_s_is_group(o,typespec_expr->type ) )
                {
                    implicit_cast = true;
                }
                else if( xoico_che_s_is_stamp(o,typespec_expr->type ) )
                {
                    const xoico_stamp_s* stamp = xoico_che_s_get_stamp(o,typespec_expr->type );
                    implicit_cast = stamp->is_aware || typespec_target->flag_unaware;
                }
            }
    
            if( !implicit_cast )
            {
                st_s* st_typespec_expr = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
                st_s* st_typespec_target = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
                xoico_che_s_typespec_to_sink(o,typespec_expr,((bcore_sink*)( st_typespec_expr )));
                xoico_che_s_typespec_to_sink(o,typespec_target,((bcore_sink*)( st_typespec_target )));
                BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Implicit cast from '#<sc_t>' to '#<sc_t>' is not allowed. A cast-operator might be needed here.", st_typespec_expr->sc, st_typespec_target->sc ))
            }
        }
    
        if( implicit_cast )
        {
            BLM_TRY(xoico_che_result_a_push_sc(result,"((" ))
            BLM_TRY(xoico_che_s_push_typespec(o,typespec_target, result ))
            BLM_TRY(xoico_che_result_a_push_sc(result,")(" ))
        }
        BLM_TRY(xoico_che_s_adapt_expression_indirection(o,source, typespec_expr, typespec_target->indirection, result_expr, result ))
        if( implicit_cast ) BLM_TRY(xoico_che_result_a_push_sc(result,"))" ))
    }
    BLM_RETURNV(er_t, 0)
}

er_t xoico_che_s_trans_function_args( xoico_che_s* o, bcore_source* source, tp_t object_type, const xoico_signature_s* signature, const xoico_transient_map_s* transient_map, const xoico_che_result* result_obj_expr, const xoico_typespec_s* typespec_obj_expr, xoico_che_result* result_out, tp_t* transient_type )
{
    // xoico_che.x:554:5
    BLM_INIT_LEVEL(0);
    BLM_TRY(xoico_che_s_trans(o,source, "(", result_out ))
    
    tp_t transient_class = signature->typespec_ret.transient_class;
    
    if( signature->arg_o )
    {
        if( !result_obj_expr )
        {
            xoico_che_result* result_expr   = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
            xoico_typespec_s* typespec_expr = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
            BLM_TRY(xoico_che_s_trans_expression(o,source, result_expr, typespec_expr ))
            result_obj_expr = result_expr;
            typespec_obj_expr = typespec_expr;
            if( signature->args.size > 0 ) BLM_TRY(bcore_source_a_parse_em_fa(source," ," ))
        }
    
        xoico_typespec_s* typespec_obj_out = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
        typespec_obj_out->type = object_type ? object_type : typespec_obj_expr->type;
        typespec_obj_out->flag_const = signature->arg_o == TYPEOF_const;
        typespec_obj_out->indirection = 1; // first argument of a member function has always indirection 1
    
        if( signature->typed )
        {
            if( typespec_obj_expr->type )
            {
                xoico_che_result_a_push_fa( result_out,"TYPEOF_#<sc_t>,", xoico_che_s_nameof(o,typespec_obj_expr->type ) );
            }
            else
            {
                BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Function requires a typed object reference but object expression is not tractable." ))
            }
        }
    
        if( typespec_obj_expr->type )
        {
            if( !transient_map ) transient_map = xoico_che_s_get_transient_map(o,typespec_obj_expr->type );
            if( transient_class && transient_type && ( (*(transient_type)) == 0 ) && ( signature->arg_o_transient_class == transient_class ) )
            {
                (*(transient_type)) = typespec_obj_expr->type;
            }
            BLM_TRY(xoico_che_s_adapt_expression(o,source, typespec_obj_expr, typespec_obj_out, result_obj_expr, result_out ))
        }
        else
        {
            xoico_che_result_a_push_result_c(result_out,result_obj_expr );
        }
        if( signature->args.size > 0 ) BLM_TRY(xoico_che_result_a_push_sc(result_out,"," ))
    }
    
    if( transient_map && transient_class && transient_type )
    {
        tp_t type = xoico_transient_map_s_get(transient_map,transient_class );
        if( type )
        {
            if( !(*(transient_type)) )
            {
                (*(transient_type)) = type;
            }
            else if( (*(transient_type)) != type )
            {
                BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Object type expected: '#<sc_t>'. Object type passed: '#<sc_t>'.", xoico_che_s_nameof(o,type ), xoico_che_s_nameof(o,(*(transient_type)) ) ))
            }
        }
    }
    
    {const xoico_args_s* __a=&(signature->args );if(__a)for(sz_t __i=0; __i<__a->size; __i++){const xoico_arg_s* arg=__a->data[__i];
    {BLM_INIT_LEVEL(3);
        if( xoico_arg_s_is_variadic(arg) ) BLM_BREAK_LEVEL(1);
    
        xoico_che_result_arr_s* result_expr = ((xoico_che_result_arr_s*)BLM_LEVEL_T_PUSH(0,xoico_che_result_arr_s,xoico_che_result_arr_s_create()));
        xoico_typespec_s* typespec_expr = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(3,xoico_typespec_s,xoico_typespec_s_create()));
        BLM_TRY(bcore_source_a_parse_em_fa(source," " ))
    
        if( __i > 0 )
        {
            BLM_TRY(bcore_source_a_parse_em_fa(source," ," ))
            BLM_TRY(xoico_che_result_a_push_sc(result_out,"," ))
        }
    
        BLM_TRY(xoico_che_s_trans_whitespace(o,source,((xoico_che_result*)( result_expr ))))
        if( bcore_source_a_parse_bl(source,"#?')'" ) ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Function argument '#<sc_t>': No value passed.", xoico_che_s_nameof(o,arg->name ) ))
    
        BLM_TRY(xoico_che_s_trans_expression(o,source,((xoico_che_result*)( result_expr)), typespec_expr ))
    
        if( typespec_expr->type )
        {
            if( arg->typespec.transient_class )
            {
                if( transient_type && ( (*(transient_type)) == 0 ) && ( arg->typespec.transient_class == transient_class ) )
                {
                    (*(transient_type)) = typespec_expr->type;
                }
    
                if( transient_map )
                {
                    tp_t type = xoico_transient_map_s_get(transient_map,arg->typespec.transient_class );
                    if( type && typespec_expr->type != type )
                    {
                        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Function argument '#<sc_t>': Type expected: '#<sc_t>'. Type passed: '#<sc_t>'.", xoico_che_s_nameof(o,arg->name ), xoico_che_s_nameof(o,type ), xoico_che_s_nameof(o,typespec_expr->type ) ))
                    }
                }
            }
    
            BLM_TRY(xoico_che_s_adapt_expression(o,source, typespec_expr,&( arg->typespec),((const xoico_che_result*)( result_expr)), result_out ))
        }
        else
        {
            xoico_che_result_a_push_result_d(result_out,((xoico_che_result*)(((xoico_che_result_arr_s*)bcore_fork(result_expr)) )));
        }
    BLM_DOWN();}
    
    }}if( xoico_args_s_is_variadic(&(signature->args)) )
    {
        while( !bcore_source_a_eos(source) && !bcore_source_a_parse_bl(source," #=?')'" ) )
        {
            BLM_TRY(bcore_source_a_parse_em_fa(source," ," ))
            BLM_TRY(xoico_che_result_a_push_sc(result_out,"," ))
            BLM_TRY(xoico_che_s_trans_expression(o,source, result_out, NULL ))
        }
    }
    
    BLM_TRY(bcore_source_a_parse_em_fa(source," " ))
    BLM_TRY(xoico_che_s_trans(o,source, ")", result_out ))
    BLM_RETURNV(er_t, 0)
}

er_t xoico_che_s_trans_typespec_member( xoico_che_s* o, bcore_source* source, xoico_che_result* result, const xoico_typespec_s* in_typespec, xoico_typespec_s* out_typespec )
{
    // xoico_che.x:694:5
    BLM_INIT_LEVEL(0);
    if( bcore_source_a_parse_bl(source,"#?'->'" ) )
    {
        if( in_typespec->indirection != 1 )
        {
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Given indirection is '#<sz_t>'. '->' can only be used at indirection '1'.", in_typespec->indirection ))
        }
    }
    else
    {
        BLM_TRY(bcore_source_a_parse_em_fa(source,"." ))
    }
    BLM_TRY(bcore_source_a_parse_em_fa(source," " ))
    xoico_compiler_element_info_s* info = ((xoico_compiler_element_info_s*)BLM_LEVEL_T_PUSH(0,xoico_compiler_element_info_s,xoico_compiler_element_info_s_create()));
    
    char c = bcore_source_a_inspect_char(source);
    
    if( c == '*' || c == '&' )
    {
        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Postfix operators '&' and '*' are deprecated. Use numeric indirection level.\n" ))
    }
    
    if( c >= '0' && c <= '9' )
    {
        xoico_typespec_s* typespec_adapted = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_clone(in_typespec)));
        sz_t adapted_indirection = 0;
        BLM_TRY(bcore_source_a_parse_em_fa(source,"#<sz_t*>", &adapted_indirection ))
    
        typespec_adapted->indirection = adapted_indirection;
    
        xoico_che_result_arr_s* result_adapted = ((xoico_che_result_arr_s*)BLM_LEVEL_T_PUSH(0,xoico_che_result_arr_s,xoico_che_result_arr_s_create()));
        BLM_TRY(xoico_che_result_arr_s_push_sc(result_adapted,"(" ))
        BLM_TRY(xoico_che_s_adapt_expression(o,source, in_typespec, typespec_adapted, result,((xoico_che_result*)( result_adapted ))))
        BLM_TRY(xoico_che_result_arr_s_push_sc(result_adapted,")" ))
        xoico_che_result_a_clear(result);
        xoico_che_result_a_push_result_d(result,((xoico_che_result*)(((xoico_che_result_arr_s*)bcore_fork(result_adapted)) )));
        BLM_TRY(xoico_che_s_trans_typespec_expression(o,source, result, typespec_adapted, out_typespec ))
        BLM_RETURNV(er_t, 0)
    }
    
    if( bcore_source_a_parse_bl(source,"#=?'['" ) || bcore_source_a_parse_bl(source,"#=?'?['" ) ) // array subscript
    {
        bl_t bounds_check = false;
        if( bcore_source_a_parse_bl(source,"#=?'?'" ) )
        {
            BLM_TRY(bcore_source_a_parse_em_fa(source,"?[" ))
            bounds_check = true;
        }
        else
        {
            BLM_TRY(bcore_source_a_parse_em_fa(source,"[" ))
        }
    
        if( bounds_check ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Bounds check not yet available." ))
    
        if( in_typespec->indirection > 1 )
        {
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Resolving subscript: Indirection '#<sz_t>' is too large.",
                in_typespec->indirection
            ))
        }
    
        xoico_che_result_a_push_fa( result,"#<sc_t>data[", ( in_typespec->indirection == 1 ) ? "->" : "." );
        BLM_TRY(xoico_che_s_trans_expression(o,source, result, NULL ))
        BLM_TRY(bcore_source_a_parse_em_fa(source,"]" ))
        BLM_TRY(xoico_che_result_a_push_sc(result,"]" ))
    
        if( xoico_compiler_s_get_type_array_element_info(o->compiler,in_typespec->type, info ) )
        {
            BLM_TRY(xoico_che_s_trans_typespec_expression(o,source, result,&( info->type_info.typespec), out_typespec ))
        }
        else
        {
            BLM_TRY(xoico_che_s_trans_expression(o,source, result, NULL ))
        }
    }
    else // member (object or function)
    {
        xoico_che_result* result_local = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
        tp_t tp_identifier = 0;
        BLM_TRY(xoico_che_s_trans_identifier(o,source, result_local,&( tp_identifier )))
        BLM_TRY(xoico_che_s_trans_whitespace(o,source, result_local ))
    
        // builtin functions ...
        if( xoico_che_s_is_builtin_func(o,tp_identifier ) )
        {
            xoico_typespec_s* typespec_builtin = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
            BLM_TRY(xoico_che_s_trans_builtin(o,tp_identifier, source, result, in_typespec, result_local, typespec_builtin ))
            xoico_che_result_a_copy(result,result_local );
            BLM_TRY(xoico_che_s_trans_typespec_expression(o,source, result, typespec_builtin, out_typespec ))
        }
        else if( xoico_compiler_s_get_type_element_info(o->compiler,in_typespec->type, tp_identifier, info ) )
        {
            if( info->func ) // member function
            {
                xoico_func_s* func = info->func;
                xoico_signature_s* signature = ((xoico_signature_s*)BLM_LEVEL_T_PUSH(0,xoico_signature_s,xoico_signature_s_clone(func->signature)));
                tp_t object_type = func->obj_type;
                BLM_TRY(xoico_signature_s_relent(signature,o->host, object_type ))
                sc_t sc_func_name = xoico_che_s_nameof(o,func->global_name );
                ASSERT( sc_func_name );
    
                xoico_typespec_s* typespec_ret = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_clone(&(signature->typespec_ret))));
                tp_t transient_type = 0;
    
                xoico_che_result* result_arg_obj = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_a_clone(result)));
                xoico_che_result_a_clear(result);
                xoico_che_result_arr_s* result_args = ((xoico_che_result_arr_s*)BLM_LEVEL_T_PUSH(0,xoico_che_result_arr_s,xoico_che_result_arr_s_create()));
    
                xoico_transient_map_s* transient_map = xoico_che_s_get_transient_map(o,in_typespec->type );
    
                BLM_TRY(xoico_che_s_trans_function_args(o,source,
                    object_type,
                    signature,
                    transient_map,
                    result_arg_obj,
                    in_typespec,((xoico_che_result*)(
                    result_args)),
                    &transient_type
                ))
    
                if( transient_type != 0 )
                {
                    typespec_ret->type = transient_type;
                    BLM_TRY(xoico_che_result_a_push_sc(result,"((" ))
                    BLM_TRY(xoico_che_s_push_typespec(o,typespec_ret, result ))
                    BLM_TRY(xoico_che_result_a_push_sc(result,")(" ))
                }
    
                xoico_che_result_a_push_fa( result,"#<sc_t>", sc_func_name );
                xoico_che_result_a_push_result_d(result,((xoico_che_result*)(((xoico_che_result_arr_s*)bcore_fork(result_args)) )));
    
                if( transient_type != 0 )
                {
                    BLM_TRY(xoico_che_result_a_push_sc(result,"))" ))
                }
    
                BLM_TRY(xoico_che_s_trans_typespec_expression(o,source, result, typespec_ret, out_typespec ))
            }
            else // traced member element
            {
                if( in_typespec->indirection > 1 )
                {
                    BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Dereferencing #<sc_t>: Indirection '#<sz_t>' is too large.",
                        xoico_che_s_nameof(o,tp_identifier ),
                        in_typespec->indirection
                    ))
                }
                xoico_che_result_a_push_fa( result,"#<sc_t>", ( in_typespec->indirection == 1 ) ? "->" : "." );
                xoico_che_result_a_push_result_d(result,((xoico_che_result*)bcore_fork(result_local)) );
    
                BLM_TRY(xoico_che_s_trans_typespec_expression(o,source, result,&( info->type_info.typespec), out_typespec ))
            }
        }
        else if( bcore_source_a_parse_bl(source,"#?'('" ) ) // untraced member function
        {
            xoico_che_result* result_arg_obj = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_a_clone(result)));
            xoico_che_result_a_clear(result);
    
            /// Untraced member functions of a group are always treated as 'aware'
            if( xoico_che_s_is_group(o,in_typespec->type ) )
            {
                xoico_che_result_a_copy_fa( result,"#<sc_t>_a_#<sc_t>( ",
                    xoico_che_s_nameof(o,in_typespec->type ),
                    xoico_che_s_nameof(o,tp_identifier )
                );
            }
            else
            {
                xoico_che_result_a_copy_fa( result,"#<sc_t>_#<sc_t>( ",
                    xoico_che_s_nameof(o,in_typespec->type ),
                    xoico_che_s_nameof(o,tp_identifier )
                );
            }
    
            {
                xoico_typespec_s* typespec_obj = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_clone(in_typespec)));
                typespec_obj->indirection = 1; // first argument of member functions
                BLM_TRY(xoico_che_s_adapt_expression(o,source, in_typespec, typespec_obj, result_arg_obj, result ))
            }
    
            bl_t first = true;
            BLM_TRY(xoico_che_s_trans_whitespace(o,source, result_local ))
            while( !bcore_source_a_eos(source) )
            {
                if( bcore_source_a_parse_bl(source,"#=?')'" ) ) break;
    
                xoico_che_result* result_expr = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
                if( !first ) BLM_TRY(bcore_source_a_parse_em_fa(source,"," ))
                BLM_TRY(xoico_che_s_trans_expression(o,source, result_expr, NULL ))
                BLM_TRY(xoico_che_s_trans_whitespace(o,source, result_expr ))
                xoico_che_result_a_push_fa( result,"," );
                xoico_che_result_a_push_result_d(result,((xoico_che_result*)bcore_fork(result_expr)) );
                first = false;
            }
    
            BLM_TRY(bcore_source_a_parse_em_fa(source,")" ))
            BLM_TRY(xoico_che_result_a_push_sc(result,")" ))
    
            BLM_TRY(xoico_che_s_trans_expression(o,source, result, NULL ))
        }
        else // untraced member element
        {
            xoico_che_result_a_push_fa( result,"#<sc_t>", ( in_typespec->indirection == 1 ) ? "->" : "." );
            xoico_che_result_a_push_result_d(result,((xoico_che_result*)bcore_fork(result_local)) );
            BLM_TRY(xoico_che_s_trans_expression(o,source, result, NULL ))
        }
    }
    BLM_RETURNV(er_t, 0)
}

er_t xoico_che_s_trans_typespec_array_subscript( xoico_che_s* o, bcore_source* source, xoico_che_result* result, const xoico_typespec_s* in_typespec, xoico_typespec_s* out_typespec )
{
    // xoico_che.x:928:5
    BLM_INIT_LEVEL(0);
    BLM_TRY(bcore_source_a_parse_em_fa(source,"[" ))
    
    BLM_TRY(xoico_che_result_a_push_sc(result,"[" ))
    BLM_TRY(xoico_che_s_trans_expression(o,source, result, NULL ))
    BLM_TRY(bcore_source_a_parse_em_fa(source,"]" ))
    BLM_TRY(xoico_che_result_a_push_sc(result,"]" ))
    
    xoico_typespec_s* typespec = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_clone(in_typespec)));
    
    if( typespec->indirection == 0 )
    {
        if( in_typespec->type == TYPEOF_sc_t || in_typespec->type == TYPEOF_sd_t )
        {
            typespec->type = TYPEOF_u0_t;
        }
        else
        {
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Array subscript requires indirection >= 1." ))
        }
    }
    else
    {
        typespec->indirection--;
    }
    
    BLM_TRY(xoico_che_s_trans_typespec_expression(o,source, result, typespec, out_typespec ))
    
    BLM_RETURNV(er_t, 0)
}

er_t xoico_che_s_trans_typespec_create( xoico_che_s* o, bcore_source* source, xoico_che_result* result, const xoico_typespec_s* in_typespec, xoico_typespec_s* out_typespec )
{
    // xoico_che.x:972:5
    BLM_INIT_LEVEL(0);
    BLM_TRY(bcore_source_a_parse_em_fa(source,"!" ))
    
    //ignore in case indirection is 0;
    if( in_typespec->indirection > 0 )
    {
        if( !( in_typespec->indirection == 1 && in_typespec->flag_addressable ) )
        {
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Create-Operator requires lvalue with addressable indirection of 1." ))
        }
    
        if( xoico_che_s_is_group( o,in_typespec->type ) )
        {
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Create-Operator: lvalue is a group." ))
        }
    
        xoico_che_result* result_arg_obj = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_a_clone(result)));
        xoico_che_result_a_clear(result);
    
        sc_t sc_type = xoico_che_s_nameof(o,in_typespec->type );
        xoico_che_result_a_push_fa( result,"BCORE_PASS_CREATE(#<sc_t>,", sc_type );
        xoico_che_result_a_push_result_d(result,((xoico_che_result*)bcore_fork(result_arg_obj)) );
        BLM_TRY(xoico_che_result_a_push_sc(result,")" ))
    }
    
    BLM_TRY(xoico_che_s_trans_typespec_expression(o,source, result, in_typespec, out_typespec ))
    BLM_RETURNV(er_t, 0)
}

er_t xoico_che_s_trans_typespec_test_presence( xoico_che_s* o, bcore_source* source, xoico_che_result* result, const xoico_typespec_s* in_typespec, xoico_typespec_s* out_typespec )
{
    // xoico_che.x:1014:5
    BLM_INIT_LEVEL(0);
    BLM_TRY(bcore_source_a_parse_em_fa(source,"?" ))
    
    //ignore in case indirection is 0;
    if( in_typespec->indirection > 0 )
    {
        if( in_typespec->indirection != 1 )
        {
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Test-Operator requires lvalue with indirection of 1." ))
        }
    
        xoico_che_result* result_arg_obj = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_a_clone(result)));
        xoico_che_result_a_clear(result);
    
        sc_t sc_type = xoico_che_s_nameof(o,in_typespec->type );
        xoico_che_result_a_push_fa( result,"BCORE_PASS_TEST(#<sc_t>,", sc_type );
        xoico_che_result_a_push_result_d(result,((xoico_che_result*)bcore_fork(result_arg_obj)) );
        BLM_TRY(xoico_che_result_a_push_sc(result,")" ))
    }
    
    BLM_TRY(xoico_che_s_trans_typespec_expression(o,source, result, in_typespec, out_typespec ))
    BLM_RETURNV(er_t, 0)
}

er_t xoico_che_s_trans_typespec_attach( xoico_che_s* o, bcore_source* source, xoico_che_result* result, const xoico_typespec_s* in_typespec, xoico_typespec_s* out_typespec )
{
    // xoico_che.x:1051:5
    BLM_INIT_LEVEL(0);
    if( !( in_typespec->indirection == 1 && in_typespec->flag_addressable ) )
    {
        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Attach-Operator requires lvalue with addressable indirection of 1" ))
    }
    
    BLM_TRY(bcore_source_a_parse_em_fa(source,"=<" ))
    
    xoico_che_result* result_arg_obj = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_a_clone(result)));
    xoico_che_result_a_clear(result);
    
    sc_t sc_type = xoico_che_s_nameof(o,in_typespec->type );
    xoico_che_result_a_push_fa( result,"#<sc_t>", sc_type );
    
    xoico_typespec_s* typespec_rval = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
    if( xoico_che_s_is_group(o,in_typespec->type ) )
    {
        BLM_TRY(xoico_che_result_a_push_sc(result,"_a" ))
        BLM_TRY(xoico_che_result_a_push_sc(result,"_attach( &(" ))
        xoico_che_result_a_push_result_d(result,((xoico_che_result*)bcore_fork(result_arg_obj)) );
        xoico_che_result_a_push_fa( result,"), (#<sc_t>*)", sc_type );
    
        BLM_TRY(xoico_che_result_a_push_sc(result,"(" ))
        BLM_TRY(xoico_che_s_trans_expression(o,source, result, typespec_rval ))
        BLM_TRY(xoico_che_result_a_push_sc(result,"))" ))
    }
    else
    {
        BLM_TRY(xoico_che_result_a_push_sc(result,"_attach( &(" ))
        xoico_che_result_a_push_result_d(result,((xoico_che_result*)bcore_fork(result_arg_obj)) );
        BLM_TRY(xoico_che_result_a_push_sc(result,"), " ))
        BLM_TRY(xoico_che_s_trans_expression(o,source, result, typespec_rval ))
        BLM_TRY(xoico_che_result_a_push_sc(result,")" ))
    }
    
    if( typespec_rval->type && typespec_rval->indirection != 1 )
    {
        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Attach operator requires rvalue with indirection '1'" ))
    }
    
    if( out_typespec ) xoico_typespec_s_copy(out_typespec,in_typespec );
    BLM_RETURNV(er_t, 0)
}

er_t xoico_che_s_trans_typespec_ternary_branch( xoico_che_s* o, bcore_source* source, xoico_che_result* result, const xoico_typespec_s* in_typespec, xoico_typespec_s* out_typespec )
{
    // xoico_che.x:1108:5
    BLM_INIT_LEVEL(0);
    BLM_TRY(bcore_source_a_parse_em_fa(source,"?" ))
    BLM_TRY(xoico_che_result_a_push_sc(result,"?" ))
    xoico_typespec_s* typespec_true  = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
    
    BLM_TRY(xoico_che_s_trans_expression(o,source, result, typespec_true ))
    BLM_TRY(bcore_source_a_parse_em_fa(source,": " ))
    BLM_TRY(xoico_che_result_a_push_sc(result,": " ))
    BLM_TRY(xoico_che_s_trans_expression(o,source, result, NULL ))
    
    if( out_typespec && typespec_true->type )
    {
        xoico_typespec_s_copy(out_typespec,typespec_true );
        out_typespec->flag_addressable = false;
    }
    BLM_RETURNV(er_t, 0)
}

er_t xoico_che_s_trans_typespec_expression( xoico_che_s* o, bcore_source* source, xoico_che_result* result, const xoico_typespec_s* in_typespec, xoico_typespec_s* out_typespec )
{
    // xoico_che.x:1139:5
    
    if( out_typespec ) out_typespec->type = 0;
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    
    u0_t c[ 2 ];
    bcore_source_a_inspect_data(source,c, sizeof( c ) );
    
    if( c[0] == '.' || ( c[0] == '-' && c[1] == '>' ) )
    {
        BLM_TRY(xoico_che_s_trans_typespec_member(o,source, result, in_typespec, out_typespec ))
    }
    else if( c[0] == '[' )
    {
        BLM_TRY(xoico_che_s_trans_typespec_array_subscript(o,source, result, in_typespec, out_typespec ))
    }
    // create if not present
    else if( c[0] =='!' && c[1] != '=' )
    {
        BLM_TRY(xoico_che_s_trans_typespec_create(o,source, result, in_typespec, out_typespec ))
    }
    // test for presence
    else if( c[0] == '?' && c[1] == '.' )
    {
        BLM_TRY(xoico_che_s_trans_typespec_test_presence(o,source, result, in_typespec, out_typespec ))
    }
    // attach (detach)
    else if( c[0] == '=' && c[1] == '<' )
    {
        BLM_TRY(xoico_che_s_trans_typespec_attach(o,source, result, in_typespec, out_typespec ))
    }
    // ternary branch operator
    else if( c[0] == '?' )
    {
        BLM_TRY(xoico_che_s_trans_typespec_ternary_branch(o,source, result, in_typespec, out_typespec ))
    }
    else if( out_typespec )
    {
        xoico_typespec_s_copy(out_typespec,in_typespec );
    }
    
    return  0;
}

er_t xoico_che_s_trans_member( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che.x:1185:82
    
    if(      bcore_source_a_parse_bl(source,"#?'.'"  ) ) BLM_TRY(xoico_che_result_a_push_sc(result,"." ))
    else if( bcore_source_a_parse_bl(source,"#?'->'" ) ) BLM_TRY(xoico_che_result_a_push_sc(result,"->" ))
    
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    
    char c = bcore_source_a_inspect_char(source);
    
    if( c == '*' || c == '&' )
    {
        return  bcore_source_a_parse_error_fa(source,"Postfix operators '&' and '*' are deprecated.\n" );
    }
    
    if( c >= '0' && c <= '9' )
    {
        return  bcore_source_a_parse_error_fa(source,"Setting indirection: Expression not tractable\n" );
    }
    
    tp_t tp_identifier = xoico_che_s_get_identifier(o,source, false );
    
    if( xoico_che_s_is_builtin_func(o,tp_identifier ) )
    {
        return  bcore_source_a_parse_error_fa(source,"Expression before '#<sc_t>' not tractable\n", xoico_che_s_nameof(o,tp_identifier ) );
    }
    
    BLM_TRY(xoico_che_s_trans_identifier(o,source, result, NULL ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    if( bcore_source_a_parse_bl(source,"#?'('") )
    {
        return  bcore_source_a_parse_error_fa(source,"Untraced member function '#<sc_t>'\n", xoico_che_s_nameof(o,tp_identifier ) );
    }
    
    return  0;
}

er_t xoico_che_s_try_take_typespec( xoico_che_s* o, bcore_source* source, xoico_typespec_s* typespec, bl_t require_tractable_type, bl_t* success )
{
    // xoico_che.x:1236:5
    
    if( success ) (*(success)) = false;
    
    sz_t index = bcore_source_a_get_index(source);
    
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, NULL ))
    tp_t tp_identifier = xoico_che_s_get_identifier(o,source, true );
    
    if( !tp_identifier )
    {
        bcore_source_a_set_index(source,index );
        return  0;
    }
    
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, NULL ))
    
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
        if( tp_identifier == TYPEOF_scope    ) typespec->flag_scope    = true;
    
        // take fails if keyword is actually a function
        if( bcore_source_a_parse_bl(source,"#?'('" ) )
        {
            bcore_source_a_set_index(source,index );
            return  0;
        }
    
        BLM_TRY(xoico_che_s_trans_identifier(o,source, NULL,&( tp_identifier )))
        BLM_TRY(xoico_che_s_trans_whitespace(o,source, NULL ))
    }
    
    typespec->type = tp_identifier;
    
    //    if( source.parse_bl( "#?'.' " ) )
    //    {
    //        if( !source.parse_bl( "#?([0]>='0'||[0]<='1') " ) ) source.parse_error_fa( "Argument: Indirection literal expected." );
    //        sz_t indirection = 0;
    //        source.parse_fa( "#<sz_t*> ", indirection.1 );
    //        typespec.indirection = indirection;
    //    }
    //    else
    {
        while( bcore_source_a_parse_bl(source,"#?'*' " ) ) typespec->indirection++;
    }
    
    if( require_tractable_type )
    {
        if( !( tp_identifier == TYPEOF_type_deduce || xoico_che_s_is_type(o,tp_identifier ) ) )
        {
            bcore_source_a_set_index(source,index );
            return  0;
        }
    }
    
    if( success ) (*(success)) = true;
    return  0;
}

er_t xoico_che_s_take_typespec( xoico_che_s* o, bcore_source* source, xoico_typespec_s* typespec, bl_t require_tractable_type )
{
    // xoico_che.x:1315:5
    
    bl_t success = false;
    BLM_TRY(xoico_che_s_try_take_typespec(o,source, typespec, require_tractable_type,&( success )))
    
    if( !success )
    {
        if( require_tractable_type )
        {
            return  bcore_source_a_parse_error_fa(source,"Typespec: Syntax error or intractable type." );
        }
        else
        {
            return  bcore_source_a_parse_error_fa(source,"Typespec: Syntax error." );
        }
    }
    
    return  0;
}

er_t xoico_che_s_push_typespec( xoico_che_s* o, const xoico_typespec_s* typespec, xoico_che_result* result )
{
    // xoico_che.x:1337:29
    BLM_INIT_LEVEL(0);
    tp_t type = typespec->type;
    
    if( type == TYPEOF_type_object )
    {
        ERR_fa( "Cannot resolve 'type_object' at this point." );
    }
    else if( type == TYPEOF_type_deduce )
    {
        ERR_fa( "Cannot resolve 'type_deduce' at this point." );
    }
    else if( type == 0 )
    {
        ERR_fa( "Type is 0." );
    }
    
    st_s* st_type = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create_sc(xoico_che_s_nameof(o,type ) )));
    
    if( st_type->size == 0 )
    {
        ERR_fa( "Type '#<tp_t>' has no name.", type );
    }
    
    sc_t sc_type = st_type->sc;
    if( typespec->flag_static   ) xoico_che_result_a_push_fa( result,"static " );
    if( typespec->flag_const    ) xoico_che_result_a_push_fa( result,"const " );
    if( typespec->flag_volatile ) xoico_che_result_a_push_fa( result,"volatile " );
    xoico_che_result_a_push_fa( result,"#<sc_t>", sc_type );
    
    for( sz_t i = 0; i < typespec->indirection; i++ ) xoico_che_result_a_push_fa( result,"*" );
    if( typespec->flag_restrict ) xoico_che_result_a_push_fa( result,"restrict " );
    
    BLM_RETURNV(er_t, 0)
}

er_t xoico_che_s_trans_type( xoico_che_s* o, bcore_source* source, xoico_che_result* result, xoico_typespec_s* out_typespec )
{
    // xoico_che.x:1384:5
    BLM_INIT_LEVEL(0);
    xoico_che_result* result_type = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
    tp_t tp_identifier;
    BLM_TRY(xoico_che_s_trans_identifier(o,source, result_type,&( tp_identifier )))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result_type ))
    if( bcore_source_a_parse_bl(source,"#?'!'" ) )
    {
        if( xoico_che_s_is_group(o,tp_identifier ) )
        {
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Operator '!': lvalue is a group." ))
        }
        xoico_che_result_a_push_fa( result,"#<sc_t>_create()", xoico_che_s_nameof(o,tp_identifier ) );
        xoico_typespec_s* typespec = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
        typespec->type = tp_identifier;
        typespec->indirection = 1;
        typespec->flag_addressable = false;
        BLM_TRY(xoico_che_s_trans_typespec_expression(o,source, result, typespec, out_typespec ))
    }
    else
    {
        xoico_che_result_a_push_result_d(result,((xoico_che_result*)bcore_fork(result_type)) );
    }
    BLM_RETURNV(er_t, 0)
}

er_t xoico_che_s_trans_func( xoico_che_s* o, bcore_source* source, xoico_che_result* result, xoico_typespec_s* out_typespec )
{
    // xoico_che.x:1421:5
    BLM_INIT_LEVEL(0);
    tp_t tp_identifier = 0;
    
    xoico_che_result_arr_s* result_func = xoico_che_result_arr_s_create();
    BLM_TRY(xoico_che_s_trans_identifier(o,source,((xoico_che_result*)( result_func)),&( tp_identifier )))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source,((xoico_che_result*)( result_func ))))
    
    if( bcore_source_a_parse_bl(source,"#=?'('" ) ) // actual function call
    {BLM_INIT_LEVEL(1);
        const xoico_func_s* func = xoico_che_s_get_func(o,tp_identifier );
    
        if( !func->signature )
        {
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Function #<sc_t> has no signature.", xoico_che_s_nameof(o,tp_identifier ) ))
        }
    
        xoico_signature_s* signature = ((xoico_signature_s*)BLM_LEVEL_T_PUSH(0,xoico_signature_s,xoico_signature_s_clone(func->signature)));
        tp_t object_type = func->obj_type;
        BLM_TRY(xoico_signature_s_relent(signature,o->host, object_type ))
    
        xoico_typespec_s* typespec_ret = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(1,xoico_typespec_s,xoico_typespec_s_clone(&(signature->typespec_ret))));
        tp_t transient_type = 0;
    
        BLM_TRY(xoico_che_s_trans_function_args(o,source,
            object_type,
            signature,
            NULL/*transient_map*/,
            NULL,
            NULL,((xoico_che_result*)(
            result_func)),
            &transient_type
        ))
    
        if( transient_type != 0 )
        {
            typespec_ret->type = transient_type;
            BLM_TRY(xoico_che_result_a_push_sc(result,"((" ))
            BLM_TRY(xoico_che_s_push_typespec(o,typespec_ret, result ))
            BLM_TRY(xoico_che_result_a_push_sc(result,")(" ))
        }
    
        xoico_che_result_a_push_result_d(result,((xoico_che_result*)(result_func )));
    
        if( transient_type != 0 )
        {
            BLM_TRY(xoico_che_result_a_push_sc(result,"))" ))
        }
    
        BLM_TRY(xoico_che_s_trans_typespec_expression(o,source, result, typespec_ret, out_typespec ))
    BLM_DOWN();}
    else
    {
        xoico_che_result_a_push_result_d(result,((xoico_che_result*)(result_func )));
    }
    
    BLM_RETURNV(er_t, 0)
}

er_t xoico_che_s_trans_ternary_branch( xoico_che_s* o, bcore_source* source, xoico_che_result* result, xoico_typespec_s* out_typespec )
{
    // xoico_che.x:1493:5
    
    BLM_TRY(bcore_source_a_parse_em_fa(source,"?" ))
    BLM_TRY(xoico_che_result_a_push_sc(result,"?" ))
    BLM_TRY(xoico_che_s_trans_expression(o,source, result, NULL ))
    BLM_TRY(xoico_che_s_trans(o,source, ": ", result ))
    BLM_TRY(xoico_che_s_trans_expression(o,source, result, NULL ))
    return  0;
}

er_t xoico_che_s_trans_bracket( xoico_che_s* o, bcore_source* source, xoico_che_result* result, xoico_typespec_s* out_typespec )
{
    // xoico_che.x:1514:5
    
    BLM_TRY(bcore_source_a_parse_em_fa(source,"(" ))
    BLM_TRY(xoico_che_result_a_push_char(result,'(' ))
    while( !bcore_source_a_eos(source) )
    {
        BLM_TRY(xoico_che_s_trans_expression(o,source, result, out_typespec ))
        if     ( bcore_source_a_parse_bl(source,"#?')'" ) ) break;
        else if( bcore_source_a_parse_bl(source,"#?','" ) ) BLM_TRY(xoico_che_result_a_push_char(result,',' ))
        else return  bcore_source_a_parse_error_fa(source,"Syntax error in bracket expression." );
        if( out_typespec ) out_typespec->type = 0;
    }
    BLM_TRY(xoico_che_result_a_push_char(result,')' ))
    return  0;
}

er_t xoico_che_s_trans_array_subscript( xoico_che_s* o, bcore_source* source, xoico_che_result* result, xoico_typespec_s* out_typespec )
{
    // xoico_che.x:1541:5
    
    BLM_TRY(bcore_source_a_parse_em_fa(source,"[" ))
    BLM_TRY(xoico_che_result_a_push_sc(result,"[" ))
    BLM_TRY(xoico_che_s_trans_expression(o,source, result, NULL ))
    BLM_TRY(bcore_source_a_parse_em_fa(source,"]" ))
    BLM_TRY(xoico_che_result_a_push_sc(result,"]" ))
    return  0;
}

er_t xoico_che_s_trans_expression( xoico_che_s* o, bcore_source* source, xoico_che_result* result_out, xoico_typespec_s* out_typespec )
{
    // xoico_che.x:1562:5
    BLM_INIT_LEVEL(0);
    sc_t sc_bl_end_of_expression = "#?([0]==';'||[0]=='{'||[0]=='}'||[0]==')'||[0]==']'||[0]==','||([0]==':'&&([1]==' '||[1]=='\t'||[1]=='\n'||[1]=='/')))";
    
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result_out ))
    
    xoico_che_result* result = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
    bl_t continuation = true;
    
    if( out_typespec ) xoico_typespec_s_reset(out_typespec);
    
    tp_t tp_identifier = xoico_che_s_get_identifier(o,source, false );
    
    if( tp_identifier )
    {
        // examples of builtin functions: scope, cast, try, fork
        if( xoico_che_s_is_builtin_func(o,tp_identifier ) )
        {
            xoico_typespec_s* typespec_builtin = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
            BLM_TRY(xoico_che_s_trans_builtin(o,tp_identifier, source, NULL, NULL, result, typespec_builtin ))
            BLM_TRY(xoico_che_s_trans_typespec_expression(o,source, result, typespec_builtin, out_typespec ))
        }
    
        else if( tp_identifier == TYPEOF_verbatim_C )
        {
            BLM_TRY(bcore_source_a_parse_em_fa(source,"verbatim_C {" ))
            BLM_TRY(xoico_che_s_trans_block_inside_verbatim_c(o,source, result ))
            BLM_TRY(bcore_source_a_parse_em_fa(source," }" ))
        }
    
        // a control name marks end of expression...
        else if( xoico_che_s_is_control_name(o,tp_identifier ) )
        {
            continuation = false;
        }
    
        // identifier represents a registered variable
        else if( xoico_che_s_is_var(o,tp_identifier ) )
        {
            BLM_TRY(xoico_che_s_trans_identifier(o,source, result, NULL ))
            BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
            const xoico_typespec_s* typespec_var = xoico_che_stack_var_s_get_typespec(&(o->stack_var),tp_identifier );
            BLM_TRY(xoico_che_s_trans_typespec_expression(o,source, result, typespec_var, out_typespec ))
        }
    
        // identifier represents a type known to the compiler
        else if( xoico_che_s_is_type(o,tp_identifier ) )
        {
            BLM_TRY(xoico_che_s_trans_type(o,source, result, out_typespec ))
        }
    
        // identifier represents a (global) function name
        else if( xoico_che_s_is_func(o,tp_identifier ) )
        {
            BLM_TRY(xoico_che_s_trans_func(o,source, result, out_typespec ))
        }
        else // unknown identifier
        {
            BLM_TRY(xoico_che_s_trans_identifier(o,source, result, NULL ))
            BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    
            // assume untraced function call: bracket evaluation without internal type evaluation
            if( bcore_source_a_parse_bl(source,"#=?'('" ) )
            {
                BLM_TRY(xoico_che_s_trans_bracket(o,source, result, NULL ))
            }
        }
    }
    
    // literals and members
    else if( bcore_source_a_parse_bl(source,"#?([0]>='0'&&[0]<='9')" ) ) BLM_TRY(xoico_che_s_trans_number_literal(o,source, result ))
    else if( bcore_source_a_parse_bl(source,"#=?'\"'" )                ) BLM_TRY(xoico_che_s_trans_string_literal(o,source, result ))
    else if( bcore_source_a_parse_bl(source,"#=?|'|" )                 ) BLM_TRY(xoico_che_s_trans_char_literal(o,source, result ))
    else if( bcore_source_a_parse_bl(source,"#=?'.'" )                 ) BLM_TRY(xoico_che_s_trans_member(o,source, result ))
    else if( bcore_source_a_parse_bl(source,"#=?'->'" )                ) BLM_TRY(xoico_che_s_trans_member(o,source, result ))
    
    else if( bcore_source_a_parse_bl(source,"#=?'=<'" )                ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Attach operator: Expression not tractable." ))
    
    //    else if( source.parse_bl( "#=?'&'" ) ) return source.parse_error_fa( "Changing indirection: Prefix '&' is disallowed. Use postfix '.&'" );
    //    else if( source.parse_bl( "#=?'*'" ) ) return source.parse_error_fa( "Changing indirection: Prefix '*' is disallowed. Use postfix '.*'" );
    
    else if( xoico_che_s_trans_inert_operator(o,source, result )       ) {} // inert operators are not interpreted by che and passed to the c-compiler
    
    // ternary branch operator
    else if( bcore_source_a_parse_bl(source,"#=?'?'" ) )
    {
        BLM_TRY(xoico_che_s_trans_ternary_branch(o,source, result, out_typespec ))
    }
    
    // general bracket
    else if( bcore_source_a_parse_bl(source,"#=?'('" ) )
    {
        xoico_typespec_s* typespec_bracket = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
        BLM_TRY(xoico_che_s_trans_bracket(o,source, result, typespec_bracket ))
        if( typespec_bracket->type ) BLM_TRY(xoico_che_s_trans_typespec_expression(o,source, result, typespec_bracket, out_typespec ))
    }
    
    // array subscript
    else if( bcore_source_a_parse_bl(source,"#=?'['" ) )
    {
        BLM_TRY(xoico_che_s_trans_array_subscript(o,source, result, out_typespec ))
    }
    
    // end of expression...
    else if( bcore_source_a_parse_bl(source,sc_bl_end_of_expression ) )
    {
        continuation = false;
    }
    
    // unhandled
    else
    {
        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Syntax error after '#<sc_t>'", ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,xoico_che_result_a_create_st(result)))->sc ))
    }
    
    if( continuation )
    {
        if( !bcore_source_a_parse_bl(source,sc_bl_end_of_expression ) )
        {
            if( out_typespec ) xoico_typespec_s_reset(out_typespec);
    
    
            BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
            xoico_che_s_trans_operator(o,source, result );
    
    
            BLM_TRY(xoico_che_s_trans_expression(o,source, result, NULL ))
        }
    }
    
    if( result_out ) xoico_che_result_a_push_result_d(result_out,((xoico_che_result*)bcore_fork(result)) );
    
    BLM_RETURNV(er_t, 0)
}

er_t xoico_che_s_try_trans_declaration( xoico_che_s* o, bcore_source* source, xoico_che_result* result_out, bl_t* success )
{
    // xoico_che.x:1711:5
    BLM_INIT_LEVEL(0);
    if( success ) (*(success)) = false;
    
    xoico_typespec_s* typespec_var = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
    
    sz_t index = bcore_source_a_get_index(source);
    
    xoico_che_result* result_var = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
    
    bl_t success_take_typespec = false;
    BLM_TRY(xoico_che_s_try_take_typespec(o,source, typespec_var, true, (&(success_take_typespec)) ))
    
    if( !success_take_typespec )
    {
        bcore_source_a_set_index(source,index );
        BLM_RETURNV(er_t, 0)
    }
    
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result_var ))
    
    if
    (
        typespec_var->type &&
        bcore_source_a_parse_bl(source,"#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||[0]=='_')" )
    )
    {
        tp_t tp_identifier = 0;
        BLM_TRY(xoico_che_s_trans_identifier(o,source, result_var, (&(tp_identifier)) ))
        BLM_TRY(xoico_che_s_trans_whitespace(o,source, result_var ))
    
        if( bcore_source_a_parse_bl(source,"#?'='" ) )
        {
            bl_t pushed_typedecl = false;
            if( typespec_var->type != TYPEOF_type_deduce )
            {
                xoico_che_s_push_typedecl(o,typespec_var, tp_identifier );
                pushed_typedecl = true;
            }
    
            BLM_TRY(xoico_che_result_a_push_sc(result_var,"=" ))
            xoico_typespec_s* typespec_expr = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
            xoico_che_result* result_expr = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
            BLM_TRY(xoico_che_s_trans_expression(o,source, result_expr, typespec_expr ))
    
            if( typespec_var->type == TYPEOF_type_deduce )
            {
                if( !typespec_expr->type )
                {
                    BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Declaration-syntax: Deduce requested but expression is intractable." ))
                }
                typespec_var->type = typespec_expr->type;
            }
    
            if( typespec_expr->type )
            {
                BLM_TRY(xoico_che_s_adapt_expression(o,source, typespec_expr, typespec_var, result_expr, result_var ))
            }
            else
            {
                xoico_che_result_a_push_result_d(result_var,((xoico_che_result*)bcore_fork(result_expr)) );
            }
            BLM_TRY(xoico_che_s_push_typespec(o,typespec_var, result_out ))
            BLM_TRY(xoico_che_result_a_push_char(result_out,' ' ))
            xoico_che_result_a_push_result_d(result_out,((xoico_che_result*)bcore_fork(result_var)) );
            if( !pushed_typedecl ) xoico_che_s_push_typedecl(o,typespec_var, tp_identifier );
        }
        else if( typespec_var->type == TYPEOF_type_deduce )
        {
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Declaration-syntax: Deduce requested without assignment." ))
        }
        else if( bcore_source_a_parse_bl(source,"#=?'['" ) )
        {
            BLM_TRY(xoico_che_s_push_typespec(o,typespec_var, result_out ))
            while( bcore_source_a_parse_bl(source,"#?'['" ) )
            {
                BLM_TRY(xoico_che_result_a_push_char(result_var,'[' ))
                BLM_TRY(xoico_che_s_trans_expression(o,source, result_var, NULL ))
                BLM_TRY(bcore_source_a_parse_em_fa(source,"]" ))
                BLM_TRY(xoico_che_result_a_push_char(result_var,']' ))
                typespec_var->indirection++;
            }
            BLM_TRY(xoico_che_result_a_push_char(result_out,' ' ))
            xoico_che_result_a_push_result_d(result_out,((xoico_che_result*)bcore_fork(result_var)) );
            xoico_che_s_push_typedecl(o,typespec_var, tp_identifier );
        }
        else
        {
            BLM_TRY(xoico_che_s_push_typespec(o,typespec_var, result_out ))
            BLM_TRY(xoico_che_result_a_push_char(result_out,' ' ))
            xoico_che_result_a_push_result_d(result_out,((xoico_che_result*)bcore_fork(result_var)) );
            xoico_che_s_push_typedecl(o,typespec_var, tp_identifier );
        }
    
        if( success ) (*(success)) = true;
    }
    else
    {
        bcore_source_a_set_index(source,index );
        BLM_RETURNV(er_t, 0)
    }
    
    if( success ) (*(success)) = true;
    
    BLM_RETURNV(er_t, 0)
}

er_t xoico_che_s_inspect_variable( xoico_che_s* o, bcore_source* source )
{
    // xoico_che.x:1820:68
    BLM_INIT_LEVEL(0);
    BLM_TRY(bcore_source_a_parse_em_fa(source,"\?\?" ))
    
    st_s* st = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    xoico_che_result* result_local = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
    xoico_typespec_s* typespec = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
    BLM_TRY(bcore_source_a_parse_em_fa(source," #until';' ", st ))
    BLM_TRY(bcore_source_a_parse_em_fa(source,";" ))
    bcore_msg_fa( " \?? #<sc_t>;\n", st->sc );
    if( xoico_che_s_trans_expression(o,((bcore_source*)(((bcore_source_string_s*)BLM_LEVEL_T_PUSH(0,bcore_source_string_s,bcore_source_string_s_create_fa("#<st_s*>;", st ))))), result_local, typespec ) )
    {
        bcore_error_pop_to_sink( BCORE_STDOUT );
        bcore_msg_fa( "\n" );
    }
    else
    {
        if( st->size == 0 ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Variable name expected." ))
        bcore_msg_fa( "--> #<sc_t>;\n", ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,xoico_che_result_a_create_st(result_local)))->sc );
    
        if( typespec->type )
        {
            bcore_msg_fa( "Expression yields typespec:\n" );
            bcore_msg_fa( "  const      : #<bl_t>\n", typespec->flag_const );
            bcore_msg_fa( "  type       : #<sc_t>\n", xoico_che_s_nameof(o,typespec->type ) );
            bcore_msg_fa( "  indirection: #<sz_t>\n", typespec->indirection );
        }
        else
        {
            bcore_msg_fa( "Expression does not yield a typespec.\n" );
        }
    }
    BLM_RETURNV(er_t, 0)
}

er_t xoico_che_s_trans_statement_expression( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che.x:1857:96
    BLM_INIT_LEVEL(0);
    if( o->try_block_level > 0 )
    {
        xoico_typespec_s* typespec = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
        xoico_che_result* result_expr = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
        BLM_TRY(xoico_che_s_trans_expression(o,source, result_expr, typespec ))
        if
        (
            ( typespec->type == TYPEOF_er_t ) &&
            ( typespec->indirection == 0 ) &&
            ( typespec->flag_addressable == false )
        )
        {
            if( !bcore_source_a_parse_bl(source," #?';'" ) )
            {
                BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Inside a try-block: Expressions yielding 'er_t' must end with ';'" ))
            }
            BLM_TRY(xoico_che_result_a_push_sc(result,"BLM_TRY(" ))
            xoico_che_result_a_push_result_d(result,((xoico_che_result*)bcore_fork(result_expr)) );
            BLM_TRY(xoico_che_result_a_push_sc(result,")" ))
        }
        else
        {
            xoico_che_result_a_push_result_d(result,((xoico_che_result*)bcore_fork(result_expr)) );
        }
    }
    else
    {
        BLM_TRY(xoico_che_s_trans_expression(o,source, result, NULL ))
    }
    
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    
    // ':' between expressions is to be taken literally
    if( bcore_source_a_parse_bl(source,"#?':'" ) ) BLM_TRY(xoico_che_result_a_push_char(result,':' ))
    BLM_RETURNV(er_t, 0)
}

er_t xoico_che_s_trans_statement( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che.x:1898:85
    
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    
    if( bcore_source_a_parse_bl(source,"#?([0]=='{'||[0]=='#'||[0]==';'||[0]==','||[0]==')'||[0]=='}'||([0]=='?'&&[1]=='?'))" ) )
    {
        char c = bcore_source_a_inspect_char(source);
        switch( c )
        {
            case '{':
            {
                BLM_TRY(xoico_che_s_trans_block(o,source, result, false ))
            }
            break;
    
            case '#':
            {
                BLM_TRY(xoico_che_s_trans_preprocessor(o,source, result ))
            }
            break;
    
            case ';':
            {
                bcore_source_a_get_char(source);
                BLM_TRY(xoico_che_result_a_push_char(result,';' ))
            }
            break;
    
            case ',':
            {
                bcore_source_a_get_char(source);
                BLM_TRY(xoico_che_result_a_push_char(result,',' ))
            }
            break;
    
            case '?':
            {
                BLM_TRY(xoico_che_s_inspect_variable(o,source ))
            }
            break;
    
            case ')':
            {
                return  bcore_source_a_parse_error_fa(source,"Unmatched closing bracket." );
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
        tp_t tp_identifier = xoico_che_s_get_identifier(o,source, false );
    
        if( tp_identifier && xoico_che_s_is_control_name(o,tp_identifier ) )
        {
            BLM_TRY(xoico_che_s_trans_control(o,tp_identifier, source, result ))
        }
        else
        {
            bl_t success_declaration = false;
            BLM_TRY(xoico_che_s_try_trans_declaration(o,source, result, (&(success_declaration)) ))
            if( !success_declaration ) BLM_TRY(xoico_che_s_trans_statement_expression(o,source, result ))
        }
    }
    
    return  0;
}

er_t xoico_che_s_trans_block_inside( xoico_che_s* o, bcore_source* source, xoico_che_result* result_out )
{
    // xoico_che.x:1975:92
    BLM_INIT_LEVEL(0);
    xoico_che_result* result = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
    
    while( !bcore_source_a_parse_bl(source,"#=?'}'" ) && !bcore_source_a_eos(source) )
    {
        BLM_TRY(xoico_che_s_trans_statement(o,source, result ))
    }
    
    if( xoico_che_s_stack_block_get_top_unit(o)->use_blm )
    {
        xoico_che_result* result_block = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_block(o->level, true )));
    
        xoico_che_result_a_push_result_d(result_block,xoico_che_result_create_blm_init(o->level ) );
        xoico_che_result_a_push_result_d(result_block,((xoico_che_result*)bcore_fork(result)) );
    
        if( ( o->level > 0 ) || !xoico_che_s_returns_a_value(o) )
        {
            xoico_che_result_a_push_result_d(result_block,xoico_che_result_create_blm_down() );
        }
    
        xoico_che_result_a_push_result_d(result_out,((xoico_che_result*)bcore_fork(result_block)) );
    }
    else
    {
        xoico_che_result_a_push_result_d(result_out,((xoico_che_result*)bcore_fork(result)) );
    }
    
    BLM_RETURNV(er_t, 0)
}

er_t xoico_che_s_trans_block( xoico_che_s* o, bcore_source* source, xoico_che_result* result_out, bl_t is_break_ledge )
{
    // xoico_che.x:2008:106
    BLM_INIT_LEVEL(0);
    xoico_che_s_inc_block(o);
    xoico_che_result* result = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
    xoico_che_s_stack_block_get_top_unit(o)->break_ledge = is_break_ledge;
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    BLM_TRY(xoico_che_s_trans(o,source, "{", result ))
    BLM_TRY(xoico_che_s_trans_block_inside(o,source, result ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    BLM_TRY(xoico_che_s_trans(o,source, "}", result ))
    xoico_che_result_a_push_result_d(result_out,((xoico_che_result*)bcore_fork(result)) );
    xoico_che_s_dec_block(o);
    BLM_RETURNV(er_t, 0)
}

er_t xoico_che_s_trans_statement_as_block( xoico_che_s* o, bcore_source* source, xoico_che_result* result_out, bl_t is_break_ledge )
{
    // xoico_che.x:2025:119
    BLM_INIT_LEVEL(0);
    xoico_che_result* result = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
    
    xoico_che_s_inc_block(o);
    xoico_che_s_stack_block_get_top_unit(o)->break_ledge = is_break_ledge;
    
    BLM_TRY(xoico_che_s_trans_statement(o,source, result ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    if( bcore_source_a_parse_bl(source,"#?';'" ) ) BLM_TRY(xoico_che_result_a_push_sc(result,";" ))
    
    if( xoico_che_s_stack_block_get_top_unit(o)->use_blm )
    {
        xoico_che_result* result_block = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_block(o->level, true )));
        xoico_che_result_a_push_result_d(result_block,xoico_che_result_create_blm_init(o->level ) );
        xoico_che_result_a_push_result_d(result_block,((xoico_che_result*)bcore_fork(result)) );
        xoico_che_result_a_push_result_d(result_block,xoico_che_result_create_blm_down() );
    
        BLM_TRY(xoico_che_result_a_push_sc(result_out,"{" ))
        xoico_che_result_a_push_result_d(result_out,((xoico_che_result*)bcore_fork(result_block)) );
        BLM_TRY(xoico_che_result_a_push_sc(result_out,"}" ))
    }
    else
    {
        xoico_che_result_a_push_result_d(result_out,((xoico_che_result*)bcore_fork(result)) );
    }
    
    xoico_che_s_dec_block(o);
    BLM_RETURNV(er_t, 0)
}

er_t xoico_che_s_trans_block_inside_verbatim_c( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che.x:2058:99
    
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    while( !bcore_source_a_parse_bl(source,"#=?'}'" ) && !bcore_source_a_eos(source) )
    {
        switch( bcore_source_a_inspect_char(source) )
        {
            case '"':
            {
                BLM_TRY(xoico_che_s_trans_string_literal(o,source, result ))
            }
            break;
    
            case '\'':
            {
                BLM_TRY(xoico_che_s_trans_char_literal(o,source, result ))
            }
            break;
    
            case '{':
            {
                BLM_TRY(xoico_che_result_a_push_char(result,bcore_source_a_get_char(source) ))
                BLM_TRY(xoico_che_s_trans_block_inside_verbatim_c(o,source, result ))
                BLM_TRY(bcore_source_a_parse_em_fa(source,"}" ))
                BLM_TRY(xoico_che_result_a_push_char(result,'}' ))
            }
            break;
    
            default:
            {
                BLM_TRY(xoico_che_result_a_push_char(result,bcore_source_a_get_char(source) ))
            }
            break;
        }
        BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    }
    return  0;
}

er_t xoico_che_s_setup( xoico_che_s* o, const xoico_host* host, const xoico_signature_s* signature )
{
    // xoico_che.x:2099:96
    BLM_INIT_LEVEL(0);
    tp_t host_obj_type = xoico_host_a_obj_type(host);
    
    const xoico_args_s* args =&( signature->args);
    
    tp_t tp_member_obj_type  = ( signature->arg_o == 0 ) ? 0 : host_obj_type;
    bl_t member_obj_const = ( signature->arg_o == TYPEOF_const );
    
    xoico_typespec_s_copy(&(o->typespec_ret),&(signature->typespec_ret ));
    BLM_TRY(xoico_typespec_s_relent(&(o->typespec_ret),host, host_obj_type ))
    
    o->host     = ((xoico_host*)(host));
    o->compiler = xoico_host_a_compiler(host);
    o->member_obj_type = tp_member_obj_type;
    o->level    = 0;
    o->try_block_level = 0;
    xoico_che_stack_var_s_clear(&(o->stack_var));
    xoico_che_s_init_level0(o);
    
    if( signature->typed )
    {
        xoico_che_stack_var_unit_s* unit = ((xoico_che_stack_var_unit_s*)BLM_LEVEL_T_PUSH(0,xoico_che_stack_var_unit_s,xoico_che_stack_var_unit_s_create()));
        unit->typespec.type = TYPEOF_tp_t;
        unit->typespec.flag_const = false;
        unit->typespec.indirection = 1;
        unit->name = xoico_che_s_entypeof(o,"t" );
        unit->level = o->level;
        xoico_che_stack_var_s_push_unit(&(o->stack_var),unit );
        bcore_hmap_name_s_set_sc(&(o->hmap_name),"tp_t" );
        bcore_hmap_name_s_set_sc(&(o->hmap_name),"t" );
    }
    
    if( tp_member_obj_type )
    {
        xoico_che_stack_var_unit_s* unit = ((xoico_che_stack_var_unit_s*)BLM_LEVEL_T_PUSH(0,xoico_che_stack_var_unit_s,xoico_che_stack_var_unit_s_create()));
        tp_t tp_member_obj_name  = xoico_che_s_entypeof(o,"o" );
        unit->typespec.flag_const = member_obj_const;
        unit->typespec.type = tp_member_obj_type;
        unit->typespec.indirection = 1;
        unit->name = tp_member_obj_name;
        unit->level = o->level;
        xoico_che_stack_var_s_push_unit(&(o->stack_var),unit );
        bcore_hmap_name_s_set_sc(&(o->hmap_name),xoico_compiler_s_nameof(o->compiler,tp_member_obj_type ) );
        bcore_hmap_name_s_set_sc(&(o->hmap_name),xoico_compiler_s_nameof(o->compiler,tp_member_obj_name ) );
    }
    
    {const xoico_args_s* __a=args ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_arg_s* arg=__a->data[__i];
    {
        if( arg->typespec.type && arg->name )
        {
            xoico_che_stack_var_unit_s* unit = ((xoico_che_stack_var_unit_s*)BLM_LEVEL_T_PUSH(0,xoico_che_stack_var_unit_s,xoico_che_stack_var_unit_s_create()));
            xoico_typespec_s_copy(&(unit->typespec),&(arg->typespec ));
            BLM_TRY(xoico_typespec_s_relent(&(unit->typespec),host, host_obj_type ))
            unit->name = arg->name;
            unit->level = o->level;
            xoico_che_stack_var_s_push_unit(&(o->stack_var),unit );
            bcore_hmap_name_s_set_sc(&(o->hmap_name),xoico_compiler_s_nameof(o->compiler,arg->typespec.type ) );
            bcore_hmap_name_s_set_sc(&(o->hmap_name),xoico_compiler_s_nameof(o->compiler,arg->name ) );
        }
    }
    }}BLM_RETURNV(er_t, 0)
}

sz_t xoico_che_s_assess_indentation( bcore_source* source )
{
    // xoico_che.x:2166:1
    
    sz_t index = bcore_source_a_get_index(source);
    while( !bcore_source_a_eos(source) ) if( bcore_source_a_get_char(source) == '\n' ) break;
    sz_t indentation = 0;
    while( !bcore_source_a_eos(source) )
    {
        if( bcore_source_a_get_char(source) != ' ' ) break;
        indentation++;
    }
    bcore_source_a_set_index(source,index );
    return  indentation;
}

void xoico_che_s_remove_indentation( st_s* string, sz_t indentation )
{
    // xoico_che.x:2182:1
    
    ASSERT( string->space >= string->size );
    
    sz_t j = 0;
    for( sz_t i = 0; i < string->size; i++ )
    {
        char c = string->data[ i ];
        string->data[ j++ ] = c;
        if( c == '\n' )
        {
            for( sz_t k = 0; k < indentation; k++ )
            {
                if( string->data[ i + 1 ] != ' ' ) break;
                i++;
            }
        }
    }
    
    string->data[ j ] = 0;
    string->size = j;
}

er_t xoico_che_s_translate_mutable( xoico_che_s* o, const xoico_host* host, const xoico_body_s* body, const xoico_signature_s* signature, bcore_sink* sink )
{
    // xoico_che.x:2206:152
    BLM_INIT_LEVEL(0);
    BLM_TRY(xoico_che_s_setup(o,host, signature ))
    
    bcore_source* source = ((bcore_source*)BLM_LEVEL_A_PUSH(0,bcore_source_point_s_clone_source(&(body->code->source_point))));
    
    xoico_che_result* result = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
    
    bl_t flag_verbatim_c = false;
    bl_t flag_try = false;
    
    if( bcore_source_a_parse_bl(source," #?'('" ) )
    {
        while( !bcore_source_a_parse_bl(source," #?')'" ) )
        {
            if( bcore_source_a_parse_bl(source," #?'try'" ) )
            {
                if( o->typespec_ret.type != TYPEOF_er_t || o->typespec_ret.indirection != 0 )
                {
                    BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Operator 'try': This operator can only be used in functions returning 'er_t'." ))
                }
                flag_try = true;
            }
            else if( bcore_source_a_parse_bl(source," #?'verbatim_C'" ) )
            {
                flag_verbatim_c = true;
            }
            else
            {
                BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Invalid c-engine expression." ))
            }
        }
    }
    
    BLM_TRY(bcore_source_a_parse_em_fa(source," {" ))
    sz_t indentation = 0;
    if( !body->go_inline ) indentation = xoico_che_s_assess_indentation(source );
    
    if( flag_verbatim_c )
    {
        BLM_TRY(xoico_che_s_trans_block_inside_verbatim_c(o,source, result ))
    }
    else
    {
        o->try_block_level += flag_try;
        BLM_TRY(xoico_che_s_trans_block_inside(o,source, result ))
        o->try_block_level -= flag_try;
    }
    BLM_TRY(bcore_source_a_parse_em_fa(source," }" ))
    
    xoico_che_result* result_block = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_block(o->level, xoico_che_s_stack_block_get_bottom_unit(o)->use_blm )));
    ((xoico_che_result_block_s*)(result_block))->is_root = true;
    xoico_che_result_a_push_result_d(result_block,((xoico_che_result*)bcore_fork(result)) );
    
    st_s* buf = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    BLM_TRY(xoico_che_result_a_to_sink(result_block,((bcore_sink*)(buf ))))
    
    //remove trailing whitespaces
    for( sz_t i = buf->size - 1; i >= 0; i-- )
    {
        if( buf->data[ i ] != ' ' && buf->data[ i ] != '\t' && buf->data[ i ] != '\n' ) break;
        buf->data[ i ] = 0;
        buf->size = i;
    }
    
    if( o->insert_source_reference && !body->code->single_line )
    {
        bcore_sink_a_push_fa(sink,"// " );
        bcore_source_point_s_source_reference_to_sink(&(body->code->source_point),true, sink );
        bcore_sink_a_push_fa(sink,"\n" );
    }
    
    if( indentation > 0 ) xoico_che_s_remove_indentation(buf, indentation );
    
    if( o->verbose )
    {
        bcore_sink_a_push_fa( BCORE_STDOUT,"##############################\n" );
        bcore_sink_a_push_fa( BCORE_STDOUT,"#<st_s*>\n", buf );
    }
    
    bcore_sink_a_push_sc(sink,buf->sc );
    
    BLM_RETURNV(er_t, 0)
}

er_t xoico_che_s_translate( const xoico_che_s* o, const xoico_host* host, const xoico_body_s* body, const xoico_signature_s* signature, bcore_sink* sink )
{
    // xoico_che.x:2294:1
    BLM_INIT_LEVEL(0);
    er_t er = xoico_che_s_translate_mutable(((xoico_che_s*)BLM_LEVEL_T_PUSH(0,xoico_che_s,xoico_che_s_clone(o))),host, body, signature, sink );
    BLM_RETURNV(er_t, er)
}

bl_t xoico_che_s_is_builtin_func( const xoico_che_s* o, tp_t tp_identifier )
{
    // xoico_che_builtin.x:21:1
    
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

er_t xoico_che_s_trans_builtin( xoico_che_s* o, tp_t tp_builtin, bcore_source* source, const xoico_che_result* result_expr, const xoico_typespec_s* typespec_expr, xoico_che_result* result_out, xoico_typespec_s* typespec_out )
{
    // xoico_che_builtin.x:49:5
    
    switch( tp_builtin )
    {
        case TYPEOF_cast : return  xoico_che_s_trans_builtin_cast(o,source, result_expr, typespec_expr, result_out, typespec_out );
        case TYPEOF_scope: return  xoico_che_s_trans_builtin_scope(o,source, result_expr, typespec_expr, result_out, typespec_out );
        case TYPEOF_fork:  return  xoico_che_s_trans_builtin_fork(o,source, result_expr, typespec_expr, result_out, typespec_out );
        case TYPEOF_try:   return  xoico_che_s_trans_builtin_try(o,source, result_expr, typespec_expr, result_out, typespec_out );
        default: return  bcore_source_a_parse_error_fa(source,"Internal error: Invalid builtin type '#<sc_t>'", ifnameof( tp_builtin ) );
    }
}

er_t xoico_che_s_trans_builtin_cast( xoico_che_s* o, bcore_source* source, const xoico_che_result* result_expr, const xoico_typespec_s* typespec_expr, xoico_che_result* result_out, xoico_typespec_s* typespec_out )
{
    // xoico_che_builtin.x:74:5
    BLM_INIT_LEVEL(0);
    if( result_expr ) // member call
    {
        BLM_TRY(bcore_source_a_parse_em_fa(source," ( " ))
        xoico_che_result_a_clear(result_out);
    }
    else // direct call
    {
        BLM_TRY(bcore_source_a_parse_em_fa(source,"cast ( " ))
        xoico_che_result* result = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
        xoico_typespec_s* typespec = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
        BLM_TRY(xoico_che_s_trans_expression(o,source, result, typespec ))
        BLM_TRY(bcore_source_a_parse_em_fa(source," , " ))
        typespec_expr = typespec;
        result_expr = result;
    }
    
    BLM_TRY(xoico_che_result_a_push_sc(result_out,"((" ))
    xoico_typespec_s* typespec_cast = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
    
    BLM_TRY(xoico_che_s_take_typespec(o,source, typespec_cast, true ))
    
    if( typespec_cast->type == TYPEOF_type_deduce )
    {
        if( !typespec_expr->type )
        {
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Cast-syntax: Deduce requested but expression is intractable." ))
        }
        typespec_cast->type = typespec_expr->type;
    }
    
    BLM_TRY(xoico_che_s_push_typespec(o,typespec_cast, result_out ))
    BLM_TRY(xoico_che_result_a_push_sc(result_out,")(" ))
    
    if
    (
        typespec_expr->type &&
        ( typespec_expr->type != TYPEOF_vc_t ) &&
        ( typespec_expr->type != TYPEOF_vd_t ) &&
        ( typespec_expr->type != TYPEOF_sc_t ) &&
        ( typespec_expr->type != TYPEOF_sd_t ) &&
        ( typespec_expr->type != TYPEOF_void )
    )
    {
        BLM_TRY(xoico_che_s_adapt_expression_indirection(o,source, typespec_expr, typespec_cast->indirection, result_expr, result_out ))
    }
    else
    {
        xoico_che_result_a_push_result_c(result_out,result_expr );
    }
    
    BLM_TRY(bcore_source_a_parse_em_fa(source," )" ))
    BLM_TRY(xoico_che_result_a_push_sc(result_out,"))" ))
    
    if( typespec_out ) xoico_typespec_s_copy(typespec_out,typespec_cast );
    
    if( typespec_cast->indirection > typespec_expr->indirection )
    {
        typespec_out->flag_addressable = false;
    }
    
    BLM_RETURNV(er_t, 0)
}

er_t xoico_che_s_trans_builtin_scope( xoico_che_s* o, bcore_source* source, const xoico_che_result* result_expr, const xoico_typespec_s* typespec_expr, xoico_che_result* result_out, xoico_typespec_s* typespec_out )
{
    // xoico_che_builtin.x:152:5
    BLM_INIT_LEVEL(0);
    bl_t has_arg = false;
    
    if( result_expr ) // member call
    {
        BLM_TRY(bcore_source_a_parse_em_fa(source," ( " ))
        xoico_che_result_a_clear(result_out);
        has_arg = !bcore_source_a_parse_bl(source,"#=?')'" );
    }
    else // direct call
    {
        BLM_TRY(bcore_source_a_parse_em_fa(source,"scope ( " ))
        xoico_che_result* result = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
        xoico_typespec_s* typespec = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
        BLM_TRY(xoico_che_s_trans_expression(o,source, result, typespec ))
        typespec_expr = typespec;
        result_expr = result;
        has_arg = bcore_source_a_parse_bl(source,"#?','" );
    }
    
    const xoico_typespec_s* typespec_scope = typespec_expr;
    
    BLM_TRY(xoico_che_result_a_push_sc(result_out,"((" ))
    
    sz_t level = 0;
    
    if( has_arg )
    {
        BLM_TRY(bcore_source_a_parse_em_fa(source," " ))
        tp_t tp_identifier = xoico_che_s_get_identifier(o,source, true );
    
        if( xoico_che_s_is_var(o,tp_identifier ) )
        {
            level = xoico_che_stack_var_s_get_level(&(o->stack_var),tp_identifier );
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
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"scope: identifier '#<sc_t>' does not represent a variable.", xoico_che_s_nameof(o,tp_identifier ) ))
        }
    }
    
    BLM_TRY(bcore_source_a_parse_em_fa(source," )" ))
    
    if( typespec_scope->type        == 0 ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Operator 'scope': Expression not tractable." ))
    if( typespec_scope->indirection != 1 ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Operator 'scope': Expression's indirection != 1." ))
    if( typespec_scope->flag_scope )       BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Operator 'scope': Target is already scoped." ))
    
    BLM_TRY(xoico_che_s_push_typespec(o,typespec_scope, result_out ))
    
    if( xoico_che_s_is_group(o,typespec_scope->type ) )
    {
        xoico_che_result_a_push_fa( result_out,")BLM_LEVEL_A_PUSH(#<sz_t>,", level );
        xoico_che_result_a_push_result_c(result_out,result_expr );
        BLM_TRY(xoico_che_result_a_push_sc(result_out,"))" ))
    }
    else
    {
        xoico_che_result_a_push_fa( result_out,")BLM_LEVEL_T_PUSH(#<sz_t>,#<sc_t>,", level, xoico_che_s_nameof(o,typespec_scope->type ) );
        xoico_che_result_a_push_result_c(result_out,result_expr );
        BLM_TRY(xoico_che_result_a_push_sc(result_out,"))" ))
    }
    
    o->stack_block.adl.data[ level ]->use_blm = true;
    
    if( typespec_out )
    {
        xoico_typespec_s_copy(typespec_out,typespec_scope );
        typespec_out->flag_scope = true;
    }
    
    BLM_RETURNV(er_t, 0)
}

er_t xoico_che_s_trans_builtin_fork( xoico_che_s* o, bcore_source* source, const xoico_che_result* result_expr, const xoico_typespec_s* typespec_expr, xoico_che_result* result_out, xoico_typespec_s* typespec_out )
{
    // xoico_che_builtin.x:247:5
    BLM_INIT_LEVEL(0);
    if( result_expr ) // member call
    {
        BLM_TRY(bcore_source_a_parse_em_fa(source," ( " ))
        xoico_che_result_a_clear(result_out);
    }
    else // direct call
    {
        BLM_TRY(bcore_source_a_parse_em_fa(source,"fork ( " ))
        xoico_che_result* result = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
        xoico_typespec_s* typespec = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
        BLM_TRY(xoico_che_s_trans_expression(o,source, result, typespec ))
        typespec_expr = typespec;
        result_expr = result;
    }
    
    const xoico_typespec_s* typespec_fork = typespec_expr;
    
    BLM_TRY(xoico_che_result_a_push_sc(result_out,"((" ))
    
    BLM_TRY(bcore_source_a_parse_em_fa(source," )" ))
    
    if( typespec_fork->type        == 0 ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Operator 'fork': Expression not tractable." ))
    if( typespec_fork->indirection != 1 ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Operator 'fork': Expression's indirection != 1." ))
    
    BLM_TRY(xoico_che_s_push_typespec(o,typespec_fork, result_out ))
    BLM_TRY(xoico_che_result_a_push_sc(result_out,")bcore_fork(" ))
    xoico_che_result_a_push_result_c(result_out,result_expr );
    BLM_TRY(xoico_che_result_a_push_sc(result_out,"))" ))
    
    if( typespec_out ) xoico_typespec_s_copy(typespec_out,typespec_fork );
    
    BLM_RETURNV(er_t, 0)
}

er_t xoico_che_s_trans_builtin_try( xoico_che_s* o, bcore_source* source, const xoico_che_result* result_expr, const xoico_typespec_s* typespec_expr, xoico_che_result* result_out, xoico_typespec_s* typespec_out )
{
    // xoico_che_builtin.x:296:5
    BLM_INIT_LEVEL(0);
    if( o->typespec_ret.type != TYPEOF_er_t || o->typespec_ret.indirection != 0 )
    {
        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Operator 'try': This operator can only be used in functions returning 'er_t'." ))
    }
    
    if( typespec_out ) xoico_typespec_s_reset(typespec_out);
    
    if( result_expr ) // member call
    {
        BLM_TRY(bcore_source_a_parse_em_fa(source," ( " ))
        xoico_che_result_a_clear(result_out);
    }
    else // direct call
    {
        BLM_TRY(bcore_source_a_parse_em_fa(source,"try " ))
    
        if( bcore_source_a_parse_bl(source,"#=?'{'" ) ) // try block
        {
            o->try_block_level++;
            BLM_TRY(xoico_che_s_trans_block(o,source, result_out, false ))
            o->try_block_level--;
            BLM_RETURNV(er_t, 0)
        }
    
        BLM_TRY(bcore_source_a_parse_em_fa(source,"( " ))
        xoico_che_result* result = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
        xoico_typespec_s* typespec = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
        BLM_TRY(xoico_che_s_trans_expression(o,source, result, typespec ))
        typespec_expr = typespec;
        result_expr = result;
    }
    
    const xoico_typespec_s* typespec_try = typespec_expr;
    
    BLM_TRY(bcore_source_a_parse_em_fa(source," ) ;" ))
    
    if( typespec_try->type != 0 )
    {
        if( typespec_try->type != TYPEOF_er_t ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Operator 'try': Expression must yield er_t." ))
        if( typespec_try->indirection != 0    ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Operator 'try': Expression's indirection != 0." ))
    }
    else
    {
        // return source.parse_error_fa( "Operator 'try': Expression not tractable." );
    }
    
    BLM_TRY(xoico_che_result_a_push_sc(result_out,"BLM_TRY(" ))
    xoico_che_result_a_push_result_c(result_out,result_expr );
    BLM_TRY(xoico_che_result_a_push_sc(result_out,")" ))
    
    BLM_RETURNV(er_t, 0)
}

bl_t xoico_che_s_is_control_name( const xoico_che_s* o, tp_t tp_identifier )
{
    // xoico_che_control.x:21:1
    
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
        case TYPEOF_continue:
        case TYPEOF_goto:
            return  true;
    
        default:
            return  false;
    }
}

er_t xoico_che_s_trans_control( xoico_che_s* o, tp_t tp_control, bcore_source* source, xoico_che_result* result )
{
    // xoico_che_control.x:46:101
    
    switch( tp_control )
    {
        case TYPEOF_for:     return  xoico_che_s_trans_control_for(o,source, result );
        case TYPEOF_foreach: return  xoico_che_s_trans_control_foreach(o,source, result );
        case TYPEOF_if:      return  xoico_che_s_trans_control_if(o,source, result );
        case TYPEOF_else:    return  xoico_che_s_trans_control_else(o,source, result );
        case TYPEOF_break:   return  xoico_che_s_trans_control_break(o,source, result );
        case TYPEOF_while:   return  xoico_che_s_trans_control_while(o,source, result );
        case TYPEOF_do:      return  xoico_che_s_trans_control_do(o,source, result );
        case TYPEOF_switch:  return  xoico_che_s_trans_control_switch(o,source, result );
        case TYPEOF_case:    return  xoico_che_s_trans_control_case(o,source, result );
        case TYPEOF_default: return  xoico_che_s_trans_control_default(o,source, result );
        case TYPEOF_return:  return  xoico_che_s_trans_control_return(o,source, result );
    
        // unsupported controls
        case TYPEOF_goto:
        case TYPEOF_continue:
            return  bcore_source_a_parse_error_fa(source,"Control statement '#<sc_t>' is not supported.", ifnameof( tp_control ) );
    
        default:
            return  bcore_source_a_parse_error_fa(source,"Internal error: Invalid control name '#<sc_t>'", ifnameof( tp_control ) );
    }
}

er_t xoico_che_s_trans_control_for( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che_control.x:74:88
    
    xoico_che_s_inc_block(o);
    xoico_che_s_stack_block_get_top_unit(o)->break_ledge = true;
    BLM_TRY(xoico_che_s_trans(o,source, "for", result ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    BLM_TRY(xoico_che_s_trans(o,source, "(", result ))
    BLM_TRY(xoico_che_s_trans_statement(o,source, result )) // def
    BLM_TRY(xoico_che_s_trans(o,source, ";", result ))
    BLM_TRY(xoico_che_s_trans_expression(o,source, result, NULL )) // cond
    BLM_TRY(xoico_che_s_trans(o,source, ";", result ))
    BLM_TRY(xoico_che_s_trans_expression(o,source, result, NULL )) // update
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    BLM_TRY(xoico_che_s_trans(o,source, ")", result ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    if( bcore_source_a_parse_bl(source,"#=?'{'" ) )
    {
        BLM_TRY(xoico_che_s_trans_block(o,source, result, false ))
    }
    else
    {
        BLM_TRY(xoico_che_s_trans_statement_as_block(o,source, result, false ))
    }
    xoico_che_s_dec_block(o);
    return  0;
}

er_t xoico_che_s_trans_control_foreach( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che_control.x:107:92
    BLM_INIT_LEVEL(0);
    xoico_che_s_inc_block(o);
    xoico_che_s_stack_block_get_top_unit(o)->break_ledge = true;
    BLM_TRY(bcore_source_a_parse_em_fa(source,"foreach ( " ))
    
    xoico_typespec_s* typespec_var = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create() ));
    BLM_TRY(xoico_che_s_take_typespec(o,source, typespec_var, true ))
    
    tp_t tp_var_name = 0;
    
    if( bcore_source_a_parse_bl(source,"#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||[0]=='_')" ) )
    {
        tp_var_name = xoico_che_s_get_identifier(o,source, true );
    }
    else
    {
        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Variable name expected." ))
    }
    
    BLM_TRY(bcore_source_a_parse_em_fa(source," in " ))
    
    xoico_typespec_s* typespec_arr_expr = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create() ));
    xoico_che_result* result_arr_expr = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
    BLM_TRY(xoico_che_s_trans_expression(o,source, result_arr_expr, typespec_arr_expr ))
    
    if( !typespec_arr_expr->type )
    {
        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Array expression not tractable." ))
    }
    
    xoico_compiler_element_info_s* info = ((xoico_compiler_element_info_s*)BLM_LEVEL_T_PUSH(0,xoico_compiler_element_info_s,xoico_compiler_element_info_s_create() ));
    
    if( !xoico_compiler_s_get_type_array_element_info(o->compiler,typespec_arr_expr->type, info ) )
    {
        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Expression does not evaluate to an array." ))
    }
    
    xoico_typespec_s* typespec_element =&( info->type_info.typespec);
    
    if( typespec_var->type == TYPEOF_type_deduce ) typespec_var->type = typespec_element->type;
    
    BLM_TRY(bcore_source_a_parse_em_fa(source," )" ))
    
    xoico_typespec_s* typespec_arr = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_clone(typespec_arr_expr) ));
    typespec_arr->indirection = 1;
    typespec_arr->flag_const = true;
    
    xoico_typespec_s* typespec_idx = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create() ));
    typespec_idx->type = TYPEOF_sz_t;
    
    xoico_che_s_push_typedecl(o,typespec_var, tp_var_name );
    xoico_che_s_push_typedecl(o,typespec_arr, xoico_che_s_entypeof(o,"__a" ) );
    xoico_che_s_push_typedecl(o,typespec_idx, xoico_che_s_entypeof(o,"__i" ) );
    
    xoico_che_result* result_statement = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
    if( bcore_source_a_parse_bl(source,"#=?'{'" ) )
    {
        BLM_TRY(xoico_che_s_trans_block(o,source, result_statement, false ))
    }
    else
    {
        BLM_TRY(xoico_che_s_trans_statement_as_block(o,source, result_statement, false ))
    }
    
    xoico_che_result_a_push_fa( result,"{" );
    
    BLM_TRY(xoico_che_s_push_typespec(o,typespec_arr, result ))
    
    xoico_che_result_a_push_fa( result," __a=" );
    BLM_TRY(xoico_che_s_adapt_expression(o,source, typespec_arr_expr, typespec_arr, result_arr_expr, result ))
    xoico_che_result_a_push_fa( result,";" );
    xoico_che_result_a_push_fa( result,"if(__a)for(sz_t __i=0; __i<__a->size; __i++){" );
    BLM_TRY(xoico_che_s_push_typespec(o,typespec_var, result ))
    xoico_che_result_a_push_fa( result," #<sc_t>=", xoico_che_s_nameof( o,tp_var_name ) );
    
    xoico_che_result* result_element_expr = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_from_sc("__a->data[__i]" )));
    
    BLM_TRY(xoico_che_s_adapt_expression(o,source, typespec_element, typespec_var, result_element_expr, result ))
    xoico_che_result_a_push_fa( result,";" );
    
    xoico_che_result_a_push_result_d(result,((xoico_che_result*)bcore_fork(result_statement)) );
    
    xoico_che_result_a_push_fa( result,"}}" );
    xoico_che_s_dec_block(o);
    BLM_RETURNV(er_t, 0)
}

er_t xoico_che_s_trans_control_if( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che_control.x:197:87
    
    BLM_TRY(xoico_che_s_trans(o,source, "if", result ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    BLM_TRY(xoico_che_s_trans(o,source, "(", result ))
    BLM_TRY(xoico_che_s_trans_expression(o,source, result, NULL )) // def
    BLM_TRY(xoico_che_s_trans(o,source, ")", result ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    if( bcore_source_a_parse_bl(source,"#=?'{'" ) )
    {
        BLM_TRY(xoico_che_s_trans_block(o,source, result, false ))
    }
    else
    {
        BLM_TRY(xoico_che_s_trans_statement_as_block(o,source, result, false ))
    }
    return  0;
}

er_t xoico_che_s_trans_control_while( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che_control.x:218:90
    
    BLM_TRY(xoico_che_s_trans(o,source, "while", result ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    BLM_TRY(xoico_che_s_trans(o,source, "(", result ))
    BLM_TRY(xoico_che_s_trans_expression(o,source, result, NULL )) // def
    BLM_TRY(xoico_che_s_trans(o,source, ")", result ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    if( bcore_source_a_parse_bl(source,"#=?'{'" ) )
    {
        BLM_TRY(xoico_che_s_trans_block(o,source, result, true ))
    }
    else
    {
        BLM_TRY(xoico_che_s_trans_statement_as_block(o,source, result, true ))
    }
    return  0;
}

er_t xoico_che_s_trans_control_do( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che_control.x:239:87
    
    BLM_TRY(xoico_che_s_trans(o,source, "do", result ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    if( bcore_source_a_parse_bl(source,"#=?'{'" ) )
    {
        BLM_TRY(xoico_che_s_trans_block(o,source, result, true ))
    }
    else
    {
        BLM_TRY(xoico_che_s_trans_statement_as_block(o,source, result, true ))
    }
    BLM_TRY(xoico_che_s_trans(o,source, "while", result ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    BLM_TRY(xoico_che_s_trans(o,source, "(", result ))
    BLM_TRY(xoico_che_s_trans_expression(o,source, result, NULL )) // def
    BLM_TRY(xoico_che_s_trans(o,source, ")", result ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    BLM_TRY(xoico_che_s_trans(o,source, ";", result ))
    return  0;
}

er_t xoico_che_s_trans_control_else( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che_control.x:263:89
    
    BLM_TRY(xoico_che_s_trans(o,source, "else", result ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    if( bcore_source_a_parse_bl(source,"#=?'{'" ) )
    {
        BLM_TRY(xoico_che_s_trans_block(o,source, result, false ))
    }
    else
    {
        BLM_TRY(xoico_che_s_trans_statement_as_block(o,source, result, false ))
    }
    return  0;
}

er_t xoico_che_s_trans_control_switch( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che_control.x:280:91
    
    BLM_TRY(xoico_che_s_trans(o,source, "switch", result ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    BLM_TRY(xoico_che_s_trans(o,source, "(", result ))
    BLM_TRY(xoico_che_s_trans_expression(o,source, result, NULL )) // def
    BLM_TRY(xoico_che_s_trans(o,source, ")", result ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    BLM_TRY(xoico_che_s_trans_block(o,source, result, true ))
    return  0;
}

er_t xoico_che_s_trans_control_case( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che_control.x:294:89
    
    BLM_TRY(xoico_che_s_trans(o,source, "case", result ))
    BLM_TRY(xoico_che_s_trans_expression(o,source, result, NULL ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    BLM_TRY(xoico_che_s_trans(o,source, ":", result ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    BLM_TRY(xoico_che_s_trans_statement_as_block(o,source, result, false ))
    return  0;
}

er_t xoico_che_s_trans_control_default( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che_control.x:307:92
    
    BLM_TRY(xoico_che_s_trans(o,source, "default", result ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    BLM_TRY(xoico_che_s_trans(o,source, ":", result ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    BLM_TRY(xoico_che_s_trans_statement_as_block(o,source, result, false ))
    return  0;
}

er_t xoico_che_s_trans_control_break( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che_control.x:343:90
    
    BLM_TRY(bcore_source_a_parse_em_fa(source,"break ;" ))
    
    sz_t ledge_level = -1;
    bl_t use_blm = false;
    
    for( sz_t i = o->stack_block.adl.size - 1; i >= 0; i-- )
    {
        const xoico_che_stack_block_unit_s* unit = o->stack_block.adl.data[ i ];
        use_blm = use_blm || unit->use_blm;
        if( unit->break_ledge )
        {
            ledge_level = unit->level;
            break;
        }
    }
    
    if( ledge_level == -1 ) return  bcore_source_a_parse_error_fa(source,"'break' has no ledge." );
    
    xoico_che_result_a_push_result_d(result,((xoico_che_result*)(xoico_che_result_break_s_create_setup(ledge_level ) )));
    
    return  0;
}

er_t xoico_che_s_trans_control_return( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che_control.x:395:91
    BLM_INIT_LEVEL(0);
    BLM_TRY(bcore_source_a_parse_em_fa(source,"return" ))
    
    xoico_che_result* result_expr = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
    
    xoico_typespec_s* typespec_expr = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create() ));
    const xoico_typespec_s* typespec_ret =&( o->typespec_ret);
    
    BLM_TRY(xoico_che_s_trans_expression(o,source, result_expr, typespec_expr ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result_expr ))
    BLM_TRY(bcore_source_a_parse_em_fa(source,";" ))
    
    if( typespec_expr->type )
    {
        if( !xoico_che_s_returns_a_value(o) )
        {
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa(source,"Function does not return a value." ))
        }
    }
    
    xoico_che_result* result_expr_adapted = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
    if( xoico_che_s_returns_a_value(o) && typespec_expr->type )
    {
        BLM_TRY(xoico_che_s_adapt_expression(o,source, typespec_expr, typespec_ret, result_expr, result_expr_adapted ))
    }
    else
    {
        xoico_che_result_a_push_result_d(result_expr_adapted,((xoico_che_result*)bcore_fork(result_expr)) );
    }
    
    
    xoico_che_result* result_blm = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
    if( xoico_che_s_returns_a_value(o) )
    {
        BLM_TRY(xoico_che_result_a_push_sc(result_blm,"BLM_RETURNV(" ))
        BLM_TRY(xoico_che_s_push_typespec(o,typespec_ret, result_blm ))
        BLM_TRY(xoico_che_result_a_push_sc(result_blm,"," ))
        xoico_che_result_a_push_result_d(result_blm,((xoico_che_result*)bcore_fork(result_expr_adapted)) );
        BLM_TRY(xoico_che_result_a_push_sc(result_blm,")" ))  // do not terminate BLM_RETURNV macro with a semicolon, otherwise if-else statements might not be handled correctly
    }
    else
    {
        BLM_TRY(xoico_che_result_a_push_sc(result_blm,"BLM_RETURN" ))
        xoico_che_result_a_push_result_d(result_blm,((xoico_che_result*)bcore_fork(result_expr_adapted)) );
        BLM_TRY(xoico_che_result_a_push_sc(result_blm,";" ))
    }
    
    xoico_che_result* result_direct = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
    BLM_TRY(xoico_che_result_a_push_sc(result_direct,"return " ))
    xoico_che_result_a_push_result_d(result_direct,((xoico_che_result*)bcore_fork(result_expr_adapted)) );
    BLM_TRY(xoico_che_result_a_push_sc(result_direct,";" ))
    
    xoico_che_result_return_s* result_return = ((xoico_che_result_return_s*)BLM_LEVEL_T_PUSH(0,xoico_che_result_return_s,xoico_che_result_return_s_create()));
    xoico_che_result_a_attach( &(result_return->result_blm ), (xoico_che_result*)( ((xoico_che_result*)bcore_fork(result_blm))));
    xoico_che_result_a_attach( &(result_return->result_direct ), (xoico_che_result*)( ((xoico_che_result*)bcore_fork(result_direct))));
    
    xoico_che_result_a_push_result_d(result,((xoico_che_result*)(((xoico_che_result_return_s*)bcore_fork(result_return)) )));
    
    BLM_RETURNV(er_t, 0)
}

BCORE_DEFINE_OBJECT_INST_P( xoico_che_result_break_s )
"aware xoico_che_result"
"{"
    "sz_t ledge_level;"
    "hidden xoico_che_result_block_s* parent;"
    "func xoico_che_result:set_parent_block;"
    "func xoico_che_result:to_sink;"
"}";

er_t xoico_che_result_break_s_to_sink( const xoico_che_result_break_s* o, bcore_sink* sink )
{
    // xoico_che_control.x:327:5
    
    if( !o->parent ) ERR_fa( "Parent missing." );
    if( xoico_che_result_block_s_is_using_blm_until_level(o->parent,o->ledge_level ) )
    {
        bcore_sink_a_push_fa(sink,"BLM_BREAK_LEVEL(#<sz_t>);", o->ledge_level );
    }
    else
    {
        bcore_sink_a_push_fa(sink,"break;" );
    }
    return  0;
}

BCORE_DEFINE_OBJECT_INST_P( xoico_che_result_return_s )
"aware xoico_che_result"
"{"
    "hidden xoico_che_result_block_s* parent;"
    "hidden aware xoico_che_result -> result_blm;"
    "hidden aware xoico_che_result -> result_direct;"
    "func xoico_che_result:set_parent_block;"
    "func xoico_che_result:to_sink;"
"}";

er_t xoico_che_result_return_s_to_sink( const xoico_che_result_return_s* o, bcore_sink* sink )
{
    // xoico_che_control.x:379:5
    
    if( !o->parent ) ERR_fa( "Parent missing." );
    if( xoico_che_result_block_s_is_using_blm_until_level(o->parent,0 ) )
    {
        xoico_che_result_a_to_sink(o->result_blm,sink );
    }
    else
    {
        xoico_che_result_a_to_sink(o->result_direct,sink );
    }
    return  0;
}

XOILA_DEFINE_SPECT( xoico_cengine, xoico_che )
"{"
    "bcore_spect_header_s header;"
"}";

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_che_result

BCORE_DEFINE_OBJECT_INST_P( xoico_che_result_plain_s )
"aware xoico_che_result"
"{"
    "st_s st;"
    "func xoico_che_result:clear;"
    "func xoico_che_result:push_char;"
    "func xoico_che_result:push_sc;"
    "func xoico_che_result:push_st;"
    "func xoico_che_result:to_sink;"
    "func xoico_che_result:create_st;"
"}";

BCORE_DEFINE_OBJECT_INST_P( xoico_che_result_adl_s )
"aware x_array"
"{"
    "aware xoico_che_result-> [];"
"}";

BCORE_DEFINE_OBJECT_INST_P( xoico_che_result_arr_s )
"aware xoico_che_result"
"{"
    "xoico_che_result_adl_s adl;"
    "func xoico_che_result:clear;"
    "func xoico_che_result:push_char;"
    "func xoico_che_result:push_sc;"
    "func xoico_che_result:push_st;"
    "func xoico_che_result:push_result_d;"
    "func xoico_che_result:push_result_c;"
    "func xoico_che_result:to_sink;"
    "func xoico_che_result:set_parent_block;"
"}";

xoico_che_result* xoico_che_result_arr_s_last( xoico_che_result_arr_s* o )
{
    // xoico_che.h:87:9
    
    return  ( o->adl.size == 0 ) ? ((xoico_che_result*)(x_array_push_d(((x_array*)(&(o->adl))),((x_inst*)(((xoico_che_result*)(xoico_che_result_plain_s_create())) ))))) : o->adl.data[ o->adl.size - 1 ];
}

xoico_che_result* xoico_che_result_arr_s_last_plain( xoico_che_result_arr_s* o )
{
    // xoico_che.h:92:9
    
    return  ( xoico_che_result_arr_s_last(o)->_ != TYPEOF_xoico_che_result_plain_s ) ? ((xoico_che_result*)(x_array_push_d(((x_array*)(&(o->adl))),((x_inst*)(((xoico_che_result*)(xoico_che_result_plain_s_create())) ))))) : o->adl.data[ o->adl.size - 1 ];
}

er_t xoico_che_result_arr_s_to_sink( const xoico_che_result_arr_s* o, bcore_sink* sink )
{
    // xoico_che.h:103:9
    
    {const xoico_che_result_adl_s* __a=&(o->adl );if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_che_result* e=__a->data[__i]; xoico_che_result_a_to_sink(e,sink );}}
    return  0;
}

void xoico_che_result_arr_s_set_parent_block( xoico_che_result_arr_s* o, xoico_che_result_block_s* parent )
{
    // xoico_che.h:109:9
    
    {const xoico_che_result_adl_s* __a=&(o->adl );if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_che_result* e=__a->data[__i]; xoico_che_result_a_set_parent_block(e,parent );}}
}

BCORE_DEFINE_OBJECT_INST_P( xoico_che_result_block_s )
"aware xoico_che_result"
"{"
    "xoico_che_result_arr_s arr;"
    "sz_t level = 0;"
    "bl_t is_using_blm = false;"
    "bl_t is_root = false;"
    "hidden xoico_che_result_block_s* parent;"
    "func xoico_che_result:clear;"
    "func xoico_che_result:push_char;"
    "func xoico_che_result:push_sc;"
    "func xoico_che_result:push_st;"
    "func xoico_che_result:push_result_d;"
    "func xoico_che_result:push_result_c;"
    "func xoico_che_result:to_sink;"
    "func xoico_che_result:set_parent_block;"
"}";

xoico_che_result* xoico_che_result_block_s_push_result_d( xoico_che_result_block_s* o, xoico_che_result* result )
{
    // xoico_che.h:131:9
    
    xoico_che_result* result_pushed = xoico_che_result_arr_s_push_result_d(&(o->arr),result );
    xoico_che_result_a_set_parent_block(result_pushed,o );
    return  result_pushed;
}

xoico_che_result* xoico_che_result_block_s_push_result_c( xoico_che_result_block_s* o, const xoico_che_result* result )
{
    // xoico_che.h:138:9
    
    xoico_che_result* result_pushed = xoico_che_result_arr_s_push_result_c(&(o->arr),result );
    xoico_che_result_a_set_parent_block(result_pushed,o );
    return  result_pushed;
}

bl_t xoico_che_result_block_s_is_using_blm_until_level( const xoico_che_result_block_s* o, sz_t level )
{
    // xoico_che.h:148:9
    
    if( level > o->level ) return  false;
    if( o->is_using_blm ) return  true;
    if( o->is_root ) return  false;
    
    ASSERT( o->parent );
    return  xoico_che_result_block_s_is_using_blm_until_level(o->parent,level );
}

BCORE_DEFINE_OBJECT_INST_P( xoico_che_result_blm_init_s )
"aware xoico_che_result"
"{"
    "sz_t level;"
    "func xoico_che_result:to_sink;"
"}";

BCORE_DEFINE_OBJECT_INST_P( xoico_che_result_blm_down_s )
"aware xoico_che_result"
"{"
    "func xoico_che_result:to_sink;"
"}";

XOILA_DEFINE_SPECT( xoico_che, xoico_che_result )
"{"
    "bcore_spect_header_s header;"
    "feature aware xoico_che_result : clear = xoico_che_result_clear_default;"
    "feature aware xoico_che_result : push_char = xoico_che_result_push_char_default;"
    "feature aware xoico_che_result : push_sc = xoico_che_result_push_sc_default;"
    "feature aware xoico_che_result : push_st = xoico_che_result_push_st_default;"
    "feature aware xoico_che_result : push_result_c = xoico_che_result_push_result_c_default;"
    "feature aware xoico_che_result : push_result_d = xoico_che_result_push_result_d_default;"
    "feature aware xoico_che_result : to_sink;"
    "feature aware xoico_che_result : set_parent_block = xoico_che_result_set_parent_block_default;"
    "feature aware xoico_che_result : create_st = xoico_che_result_create_st_default;"
"}";

st_s* xoico_che_result_create_st_default( const xoico_che_result* o )
{
    // xoico_che.h:49:5
    
    st_s* st = st_s_create();
    xoico_che_result_a_to_sink(o,((bcore_sink*)(st )));
    return  st;
}

xoico_che_result* xoico_che_result_create_block( sz_t level, bl_t is_using_blm )
{
    // xoico_che.h:160:5
    
    xoico_che_result_block_s* o = xoico_che_result_block_s_create();
    o->level = level;
    o->is_using_blm = is_using_blm;
    return ((xoico_che_result*)( o));
}

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_che_stack_var

BCORE_DEFINE_OBJECT_INST_P( xoico_che_stack_var_unit_s )
"aware bcore_inst"
"{"
    "sz_t level;"
    "tp_t name;"
    "xoico_typespec_s typespec;"
"}";

BCORE_DEFINE_OBJECT_INST_P( xoico_che_stack_var_unit_adl_s )
"aware x_array"
"{"
    "xoico_che_stack_var_unit_s => [];"
"}";

BCORE_DEFINE_OBJECT_INST_P( xoico_che_stack_var_s )
"aware xoico_che_stack_var"
"{"
    "xoico_che_stack_var_unit_adl_s adl;"
    "bcore_hmap_tpuz_s hmap_name;"
"}";

void xoico_che_stack_var_s_rehash_names( xoico_che_stack_var_s* o )
{
    // xoico_che.h:219:9
    
    bcore_hmap_tpuz_s_clear(&(o->hmap_name));
    for( sz_t i = 0; i < o->adl.size; i++ ) bcore_hmap_tpuz_s_set(&(o->hmap_name),o->adl.data[i]->name, i );
}

xoico_che_stack_var_s* xoico_che_stack_var_s_push_unit( xoico_che_stack_var_s* o, const xoico_che_stack_var_unit_s* unit )
{
    // xoico_che.h:225:9
    
    ((xoico_che_stack_var_unit_s*)(x_array_push_c(((x_array*)(&(o->adl))),((const x_inst*)(unit )))));
    bcore_hmap_tpuz_s_set(&(o->hmap_name),unit->name, o->adl.size - 1 );
    return  o;
}

xoico_che_stack_var_s* xoico_che_stack_var_s_pop_level( xoico_che_stack_var_s* o, sz_t level )
{
    // xoico_che.h:232:9
    
    sz_t size = o->adl.size;
    while( size > 0 && o->adl.data[ size - 1 ]->level >= level ) size--;
    ((xoico_che_stack_var_unit_adl_s*)(x_array_set_size(((x_array*)(&(o->adl))),size )));
    xoico_che_stack_var_s_rehash_names(o);
    return  o;
}

const xoico_typespec_s* xoico_che_stack_var_s_get_typespec( const xoico_che_stack_var_s* o, tp_t name )
{
    // xoico_che.h:241:9
    
    uz_t* p_idx = bcore_hmap_tpuz_s_get(&(o->hmap_name),name );
    if( !p_idx ) return  NULL;
    return &( o->adl.data[ (*(p_idx)) ]->typespec);
}

const sz_t xoico_che_stack_var_s_get_level( const xoico_che_stack_var_s* o, tp_t name )
{
    // xoico_che.h:249:9
    
    uz_t* p_idx = bcore_hmap_tpuz_s_get(&(o->hmap_name),name );
    if( !p_idx ) return  -1;
    return  o->adl.data[ (*(p_idx)) ]->level;
}

void xoico_che_stack_var_s_clear( xoico_che_stack_var_s* o )
{
    // xoico_che.h:256:9
    
    ((xoico_che_stack_var_unit_adl_s*)(x_array_clear(((x_array*)(&(o->adl))))));
    bcore_hmap_tpuz_s_clear(&(o->hmap_name));
}

XOILA_DEFINE_SPECT( xoico_che, xoico_che_stack_var )
"{"
    "bcore_spect_header_s header;"
"}";

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_che_stack_block

BCORE_DEFINE_OBJECT_INST_P( xoico_che_stack_block_unit_s )
"aware bcore_inst"
"{"
    "sz_t level;"
    "bl_t use_blm = false;"
    "bl_t break_ledge = false;"
"}";

BCORE_DEFINE_OBJECT_INST_P( xoico_che_stack_block_unit_adl_s )
"aware x_array"
"{"
    "xoico_che_stack_block_unit_s => [];"
"}";

BCORE_DEFINE_OBJECT_INST_P( xoico_che_stack_block_s )
"aware xoico_che_stack_block"
"{"
    "xoico_che_stack_block_unit_adl_s adl;"
"}";

xoico_che_stack_block_s* xoico_che_stack_block_s_pop( xoico_che_stack_block_s* o )
{
    // xoico_che.h:290:9
    
    ((xoico_che_stack_block_unit_adl_s*)(x_array_set_size(((x_array*)(&(o->adl))),sz_max( o->adl.size - 1, 0 ) )));
    return  o;
}

XOILA_DEFINE_SPECT( xoico_che, xoico_che_stack_block )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/

vd_t bcore_general_signal_handler( const bcore_signal_s* o );

vd_t xoico_xo_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "xoico_xo" ) ) )
    {
        case TYPEOF_init1:
        {

            // --------------------------------------------------------------------
            // source: xoico.h

            // group: xoico
            BCORE_REGISTER_NAME( mutable );
            BCORE_REGISTER_NAME( const );
            BCORE_REGISTER_NAME( void );
            BCORE_REGISTER_FEATURE( xoico_get_hash );
            BCORE_REGISTER_FEATURE( xoico_get_global_name_sc );
            BCORE_REGISTER_FEATURE( xoico_get_global_name_tp );
            BCORE_REGISTER_FFUNC( xoico_get_global_name_tp, xoico_get_global_name_tp_default );
            BCORE_REGISTER_FEATURE( xoico_parse );
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
            XOILA_REGISTER_SPECT( xoico );

            // group: xoico_host
            BCORE_REGISTER_FEATURE( xoico_host_parse_name );
            BCORE_REGISTER_FFUNC( xoico_host_parse_name, xoico_host_parse_name_default );
            BCORE_REGISTER_FEATURE( xoico_host_compiler );
            BCORE_REGISTER_FFUNC( xoico_host_compiler, xoico_host_compiler_default );
            BCORE_REGISTER_FEATURE( xoico_host_cengine );
            BCORE_REGISTER_FFUNC( xoico_host_cengine, xoico_host_cengine_default );
            BCORE_REGISTER_FEATURE( xoico_host_obj_type );
            BCORE_REGISTER_FFUNC( xoico_host_obj_type, xoico_host_obj_type_default );
            BCORE_REGISTER_FEATURE( xoico_host_create_spect_name );
            BCORE_REGISTER_FFUNC( xoico_host_create_spect_name, xoico_host_create_spect_name_default );
            XOILA_REGISTER_SPECT( xoico_host );

            // --------------------------------------------------------------------
            // source: xoico_name.h

            // group: xoico_name
            BCORE_REGISTER_FFUNC( xoico_parse, xoico_name_s_parse );
            BCORE_REGISTER_FFUNC( xoico_get_hash, xoico_name_s_get_hash );
            BCORE_REGISTER_FFUNC( xoico_get_global_name_tp, xoico_name_s_get_global_name_tp );
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
            // source: xoico_transient_map.h

            // group: xoico_transient_map
            BCORE_REGISTER_FFUNC( xoico_parse, xoico_transient_map_s_parse );
            BCORE_REGISTER_OBJECT( xoico_transient_map_s );
            XOILA_REGISTER_SPECT( xoico_transient_map );

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
            BCORE_REGISTER_FFUNC( xoico_get_global_name_tp, xoico_signature_s_get_global_name_tp );
            BCORE_REGISTER_FFUNC( xoico_get_hash, xoico_signature_s_get_hash );
            BCORE_REGISTER_FFUNC( xoico_parse, xoico_signature_s_parse );
            BCORE_REGISTER_OBJECT( xoico_signature_s );
            XOILA_REGISTER_SPECT( xoico_signature );

            // --------------------------------------------------------------------
            // source: xoico_body.h

            // group: xoico_body
            BCORE_REGISTER_FFUNC( xoico_parse, xoico_body_code_s_parse );
            BCORE_REGISTER_FFUNC( xoico_get_hash, xoico_body_code_s_get_hash );
            BCORE_REGISTER_OBJECT( xoico_body_code_s );
            BCORE_REGISTER_FFUNC( xoico_get_global_name_sc, xoico_body_s_get_global_name_sc );
            BCORE_REGISTER_FFUNC( xoico_get_hash, xoico_body_s_get_hash );
            BCORE_REGISTER_FFUNC( xoico_parse, xoico_body_s_parse );
            BCORE_REGISTER_OBJECT( xoico_body_s );
            XOILA_REGISTER_SPECT( xoico_body );

            // --------------------------------------------------------------------
            // source: xoico_feature.h

            // group: xoico_feature
            BCORE_REGISTER_FFUNC( xoico_get_global_name_tp, xoico_feature_s_get_global_name_tp );
            BCORE_REGISTER_FFUNC( xoico_get_hash, xoico_feature_s_get_hash );
            BCORE_REGISTER_FFUNC( xoico_parse, xoico_feature_s_parse );
            BCORE_REGISTER_FFUNC( xoico_finalize, xoico_feature_s_finalize );
            BCORE_REGISTER_FFUNC( xoico_expand_forward, xoico_feature_s_expand_forward );
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
            BCORE_REGISTER_FFUNC( xoico_parse, xoico_func_s_parse );
            BCORE_REGISTER_FFUNC( xoico_finalize, xoico_func_s_finalize );
            BCORE_REGISTER_FFUNC( xoico_expand_forward, xoico_func_s_expand_forward );
            BCORE_REGISTER_FFUNC( xoico_expand_declaration, xoico_func_s_expand_declaration );
            BCORE_REGISTER_FFUNC( xoico_expand_definition, xoico_func_s_expand_definition );
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
            BCORE_REGISTER_FFUNC( xoico_get_global_name_sc, xoico_group_s_get_global_name_sc );
            BCORE_REGISTER_FFUNC( xoico_get_global_name_tp, xoico_group_s_get_global_name_tp );
            BCORE_REGISTER_FFUNC( xoico_expand_setup, xoico_group_s_expand_setup );
            BCORE_REGISTER_FFUNC( xoico_host_compiler, xoico_group_s_compiler );
            BCORE_REGISTER_FFUNC( xoico_host_cengine, xoico_group_s_cengine );
            BCORE_REGISTER_FFUNC( xoico_host_obj_type, xoico_group_s_obj_type );
            BCORE_REGISTER_FFUNC( xoico_get_hash, xoico_group_s_get_hash );
            BCORE_REGISTER_FFUNC( xoico_host_create_spect_name, xoico_group_s_create_spect_name );
            BCORE_REGISTER_FFUNC( xoico_host_parse_name, xoico_group_s_parse_name );
            BCORE_REGISTER_FFUNC( xoico_parse, xoico_group_s_parse );
            BCORE_REGISTER_FFUNC( xoico_finalize, xoico_group_s_finalize );
            BCORE_REGISTER_OBJECT( xoico_group_s );
            XOILA_REGISTER_SPECT( xoico_group );

            // --------------------------------------------------------------------
            // source: xoico_stamp.h

            // group: xoico_stamp
            BCORE_REGISTER_FFUNC( xoico_get_hash, xoico_stamp_s_get_hash );
            BCORE_REGISTER_FFUNC( xoico_get_global_name_sc, xoico_stamp_s_get_global_name_sc );
            BCORE_REGISTER_FFUNC( xoico_get_global_name_tp, xoico_stamp_s_get_global_name_tp );
            BCORE_REGISTER_FFUNC( xoico_expand_setup, xoico_stamp_s_expand_setup );
            BCORE_REGISTER_FFUNC( xoico_expand_forward, xoico_stamp_s_expand_forward );
            BCORE_REGISTER_FFUNC( xoico_expand_indef_declaration, xoico_stamp_s_expand_indef_declaration );
            BCORE_REGISTER_FFUNC( xoico_host_parse_name, xoico_stamp_s_parse_name );
            BCORE_REGISTER_FFUNC( xoico_host_compiler, xoico_stamp_s_compiler );
            BCORE_REGISTER_FFUNC( xoico_host_cengine, xoico_stamp_s_cengine );
            BCORE_REGISTER_FFUNC( xoico_host_obj_type, xoico_stamp_s_obj_type );
            BCORE_REGISTER_FFUNC( xoico_parse, xoico_stamp_s_parse );
            BCORE_REGISTER_FFUNC( xoico_finalize, xoico_stamp_s_finalize );
            BCORE_REGISTER_FFUNC( xoico_expand_declaration, xoico_stamp_s_expand_declaration );
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
            BCORE_REGISTER_FFUNC( xoico_get_hash, xoico_source_s_get_hash );
            BCORE_REGISTER_FFUNC( xoico_finalize, xoico_source_s_finalize );
            BCORE_REGISTER_FFUNC( xoico_expand_declaration, xoico_source_s_expand_declaration );
            BCORE_REGISTER_FFUNC( xoico_expand_definition, xoico_source_s_expand_definition );
            BCORE_REGISTER_FFUNC( xoico_expand_init1, xoico_source_s_expand_init1 );
            BCORE_REGISTER_FFUNC( xoico_host_compiler, xoico_source_s_compiler );
            BCORE_REGISTER_FFUNC( xoico_parse, xoico_source_s_parse );
            BCORE_REGISTER_OBJECT( xoico_source_s );
            XOILA_REGISTER_SPECT( xoico_source );

            // --------------------------------------------------------------------
            // source: xoico_target.h

            // group: xoico_target
            BCORE_REGISTER_FFUNC( xoico_finalize, xoico_target_s_finalize );
            BCORE_REGISTER_FFUNC( xoico_expand_setup, xoico_target_s_expand_setup );
            BCORE_REGISTER_FFUNC( xoico_host_compiler, xoico_target_s_compiler );
            BCORE_REGISTER_FFUNC( xoico_host_cengine, xoico_target_s_cengine );
            BCORE_REGISTER_OBJECT( xoico_target_s );
            XOILA_REGISTER_SPECT( xoico_target );

            // --------------------------------------------------------------------
            // source: xoico_compiler.h

            // group: xoico_compiler
            BCORE_REGISTER_OBJECT( xoico_compiler_type_info_s );
            BCORE_REGISTER_OBJECT( xoico_compiler_element_info_s );
            BCORE_REGISTER_FFUNC( bcore_inst_call_init_x, xoico_compiler_s_init_x );
            BCORE_REGISTER_FFUNC( xoico_finalize, xoico_compiler_s_finalize );
            BCORE_REGISTER_FFUNC( xoico_expand_setup, xoico_compiler_s_expand_setup );
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
            // source: xoico_che.h

            // group: xoico_che
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
            BCORE_REGISTER_NAME( continue );
            BCORE_REGISTER_NAME( goto );
            BCORE_REGISTER_FFUNC( xoico_cengine_is_reserved, xoico_che_s_is_reserved );
            BCORE_REGISTER_FFUNC( xoico_cengine_translate, xoico_che_s_translate );
            BCORE_REGISTER_OBJECT( xoico_che_s );
            BCORE_REGISTER_FFUNC( xoico_che_result_set_parent_block, xoico_che_result_break_s_set_parent_block );
            BCORE_REGISTER_FFUNC( xoico_che_result_to_sink, xoico_che_result_break_s_to_sink );
            BCORE_REGISTER_OBJECT( xoico_che_result_break_s );
            BCORE_REGISTER_FFUNC( xoico_che_result_set_parent_block, xoico_che_result_return_s_set_parent_block );
            BCORE_REGISTER_FFUNC( xoico_che_result_to_sink, xoico_che_result_return_s_to_sink );
            BCORE_REGISTER_OBJECT( xoico_che_result_return_s );
            XOILA_REGISTER_SPECT( xoico_che );

            // group: xoico_che_result
            BCORE_REGISTER_FEATURE( xoico_che_result_clear );
            BCORE_REGISTER_FFUNC( xoico_che_result_clear, xoico_che_result_clear_default );
            BCORE_REGISTER_FEATURE( xoico_che_result_push_char );
            BCORE_REGISTER_FFUNC( xoico_che_result_push_char, xoico_che_result_push_char_default );
            BCORE_REGISTER_FEATURE( xoico_che_result_push_sc );
            BCORE_REGISTER_FFUNC( xoico_che_result_push_sc, xoico_che_result_push_sc_default );
            BCORE_REGISTER_FEATURE( xoico_che_result_push_st );
            BCORE_REGISTER_FFUNC( xoico_che_result_push_st, xoico_che_result_push_st_default );
            BCORE_REGISTER_FEATURE( xoico_che_result_push_result_c );
            BCORE_REGISTER_FFUNC( xoico_che_result_push_result_c, xoico_che_result_push_result_c_default );
            BCORE_REGISTER_FEATURE( xoico_che_result_push_result_d );
            BCORE_REGISTER_FFUNC( xoico_che_result_push_result_d, xoico_che_result_push_result_d_default );
            BCORE_REGISTER_FEATURE( xoico_che_result_to_sink );
            BCORE_REGISTER_FEATURE( xoico_che_result_set_parent_block );
            BCORE_REGISTER_FFUNC( xoico_che_result_set_parent_block, xoico_che_result_set_parent_block_default );
            BCORE_REGISTER_FEATURE( xoico_che_result_create_st );
            BCORE_REGISTER_FFUNC( xoico_che_result_create_st, xoico_che_result_create_st_default );
            BCORE_REGISTER_FFUNC( xoico_che_result_clear, xoico_che_result_plain_s_clear );
            BCORE_REGISTER_FFUNC( xoico_che_result_push_char, xoico_che_result_plain_s_push_char );
            BCORE_REGISTER_FFUNC( xoico_che_result_push_sc, xoico_che_result_plain_s_push_sc );
            BCORE_REGISTER_FFUNC( xoico_che_result_push_st, xoico_che_result_plain_s_push_st );
            BCORE_REGISTER_FFUNC( xoico_che_result_to_sink, xoico_che_result_plain_s_to_sink );
            BCORE_REGISTER_FFUNC( xoico_che_result_create_st, xoico_che_result_plain_s_create_st );
            BCORE_REGISTER_OBJECT( xoico_che_result_plain_s );
            BCORE_REGISTER_OBJECT( xoico_che_result_adl_s );
            BCORE_REGISTER_FFUNC( xoico_che_result_clear, xoico_che_result_arr_s_clear );
            BCORE_REGISTER_FFUNC( xoico_che_result_push_char, xoico_che_result_arr_s_push_char );
            BCORE_REGISTER_FFUNC( xoico_che_result_push_sc, xoico_che_result_arr_s_push_sc );
            BCORE_REGISTER_FFUNC( xoico_che_result_push_st, xoico_che_result_arr_s_push_st );
            BCORE_REGISTER_FFUNC( xoico_che_result_push_result_d, xoico_che_result_arr_s_push_result_d );
            BCORE_REGISTER_FFUNC( xoico_che_result_push_result_c, xoico_che_result_arr_s_push_result_c );
            BCORE_REGISTER_FFUNC( xoico_che_result_to_sink, xoico_che_result_arr_s_to_sink );
            BCORE_REGISTER_FFUNC( xoico_che_result_set_parent_block, xoico_che_result_arr_s_set_parent_block );
            BCORE_REGISTER_OBJECT( xoico_che_result_arr_s );
            BCORE_REGISTER_FFUNC( xoico_che_result_clear, xoico_che_result_block_s_clear );
            BCORE_REGISTER_FFUNC( xoico_che_result_push_char, xoico_che_result_block_s_push_char );
            BCORE_REGISTER_FFUNC( xoico_che_result_push_sc, xoico_che_result_block_s_push_sc );
            BCORE_REGISTER_FFUNC( xoico_che_result_push_st, xoico_che_result_block_s_push_st );
            BCORE_REGISTER_FFUNC( xoico_che_result_push_result_d, xoico_che_result_block_s_push_result_d );
            BCORE_REGISTER_FFUNC( xoico_che_result_push_result_c, xoico_che_result_block_s_push_result_c );
            BCORE_REGISTER_FFUNC( xoico_che_result_to_sink, xoico_che_result_block_s_to_sink );
            BCORE_REGISTER_FFUNC( xoico_che_result_set_parent_block, xoico_che_result_block_s_set_parent_block );
            BCORE_REGISTER_OBJECT( xoico_che_result_block_s );
            BCORE_REGISTER_FFUNC( xoico_che_result_to_sink, xoico_che_result_blm_init_s_to_sink );
            BCORE_REGISTER_OBJECT( xoico_che_result_blm_init_s );
            BCORE_REGISTER_FFUNC( xoico_che_result_to_sink, xoico_che_result_blm_down_s_to_sink );
            BCORE_REGISTER_OBJECT( xoico_che_result_blm_down_s );
            XOILA_REGISTER_SPECT( xoico_che_result );

            // group: xoico_che_stack_var
            BCORE_REGISTER_OBJECT( xoico_che_stack_var_unit_s );
            BCORE_REGISTER_OBJECT( xoico_che_stack_var_unit_adl_s );
            BCORE_REGISTER_OBJECT( xoico_che_stack_var_s );
            XOILA_REGISTER_SPECT( xoico_che_stack_var );

            // group: xoico_che_stack_block
            BCORE_REGISTER_OBJECT( xoico_che_stack_block_unit_s );
            BCORE_REGISTER_OBJECT( xoico_che_stack_block_unit_adl_s );
            BCORE_REGISTER_OBJECT( xoico_che_stack_block_s );
            XOILA_REGISTER_SPECT( xoico_che_stack_block );
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
// XOILA_OUT_SIGNATURE 0x80B7E1A8F2900ADBull
