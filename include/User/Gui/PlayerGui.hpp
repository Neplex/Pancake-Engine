//
// Created by nicolas on 08/03/17.
//

#ifndef PANCAKE_PLAYERGUI_HPP
#define PANCAKE_PLAYERGUI_HPP

#include <GameLogic/GameObject.hpp>
#include <GameLogic/Components/SpriteRenderer.hpp>
#include <Graphics/AssetsManager.hpp>

#include <SceneManager.hpp>
#include <User/Health.hpp>



class PlayerGuiScript : public PancakeEngine::Behavior {

    public:

    std::vector<PancakeEngine::SpriteRenderer*> lifeSprites;
    unsigned nbHeart = 3;
    int playerNumber;


    void lifeToSprite(unsigned life) {
        PancakeEngine::SpriteSheet& heart = PancakeEngine::AssetsManager::getSpriteSheet("heart");
        unsigned buffLife = life;
        for (int i = 0; i < lifeSprites.size(); ++i) {
            if (buffLife >= 2) { lifeSprites[i]->setSprite(heart, 0, 0); buffLife-=2; }
            else if (buffLife == 1) { lifeSprites[i]->setSprite(heart, 1, 0); buffLife--; }
            else { lifeSprites[i]->setSprite(heart, 2, 0); }
        }
    }

    Health* playerHealth = NULL;

    void awake() override {
        PancakeEngine::GameObject* go = PancakeEngine::SceneManager::findByName(std::string("player") + std::to_string(playerNumber));
        if (go == NULL) {
            destroy(*gameObject);
            return;
        };
        playerHealth = go->getComponent<Health>();
    }

    void update() override {
        if (playerHealth) lifeToSprite(playerHealth->getHp());
    }
};


class PlayerGUI : public PancakeEngine::GameObject {
    friend class PlayerGUI1;
    friend class PlayerGUI2;
    friend class PlayerGUI3;
    friend class PlayerGUI4;
    friend class PlayerGUI5;

    PlayerGUI (unsigned n) : GameObject() {
        PlayerGuiScript& pgs = addComponent<PlayerGuiScript>();
        name = "PlayerGui" + n;
        pgs.playerNumber = n;

        PancakeEngine::SpriteRenderer& head = addComponent<PancakeEngine::SpriteRenderer>();
        head.setSprite(PancakeEngine::AssetsManager::getSpriteSheet("hud"), 4, n);

        for (int i = 0; i < pgs.nbHeart; ++i) {
            PancakeEngine::SpriteRenderer& heart = addComponent<PancakeEngine::SpriteRenderer>();
            heart.setSprite(PancakeEngine::AssetsManager::getSpriteSheet("heart"), 2, 0);
            heart.setPosition(sf::Vector2f(i*55 + 60, 0));
            pgs.lifeSprites.push_back(&heart);
        }
    }

};

class PlayerGUI1 : public PlayerGUI { public: PlayerGUI1() : PlayerGUI(1) {} };
class PlayerGUI2 : public PlayerGUI { public: PlayerGUI2() : PlayerGUI(2) {} };
class PlayerGUI3 : public PlayerGUI { public: PlayerGUI3() : PlayerGUI(3) {} };
class PlayerGUI4 : public PlayerGUI { public: PlayerGUI4() : PlayerGUI(4) {} };
class PlayerGUI5 : public PlayerGUI { public: PlayerGUI5() : PlayerGUI(5) {} };




#endif //PANCAKE_PLAYERGUI_HPP
