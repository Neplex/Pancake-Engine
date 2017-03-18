//
// Created by virgil on 17/03/17.
//

#include <User.hpp>
void CreatePrefabAndSpriteAndInput() {
    PancakeEngine::AssetsManager::createSpriteSheet("player1", "../resources/players/player1.png", 70, 100);
    PancakeEngine::AssetsManager::createSpriteSheet("player2", "../resources/players/player2.png", 70, 100);
    PancakeEngine::AssetsManager::createSpriteSheet("player3", "../resources/players/player3.png", 70, 100);
    PancakeEngine::AssetsManager::createSpriteSheet("player4", "../resources/players/player4.png", 70, 100);
    PancakeEngine::AssetsManager::createSpriteSheet("player5", "../resources/players/player5.png", 70, 100);
    PancakeEngine::AssetsManager::createSpriteSheet("tiles", "../resources/tiles/tiles.png", 70, 70);
    PancakeEngine::AssetsManager::createSpriteSheet("miscs", "../resources/tiles/miscs.png", 70, 70);
    PancakeEngine::AssetsManager::createSpriteSheet("items", "../resources/items.png", 70, 70);
    PancakeEngine::AssetsManager::createSpriteSheet("slimeGreen", "../resources/enemies/slimeGreen.png", 57, 34);
    PancakeEngine::AssetsManager::createSpriteSheet("slimePink", "../resources/enemies/slimePink.png", 57, 34);
    PancakeEngine::AssetsManager::createSpriteSheet("slimeBlue", "../resources/enemies/slimeBlue.png", 57, 34);
    PancakeEngine::AssetsManager::createSpriteSheet("heart", "../resources/heart.png", 53, 45);
    PancakeEngine::AssetsManager::createSpriteSheet("hud", "../resources/hud.png", 47, 47);

    PancakeEngine::SceneFactory::addPrefab<Coin>("Coin");
    PancakeEngine::SceneFactory::addPrefab<Player1>("Player");
    PancakeEngine::SceneFactory::addPrefab<Player1>("Player1");
    PancakeEngine::SceneFactory::addPrefab<Player2>("Player2");
    PancakeEngine::SceneFactory::addPrefab<Player3>("Player3");
    PancakeEngine::SceneFactory::addPrefab<Player4>("Player4");
    PancakeEngine::SceneFactory::addPrefab<Player5>("Player5");
    PancakeEngine::SceneFactory::addPrefab<Box>("Box");
    PancakeEngine::SceneFactory::addPrefab<Rock>("Rock");
    PancakeEngine::SceneFactory::addPrefab<SmallRock>("SmallRock");
    PancakeEngine::SceneFactory::addPrefab<Ladder>("Ladder");
    PancakeEngine::SceneFactory::addPrefab<Water>("Water");
    PancakeEngine::SceneFactory::addPrefab<Laser>("Laser");
    PancakeEngine::SceneFactory::addPrefab<DeathZone>("DeathZone");
    PancakeEngine::SceneFactory::addPrefab<Transporter1>("Transporter1");
    PancakeEngine::SceneFactory::addPrefab<Transporter2>("Transporter2");
    PancakeEngine::SceneFactory::addPrefab<Transporter3>("Transporter3");
    PancakeEngine::SceneFactory::addPrefab<Trampoline>("Trampoline");
    PancakeEngine::SceneFactory::addPrefab<CheckPoint1>("CheckPoint1");
    PancakeEngine::SceneFactory::addPrefab<CheckPoint2>("CheckPoint2");
    PancakeEngine::SceneFactory::addPrefab<CheckPoint3>("CheckPoint3");
    PancakeEngine::SceneFactory::addPrefab<CheckPoint4>("CheckPoint4");
    PancakeEngine::SceneFactory::addPrefab<LaserButton>("LaserButton");
    PancakeEngine::SceneFactory::addPrefab<Enemy1>("slimeGreen");
    PancakeEngine::SceneFactory::addPrefab<Enemy2>("slimePink");
    PancakeEngine::SceneFactory::addPrefab<Enemy3>("slimeBlue");

    PancakeEngine::InputManager::createButton("player1_jump", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Z}));
    PancakeEngine::InputManager::createButton("player1_fire", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Space}));
    PancakeEngine::InputManager::createButton("player1_right", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::D}));
    PancakeEngine::InputManager::createButton("player1_left", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Q}));
    PancakeEngine::InputManager::createButton("player1_duck", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::S}));

    PancakeEngine::InputManager::createButton("player2_jump", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Up}));
    PancakeEngine::InputManager::createButton("player2_fire", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::RControl}));
    PancakeEngine::InputManager::createButton("player2_right", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Right}));
    PancakeEngine::InputManager::createButton("player2_left", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Left}));
    PancakeEngine::InputManager::createButton("player2_duck", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Down}));

    PancakeEngine::InputManager::createButton("player3_jump", 0, -1, -1);
    PancakeEngine::InputManager::createButton("player3_fire", 0, 0);
    PancakeEngine::InputManager::createButton("player3_right", 0, 1, 1);
    PancakeEngine::InputManager::createButton("player3_left", 0, -1, 1);
    PancakeEngine::InputManager::createButton("player3_duck",0, 1, -1);

    PancakeEngine::InputManager::createButton("player4_jump", 2, -1, -1);
    PancakeEngine::InputManager::createButton("player4_fire", 2, 0);
    PancakeEngine::InputManager::createButton("player4_right", 2, 1, 1);
    PancakeEngine::InputManager::createButton("player4_left", 2, -1, 1);
    PancakeEngine::InputManager::createButton("player4_duck",2, 1, -1);

    PancakeEngine::InputManager::createButton("ShowDebugInfo", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::F1}), PancakeEngine::Debug::switchEnableDebugGUI);
};
