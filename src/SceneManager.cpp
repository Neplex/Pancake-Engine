//
// Created by nicolas on 23/01/17.
//

#include <SceneManager.hpp>

using namespace PancakeEngine;

Scene *SceneManager::scene = nullptr;
std::vector<Scene *> SceneManager::scenes = std::vector<Scene *>();
PhysicsEngine *SceneManager::physicsEngine = nullptr;
