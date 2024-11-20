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
 * \file        InputManager.hpp
 * \author      Darenn Keller - keller.darenn@gmail.com
 */

#ifndef PANCAKE_INPUTMANAGER_HPP
#define PANCAKE_INPUTMANAGER_HPP

#include <Debug/Debug.hpp>
#include <Inputs/Button.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace PancakeEngine {

/**
 * \class InputManager
 * \brief Handle all inputs. Should be used to create and destroy buttons.
 * \details This class is used by the engine to handle inputs events.
 * The engine user should only use it to create buttons.
 * \ingroup Inputs
 */
class InputManager {
  // TODO make a InputHandler that will handle inputs. Input Manager will only
  // create and update buttons.
 public:
  /**
   * @brief Create a virtual Button that will be pressed or released when the
   * given keys are.
   * @param name The name of the button.
   * @param keys The keys that will be pressed or released.
   * @param callback A callback function that will be called when the button is
   * pressed, you should use Input class instead.
   * @see Input
   * @pre The name of the button should be unique.
   * @post The button is associated with the keys.
   * @example If you want to create a button called "Jump" that will be pressed
   * if Space key is pressed.
   * @code
   * InputManager::createButton("Jump", std::vector<sf::Keyboard::Key>
   * ({sf::Keyboard::Key::Space}));
   * @endcode
   */
  static void createButton(const std::string &name, const std::vector<sf::Keyboard::Key> &keys,
                           const std::function<void()> &callback = nullptr);

  static void createButton(const std::string &name, int joystickNumber, int joystickButton,
                           const std::function<void()> &callback = nullptr);

  static void createButton(const std::string &name, int joystickNumber, int axisValue, int axis);

  /**
   * @brief Free all buttons.
   * @details Should becalled before the end of the program.
   */
  static void destroyButtons();

 private:
  /**
   * @brief Update the state of the buttons.
   * @details Should be called after all updates that need inputs data.
   */
  static void update();

  /**
   * @brief Handle all inputs events related to window.
   * @details Should be called by the engine to handle the inputs events.
   */
  static void handleInputs();

 private:
  friend class Engine;  ///< the engine is the only one to call update and
                        ///< handleInputs

  static sf::RenderWindow *window;                                  ///< the window from where poll events
  static std::vector<Button *> buttons;                             ///< the buttons created
  static std::map<std::pair<int, int>, Button *> joystickToButton;  ///< mapping between joyticks buttons and buttons.
  static std::map<std::pair<int, int>, Button *> XaxisToButton;
  static std::map<std::pair<int, int>, Button *> YaxisToButton;
  static std::map<sf::Keyboard::Key, std::vector<Button *> > keyToButtons;  ///< mapping between keys and buttons.
};

}  // namespace PancakeEngine
#endif  // PANCAKE_INPUTMANAGER_HPP
