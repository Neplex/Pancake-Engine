//
// Created by Darenn on 15/03/2017.
//

#ifndef PANCAKE_GAMECONTROLLERSOLOOBJECT_HPP
#define PANCAKE_GAMECONTROLLERSOLOOBJECT_HPP

#include <User/Behaviors/GameController.hpp>

class GameControllerSoloObject : public PancakeEngine::GameObject {
 public:
  virtual ~GameControllerSoloObject() = default;

  GameControllerSoloObject() {
    name = "GameController";
    addComponent<GameController>();
  }
};

#endif  // PANCAKE_GAMECONTROLLERSOLOOBJECT_HPP
