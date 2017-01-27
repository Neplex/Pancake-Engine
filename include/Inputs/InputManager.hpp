//
// Created by kelle on 27/01/2017.
//

#ifndef PANCAKE_INPUTMANAGER_HPP
#define PANCAKE_INPUTMANAGER_HPP

#include <map>
#include <vector>
#include <string>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include "Button.hpp"
#include "Input.hpp"

class InputManager {
public:
    /**
     * Create a virtual Button that will be pressed or released when the given keys are.
     * @param name The name of the button. (ex: "Jump")
     * @param keys The keys that will be pressed or released.
     * @pre The name of the button should be unique.
     * @post The button is associated with the keys.
     */
    static void createButton(const std::string& name, const std::vector<sf::Keyboard::Key>& keys) {
        // TODO assert
        buttons.push_back(Button(name, keys));
        Input::buttons[buttons.back().name] = &buttons.back();
        for (int i = 0; i < keys.size(); ++i) {
            keyToButtons[keys[i]].push_back(&buttons.back());
        }
    }

    static void handleInputs() {
        sf::Event event;
        while (window->pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Key::Escape)
                    window->close();
                else
                    for (Button* b : keyToButtons[event.key.code]) {
                        b->press();
                    }
                break;
                case sf::Event::KeyReleased:
                    for (Button * b : keyToButtons[event.key.code]) {
                        b->release();
                    }
            default:
                break;
            }
        }
    }

private:
    friend class Engine;
    static sf::RenderWindow* window;
    static std::vector<Button> buttons;
    static std::map<sf::Keyboard::Key, std::vector<Button *>> keyToButtons;
};

#endif //PANCAKE_INPUTMANAGER_HPP
