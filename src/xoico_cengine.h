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

#ifndef XOICO_CENGINE_H
#define XOICO_CENGINE_H

/**********************************************************************************************************************/

/** C-Engine Interface */

/**********************************************************************************************************************/

#include "bcore_std.h"
#include "xoico.h"
#include "xoico_signature.h"
#include "xoico_compiler.h"
#include "xoico.xo.h"

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( xoico_cengine, xoico )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

feature 'a' er_t translate( c @* o, c xoico_host* host, c xoico_body_s* body, c xoico_signature_s* signature, m bcore_sink* sink );
feature 'a' tp_t get_hash ( c @* o ) = { return bcore_hash_a_get_tp( (bcore_hash*)o ); };
feature 'a' bl_t is_reserved( c @* o, tp_t tp_identifier ) = { return false; };

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//----------------------------------------------------------------------------------------------------------------------
// functions

/**********************************************************************************************************************/

#endif // XOICO_H
