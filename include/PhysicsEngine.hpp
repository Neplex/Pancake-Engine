//
// Created by kelle on 23/01/2017.
//

#ifndef PANCAKE_PHYSICSENGINE_HPP
#define PANCAKE_PHYSICSENGINE_HPP

#include <Box2D/Box2D.h>
#include "Collider.hpp"
#include "GameObject.hpp"
#include "BoxCollider.hpp"

/**
 * Provide an interface to interact with the box2D physics engine.
 */
class PhysicsEngine {

public:
    static const int velocityIterations = 8; // how strongly to correct velocity
    static const int positionIterations = 3; // how strongly to correct position

    PhysicsEngine();
    ~PhysicsEngine();
    /**
     * Simulate physics for the given time.
     * @param dt The length of time passed to simulate (seconds).
     */
    static void update(float dt);

private:
    void addStaticBodyToPhysicsWorld(Collider& c);
    b2World* world;
};



#endif //PANCAKE_PHYSICSENGINE_HPP
