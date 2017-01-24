//
// Created by kelle on 23/01/2017.
//

#include "../include/Collider.hpp"
#include "../include/PhysicsEngine.hpp"

void Collider::awake() {
    Component::awake();
    PhysicsEngine::getInstance().addStaticBodyToPhysicsWorld(*this);
}