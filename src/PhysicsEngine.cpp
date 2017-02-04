//
// Created by kelle on 23/01/2017.
//

#include "../include/Physics/PhysicsEngine.hpp"
#include "../include/GameLogic/Components/Transform.hpp"
#include "../include/Physics/PhysicsUserData.hpp"
#include <iostream>

using namespace PancakeEngine;

int PhysicsEngine::numberPixelsPerMeter = 72; // TODO to change with the scene

PhysicsEngine::PhysicsEngine() : world(b2Vec2(0, 10)), physicsListener() {
    world.SetContactListener(&physicsListener);
}

PhysicsEngine::~PhysicsEngine() {
}

void PhysicsEngine::update(float dt) {
    world.Step(dt, velocityIterations, positionIterations);
    for ( b2Body* b = world.GetBodyList(); b; b = b->GetNext())
    {
        if (b->GetType() != b2_staticBody) {
            Rigidbody * rb = static_cast<Rigidbody*>(b->GetUserData());
            rb->gameObject->transform.setPosition((sf::Vector2f(b->GetPosition().x * numberPixelsPerMeter,
                                                                 b->GetPosition().y * numberPixelsPerMeter)));
            rb->gameObject->transform.setRotation(b->GetAngle());
        }
    }
}

void PhysicsEngine::addStaticBodyToPhysicsWorld(Collider& c) {
    // TODO Test if ti works with multiple triggers.

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;

    bodyDef.position.Set((c.gameObject->transform.getPosition().x)/numberPixelsPerMeter,
                         (c.gameObject->transform.getPosition().y)/numberPixelsPerMeter);
    bodyDef.userData = (void *) &c;
    //bodyDef.userData = new PhysicsUserData(PhysicsUserData::Type::Collider, nullptr, &c);
    b2Body* body = world.CreateBody(&bodyDef);
    createFixtures(*c.gameObject, *body);
}

void PhysicsEngine::addRigidBodyToPhysicsWorld(Rigidbody &rb) {
    b2BodyDef bodyDef;
    switch (rb.type) {
        case Rigidbody::bodyType::dynamicBody:
            bodyDef.type = b2_dynamicBody;
            break;
        case Rigidbody::bodyType::staticBody:
            bodyDef.type = b2_staticBody;
            break;
        case Rigidbody::bodyType::kinematicBody:
            bodyDef.type = b2_kinematicBody;
            break;
        default:
            assert(false);
    }

    bodyDef.position.Set((rb.gameObject->transform.getPosition().x)/numberPixelsPerMeter,
                         (rb.gameObject->transform.getPosition().y)/numberPixelsPerMeter);
    //bodyDef.userData = new PhysicsUserData(PhysicsUserData::Type::Rigidbody, &rb);
    bodyDef.userData = (void *) &rb;
    //bodyDef.angularVelocity = rb.angularVelocity;
    bodyDef.angularDamping = rb.angularDrag;
    bodyDef.fixedRotation = rb.freezeRotation;
    bodyDef.bullet = rb.isBullet;
    b2Body *body = world.CreateBody(&bodyDef);
    rb.physicsBody = body;

    createFixtures(*rb.gameObject, *body);
}

// Helper functions

void PhysicsEngine::createFixtures(const GameObject& go, b2Body& body) {
    // Create a fixture for each collider
    std::vector<Collider *> v = go.getComponents<Collider>();
    for (unsigned i = 0; i < v.size(); ++i) {
        Collider & c = *v[i];
        b2PolygonShape shape;
        if (dynamic_cast<BoxCollider *>(&c) != NULL) {
            BoxCollider *bc = (BoxCollider *) &c;
            shape.SetAsBox((bc->width/2)/PhysicsEngine::numberPixelsPerMeter, (bc->height/2)/PhysicsEngine::numberPixelsPerMeter,
                           (b2Vec2(c.offset.x/PhysicsEngine::numberPixelsPerMeter,c.offset.y/PhysicsEngine::numberPixelsPerMeter)),
                           c.gameObject->transform.getRotation());
        } else {
            assert(false); // Collider unknown
        }
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = c.density;
        fixtureDef.friction = c.friction;
        fixtureDef.restitution = c.bounciness;
        fixtureDef.isSensor = c.isTrigger;
        fixtureDef.userData = (void *) &c;
        body.CreateFixture(&fixtureDef);
    }
}


