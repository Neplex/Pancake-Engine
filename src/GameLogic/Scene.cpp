//
// Created by Darenn on 17/01/2017.
//

#include <GameLogic.hpp>

using namespace PancakeEngine;

void Scene::awake() {
    for (GameObject* l : layers) l->awake();
}

void Scene::start() {
    for (GameObject* l : layers) l->start();
}

void Scene::update() {
    for (GameObject* layer : layers) {
        for (GameObject* go : layer->getChilds()) {
            go->update();
            if (go->toDestroy) {
                toDestroy.push_back(go);
            }
        }
    }
    destroyGameObjects();
}

void Scene::lateUpdate() {
    for (GameObject* layer : layers) {
        for (GameObject* go : layer->getChilds()) {
            go->lateUpdate();
            if (go->toDestroy) {
                toDestroy.push_back(go);
            }
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

