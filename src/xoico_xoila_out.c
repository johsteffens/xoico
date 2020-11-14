/** This file was generated from xoila source code.
 *  Compiling Agent : xoico_compiler (C) 2020 J.B.Steffens
 *  Last File Update: 2020-11-14T16:25:26Z
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

er_t xoico_parse_f( bcore_source* source, sc_t format )
{
    // xoico.h:76:1
    
    return  bcore_source_a_parse_em_fa( source, format );
}

er_t xoico_embed_file_open( bcore_source* parent, sc_t file_name, bcore_source** include_source )
{
    // xoico.h:84:1
    BLM_INIT_LEVEL(0); {
    st_s* folder = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,bcore_file_folder_path(bcore_source_a_get_file( parent) )));
    if( folder->size == 0 ) st_s_push_char( folder,'.' );
    
    st_s* path = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    if( file_name[ 0 ] == '/' )
    {
        st_s_copy_sc( path,file_name );
    }
    else
    {
        st_s_copy_fa( path,"#<sc_t>/#<sc_t>", folder->sc, file_name );
    }
    
    if( !bcore_file_exists(path->sc ) )
    {
        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( parent,"Xoico: File '#<sc_t>' not found.", path->sc ))
    }
    
    *include_source = bcore_file_open_source(path->sc );
    BLM_RETURNV(er_t, 0)
    } /* try */
}

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

er_t xoico_forward_s_parse( xoico_forward_s* o, bcore_source* source )
{
    // xoico_forward.h:35:5
    BLM_INIT_LEVEL(0); {
    bcore_source_point_s_set( &(o->source_point),source );
    if( bcore_source_a_parse_bl_fa( source," #?':'" ) )
    {
        st_s* name = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
        BLM_TRY(bcore_source_a_parse_em_fa( source," #name", name ) )
        st_s_push_fa( &(o->name),"#<sc_t>#<sc_t>#<sc_t>", o->group->st_name.sc, name->sc[ 0 ] ? "_" : "", name->sc );
    }
    else
    {
        BLM_TRY(bcore_source_a_parse_em_fa( source," #name", &o->name ) )
    }
    if( o->name.size == 0 ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Feature: Name missing." ))
    BLM_TRY(bcore_source_a_parse_em_fa( source," ; " ) )
    BLM_RETURNV(er_t, 0)
    } /* try */
}

tp_t xoico_forward_s_get_hash( const xoico_forward_s* o )
{
    // xoico_forward.h:53:5
    
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
    hash = bcore_tp_fold_sc( hash, o->name.sc );
    return  hash;
}

er_t xoico_forward_s_expand_declaration( const xoico_forward_s* o, sz_t indent, bcore_sink* sink )
{
    // xoico_forward.h:62:5
     {
    bcore_sink_a_push_fa( sink,"#rn{ }##define TYPEOF_#<sc_t> 0x#pl16'0'{#X<tp_t>}ull\n", indent, o->name.sc, btypeof( o->name.sc ) );
    return  0;
    } /* try */
}

er_t xoico_forward_s_expand_forward( const xoico_forward_s* o, sz_t indent, bcore_sink* sink )
{
    // xoico_forward.h:68:5
     {
    bcore_sink_a_push_fa( sink," \\\n#rn{ }BCORE_FORWARD_OBJECT( #<sc_t> );", indent, o->name.sc );
    return  0;
    } /* try */
}

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
    // xoico_typespec.h:57:5
    
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

er_t xoico_arg_s_parse( xoico_arg_s* o, bcore_source* source )
{
    // xoico_arg.h:40:1
    BLM_INIT_LEVEL(0);
    {
        xoico_compiler_s* compiler = o->group->compiler;
        bcore_source_point_s_set( &(o->source_point),source );
        BLM_TRY(xoico_typespec_s_parse(&(o->typespec),o->group, source ))
    
        if( o->typespec.type == TYPEOF_void && o->typespec.indirection == 0 )
        {
            BLM_RETURNV(er_t, bcore_source_point_s_parse_error_fa( &(o->source_point),"'void' is misplaced here." ))
        }
    
        st_s* s = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
        bcore_source_a_parse_fa( source,"#name ", s );
        if( s->size == 0 ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Argument: Name expected." ))
        o->name = xoico_compiler_s_entypeof(compiler,s->sc );
    
        BLM_RETURNV(er_t, 0)
    } // try
}

tp_t xoico_arg_s_get_hash( const xoico_arg_s* o )
{
    // xoico_arg.h:62:1
    
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
    hash = bcore_tp_fold_tp( hash, xoico_typespec_s_get_hash(&(o->typespec)) );
    hash = bcore_tp_fold_tp( hash, o->name );
    return  hash;
}

er_t xoico_arg_s_relent( xoico_arg_s* o, tp_t tp_obj_type )
{
    // xoico_arg.h:70:1
    
    return  xoico_typespec_s_relent(&(o->typespec),o->group, tp_obj_type );
}

er_t xoico_arg_s_expand( const xoico_arg_s* o, sc_t sc_obj_type, bcore_sink* sink )
{
    // xoico_arg.h:75:1
    
    BLM_TRY(xoico_typespec_s_expand(&(o->typespec),o->group, sc_obj_type, sink ) )
    bcore_sink_a_push_fa( sink," " );
    xoico_arg_s_expand_name(o,sink );
    return  0;
}

er_t xoico_arg_s_expand_name( const xoico_arg_s* o, bcore_sink* sink )
{
    // xoico_arg.h:83:1
    
    bcore_sink_a_push_fa( sink,"#<sc_t>", xoico_compiler_s_nameof(o->group->compiler,o->name ) );
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
"aware bcore_array"
"{"
    "xoico_arg_s [];"
    "hidden aware xoico_group_s* group;"
    "func xoico:parse;"
    "func xoico:get_hash;"
"}";

er_t xoico_args_s_append( xoico_args_s* o, bcore_source* source )
{
    // xoico_args.h:40:1
    
    {
        bl_t first = true;
        while( !bcore_source_a_parse_bl_fa( source," #=?')' " ) ) // args follow
        {
            if( !first ) BLM_TRY(xoico_parse_f(source, " , " ))
            xoico_arg_s* arg = xoico_arg_s_create();
            arg->group = o->group;
            BLM_TRY(xoico_arg_s_parse(arg,source ))
            xoico_args_s_push_d( o,arg );
            first = false;
        }
    }
    return  0;
}

er_t xoico_args_s_relent( xoico_args_s* o, tp_t tp_obj_type )
{
    // xoico_args.h:58:1
    
    {const xoico_args_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_arg_s* arg=&(__a->data[__i]); BLM_TRY(xoico_arg_s_relent(arg,tp_obj_type ))
    }}return  0;
}

er_t xoico_args_s_expand( const xoico_args_s* o, bl_t first, sc_t sc_obj_type, bcore_sink* sink )
{
    // xoico_args.h:64:1
    
    {const xoico_args_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_arg_s* arg=&(__a->data[__i]);
    {
        if( !first ) bcore_sink_a_push_fa( sink,", " );
        first = false;
        BLM_TRY(xoico_arg_s_expand(arg,sc_obj_type, sink ))
    }
    }}return  0;
}

er_t xoico_args_s_expand_name( const xoico_args_s* o, bl_t first, bcore_sink* sink )
{
    // xoico_args.h:75:1
    
    {const xoico_args_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_arg_s* arg=&(__a->data[__i]);
    {
        if( !first ) bcore_sink_a_push_fa( sink,", " );
        first = false;
        BLM_TRY(xoico_arg_s_expand_name(arg,sink ))
    }
    }}return  0;
}

tp_t xoico_args_s_get_hash( const xoico_args_s* o )
{
    // xoico_args.h:86:1
    
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
    {const xoico_args_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_arg_s* arg=&(__a->data[__i]); hash = bcore_tp_fold_tp( hash, xoico_arg_s_get_hash(arg) );}}
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
#include "xoico_stamp.h"
#include "xoico_cengine.h"

BCORE_DEFINE_OBJECT_INST_P( xoico_body_code_s )
"aware xoico_body"
"{"
    "bl_t single_line;"
    "tp_t hash_source;"
    "bcore_source_point_s source_point;"
    "hidden aware xoico_group_s* group;"
    "hidden aware xoico_stamp_s* stamp;"
    "func xoico:get_hash;"
"}";

er_t xoico_body_code_s_parse( xoico_body_code_s* o, bcore_source* source )
{
    // xoico_body.x:21:1
     {
    if( !o->group ) return  bcore_source_a_parse_error_fa( source,"xoico_body_code_s: Code has no group assigned." );
    
    tp_t hash = bcore_tp_init();
    
    bcore_source_point_s_set( &(o->source_point),source );
    
    BLM_TRY(bcore_source_a_parse_em_fa( source," {" ) )
    
    sz_t nest_count = 1;
    bl_t exit_loop = false;
    o->single_line = true;
    
    while( bcore_source_a_parse_bl_fa( source,"#?' '" ) ); // skip leading spaces
    
    while( !bcore_source_a_eos( source) && !exit_loop )
    {
        u0_t c =  bcore_source_a_get_u0( source);
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
                while( !bcore_source_a_eos( source) && ((c = bcore_source_a_get_char( source)) != '"') )
                {
                    hash = bcore_tp_fold_u0( hash, c );
                    if( c == '\\' ) hash = bcore_tp_fold_u0( hash, bcore_source_a_get_u0( source) );
                    if( c == '\n' ) return  bcore_source_a_parse_error_fa( source,"Newline in string literal." );
                }
                c = 0;
            }
            break;
    
            case '\'': // char literal
            {
                hash = bcore_tp_fold_u0( hash, c );
                while( !bcore_source_a_eos( source) && ((c = bcore_source_a_get_char( source)) != '\'') )
                {
                    hash = bcore_tp_fold_u0( hash, c );
                    if( c == '\\' ) hash = bcore_tp_fold_u0( hash, bcore_source_a_get_u0( source ) );
                    if( c == '\n' ) return  bcore_source_a_parse_error_fa( source,"Newline in char literal." );
                }
                c = 0;
            }
            break;
    
            case '/': // comment
            {
                hash = bcore_tp_fold_u0( hash, c );
                if( bcore_source_a_inspect_char( source) == '/' )
                {
                    while( !bcore_source_a_eos( source) )
                    {
                        c = bcore_source_a_get_char( source);
                        hash = bcore_tp_fold_u0( hash, c );
                        if( c == '\n' )
                        {
                            o->single_line = false;
                            break;
                        }
                    }
                }
                else if( bcore_source_a_inspect_char( source) == '*' )
                {
                    while( !bcore_source_a_eos( source) )
                    {
                        if( bcore_source_a_parse_bl_fa( source,"#?'*/'" ) )
                        {
                            hash = bcore_tp_fold_sc( hash, "*/" );
                            break;
                        }
                        else
                        {
                            c = bcore_source_a_get_char( source);
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
    } /* try */
}

tp_t xoico_body_code_s_get_hash( const xoico_body_code_s* o )
{
    // xoico_body.x:139:1
    
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
    "hidden aware xoico_group_s* group;"
    "hidden aware xoico_stamp_s* stamp;"
    "func xoico:get_global_name_sc;"
    "func xoico:get_hash;"
"}";

er_t xoico_body_s_set_group( xoico_body_s* o, xoico_group_s* group )
{
    // xoico_body.x:152:1
    
    if( !o->group ) o->group = group;
    if( o->code && !o->code->group ) o->code->group = group;
    return  0;
}

er_t xoico_body_s_set_stamp( xoico_body_s* o, xoico_stamp_s* stamp )
{
    // xoico_body.x:161:1
    
    o->stamp = stamp;
    if( o->code ) o->code->stamp = stamp;
    return  0;
}

tp_t xoico_body_s_get_hash( const xoico_body_s* o )
{
    // xoico_body.x:170:1
    
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
    hash = bcore_tp_fold_sc( hash, o->name.sc );
    if( o->code ) hash = bcore_tp_fold_tp( hash, xoico_body_code_s_get_hash(o->code) );
    hash = bcore_tp_fold_bl( hash, o->go_inline );
    return  hash;
}

er_t xoico_body_s_parse_expression( xoico_body_s* o, bcore_source* source )
{
    // xoico_body.x:181:1
    BLM_INIT_LEVEL(0); {
    if( bcore_source_a_parse_bl_fa( source," #=?'{'" ) )
    {
        xoico_body_code_s_attach( &(o->code ),  xoico_body_code_s_create());
        o->code->group = o->group;
        o->code->stamp = o->stamp;
        BLM_TRY(xoico_body_code_s_parse(o->code,source ))
        o->go_inline = o->code->single_line;
    }
    else
    {
        xoico_compiler_s* compiler = o->group->compiler;
        st_s* st_name = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
        BLM_TRY(xoico_group_s_parse_name(o->group,st_name, source ))
    
        if( st_name->size == 0 ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Body name expected." ))
    
        if( o->stamp ) st_s_replace_sc_sc( st_name,"@", o->stamp->st_name.sc );
    
        tp_t tp_name = xoico_compiler_s_entypeof(compiler,st_name->sc );
    
        // if name_buf refers to another body
        if( xoico_compiler_s_is_item(compiler,tp_name ) )
        {
            const xoico* item = xoico_compiler_s_get_const_item(compiler,tp_name );
            if( item->_ == TYPEOF_xoico_body_s )
            {
                const xoico_body_s* body = ((xoico_body_s*)(item));
                xoico_body_code_s_attach( &(o->code ),  xoico_body_code_s_clone(body->code));
                if( o->code )
                {
                    o->code->group = body->code->group;
                    o->code->stamp = body->code->stamp;
                }
                o->go_inline = body->go_inline;
            }
        }
        else
        {
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Cannot resolve body name '#<sc_t>'\n", st_name->sc ))
        }
    }
    BLM_RETURNV(er_t, 0)
    
    } /* try */
}

er_t xoico_body_s_parse( xoico_body_s* o, bcore_source* source )
{
    // xoico_body.x:230:1
    BLM_INIT_LEVEL(0); {
    if( !o->group ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Body has no group assigned." ))
    st_s* string = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    bcore_source_point_s_set( &(o->source_point),source );
    
    if( !bcore_source_a_parse_bl_fa( source," #=?'='" ) )
    {
        BLM_TRY(bcore_source_a_parse_em_fa( source," #name", string ) )
        if( string->size == 0 ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Body name expected." ))
        st_s_push_fa( &(o->name),"#<sc_t>", string->sc );
    }
    
    BLM_TRY(bcore_source_a_parse_em_fa( source," =" ) )
    xoico_body_s_parse_expression(o,source );
    st_s_copy_fa( &(o->global_name),"#<sc_t>_#<sc_t>", o->group->st_name.sc, o->name.sc );
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_body_s_expand( const xoico_body_s* o, const xoico_signature_s* signature, sz_t indent, bcore_sink* sink )
{
    // xoico_body.x:251:1
    BLM_INIT_LEVEL(0); {
    const st_s* final_code = NULL;
    st_s* st_out = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    
    xoico_cengine* cengine = o->group->xoico_source->target->cengine;
    ASSERT( cengine );
    
    if( o->code )
    {
        if( !o->group ) BLM_RETURNV(er_t, bcore_source_point_s_parse_error_fa( &(o->source_point),"Body has no group assigned." ))
        BLM_TRY(xoico_cengine_a_translate(cengine,o, signature, ( bcore_sink* )st_out ))
        final_code = st_out;
    }
    
    if( o->go_inline )
    {
        bcore_sink_a_push_fa( sink,"{#<sc_t>}", final_code->sc );
    }
    else
    {
        bcore_sink_a_push_fa( sink,"{\n#rn{ }", indent + 4 );
        for( sz_t i = 0; i < final_code->size; i++ )
        {
            char c = final_code->sc[ i ];
            bcore_sink_a_push_char( sink,c );
            if( c == '\n' ) bcore_sink_a_push_fa( sink,"#rn{ }", indent + 4 );
        }
        bcore_sink_a_push_fa( sink,"\n#rn{ }}", indent );
    }
    BLM_RETURNV(er_t, 0)
    } /* try */
}

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
    "func xoico:get_global_name_sc;"
    "func xoico:get_hash;"
    "func xoico:parse;"
    "func xoico:expand_indef_typedef;"
    "func xoico:expand_spect_declaration;"
    "func xoico:expand_spect_definition;"
    "func xoico:expand_indef_declaration;"
    "func xoico:expand_definition;"
    "func xoico:expand_init1;"
"}";

sc_t xoico_feature_s_get_global_name_sc( const xoico_feature_s* o )
{
    // xoico_feature.h:57:5
    
    return  xoico_compiler_s_nameof(o->group->compiler,o->signature.global_name );
}

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

er_t xoico_feature_s_parse( xoico_feature_s* o, bcore_source* source )
{
    // xoico_feature.x:36:1
    BLM_INIT_LEVEL(0); {
    xoico_compiler_s* compiler = o->group->compiler;
    
    bcore_source_point_s_set( &(o->source_point),source );
    o->strict = bcore_source_a_parse_bl_fa( source," #?w'strict' " );
    
    if( bcore_source_a_parse_bl_fa( source," #?|'|" ) )
    {
        st_s* flags = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
        BLM_TRY(bcore_source_a_parse_em_fa( source," #until'''", flags ) )
        for( sz_t i = 0; i < flags->size; i++ )
        {
            switch( flags->data[ i ] )
            {
                case 'p': o->flag_p = true; break;
                case 't': o->flag_t = true; break;
                case 'a': o->flag_a = true; break;
                case 'r': o->flag_r = true; break;
                default: BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Feature: Flag '#<char>' not handled. Choose from 'ptar'.", flags->data[ i ] ))
            }
        }
        BLM_TRY(bcore_source_a_parse_em_fa( source,"' " ) )
    }
    else
    {
        /// the default feature is an aware one
        o->flag_a = true;
    }
    
    xoico_signature_s* signature =&( o->signature);
    
    signature->group = o->group;
    BLM_TRY(xoico_signature_s_parse(signature,source ))
    
    if( !signature->arg_o )
    {
        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Feature: The first argument must be 'mutable' or 'const'." ))
    }
    
    if( bcore_source_a_parse_bl_fa( source," #?'=' " ) )
    {
        if( bcore_source_a_parse_bl_fa( source," #=?'{' " ) )
        {
            if( o->strict ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Feature is 'strict'. Default function would have no effect." ))
            o->default_body = xoico_body_s_create();
            BLM_TRY(xoico_body_s_set_group(o->default_body,o->group ))
            bcore_source_point_s_set( &(o->default_body->source_point),source );
            BLM_TRY(xoico_body_s_parse_expression(o->default_body,source ))
            st_s_copy_fa( &(o->st_default_func_name),"#<sc_t>_default", xoico_compiler_s_nameof(compiler,o->signature.name ) );
        }
        else
        {
            if( o->strict )  BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Feature is 'strict'. Default function would have no effect." ))
            BLM_TRY(bcore_source_a_parse_em_fa( source," #name ", &o->st_default_func_name ) )
            if( o->st_default_func_name.size == 0 ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Feature: Default function name expected." ))
            if( st_s_equal_sc( &(o->st_default_func_name),xoico_compiler_s_nameof(compiler,o->signature.name ) ) )
            {
                BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Feature: Default function name must differ from feature name." ))
            }
        }
    }
    
    BLM_TRY(bcore_source_a_parse_em_fa( source," ; " ) )
    
    sc_t sc_name = xoico_compiler_s_nameof(compiler,o->signature.name );
    sc_t sc_group_name = o->group->st_name.sc;
    
    if( o->flag_a )
    {
        o->func_a = xoico_func_s_create();
        o->func_a->group = o->group;
        o->func_a->name = o->signature.name;
        st_s* name_buf = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
        st_s_copy_fa( name_buf,"#<sc_t>_a_#<sc_t>", sc_group_name, sc_name );
        o->func_a->global_name = xoico_compiler_s_entypeof(compiler,name_buf->sc );
        o->func_a->signature_global_name = o->signature.global_name;
        o->func_a->expandable = false;
        o->func_a->signature = &o->signature;
        bcore_source_point_s_copy( &(o->func_a->source_point),&o->source_point );
        BLM_TRY(xoico_compiler_s_register_func(compiler,o->func_a ))
    }
    
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_feature_s_expand_indef_typedef( const xoico_feature_s* o, sz_t indent, bcore_sink* sink )
{
    // xoico_feature.x:124:1
     {
    if( !o->expandable ) return  0;
    xoico_compiler_s* compiler = o->group->compiler;
    bcore_sink_a_push_fa( sink," \\\n#rn{ }  typedef ", indent );
    BLM_TRY(xoico_typespec_s_expand(&(o->signature.typespec_ret),o->group, o->group->st_name.sc, sink ))
    bcore_sink_a_push_fa( sink," (*#<sc_t>_#<sc_t>)(", o->group->st_name.sc, xoico_compiler_s_nameof(compiler,o->signature.name ) );
    if( o->signature.arg_o == TYPEOF_const ) bcore_sink_a_push_fa( sink," const" );
    bcore_sink_a_push_fa( sink," #<sc_t>* o", o->group->st_name.sc );
    BLM_TRY(xoico_args_s_expand(&(o->signature.args),false, o->group->st_name.sc, sink ))
    bcore_sink_a_push_fa( sink," );" );
    return  0;
    } /* try */
}

er_t xoico_feature_s_expand_spect_declaration( const xoico_feature_s* o, sz_t indent, bcore_sink* sink )
{
    // xoico_feature.x:140:1
     {
    if( !o->expandable ) return  0;
    xoico_compiler_s* compiler = o->group->compiler;
    bcore_sink_a_push_fa( sink," \\\n#rn{ }#<sc_t> #<sc_t>;", indent, xoico_compiler_s_nameof(compiler,o->signature.global_name ), xoico_compiler_s_nameof(compiler,o->signature.name ) );
    return  0;
    } /* try */
}

er_t xoico_feature_s_expand_spect_definition( const xoico_feature_s* o, sz_t indent, bcore_sink* sink )
{
    // xoico_feature.x:150:1
     {
    if( !o->expandable ) return  0;
    xoico_compiler_s* compiler = o->group->compiler;
    bcore_sink_a_push_fa( sink,"#rn{ }\"feature ", indent );
    if( o->strict ) bcore_sink_a_push_fa( sink,"strict " );
    if( o->flag_a ) bcore_sink_a_push_fa( sink,"aware " );
    
    bcore_sink_a_push_fa( sink,"#<sc_t> : #<sc_t>", o->group->st_name.sc, xoico_compiler_s_nameof(compiler,o->signature.name ) );
    if( o->st_default_func_name.size > 0 )
    {
        bcore_sink_a_push_fa( sink," = #<sc_t>_#<sc_t>", o->group->st_name.sc, o->st_default_func_name.sc );
    }
    bcore_sink_a_push_fa( sink,";\"\n" );
    return  0;
    } /* try */
}

er_t xoico_feature_s_expand_indef_declaration( const xoico_feature_s* o, sz_t indent, bcore_sink* sink )
{
    // xoico_feature.x:169:1
    BLM_INIT_LEVEL(0); {
    if( !o->expandable ) BLM_RETURNV(er_t, 0)
    xoico_compiler_s* compiler = o->group->compiler;
    
    sc_t sc_name         = xoico_compiler_s_nameof(compiler,o->signature.name );
    sc_t sc_group_name   = o->group->st_name.sc;
    
    st_s* st_ret_typespec = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    st_s* st_spect_name = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,xoico_group_s_create_spect_name(o->group)));
    sc_t sc_spect_name = st_spect_name->sc;
    
    BLM_TRY(xoico_typespec_s_expand(&(o->signature.typespec_ret),o->group, sc_group_name, ((bcore_sink*)(st_ret_typespec)) ))
    bl_t has_ret = ( o->signature.typespec_ret.type != TYPEOF_void );
    
    sc_t sc_ret_typespec = st_ret_typespec->sc;
    sc_t sc_default_func_name = o->st_default_func_name.sc;
    bl_t flag_const = o->signature.arg_o == TYPEOF_const;
    
    if( o->flag_p )
    {
        bcore_sink_a_push_fa( sink," \\\n#rn{ }  static inline #<sc_t> #<sc_t>_p_#<sc_t>( const #<sc_t>* __p,",
            indent,
            sc_ret_typespec,
            sc_group_name,
            sc_name,
            sc_spect_name
        );
    
        if( flag_const ) bcore_sink_a_push_fa( sink," const" );
        bcore_sink_a_push_fa( sink," #<sc_t>* o", sc_group_name );
        BLM_TRY(xoico_args_s_expand(&(o->signature.args),false, sc_group_name, sink ))
        bcore_sink_a_push_fa( sink," ) { " );
        bcore_sink_a_push_fa( sink,"assert( __p->#<sc_t> ); ", sc_name );
        if( has_ret ) bcore_sink_a_push_fa( sink,"return " );
        bcore_sink_a_push_fa( sink,"__p->#<sc_t>( o", sc_name );
        BLM_TRY(xoico_args_s_expand_name(&(o->signature.args),false, sink ))
        bcore_sink_a_push_fa( sink," ); }" );
    }
    
    if( o->flag_t )
    {
        bcore_sink_a_push_fa( sink," \\\n#rn{ }  static inline #<sc_t> #<sc_t>_t_#<sc_t>( tp_t __t,",
            indent,
            sc_ret_typespec,
            sc_group_name,
            sc_name,
            sc_group_name
        );
    
        if( flag_const ) bcore_sink_a_push_fa( sink," const" );
        bcore_sink_a_push_fa( sink," #<sc_t>* o", sc_group_name );
        BLM_TRY(xoico_args_s_expand(&(o->signature.args),false, sc_group_name, sink ))
        bcore_sink_a_push_fa( sink," ) { " );
        bcore_sink_a_push_fa( sink,"const #<sc_t>* p = #<sc_t>_get_typed( __t ); ", sc_spect_name, sc_spect_name );
        bcore_sink_a_push_fa( sink,"assert( p->#<sc_t> ); ", sc_name );
        if( has_ret ) bcore_sink_a_push_fa( sink,"return " );
        bcore_sink_a_push_fa( sink,"p->#<sc_t>( o", sc_name );
        BLM_TRY(xoico_args_s_expand_name(&(o->signature.args),false, sink ))
        bcore_sink_a_push_fa( sink," ); }" );
    }
    
    if( o->flag_a )
    {
        bcore_sink_a_push_fa( sink," \\\n#rn{ }  static inline #<sc_t> #<sc_t>_a_#<sc_t>(",
            indent,
            sc_ret_typespec,
            sc_group_name,
            sc_name
        );
    
        if( flag_const ) bcore_sink_a_push_fa( sink," const" );
        bcore_sink_a_push_fa( sink," #<sc_t>* o", sc_group_name );
        BLM_TRY(xoico_args_s_expand(&(o->signature.args),false, sc_group_name, sink ))
        bcore_sink_a_push_fa( sink," ) { " );
        bcore_sink_a_push_fa( sink,"const #<sc_t>* p = #<sc_t>_get_aware( o ); ", sc_spect_name, sc_spect_name );
        bcore_sink_a_push_fa( sink,"assert( p->#<sc_t> ); ", sc_name );
        if( has_ret ) bcore_sink_a_push_fa( sink,"return " );
        bcore_sink_a_push_fa( sink,"p->#<sc_t>( o", sc_name );
        BLM_TRY(xoico_args_s_expand_name(&(o->signature.args),false, sink ))
        bcore_sink_a_push_fa( sink," ); }" );
    }
    
    if( o->flag_r )
    {
        bcore_sink_a_push_fa( sink," \\\n#rn{ }  static inline #<sc_t> #<sc_t>_r_#<sc_t>(",
            indent,
            sc_ret_typespec,
            sc_group_name,
            sc_name
        );
    
        bcore_sink_a_push_fa( sink," const sr_s* o" );
        BLM_TRY(xoico_args_s_expand(&(o->signature.args),false, sc_group_name, sink ))
        bcore_sink_a_push_fa( sink," ) { " );
        if( !flag_const ) bcore_sink_a_push_fa( sink,"ASSERT( !sr_s_is_const( o ) ); ", indent );
        bcore_sink_a_push_fa( sink,"const #<sc_t>* p = (const #<sc_t>*)ch_spect_p( o->p, TYPEOF_#<sc_t> ); ",
            sc_spect_name,
            sc_spect_name,
            sc_spect_name
        );
    
        bcore_sink_a_push_fa( sink,"assert( p->#<sc_t> ); ", sc_name );
        if( has_ret ) bcore_sink_a_push_fa( sink,"return " );
        bcore_sink_a_push_fa( sink,"p->#<sc_t>( o->o", sc_name );
        BLM_TRY(xoico_args_s_expand_name(&(o->signature.args),false, sink ))
        bcore_sink_a_push_fa( sink," ); }" );
    }
    
    if( o->flag_p )
    {
        bcore_sink_a_push_fa( sink," \\\n#rn{ }  static inline bl_t #<sc_t>_p_defines_#<sc_t>( const #<sc_t>* __p ) ",
            indent,
            sc_group_name,
            sc_name,
            sc_spect_name
        );
    
        if( o->strict || o->default_body || o->st_default_func_name.size > 0 )
        {
            bcore_sink_a_push_fa( sink,"{ return true; }", sc_name );
        }
        else
        {
            bcore_sink_a_push_fa( sink,"{ return __p->#<sc_t> != NULL; }", sc_name );
        }
    }
    
    if( o->flag_t )
    {
        bcore_sink_a_push_fa( sink," \\\n#rn{ }  static inline bl_t #<sc_t>_t_defines_#<sc_t>( tp_t __t ) ",
            indent,
            sc_group_name,
            sc_name
        );
    
        if( o->strict || o->default_body || o->st_default_func_name.size > 0 )
        {
            bcore_sink_a_push_fa( sink,"{ return true; }", sc_name );
        }
        else
        {
            bcore_sink_a_push_fa( sink,"{ return #<sc_t>_get_typed( __t )->#<sc_t> != NULL; }", sc_spect_name, sc_name );
        }
    }
    
    if( o->flag_a )
    {
        bcore_sink_a_push_fa( sink," \\\n#rn{ }  static inline bl_t #<sc_t>_a_defines_#<sc_t>( const #<sc_t>* o ) ",
            indent,
            sc_group_name,
            sc_name,
            sc_group_name
        );
    
        if( o->strict || o->default_body || o->st_default_func_name.size > 0 )
        {
            bcore_sink_a_push_fa( sink,"{ return true; }", sc_name );
        }
        else
        {
            bcore_sink_a_push_fa( sink,"{ return #<sc_t>_get_aware( o )->#<sc_t> != NULL; }", sc_spect_name, sc_name );
        }
    }
    
    if( o->flag_r )
    {
        bcore_sink_a_push_fa( sink," \\\n#rn{ }  static inline bl_t #<sc_t>_r_defines_#<sc_t>( const sr_s* o ) ",
            indent,
            sc_group_name,
            sc_name
        );
    
        if( o->strict || o->default_body || o->st_default_func_name.size > 0 )
        {
            bcore_sink_a_push_fa( sink,"{ return true; }", sc_name );
        }
        else
        {
            bcore_sink_a_push_fa( sink,"{ return ( (#<sc_t>*)ch_spect_p( o->p, TYPEOF_#<sc_t> ) )->#<sc_t> != NULL; }", sc_spect_name, sc_spect_name, sc_name );
        }
    }
    
    if( o->st_default_func_name.size > 0 )
    {
        if( o->default_body && o->default_body->go_inline )
        {
            bcore_sink_a_push_fa( sink," \\\n#rn{ }  static inline #<sc_t> #<sc_t>_#<sc_t>(",
                indent,
                sc_ret_typespec,
                sc_group_name,
                sc_default_func_name
            );
    
            if( flag_const ) bcore_sink_a_push_fa( sink," const" );
            bcore_sink_a_push_fa( sink," #<sc_t>* o", sc_group_name );
            BLM_TRY(xoico_args_s_expand(&(o->signature.args),false, sc_group_name, sink ))
            bcore_sink_a_push_fa( sink," )" );
            BLM_TRY(xoico_body_s_expand(o->default_body,&o->signature, indent, sink ))
        }
        else
        {
            bcore_sink_a_push_fa( sink," \\\n#rn{ }  #<sc_t> #<sc_t>_#<sc_t>(", indent, sc_ret_typespec, sc_group_name, sc_default_func_name );
            if( flag_const ) bcore_sink_a_push_fa( sink," const" );
            bcore_sink_a_push_fa( sink," #<sc_t>* o", sc_group_name );
            BLM_TRY(xoico_args_s_expand(&(o->signature.args),false, sc_group_name, sink ))
            bcore_sink_a_push_fa( sink," );" );
        }
    }
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_feature_s_expand_definition( const xoico_feature_s* o, sz_t indent, bcore_sink* sink )
{
    // xoico_feature.x:403:1
    BLM_INIT_LEVEL(0); {
    if( !o->expandable ) BLM_RETURNV(er_t, 0)
    if( o->default_body && !o->default_body->go_inline )
    {
        sc_t sc_group_name = o->group->st_name.sc;
        st_s* st_ret_typespec = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
        BLM_TRY(xoico_typespec_s_expand(&(o->signature.typespec_ret),o->group, sc_group_name, ((bcore_sink*)(st_ret_typespec)) ))
    
        bcore_sink_a_push_fa( sink,"\n" );
        bcore_sink_a_push_fa( sink,"\n#<sc_t> #<sc_t>_#<sc_t>(", st_ret_typespec->sc, sc_group_name, o->st_default_func_name.sc );
        if( o->signature.arg_o == TYPEOF_const ) bcore_sink_a_push_fa( sink," const" );
        bcore_sink_a_push_fa( sink," #<sc_t>* o", sc_group_name );
        BLM_TRY(xoico_args_s_expand(&(o->signature.args),false, sc_group_name, sink ))
        bcore_sink_a_push_fa( sink," )\n" );
        BLM_TRY(xoico_body_s_expand(o->default_body,&o->signature, indent, sink ))
    }
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_feature_s_expand_init1( const xoico_feature_s* o, sz_t indent, bcore_sink* sink )
{
    // xoico_feature.x:425:1
     {
    if( !o->expandable ) return  0;
    xoico_compiler_s* compiler = o->group->compiler;
    sc_t sc_global_name = xoico_compiler_s_nameof(compiler,o->signature.global_name );
    
    bcore_sink_a_push_fa( sink,"#rn{ }BCORE_REGISTER_FEATURE( #<sc_t> );\n", indent, sc_global_name );
    if( o->st_default_func_name.size > 0 )
    {
        bcore_sink_a_push_fa( sink,"#rn{ }BCORE_REGISTER_FFUNC( #<sc_t>, #<sc_t>_#<sc_t> );\n",
            indent,
            sc_global_name,
            o->group->st_name.sc,
            o->st_default_func_name.sc
        );
    }
    return  0;
    } /* try */
}

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
    "hidden aware xoico_signature_s* signature;"
    "hidden aware xoico_group_s* group;"
    "hidden aware xoico_stamp_s* stamp;"
    "bcore_source_point_s source_point;"
    "func xoico:expand_forward;"
    "func xoico:expand_declaration;"
    "func xoico:expand_definition;"
"}";

tp_t xoico_func_s_get_hash( const xoico_func_s* o )
{
    // xoico_func.x:21:1
    
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o->_ );
    hash = bcore_tp_fold_tp( hash, o->pre_hash );
    hash = bcore_tp_fold_tp( hash, o->name );
    hash = bcore_tp_fold_sc( hash, o->flect_decl.sc );
    hash = bcore_tp_fold_tp( hash, o->signature_global_name );
    hash = bcore_tp_fold_bl( hash, o->overloadable );
    hash = bcore_tp_fold_bl( hash, o->expandable );
    if( o->body ) hash = bcore_tp_fold_tp( hash, xoico_body_s_get_hash( o->body ) );
    return  hash;
}

er_t xoico_func_s_set_global_name( xoico_func_s* o )
{
    // xoico_func.x:36:1
    BLM_INIT_LEVEL(0); {
    st_s* st_global_name = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    
    xoico_compiler_s* compiler = o->group->compiler;
    sc_t sc_name = xoico_compiler_s_nameof(compiler,o->name );
    
    if( o->stamp )
    {
        st_s_push_fa( st_global_name,"#<sc_t>_#<sc_t>", o->stamp->st_name.sc, sc_name );
    }
    else
    {
        st_s_push_fa( st_global_name,"#<sc_t>_#<sc_t>", o->group->st_name.sc, sc_name );
    }
    
    o->global_name = xoico_compiler_s_entypeof(compiler,st_global_name->sc );
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_func_s_parse( xoico_func_s* o, bcore_source* source )
{
    // xoico_func.x:58:1
    BLM_INIT_LEVEL(0); {
    xoico_compiler_s* compiler = o->group->compiler;
    
    // global name signature
    st_s* st_type = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    bcore_source_point_s_set( &(o->source_point),source );
    
    st_s_push_sc( &(o->flect_decl),"func " );
    
    st_s* st_name = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    
    if( bcore_source_a_parse_bl_fa( source," #?'('" ) )
    {
        xoico_signature_s* signature = xoico_signature_s_create();
        BLM_TRY(xoico_compiler_s_life_a_push(compiler,((bcore_inst*)(signature)) ))
    
        signature->group = o->group;
        signature->stamp = o->stamp;
    
        BLM_TRY(xoico_signature_s_parse(signature,source ))
    
        if( signature->arg_o )
        {
            if( !o->stamp ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Signature specifies a member-function. A plain function was expected at this point." ))
        }
    
        BLM_TRY(bcore_source_a_parse_em_fa( source," ) " ) )
    
        xoico_compiler_s_register_item(compiler,((xoico*)(signature)), source );
    
        o->pre_hash = bcore_tp_fold_tp( o->pre_hash, xoico_signature_s_get_hash(signature) );
    
        if( o->stamp )
        {
            st_s_copy(st_type,&o->stamp->st_name );
        }
        else
        {
            st_s_copy(st_type,&o->group->st_name );
        }
    
        st_s_copy_sc( st_name,xoico_compiler_s_nameof(compiler,signature->name ) );
        st_s_push_fa( &(o->flect_decl),"#<sc_t>:#<sc_t>", st_type->sc, st_name->sc );
    }
    else
    {
        if( bcore_source_a_parse_bl_fa( source," #?'^'" ) )
        {
            if( !o->stamp ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"'^' is only inside a stamp allowed." ))
            st_s_copy(st_type,&o->stamp->st_trait_name );
            st_s_push_sc( &(o->flect_decl),"^" );
        }
        else
        {
            BLM_TRY(xoico_group_s_parse_name(o->group,st_type, source ))
    
            if( o->stamp && st_s_equal_st( st_type,&o->stamp->st_trait_name ) )
            {
                st_s_push_fa( &(o->flect_decl),"^" );
            }
            else
            {
                st_s_push_fa( &(o->flect_decl),"#<sc_t>", st_type->sc );
            }
        }
    
        BLM_TRY(bcore_source_a_parse_em_fa( source," ." ) )
        st_s_push_sc( &(o->flect_decl),":" );
    
        BLM_TRY(bcore_source_a_parse_em_fa( source," #name", st_name ) )
    }
    
    if( st_name->size == 0 ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Function name expected." ))
    o->name = xoico_compiler_s_entypeof(compiler,st_name->sc );
    
    st_s_push_sc( &(o->flect_decl),st_name->sc );
    
    st_s_push_fa( st_type,"_#<sc_t>", st_name->sc );
    
    o->signature_global_name = xoico_compiler_s_entypeof(compiler,st_type->sc );
    BLM_TRY(xoico_func_s_set_global_name(o))
    
    if( bcore_source_a_parse_bl_fa( source," #=?'='" ) )
    {
        o->body = xoico_body_s_create();
        BLM_TRY(xoico_body_s_set_group(o->body,o->group ))
        BLM_TRY(xoico_body_s_set_stamp(o->body,o->stamp ))
        BLM_TRY(xoico_body_s_parse(o->body,source ))
    }
    
    BLM_TRY(bcore_source_a_parse_em_fa( source," ; " ) )
    st_s_push_sc( &(o->flect_decl),";" );
    BLM_RETURNV(er_t, 0)
    } /* try */
}

bl_t xoico_func_s_registerable( const xoico_func_s* o )
{
    // xoico_func.x:156:1
    
    if( !o->expandable ) return  false;
    if( xoico_compiler_s_is_item(o->group->compiler,o->signature_global_name ) )
    {
        const xoico* item = xoico_compiler_s_get_const_item(o->group->compiler,o->signature_global_name );
        if( item->_ == TYPEOF_xoico_signature_s )
        {
            if( !o->group->compiler->register_signatures ) return  false;
            const xoico_signature_s* signature = ((xoico_signature_s*)(item));
            return  ( signature->arg_o != 0 || o->group->compiler->register_non_feature_functions );
        }
        else
        {
            return  true;
        }
    }
    else
    {
        return  true;
    }
}

er_t xoico_func_s_finalize( xoico_func_s* o )
{
    // xoico_func.x:181:1
     {
    xoico_compiler_s* compiler = o->group->compiler;
    BLM_TRY(xoico_func_s_set_global_name(o))
    
    xoico_signature_s* signature = ((xoico_signature_s*)(xoico_compiler_s_get_signature(compiler,o->signature_global_name )));
    if( !signature )
    {
        return  bcore_source_point_s_parse_error_fa( &(o->source_point),"Function #<sc_t>: Could not find signature #<sc_t>",
            xoico_compiler_s_nameof(compiler,o->name ),
            xoico_compiler_s_nameof(compiler,o->signature_global_name )
        );
    }
    
    o->signature = signature;
    
    if( o->body )
    {
        BLM_TRY(xoico_body_s_set_group(o->body,o->group ))
        BLM_TRY(xoico_body_s_set_stamp(o->body,o->stamp ))
        BLM_TRY(xoico_body_s_finalize(o->body))
    }
    
    return  0;
    } /* try */
}

er_t xoico_func_s_expand_forward( const xoico_func_s* o, sz_t indent, bcore_sink* sink )
{
    // xoico_func.x:211:1
     {
    if( !o->expandable ) return  0;
    
    xoico_compiler_s* compiler = o->group->compiler;
    bcore_sink_a_push_fa( sink," \\\n#rn{ }", indent );
    bl_t go_inline = o->body && o->body->go_inline;
    const xoico_signature_s* signature = o->signature;
    ASSERT( signature );
    if( go_inline )
    {
        bcore_sink_a_push_fa( sink,"static inline " );
        BLM_TRY(xoico_signature_s_expand_declaration(signature,o->stamp, xoico_compiler_s_nameof(compiler,o->global_name ), indent, sink ))
    }
    else
    {
        BLM_TRY(xoico_signature_s_expand_declaration(signature,o->stamp, xoico_compiler_s_nameof(compiler,o->global_name ), indent, sink ))
    }
    bcore_sink_a_push_fa( sink,";" );
    
    return  0;
    } /* try */
}

er_t xoico_func_s_expand_declaration( const xoico_func_s* o, sz_t indent, bcore_sink* sink )
{
    // xoico_func.x:236:1
     {
    if( !o->expandable ) return  0;
    
    bl_t go_inline = o->body && o->body->go_inline;
    const xoico_signature_s* signature = o->signature;
    ASSERT( signature );
    
    if( go_inline )
    {
        xoico_compiler_s* compiler = o->group->compiler;
        bcore_sink_a_push_fa( sink," \\\n#rn{ }", indent );
        bcore_sink_a_push_fa( sink,"static inline " );
        BLM_TRY(xoico_signature_s_expand_declaration(signature,o->stamp, xoico_compiler_s_nameof( compiler,o->global_name ), indent, sink ))
        BLM_TRY(xoico_body_s_expand(o->body,signature, indent, sink ))
    }
    // non-inline functions are already declared in expand_forward
    
    return  0;
    } /* try */
}

er_t xoico_func_s_expand_definition( const xoico_func_s* o, sz_t indent, bcore_sink* sink )
{
    // xoico_func.x:259:1
     {
    if( !o->expandable ) return  0;
    xoico_compiler_s* compiler = o->group->compiler;
    
    const xoico_signature_s* signature = o->signature;
    ASSERT( signature );
    if( o->body && !o->body->go_inline )
    {
        bcore_sink_a_push_fa( sink,"\n" );
        bcore_sink_a_push_fa( sink,"#rn{ }", indent );
        BLM_TRY(xoico_signature_s_expand_declaration(signature,o->stamp, xoico_compiler_s_nameof(compiler,o->global_name ), indent, sink ))
        bcore_sink_a_push_fa( sink,"\n" );
        BLM_TRY(xoico_body_s_expand(o->body,signature, indent, sink ))
        bcore_sink_a_push_fa( sink,"\n" );
    }
    
    return  0;
    } /* try */
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
"aware xoico_funcs"
"{"
    "xoico_func_s => [];"
"}";

sz_t xoico_funcs_s_get_index_from_signature_global_name( const xoico_funcs_s* o, tp_t signature_global_name )
{
    // xoico_funcs.h:44:5
    
    {const xoico_funcs_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_func_s* e=__a->data[__i]; if( e->signature_global_name == signature_global_name ) return  __i;
    }}return  -1;
}

bl_t xoico_funcs_s_exists_from_signature_global_name( const xoico_funcs_s* o, tp_t signature_global_name )
{
    // xoico_funcs.h:50:5
    
    return  ( xoico_funcs_s_get_index_from_signature_global_name(o,signature_global_name ) >= 0 );
}

sz_t xoico_funcs_s_get_index_from_name( const xoico_funcs_s* o, tp_t name )
{
    // xoico_funcs.h:55:5
    
    {const xoico_funcs_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_func_s* e=__a->data[__i]; if( e->name == name ) return  __i;
    }}return  -1;
}

bl_t xoico_funcs_s_exists_from_name( const xoico_funcs_s* o, tp_t name )
{
    // xoico_funcs.h:61:5
    
    return  ( xoico_funcs_s_get_index_from_name(o,name ) >= 0 );
}

xoico_func_s* xoico_funcs_s_get_func_from_signature_global_name( const xoico_funcs_s* o, tp_t signature_global_name )
{
    // xoico_funcs.h:66:5
    
    sz_t idx = xoico_funcs_s_get_index_from_signature_global_name(o,signature_global_name );
    return  ( idx >= 0 ) ? o->data[ idx ] : NULL;
}

xoico_func_s* xoico_funcs_s_get_func_from_name( const xoico_funcs_s* o, tp_t name )
{
    // xoico_funcs.h:72:5
    
    sz_t idx = xoico_funcs_s_get_index_from_name(o,name );
    return  ( idx >= 0 ) ? o->data[ idx ] : NULL;
}

er_t xoico_funcs_s_replace_fork( xoico_funcs_s* o, sz_t idx, xoico_func_s* func )
{
    // xoico_funcs.h:78:5
    
    ASSERT( idx >= 0 && idx < o->size );
    xoico_func_s_attach( &(o->data[ idx ] ),  NULL);
    for( sz_t i = idx + 1; i < o->size; i++ ) o->data[ i - 1 ] = o->data[ i ];
    o->data[ o->size - 1 ] = ((xoico_func_s*)bcore_fork(func));
    return  0;
}

er_t xoico_funcs_s_push_d( xoico_funcs_s* o, xoico_func_s* func )
{
    // xoico_funcs.h:87:5
    
    bcore_array_a_push( ((bcore_array*)(o)),sr_asd( func ) );
    return  0;
}

tp_t xoico_funcs_s_get_hash( const xoico_funcs_s* o )
{
    // xoico_funcs.h:93:5
    
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
// group: xoico_group
#include "xoico_nested_group.h"

BCORE_DEFINE_OBJECT_INST_P( xoico_group_source_stack_s )
"aware bcore_array"
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
    "st_s st_name;"
    "tp_t tp_name;"
    "st_s trait_name = \"bcore_inst\";"
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
    "func xoico:get_global_name_sc;"
    "func xoico:get_global_name_tp;"
    "func xoico:expand_setup;"
    "func xoico:get_hash;"
    "func xoico:parse;"
    "func xoico:finalize;"
"}";

er_t xoico_group_s_expand_setup( xoico_group_s* o )
{
    // xoico_group.h:97:5
    
    {const xoico_group_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico* e=__a->data[__i]; BLM_TRY(xoico_a_expand_setup(e) )
    }}return  0;
}

er_t xoico_group_s_push_item_d( xoico_group_s* o, xoico* item )
{
    // xoico_group.h:110:5
    
    bcore_array_a_push( ((bcore_array*)(o)),sr_asd( item ) );
    return  0;
}

tp_t xoico_group_s_get_hash( const xoico_group_s* o )
{
    // xoico_group.x:21:1
    
    tp_t hash = o->pre_hash;
    hash = bcore_tp_fold_sc( hash, o->st_name.sc );
    hash = bcore_tp_fold_sc( hash, o->trait_name.sc );
    hash = bcore_tp_fold_bl( hash, o->retrievable );
    hash = bcore_tp_fold_bl( hash, o->expandable );
    hash = bcore_tp_fold_bl( hash, o->short_spect_name );
    hash = bcore_tp_fold_tp( hash, o->beta );
    hash = bcore_tp_fold_tp( hash, xoico_funcs_s_get_hash(&(o->funcs)) );
    {const xoico_group_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico* e=__a->data[__i]; hash = bcore_tp_fold_tp( hash, xoico_a_get_hash(e) );}}
    {const bcore_arr_st_s* __a=&(o->includes_in_declaration );if(__a)for(sz_t __i=0; __i<__a->size; __i++){st_s* e=__a->data[__i]; hash = bcore_tp_fold_sc( hash, e->sc );}}
    {const bcore_arr_st_s* __a=&(o->includes_in_definition  );if(__a)for(sz_t __i=0; __i<__a->size; __i++){st_s* e=__a->data[__i]; hash = bcore_tp_fold_sc( hash, e->sc );}}
    return  hash;
}

st_s* xoico_group_s_create_spect_name( const xoico_group_s* o )
{
    // xoico_group.x:39:1
    
    if( o->short_spect_name )
    {
        return  st_s_create_fa( "#<sc_t>_s", o->st_name.sc );
    }
    else
    {
        return  st_s_create_fa( "#<sc_t>_spect_s", o->st_name.sc );
    }
}

er_t xoico_group_s_parse_name_recursive( xoico_group_s* o, st_s* name, bcore_source* source )
{
    // xoico_group.x:53:1
    BLM_INIT_LEVEL(0); {
    if( bcore_source_a_parse_bl_fa( source,"#?':'" ) )
    {
        if( o->parent )
        {
            BLM_TRY(xoico_group_s_parse_name_recursive(o->parent,name, source ))
        }
        else
        {
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Too many colons: Namespace depth exceeded." ))
        }
    }
    else
    {
        st_s_copy(name,&(o->st_name ));
        st_s* s = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
        BLM_TRY(bcore_source_a_parse_em_fa( source," #name", s ) )
        if( s->size > 0 ) st_s_push_fa( name,"_#<sc_t>", s->sc );
    }
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_group_s_parse_name( xoico_group_s* o, st_s* name, bcore_source* source )
{
    // xoico_group.x:78:1
     {
    if( bcore_source_a_parse_bl_fa( source," #?':'" ) )
    {
        BLM_TRY(xoico_group_s_parse_name_recursive(o,name, source ))
    }
    else
    {
        BLM_TRY(bcore_source_a_parse_em_fa( source," #name", name ) )
    }
    
    if( name->size > 0 ) xoico_compiler_s_entypeof(o->compiler,name->sc );
    
    return  0;
    } /* try */
}

er_t xoico_group_s_push_default_feature_from_sc( xoico_group_s* o, sc_t sc )
{
    // xoico_group.x:96:1
    BLM_INIT_LEVEL(0); {
    xoico_compiler_s* compiler = o->compiler;
    xoico_feature_s* feature = ((xoico_feature_s*)BLM_LEVEL_T_PUSH(0,xoico_feature_s,xoico_feature_s_create()));
    feature->expandable = false;
    feature->group = o;
    BLM_TRY(xoico_feature_s_parse(feature,((bcore_source*)BLM_LEVEL_A_PUSH(0,((bcore_source*)(bcore_source_string_s_create_from_sc( sc ))))) ))
    
    if( !xoico_compiler_s_is_item(compiler,xoico_a_get_global_name_tp(((xoico*)(feature))) ) )
    {
        BLM_TRY(xoico_compiler_s_register_item(compiler,((xoico*)(feature)), o->source_point.source ))
        bcore_hmap_tpvd_s_set(&(o->hmap_feature),feature->signature.name, ( vd_t )feature );
        BLM_TRY(xoico_group_s_push_item_d(o,((xoico*)(((xoico_feature_s*)bcore_fork(feature)))) ))
    }
    
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_group_s_parse_func( xoico_group_s* o, bcore_source* source )
{
    // xoico_group.x:116:1
    BLM_INIT_LEVEL(0); {
    xoico_compiler_s* compiler = o->compiler;
    xoico_func_s* func = ((xoico_func_s*)BLM_LEVEL_T_PUSH(0,xoico_func_s,xoico_func_s_create()));
    func->group = o;
    func->stamp = NULL;
    
    BLM_TRY(xoico_func_s_parse(func,source ))
    sz_t idx = xoico_funcs_s_get_index_from_name(&(o->funcs),func->name );
    
    if( idx >= 0 )
    {
        xoico_func_s* prex_func = o->funcs.data[ idx ];
        if( ( prex_func->signature_global_name == func->signature_global_name ) )
        {
            if( !func->body )
            {
                BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Function '#<sc_t>' has already been declared.", xoico_compiler_s_nameof(compiler,func->name ) ))
            }
            else if( prex_func->body )
            {
                BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Function '#<sc_t>' has already a body.", xoico_compiler_s_nameof(compiler,func->name ) ))
            }
            else
            {
                BLM_TRY(xoico_funcs_s_replace_fork(&(o->funcs),idx, func ))
            }
        }
        else
        {
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Function '#<sc_t>' has already been declared.", xoico_compiler_s_nameof(compiler,func->name ) ))
        }
    }
    else
    {
        BLM_TRY(xoico_funcs_s_push_d(&(o->funcs),((xoico_func_s*)bcore_fork(func)) ))
    }
    
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_group_s_parse( xoico_group_s* o, bcore_source* source )
{
    // xoico_group.x:159:1
    BLM_INIT_LEVEL(0); {
    xoico_group_source_stack_s* stack = ((xoico_group_source_stack_s*)BLM_LEVEL_T_PUSH(0,xoico_group_source_stack_s,xoico_group_source_stack_s_create()));
    xoico_group_source_stack_s_push_d( stack,((bcore_source*)bcore_fork(source)) );
    
    sc_t group_termination = NULL;
    
    bcore_source_point_s_set( &(o->source_point),source );
    o->pre_hash = bcore_tp_init();
    
    if( o->parent ) // this group is nested in another group, the group body is enclosed in { ... }
    {
        BLM_TRY(bcore_source_a_parse_em_fa( source," {" ) )
        group_termination = " #?'}'";
    }
    else // this group is root
    {
        if( bcore_source_a_parse_bl_fa( source," #?'#ifdef XOILA_SECTION'" ) )
        {
            group_termination = " #?'#endif'";
        }
        else
        {
            group_termination = NULL;
        }
    }
    
    bl_t extend_stump = false;
    
    xoico_compiler_s* compiler = o->compiler;
    
    while
    (
        stack->size >= 2 ||
        ( group_termination ? !bcore_source_a_parse_bl_fa( source,group_termination ) : !bcore_source_a_eos( source) )
    )
    {
        if( bcore_source_a_eos( source) )
        {
            if( stack->size >= 2 )
            {
                bcore_source_a_attach( &(stack->data[ stack->size - 1 ] ), (bcore_source*)( NULL));
                source = stack->data[ stack->size - 2 ];
                xoico_group_source_stack_s_set_size( stack,stack->size - 1 );
            }
            else if( group_termination )
            {
                BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Unexpected end of file." ))
            }
            else
            {
                break;
            }
        }
        else if( bcore_source_a_parse_bl_fa( source," #?w'stamp' " ) )
        {BLM_INIT_LEVEL(4);
            xoico_stamp_s* stamp = ((xoico_stamp_s*)BLM_LEVEL_T_PUSH(4,xoico_stamp_s,xoico_stamp_s_create()));
            stamp->group = o;
            BLM_TRY(xoico_stamp_s_parse(stamp,source ))
            BLM_TRY(xoico_stamp_s_push_default_funcs(stamp))
            BLM_TRY(xoico_compiler_s_register_item(compiler,((xoico*)(stamp)), source ))
            BLM_TRY(xoico_group_s_push_item_d(o,((xoico*)(((xoico_stamp_s*)bcore_fork(stamp)))) ))
        BLM_DOWN();}
    
        /// stumps are inexpandable stamps. They can be used as template.
        else if( bcore_source_a_parse_bl_fa( source," #?w'stump' " ) )
        {BLM_INIT_LEVEL(4);
            xoico_stamp_s* stump = ((xoico_stamp_s*)BLM_LEVEL_T_PUSH(4,xoico_stamp_s,xoico_stamp_s_create()));
            stump->group = o;
            BLM_TRY(xoico_stamp_s_parse(stump,source ))
            BLM_TRY(xoico_stamp_s_make_funcs_overloadable(stump))
            BLM_TRY(xoico_compiler_s_register_item(compiler,((xoico*)(stump)), source ))
            BLM_TRY(xoico_compiler_s_life_a_push(compiler,((bcore_inst*)(((xoico_stamp_s*)bcore_fork(stump)))) ))
            if( extend_stump )
            {
                o->extending_stamp = stump;
                extend_stump = false;
            }
        BLM_DOWN();}
        else if( bcore_source_a_parse_bl_fa( source," #?w'signature' " ) )
        {BLM_INIT_LEVEL(4);
            xoico_signature_s* signature = ((xoico_signature_s*)BLM_LEVEL_T_PUSH(4,xoico_signature_s,xoico_signature_s_create()));
            signature->group = o;
            BLM_TRY(xoico_signature_s_parse(signature,source ))
            BLM_TRY(bcore_source_a_parse_em_fa( source," ; " ) )
            xoico_compiler_s_register_item(compiler,((xoico*)(signature)), source );
            BLM_TRY(xoico_group_s_push_item_d(o,((xoico*)(((xoico_signature_s*)bcore_fork(signature)))) ))
        BLM_DOWN();}
        else if( bcore_source_a_parse_bl_fa( source, " #?w'body' " ) )
        {BLM_INIT_LEVEL(4);
            xoico_body_s* body = ((xoico_body_s*)BLM_LEVEL_T_PUSH(4,xoico_body_s,xoico_body_s_create()));
            BLM_TRY(xoico_body_s_set_group(body,o ))
            BLM_TRY(xoico_body_s_parse(body,source ))
            BLM_TRY(bcore_source_a_parse_em_fa( source," ; " ) )
            xoico_compiler_s_register_item(compiler,((xoico*)(body)), source );
            BLM_TRY(xoico_group_s_push_item_d(o,((xoico*)(((xoico_body_s*)bcore_fork(body)))) ))
        BLM_DOWN();}
        else if( bcore_source_a_parse_bl_fa( source," #?w'feature' " ) )
        {BLM_INIT_LEVEL(4);
            xoico_feature_s* feature = ((xoico_feature_s*)BLM_LEVEL_T_PUSH(4,xoico_feature_s,xoico_feature_s_create()));
            feature->group = o;
            BLM_TRY(xoico_feature_s_parse(feature,source ))
            BLM_TRY(xoico_compiler_s_register_item(compiler,((xoico*)(feature)), source ))
            bcore_hmap_tpvd_s_set(&(o->hmap_feature),feature->signature.name, ( vd_t )feature );
            BLM_TRY(xoico_group_s_push_item_d(o,((xoico*)(((xoico_feature_s*)bcore_fork(feature)))) ))
        BLM_DOWN();}
        else if( bcore_source_a_parse_bl_fa( source," #?w'func' " ) )
        {
            bl_t is_plain_function = true;
            if( bcore_source_a_parse_bl_fa( source," #=?'('" ) )
            {BLM_INIT_LEVEL(5);
                sz_t index = bcore_source_a_get_index( source);
                bcore_source_a_parse_fa( source,"(" );
                st_s* stamp_name = ((st_s*)BLM_LEVEL_T_PUSH(5,st_s,st_s_create()));
                BLM_TRY(xoico_group_s_parse_name(o,stamp_name, source ))
                if( bcore_source_a_parse_bl_fa( source," #?')'" ) )
                {
                    st_s_push_sc( stamp_name,"_s" );
                    tp_t tp_stamp_name = btypeof( stamp_name->sc );
                    if( !xoico_compiler_s_is_stamp(compiler,tp_stamp_name ) )
                    {
                        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Cannot associate type name '#<sc_t>' with a stamp.", stamp_name->sc ))
                    }
    
                    xoico_stamp_s* stamp = xoico_compiler_s_get_stamp(compiler,tp_stamp_name );
                    BLM_TRY(xoico_stamp_s_parse_func(stamp,source ))
                    o->pre_hash = bcore_tp_fold_tp( o->pre_hash, xoico_stamp_s_get_hash(stamp) );
                    is_plain_function = false;
                }
                else
                {
                    bcore_source_a_set_index( source,index );
                    is_plain_function = true;
                }
            BLM_DOWN();}
    
            if( is_plain_function )
            {
                BLM_TRY(xoico_group_s_parse_func(o,source ))
            }
        }
        else if( bcore_source_a_parse_bl_fa( source," #?w'name' " ) )
        {BLM_INIT_LEVEL(4);
            xoico_name_s* name = ((xoico_name_s*)BLM_LEVEL_T_PUSH(4,xoico_name_s,xoico_name_s_create()));
            name->group = o;
            BLM_TRY(xoico_name_s_parse(name,source ))
            BLM_TRY(xoico_group_s_push_item_d(o,((xoico*)(((xoico_name_s*)bcore_fork(name)))) ))
        BLM_DOWN();}
        else if( bcore_source_a_parse_bl_fa( source," #?w'type' " ) )
        {BLM_INIT_LEVEL(4);
            xoico_name_s* name = ((xoico_name_s*)BLM_LEVEL_T_PUSH(4,xoico_name_s,xoico_name_s_create()));
            name->group = o;
            BLM_TRY(xoico_name_s_parse(name,source ))
            BLM_TRY(xoico_compiler_s_register_external_type(compiler,name->name ))
            BLM_TRY(xoico_group_s_push_item_d(o,((xoico*)(((xoico_name_s*)bcore_fork(name)))) ))
        BLM_DOWN();}
        else if( bcore_source_a_parse_bl_fa( source, " #?w'forward' " ) )
        {BLM_INIT_LEVEL(4);
            xoico_forward_s* forward = ((xoico_forward_s*)BLM_LEVEL_T_PUSH(4,xoico_forward_s,xoico_forward_s_create()));
            forward->group = o;
            BLM_TRY(xoico_forward_s_parse(forward,source ))
            BLM_TRY(xoico_group_s_push_item_d(o,((xoico*)(((xoico_forward_s*)bcore_fork(forward)))) ))
        BLM_DOWN();}
        else if( bcore_source_a_parse_bl_fa( source, " #?w'extending'" ) )
        {
            o->extending_stamp = NULL;
            if( bcore_source_a_parse_bl_fa( source," #=?';'" ) )
            {
                // just reset o->extending - nothing else
            }
            else if( bcore_source_a_parse_bl_fa( source," #=?w'stump'" ) )
            {
                extend_stump = true;
            }
            else
            {BLM_INIT_LEVEL(5);
                st_s* templ_name = ((st_s*)BLM_LEVEL_T_PUSH(5,st_s,st_s_create()));
                BLM_TRY(xoico_group_s_parse_name(o,templ_name, source ))
                st_s_push_fa( templ_name,"_s" );
                const xoico* item = xoico_compiler_s_get_const_item(compiler,typeof( templ_name->sc ) );
                if( !item ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Template #<sc_t> not found.", templ_name->sc ))
                if( item->_ != TYPEOF_xoico_stamp_s ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Template #<sc_t> is no stamp.", templ_name->sc ))
                o->extending_stamp = ((xoico_stamp_s*)(item));
                BLM_TRY(bcore_source_a_parse_em_fa( source," ;" ) )
            BLM_DOWN();}
        }
        else if( bcore_source_a_parse_bl_fa( source," #?w'group' " ) )
        {BLM_INIT_LEVEL(4);
            xoico_group_s* group = ((xoico_group_s*)BLM_LEVEL_T_PUSH(4,xoico_group_s,xoico_group_s_create()));
            BLM_TRY(xoico_source_s_push_d(o->xoico_source,((xoico_group_s*)bcore_fork(group)) ))
            group->parent = o;
            group->xoico_source = o->xoico_source;
            group->compiler = o->compiler;
            group->extending_stamp = o->extending_stamp;
            group->expandable  = o->expandable;
    
            BLM_TRY(xoico_group_s_parse_name(o,&group->st_name, source ))
            BLM_TRY(bcore_source_a_parse_em_fa( source," =" ) )
    
            // flags
            if( bcore_source_a_parse_bl_fa( source," #?w'retrievable' " ) ) group->retrievable = true;
    
            BLM_TRY(xoico_group_s_parse_name(o,&group->trait_name, source ))
            if( group->trait_name.size == 0 ) st_s_copy(&(group->trait_name),&(o->st_name ));
            BLM_TRY(xoico_group_s_parse(group,source ))
            BLM_TRY(bcore_source_a_parse_em_fa( source," ; " ) )
            xoico_compiler_s_register_group(compiler,group );
            xoico_nested_group_s* nested_group = ((xoico_nested_group_s*)BLM_LEVEL_T_PUSH(4,xoico_nested_group_s,xoico_nested_group_s_create()));
            nested_group->group = group;
            BLM_TRY(xoico_group_s_push_item_d(o,((xoico*)(((xoico_nested_group_s*)bcore_fork(nested_group)))) ))
        BLM_DOWN();}
        else if( bcore_source_a_parse_bl_fa( source," #?w'set' " ) )
        {
            if(      bcore_source_a_parse_bl_fa( source," #?w'retrievable' "      ) ) o->retrievable = true;
            else if( bcore_source_a_parse_bl_fa( source," #?w'inexpandable' "     ) ) o->expandable = false;
            else if( bcore_source_a_parse_bl_fa( source," #?w'short_spect_name' " ) ) o->short_spect_name = true;
            else if( bcore_source_a_parse_bl_fa( source," #?w'beta' "             ) ) BLM_TRY(bcore_source_a_parse_em_fa( source," = #<tp_t*>", &o->beta ) )
            BLM_TRY(bcore_source_a_parse_em_fa( source," ;" ) )
        }
        else if( bcore_source_a_parse_bl_fa( source," #?w'embed' " ) )
        {BLM_INIT_LEVEL(4);
            st_s* folder = ((st_s*)BLM_LEVEL_T_PUSH(4,st_s,((st_s*)(bcore_file_folder_path(bcore_source_a_get_file( source ) )))));
            if( folder->size == 0 ) st_s_push_char( folder,'.' );
            st_s* include_file = ((st_s*)BLM_LEVEL_T_PUSH(4,st_s,st_s_create()));
            BLM_TRY(bcore_source_a_parse_em_fa( source," #string" , include_file ) )
            BLM_TRY(bcore_source_a_parse_em_fa( source," ;" ) )
            bcore_arr_st_s_push_st(&(o->xoico_source->target->explicit_embeddings),include_file );
            bcore_source* embed_source = NULL;
            BLM_TRY(xoico_embed_file_open(source, include_file->sc, &embed_source ) )
    
            // check for cyclic inclusions
            {const xoico_group_source_stack_s* __a=stack ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){bcore_source* e=__a->data[__i];
            {
                sc_t path = bcore_source_a_get_file( embed_source);
                if( sc_t_equal( path, bcore_source_a_get_file( e) ) )
                {
                    BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Xoico: Cyclic inclusion." ))
                }
            }
    
            }}xoico_group_source_stack_s_push_d( stack,source = embed_source );
        BLM_DOWN();}
        else if( bcore_source_a_parse_bl_fa( source," #?w'include' " ) )
        {BLM_INIT_LEVEL(4);
            bl_t deferred = bcore_source_a_parse_bl_fa( source," #?w'deferred' " );
            st_s* include_file = ((st_s*)BLM_LEVEL_T_PUSH(4,st_s,st_s_create()));
            BLM_TRY(bcore_source_a_parse_em_fa( source," #string" , include_file ) )
            BLM_TRY(bcore_source_a_parse_em_fa( source," ;" ) )
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
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Xoico: syntax error." ))
        }
    
        BLM_TRY(bcore_source_a_parse_em_fa( source," " ) )// consume whitespaces
    }
    
    /// default features
    BLM_TRY(xoico_group_s_push_default_feature_from_sc(o,"@* clone( const );" ))
    BLM_TRY(xoico_group_s_push_default_feature_from_sc(o,"void copy( mutable, const @* src );" ))
    BLM_TRY(xoico_group_s_push_default_feature_from_sc(o,"void discard( mutable );" ))
    
    if( stack->size > 1 )
    {
        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Xoico: Unexpected end of group reached." ))
    }
    
    o->tp_name = xoico_compiler_s_entypeof(compiler,o->st_name.sc );
    
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_group_s_finalize( xoico_group_s* o )
{
    // xoico_group.x:441:1
     {
    {const xoico_group_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico* e=__a->data[__i]; BLM_TRY(xoico_a_finalize(e))
    }}{const xoico_funcs_s* __a=&(o->funcs );if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_func_s* func=__a->data[__i];
    {
        BLM_TRY(xoico_func_s_finalize(func))
        BLM_TRY(xoico_compiler_s_register_func(o->compiler,func ))
    }
    }}return  0;
    } /* try */
}

er_t xoico_group_s_expand_forward( const xoico_group_s* o, sz_t indent, bcore_sink* sink )
{
    // xoico_group.x:454:1
     {
    if( !o->expandable ) return  0;
    bcore_sink_a_push_fa( sink," \\\n#rn{ }BCORE_FORWARD_OBJECT( #<sc_t> );", indent, o->st_name.sc );
    {const xoico_group_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico* e=__a->data[__i]; BLM_TRY(xoico_a_expand_forward(e,indent, sink ))
    }}{const xoico_funcs_s* __a=&(o->funcs );if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_func_s* func=__a->data[__i]; BLM_TRY(xoico_func_s_expand_forward(func,indent, sink ))
    }}return  0;
    } /* try */
}

er_t xoico_group_s_expand_spect_declaration( const xoico_group_s* o, sz_t indent, bcore_sink* sink )
{
    // xoico_group.x:465:1
     {
    if( !o->expandable ) return  0;
    if( o->short_spect_name )
    {
        bcore_sink_a_push_fa( sink," \\\n#rn{ }BCORE_DECLARE_SPECT( #<sc_t> )", indent, o->st_name.sc );
    }
    else
    {
        bcore_sink_a_push_fa( sink," \\\n#rn{ }XOILA_DECLARE_SPECT( #<sc_t> )", indent, o->st_name.sc );
    }
    
    bcore_sink_a_push_fa( sink," \\\n#rn{ }{", indent );
    bcore_sink_a_push_fa( sink," \\\n#rn{ }    bcore_spect_header_s header;", indent );
    {const xoico_group_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico* e=__a->data[__i]; BLM_TRY(xoico_a_expand_spect_declaration(e,indent + 4, sink ))
    }}bcore_sink_a_push_fa( sink," \\\n#rn{ }};", indent );
    
    bcore_sink_a_push_fa( sink," \\\n#rn{ }"
        "BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( #<sc_t> )",
        indent,
        o->st_name.sc
    );
    
    return  0;
    } /* try */
}

er_t xoico_group_s_expand_declaration( const xoico_group_s* o, sz_t indent, bcore_sink* sink )
{
    // xoico_group.x:495:1
    BLM_INIT_LEVEL(0); {
    if( !o->expandable ) BLM_RETURNV(er_t, 0)
    
    bcore_sink_a_push_fa( sink,"\n" );
    bcore_sink_a_push_fa( sink,"#rn{ }//#rn{-}\n", indent, sz_max( 0, 118 - indent ) );
    bcore_sink_a_push_fa( sink,"#rn{ }// group: #<sc_t>\n", indent, o->st_name.sc );
    
    {const bcore_arr_st_s* __a=&(o->includes_in_declaration );if(__a)for(sz_t __i=0; __i<__a->size; __i++){st_s* e=__a->data[__i]; bcore_sink_a_push_fa( sink,"##include \"#<sc_t>\"\n", e->sc );}}
    
    bcore_sink_a_push_fa( sink,"\n" );
    bcore_sink_a_push_fa( sink,"#rn{ }##define TYPEOF_#<sc_t> 0x#pl16'0'{#X<tp_t>}ull\n", indent, o->st_name.sc, btypeof( o->st_name.sc ) );
    
    st_s* st_spect_name = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,((st_s*)(xoico_group_s_create_spect_name( o )))));
    sc_t sc_spect_name = st_spect_name->sc;
    
    bcore_sink_a_push_fa( sink,"#rn{ }##define TYPEOF_#<sc_t> 0x#pl16'0'{#X<tp_t>}ull\n", indent, sc_spect_name, btypeof( sc_spect_name ) );
    
    {const xoico_group_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico* e=__a->data[__i]; BLM_TRY(xoico_a_expand_declaration(e,indent, sink ))
    }}bcore_sink_a_push_fa( sink,"#rn{ }##define BETH_EXPAND_GROUP_#<sc_t>", indent, o->st_name.sc );
    
    BLM_TRY(xoico_group_s_expand_forward(o,indent + 2, sink ))
    
    {const xoico_group_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico* e=__a->data[__i]; BLM_TRY(xoico_a_expand_indef_typedef(e,indent, sink ))
    }}BLM_TRY(xoico_group_s_expand_spect_declaration(o,indent + 2, sink ))
    
    {const xoico_group_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico* e=__a->data[__i]; BLM_TRY(xoico_a_expand_indef_declaration(e,indent, sink ))
    }}{const xoico_funcs_s* __a=&(o->funcs );if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_func_s* func=__a->data[__i]; BLM_TRY(xoico_func_s_expand_declaration(func,indent + 2, sink ))
    
    }}bcore_sink_a_push_fa( sink,"\n" );
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_group_s_expand_spect_definition( const xoico_group_s* o, sz_t indent, bcore_sink* sink )
{
    // xoico_group.x:530:1
     {
    if( !o->expandable ) return  0;
    bcore_sink_a_push_fa( sink,"\n" );
    if( o->short_spect_name )
    {
        bcore_sink_a_push_fa( sink,"#rn{ }BCORE_DEFINE_SPECT( #<sc_t>, #<sc_t> )\n", indent, o->trait_name.sc, o->st_name.sc );
    }
    else
    {
        bcore_sink_a_push_fa( sink,"#rn{ }XOILA_DEFINE_SPECT( #<sc_t>, #<sc_t> )\n", indent, o->trait_name.sc, o->st_name.sc );
    }
    
    bcore_sink_a_push_fa( sink,"#rn{ }\"{\"\n", indent );
    bcore_sink_a_push_fa( sink,"#rn{ }    \"bcore_spect_header_s header;\"\n", indent );
    {const xoico_group_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico* e=__a->data[__i]; BLM_TRY(xoico_a_expand_spect_definition(e,indent + 4, sink ))
    }}bcore_sink_a_push_fa( sink,"#rn{ }\"}\";\n", indent );
    return  0;
    } /* try */
}

er_t xoico_group_s_expand_definition( const xoico_group_s* o, sz_t indent, bcore_sink* sink )
{
    // xoico_group.x:552:1
     {
    if( !o->expandable ) return  0;
    bcore_sink_a_push_fa( sink,"\n" );
    bcore_sink_a_push_fa( sink,"#rn{ }//#rn{-}\n", indent, sz_max( 0, 118 - indent ) );
    bcore_sink_a_push_fa( sink,"#rn{ }// group: #<sc_t>\n", indent, o->st_name.sc );
    
    {const bcore_arr_st_s* __a=&(o->includes_in_definition );if(__a)for(sz_t __i=0; __i<__a->size; __i++){st_s* e=__a->data[__i]; bcore_sink_a_push_fa( sink,"##include \"#<sc_t>\"\n", e->sc );}}
    
    // non-features
    {const xoico_group_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico* e=__a->data[__i]; if( e->_ != TYPEOF_xoico_feature_s ) BLM_TRY(xoico_a_expand_definition(e,indent, sink ))
    
    }}BLM_TRY(xoico_group_s_expand_spect_definition(o,indent, sink ))
    
    // just-features
    {const xoico_group_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico* e=__a->data[__i]; if( e->_ == TYPEOF_xoico_feature_s ) BLM_TRY(xoico_a_expand_definition(e,indent, sink ))
    
    }}{const xoico_funcs_s* __a=&(o->funcs );if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_func_s* func=__a->data[__i]; BLM_TRY(xoico_func_s_expand_definition(func,indent, sink ))
    
    }}return  0;
    } /* try */
}

er_t xoico_group_s_expand_init1( const xoico_group_s* o, sz_t indent, bcore_sink* sink )
{
    // xoico_group.x:576:1
     {
    if( !o->expandable ) return  0;
    bcore_sink_a_push_fa( sink,"\n" );
    bcore_sink_a_push_fa( sink,"#rn{ }// group: #<sc_t>\n", indent, o->st_name.sc );
    {const xoico_group_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico* e=__a->data[__i]; BLM_TRY(xoico_a_expand_init1(e,indent, sink ))
    
    }}if( o->short_spect_name )
    {
        bcore_sink_a_push_fa( sink,"#rn{ }BCORE_REGISTER_SPECT( #<sc_t> );\n", indent, o->st_name.sc );
    }
    else
    {
        bcore_sink_a_push_fa( sink,"#rn{ }XOILA_REGISTER_SPECT( #<sc_t> );\n", indent, o->st_name.sc );
    }
    
    if( o->retrievable )
    {
        {const xoico_group_s* __a=o ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico* e=__a->data[__i];
        {
            if( e->_ == TYPEOF_xoico_stamp_s )
            {
                bcore_sink_a_push_fa( sink,"#rn{ }bcore_inst_s_get_typed( TYPEOF_#<sc_t> );\n", indent, ((xoico_stamp_s*)(e))->st_name.sc );
            }
        }
    }}}
    return  0;
    } /* try */
}

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
    "bl_t is_aware;"
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
    "xoico_group_s => [];"
    "hidden aware xoico_target_s* target;"
    "func xoico:expand_setup;"
    "func xoico:get_hash;"
"}";

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

void xoico_target_s_push_d( xoico_target_s* o, xoico_source_s* source )
{
    // xoico_target.h:71:5
    
    bcore_array_a_push( ((bcore_array*)(o)),sr_asd( source ) );
}

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
    "hidden bcore_life_s life;"
    "hidden bcore_hmap_tpvd_s hmap_group;"
    "hidden bcore_hmap_tpvd_s hmap_item;"
    "hidden bcore_hmap_tpvd_s hmap_func;"
    "hidden bcore_hmap_tp_s hmap_external_type;"
    "hidden bcore_hmap_name_s name_map;"
    "tp_t target_pre_hash = 71;"
    "bl_t work_build_time_into_pre_hash = true;"
    "bl_t register_non_feature_functions = true;"
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
    // xoico_compiler.h:125:5
    
    if( xoico_compiler_s_is_group(o,name ) ) return  true;
    if( xoico_compiler_s_is_stamp(o,name ) ) return  true;
    if( bcore_hmap_tp_s_exists(&(o->hmap_external_type),name ) ) return  true;
    return  false;
}

bl_t xoico_compiler_s_is_stamp( const xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:133:5
    
    const xoico* item = xoico_compiler_s_get_const_item(o,name );
    if( item && ( item->_ == TYPEOF_xoico_stamp_s ) ) return  true;
    return  false;
}

bl_t xoico_compiler_s_is_signature( const xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:140:5
    
    const xoico* item = xoico_compiler_s_get_const_item(o,name );
    if( item && ( item->_ == TYPEOF_xoico_signature_s ) ) return  true;
    return  false;
}

bl_t xoico_compiler_s_is_signature_or_feature( const xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:147:5
    
    const xoico* item = xoico_compiler_s_get_const_item(o,name );
    if( !item ) return  NULL;
    if( item->_ == TYPEOF_xoico_signature_s || item->_ == TYPEOF_xoico_feature_s ) return  true;
    return  false;
}

bl_t xoico_compiler_s_is_feature( const xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:155:5
    
    const xoico* item = xoico_compiler_s_get_const_item(o,name );
    if( item && ( item->_ == TYPEOF_xoico_feature_s ) ) return  true;
    return  false;
}

const xoico* xoico_compiler_s_get_const_item( const xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:162:5
    
    vd_t* ptr = bcore_hmap_tpvd_s_get(&(o->hmap_item),name );
    return  ptr ? ( const xoico* )*ptr : NULL;
}

xoico* xoico_compiler_s_get_item( xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:168:5
    
    vd_t* ptr = bcore_hmap_tpvd_s_get(&(o->hmap_item),name );
    return  ptr ? ( xoico* )*ptr : NULL;
}

xoico_stamp_s* xoico_compiler_s_get_stamp( xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:174:5
    
    const xoico* item = xoico_compiler_s_get_const_item(o,name );
    return  ( item ) ? ( item->_ == TYPEOF_xoico_stamp_s ) ? ((xoico_stamp_s*)(item)) : NULL : NULL;
}

const xoico_feature_s* xoico_compiler_s_get_feature( const xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:180:5
    
    const xoico* item = xoico_compiler_s_get_const_item(o,name );
    return  ( item ) ? ( item->_ == TYPEOF_xoico_feature_s ) ? ((xoico_feature_s*)(item)) : NULL : NULL;
}

const xoico_signature_s* xoico_compiler_s_get_signature( const xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:186:5
    
    const xoico* item = xoico_compiler_s_get_const_item(o,name );
    if( !item ) return  NULL;
    if( item->_ == TYPEOF_xoico_signature_s ) return  ((xoico_signature_s*)(item));
    if( item->_ == TYPEOF_xoico_feature_s   ) return &( ((xoico_feature_s*)(item))->signature);
    return  NULL;
}

xoico_group_s* xoico_compiler_s_get_group( xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:195:5
    
    vd_t* ptr = bcore_hmap_tpvd_s_get(&(o->hmap_group),name );
    return  ptr ? ( xoico_group_s* )*ptr : NULL;
}

xoico_func_s* xoico_compiler_s_get_func( xoico_compiler_s* o, tp_t name )
{
    // xoico_compiler.h:201:5
    
    vd_t* ptr = bcore_hmap_tpvd_s_get(&(o->hmap_func),name );
    return  ptr ? ( xoico_func_s* )*ptr : NULL;
}

er_t xoico_compiler_s_life_a_push( xoico_compiler_s* o, bcore_inst* object )
{
    // xoico_compiler.h:207:5
    
    bcore_life_s_push_aware( &o->life, object );
    return  0;
}

void xoico_compiler_s_init_x( xoico_compiler_s* o )
{
    // xoico_compiler.h:228:5
    
    if( o->work_build_time_into_pre_hash )
    {
        o->target_pre_hash = bcore_tp_fold_sc( o->target_pre_hash, __DATE__ );
        o->target_pre_hash = bcore_tp_fold_sc( o->target_pre_hash, __TIME__ );
    }
}

void xoico_compiler_s_push_d( xoico_compiler_s* o, xoico_target_s* target )
{
    // xoico_compiler.h:237:5
    
    bcore_array_a_push( ((bcore_array*)(o)),sr_asd( target ) );
}

er_t xoico_compiler_s_register_group( xoico_compiler_s* o, const xoico_group_s* group )
{
    // xoico_compiler.x:21:1
    
    if( bcore_hmap_tpvd_s_exists(&(o->hmap_group),group->tp_name ) )
    {
        return  bcore_source_point_s_parse_error_fa
        (
            &group->source_point,
            "'#<sc_t>' was already registered\n",
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
        return  bcore_source_a_parse_error_fa( source,"'#<sc_t>' was already registered\n", xoico_compiler_s_nameof(o,global_id ) );
    }
    bcore_hmap_tpvd_s_set(&(o->hmap_item),global_id, ( vd_t )item );
    return  0;
}

er_t xoico_compiler_s_register_func( xoico_compiler_s* o, const xoico_func_s* func )
{
    // xoico_compiler.x:51:1
    
    if( bcore_hmap_tpvd_s_exists(&(o->hmap_func),func->global_name ) )
    {
        return  bcore_source_point_s_parse_error_fa
        (
            &func->source_point,
            "'#<sc_t>' was already registered\n",
            xoico_compiler_s_nameof(o,func->global_name )
        );
    }
    
    bcore_hmap_tpvd_s_set(&(o->hmap_func),func->global_name, ( vd_t )func );
    return  0;
}

er_t xoico_compiler_s_check_overwrite( const xoico_compiler_s* o, sc_t file )
{
    // xoico_compiler.x:96:1
    
    if( !bcore_file_exists(file ) ) return  0;
    
    if( !xoico_compiler_is_signed(file ) )
    {BLM_INIT_LEVEL(1);
        st_s* s = ((st_s*)BLM_LEVEL_T_PUSH(1,st_s,st_s_create()));
        st_s_push_fa( s,"Planted file #<sc_t>: Signature check failed.\n", file );
        st_s_push_fa( s,"This file might have been created or edited outside the xoico framework.\n" );
        if( o->overwrite_unsigned_target_files )
        {
            st_s_push_fa( s,"Flag 'overwrite_unsigned_target_files' is 'true'. The file will be overwritten.\n" );
            bcore_sink_a_push_fa( BCORE_STDERR, "\nWARNING: #<sc_t>\n", s->sc );
        }
        else
        {
            st_s_push_fa( s,"Xoico has currently no permission to overwrite unsigned target files.\n" );
            st_s_push_fa( s,"You can fix it in one of following ways:\n" );
            st_s_push_fa( s,"* Rename or (re)move the file.\n" );
            st_s_push_fa( s,"* Use command line flag '-f'.\n" );
            BLM_RETURNV(er_t, bcore_error_push_fa( TYPEOF_general_error, "\nERROR: #<sc_t>\n", s->sc ))
        }
    BLM_DOWN();}
    
    return  0;
}

er_t xoico_compiler_s_parse( xoico_compiler_s* o, sc_t target_name, sc_t source_path, sz_t* p_target_index )
{
    // xoico_compiler.x:125:1
    BLM_INIT_LEVEL(0);
    {
        st_s* source_folder_path = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,((st_s*)(bcore_file_folder_path(source_path ))) ));
        st_s* target_path        = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,((st_s*)(st_s_create_fa( "#<sc_t>/#<sc_t>", source_folder_path->sc, target_name ))) ));
    
        sz_t target_index = -1;
        for( sz_t i = 0; i < o->size; i++ )
        {
            if( st_s_equal_st( target_path,&o->data[ i ]->path ) )
            {
                target_index = i;
                break;
            }
        }
    
        if( target_index == -1 )
        {
            xoico_target_s* target = xoico_target_s_create();
            target->compiler = o;
            st_s_copy_sc( &(target->name),target_name );
            st_s_copy(&(target->path),target_path );
            xoico_compiler_s_push_d(o,target );
            target_index = o->size - 1;
        }
    
        xoico_target_s* target = o->data[ target_index ];
        BLM_TRY(xoico_target_s_parse(target,source_path ))
        if( p_target_index ) *p_target_index = target_index;
    
        BLM_RETURNV(er_t, 0)
    } // try
}

er_t xoico_compiler_s_finalize( xoico_compiler_s* o )
{
    // xoico_compiler.x:162:1
    
    {
        for( sz_t i = 0; i < o->size; i++ ) BLM_TRY(xoico_target_s_finalize(o->data[ i ]))
    }
    return  0;
}

er_t xoico_compiler_s_expand_setup( xoico_compiler_s* o )
{
    // xoico_compiler.x:173:1
    
    {
        for( sz_t i = 0; i < o->size; i++ ) BLM_TRY(xoico_target_s_expand_setup(o->data[ i ]))
    
        /* We obtain all names from the global map.
         * This is necessary because names of reflection elements are parsed outside
         * this framework and remembered by the global map.
         */
        bcore_name_push_all( &o->name_map );
    }
    
    return  0;
}

bl_t xoico_compiler_s_to_be_modified( const xoico_compiler_s* o )
{
    // xoico_compiler.x:192:1
    
    for( sz_t i = 0; i < o->size; i++ )
    {
        if( xoico_target_s_to_be_modified(o->data[ i ]) ) return  true;
    }
    return  false;
}

er_t xoico_compiler_s_expand( xoico_compiler_s* o, bl_t* p_modified )
{
    // xoico_compiler.x:204:1
    
    {
        bl_t modified = false;
    
        BLM_TRY(xoico_compiler_s_expand_setup(o))
        for( sz_t i = 0; i < o->size; i++ ) BLM_TRY(xoico_target_s_expand_phase1(o->data[i],&modified ))
        for( sz_t i = 0; i < o->size; i++ ) BLM_TRY(xoico_target_s_expand_phase2(o->data[i],&modified ))
    
        if( p_modified ) *p_modified = modified;
        return  0;
    } // try
}

bl_t xoico_compiler_s_get_self( const xoico_compiler_s* o, tp_t type, const bcore_self_s** self )
{
    // xoico_compiler.x:221:1
    
    const xoico* item = xoico_compiler_s_get_const_item(o,type );
    if( !item ) return  false;
    
    if( item->_ == TYPEOF_xoico_stamp_s )
    {
        const xoico_stamp_s* stamp = ((const xoico_stamp_s*)(item));
        if( self ) *self = stamp->self;
        return  true;
    }
    
    return  false;
}

bl_t xoico_compiler_s_get_type_info( const xoico_compiler_s* o, tp_t type, xoico_compiler_type_info_s* info )
{
    // xoico_compiler.x:238:1
    
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
    // xoico_compiler.x:255:1
    
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
    
                case BCORE_CAPS_EXTERNAL_FUNC:
                {
                    found = false;
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
    
        if( !found )
        {
            // try function
            xoico_func_s* func = xoico_funcs_s_get_func_from_name(&(stamp->funcs),name );
            if( func )
            {
                info->type_info.typespec.type = func->global_name;
                info->type_info.typespec.indirection = 0;
                const xoico_signature_s* signature = func->signature;
                info->type_info.typespec.flag_const = ( signature->arg_o == TYPEOF_const );
                xoico_signature_s_attach( &(info->signature ),  xoico_signature_s_clone(signature));
                xoico_signature_s_relent(info->signature,self->type );
                success = true;
            }
            else // try generic types
            {
                success = false;
            }
        }
        else
        {
            info->type_info.typespec.type = self_item->type;
            info->type_info.typespec.indirection = indirection;
            info->signature = NULL;
            success = true;
        }
    }
    else if( xoico_item->_ == TYPEOF_xoico_group_s )
    {
        xoico_group_s* group = ((xoico_group_s*)(xoico_item));
        if( bcore_hmap_tpvd_s_exists(&(group->hmap_feature),name ) )
        {
            info->type_info.typespec.flag_const = false;
            xoico_feature_s* feature = *bcore_hmap_tpvd_s_get(&(group->hmap_feature),name );
            if( feature->flag_a )
            {BLM_INIT_LEVEL(4);
                const xoico_signature_s* signature = &feature->signature;
                info->type_info.typespec.flag_const = ( signature->arg_o == TYPEOF_const );
                sc_t st_func_name = xoico_compiler_s_nameof(o,name );
                ASSERT( st_func_name );
                st_s* st_full_func_name = ((st_s*)BLM_LEVEL_T_PUSH(4,st_s,st_s_create()));
                st_s_copy_fa( st_full_func_name,"#<sc_t>_a_#<sc_t>", group->st_name.sc, st_func_name );
                info->type_info.typespec.type = xoico_compiler_s_entypeof(((xoico_compiler_s*)(o)),st_full_func_name->sc );
                info->type_info.typespec.indirection = 0;
                xoico_signature_s_attach( &(info->signature ),  xoico_signature_s_clone(signature));
                xoico_signature_s_relent(info->signature,group->tp_name );
                success = true;
            BLM_DOWN();}
        }
    }
    
    return  success;
}

bl_t xoico_compiler_s_get_type_array_element_info( const xoico_compiler_s* o, tp_t type, xoico_compiler_element_info_s* info )
{
    // xoico_compiler.x:376:1
    
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
            info->signature = NULL;
            success = true;
        }
    }
    
    return  success;
}

er_t xoico_compiler_s_update_target_files( xoico_compiler_s* o, bl_t* p_modified )
{
    // xoico_compiler.x:441:1
    
    bl_t modified = false;
    bl_t verbosity = o->verbosity;
    f3_t time = 0;
    
    er_t er = 0;
    ABS_TIME_OF( er = xoico_compiler_s_expand(o,&modified ), time );
    BLM_TRY(er )
    
    if( modified )
    {
        if( verbosity > 0 ) bcore_msg_fa( "XOICO: Expanded in #<f3_t> sec.\n", time );
        if( verbosity > 0 ) bcore_msg_fa( "XOICO: Files were updated. Rebuild is necessary.\n" );
    }
    
    if( p_modified ) *p_modified = modified;
    
    return  er;
}

XOILA_DEFINE_SPECT( xoico, xoico_compiler )
"{"
    "bcore_spect_header_s header;"
"}";

bl_t xoico_compiler_is_signed( sc_t file )
{
    // xoico_compiler.x:70:1
    BLM_INIT_LEVEL(0);
    bcore_source* source = BLM_A_PUSH( bcore_file_open_source(file ) );
    st_s* data = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    while( !bcore_source_a_eos( source) ) st_s_push_char( data,bcore_source_a_get_u0( source) );
    
    if( data->size < bcore_strlen( "// XOILA_OUT_SIGNATURE" ) ) BLM_RETURNV(bl_t, false)
    
    sz_t idx = data->size - 1;
    while( idx >= 0 && data->data[ idx ] != '/' ) idx--;
    if( idx > 0 ) idx--;
    
    if( st_s_find_sc( data,idx, -1, "// XOILA_OUT_SIGNATURE" ) != idx ) BLM_RETURNV(bl_t, false)
    
    tp_t hash = 0;
    st_s_parse_fa( data,idx, -1, "// XOILA_OUT_SIGNATURE #<tp_t*>", &hash );
    
    data->data[ idx ] = 0;
    
    if( hash != bcore_tp_fold_sc( bcore_tp_init(), data->sc ) ) BLM_RETURNV(bl_t, false)
    
    BLM_RETURNV(bl_t, true)
}

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
        st_s_attach( &o->root_folder, bcore_file_path_minimized(o->root_folder->sc ) );
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
    // xoico_builder.x:21:1
    BLM_INIT_LEVEL(0); {
    st_s* st_path = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    st_s_copy_sc( st_path,path );
    
    if( st_path->sc[ 0 ] != '/' )
    {
        st_s* current_folder = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
        bcore_folder_get_current( current_folder );
        st_path = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,((st_s*)(st_s_create_fa( "#<sc_t>/#<sc_t>", current_folder->sc, st_path->sc )))));
    }
    
    st_path = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,((st_s*)(bcore_file_path_minimized(st_path->sc )))));
    
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
            if( st_s_equal_st( &(match->full_path_),&o->full_path_ ) )
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
    {BLM_INIT_LEVEL(4);
        if( !o->dependencies_target_ ) o->dependencies_target_ = xoico_builder_arr_target_s_create();
    
        st_s* file_path = ((st_s*)BLM_LEVEL_T_PUSH(4,st_s,st_s_create()));
        if( e->sc[ 0 ] != '/' )
        {
            if( o->root_folder ) st_s_push_fa( file_path,"#<sc_t>/", o->root_folder->sc );
        }
    
        bl_t dep_readonly = o->readonly;
    
        bcore_source* source = ((bcore_source*)BLM_LEVEL_A_PUSH(4,((bcore_source*)(bcore_source_string_s_create_sc( e->sc )))));
        BLM_TRY(bcore_source_a_parse_em_fa( source," #:until':'", file_path ) )
    
        /// remove trailing spaces
        while( file_path->sc[ 0 ] == ' ' || file_path->sc[ 0 ] == '\t' ) st_s_pop_char( file_path);
    
        if( bcore_source_a_parse_bl_fa( source, "#?':'" ) )
        {
            if( bcore_source_a_parse_bl_fa( source," #?w'readonly'" ) )
            {
                dep_readonly = true;
            }
            else
            {
                BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Syntax error in dependency declaration." ))
            }
        }
    
        xoico_builder_target_s* target = xoico_builder_arr_target_s_push_d( o->dependencies_target_,xoico_builder_target_s_create() );
        target->parent_ = o;
    
        BLM_TRY(xoico_builder_target_s_load(target,dep_readonly, file_path->sc ))
    BLM_DOWN();}
    
    }}BLM_RETURNV(er_t, 0)
    
    } /* try */
}

er_t xoico_builder_target_s_build( xoico_builder_target_s* o )
{
    // xoico_builder.x:100:1
    BLM_INIT_LEVEL(0); {
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
        xoico_builder_target_s* target = *bcore_hmap_tpvd_s_get(o->root_->hmap_built_target_,tp_target_name );
        o->target_index_ = target->target_index_;
        BLM_RETURNV(er_t, 0)
    }
    
    bcore_hmap_tpvd_s_set(o->root_->hmap_built_target_,tp_target_name, ( vd_t )o );
    
    o->target_index_ = -1;
    
    bcore_msg_fa( "XOICO: compiling #<sc_t>\n", o->full_path_.sc );
    
    {const bcore_arr_st_s* __a=&(o->sources );if(__a)for(sz_t __i=0; __i<__a->size; __i++){st_s* e=__a->data[__i];
    {BLM_INIT_LEVEL(4);
        st_s* file_path = ((st_s*)BLM_LEVEL_T_PUSH(4,st_s,st_s_create()));
        if( e->sc[ 0 ] != '/' )
        {
            if( o->root_folder ) st_s_push_fa( file_path,"#<sc_t>/", o->root_folder->sc );
        }
        st_s_push_fa( file_path,"#<sc_t>", e->sc );
    
        ASSERT( o->name );
        ASSERT( o->extension );
        st_s* xoi_target_name = ((st_s*)BLM_LEVEL_T_PUSH(4,st_s,((st_s*)(st_s_create_fa( "#<sc_t>_#<sc_t>", o->name->sc, o->extension->sc )))));
    
        sz_t index = -1;
    
        BLM_TRY(xoico_compiler_s_parse(o->compiler,xoi_target_name->sc, file_path->sc, &index ))
    
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
        st_s* signal_handler = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,((st_s*)(st_s_create_fa( "#<sc_t>_general_signal_handler", o->name->sc )))));
        if( o->signal_handler ) st_s_copy(signal_handler,o->signal_handler );
        st_s_copy_sc( &(target->signal_handler_name),signal_handler->sc );
        target->readonly = o->readonly;
        xoico_cengine_a_attach( &(target->cengine ), (xoico_cengine*)( ((xoico_cengine*)bcore_fork(o->cengine))));
    }
    
    BLM_RETURNV(er_t, 0)
    } /* try */
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
    // xoico_builder.x:187:1
     {
    xoico_builder_target_s_attach( &(o->target ),  xoico_builder_target_s_create());
    BLM_TRY(xoico_builder_target_s_load(o->target,false, path ))
    o->target->compiler = o->compiler;
    BLM_TRY(xoico_builder_target_s_build(o->target))
    BLM_TRY(xoico_compiler_s_finalize(o->compiler))
    return  0;
    } /* try */
}

er_t xoico_builder_main_s_update( const xoico_builder_main_s* o )
{
    // xoico_builder.x:199:1
    
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
    
    sc_t name = bcore_hmap_name_s_get_sc( &o->hmap_name,type );
    if( !name ) name = xoico_compiler_s_nameof( o->compiler,type );
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
    unit->type = bcore_hmap_name_s_set_sc( &o->name_map,type );
    unit->name = bcore_hmap_name_s_set_sc( &o->name_map,name );
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
    
    return  bcore_hmap_name_s_get_sc( &o->name_map,xoico_cbeth_tn_stack_s_get_type( o,btypeof( name ) ) );
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
    
    const xoico_compiler_s* compiler = args->group->compiler;
    xoico_cbeth_tn_stack_s_clear( o );
    if( obj_type ) xoico_cbeth_tn_stack_s_push_sc( o,obj_type, obj_name, 0 );
    BFOR_EACH( i, args )
    {
        sc_t sc_type = xoico_compiler_s_nameof( compiler,args->data[ i ].typespec.type );
        sc_t sc_name = xoico_compiler_s_nameof( compiler,args->data[ i ].name );
        xoico_cbeth_tn_stack_s_push_sc( o,sc_type, sc_name, 0 );
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
    
    sc_t name = bcore_hmap_name_s_get_sc( &o->hmap_name,type );
    if( !name ) name = xoico_compiler_s_nameof( o->compiler,type );
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
    
    xoico_cgimel_stack_s_pop_level( &o->stack,o->level );
    o->level--;
}

void xoico_cgimel_s_push_typedecl( xoico_cgimel_s* o, const xoico_typespec_s* typespec, tp_t name )
{
    // xoico_cgimel.h:132:5
    
    BLM_INIT();
    xoico_cgimel_stack_unit_s* unit = BLM_CREATE( xoico_cgimel_stack_unit_s );
    unit->level = o->level;
    unit->name = name;
    xoico_typespec_s_copy( &unit->typespec,typespec );
    xoico_cgimel_stack_s_push_unit( &o->stack,unit );
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
    // xoico_cdaleth.h:215:5
    
    return  xoico_cdaleth_s_is_builtin_func(o,tp_identifier ) ||
           xoico_cdaleth_s_is_control_name(o,tp_identifier ) ||
           tp_identifier == TYPEOF_verbatim_C;
}

sc_t xoico_cdaleth_s_nameof( xoico_cdaleth_s* o, tp_t type )
{
    // xoico_cdaleth.h:224:5
    
    sc_t name = bcore_hmap_name_s_get_sc(&(o->hmap_name),type );
    if( !name ) name = xoico_compiler_s_nameof(o->compiler,type );
    return  name;
}

void xoico_cdaleth_s_init_level0( xoico_cdaleth_s* o )
{
    // xoico_cdaleth.h:231:5
    
    xoico_cdaleth_stack_block_s_clear(&(o->stack_block));
    xoico_cdaleth_stack_block_s_push(&(o->stack_block));
    o->level = 0;
}

void xoico_cdaleth_s_inc_block( xoico_cdaleth_s* o )
{
    // xoico_cdaleth.h:238:5
    
    xoico_cdaleth_stack_block_s_push(&(o->stack_block));
    o->level++;
    xoico_cdaleth_s_stack_block_get_top_unit(o)->level = o->level;
}

void xoico_cdaleth_s_dec_block( xoico_cdaleth_s* o )
{
    // xoico_cdaleth.h:245:5
    
    xoico_cdaleth_stack_var_s_pop_level(&(o->stack_var),o->level );
    o->level--;
    ASSERT( o->level >= 0 );
    xoico_cdaleth_stack_block_s_pop(&(o->stack_block));
}

xoico_cdaleth_stack_block_unit_s* xoico_cdaleth_s_stack_block_get_top_unit( xoico_cdaleth_s* o )
{
    // xoico_cdaleth.h:253:5
    
    return  o->stack_block.adl.data[ o->stack_block.adl.size - 1 ];
}

xoico_cdaleth_stack_block_unit_s* xoico_cdaleth_s_stack_block_get_bottom_unit( xoico_cdaleth_s* o )
{
    // xoico_cdaleth.h:258:5
    
    return  o->stack_block.adl.data[ 0 ];
}

xoico_cdaleth_stack_block_unit_s* xoico_cdaleth_s_stack_block_get_level_unit( xoico_cdaleth_s* o, sz_t level )
{
    // xoico_cdaleth.h:263:5
    
    {const xoico_cdaleth_stack_block_unit_adl_s* __a=&(o->stack_block.adl );if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_cdaleth_stack_block_unit_s* e=__a->data[__i]; if( e->level == level ) return  e;
    }}ERR_fa( "Level #<sz_t> not found.", level );
    return  NULL;
}

void xoico_cdaleth_s_push_typedecl( xoico_cdaleth_s* o, const xoico_typespec_s* typespec, tp_t name )
{
    // xoico_cdaleth.h:270:5
    BLM_INIT_LEVEL(0);
    xoico_cdaleth_stack_var_unit_s* unit = ((xoico_cdaleth_stack_var_unit_s*)BLM_LEVEL_T_PUSH(0,xoico_cdaleth_stack_var_unit_s,xoico_cdaleth_stack_var_unit_s_create()));
    unit->level = o->level;
    unit->name = name;
    xoico_typespec_s_copy(&(unit->typespec),typespec );
    xoico_cdaleth_stack_var_s_push_unit(&(o->stack_var),unit );
    BLM_DOWN();
}

bl_t xoico_cdaleth_s_returns_a_value( const xoico_cdaleth_s* o )
{
    // xoico_cdaleth.h:289:5
    
    return  ( o->typespec_ret->type != TYPEOF_void ) || ( o->typespec_ret->indirection > 0 );
}

er_t xoico_cdaleth_s_parse( const xoico_cdaleth_s* o, bcore_source* source, sc_t format )
{
    // xoico_cdaleth.h:294:5
    
    return  bcore_source_a_parse_em_fa( source,format );
}

er_t xoico_cdaleth_s_trans( const xoico_cdaleth_s* o, bcore_source* source, sc_t format, st_s* buf )
{
    // xoico_cdaleth.h:299:5
    
    BLM_TRY(xoico_cdaleth_s_parse(o,source, format ))
    st_s_push_sc( buf,format );
    return  0;
}

tp_t xoico_cdaleth_s_get_identifier( xoico_cdaleth_s* o, bcore_source* source, bl_t take_from_source )
{
    // xoico_cdaleth.x:26:1
    BLM_INIT_LEVEL(0);
    tp_t tp_identifier = 0;
    if( bcore_source_a_parse_bl( source,"#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||[0]=='_'||[0]=='@'||[0]=='$'||([0]==':'&&([1]!=' '&&[1]!='\t'&&[1]!='\n'&&[1]!='/')))" ) )
    {
        sz_t source_index = take_from_source ? 0 : bcore_source_a_get_index( source);
        switch( bcore_source_a_inspect_char( source) )
        {
            case '@':
            {
                bcore_source_a_get_char( source);
                st_s* st_name = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
                st_s_copy(st_name,o->stamp ? &o->stamp->st_name : &o->group->st_name );
                if( bcore_source_a_parse_bl( source,"#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||[0]=='_'||([0]>='0'&&[0]<='9'))" ) )
                {
                    bcore_source_a_parse_fa( source,"#:name", st_name );
                }
                tp_identifier = xoico_cdaleth_s_entypeof(o,st_name->sc );
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
                st_s* st_name = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
                xoico_group_s_parse_name(o->group,st_name, source );
                tp_identifier = xoico_cdaleth_s_entypeof(o,st_name->sc );
            }
            break;
    
            default:
            {
                st_s* st_name = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
                bcore_source_a_parse_fa( source,"#name", st_name );
                tp_identifier = xoico_cdaleth_s_entypeof(o,st_name->sc );
            }
            break;
        }
    
        if( !take_from_source ) bcore_source_a_set_index( source,source_index );
    }
    
    BLM_RETURNV(tp_t, tp_identifier)
}

er_t xoico_cdaleth_s_trans_identifier( xoico_cdaleth_s* o, bcore_source* source, st_s* buf, tp_t* tp_identifier )
{
    // xoico_cdaleth.x:80:1
     {
    tp_t identifier = xoico_cdaleth_s_get_identifier(o,source, true );
    if( !identifier )
    {
        return  bcore_source_a_parse_error_fa( source,"Identifier exected" );
    }
    if( tp_identifier ) *tp_identifier = identifier;
    if( buf ) st_s_push_sc( buf,xoico_cdaleth_s_nameof(o,identifier ) );
    return  0;
    } /* try */
}

er_t xoico_cdaleth_s_trans_number_literal( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth.x:95:1
     {
    bl_t hex = false;
    if( bcore_source_a_parse_bl( source,"#?'0x'" ) )
    {
        st_s_push_sc( buf,"0x" );
        hex = true;
    }
    else if( bcore_source_a_parse_bl( source,"#?'0X'" ) )
    {
        st_s_push_sc( buf,"0X" );
        hex = true;
    }
    
    if( hex )
    {
        while( bcore_source_a_parse_bl( source,"#?(([0]>='0'&&[0]<='9')||([0]>='a'&&[0]<='f')||([0]>='A'&&[0]<='F'))" ) )
        {
            st_s_push_char( buf,bcore_source_a_get_char( source) );
        }
    }
    else // decimal
    {
        while( bcore_source_a_parse_bl( source,"#?([0]>='0'&&[0]<='9')" ) )
        {
            st_s_push_char( buf,bcore_source_a_get_char( source) );
        }
    }
    
    bl_t fraction = false;
    
    if( bcore_source_a_parse_bl( source,"#?([0]=='.')" ) )
    {
        st_s_push_char( buf,bcore_source_a_get_char( source) );
        fraction = true;
    }
    
    if( fraction )
    {
        while( bcore_source_a_parse_bl( source,"#?([0]>='0'&&[0]<='9')" ) )
        {
            st_s_push_char( buf,bcore_source_a_get_char( source) );
        }
    }
    
    bl_t exponent = false;
    
    if( bcore_source_a_parse_bl( source,"#?([0]=='e'&&[0]=='E')" ) )
    {
        st_s_push_char( buf,bcore_source_a_get_char( source) );
        exponent = true;
    }
    
    if( exponent )
    {
        if( bcore_source_a_parse_bl( source,"#?([0]=='+'||[0]=='-')" ) )
        {
            st_s_push_char( buf,bcore_source_a_get_char( source) );
        }
    
        while( bcore_source_a_parse_bl( source,"#?([0]>='0'&&[0]<='9')" ) )
        {
            st_s_push_char( buf,bcore_source_a_get_char( source) );
        }
    }
    
    // suffix
    while( bcore_source_a_parse_bl( source,"#?([0]=='l'||[0]=='L'||[0]=='u'||[0]=='U'||[0]=='f'||[0]=='F')" ) )
    {
        st_s_push_char( buf,bcore_source_a_get_char( source) );
    }
    
    return  0;
    } /* try */
}

er_t xoico_cdaleth_s_trans_string_literal( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth.x:173:1
     {
    BLM_TRY(xoico_cdaleth_s_trans(o,source, "\"", buf ))
    
    while( !bcore_source_a_eos( source) && !bcore_source_a_parse_bl( source,"#=?'\"'" ) )
    {
        if( bcore_source_a_parse_bl( source,"#?'\\'" ) ) st_s_push_char( buf,'\\' );
        st_s_push_char( buf,bcore_source_a_get_char( source) );
    }
    
    BLM_TRY(xoico_cdaleth_s_trans(o,source, "\"", buf ))
    return  0;
    } /* try */
}

er_t xoico_cdaleth_s_trans_char_literal( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth.x:190:1
    
    {
        BLM_TRY(xoico_cdaleth_s_trans(o,source, "'", buf ))
    
        while( !bcore_source_a_eos( source) && !bcore_source_a_parse_bl( source,"#=?|'|" ) )
        {
            if( bcore_source_a_parse_bl( source,"#?'\\'" ) ) st_s_push_char( buf,'\\' );
            st_s_push_char( buf,bcore_source_a_get_char( source) );
        }
    
        BLM_TRY(xoico_cdaleth_s_trans(o,source, "'", buf ))
        return  0;
    } /* try */
}

er_t xoico_cdaleth_s_trans_whitespace( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth.x:209:1
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
                if( buf )  st_s_push_char( buf,c );
            }
            break;
    
            case '/':
            {
                if( bcore_source_a_parse_bl( source,"#?'//'" ) )
                {
                    if( buf ) st_s_push_sc( buf,"//" );
                    while( !bcore_source_a_eos( source) )
                    {
                        char c =  bcore_source_a_get_char( source);
                        if( buf ) st_s_push_char( buf,c );
                        if( c == '\n' ) break;
                    }
                }
                else if( bcore_source_a_parse_bl( source,"#?'/*'" ) )
                {
                    if( buf ) st_s_push_sc( buf,"/*" );
                    while( !bcore_source_a_eos( source) )
                    {
                        if( bcore_source_a_parse_bl( source,"#?'*/'" ) )
                        {
                            if( buf ) st_s_push_sc( buf,"*/" );
                            break;
                        }
                        char c =  bcore_source_a_get_char( source);
                        if( buf ) st_s_push_char( buf,c );
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
    } /* try */
}

er_t xoico_cdaleth_s_trans_preprocessor( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth.x:271:1
     {
    BLM_TRY(xoico_cdaleth_s_parse(o,source, "##" ))
    st_s_push_sc( buf,"#" );
    while( !bcore_source_a_eos( source) )
    {
        char c = bcore_source_a_get_char( source);
        st_s_push_char( buf,c );
        if( c == '\\' && bcore_source_a_inspect_char( source) == '\n' ) st_s_push_char( buf,bcore_source_a_get_char( source) );
        if( c == '\n' ) break;
    }
    return  0;
    } /* try */
}

tp_t xoico_cdaleth_s_trans_inert_operator( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth.x:288:1
    
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
            st_s_push_char( buf,bcore_source_a_get_char( source) );
            return  1;
        }
        break;
    
        default: break;
    }
    
    return  false;
}

er_t xoico_cdaleth_s_adapt_expression( xoico_cdaleth_s* o, bcore_source* source, const xoico_typespec_s* typespec_expr, const xoico_typespec_s* typespec_target, const st_s* expr, st_s* buf )
{
    // xoico_cdaleth.x:330:1
     {
    if( !typespec_expr->type )
    {
        return  bcore_source_a_parse_error_fa( source,"xoico_cdaleth_s_adapt_expression: no type specified.",
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
        st_s_push_fa( buf,"#<st_s*>", expr );
    }
    else if( typespec_target->indirection == typespec_expr->indirection + 1 )
    {
        if( typespec_expr->flag_addressable )
        {
            st_s_push_fa( buf,"&(#<st_s*>)", expr );
        }
        else
        {
            return  bcore_source_a_parse_error_fa( source,"Increasing indirection: Expression has no address." );
        }
    }
    else if( typespec_target->indirection == typespec_expr->indirection - 1 )
    {
        st_s_push_fa( buf,"*(#<st_s*>)", expr );
    }
    else
    {
        return  bcore_source_a_parse_error_fa( source,"Cannot adapt from expression's indirection '#<sz_t>' to target indirection '#<sz_t>'.",
            typespec_expr->indirection,
            typespec_target->indirection
        );
    }
    return  0;
    } /* try */
}

er_t xoico_cdaleth_s_trans_function_args( xoico_cdaleth_s* o, bcore_source* source, const xoico_signature_s* signature, const st_s* buf_obj_expr, const xoico_typespec_s* typespec_obj_expr, st_s* buf_out )
{
    // xoico_cdaleth.x:392:1
    BLM_INIT_LEVEL(0); {
    BLM_TRY(xoico_cdaleth_s_trans(o,source, "(", buf_out ))
    
    if( signature->arg_o )
    {
        if( !buf_obj_expr )
        {
            st_s* buf_expr                  = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
            xoico_typespec_s* typespec_expr = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
            BLM_TRY(xoico_cdaleth_s_trans_expression(o,source, buf_expr, typespec_expr ))
            buf_obj_expr = buf_expr;
            typespec_obj_expr = typespec_expr;
            if( signature->args.size > 0 ) BLM_TRY(xoico_cdaleth_s_parse(o,source, " ," ))
        }
    
        xoico_typespec_s* typespec_obj_out = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_clone(typespec_obj_expr)));
        typespec_obj_out->indirection = 1; // first argument of member functions has always indirection 1
    
        if( typespec_obj_expr->type )
        {
            BLM_TRY(xoico_cdaleth_s_adapt_expression(o,source, typespec_obj_expr, typespec_obj_out, buf_obj_expr, buf_out ))
        }
        else
        {
            st_s_push_st( buf_out,buf_obj_expr );
        }
        if( signature->args.size > 0 ) st_s_push_sc( buf_out,"," );
    }
    
    {const xoico_args_s* __a=&(signature->args );if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_arg_s* arg=&(__a->data[__i]);
    {BLM_INIT_LEVEL(4);
        st_s* buf_expr                  = ((st_s*)BLM_LEVEL_T_PUSH(4,st_s,st_s_create()));
        xoico_typespec_s* typespec_expr = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(4,xoico_typespec_s,xoico_typespec_s_create()));
        BLM_TRY(xoico_cdaleth_s_parse(o,source, " " ))
        if( __i > 0 ) BLM_TRY(xoico_cdaleth_s_parse(o,source, " ," ))
        BLM_TRY(xoico_cdaleth_s_trans_expression(o,source, buf_expr, typespec_expr ))
        if( __i > 0 ) st_s_push_sc( buf_out,"," );
        if( typespec_expr->type )
        {
            BLM_TRY(xoico_cdaleth_s_adapt_expression(o,source, typespec_expr, &arg->typespec, buf_expr, buf_out ))
        }
        else
        {
            st_s_push_st( buf_out,buf_expr );
        }
    BLM_DOWN();}
    
    }}BLM_TRY(xoico_cdaleth_s_parse(o,source, " " ))
    BLM_TRY(xoico_cdaleth_s_trans(o,source, ")", buf_out ))
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_cdaleth_s_trans_typespec_member( xoico_cdaleth_s* o, bcore_source* source, st_s* buf, const xoico_typespec_s* in_typespec, xoico_typespec_s* out_typespec )
{
    // xoico_cdaleth.x:457:1
    BLM_INIT_LEVEL(0); {
    if( bcore_source_a_parse_bl_fa( source,"#?'->'" ) )
    {
        if( in_typespec->indirection != 1 )
        {
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Given indirection is '#<sz_t>'. '->' can only be used at indirection '1'.", in_typespec->indirection ))
        }
    }
    else
    {
        BLM_TRY(xoico_cdaleth_s_parse(o,source, "." ))
    }
    BLM_TRY(xoico_cdaleth_s_parse(o,source, " " ))
    xoico_compiler_element_info_s* info = ((xoico_compiler_element_info_s*)BLM_LEVEL_T_PUSH(0,xoico_compiler_element_info_s,xoico_compiler_element_info_s_create()));
    if( bcore_source_a_parse_bl_fa( source,"#=?'['" ) || bcore_source_a_parse_bl_fa( source,"#=?'?['" ) ) // array subscript
    {
        bl_t bounds_check = false;
        if( bcore_source_a_parse_bl_fa( source,"#=?'?'" ) )
        {
            BLM_TRY(xoico_cdaleth_s_parse(o,source, "?[" ))
            bounds_check = true;
        }
        else
        {
            BLM_TRY(xoico_cdaleth_s_parse(o,source, "[" ))
        }
    
        if( bounds_check ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Bounds check not yet available." ))
    
        if( in_typespec->indirection > 1 )
        {
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Resolving subscript: Indirection '#<sz_t>' is too large.",
                in_typespec->indirection
            ))
        }
    
        st_s_push_fa( buf,"#<sc_t>data[", ( in_typespec->indirection == 1 ) ? "->" : "." );
        BLM_TRY(xoico_cdaleth_s_trans_expression(o,source, buf, NULL ))
        BLM_TRY(xoico_cdaleth_s_parse(o,source, "]" ))
        st_s_push_sc( buf,"]" );
    
        if( xoico_compiler_s_get_type_array_element_info(o->compiler,in_typespec->type, info ) )
        {
            BLM_TRY(xoico_cdaleth_s_trans_typespec_expression(o,source, buf, &info->type_info.typespec, out_typespec ))
        }
        else
        {
            BLM_TRY(xoico_cdaleth_s_trans_expression(o,source, buf, NULL ))
        }
    }
    else // member (object or function)
    {
        st_s* buf_local = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
        tp_t tp_identifier = 0;
        BLM_TRY(xoico_cdaleth_s_trans_identifier(o,source, buf_local, &tp_identifier ))
        BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf_local ))
    
        // builtin functions ...
        if( xoico_cdaleth_s_is_builtin_func(o,tp_identifier ) )
        {
            xoico_typespec_s* typespec_builtin = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
            BLM_TRY(xoico_cdaleth_s_trans_builtin(o,tp_identifier, source, buf, in_typespec, buf_local, typespec_builtin ))
            st_s_copy(buf,buf_local );
            BLM_TRY(xoico_cdaleth_s_trans_typespec_expression(o,source, buf, typespec_builtin, out_typespec ))
        }
        else if( xoico_compiler_s_get_type_element_info(o->compiler,in_typespec->type, tp_identifier, info ) )
        {
            if( info->signature ) // member function
            {
                sc_t sc_func_name = xoico_cdaleth_s_nameof(o,info->type_info.typespec.type );
                ASSERT( sc_func_name );
                st_s* arg_obj = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_clone(buf)));
                st_s_copy_fa( buf,"#<sc_t>", sc_func_name );
                BLM_TRY(xoico_cdaleth_s_trans_function_args(o,source, info->signature, arg_obj, in_typespec, buf ))
                BLM_TRY(xoico_cdaleth_s_trans_typespec_expression(o,source, buf, &info->signature->typespec_ret, out_typespec ))
            }
            else // traced member element
            {
                if( in_typespec->indirection > 1 )
                {
                    BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Dereferencing #<sc_t>: Indirection '#<sz_t>' is too large.",
                        xoico_cdaleth_s_nameof(o,tp_identifier ),
                        in_typespec->indirection
                    ))
                }
                st_s_push_fa( buf,"#<sc_t>#<sc_t>", ( in_typespec->indirection == 1 ) ? "->" : ".", buf_local->sc );
                BLM_TRY(xoico_cdaleth_s_trans_typespec_expression(o,source, buf, &info->type_info.typespec, out_typespec ))
            }
        }
        else if( bcore_source_a_parse_bl_fa( source,"#?'('" ) ) // untraced member function
        {
            st_s* arg_obj = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_clone(buf)));
            st_s_clear( buf );
    
            /// Untraced member functions of a group are always treated as 'aware'
            if( xoico_cdaleth_s_is_group(o,in_typespec->type ) )
            {
                st_s_copy_fa
                (
                    buf,
                    "#<sc_t>_a_#<sc_t>( ",
                    xoico_cdaleth_s_nameof(o,in_typespec->type ),
                    xoico_cdaleth_s_nameof(o,tp_identifier )
                );
            }
            else
            {
                st_s_copy_fa
                (
                    buf,
                    "#<sc_t>_#<sc_t>( ",
                    xoico_cdaleth_s_nameof(o,in_typespec->type ),
                    xoico_cdaleth_s_nameof(o,tp_identifier )
                );
            }
    
            {
                xoico_typespec_s* typespec_obj = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_clone(in_typespec)));
                typespec_obj->indirection = 1; // first argument of member functions
                BLM_TRY(xoico_cdaleth_s_adapt_expression(o,source, in_typespec, typespec_obj, arg_obj, buf ))
            }
    
            bl_t first = true;
            BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf_local ))
            while( !bcore_source_a_eos( source) )
            {BLM_INIT_LEVEL(5);
                if( bcore_source_a_parse_bl_fa( source,"#=?')'" ) ) BLM_BREAK_LEVEL(5);
    
                st_s* buf_expr = ((st_s*)BLM_LEVEL_T_PUSH(5,st_s,st_s_create()));
                if( !first ) BLM_TRY(xoico_cdaleth_s_parse(o,source, "," ))
                BLM_TRY(xoico_cdaleth_s_trans_expression(o,source, buf_expr, NULL ))
                BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf_expr ))
                st_s_push_fa( buf,"," );
                st_s_push_fa( buf,"#<sc_t>", buf_expr->sc );
                first = false;
            BLM_DOWN();}
    
            BLM_TRY(xoico_cdaleth_s_parse(o,source, ")" ))
            st_s_push_sc( buf,")" );
    
            BLM_TRY(xoico_cdaleth_s_trans_expression(o,source, buf, NULL ))
        }
        else // untraced member element
        {
            st_s_push_fa( buf,"#<sc_t>#<sc_t>", ( in_typespec->indirection == 1 ) ? "->" : ".", buf_local->sc );
            BLM_TRY(xoico_cdaleth_s_trans_expression(o,source, buf, NULL ))
        }
    }
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_cdaleth_s_trans_typespec_array_subscript( xoico_cdaleth_s* o, bcore_source* source, st_s* buf, const xoico_typespec_s* in_typespec, xoico_typespec_s* out_typespec )
{
    // xoico_cdaleth.x:625:1
    BLM_INIT_LEVEL(0); {
    BLM_TRY(xoico_cdaleth_s_parse(o,source, "[" ))
    if( in_typespec->indirection == 0 )
    {
        if( in_typespec->type != TYPEOF_sc_t && in_typespec->type != TYPEOF_sd_t )
        {
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Array subscript requires indirection >= 1." ))
        }
    }
    st_s_push_sc( buf,"[" );
    BLM_TRY(xoico_cdaleth_s_trans_expression(o,source, buf, NULL ))
    BLM_TRY(xoico_cdaleth_s_parse(o,source, "]" ))
    st_s_push_sc( buf,"]" );
    
    xoico_typespec_s* typespec = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_clone(in_typespec)));
    if( in_typespec->type != TYPEOF_sc_t && in_typespec->type != TYPEOF_sd_t )
    {
        typespec->indirection--;
    }
    BLM_TRY(xoico_cdaleth_s_trans_typespec_expression(o,source, buf, typespec, out_typespec ))
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_cdaleth_s_trans_typespec_create( xoico_cdaleth_s* o, bcore_source* source, st_s* buf, const xoico_typespec_s* in_typespec, xoico_typespec_s* out_typespec )
{
    // xoico_cdaleth.x:661:1
    BLM_INIT_LEVEL(0); {
    BLM_TRY(xoico_cdaleth_s_parse(o,source, "!" ))
    
    //ignore in case indirection is 0;
    if( in_typespec->indirection > 0 )
    {
        if( !( in_typespec->indirection == 1 && in_typespec->flag_addressable ) )
        {
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Create-Operator requires lvalue with addressable indirection of 1." ))
        }
    
        if( xoico_cdaleth_s_is_group( o,in_typespec->type ) )
        {
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Create-Operator: lvalue is a group." ))
        }
    
        st_s* arg_obj = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_clone(buf)));
        st_s_clear( buf);
    
        sc_t sc_type = xoico_cdaleth_s_nameof(o,in_typespec->type );
        st_s_push_fa( buf,"BCORE_PASS_CREATE(#<sc_t>,#<sc_t>)", sc_type, arg_obj->sc );
    }
    
    BLM_TRY(xoico_cdaleth_s_trans_typespec_expression(o,source, buf, in_typespec, out_typespec ))
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_cdaleth_s_trans_typespec_test_presence( xoico_cdaleth_s* o, bcore_source* source, st_s* buf, const xoico_typespec_s* in_typespec, xoico_typespec_s* out_typespec )
{
    // xoico_cdaleth.x:701:1
    BLM_INIT_LEVEL(0); {
    BLM_TRY(xoico_cdaleth_s_parse(o,source, "?" ))
    
    //ignore in case indirection is 0;
    if( in_typespec->indirection > 0 )
    {
        if( in_typespec->indirection != 1 )
        {
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Test-Operator requires lvalue with indirection of 1." ))
        }
    
        st_s* arg_obj = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_clone(buf)));
        st_s_clear( buf );
    
        sc_t sc_type = xoico_cdaleth_s_nameof(o,in_typespec->type );
        st_s_push_fa( buf,"BCORE_PASS_TEST(#<sc_t>,#<sc_t>)", sc_type, arg_obj->sc );
    }
    
    BLM_TRY(xoico_cdaleth_s_trans_typespec_expression(o,source, buf, in_typespec, out_typespec ))
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_cdaleth_s_trans_typespec_attach( xoico_cdaleth_s* o, bcore_source* source, st_s* buf, const xoico_typespec_s* in_typespec, xoico_typespec_s* out_typespec )
{
    // xoico_cdaleth.x:736:1
    BLM_INIT_LEVEL(0); {
    if( !( in_typespec->indirection == 1 && in_typespec->flag_addressable ) )
    {
        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Attach-Operator requires lvalue with addressable indirection of 1" ))
    }
    
    BLM_TRY(xoico_cdaleth_s_parse(o,source, "=<" ))
    
    st_s* arg_obj = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_clone(buf)));
    st_s_clear( buf);
    
    sc_t sc_type = xoico_cdaleth_s_nameof(o,in_typespec->type );
    st_s_push_fa( buf,"#<sc_t>", sc_type );
    
    xoico_typespec_s* typespec_rval = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
    if( xoico_cdaleth_s_is_group(o,in_typespec->type ) )
    {
        st_s_push_sc( buf,"_a" );
        st_s_push_fa( buf,"_attach( &(#<sc_t>), (#<sc_t>*)", arg_obj->sc, sc_type );
        st_s_push_fa( buf,"(" );
        BLM_TRY(xoico_cdaleth_s_trans_expression(o,source, buf, typespec_rval ))
        st_s_push_fa( buf,"))" );
    }
    else
    {
        st_s_push_fa( buf,"_attach( &(#<sc_t>), ", arg_obj->sc );
        BLM_TRY(xoico_cdaleth_s_trans_expression(o,source, buf, typespec_rval ))
        st_s_push_fa( buf,")" );
    }
    
    if( typespec_rval->type && typespec_rval->indirection != 1 )
    {
        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Attach operator requires rvalue with indirection '1'" ))
    }
    
    if( out_typespec ) xoico_typespec_s_copy(out_typespec,in_typespec );
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_cdaleth_s_trans_typespec_ternary_branch( xoico_cdaleth_s* o, bcore_source* source, st_s* buf, const xoico_typespec_s* in_typespec, xoico_typespec_s* out_typespec )
{
    // xoico_cdaleth.x:788:1
    BLM_INIT_LEVEL(0); {
    BLM_TRY(xoico_cdaleth_s_parse(o,source, "?" ))
    st_s_push_sc( buf,"?" );
    xoico_typespec_s* typespec_true  = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
    
    BLM_TRY(xoico_cdaleth_s_trans_expression(o,source, buf, typespec_true ))
    BLM_TRY(xoico_cdaleth_s_parse(o,source, ": " ))
    st_s_push_sc( buf,": " );
    BLM_TRY(xoico_cdaleth_s_trans_expression(o,source, buf, NULL ))
    
    if( out_typespec && typespec_true->type )
    {
        xoico_typespec_s_copy(out_typespec,typespec_true );
        out_typespec->flag_addressable = false;
    }
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_cdaleth_s_trans_typespec_expression( xoico_cdaleth_s* o, bcore_source* source, st_s* buf, const xoico_typespec_s* in_typespec, xoico_typespec_s* out_typespec )
{
    // xoico_cdaleth.x:819:1
     {
    if( out_typespec ) out_typespec->type = 0;
    BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf ))
    
    u0_t c[ 2 ];
    bcore_source_a_inspect_data( source,c, sizeof( c ) );
    
    if( c[0] == '.' || ( c[0] == '-' && c[1] == '>' ) )
    {
        BLM_TRY(xoico_cdaleth_s_trans_typespec_member(o,source, buf, in_typespec, out_typespec ))
    }
    else if( c[0] == '[' )
    {
        BLM_TRY(xoico_cdaleth_s_trans_typespec_array_subscript(o,source, buf, in_typespec, out_typespec ))
    }
    // create if not present
    else if( c[0] =='!' && c[1] != '=' )
    {
        BLM_TRY(xoico_cdaleth_s_trans_typespec_create(o,source, buf, in_typespec, out_typespec ))
    }
    // test for presence
    else if( c[0] == '?' && c[1] == '.' )
    {
        BLM_TRY(xoico_cdaleth_s_trans_typespec_test_presence(o,source, buf, in_typespec, out_typespec ))
    }
    // attach (detach)
    else if( c[0] == '=' && c[1] == '<' )
    {
        BLM_TRY(xoico_cdaleth_s_trans_typespec_attach(o,source, buf, in_typespec, out_typespec ))
    }
    // ternary branch operator
    else if( c[0] == '?' )
    {
        BLM_TRY(xoico_cdaleth_s_trans_typespec_ternary_branch(o,source, buf, in_typespec, out_typespec ))
    }
    else if( out_typespec )
    {
        xoico_typespec_s_copy(out_typespec,in_typespec );
    }
    
    return  0;
    } /* try */
}

er_t xoico_cdaleth_s_trans_member( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth.x:865:1
     {
    if(      bcore_source_a_parse_bl_fa( source,"#?'.'"  ) ) st_s_push_sc( buf,"." );
    else if( bcore_source_a_parse_bl_fa( source,"#?'->'" ) ) st_s_push_sc( buf,"->" );
    
    BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf ))
    tp_t tp_identifier = xoico_cdaleth_s_get_identifier(o,source, false );
    
    if( xoico_cdaleth_s_is_builtin_func(o,tp_identifier ) )
    {
        return  bcore_source_a_parse_error_fa( source,"Expression before '#<sc_t>' not tractable\n", xoico_cdaleth_s_nameof(o,tp_identifier ) );
    }
    
    BLM_TRY(xoico_cdaleth_s_trans_identifier(o,source, buf, NULL ))
    BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf ))
    if( bcore_source_a_parse_bl_fa( source,"#?'('") )
    {
        return  bcore_source_a_parse_error_fa( source,"Untraced member function '#<sc_t>'\n", xoico_cdaleth_s_nameof(o,tp_identifier ) );
    }
    return  0;
    } /* try */
}

er_t xoico_cdaleth_s_try_take_typespec( xoico_cdaleth_s* o, bcore_source* source, xoico_typespec_s* typespec, bl_t require_tractable_type, bl_t* success )
{
    // xoico_cdaleth.x:902:1
     {
    if( success ) *success = false;
    
    sz_t index = bcore_source_a_get_index( source);
    
    BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, NULL ))
    tp_t tp_identifier = xoico_cdaleth_s_get_identifier(o,source, true );
    
    if( !tp_identifier )
    {
        bcore_source_a_set_index( source,index );
        return  0;
    }
    
    BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, NULL ))
    
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
        if( bcore_source_a_parse_bl_fa( source,"#?'('" ) )
        {
            bcore_source_a_set_index( source,index );
            return  0;
        }
    
        BLM_TRY(xoico_cdaleth_s_trans_identifier(o,source, NULL, &tp_identifier ))
        BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, NULL ))
    }
    
    typespec->type = tp_identifier;
    while( bcore_source_a_parse_bl_fa( source,"#?'*'" ) )
    {
        typespec->indirection++;
        BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, NULL ))
    }
    
    if( require_tractable_type )
    {
        if( !( tp_identifier == TYPEOF_type_deduce || xoico_cdaleth_s_is_type(o,tp_identifier ) ) )
        {
            bcore_source_a_set_index( source,index );
            return  0;
        }
    }
    
    if( success ) *success = true;
    return  0;
    } /* try */
}

er_t xoico_cdaleth_s_take_typespec( xoico_cdaleth_s* o, bcore_source* source, xoico_typespec_s* typespec, bl_t require_tractable_type )
{
    // xoico_cdaleth.x:974:1
     {
    bl_t success = false;
    BLM_TRY(xoico_cdaleth_s_try_take_typespec(o,source, typespec, require_tractable_type, &success ))
    
    if( !success )
    {
        if( require_tractable_type )
        {
            return  bcore_source_a_parse_error_fa( source,"Typespec: Syntax error or intractable type." );
        }
        else
        {
            return  bcore_source_a_parse_error_fa( source,"Typespec: Syntax error." );
        }
    }
    
    return  0;
    } /* try */
}

er_t xoico_cdaleth_s_push_typespec( xoico_cdaleth_s* o, const xoico_typespec_s* typespec, st_s* buf )
{
    // xoico_cdaleth.x:1004:1
    BLM_INIT_LEVEL(0); {
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
    
    st_s* st_type = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,((st_s*)(st_s_create_sc( xoico_cdaleth_s_nameof(o,type ) )))));
    
    if( st_type->size == 0 )
    {
        ERR_fa( "Type has no name." );
    }
    
    sc_t sc_type = st_type->sc;
    if( typespec->flag_static   ) st_s_push_fa( buf,"static " );
    if( typespec->flag_const    ) st_s_push_fa( buf,"const " );
    if( typespec->flag_volatile ) st_s_push_fa( buf,"volatile " );
    st_s_push_fa( buf, "#<sc_t>", sc_type );
    
    for( sz_t i = 0; i < typespec->indirection; i++ ) st_s_push_fa( buf,"*" );
    if( typespec->flag_restrict ) st_s_push_fa( buf,"restrict " );
    
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_cdaleth_s_trans_type( xoico_cdaleth_s* o, bcore_source* source, st_s* buf, xoico_typespec_s* out_typespec )
{
    // xoico_cdaleth.x:1051:1
    BLM_INIT_LEVEL(0); {
    st_s* buf_type = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    tp_t tp_identifier;
    BLM_TRY(xoico_cdaleth_s_trans_identifier(o,source, buf_type, &tp_identifier ))
    BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf_type ))
    if( bcore_source_a_parse_bl_fa( source,"#?'!'" ) )
    {
        if( xoico_cdaleth_s_is_group(o,tp_identifier ) )
        {
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Operator '!': lvalue is a group." ))
        }
        st_s_push_fa( buf,"#<sc_t>_create()", xoico_cdaleth_s_nameof(o,tp_identifier ) );
        xoico_typespec_s* typespec = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
        typespec->type = tp_identifier;
        typespec->indirection = 1;
        typespec->flag_addressable = false;
        BLM_TRY(xoico_cdaleth_s_trans_typespec_expression(o,source, buf, typespec, out_typespec ))
    }
    else
    {
        st_s_push_st( buf,buf_type );
    }
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_cdaleth_s_trans_func( xoico_cdaleth_s* o, bcore_source* source, st_s* buf, xoico_typespec_s* out_typespec )
{
    // xoico_cdaleth.x:1088:1
     {
    tp_t tp_identifier = 0;
    BLM_TRY(xoico_cdaleth_s_trans_identifier(o,source, buf, &tp_identifier ))
    BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf ))
    if( bcore_source_a_parse_bl_fa( source,"#=?'('" ) ) // actual function call
    {
        const xoico_func_s* func = xoico_cdaleth_s_get_func(o,tp_identifier );
        if( !func->signature )
        {
            return  bcore_source_a_parse_error_fa( source,"Function #<sc_t> has no signature.", xoico_cdaleth_s_nameof(o,tp_identifier ) );
        }
        BLM_TRY(xoico_cdaleth_s_trans_function_args(o,source, func->signature, NULL, NULL, buf ))
        BLM_TRY(xoico_cdaleth_s_trans_typespec_expression(o,source, buf,&( func->signature->typespec_ret), out_typespec ))
    }
    return  0;
    } /* try */
}

er_t xoico_cdaleth_s_trans_ternary_branch( xoico_cdaleth_s* o, bcore_source* source, st_s* buf, xoico_typespec_s* out_typespec )
{
    // xoico_cdaleth.x:1117:1
     {
    BLM_TRY(xoico_cdaleth_s_parse(o,source, "?" ))
    st_s_push_sc( buf,"?" );
    BLM_TRY(xoico_cdaleth_s_trans_expression(o,source, buf, NULL ))
    BLM_TRY(xoico_cdaleth_s_trans(o,source, ": ", buf ))
    BLM_TRY(xoico_cdaleth_s_trans_expression(o,source, buf, NULL ))
    return  0;
    } /* try */
}

er_t xoico_cdaleth_s_trans_bracket( xoico_cdaleth_s* o, bcore_source* source, st_s* buf, xoico_typespec_s* out_typespec )
{
    // xoico_cdaleth.x:1138:1
    BLM_INIT_LEVEL(0); {
    xoico_typespec_s* typespec_bracket = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
    BLM_TRY(xoico_cdaleth_s_parse(o,source, "(" ))
    st_s_push_char( buf,'(' );
    while( !bcore_source_a_eos( source) )
    {
        BLM_TRY(xoico_cdaleth_s_trans_expression(o,source, buf, typespec_bracket ))
        if     ( bcore_source_a_parse_bl_fa( source,"#?')'" ) ) break;
        else if( bcore_source_a_parse_bl_fa( source,"#?','" ) ) st_s_push_char( buf,',' );
        else BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Syntax error in bracket expression." ))
        typespec_bracket->type = 0;
    }
    st_s_push_char( buf,')' );
    if( typespec_bracket->type ) BLM_TRY(xoico_cdaleth_s_trans_typespec_expression(o,source, buf, typespec_bracket, out_typespec ))
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_cdaleth_s_trans_array_subscript( xoico_cdaleth_s* o, bcore_source* source, st_s* buf, xoico_typespec_s* out_typespec )
{
    // xoico_cdaleth.x:1167:1
     {
    BLM_TRY(xoico_cdaleth_s_parse(o,source, "[" ))
    st_s_push_sc( buf,"[" );
    BLM_TRY(xoico_cdaleth_s_trans_expression(o,source, buf, NULL ))
    BLM_TRY(xoico_cdaleth_s_parse(o,source, "]" ))
    st_s_push_sc( buf,"]" );
    return  0;
    } /* try */
}

er_t xoico_cdaleth_s_trans_expression( xoico_cdaleth_s* o, bcore_source* source, st_s* buf_out, xoico_typespec_s* out_typespec )
{
    // xoico_cdaleth.x:1188:1
    BLM_INIT_LEVEL(0); {
    sc_t sc_bl_end_of_expression = "#?([0]==';'||[0]=='{'||[0]=='}'||[0]==')'||[0]==']'||[0]==','||([0]==':'&&([1]==' '||[1]=='\t'||[1]=='\n'||[1]=='/')))";
    
    BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf_out ))
    
    st_s* buf = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    bl_t continuation = true;
    
    if( out_typespec ) xoico_typespec_s_reset(out_typespec);
    
    tp_t tp_identifier = xoico_cdaleth_s_get_identifier(o,source, false );
    
    if( tp_identifier )
    {
        // examples of builtin functions: scope, cast, try, fork
        if( xoico_cdaleth_s_is_builtin_func(o,tp_identifier ) )
        {
            xoico_typespec_s* typespec_builtin = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
            BLM_TRY(xoico_cdaleth_s_trans_builtin(o,tp_identifier, source, NULL, NULL, buf, typespec_builtin ))
            BLM_TRY(xoico_cdaleth_s_trans_typespec_expression(o,source, buf, typespec_builtin, out_typespec ))
        }
    
        else if( tp_identifier == TYPEOF_verbatim_C )
        {
            BLM_TRY(xoico_cdaleth_s_parse(o,source, "verbatim_C {" ))
            BLM_TRY(xoico_cdaleth_s_trans_block_inside_verbatim_c(o,source, buf ))
            BLM_TRY(xoico_cdaleth_s_parse(o,source, " }" ))
        }
    
        // a control name marks end of expression...
        else if( xoico_cdaleth_s_is_control_name(o,tp_identifier ) )
        {
            continuation = false;
        }
    
        // identifier represents a registered variable
        else if( xoico_cdaleth_s_is_var(o,tp_identifier ) )
        {
            BLM_TRY(xoico_cdaleth_s_trans_identifier(o,source, buf, NULL ))
            BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf ))
            const xoico_typespec_s* typespec_var = xoico_cdaleth_stack_var_s_get_typespec(&(o->stack_var),tp_identifier );
            BLM_TRY(xoico_cdaleth_s_trans_typespec_expression(o,source, buf, typespec_var, out_typespec ))
        }
    
        // identifier represents a type known to the compiler
        else if( xoico_cdaleth_s_is_type(o,tp_identifier ) )
        {
            BLM_TRY(xoico_cdaleth_s_trans_type(o,source, buf, out_typespec ))
        }
    
        // identifier represents a (global) function name
        else if( xoico_cdaleth_s_is_func(o,tp_identifier ) )
        {
            BLM_TRY(xoico_cdaleth_s_trans_func(o,source, buf, out_typespec ))
        }
        else
        {
            BLM_TRY(xoico_cdaleth_s_trans_identifier(o,source, buf, NULL ))
            BLM_TRY(xoico_cdaleth_s_trans_expression(o,source, buf, NULL ))
        }
    }
    
    // literals and members
    else if( bcore_source_a_parse_bl_fa( source,"#?([0]>='0'&&[0]<='9')" ) ) BLM_TRY(xoico_cdaleth_s_trans_number_literal(o,source, buf ))
    else if( bcore_source_a_parse_bl_fa( source,"#=?'\"'" )                ) BLM_TRY(xoico_cdaleth_s_trans_string_literal(o,source, buf ))
    else if( bcore_source_a_parse_bl_fa( source,"#=?|'|" )                 ) BLM_TRY(xoico_cdaleth_s_trans_char_literal(o,source, buf ))
    else if( bcore_source_a_parse_bl_fa( source,"#=?'.'" )                 ) BLM_TRY(xoico_cdaleth_s_trans_member(o,source, buf ))
    else if( bcore_source_a_parse_bl_fa( source,"#=?'->'" )                ) BLM_TRY(xoico_cdaleth_s_trans_member(o,source, buf ))
    
    else if( bcore_source_a_parse_bl_fa( source,"#=?'=<'" )                ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Attach operator: Expression not tractable." ))
    else if( xoico_cdaleth_s_trans_inert_operator(o,source, buf )          ) {} // inert operators are not interpreted by cdaleth and passed to the c-compiler
    
    // ternary branch operator
    else if( bcore_source_a_parse_bl_fa( source,"#=?'?'" ) )
    {
        BLM_TRY(xoico_cdaleth_s_trans_ternary_branch(o,source, buf, out_typespec ))
    }
    
    // general bracket
    else if( bcore_source_a_parse_bl_fa( source,"#=?'('" ) )
    {
        BLM_TRY(xoico_cdaleth_s_trans_bracket(o,source, buf, out_typespec ))
    }
    
    // array subscript
    else if( bcore_source_a_parse_bl_fa( source,"#=?'['" ) )
    {
        BLM_TRY(xoico_cdaleth_s_trans_array_subscript(o,source, buf, out_typespec ))
    }
    
    // end of expression...
    else if( bcore_source_a_parse_bl_fa( source,sc_bl_end_of_expression ) )
    {
        continuation = false;
    }
    
    // unhandled
    else
    {
        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Syntax error after '#<sc_t>'", buf->sc ))
    }
    
    if( continuation )
    {
        if( !bcore_source_a_parse_bl_fa( source,sc_bl_end_of_expression ) )
        {
            if( out_typespec ) xoico_typespec_s_reset(out_typespec);
            BLM_TRY(xoico_cdaleth_s_trans_expression(o,source, buf, NULL ))
        }
    }
    
    if( buf_out ) st_s_push_st( buf_out,buf );
    
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_cdaleth_s_try_trans_declaration( xoico_cdaleth_s* o, bcore_source* source, st_s* buf_out, bl_t* success )
{
    // xoico_cdaleth.x:1319:1
    BLM_INIT_LEVEL(0); {
    if( success ) *success = false;
    
    xoico_typespec_s* typespec_var = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
    
    sz_t index = bcore_source_a_get_index( source);
    
    st_s* buf_var = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    
    bl_t success_take_typespec = false;
    BLM_TRY(xoico_cdaleth_s_try_take_typespec(o,source, typespec_var, true, &success_take_typespec ))
    
    if( !success_take_typespec )
    {
        bcore_source_a_set_index( source,index );
        BLM_RETURNV(er_t, 0)
    }
    
    BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf_var ))
    
    if
    (
        typespec_var->type &&
        bcore_source_a_parse_bl_fa( source,"#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||[0]=='_')" )
    )
    {
        tp_t tp_identifier = 0;
        BLM_TRY(xoico_cdaleth_s_trans_identifier(o,source, buf_var, &tp_identifier ))
        BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf_var ))
    
        if( bcore_source_a_parse_bl_fa( source,"#?'='" ) )
        {
            bl_t pushed_typedecl = false;
            if( typespec_var->type != TYPEOF_type_deduce )
            {
                xoico_cdaleth_s_push_typedecl(o,typespec_var, tp_identifier );
                pushed_typedecl = true;
            }
    
            st_s_push_sc( buf_var,"=" );
            xoico_typespec_s* typespec_expr = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
            st_s* buf_expr = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
            BLM_TRY(xoico_cdaleth_s_trans_expression(o,source, buf_expr, typespec_expr ))
    
            if( typespec_var->type == TYPEOF_type_deduce )
            {
                if( !typespec_expr->type )
                {
                    BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Declaration-syntax: Deduce requested but expression is intractable." ))
                }
                typespec_var->type = typespec_expr->type;
            }
    
            if( typespec_expr->type )
            {
                BLM_TRY(xoico_cdaleth_s_adapt_expression(o,source, typespec_expr, typespec_var, buf_expr, buf_var ))
            }
            else
            {
                st_s_push_st( buf_var,buf_expr );
            }
            BLM_TRY(xoico_cdaleth_s_push_typespec(o,typespec_var, buf_out ))
            st_s_push_char( buf_out,' ' );
            st_s_push_st( buf_out,buf_var );
            if( !pushed_typedecl ) xoico_cdaleth_s_push_typedecl(o,typespec_var, tp_identifier );
        }
        else if( typespec_var->type == TYPEOF_type_deduce )
        {
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Declaration-syntax: Deduce requested without assignment." ))
        }
        else if( bcore_source_a_parse_bl_fa( source,"#=?'['" ) )
        {
            BLM_TRY(xoico_cdaleth_s_push_typespec(o,typespec_var, buf_out ))
            while( bcore_source_a_parse_bl_fa( source,"#?'['" ) )
            {
                st_s_push_char( buf_var,'[' );
                BLM_TRY(xoico_cdaleth_s_trans_expression(o,source, buf_var, NULL ))
                BLM_TRY(xoico_cdaleth_s_parse(o,source, "]" ))
                st_s_push_char( buf_var,']' );
                typespec_var->indirection++;
            }
            st_s_push_char( buf_out,' ' );
            st_s_push_st( buf_out,buf_var );
            xoico_cdaleth_s_push_typedecl(o,typespec_var, tp_identifier );
        }
        else
        {
            BLM_TRY(xoico_cdaleth_s_push_typespec(o,typespec_var, buf_out ))
            st_s_push_char( buf_out,' ' );
            st_s_push_st( buf_out,buf_var );
            xoico_cdaleth_s_push_typedecl(o,typespec_var, tp_identifier );
        }
    
        if( success ) *success = true;
    }
    else
    {
        bcore_source_a_set_index( source,index );
        BLM_RETURNV(er_t, 0)
    }
    
    if( success ) *success = true;
    
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_cdaleth_s_inspect_variable( xoico_cdaleth_s* o, bcore_source* source )
{
    // xoico_cdaleth.x:1428:1
    BLM_INIT_LEVEL(0); {
    BLM_TRY(xoico_cdaleth_s_parse(o,source, "\?\?" ))
    
    st_s* st        = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    st_s* buf_local = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    xoico_typespec_s* typespec = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
    BLM_TRY(bcore_source_a_parse_em_fa( source," #until';' ", st ) )
    BLM_TRY(bcore_source_a_parse_em_fa( source,";" ) )
    bcore_msg_fa( " \?? #<sc_t>;\n", st->sc );
    if( xoico_cdaleth_s_trans_expression(o,((bcore_source*)BLM_LEVEL_A_PUSH(0,((bcore_source*)(bcore_source_string_s_create_fa( "#<st_s*>;", st ))))), buf_local, typespec ) )
    {
        bcore_error_pop_to_sink( BCORE_STDOUT );
        bcore_msg_fa( "\n" );
    }
    else
    {
        if( st->size == 0 ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Variable name expected." ))
        bcore_msg_fa( "--> #<sc_t>;\n", buf_local->sc );
    
        if( typespec->type )
        {
            bcore_msg_fa( "Expression yields typespec:\n" );
            bcore_msg_fa( "  const      : #<bl_t>\n", typespec->flag_const );
            bcore_msg_fa( "  type       : #<sc_t>\n", xoico_cdaleth_s_nameof(o,typespec->type ) );
            bcore_msg_fa( "  indirection: #<sz_t>\n", typespec->indirection );
        }
        else
        {
            bcore_msg_fa( "Expression does not yield a typespec.\n" );
        }
    }
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_cdaleth_s_trans_statement_expression( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth.x:1465:1
    BLM_INIT_LEVEL(0); {
    if( o->try_block_level > 0 )
    {
        xoico_typespec_s* typespec = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
        st_s* buf_expr = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
        BLM_TRY(xoico_cdaleth_s_trans_expression(o,source, buf_expr, typespec ))
        if
        (
            ( typespec->type == TYPEOF_er_t ) &&
            ( typespec->indirection == 0 ) &&
            ( typespec->flag_addressable == false )
        )
        {
            if( !bcore_source_a_parse_bl_fa( source," #?';'" ) )
            {
                BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Inside a try-block: Expressions yielding 'er_t' must end with ';'" ))
            }
            st_s_push_fa( buf,"BLM_TRY(#<sc_t>)", buf_expr->sc );
        }
        else
        {
            st_s_push_st( buf,buf_expr );
        }
    }
    else
    {
        BLM_TRY(xoico_cdaleth_s_trans_expression(o,source, buf, NULL ))
    }
    
    BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf ))
    
    // ':' between expressions is to be taken literally
    if( bcore_source_a_parse_bl_fa( source,"#?':'" ) ) st_s_push_char( buf,':' );
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_cdaleth_s_trans_statement( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth.x:1504:1
     {
    BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf ))
    
    if( bcore_source_a_parse_bl_fa( source,"#?([0]=='{'||[0]=='#'||[0]==';'||[0]==','||[0]==')'||[0]=='}'||([0]=='?'&&[1]=='?'))" ) )
    {
        char c = bcore_source_a_inspect_char( source);
        switch( c )
        {
            case '{':
            {
                BLM_TRY(xoico_cdaleth_s_trans_block(o,source, buf, false ))
            }
            break;
    
            case '#':
            {
                BLM_TRY(xoico_cdaleth_s_trans_preprocessor(o,source, buf ))
            }
            break;
    
            case ';':
            {
                bcore_source_a_get_char( source);
                st_s_push_char( buf,';' );
            }
            break;
    
            case ',':
            {
                bcore_source_a_get_char( source);
                st_s_push_char( buf,',' );
            }
            break;
    
            case '?':
            {
                BLM_TRY(xoico_cdaleth_s_inspect_variable(o,source ))
            }
            break;
    
            case ')':
            {
                return  bcore_source_a_parse_error_fa( source,"Unmatched closing bracket." );
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
        tp_t tp_identifier = xoico_cdaleth_s_get_identifier(o,source, false );
    
        if( tp_identifier && xoico_cdaleth_s_is_control_name(o,tp_identifier ) )
        {
            BLM_TRY(xoico_cdaleth_s_trans_control(o,tp_identifier, source, buf ))
        }
        else
        {
            bl_t success_declaration = false;
            BLM_TRY(xoico_cdaleth_s_try_trans_declaration(o,source, buf, &success_declaration ))
            if( !success_declaration ) BLM_TRY(xoico_cdaleth_s_trans_statement_expression(o,source, buf ))
        }
    }
    
    return  0;
    } /* try */
}

er_t xoico_cdaleth_s_trans_block_inside( xoico_cdaleth_s* o, bcore_source* source, st_s* buf_out )
{
    // xoico_cdaleth.x:1581:1
    BLM_INIT_LEVEL(0); {
    st_s* buf = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    
    while( !bcore_source_a_parse_bl_fa( source,"#=?'}'" ) && !bcore_source_a_eos( source) )
    {
        BLM_TRY(xoico_cdaleth_s_trans_statement(o,source, buf ))
    }
    
    if( xoico_cdaleth_s_stack_block_get_top_unit(o)->use_blm )
    {
        st_s_push_fa( buf_out,"BLM_INIT_LEVEL(#<sz_t>);", o->level );
        st_s_push_st( buf_out,buf );
    
        if( ( o->level > 0 ) || !xoico_cdaleth_s_returns_a_value(o) )
        {
            st_s_push_sc( buf_out,"BLM_DOWN();" );
        }
    }
    else
    {
        st_s_push_st( buf_out,buf );
    }
    
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_cdaleth_s_trans_block( xoico_cdaleth_s* o, bcore_source* source, st_s* buf, bl_t is_break_ledge )
{
    // xoico_cdaleth.x:1610:1
     {
    xoico_cdaleth_s_inc_block(o);
    xoico_cdaleth_s_stack_block_get_top_unit(o)->break_ledge = is_break_ledge;
    BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf ))
    BLM_TRY(xoico_cdaleth_s_trans(o,source, "{", buf ))
    BLM_TRY(xoico_cdaleth_s_trans_block_inside(o,source, buf ))
    BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf ))
    BLM_TRY(xoico_cdaleth_s_trans(o,source, "}", buf ))
    xoico_cdaleth_s_dec_block(o);
    return  0;
    } /* try */
}

er_t xoico_cdaleth_s_trans_statement_as_block( xoico_cdaleth_s* o, bcore_source* source, st_s* buf_out, bl_t is_break_ledge )
{
    // xoico_cdaleth.x:1625:1
    BLM_INIT_LEVEL(0); {
    st_s* buf = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    
    xoico_cdaleth_s_inc_block(o);
    xoico_cdaleth_s_stack_block_get_top_unit(o)->break_ledge = is_break_ledge;
    
    BLM_TRY(xoico_cdaleth_s_trans_statement(o,source, buf ))
    BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf ))
    if( bcore_source_a_parse_bl_fa( source,"#?';'" ) ) st_s_push_sc( buf,";" );
    
    if( xoico_cdaleth_s_stack_block_get_top_unit(o)->use_blm )
    {
        st_s_push_fa( buf_out,"{BLM_INIT_LEVEL(#<sz_t>);", o->level );
        st_s_push_st( buf_out,buf );
        st_s_push_sc( buf_out,"BLM_DOWN();}" );
    }
    else
    {
        st_s_push_st( buf_out,buf );
    }
    
    xoico_cdaleth_s_dec_block(o);
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_cdaleth_s_trans_block_inside_verbatim_c( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth.x:1653:1
     {
    BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf ))
    while( !bcore_source_a_parse_bl_fa( source,"#=?'}'" ) && !bcore_source_a_eos( source) )
    {
        switch( bcore_source_a_inspect_char( source) )
        {
            case '"':
            {
                BLM_TRY(xoico_cdaleth_s_trans_string_literal(o,source, buf ))
            }
            break;
    
            case '\'':
            {
                BLM_TRY(xoico_cdaleth_s_trans_char_literal(o,source, buf ))
            }
            break;
    
            case '{':
            {
                st_s_push_char( buf,bcore_source_a_get_char( source) );
                BLM_TRY(xoico_cdaleth_s_trans_block_inside_verbatim_c(o,source, buf ))
                BLM_TRY(xoico_cdaleth_s_parse(o,source, "}" ))
                st_s_push_char( buf,'}' );
            }
            break;
    
            default:
            {
                st_s_push_char( buf,bcore_source_a_get_char( source) );
            }
            break;
        }
        BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf ))
    }
    return  0;
    } /* try */
}

er_t xoico_cdaleth_s_setup( xoico_cdaleth_s* o, const xoico_body_s* body, const xoico_signature_s* signature )
{
    // xoico_cdaleth.x:1694:1
    BLM_INIT_LEVEL(0); {
    sc_t sc_obj_type = ( signature->arg_o ) ? ( body->stamp ? body->stamp->st_name.sc : body->group->st_name.sc ) : NULL;
    
    const xoico_args_s* args = &signature->args;
    
    tp_t obj_type  = ( signature->arg_o == 0 ) ? 0 : xoico_cdaleth_s_entypeof(o,sc_obj_type );
    bl_t obj_const = ( signature->arg_o == TYPEOF_const );
    tp_t obj_name  = xoico_cdaleth_s_entypeof(o,"o" );
    
    o->args     = ((xoico_args_s*)(args));
    o->typespec_ret = ((xoico_typespec_s*)(&(signature->typespec_ret)));
    o->group    = body->code->group;
    o->stamp    = body->code->stamp;
    o->compiler = body->group->compiler;
    o->obj_type = obj_type;
    o->level    = 0;
    o->try_block_level = 0;
    xoico_cdaleth_stack_var_s_clear(&(o->stack_var));
    xoico_cdaleth_s_init_level0(o);
    
    xoico_cdaleth_stack_var_unit_s* unit = ((xoico_cdaleth_stack_var_unit_s*)BLM_LEVEL_T_PUSH(0,xoico_cdaleth_stack_var_unit_s,xoico_cdaleth_stack_var_unit_s_create()));
    
    if( obj_type )
    {
        unit->typespec.flag_const = obj_const;
        unit->typespec.type = obj_type;
        unit->typespec.indirection = 1;
        unit->name = obj_name;
        unit->level = o->level;
        xoico_cdaleth_stack_var_s_push_unit(&(o->stack_var),unit );
        bcore_hmap_name_s_set_sc(&(o->hmap_name),xoico_compiler_s_nameof(o->compiler,obj_type ) );
        bcore_hmap_name_s_set_sc(&(o->hmap_name),xoico_compiler_s_nameof(o->compiler,obj_name ) );
    }
    
    {const xoico_args_s* __a=args ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_arg_s* arg=&(__a->data[__i]);
    {
        if( arg->typespec.type && arg->name )
        {
            xoico_typespec_s_copy(&(unit->typespec),&(arg->typespec ));
            if( obj_type ) BLM_TRY(xoico_typespec_s_relent(&(unit->typespec),o->group, obj_type ))
            unit->name = arg->name;
            unit->level = o->level;
            xoico_cdaleth_stack_var_s_push_unit(&(o->stack_var),unit );
            bcore_hmap_name_s_set_sc(&(o->hmap_name),xoico_compiler_s_nameof(o->compiler,arg->typespec.type ) );
            bcore_hmap_name_s_set_sc(&(o->hmap_name),xoico_compiler_s_nameof(o->compiler,arg->name ) );
        }
    }
    }}BLM_RETURNV(er_t, 0)
    } /* try */
}

sz_t xoico_cdaleth_s_assess_indentation( bcore_source* source )
{
    // xoico_cdaleth.x:1747:1
    
    sz_t index = bcore_source_a_get_index( source);
    while( !bcore_source_a_eos( source) ) if( bcore_source_a_get_char( source) == '\n' ) break;
    sz_t indentation = 0;
    while( !bcore_source_a_eos( source) )
    {
        if( bcore_source_a_get_char( source) != ' ' ) break;
        indentation++;
    }
    bcore_source_a_set_index( source,index );
    return  indentation;
}

void xoico_cdaleth_s_remove_indentation( st_s* buf, sz_t indentation )
{
    // xoico_cdaleth.x:1763:1
    
    ASSERT( buf->space >= buf->size );
    
    sz_t j = 0;
    for( sz_t i = 0; i < buf->size; i++ )
    {
        char c = buf->data[ i ];
        buf->data[ j++ ] = c;
        if( c == '\n' )
        {
            for( sz_t k = 0; k < indentation; k++ )
            {
                if( buf->data[ i + 1 ] != ' ' ) break;
                i++;
            }
        }
    }
    
    buf->data[ j ] = 0;
    buf->size = j;
}

er_t xoico_cdaleth_s_translate( const xoico_cdaleth_s* o, const xoico_body_s* body, const xoico_signature_s* signature, bcore_sink* sink )
{
    // xoico_cdaleth.x:1788:1
    BLM_INIT_LEVEL(0); {
    xoico_cdaleth_s* engine = ((xoico_cdaleth_s*)BLM_LEVEL_T_PUSH(0,xoico_cdaleth_s,xoico_cdaleth_s_clone(o)));
    BLM_TRY(xoico_cdaleth_s_setup(engine,body, signature ))
    
    bcore_source* source = ((bcore_source*)BLM_LEVEL_A_PUSH(0,((bcore_source*)(bcore_source_point_s_clone_source( &body->code->source_point )))));
    
    st_s* buf = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    
    BLM_TRY(xoico_cdaleth_s_parse(engine,source, " {" ))
    sz_t indentation = 0;
    if( !body->go_inline ) indentation = xoico_cdaleth_s_assess_indentation(source );
    BLM_TRY(xoico_cdaleth_s_trans_block_inside(engine,source, buf ))
    BLM_TRY(xoico_cdaleth_s_parse(engine,source, " }" ))
    
    //remove trailing whitespaces
    for( sz_t i = buf->size - 1; i >= 0; i-- )
    {
        if( buf->data[ i ] != ' ' && buf->data[ i ] != '\t' && buf->data[ i ] != '\n' ) break;
        buf->data[ i ] = 0;
        buf->size = i;
    }
    
    if( engine->insert_source_reference && !body->code->single_line )
    {
        bcore_sink_a_push_fa( sink,"// " );
        bcore_source_point_s_source_reference_to_sink( &(body->code->source_point),true, sink );
        bcore_sink_a_push_fa( sink,"\n" );
    }
    
    if( indentation > 0 ) xoico_cdaleth_s_remove_indentation(buf, indentation );
    
    if( engine->verbose )
    {
        bcore_sink_a_push_fa( BCORE_STDOUT, "##############################\n" );
        bcore_sink_a_push_fa( BCORE_STDOUT, "#<st_s*>\n", buf );
    }
    
    bcore_sink_a_push_sc( sink,buf->sc );
    
    BLM_RETURNV(er_t, 0)
    } /* try */
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
        case TYPEOF_cast : return  xoico_cdaleth_s_trans_builtin_cast(o,source, buf_expr, typespec_expr, buf_out, typespec_out );
        case TYPEOF_scope: return  xoico_cdaleth_s_trans_builtin_scope(o,source, buf_expr, typespec_expr, buf_out, typespec_out );
        case TYPEOF_fork:  return  xoico_cdaleth_s_trans_builtin_fork(o,source, buf_expr, typespec_expr, buf_out, typespec_out );
        case TYPEOF_try:   return  xoico_cdaleth_s_trans_builtin_try(o,source, buf_expr, typespec_expr, buf_out, typespec_out );
        default: return  bcore_source_a_parse_error_fa( source,"Internal error: Invalid builtin type '#<sc_t>'", ifnameof( tp_builtin ) );
    }
    } /* try */
}

er_t xoico_cdaleth_s_trans_builtin_cast( xoico_cdaleth_s* o, bcore_source* source, const st_s* buf_expr, const xoico_typespec_s* typespec_expr, st_s* buf_out, xoico_typespec_s* typespec_out )
{
    // xoico_cdaleth_builtin.x:75:1
    BLM_INIT_LEVEL(0); {
    if( buf_expr ) // member call
    {
        BLM_TRY(xoico_cdaleth_s_parse(o,source, " ( " ))
        st_s_clear( buf_out);
    }
    else // direct call
    {
        BLM_TRY(xoico_cdaleth_s_parse(o,source, "cast ( " ))
        st_s* buf = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
        xoico_typespec_s* typespec = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
        BLM_TRY(xoico_cdaleth_s_trans_expression(o,source, buf, typespec ))
        BLM_TRY(xoico_cdaleth_s_parse(o,source, " , " ))
        typespec_expr = typespec;
        buf_expr = buf;
    }
    
    st_s_push_sc( buf_out, "((" );
    xoico_typespec_s* typespec_cast = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create() ));
    
    BLM_TRY(xoico_cdaleth_s_take_typespec(o,source, typespec_cast, true ))
    
    if( typespec_cast->type == TYPEOF_type_deduce )
    {
        if( !typespec_expr->type )
        {
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Cast-syntax: Deduce requested but expression is intractable." ))
        }
        typespec_cast->type = typespec_expr->type;
    }
    
    BLM_TRY(xoico_cdaleth_s_push_typespec(o,typespec_cast, buf_out ))
    st_s_push_sc( buf_out, ")(" );
    
    if( typespec_expr->type )
    {
        BLM_TRY(xoico_cdaleth_s_adapt_expression(o,source, typespec_expr, typespec_cast, buf_expr, buf_out ))
    }
    else
    {
        st_s_push_st( buf_out, buf_expr );
    }
    
    BLM_TRY(xoico_cdaleth_s_parse(o,source, " )" ))
    st_s_push_sc( buf_out, "))" );
    
    if( typespec_out ) xoico_typespec_s_copy(typespec_out,typespec_cast );
    
    if( typespec_cast->indirection > typespec_expr->indirection )
    {
        typespec_out->flag_addressable = false;
    }
    
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_cdaleth_s_trans_builtin_scope( xoico_cdaleth_s* o, bcore_source* source, const st_s* buf_expr, const xoico_typespec_s* typespec_expr, st_s* buf_out, xoico_typespec_s* typespec_out )
{
    // xoico_cdaleth_builtin.x:145:1
    BLM_INIT_LEVEL(0); {
    bl_t has_arg = false;
    
    if( buf_expr ) // member call
    {
        BLM_TRY(xoico_cdaleth_s_parse(o,source, " ( " ))
        st_s_clear( buf_out);
        has_arg = !bcore_source_a_parse_bl( source,"#=?')'" );
    }
    else // direct call
    {
        BLM_TRY(xoico_cdaleth_s_parse(o,source, "scope ( " ))
        st_s* buf = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
        xoico_typespec_s* typespec = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
        BLM_TRY(xoico_cdaleth_s_trans_expression(o,source, buf, typespec ))
        typespec_expr = typespec;
        buf_expr = buf;
        has_arg = bcore_source_a_parse_bl( source,"#?','" );
    }
    
    const xoico_typespec_s* typespec_scope = typespec_expr;
    
    st_s_push_sc( buf_out, "((" );
    
    sz_t level = 0;
    
    if( has_arg )
    {
        BLM_TRY(xoico_cdaleth_s_parse(o,source, " " ))
        tp_t tp_identifier = xoico_cdaleth_s_get_identifier(o,source, true );
    
        if( xoico_cdaleth_s_is_var(o,tp_identifier ) )
        {
            level = xoico_cdaleth_stack_var_s_get_level(&(o->stack_var),tp_identifier );
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
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"scope: identifier '#<sc_t>' does not represent a variable.", xoico_cdaleth_s_nameof(o,tp_identifier ) ))
        }
    }
    
    BLM_TRY(xoico_cdaleth_s_parse(o,source, " )" ))
    
    if( typespec_scope->type        == 0 ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Operator 'scope': Expression not tractable." ))
    if( typespec_scope->indirection != 1 ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Operator 'scope': Expression's indirection != 1." ))
    if( typespec_scope->flag_keep )        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Operator 'scope': Target is already scoped." ))
    
    BLM_TRY(xoico_cdaleth_s_push_typespec(o,typespec_scope, buf_out ))
    
    if( xoico_cdaleth_s_is_group(o,typespec_scope->type ) )
    {
        st_s_push_fa( buf_out,")BLM_LEVEL_A_PUSH(#<sz_t>,#<sc_t>))", level, buf_expr->sc );
    }
    else
    {
        st_s_push_fa( buf_out,")BLM_LEVEL_T_PUSH(#<sz_t>,#<sc_t>,#<sc_t>))", level, xoico_cdaleth_s_nameof(o,typespec_scope->type ), buf_expr->sc );
    }
    
    o->stack_block.adl.data[ level ]->use_blm = true;
    
    if( typespec_out )
    {
        xoico_typespec_s_copy(typespec_out,typespec_scope );
        typespec_out->flag_keep = true;
    }
    
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_cdaleth_s_trans_builtin_fork( xoico_cdaleth_s* o, bcore_source* source, const st_s* buf_expr, const xoico_typespec_s* typespec_expr, st_s* buf_out, xoico_typespec_s* typespec_out )
{
    // xoico_cdaleth_builtin.x:236:1
    BLM_INIT_LEVEL(0); {
    if( buf_expr ) // member call
    {
        BLM_TRY(xoico_cdaleth_s_parse(o,source, " ( " ))
        st_s_clear( buf_out);
    }
    else // direct call
    {
        BLM_TRY(xoico_cdaleth_s_parse(o,source, "fork ( " ))
        st_s* buf = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
        xoico_typespec_s* typespec = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
        BLM_TRY(xoico_cdaleth_s_trans_expression(o,source, buf, typespec ))
        typespec_expr = typespec;
        buf_expr = buf;
    }
    
    const xoico_typespec_s* typespec_fork = typespec_expr;
    
    st_s_push_sc( buf_out, "((" );
    
    BLM_TRY(xoico_cdaleth_s_parse(o,source, " )" ))
    
    if( typespec_fork->type        == 0 ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Operator 'fork': Expression not tractable." ))
    if( typespec_fork->indirection != 1 ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Operator 'fork': Expression's indirection != 1." ))
    
    BLM_TRY(xoico_cdaleth_s_push_typespec(o,typespec_fork, buf_out ))
    st_s_push_fa( buf_out,")bcore_fork(#<sc_t>))", buf_expr->sc );
    
    if( typespec_out ) xoico_typespec_s_copy(typespec_out,typespec_fork );
    
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_cdaleth_s_trans_builtin_try( xoico_cdaleth_s* o, bcore_source* source, const st_s* buf_expr, const xoico_typespec_s* typespec_expr, st_s* buf_out, xoico_typespec_s* typespec_out )
{
    // xoico_cdaleth_builtin.x:283:1
    BLM_INIT_LEVEL(0); {
    if( o->typespec_ret->type != TYPEOF_er_t || o->typespec_ret->indirection != 0 )
    {
        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Operator 'try': This operator can only be used in functions returning 'er_t'." ))
    }
    
    if( typespec_out ) xoico_typespec_s_reset(typespec_out);
    
    if( buf_expr ) // member call
    {
        BLM_TRY(xoico_cdaleth_s_parse(o,source, " ( " ))
        st_s_clear( buf_out);
    }
    else // direct call
    {
        BLM_TRY(xoico_cdaleth_s_parse(o,source, "try " ))
    
        if( bcore_source_a_parse_bl( source,"#=?'{'" ) ) // try block
        {
            o->try_block_level++;
            BLM_TRY(xoico_cdaleth_s_trans_block(o,source, buf_out, false ))
            o->try_block_level--;
            BLM_RETURNV(er_t, 0)
        }
    
        BLM_TRY(xoico_cdaleth_s_parse(o,source, "( " ))
        st_s* buf = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
        xoico_typespec_s* typespec = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
        BLM_TRY(xoico_cdaleth_s_trans_expression(o,source, buf, typespec ))
        typespec_expr = typespec;
        buf_expr = buf;
    }
    
    const xoico_typespec_s* typespec_try = typespec_expr;
    
    BLM_TRY(xoico_cdaleth_s_parse(o,source, " ) ;" ))
    
    if( typespec_try->type != 0 )
    {
        if( typespec_try->type != TYPEOF_er_t ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Operator 'try': Expression must yield er_t." ))
        if( typespec_try->indirection != 0    ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Operator 'try': Expression's indirection != 0." ))
    }
    else
    {
        // return source.parse_error_fa( "Operator 'try': Expression not tractable." );
    }
    
    
    st_s_push_fa( buf_out,"BLM_TRY(#<sc_t>)", buf_expr->sc );
    
    BLM_RETURNV(er_t, 0)
    } /* try */
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
        case TYPEOF_for:     return  xoico_cdaleth_s_trans_control_for(o,source, buf );
        case TYPEOF_foreach: return  xoico_cdaleth_s_trans_control_foreach(o,source, buf );
        case TYPEOF_if:      return  xoico_cdaleth_s_trans_control_if(o,source, buf );
        case TYPEOF_else:    return  xoico_cdaleth_s_trans_control_else(o,source, buf );
        case TYPEOF_break:   return  xoico_cdaleth_s_trans_control_break(o,source, buf );
        case TYPEOF_while:   return  xoico_cdaleth_s_trans_control_while(o,source, buf );
        case TYPEOF_do:      return  xoico_cdaleth_s_trans_control_do(o,source, buf );
        case TYPEOF_switch:  return  xoico_cdaleth_s_trans_control_switch(o,source, buf );
        case TYPEOF_case:    return  xoico_cdaleth_s_trans_control_case(o,source, buf );
        case TYPEOF_default: return  xoico_cdaleth_s_trans_control_default(o,source, buf );
        case TYPEOF_return:  return  xoico_cdaleth_s_trans_control_return(o,source, buf );
        default: return  bcore_source_a_parse_error_fa( source,"Internal error: Invalid control name '#<sc_t>'", ifnameof( tp_control ) );
    }
    } /* try */
}

er_t xoico_cdaleth_s_trans_control_for( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth_control.x:66:1
     {
    xoico_cdaleth_s_inc_block(o);
    xoico_cdaleth_s_stack_block_get_top_unit(o)->break_ledge = true;
    BLM_TRY(xoico_cdaleth_s_trans(o,source, "for", buf ))
    BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf ))
    BLM_TRY(xoico_cdaleth_s_trans(o,source, "(", buf ))
    BLM_TRY(xoico_cdaleth_s_trans_statement(o,source, buf )) // def
    BLM_TRY(xoico_cdaleth_s_trans(o,source, ";", buf ))
    BLM_TRY(xoico_cdaleth_s_trans_expression(o,source, buf, NULL )) // cond
    BLM_TRY(xoico_cdaleth_s_trans(o,source, ";", buf ))
    BLM_TRY(xoico_cdaleth_s_trans_expression(o,source, buf, NULL )) // update
    BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf ))
    BLM_TRY(xoico_cdaleth_s_trans(o,source, ")", buf ))
    BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf ))
    if( bcore_source_a_parse_bl( source,"#=?'{'" ) )
    {
        BLM_TRY(xoico_cdaleth_s_trans_block(o,source, buf, false ))
    }
    else
    {
        BLM_TRY(xoico_cdaleth_s_trans_statement_as_block(o,source, buf, false ))
    }
    xoico_cdaleth_s_dec_block(o);
    return  0;
    } /* try */
}

er_t xoico_cdaleth_s_trans_control_foreach( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth_control.x:99:1
    BLM_INIT_LEVEL(0); {
    xoico_cdaleth_s_inc_block(o);
    xoico_cdaleth_s_stack_block_get_top_unit(o)->break_ledge = true;
    BLM_TRY(xoico_cdaleth_s_parse(o,source, "foreach ( " ))
    
    xoico_typespec_s* typespec_var = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create() ));
    BLM_TRY(xoico_cdaleth_s_take_typespec(o,source, typespec_var, true ))
    
    tp_t tp_var_name = 0;
    
    if( bcore_source_a_parse_bl( source,"#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||[0]=='_')" ) )
    {
        tp_var_name = xoico_cdaleth_s_get_identifier(o,source, true );
    }
    else
    {
        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Variable name expected." ))
    }
    
    BLM_TRY(xoico_cdaleth_s_parse(o,source, " in " ))
    
    xoico_typespec_s* typespec_arr_expr = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create() ));
    st_s* buf_arr_expr = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create() ));
    BLM_TRY(xoico_cdaleth_s_trans_expression(o,source, buf_arr_expr, typespec_arr_expr ))
    
    if( !typespec_arr_expr->type )
    {
        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Array expression not tractable." ))
    }
    
    xoico_compiler_element_info_s* info = ((xoico_compiler_element_info_s*)BLM_LEVEL_T_PUSH(0,xoico_compiler_element_info_s,xoico_compiler_element_info_s_create() ));
    
    if( !xoico_compiler_s_get_type_array_element_info(o->compiler,typespec_arr_expr->type, info ) )
    {
        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Expression does not evaluate to an array." ))
    }
    
    xoico_typespec_s* typespec_element = &info->type_info.typespec;
    
    if( typespec_var->type == TYPEOF_type_deduce ) typespec_var->type = typespec_element->type;
    
    BLM_TRY(xoico_cdaleth_s_parse(o,source, " )" ))
    
    xoico_typespec_s* typespec_arr = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_clone(typespec_arr_expr) ));
    typespec_arr->indirection = 1;
    typespec_arr->flag_const = true;
    
    xoico_typespec_s* typespec_idx = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create() ));
    typespec_idx->type = TYPEOF_sz_t;
    
    xoico_cdaleth_s_push_typedecl(o,typespec_var, tp_var_name );
    xoico_cdaleth_s_push_typedecl(o,typespec_arr, xoico_cdaleth_s_entypeof(o,"__a" ) );
    xoico_cdaleth_s_push_typedecl(o,typespec_idx, xoico_cdaleth_s_entypeof(o,"__i" ) );
    
    st_s* buf_statement = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create() ));
    if( bcore_source_a_parse_bl( source,"#=?'{'" ) )
    {
        BLM_TRY(xoico_cdaleth_s_trans_block(o,source, buf_statement, false ))
    }
    else
    {
        BLM_TRY(xoico_cdaleth_s_trans_statement_as_block(o,source, buf_statement, false ))
    }
    
    st_s_push_fa( buf,"{" );
    
    BLM_TRY(xoico_cdaleth_s_push_typespec(o,typespec_arr, buf ))
    
    st_s_push_fa( buf," __a=" );
    BLM_TRY(xoico_cdaleth_s_adapt_expression(o,source, typespec_arr_expr, typespec_arr, buf_arr_expr, buf ))
    st_s_push_fa( buf,";" );
    st_s_push_fa( buf,"if(__a)for(sz_t __i=0; __i<__a->size; __i++){" );
    BLM_TRY(xoico_cdaleth_s_push_typespec(o,typespec_var, buf ))
    st_s_push_fa( buf," #<sc_t>=", xoico_cdaleth_s_nameof( o,tp_var_name ) );
    
    st_s* buf_element_expr = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,((st_s*)(st_s_create_sc( "__a->data[__i]" ))) ));
    BLM_TRY(xoico_cdaleth_s_adapt_expression(o,source, typespec_element, typespec_var, buf_element_expr, buf ))
    st_s_push_fa( buf,";" );
    
    st_s_push_fa( buf,"#<sc_t>", buf_statement->sc );
    
    st_s_push_fa( buf,"}}" );
    xoico_cdaleth_s_dec_block(o);
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_cdaleth_s_trans_control_if( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth_control.x:188:1
     {
    BLM_TRY(xoico_cdaleth_s_trans(o,source, "if", buf ))
    BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf ))
    BLM_TRY(xoico_cdaleth_s_trans(o,source, "(", buf ))
    BLM_TRY(xoico_cdaleth_s_trans_expression(o,source, buf, NULL )) // def
    BLM_TRY(xoico_cdaleth_s_trans(o,source, ")", buf ))
    BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf ))
    if( bcore_source_a_parse_bl( source,"#=?'{'" ) )
    {
        BLM_TRY(xoico_cdaleth_s_trans_block(o,source, buf, false ))
    }
    else
    {
        BLM_TRY(xoico_cdaleth_s_trans_statement_as_block(o,source, buf, false ))
    }
    return  0;
    } /* try */
}

er_t xoico_cdaleth_s_trans_control_while( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth_control.x:209:1
     {
    BLM_TRY(xoico_cdaleth_s_trans(o,source, "while", buf ))
    BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf ))
    BLM_TRY(xoico_cdaleth_s_trans(o,source, "(", buf ))
    BLM_TRY(xoico_cdaleth_s_trans_expression(o,source, buf, NULL )) // def
    BLM_TRY(xoico_cdaleth_s_trans(o,source, ")", buf ))
    BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf ))
    if( bcore_source_a_parse_bl( source,"#=?'{'" ) )
    {
        BLM_TRY(xoico_cdaleth_s_trans_block(o,source, buf, true ))
    }
    else
    {
        BLM_TRY(xoico_cdaleth_s_trans_statement_as_block(o,source, buf, true ))
    }
    return  0;
    } /* try */
}

er_t xoico_cdaleth_s_trans_control_do( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth_control.x:230:1
     {
    BLM_TRY(xoico_cdaleth_s_trans(o,source, "do", buf ))
    BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf ))
    if( bcore_source_a_parse_bl( source,"#=?'{'" ) )
    {
        BLM_TRY(xoico_cdaleth_s_trans_block(o,source, buf, true ))
    }
    else
    {
        BLM_TRY(xoico_cdaleth_s_trans_statement_as_block(o,source, buf, true ))
    }
    BLM_TRY(xoico_cdaleth_s_trans(o,source, "while", buf ))
    BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf ))
    BLM_TRY(xoico_cdaleth_s_trans(o,source, "(", buf ))
    BLM_TRY(xoico_cdaleth_s_trans_expression(o,source, buf, NULL )) // def
    BLM_TRY(xoico_cdaleth_s_trans(o,source, ")", buf ))
    BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf ))
    BLM_TRY(xoico_cdaleth_s_trans(o,source, ";", buf ))
    return  0;
    } /* try */
}

er_t xoico_cdaleth_s_trans_control_else( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth_control.x:254:1
     {
    BLM_TRY(xoico_cdaleth_s_trans(o,source, "else", buf ))
    BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf ))
    if( bcore_source_a_parse_bl( source,"#=?'{'" ) )
    {
        BLM_TRY(xoico_cdaleth_s_trans_block(o,source, buf, false ))
    }
    else
    {
        BLM_TRY(xoico_cdaleth_s_trans_statement_as_block(o,source, buf, false ))
    }
    return  0;
    } /* try */
}

er_t xoico_cdaleth_s_trans_control_switch( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth_control.x:271:1
     {
    BLM_TRY(xoico_cdaleth_s_trans(o,source, "switch", buf ))
    BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf ))
    BLM_TRY(xoico_cdaleth_s_trans(o,source, "(", buf ))
    BLM_TRY(xoico_cdaleth_s_trans_expression(o,source, buf, NULL )) // def
    BLM_TRY(xoico_cdaleth_s_trans(o,source, ")", buf ))
    BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf ))
    BLM_TRY(xoico_cdaleth_s_trans_block(o,source, buf, true ))
    return  0;
    } /* try */
}

er_t xoico_cdaleth_s_trans_control_case( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth_control.x:285:1
     {
    BLM_TRY(xoico_cdaleth_s_trans(o,source, "case", buf ))
    BLM_TRY(xoico_cdaleth_s_trans_expression(o,source, buf, NULL ))
    BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf ))
    BLM_TRY(xoico_cdaleth_s_trans(o,source, ":", buf ))
    BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf ))
    BLM_TRY(xoico_cdaleth_s_trans_statement_as_block(o,source, buf, false ))
    
    return  0;
    } /* try */
}

er_t xoico_cdaleth_s_trans_control_default( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth_control.x:299:1
     {
    BLM_TRY(xoico_cdaleth_s_trans(o,source, "default", buf ))
    BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf ))
    BLM_TRY(xoico_cdaleth_s_trans(o,source, ":", buf ))
    BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf ))
    BLM_TRY(xoico_cdaleth_s_trans_statement_as_block(o,source, buf, false ))
    return  0;
    } /* try */
}

er_t xoico_cdaleth_s_trans_control_break( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth_control.x:311:1
     {
    BLM_TRY(xoico_cdaleth_s_parse(o,source, "break ;" ))
    
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
    
    if( ledge_level == -1 ) return  bcore_source_a_parse_error_fa( source,"'break' has no ledge." );
    
    if( use_blm )
    {
        st_s_push_fa( buf,"BLM_BREAK_LEVEL(#<sz_t>);", ledge_level );
    }
    else
    {
        st_s_push_sc( buf,"break;" );
    }
    
    return  0;
    } /* try */
}

er_t xoico_cdaleth_s_trans_control_return( xoico_cdaleth_s* o, bcore_source* source, st_s* buf )
{
    // xoico_cdaleth_control.x:345:1
    BLM_INIT_LEVEL(0); {
    BLM_TRY(xoico_cdaleth_s_parse(o,source, "return" ))
    
    st_s* buf_expr = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create() ));
    xoico_typespec_s* typespec_expr = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create() ));
    const xoico_typespec_s* typespec_ret = o->typespec_ret;
    
    BLM_TRY(xoico_cdaleth_s_trans_expression(o,source, buf_expr, typespec_expr ))
    BLM_TRY(xoico_cdaleth_s_trans_whitespace(o,source, buf ))
    BLM_TRY(xoico_cdaleth_s_parse(o,source, ";" ))
    
    if( typespec_expr->type )
    {
        if( !xoico_cdaleth_s_returns_a_value(o) )
        {
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Function does not return a value." ))
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
        if( xoico_cdaleth_s_returns_a_value(o) )
        {
            st_s_push_sc( buf,"BLM_RETURNV(" );
            BLM_TRY(xoico_cdaleth_s_push_typespec(o,typespec_ret, buf ))
            st_s_push_sc( buf,"," );
            if( typespec_expr->type )
            {
                BLM_TRY(xoico_cdaleth_s_adapt_expression(o,source, typespec_expr, typespec_ret, buf_expr, buf ))
            }
            else
            {
                st_s_push_st( buf,buf_expr );
            }
            st_s_push_sc( buf,")" );  // do not terminate BLM_RETURNV macro with a semicolon, otherwise if-else statements might not be handled correctly
        }
        else
        {
            st_s_push_sc( buf,"BLM_RETURN" );
            st_s_push_st( buf,buf_expr );
            st_s_push_sc( buf,";" );
        }
    }
    else
    {
        st_s_push_sc( buf,"return " );
        if( typespec_expr->type )
        {
            BLM_TRY(xoico_cdaleth_s_adapt_expression(o,source, typespec_expr, typespec_ret, buf_expr, buf ))
        }
        else
        {
            st_s_push_st( buf,buf_expr );
        }
        st_s_push_sc( buf,";" );
    }
    
    BLM_RETURNV(er_t, 0)
    } /* try */
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
    
    bcore_hmap_tpuz_s_clear(&(o->hmap_name));
    for( sz_t i = 0; i < o->adl.size; i++ ) bcore_hmap_tpuz_s_set(&(o->hmap_name),o->adl.data[i]->name, i );
}

xoico_cdaleth_stack_var_s* xoico_cdaleth_stack_var_s_push_unit( xoico_cdaleth_stack_var_s* o, const xoico_cdaleth_stack_var_unit_s* unit )
{
    // xoico_cdaleth.h:69:9
    
    xoico_cdaleth_stack_var_unit_adl_s_push_c( &(o->adl),unit );
    bcore_hmap_tpuz_s_set(&(o->hmap_name),unit->name, o->adl.size - 1 );
    return  o;
}

xoico_cdaleth_stack_var_s* xoico_cdaleth_stack_var_s_pop_level( xoico_cdaleth_stack_var_s* o, sz_t level )
{
    // xoico_cdaleth.h:76:9
    
    sz_t size = o->adl.size;
    while( size > 0 && o->adl.data[ size - 1 ]->level >= level ) size--;
    xoico_cdaleth_stack_var_unit_adl_s_set_size( &(o->adl),size );
    xoico_cdaleth_stack_var_s_rehash_names(o);
    return  o;
}

const xoico_typespec_s* xoico_cdaleth_stack_var_s_get_typespec( const xoico_cdaleth_stack_var_s* o, tp_t name )
{
    // xoico_cdaleth.h:85:9
    
    uz_t* p_idx = bcore_hmap_tpuz_s_get(&(o->hmap_name),name );
    if( !p_idx ) return  NULL;
    return &( o->adl.data[ *p_idx ]->typespec);
}

const sz_t xoico_cdaleth_stack_var_s_get_level( const xoico_cdaleth_stack_var_s* o, tp_t name )
{
    // xoico_cdaleth.h:93:9
    
    uz_t* p_idx = bcore_hmap_tpuz_s_get(&(o->hmap_name),name );
    if( !p_idx ) return  -1;
    return  o->adl.data[ *p_idx ]->level;
}

void xoico_cdaleth_stack_var_s_clear( xoico_cdaleth_stack_var_s* o )
{
    // xoico_cdaleth.h:100:9
    
    xoico_cdaleth_stack_var_unit_adl_s_clear( &(o->adl));
    bcore_hmap_tpuz_s_clear(&(o->hmap_name));
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
    
    xoico_cdaleth_stack_block_unit_adl_s_set_size( &(o->adl),sz_max( o->adl.size - 1, 0 ) );
    return  o;
}

XOILA_DEFINE_SPECT( xoico_cdaleth, xoico_cdaleth_stack_block )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/
// source: xoico_che.h
#include "xoico_che.h"

//----------------------------------------------------------------------------------------------------------------------
// group: xoico_che

BCORE_DEFINE_OBJECT_INST_P( xoico_che_s )
"aware xoico_che"
"{"
    "bl_t verbose = false;"
    "bl_t insert_source_reference = true;"
    "hidden xoico_compiler_s* compiler;"
    "hidden xoico_group_s* group;"
    "hidden xoico_stamp_s* stamp;"
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
    // xoico_che.h:372:5
    
    return  xoico_che_s_is_builtin_func(o,tp_identifier ) ||
           xoico_che_s_is_control_name(o,tp_identifier ) ||
           tp_identifier == TYPEOF_verbatim_C;
}

sc_t xoico_che_s_nameof( xoico_che_s* o, tp_t type )
{
    // xoico_che.h:381:5
    
    sc_t name = bcore_hmap_name_s_get_sc(&(o->hmap_name),type );
    if( !name ) name = xoico_compiler_s_nameof(o->compiler,type );
    return  name;
}

void xoico_che_s_init_level0( xoico_che_s* o )
{
    // xoico_che.h:388:5
    
    xoico_che_stack_block_s_clear(&(o->stack_block));
    xoico_che_stack_block_s_push(&(o->stack_block));
    o->level = 0;
}

void xoico_che_s_inc_block( xoico_che_s* o )
{
    // xoico_che.h:395:5
    
    xoico_che_stack_block_s_push(&(o->stack_block));
    o->level++;
    xoico_che_s_stack_block_get_top_unit(o)->level = o->level;
}

void xoico_che_s_dec_block( xoico_che_s* o )
{
    // xoico_che.h:402:5
    
    xoico_che_stack_var_s_pop_level(&(o->stack_var),o->level );
    o->level--;
    ASSERT( o->level >= 0 );
    xoico_che_stack_block_s_pop(&(o->stack_block));
}

xoico_che_stack_block_unit_s* xoico_che_s_stack_block_get_top_unit( xoico_che_s* o )
{
    // xoico_che.h:410:5
    
    return  o->stack_block.adl.data[ o->stack_block.adl.size - 1 ];
}

xoico_che_stack_block_unit_s* xoico_che_s_stack_block_get_bottom_unit( xoico_che_s* o )
{
    // xoico_che.h:415:5
    
    return  o->stack_block.adl.data[ 0 ];
}

xoico_che_stack_block_unit_s* xoico_che_s_stack_block_get_level_unit( xoico_che_s* o, sz_t level )
{
    // xoico_che.h:420:5
    
    {const xoico_che_stack_block_unit_adl_s* __a=&(o->stack_block.adl );if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_che_stack_block_unit_s* e=__a->data[__i]; if( e->level == level ) return  e;
    }}ERR_fa( "Level #<sz_t> not found.", level );
    return  NULL;
}

void xoico_che_s_push_typedecl( xoico_che_s* o, const xoico_typespec_s* typespec, tp_t name )
{
    // xoico_che.h:427:5
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
    // xoico_che.h:437:5
    BLM_INIT_LEVEL(0);
    xoico_che_result* result = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
    xoico_che_s_push_typespec(o,typespec, result );
    bcore_sink_a_push_sc( sink,((st_s*)BLM_LEVEL_T_PUSH(0,st_s,xoico_che_result_a_create_st(result)))->sc );
    BLM_DOWN();
}

bl_t xoico_che_s_returns_a_value( const xoico_che_s* o )
{
    // xoico_che.h:454:5
    
    return  ( !( ( o->typespec_ret.type == 0 ) || ( o->typespec_ret.type == TYPEOF_void ) ) ) || ( o->typespec_ret.indirection > 0 );
}

er_t xoico_che_s_parse( const xoico_che_s* o, bcore_source* source, sc_t format )
{
    // xoico_che.h:459:5
    
    return  bcore_source_a_parse_em_fa( source,format );
}

er_t xoico_che_s_trans( const xoico_che_s* o, bcore_source* source, sc_t format, xoico_che_result* result )
{
    // xoico_che.h:464:5
    
    BLM_TRY(xoico_che_s_parse(o,source, format ))
    xoico_che_result_a_push_sc(result,format );
    return  0;
}

tp_t xoico_che_s_get_identifier( xoico_che_s* o, bcore_source* source, bl_t take_from_source )
{
    // xoico_che.x:26:1
    BLM_INIT_LEVEL(0);
    tp_t tp_identifier = 0;
    if( bcore_source_a_parse_bl( source,"#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||[0]=='_'||[0]=='@'||[0]=='$'||([0]==':'&&([1]!=' '&&[1]!='\t'&&[1]!='\n'&&[1]!='/')))" ) )
    {
        sz_t source_index = take_from_source ? 0 : bcore_source_a_get_index( source);
        switch( bcore_source_a_inspect_char( source) )
        {
            case '@':
            {
                bcore_source_a_get_char( source);
                st_s* st_name = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
                st_s_copy(st_name,o->stamp ? &o->stamp->st_name : &o->group->st_name );
                if( bcore_source_a_parse_bl( source,"#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||[0]=='_'||([0]>='0'&&[0]<='9'))" ) )
                {
                    bcore_source_a_parse_fa( source,"#:name", st_name );
                }
                tp_identifier = xoico_che_s_entypeof(o,st_name->sc );
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
                st_s* st_name = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
                xoico_group_s_parse_name(o->group,st_name, source );
                tp_identifier = xoico_che_s_entypeof(o,st_name->sc );
            }
            break;
    
            default:
            {
                st_s* st_name = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
                bcore_source_a_parse_fa( source,"#name", st_name );
                tp_identifier = xoico_che_s_entypeof(o,st_name->sc );
            }
            break;
        }
    
        if( !take_from_source ) bcore_source_a_set_index( source,source_index );
    }
    
    BLM_RETURNV(tp_t, tp_identifier)
}

er_t xoico_che_s_trans_identifier( xoico_che_s* o, bcore_source* source, xoico_che_result* result, tp_t* tp_identifier )
{
    // xoico_che.x:80:1
     {
    tp_t identifier = xoico_che_s_get_identifier(o,source, true );
    if( !identifier )
    {
        return  bcore_source_a_parse_error_fa( source,"Identifier exected" );
    }
    if( tp_identifier ) *tp_identifier = identifier;
    if( result ) BLM_TRY(xoico_che_result_a_push_sc(result,xoico_che_s_nameof(o,identifier ) ))
    return  0;
    } /* try */
}

er_t xoico_che_s_trans_number_literal( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che.x:95:1
     {
    bl_t hex = false;
    if( bcore_source_a_parse_bl( source,"#?'0x'" ) )
    {
        BLM_TRY(xoico_che_result_a_push_sc(result,"0x" ))
        hex = true;
    }
    else if( bcore_source_a_parse_bl( source,"#?'0X'" ) )
    {
        BLM_TRY(xoico_che_result_a_push_sc(result,"0X" ))
        hex = true;
    }
    
    if( hex )
    {
        while( bcore_source_a_parse_bl( source,"#?(([0]>='0'&&[0]<='9')||([0]>='a'&&[0]<='f')||([0]>='A'&&[0]<='F'))" ) )
        {
            BLM_TRY(xoico_che_result_a_push_char(result,bcore_source_a_get_char( source) ))
        }
    }
    else // decimal
    {
        while( bcore_source_a_parse_bl( source,"#?([0]>='0'&&[0]<='9')" ) )
        {
            BLM_TRY(xoico_che_result_a_push_char(result,bcore_source_a_get_char( source) ))
        }
    }
    
    bl_t fraction = false;
    
    if( bcore_source_a_parse_bl( source,"#?([0]=='.')" ) )
    {
        BLM_TRY(xoico_che_result_a_push_char(result,bcore_source_a_get_char( source) ))
        fraction = true;
    }
    
    if( fraction )
    {
        while( bcore_source_a_parse_bl( source,"#?([0]>='0'&&[0]<='9')" ) )
        {
            BLM_TRY(xoico_che_result_a_push_char(result,bcore_source_a_get_char( source) ))
        }
    }
    
    bl_t exponent = false;
    
    if( bcore_source_a_parse_bl( source,"#?([0]=='e'&&[0]=='E')" ) )
    {
        BLM_TRY(xoico_che_result_a_push_char(result,bcore_source_a_get_char( source) ))
        exponent = true;
    }
    
    if( exponent )
    {
        if( bcore_source_a_parse_bl( source,"#?([0]=='+'||[0]=='-')" ) )
        {
            BLM_TRY(xoico_che_result_a_push_char(result,bcore_source_a_get_char( source) ))
        }
    
        while( bcore_source_a_parse_bl( source,"#?([0]>='0'&&[0]<='9')" ) )
        {
            BLM_TRY(xoico_che_result_a_push_char(result,bcore_source_a_get_char( source) ))
        }
    }
    
    // suffix
    while( bcore_source_a_parse_bl( source,"#?([0]=='l'||[0]=='L'||[0]=='u'||[0]=='U'||[0]=='f'||[0]=='F')" ) )
    {
        BLM_TRY(xoico_che_result_a_push_char(result,bcore_source_a_get_char( source) ))
    }
    
    return  0;
    } /* try */
}

er_t xoico_che_s_trans_string_literal( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che.x:173:1
     {
    BLM_TRY(xoico_che_s_trans(o,source, "\"", result ))
    
    while( !bcore_source_a_eos( source) && !bcore_source_a_parse_bl( source,"#=?'\"'" ) )
    {
        if( bcore_source_a_parse_bl( source,"#?'\\'" ) ) BLM_TRY(xoico_che_result_a_push_char(result,'\\' ))
        BLM_TRY(xoico_che_result_a_push_char(result,bcore_source_a_get_char( source) ))
    }
    
    BLM_TRY(xoico_che_s_trans(o,source, "\"", result ))
    return  0;
    } /* try */
}

er_t xoico_che_s_trans_char_literal( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che.x:190:1
    
    {
        BLM_TRY(xoico_che_s_trans(o,source, "'", result ))
    
        while( !bcore_source_a_eos( source) && !bcore_source_a_parse_bl( source,"#=?|'|" ) )
        {
            if( bcore_source_a_parse_bl( source,"#?'\\'" ) ) BLM_TRY(xoico_che_result_a_push_char(result,'\\' ))
            BLM_TRY(xoico_che_result_a_push_char(result,bcore_source_a_get_char( source) ))
        }
    
        BLM_TRY(xoico_che_s_trans(o,source, "'", result ))
        return  0;
    } /* try */
}

er_t xoico_che_s_trans_whitespace( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che.x:209:1
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
                if( result )  BLM_TRY(xoico_che_result_a_push_char(result,c ))
            }
            break;
    
            case '/':
            {
                if( bcore_source_a_parse_bl( source,"#?'//'" ) )
                {
                    if( result ) BLM_TRY(xoico_che_result_a_push_sc(result,"//" ))
                    while( !bcore_source_a_eos( source) )
                    {
                        char c =  bcore_source_a_get_char( source);
                        if( result ) BLM_TRY(xoico_che_result_a_push_char(result,c ))
                        if( c == '\n' ) break;
                    }
                }
                else if( bcore_source_a_parse_bl( source,"#?'/*'" ) )
                {
                    if( result ) BLM_TRY(xoico_che_result_a_push_sc(result,"/*" ))
                    while( !bcore_source_a_eos( source) )
                    {
                        if( bcore_source_a_parse_bl( source,"#?'*/'" ) )
                        {
                            if( result ) BLM_TRY(xoico_che_result_a_push_sc(result,"*/" ))
                            break;
                        }
                        char c =  bcore_source_a_get_char( source);
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
    } /* try */
}

er_t xoico_che_s_trans_preprocessor( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che.x:271:1
     {
    BLM_TRY(xoico_che_s_parse(o,source, "##" ))
    BLM_TRY(xoico_che_result_a_push_sc(result,"#" ))
    while( !bcore_source_a_eos( source) )
    {
        char c = bcore_source_a_get_char( source);
        BLM_TRY(xoico_che_result_a_push_char(result,c ))
        if( c == '\\' && bcore_source_a_inspect_char( source) == '\n' ) BLM_TRY(xoico_che_result_a_push_char(result,bcore_source_a_get_char( source) ))
        if( c == '\n' ) break;
    }
    return  0;
    } /* try */
}

tp_t xoico_che_s_trans_inert_operator( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che.x:288:1
    
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
            xoico_che_result_a_push_char(result,bcore_source_a_get_char( source) );
            return  1;
        }
        break;
    
        default: break;
    }
    
    return  false;
}

er_t xoico_che_s_adapt_expression_indirection( xoico_che_s* o, bcore_source* source, const xoico_typespec_s* typespec_expr, sz_t target_indirection, const xoico_che_result* result_expr, xoico_che_result* result )
{
    // xoico_che.x:330:1
     {
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
            return  bcore_source_a_parse_error_fa( source,"Increasing indirection: Expression has no address." );
        }
    }
    else if( target_indirection == typespec_expr->indirection - 1 )
    {
        BLM_TRY(xoico_che_result_a_push_sc(result,"*(" ))
        xoico_che_result_a_push_result_c(result,result_expr );
        BLM_TRY(xoico_che_result_a_push_sc(result,")" ))
    }
    else
    {
        return  bcore_source_a_parse_error_fa( source,"Cannot adapt from expression's indirection '#<sz_t>' to target indirection '#<sz_t>'.",
            typespec_expr->indirection,
            target_indirection
        );
    }
    return  0;
    } /* try */
}

er_t xoico_che_s_adapt_expression( xoico_che_s* o, bcore_source* source, const xoico_typespec_s* typespec_expr, const xoico_typespec_s* typespec_target, const xoico_che_result* result_expr, xoico_che_result* result )
{
    // xoico_che.x:380:1
    BLM_INIT_LEVEL(0); {
    if( !typespec_expr->type )
    {
        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"xoico_che_s_adapt_expression: no expression type specified.",
            typespec_expr->indirection,
            typespec_target->indirection
        ))
    }
    
    if( !typespec_target->type )
    {
        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"xoico_che_s_adapt_expression: no target type specified.",
            typespec_expr->indirection,
            typespec_target->indirection
        ))
    }
    
    if( typespec_target->type == TYPEOF_type_deduce ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"adapt_expression: typespec_target is 'type_deduce'" ))
    if( typespec_target->type == TYPEOF_type_object ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"adapt_expression: typespec_target is 'type_object'" ))
    if( typespec_expr->type == TYPEOF_type_deduce ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"adapt_expression: typespec_expr is 'type_deduce'" ))
    if( typespec_expr->type == TYPEOF_type_object ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"adapt_expression: typespec_expr is 'type_object'" ))
    
    bl_t discarding_const =
        ( typespec_expr->flag_const && !typespec_target->flag_const ) &&
        ( typespec_expr->indirection > 0 || typespec_target->indirection > 0 );
    
    if( discarding_const ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Discarding 'const' qualifier." ))
    
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
                    implicit_cast = stamp->is_aware;
                }
            }
    
            if( !implicit_cast )
            {
                st_s* st_typespec_expr = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
                st_s* st_typespec_target = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
                xoico_che_s_typespec_to_sink(o,typespec_expr,((bcore_sink*)( st_typespec_expr )));
                xoico_che_s_typespec_to_sink(o,typespec_target,((bcore_sink*)( st_typespec_target )));
                BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Implicit cast from '#<sc_t>' to '#<sc_t>' is not possible.", st_typespec_expr->sc, st_typespec_target->sc ))
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
    } /* try */
}

er_t xoico_che_s_trans_function_args( xoico_che_s* o, bcore_source* source, const xoico_signature_s* signature, const xoico_che_result* result_obj_expr, const xoico_typespec_s* typespec_obj_expr, xoico_che_result* result_out )
{
    // xoico_che.x:471:1
    BLM_INIT_LEVEL(0); {
    BLM_TRY(xoico_che_s_trans(o,source, "(", result_out ))
    
    if( signature->arg_o )
    {
        if( !result_obj_expr )
        {
            xoico_che_result* result_expr   = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
            xoico_typespec_s* typespec_expr = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
            BLM_TRY(xoico_che_s_trans_expression(o,source, result_expr, typespec_expr ))
            result_obj_expr = result_expr;
            typespec_obj_expr = typespec_expr;
            if( signature->args.size > 0 ) BLM_TRY(xoico_che_s_parse(o,source, " ," ))
        }
    
        xoico_typespec_s* typespec_obj_out = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_clone(typespec_obj_expr)));
        typespec_obj_out->indirection = 1; // first argument of member functions has always indirection 1
    
        if( typespec_obj_expr->type )
        {
            BLM_TRY(xoico_che_s_adapt_expression(o,source, typespec_obj_expr, typespec_obj_out, result_obj_expr, result_out ))
        }
        else
        {
            xoico_che_result_a_push_result_c(result_out,result_obj_expr );
        }
        if( signature->args.size > 0 ) BLM_TRY(xoico_che_result_a_push_sc(result_out,"," ))
    }
    
    {const xoico_args_s* __a=&(signature->args );if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_arg_s* arg=&(__a->data[__i]);
    {BLM_INIT_LEVEL(4);
        xoico_che_result* result_expr = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
        xoico_typespec_s* typespec_expr = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(4,xoico_typespec_s,xoico_typespec_s_create()));
        BLM_TRY(xoico_che_s_parse(o,source, " " ))
        if( __i > 0 ) BLM_TRY(xoico_che_s_parse(o,source, " ," ))
        BLM_TRY(xoico_che_s_trans_expression(o,source, result_expr, typespec_expr ))
        if( __i > 0 ) BLM_TRY(xoico_che_result_a_push_sc(result_out,"," ))
        if( typespec_expr->type )
        {
            BLM_TRY(xoico_che_s_adapt_expression(o,source, typespec_expr, &arg->typespec, result_expr, result_out ))
        }
        else
        {
            xoico_che_result_a_push_result_d(result_out,((xoico_che_result*)bcore_fork(result_expr)) );
        }
    BLM_DOWN();}
    
    }}BLM_TRY(xoico_che_s_parse(o,source, " " ))
    BLM_TRY(xoico_che_s_trans(o,source, ")", result_out ))
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_che_s_trans_typespec_member( xoico_che_s* o, bcore_source* source, xoico_che_result* result, const xoico_typespec_s* in_typespec, xoico_typespec_s* out_typespec )
{
    // xoico_che.x:536:1
    BLM_INIT_LEVEL(0); {
    if( bcore_source_a_parse_bl_fa( source,"#?'->'" ) )
    {
        if( in_typespec->indirection != 1 )
        {
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Given indirection is '#<sz_t>'. '->' can only be used at indirection '1'.", in_typespec->indirection ))
        }
    }
    else
    {
        BLM_TRY(xoico_che_s_parse(o,source, "." ))
    }
    BLM_TRY(xoico_che_s_parse(o,source, " " ))
    xoico_compiler_element_info_s* info = ((xoico_compiler_element_info_s*)BLM_LEVEL_T_PUSH(0,xoico_compiler_element_info_s,xoico_compiler_element_info_s_create()));
    if( bcore_source_a_parse_bl_fa( source,"#=?'['" ) || bcore_source_a_parse_bl_fa( source,"#=?'?['" ) ) // array subscript
    {
        bl_t bounds_check = false;
        if( bcore_source_a_parse_bl_fa( source,"#=?'?'" ) )
        {
            BLM_TRY(xoico_che_s_parse(o,source, "?[" ))
            bounds_check = true;
        }
        else
        {
            BLM_TRY(xoico_che_s_parse(o,source, "[" ))
        }
    
        if( bounds_check ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Bounds check not yet available." ))
    
        if( in_typespec->indirection > 1 )
        {
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Resolving subscript: Indirection '#<sz_t>' is too large.",
                in_typespec->indirection
            ))
        }
    
        xoico_che_result_a_push_fa( result,"#<sc_t>data[", ( in_typespec->indirection == 1 ) ? "->" : "." );
        BLM_TRY(xoico_che_s_trans_expression(o,source, result, NULL ))
        BLM_TRY(xoico_che_s_parse(o,source, "]" ))
        BLM_TRY(xoico_che_result_a_push_sc(result,"]" ))
    
        if( xoico_compiler_s_get_type_array_element_info(o->compiler,in_typespec->type, info ) )
        {
            BLM_TRY(xoico_che_s_trans_typespec_expression(o,source, result, &info->type_info.typespec, out_typespec ))
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
        BLM_TRY(xoico_che_s_trans_identifier(o,source, result_local, &tp_identifier ))
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
            if( info->signature ) // member function
            {
                sc_t sc_func_name = xoico_che_s_nameof(o,info->type_info.typespec.type );
                ASSERT( sc_func_name );
                xoico_che_result* result_arg_obj = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_a_clone(result)));
                xoico_che_result_a_copy_fa( result,"#<sc_t>", sc_func_name );
                BLM_TRY(xoico_che_s_trans_function_args(o,source, info->signature, result_arg_obj, in_typespec, result ))
                BLM_TRY(xoico_che_s_trans_typespec_expression(o,source, result, &info->signature->typespec_ret, out_typespec ))
            }
            else // traced member element
            {
                if( in_typespec->indirection > 1 )
                {
                    BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Dereferencing #<sc_t>: Indirection '#<sz_t>' is too large.",
                        xoico_che_s_nameof(o,tp_identifier ),
                        in_typespec->indirection
                    ))
                }
                xoico_che_result_a_push_fa( result,"#<sc_t>", ( in_typespec->indirection == 1 ) ? "->" : "." );
                xoico_che_result_a_push_result_d(result,((xoico_che_result*)bcore_fork(result_local)) );
    
                BLM_TRY(xoico_che_s_trans_typespec_expression(o,source, result, &info->type_info.typespec, out_typespec ))
            }
        }
        else if( bcore_source_a_parse_bl_fa( source,"#?'('" ) ) // untraced member function
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
            while( !bcore_source_a_eos( source) )
            {
                if( bcore_source_a_parse_bl_fa( source,"#=?')'" ) ) break;
    
                xoico_che_result* result_expr = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
                if( !first ) BLM_TRY(xoico_che_s_parse(o,source, "," ))
                BLM_TRY(xoico_che_s_trans_expression(o,source, result_expr, NULL ))
                BLM_TRY(xoico_che_s_trans_whitespace(o,source, result_expr ))
                xoico_che_result_a_push_fa( result,"," );
                xoico_che_result_a_push_result_d(result,((xoico_che_result*)bcore_fork(result_expr)) );
                first = false;
            }
    
            BLM_TRY(xoico_che_s_parse(o,source, ")" ))
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
    } /* try */
}

er_t xoico_che_s_trans_typespec_array_subscript( xoico_che_s* o, bcore_source* source, xoico_che_result* result, const xoico_typespec_s* in_typespec, xoico_typespec_s* out_typespec )
{
    // xoico_che.x:705:1
    BLM_INIT_LEVEL(0); {
    BLM_TRY(xoico_che_s_parse(o,source, "[" ))
    
    BLM_TRY(xoico_che_result_a_push_sc(result,"[" ))
    BLM_TRY(xoico_che_s_trans_expression(o,source, result, NULL ))
    BLM_TRY(xoico_che_s_parse(o,source, "]" ))
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
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Array subscript requires indirection >= 1." ))
        }
    }
    else
    {
        typespec->indirection--;
    }
    
    BLM_TRY(xoico_che_s_trans_typespec_expression(o,source, result, typespec, out_typespec ))
    
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_che_s_trans_typespec_create( xoico_che_s* o, bcore_source* source, xoico_che_result* result, const xoico_typespec_s* in_typespec, xoico_typespec_s* out_typespec )
{
    // xoico_che.x:749:1
    BLM_INIT_LEVEL(0); {
    BLM_TRY(xoico_che_s_parse(o,source, "!" ))
    
    //ignore in case indirection is 0;
    if( in_typespec->indirection > 0 )
    {
        if( !( in_typespec->indirection == 1 && in_typespec->flag_addressable ) )
        {
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Create-Operator requires lvalue with addressable indirection of 1." ))
        }
    
        if( xoico_che_s_is_group( o,in_typespec->type ) )
        {
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Create-Operator: lvalue is a group." ))
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
    } /* try */
}

er_t xoico_che_s_trans_typespec_test_presence( xoico_che_s* o, bcore_source* source, xoico_che_result* result, const xoico_typespec_s* in_typespec, xoico_typespec_s* out_typespec )
{
    // xoico_che.x:791:1
    BLM_INIT_LEVEL(0); {
    BLM_TRY(xoico_che_s_parse(o,source, "?" ))
    
    //ignore in case indirection is 0;
    if( in_typespec->indirection > 0 )
    {
        if( in_typespec->indirection != 1 )
        {
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Test-Operator requires lvalue with indirection of 1." ))
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
    } /* try */
}

er_t xoico_che_s_trans_typespec_attach( xoico_che_s* o, bcore_source* source, xoico_che_result* result, const xoico_typespec_s* in_typespec, xoico_typespec_s* out_typespec )
{
    // xoico_che.x:828:1
    BLM_INIT_LEVEL(0); {
    if( !( in_typespec->indirection == 1 && in_typespec->flag_addressable ) )
    {
        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Attach-Operator requires lvalue with addressable indirection of 1" ))
    }
    
    BLM_TRY(xoico_che_s_parse(o,source, "=<" ))
    
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
        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Attach operator requires rvalue with indirection '1'" ))
    }
    
    if( out_typespec ) xoico_typespec_s_copy(out_typespec,in_typespec );
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_che_s_trans_typespec_ternary_branch( xoico_che_s* o, bcore_source* source, xoico_che_result* result, const xoico_typespec_s* in_typespec, xoico_typespec_s* out_typespec )
{
    // xoico_che.x:885:1
    BLM_INIT_LEVEL(0); {
    BLM_TRY(xoico_che_s_parse(o,source, "?" ))
    BLM_TRY(xoico_che_result_a_push_sc(result,"?" ))
    xoico_typespec_s* typespec_true  = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
    
    BLM_TRY(xoico_che_s_trans_expression(o,source, result, typespec_true ))
    BLM_TRY(xoico_che_s_parse(o,source, ": " ))
    BLM_TRY(xoico_che_result_a_push_sc(result,": " ))
    BLM_TRY(xoico_che_s_trans_expression(o,source, result, NULL ))
    
    if( out_typespec && typespec_true->type )
    {
        xoico_typespec_s_copy(out_typespec,typespec_true );
        out_typespec->flag_addressable = false;
    }
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_che_s_trans_typespec_expression( xoico_che_s* o, bcore_source* source, xoico_che_result* result, const xoico_typespec_s* in_typespec, xoico_typespec_s* out_typespec )
{
    // xoico_che.x:916:1
     {
    if( out_typespec ) out_typespec->type = 0;
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    
    u0_t c[ 2 ];
    bcore_source_a_inspect_data( source,c, sizeof( c ) );
    
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
    } /* try */
}

er_t xoico_che_s_trans_member( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che.x:962:1
     {
    if(      bcore_source_a_parse_bl_fa( source,"#?'.'"  ) ) BLM_TRY(xoico_che_result_a_push_sc(result,"." ))
    else if( bcore_source_a_parse_bl_fa( source,"#?'->'" ) ) BLM_TRY(xoico_che_result_a_push_sc(result,"->" ))
    
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    tp_t tp_identifier = xoico_che_s_get_identifier(o,source, false );
    
    if( xoico_che_s_is_builtin_func(o,tp_identifier ) )
    {
        return  bcore_source_a_parse_error_fa( source,"Expression before '#<sc_t>' not tractable\n", xoico_che_s_nameof(o,tp_identifier ) );
    }
    
    BLM_TRY(xoico_che_s_trans_identifier(o,source, result, NULL ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    if( bcore_source_a_parse_bl_fa( source,"#?'('") )
    {
        return  bcore_source_a_parse_error_fa( source,"Untraced member function '#<sc_t>'\n", xoico_che_s_nameof(o,tp_identifier ) );
    }
    return  0;
    } /* try */
}

er_t xoico_che_s_try_take_typespec( xoico_che_s* o, bcore_source* source, xoico_typespec_s* typespec, bl_t require_tractable_type, bl_t* success )
{
    // xoico_che.x:999:1
     {
    if( success ) *success = false;
    
    sz_t index = bcore_source_a_get_index( source);
    
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, NULL ))
    tp_t tp_identifier = xoico_che_s_get_identifier(o,source, true );
    
    if( !tp_identifier )
    {
        bcore_source_a_set_index( source,index );
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
        if( tp_identifier == TYPEOF_keep     ) typespec->flag_keep     = true;
    
        // take fails if keyword is actually a function
        if( bcore_source_a_parse_bl_fa( source,"#?'('" ) )
        {
            bcore_source_a_set_index( source,index );
            return  0;
        }
    
        BLM_TRY(xoico_che_s_trans_identifier(o,source, NULL, &tp_identifier ))
        BLM_TRY(xoico_che_s_trans_whitespace(o,source, NULL ))
    }
    
    typespec->type = tp_identifier;
    while( bcore_source_a_parse_bl_fa( source,"#?'*'" ) )
    {
        typespec->indirection++;
        BLM_TRY(xoico_che_s_trans_whitespace(o,source, NULL ))
    }
    
    if( require_tractable_type )
    {
        if( !( tp_identifier == TYPEOF_type_deduce || xoico_che_s_is_type(o,tp_identifier ) ) )
        {
            bcore_source_a_set_index( source,index );
            return  0;
        }
    }
    
    if( success ) *success = true;
    return  0;
    } /* try */
}

er_t xoico_che_s_take_typespec( xoico_che_s* o, bcore_source* source, xoico_typespec_s* typespec, bl_t require_tractable_type )
{
    // xoico_che.x:1071:1
     {
    bl_t success = false;
    BLM_TRY(xoico_che_s_try_take_typespec(o,source, typespec, require_tractable_type, &success ))
    
    if( !success )
    {
        if( require_tractable_type )
        {
            return  bcore_source_a_parse_error_fa( source,"Typespec: Syntax error or intractable type." );
        }
        else
        {
            return  bcore_source_a_parse_error_fa( source,"Typespec: Syntax error." );
        }
    }
    
    return  0;
    } /* try */
}

er_t xoico_che_s_push_typespec( xoico_che_s* o, const xoico_typespec_s* typespec, xoico_che_result* result )
{
    // xoico_che.x:1093:1
    BLM_INIT_LEVEL(0); {
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
    
    st_s* st_type = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,((st_s*)(st_s_create_sc( xoico_che_s_nameof(o,type ) )))));
    
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
    } /* try */
}

er_t xoico_che_s_trans_type( xoico_che_s* o, bcore_source* source, xoico_che_result* result, xoico_typespec_s* out_typespec )
{
    // xoico_che.x:1140:1
    BLM_INIT_LEVEL(0); {
    xoico_che_result* result_type = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
    tp_t tp_identifier;
    BLM_TRY(xoico_che_s_trans_identifier(o,source, result_type, &tp_identifier ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result_type ))
    if( bcore_source_a_parse_bl_fa( source,"#?'!'" ) )
    {
        if( xoico_che_s_is_group(o,tp_identifier ) )
        {
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Operator '!': lvalue is a group." ))
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
    } /* try */
}

er_t xoico_che_s_trans_func( xoico_che_s* o, bcore_source* source, xoico_che_result* result, xoico_typespec_s* out_typespec )
{
    // xoico_che.x:1177:1
    BLM_INIT_LEVEL(0); {
    tp_t tp_identifier = 0;
    BLM_TRY(xoico_che_s_trans_identifier(o,source, result, &tp_identifier ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    
    if( bcore_source_a_parse_bl_fa( source,"#=?'('" ) ) // actual function call
    {
        const xoico_func_s* func = xoico_che_s_get_func(o,tp_identifier );
    
        if( !func->signature )
        {
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Function #<sc_t> has no signature.", xoico_che_s_nameof(o,tp_identifier ) ))
        }
    
        xoico_signature_s* signature = ((xoico_signature_s*)BLM_LEVEL_T_PUSH(0,xoico_signature_s,xoico_signature_s_clone(func->signature)));
        BLM_TRY(xoico_signature_s_relent(signature,func->stamp ? func->stamp->tp_name : func->group->tp_name ))
    
        BLM_TRY(xoico_che_s_trans_function_args(o,source, signature, NULL, NULL, result ))
        BLM_TRY(xoico_che_s_trans_typespec_expression(o,source, result,&( signature->typespec_ret), out_typespec ))
    }
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_che_s_trans_ternary_branch( xoico_che_s* o, bcore_source* source, xoico_che_result* result, xoico_typespec_s* out_typespec )
{
    // xoico_che.x:1212:1
     {
    BLM_TRY(xoico_che_s_parse(o,source, "?" ))
    BLM_TRY(xoico_che_result_a_push_sc(result,"?" ))
    BLM_TRY(xoico_che_s_trans_expression(o,source, result, NULL ))
    BLM_TRY(xoico_che_s_trans(o,source, ": ", result ))
    BLM_TRY(xoico_che_s_trans_expression(o,source, result, NULL ))
    return  0;
    } /* try */
}

er_t xoico_che_s_trans_bracket( xoico_che_s* o, bcore_source* source, xoico_che_result* result, xoico_typespec_s* out_typespec )
{
    // xoico_che.x:1233:1
     {
    BLM_TRY(xoico_che_s_parse(o,source, "(" ))
    BLM_TRY(xoico_che_result_a_push_char(result,'(' ))
    while( !bcore_source_a_eos( source) )
    {
        BLM_TRY(xoico_che_s_trans_expression(o,source, result, out_typespec ))
        if     ( bcore_source_a_parse_bl_fa( source,"#?')'" ) ) break;
        else if( bcore_source_a_parse_bl_fa( source,"#?','" ) ) BLM_TRY(xoico_che_result_a_push_char(result,',' ))
        else return  bcore_source_a_parse_error_fa( source,"Syntax error in bracket expression." );
        if( out_typespec ) out_typespec->type = 0;
    }
    BLM_TRY(xoico_che_result_a_push_char(result,')' ))
    return  0;
    } /* try */
}

er_t xoico_che_s_trans_array_subscript( xoico_che_s* o, bcore_source* source, xoico_che_result* result, xoico_typespec_s* out_typespec )
{
    // xoico_che.x:1260:1
     {
    BLM_TRY(xoico_che_s_parse(o,source, "[" ))
    BLM_TRY(xoico_che_result_a_push_sc(result,"[" ))
    BLM_TRY(xoico_che_s_trans_expression(o,source, result, NULL ))
    BLM_TRY(xoico_che_s_parse(o,source, "]" ))
    BLM_TRY(xoico_che_result_a_push_sc(result,"]" ))
    return  0;
    } /* try */
}

er_t xoico_che_s_trans_expression( xoico_che_s* o, bcore_source* source, xoico_che_result* result_out, xoico_typespec_s* out_typespec )
{
    // xoico_che.x:1281:1
    BLM_INIT_LEVEL(0); {
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
            BLM_TRY(xoico_che_s_parse(o,source, "verbatim_C {" ))
            BLM_TRY(xoico_che_s_trans_block_inside_verbatim_c(o,source, result ))
            BLM_TRY(xoico_che_s_parse(o,source, " }" ))
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
            if( bcore_source_a_parse_bl_fa( source,"#=?'('" ) )
            {
                BLM_TRY(xoico_che_s_trans_bracket(o,source, result, NULL ))
            }
        }
    }
    
    // literals and members
    else if( bcore_source_a_parse_bl_fa( source,"#?([0]>='0'&&[0]<='9')" ) ) BLM_TRY(xoico_che_s_trans_number_literal(o,source, result ))
    else if( bcore_source_a_parse_bl_fa( source,"#=?'\"'" )                ) BLM_TRY(xoico_che_s_trans_string_literal(o,source, result ))
    else if( bcore_source_a_parse_bl_fa( source,"#=?|'|" )                 ) BLM_TRY(xoico_che_s_trans_char_literal(o,source, result ))
    else if( bcore_source_a_parse_bl_fa( source,"#=?'.'" )                 ) BLM_TRY(xoico_che_s_trans_member(o,source, result ))
    else if( bcore_source_a_parse_bl_fa( source,"#=?'->'" )                ) BLM_TRY(xoico_che_s_trans_member(o,source, result ))
    
    else if( bcore_source_a_parse_bl_fa( source,"#=?'=<'" )                ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Attach operator: Expression not tractable." ))
    else if( xoico_che_s_trans_inert_operator(o,source, result )       ) {} // inert operators are not interpreted by che and passed to the c-compiler
    
    // ternary branch operator
    else if( bcore_source_a_parse_bl_fa( source,"#=?'?'" ) )
    {
        BLM_TRY(xoico_che_s_trans_ternary_branch(o,source, result, out_typespec ))
    }
    
    // general bracket
    else if( bcore_source_a_parse_bl_fa( source,"#=?'('" ) )
    {
        xoico_typespec_s* typespec_bracket = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
        BLM_TRY(xoico_che_s_trans_bracket(o,source, result, typespec_bracket ))
        if( typespec_bracket->type ) BLM_TRY(xoico_che_s_trans_typespec_expression(o,source, result, typespec_bracket, out_typespec ))
    }
    
    // array subscript
    else if( bcore_source_a_parse_bl_fa( source,"#=?'['" ) )
    {
        BLM_TRY(xoico_che_s_trans_array_subscript(o,source, result, out_typespec ))
    }
    
    // end of expression...
    else if( bcore_source_a_parse_bl_fa( source,sc_bl_end_of_expression ) )
    {
        continuation = false;
    }
    
    // unhandled
    else
    {
        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Syntax error after '#<sc_t>'", ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,xoico_che_result_a_create_st(result)))->sc ))
    }
    
    if( continuation )
    {
        if( !bcore_source_a_parse_bl_fa( source,sc_bl_end_of_expression ) )
        {
            if( out_typespec ) xoico_typespec_s_reset(out_typespec);
            BLM_TRY(xoico_che_s_trans_expression(o,source, result, NULL ))
        }
    }
    
    if( result_out ) xoico_che_result_a_push_result_d(result_out,((xoico_che_result*)bcore_fork(result)) );
    
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_che_s_try_trans_declaration( xoico_che_s* o, bcore_source* source, xoico_che_result* result_out, bl_t* success )
{
    // xoico_che.x:1420:1
    BLM_INIT_LEVEL(0); {
    if( success ) *success = false;
    
    xoico_typespec_s* typespec_var = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
    
    sz_t index = bcore_source_a_get_index( source);
    
    xoico_che_result* result_var = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
    
    bl_t success_take_typespec = false;
    BLM_TRY(xoico_che_s_try_take_typespec(o,source, typespec_var, true, &success_take_typespec ))
    
    if( !success_take_typespec )
    {
        bcore_source_a_set_index( source,index );
        BLM_RETURNV(er_t, 0)
    }
    
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result_var ))
    
    if
    (
        typespec_var->type &&
        bcore_source_a_parse_bl_fa( source,"#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||[0]=='_')" )
    )
    {
        tp_t tp_identifier = 0;
        BLM_TRY(xoico_che_s_trans_identifier(o,source, result_var, &tp_identifier ))
        BLM_TRY(xoico_che_s_trans_whitespace(o,source, result_var ))
    
        if( bcore_source_a_parse_bl_fa( source,"#?'='" ) )
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
                    BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Declaration-syntax: Deduce requested but expression is intractable." ))
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
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Declaration-syntax: Deduce requested without assignment." ))
        }
        else if( bcore_source_a_parse_bl_fa( source,"#=?'['" ) )
        {
            BLM_TRY(xoico_che_s_push_typespec(o,typespec_var, result_out ))
            while( bcore_source_a_parse_bl_fa( source,"#?'['" ) )
            {
                BLM_TRY(xoico_che_result_a_push_char(result_var,'[' ))
                BLM_TRY(xoico_che_s_trans_expression(o,source, result_var, NULL ))
                BLM_TRY(xoico_che_s_parse(o,source, "]" ))
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
    
        if( success ) *success = true;
    }
    else
    {
        bcore_source_a_set_index( source,index );
        BLM_RETURNV(er_t, 0)
    }
    
    if( success ) *success = true;
    
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_che_s_inspect_variable( xoico_che_s* o, bcore_source* source )
{
    // xoico_che.x:1529:1
    BLM_INIT_LEVEL(0); {
    BLM_TRY(xoico_che_s_parse(o,source, "\?\?" ))
    
    st_s* st = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    xoico_che_result* result_local = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
    xoico_typespec_s* typespec = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
    BLM_TRY(bcore_source_a_parse_em_fa( source," #until';' ", st ) )
    BLM_TRY(bcore_source_a_parse_em_fa( source,";" ) )
    bcore_msg_fa( " \?? #<sc_t>;\n", st->sc );
    if( xoico_che_s_trans_expression(o,((bcore_source*)BLM_LEVEL_A_PUSH(0,((bcore_source*)(bcore_source_string_s_create_fa( "#<st_s*>;", st ))))), result_local, typespec ) )
    {
        bcore_error_pop_to_sink( BCORE_STDOUT );
        bcore_msg_fa( "\n" );
    }
    else
    {
        if( st->size == 0 ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Variable name expected." ))
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
    } /* try */
}

er_t xoico_che_s_trans_statement_expression( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che.x:1566:1
    BLM_INIT_LEVEL(0); {
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
            if( !bcore_source_a_parse_bl_fa( source," #?';'" ) )
            {
                BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Inside a try-block: Expressions yielding 'er_t' must end with ';'" ))
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
    if( bcore_source_a_parse_bl_fa( source,"#?':'" ) ) BLM_TRY(xoico_che_result_a_push_char(result,':' ))
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_che_s_trans_statement( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che.x:1607:1
     {
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    
    if( bcore_source_a_parse_bl_fa( source,"#?([0]=='{'||[0]=='#'||[0]==';'||[0]==','||[0]==')'||[0]=='}'||([0]=='?'&&[1]=='?'))" ) )
    {
        char c = bcore_source_a_inspect_char( source);
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
                bcore_source_a_get_char( source);
                BLM_TRY(xoico_che_result_a_push_char(result,';' ))
            }
            break;
    
            case ',':
            {
                bcore_source_a_get_char( source);
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
                return  bcore_source_a_parse_error_fa( source,"Unmatched closing bracket." );
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
            BLM_TRY(xoico_che_s_try_trans_declaration(o,source, result, &success_declaration ))
            if( !success_declaration ) BLM_TRY(xoico_che_s_trans_statement_expression(o,source, result ))
        }
    }
    
    return  0;
    } /* try */
}

er_t xoico_che_s_trans_block_inside( xoico_che_s* o, bcore_source* source, xoico_che_result* result_out )
{
    // xoico_che.x:1684:1
    BLM_INIT_LEVEL(0); {
    xoico_che_result* result = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
    
    while( !bcore_source_a_parse_bl_fa( source,"#=?'}'" ) && !bcore_source_a_eos( source) )
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
    } /* try */
}

er_t xoico_che_s_trans_block( xoico_che_s* o, bcore_source* source, xoico_che_result* result_out, bl_t is_break_ledge )
{
    // xoico_che.x:1717:1
    BLM_INIT_LEVEL(0); {
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
    } /* try */
}

er_t xoico_che_s_trans_statement_as_block( xoico_che_s* o, bcore_source* source, xoico_che_result* result_out, bl_t is_break_ledge )
{
    // xoico_che.x:1734:1
    BLM_INIT_LEVEL(0); {
    xoico_che_result* result = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
    
    xoico_che_s_inc_block(o);
    xoico_che_s_stack_block_get_top_unit(o)->break_ledge = is_break_ledge;
    
    BLM_TRY(xoico_che_s_trans_statement(o,source, result ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    if( bcore_source_a_parse_bl_fa( source,"#?';'" ) ) BLM_TRY(xoico_che_result_a_push_sc(result,";" ))
    
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
    } /* try */
}

er_t xoico_che_s_trans_block_inside_verbatim_c( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che.x:1767:1
     {
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    while( !bcore_source_a_parse_bl_fa( source,"#=?'}'" ) && !bcore_source_a_eos( source) )
    {
        switch( bcore_source_a_inspect_char( source) )
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
                BLM_TRY(xoico_che_result_a_push_char(result,bcore_source_a_get_char( source) ))
                BLM_TRY(xoico_che_s_trans_block_inside_verbatim_c(o,source, result ))
                BLM_TRY(xoico_che_s_parse(o,source, "}" ))
                BLM_TRY(xoico_che_result_a_push_char(result,'}' ))
            }
            break;
    
            default:
            {
                BLM_TRY(xoico_che_result_a_push_char(result,bcore_source_a_get_char( source) ))
            }
            break;
        }
        BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    }
    return  0;
    } /* try */
}

er_t xoico_che_s_setup( xoico_che_s* o, const xoico_body_s* body, const xoico_signature_s* signature )
{
    // xoico_che.x:1808:1
    BLM_INIT_LEVEL(0); {
    tp_t tp_assoc_obj_type = body->stamp ? body->stamp->tp_name : body->group->tp_name;
    
    const xoico_args_s* args = &signature->args;
    
    tp_t tp_member_obj_type  = ( signature->arg_o == 0 ) ? 0 : tp_assoc_obj_type;
    bl_t member_obj_const = ( signature->arg_o == TYPEOF_const );
    tp_t tp_member_obj_name  = xoico_che_s_entypeof(o,"o" );
    
    xoico_typespec_s_copy(&(o->typespec_ret),&(signature->typespec_ret ));
    BLM_TRY(xoico_typespec_s_relent(&(o->typespec_ret),body->code->group, tp_assoc_obj_type ))
    
    o->group    = body->code->group;
    o->stamp    = body->code->stamp;
    o->compiler = body->group->compiler;
    o->member_obj_type = tp_member_obj_type;
    o->level    = 0;
    o->try_block_level = 0;
    xoico_che_stack_var_s_clear(&(o->stack_var));
    xoico_che_s_init_level0(o);
    
    xoico_che_stack_var_unit_s* unit = ((xoico_che_stack_var_unit_s*)BLM_LEVEL_T_PUSH(0,xoico_che_stack_var_unit_s,xoico_che_stack_var_unit_s_create()));
    
    if( tp_member_obj_type )
    {
        unit->typespec.flag_const = member_obj_const;
        unit->typespec.type = tp_member_obj_type;
        unit->typespec.indirection = 1;
        unit->name = tp_member_obj_name;
        unit->level = o->level;
        xoico_che_stack_var_s_push_unit(&(o->stack_var),unit );
        bcore_hmap_name_s_set_sc(&(o->hmap_name),xoico_compiler_s_nameof(o->compiler,tp_member_obj_type ) );
        bcore_hmap_name_s_set_sc(&(o->hmap_name),xoico_compiler_s_nameof(o->compiler,tp_member_obj_name ) );
    }
    
    {const xoico_args_s* __a=args ;if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_arg_s* arg=&(__a->data[__i]);
    {
        if( arg->typespec.type && arg->name )
        {
            xoico_typespec_s_copy(&(unit->typespec),&(arg->typespec ));
            BLM_TRY(xoico_typespec_s_relent(&(unit->typespec),o->group, tp_assoc_obj_type ))
            unit->name = arg->name;
            unit->level = o->level;
            xoico_che_stack_var_s_push_unit(&(o->stack_var),unit );
            bcore_hmap_name_s_set_sc(&(o->hmap_name),xoico_compiler_s_nameof(o->compiler,arg->typespec.type ) );
            bcore_hmap_name_s_set_sc(&(o->hmap_name),xoico_compiler_s_nameof(o->compiler,arg->name ) );
        }
    }
    }}BLM_RETURNV(er_t, 0)
    } /* try */
}

sz_t xoico_che_s_assess_indentation( bcore_source* source )
{
    // xoico_che.x:1862:1
    
    sz_t index = bcore_source_a_get_index( source);
    while( !bcore_source_a_eos( source) ) if( bcore_source_a_get_char( source) == '\n' ) break;
    sz_t indentation = 0;
    while( !bcore_source_a_eos( source) )
    {
        if( bcore_source_a_get_char( source) != ' ' ) break;
        indentation++;
    }
    bcore_source_a_set_index( source,index );
    return  indentation;
}

void xoico_che_s_remove_indentation( st_s* string, sz_t indentation )
{
    // xoico_che.x:1878:1
    
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

er_t xoico_che_s_translate_mutable( xoico_che_s* o, const xoico_body_s* body, const xoico_signature_s* signature, bcore_sink* sink )
{
    // xoico_che.x:1903:1
    BLM_INIT_LEVEL(0); {
    BLM_TRY(xoico_che_s_setup(o,body, signature ))
    
    bcore_source* source = ((bcore_source*)BLM_LEVEL_A_PUSH(0,((bcore_source*)(bcore_source_point_s_clone_source( &body->code->source_point )))));
    
    xoico_che_result* result = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
    
    BLM_TRY(xoico_che_s_parse(o,source, " {" ))
    sz_t indentation = 0;
    if( !body->go_inline ) indentation = xoico_che_s_assess_indentation(source );
    BLM_TRY(xoico_che_s_trans_block_inside(o,source, result ))
    BLM_TRY(xoico_che_s_parse(o,source, " }" ))
    
    xoico_che_result* result_block = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_block(o->level, xoico_che_s_stack_block_get_bottom_unit(o)->use_blm )));
    ((xoico_che_result_block_s*)(result_block))->is_root = true;
    //    $* result_block = :result_create_block( o.level, true ).scope();
    xoico_che_result_a_push_result_d(result_block,((xoico_che_result*)bcore_fork(result)) );
    
    st_s* buf = ((st_s*)BLM_LEVEL_T_PUSH(0,st_s,st_s_create()));
    BLM_TRY(xoico_che_result_a_to_sink(result_block,((bcore_sink*)(buf)) ))
    
    //remove trailing whitespaces
    for( sz_t i = buf->size - 1; i >= 0; i-- )
    {
        if( buf->data[ i ] != ' ' && buf->data[ i ] != '\t' && buf->data[ i ] != '\n' ) break;
        buf->data[ i ] = 0;
        buf->size = i;
    }
    
    if( o->insert_source_reference && !body->code->single_line )
    {
        bcore_sink_a_push_fa( sink,"// " );
        bcore_source_point_s_source_reference_to_sink( &(body->code->source_point),true, sink );
        bcore_sink_a_push_fa( sink,"\n" );
    }
    
    if( indentation > 0 ) xoico_che_s_remove_indentation(buf, indentation );
    
    if( o->verbose )
    {
        bcore_sink_a_push_fa( BCORE_STDOUT, "##############################\n" );
        bcore_sink_a_push_fa( BCORE_STDOUT, "#<st_s*>\n", buf );
    }
    
    bcore_sink_a_push_sc( sink,buf->sc );
    
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_che_s_translate( const xoico_che_s* o, const xoico_body_s* body, const xoico_signature_s* signature, bcore_sink* sink )
{
    // xoico_che.x:1955:1
    BLM_INIT_LEVEL(0);
    er_t er = xoico_che_s_translate_mutable(((xoico_che_s*)BLM_LEVEL_T_PUSH(0,xoico_che_s,xoico_che_s_clone(o))),body, signature, sink );
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
    // xoico_che_builtin.x:50:1
     {
    switch( tp_builtin )
    {
        case TYPEOF_cast : return  xoico_che_s_trans_builtin_cast(o,source, result_expr, typespec_expr, result_out, typespec_out );
        case TYPEOF_scope: return  xoico_che_s_trans_builtin_scope(o,source, result_expr, typespec_expr, result_out, typespec_out );
        case TYPEOF_fork:  return  xoico_che_s_trans_builtin_fork(o,source, result_expr, typespec_expr, result_out, typespec_out );
        case TYPEOF_try:   return  xoico_che_s_trans_builtin_try(o,source, result_expr, typespec_expr, result_out, typespec_out );
        default: return  bcore_source_a_parse_error_fa( source,"Internal error: Invalid builtin type '#<sc_t>'", ifnameof( tp_builtin ) );
    }
    } /* try */
}

er_t xoico_che_s_trans_builtin_cast( xoico_che_s* o, bcore_source* source, const xoico_che_result* result_expr, const xoico_typespec_s* typespec_expr, xoico_che_result* result_out, xoico_typespec_s* typespec_out )
{
    // xoico_che_builtin.x:75:1
    BLM_INIT_LEVEL(0); {
    if( result_expr ) // member call
    {
        BLM_TRY(xoico_che_s_parse(o,source, " ( " ))
        xoico_che_result_a_clear(result_out);
    }
    else // direct call
    {
        BLM_TRY(xoico_che_s_parse(o,source, "cast ( " ))
        xoico_che_result* result = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
        xoico_typespec_s* typespec = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
        BLM_TRY(xoico_che_s_trans_expression(o,source, result, typespec ))
        BLM_TRY(xoico_che_s_parse(o,source, " , " ))
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
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Cast-syntax: Deduce requested but expression is intractable." ))
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
    
    BLM_TRY(xoico_che_s_parse(o,source, " )" ))
    BLM_TRY(xoico_che_result_a_push_sc(result_out,"))" ))
    
    if( typespec_out ) xoico_typespec_s_copy(typespec_out,typespec_cast );
    
    if( typespec_cast->indirection > typespec_expr->indirection )
    {
        typespec_out->flag_addressable = false;
    }
    
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_che_s_trans_builtin_scope( xoico_che_s* o, bcore_source* source, const xoico_che_result* result_expr, const xoico_typespec_s* typespec_expr, xoico_che_result* result_out, xoico_typespec_s* typespec_out )
{
    // xoico_che_builtin.x:153:1
    BLM_INIT_LEVEL(0); {
    bl_t has_arg = false;
    
    if( result_expr ) // member call
    {
        BLM_TRY(xoico_che_s_parse(o,source, " ( " ))
        xoico_che_result_a_clear(result_out);
        has_arg = !bcore_source_a_parse_bl( source,"#=?')'" );
    }
    else // direct call
    {
        BLM_TRY(xoico_che_s_parse(o,source, "scope ( " ))
        xoico_che_result* result = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
        xoico_typespec_s* typespec = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
        BLM_TRY(xoico_che_s_trans_expression(o,source, result, typespec ))
        typespec_expr = typespec;
        result_expr = result;
        has_arg = bcore_source_a_parse_bl( source,"#?','" );
    }
    
    const xoico_typespec_s* typespec_scope = typespec_expr;
    
    BLM_TRY(xoico_che_result_a_push_sc(result_out,"((" ))
    
    sz_t level = 0;
    
    if( has_arg )
    {
        BLM_TRY(xoico_che_s_parse(o,source, " " ))
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
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"scope: identifier '#<sc_t>' does not represent a variable.", xoico_che_s_nameof(o,tp_identifier ) ))
        }
    }
    
    BLM_TRY(xoico_che_s_parse(o,source, " )" ))
    
    if( typespec_scope->type        == 0 ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Operator 'scope': Expression not tractable." ))
    if( typespec_scope->indirection != 1 ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Operator 'scope': Expression's indirection != 1." ))
    if( typespec_scope->flag_keep )        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Operator 'scope': Target is already scoped." ))
    
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
        typespec_out->flag_keep = true;
    }
    
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_che_s_trans_builtin_fork( xoico_che_s* o, bcore_source* source, const xoico_che_result* result_expr, const xoico_typespec_s* typespec_expr, xoico_che_result* result_out, xoico_typespec_s* typespec_out )
{
    // xoico_che_builtin.x:248:1
    BLM_INIT_LEVEL(0); {
    if( result_expr ) // member call
    {
        BLM_TRY(xoico_che_s_parse(o,source, " ( " ))
        xoico_che_result_a_clear(result_out);
    }
    else // direct call
    {
        BLM_TRY(xoico_che_s_parse(o,source, "fork ( " ))
        xoico_che_result* result = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
        xoico_typespec_s* typespec = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
        BLM_TRY(xoico_che_s_trans_expression(o,source, result, typespec ))
        typespec_expr = typespec;
        result_expr = result;
    }
    
    const xoico_typespec_s* typespec_fork = typespec_expr;
    
    BLM_TRY(xoico_che_result_a_push_sc(result_out,"((" ))
    
    BLM_TRY(xoico_che_s_parse(o,source, " )" ))
    
    if( typespec_fork->type        == 0 ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Operator 'fork': Expression not tractable." ))
    if( typespec_fork->indirection != 1 ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Operator 'fork': Expression's indirection != 1." ))
    
    BLM_TRY(xoico_che_s_push_typespec(o,typespec_fork, result_out ))
    BLM_TRY(xoico_che_result_a_push_sc(result_out,")bcore_fork(" ))
    xoico_che_result_a_push_result_c(result_out,result_expr );
    BLM_TRY(xoico_che_result_a_push_sc(result_out,"))" ))
    
    if( typespec_out ) xoico_typespec_s_copy(typespec_out,typespec_fork );
    
    BLM_RETURNV(er_t, 0)
    } /* try */
}

er_t xoico_che_s_trans_builtin_try( xoico_che_s* o, bcore_source* source, const xoico_che_result* result_expr, const xoico_typespec_s* typespec_expr, xoico_che_result* result_out, xoico_typespec_s* typespec_out )
{
    // xoico_che_builtin.x:297:1
    BLM_INIT_LEVEL(0); {
    if( o->typespec_ret.type != TYPEOF_er_t || o->typespec_ret.indirection != 0 )
    {
        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Operator 'try': This operator can only be used in functions returning 'er_t'." ))
    }
    
    if( typespec_out ) xoico_typespec_s_reset(typespec_out);
    
    if( result_expr ) // member call
    {
        BLM_TRY(xoico_che_s_parse(o,source, " ( " ))
        xoico_che_result_a_clear(result_out);
    }
    else // direct call
    {
        BLM_TRY(xoico_che_s_parse(o,source, "try " ))
    
        if( bcore_source_a_parse_bl( source,"#=?'{'" ) ) // try block
        {
            o->try_block_level++;
            BLM_TRY(xoico_che_s_trans_block(o,source, result_out, false ))
            o->try_block_level--;
            BLM_RETURNV(er_t, 0)
        }
    
        BLM_TRY(xoico_che_s_parse(o,source, "( " ))
        xoico_che_result* result = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
        xoico_typespec_s* typespec = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create()));
        BLM_TRY(xoico_che_s_trans_expression(o,source, result, typespec ))
        typespec_expr = typespec;
        result_expr = result;
    }
    
    const xoico_typespec_s* typespec_try = typespec_expr;
    
    BLM_TRY(xoico_che_s_parse(o,source, " ) ;" ))
    
    if( typespec_try->type != 0 )
    {
        if( typespec_try->type != TYPEOF_er_t ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Operator 'try': Expression must yield er_t." ))
        if( typespec_try->indirection != 0    ) BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Operator 'try': Expression's indirection != 0." ))
    }
    else
    {
        // return source.parse_error_fa( "Operator 'try': Expression not tractable." );
    }
    
    BLM_TRY(xoico_che_result_a_push_sc(result_out,"BLM_TRY(" ))
    xoico_che_result_a_push_result_c(result_out,result_expr );
    BLM_TRY(xoico_che_result_a_push_sc(result_out,")" ))
    
    BLM_RETURNV(er_t, 0)
    } /* try */
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
            return  true;
    
        default:
            return  false;
    }
}

er_t xoico_che_s_trans_control( xoico_che_s* o, tp_t tp_control, bcore_source* source, xoico_che_result* result )
{
    // xoico_che_control.x:45:1
     {
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
        default: return  bcore_source_a_parse_error_fa( source,"Internal error: Invalid control name '#<sc_t>'", ifnameof( tp_control ) );
    }
    } /* try */
}

er_t xoico_che_s_trans_control_for( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che_control.x:66:1
     {
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
    if( bcore_source_a_parse_bl( source,"#=?'{'" ) )
    {
        BLM_TRY(xoico_che_s_trans_block(o,source, result, false ))
    }
    else
    {
        BLM_TRY(xoico_che_s_trans_statement_as_block(o,source, result, false ))
    }
    xoico_che_s_dec_block(o);
    return  0;
    } /* try */
}

er_t xoico_che_s_trans_control_foreach( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che_control.x:99:1
    BLM_INIT_LEVEL(0); {
    xoico_che_s_inc_block(o);
    xoico_che_s_stack_block_get_top_unit(o)->break_ledge = true;
    BLM_TRY(xoico_che_s_parse(o,source, "foreach ( " ))
    
    xoico_typespec_s* typespec_var = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create() ));
    BLM_TRY(xoico_che_s_take_typespec(o,source, typespec_var, true ))
    
    tp_t tp_var_name = 0;
    
    if( bcore_source_a_parse_bl( source,"#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||[0]=='_')" ) )
    {
        tp_var_name = xoico_che_s_get_identifier(o,source, true );
    }
    else
    {
        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Variable name expected." ))
    }
    
    BLM_TRY(xoico_che_s_parse(o,source, " in " ))
    
    xoico_typespec_s* typespec_arr_expr = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create() ));
    xoico_che_result* result_arr_expr = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
    BLM_TRY(xoico_che_s_trans_expression(o,source, result_arr_expr, typespec_arr_expr ))
    
    if( !typespec_arr_expr->type )
    {
        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Array expression not tractable." ))
    }
    
    xoico_compiler_element_info_s* info = ((xoico_compiler_element_info_s*)BLM_LEVEL_T_PUSH(0,xoico_compiler_element_info_s,xoico_compiler_element_info_s_create() ));
    
    if( !xoico_compiler_s_get_type_array_element_info(o->compiler,typespec_arr_expr->type, info ) )
    {
        BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Expression does not evaluate to an array." ))
    }
    
    xoico_typespec_s* typespec_element = &info->type_info.typespec;
    
    if( typespec_var->type == TYPEOF_type_deduce ) typespec_var->type = typespec_element->type;
    
    BLM_TRY(xoico_che_s_parse(o,source, " )" ))
    
    xoico_typespec_s* typespec_arr = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_clone(typespec_arr_expr) ));
    typespec_arr->indirection = 1;
    typespec_arr->flag_const = true;
    
    xoico_typespec_s* typespec_idx = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create() ));
    typespec_idx->type = TYPEOF_sz_t;
    
    xoico_che_s_push_typedecl(o,typespec_var, tp_var_name );
    xoico_che_s_push_typedecl(o,typespec_arr, xoico_che_s_entypeof(o,"__a" ) );
    xoico_che_s_push_typedecl(o,typespec_idx, xoico_che_s_entypeof(o,"__i" ) );
    
    xoico_che_result* result_statement = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
    if( bcore_source_a_parse_bl( source,"#=?'{'" ) )
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
    } /* try */
}

er_t xoico_che_s_trans_control_if( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che_control.x:189:1
     {
    BLM_TRY(xoico_che_s_trans(o,source, "if", result ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    BLM_TRY(xoico_che_s_trans(o,source, "(", result ))
    BLM_TRY(xoico_che_s_trans_expression(o,source, result, NULL )) // def
    BLM_TRY(xoico_che_s_trans(o,source, ")", result ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    if( bcore_source_a_parse_bl( source,"#=?'{'" ) )
    {
        BLM_TRY(xoico_che_s_trans_block(o,source, result, false ))
    }
    else
    {
        BLM_TRY(xoico_che_s_trans_statement_as_block(o,source, result, false ))
    }
    return  0;
    } /* try */
}

er_t xoico_che_s_trans_control_while( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che_control.x:210:1
     {
    BLM_TRY(xoico_che_s_trans(o,source, "while", result ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    BLM_TRY(xoico_che_s_trans(o,source, "(", result ))
    BLM_TRY(xoico_che_s_trans_expression(o,source, result, NULL )) // def
    BLM_TRY(xoico_che_s_trans(o,source, ")", result ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    if( bcore_source_a_parse_bl( source,"#=?'{'" ) )
    {
        BLM_TRY(xoico_che_s_trans_block(o,source, result, true ))
    }
    else
    {
        BLM_TRY(xoico_che_s_trans_statement_as_block(o,source, result, true ))
    }
    return  0;
    } /* try */
}

er_t xoico_che_s_trans_control_do( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che_control.x:231:1
     {
    BLM_TRY(xoico_che_s_trans(o,source, "do", result ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    if( bcore_source_a_parse_bl( source,"#=?'{'" ) )
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
    } /* try */
}

er_t xoico_che_s_trans_control_else( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che_control.x:255:1
     {
    BLM_TRY(xoico_che_s_trans(o,source, "else", result ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    if( bcore_source_a_parse_bl( source,"#=?'{'" ) )
    {
        BLM_TRY(xoico_che_s_trans_block(o,source, result, false ))
    }
    else
    {
        BLM_TRY(xoico_che_s_trans_statement_as_block(o,source, result, false ))
    }
    return  0;
    } /* try */
}

er_t xoico_che_s_trans_control_switch( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che_control.x:272:1
     {
    BLM_TRY(xoico_che_s_trans(o,source, "switch", result ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    BLM_TRY(xoico_che_s_trans(o,source, "(", result ))
    BLM_TRY(xoico_che_s_trans_expression(o,source, result, NULL )) // def
    BLM_TRY(xoico_che_s_trans(o,source, ")", result ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    BLM_TRY(xoico_che_s_trans_block(o,source, result, true ))
    return  0;
    } /* try */
}

er_t xoico_che_s_trans_control_case( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che_control.x:286:1
     {
    BLM_TRY(xoico_che_s_trans(o,source, "case", result ))
    BLM_TRY(xoico_che_s_trans_expression(o,source, result, NULL ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    BLM_TRY(xoico_che_s_trans(o,source, ":", result ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    BLM_TRY(xoico_che_s_trans_statement_as_block(o,source, result, false ))
    return  0;
    } /* try */
}

er_t xoico_che_s_trans_control_default( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che_control.x:299:1
     {
    BLM_TRY(xoico_che_s_trans(o,source, "default", result ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    BLM_TRY(xoico_che_s_trans(o,source, ":", result ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result ))
    BLM_TRY(xoico_che_s_trans_statement_as_block(o,source, result, false ))
    return  0;
    } /* try */
}

er_t xoico_che_s_trans_control_break( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che_control.x:335:1
     {
    BLM_TRY(xoico_che_s_parse(o,source, "break ;" ))
    
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
    
    if( ledge_level == -1 ) return  bcore_source_a_parse_error_fa( source,"'break' has no ledge." );
    
    xoico_che_result_a_push_result_d(result,((xoico_che_result*)(xoico_che_result_break_s_create_setup(ledge_level ))) );
    
    return  0;
    } /* try */
}

er_t xoico_che_s_trans_control_return( xoico_che_s* o, bcore_source* source, xoico_che_result* result )
{
    // xoico_che_control.x:387:1
    BLM_INIT_LEVEL(0); {
    BLM_TRY(xoico_che_s_parse(o,source, "return" ))
    
    xoico_che_result* result_expr = ((xoico_che_result*)BLM_LEVEL_A_PUSH(0,xoico_che_result_create_arr()));
    
    xoico_typespec_s* typespec_expr = ((xoico_typespec_s*)BLM_LEVEL_T_PUSH(0,xoico_typespec_s,xoico_typespec_s_create() ));
    const xoico_typespec_s* typespec_ret =&( o->typespec_ret);
    
    BLM_TRY(xoico_che_s_trans_expression(o,source, result_expr, typespec_expr ))
    BLM_TRY(xoico_che_s_trans_whitespace(o,source, result_expr ))
    BLM_TRY(xoico_che_s_parse(o,source, ";" ))
    
    if( typespec_expr->type )
    {
        if( !xoico_che_s_returns_a_value(o) )
        {
            BLM_RETURNV(er_t, bcore_source_a_parse_error_fa( source,"Function does not return a value." ))
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
    
    xoico_che_result_a_push_result_d(result,((xoico_che_result*)bcore_fork(((xoico_che_result*)(result_return)))) );
    
    BLM_RETURNV(er_t, 0)
    } /* try */
}

BCORE_DEFINE_OBJECT_INST_P( xoico_che_result_break_s )
"aware xoico_che_result"
"{"
    "sz_t ledge_level;"
    "hidden xoico_che_result_block_s* parent;"
    "func ^:set_parent_block;"
    "func ^:to_sink;"
"}";

er_t xoico_che_result_break_s_to_sink( const xoico_che_result_break_s* o, bcore_sink* sink )
{
    // xoico_che_control.x:318:5
    
    if( !o->parent ) ERR_fa( "Parent missing." );
    if( xoico_che_result_block_s_is_using_blm_until_level(o->parent,o->ledge_level ) )
    {
        bcore_sink_a_push_fa( sink,"BLM_BREAK_LEVEL(#<sz_t>);", o->ledge_level );
    }
    else
    {
        bcore_sink_a_push_fa( sink,"break;" );
    }
    return  0;
}

BCORE_DEFINE_OBJECT_INST_P( xoico_che_result_return_s )
"aware xoico_che_result"
"{"
    "hidden xoico_che_result_block_s* parent;"
    "hidden aware xoico_che_result -> result_blm;"
    "hidden aware xoico_che_result -> result_direct;"
    "func ^:set_parent_block;"
    "func ^:to_sink;"
"}";

er_t xoico_che_result_return_s_to_sink( const xoico_che_result_return_s* o, bcore_sink* sink )
{
    // xoico_che_control.x:370:5
    
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
    "func ^:clear;"
    "func ^:push_char;"
    "func ^:push_sc;"
    "func ^:push_st;"
    "func ^:to_sink;"
    "func ^:create_st;"
"}";

BCORE_DEFINE_OBJECT_INST_P( xoico_che_result_adl_s )
"aware bcore_array"
"{"
    "aware xoico_che_result-> [];"
"}";

BCORE_DEFINE_OBJECT_INST_P( xoico_che_result_arr_s )
"aware xoico_che_result"
"{"
    "xoico_che_result_adl_s adl;"
    "func ^:clear;"
    "func ^:push_char;"
    "func ^:push_sc;"
    "func ^:push_st;"
    "func ^:push_result_d;"
    "func ^:push_result_c;"
    "func ^:to_sink;"
    "func ^:set_parent_block;"
"}";

xoico_che_result* xoico_che_result_arr_s_last( xoico_che_result_arr_s* o )
{
    // xoico_che.h:86:9
    
    return  ( o->adl.size == 0 ) ? xoico_che_result_adl_s_push_d( &(o->adl),((xoico_che_result*)(xoico_che_result_plain_s_create())) ) : o->adl.data[ o->adl.size - 1 ];
}

xoico_che_result* xoico_che_result_arr_s_last_plain( xoico_che_result_arr_s* o )
{
    // xoico_che.h:91:9
    
    return  ( xoico_che_result_arr_s_last(o)->_ != TYPEOF_xoico_che_result_plain_s ) ? xoico_che_result_adl_s_push_d( &(o->adl),((xoico_che_result*)(xoico_che_result_plain_s_create())) ) : o->adl.data[ o->adl.size - 1 ];
}

er_t xoico_che_result_arr_s_to_sink( const xoico_che_result_arr_s* o, bcore_sink* sink )
{
    // xoico_che.h:102:9
    
    {const xoico_che_result_adl_s* __a=&(o->adl );if(__a)for(sz_t __i=0; __i<__a->size; __i++){xoico_che_result* e=__a->data[__i]; xoico_che_result_a_to_sink(e,sink );}}
    return  0;
}

void xoico_che_result_arr_s_set_parent_block( xoico_che_result_arr_s* o, xoico_che_result_block_s* parent )
{
    // xoico_che.h:108:9
    
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
    "func ^:clear;"
    "func ^:push_char;"
    "func ^:push_sc;"
    "func ^:push_st;"
    "func ^:push_result_d;"
    "func ^:push_result_c;"
    "func ^:to_sink;"
    "func ^:set_parent_block;"
"}";

xoico_che_result* xoico_che_result_block_s_push_result_d( xoico_che_result_block_s* o, xoico_che_result* result )
{
    // xoico_che.h:130:9
    
    xoico_che_result* result_pushed = xoico_che_result_arr_s_push_result_d(&(o->arr),result );
    xoico_che_result_a_set_parent_block(result_pushed,o );
    return  result_pushed;
}

xoico_che_result* xoico_che_result_block_s_push_result_c( xoico_che_result_block_s* o, const xoico_che_result* result )
{
    // xoico_che.h:137:9
    
    xoico_che_result* result_pushed = xoico_che_result_arr_s_push_result_c(&(o->arr),result );
    xoico_che_result_a_set_parent_block(result_pushed,o );
    return  result_pushed;
}

bl_t xoico_che_result_block_s_is_using_blm_until_level( const xoico_che_result_block_s* o, sz_t level )
{
    // xoico_che.h:147:9
    
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
    "func ^:to_sink;"
"}";

BCORE_DEFINE_OBJECT_INST_P( xoico_che_result_blm_down_s )
"aware xoico_che_result"
"{"
    "func ^:to_sink;"
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
    // xoico_che.h:48:5
    
    st_s* st = st_s_create();
    xoico_che_result_a_to_sink(o,((bcore_sink*)(st)) );
    return  st;
}
xoico_che_result* xoico_che_result_create_block( sz_t level, bl_t is_using_blm )
{
    // xoico_che.h:159:5
    
    xoico_che_result_block_s* o = xoico_che_result_block_s_create();
    o->level = level;
    o->is_using_blm = is_using_blm;
    return  ((xoico_che_result*)(o));
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
"aware bcore_array"
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
    // xoico_che.h:218:9
    
    bcore_hmap_tpuz_s_clear(&(o->hmap_name));
    for( sz_t i = 0; i < o->adl.size; i++ ) bcore_hmap_tpuz_s_set(&(o->hmap_name),o->adl.data[i]->name, i );
}

xoico_che_stack_var_s* xoico_che_stack_var_s_push_unit( xoico_che_stack_var_s* o, const xoico_che_stack_var_unit_s* unit )
{
    // xoico_che.h:224:9
    
    xoico_che_stack_var_unit_adl_s_push_c( &(o->adl),unit );
    bcore_hmap_tpuz_s_set(&(o->hmap_name),unit->name, o->adl.size - 1 );
    return  o;
}

xoico_che_stack_var_s* xoico_che_stack_var_s_pop_level( xoico_che_stack_var_s* o, sz_t level )
{
    // xoico_che.h:231:9
    
    sz_t size = o->adl.size;
    while( size > 0 && o->adl.data[ size - 1 ]->level >= level ) size--;
    xoico_che_stack_var_unit_adl_s_set_size( &(o->adl),size );
    xoico_che_stack_var_s_rehash_names(o);
    return  o;
}

const xoico_typespec_s* xoico_che_stack_var_s_get_typespec( const xoico_che_stack_var_s* o, tp_t name )
{
    // xoico_che.h:240:9
    
    uz_t* p_idx = bcore_hmap_tpuz_s_get(&(o->hmap_name),name );
    if( !p_idx ) return  NULL;
    return &( o->adl.data[ *p_idx ]->typespec);
}

const sz_t xoico_che_stack_var_s_get_level( const xoico_che_stack_var_s* o, tp_t name )
{
    // xoico_che.h:248:9
    
    uz_t* p_idx = bcore_hmap_tpuz_s_get(&(o->hmap_name),name );
    if( !p_idx ) return  -1;
    return  o->adl.data[ *p_idx ]->level;
}

void xoico_che_stack_var_s_clear( xoico_che_stack_var_s* o )
{
    // xoico_che.h:255:9
    
    xoico_che_stack_var_unit_adl_s_clear( &(o->adl));
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
"aware bcore_array"
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
    // xoico_che.h:289:9
    
    xoico_che_stack_block_unit_adl_s_set_size( &(o->adl),sz_max( o->adl.size - 1, 0 ) );
    return  o;
}

XOILA_DEFINE_SPECT( xoico_che, xoico_che_stack_block )
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
            BCORE_REGISTER_FFUNC( xoico_get_global_name_sc, xoico_body_s_get_global_name_sc );
            BCORE_REGISTER_FFUNC( xoico_get_hash, xoico_body_s_get_hash );
            BCORE_REGISTER_OBJECT( xoico_body_s );
            XOILA_REGISTER_SPECT( xoico_body );

            // --------------------------------------------------------------------
            // source: xoico_feature.h

            // group: xoico_feature
            BCORE_REGISTER_FFUNC( xoico_get_global_name_sc, xoico_feature_s_get_global_name_sc );
            BCORE_REGISTER_FFUNC( xoico_get_hash, xoico_feature_s_get_hash );
            BCORE_REGISTER_FFUNC( xoico_parse, xoico_feature_s_parse );
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
            BCORE_REGISTER_FFUNC( xoico_get_hash, xoico_group_s_get_hash );
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
            BCORE_REGISTER_FFUNC( xoico_get_hash, xoico_source_s_get_hash );
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
// XOILA_OUT_SIGNATURE 0x0A3B499E72DBDED5ull
