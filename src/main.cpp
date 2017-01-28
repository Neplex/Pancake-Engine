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
        Box * box = new Box("Box" + i);
        scene->addGameObject(box);
    }

    engine->sceneManager.addScene(scene);
    engine->sceneManager.loadScene();
    engine->window.setDebug();

    InputManager::createButton("Jump", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Space}));

    // TEST //
    engine->run();
    delete engine;
    return EXIT_SUCCESS;
}