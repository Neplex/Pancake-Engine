//
// Created by kelle on 26/01/2017.
//

#ifndef PANCAKE_BOX_HPP
#define PANCAKE_BOX_HPP

#include <GameLogic.hpp>
#include <Graphics.hpp>

namespace PancakeEngine {

    class Box : public GameObject {
    public:
        Box() :GameObject() {
            name = "Box";

            Rigidbody& rb = addComponent<Rigidbody>();
            //rb.setFreezeRotation(true);
            BoxCollider& bc = addComponent<BoxCollider>();
            bc.width = 70;
            bc.height = 70;
            bc.density = 15;
            transform.setPosition(sf::Vector2f(100, -100));
            transform.setRotation(0);

            addComponent<SpriteRenderer>().setSprite(
                    AssetsManager::getSpriteSheet("tiles"), 0, 1
            );
        }
    };
}
#endif //PANCAKE_BOX_HPP
