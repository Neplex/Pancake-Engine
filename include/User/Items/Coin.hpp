//
// Created by Darenn on 10/02/2017.
//

#ifndef PANCAKE_COIN_HPP
#define PANCAKE_COIN_HPP

#include <GameLogic.hpp>
#include <Graphics.hpp>
#include <User/Behaviors/OnTriggerDestroy.hpp>
#include <User/Behaviors/GameController.hpp>

class CoinScript : public PancakeEngine::Behavior {
public:
    void OnTriggerEnter(const PancakeEngine::Collider &triggered, const PancakeEngine::Collider &other) override {
        std::string oname = other.gameObject->name;
        if (oname == "player1" || oname == "player2" || oname == "player3" || oname == "player4" || oname == "player5") {
            PancakeEngine::SceneManager::findByName("GameController")->getComponent<GameController>()->coins++;
            destroy(*gameObject);
        }
    }
};

class Coin : public PancakeEngine::GameObject {
public:
    Coin() {
        name = "Coin";
        addComponent<PancakeEngine::Rigidbody>().setType(PancakeEngine::Rigidbody::bodyType::kinematicBody);
        PancakeEngine::CircleCollider& cc = addComponent<PancakeEngine::CircleCollider>();
        cc.radius = 20;
        cc.isTrigger = true;
        addComponent<CoinScript>();
        addComponent<PancakeEngine::SpriteRenderer>().setSprite(PancakeEngine::AssetsManager::getSpriteSheet("items"), 2, 3);
    }
};

#endif //PANCAKE_COIN_HPP
