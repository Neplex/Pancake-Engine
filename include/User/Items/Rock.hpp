//
// Created by nicolas on 13/03/17.
//

#ifndef PANCAKE_ROCK_HPP
#define PANCAKE_ROCK_HPP

#include <GameLogic/GameObject.hpp>
#include <GameLogic/Components/CircleCollider.hpp>
#include <GameLogic/Components/SpriteRenderer.hpp>
#include <Graphics/AssetsManager.hpp>
#include <User/Behaviors/CheckPoint.hpp>

namespace PancakeEngine {
    class Rock : public GameObject {
    public:
        Rock() {
            name = "Rock";

            Rigidbody& rb = addComponent<Rigidbody>();
            CircleCollider& cc = addComponent<CircleCollider>();
            cc.radius = 35;

            addComponent<SpriteRenderer>().setSprite(
                    AssetsManager::getSpriteSheet("miscs"), 13, 3
            );
        }
    };

    class SmallRock : public GameObject {
    public:
        SmallRock() {
            name = "Rock";

            Rigidbody& rb = addComponent<Rigidbody>();
            CircleCollider& cc = addComponent<CircleCollider>();
            cc.radius = 15;
            addComponent<CheckPoint>();

            addComponent<SpriteRenderer>().setSprite(
                    AssetsManager::getSpriteSheet("miscs"), 13, 4
            );
        }
    };
}

#endif //PANCAKE_ROCK_HPP
