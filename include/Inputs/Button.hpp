//
// Created by keller on 27/01/2017.
//

#ifndef PANCAKE_BUTTON_HPP
#define PANCAKE_BUTTON_HPP

#include <SFML/Window/Keyboard.hpp>
#include <vector>
#include <string>

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
    bool isButtonDown() const { return isDown; }

    /**
     * Returns true if the button is released.
     * @return true if the button is released.
     */
    bool isButtonUp() const { return isUp; }

    /**
    * Returns true if the button is pressed.
    * @return true if the button is pressed.
    */
    bool isButtonHeld() const;

private:
    friend class InputManager;

    void update() {

    }

    /**
     * Change the state of the button as if it was just pressed (or held)
     */
    void press() {
        isDown = !(isDown || isHeld);
        isHeld = true;
        isUp = false;
    }

    /**
     * Change the state of the button as if it was just released (or just up)
     */
    void release() {
        isDown = false;
        isHeld = false;
        isUp = true;
    }

    bool isDown; ///< True at the frame the button is pressed
    bool isHeld; ///< True while the button is pressed
    bool isUp; ///< True while the button is up
};

#endif //PANCAKE_BUTTON_HPP
