//
// Created by nicolas on 14/03/17.
//

#ifndef PANCAKE_WATER_HPP
#define PANCAKE_WATER_HPP


#include <GameLogic/GameObject.hpp>
#include <GameLogic/Components/BoxCollider.hpp>
#include <User/Behaviors/WaterScript.hpp>

namespace PancakeEngine {
    class Water : public GameObject {
    public:
        Water() {
            addComponent<WaterScript>();
            BoxCollider &bc = addComponent<BoxCollider>();
            bc.width = 70*10;
            bc.height = 70*2;
            bc.offset = sf::Vector2f(0, 35);
            bc.isTrigger = true;
        }
    };
}

#endif //PANCAKE_WATER_HPP
