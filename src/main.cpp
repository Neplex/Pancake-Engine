#include <User/Coin.hpp>
#include "../include/Engine.hpp"
#include "../include/User/Box.hpp"
#include "../include/User/MainCamera.hpp"
#include "../include/User/Ground.hpp"
#include <Parser/SceneFactory.hpp>
using namespace PancakeEngine;

int main() {
    Engine * engine = new Engine();
    //Ground * ground = new Ground("Ground");
    //MainCamera * mainCamera = new MainCamera("MainCamera");
    Scene& scene = SceneFactory::loadAllGameObject("../resources/sans-titre.tmx");;
    //scene.addGameObject<Ground>();
    //scene.addGameObject<Ground>().transform.setPosition(sf::Vector2f(1000, 228));

    for (int i = 0; i < 1; ++i) {
        //Box * box = new Box("Box");
        scene->addGameObject<Box>();
    }
    Box& player = scene->addGameObject<Box>();
    player.addComponent<PlayerController>();
    player.addComponent<Camera>();
    player.getComponent<Rigidbody>()->setFreezeRotation(true);
    scene->addGameObject<Coin>().transform.setPosition(sf::Vector2f(300, -100));

    //scene->addGameObject<MainCamera>();

    engine->sceneManager.loadScene(scene);
   // engine->window.setDebug();

    InputManager::createButton("Jump", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Space}));
    InputManager::createButton("Left", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Left}));
    InputManager::createButton("Right", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Right}));

    InputManager::createButton("ShowDebugInfo", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::F1}), Debug::switchEnableDebugGUI);

    InputManager::createButton("S1", std::vector<sf::Keyboard::Key>({sf::Keyboard::Key::Up}));
    InputManager::createButton("S2", std::vector<sf::Keyboard::Key>({sf::Keyboard::Key::Down}));
    
    engine->run();
    delete engine;
    return EXIT_SUCCESS;
}
