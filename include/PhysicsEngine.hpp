//
// Created by kelle on 23/01/2017.
//

#ifndef PANCAKE_PHYSICSENGINE_HPP
#define PANCAKE_PHYSICSENGINE_HPP

#include <Box2D/Box2D.h>

/**
 * Provide an interface to interact with the box2D physics engine.
 */
class PhysicsEngine {

public:
    const static int velocityIterations = 8; // how strongly to correct velocity
    const static int positionIterations = 3; // how strongly to correct position
    /**
     * Simulate physics for the given time.
     * @param dt The length of time passed to simulate (seconds).
     */
    void update(float dt);
    ~PhysicsEngine();

private:
    //b2World world;
};


#endif //PANCAKE_PHYSICSENGINE_HPP
