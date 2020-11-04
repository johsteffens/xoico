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

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

func (:) :.register_group =
{
    if( o.hmap_group.exists( group.tp_name ) )
    {
        return bcore_source_point_s_parse_err_to_em_fa
        (
            &group.source_point,
            TYPEOF_parse_error,
            "'#<sc_t>' was already registered\n",
            o.nameof( group.tp_name )
        );
    }
    o.hmap_group.set( group.tp_name, ( vd_t )group );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) :.register_item =
{
    tp_t global_id = item.get_global_name_tp();
    if( o.hmap_item.exists( global_id ) )
    {
        return o.parse_err_fa( source, "'#<sc_t>' was already registered\n", o.nameof( global_id ) );
    }
    o.hmap_item.set( global_id, ( vd_t )item );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

func (:) :.register_func =
{
    if( o.hmap_func.exists( func.global_name ) )
    {
        return bcore_source_point_s_parse_err_to_em_fa
        (
            &func.source_point,
            TYPEOF_parse_error,
            "'#<sc_t>' was already registered\n",
            o.nameof( func.global_name )
        );
    }

    o.hmap_func.set( func.global_name, ( vd_t )func );
    return 0;
};

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
