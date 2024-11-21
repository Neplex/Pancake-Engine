//
// Created by nicolas on 15/03/17.
//

#ifndef PANCAKE_DEATHZONE_HPP
#define PANCAKE_DEATHZONE_HPP

#include <GameLogic/GameObject.hpp>
#include <User/Behaviors/OnAwakeSetBoxCollider.hpp>
#include <User/Behaviors/OnTriggerKill.hpp>

class DeathZone : public PancakeEngine::GameObject {
 public:
  virtual ~DeathZone() = default;

  DeathZone() {
    addComponent<OnAwakeSetBoxCollider>();
    addComponent<OnTriggerKill>();
  }
};

#endif  // PANCAKE_DEATHZONE_HPP
