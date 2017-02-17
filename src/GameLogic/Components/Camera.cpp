//
// Created by nicolas on 24/01/17.
//

#include "../../../include/GameLogic/Components/Camera.hpp"

using namespace PancakeEngine;

Camera::Camera() {
    view = sf::View(sf::FloatRect(0, 0, sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));
}

void Camera::zoom(float factor) {
    view.zoom(factor);
}
