//
// Created by kelle on 26/01/2017.
//

#ifndef PANCAKE_BOX_HPP
#define PANCAKE_BOX_HPP

#include <GameLogic.hpp>
#include <Graphics.hpp>


    class Box : public PancakeEngine::GameObject {
    public:
        Box() : PancakeEngine::GameObject() {
            name = "Box";

            PancakeEngine::Rigidbody& rb = addComponent<PancakeEngine::Rigidbody>();
            //rb.setFreezeRotation(true);
            PancakeEngine::BoxCollider& bc = addComponent<PancakeEngine::BoxCollider>();
            bc.width = 70;
            bc.height = 70;
            bc.density = 15;
            transform.setPosition(sf::Vector2f(100, -100));
            transform.setRotation(0);

            addComponent<PancakeEngine::SpriteRenderer>().setSprite(
                    PancakeEngine::AssetsManager::getSpriteSheet("tiles"), 0, 1
            );
        }
    };
#endif //PANCAKE_BOX_HPP
