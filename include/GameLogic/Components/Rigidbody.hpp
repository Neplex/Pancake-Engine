//
// Created by kelle on 24/01/2017.
//

#ifndef PANCAKE_RIGIDBODY_HPP
#define PANCAKE_RIGIDBODY_HPP

#include <box2d/b2_body.h>

#include <GameLogic/Components/Component.hpp>
#include <SFML/System.hpp>

// Tutorial here : http://www.iforce2d.net/b2dtut/introduction

namespace PancakeEngine {

class PhysicsEngine;

class Rigidbody : public Component {
 public:
  Rigidbody();

  enum class bodyType { dynamicBody, staticBody, kinematicBody };

  void awake() override;

  void start() override;

  void update() override;

  // Setters

  void setType(bodyType type);

  void setAngularVelocity(float angularVelocity);

  void setDrag(float drag);

  void setFreezeRotation(bool freezeRotation);

  void setGravityScale(float gravityScale);

  void setAngularDrag(float angularDrag);

  void setIsBullet(bool isBullet);

  void setVelocity(const sf::Vector2f &velocity);

  // Getters

  bodyType getType() const;

  float getAngularVelocity() const;

  float getDrag() const;

  float getMass() const;

  bool isFreezeRotation() const;

  float getGravityScale() const;

  float getAngularDrag() const;

  bool isBullet() const;

  sf::Vector2f getVelocity() const;

  // Methods

  /**
   * Applies a force to the Rigidbody.
   * @param force The force to apply.
   */
  void applyForce(const sf::Vector2f &force) const;

  /**
   * Applies an impulse to the Rigidbody.
   * @param impulse The impulse to apply.
   */
  void applyLinearImpulse(const sf::Vector2f &impulse) const;

  /**
   * Applies a torque to the rigidbody.
   * @param torque The torque to apply.
   */
  void applyTorque(float torque) const;

  /**
   * Applies an angular impulse to the rigibody.
   * @param impulse
   */
  void applyAngularImpulse(float impulse) const;

  /**
   * Applies force at position. As a result this will apply a torque and force
   * on the object. For realistic effects position should be approximately in
   * the range of the surface of the rigidbody. This is most commonly used for
   * explosions. When applying explosions it is best to apply forces over
   * several frames instead of just one. Note that when position is far away
   * from the center of the rigidbody the applied torque will be
   * unrealistically large.
   * @param force The force to apply.
   * @param position Position in world coordinates.
   */
  void applyForceAtPosition(const sf::Vector2f &force, const sf::Vector2f &position) const;

  /**
   * Applies impulse at position. As a result this will apply a torque and
   * force on the object. For realistic effects position should be
   * approximately in the range of the surface of the rigidbody. This is most
   * commonly used for explosions. Note that when position is far away from the
   * center of the rigidbody the applied torque will be unrealistically large.
   * @param impulse The impulse to apply.
   * @param position Position in world coordinates.
   */
  void applyLinearImpulseAtPosition(const sf::Vector2f &impulse, const sf::Vector2f &position) const;

 private:
  friend class Engine;
  friend class Transform;  ///< The transform update the position of the physics
                           ///< body

  friend class PhysicsEngine;

  ~Rigidbody() override;

  bodyType type;  ///< The physical behaviour type of the Rigidbody.

  // These attributes are only use before the physic body is created
  float angularVelocity;  ///< Angular velocity in degrees per second.
  float drag;             ///< Coefficient of drag.
  bool freezeRotation;    ///< Controls whether physics will change the rotation
                          ///< of the object.
  float gravityScale;     ///< The degree to which this object is affected by
                          ///< gravity.
  float mass;             ///< Mass of the rigidbody.
  float angularDrag;      ///< Coefficient of angular drag.
  bool bullet;            ///< More realistics impacts, good for fast rigibody, but more
                          ///< CPU usage.

  static PhysicsEngine *physicsEngine;
  // The body of the rigidbody in the physics engine.
  b2Body *physicsBody;
  sf::Vector2f velocity;  // Linear velocity of the rigidbody.
};
}  // namespace PancakeEngine

#endif  // PANCAKE_RIGIDBODY_HPP
