//
// Created by Darenn on 15/03/2017.
//

#ifndef PANCAKE_GAMECONTROLLER_HPP
#define PANCAKE_GAMECONTROLLER_HPP

#include <GameLogic.hpp>
#include <User/Health.hpp>

class GameController : public PancakeEngine::Behavior {

public:
    void setLastCheckPoint(PancakeEngine::GameObject* cp, PancakeEngine::GameObject* player) {
        playerToLastCheckPoint[player->name] = cp;
    }

    void playerDie(PancakeEngine::GameObject* p) {
        PancakeEngine::GameObject* lastCheckPoint = playerToLastCheckPoint[p->name];
        p->transform.setPosition(sf::Vector2f(lastCheckPoint->transform.getWorldPosition().x,
                lastCheckPoint->transform.getWorldPosition().y));
        p->getComponent<Health>()->reSpawn();
    }

private:
    std::map<std::string, PancakeEngine::GameObject*> playerToLastCheckPoint;

};

#include <User/Behaviors/CheckPointScript.hpp>

#endif //PANCAKE_GAMECONTROLLER_HPP
