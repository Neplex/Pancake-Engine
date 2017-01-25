//
// Created by kelle on 24/01/2017.
//

#include "../include/Rigidbody.hpp"
#include "../include/Collider.hpp"
#include "../include/PhysicsEngine.hpp"

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

Rigidbody::Rigidbody() : type(bodyType::dynamicBody), angularDrag(0.05f), drag(0),
                         gravityScale(1), freezeRotation(false), mass(1)
{

}
