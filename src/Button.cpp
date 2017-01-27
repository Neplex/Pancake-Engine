//
// Created by kelle on 27/01/2017.
//

#include "../include/Inputs/Button.hpp"

Button::Button(const std::string& name, const std::vector<sf::Keyboard::Key>& keys)
{
    this->name = name;
    this->keys = keys;
    this->isUp = true;
    this->isDown = false;
    this->isHeld = false;
}
