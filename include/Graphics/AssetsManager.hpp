/*
     Copyright (C) 2016-2017 Nicolas Hiot - nicolashiot@hotmail.com

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
 * \file        AssetsManager.hpp
 * \author      Nicolas Hiot - nicolashiot@hotmail.com
 */

#ifndef PANCAKE_ASSETMANAGER_HPP
#define PANCAKE_ASSETMANAGER_HPP


#include <map>
#include "SpriteSheet.hpp"
#include "Animation.hpp"

namespace PancakeEngine {

    /**
     * @class AssetsManager
     * @brief Manage animations and spriteSheets.
     * @details Construct and store animations and spriteSheets.
     * @sa Animation SpriteSheet
     */
    class AssetsManager {
    public:
        /**
         * @brief Create a new spriteSheet and return it.
         * @details Name is unique, if you try to create a new spriteSheet
         * with an existing name, the method return the existing spriteSheet.
         * SpriteSheet cannot be override.
         * @attention SpriteSheet must be unique for better performance.
         * Don't create two spriteSheet with the same texture.
         * @param name the name of the spriteSheet.
         * @param uri the uri of the image
         * @param tile_w the tile width
         * @param tile_h the tile height
         * @return the created spriteSheet
         * @as SpriteSheet
         */
        static SpriteSheet& createSpriteSheet(std::string name, std::string uri, unsigned int tile_w, unsigned int tile_h);

        /**
         * @brief Get a spriteSheet by name. If name doesn't exist, return the
         * default spriteSheet.
         * @param name the spriteSheet name.
         * @return The spriteSheet with the name.
         * @as SpriteSheet
         */
        static SpriteSheet& getSpriteSheet(std::string name);

        /**
         * @brief Get the default spriteSheet.
         * @return The default spriteSheet.
         * @as SpriteSheet
         */
        static SpriteSheet& getDefaultSpriteSheet();

        /**
         * @brief Create a new animation and return it.
         * @details Name is unique, if you try to create a new animation
         * with an existing name, the method return the existing animation.
         * Animation cannot be override.
         * @attention Animation must be unique for better performance.
         * Don't create two same animation.
         * @param name the animation name.
         * @param spriteSheetName the spriteSheet name.
         * @return A new animation.
         * @as Animation SpriteSheet
         */
        static Animation& createAnimation(std::string name, std::string spriteSheetName);
        /**
         * @brief Create a new animation and return it.
         * @details Name is unique, if you try to create a new animation
         * with an existing name, the method return the existing animation.
         * Animation cannot be override.
         * @attention Animation must be unique for better performance.
         * Don't create two same animation.
         * @param name the animation name.
         * @param spriteSheet the spriteSheet.
         * @return A new animation.
         * @as Animation SpriteSheet
         */
        static Animation& createAnimation(std::string name, SpriteSheet& spriteSheet);

        /**
         * @brief Get an animation by name. If name doesn't exist, return the
         * default animation.
         * @param name the animation name.
         * @return The animation with the name.
         * @as Animation
         */
        static Animation& getAnimation(std::string name);

        /**
         * @brief Get the default animation.
         * @return The default animation.
         * @as Animation
         */
        static Animation& getDefaultAnimation();

    private:
        static std::map<std::string, SpriteSheet> spriteSheets; ///< List of spriteSheets
        static std::map<std::string, Animation> animations; ///< List of animations

        static SpriteSheet defaultSpriteSheet; ///< The default spriteSheet
        static Animation defaultAnimation; ///< The default animation

        AssetsManager();
    };
}

#endif //PANCAKE_ASSETMANAGER_HPP
