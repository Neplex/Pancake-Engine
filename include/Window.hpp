//
// Created by nicolas on 22/01/17.
//

#ifndef PANCAKE_WINDOW_HPP
#define PANCAKE_WINDOW_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include "InputHandler.hpp"
#include "SceneManager.hpp"

/**
 * Window and render loop
 */
class Window {
public:
    Window(SceneManager& s, InputHandler& ih);

    /**
     * Start the render loop
     */
    void run();

private:
    SceneManager& scenes;
    InputHandler& inputHandler;
    sf::RenderWindow window;

    /**
     * Handle the events received by the window (keyboard, mouse, joystick)
     */
    void handleEvent();
    /**
     * Draw all elements (SpriteRenderer) of the current scene
     */
    void drawScene();
};

#endif //PANCAKE_WINDOW_HPP
