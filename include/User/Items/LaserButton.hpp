//
// Created by nicolas on 16/03/17.
//

#ifndef PANCAKE_LASERBUTTON_HPP
#define PANCAKE_LASERBUTTON_HPP


#include <GameLogic/GameObject.hpp>
#include <User/Behaviors/LaserButtonScript.hpp>

class LaserButton : public PancakeEngine::GameObject {
public:
    LaserButton() {
        name = "LaserButton";
        addComponent<LaserButtonScript>();
        PancakeEngine::BoxCollider& bc = addComponent<PancakeEngine::BoxCollider>();
        bc.width = 70;
        bc.height = 70;
        bc.isTrigger = true;
        addComponent<PancakeEngine::SpriteRenderer>().setSprite(
                PancakeEngine::AssetsManager::getSpriteSheet("miscs"),
                3, 6
        );
    }
};


#endif //PANCAKE_LASERBUTTON_HPP
