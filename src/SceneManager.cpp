//
// Created by nicolas on 23/01/17.
//

#include "../include/SceneManager.hpp"

using namespace PancakeEngine;

void SceneManager::addScene(Scene *scene) {
    scenes.push_back(scene);
}

Scene* SceneManager::getCurrentScene() {
    //return scenes[currentScene];
    return scene;
}

void SceneManager::setCurrentScene(std::string name) {
    for (unsigned int i = 0; i < scenes.size(); ++i) {
        if (scenes[i]->name == name) {
            currentScene = i;
            return;
        }
    }
}

void SceneManager::nextScene() {
    //currentScene = (currentScene++)%scenes.size();
}
/**!
 * @deprecated
 * @param scene
 */
void SceneManager::loadScene(Scene *scene)
{
    this->scene = scene;
    getCurrentScene()->awake();
    getCurrentScene()->start();
}

Scene SceneManager::loadScene(const char *filename) {
    SceneFactory sceneFactory;
    return sceneFactory.loadAllGameObject(filename);
}