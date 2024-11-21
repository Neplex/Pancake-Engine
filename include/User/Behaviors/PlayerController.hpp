//
// Created by kelle on 02/02/2017.
//

#ifndef PANCAKE_PLAYERCONTROLLER_HPP
#define PANCAKE_PLAYERCONTROLLER_HPP

#include <GameLogic.hpp>
#include <Inputs.hpp>
#include <User/Items/Bullet.hpp>

class PlayerController : public PancakeEngine::Behavior {
 public:
  bool climbing = false;
  bool swiming = false;
  bool onGround = false;
  PancakeEngine::Collider *topCollider;
  int direction = 1;

  void OnTriggerEnter(const PancakeEngine::Collider &triggered, const PancakeEngine::Collider &other) override {
    onGround = true;
  }

  void OnTriggerExit(const PancakeEngine::Collider &triggered, const PancakeEngine::Collider &other) override {
    onGround = false;
  }

  void update() {
    topCollider->setSleep(false);
    float velocityXDesired = 0;
    float velocityYDesired = 0;
    PancakeEngine::Rigidbody *rb = gameObject->getComponent<PancakeEngine::Rigidbody>();
    if (PancakeEngine::Input::getButtonHeld(gameObject->name + "_jump") && (climbing || swiming)) {
      velocityYDesired = -5;
    }

    if (onGround && PancakeEngine::Input::getButtonPressed(gameObject->name + "_jump")) {
      gameObject->getComponent<PancakeEngine::Rigidbody>()->applyLinearImpulse(sf::Vector2f(0, -11));
    }

    if (PancakeEngine::Input::getButtonHeld(gameObject->name + "_duck")) {
      velocityYDesired = 5;
      if (!climbing && !swiming) {
        topCollider->setSleep(true);
      }
    }

    if (PancakeEngine::Input::getButtonHeld(gameObject->name + "_right")) {
      velocityXDesired = 5;
    }

    if (PancakeEngine::Input::getButtonHeld(gameObject->name + "_left")) {
      velocityXDesired = -5;
    }

    float velYChange = velocityYDesired - rb->getVelocity().y;
    float velXChange = velocityXDesired - rb->getVelocity().x;
    float impulseY = rb->getMass() * velYChange;
    float impulseX = rb->getMass() * velXChange;  // disregard time factor
    rb->applyLinearImpulse(sf::Vector2f(impulseX, 0));
    if (climbing || swiming) {
      rb->applyLinearImpulse(sf::Vector2f(0, impulseY));
    }

    if (rb->getVelocity().x > 2) {
      direction = 1;
    } else if (rb->getVelocity().x < -2) {
      direction = -1;
    }

    if (PancakeEngine::Input::getButtonPressed(gameObject->name + "_fire")) {
      Bullet &bo = PancakeEngine::SceneManager::getCurrentScene()->addGameObject<Bullet>(1);
      BulletScript *b = bo.getComponent<BulletScript>();
      b->direction = direction;
      b->owner = gameObject->name;

      bo.transform.setPosition(sf::Vector2f(gameObject->transform.getWorldPosition().x + b->direction * 40,
                                            gameObject->transform.getWorldPosition().y));
    }
  }
};

#endif  // PANCAKE_PLAYERCONTROLLER_HPP
