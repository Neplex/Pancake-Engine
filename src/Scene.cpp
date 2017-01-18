//
// Created by Darenn on 17/01/2017.
//

#include "../include/Scene.hpp"

Scene::Scene(std::string n) {
    name = n;
}

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

void Scene::addGameObject(GameObject * go) {
    gameObjects.push_back(go);
}