//
// Created by nicolas on 24/01/17.
//

#include "../../../include/GameLogic/Components/Camera.hpp"

using namespace PancakeEngine;

Camera::Camera() {
    int width = sf::VideoMode::getDesktopMode().width;
    int height = sf::VideoMode::getDesktopMode().height;
    view = sf::View(sf::FloatRect(0, 0, width, height));
}

Camera::~Camera() {
    if (background != NULL) delete background;
}

void Camera::zoom(float factor) {
    view.zoom(factor);
}

void Camera::setBackground(std::string file) {
    if (background != NULL) delete background;
    background = new sf::Texture();
    assert(background->loadFromFile(file));
    background->setRepeated(true);
    background->setSmooth(true);
}