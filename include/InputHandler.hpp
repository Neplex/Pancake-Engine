//
// Created by nicolas on 22/01/17.
//

#ifndef PANCAKE_INPUTHANDLER_HPP
#define PANCAKE_INPUTHANDLER_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include "Command.hpp"

/**
 * Triggering commands when the associated button is pressed
 */
class InputHandler {
public:
    // Keyboard
    /**
     * Triggering the command associated with the keyboard'key'
     * @param key
     */
    void handleInput(sf::Keyboard::Key key);
    /**
     * Set the 'command' to the keyboard 'key'
     * @param key
     * @param command
     */
    void setCommand(sf::Keyboard::Key key, Command* command);
    /**
     * Remove the 'command' associated to keyboard 'key'
     * @param key
     */
    void clearCommand(sf::Keyboard::Key key);

    // Mouse
    /**
     * Triggering the command associated to the mouse
     * @param x
     * @param y
     */
    void handleMouse(int x, int y);
    /**
     * Triggering the command associated with the mouse 'button'
     * @param button
     */
    void handleInput(sf::Mouse::Button button);
    /**
     * Set the 'command' to the mouse 'button'
     * @param button
     * @param command
     */
    void setCommand(sf::Mouse::Button button, Command* command);
    /**
     * Remove the 'command' associated to mouse 'button'
     * @param button
     */
    void clearCommand(sf::Mouse::Button button);

private:
    std::map<sf::Keyboard::Key, Command*> keyboardCommands;
    std::map<sf::Mouse::Button, Command*> mouseCommands;
    Command* mouseCommand;
};

#endif //PANCAKE_INPUTHANDLER_HPP
