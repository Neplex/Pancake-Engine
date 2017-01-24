//
// Created by kelle on 23/01/2017.
//

#ifndef PANCAKE_PHYSICSENGINE_HPP
#define PANCAKE_PHYSICSENGINE_HPP

#include <Box2D/Box2D.h>
#include "GameObject.hpp"
#include "BoxCollider.hpp"

class Collider;
class Rigidbody;

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
    void update(float dt);

    /**
     * Add a static body to the physics world according to a given collider.
     * That allows to have other gameobject with rigidbody to collide this object.
     * @param c The collider of the object to create in the world.
     */
    void addStaticBodyToPhysicsWorld(Collider& c);

    /**
     * Add a rigidbody to the physics world.
     * It can be dynamic or kinematic.
     * @param rb
     */
    void addRigidBodyToPhysicsWorld(Rigidbody& rb);

private:
    b2World* world;
};



#endif //PANCAKE_PHYSICSENGINE_HPP
