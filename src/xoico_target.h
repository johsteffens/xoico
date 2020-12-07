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

#ifndef XOICO_TARGET_H
#define XOICO_TARGET_H

/**********************************************************************************************************************/

#include "xoico.h"
#include "xoico_source.h"

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( xoico_target, xoico )
#ifdef XOILA_SECTION

//----------------------------------------------------------------------------------------------------------------------

signature er_t parse_from_path( mutable, sc_t source_path );
signature bl_t to_be_modified( const );
signature er_t expand_phase1( mutable, bl_t* p_modified );
signature er_t expand_phase2( mutable, bl_t* p_modified );
signature bl_t is_cyclic( mutable ); // mutable because flag is used for cyclic test
signature er_t set_dependencies( mutable, const bcore_arr_sz_s* dependencies );

stamp :s = aware :
{
    st_s name; // target name (e.g. "bcore")
    st_s include_path; // (local) path used in generated '#include' directives
    st_s path; // full path excluding extension *.h or *.c
    xoico_source_s => [];

    st_s signal_handler_name;    // name of governing signal handler
    bcore_arr_sz_s dependencies; // index array to dependent targets
    bl_t flag; // general purpose flag
    bl_t modified;    // target is to be modified
    bl_t readonly;    // target is readonly (affects writing in phase2)
    st_s => target_h; // target header file
    st_s => target_c; // target c file

    /// Optional cengine that is to be used in all bodies of this target
    aware xoico_cengine -> cengine;

    hidden aware xoico_compiler_s* compiler;

    func :.parse_from_path;
    func :.to_be_modified;

    func xoico.finalize =
    {
        foreach( $* e in o ) e.finalize( o ).try();
        return 0;
    };

    func xoico.expand_setup =
    {
        foreach( $* e in o ) e.expand_setup( o ).try();
        return 0;
    };

    func :.expand_phase1;
    func :.expand_phase2;
    func :.is_cyclic;
    func :.set_dependencies;

    func (void push_d( mutable, xoico_source_s* source )) =
    {
        o.cast( bcore_array* ).push( sr_asd( source ) );
    };

    func xoico_group.explicit_embeddings_push =
    {
        foreach( $* source in o ) source.explicit_embeddings_push( arr );
    };

    func xoico_host.compiler = { return o.compiler; };
    func xoico_host.cengine = { return o.cengine; };
};

//----------------------------------------------------------------------------------------------------------------------

embed "xoico_target.x";

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // XOICO_TARGET_H
