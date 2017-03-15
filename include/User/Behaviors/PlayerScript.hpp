//
// Created by Darenn on 15/03/2017.
//

#ifndef PANCAKE_PLAYERSCRIPT_HPP
#define PANCAKE_PLAYERSCRIPT_HPP

#include <GameLogic.hpp>
#include <User/Health.hpp>
#include "GameController.hpp"

class PlayerScript : public PancakeEngine::Behavior {
public:
    void awake() override
    {
        gc = PancakeEngine::SceneManager::findByName("GameController")->getComponent<GameController>();
        h = gameObject->getComponent<Health>();
    }

    void update() override
    {
        if (h->isDead()) {
            gc->playerDie(gameObject);
        }
    }

private:
    GameController* gc;
    Health* h;
};

#endif //PANCAKE_PLAYERSCRIPT_HPP
