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

#ifndef XOICO_H
#define XOICO_H

/**********************************************************************************************************************/

/** Main Interface */

/**********************************************************************************************************************/

#include "bcore_std.h"
#include "xoico_xoila_out.h"

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( xoico, bcore_inst )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

feature 'ap' er_t parse                     ( mutable, bcore_source* source );
feature 'ap' tp_t get_hash                  ( const   );
feature 'ap' sc_t get_global_name_sc        ( const   );
feature 'ap' er_t finalize                  ( mutable )                              = { return 0; };
feature 'ap' er_t expand_forward            ( const, sz_t indent, bcore_sink* sink ) = { return 0; };
feature 'ap' er_t expand_indef_typedef      ( const, sz_t indent, bcore_sink* sink ) = { return 0; };
feature 'ap' er_t expand_spect_declaration  ( const, sz_t indent, bcore_sink* sink ) = { return 0; };
feature 'ap' er_t expand_spect_definition   ( const, sz_t indent, bcore_sink* sink ) = { return 0; };
feature 'ap' er_t expand_declaration        ( const, sz_t indent, bcore_sink* sink ) = { return 0; };
feature 'ap' er_t expand_indef_declaration  ( const, sz_t indent, bcore_sink* sink ) = { return 0; };
feature 'ap' er_t expand_definition         ( const, sz_t indent, bcore_sink* sink ) = { return 0; };
feature 'ap' er_t expand_init1              ( const, sz_t indent, bcore_sink* sink ) = { return 0; };

name mutable;
name const;

forward :name_s;
forward :forward_s;
forward :arg_s;
forward :args_s;
forward :signature_s;
forward :body_s;
forward :feature_s;

forward :func_s;
forward :funcs_s;
forward :stamp_s;

forward :group_s;
forward :nested_group_s;

forward :source_s;
forward :target_s;
forward :compiler_s;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//----------------------------------------------------------------------------------------------------------------------
// functions

/// opens an include file from an include directive in parent
er_t xoico_embed_file_open( bcore_source* parent, sc_t file_name, bcore_source** include_source );

//----------------------------------------------------------------------------------------------------------------------
// macros

#define XOICO_BLM_SOURCE_PARSE_ERR_FA( source, ... ) \
{ \
    BLM_RETURNV( er_t, bcore_source_a_parse_err_to_em_fa( source, TYPEOF_parse_error, __VA_ARGS__ ) ); \
}

#define XOICO_BLM_SOURCE_PARSE_FA( source, ... ) \
{ \
    er_t er = bcore_source_a_parse_em_fa( source, __VA_ARGS__ ); \
    if( er ) BLM_RETURNV( er_t, er ); \
}

#define XOICO_BLM_SOURCE_POINT_PARSE_ERR_FA( source_point, ... ) \
{ \
    BLM_RETURNV( er_t, bcore_source_point_s_parse_err_to_em_fa( source_point, TYPEOF_parse_error, __VA_ARGS__ ) ); \
}

/**********************************************************************************************************************/

#endif // XOICO_H
