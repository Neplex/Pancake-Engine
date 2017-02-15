//
// Created by nicolas on 19/01/17.
//

#include "../../../include/GameLogic/Components/SpriteRenderer.hpp"
#include "../../../include/Graphics/AssetsManager.hpp"


using namespace PancakeEngine;

SpriteRenderer::SpriteRenderer() : isFlip(false) {
    setSprite(AssetsManager::getDefaultSpriteSheet(), 0, 0);
}

void SpriteRenderer::setSprite(SpriteSheet &sheet, unsigned int i, unsigned int j) {
    sprite.setTexture(sheet.texture);
    sprite.setTextureRect(sf::IntRect(
            sheet.tile_width  * i,
            sheet.tile_height * j,
            sheet.tile_width,
            sheet.tile_height
    ));
    sprite.setOrigin(sheet.tile_width/2, sheet.tile_height/2);
}

void SpriteRenderer::flip(bool b) {
    isFlip = b;
    if (isFlip) sprite.setScale(-1, 1);
    else sprite.setScale(1, 1);
}