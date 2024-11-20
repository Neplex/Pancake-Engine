//
// Created by kelle on 27/01/2017.
//

#include <Inputs/Button.hpp>
#include <utility>

using namespace PancakeEngine;

Button::Button(std::string name, const std::vector<sf::Keyboard::Key> &keys)
    : name(std::move(name)),
      keys(keys),
      isPressed(false),
      isReleased(false),
      isHeld(false),
      isDown(false),
      isUp(true),
      pressedCallback(nullptr) {}

void Button::update() {
  if (isPressed) {
    isPressed = false;
    isHeld = true;
    isDown = true;
    isReleased = false;
    isUp = false;

  } else if (isReleased) {
    isReleased = false;
    isHeld = false;
    isDown = false;
    isPressed = false;
    isUp = true;
  }
}

void Button::press() {
  if (!isDown) {
    Debug::log("Inputs", "Button " + name + " has been pressed.");
    if (pressedCallback != nullptr) {
      pressedCallback();
    }
    isDown = true;
    isPressed = true;
    isUp = false;
    isReleased = false;
    isHeld = false;
  }
}

void Button::release() {
  Debug::log("Inputs", "Button " + name + " has been released.");
  isDown = false;
  isHeld = false;
  isPressed = false;
  isUp = true;
  isReleased = true;
}

Button::Button(std::string name, const int numButton, const int numJoystick)
    : name(std::move(name)),
      numButton(numButton),
      numJoystick(numJoystick),
      isPressed(false),
      isReleased(false),
      isHeld(false),
      isDown(false),
      isUp(true),
      isJoystick(true),
      pressedCallback(nullptr) {}
