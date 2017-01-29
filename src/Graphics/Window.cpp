//
// Created by nicolas on 22/01/17.
//

#include <iostream>
#include "../../include/Graphics/Window.hpp"
#include "../../include/GameLogic/Components/SpriteRenderer.hpp"
#include "../../include/GameLogic/Components/Camera.hpp"
#include "../../include/GameLogic/Components/AnimationRenderer.hpp"
#include "../include/GameLogic/Components/Transform.hpp"
#include "../../include/Debug.hpp"

Window::Window(SceneManager& s) : scenes(s), window(sf::VideoMode::getDesktopMode(), "", sf::Style::Close) {
    FPS = 60.0f;
    timeBetweenTwoFrames = sf::seconds((1.0f/FPS));
    clock = sf::Clock();
    window.setVerticalSyncEnabled(false); ///< Don't activate it ! It does not fit with our type of game loop
    window.setActive(false); // TODO Why ?
}

void Window::render()
{
    if (clock.getElapsedTime() >= timeBetweenTwoFrames) {
        clock.restart();
        if (window.isOpen()) {
            window.clear();
            drawScene();
            if (debug) {
                drawDebug();
            }
            Debug::update(); // should be called only once per frame
            Debug::render();
            window.display();
        }
    }
}

void Window::setDebug(bool val) {
    debug = val;
}

void Window::setFrameRate(float framerate) {
    FPS = framerate;
    timeBetweenTwoFrames = sf::seconds((float) (1.0/FPS));
}

void Window::drawScene() {
    // Set view
    if (Camera::mainCamera != NULL) {
        sf::View view = Camera::mainCamera->view;
        view.setCenter(Camera::mainCamera->gameObject->transform->getPosition());
        view.setRotation(Camera::mainCamera->gameObject->transform->getRotation());
        window.setView(view);
    } else {
        window.setView(window.getDefaultView());
    }

    for (int i = 0; i < scenes.getCurrentScene()->gameObjects.size(); ++i) {
         const GameObject * gameObject = scenes.getCurrentScene()->gameObjects[i];

        // Get SpriteRenderer
        const SpriteRenderer * spriteRenderer = gameObject->getComponent<SpriteRenderer>();
        if (spriteRenderer != NULL) {
            sf::RenderStates renderStates;
            renderStates.transform = gameObject->transform->getTransformMatrix();
            window.draw(spriteRenderer->sprite, renderStates);
        }

        // Get AnimationRenderer
        const AnimationRenderer * animationRenderer = gameObject->getComponent<AnimationRenderer>();
        if (animationRenderer != NULL) {
            sf::RenderStates renderStates;
            renderStates.transform = gameObject->transform->getTransformMatrix();
            window.draw(animationRenderer->sprite, renderStates);
        }
    }
}

void Window::drawDebug() {
    for (int i = 0; i < scenes.getCurrentScene()->gameObjects.size(); ++i) {

        // Box collider
        const BoxCollider * boxCollider = scenes.getCurrentScene()->gameObjects[i]->getComponent<BoxCollider>();
        if (boxCollider != NULL) draw(boxCollider);
    }
}

sf::Color Window::getColor(const Collider * collider) {
    sf::Color color;
    switch (collider->getBodyType()) {

        case Rigidbody::bodyType::staticBody:
            color = sf::Color(255, 0, 0);
            break;

        case Rigidbody::bodyType::dynamicBody:
            color = sf::Color(0, 255, 0);
            break;

        case Rigidbody::bodyType::kinematicBody:
            color = sf::Color(0, 0, 255);
            break;

        default:
            color = sf::Color(255, 255, 255);
            break;

    }
    return color;
}

void Window::draw(const BoxCollider * boxCollider) {
    // To draw from center
    sf::Vertex vertices[6] = {
            sf::Vertex(sf::Vector2f(-boxCollider->width/2, -boxCollider->height/2)),
            sf::Vertex(sf::Vector2f(boxCollider->width/2, -boxCollider->height/2)),
            sf::Vertex(sf::Vector2f(boxCollider->width/2, boxCollider->height/2)),
            sf::Vertex(sf::Vector2f(-boxCollider->width/2, -boxCollider->height/2)),
            sf::Vertex(sf::Vector2f(-boxCollider->width/2, boxCollider->height/2)),
            sf::Vertex(sf::Vector2f(boxCollider->width/2, boxCollider->height/2))
    };
    // Color for type
    sf::Color color = getColor(boxCollider);
    for (int i = 0; i < 6; ++i) {
        vertices[i].color = color;
    }
    // Transform
    sf::Transform transform = boxCollider->gameObject->transform->getTransformMatrix();
    sf::RenderStates renderStates;
    renderStates.transform = boxCollider->gameObject->transform->getTransformMatrix();
    renderStates.transform.translate(boxCollider->offset);
    window.draw(vertices, 6, sf::LinesStrip, renderStates);
}