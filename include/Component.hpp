//
// Created by Darenn on 12/01/2017.
//

#ifndef PANCAKE_COMPONENT_HPP
#define PANCAKE_COMPONENT_HPP

class Component {
public:
    /**
     * Called at GameObject creation.
     */
    virtual void awake() = 0;
    /**
     * Called just before the first update call.
     */
    virtual void start() = 0;
    /**
     * Called at each frame before physics.
     */
    virtual void update() = 0;
    /**
     * Called at each frame after physics.
     */
    virtual void lateUpdate() = 0;

};

#endif //PANCAKE_COMPONENT_HPP
