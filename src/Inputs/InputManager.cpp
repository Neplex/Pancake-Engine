//
// Created by kelle on 27/01/2017.
//

#include "../../include/Inputs/InputManager.hpp"

sf::RenderWindow* InputManager::window = nullptr;
std::vector<Button*> InputManager::buttons = std::vector<Button*>();
std::map<sf::Keyboard::Key, std::vector<Button *>> InputManager::keyToButtons
        = std::map<sf::Keyboard::Key, std::vector<Button *>>();