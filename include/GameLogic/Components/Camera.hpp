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
 * \file        Camera.hpp
 * \author      Nicolas Hiot - nicolashiot@hotmail.com
 */

#ifndef PANCAKE_CAMERA_HPP
#define PANCAKE_CAMERA_HPP

#include <GameLogic/Components/Component.hpp>
#include <Graphics/Window.hpp>
#include <SFML/Graphics/View.hpp>

namespace PancakeEngine {

/**
 * @class Camera
 * @brief Attach a camera on a GameObject.
 * @sa Component Window
 */
class Camera : public Component {
 public:
  Camera();
  ~Camera() override;

  /**
   * @brief Zoom view with factor.
   * @param factor
   */
  void zoom(float factor);

  /**
   * @brief Set background image.
   * @param file the new background path.
   */
  void setBackground(const std::string &file);

 private:
  friend class Window;  ///< Use the camera to draw.
  sf::View view;
  sf::Texture *background = nullptr;
};
}  // namespace PancakeEngine
#endif  // PANCAKE_CAMERA_HPP
