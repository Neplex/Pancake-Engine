#include <Engine.hpp>
#include <User/Sandbox.hpp>
#include <Parser/SceneFactory.hpp>

using namespace PancakeEngine;

int main() {
    AssetsManager::createSpriteSheet("player1", "../resources/players/player1.png", 70, 100);
    AssetsManager::createSpriteSheet("player2", "../resources/players/player2.png", 70, 100);
    AssetsManager::createSpriteSheet("player3", "../resources/players/player3.png", 70, 100);
    AssetsManager::createSpriteSheet("player4", "../resources/players/player4.png", 70, 100);
    AssetsManager::createSpriteSheet("player5", "../resources/players/player5.png", 70, 100);
    AssetsManager::createSpriteSheet("tiles", "../resources/tiles/tiles.png", 70, 70);
    AssetsManager::createSpriteSheet("items", "../resources/items.png", 70, 70);

    Engine * app = new Engine();
    const char* filename = "../resources/test.tmx";
    //app->sceneManager.loadScene(new Sandbox());
    SceneFactory sf;
    SceneFactory::addPrefab<Coin>("Coin");
    SceneFactory::addPrefab<Player1>("Player");
    SceneFactory::addPrefab<Player2>("Player2");
    SceneFactory::addPrefab<Player3>("Player3");
    SceneFactory::addPrefab<Player4>("Player4");
    SceneFactory::addPrefab<Player5>("Player5");
    SceneFactory::addPrefab<Box>("Box");

    Scene* sc = sf.loadAllSceneObject(filename);
    // Add GUI
    AssetsManager::createSpriteSheet("heart", "../resources/heart.png", 53, 45);
    AssetsManager::createSpriteSheet("hud", "../resources/hud.png", 47, 47);
    unsigned height = sf::VideoMode::getDesktopMode().height - 120;
    unsigned width = sf::VideoMode::getDesktopMode().width / 5;
    sc->addGameObjectToGui<PlayerGUI1>().transform.setPosition(sf::Vector2f(width * 0 + 50, height));
    SceneManager::loadScene(sc);

    InputManager::createButton("player1_jump", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Z}));
    InputManager::createButton("player1_right", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::D}));
    InputManager::createButton("player1_left", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Q}));
    InputManager::createButton("player1_duck", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::S}));

    InputManager::createButton("player2_jump", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Up}));
    InputManager::createButton("player2_right", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Right}));
    InputManager::createButton("player2_left", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Left}));
    InputManager::createButton("player2_duck", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Down}));

    InputManager::createButton("player3_jump", std::vector<sf::Keyboard::Key> ({}));
    InputManager::createButton("player3_right", std::vector<sf::Keyboard::Key> ({}));
    InputManager::createButton("player3_left", std::vector<sf::Keyboard::Key> ({}));
    InputManager::createButton("player3_duck", std::vector<sf::Keyboard::Key> ({}));

    InputManager::createButton("player4_jump", std::vector<sf::Keyboard::Key> ({}));
    InputManager::createButton("player4_right", std::vector<sf::Keyboard::Key> ({}));
    InputManager::createButton("player4_left", std::vector<sf::Keyboard::Key> ({}));
    InputManager::createButton("player4_duck", std::vector<sf::Keyboard::Key> ({}));

    InputManager::createButton("player5_jump", std::vector<sf::Keyboard::Key> ({}));
    InputManager::createButton("player5_right", std::vector<sf::Keyboard::Key> ({}));
    InputManager::createButton("player5_left", std::vector<sf::Keyboard::Key> ({}));
    InputManager::createButton("player5_duck", std::vector<sf::Keyboard::Key> ({}));

    InputManager::createButton("ShowDebugInfo", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::F1}), Debug::switchEnableDebugGUI);

    app->run();
    delete app;

    return EXIT_SUCCESS;
}
