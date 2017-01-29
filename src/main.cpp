#include "../include/Engine.hpp"
#include "../include/User/Ground.hpp"
#include "../include/User/Box.hpp"
#include "../include/User/MainCamera.hpp"
#include "../include/Inputs/InputManager.hpp"

int main() {
    Engine * engine = new Engine();
    // TEST //
    // Ground
    Ground * ground = new Ground("Ground");
    // Box
    // Camera
    MainCamera * mainCamera = new MainCamera("MainCamera");
    Scene* scene = new Scene("TestScene");
    scene->addGameObject(ground);
    scene->addGameObject(mainCamera);

    for (int i = 0; i < 20; ++i) {
        Box * box = new Box("Box");
        scene->addGameObject(box);
    }

    //engine->sceneManager.addScene(scene);
    engine->sceneManager.loadScene(scene);
    engine->window.setDebug();

    InputManager::createButton("Jump", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Space}));
    /*InputManager::createButton("High", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Up}));
    InputManager::createButton("ShowDebugInfo", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::A}), &Debug::switchEnableDebugGUI);*/

    // TEST //
    engine->run();
    delete engine;
    return EXIT_SUCCESS;
}
