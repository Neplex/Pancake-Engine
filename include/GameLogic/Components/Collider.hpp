//
// Created by kelle on 23/01/2017.
//

#ifndef PANCAKE_COLLIDER_HPP
#define PANCAKE_COLLIDER_HPP


#include <SFML/System/Vector2.hpp>
#include "Component.hpp"
#include "Rigidbody.hpp"

namespace PancakeEngine {

    class PhysicsEngine;

    class Collider : public Component {

    public:
        Collider();

        void awake();

        // TODO make getters and setters
        Rigidbody* attachedRigidbody;
        // Is this collider configured as a trigger?
        bool isTrigger;
        // Get the bounciness used by the collider.
        float bounciness;
        // The density of the collider used to calculate its mass.
        float density;
        // Get the friction used by the collider.
        float friction;
        // The local offset of the collider
        sf::Vector2f offset;
        // category bits
        uint16 categoryBits;
        // mask bits
        uint16 maskBits;

        /**
         * Return the body type of this collider.
         * If the collider has not rigidbody, it is a static body.
         * Otherwise the body type of the collider is the bodyType of the rigibody.
         * @return The bodytype of the collider.
         */
        Rigidbody::bodyType getBodyType() const
        {
            if (attachedRigidbody!=NULL) {
                return attachedRigidbody->getType();
            }
            return Rigidbody::bodyType::staticBody;
        }

    protected:
        ~Collider();

    private:
        friend class Engine;
        friend class Transform; ///< Change the position of the fixture
        friend class PhysicsEngine;
        friend class Rigidbody; ///< null fixtures if removed body
        static PhysicsEngine* physicsEngine;
        b2Fixture* fixture;

    };
}

#endif //PANCAKE_COLLIDER_HPP
