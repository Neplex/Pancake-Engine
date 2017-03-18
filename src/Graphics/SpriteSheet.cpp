//
// Created by nicolas on 18/03/17.
//

#include <Graphics/SpriteSheet.hpp>

using namespace PancakeEngine;

SpriteSheet::SpriteSheet(std::string uri, unsigned int tile_w, unsigned int tile_h, unsigned int m) : tile_width(tile_w), tile_height(tile_h), margin(m) {
    if (!texture.loadFromFile(uri)) exit(EXIT_FAILURE);
    texture.setSmooth(true);
}

sf::Sprite SpriteSheet::getSprite(unsigned i, unsigned j, bool flip) {
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setTextureRect(getRect(i, j, flip));
    sprite.setOrigin(tile_width / 2, tile_height / 2);
    return sprite;
}

sf::IntRect SpriteSheet::getRect(unsigned i, unsigned j, bool flip) {
    if (!flip) return sf::IntRect(
                (tile_width  + margin) * i,
                (tile_height + margin) * j,
                tile_width,
                tile_height
        );
    else return sf::IntRect(
                (tile_width  + margin) * (i+1),
                (tile_height + margin) * j,
                -tile_width,
                tile_height
        );
}