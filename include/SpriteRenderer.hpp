//
// Created by Darenn on 17/01/2017.
//

#ifndef PANCAKE_SPRITERENDERER_HPP
#define PANCAKE_SPRITERENDERER_HPP

#include "Component.hpp"
#include <SFML/Graphics.hpp>


class SpriteRenderer : public Component {
public:
    sf::Sprite sprite;

    /**
     * Create sprite with default texture
     * @param width
     * @param height
     */
    SpriteRenderer(unsigned int width, unsigned int height);
};

#endif //PANCAKE_SPRITERENDERER_HPP
