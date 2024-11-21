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
 * \file        Button.hpp
 * \author      Darenn Keller - keller.darenn@gmail.com
 */

#ifndef PANCAKE_BUTTON_HPP
#define PANCAKE_BUTTON_HPP

#include <Debug/Debug.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <functional>
#include <string>
#include <vector>

namespace PancakeEngine {

/**
 * \class Button
 * \brief Represent a button with its different states (pressed, held,
 * released). \details Buttons are created by the engine user via the
 * InputManager class. When one of the keys associated with the button is
 * pressed or released, the InputManager class calls the private methods press
 * and release respectively on the button. The engine user can know the state
 * of the buttons via the Input static class. The engine user is not supposed
 * to use buttons. \sa Input InputManager
 * @ingroup Inputs
 */
class Button {
 public:
  /**
   * \brief Returns true if the button was pressed during this update.
   * \return true if the button was pressed during this update.
   */
  bool isButtonPressed() const { return isPressed; }

  /**
   * \brief Returns true if the button was released during this update.
   * \return true if the button was released during this update.
   */
  bool isButtonReleased() const { return isReleased; }

  /**
   * \brief Returns true if the button is down (pressed).
   * \return true if the button is down (pressed).
   */
  bool isButtonDown() const { return isDown; }

  /**
   * \brief Returns true if the button is up (released).
   * \return true if the button is up (released).
   */
  bool isButtonUp() const { return isUp; }

  /**
   * \brief Returns true if the button is held.
   * \details Returns false during the update the button was pressed,
   * and true on following updates, until the button is released.
   * \return true if the button is pressed.
   */
  bool isButtonHeld() const { return isHeld; }

 private:
  friend class InputManager;  ///< The only class that should update the state
                              ///< of the button is InputManager

  /**
   * \brief Construct a button with the given name and associated to the given
   * keys. \param name The name of the button. \param keys The keys associated
   * to the button.
   */
  Button(std::string name, const std::vector<sf::Keyboard::Key> &keys);

  Button(std::string name, int numButton, int numJoystick);

  /**
   * \brief Notify the button that an in-game update has been made.
   * \details Update to change the state of isPressed and isReleased that
   * should be true just during one update. Should be called after all objects
   * no more need to get button state.
   */
  void update();

  /**
   * \brief Change the state of the button as if it was just pressed (or held).
   */
  void press();

  /**
   * \brief Change the state of the button as if it was just released (or just
   * up).
   */
  void release();

  std::string name;                     ///< Name of the button.
  std::vector<sf::Keyboard::Key> keys;  ///< Keys associated with the button.
  int numButton{};
  int numJoystick{};
  bool isPressed;   ///< True at the update the button is pressed
  bool isReleased;  ///< True at the update the button is released
  bool isHeld;      ///< True while the button is pressed
  bool isDown;      ///< True while the button is down (pressed)
  bool isUp;        ///< True while the button is up (released)
  bool isJoystick = false;
  std::function<void()> pressedCallback;  ///< Called when the button is pressed.
};
}  // namespace PancakeEngine

#endif  // PANCAKE_BUTTON_HPP
