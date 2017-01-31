//
// Created by nicolas on 25/01/17.
//

#ifndef PANCAKE_SPRITESHEET_HPP
#define PANCAKE_SPRITESHEET_HPP


#include <SFML/Graphics/Texture.hpp>

namespace PancakeEngine {

    class SpriteSheet {
    public:
        /**
         * Create a SpriteSheet from image 'uri'
         * @param uri the link to the image
         * @param tile_w the tile width
         * @param tile_h the tile height
         */
        SpriteSheet(std::string uri, unsigned int tile_w, unsigned int tile_h) : tile_width(tile_w), tile_height(tile_h) {
            if (!texture.loadFromFile(uri)) exit(EXIT_FAILURE);
            texture.setSmooth(true);
        }

    private:
        friend class Animation;

        friend class AnimationRenderer;

        friend class SpriteRenderer;

        sf::Texture texture;
        unsigned int tile_width;
        unsigned int tile_height;
    };
}

#endif //PANCAKE_SPRITESHEET_HPP
