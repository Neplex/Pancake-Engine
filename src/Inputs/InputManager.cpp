//
// Created by kelle on 27/01/2017.
//

#include "../../include/Inputs/InputManager.hpp"

using namespace PancakeEngine;

sf::RenderWindow* InputManager::window = nullptr;
std::vector<Button*> InputManager::buttons = std::vector<Button*>();
std::map<sf::Keyboard::Key, std::vector<Button *>> InputManager::keyToButtons
        = std::map<sf::Keyboard::Key, std::vector<Button *>>();

std::map<std::pair<int, int>, Button*> InputManager::joystickToButton = std::map<std::pair<int, int>, Button*>();

std::map<std::pair<int, int>, Button*> InputManager::XaxisToButton = std::map<std::pair<int, int>, Button*>();
std::map<std::pair<int, int>, Button*> InputManager::YaxisToButton = std::map<std::pair<int, int>, Button*>();

void InputManager::handleInputs()
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
            break;
        case sf::Event::JoystickButtonPressed: {
            std::pair<int, int> pad(event.joystickButton.joystickId, event.joystickButton.button);
            if (joystickToButton.count(pad)) {
                joystickToButton[pad]->press();
            }
            break;
        }
        case sf::Event::JoystickButtonReleased: {
            std::pair<int, int> pad(event.joystickButton.joystickId, event.joystickButton.button);
            if (joystickToButton.count(pad)) {
                joystickToButton[pad]->release();
            }
            break;
        }
        case sf::Event::JoystickMoved: {
            if (event.joystickMove.axis == sf::Joystick::X || event.joystickMove.axis == sf::Joystick::PovX)
            {
                if (event.joystickMove.position > 50) {
                    std::pair<int, int> pad(event.joystickButton.joystickId, 1);
                    if (XaxisToButton.count(pad))
                        XaxisToButton[pad]->press();
                } else if (event.joystickMove.position < -50){
                    std::pair<int, int> pad(event.joystickButton.joystickId, -1);
                    if (XaxisToButton.count(pad))
                        XaxisToButton[pad]->press();
                }  else {
                    std::pair<int, int> pad(event.joystickButton.joystickId, 1);
                    if (XaxisToButton.count(pad))
                        XaxisToButton[pad]->release();
                    std::pair<int, int> pad2(event.joystickButton.joystickId, -1);
                    if (XaxisToButton.count(pad2))
                        XaxisToButton[pad2]->release();
                }
            }
            if (event.joystickMove.axis == sf::Joystick::Y || event.joystickMove.axis == sf::Joystick::PovY)
            {
                if (event.joystickMove.position > 50) {
                    std::pair<int, int> pad(event.joystickButton.joystickId, 1);
                    if (YaxisToButton.count(pad))
                        YaxisToButton[pad]->press();
                } else if (event.joystickMove.position < -50){
                    std::pair<int, int> pad(event.joystickButton.joystickId, -1);
                    if (YaxisToButton.count(pad))
                        YaxisToButton[pad]->press();
                } else {
                    std::pair<int, int> pad(event.joystickButton.joystickId, 1);
                    if (YaxisToButton.count(pad))
                        YaxisToButton[pad]->release();
                    std::pair<int, int> pad2(event.joystickButton.joystickId, -1);
                    if (YaxisToButton.count(pad2))
                        YaxisToButton[pad2]->release();
                }
            }
        }
        default:
            break;
        }
    }
}

void InputManager::update()
{
    for (Button* bu : buttons) {
        bu->update();
    }
}

void InputManager::destroyButtons()
{
    for (Button * b : buttons) {
        delete b;
    }
}

void InputManager::createButton(const std::string& name, int joystickNumber, int axisValue, int axis)
{
    for (unsigned i = 0; i<buttons.size(); ++i) {
        assert(name != buttons[i]->name);
    }
    Button* b = new Button(name, axisValue, joystickNumber);
    buttons.push_back(b);
    Input::buttons[b->name] = b;
    std::pair<int,int> pad (joystickNumber, axisValue);
    if (axis == -1)
        YaxisToButton[pad] = b;
    else
        XaxisToButton[pad] = b;
}

void InputManager::createButton(const std::string& name, int joystickNumber, int joystickButton, void (* callback)())
{
    for (unsigned i = 0; i<buttons.size(); ++i) {
        assert(name != buttons[i]->name);
    }
    Button* b = new Button(name, joystickButton, joystickNumber);
    b->pressedCallback = callback;
    buttons.push_back(b);
    Input::buttons[b->name] = b;
    std::pair<int,int> pad (joystickNumber, joystickButton);
    joystickToButton[pad] = b;
}

void
InputManager::createButton(const std::string& name, const std::vector<sf::Keyboard::Key>& keys, void (* callback)())
{
    for (unsigned i = 0; i<buttons.size(); ++i) {
        assert(name != buttons[i]->name);
    }
    Button* b = new Button(name, keys);
    b->pressedCallback = callback;
    buttons.push_back(b);
    Input::buttons[b->name] = b;
    for (unsigned i = 0; i<keys.size(); ++i) {
        keyToButtons[keys[i]].push_back(b);
    }
}
