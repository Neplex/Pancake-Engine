//
// Created by nicolas on 14/03/17.
//

#ifndef PANCAKE_LADDER_HPP
#define PANCAKE_LADDER_HPP

#include <GameLogic/GameObject.hpp>
#include <User/Behaviors/LadderScript.hpp>
#include <User/Behaviors/OnAwakeSetBoxCollider.hpp>

    class Ladder : public PancakeEngine::GameObject {
    public:
        Ladder() {
            addComponent<OnAwakeSetBoxCollider>();
            addComponent<LadderScript>();
        }
    };


#endif //PANCAKE_LADDER_HPP
