//
// Created by nicolas on 22/01/17.
//

#include "../include/InputHandler.hpp"

// Keyboard
void InputHandler::handleInput(sf::Keyboard::Key key) {
    Command* command = keyboardCommands[key];
    if (command != NULL)
        command->execute();
}

void InputHandler::setCommand(sf::Keyboard::Key key, Command* command) {
    keyboardCommands[key] = command;
}

void InputHandler::clearCommand(sf::Keyboard::Key key) {
    keyboardCommands.erase(key);
}


// Mouse
void InputHandler::handleMouse(int x, int y) {
    if (mouseCommand != NULL)
        mouseCommand->execute(x, y);
}

void InputHandler::handleInput(sf::Mouse::Button button) {
    Command* command = mouseCommands[button];
    if (command != NULL)
        command->execute();
}

void InputHandler::setCommand(sf::Mouse::Button button, Command *command) {
    mouseCommands[button] = command;
}

void InputHandler::clearCommand(sf::Mouse::Button button) {
    mouseCommands.erase(button);
}