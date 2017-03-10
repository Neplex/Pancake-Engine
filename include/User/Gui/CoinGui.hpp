//
// Created by nicolas on 08/03/17.
//

#ifndef PANCAKE_COINGUI_HPP
#define PANCAKE_COINGUI_HPP

#include <GameLogic/GameObject.hpp>
#include <GameLogic/Components/SpriteRenderer.hpp>
#include <Graphics/AssetsManager.hpp>
#include <Time.hpp>
#include <stdlib.h>

namespace PancakeEngine {

    class CoinGuiBehavior : public Behavior {
    public:
        void lateUpdate() override {
            for (Component* sr : text) {
                //destroy(*sr);
            }
            //nbCoinToSprite(100);
        }

    private:
        std::vector<SpriteRenderer*> text;

        void nbCoinToSprite(unsigned long nb) {
            std::string s = std::to_string(nb);
            for (unsigned i = 0; i < s.length(); ++i) {
                SpriteRenderer &sr = gameObject->addComponent<SpriteRenderer>();
                text.push_back(&sr);
                unsigned d = s[i] - '0';
                unsigned x = d % 6;
                unsigned y = d / 6;
                sr.setSprite(AssetsManager::getSpriteSheet("hud"), x, y);
                sr.setPosition(sf::Vector2f(i * 40 + 50, 0));
            }
        }
    };

    class CoinGui : public GameObject {
    public:
        CoinGui() {
            name = "CoinGui";
            addComponent<SpriteRenderer>().setSprite(AssetsManager::getSpriteSheet("hud"), 0, 5);
            addComponent<CoinGuiBehavior>();
        }
    };
}

#endif //PANCAKE_COINGUI_HPP
