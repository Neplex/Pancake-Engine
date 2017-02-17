//
// Created by kelle on 26/01/2017.
//

#ifndef PANCAKE_GROUND_HPP
#define PANCAKE_GROUND_HPP

#include "../GameLogic/GameObject.hpp"
#include "../GameLogic/Components/BoxCollider.hpp"

#define SIZE 70
#define WIDTH 61

namespace PancakeEngine {
    class Ground : public GameObject {
    public:
        Ground() : GameObject() {
            name = "Ground";

            BoxCollider& bcGroundingBox = addComponent<BoxCollider>();
            bcGroundingBox.height = SIZE;
            bcGroundingBox.width = SIZE * WIDTH;

            SpriteSheet& sheet = AssetsManager::getSpriteSheet("tiles");

            for (int i = -WIDTH/2; i < WIDTH/2; ++i) {
                SpriteRenderer& sr = addComponent<SpriteRenderer>();
                sr.setSprite(sheet, 7, 8);
                sr.setPosition(sf::Vector2f(i*SIZE, 0));
            }
        }

    };
}

#endif //PANCAKE_GROUND_HPP
