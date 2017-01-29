//
// Created by keller on 27/01/2017.
//

#ifndef PANCAKE_BUTTON_HPP
#define PANCAKE_BUTTON_HPP

#include <SFML/Window/Keyboard.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "../Debug/Debug.hpp"

/**
 * Represent a virtual button. Buttons are created by the engine user via the InputManager class.
 * The user give it a name (i.e : "Jump") and a set of keys (i.e { sf::Keyboard::Key::Space, sf::Keyboard::Key::Up }).
 * When one of the keys is pressed or released,
 * the InputManager class calls the private methods press and release respectively on the button.
 * The engine user can know the state of the buttons via the Input static class.
 * @see Input
 * @see InputManager
 */
class Button {
public:
    std::string name; ///< Name of the button
    std::vector<sf::Keyboard::Key> keys; ///< Keys associated with the button

    /**
     * Construct a button with the given name and associated to the given keys.
     * @param name The name of the button.
     * @param keys The keys associated to the button.
     */
    Button(const std::string& name, const std::vector<sf::Keyboard::Key>& keys);

    /**
     * Returns true if the button was pressed during this update.
     * @return true if the button was pressed during this update.
     */
    bool isButtonPressed() const { return isPressed; }

    /**
     * Returns true if the button was released during this update.
     * @return true if the button was released during this update.
     */
    bool isButtonReleased() const { return isReleased; }


    /**
     * Returns true if the button is down (pressed).
     * @return true if the button is down (pressed).
     */
    bool isButtonDown() const { return isDown; }

    /**
     * Returns true if the button is up (released).
     * @return true if the button is up (released).
     */
    bool isButtonUp() const { return isUp; }

    /**
    * Returns true if the button is held.
    * Returns false during the update the button was pressed,
    * and true on following updates, until the button is released.
    * @return true if the button is pressed.
    */
    bool isButtonHeld() const { return isHeld; }

private:
    friend class InputManager;

    /**
     * Called before each update of handleInput() in order
     * to change the state of isPressed and isReleased the next update they were true.
     */
    void update();

    /**
     * Change the state of the button as if it was just pressed (or held)
     */
    void press() {
        if (!isDown) {
            // TODO bug here at runtime without debugger the name is chelou sometimes
            Debug::log("Inputs", "Button " + name + " has been pressed.");
            if (pressedCallback != nullptr)
            {
                pressedCallback();
            }
            isDown = true;
            isPressed = true;
            isUp = false;
            isReleased = false;
            isHeld = false;
        }
    }

    /**
     * Change the state of the button as if it was just released (or just up)
     */
    void release() {
        Debug::log("Inputs", "Button " + name + " has been released.");
        isDown = false;
        isHeld = false;
        isPressed = false;
        isUp = true;
        isReleased = true;
    }

    bool isPressed; ///< True at the update the button is pressed
    bool isReleased; ///< True at the update the button is released
    bool isHeld; ///< True while the button is pressed
    bool isDown; ///< True while the button is down (pressed)
    bool isUp; ///< True while the button is up (released)

    static int numButtons;
    void (*pressedCallback)(); ///< Called when the button is pressed.
};

#endif //PANCAKE_BUTTON_HPP
