//
// Created by nicolas on 22/01/17.
//

#include "../include/Window.hpp"
#include "../include/SpriteRenderer.hpp"

Window::Window(Scene& s, InputHandler& ih) : scene(s), inputHandler(ih), window(sf::VideoMode::getDesktopMode(), s.name, sf::Style::Fullscreen) {
    window.setVerticalSyncEnabled(true);
    window.setActive(false);
}

void Window::run() {
    while (window.isOpen()) {
        scene.update();
        scene.lateUpdate();
        handleEvent();
        drawScene();
    }
}

void Window::drawScene() {
    window.clear();
    for (int i = 0; i < scene.gameObjects.size(); ++i) {
        const SpriteRenderer *spriteRenderer = scene.gameObjects[i]->getComponent<SpriteRenderer>();
        if (spriteRenderer != NULL)
            window.draw(spriteRenderer->sprite);
    }
    window.display();
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