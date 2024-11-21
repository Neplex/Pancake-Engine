//
// Created by virgil on 14/03/17.
//

#ifndef PANCAKE_TRAMPOLINESCRIPT_HPP
#define PANCAKE_TRAMPOLINESCRIPT_HPP

#include <GameLogic.hpp>

class TrampolineScript : public PancakeEngine::Behavior {
 public:
  void OnCollisionEnter(const PancakeEngine::Collision &collision) override {
    PancakeEngine::SpriteSheet &ss = PancakeEngine::AssetsManager::getSpriteSheet("items");
    gameObject->getComponent<PancakeEngine::SpriteRenderer>()->setSprite(ss, 0, 5);
  };
  void OnCollisionExit(const PancakeEngine::Collision &collision) override {
    PancakeEngine::SpriteSheet &ss = PancakeEngine::AssetsManager::getSpriteSheet("items");
    gameObject->getComponent<PancakeEngine::SpriteRenderer>()->setSprite(ss, 0, 6);
  };
};
#endif  // PANCAKE_TRAMPOLINESCRIPT_HPP
