//
// Created by nicolas on 24/01/17.
//

#include "../include/Camera.hpp"

Camera * Camera::mainCamera = NULL;

Camera::Camera(sf::FloatRect floatRect) : view(floatRect) {
    if (Camera::mainCamera == NULL) mainCamera = this;
}

void Camera::zoom(float factor) {
    view.zoom(factor);
}