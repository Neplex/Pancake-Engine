//
// Created by Darenn on 12/01/2017.
//

#ifndef PANCAKE_TRANSFORM_HPP
#define PANCAKE_TRANSFORM_HPP

#include "Component.hpp"
#include <SFML/Graphics.hpp>

class Transform : public Component{
public:
    Transform();

    /**
     * Get the position of the transform.
     * @return The position of the transform.
     */
    sf::Vector2f getPosition() const {
        return transform.getPosition();
    }

    /**
     * Set the position of the transform.
     * @param newPos The new position.
     */
    void setPosition(const sf::Vector2f newPos) {
        transform.setPosition(newPos);
    }

    /**
     * Apply rotation with angle 'angle'
     * @param angle
     */
    void setRotation(float angle) {
        transform.setRotation(angle);
    }

    /**
     * Get current rotation
     * @return current rotation
     */
    float getRotation() {
        return transform.getRotation();
    }

    /**
     * Get the transform matrix
     * @return the transform matrix
     */
    sf::Transform getTransformMatrix() {
        return transform.getTransform();
    }

private:
    sf::Transformable transform;
};


#endif //PANCAKE_TRANSFORM_HPP
