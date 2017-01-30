//
// Created by kelle on 27/01/2017.
//

#include <cassert>
#include "../../include/Inputs/Input.hpp"

using namespace PancakeEngine;

std::map<std::string, Button *> Input::buttons = std::map<std::string, Button *>();

bool Input::getButtonPressed(const std::string& buttonName)
{
    assert(buttons.find(buttonName) != buttons.end()); // button should be in the map (created)
    return buttons[buttonName]->isButtonPressed();
}
