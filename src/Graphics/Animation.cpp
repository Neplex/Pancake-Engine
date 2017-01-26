//
// Created by nicolas on 25/01/17.
//

#include "../../include/Graphics/Animation.hpp"

void Animation::addFrame(unsigned int i, unsigned int j, unsigned int time) {
    Frame frame;
    frame.rect = sf::IntRect(
            spriteSheet.tile_width  * i,
            spriteSheet.tile_height * j,
            spriteSheet.tile_width,
            spriteSheet.tile_height
    );
    frame.time = time;
    frames.push_back(frame);
}