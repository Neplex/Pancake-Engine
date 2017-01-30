//
// Created by Darenn on 17/01/2017.
//

#include "../../include/GameLogic/Scene.hpp"

using namespace PancakeEngine;

void Scene::awake() {
    for (int i = 0; i < gameObjects.size(); ++i) {
        gameObjects[i]->awake();
    }
}

void Scene::start() {
    for (int i = 0; i < gameObjects.size(); ++i) {
        gameObjects[i]->start();
    }
}

void Scene::update() {
    for (int i = 0; i < gameObjects.size(); ++i) {
        gameObjects[i]->update();
    }
}

void Scene::lateUpdate() {
    for (int i = 0; i < gameObjects.size(); ++i) {
        gameObjects[i]->lateUpdate();
    }
}

// TODO should create game object only with this method
void Scene::addGameObject(GameObject * go) {
    gameObjects.push_back(go);
}
