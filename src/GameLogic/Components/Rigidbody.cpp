//
// Created by kelle on 24/01/2017.
//

#include <GameLogic/Components/Collider.hpp>
#include <GameLogic/Components/Rigidbody.hpp>
#include <Inputs/Input.hpp>
#include <Physics/PhysicsEngine.hpp>

using namespace PancakeEngine;

PhysicsEngine *Rigidbody::physicsEngine = nullptr;

void Rigidbody::awake() {
  Component::awake();

  if (physicsEngine != nullptr) {
    physicsEngine->addRigidBodyToPhysicsWorld(*this);
  } else {
    assert(false);
    // Should have an engine
  }

  std::vector<Collider *> v = gameObject->getComponents<Collider>();
  for (const auto &i : v) {
    i->attachedRigidbody = this;
  }
}

void Rigidbody::start() { Component::start(); }

void Rigidbody::update() { Component::update(); }

Rigidbody::Rigidbody()
    : type(bodyType::dynamicBody),
      angularVelocity(),
      drag(0),
      freezeRotation(false),
      gravityScale(1),
      mass(1),
      angularDrag(0.05f),
      bullet(false),
      physicsBody(nullptr),
      velocity(sf::Vector2f(0, 0)) {}

void Rigidbody::applyForce(const sf::Vector2f &force) const {
  physicsBody->ApplyForceToCenter(b2Vec2(force.x, force.y), true);
}

void Rigidbody::applyLinearImpulse(const sf::Vector2f &impulse) const {
  physicsBody->ApplyLinearImpulseToCenter(b2Vec2(impulse.x, impulse.y), true);
}

void Rigidbody::applyTorque(float torque) const { physicsBody->ApplyTorque(torque, true); }

void Rigidbody::applyAngularImpulse(float impulse) const { physicsBody->ApplyAngularImpulse(impulse, true); }

void Rigidbody::applyForceAtPosition(const sf::Vector2f &force, const sf::Vector2f &position) const {
  physicsBody->ApplyForce(b2Vec2(force.x, force.y), b2Vec2(position.x, position.y), true);
}

void Rigidbody::applyLinearImpulseAtPosition(const sf::Vector2f &impulse, const sf::Vector2f &position) const {
  physicsBody->ApplyLinearImpulse(b2Vec2(impulse.x, impulse.y), b2Vec2(position.x, position.y), true);
}

Rigidbody::bodyType Rigidbody::getType() const { return type; }

float Rigidbody::getAngularVelocity() const {
  if (physicsBody) return physicsBody->GetAngularVelocity();

  return angularVelocity;
}

float Rigidbody::getDrag() const {
  if (physicsBody) return physicsBody->GetLinearDamping();

  return drag;
}

bool Rigidbody::isFreezeRotation() const {
  if (physicsBody) return physicsBody->IsFixedRotation();

  return freezeRotation;
}

float Rigidbody::getGravityScale() const {
  if (physicsBody) return physicsBody->GetGravityScale();

  return gravityScale;
}

float Rigidbody::getAngularDrag() const {
  if (physicsBody) return physicsBody->GetAngularDamping();
  return angularDrag;
}

bool Rigidbody::isBullet() const {
  if (physicsBody) return physicsBody->IsBullet();

  return bullet;
}

sf::Vector2f Rigidbody::getVelocity() const {
  if (physicsBody) {
    return {physicsBody->GetLinearVelocity().x, physicsBody->GetLinearVelocity().y};
  }

  return velocity;
}

void Rigidbody::setType(bodyType type) {
  Rigidbody::type = type;

  if (physicsBody) {
    switch (type) {
      case bodyType::dynamicBody:
        physicsBody->SetType(b2_dynamicBody);
        break;
      case bodyType::kinematicBody:
        physicsBody->SetType(b2_kinematicBody);
        break;
      case bodyType::staticBody:
        physicsBody->SetType(b2_staticBody);
        break;
      default:
        assert(false);  // Impossible to have another type of body
    }
  }
}

void Rigidbody::setAngularVelocity(float angularVelocity) {
  Rigidbody::angularVelocity = angularVelocity;
  if (physicsBody) physicsBody->SetAngularVelocity(angularVelocity);
}

void Rigidbody::setDrag(float drag) {
  Rigidbody::drag = drag;
  if (physicsBody) physicsBody->SetLinearDamping(drag);
}

void Rigidbody::setFreezeRotation(bool freezeRotation) {
  Rigidbody::freezeRotation = freezeRotation;
  if (physicsBody) physicsBody->SetFixedRotation(freezeRotation);
}

void Rigidbody::setGravityScale(float gravityScale) {
  Rigidbody::gravityScale = gravityScale;
  if (physicsBody) physicsBody->SetGravityScale(gravityScale);
}

void Rigidbody::setAngularDrag(float angularDrag) {
  Rigidbody::angularDrag = angularDrag;
  if (physicsBody) physicsBody->SetAngularDamping(angularDrag);
}

void Rigidbody::setIsBullet(bool isBullet) {
  Rigidbody::bullet = isBullet;
  if (physicsBody) physicsBody->SetBullet(isBullet);
}

void Rigidbody::setVelocity(const sf::Vector2f &velocity) {
  Rigidbody::velocity = velocity;
  const auto vel = b2Vec2(velocity.x, velocity.y);
  if (physicsBody) physicsBody->SetLinearVelocity(vel);
}

Rigidbody::~Rigidbody() {
  if (physicsBody != nullptr) {
    physicsBody->SetUserData(nullptr);
    physicsEngine->removeBody(physicsBody);
    physicsBody = nullptr;
  }
}

float Rigidbody::getMass() const {
  if (physicsBody) return physicsBody->GetMass();

  return mass;
}
