//
// Created by kelle on 27/01/2017.
//

#include <Inputs/Input.hpp>
#include <cassert>

using namespace PancakeEngine;

std::map<std::string, Button *> Input::buttons = std::map<std::string, Button *>();

bool Input::getButtonPressed(const std::string &buttonName) {
  assert(buttons.find(buttonName) != buttons.end());  // button should be in the map (created)
  return buttons[buttonName]->isButtonPressed();
}

bool Input::getButtonHeld(const std::string &buttonName) {
  assert(buttons.find(buttonName) != buttons.end());  // button should be in the map (created)
  return buttons[buttonName]->isButtonHeld();
}
