#include <Engine.hpp>
#include <Parser/SceneFactory.hpp>
#include <User.hpp>
#include <User/GameControllerSoloObject.hpp>
#include <User/Sandbox.hpp>

using namespace PancakeEngine;

int main() {
  CreatePrefabAndSpriteAndInput();
  auto *app = new Engine();
  auto filename = "../resources/maps/arena.tmx";

  SceneFactory sf;
  Scene *sc = sf.loadAllSceneObject(filename);

  // Add GUI
  const unsigned height = sf::VideoMode::getDesktopMode().height / 2 + 50;
  const unsigned width = sf::VideoMode::getDesktopMode().width / 2;

  sc->addGameObjectToGui<PlayerGUI1>().transform.setPosition(sf::Vector2f(width * 0 + 50, 50));
  sc->addGameObjectToGui<PlayerGUI2>().transform.setPosition(sf::Vector2f(width * 1 + 50, 50));
  sc->addGameObjectToGui<PlayerGUI3>().transform.setPosition(sf::Vector2f(width * 0 + 50, height));
  sc->addGameObjectToGui<PlayerGUI4>().transform.setPosition(sf::Vector2f(width * 1 + 50, height));
  sc->addGameObjectToGui<CoinGui>().transform.setPosition(sf::Vector2f(50, height * 2 - 150));
  sc->addGameObject<GameControllerSoloObject>(1);

  SceneManager::loadScene(sc);

  app->run();
  delete app;

  return EXIT_SUCCESS;
}
