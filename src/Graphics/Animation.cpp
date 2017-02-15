//
// Created by nicolas on 25/01/17.
//

#include "../../include/Graphics/Animation.hpp"

using namespace PancakeEngine;

void Animation::addFrame(unsigned int i, unsigned int j, unsigned int time, bool flip) {
    Frame frame;
    if (!flip)
        frame.rect = sf::IntRect(
                spriteSheet.tile_width  * i,
                spriteSheet.tile_height * j,
                spriteSheet.tile_width,
                spriteSheet.tile_height
        );
    else
        frame.rect = sf::IntRect(
                spriteSheet.tile_width  * (i+1),
                spriteSheet.tile_height * j,
               -spriteSheet.tile_width,
                spriteSheet.tile_height
        );
    frame.time = time;
    frames.push_back(frame);
}
