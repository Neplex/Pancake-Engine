//
// Created by nicolas on 15/02/17.
//

#ifndef PANCAKE_PLAYER_HPP
#define PANCAKE_PLAYER_HPP

#include <GameLogic.hpp>
#include <Graphics.hpp>
#include <User/Behaviors/PlayerController.hpp>

#define ANIMATION_SPEED 150

namespace PancakeEngine {
    class Player : public GameObject {
        friend class Player1;
        friend class Player2;
        friend class Player3;
        friend class Player4;
        friend class Player5;

        static std::string handler(GameObject& go) {
            sf::Vector2f velocity = go.getComponent<Rigidbody>()->getVelocity();
            Animator* ar = go.getComponent<Animator>();

            if (velocity.x > .1) {
                ar->flip(false);
            } else if (velocity.x < -.1){
                ar->flip(true);
            }

            if (Input::getButtonHeld(go.name + "_duck")) {
                return "duck";
            } else if (velocity.y < -.1 || velocity.y > .1) {
                return "jump";
            } else if (velocity.x < -.1 || velocity.x > .1) {
                return "walk";
            }
            return "idle";
        }

        Player (std::string n) : GameObject() {
            name = n;

            addComponent<Rigidbody>().setFreezeRotation(true);
            // TODO: Add "capsule" collider
            CircleCollider& cl_top = addComponent<CircleCollider>();
            CircleCollider& cl_bottom = addComponent<CircleCollider>();
            cl_top.radius = cl_bottom.radius = 35;
            cl_top.offset = sf::Vector2f(0, -13);
            cl_bottom.offset = sf::Vector2f(0, 13);

            addComponent<PlayerController>();
           // addComponent<LuaScript>().setScript("../resources/scripts/PlayerController.lua");
            addComponent<Camera>().setBackground("../resources/backgrounds/bg_grasslands.png");

            SpriteSheet& sprites = AssetsManager::getSpriteSheet(name);

            Animation& a_idle = AssetsManager::createAnimation(name + "r_idle", sprites);
            a_idle.addFrame(0, 0, ANIMATION_SPEED);
            Animation& a_duck = AssetsManager::createAnimation(name + "_duck", sprites);
            a_duck.addFrame(1, 0, ANIMATION_SPEED);
            Animation& a_jump = AssetsManager::createAnimation(name + "_jump", sprites);
            a_jump.addFrame(2, 0, ANIMATION_SPEED);
            Animation& a_hurt = AssetsManager::createAnimation(name + "_hurt", sprites);
            a_hurt.addFrame(3, 0, ANIMATION_SPEED);
            Animation& a_walk = AssetsManager::createAnimation(name + "_walk", sprites);
            a_walk.addFrame(0, 1, ANIMATION_SPEED);
            a_walk.addFrame(0, 2, ANIMATION_SPEED);
            Animation& a_swing = AssetsManager::createAnimation(name + "_swing", sprites);
            a_swing.addFrame(1, 1, ANIMATION_SPEED);
            a_swing.addFrame(1, 2, ANIMATION_SPEED);
            Animation& a_climb = AssetsManager::createAnimation(name + "_climb", sprites);
            a_climb.addFrame(2, 1, ANIMATION_SPEED);
            a_climb.addFrame(2, 2, ANIMATION_SPEED);
            Animation& a_front = AssetsManager::createAnimation(name + "_front", sprites);
            a_front.addFrame(3, 1, ANIMATION_SPEED);

            Animator& ar = addComponent<Animator>();
            ar.addAnimation("idle", a_idle, handler);
            ar.addAnimation("duck", a_duck, handler);
            ar.addAnimation("jump", a_jump, handler);
            ar.addAnimation("hurt", a_hurt, handler);
            ar.addAnimation("walk", a_walk, handler);
            ar.addAnimation("swing", a_walk, handler);
            ar.addAnimation("climb", a_walk, handler);
            ar.addAnimation("front", a_front, handler);
        }
    };

    class Player1 : public Player { public: Player1() : Player("player1") {} };
    class Player2 : public Player { public: Player2() : Player("player2") {} };
    class Player3 : public Player { public: Player3() : Player("player3") {} };
    class Player4 : public Player { public: Player4() : Player("player4") {} };
    class Player5 : public Player { public: Player5() : Player("player5") {} };
}

#endif //PANCAKE_PLAYER_HPP
