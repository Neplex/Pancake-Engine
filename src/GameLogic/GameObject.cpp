//
// Created by Darenn on 17/01/2017.
//

#include <GameLogic/GameObject.hpp>

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
            components.erase(components.begin() + i);
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
            components.erase(components.begin() + i);
            i--;
        }
    }
    destroyComponents();

    for (unsigned i = 0; i < childs.size(); ++i) {
        childs[i]->lateUpdate();
    }
}

void GameObject::destroyComponents() {
    for (auto c : componentsToDestroy) delete c;
    componentsToDestroy.clear();
}

void GameObject::addChild(GameObject &go) {
    if (go.parent != NULL) go.removeParent();
    go.parent = this;
    childs.push_back(&go);
}

void GameObject::setParent(GameObject &go) {
    go.addChild(*this);
}

void GameObject::removeChild(GameObject &go) {
    for (int i = 0; i < childs.size(); ++i) {
        if (childs.at(i) == &go) {
            childs.at(i)->parent = NULL;
            childs.erase(childs.begin() + i);
            return;
        }
    }
    assert(false); ///< GameObject not in this
}

void GameObject::removeParent() {
    if (parent != NULL) parent->removeChild(*this);
}

std::vector<GameObject*> GameObject::getChilds() const {
    std::vector<GameObject*> cs;
    for (int i = 0; i < childs.size(); ++i) {
        std::vector<GameObject*> subChilds = childs.at(i)->getChilds();
        cs.push_back(childs.at(i));
        cs.insert(cs.end(), subChilds.begin(), subChilds.end());
    }
    return cs;
}

void GameObject::OnCollisionEnter(const Collision &collision) {
    std::vector<Behavior*> v = getComponents<Behavior>();
    for (Behavior* b : v) {
        b->OnCollisionEnter(collision);
    }
}

void GameObject::OnCollisionExit(const Collision &collision) {
    std::vector<Behavior*> v = getComponents<Behavior>();
    for (Behavior* b : v) {
        b->OnCollisionExit(collision);
    }
}

void GameObject::OnTriggerEnter(const Collider &triggered, const Collider &other) {
    std::vector<Behavior*> v = getComponents<Behavior>();
    for (Behavior* b : v) {
        b->OnTriggerEnter(triggered, other);
    }
}

void GameObject::OnTriggerExit(const Collider &triggered, const Collider &other) {
    std::vector<Behavior*> v = getComponents<Behavior>();
    for (Behavior* b : v) {
        b->OnTriggerExit(triggered, other);
    }
}