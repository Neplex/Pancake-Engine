//
// Created by nicolas on 25/01/17.
//

#include "../include/SpriteSheet.hpp"

SpriteSheet::SpriteSheet(std::string uri, int tile_w, int tile_h) : tile_width(tile_w), tile_height(tile_h) {
    if (!texture.loadFromFile(uri)) {
        exit(EXIT_FAILURE);
    }
    texture.setSmooth(true);
}