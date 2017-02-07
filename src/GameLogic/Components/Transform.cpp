//
// Created by Darenn on 17/01/2017.
//

#include "../../../include/GameLogic/Components/Transform.hpp"
#include "GameLogic/GameObject.hpp"
#include <Box2D/Box2D.h>
#include "Physics/PhysicsEngine.hpp"

using namespace PancakeEngine;

Transform::Transform() : transform() {
    transform.setPosition(0, 0);
}

void Transform::setPosition(const sf::Vector2f &newPos) {
    transform.setPosition(newPos);
    Collider * c = gameObject->getComponent<Collider>();
    Rigidbody* rb = gameObject->getComponent<Rigidbody>();
    if (rb != nullptr && rb->physicsBody != nullptr) { // Have to check that because the physicsBody is set at the awake
        rb->physicsEngine->setPosition(newPos, *rb->physicsBody);
    } else if (c != nullptr && c->fixture != nullptr){
        c->physicsEngine->setPosition(newPos, *c->fixture->GetBody());
    }
}

void Transform::setRotation(float angle) {
    transform.setRotation(angle);
    Collider * c = gameObject->getComponent<Collider>();
    Rigidbody* rb = gameObject->getComponent<Rigidbody>();
    if (rb != nullptr && rb->physicsBody != nullptr) { // Have to check that because the physicsBody is set at the awake
        rb->physicsEngine->setRotation(angle, *rb->physicsBody);
    } else if (c != nullptr && c->fixture != nullptr){
        c->physicsEngine->setRotation(angle, *c->fixture->GetBody());
    }
}
