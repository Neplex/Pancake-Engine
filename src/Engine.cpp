//
// Created by Darenn on 24/01/2017.
//

#include "../include/Engine.hpp"
#include "../include/Inputs/InputManager.hpp"

Engine::Engine() : sceneManager(), inputHandler(), window(sceneManager, inputHandler), physicsEngine(), time() {

    Collider::physicsEngine = &physicsEngine;
    Rigidbody::physicsEngine = &physicsEngine;
    Time::deltaTime = SECONDS_PER_UPDATE;
    InputManager::window = &window.window;
}

void Engine::update() {
    physicsEngine.update(SECONDS_PER_UPDATE);
    sceneManager.getCurrentScene()->update();
    sceneManager.getCurrentScene()->lateUpdate();
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

        // Processing inputs
        InputManager::handleInputs();
        while(lag >= SECONDS_PER_UPDATE)
        {
            // Updating

            update();
            // Retrieve elapsed time
            lag -= SECONDS_PER_UPDATE;
        }
        // Rendering
        window.render();
        //m_graphicEngine.render(lag / SECONDS_PER_UPDATE);
    }
}