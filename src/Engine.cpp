//
// Created by Darenn on 24/01/2017.
//

#include <Engine.hpp>

using namespace PancakeEngine;

Engine::Engine() {
  Collider::physicsEngine = &physicsEngine;
  Rigidbody::physicsEngine = &physicsEngine;
  Time::deltaTime = SECONDS_PER_UPDATE;
  InputManager::window = &window.window;
  SceneManager::physicsEngine = &physicsEngine;
#ifdef PANCAKE_DEBUG
  Debug::init(window.window, window);

  // Add some loggers
  Debug::addLogger("Foo");
  Debug::addLogger("Inputs");
  Debug::addLogger("Lua");

  // Add some shortcuts for debug

#endif
}

void Engine::update() {
  physicsEngine.update(SECONDS_PER_UPDATE);
  SceneManager::getCurrentScene()->update();
  SceneManager::getCurrentScene()->lateUpdate();
  InputManager::update();
}

void Engine::run() {
  const sf::Clock clock;
  double lag = 0.0;
  double previous = clock.getElapsedTime().asSeconds();

  while (!window.isClosed()) {
    const double current = clock.getElapsedTime().asSeconds();
    const double elapsed = current - previous;
    previous = current;

    lag += elapsed;

    InputManager::handleInputs();

    while (lag >= SECONDS_PER_UPDATE) {
      update();
      lag -= SECONDS_PER_UPDATE;
    }
    window.render();
  }

  Debug::shutDown();
}
