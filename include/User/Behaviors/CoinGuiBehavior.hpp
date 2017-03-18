//
// Created by virgil on 17/03/17.
//

#ifndef PANCAKE_COINGUIBEHAVIOR_HPP
#define PANCAKE_COINGUIBEHAVIOR_HPP

#include <GameLogic.hpp>

class CoinGuiBehavior : public PancakeEngine::Behavior {
public:
    void lateUpdate() override {
        nbCoinToSprite(PancakeEngine::SceneManager::findByName("GameController")->getComponent<GameController>()->coins);
    }

private:
    std::vector<PancakeEngine::SpriteRenderer*> text;

    void nbCoinToSprite(unsigned long nb) {
        std::string s = std::to_string(nb);
        while (text.size() < s.length()) {
            PancakeEngine::SpriteRenderer &sr = gameObject->addComponent<PancakeEngine::SpriteRenderer>();
            sr.setPosition(sf::Vector2f(text.size() * 40 + 50, 0));
            text.push_back(&sr);
        }

        for (unsigned i = 0; i < s.length(); ++i) {
            unsigned d = s[i] - '0';
            unsigned x = d % 6;
            unsigned y = d / 6;
            text[i]->setSprite(PancakeEngine::AssetsManager::getSpriteSheet("hud"), x, y);
        }
    }
};
#endif //PANCAKE_COINGUIBEHAVIOR_HPP
