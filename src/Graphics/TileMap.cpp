//
// Created by nicolas on 22/02/17.
//

#include <Graphics/TileMap.hpp>
#include <cassert>

using namespace PancakeEngine;

TileMap::TileMap(const unsigned tile_width, const unsigned tile_height, const unsigned width, const unsigned height)
    : tile_width(tile_width), tile_height(tile_height), width(width), height(height) {}

void TileMap::addTile(SpriteSheet &sheet, const unsigned i, const unsigned j, const unsigned x, const unsigned y) {
  assert(x < width && y < height);  ///< The position is out of the map
  Tile tile{};
  tile.sheet = &sheet;
  tile.i = i;
  tile.j = j;
  tile.x = x;
  tile.y = y;
  map.push_back(tile);
}