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
            addComponent<OnAwakeSetBoxCollider>();
            addComponent<WaterScript>();
        }
    };
}

#endif //PANCAKE_WATER_HPP
