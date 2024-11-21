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
 * \file        AnimationRenderer.hpp
 * \author      Nicolas Hiot - nicolashiot@hotmail.com
 */

#ifndef PANCAKE_ANIMATIONRENDERER_HPP
#define PANCAKE_ANIMATIONRENDERER_HPP

#include <GameLogic/Components/Renderer.hpp>
#include <Graphics.hpp>

namespace PancakeEngine {

/**
 * @class AnimationRenderer
 * @brief An animation renderer is used to display and control an animation.
 * @sa Component Renderer Animation
 */
class AnimationRenderer : public Renderer {
 public:
  /**
   * @brief Construct an AnimationRenderer with a default animation.
   * @sa AssetsManager
   */
  AnimationRenderer();

  /**
   * @brief Play the animation.
   */
  void play();

  /**
   * @brief Pause the animation.
   */
  void pause();

  /**
   * @brief Stop the animation (pause and get back to start).
   */
  void stop();

  /**
   * @brief Choose if the animation loop or not.
   * default: False
   * @param b True if the animation loop, else False.
   */
  void loop(bool b = true);

  /**
   * @brief Flip the animation
   * @param b True to flip animation
   */
  void flip(bool b = true);

  /**
   * @brief Update the animation with time elapse.
   */
  void update() override;

  /**
   * @brief Set the animation.
   * @param a the animation.
   */
  void setAnimation(Animation &a);

  sf::Sprite getSprite() const override;

 private:
  Animation *animation;
  bool isRun;   ///< True if the animation is playing
  bool isLoop;  ///< True if the animation loop
  bool isFlip;  ///< True if the animation is flip
  double currentTime;
  unsigned int currentFrame;
  sf::Sprite sprite;

  void reset();
};
}  // namespace PancakeEngine

#endif  // PANCAKE_ANIMATIONRENDERER_HPP
