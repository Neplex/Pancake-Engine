//
// Created by nicolas on 31/01/17.
//

#include "../../include/Graphics/AssetsManager.hpp"

using namespace PancakeEngine;

std::map<std::string, SpriteSheet> AssetsManager::spriteSheets;
std::map<std::string, Animation> AssetsManager::animations;

SpriteSheet AssetsManager::defaultSpriteSheet = SpriteSheet("../resources/default.png", 32, 32);
Animation AssetsManager::defaultAnimation = Animation(defaultSpriteSheet);

AssetsManager::AssetsManager() {}

SpriteSheet& AssetsManager::createSpriteSheet(std::string name, std::string uri, unsigned int tile_w, unsigned int tile_h, unsigned int margin) {
    if (spriteSheets.find(name) == spriteSheets.end())
        spriteSheets.emplace(name, SpriteSheet(uri, tile_w, tile_h, margin));
    return spriteSheets.at(name);
}

SpriteSheet& AssetsManager::getSpriteSheet(std::string name) {
    if (spriteSheets.find(name) != spriteSheets.end())
        return spriteSheets.at(name);
    else
        return getDefaultSpriteSheet();
}

SpriteSheet &AssetsManager::getDefaultSpriteSheet() {
    return defaultSpriteSheet;
}

Animation& AssetsManager::createAnimation(std::string name, std::string spriteSheetName) {
    return createAnimation(name, spriteSheets.at(spriteSheetName));
}

Animation& AssetsManager::createAnimation(std::string name, SpriteSheet &spriteSheet) {
    if (animations.find(name) == animations.end())
        animations.emplace(name, Animation(spriteSheet));
    return animations.at(name);
}

Animation& AssetsManager::getAnimation(std::string name) {
    if (animations.find(name) != animations.end())
        return animations.at(name);
    else
        return getDefaultAnimation();
}

Animation &AssetsManager::getDefaultAnimation() {
    return defaultAnimation;
}