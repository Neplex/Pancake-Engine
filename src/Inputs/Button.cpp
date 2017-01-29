//
// Created by kelle on 27/01/2017.
//

#include "../../include/Inputs/Button.hpp"

int Button::numButtons = 0;

Button::Button(const std::string& name, const std::vector<sf::Keyboard::Key>& keys)
{
    this->name = name;
    this->keys = keys;
    this->isUp = true;
    this->isDown = false;
    this->isHeld = false;
    this->isPressed = false;
    this->isReleased = false;
    this->pressedCallback = nullptr;
    numButtons++;
}

void Button::update() {
    if (isPressed) {
        isPressed = false;
        isHeld = true;
        isDown = true;
        isReleased = false;
        isUp = false;

    } else if (isReleased){
        isReleased = false;
        isHeld = false;
        isDown = false;
        isPressed = false;
        isUp = true;
    }
}
