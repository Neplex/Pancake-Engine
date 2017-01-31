//
// Created by nicolas on 25/01/17.
//

#ifndef PANCAKE_ANIMATION_HPP
#define PANCAKE_ANIMATION_HPP

#include <SFML/Graphics/Sprite.hpp>
#include "SpriteSheet.hpp"

namespace PancakeEngine {

    class AssetsManager;
    class Animation {
    public:
        /**
         * Add the sprite at the column i and row j from the SpriteSheet to the animation
         * @param i the column index
         * @param j the row index
         * @param time the duration in millisecond
         */
        void addFrame(unsigned int i, unsigned int j, unsigned int time);

    private:
        friend class AssetsManager;
        friend class AnimationRenderer;

        struct Frame {
            sf::IntRect rect;
            unsigned int time;
        };

        SpriteSheet spriteSheet;
        std::vector<Animation::Frame> frames;

        Animation(SpriteSheet sheet) : spriteSheet(sheet) {}
    };

}
#endif //PANCAKE_ANIMATION_HPP
