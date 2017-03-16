//
// Created by kelle on 24/01/2017.
//

#include <iostream>
#include "../../../include/GameLogic/Components/Rigidbody.hpp"
#include "../../../include/GameLogic/Components/Collider.hpp"
#include "../../../include/Physics/PhysicsEngine.hpp"
#include "../../../include/Inputs/Input.hpp"

using namespace PancakeEngine;

PhysicsEngine * Rigidbody::physicsEngine = NULL;

void Rigidbody::awake() {
    Component::awake();
    if (physicsEngine != NULL) {
        Rigidbody::physicsEngine->addRigidBodyToPhysicsWorld(*this);
    } else {
        assert(false);
        // Should have an engine
    }
    std::vector<Collider*> v = gameObject->getComponents<Collider>();
    for (unsigned i = 0; i < v.size(); ++i) {
        v[i]->attachedRigidbody = this;
    }
}

void Rigidbody::start() {
    Component::start();
}

void Rigidbody::update() {
    Component::update();
}

Rigidbody::Rigidbody() : type(bodyType::dynamicBody), angularVelocity(), drag(0), freezeRotation(false),
                         gravityScale(1), mass(1), angularDrag(0.05f), bullet(false), physicsBody(nullptr), velocity(sf::Vector2f(0,0))
{

}


void Rigidbody::applyForce(const sf::Vector2f& force) {
    physicsBody->ApplyForceToCenter(b2Vec2(force.x, force.y), true);
}

void Rigidbody::applyLinearImpulse(const sf::Vector2f& impulse) {
    physicsBody->ApplyLinearImpulseToCenter(b2Vec2(impulse.x, impulse.y), true);
}

void Rigidbody::applyTorque(float torque) {
    physicsBody->ApplyTorque(torque, true);
}

void Rigidbody::applyAngularImpulse(float impulse) {
    physicsBody->ApplyAngularImpulse(impulse, true);
}

void Rigidbody::applyForceAtPosition(const sf::Vector2f& force, const sf::Vector2f& position) {
    physicsBody->ApplyForce(b2Vec2(force.x, force.y), b2Vec2(position.x, position.y), true);
}

void Rigidbody::applyLinearImpulseAtPosition(const sf::Vector2f& impulse, const sf::Vector2f& position) {
    physicsBody->ApplyLinearImpulse(b2Vec2(impulse.x, impulse.y), b2Vec2(position.x, position.y), true);
}

Rigidbody::bodyType Rigidbody::getType() const {
    return type;
}

float Rigidbody::getAngularVelocity() const {
    if (physicsBody)
        return physicsBody->GetAngularVelocity();
    else
        return angularVelocity;
}

float Rigidbody::getDrag() const {
    if (physicsBody)
        return physicsBody->GetLinearDamping();
    else
        return drag;
}

bool Rigidbody::isFreezeRotation() const {
    if (physicsBody)
        return physicsBody->IsFixedRotation();
    else
        return freezeRotation;
}

float Rigidbody::getGravityScale() const {
    if (physicsBody)
        return physicsBody->GetGravityScale();
    else
        return gravityScale;
}

float Rigidbody::getAngularDrag() const {
    if (physicsBody)
        return physicsBody->GetAngularDamping();
    else
        return angularDrag;
}

bool Rigidbody::isBullet() const {
    if (physicsBody) {
        return physicsBody->IsBullet();
    } else {
        return bullet;
    }
}

const sf::Vector2f Rigidbody::getVelocity() const {
    if (physicsBody) {
        return sf::Vector2f(physicsBody->GetLinearVelocity().x, physicsBody->GetLinearVelocity().y);
    } else {
        return velocity;
    }
}

void Rigidbody::setType(Rigidbody::bodyType type) {
    Rigidbody::type = type;
    if (physicsBody) {
        switch (type) {
            case bodyType::dynamicBody:
                physicsBody->SetType(b2_dynamicBody);
                break;
            case bodyType::kinematicBody:
                physicsBody->SetType(b2_kinematicBody);
                break;
            case bodyType::staticBody:
                physicsBody->SetType(b2_staticBody);
                break;
            default:
                assert(false); // Imposible to have another type of body
        }
    }

}

void Rigidbody::setAngularVelocity(float angularVelocity) {
    Rigidbody::angularVelocity = angularVelocity;
    if (physicsBody)
        physicsBody->SetAngularVelocity(angularVelocity);
}

void Rigidbody::setDrag(float drag) {
    Rigidbody::drag = drag;
    if (physicsBody)
        physicsBody->SetLinearDamping(drag);
}

void Rigidbody::setFreezeRotation(bool freezeRotation) {
    Rigidbody::freezeRotation = freezeRotation;
    if (physicsBody)
        physicsBody->SetFixedRotation(freezeRotation);
}

void Rigidbody::setGravityScale(float gravityScale) {
    Rigidbody::gravityScale = gravityScale;
    if (physicsBody)
        physicsBody->SetGravityScale(gravityScale);
}

void Rigidbody::setAngularDrag(float angularDrag) {
    Rigidbody::angularDrag = angularDrag;
    if (physicsBody)
        physicsBody->SetAngularDamping(angularDrag);
}

void Rigidbody::setIsBullet(bool isBullet) {
    Rigidbody::bullet = isBullet;
    if (physicsBody)
        physicsBody->SetBullet(isBullet);
}

void Rigidbody::setVelocity(const sf::Vector2f &velocity) {
    Rigidbody::velocity = velocity;
    const b2Vec2 vel = b2Vec2(velocity.x, velocity.y);
    if (physicsBody)
        physicsBody->SetLinearVelocity(vel);
}

Rigidbody::~Rigidbody() {
    if (physicsBody != nullptr) {
        physicsBody->SetUserData(nullptr);
        physicsEngine->removeBody(physicsBody);
        /*std::vector<Collider *> v = gameObject->getComponents<Collider>();
        for (Collider* c : v) {
            c->fixture = nullptr;
        }*/
        physicsBody = nullptr;
    }
}

float Rigidbody::getMass() const {
    if (physicsBody)
        return physicsBody->GetMass();
    else
        return mass;
}



