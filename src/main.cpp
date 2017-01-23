#include "../include/Scene.hpp"
#include "../include/SpriteRenderer.hpp"
#include "../include/InputHandler.hpp"
#include "../include/Window.hpp"

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

    InputHandler inputHandler = InputHandler();

    Window window(scene, inputHandler);
    window.run();

    return EXIT_SUCCESS;
}