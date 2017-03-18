//
// Created by kelle on 03/02/2017.
//

#include "Physics/PhysicsListener.hpp"
namespace PancakeEngine {
    void PhysicsListener::onContact(b2Contact *contact,
                                    void (GameObject::*triggerFunction)(const Collider &, const Collider &),
                                    void (GameObject::*collisionFunction)(const Collision &), bool exiting) {
        if (contact->IsTouching() || exiting) {
            // If only one of them is a sensor call OnTrigger on the sensor GameObject
            if (contact->GetFixtureA()->IsSensor() ^ contact->GetFixtureB()->IsSensor()) {
                const Collider *sensor;
                const Collider *other;
                if (contact->GetFixtureA()->IsSensor()) {
                    sensor = static_cast<Collider *>(contact->GetFixtureA()->GetUserData());
                    other = static_cast<Collider *>(contact->GetFixtureB()->GetUserData());
                } else if (contact->GetFixtureB()->IsSensor()) {
                    sensor = static_cast<Collider *>(contact->GetFixtureB()->GetUserData());
                    other = static_cast<Collider *>(contact->GetFixtureA()->GetUserData());
                }
                (sensor->gameObject->*triggerFunction)(*sensor, *other);
                // If none of them is a sensor, call OnCollision on both ot them
            } else if (!contact->GetFixtureA()->IsSensor() && !contact->GetFixtureB()->IsSensor()) {
                const Collision collA(*(static_cast<Collider *>(contact->GetFixtureA()->GetUserData())),
                                      *(static_cast<Collider *>(contact->GetFixtureB()->GetUserData())),
                                      contact->GetRestitution(), contact->GetFriction(),
                                      contact->GetTangentSpeed());
                (static_cast<Collider *>(contact->GetFixtureA()->GetUserData())->gameObject->*collisionFunction)(collA);

                const Collision collB(*(static_cast<Collider *>(contact->GetFixtureB()->GetUserData())),
                                      *(static_cast<Collider *>(contact->GetFixtureA()->GetUserData())),
                                      contact->GetRestitution(), contact->GetFriction(),
                                      contact->GetTangentSpeed());
                (static_cast<Collider *>(contact->GetFixtureB()->GetUserData())->gameObject->*collisionFunction)(collB);
            } // Else if both are sensor do nothing
        } // Else if fixtures are not touching do nothing
    }
}