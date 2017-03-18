//
// Created by kelle on 27/01/2017.
//

#include <iostream>
#include <cassert>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <Inputs/InputManager.hpp>
#include <Inputs/Input.hpp>

using namespace PancakeEngine;

sf::RenderWindow* InputManager::window = nullptr;
std::vector<Button*> InputManager::buttons = std::vector<Button*>();
std::map<sf::Keyboard::Key, std::vector<Button *>> InputManager::keyToButtons = std::map<sf::Keyboard::Key, std::vector<Button *>>();

void InputManager::createButton(const std::string &name, const std::vector<sf::Keyboard::Key> &keys, void (* callback)()) {
    for (unsigned i = 0; i<buttons.size(); ++i) assert(name != buttons[i]->name);
    Button* b = new Button(name, keys);
    b->pressedCallback = callback;
    buttons.push_back(b);
    Input::buttons[b->name] = b;
    for (unsigned i = 0; i<keys.size(); ++i) keyToButtons[keys[i]].push_back(b);
}

void InputManager::destroyButtons() {
    for (Button * b : buttons) delete b;
}

void InputManager::update() {
    for (Button* bu : buttons) bu->update();
}

void InputManager::handleInputs() {
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