//
// Created by Darenn on 24/01/2017.
//

#include <iostream>
#include "../include/Engine.hpp"
#include "../include/Camera.hpp"
#include "../include/AnimationRenderer.hpp"

Engine::Engine() : sceneManager(), inputHandler(), window(sceneManager, inputHandler), physicsEngine(), time() {

    Collider::physicsEngine = &physicsEngine;
    Rigidbody::physicsEngine = &physicsEngine;
    Time::deltaTime = SECONDS_PER_UPDATE;

    // TEST //
    // Ground
    GameObject * groudingBox = new GameObject("GroundinBox");
    BoxCollider * bcGroundingBox = new BoxCollider();
    bcGroundingBox->height = 72;
    bcGroundingBox->width = 72 * 8;
    groudingBox->transform->setPosition(sf::Vector2f(200, 300));
    groudingBox->addComponent(*bcGroundingBox);
    // Box
    GameObject * go1 = new GameObject("");
    SpriteSheet * ss = new SpriteSheet("../resources/tiles_spritesheet.png", 72, 72);
    Animation * a = new Animation(*ss);
    a->addFrame(0, 3, 200);
    a->addFrame(0, 4, 200);
    a->addFrame(0, 5, 200);
    AnimationRenderer * ar = new AnimationRenderer(*a);
    ar->play();
    BoxCollider * bc = new BoxCollider();
    Rigidbody * rb = new Rigidbody();
    bc->width = 72; bc->height = 72;
    go1->transform->setPosition(sf::Vector2f(100, -100));
    go1->transform->setRotation(0);
    go1->addComponent(*ar);
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
        window.handleEvent();
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