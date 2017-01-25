//
// Created by nicolas on 22/01/17.
//

#include "../include/Window.hpp"
#include "../include/SpriteRenderer.hpp"
#include "../include/Camera.hpp"

Window::Window(SceneManager& s, InputHandler& ih) : scenes(s), inputHandler(ih), window(sf::VideoMode::getDesktopMode(), "", sf::Style::Close) {
    window.setVerticalSyncEnabled(true);
    window.setActive(false);
}

void Window::render() {
    if (window.isOpen()) {
        window.clear();
        drawScene();
        if (debug) drawDebug();
        window.display();
    }
}

void Window::setDebug(bool val) {
    debug = val;
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

        // Get spriteRenderer
        const SpriteRenderer * spriteRenderer = gameObject->getComponent<SpriteRenderer>();
        if (spriteRenderer != NULL) {
            sf::RenderStates renderStates;
            renderStates.transform = gameObject->transform->getTransformMatrix();
            window.draw(spriteRenderer->sprite, renderStates);
        }
    }
}

void Window::handleEvent() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::GainedFocus:
                break;

            case sf::Event::LostFocus:
                break;

            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Key::Escape)
                    window.close();
                else
                    inputHandler.handleInput(event.key.code);
                break;

            case sf::Event::MouseMoved:
                inputHandler.handleMouse(event.mouseMove.x, event.mouseMove.y);
                break;

            case sf::Event::MouseButtonPressed:
                inputHandler.handleInput(event.mouseButton.button);
                break;

            default:
                break;
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