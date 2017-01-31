//
// Created by Darenn on 17/01/2017.
//

#include "../../include/GameLogic/GameObject.hpp"
#include "../../include/GameLogic/Components/Transform.hpp"
#include "../../include/GameLogic/Components/BoxCollider.hpp"

using namespace PancakeEngine;

GameObject::GameObject() : components() {
    transform.gameObject = this;
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

