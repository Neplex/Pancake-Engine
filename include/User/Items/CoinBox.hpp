//
// Created by nicolas on 18/03/17.
//

#ifndef PANCAKE_COINBOX_HPP
#define PANCAKE_COINBOX_HPP


#include <GameLogic/GameObject.hpp>
#include <GameLogic/Components/BoxCollider.hpp>
#include <SceneManager.hpp>
#include <User/Behaviors/GameController.hpp>

class CoinBoxScript : public PancakeEngine::Behavior {
public:
    void update() override {
        if (coin == 0) gameObject->getComponent<PancakeEngine::SpriteRenderer>()->setSprite(PancakeEngine::AssetsManager::getSpriteSheet("tiles"), 2, 0);
    }

    void OnTriggerEnter(const PancakeEngine::Collider &triggered, const PancakeEngine::Collider &other) override {
        std::string oname = other.gameObject->name;
        if ((oname == "player1" || oname == "player2" || oname == "player3" || oname == "player4" || oname == "player5") && coin > 0) {
            PancakeEngine::SceneManager::findByName("GameController")->getComponent<GameController>()->coins++;
            coin--;
        }
    }

private:
    unsigned coin = 3;
};

class CoinBox : public PancakeEngine::GameObject {
public:
    CoinBox() {
        PancakeEngine::BoxCollider& bc = addComponent<PancakeEngine::BoxCollider>();
        bc.width = bc.height = 70;
        PancakeEngine::BoxCollider& bottom = addComponent<PancakeEngine::BoxCollider>();
        bottom.width = 70;
        bottom.height = 2;
        bottom.offset = sf::Vector2f(0, 35);
        bottom.isTrigger = true;
        addComponent<PancakeEngine::SpriteRenderer>().setSprite(PancakeEngine::AssetsManager::getSpriteSheet("tiles"), 1, 0);
        addComponent<CoinBoxScript>();
    }
};


#endif //PANCAKE_COINBOX_HPP
