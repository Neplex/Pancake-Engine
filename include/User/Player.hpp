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
            addComponent<Rigidbody>();
            addComponent<PlayerController>();
            addComponent<Camera>().zoom(1.2f);

           /* LuaScript& lua = addComponent<LuaScript>();
            lua.setScript("../resources/scripts/test.lua");*/
        }
        void setAnimation(){
            Animation &a = AssetsManager::createAnimation("PlayerAnimation", "Player");
            a.addFrame(0, 0, 100);
            a.addFrame(0, 2, 100);
            a.addFrame(0, 1, 100);
            a.addFrame(0, 0, 100);
            a.addFrame(0, 1, 100);

            AnimationRenderer &ar = addComponent<AnimationRenderer>();
            ar.setAnimation(a);
            ar.start();
            ar.loop();
            ar.play();
        };
    };
}
#endif //PANCAKE_PLAYER_HPP
