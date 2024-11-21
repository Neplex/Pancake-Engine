//
// Created by virgil on 16/03/17.
//

#ifndef PANCAKE_ENNEMIES_HPP
#define PANCAKE_ENNEMIES_HPP

#include <GameLogic.hpp>
#include <User/Behaviors/enemyScript.hpp>
#include <utility>

constexpr unsigned int ANIMATION_SPEED = 150;

class Enemy : public PancakeEngine::GameObject {
 public:
  virtual ~Enemy() = default;

  static std::string handler1(PancakeEngine::GameObject const &go) {
    sf::Vector2f velocity = go.getComponent<PancakeEngine::Rigidbody>()->getVelocity();
    auto *ar = go.getComponent<PancakeEngine::Animator>();

    if (velocity.x > .1) {
      ar->flip(true);
    } else if (velocity.x < -.1) {
      ar->flip(false);
    }
    if (velocity.x < -.1 || velocity.x > .1) {
      return "walk";
    }
    return "idle";
  }
  explicit Enemy(std::string n) {
    name = std::move(n);
    auto &rb = addComponent<PancakeEngine::Rigidbody>();
    rb.setFreezeRotation(true);
    auto &bc = addComponent<PancakeEngine::BoxCollider>();
    bc.width = 57;
    bc.height = 2;
    bc.offset.y = 14;
    auto &bc2 = addComponent<PancakeEngine::BoxCollider>();
    bc2.width = 55;
    bc2.height = 30;
    bc2.offset.y = -2;
    bc2.isTrigger = true;
    PancakeEngine::SpriteSheet &sprites = PancakeEngine::AssetsManager::getSpriteSheet(name);

    PancakeEngine::Animation &a_idle = PancakeEngine::AssetsManager::createAnimation(name + "r_idle", sprites);
    a_idle.addFrame(0, 0, ANIMATION_SPEED);
    PancakeEngine::Animation &a_walk = PancakeEngine::AssetsManager::createAnimation(name + "_walk", sprites);
    a_walk.addFrame(0, 0, ANIMATION_SPEED);
    a_walk.addFrame(1, 0, ANIMATION_SPEED);
    a_walk.addFrame(0, 0, ANIMATION_SPEED);
    PancakeEngine::Animation &a_die = PancakeEngine::AssetsManager::createAnimation(name + "_die", sprites);
    a_die.addFrame(0, 1, ANIMATION_SPEED);
    addComponent<EnemyScript>();

    auto &ar = addComponent<PancakeEngine::Animator>();
    ar.addAnimation("idle", a_idle, handler1);
    ar.addAnimation("walk", a_walk, handler1);
    ar.addAnimation("die", a_die, handler1);
  }
};
class Enemy1 : public Enemy {
 public:
  Enemy1() : Enemy("slimeGreen") {}
};
class Enemy2 : public Enemy {
 public:
  Enemy2() : Enemy("slimePink") {}
};
class Enemy3 : public Enemy {
 public:
  Enemy3() : Enemy("slimeBlue") {}
};

#endif  // PANCAKE_ENNEMIES_HPP
