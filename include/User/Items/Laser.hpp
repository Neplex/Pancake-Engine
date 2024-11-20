//
// Created by nicolas on 15/03/17.
//

#ifndef PANCAKE_LASER_HPP
#define PANCAKE_LASER_HPP

#include <GameLogic/GameObject.hpp>
#include <User/Behaviors/LaserScript.hpp>
#include <User/Behaviors/OnTriggerKill.hpp>

class Laser : public PancakeEngine::GameObject {
 public:
  virtual ~Laser() = default;

  Laser() {
    name = "Laser";
    addComponent<LaserScript>();
    addComponent<OnTriggerKill>();
    addComponent<PancakeEngine::Rigidbody>().setType(PancakeEngine::Rigidbody::bodyType::kinematicBody);
  }
};

#endif  // PANCAKE_LASER_HPP
