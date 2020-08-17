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

#include "xoico.h"

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

er_t xoico_embed_file_open( bcore_source* parent, sc_t file_name, bcore_source** include_source )
{
    BLM_INIT();
    st_s* folder = BLM_A_PUSH( bcore_file_folder_path( bcore_source_a_get_file( parent ) ) );
    if( folder->size == 0 ) st_s_push_char( folder, '.' );

    st_s* path = BLM_CREATE( st_s );
    if( file_name[ 0 ] == '/' )
    {
        st_s_copy_sc( path, file_name );
    }
    else
    {
        st_s_copy_fa( path, "#<sc_t>/#<sc_t>", folder->sc, file_name );
    }

    if( !bcore_file_exists( path->sc ) )
    {
        XOICO_BLM_SOURCE_PARSE_ERR_FA( parent, "Xoico: File '#<sc_t>' not found.", path->sc );
    }

    *include_source = bcore_file_open_source( path->sc );

    BLM_RETURNV( er_t, 0 );
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/



