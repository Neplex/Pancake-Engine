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

    class CoinGui : public GameObject {
    public:
        std::vector<SpriteRenderer*> text;

        CoinGui() {
            name = "CoinGui";
            addComponent<SpriteRenderer>().setSprite(AssetsManager::getSpriteSheet("hud"), 0, 5);

        }

        void nbCoinToSprite(unsigned nb, unsigned i) {
            div_t q = div(nb, 10);
            if (q.quot) nbCoinToSprite(q.quot, i+1);
            SpriteRenderer& sr = addComponent<SpriteRenderer>();
            text.push_back(&sr);
            unsigned x = q.rem%5;
            unsigned y = q.rem/5;
            sr.setSprite(AssetsManager::getSpriteSheet("hud"), x, y);
            sr.setPosition(sf::Vector2f(i*45 + 50, 0));
        }

        void lateUpdate() override {
            GameObject::lateUpdate();
            for (Component* sr : text) {
                //sr->toDestroy = true;
            }
            nbCoinToSprite(0, 0);
        }
    };
}

#endif //PANCAKE_COINGUI_HPP
