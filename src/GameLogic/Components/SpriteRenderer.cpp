//
// Created by nicolas on 19/01/17.
//

#include <GameLogic/Components/SpriteRenderer.hpp>
#include <Graphics/AssetsManager.hpp>

using namespace PancakeEngine;

SpriteRenderer::SpriteRenderer() : isFlip(false) { setSprite(AssetsManager::getDefaultSpriteSheet(), 0, 0); }

void SpriteRenderer::setSprite(SpriteSheet &sheet, const unsigned i, const unsigned j) {
  const sf::Vector2f pos = sprite.getPosition();
  const float rotation = sprite.getRotation();
  sprite = sheet.getSprite(i, j);
  sprite.setPosition(pos);
  sprite.setRotation(rotation);
}

void SpriteRenderer::flip(const bool b) {
  isFlip = b;
  if (isFlip) {
    sprite.setScale(-1, 1);
  } else {
    sprite.setScale(1, 1);
  }
}

void SpriteRenderer::setPosition(const sf::Vector2f position) { sprite.move(position); }

sf::Sprite SpriteRenderer::getSprite() const { return sprite; }

void SpriteRenderer::setRotation(const float r) { sprite.setRotation(r); }

void SpriteRenderer::setScale(const sf::Vector2f scale) { sprite.setScale(scale); }