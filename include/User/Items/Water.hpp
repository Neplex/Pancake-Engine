//
// Created by nicolas on 14/03/17.
//

#ifndef PANCAKE_WATER_HPP
#define PANCAKE_WATER_HPP

#include <GameLogic/GameObject.hpp>
#include <User/Behaviors/WaterScript.hpp>

class Water : public PancakeEngine::GameObject {
 public:
  virtual ~Water() = default;

  Water() {
    addComponent<OnAwakeSetBoxCollider>();
    addComponent<WaterScript>();
  }
};

#endif  // PANCAKE_WATER_HPP
