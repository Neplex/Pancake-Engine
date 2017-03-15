//
// Created by Darenn on 15/03/2017.
//

#ifndef PANCAKE_CHECKPOINT_HPP
#define PANCAKE_CHECKPOINT_HPP

#include <GameLogic.hpp>
#include "GameController.hpp"
#include "PlayerController.hpp"

class CheckPoint : public PancakeEngine::Behavior {

public:
    void awake() override {
        gc = PancakeEngine::SceneManager::findByName("GameController")->getComponent<GameController>();
    }

    void OnTriggerEnter(const PancakeEngine::Collider& triggered, const PancakeEngine::Collider& other) override
    {
        if (other.gameObject->getComponent<PlayerController>()) {
            gc->setLastCheckPoint(gameObject);
        }
    }

private:
    GameController* gc;
};

#endif //PANCAKE_CHECKPOINT_HPP
