//
// Created by nicolas on 19/01/17.
//

#include "../include/SpriteRenderer.hpp"

SpriteRenderer::SpriteRenderer(unsigned int width, unsigned int height) {
    sf::Texture* texture = new sf::Texture();
    if (!texture->loadFromFile("../resources/default.png")) {
        exit(EXIT_FAILURE);
    }
    texture->setRepeated(true);
    sprite.setTexture(*texture);
    sprite.setTextureRect(sf::IntRect(0, 0, width, height));
}