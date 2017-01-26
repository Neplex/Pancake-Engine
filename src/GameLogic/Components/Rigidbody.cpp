//
// Created by kelle on 24/01/2017.
//

#include <iostream>
#include "../../../include/GameLogic/Components/Rigidbody.hpp"
#include "../../../include/GameLogic/Components/Collider.hpp"
#include "../../../include/PhysicsEngine.hpp"

PhysicsEngine * Rigidbody::physicsEngine = NULL;

void Rigidbody::awake() {
    Component::awake();
    if (physicsEngine != NULL) {
        Rigidbody::physicsEngine->addRigidBodyToPhysicsWorld(*this);
    } else {
        assert(false);
        // Should have an engine
    }
    std::vector<Collider *> v = gameObject->getComponents<Collider>();
    for (int i = 0; i < v.size(); ++i) {
        v[i]->attachedRigidbody = this;
    }
}

void Rigidbody::start() {
    Component::start();
    std::cout << physicsBody->GetLinearVelocity().x << std::endl;
    //applyTorque(1000000);
    std::cout << physicsBody->GetLinearVelocity().x << std::endl;
}

void Rigidbody::update() {
    Component::update();
    applyForce(sf::Vector2f(3, 0));
    //applyForce(sf::Vector2f(10500, 0));
    //std::cout << physicsBody->GetPosition().x << std::endl;
    //applyForce(sf::Vector2f(5, 0));
}

Rigidbody::Rigidbody() : type(bodyType::dynamicBody), angularDrag(0.05f), drag(0),
                         gravityScale(1), freezeRotation(false), mass(1)
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


