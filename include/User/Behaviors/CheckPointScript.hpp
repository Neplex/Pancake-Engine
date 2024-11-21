//
// Created by Darenn on 15/03/2017.
//

#ifndef PANCAKE_CHECKPOINT_HPP
#define PANCAKE_CHECKPOINT_HPP

#include <GameLogic.hpp>
#include <User/Behaviors/GameController.hpp>
#include <User/Behaviors/PlayerController.hpp>

class CheckPointScript : public PancakeEngine::Behavior {
 public:
  void awake() override {
    gc = PancakeEngine::SceneManager::findByName("GameController")->getComponent<GameController>();
  }

  void OnTriggerEnter(const PancakeEngine::Collider &triggered, const PancakeEngine::Collider &other) override {
    if (other.gameObject->getComponent<PlayerController>()) {
      gc->setLastCheckPoint(gameObject, other.gameObject);
    }

    PancakeEngine::GameObject *go = triggered.gameObject;
    PancakeEngine::SpriteSheet &ss = PancakeEngine::AssetsManager::getSpriteSheet("items");

    if (go->name == "CheckPoint1") {
      go->getComponent<PancakeEngine::SpriteRenderer>()->setSprite(ss, 6, 2);
    } else if (go->name == "CheckPoint2") {
      go->getComponent<PancakeEngine::SpriteRenderer>()->setSprite(ss, 6, 1);
    } else if (go->name == "CheckPoint3") {
      go->getComponent<PancakeEngine::SpriteRenderer>()->setSprite(ss, 6, 3);
    } else if (go->name == "CheckPoint4") {
      go->getComponent<PancakeEngine::SpriteRenderer>()->setSprite(ss, 6, 4);
    }
  }

 private:
  GameController *gc{};
};

#endif  // PANCAKE_CHECKPOINT_HPP
