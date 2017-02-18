//
// Created by Darenn on 13/01/2017.
//

#ifndef PANCAKE_SCENE_HPP
#define PANCAKE_SCENE_HPP

#include <vector>
#include <GameLogic/GameObject.hpp>

namespace PancakeEngine {

    class Camera;
    class Scene {
    public:
        std::string name;
        std::vector<GameObject*> gameObjects; // TODO: vector of pointer is dangerous. Use references.
        std::vector<Camera*> cameras; // Temporary, use to have a fixed order of camera. TODO: remove this, use static order of GameObjects

        Scene(std::string name)
                :name(name), gameObjects(), cameras() { }

        ~Scene() {
                for(GameObject* go : gameObjects) {
                        delete go;
                }
        }

        /**
         * Add the given game object to the scene (after the others).
         * @param go The game object to add.
         */
        template <class T>
        T& addGameObject() {
                T* gameObject = new T();
                gameObjects.push_back(gameObject);
                return *gameObject;
        }

        /**
         * Awake is used to initialize any variables or game state before the game starts.
         */
        void awake();

        /**
         * Called just before the first Update call.
         * Call the same method on all game objects in order.
         */
        void start();

        /**
         * Called at each frame before physics.
         * Call the same method on all game objects in order.
         */
        void update();

        /**
         * Called at each frame after physics.
         * Call the same method on all game objects in order.
         */
        void lateUpdate();
    private:
        std::vector<GameObject*> toDestroy;
        void destroyGameObjects();
    };
}

#endif //PANCAKE_SCENE_HPP
