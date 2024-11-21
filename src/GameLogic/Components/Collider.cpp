//
// Created by kelle on 23/01/2017.
//

#include <GameLogic/Components/Collider.hpp>
#include <GameLogic/Components/Rigidbody.hpp>
#include <Physics/PhysicsEngine.hpp>

using namespace PancakeEngine;

PhysicsEngine* Collider::physicsEngine = nullptr;

PancakeEngine::Collider::Collider()
    : attachedRigidbody(nullptr),
      isTrigger(false),
      bounciness(0),
      density(1),
      friction(0.5),
      offset(sf::Vector2f(0, 0)),
      categoryBits(0x0001),
      maskBits(0x0001) {
  fixture = nullptr;
}

void Collider::awake() {
  Component::awake();
  if (physicsEngine != nullptr) {
    auto const* rb = gameObject->getComponent<Rigidbody>();
    if (rb == nullptr && fixture == nullptr) {  // If fixture is set, it's because it was already added
      physicsEngine->addStaticBodyToPhysicsWorld(*this);
    }
  } else {
    assert(false);
    // Should have an engine
  }
  // Else we do nothing, the awake of the rigid body will do the work
}

Collider::~Collider() {
  if (fixture != nullptr) {  // we let the rigid body destroy the body if there is one
    fixture->GetBody()->SetUserData(nullptr);
    physicsEngine->removeBody(fixture->GetBody());
    fixture->SetUserData(nullptr);
    fixture = nullptr;
  }
}
