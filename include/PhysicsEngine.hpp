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
    const int velocityIterations = 8; // how strongly to correct velocity
    const int positionIterations = 3; // how strongly to correct position

    PhysicsEngine();
    /**
     * Simulate physics for the given time.
     * @param dt The length of time passed to simulate (seconds).
     */
    void update(float dt);
    void addStaticBodyToPhysicsWorld(Collider c) {
        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.position.Set(c.gameObject->transform->getPosition().x + c.offset.x,
                             c.gameObject->transform->getPosition().y + c.offset.y);
        b2Body* body = world.CreateBody(&bodyDef);
        b2PolygonShape shape;
        if(dynamic_cast<BoxCollider*>(&c) != NULL) {
            BoxCollider * bc = (BoxCollider *)&c;
            shape.SetAsBox(bc->width, bc->height);
        } else {
            assert(false);
        }
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = c.density;
        fixtureDef.friction = c.friction;
        body->CreateFixture(&fixtureDef);
    }
    ~PhysicsEngine();

private:
    static b2Vec2 gravity;
    static b2World world;
};


#endif //PANCAKE_PHYSICSENGINE_HPP
