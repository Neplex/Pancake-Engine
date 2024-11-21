//
// Created by nicolas on 14/03/17.
//

#ifndef PANCAKE_WATERSCRIPT_HPP
#define PANCAKE_WATERSCRIPT_HPP

#include <GameLogic/Components/Collider.hpp>
#include <GameLogic/Components/Rigidbody.hpp>

#include "PlayerController.hpp"
class WaterScript : public PancakeEngine::Behavior {
 public:
  float maxSpeed = 5;

  void OnTriggerEnter(const PancakeEngine::Collider &triggered, const PancakeEngine::Collider &other) override {
    auto *pc = other.gameObject->getComponent<PlayerController>();
    auto *rb = other.gameObject->getComponent<PancakeEngine::Rigidbody>();
    if (rb != nullptr && pc != nullptr) {
      rb->setVelocity(sf::Vector2f(0, 0));
      rb->setGravityScale(0);
      swimers.push_back(rb);
      pc->swiming = true;
    }
  }

  void update() override {
    for (auto &swimer : swimers) {
      if (std::abs(swimer->getVelocity().x) > maxSpeed && swimer->getVelocity().x < 0) {
        swimer->setVelocity(sf::Vector2f(-maxSpeed, swimer->getVelocity().y));
      }

      if (std::abs(swimer->getVelocity().y) > maxSpeed && swimer->getVelocity().y < 0) {
        swimer->setVelocity(sf::Vector2f(swimer->getVelocity().x, -maxSpeed));
      }
    }
  }

  void OnTriggerExit(const PancakeEngine::Collider &triggered, const PancakeEngine::Collider &other) override {
    auto *pc = other.gameObject->getComponent<PlayerController>();
    auto *rb = other.gameObject->getComponent<PancakeEngine::Rigidbody>();
    if (rb != nullptr && pc != nullptr) {
      rb->setGravityScale(1);
      pc->swiming = false;
      for (int i = 0; i < swimers.size(); i++) {
        if (swimers[i] == rb) {
          swimers.erase(swimers.begin() + i);
        }
      }
    }
  }

 private:
  std::vector<PancakeEngine::Rigidbody *> swimers;
};

#endif  // PANCAKE_WATERSCRIPT_HPP
