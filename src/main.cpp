#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/Scene.hpp"
#include "../include/SpriteRenderer.hpp"

int main() {
    Scene s = Scene("TestScene");
    GameObject * go = new GameObject("Bajiru");
    SpriteRenderer spriteRenderer1 = SpriteRenderer();
    go->addComponent(spriteRenderer1);
    s.addGameObject(go);
    s.awake();
    s.start();

    sf::RenderWindow window(sf::VideoMode(1280, 720), s.name);
    window.setVerticalSyncEnabled(true);

    while (window.isOpen()) {
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
                    break;

                case sf::Event::MouseMoved:
                    break;

                case sf::Event::MouseButtonPressed:
                    break;

                default:
                    break;
            }
        }

        s.update();
        s.lateUpdate();
        for (int i = 0; i < s.gameObjects.size(); ++i) {
            const SpriteRenderer * spriteRenderer = s.gameObjects[i]->getComponent<SpriteRenderer>();
            if (spriteRenderer != NULL)
                window.draw(spriteRenderer->sprite);
        }
        window.clear();
        window.display();
    }

    return EXIT_SUCCESS;
}