//
// Created by nicolas on 23/02/17.
//

#ifndef PANCAKE_RENDERER_HPP
#define PANCAKE_RENDERER_HPP

#include <GameLogic/Components/Component.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace PancakeEngine {
    class Renderer : public Component {
    protected:
        friend class Window;
        sf::Sprite sprite;
    };
}

#endif //PANCAKE_RENDERER_HPP
