//
// Created by virgil on 18/03/17.
//

#ifndef PANCAKE_EXITNOTICE_HPP
#define PANCAKE_EXITNOTICE_HPP

#include <GameLogic.hpp>
#include <User/Behaviors/ExitNoticeScript.hpp>

class ExitNotice : public PancakeEngine::GameObject {
 public:
  virtual ~ExitNotice() = default;

  ExitNotice() {
    name = "ExitNotice";
    addComponent<PancakeEngine::Rigidbody>().setFreezeRotation(true);
    auto &ground = addComponent<PancakeEngine::BoxCollider>();
    ground.width = 70;
    ground.height = 2;
    ground.offset = sf::Vector2f(0, 50);

    auto &bc = addComponent<PancakeEngine::BoxCollider>();
    bc.width = 70;
    bc.height = 67;
    bc.offset = sf::Vector2f(0, -2);
    bc.isTrigger = true;
    addComponent<PancakeEngine::SpriteRenderer>().setSprite(PancakeEngine::AssetsManager::getSpriteSheet("tiles"), 4,
                                                            16);
    addComponent<ExitNoticeScript>();
  }
};
#endif  // PANCAKE_EXITNOTICE_HPP
