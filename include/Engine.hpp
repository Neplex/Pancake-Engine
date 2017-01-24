//
// Created by Darenn on 24/01/2017.
//

#ifndef PANCAKE_ENGINE_HPP
#define PANCAKE_ENGINE_HPP


#include "SceneManager.hpp"
#include "InputHandler.hpp"
#include "Window.hpp"
#include "PhysicsEngine.hpp"

class Engine {

public:
    static constexpr float MS_PER_UPDATE = 18.288f;

    Engine();
    void run();

private:
    SceneManager sceneManager;
    InputHandler inputHandler;
    Window window;
    PhysicsEngine physicsEngine;

    void update(float dt);
};


#endif //PANCAKE_ENGINE_HPP
