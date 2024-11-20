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

#include <GameLogic/Components/Renderer.hpp>
#include <Graphics/SpriteSheet.hpp>

namespace PancakeEngine {

/**
 * @class SpriteRenderer
 * @brief Attach a sprite on a GameObject.
 * @sa Component Renderer SpriteSheet
 */
class SpriteRenderer : public Renderer {
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
  void setSprite(SpriteSheet &sheet, unsigned i, unsigned j);

  /**
   * @brief Flip the sprite.
   * @param b True to flip sprite
   */
  void flip(bool b = true);

  /**
   * @brief Set the position of the sprite relative to the parent
   * @param position the position relative to the parent
   */
  void setPosition(sf::Vector2f position);

  /**
   * @brief Set the rotation of the sprite relative to the parent
   * @param r the rotation relative to the parent
   */
  void setRotation(float r);

  /**
   * @brief Set the scale of the sprite
   * @param scale the scale factor
   */
  void setScale(sf::Vector2f scale);

  sf::Sprite getSprite() const override;

 private:
  bool isFlip;
  sf::Sprite sprite;
};
}  // namespace PancakeEngine

#endif  // PANCAKE_SPRITERENDERER_HPP
