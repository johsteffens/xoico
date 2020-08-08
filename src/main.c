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
#include "xoico_builder.h"

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

BETH_SIGNAL_DEFINE( xoico )

//----------------------------------------------------------------------------------------------------------------------

void help( bcore_sink* sink )
{
    bcore_sink_a_push_fa
    (
        sink,
        "Xoila Compiler: (C) J.B.Steffens\n"
        "Usage: [options] xoico <xoico-config-file> [<xoico-config-file> ...]\n"
        "\n"
        "Options:\n"
        "-d : Dry run. Target files are not modified.\n"
        "-e : Always expand: Expands target files even if their hash has not changed.\n"
        "-f : Force overwrite target files. Use with care.\n"
    );
}

//----------------------------------------------------------------------------------------------------------------------

int main( int argc, char** argv )
{
    BETH_USE( xoico );

    BLM_INIT();

    xoico_builder_main_s* builder_main = BLM_CREATE( xoico_builder_main_s );
    er_t er = 0;

    sz_t arg_idx = 1;

    if( argc > 1 )
    {
        if( sc_t_equal( argv[ arg_idx ], "--help" ) )
        {
            help( BCORE_STDOUT );
        }
        else
        {
            while( argv[ arg_idx ][ 0 ] == '-' )
            {
                if( sc_t_equal( argv[ arg_idx ], "-d" ) )
                {
                    xoico_builder_main_s_set_dry_run( builder_main, true );
                }
                else if( sc_t_equal( argv[ arg_idx ], "-e" ) )
                {
                    xoico_builder_main_s_set_always_expand( builder_main, true );
                }
                else if( sc_t_equal( argv[ arg_idx ], "-f" ) )
                {
                    xoico_builder_main_s_set_overwrite_unsigned_target_files( builder_main, true );
                }
                else
                {
                    ERR_fa( "Invalid option: #<sc_t>\n", argv[ arg_idx ] );
                }
                arg_idx++;
            }

            if( xoico_builder_main_s_get_dry_run( builder_main ) )
            {
                bcore_sink_a_pushf( BCORE_STDOUT, "Dry run ...\n" );
            }

            if( xoico_builder_main_s_get_always_expand( builder_main ) )
            {
                bcore_sink_a_pushf( BCORE_STDOUT, "Expanding all ...\n" );
            }

            if( arg_idx >= argc ) help( BCORE_STDOUT );
            clock_t time = clock();

            for( sz_t i = arg_idx; i < argc; i++ )
            {
                if( ( er = xoico_builder_main_s_build_from_file( builder_main, argv[ i ] ) ) ) break;
            }

            if( !er && xoico_builder_main_s_update_required( builder_main ) )
            {
                er = xoico_builder_main_s_update( builder_main );
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

    BETH_CLOSEV( false );

    return ( er > 0 ) ? 1 : 0;
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

