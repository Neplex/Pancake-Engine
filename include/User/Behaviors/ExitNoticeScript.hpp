//
// Created by virgil on 18/03/17.
//

#ifndef PANCAKE_EXITNOTICESCRIPT_HPP
#define PANCAKE_EXITNOTICESCRIPT_HPP

#include <GameLogic.hpp>
#include <User/GameControllerSoloObject.hpp>

class ExitNoticeScript : public PancakeEngine::Behavior {
 public:
  void OnTriggerEnter(const PancakeEngine::Collider &triggered, const PancakeEngine::Collider &other) override {
    if (other.gameObject->name == "player1") {
      reload = true;
    }
  }
  void update() override {
    if (reload) {
      PancakeEngine::SceneFactory sf;
      PancakeEngine::Scene *sc = sf.loadAllSceneObject("../resources/maps/test.tmx");
      sc->addGameObject<GameControllerSoloObject>(1);
      PancakeEngine::SceneManager::loadScene(sc);
      reload = false;
    }
  }

 private:
  bool reload = false;
};
#endif  // PANCAKE_EXITNOTICESCRIPT_HPP
