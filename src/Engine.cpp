//
// Created by Darenn on 24/01/2017.
//

#include <vector>
#include "../include/Engine.hpp"
#include "../include/Inputs/InputManager.hpp"
#include "../include/imgui/imgui-SFML.h"
#include "../include/Debug.hpp"

Engine::Engine() : sceneManager(), window(sceneManager), physicsEngine(), time() {

    Collider::physicsEngine = &physicsEngine;
    Rigidbody::physicsEngine = &physicsEngine;
    Time::deltaTime = SECONDS_PER_UPDATE;
    InputManager::window = &window.window;
#ifdef PANCAKE_DEBUG
    Debug::init(window.window);

    // Add some loggers
    Debug::addLogger("Inputs");
#endif
}

void Engine::update() {
    physicsEngine.update(SECONDS_PER_UPDATE);
    sceneManager.getCurrentScene()->update();
    sceneManager.getCurrentScene()->lateUpdate();
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