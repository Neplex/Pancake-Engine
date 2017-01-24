#include "../include/SpriteRenderer.hpp"
#include "../include/Window.hpp"

int main() {
    GameObject * go1 = new GameObject("");
    GameObject * go2 = new GameObject("");
    SpriteRenderer sr(32, 32);
    BoxCollider bc = BoxCollider();
    bc.width = 32; bc.height = 32;
    bc.gameObject = go1;
    bc.offset = sf::Vector2f(25, 25);
    go1->transform->setPosition(sf::Vector2f(100, 100));
    go1->transform->setRotation(10);
    go1->addComponent(sr);
    go1->addComponent(bc);

    Scene scene("TestScene");
    scene.addGameObject(go1);
    scene.addGameObject(go2);
    scene.awake();
    scene.start();

    SceneManager sceneManager = SceneManager();
    sceneManager.addScene(&scene);

    InputHandler inputHandler = InputHandler();

    Window window(sceneManager, inputHandler);
    window.setDebug();

    while (true) {
        window.handleEvent();
        sceneManager.getCurrentScene()->update();
        sceneManager.getCurrentScene()->lateUpdate();
        window.render();
    }

    return EXIT_SUCCESS;
}