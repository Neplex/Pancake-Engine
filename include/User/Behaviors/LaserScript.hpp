//
// Created by nicolas on 15/03/17.
//

#ifndef PANCAKE_LASERSCRIPT_HPP
#define PANCAKE_LASERSCRIPT_HPP


#include <GameLogic.hpp>
#include <GameLogic/Components/Behavior.hpp>

class LaserScript : public PancakeEngine::Behavior {
public:
    void awake() override {
        PancakeEngine::BoxCollider& bc = gameObject->addComponent<PancakeEngine::BoxCollider>();
        PancakeEngine::DataStorage* ds = gameObject->getComponent<PancakeEngine::DataStorage>();
        bc.isTrigger = true;

        PancakeEngine::SpriteRenderer& sr = gameObject->addComponent<PancakeEngine::SpriteRenderer>();
        PancakeEngine::SpriteSheet& ss = PancakeEngine::AssetsManager::getSpriteSheet("miscs");
        int width = ds->get<int>("width");
        int height = ds->get<int>("height");
        if (width > height) {
            sr.setSprite(ss, 11, 6);
            sr.setScale(sf::Vector2f(width / 70, 1));
            bc.width = width;
            bc.height = 20;

        } else {
            sr.setSprite(ss, 11, 5);
            sr.setScale(sf::Vector2f(1, height / 70));
            bc.width = 20;
            bc.height = height;
        }
    }
};


#endif //PANCAKE_LASERSCRIPT_HPP
