/*
     Copyright (C) 2016-2017 Pia Virgil - virgil.pia@gmail.com

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

/**
 * \file        SceneFactory.hpp
 * \author      Virgil Pia - virgil.pia@gmail.com
 */

#ifndef PANCAKE_TMXPARSER_HPP
#define PANCAKE_TMXPARSER_HPP
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <Tmx.h>
#include "iostream"
/**
     * @class Parser
     * @brief Use to parse a file and retrieve all file data
     */
class Parser
{
public:
    /**!
     * @brief Create a Parse object and load the file
     * @param filename file to parse
    */
    Parser( const char* filename ){load( filename );};
    virtual ~Parser(){delete map;};
    /**!
     * @brief Parse the file in param
     * @param filename file to parse
     * @return boolean true if there is no error
    */
    bool load( const char* filename );
    /**!
     * @brief load all the layer
     * @return vector of layer
    */
    std::vector<Tmx::TileLayer*> loadLayer();
    /**!
     * @brief Contains all the map data
    */
    Tmx::Map * map;
    /**!
     * @brief load all the layer
     * @return vector of object
    */
    std::vector<Tmx::Object> loadObjectGroups();

};


#endif //PANCAKE_TMXPARSER_HPP
