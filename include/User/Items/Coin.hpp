//
// Created by Darenn on 10/02/2017.
//

#ifndef PANCAKE_COIN_HPP
#define PANCAKE_COIN_HPP

#include <GameLogic.hpp>
#include <Graphics.hpp>
#include <User/Behaviors/OnTriggerDestroy.hpp>


    class Coin : public PancakeEngine::GameObject {
    public:
        Coin() {
            name = "Coin";
            addComponent<PancakeEngine::Rigidbody>().setType(PancakeEngine::Rigidbody::bodyType::kinematicBody);
            PancakeEngine::CircleCollider& cc = addComponent<PancakeEngine::CircleCollider>();

            cc.radius = 20;
            cc.isTrigger = true;
            addComponent<OnTriggerDestroy>().target = "player1";

            addComponent<PancakeEngine::SpriteRenderer>().setSprite(
                    PancakeEngine::AssetsManager::getSpriteSheet("items"), 2, 3
            );
        }
    };

#endif //PANCAKE_COIN_HPP
