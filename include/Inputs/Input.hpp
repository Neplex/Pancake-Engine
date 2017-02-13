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
 * \file        Input.hpp
 * \author      Darenn Keller - keller.darenn@gmail.com
 */

#ifndef PANCAKE_INPUT_HPP
#define PANCAKE_INPUT_HPP

#include <string>
#include <map>
#include "Button.hpp"

namespace PancakeEngine {

    /**
     * @class Input
     * @ingroup Inputs
     * @brief Class used by the user to get inputs buttons states.
     * @details The buttons must be created with the InputManager.
     * @sa InputManager
     */
    class Input {
    public:
        /**
         * @brief Returns true during the frame the user pressed down the virtual button identified by buttonName.
         * @param buttonName The name of the virtual button created with InputManager.
         * @return true during the frame the user pressed down the virtual button identified by buttonName.
         */
        static bool getButtonPressed(const std::string& buttonName);

        static bool getButtonHeld(const std::string& buttonName);

    private:
        friend class InputManager; ///< The input manager update #buttons.
        static std::map<std::string, Button*> buttons; ///< Associate a name with a button.
    };
}

#endif //PANCAKE_INPUT_HPP
