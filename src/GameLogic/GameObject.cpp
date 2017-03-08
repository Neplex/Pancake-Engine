//
// Created by Darenn on 17/01/2017.
//

#include "../../include/GameLogic/GameObject.hpp"
#include "../../include/GameLogic/Components/Transform.hpp"
#include "../../include/GameLogic/Components/BoxCollider.hpp"

using namespace PancakeEngine;

int GameObject::numGameobjects = 0;

GameObject::GameObject() : components() {
    transform.gameObject = this;
    numGameobjects++;
}

void GameObject::awake() {
    for (unsigned i = 0; i < components.size(); ++i) {
        components[i]->awake();
    }

    for (unsigned i = 0; i < childs.size(); ++i) {
        childs[i]->awake();
    }
}

void GameObject::start() {
    for (unsigned i = 0; i < components.size(); ++i) {
        components[i]->start();
    }

    for (unsigned i = 0; i < childs.size(); ++i) {
        childs[i]->start();
    }
}

void GameObject::update() {
    for (unsigned i = 0; i < components.size(); ++i) {
        components[i]->update();
        if (components[i]->toDestroy) {
            componentsToDestroy.push_back(components[i]);
            components[i] = components.back();
            components.pop_back();
            i--;
        }
    }
    destroyComponents();

    for (unsigned i = 0; i < childs.size(); ++i) {
        childs[i]->update();
    }
}

void GameObject::lateUpdate() {
    for (unsigned i = 0; i < components.size(); ++i) {
        components[i]->lateUpdate();
        if (components[i]->toDestroy) {
            componentsToDestroy.push_back(components[i]);
            components[i] = components.back();
            components.pop_back();
            i--;
        }
    }
    destroyComponents();

    for (unsigned i = 0; i < childs.size(); ++i) {
        childs[i]->lateUpdate();
    }
}

void GameObject::destroyComponents() {
    for (unsigned i = 0; i < componentsToDestroy.size(); ++i) {
        delete componentsToDestroy[i];
    }
    componentsToDestroy.clear();
}

