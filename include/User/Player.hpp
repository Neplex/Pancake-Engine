//
// Created by virgil on 08/02/17.
//

#ifndef PANCAKE_PLAYER_HPP
#define PANCAKE_PLAYER_HPP

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
    class Player : public GameObject {
    public:
        Player() :GameObject() {
            name = "Player";

            BoxCollider& bc = addComponent<BoxCollider>();
            addComponent<Rigidbody>();
            addComponent<PlayerController>();
            addComponent<Camera>().zoom(1.2f);
            bc.width = 72;
            bc.height = 72;
            transform.setPosition(sf::Vector2f(100, -100));
            transform.setRotation(0);

            /*AssetsManager::createSpriteSheet("sprites", "../resources/tiles_spritesheet.png", 72, 72);
            Animation& a1 = AssetsManager::createAnimation("a1", "sprites");
            a1.addFrame(0, 9, 200);
            a1.addFrame(0, 10, 200);
            Animation& a2 = AssetsManager::createAnimation("a2", "sprites");
            a2.addFrame(0, 1, 200);
            a2.addFrame(0, 2, 200);
            Animator& ar = addComponent<Animator>();
            ar.addAnimation("idle", a1, sh1);
            ar.addAnimation("jump", a2, sh2);*/

            //addComponent<SpriteRenderer>();

           /* LuaScript& lua = addComponent<LuaScript>();
            lua.setScript("../resources/scripts/test.lua");*/
        }
    };
}
#endif //PANCAKE_PLAYER_HPP
