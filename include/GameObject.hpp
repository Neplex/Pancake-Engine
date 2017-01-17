//
// Created by Darenn on 12/01/2017.
//

#ifndef PANCAKE_GAMEOBJECT_HPP
#define PANCAKE_GAMEOBJECT_HPP

#include "Component.hpp"
#include "Transform.hpp"
#include <vector>
#include <string>

using namespace std;

class GameObject {
public:
    string name;
    Transform transform;

    GameObject(string name);
    ~GameObject();

    /**
     * Return the first component of the type T in the game object.
     * @tparam T The type of the component.
     * @return The first component of the type T.
     */
    template <typename T>
    const Component& getComponent();

    template <typename T>
    const vector<Component&> getComponents();

    /**
     * Add the given component after the others on the game object.
     * @param c The component to add.
     */
    void addComponent(Component& c);

    /**
     * Called at GameObject creation.
     * Call the same method on all components in order.
     */
    void awake();
    /**
     * Called just before the first Update call.
     * Call the same method on all components in order.
     */
    void start();
    /**
     * Called at each frame before physics.
     * Call the same method on all components in order.
     */
    void update();
    /**
     * Called at each frame after physics.
     * Call the same method on all components in order.
     */
    void lateUpdate();

private:
    vector<Component *> components;
};


#endif //PANCAKE_GAMEOBJECT_HPP
