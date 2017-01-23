//
// Created by nicolas on 22/01/17.
//

#ifndef PANCAKE_INPUTHANDLER_HPP
#define PANCAKE_INPUTHANDLER_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include "Command.hpp"

class InputHandler {
public:
    // Keyboard
    void handleInput(sf::Keyboard::Key key);
    void setCommand(sf::Keyboard::Key key, Command* command);
    void clearCommand(sf::Keyboard::Key key);

    // Mouse
    void handleMouse(int x, int y);
    void handleInput(sf::Mouse::Button button);
    void setCommand(sf::Mouse::Button button, Command* command);
    void clearCommand(sf::Mouse::Button button);

private:
    std::map<sf::Keyboard::Key, Command*> keyboardCommands;
    std::map<sf::Mouse::Button, Command*> mouseCommands;
    Command* mouseCommand;
};

#endif //PANCAKE_INPUTHANDLER_HPP
