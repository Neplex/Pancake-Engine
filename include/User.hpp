//
// Created by virgil on 17/03/17.
//

#ifndef PANCAKE_USER_HPP
#define PANCAKE_USER_HPP
#include <User/Items/Rock.hpp>
#include <User/Ladder.hpp>
#include <User/Items/Transporter.hpp>
#include <User/Items/Trampoline.hpp>
#include <User/Items/Water.hpp>
#include <User/GameControllerSoloObject.hpp>
#include <User/CheckPointObject.hpp>
#include <User/Laser.hpp>
#include <User/DeathZone.hpp>
#include <User/Enemy.hpp>
#include <User/LaserButton.hpp>
#include <Parser/SceneFactory.hpp>
#include <User/Coin.hpp>
#include <User/Player.hpp>
#include <User/Items/Box.hpp>


namespace PancakeEngine{
    void loadPrefabAndSprite() {
        AssetsManager::createSpriteSheet("player1", "../resources/players/player1.png", 70, 100);
        AssetsManager::createSpriteSheet("player2", "../resources/players/player2.png", 70, 100);
        AssetsManager::createSpriteSheet("player3", "../resources/players/player3.png", 70, 100);
        AssetsManager::createSpriteSheet("player4", "../resources/players/player4.png", 70, 100);
        AssetsManager::createSpriteSheet("player5", "../resources/players/player5.png", 70, 100);
        AssetsManager::createSpriteSheet("tiles", "../resources/tiles/tiles.png", 70, 70);
        AssetsManager::createSpriteSheet("miscs", "../resources/tiles/miscs.png", 70, 70);
        AssetsManager::createSpriteSheet("items", "../resources/items.png", 70, 70);
        AssetsManager::createSpriteSheet("slimeGreen", "../resources/enemies/slimeGreen.png", 57, 34);
        AssetsManager::createSpriteSheet("slimePink", "../resources/enemies/slimePink.png", 57, 34);
        AssetsManager::createSpriteSheet("slimeBlue", "../resources/enemies/slimeBlue.png", 57, 34);
        AssetsManager::createSpriteSheet("heart", "../resources/heart.png", 53, 45);
        AssetsManager::createSpriteSheet("hud", "../resources/hud.png", 47, 47);

        SceneFactory::addPrefab<Coin>("Coin");
        SceneFactory::addPrefab<Player1>("Player");
        SceneFactory::addPrefab<Player1>("Player1");
        SceneFactory::addPrefab<Player2>("Player2");
        SceneFactory::addPrefab<Player3>("Player3");
        SceneFactory::addPrefab<Player4>("Player4");
        SceneFactory::addPrefab<Player5>("Player5");
        SceneFactory::addPrefab<Box>("Box");
        SceneFactory::addPrefab<Rock>("Rock");
        SceneFactory::addPrefab<SmallRock>("SmallRock");
        SceneFactory::addPrefab<Ladder>("Ladder");
        SceneFactory::addPrefab<Water>("Water");
        SceneFactory::addPrefab<Laser>("Laser");
        SceneFactory::addPrefab<DeathZone>("DeathZone");
        SceneFactory::addPrefab<Transporter1>("Transporter1");
        SceneFactory::addPrefab<Transporter2>("Transporter2");
        SceneFactory::addPrefab<Transporter3>("Transporter3");
        SceneFactory::addPrefab<Trampoline>("Trampoline");
        SceneFactory::addPrefab<CheckPointObject1>("CheckPoint1");
        SceneFactory::addPrefab<CheckPointObject2>("CheckPoint2");
        SceneFactory::addPrefab<CheckPointObject3>("CheckPoint3");
        SceneFactory::addPrefab<CheckPointObject4>("CheckPoint4");
        SceneFactory::addPrefab<LaserButton>("LaserButton");
        SceneFactory::addPrefab<Enemy1>("slimeGreen");
        SceneFactory::addPrefab<Enemy2>("slimePink");
        SceneFactory::addPrefab<Enemy3>("slimeBlue");

        InputManager::createButton("player1_jump", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Z}));
        InputManager::createButton("player1_fire", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Space}));
        InputManager::createButton("player1_right", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::D}));
        InputManager::createButton("player1_left", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Q}));
        InputManager::createButton("player1_duck", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::S}));

        InputManager::createButton("player2_jump", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Up}));
        InputManager::createButton("player2_fire", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::RControl}));
        InputManager::createButton("player2_right", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Right}));
        InputManager::createButton("player2_left", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Left}));
        InputManager::createButton("player2_duck", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Down}));

        InputManager::createButton("player3_jump", 0, -1, -1);
        InputManager::createButton("player3_fire", 0, 0);
        InputManager::createButton("player3_right", 0, 1, 1);
        InputManager::createButton("player3_left", 0, -1, 1);
        InputManager::createButton("player3_duck",0, 1, -1);

        InputManager::createButton("player4_jump", 2, -1, -1);
        InputManager::createButton("player4_fire", 2, 0);
        InputManager::createButton("player4_right", 2, 1, 1);
        InputManager::createButton("player4_left", 2, -1, 1);
        InputManager::createButton("player4_duck",2, 1, -1);

        InputManager::createButton("ShowDebugInfo", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::F1}), Debug::switchEnableDebugGUI);
    };

};
#endif //PANCAKE_USER_HPP
