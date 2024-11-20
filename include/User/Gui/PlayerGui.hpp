//
// Created by nicolas on 08/03/17.
//

#ifndef PANCAKE_PLAYERGUI_HPP
#define PANCAKE_PLAYERGUI_HPP

#include <GameLogic/Components/SpriteRenderer.hpp>
#include <GameLogic/GameObject.hpp>
#include <Graphics/AssetsManager.hpp>
#include <SceneManager.hpp>
#include <User/Health.hpp>

class PlayerGuiScript : public PancakeEngine::Behavior {
 public:
  std::vector<PancakeEngine::SpriteRenderer *> lifeSprites;
  unsigned nbHeart = 3;
  unsigned playerNumber{};

  void lifeToSprite(unsigned life) const {
    PancakeEngine::SpriteSheet &heart = PancakeEngine::AssetsManager::getSpriteSheet("heart");
    unsigned buffLife = life;

    for (const auto lifeSprite : lifeSprites) {
      if (buffLife >= 2) {
        lifeSprite->setSprite(heart, 0, 0);
        buffLife -= 2;
      } else if (buffLife == 1) {
        lifeSprite->setSprite(heart, 1, 0);
        buffLife--;
      } else {
        lifeSprite->setSprite(heart, 2, 0);
      }
    }
  }

  Health *playerHealth = nullptr;

  void awake() override {
    PancakeEngine::GameObject *go =
        PancakeEngine::SceneManager::findByName(std::string("player") + std::to_string(playerNumber));

    if (go == nullptr) {
      destroy(*gameObject);
      return;
    }

    playerHealth = go->getComponent<Health>();
  }

  void update() override {
    if (playerHealth) lifeToSprite(playerHealth->getHp());
  }
};

class PlayerGUI : public PancakeEngine::GameObject {
 public:
  virtual ~PlayerGUI() = default;

 private:
  friend class PlayerGUI1;
  friend class PlayerGUI2;
  friend class PlayerGUI3;
  friend class PlayerGUI4;
  friend class PlayerGUI5;

  explicit PlayerGUI(unsigned n) {
    auto &pgs = addComponent<PlayerGuiScript>();
    name = "PlayerGui" + n;
    pgs.playerNumber = n;

    auto &head = addComponent<PancakeEngine::SpriteRenderer>();
    head.setSprite(PancakeEngine::AssetsManager::getSpriteSheet("hud"), 4, n);

    for (int i = 0; i < pgs.nbHeart; ++i) {
      auto &heart = addComponent<PancakeEngine::SpriteRenderer>();
      heart.setSprite(PancakeEngine::AssetsManager::getSpriteSheet("heart"), 2, 0);
      heart.setPosition(sf::Vector2f(i * 55 + 60, 0));
      pgs.lifeSprites.push_back(&heart);
    }
  }
};

class PlayerGUI1 : public PlayerGUI {
 public:
  PlayerGUI1() : PlayerGUI(1) {}
};
class PlayerGUI2 : public PlayerGUI {
 public:
  PlayerGUI2() : PlayerGUI(2) {}
};
class PlayerGUI3 : public PlayerGUI {
 public:
  PlayerGUI3() : PlayerGUI(3) {}
};
class PlayerGUI4 : public PlayerGUI {
 public:
  PlayerGUI4() : PlayerGUI(4) {}
};
class PlayerGUI5 : public PlayerGUI {
 public:
  PlayerGUI5() : PlayerGUI(5) {}
};

#endif  // PANCAKE_PLAYERGUI_HPP
