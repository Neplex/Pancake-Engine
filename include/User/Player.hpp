//
// Created by nicolas on 15/02/17.
//

#ifndef PANCAKE_PLAYER_HPP
#define PANCAKE_PLAYER_HPP

#include <GameLogic.hpp>
#include <Graphics.hpp>
#include <User/Behaviors/PlayerController.hpp>
#include <User/Behaviors/PlayerScript.hpp>
#include <User/Health.hpp>

constexpr int Animation_SPEED = 150;

class Player : public PancakeEngine::GameObject {
 public:
  virtual ~Player() = default;

 private:
  friend class Player1;
  friend class Player2;
  friend class Player3;
  friend class Player4;
  friend class Player5;

  static std::string handler(PancakeEngine::GameObject const &go) {
    sf::Vector2f velocity = go.getComponent<PancakeEngine::Rigidbody>()->getVelocity();
    auto *ar = go.getComponent<PancakeEngine::Animator>();
    auto const *pc = go.getComponent<PlayerController>();

    if (velocity.x > .1) {
      ar->flip(false);
    } else if (velocity.x < -.1) {
      ar->flip(true);
    }

    if (pc->climbing) {
      return "climb";
    }
    if (pc->swiming) {
      return "swing";
    }
    if (PancakeEngine::Input::getButtonHeld(go.name + "_duck")) {
      return "duck";
    }
    if (!pc->onGround) {
      return "jump";
    }
    if (velocity.x < -.1 || velocity.x > .1) {
      return "walk";
    }
    return "idle";
  }

  explicit Player(std::string const &n) {
    name = n;
    addComponent<Health>();
    addComponent<PancakeEngine::Rigidbody>().setFreezeRotation(true);
    // TODO: Add "capsule" collider
    auto &cl_top = addComponent<PancakeEngine::CircleCollider>();
    auto &cl_bottom = addComponent<PancakeEngine::CircleCollider>();
    cl_top.radius = cl_bottom.radius = 33;
    cl_top.offset = sf::Vector2f(0, -10);
    cl_bottom.offset = sf::Vector2f(0, 17);

    auto &ground = addComponent<PancakeEngine::BoxCollider>();
    ground.width = 50;
    ground.height = 2;
    ground.isTrigger = true;
    ground.offset = sf::Vector2f(0, 50);

    auto &pc = addComponent<PlayerController>();
    pc.topCollider = &cl_top;
    cl_top.friction = 0;
    cl_bottom.friction = 0;
    addComponent<PlayerScript>();
    // addComponent<LuaScript>().setScript("../resources/scripts/PlayerController.lua");
    addComponent<PancakeEngine::Camera>().setBackground("../resources/backgrounds/bg_grasslands.png");

    PancakeEngine::SpriteSheet &sprites = PancakeEngine::AssetsManager::getSpriteSheet(name);

    PancakeEngine::Animation &a_idle = PancakeEngine::AssetsManager::createAnimation(name + "r_idle", sprites);
    a_idle.addFrame(0, 0, Animation_SPEED);
    PancakeEngine::Animation &a_duck = PancakeEngine::AssetsManager::createAnimation(name + "_duck", sprites);
    a_duck.addFrame(1, 0, Animation_SPEED);
    PancakeEngine::Animation &a_jump = PancakeEngine::AssetsManager::createAnimation(name + "_jump", sprites);
    a_jump.addFrame(2, 0, Animation_SPEED);
    PancakeEngine::Animation &a_hurt = PancakeEngine::AssetsManager::createAnimation(name + "_hurt", sprites);
    a_hurt.addFrame(3, 0, Animation_SPEED);
    PancakeEngine::Animation &a_walk = PancakeEngine::AssetsManager::createAnimation(name + "_walk", sprites);
    a_walk.addFrame(0, 1, Animation_SPEED);
    a_walk.addFrame(0, 2, Animation_SPEED);
    PancakeEngine::Animation &a_swing = PancakeEngine::AssetsManager::createAnimation(name + "_swing", sprites);
    a_swing.addFrame(1, 1, Animation_SPEED * 2);
    a_swing.addFrame(1, 2, Animation_SPEED * 2);
    PancakeEngine::Animation &a_climb = PancakeEngine::AssetsManager::createAnimation(name + "_climb", sprites);
    a_climb.addFrame(2, 1, Animation_SPEED * 2);
    a_climb.addFrame(2, 2, Animation_SPEED * 2);
    PancakeEngine::Animation &a_front = PancakeEngine::AssetsManager::createAnimation(name + "_front", sprites);
    a_front.addFrame(3, 1, Animation_SPEED);

    auto &ar = addComponent<PancakeEngine::Animator>();
    ar.addAnimation("idle", a_idle, handler);
    ar.addAnimation("duck", a_duck, handler);
    ar.addAnimation("jump", a_jump, handler);
    ar.addAnimation("hurt", a_hurt, handler);
    ar.addAnimation("walk", a_walk, handler);
    ar.addAnimation("swing", a_swing, handler);
    ar.addAnimation("climb", a_climb, handler);
    ar.addAnimation("front", a_front, handler);
  }
};

class Player1 final : public Player {
 public:
  Player1() : Player("player1") {}
};
class Player2 final : public Player {
 public:
  Player2() : Player("player2") {}
};
class Player3 final : public Player {
 public:
  Player3() : Player("player3") {}
};
class Player4 final : public Player {
 public:
  Player4() : Player("player4") {}
};
class Player5 final : public Player {
 public:
  Player5() : Player("player5") {}
};

#endif  // PANCAKE_PLAYER_HPP
