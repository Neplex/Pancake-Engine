//
// Created by Darenn on 12/01/2017.
//

#ifndef PANCAKE_COMPONENT_HPP
#define PANCAKE_COMPONENT_HPP

#include "GameObject.hpp"
class GameObject;

class Component {
public:
    GameObject * gameObject;
    virtual ~Component() {};
    /**
     * Called at GameObject creation.
     */
    virtual void awake() {};
    /**
     * Called just before the first update call.
     */
    virtual void start() {};
    /**
     * Called at each frame before physics.
     */
    virtual void update() {};
    /**
     * Called at each frame after physics.
     */
    virtual void lateUpdate() {};

};

#endif //PANCAKE_COMPONENT_HPP
