//
// Created by nicolas on 25/01/17.
//

#ifndef PANCAKE_ANIMATION_HPP
#define PANCAKE_ANIMATION_HPP

#include <SFML/Graphics/Sprite.hpp>
#include "SpriteSheet.hpp"

struct Frame {
    sf::IntRect rect;
    unsigned int time;
};

class Animation {
public:
    Animation(SpriteSheet& sheet) : spriteSheet(sheet) {}

    /**
     * Add the sprite at the column i and row j from the SpriteSheet to the animation
     * @param i the column index
     * @param j the row index
     * @param time the duration in millisecond
     */
    void addFrame(unsigned int i, unsigned int j, unsigned int time);

private:
    friend class AnimationRenderer;

    SpriteSheet spriteSheet;
    std::vector<Frame> frames;
};


#endif //PANCAKE_ANIMATION_HPP
