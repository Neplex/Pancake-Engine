//
// Created by nicolas on 24/01/17.
//

#include "../../../include/GameLogic/Components/Camera.hpp"

Camera * Camera::mainCamera = NULL;

Camera::Camera()  {
    view = sf::View(sf::FloatRect(0, 0, sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));
    if (Camera::mainCamera == NULL) mainCamera = this;
}

void Camera::zoom(float factor) {
    view.zoom(factor);
}