//
// Created by Darenn on 13/01/2017.
//

#ifndef PANCAKE_SCENE_HPP
#define PANCAKE_SCENE_HPP

#include <vector>
#include <GameLogic/GameObject.hpp>

namespace PancakeEngine {

    class Scene {
    public:
        std::string name;
        std::vector<std::vector<GameObject*>> layers; // TODO: vector of pointer is dangerous. Use references.

        Scene(std::string name) :name(name) {}

        ~Scene() {
            for (auto l : layers)
                for(GameObject* go : l) {
                    delete go;
                }
        }

        /**
         * Add the given game object to the scene (after the others) in the corresponding layer.
         * @tparam T the type of gameObject.
         * @param layer the layer index (draw over lower index).
         * @return the created gameObject
         */
        template <class T>
        T& addGameObject(unsigned layer) {
            while (layers.size() <= layer) layers.push_back(std::vector<GameObject*>());
            T* gameObject = new T();
            layers.at(layer).push_back(gameObject);
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
