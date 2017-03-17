//
// Created by nicolas on 13/03/17.
//

#ifndef PANCAKE_ROCK_HPP
#define PANCAKE_ROCK_HPP

#include <GameLogic/GameObject.hpp>
#include <GameLogic/Components/CircleCollider.hpp>
#include <GameLogic/Components/SpriteRenderer.hpp>
#include <Graphics/AssetsManager.hpp>
#include <User/Behaviors/CheckPointScript.hpp>

    class Rock : public PancakeEngine::GameObject {
    public:
        Rock() {
            name = "Rock";

            PancakeEngine::Rigidbody& rb = addComponent<PancakeEngine::Rigidbody>();
            PancakeEngine::CircleCollider& cc = addComponent<PancakeEngine::CircleCollider>();
            cc.radius = 35;

            addComponent<PancakeEngine::SpriteRenderer>().setSprite(
                    PancakeEngine::AssetsManager::getSpriteSheet("miscs"), 13, 3
            );
        }
    };

    class SmallRock : public PancakeEngine::GameObject {
    public:
        SmallRock() {
            name = "Rock";

            PancakeEngine::Rigidbody& rb = addComponent<PancakeEngine::Rigidbody>();
            PancakeEngine::CircleCollider& cc = addComponent<PancakeEngine::CircleCollider>();
            cc.radius = 15;
            addComponent<CheckPointScript>();

            addComponent<PancakeEngine::SpriteRenderer>().setSprite(
                    PancakeEngine::AssetsManager::getSpriteSheet("miscs"), 13, 4
            );
        }
    };


#endif //PANCAKE_ROCK_HPP
