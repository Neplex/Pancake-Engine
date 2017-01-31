#include "../include/Engine.hpp"
#include "../include/User/Ground.hpp"
#include "../include/User/Box.hpp"
#include "../include/User/MainCamera.hpp"
#include "../include/Inputs/InputManager.hpp"

using namespace PancakeEngine;

int main() {
    Engine * engine = new Engine();
    //Ground * ground = new Ground("Ground");
    //MainCamera * mainCamera = new MainCamera("MainCamera");
    Scene* scene = new Scene("TestScene");
    scene->addGameObject<Ground>();
    scene->addGameObject<MainCamera>();

    for (int i = 0; i < 40; ++i) {
        //Box * box = new Box("Box");
        scene->addGameObject<Box>();
    }

    engine->sceneManager.loadScene(scene);
    engine->window.setDebug();

    InputManager::createButton("Jump", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Space}));

    InputManager::createButton("ShowDebugInfo", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::F1}), Debug::switchEnableDebugGUI);

    engine->run();
    delete engine;
    return EXIT_SUCCESS;
}
