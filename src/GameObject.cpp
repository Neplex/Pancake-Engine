//
// Created by Darenn on 17/01/2017.
//

#include "../include/GameObject.hpp"

GameObject::GameObject(string n) {
    name = n;
    transform = Transform();
    components = vector<Component *> ();
    components.push_back(&transform);
}

GameObject::~GameObject() {
    for (int i = 0; i < components.size(); ++i) {
        delete(components[i]);
    }
}

void GameObject::awake() {
    for (int i = 0; i < components.size(); ++i) {
        components[i]->awake();
    }
}

void GameObject::start() {
    for (int i = 0; i < components.size(); ++i) {
        components[i]->start();
    }
}

void GameObject::update() {
    for (int i = 0; i < components.size(); ++i) {
        components[i]->update();
    }
}

void GameObject::lateUpdate() {
    for (int i = 0; i < components.size(); ++i) {
        components[i]->lateUpdate();
    }
}