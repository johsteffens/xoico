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

#include "xoico_compiler.h"
#include "xoico_group.h"
#include "xoico_target.h"
#include "xoico_source.h"
#include "xoico_stamp.h"
#include "xoico_funcs.h"
#include "xoico_feature.h"

/**********************************************************************************************************************/

er_t xoico_compiler_s_parse_err_fv( const xoico_compiler_s* o, bcore_source* source, sc_t format, va_list args )
{
    return bcore_source_a_parse_error_fv( source, format, args );
}

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_compiler_s_parse_err_fa( const xoico_compiler_s* o, bcore_source* source, sc_t format, ... )
{
    va_list args;
    va_start( args, format );
    er_t er = xoico_compiler_s_parse_err_fv( o, source, format, args );
    va_end( args );
    return er;
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

