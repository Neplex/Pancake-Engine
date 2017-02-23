//
// Created by Darenn on 17/01/2017.
//

#include <GameLogic.hpp>

using namespace PancakeEngine;

void Scene::awake() {
    for (auto l : layers)
        for (GameObject* go : l)
            go->awake();
}

void Scene::start() {
    for (auto l : layers)
        for (GameObject* go : l)
            go->start();
}

void Scene::update() {
    for (auto layer : layers)
        for (unsigned i=0; i<layer.size(); i++) {
            layer.at(i)->update();
            if (layer.at(i)->toDestroy) {
                toDestroy.push_back(layer[i]);
                layer[i] = layer.back();
                layer.pop_back();
                i--;
            }
        }
    destroyGameObjects();
}

void Scene::lateUpdate() {
    for (auto layer : layers)
        for (unsigned i=0; i<layer.size(); i++) {
            layer.at(i)->lateUpdate();
            if (layer.at(i)->toDestroy) {
                toDestroy.push_back(layer[i]);
                layer[i] = layer.back();
                layer.pop_back();
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

