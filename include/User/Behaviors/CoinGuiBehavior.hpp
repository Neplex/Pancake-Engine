//
// Created by virgil on 17/03/17.
//

#ifndef PANCAKE_COINGUIBEHAVIOR_HPP
#define PANCAKE_COINGUIBEHAVIOR_HPP

#include <GameLogic.hpp>

class CoinGuiBehavior : public PancakeEngine::Behavior {
public:
    void lateUpdate() override {
        for (PancakeEngine::Component* sr : text) {
            //destroy(*sr);
        }
        //nbCoinToSprite(100);
    }

private:
    std::vector<PancakeEngine::SpriteRenderer*> text;

    void nbCoinToSprite(unsigned long nb) {
        std::string s = std::to_string(nb);
        for (unsigned i = 0; i < s.length(); ++i) {
            PancakeEngine::SpriteRenderer &sr = gameObject->addComponent<PancakeEngine::SpriteRenderer>();
            text.push_back(&sr);
            unsigned d = s[i] - '0';
            unsigned x = d % 6;
            unsigned y = d / 6;
            sr.setSprite(PancakeEngine::AssetsManager::getSpriteSheet("hud"), x, y);
            sr.setPosition(sf::Vector2f(i * 40 + 50, 0));
        }
    }
};
#endif //PANCAKE_COINGUIBEHAVIOR_HPP
