//
// Created by nicolas on 22/01/17.
//

#include <iostream>
#include <math.h>
#include <GameLogic/Components/CircleCollider.hpp>
#include <GameLogic.hpp>

using namespace PancakeEngine;

Window::Window(SceneManager& s) : scenes(s), window(sf::VideoMode::getDesktopMode(), "", sf::Style::Close) {
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
    if (nbPart < 3) return {nbPart, 1};
    std::pair<unsigned, unsigned> dimensions;
    double s = sqrt(nbPart);
    dimensions.first = (unsigned)ceil(s);
    dimensions.second = dimensions.first < s ? dimensions.first+1 : dimensions.first;
    return dimensions;
}

void Window::drawScene() {
    // Set view
    std::vector<sf::View> views;
    for (GameObject* go : scenes.getCurrentScene()->gameObjects) {
        Camera* c = go->getComponent<Camera>();
        if (c != NULL) {
            sf::View view = c->view;
            view.setCenter(c->gameObject->transform.getPosition());
            view.setRotation(c->gameObject->transform.getRotation());
            views.push_back(view);
        }
    }
    if (views.size() == 0) views.push_back(window.getDefaultView());

    std::pair<unsigned, unsigned> nbElem = splitScreen((unsigned) views.size());
    float width = (float)1.0 / nbElem.first;
    float height = (float)1.0 / nbElem.second;

    unsigned nbCamera = (unsigned) views.size();
    for (unsigned i = 0; i < nbCamera; i++) {
        views[i].setViewport(sf::FloatRect(
                (i%nbElem.first) * width ,
                (i/nbElem.second) * height * (nbCamera > 2),
                width, height
        ));
        if (nbCamera < 3)
            views[i].setSize(
                    width * sf::VideoMode::getDesktopMode().width * 1.5,
                    height * sf::VideoMode::getDesktopMode().height * 1.5
            );
        window.setView(views[i]);

        sf::RenderStates renderStates;
        for (GameObject *gameObject : scenes.getCurrentScene()->gameObjects) {
            renderStates.transform = gameObject->transform.getTransformMatrix();

            // Get SpriteRenderer
            const std::vector<SpriteRenderer *> spriteRenderers = gameObject->getComponents<SpriteRenderer>();
            for (SpriteRenderer *sr : spriteRenderers) window.draw(sr->sprite, renderStates);

            // Get AnimationRenderer
            const std::vector<AnimationRenderer *> animationRenderers = gameObject->getComponents<AnimationRenderer>();
            for (AnimationRenderer *ar : animationRenderers) window.draw(ar->sprite, renderStates);

            // Get Animator
            const std::vector<Animator *> animators = gameObject->getComponents<Animator>();
            for (Animator *ar : animators) if (ar->getCurrentAnimation() != NULL) window.draw(ar->getCurrentAnimation()->sprite, renderStates);

            // Debug elements
            if (debug) {
                // Box collider
                const std::vector<BoxCollider *> boxColliders = gameObject->getComponents<BoxCollider>();
                for (BoxCollider *bc : boxColliders) draw(bc);
                // Circle collider
                const std::vector<CircleCollider *> circleColliders = gameObject->getComponents<CircleCollider>();
                for (CircleCollider *bc : circleColliders) draw(bc);
            }
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
