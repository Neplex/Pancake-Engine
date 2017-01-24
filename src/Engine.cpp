//
// Created by Darenn on 24/01/2017.
//

#include "../include/Engine.hpp"
#include "../include/SpriteRenderer.hpp"
#include "../include/Camera.hpp"

Engine::Engine() : sceneManager(), inputHandler(), window(sceneManager, inputHandler),
                   physicsEngine(), toShutdown(false) {
    GameObject * go1 = new GameObject("");
    GameObject * go2 = new GameObject("");
    SpriteRenderer * sr = new SpriteRenderer(32, 32);
    Camera * cm = new Camera();
    cm->zoom(.6);
    BoxCollider * bc = new BoxCollider();
    bc->width = 32; bc->height = 32;
    bc->offset = sf::Vector2f(25, 25);
    go1->transform->setPosition(sf::Vector2f(100, -100));
    go1->transform->setRotation(10);
    go1->addComponent(*sr);
    go1->addComponent(*bc);
    go2->addComponent(*cm);

    Scene* scene = new Scene("TestScene");
    scene->addGameObject(go1);
    scene->addGameObject(go2);
    scene->awake();
    scene->start();

    sceneManager.addScene(scene);
    window.setDebug();
}

void Engine::update(float dt) {
    physicsEngine.update(dt);
    sceneManager.getCurrentScene()->update();
    sceneManager.getCurrentScene()->lateUpdate();
}

void Engine::run() {
    double lag = 0.0;
    sf::Clock clock;
    while (!window.isClosed())
    {
        clock.restart();
        lag += clock.getElapsedTime().asMilliseconds();

        window.handleEvent();

        while (lag >= MS_PER_UPDATE)
        {
            update(clock.getElapsedTime().asMilliseconds());
            lag -= MS_PER_UPDATE;
        }

        window.render();
    }
}