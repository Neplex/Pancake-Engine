//
// Created by nicolas on 19/01/17.
//

#include "../../../include/GameLogic/Components/SpriteRenderer.hpp"


using namespace PancakeEngine;

SpriteRenderer::SpriteRenderer(unsigned int width, unsigned int height) {
    sf::Texture* texture = new sf::Texture();
    if (!texture->loadFromFile("../resources/default.png")) {
        exit(EXIT_FAILURE);
    }
    texture->setRepeated(true);
    texture->setSmooth(true);
    sprite.setTexture(*texture);
    sprite.setTextureRect(sf::IntRect(0, 0, width, height));
    sprite.setOrigin(width/2, height/2);
}

SpriteRenderer::SpriteRenderer(SpriteSheet& sheet, unsigned int i, unsigned int j) {
    sprite.setTexture(sheet.texture);
    sprite.setTextureRect(sf::IntRect(
            sheet.tile_width  * i,
            sheet.tile_height * j,
            sheet.tile_width,
            sheet.tile_height
    ));
    sprite.setOrigin(sheet.tile_width/2, sheet.tile_height/2);
}
