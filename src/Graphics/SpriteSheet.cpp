//
// Created by nicolas on 18/03/17.
//

#include <Graphics/SpriteSheet.hpp>

using namespace PancakeEngine;

SpriteSheet::SpriteSheet(const std::string &uri, const unsigned int tile_w, const unsigned int tile_h,
                         const unsigned int m)
    : tile_width(tile_w), tile_height(tile_h), margin(m) {
  if (!texture.loadFromFile(uri)) exit(EXIT_FAILURE);
  texture.setSmooth(true);
}

sf::Sprite SpriteSheet::getSprite(const unsigned i, const unsigned j, const bool flip) const {
  sf::Sprite sprite;
  sprite.setTexture(texture);
  sprite.setTextureRect(getRect(i, j, flip));
  sprite.setOrigin(tile_width / 2, tile_height / 2);
  return sprite;
}

sf::IntRect SpriteSheet::getRect(const unsigned i, const unsigned j, const bool flip) const {
  if (flip) return {(tile_width + margin) * (i + 1), (tile_height + margin) * j, -tile_width, tile_height};

  return {(tile_width + margin) * i, (tile_height + margin) * j, tile_width, tile_height};
}
