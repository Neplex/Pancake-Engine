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
