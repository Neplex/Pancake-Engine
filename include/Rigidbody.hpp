//
// Created by kelle on 24/01/2017.
//

#ifndef PANCAKE_RIGIDBODY_HPP
#define PANCAKE_RIGIDBODY_HPP


#include <SFML/System.hpp>
#include "Component.hpp"

class PhysicsEngine;

class Rigidbody : public Component {
public:

    Rigidbody();

    enum bodyType {dynamicBody, staticBody, kinematicBody};
    float angularDrag; // Coefficient of angular drag.
    float angularVelocity; // Angular velocity in degrees per second.
    bodyType type; // The physical behaviour type of the Rigidbody.
    float drag; // Coefficient of drag.
    bool freezeRotation; // Controls whether physics will change the rotation of the object.
    float gravityScale; // The degree to which this object is affected by gravity.
    float mass; // Mass of the rigidbody.

    void awake();

private:
    friend class Engine;
    static PhysicsEngine * physicsEngine;
    sf::Vector2f velocity;// Linear velocity of the rigidbody.
};


#endif //PANCAKE_RIGIDBODY_HPP
