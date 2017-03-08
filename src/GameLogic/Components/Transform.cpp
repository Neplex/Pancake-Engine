//
// Created by Darenn on 17/01/2017.
//

#include <GameLogic/Components/Transform.hpp>
#include <Box2D/Box2D.h>
#include <Physics/PhysicsEngine.hpp>

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

sf::Vector2f Transform::getWorldPosition() const {
    if (gameObject->parent == NULL) return getLocalPosition();
    return getWorldTransformMatrix() * transform.getOrigin();
}

sf::Vector2f Transform::getLocalPosition() const {
    return transform.getPosition();
}

float Transform::getWorldRotation() const {
    if (gameObject->parent == NULL) return getLocalRotation();
    return gameObject->parent->transform.getWorldRotation() + transform.getRotation();
}

float Transform::getLocalRotation() const {
    return transform.getRotation();
}

sf::Transform Transform::getWorldTransformMatrix() const {
    if (gameObject->parent == NULL) return getLocalTransformMatrix();
    sf::Transform t = gameObject->parent->transform.getWorldTransformMatrix();
    t.combine(transform.getTransform());
    return t;
}

sf::Transform Transform::getLocalTransformMatrix() const {
    return transform.getTransform();
}