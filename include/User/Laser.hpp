//
// Created by nicolas on 15/03/17.
//

#ifndef PANCAKE_LASER_HPP
#define PANCAKE_LASER_HPP

#include <User/Behaviors/LaserScript.hpp>
#include <User/Behaviors/OnTriggerKill.hpp>
#include <GameLogic/GameObject.hpp>

class Laser : public PancakeEngine::GameObject {
public:
    Laser() {
        addComponent<LaserScript>();
        addComponent<OnTriggerKill>();
    }
};


#endif //PANCAKE_LASER_HPP
