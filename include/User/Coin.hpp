//
// Created by Darenn on 10/02/2017.
//

#ifndef PANCAKE_COIN_HPP
#define PANCAKE_COIN_HPP

#include <GameLogic/Components/CircleCollider.hpp>
#include "GameLogic/GameObject.hpp"

namespace PancakeEngine {

    class Coin : public GameObject {
    public:
        Coin()
        {
            name = "Coin";
            addComponent<Rigidbody>();
            addComponent<CircleCollider>().radius = 50;
            transform.setPosition(sf::Vector2f(200,-500));
        }
    };
}

#endif //PANCAKE_COIN_HPP
