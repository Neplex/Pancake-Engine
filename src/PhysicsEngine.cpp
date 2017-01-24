//
// Created by kelle on 23/01/2017.
//

#include "../include/PhysicsEngine.hpp"

PhysicsEngine::PhysicsEngine() {
    world = new b2World(b2Vec2(0, -10));
}

PhysicsEngine::~PhysicsEngine() {
    delete world;
}

void PhysicsEngine::update(float dt) {

}

void PhysicsEngine::addStaticBodyToPhysicsWorld(Collider& c) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(c.gameObject->transform->getPosition().x + c.offset.x,
                         c.gameObject->transform->getPosition().y + c.offset.y);
    b2Body* body = world->CreateBody(&bodyDef);
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
