#include <Engine.hpp>
#include <User/Sandbox.hpp>
#include <User.hpp>

using namespace PancakeEngine;

int main() {

    CreatePrefabAndSpriteAndInput();
    Engine * app = new Engine();
    const char* filename = "../resources/maps/test.tmx";
    //app->sceneManager.loadScene(new Sandbox());
    SceneFactory sf;


    Scene* sc = sf.loadAllSceneObject(filename);
    // Add GUI

    unsigned height = sf::VideoMode::getDesktopMode().height / 2 + 50;
    unsigned width = sf::VideoMode::getDesktopMode().width / 2;
    sc->addGameObjectToGui<PlayerGUI1>().transform.setPosition(sf::Vector2f(width * 0 + 50, 50));
    //sc->addGameObjectToGui<PlayerGUI2>().transform.setPosition(sf::Vector2f(width * 1 + 50, 50));
    //sc->addGameObjectToGui<PlayerGUI3>().transform.setPosition(sf::Vector2f(width * 0 + 50, height));
    //sc->addGameObjectToGui<PlayerGUI4>().transform.setPosition(sf::Vector2f(width * 1 + 50, height));
    sc->addGameObject<GameControllerSoloObject>(1);

    SceneManager::loadScene(sc);

    app->run();
    delete app;

    return EXIT_SUCCESS;
}
