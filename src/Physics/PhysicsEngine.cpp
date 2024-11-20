//
// Created by kelle on 23/01/2017.
//

#include <box2d/box2d.h>

#include <GameLogic/Components/BoxCollider.hpp>
#include <GameLogic/Components/CircleCollider.hpp>
#include <GameLogic/Components/Transform.hpp>
#include <Physics/PhysicsEngine.hpp>
#include <Physics/PhysicsUserData.hpp>

using namespace PancakeEngine;

constexpr float to_rad = 0.0174533f;
constexpr float to_deg = 57.2958f;

int PhysicsEngine::numberPixelsPerMeter = 72;  // TODO to change with the scene

PhysicsEngine::PhysicsEngine() : world(b2Vec2(0, 10)) { world.SetContactListener(&physicsListener); }

PhysicsEngine::~PhysicsEngine() = default;

void PhysicsEngine::update(const float dt) {
  // Update the body position if the engine changes it
  world.Step(dt, velocityIterations, positionIterations);
  for (b2Body *b = world.GetBodyList(); b; b = b->GetNext()) {
    if (b->GetType() != b2_staticBody) {
      const auto *rb = static_cast<Rigidbody *>(b->GetUserData());
      rb->gameObject->transform.setPosition(
          sf::Vector2f(b->GetPosition().x * numberPixelsPerMeter, b->GetPosition().y * numberPixelsPerMeter));
      rb->gameObject->transform.setRotation(b->GetAngle() * to_deg);
    }
  }
}

void PhysicsEngine::addStaticBodyToPhysicsWorld(Collider &c) {
  b2BodyDef bodyDef;
  bodyDef.type = b2_staticBody;

  bodyDef.position.Set(c.gameObject->transform.getWorldPosition().x / numberPixelsPerMeter,
                       c.gameObject->transform.getWorldPosition().y / numberPixelsPerMeter);
  bodyDef.angle = c.gameObject->transform.getWorldRotation() * to_rad;
  bodyDef.userData = static_cast<void *>(&c);
  b2Body *body = world.CreateBody(&bodyDef);
  createFixtures(*c.gameObject, *body);
}

void PhysicsEngine::addRigidBodyToPhysicsWorld(Rigidbody &rb) {
  b2BodyDef bodyDef;

  switch (rb.type) {
    case Rigidbody::bodyType::dynamicBody:
      bodyDef.type = b2_dynamicBody;
      break;

    case Rigidbody::bodyType::staticBody:
      bodyDef.type = b2_staticBody;
      break;

    case Rigidbody::bodyType::kinematicBody:
      bodyDef.type = b2_kinematicBody;
      break;

    default:
      assert(false);
  }

  bodyDef.position.Set(rb.gameObject->transform.getWorldPosition().x / numberPixelsPerMeter,
                       rb.gameObject->transform.getWorldPosition().y / numberPixelsPerMeter);
  bodyDef.angle = rb.gameObject->transform.getWorldRotation() * to_rad;
  bodyDef.userData = static_cast<void *>(&rb);
  bodyDef.angularVelocity = rb.angularVelocity;
  bodyDef.angularDamping = rb.angularDrag;
  bodyDef.fixedRotation = rb.freezeRotation;
  bodyDef.bullet = rb.bullet;
  b2Body *body = world.CreateBody(&bodyDef);
  rb.physicsBody = body;

  createFixtures(*rb.gameObject, *body);
}

void PhysicsEngine::setPosition(const sf::Vector2f &pos, b2Body &body) {
  body.SetTransform(b2Vec2(pos.x / numberPixelsPerMeter, pos.y / numberPixelsPerMeter), body.GetAngle());
}

void PhysicsEngine::setRotation(const float angle, b2Body &body) {
  body.SetTransform(body.GetPosition(), angle * to_rad);
}

void PhysicsEngine::removeBody(b2Body *body) { world.DestroyBody(body); }

// Helper functions

void PhysicsEngine::createFixtures(const GameObject &go, b2Body &body) {
  // Create a fixture for each collider
  for (const auto &i : go.getComponents<Collider>()) {
    Collider &c = *i;
    b2FixtureDef fixtureDef;
    b2PolygonShape polygonShape;
    b2CircleShape circleShape;

    if (dynamic_cast<BoxCollider *>(&c) != nullptr) {
      const auto *bc = dynamic_cast<BoxCollider *>(&c);
      polygonShape.SetAsBox(bc->width / 2 / numberPixelsPerMeter, (bc->height / 2) / numberPixelsPerMeter,
                            b2Vec2(c.offset.x / numberPixelsPerMeter, c.offset.y / numberPixelsPerMeter), 0);
      fixtureDef.shape = &polygonShape;

    } else if (dynamic_cast<CircleCollider *>(&c) != nullptr) {
      auto const *cc = dynamic_cast<CircleCollider *>(&c);
      circleShape.m_p.Set(cc->offset.x / numberPixelsPerMeter, cc->offset.y / numberPixelsPerMeter);
      circleShape.m_radius = cc->radius / numberPixelsPerMeter;
      fixtureDef.shape = &circleShape;

    } else {
      assert(false);  // Collider unknown
    }

    fixtureDef.density = c.density;
    fixtureDef.friction = c.friction;
    fixtureDef.restitution = c.bounciness;
    fixtureDef.isSensor = c.isTrigger;
    fixtureDef.userData = static_cast<void *>(&c);
    fixtureDef.filter.categoryBits = c.categoryBits;
    fixtureDef.filter.maskBits = c.maskBits;

    // TODO use indexgroup
    c.fixture = body.CreateFixture(&fixtureDef);
  }
}

void PhysicsEngine::resetWorld() {
  for (b2Body *b = world.GetBodyList(); b; b = b->GetNext()) {
    world.DestroyBody(b);
  }
}
