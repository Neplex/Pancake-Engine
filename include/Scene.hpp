//
// Created by Darenn on 13/01/2017.
//

#ifndef PANCAKE_SCENE_HPP
#define PANCAKE_SCENE_HPP

#include <vector>
#include "GameObject.hpp"

class Scene {
public:
    string name;
    //vector<GameObject> gameObjects;

    Scene(string name);

    void addGameObject(GameObject go);

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
};


#endif //PANCAKE_SCENE_HPP
