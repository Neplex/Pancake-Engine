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
#include <cassert>
#include "Button.hpp"
#include "Input.hpp"
#include "../Debug/Debug.hpp"

namespace PancakeEngine {

    class InputManager {
    public:
        /**
         * Create a virtual Button that will be pressed or released when the given keys are.
         * @param name The name of the button. (ex: "Jump")
         * @param keys The keys that will be pressed or released.
         * @param callback A callback function that will be called when the button is pressed, you should use Input class instead.
         * @see Input
         * @pre The name of the button should be unique.
         * @post The button is associated with the keys.
         * @exemple
         * If you want to create a button called "Jump" that will be pressed if Space key is pressed.
         * @code
         * InputManager::createButton("Jump", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Space}));
         * @endcode
         */
        static void createButton(const std::string& name, const std::vector<sf::Keyboard::Key>& keys,
                void (* callback)() = nullptr)
        {
            // TODO assert that the button is not here already
            Button* b = new Button(name, keys);
            b->pressedCallback = callback;
            buttons.push_back(b);
            Input::buttons[b->name] = b;
            for (int i = 0; i<keys.size(); ++i) {
                keyToButtons[keys[i]].push_back(b);
            }
        }

        /**
         * Update the buttons. (To let know if a button was pressed just for one update)
         * Should be called after all updates.
         */
        static void update()
        {
            for (Button* bu : buttons) {
                bu->update();
            }
        }

        /*!
         *
         */
        static void handleInputs()
        {

            sf::Event event;
            while (window->pollEvent(event)) {
                Debug::processEvent(event);
                switch (event.type) {
                case sf::Event::Closed:
                    window->close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code==sf::Keyboard::Key::Escape)
                        window->close();
                    else
                        for (Button* b : keyToButtons[event.key.code]) {
                            b->press();
                        }
                    break;
                case sf::Event::KeyReleased:
                    for (Button* b : keyToButtons[event.key.code]) {
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
        static std::vector<Button*> buttons;
        static std::map<sf::Keyboard::Key, std::vector<Button*>> keyToButtons;
    };

}
#endif //PANCAKE_INPUTMANAGER_HPP
