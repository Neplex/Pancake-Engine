//
// Created by nicolas on 31/01/17.
//

#ifndef PANCAKE_ASSETMANAGER_HPP
#define PANCAKE_ASSETMANAGER_HPP


#include <map>
#include "SpriteSheet.hpp"
#include "Animation.hpp"

namespace PancakeEngine {
    class AssetsManager {
    public:
        static SpriteSheet& createSpriteSheet(std::string name, std::string uri, unsigned int tile_w, unsigned int tile_h);
        static SpriteSheet& getSpriteSheet(std::string name);

        static Animation& createAnimation(std::string name, std::string spriteSheetName);
        static Animation& createAnimation(std::string name, SpriteSheet& spriteSheet);
        static Animation& getAnimation(std::string name);

    private:
        static std::map<std::string, SpriteSheet> spriteSheets;
        static std::map<std::string, Animation> animations;

        AssetsManager();
    };
}

#endif //PANCAKE_ASSETMANAGER_HPP
