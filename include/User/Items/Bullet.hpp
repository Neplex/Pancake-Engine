//
// Created by Darenn on 15/03/2017.
//

#ifndef PANCAKE_BULLETOBJECT_HPP
#define PANCAKE_BULLETOBJECT_HPP

#include <GameLogic.hpp>
#include <User/Behaviors/BulletScript.hpp>

class Bullet : public PancakeEngine::GameObject {
 public:
  virtual ~Bullet() = default;

  Bullet() {
    name = "Bullet";
    addComponent<PancakeEngine::Rigidbody>();  // todo problem if put after
                                               // colliders
    auto &cc = addComponent<PancakeEngine::CircleCollider>();
    cc.radius = 4;
    cc.isTrigger = true;
    addComponent<BulletScript>();

    auto &cc1 = addComponent<PancakeEngine::CircleCollider>();
    cc1.radius = 4;

    addComponent<PancakeEngine::SpriteRenderer>().setSprite(PancakeEngine::AssetsManager::getSpriteSheet("miscs"), 7,
                                                            0);
  }
};

#endif  // PANCAKE_BULLETOBJECT_HPP
