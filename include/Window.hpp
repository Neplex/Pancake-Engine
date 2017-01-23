//
// Created by nicolas on 22/01/17.
//

#ifndef PANCAKE_WINDOW_HPP
#define PANCAKE_WINDOW_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include "Scene.hpp"
#include "InputHandler.hpp"

class Window {
public:
    Window(Scene& s, InputHandler& ih);

    void run();

private:
    Scene& scene;
    InputHandler& inputHandler;
    sf::RenderWindow window;

    void handleEvent();
    void drawScene();
};

#endif //PANCAKE_WINDOW_HPP
