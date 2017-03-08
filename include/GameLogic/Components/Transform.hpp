//
// Created by Darenn on 12/01/2017.
//

#ifndef PANCAKE_TRANSFORM_HPP
#define PANCAKE_TRANSFORM_HPP

#include <cassert>
#include <SFML/Graphics.hpp>
#include "Component.hpp"

namespace PancakeEngine {
    class Transform : public Component {
    public:
        Transform();

        /**
         * Get the world position of the transform.
         * @return The world position of the transform.
         */
        sf::Vector2f getWorldPosition() const;

        /**
         * Get the local position of the transform.
         * @return The local position of the transform.
         */
        sf::Vector2f getLocalPosition() const;

        /**
         * Set the position of the transform.
         * @param newPos The new position.
         */
        void setPosition(const sf::Vector2f& newPos);

        /**
         * Apply rotation with angle 'angle'
         * @param angle
         */
        void setRotation(float angle);

        /**
         * Get world rotation
         * @return world rotation
         */
        float getWorldRotation() const;

        /**
         * Get local rotation
         * @return local rotation
         */
        float getLocalRotation() const;

        /**
         * Get the world transform matrix
         * @return the world transform matrix
         */
        sf::Transform getWorldTransformMatrix() const;

        /**
         * Get the local transform matrix
         * @return the local transform matrix
         */
        sf::Transform getLocalTransformMatrix() const;

    private:
        sf::Transformable transform;
    };
}

#endif //PANCAKE_TRANSFORM_HPP
