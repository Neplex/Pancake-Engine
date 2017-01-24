//
// Created by kelle on 23/01/2017.
//

#include <iostream>
#include "../include/Collider.hpp"
#include "../include/PhysicsEngine.hpp"
#include "../include/Rigidbody.hpp"


PhysicsEngine* Collider::physicsEngine = NULL;

void Collider::awake() {
    Component::awake();
    if (physicsEngine != NULL) {
        Rigidbody *rb = gameObject->getComponent<Rigidbody>();
        if (rb == NULL) {
            std::cout << "no rigibody" << std::endl;
            Collider::physicsEngine->addStaticBodyToPhysicsWorld(*this);
        }
    } else {
        assert(false);
        // Should have an engine
    }
    // Else we do nothing, the awake of the rigibody will do the work
}