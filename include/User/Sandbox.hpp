//
// Created by nicolas on 15/02/17.
//

#ifndef PANCAKE_SANDBOX_HPP
#define PANCAKE_SANDBOX_HPP

#include <GameLogic.hpp>
#include <User/Ground.hpp>
#include <User/Box.hpp>
#include <User/Coin.hpp>
#include <User/Player.hpp>

namespace PancakeEngine {

    class Sandbox : public Scene {
    public:
        Sandbox() : Scene("Sandbox") {
            SpriteSheet& s = AssetsManager::createSpriteSheet("sprites", "../resources/tiles_spritesheet.png", 70, 70, 2);

            addGameObject<Ground>().transform.setPosition(sf::Vector2f(0, 50));
            addGameObject<Box>();
            addGameObject<Box>();
            addGameObject<Box>();
            addGameObject<Player>();
        }
    };
}

#endif //PANCAKE_SANDBOX_HPP
