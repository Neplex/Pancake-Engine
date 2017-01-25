//
// Created by nicolas on 25/01/17.
//

#ifndef PANCAKE_SPRITESHEET_HPP
#define PANCAKE_SPRITESHEET_HPP


#include <SFML/Graphics/Texture.hpp>
#include "SpriteRenderer.hpp"

class SpriteSheet {
public:
    /**
     * Create a SpriteSheet from image 'uri'
     * @param uri the link to the image
     * @param tile_w the tile width
     * @param tile_h the tile height
     */
    SpriteSheet(std::string uri, int tile_w, int tile_h);

private:
    friend class SpriteRenderer;

    sf::Texture texture;
    int tile_width;
    int tile_height;
};


#endif //PANCAKE_SPRITESHEET_HPP
