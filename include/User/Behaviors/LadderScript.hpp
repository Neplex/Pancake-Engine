//
// Created by Darenn on 13/03/2017.
//

#ifndef PANCAKE_LADDERSCRIPT_HPP
#define PANCAKE_LADDERSCRIPT_HPP

#include <GameLogic.hpp>
#include <cmath>

#include "PlayerController.hpp"

class LadderScript : public PancakeEngine::Behavior {
 public:
  float maxSpeed = 5;

  void OnTriggerEnter(const PancakeEngine::Collider &triggered, const PancakeEngine::Collider &other) override {
    auto *pc = other.gameObject->getComponent<PlayerController>();
    auto *rb = other.gameObject->getComponent<PancakeEngine::Rigidbody>();

    if (rb != nullptr && pc != nullptr) {
      rb->setVelocity(sf::Vector2f(0, 0));
      rb->setGravityScale(0);
      climbers.push_back(rb);
      pc->climbing = true;
    }
  }

  void update() override {
    for (auto &climber : climbers) {
      if (std::abs(climber->getVelocity().x) > maxSpeed) {
        if (climber->getVelocity().x < 0) {
          climber->setVelocity(sf::Vector2f(-maxSpeed, climber->getVelocity().y));
        }
      }

      if (std::abs(climber->getVelocity().y) > maxSpeed) {
        if (climber->getVelocity().y < 0) {
          climber->setVelocity(sf::Vector2f(climber->getVelocity().x, -maxSpeed));
        }
      }
    }
  }

  // TODO careful, maybe the base gravityScale was not 1, make a map to remember.

  void OnTriggerExit(const PancakeEngine::Collider &triggered, const PancakeEngine::Collider &other) override {
    auto *pc = other.gameObject->getComponent<PlayerController>();
    auto *rb = other.gameObject->getComponent<PancakeEngine::Rigidbody>();

    if (rb != nullptr && pc != nullptr) {
      rb->setGravityScale(1);
      pc->climbing = false;
      for (int i = 0; i < climbers.size(); i++) {
        if (climbers[i] == rb) {
          climbers.erase(climbers.begin() + i);
        }
      }
    }
  }

 private:
  std::vector<PancakeEngine::Rigidbody *> climbers;
};

#endif  // PANCAKE_LADDERSCRIPT_HPP
