//
// Created by nicolas on 22/01/17.
//

#include <iostream>
#include <GameLogic/Components/CircleCollider.hpp>
#include "../../include/Graphics/Window.hpp"
#include "../../include/GameLogic/Components/SpriteRenderer.hpp"
#include "../../include/GameLogic/Components/Camera.hpp"
#include "../../include/GameLogic/Components/AnimationRenderer.hpp"
#include "../../include/Debug/Debug.hpp"
#include "../../include/GameLogic/Components/Animator.hpp"

using namespace PancakeEngine;

Window::Window(SceneManager& s) : scenes(s), window(sf::VideoMode::getDesktopMode(), "", sf::Style::Close) {
    FPS = 60.0f;
    timeBetweenTwoFrames = sf::seconds((1.0f/FPS));
    clock = sf::Clock();
    window.setVerticalSyncEnabled(false); ///< Don't activate it ! It does not fit with our type of game loop
    window.setActive(false); // TODO Why ?
    debug = false;
}

void Window::render()
{
    if (clock.getElapsedTime() >= timeBetweenTwoFrames) {
        clock.restart();
        if (window.isOpen()) {
            window.clear();
            drawScene();
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
        view.setCenter(Camera::mainCamera->gameObject->transform.getPosition());
        view.setRotation(Camera::mainCamera->gameObject->transform.getRotation());
        window.setView(view);
    } else {
        window.setView(window.getDefaultView());
    }

    // Draw elements
    sf::RenderStates renderStates;
    for (unsigned i = 0; i < scenes.getCurrentScene()->gameObjects.size(); ++i) {
        GameObject * gameObject = scenes.getCurrentScene()->gameObjects[i];
        renderStates.transform = gameObject->transform.getTransformMatrix();

        // Get SpriteRenderer
        const SpriteRenderer * spriteRenderer = gameObject->getComponent<SpriteRenderer>();
        if (spriteRenderer != NULL) window.draw(spriteRenderer->sprite, renderStates);

        // Get AnimationRenderer
        const AnimationRenderer * animationRenderer = gameObject->getComponent<AnimationRenderer>();
        if (animationRenderer != NULL) window.draw(animationRenderer->sprite, renderStates);

        // Get Animator
        const Animator * animator = gameObject->getComponent<Animator>();
        // TODO: segmentation fault if animator is empty
        if (animator != NULL) window.draw(animator->getCurrentAnimation().sprite, renderStates);

        // Debug elements
        if (debug) {
            // Box collider
            const std::vector<BoxCollider *> boxColliders = scenes.getCurrentScene()->gameObjects[i]->getComponents<BoxCollider>();
            for (BoxCollider *bc : boxColliders) draw(bc);
            // Circle collider
            const std::vector<CircleCollider *> circleColliders = scenes.getCurrentScene()->gameObjects[i]->getComponents<CircleCollider>();
            for (CircleCollider *bc : circleColliders) draw(bc);
        }
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
            sf::Vertex(sf::Vector2f( boxCollider->width/2, -boxCollider->height/2)),
            sf::Vertex(sf::Vector2f( boxCollider->width/2,  boxCollider->height/2)),
            sf::Vertex(sf::Vector2f(-boxCollider->width/2, -boxCollider->height/2)),
            sf::Vertex(sf::Vector2f(-boxCollider->width/2,  boxCollider->height/2)),
            sf::Vertex(sf::Vector2f( boxCollider->width/2,  boxCollider->height/2))
    };
    // Color for type
    sf::Color color = getColor(boxCollider);
    for (int i = 0; i < 6; ++i) {
        vertices[i].color = color;
    }
    // Transform
    sf::RenderStates renderStates;
    renderStates.transform = boxCollider->gameObject->transform.getTransformMatrix();
    renderStates.transform.translate(boxCollider->offset);
    window.draw(vertices, 6, sf::LinesStrip, renderStates);
}

void Window::draw(const CircleCollider* collider) {
    sf::CircleShape circle(collider->radius);
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineThickness(-2);
    circle.setOutlineColor(getColor(collider));
    circle.setPosition(collider->gameObject->transform.getPosition()  + collider->offset - sf::Vector2f(collider->radius,collider->radius)); // Because SFML take the upperleftcorner
    window.draw(circle);
}
