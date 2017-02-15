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
 * \file        SpriteRenderer.hpp
 * \author      Nicolas Hiot - nicolashiot@hotmail.com
 */

#ifndef PANCAKE_SPRITERENDERER_HPP
#define PANCAKE_SPRITERENDERER_HPP

#include "Component.hpp"
#include "../../Graphics/SpriteSheet.hpp"
#include <SFML/Graphics.hpp>

namespace PancakeEngine {

    /**
     * @class SpriteRenderer
     * @brief Attach a sprite on a GameObject.
     * @sa Component
     */
    class SpriteRenderer : public Component {
    public:
        /**
         * @brief Construct an SpriteRenderer with a default SpriteSheet and
         * a default size (32, 32)
         * @sa AssetsManager
         */
        SpriteRenderer();

        /**
         * @brief Set sprite from a SpriteSheet 'sheet'.
         * Take the sprite at the column i and row j.
         * @param sheet the SpriteSheet
         * @param i the column index
         * @param j the row index
         */
        void setSprite(SpriteSheet& sheet, unsigned int i, unsigned int j);

        /**
         * @brief Flip the sprite.
         * @param b True to flip sprite
         */
        void flip(bool b = true);

    private:
        friend class Window; ///< Draw the sprite

        bool isFlip;
        sf::Sprite sprite;
    };
}

#endif //PANCAKE_SPRITERENDERER_HPP
