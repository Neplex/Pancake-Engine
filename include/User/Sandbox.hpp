//
// Created by nicolas on 15/02/17.
//

#ifndef PANCAKE_SANDBOX_HPP
#define PANCAKE_SANDBOX_HPP

#include <GameLogic.hpp>
#include <GameLogic/Components/DataStorage.hpp>
#include <User/Ground.hpp>
#include <User/Gui/CoinGui.hpp>
#include <User/Gui/PlayerGui.hpp>
#include <User/Items/Box.hpp>
#include <User/Items/Coin.hpp>
#include <User/Player.hpp>

class Sandbox : public PancakeEngine::Scene {
 public:
  Sandbox() : Scene("Sandbox") {
    PancakeEngine::AssetsManager::createSpriteSheet("player1", "../resources/players/player1.png", 70, 100);
    PancakeEngine::AssetsManager::createSpriteSheet("player2", "../resources/players/player2.png", 70, 100);
    PancakeEngine::AssetsManager::createSpriteSheet("player3", "../resources/players/player3.png", 70, 100);
    PancakeEngine::AssetsManager::createSpriteSheet("player4", "../resources/players/player4.png", 70, 100);
    PancakeEngine::AssetsManager::createSpriteSheet("player5", "../resources/players/player5.png", 70, 100);
    PancakeEngine::AssetsManager::createSpriteSheet("tiles", "../resources/tiles/tiles.png", 70, 70);
    PancakeEngine::AssetsManager::createSpriteSheet("items", "../resources/items.png", 70, 70);
    PancakeEngine::AssetsManager::createSpriteSheet("heart", "../resources/heart.png", 53, 45);
    PancakeEngine::AssetsManager::createSpriteSheet("hud", "../resources/hud.png", 47, 47);

    // Players
    auto &p = addGameObject<Player1>(2);
    // addGameObject<Player2>(2);
    // addGameObject<Player3>(2);
    // addGameObject<Player4>(2);
    // addGameObject<Player5>(2);

    Coin &c = addGameObject<Coin>(1);
    c.transform.setPosition(sf::Vector2f(0, -200));
    p.addChild(c);
    p.addComponent<PancakeEngine::DataStorage>();

    // Add objects
    addGameObject<Ground>(0).transform.setPosition(sf::Vector2f(0, 250));
    addGameObject<Box>(1);
    addGameObject<Box>(1);
    addGameObject<Box>(1);

    for (int i = 1; i <= 10; ++i) addGameObject<Coin>(1).transform.setPosition(sf::Vector2f(-75 * i - 50, -20));

    // Add GUI
    unsigned height = sf::VideoMode::getDesktopMode().height - 120;
    unsigned width = sf::VideoMode::getDesktopMode().width / 5;
    addGameObjectToGui<PlayerGUI1>().transform.setPosition(sf::Vector2f(width * 0 + 50, height));
    addGameObjectToGui<PlayerGUI2>().transform.setPosition(sf::Vector2f(width * 1 + 50, height));
    addGameObjectToGui<PlayerGUI3>().transform.setPosition(sf::Vector2f(width * 2 + 50, height));
    addGameObjectToGui<PlayerGUI4>().transform.setPosition(sf::Vector2f(width * 3 + 50, height));
    addGameObjectToGui<PlayerGUI5>().transform.setPosition(sf::Vector2f(width * 4 + 50, height));

    addGameObjectToGui<CoinGui>().transform.setPosition(sf::Vector2f(50, 50));
  }
};

#endif  // PANCAKE_SANDBOX_HPP
