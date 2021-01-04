/** Author and Copyright 2020 Johannes Bernhard Steffens
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

func (:s) :.parse = (try)
{
    o.reset();
    m $* compiler = host.compiler();

    if( source.parse_bl( "#?'...' " ) )
    {
        o.flag_variadic = true;
        return 0;
    }

    tp_t access_class = 0;

    if( source.parse_bl( " #?w'const'" ) ) source.parse_error_fa( "Abbreviate 'const' to 'c'." );

    if(      source.parse_bl( " #?w'c'" )                                           ) access_class = TYPEOF_const;
    else if( source.parse_bl( " #?w'm'" ) || source.parse_bl( " #?w'mutable'"     ) ) access_class = TYPEOF_mutable;
    else if( source.parse_bl( " #?w'd'" ) || source.parse_bl( " #?w'discardable'" ) ) access_class = TYPEOF_discardable;

    if( source.parse_bl( " #?w'unaware'"  ) ) o.flag_unaware = true;
    if( source.parse_bl( " #?w'scope'"    ) ) o.flag_scope = true;

    while( !source.eos() )
    {
        if     ( source.parse_bl( " #?w'static'"   ) ) o->flag_static = true;
        else if( source.parse_bl( " #?w'volatile'" ) ) o->flag_volatile = true;
        else break;
    }

    source.parse_em_fa( " " );

    if( source.parse_bl( "#?'(' " ) )
    {
        m st_s* s = st_s!^^;
        source.parse_em_fa( "#name ", s );
        if( s.size == 0 ) source.parse_error_fa( "Transient class: Identifier expected." );
        o.transient_class = compiler.entypeof( s.sc );
        source.parse_em_fa( " ) " );
    }

    if( source.parse_bl( "#=?':'" ) )
    {
        host.parse_name_tp( source, o.type.1 );
        source.parse_em_fa( " " );
    }
    else if( source.parse_bl( "#?'@' " ) )
    {
        o->type = TYPEOF_type_object;
    }
    else if( source.parse_bl( "#?'$' " ) )
    {
        o->type = TYPEOF_type_deduce;
    }
    else
    {
        m st_s* s = st_s!^^;
        source.parse_em_fa( "#name ", s );
        if( s.size == 0 ) source.parse_error_fa( "Argument: Type expected." );
        o->type = xoico_compiler_s_entypeof( compiler, s->sc );
    }

    if( source.parse_bl( "#?'.' " ) )
    {
        if( !source.parse_bl( "#?([0]>='0'&&[0]<='9') " ) ) source.parse_error_fa( "Argument: Indirection literal expected." );
        sz_t indirection = 0;
        source.parse_em_fa( "#<sz_t*> ", indirection.1 );
        o.indirection = indirection;
    }
    else
    {
        while( source.parse_bl( "#?'*' " ) ) o.indirection++;
    }

    if( source.parse_bl( " #?'restrict' " ) ) o.flag_restrict = true;

    switch( access_class )
    {
        case TYPEOF_const:
        {
            o->flag_const = true;
        }
        break;

        case TYPEOF_mutable:
        {
            o->flag_const = false;
        }
        break;

        case TYPEOF_discardable:
        {
            o->flag_const = false;
            o->flag_discardable = true;
        }
        break;

        default:
        {
            if( o.indirection > 0 ) source.parse_error_fa( "Access-class missing: (c|const) | (m|mutable) | (d|discardable)" );
        }
    }

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) xoico.get_hash =
{
    tp_t hash = bcore_tp_fold_tp( bcore_tp_init(), o._ );
    hash = bcore_tp_fold_bl( hash, o.flag_const );
    hash = bcore_tp_fold_bl( hash, o.flag_static );
    hash = bcore_tp_fold_bl( hash, o.flag_volatile );
    hash = bcore_tp_fold_bl( hash, o.flag_restrict );
    hash = bcore_tp_fold_bl( hash, o.flag_scope );
    hash = bcore_tp_fold_tp( hash, o.type );
    hash = bcore_tp_fold_u3( hash, o.indirection );
    return hash;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) :.expand = (try)
{
    if( o.flag_variadic )
    {
        sink.push_fa( "..." );
        return 0;
    }

    m $* compiler = host.compiler();

    tp_t type = o.type;

    if( type == TYPEOF_type_object )
    {
        //if( !sc_obj_type ) ERR_fa( "Cannot resolve 'type_object' at this point." );
        type = host.obj_type(); //compiler.entypeof( sc_obj_type );
    }
    else if( type == TYPEOF_type_deduce )
    {
        ERR_fa( "Cannot resolve 'type_deduce' at this point." );
    }

    m st_s* st_type = st_s_create_sc( compiler.nameof( type ) ).scope();

    sc_t sc_type = st_type.sc;
    if( o.flag_static   ) sink.push_fa( "static " );
    if( o.flag_const    ) sink.push_fa( "const " );
    if( o.flag_volatile ) sink.push_fa( "volatile " );
    sink.push_fa( "#<sc_t>", sc_type );

    for( sz_t i = 0; i < o.indirection; i++ ) sink.push_fa( "*" );
    if( o.flag_restrict ) sink.push_fa( " restrict " );

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) :.expand_x = (try)
{
    if( o.flag_variadic )
    {
        sink.push_fa( "..." );
        return 0;
    }

    m $* compiler = host.compiler();

    tp_t type = o.type;

    if( type == TYPEOF_type_object )
    {
        //if( !sc_obj_type ) ERR_fa( "Cannot resolve 'type_object' at this point." );
        type = host.obj_type(); //compiler.entypeof( sc_obj_type );
    }
    else if( type == TYPEOF_type_deduce )
    {
        ERR_fa( "Cannot resolve 'type_deduce' at this point." );
    }

    m st_s* st_type = st_s_create_sc( compiler.nameof( type ) ).scope();

    if( o.indirection > 0 )
    {
        if( o.flag_const )
        {
            sink.push_fa( "c " );
        }
        else if( o.flag_discardable )
        {
            sink.push_fa( "d " );
        }
        else
        {
            sink.push_fa( "m " );
        }
    }

    if( o.flag_static   ) sink.push_fa( "static " );
    if( o.flag_volatile ) sink.push_fa( "volatile " );
    sc_t sc_type = st_type.sc;
    sink.push_fa( "#<sc_t>", sc_type );

    if( o.indirection > 0 ) sink.push_fa( ".#<sz_t>", o.indirection );
    if( o.flag_restrict ) sink.push_fa( " restrict " );

    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (bl_t is_numeric( tp_t type )) =
{
    switch( type )
    {
        case TYPEOF_u0_t: return true;
        case TYPEOF_u1_t: return true;
        case TYPEOF_u2_t: return true;
        case TYPEOF_u3_t: return true;
        case TYPEOF_s0_t: return true;
        case TYPEOF_s1_t: return true;
        case TYPEOF_s2_t: return true;
        case TYPEOF_s3_t: return true;
        case TYPEOF_f2_t: return true;
        case TYPEOF_f3_t: return true;
        case TYPEOF_sz_t: return true;
        case TYPEOF_uz_t: return true;
        case TYPEOF_tp_t: return true;
        case TYPEOF_er_t: return true;
        case TYPEOF_bl_t: return true;
        case TYPEOF_char: return true;
        default: break;
    }
    return false;
};

//----------------------------------------------------------------------------------------------------------------------

func (:s) :.converts_to =
{
    if( o.type == b.type )
    {
        if( o.indirection == b.indirection )
        {
            if( o.flag_const )
            {
                return b.flag_const;
            }
            else
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        if( o.indirection == 0 && b.indirection == 0 )
        {
            if( xoico_typespec_is_numeric( o.type ) && xoico_typespec_is_numeric( b.type ) )
            {
                return true;
            }
            else if( b.type == TYPEOF_vd_t && b.type == TYPEOF_vc_t )
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else if( b.type == TYPEOF_vc_t && b.indirection == 0 )
        {
            if( o.indirection == 1 )
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else if( b.type == TYPEOF_vd_t && b.indirection == 0 )
        {
            if( o.indirection == 1 && !o.flag_const )
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else if( b.type == TYPEOF_bl_t && b.indirection == 0 )
        {
            if( o.indirection > 0 )
            {
                return true;
            }
            else if( o.type == TYPEOF_vd_t || o.type == TYPEOF_vc_t || o.type == TYPEOF_sc_t || o.type == TYPEOF_sd_t )
            {
                return ( o.indirection == 0 );
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
};

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

