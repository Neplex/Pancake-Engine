//
// Created by nicolas on 23/01/17.
//

#include "../include/SceneManager.hpp"

void SceneManager::addScene(Scene *scene) {
    //scenes.push_back(scene);
}

Scene* SceneManager::getCurrentScene() {
    //return scenes[currentScene];
    return scene;
}

void SceneManager::setCurrentScene(std::string name) {
    for (unsigned int i = 0; i < scenes.size(); ++i) {
        if (scenes[i]->name == name)
            currentScene = i;
            return;
    }
}

void SceneManager::nextScene() {
    currentScene = (currentScene++)%scenes.size();
}

void SceneManager::loadScene(Scene *scene)
{
    this->scene = scene;
    getCurrentScene()->awake();
    getCurrentScene()->start();
}
