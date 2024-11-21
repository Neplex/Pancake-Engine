/*
     Copyright (C) 2016-2017 Keller Darenn - keller.darenn@gmail.com

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
 * \file        Time.hpp
 * \author      Darenn Keller - keller.darenn@gmail.com
 */

#ifndef PANCAKE_TIME_HPP
#define PANCAKE_TIME_HPP

namespace PancakeEngine {

/**
 * @brief Provide some useful information about time and allow to rescale it.
 */
class Time {
 public:
  /**
   * @brief The time in seconds it took to complete the last frame.
   * @return The time in seconds it took to complete the last frame.
   */
  static double getDeltaTime() { return Time::deltaTime; }

 private:
  friend class Engine;  ///< The engine is the only one to change the deltatime.

  static double deltaTime;  ///< Time between two udpates.
};
}  // namespace PancakeEngine
#endif  // PANCAKE_TIME_HPP
