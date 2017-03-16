//
// Created by Darenn on 15/03/2017.
//

#ifndef PANCAKE_GAMECONTROLLER_HPP
#define PANCAKE_GAMECONTROLLER_HPP

#include <GameLogic.hpp>
#include <User/Health.hpp>

class GameController : public PancakeEngine::Behavior {

public:
    void setLastCheckPoint(PancakeEngine::GameObject* cp) {
        lastCheckPoint = cp;
    }

    void playerDie(PancakeEngine::GameObject* p) {
        p->transform.setPosition(sf::Vector2f(lastCheckPoint->transform.getWorldPosition().x,lastCheckPoint->transform.getWorldPosition().y));
        p->getComponent<Health>()->reSpawn();
    }

private:
    PancakeEngine::GameObject* lastCheckPoint;

};

#include <User/Behaviors/CheckPoint.hpp>

#endif //PANCAKE_GAMECONTROLLER_HPP
