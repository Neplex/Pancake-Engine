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

#include <box2d/b2_world_callbacks.h>

#include <GameLogic/Components/Collider.hpp>
#include <GameLogic/GameObject.hpp>
#include <Physics/Collision.hpp>

namespace PancakeEngine {

class PhysicsListener : public b2ContactListener {
  /**
   * @details If only one of them is a sensor call OnTrigger on the sensor
   * GameObject. If none of them is a sensor, call OnCollision on both ot them.
   * Else if both are sensor do nothing.
   * @param contact
   */
  void BeginContact(b2Contact *contact) override {
    onContact(contact, &GameObject::OnTriggerEnter, &GameObject::OnCollisionEnter, false);
  }

  /**
   * @details If only one of them is a sensor call OnTrigger on the sensor
   * GameObject. If none of them is a sensor, call OnCollision on both ot them.
   * Else if both are sensor do nothing.
   * @param contact
   */
  void EndContact(b2Contact *contact) override {
    onContact(contact, &GameObject::OnTriggerExit, &GameObject::OnCollisionExit, true);
  }

  // Helper functions
  void onContact(b2Contact *contact, void (GameObject::*triggerFunction)(const Collider &, const Collider &),
                 void (GameObject::*collisionFunction)(const Collision &), bool exiting);
};

}  // namespace PancakeEngine

#endif  // PANCAKE_PHYSICSLISTENER_HPP
