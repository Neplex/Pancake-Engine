#include "../include/Scene.hpp"
#include "../include/SpriteRenderer.hpp"
#include "../include/InputHandler.hpp"
#include "../include/Window.hpp"
#include "../include/SceneManager.hpp"

int main() {
    GameObject * go1 = new GameObject("");
    GameObject * go2 = new GameObject("");
    SpriteRenderer sr(32, 32);
    go1->addComponent(sr);

    Scene scene("TestScene");
    scene.addGameObject(go1);
    scene.addGameObject(go2);
    scene.awake();
    scene.start();

    SceneManager sceneManager = SceneManager();
    sceneManager.addScene(&scene);

    InputHandler inputHandler = InputHandler();

    Window window(sceneManager, inputHandler);
    window.run();

    return EXIT_SUCCESS;
}