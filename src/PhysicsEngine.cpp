//
// Created by kelle on 23/01/2017.
//

#include <crtdbg.h>
#include "../include/PhysicsEngine.hpp"

PhysicsEngine::PhysicsEngine() {
    gravity = b2Vec2(0, -10);
    world = b2World(gravity);
}