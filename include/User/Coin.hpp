//
// Created by Darenn on 10/02/2017.
//

#ifndef PANCAKE_COIN_HPP
#define PANCAKE_COIN_HPP

#include <GameLogic.hpp>
#include <Graphics.hpp>
#include <User/Behaviors/OnTriggerDestroy.hpp>

namespace PancakeEngine {

    class Coin : public GameObject {
    public:
        Coin() {
            name = "Coin";

            CircleCollider& cc = addComponent<CircleCollider>();
            addComponent<Rigidbody>().setType(Rigidbody::bodyType::kinematicBody);
            cc.radius = 20;
            cc.isTrigger = true;
            addComponent<OnTriggerDestroy>().target = "player1";

            addComponent<SpriteRenderer>().setSprite(
                    AssetsManager::getSpriteSheet("items"), 2, 3
            );
        }
    };
}

#endif //PANCAKE_COIN_HPP
