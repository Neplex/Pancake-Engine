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
 * \file        SpriteSheet.hpp
 * \author      Nicolas Hiot - nicolashiot@hotmail.com
 */

#ifndef PANCAKE_SPRITESHEET_HPP
#define PANCAKE_SPRITESHEET_HPP


#include <SFML/Graphics/Texture.hpp>

namespace PancakeEngine {

    /**
     * @class SpriteSheet
     * @brief Use to create and store a spriteSheet.
     * @details Can only construct with AssetsManager.
     * @sa Animation AssetsManager SpriteRenderer
     */
    class SpriteSheet {
    public:
        /**
         * @brief Create a SpriteSheet from image 'uri'
         * @param uri the link to the image
         * @param tile_w the tile width
         * @param tile_h the tile height
         */
        SpriteSheet(std::string uri, unsigned int tile_w, unsigned int tile_h) : tile_width(tile_w), tile_height(tile_h) {
            if (!texture.loadFromFile(uri)) exit(EXIT_FAILURE);
            texture.setSmooth(true);
        }

    private:
        friend class Animation;
        friend class AnimationRenderer;
        friend class SpriteRenderer;

        sf::Texture texture;
        unsigned int tile_width;
        unsigned int tile_height;
    };
}

#endif //PANCAKE_SPRITESHEET_HPP
