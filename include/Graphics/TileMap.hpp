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
 * \file        TileMap.hpp
 * \author      Nicolas Hiot - nicolashiot@hotmail.com
 */

#ifndef PANCAKE_TILEDMAP_HPP
#define PANCAKE_TILEDMAP_HPP

#include <SFML/Graphics.hpp>
#include <Graphics/SpriteSheet.hpp>

namespace PancakeEngine {

    /**
     * @class TileMap
     * @brief Use to create and store an tileMap.
     * @details Can only construct with AssetsManager and display with
     * TileMapRenderer.
     * @sa TileMapRenderer AssetsManager SpriteSheet
     */
    class TileMap {
    public:
        /**
         * @brief Add a new tile to map
         * @param sheet the spriteSheet of the tile
         * @param i the column index of tile in spriteSheet
         * @param j the row index of tile in spriteSheet
         * @param x the column index of tile in map
         * @param y the row index of tile in map
         */
        void addTile(SpriteSheet &sheet, unsigned i, unsigned j, unsigned x, unsigned y);

    private:
        friend class AssetsManager; ///< The only one can create tileMap
        friend class TileMapRenderer;

        /**
         * @struct Tile structure used to store data of a tile
         */
        struct Tile {
            SpriteSheet* sheet;
            unsigned i, j, x, y;
        };

        unsigned tile_width, tile_height, width, height;
        std::vector<Tile> map;

        /**
         * @brief Create a new tiled map
         * @param tile_width the width of a tile (in pixel).
         * @param tile_height the height of a tile (in pixel).
         * @param width the width of TileMap (in tile).
         * @param height the height of TileMap (in tile).
         */
        TileMap(unsigned tile_width, unsigned tile_height, unsigned width, unsigned height);
    };

}

#endif //PANCAKE_TILEDMAP_HPP
