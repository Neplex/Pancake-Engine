//
// Created by Darenn on 24/01/2017.
//

#include <iostream>
#include "../include/Engine.hpp"
#include "../include/SpriteRenderer.hpp"
#include "../include/Camera.hpp"

Engine::Engine() : sceneManager(), inputHandler(), window(sceneManager, inputHandler), physicsEngine(), time() {

    Collider::physicsEngine = &physicsEngine;
    Rigidbody::physicsEngine = &physicsEngine;
    Time::deltaTime = MS_PER_UPDATE / 1000;

    // TEST //
    // Ground
    GameObject * groudingBox = new GameObject("GroundinBox");
    BoxCollider * bcGroundingBox = new BoxCollider();
    bcGroundingBox->height = 64;
    bcGroundingBox->width = 10 * 32;
    groudingBox->transform->setPosition(sf::Vector2f(200, 100));
    groudingBox->addComponent(*bcGroundingBox);
    // Box
    GameObject * go1 = new GameObject("");
    SpriteSheet * ss = new SpriteSheet("../resources/tiles_spritesheet.png", 72, 72);
    SpriteRenderer * sr = new SpriteRenderer(*ss, 0, 11);
    BoxCollider * bc = new BoxCollider();
    Rigidbody * rb = new Rigidbody();
    bc->width = 70; bc->height = 70;
    go1->transform->setPosition(sf::Vector2f(100, -100));
    go1->transform->setRotation(0);
    go1->addComponent(*sr);
    go1->addComponent(*bc);
    go1->addComponent(*rb);
    // Camera
    GameObject * go2 = new GameObject("");
    Camera * cm = new Camera();
    cm->zoom(1.2);
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

void Engine::update() {
    physicsEngine.update(MS_PER_UPDATE);
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
            update();
            lag -= MS_PER_UPDATE;
        }

        window.render();
    }
}