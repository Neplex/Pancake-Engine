/*
     Copyright (C) 2016-2017 Keller Darenn - keller.darenn@gmail.com

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

/**
 * \file        PhysicsListener.hpp
 * \author      Darenn Keller - keller.darenn@gmail.com
 */

#ifndef PANCAKE_PHYSICSLISTENER_HPP
#define PANCAKE_PHYSICSLISTENER_HPP

#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include "../GameLogic/Components/Collider.hpp"
#include "GameLogic/GameObject.hpp"
#include "Collision.hpp"

namespace PancakeEngine {

    class PhysicsListener : public b2ContactListener {

        /**
         * @details If only one of them is a sensor call OnTrigger on the sensor GameObject.
         * If none of them is a sensor, call OnCollision on both ot them.
         * Else if both are sensor do nothing.
         * @param contact
         */
        void BeginContact(b2Contact* contact) {
            onContact(contact, &GameObject::OnTriggerEnter, &GameObject::OnCollisionEnter, false);
        }

        /**
         * @details If only one of them is a sensor call OnTrigger on the sensor GameObject.
         * If none of them is a sensor, call OnCollision on both ot them.
         * Else if both are sensor do nothing.
         * @param contact
         */
        void EndContact(b2Contact* contact) {
            onContact(contact, &GameObject::OnTriggerExit, &GameObject::OnCollisionExit, true);
        }

        // Helper functions
        void onContact(b2Contact* contact, void (GameObject::*triggerFunction)(const Collider&, const Collider&), void (GameObject::*collisionFunction)(const Collision&), bool exiting) {
            if (contact->IsTouching() || exiting) {
                // If only one of them is a sensor call OnTrigger on the sensor GameObject
                if (contact->GetFixtureA()->IsSensor() ^ contact->GetFixtureB()->IsSensor()) {
                    const Collider* sensor;
                    const Collider* other;
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
    };

}


#endif //PANCAKE_PHYSICSLISTENER_HPP
