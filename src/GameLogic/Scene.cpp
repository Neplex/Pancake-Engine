//
// Created by Darenn on 17/01/2017.
//

#include "../../include/GameLogic/Scene.hpp"

using namespace PancakeEngine;

void Scene::awake() {
    for (unsigned i = 0; i < gameObjects.size(); ++i) {
        gameObjects[i]->awake();
    }
}

void Scene::start() {
    for (unsigned i = 0; i < gameObjects.size(); ++i) {
        gameObjects[i]->start();
    }
}

void Scene::update() {
    for (unsigned i = 0; i < gameObjects.size(); ++i) {
        gameObjects[i]->update();
        if (gameObjects[i]->toDestroy) {
            toDestroy.push_back(gameObjects[i]);
            gameObjects[i] = gameObjects.back();
            gameObjects.pop_back();
            i--;
        }
    }
    destroyGameObjects();
}

void Scene::lateUpdate() {

    for (unsigned i = 0; i < gameObjects.size(); ++i) {
        gameObjects[i]->lateUpdate();
        if (gameObjects[i]->toDestroy) {
            toDestroy.push_back(gameObjects[i]);
            gameObjects[i] = gameObjects.back();
            gameObjects.pop_back();
            i--;
        }
    }
    destroyGameObjects();
}

void Scene::destroyGameObjects() {
    for (unsigned i = 0; i < toDestroy.size(); ++i) {
        delete toDestroy[i];
    }
    toDestroy.clear();
}

