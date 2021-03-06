//
// Created by kelle on 27/01/2017.
//

#include "../../include/Inputs/Button.hpp"

using namespace PancakeEngine;

Button::Button(const std::string& name, const std::vector<sf::Keyboard::Key>& keys) : name(name), keys(keys),
                                                                                      isUp(true), isDown(false),
                                                                                      isHeld(false), isPressed(false),
                                                                                      isReleased(false),
                                                                                      pressedCallback(nullptr)
{ }

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

void Button::press()
{
    if (!isDown) {
        // TODO bug here at runtime without debugger the name is chelou sometimes
        Debug::log("Inputs", "Button "+name+" has been pressed.");
        if (pressedCallback!=nullptr) {
            pressedCallback();
        }
        isDown = true;
        isPressed = true;
        isUp = false;
        isReleased = false;
        isHeld = false;
    }
}

void Button::release()
{
    Debug::log("Inputs", "Button "+name+" has been released.");
    isDown = false;
    isHeld = false;
    isPressed = false;
    isUp = true;
    isReleased = true;
}
