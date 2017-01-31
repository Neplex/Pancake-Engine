//
// Created by kelle on 26/01/2017.
//

#ifndef PANCAKE_BOX_HPP
#define PANCAKE_BOX_HPP

#include "../GameLogic/GameObject.hpp"
#include "../Graphics/SpriteSheet.hpp"
#include "../Graphics/Animation.hpp"
#include "../GameLogic/Components/AnimationRenderer.hpp"
#include "../GameLogic/Components/BoxCollider.hpp"
#include <string>
// TODO should not inclue that in the name space
namespace PancakeEngine {
    class Box : public GameObject {

    public:
        Box(std::string name)
                :GameObject(name)
        {
               //AnimationRenderer& ar = addComponent<AnimationRenderer>();
                BoxCollider& bc = addComponent<BoxCollider>();
                Rigidbody& rb = addComponent<Rigidbody>();
                //SpriteSheet* ss = new SpriteSheet("../resources/tiles_spritesheet.png", 72, 72);
                //Animation* a = new Animation(*ss);
                /*a->addFrame(0, 3, 200);
                a->addFrame(0, 4, 200);
                a->addFrame(0, 5, 200);*/
                //ar.play();
                bc.width = 72;
                bc.height = 72;
                transform.setPosition(sf::Vector2f(100, -100));
                transform.setRotation(0);
        }
    };
}
#endif //PANCAKE_BOX_HPP
