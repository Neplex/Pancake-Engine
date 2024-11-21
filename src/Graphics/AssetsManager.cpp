//
// Created by nicolas on 31/01/17.
//

#include <Graphics.hpp>

using namespace PancakeEngine;

std::map<std::string, SpriteSheet> AssetsManager::spriteSheets;
std::map<std::string, Animation> AssetsManager::animations;
std::map<std::string, TileMap> AssetsManager::tileMaps;

SpriteSheet AssetsManager::defaultSpriteSheet = SpriteSheet("../resources/default.png", 32, 32);
Animation AssetsManager::defaultAnimation = Animation(defaultSpriteSheet);
TileMap AssetsManager::defaultTileMap = TileMap(defaultSpriteSheet.tile_height, defaultSpriteSheet.tile_width, 1, 1);

AssetsManager::AssetsManager() = default;

SpriteSheet &AssetsManager::createSpriteSheet(const std::string &name, const std::string &uri, unsigned int tile_w,
                                              unsigned int tile_h, unsigned int margin) {
  if (spriteSheets.find(name) == spriteSheets.end())
    spriteSheets.emplace(name, SpriteSheet(uri, tile_w, tile_h, margin));
  return spriteSheets.at(name);
}

SpriteSheet &AssetsManager::getSpriteSheet(const std::string &name) {
  if (spriteSheets.find(name) != spriteSheets.end()) return spriteSheets.at(name);
  return getDefaultSpriteSheet();
}

SpriteSheet &AssetsManager::getDefaultSpriteSheet() { return defaultSpriteSheet; }

Animation &AssetsManager::createAnimation(const std::string &name, const std::string &spriteSheetName) {
  return createAnimation(name, spriteSheets.at(spriteSheetName));
}

Animation &AssetsManager::createAnimation(const std::string &name, const SpriteSheet &spriteSheet) {
  if (animations.find(name) == animations.end()) animations.emplace(name, Animation(spriteSheet));
  return animations.at(name);
}

Animation &AssetsManager::getAnimation(const std::string &name) {
  if (animations.find(name) != animations.end()) return animations.at(name);
  return getDefaultAnimation();
}

Animation &AssetsManager::getDefaultAnimation() { return defaultAnimation; }

TileMap &AssetsManager::createTileMap(const std::string &name, const unsigned tile_width, const unsigned tile_height,
                                      const unsigned width, const unsigned height) {
  if (tileMaps.find(name) == tileMaps.end()) tileMaps.emplace(name, TileMap(tile_width, tile_height, width, height));
  return tileMaps.at(name);
}

TileMap &AssetsManager::getTileMap(const std::string &name) {
  if (tileMaps.find(name) != tileMaps.end()) return tileMaps.at(name);

  return getDefaultTileMap();
}

TileMap &AssetsManager::getDefaultTileMap() { return defaultTileMap; }
