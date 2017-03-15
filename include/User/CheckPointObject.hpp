//
// Created by Darenn on 15/03/2017.
//

#ifndef PANCAKE_CHECKPOINTOBJECT_HPP
#define PANCAKE_CHECKPOINTOBJECT_HPP

#include <GameLogic.hpp>
#include <User/Behaviors/CheckPoint.hpp>

class CheckPointObject : public PancakeEngine::GameObject {
public:
    CheckPointObject() {
        addComponent<CheckPoint>();
        PancakeEngine::BoxCollider& bc = addComponent<PancakeEngine::BoxCollider>();
        bc.width = 60;
        bc.height = 70;
        bc.isTrigger = true;
    }
};

#endif //PANCAKE_CHECKPOINTOBJECT_HPP
