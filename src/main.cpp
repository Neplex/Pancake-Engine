#include "../include/Engine.hpp"
#include "../include/User/Ground.hpp"
#include "../include/User/Box.hpp"
#include "../include/User/MainCamera.hpp"

int main() {
    Engine * engine = new Engine();
    // TEST //
    // Ground
    Ground * ground = new Ground("Ground");
    // Box
    Box * box = new Box("Box1");
    // Camera
    MainCamera * mainCamera = new MainCamera("MainCamera");
    Scene* scene = new Scene("TestScene");
    scene->addGameObject(ground);
    scene->addGameObject(box);
    scene->addGameObject(mainCamera);
    scene->awake();
    scene->start();

    engine->sceneManager.addScene(scene);
    engine->window.setDebug();
    // TEST //
    engine->run();
    delete engine;
    return EXIT_SUCCESS;
}