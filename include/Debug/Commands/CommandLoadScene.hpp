//
// Created by nicolas on 15/03/17.
//

#ifndef PANCAKE_COMMANDLOADSCENE_HPP
#define PANCAKE_COMMANDLOADSCENE_HPP

#include <GameLogic/Scene.hpp>
#include <Parser/SceneFactory.hpp>
#include <User/GameControllerSoloObject.hpp>

#include "Command.hpp"

namespace PancakeEngine {
class CommandLoadScene : public Command {
 public:
  explicit CommandLoadScene(Console &c) : Command(c) {
    description = "Load a scene";
    help = "Load a scene from a tmx map.";
  }

  void execute(std::vector<std::string> &args) override {
    if (args.size() != 1) {
      console.printErr("Need a path to the tmx file");
      return;
    }
    SceneFactory sf;
    Scene *sc = sf.loadAllSceneObject(args[0].c_str());
    sc->addGameObject<GameControllerSoloObject>(1);
    SceneManager::loadScene(sc);
  }
};
}  // namespace PancakeEngine

#endif  // PANCAKE_COMMANDLOADSCENE_HPP
