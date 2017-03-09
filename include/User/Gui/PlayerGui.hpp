//
// Created by nicolas on 08/03/17.
//

#ifndef PANCAKE_PLAYERGUI_HPP
#define PANCAKE_PLAYERGUI_HPP

#include <GameLogic/GameObject.hpp>
#include <GameLogic/Components/SpriteRenderer.hpp>
#include <Graphics/AssetsManager.hpp>

namespace PancakeEngine {
    class PlayerGUI : public GameObject {
        friend class PlayerGUI1;
        friend class PlayerGUI2;
        friend class PlayerGUI3;
        friend class PlayerGUI4;
        friend class PlayerGUI5;

        std::vector<SpriteRenderer*> lifeSprites;
        unsigned nbHeart = 3;
        unsigned life = nbHeart * 2;

        PlayerGUI (unsigned n) : GameObject() {
            name = n;
            life = n;

            SpriteRenderer& head = addComponent<SpriteRenderer>();
            head.setSprite(AssetsManager::getSpriteSheet("hud"), 4, n);

            for (int i = 0; i < nbHeart; ++i) {
                SpriteRenderer& heart = addComponent<SpriteRenderer>();
                heart.setSprite(AssetsManager::getSpriteSheet("heart"), 2, 0);
                heart.setPosition(sf::Vector2f(i*55 + 60, 0));
                lifeSprites.push_back(&heart);
            }
        }

        void lifeToSprite() {
            SpriteSheet& heart = AssetsManager::getSpriteSheet("heart");
            unsigned buffLife = life;
            for (int i = 0; i < lifeSprites.size(); ++i) {
                if (buffLife >= 2) { lifeSprites[i]->setSprite(heart, 0, 0); buffLife-=2; }
                else if (buffLife == 1) { lifeSprites[i]->setSprite(heart, 1, 0); buffLife--; }
                else { lifeSprites[i]->setSprite(heart, 2, 0); }
            }
        }

    public:
        void lateUpdate() override {
            GameObject::lateUpdate();
            lifeToSprite();
        }
    };

    class PlayerGUI1 : public PlayerGUI { public: PlayerGUI1() : PlayerGUI(1) {} };
    class PlayerGUI2 : public PlayerGUI { public: PlayerGUI2() : PlayerGUI(2) {} };
    class PlayerGUI3 : public PlayerGUI { public: PlayerGUI3() : PlayerGUI(3) {} };
    class PlayerGUI4 : public PlayerGUI { public: PlayerGUI4() : PlayerGUI(4) {} };
    class PlayerGUI5 : public PlayerGUI { public: PlayerGUI5() : PlayerGUI(5) {} };

}

#endif //PANCAKE_PLAYERGUI_HPP
