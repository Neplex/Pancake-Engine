//
// Created by Darenn on 24/01/2017.
//

#include <vector>
#include <Engine.hpp>


using namespace PancakeEngine;

Engine::Engine() : window(), physicsEngine(), time() {

    Collider::physicsEngine = &physicsEngine;
    Rigidbody::physicsEngine = &physicsEngine;
    Time::deltaTime = SECONDS_PER_UPDATE;
    InputManager::window = &window.window;
#ifdef PANCAKE_DEBUG
   Debug::init(window.window, window);
    //Debug::setEnableDebugGUI(true);

    // Add some loggers
    Debug::addLogger("Foo");
    Debug::addLogger("Inputs");
    Debug::addLogger("Lua");

    // Add some keyshorcuts for debug
//

#endif
}

void Engine::update() {
    physicsEngine.update(SECONDS_PER_UPDATE);
    SceneManager::getCurrentScene()->update();
    SceneManager::getCurrentScene()->lateUpdate();
    InputManager::update();
}

void Engine::run() {
    sf::Clock clock;
    double lag = 0.0;
    double previous = clock.getElapsedTime().asSeconds();

    while(!window.isClosed())
    {
        double current = clock.getElapsedTime().asSeconds();
        double elapsed = current - previous;
        previous = current;

        lag += elapsed;

        InputManager::handleInputs();

        while(lag >= SECONDS_PER_UPDATE)
        {
            update();
            lag -= SECONDS_PER_UPDATE;
        }
        window.render();
    }
    Debug::shutDown();
}
