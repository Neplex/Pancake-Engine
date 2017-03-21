//
// Created by Darenn on 13/01/2017.
// Manage scenes (load them, get the current scenes etc)
//

#ifndef PANCAKE_SCENEMANAGER_HPP
#define PANCAKE_SCENEMANAGER_HPP


#include <vector>
#include <Physics/PhysicsEngine.hpp>
#include <GameLogic/Scene.hpp>

namespace PancakeEngine {

    class SceneManager {
    public:
        /**
         * Add the 'scene' to the manager
         * @param scene
         */
        static void addScene(Scene* scene){
            scenes.push_back(scene);
        };

        /**
         * Get the current scene
         * @return the current scene
         */
        static Scene* getCurrentScene(){
            //return scenes[currentScene];
            return scene;
        };

        /**
         * Set the scene with name 'name' as current.
         * No change if no scene has the name 'name'
         * @param name
         */
        static void setCurrentScene(std::string name){
            for (unsigned int i = 0; i < scenes.size(); ++i) {
                if (scenes[i]->name == name) {
                    currentScene = i;
                    return;
                }
            }
        };

        /**
         * Get next scene (in add order)
         */
        static void nextScene(){
            //currentScene = (currentScene++)%scenes.size();
        };

        static void loadScene(Scene* scene){
            //if (SceneManager::scene != NULL) delete SceneManager::scene;
            physicsEngine->resetWorld();
            SceneManager::scene = scene;
            getCurrentScene()->awake();
            getCurrentScene()->start();
        }
        ;

        static GameObject* findByName(std::string name) {
            for (GameObject* p_l: SceneManager::getCurrentScene()->layers) {
                for(GameObject* p_go : p_l->getChilds()) {
                    if (p_go->name == name) {
                        return p_go;
                    }
                }
            }
            return nullptr;
        }

        static PhysicsEngine* physicsEngine;

    private:
        friend class Engine; ///< the engine is the only one to call update and handleInputs
        static Scene* scene;
        static std::vector<Scene*> scenes;
        static unsigned int currentScene;
    };
}

#endif //PANCAKE_SCENEMANAGER_HPP
