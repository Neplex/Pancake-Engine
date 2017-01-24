//
// Created by nicolas on 22/01/17.
//

#ifndef PANCAKE_WINDOW_HPP
#define PANCAKE_WINDOW_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include "SceneManager.hpp"
#include "InputHandler.hpp"
#include "BoxCollider.hpp"

/**
 * Window and render loop
 */
class Window {
public:
    Window(SceneManager& s, InputHandler& ih);

    /**
     * Render one frame
     */
    void render();
    /**
     * Handle the events received by the window (keyboard, mouse, joystick)
     */
    void handleEvent();
    /**
     * Set debug display to True or False
     * Display colider
     * @param val
     */
    void setDebug(bool val = true);

private:
    SceneManager& scenes;
    InputHandler& inputHandler;
    sf::RenderWindow window;
    bool debug;

    /**
     * Draw all elements (SpriteRenderer) of the current scene
     */
    void drawScene();
    /**
     * Draw debug elements
     */
    void drawDebug();

    void draw(const BoxCollider * boxCollider);
};

#endif //PANCAKE_WINDOW_HPP
