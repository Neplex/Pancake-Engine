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
 * \file        Animation.hpp
 * \author      Nicolas Hiot - nicolashiot@hotmail.com
 */

#ifndef PANCAKE_ANIMATION_HPP
#define PANCAKE_ANIMATION_HPP

#include <Graphics/SpriteSheet.hpp>
#include <utility>

namespace PancakeEngine {

class AssetsManager;

/**
 * @class Animation
 * @brief Use to create and store an animation.
 * @details Can only construct with AssetsManager and display with
 * AnimationRenderer or Animator.
 * @sa AnimationRenderer Animator AssetsManager SpriteSheet
 */
class Animation {
 public:
  /**
   * @brief Add the sprite at the column i and row j from the SpriteSheet to
   * the animation.
   * @param i the column index
   * @param j the row index
   * @param time the duration in millisecond
   * @param flip True if the sprite is flip
   * @sa SpriteSheet
   */
  void addFrame(unsigned i, unsigned j, unsigned time, bool flip = false);

 private:
  friend class AssetsManager;      ///< The only one can create animation
  friend class AnimationRenderer;  ///< Control the animation

  /**
   * @brief Structure to store an animation frame.
   */
  struct Frame {
    unsigned i;
    unsigned j;
    unsigned time;
    bool flip;
  };

  SpriteSheet spriteSheet;               ///< SpriteSheet of the animation.
  std::vector<Animation::Frame> frames;  ///< List of frames.

  /**
   * @brief Construct an animation associated with a spriteSheet.
   * @param sheet spriteSheet of the animation.
   * @sa SpriteSheet
   */
  explicit Animation(SpriteSheet sheet) : spriteSheet(std::move(sheet)) {}
};

}  // namespace PancakeEngine
#endif  // PANCAKE_ANIMATION_HPP
