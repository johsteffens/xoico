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
feature 'ap' tp_t get_global_name_tp        ( const   )                              = { return btypeof( :a_get_global_name_sc( o ) ); };
feature 'ap' er_t finalize                  ( mutable )                              = { return 0; };  // final stage in the compilation phase
feature 'ap' er_t expand_setup              ( mutable )                              = { return 0; };  // first stage in the expansion phase
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
name void;

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
forward :cengine;

//----------------------------------------------------------------------------------------------------------------------
// functions

func (er_t parse_f( bcore_source* source, sc_t format )) =
{
    return bcore_source_a_parse_em_fa( source, format );
};

//----------------------------------------------------------------------------------------------------------------------

/// opens an include file from an include directive in parent
func (er_t embed_file_open( bcore_source* parent, sc_t file_name, bcore_source** include_source )) =
{ try {
    st_s* folder = bcore_file_folder_path( parent.get_file() ).scope();
    if( folder.size == 0 ) folder.push_char( '.' );

    st_s* path = st_s!.scope();
    if( file_name[ 0 ] == '/' )
    {
        path.copy_sc( file_name );
    }
    else
    {
        path.copy_fa( "#<sc_t>/#<sc_t>", folder.sc, file_name );
    }

    if( !bcore_file_exists( path.sc ) )
    {
        return parent.parse_error_fa( "Xoico: File '#<sc_t>' not found.", path->sc );
    }

    include_source.1 = bcore_file_open_source( path.sc );
    return 0;
} /* try */ };

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//----------------------------------------------------------------------------------------------------------------------
// macros

/**********************************************************************************************************************/

#endif // XOICO_H
