//
// Created by nicolas on 15/03/17.
//

#ifndef PANCAKE_ONAWAKESETBOXCOLLIDER_HPP
#define PANCAKE_ONAWAKESETBOXCOLLIDER_HPP

#include <GameLogic/GameObject.hpp>
#include <GameLogic/Components/Behavior.hpp>
#include <GameLogic/Components/BoxCollider.hpp>
#include <GameLogic/Components/DataStorage.hpp>

class OnAwakeSetBoxCollider : public PancakeEngine::Behavior {

    void awake() override {
        PancakeEngine::BoxCollider& bc = gameObject->addComponent<PancakeEngine::BoxCollider>();
        PancakeEngine::DataStorage* ds = gameObject->getComponent<PancakeEngine::DataStorage>();
        bc.width  = ds->get<int>("width");
        bc.height = ds->get<int>("height");
        bc.isTrigger = true;
    }

};


#endif //PANCAKE_ONAWAKESETBOXCOLLIDER_HPP
