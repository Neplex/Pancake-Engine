//
// Created by Darenn on 24/01/2017.
//

#include <iostream>
#include "../include/Engine.hpp"
#include "../include/SpriteRenderer.hpp"
#include "../include/Camera.hpp"
#include "../include/Rigidbody.hpp"

Engine::Engine() : sceneManager(), inputHandler(), window(sceneManager, inputHandler),
                   physicsEngine() {

    Collider::physicsEngine = &physicsEngine;
    Rigidbody::physicsEngine = &physicsEngine;
    // TEST //
    GameObject * go1 = new GameObject("");
    GameObject * go2 = new GameObject("");
    GameObject * groudingBox = new GameObject("GroundinBox");
    BoxCollider * bcGroundingBox = new BoxCollider();
    bcGroundingBox->height = 64;
    bcGroundingBox->width = 8 * 32;
    bcGroundingBox->offset = sf::Vector2f(0, 0);
    groudingBox->transform->setPosition(sf::Vector2f(200, 100));
    groudingBox->addComponent(*bcGroundingBox);

    SpriteRenderer * sr = new SpriteRenderer(32, 32);
    Camera * cm = new Camera();
    cm->zoom(.6);
    BoxCollider * bc = new BoxCollider();
    Rigidbody * rb = new Rigidbody();
    bc->width = 32; bc->height = 32;
    bc->offset = sf::Vector2f(0, 100);
    go1->transform->setPosition(sf::Vector2f(100, -100));
    go1->transform->setRotation(0);
    go1->addComponent(*sr);
    go1->addComponent(*bc);
    go1->addComponent(*rb);
    go2->addComponent(*cm);

    Scene* scene = new Scene("TestScene");
    scene->addGameObject(groudingBox);
    scene->addGameObject(go1);
    scene->addGameObject(go2);
    scene->awake();
    scene->start();

    sceneManager.addScene(scene);
    window.setDebug();
    // TEST //
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
        lag += clock.getElapsedTime().asMilliseconds();
        clock.restart();

        window.handleEvent();

        while (lag >= MS_PER_UPDATE)
        {
            update(MS_PER_UPDATE);
            lag -= MS_PER_UPDATE;
        }

        window.render();
    }
}