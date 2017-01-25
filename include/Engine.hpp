//
// Created by Darenn on 24/01/2017.
//

#ifndef PANCAKE_ENGINE_HPP
#define PANCAKE_ENGINE_HPP


#include "SceneManager.hpp"
#include "InputHandler.hpp"
#include "Window.hpp"
#include "PhysicsEngine.hpp"
#include "Time.hpp"

class Engine {

public:
    static constexpr double MS_PER_UPDATE = 100 / 6;

    Engine();
    void run();

private:

    SceneManager sceneManager;
    InputHandler inputHandler;
    Window window;
    PhysicsEngine physicsEngine;
    Time time;

    /*
     * Update the engine (physics and logic) with a constant time.
     */
    void update();
};


#endif //PANCAKE_ENGINE_HPP
