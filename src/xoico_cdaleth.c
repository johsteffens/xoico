/** Author and Copyright 2020 Johannes Bernhard Steffens
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file ecdalethpt in compliance with the License.
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

#include "xoico_cdaleth.h"
#include "xoico_caleph.h"
#include "xoico_group.h"
#include "xoico_stamp.h"
#include "xoico_body.h"
#include "xoico_compiler.h"

/**********************************************************************************************************************/

/// Prototypes

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cdaleth_s_trans_statement(  xoico_cdaleth_s* o, bcore_source* source, st_s* buf );
er_t xoico_cdaleth_s_trans_block(      xoico_cdaleth_s* o, bcore_source* source, st_s* buf, bl_t is_break_ledge );
er_t xoico_cdaleth_s_trans_statement_as_block( xoico_cdaleth_s* o, bcore_source* source, st_s* buf_out, bl_t is_break_ledge );
er_t xoico_cdaleth_s_trans_expression( xoico_cdaleth_s* o, bcore_source* source, st_s* buf, xoico_typespec_s* out_typespec /* optional */ );
er_t xoico_cdaleth_s_trans_block_inside_verbatim_c( xoico_cdaleth_s* o, bcore_source* source, st_s* buf );

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cdaleth_s_parse_err_fv( const xoico_cdaleth_s* o, bcore_source* source, sc_t format, va_list args )
{
    return bcore_source_a_parse_error_fv( source, format, args );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cdaleth_s_parse_err_fa( const xoico_cdaleth_s* o, bcore_source* source, sc_t format, ... )
{
    va_list args;
    va_start( args, format );
    er_t er = xoico_cdaleth_s_parse_err_fv( o, source, format, args );
    va_end( args );
    return er;
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cdaleth_s_parse_fv( const xoico_cdaleth_s* o, bcore_source* source, sc_t format, va_list args )
{
    return bcore_source_a_parse_em_fv( source, format, args );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_cdaleth_s_parse_fa( const xoico_cdaleth_s* o, bcore_source* source, sc_t format, ... )
{
    va_list args;
    va_start( args, format );
    er_t er = xoico_cdaleth_s_parse_fv( o, source, format, args );
    va_end( args );
    return er;
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

