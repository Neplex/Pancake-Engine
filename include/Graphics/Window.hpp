//
// Created by nicolas on 22/01/17.
//

#ifndef PANCAKE_WINDOW_HPP
#define PANCAKE_WINDOW_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include "../SceneManager.hpp"
#include "../GameLogic/Components/BoxCollider.hpp"

/**
 * Window and render loop
 */
class Window {
public:
    Window(SceneManager& s);

    bool isClosed() { return !window.isOpen(); }

    /**
     * Render one frame
     */
    void render();
    /**
     * Set debug display to True or False
     * Display colider
     * @param val
     */
    void setDebug(bool val = true);
    /**
     * Set the framerate. (FPS: frames per second)
     * @param framerate The new framerate in FPS.
     */
    void setFrameRate(float framerate);

private:
    friend class Engine;
    SceneManager& scenes;
    sf::RenderWindow window;
    bool debug;
    float FPS;
    sf::Time timeBetweenTwoFrames;
    sf::Clock clock; ///< Used to limit the FPS

    /**
     * Draw all elements (SpriteRenderer, AnimationRenderer) of the current scene
     */
    void drawScene();

    // Debug
    void draw(const BoxCollider * boxCollider);
    sf::Color getColor(const Collider * collider);
};

#endif //PANCAKE_WINDOW_HPP
