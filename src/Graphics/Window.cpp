//
// Created by nicolas on 22/01/17.
//

#include <iostream>
#include <cmath>
#include <Graphics/Window.hpp>
#include <GameLogic.hpp>
#include <Debug/Debug.hpp>

using namespace PancakeEngine;

Window::Window() : window(sf::VideoMode::getDesktopMode(), "", sf::Style::Fullscreen) {
    FPS = 60.0f;
    timeBetweenTwoFrames = sf::seconds((1.0f/FPS));
    clock = sf::Clock();
    window.setVerticalSyncEnabled(false); ///< Don't activate it ! It does not fit with our type of game loop
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

std::pair<unsigned, unsigned> splitScreen(unsigned nbPart) {
    std::pair<unsigned, unsigned> dimensions;
    double s = sqrt(nbPart);
    dimensions.first = (unsigned)ceil(s);
    dimensions.second = dimensions.first < s ? dimensions.first+1 : dimensions.first;
    return dimensions;
}

void Window::draw(const GameObject * gameObject) {
    sf::Transform transform = gameObject->transform.getWorldTransformMatrix();

    // Renderer
    const std::vector<Renderer *> rs = gameObject->getComponents<Renderer>();
    for (Renderer *r : rs) window.draw(r->getSprite(), transform);

    // TileMapRenderer
    const std::vector<TileMapRenderer *> tmrs = gameObject->getComponents<TileMapRenderer>();
    for (TileMapRenderer *tmr : tmrs)
        for (sf::Sprite s : tmr->getChunksSprites())
            window.draw(s, transform);

    // Debug elements
    if (debug) {
        // Box collider
        const std::vector<BoxCollider *> boxColliders = gameObject->getComponents<BoxCollider>();
        for (BoxCollider *bc : boxColliders) {
            if (!bc->isSleeping()) draw(bc, transform);
        }

        // Circle collider
        const std::vector<CircleCollider *> circleColliders = gameObject->getComponents<CircleCollider>();
        for (CircleCollider *bc : circleColliders) if (!bc->isSleeping()) draw(bc, transform);
    }
}

void Window::drawScene() {
    // Get views
    std::vector<std::pair<sf::View, Camera*>> views;
    // TODO: create a fix order for camera
    for (GameObject* layer : SceneManager::getCurrentScene()->layers)
        for (GameObject* go : layer->getChilds())
            for (Camera* c : go->getComponents<Camera>()) {
                sf::View view = c->view;
                view.setCenter(c->gameObject->transform.getWorldPosition());
                view.setRotation(c->gameObject->transform.getWorldRotation());
                std::pair<sf::View, Camera*> pair;
                pair.first = view;
                pair.second = c;
                views.push_back(pair);
            }

    if (views.size() == 0) {
        std::pair<sf::View, Camera*> pair;
        pair.first = window.getDefaultView();
        pair.second = NULL;
        views.push_back(pair);
    }

    std::pair<unsigned, unsigned> nbElem = splitScreen((unsigned) views.size());
    float width = (float)1.0 / nbElem.first;
    float height = (float)1.0 / nbElem.second;

    // Draw all views
    unsigned nbCamera = (unsigned) views.size();
    for (unsigned i = 0; i < nbCamera; i++) {
        views[i].first.setViewport(sf::FloatRect(
                (i%nbElem.first) * width+.003,
                (i/nbElem.second) * height+.005,
                width-.007,
                height-.01
        ));
        window.setView(views[i].first);

        if (views[i].second != NULL && views[i].second->background != NULL) {
            sf::Sprite bg;
            bg.setTexture(*views[i].second->background);
            bg.setScale(
                    sf::VideoMode::getDesktopMode().width  / bg.getGlobalBounds().width,
                    sf::VideoMode::getDesktopMode().height / bg.getGlobalBounds().height
            );
            bg.setPosition(
                    views[i].second->gameObject->transform.getWorldPosition().x - bg.getGlobalBounds().width  / 2,
                    views[i].second->gameObject->transform.getWorldPosition().y - bg.getGlobalBounds().height / 2
            );
            window.draw(bg);
        }

        // Draw gameObjects
        for (GameObject* layer : SceneManager::getCurrentScene()->layers) {
            std::vector<GameObject *> layerElems = layer->getChilds();
            for (GameObject *gameObject : layerElems) draw(gameObject);
        }
    }

    // Draw HUD
    window.setView(window.getDefaultView());
    std::vector<GameObject*> guiElems = SceneManager::getCurrentScene()->gui->getChilds();
    for (GameObject* go : guiElems) draw(go);
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

void Window::draw(const BoxCollider * collider, sf::RenderStates renderStates) {
    // To draw from center
    sf::Vertex vertices[6] = {
            sf::Vertex(sf::Vector2f(-collider->width/2, -collider->height/2)),
            sf::Vertex(sf::Vector2f( collider->width/2, -collider->height/2)),
            sf::Vertex(sf::Vector2f( collider->width/2,  collider->height/2)),
            sf::Vertex(sf::Vector2f(-collider->width/2, -collider->height/2)),
            sf::Vertex(sf::Vector2f(-collider->width/2,  collider->height/2)),
            sf::Vertex(sf::Vector2f( collider->width/2,  collider->height/2))
    };
    // Color for type
    sf::Color color = getColor(collider);
    for (int i = 0; i < 6; ++i) vertices[i].color = color;
    // Transform
    renderStates.transform.translate(collider->offset);
    window.draw(vertices, 6, sf::LinesStrip, renderStates);
}

void Window::draw(const CircleCollider* collider, sf::RenderStates renderStates) {
    sf::CircleShape circle(collider->radius);
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineThickness(-2);
    circle.setOutlineColor(getColor(collider));
    circle.setPosition(-sf::Vector2f(collider->radius,collider->radius)); // Because SFML take the upperleftcorner
    renderStates.transform.translate(collider->offset);
    window.draw(circle, renderStates);
}
