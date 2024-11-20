//
// Created by nicolas on 08/03/17.
//

#ifndef PANCAKE_COINGUI_HPP
#define PANCAKE_COINGUI_HPP

#include <GameLogic/Components/SpriteRenderer.hpp>
#include <GameLogic/GameObject.hpp>
#include <Graphics/AssetsManager.hpp>
#include <User/Behaviors/CoinGuiBehavior.hpp>

class CoinGui : public PancakeEngine::GameObject {
 public:
  CoinGui() {
    name = "CoinGui";
    addComponent<PancakeEngine::SpriteRenderer>().setSprite(PancakeEngine::AssetsManager::getSpriteSheet("hud"), 0, 5);
    addComponent<CoinGuiBehavior>();
  }
};

#endif  // PANCAKE_COINGUI_HPP
