//
// Created by kelle on 23/01/2017.
//

#include <iostream>
#include "../../../include/GameLogic/Components/Collider.hpp"
#include "../../../include/PhysicsEngine.hpp"
#include "../../../include/GameLogic/Components/Rigidbody.hpp"


PhysicsEngine* Collider::physicsEngine = NULL;

void Collider::awake() {
    Component::awake();
    if (physicsEngine != NULL) {
        Rigidbody *rb = gameObject->getComponent<Rigidbody>();
        if (rb == NULL) {
            Collider::physicsEngine->addStaticBodyToPhysicsWorld(*this);
        }
    } else {
        assert(false);
        // Should have an engine
    }
    // Else we do nothing, the awake of the rigibody will do the work
}