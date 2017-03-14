//
// Created by nicolas on 14/03/17.
//

#ifndef PANCAKE_LADDER_HPP
#define PANCAKE_LADDER_HPP

#include <GameLogic/GameObject.hpp>
#include <User/Behaviors/LadderScript.hpp>

namespace PancakeEngine {
    class Ladder : public GameObject {
    public:
        Ladder() {
            addComponent<LadderScript>();
            BoxCollider& bc = addComponent<BoxCollider>();
            bc.width = 70;
            bc.height = 70*4;
            bc.isTrigger = true;
        }
    };
}

#endif //PANCAKE_LADDER_HPP
