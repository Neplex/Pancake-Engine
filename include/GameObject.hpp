//
// Created by Darenn on 12/01/2017.
//

#ifndef PANCAKE_GAMEOBJECT_HPP
#define PANCAKE_GAMEOBJECT_HPP

#include "Component.hpp"
#include "Transform.hpp"
#include <vector>
#include <string>

class Transform;
class Component;
class GameObject {
public:
    std::string name;
    Transform * transform;

    GameObject(std::string name);
    ~GameObject();

    /**
     * Return the first component of the type T in the game object.
     * Use of dynamic_cast
     * @tparam T The type of the component.
     * @return The first component of the type T, NULL if no component of the type T.
     */
    template <typename T>
    T* getComponent() const {
        T* component;
        for (int i = 0; i < components.size(); ++i) {
            if(component = dynamic_cast<T*>(components[i]))
                return component;
        }
        return NULL;
    }

    /**
     * Return the list of components of the type T in the game object.
     * Use of dynamic_cast
     * @tparam T The type of the component.
     * @return The vector of all component of the type T.
     */
    template <typename T>
    const std::vector<T*> getComponents() const {
        std::vector<T*> cs = std::vector<T*>();
        T* component;
        for (int i = 0; i < components.size(); ++i) {
            if(component = dynamic_cast<T*>(components[i]))
                cs.push_back(component);
        }
        return cs;
    };

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
    std::vector<Component *> components;
};

#endif //PANCAKE_GAMEOBJECT_HPP
