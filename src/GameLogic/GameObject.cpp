//
// Created by Darenn on 17/01/2017.
//

#include <GameLogic/GameObject.hpp>

using namespace PancakeEngine;

int GameObject::numGameobjects = 0;

GameObject::GameObject() {
  transform.gameObject = this;
  numGameobjects++;
}

void GameObject::awake() {
  for (const auto component : components) {
    component->awake();
  }

  for (const auto child : childs) {
    child->awake();
  }
}

void GameObject::start() {
  for (const auto &component : components) {
    component->start();
  }

  for (const auto &child : childs) {
    child->start();
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

  for (const auto &child : childs) {
    child->update();
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

  for (const auto &child : childs) {
    child->lateUpdate();
  }
}

void GameObject::destroyComponents() {
  for (const auto c : componentsToDestroy) delete c;
  componentsToDestroy.clear();
}

void GameObject::addChild(GameObject &go) {
  if (go.parent != nullptr) go.removeParent();
  go.parent = this;
  childs.push_back(&go);
}

void GameObject::setParent(GameObject &go) { go.addChild(*this); }

void GameObject::removeChild(const GameObject &go) {
  for (int i = 0; i < childs.size(); ++i) {
    if (childs.at(i) == &go) {
      childs.at(i)->parent = nullptr;
      childs.erase(childs.begin() + i);
      return;
    }
  }
  assert(false);  ///< GameObject not in this
}

void GameObject::removeParent() {
  if (parent != nullptr) parent->removeChild(*this);
}

std::vector<GameObject *> GameObject::getChilds() const {
  std::vector<GameObject *> cs;

  for (auto child : childs) {
    std::vector<GameObject *> subChilds = child->getChilds();
    cs.push_back(child);
    cs.insert(cs.end(), subChilds.begin(), subChilds.end());
  }

  return cs;
}

void GameObject::OnCollisionEnter(const Collision &collision) {
  std::vector<Behavior *> v = getComponents<Behavior>();
  for (Behavior *b : v) {
    b->OnCollisionEnter(collision);
  }
}

void GameObject::OnCollisionExit(const Collision &collision) {
  std::vector<Behavior *> v = getComponents<Behavior>();
  for (Behavior *b : v) {
    b->OnCollisionExit(collision);
  }
}

void GameObject::OnTriggerEnter(const Collider &triggered, const Collider &other) {
  std::vector<Behavior *> v = getComponents<Behavior>();
  for (Behavior *b : v) {
    b->OnTriggerEnter(triggered, other);
  }
}

void GameObject::OnTriggerExit(const Collider &triggered, const Collider &other) {
  std::vector<Behavior *> v = getComponents<Behavior>();
  for (Behavior *b : v) {
    b->OnTriggerExit(triggered, other);
  }
}