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

#ifndef PANCAKE_SCENEFACTORY_HPP
#define PANCAKE_SCENEFACTORY_HPP

#include "../GameLogic/GameObject.hpp"
#include "../GameLogic/Scene.hpp"
#include "../Parser/TmxParser.hpp"
namespace PancakeEngine {
    /**
     * @class SceneFactory
     * @brief Use to create a scene from a file.
     */
    class SceneFactory {
    public:
        /**!
         * @brief Create a SceneFactory object
         */
        SceneFactory();
        /**!
         * @brief load all objects of a TMX file
         * @param filename file to parse
         * @return scene of the file
         */
        Scene loadAllSceneObject(const char *filename);
    private:
        /**!
         * Map which contains all Prefabs objects
         */
        std::map<std::string, GameObject*>  factory_map;

    };

}
#endif //PANCAKE_SCENEFACTORY_HPP
