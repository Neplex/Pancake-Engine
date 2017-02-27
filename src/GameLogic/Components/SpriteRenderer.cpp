//
// Created by nicolas on 19/01/17.
//

#include "../../../include/GameLogic/Components/SpriteRenderer.hpp"
#include "../../../include/Graphics/AssetsManager.hpp"


using namespace PancakeEngine;

SpriteRenderer::SpriteRenderer() : isFlip(false) {
    setSprite(AssetsManager::getDefaultSpriteSheet(), 0, 0);
}

void SpriteRenderer::setSprite(SpriteSheet &sheet, unsigned i, unsigned j) {
    sprite = sheet.getSprite(i, j);
}

void SpriteRenderer::flip(bool b) {
    isFlip = b;
    if (isFlip) sprite.setScale(-1, 1);
    else sprite.setScale(1, 1);
}

void SpriteRenderer::setPosition(sf::Vector2f position) {
    sprite.move(position);
}

const sf::Sprite SpriteRenderer::getSprite() const {
    return sprite;
}
