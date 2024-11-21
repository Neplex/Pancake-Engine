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
 * \file        TileMapRenderer.hpp
 * \author      Nicolas Hiot - nicolashiot@hotmail.com
 */

#ifndef PANCAKE_TILEMAPRENDERER_HPP
#define PANCAKE_TILEMAPRENDERER_HPP

#include <GameLogic/Components/Component.hpp>
#include <Graphics/TileMap.hpp>

constexpr unsigned int CHUNK_SIZE = 512;

namespace PancakeEngine {

/**
 * @class TileMapRenderer
 * @brief Component that can render a TileMap.
 * @sa TileMap Component
 */
class TileMapRenderer : public Component {
 public:
  /**
   * @brief Construct an TileMapRenderer with a default TileMap.
   * @sa AssetsManager
   */
  TileMapRenderer();
  ~TileMapRenderer() override;

  /**
   * @brief Clear the chunks grid.
   * @details Call this method to remove TileMap from the renderer.
   */
  void clearGrid();

  /**
   * @brief Set the tileMap.
   * @param map the new tileMap.
   */
  void setTileMap(const TileMap &map);

 protected:
  friend class Window;
  /**
   * @brief Get the vector of sprites (chunks).
   * @details Only used by the window.
   * @return A list of sprites (chunks).
   */
  std::vector<sf::Sprite> getChunksSprites() const;

 private:
  sf::RenderTexture ***textureGrid = nullptr;  ///< Matrix of chunks
  unsigned chunk_width;
  unsigned chunk_height;
  unsigned nb_column;
  unsigned nb_row;
  unsigned marge_x;
  unsigned marge_y;
};

}  // namespace PancakeEngine

#endif  // PANCAKE_TILEMAPRENDERER_HPP
