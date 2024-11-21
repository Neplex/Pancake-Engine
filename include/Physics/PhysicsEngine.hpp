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
 * \file        PhysicsEngine.hpp
 * \author      Darenn Keller - keller.darenn@gmail.com
 */

#ifndef PANCAKE_PHYSICSENGINE_HPP
#define PANCAKE_PHYSICSENGINE_HPP

#include <box2d/box2d.h>

#include <GameLogic/GameObject.hpp>
#include <Physics/PhysicsListener.hpp>

namespace PancakeEngine {

class Collider;
class Rigidbody;

/**
 * @brief Provide an interface to interact with the box2D physics engine.
 */
class PhysicsEngine {
 public:
  static constexpr int velocityIterations = 8;  ///< how strongly to correct velocity.
  static constexpr int positionIterations = 3;  ///< how strongly to correct position.
  static int numberPixelsPerMeter;              ///< how to rescale gameObjects positions
                                                ///< and sizes to look good in the engine.

  PhysicsEngine();

  ~PhysicsEngine();

  /**
   * @brief Simulate physics for the given time.
   * @param dt The length of time passed to simulate (seconds).
   */
  void update(float dt);

  /**
   * @brief Add a static body to the physics world according to a given
   * collider.
   * @details That allows to have other game object with rigid body to collide
   * this object. Add all colliders of the game object on the same body.
   * @param c The collider of the object to create in the world.
   */
  void addStaticBodyToPhysicsWorld(Collider &c);

  /**
   * @brief Add a rigid body to the physics world.
   * It can be dynamic, static or kinematic.
   * @param rb The rigid body of the game object.
   */
  void addRigidBodyToPhysicsWorld(Rigidbody &rb);

  void removeBody(b2Body *body);

  void setPosition(const sf::Vector2f &pos, b2Body &body);

  void setRotation(float angle, b2Body &body);

  void resetWorld();

 private:
  b2World world;  ///< the physics world of box2D
  PhysicsListener physicsListener;

  static void createFixtures(const GameObject &go, b2Body &body);
};
}  // namespace PancakeEngine

#endif  // PANCAKE_PHYSICSENGINE_HPP
