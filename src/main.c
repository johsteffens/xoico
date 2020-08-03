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

#include "bcore_std.h"
#include "xoite_builder.h"

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

void help( bcore_sink* sink )
{
    bcore_sink_a_push_fa( sink, "XOI Builder: (C) J.B.Steffens\n" );
    bcore_sink_a_push_fa( sink, "Usage: xoite <xoite-config-file> [<xoite-config-file> ...]\n" );
}

//----------------------------------------------------------------------------------------------------------------------

int main( int argc, char** argv )
{
    BETH_PLANT_USE( bcore );

    BLM_INIT();
    er_t er = 0;

    // plant
    if( argc > 1 )
    {
        if( sc_t_equal( argv[ 1 ], "--help" ) )
        {
            help( BCORE_STDOUT );
        }
        else
        {
            clock_t time = clock();

            for( sz_t i = 1; i < argc; i++ )
            {
                if( ( er = xoite_build_from_file( argv[ i ] ) ) ) break;
            }

            if( !er && xoite_update_required() )
            {
                er = xoite_update( NULL );
            }

            if( !er )
            {
                f3_t time_var = clock() - time;
                time_var /= CLOCKS_PER_SEC;
                bcore_sink_a_pushf( BCORE_STDOUT, "Finished after %.3f seconds.\n", time_var );
            }
        }
    }
    else
    {
        er = 1;
        st_s* st = BLM_CREATE( st_s );
        help( ( bcore_sink* )st );
        bcore_error_push_sc( er, st->sc );
    }

    if( er ) bcore_error_pop_all_to_stderr();

    BLM_DOWN();

    BETH_PLANT_CLOSEV( false );

    return ( er > 0 ) ? 1 : 0;
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

