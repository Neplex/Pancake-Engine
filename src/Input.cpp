//
// Created by kelle on 27/01/2017.
//

#include <cassert>
#include "../include/Inputs/Input.hpp"

std::map<std::string, Button *> Input::buttons = std::map<std::string, Button *>();

bool Input::getButtonDown(const std::string& buttonName)
{
    assert(buttons.find(buttonName) != buttons.end());
    return buttons[buttonName]->isButtonDown();
}