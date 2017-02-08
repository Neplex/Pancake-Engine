//
// Created by kelle on 23/01/2017.
//

#include <iostream>
#include "../../../include/GameLogic/Components/Collider.hpp"
#include "../../../include/Physics/PhysicsEngine.hpp"
#include "../../../include/GameLogic/Components/Rigidbody.hpp"

using namespace PancakeEngine;

PhysicsEngine* Collider::physicsEngine = NULL;

PancakeEngine::Collider::Collider() {
    fixture = nullptr;
}

void Collider::awake() {
    Component::awake();
    if (physicsEngine != NULL) {
        Rigidbody* const rb = gameObject->getComponent<Rigidbody>();
        if (rb == NULL) {
            if (fixture == nullptr) // If fixture is set, it's because it was already added
                Collider::physicsEngine->addStaticBodyToPhysicsWorld(*this);
        }
    } else {
        assert(false);
        // Should have an engine
    }
    // Else we do nothing, the awake of the rigibody will do the work
}

Collider::~Collider() {
    if (gameObject->getComponent<Rigidbody>() == nullptr && fixture != nullptr) { // we let the rigidbody destroy the body if there is one
        physicsEngine->removeBody(fixture->GetBody());
        fixture = nullptr;
    }
}
