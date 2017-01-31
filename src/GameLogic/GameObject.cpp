//
// Created by Darenn on 17/01/2017.
//

#include "../../include/GameLogic/GameObject.hpp"
#include "../../include/GameLogic/Components/Transform.hpp"

using namespace PancakeEngine;

GameObject::GameObject(std::string n) {
    name = n;
    transform = new Transform();
    components = std::vector<Component *> ();
    components.push_back((Component *&&) transform);
}

GameObject::~GameObject() {
    for (unsigned i = 0; i < components.size(); ++i) {
        delete(components[i]);
    }
}

void GameObject::awake() {
    for (unsigned i = 0; i < components.size(); ++i) {
        components[i]->awake();
    }
}

void GameObject::start() {
    for (unsigned i = 0; i < components.size(); ++i) {
        components[i]->start();
    }
}

void GameObject::update() {
    for (unsigned i = 0; i < components.size(); ++i) {
        components[i]->update();
    }
}

void GameObject::lateUpdate() {
    for (unsigned i = 0; i < components.size(); ++i) {
        components[i]->lateUpdate();
    }
}

void GameObject::addComponent(Component& c) {
    components.push_back(&c);
    c.gameObject = this;
}
