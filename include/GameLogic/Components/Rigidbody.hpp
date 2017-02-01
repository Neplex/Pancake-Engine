//
// Created by kelle on 24/01/2017.
//

#ifndef PANCAKE_RIGIDBODY_HPP
#define PANCAKE_RIGIDBODY_HPP


#include <SFML/System.hpp>
#include <Box2D/Dynamics/b2Body.h>
#include "Component.hpp"

namespace PancakeEngine {

    class PhysicsEngine;

    class Rigidbody : public Component {
    public:

        Rigidbody();

        enum bodyType {
            dynamicBody, staticBody, kinematicBody
        };
        bodyType type; // The physical behaviour type of the Rigidbody.
        float angularVelocity; // Angular velocity in degrees per second.
        float drag; // Coefficient of drag.
        bool freezeRotation; // Controls whether physics will change the rotation of the object.
        float gravityScale; // The degree to which this object is affected by gravity.
        float mass; // Mass of the rigidbody.
        float angularDrag; // Coefficient of angular drag.

        void awake();

        void start();

        void update();

        /**
         * Applies a force to the Rigidbody.
         * @param force The force to apply.
         */
        void applyForce(const sf::Vector2f& force);

        /**
         * Applies an impulse to the Rigidbody.
         * @param impulse The impulse to apply.
         */
        void applyLinearImpulse(const sf::Vector2f& impulse);

        /**
         * Applies a torque to the rigidbody.
         * @param torque The torque to apply.
         */
        void applyTorque(float torque);

        /**
         * Applies an angular impulse to the rigibody.
         * @param impulse
         */
        void applyAngularImpulse(float impulse);

        /**
         * Applies force at position. As a result this will apply a torque and force on the object.
         * For realistic effects position should be approximately in the range of the surface of the rigidbody.
         * This is most commonly used for explosions.
         * When applying explosions it is best to apply forces over several frames instead of just one.
         * Note that when position is far away from the center of the rigidbody the applied torque will be unrealistically large.
         * @param force The force to apply.
         * @param position Position in world coordinates.
         */
        void applyForceAtPosition(const sf::Vector2f& force, const sf::Vector2f& position);

        /**
         * Applies impulse at position. As a result this will apply a torque and force on the object.
         * For realistic effects position should be approximately in the range of the surface of the rigidbody.
         * This is most commonly used for explosions.
         * Note that when position is far away from the center of the rigidbody the applied torque will be unrealistically large.
         * @param impulse The impulse to apply.
         * @param position Position in world coordinates.
         */
        void applyLinearImpulseAtPosition(const sf::Vector2f& impulse, const sf::Vector2f& position);

    private:
        friend class Engine;

        friend class PhysicsEngine;

        static PhysicsEngine* physicsEngine;
        // The body of the rigidbody in the physics engine.
        b2Body* physicsBody;
        sf::Vector2f velocity;// Linear velocity of the rigidbody.
    };
}

#endif //PANCAKE_RIGIDBODY_HPP
