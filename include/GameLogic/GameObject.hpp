/*
     Copyright (C) 2016-2017 Keller Darenn - keller.darenn@gmail.com

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

/**
 * \file        GameObject.hpp
 * \author      Darenn Keller - keller.darenn@gmail.com
 * \author      Nicolas Hiot - nicolashiot@hotmail.com
 */

#ifndef PANCAKE_GAMEOBJECT_HPP
#define PANCAKE_GAMEOBJECT_HPP

#include <vector>
#include <string>
#include <iostream>
#include <GameLogic/Components/Behavior.hpp>
#include <GameLogic/Components/Transform.hpp>

namespace PancakeEngine {

    class Transform;
    class Collision;
    class Component;

    /**
     * @class GameObject
     * @brief Represent an object in the world (Scene).
     * @details A gameobject can only be create in a scene.
     * As a consequence it has a Transform.
     * A gameobject has components that define the behavior and the nature of the gameobject.
     * @sa Scene Component Transform
     */
    class GameObject {
    public:
        std::string name; ///< The name of the gameobject
        Transform transform; ///< The transform of the gameobject

        /**
         * @brief Return the first component of the type T in the game object.
         * @details Use of dynamic_cast
         * @tparam T The type of the component.
         * @return The first component of the type T, NULL if no component of the type T.
         * @attention Please do not mess up with the pointer.
         * @sa Component
         */
        template<typename T>
        T* getComponent() const
        {
            T* component;
            for (unsigned i = 0; i<components.size(); ++i) {
                if ((component = dynamic_cast<T*>(components[i])))
                    return component;
            }
            return nullptr;
        }

        /**
         * @brief Return the list of components of the type T in the game object.
         * @details Use of dynamic_cast
         * @tparam T The type of the component.
         * @return The vector of all component of the type T.
         * @attention Please do not mess up with the pointer.
         * @todo To optimize by avoiding dynamic cast
         */
        template<typename T>
        const std::vector<T*> getComponents() const
        {
            std::vector<T*> cs = std::vector<T*>();
            T* p_component;
            for (unsigned i = 0; i < components.size(); ++i) {
                if ((p_component = dynamic_cast<T*>(components[i])))
                    cs.push_back(p_component);
            }
            return cs;
        };


        /**
         * @brief Add a component to the gameobject
         * @tparam T should inherit from Component.
         * @return The component created.
         * @sa Component
         */
        template <class T>
        T& addComponent() {
            T* component = new T();
            components.push_back(component);
            component->gameObject = this;
            return *component;
        }

        /**
         * @brief Called at GameObject creation.
         * @details Call the same method on all components in order.
         */
        void awake();

        /**
         * @brief Called just before the first Update call.
         * @details Call the same method on all components in order.
         */
        void start();

        /**
         * @brief Called at each update engine call.
         * @details Call the same method on all components in order.
         */
        void update();

        /**
         * @brief Called at each frame after the update engine call.
         * @details Call the same method on all components in order.
         */
        void lateUpdate();

        // TODO: Not better to take the nb of objects in scene
        static int getNbGameObjects() { return numGameobjects; }

        /**
         * @brief Add child to the gameObject.
         * @param go the child.
         */
        void addChild(GameObject& go) {
            if (go.parent != NULL) go.removeParent();
            go.parent = this;
            childs.push_back(&go);
        }

        /**
         * @brief Set the new parent.
         * @param go the new parent.
         */
        void setParent(GameObject& go) {
            go.addChild(*this);
        }

        /**
         * @brief Remove a child;
         * @param go the child to remove.
         */
        void removeChild(GameObject& go) {
            for (int i = 0; i < childs.size(); ++i) {
                if (childs.at(i) == &go) {
                    childs.at(i)->parent = NULL;
                    childs.erase(childs.begin() + i);
                    return;
                }
            }
            assert(false); ///< GameObject not in this
        }

        /**
         * @brief Remove the current parent.
         */
        void removeParent() {
            if (parent != NULL) {
                parent->removeChild(*this);
            }
        }

        /**
         * @brief Get all sub childs.
         * @return All sub childs.
         */
        std::vector<GameObject*> getChilds() const {
            std::vector<GameObject*> cs;
            for (int i = 0; i < childs.size(); ++i) {
                std::vector<GameObject*> subChilds = childs.at(i)->getChilds();
                cs.push_back(childs.at(i));
                cs.insert(cs.end(), subChilds.begin(), subChilds.end());
            }
            return cs;
        }

    protected:
        friend class Scene; ///< The scene is the only one to create and destroy gameobjects
        GameObject();
        std::vector<Component*> components; ///< The components of the gameobject.
        ~GameObject() {
            removeParent();

            for (int i = 0; i < childs.size(); ++i) {
                delete childs.at(i);
            }

            for (int i = 0; i < components.size(); ++i) {
                delete components[i];
            }

            numGameobjects--;
        }

    private:
        friend class PhysicsListener; ///< Is the only one to call OnCollision*
        friend class Transform;
        friend class Window;
        friend void Behavior::destroy(GameObject& go);

        static int numGameobjects;

        bool toDestroy = false;
        std::vector<Component *> componentsToDestroy;
        GameObject* parent = NULL;
        std::vector<GameObject *> childs;

        void destroyComponents();

        /**
         * @brief Called by the physics listener when this gameObject collides another.
         * @details Will call OnCollisionEnter on each Behavior script.
         * @param collision Info about the collision.
         * @todo Can be optimized by avoid using getComponents.
         */
        void OnCollisionEnter(const Collision& collision) {
            std::vector<Behavior*> v = getComponents<Behavior>();
            for (Behavior* b : v) {
                b->OnCollisionEnter(collision);
            }
        }

        /**
         * @brief Called by the physics listener when this gameObject non longer collides another.
         * @details Will call OnCollisionExit on each Behavior script.
         * @param collision Info about the collision.
         * @todo Can be optimized by avoid using getComponents.
         */
        void OnCollisionExit(const Collision& collision) {
            std::vector<Behavior*> v = getComponents<Behavior>();
            for (Behavior* b : v) {
                b->OnCollisionExit(collision);
            }
        }

        /**
         * @brief Called by the physics listener when a gameobject enter one of this's triggers.
         * @details Will call OnTriggerEnter on each Behavior script.
         * @param triggered The collider triggered
         * @param other The collider triggering
         * @todo Can be optimized by avoid using getComponents.
         */
        void OnTriggerEnter(const Collider& triggered, const Collider& other) {
            std::vector<Behavior*> v = getComponents<Behavior>();
            for (Behavior* b : v) {
                b->OnTriggerEnter(triggered, other);
            }
        }

        /**
         * @brief Called by the physics listener when a gameobject exit one of this's triggers.
         * @details Will call OnTriggerExit on each Behavior script.
         * @param triggered The collider triggered
         * @param other The collider triggering
         * @todo Can be optimized by avoid using getComponents.
         */
        void OnTriggerExit(const Collider& triggered, const Collider& other) {
            std::vector<Behavior*> v = getComponents<Behavior>();
            for (Behavior* b : v) {
                b->OnTriggerExit(triggered, other);
            }
        }
    };
}

#endif //PANCAKE_GAMEOBJECT_HPP
