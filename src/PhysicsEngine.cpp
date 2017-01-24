//
// Created by kelle on 23/01/2017.
//

#include "../include/PhysicsEngine.hpp"
#include "Box2D/Box2D.h"

PhysicsEngine::PhysicsEngine() {
    world = new b2World(b2Vec2(0, -10));
}
