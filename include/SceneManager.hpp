//
// Created by Darenn on 13/01/2017.
// Manage scenes (load them, get the current scenes etc)
//

#ifndef PANCAKE_SCENEMANAGER_HPP
#define PANCAKE_SCENEMANAGER_HPP


#include <vector>
#include "GameLogic/Scene.hpp"

namespace PancakeEngine {

    class SceneManager {
    public:
        SceneManager()
                :currentScene(0)
        {

        }

        ~SceneManager() {
            delete scene;
        }

        /**
         * Add the 'scene' to the manager
         * @param scene
         */
        void addScene(Scene* scene);

        /**
         * Get the current scene
         * @return the current scene
         */
        Scene* getCurrentScene();

        /**
         * Set the scene with name 'name' as current.
         * No change if no scene has the name 'name'
         * @param name
         */
        void setCurrentScene(std::string name);

        /**
         * Get next scene (in add order)
         */
        void nextScene();

        void loadScene(Scene* scene);

    private:
        Scene* scene;
        std::vector<Scene*> scenes;
        unsigned int currentScene;
    };
}

#endif //PANCAKE_SCENEMANAGER_HPP
