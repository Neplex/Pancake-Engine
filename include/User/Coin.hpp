//
// Created by Darenn on 10/02/2017.
//

#ifndef PANCAKE_COIN_HPP
#define PANCAKE_COIN_HPP

#include <GameLogic/Components/CircleCollider.hpp>
#include <User/Behaviors/OnTriggerDestroy.hpp>
#include "GameLogic/GameObject.hpp"

namespace PancakeEngine {

    class Coin : public GameObject {
    public:
        Coin()
        {
            name = "Coin";
            CircleCollider& cc = addComponent<CircleCollider>();
            cc.radius = 20;
            cc.isTrigger = true;
            addComponent<OnTriggerDestroy>();
        }
    };
}

#endif //PANCAKE_COIN_HPP
