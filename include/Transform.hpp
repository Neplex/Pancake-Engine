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
     * Called at GameObject creation.
     */
    void awake();
    /**
     * Called just before the first update call.
     */
    void start();
    /**
     * Called at each frame before physics.
     */
    void update();
    /**
     * Called at each frame after physics.
     */
    void lateUpdate();


private:
    sf::Transformable transform;
};


#endif //PANCAKE_TRANSFORM_HPP
