//
// Created by nicolas on 22/02/17.
//

#include <Graphics/TileMap.hpp>

using namespace PancakeEngine;

TileMap::TileMap(unsigned tile_w, unsigned tile_h, unsigned w, unsigned h) : tile_width(tile_w), tile_height(tile_h), width(w), height(h), map() {}

void TileMap::addTile(SpriteSheet &sheet, unsigned i, unsigned j, unsigned x, unsigned y) {
    Tile tile;
    tile.sheet = &sheet;
    tile.i = i; tile.j = j;
    tile.x = x; tile.y = y;
    map.push_back(tile);
}