//
// Created by kelle on 27/01/2017.
//

#ifndef PANCAKE_INPUT_HPP
#define PANCAKE_INPUT_HPP

#include <string>
#include <map>
#include "Button.hpp"

class Input {
public:
    /**
     * Returns true during the frame the user pressed down the virtual button identified by buttonName.
     * @param buttonName The name of the virtual button.
     * @return true during the frame the user pressed down the virtual button identified by buttonName.
     */
    static bool getButtonPressed(const std::string& buttonName);

private:
    friend class InputManager;
    static std::map<std::string, Button *> buttons;
};

#endif //PANCAKE_INPUT_HPP
