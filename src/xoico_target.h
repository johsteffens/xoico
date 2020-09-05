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
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// extended flags (shared with external components)
group :xflags  = :
{
    /// xflags can be NULL
    signature void update( mutable, const :s* xflags );

    stamp : = aware :
    {
        bl_t => apply_cengine; // default setting for cengine usage in body-expansion

        func : :update =
        {
            if( !xflags ) return;
            if( !o->apply_cengine )
            {
                o->apply_cengine = bcore_inst_t_clone( TYPEOF_bl_t, ( bcore_inst* )xflags->apply_cengine );
            }
        };
    };
};

signature er_t parse( mutable, sc_t source_path );
signature bl_t to_be_modified( const );
signature er_t expand_phase1( mutable, bl_t* p_modified );
signature er_t expand_phase2( mutable, bl_t* p_modified );
signature bl_t is_cyclic( mutable ); // mutable because flag is used for cyclic test
signature void update_xflags( mutable, const :xflags_s* xflags );

stamp : = aware :
{
    :xflags_s xflags;
    st_s name; // target name (e.g. "bcore")
    st_s path; // path excluding extension
    xoico_source_s => [];

    st_s signal_handler_name;    // name of governing signal handler
    bcore_arr_sz_s dependencies; // index array to dependent targets
    bl_t flag; // general purpose flag
    bl_t modified;    // target is to be modified
    bl_t readonly;    // target is readonly (affects writing in phase2)
    st_s => target_h; // target header file
    st_s => target_c; // target c file

    /** List of files explicitly included by include directive.
     *  Used to list all sources contributing to this target in
     *  copyright and license info.
     */
    bcore_arr_st_s explicit_embeddings;

    private aware xoico_compiler_s* compiler;

    func : :parse;
    func : :to_be_modified;
    func xoico : finalize;
    func xoico : expand_setup;
    func : :expand_phase1;
    func : :expand_phase2;
    func : :is_cyclic;

    func : :update_xflags = { :xflags_s_update( &o->xflags, xflags ); };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // XOICO_TARGET_H
