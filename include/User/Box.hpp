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
#include "../GameLogic/Components/Animator.hpp"
#include "../Inputs/Input.hpp"
#include "../GameLogic/Components/Camera.hpp"
#include "../Graphics/AssetsManager.hpp"
#include "../GameLogic/Components/SpriteRenderer.hpp"
#include "PlayerController.hpp"
#include "../GameLogic/Components/LuaScript.hpp"
#include <string>

namespace PancakeEngine {
    std::string sh1() {
        if (Input::getButtonPressed("S1")) return "jump";
        else return "idle";
    };

    std::string sh2() {
        if (Input::getButtonPressed("S2")) return "idle";
        else return "jump";
    };

    class Box : public GameObject {

    public:
        Box() :GameObject() {
            name = "Box";

            addComponent<Rigidbody>();
            BoxCollider& bc = addComponent<BoxCollider>();
            bc.width = 72;
            bc.height = 72;
            transform.setPosition(sf::Vector2f(100, -100));
            transform.setRotation(0);

            AssetsManager::createSpriteSheet("sprites", "../resources/tiles_spritesheet.png", 72, 72);
            Animation& a1 = AssetsManager::createAnimation("a1", "sprites");
            a1.addFrame(0, 9, 200);
            a1.addFrame(0, 10, 200);
            Animation& a2 = AssetsManager::createAnimation("a2", "sprites");
            a2.addFrame(0, 1, 200);
            a2.addFrame(0, 2, 200);
            Animator& ar = addComponent<Animator>();
            ar.addAnimation("idle", a1, sh1);
            ar.addAnimation("jump", a2, sh2);

            addComponent<SpriteRenderer>();
        }
    };
}
#endif //PANCAKE_BOX_HPP
