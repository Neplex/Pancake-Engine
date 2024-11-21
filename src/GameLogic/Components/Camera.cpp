//
// Created by nicolas on 24/01/17.
//

#include <GameLogic/Components/Camera.hpp>

using namespace PancakeEngine;

Camera::Camera() {
  const unsigned int width = sf::VideoMode::getDesktopMode().width;
  const unsigned int height = sf::VideoMode::getDesktopMode().height;
  view = sf::View(sf::FloatRect(0, 0, width, height));
}

Camera::~Camera() { delete background; }

void Camera::zoom(const float factor) { view.zoom(factor); }

void Camera::setBackground(const std::string &file) {
  delete background;
  background = new sf::Texture();
  assert(background->loadFromFile(file));
  background->setRepeated(true);
  background->setSmooth(true);
}