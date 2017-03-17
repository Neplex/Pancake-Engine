//
// Created by nicolas on 15/02/17.
//

#ifndef PANCAKE_PLAYER_HPP
#define PANCAKE_PLAYER_HPP

#include <GameLogic.hpp>
#include <Graphics.hpp>
#include <User/Behaviors/PlayerController.hpp>
#include <User/Behaviors/PlayerScript.hpp>
#include "Health.hpp"

#define Animation_SPEED 150

    class Player : public PancakeEngine::GameObject {
        friend class Player1;
        friend class Player2;
        friend class Player3;
        friend class Player4;
        friend class Player5;

        static std::string handler(PancakeEngine::GameObject& go) {
            sf::Vector2f velocity = go.getComponent<PancakeEngine::Rigidbody>()->getVelocity();
            PancakeEngine::Animator* ar = go.getComponent<PancakeEngine::Animator>();

            if (velocity.x > .1) {
                ar->flip(false);
            } else if (velocity.x < -.1){
                ar->flip(true);
            }

            if (go.getComponent<PlayerController>()->climbing) {
                return "climb";
            } else if (go.getComponent<PlayerController>()->swiming) {
                return "swing";
            } else if (PancakeEngine::Input::getButtonHeld(go.name + "_duck")) {
                return "duck";
            } else if (velocity.y < -.1 || velocity.y > .1) {
                return "jump";
            } else if (velocity.x < -.1 || velocity.x > .1) {
                return "walk";
            }
            return "idle";
        }

        Player (std::string n) : PancakeEngine::GameObject() {
            name = n;
            addComponent<Health>();
            addComponent<PancakeEngine::Rigidbody>().setFreezeRotation(true);
            // TODO: Add "capsule" collider
            PancakeEngine::CircleCollider& cl_top = addComponent<PancakeEngine::CircleCollider>();
            PancakeEngine::CircleCollider& cl_bottom = addComponent<PancakeEngine::CircleCollider>();
            cl_top.radius = cl_bottom.radius = 35;
            cl_top.offset = sf::Vector2f(0, -13);
            cl_bottom.offset = sf::Vector2f(0, 13);

            PlayerController& pc = addComponent<PlayerController>();
            pc.topCollider = &cl_top;
            cl_top.friction = 0;
            cl_bottom.friction = 0;
            addComponent<PlayerScript>();
           // addComponent<LuaScript>().setScript("../resources/scripts/PlayerController.lua");
            addComponent<PancakeEngine::Camera>().setBackground("../resources/backgrounds/bg_grasslands.png");

PancakeEngine::SpriteSheet& sprites = PancakeEngine::AssetsManager::getSpriteSheet(name);

            PancakeEngine::Animation& a_idle = PancakeEngine::AssetsManager::createAnimation(name + "r_idle", sprites);
            a_idle.addFrame(0, 0, Animation_SPEED);
            PancakeEngine::Animation& a_duck = PancakeEngine::AssetsManager::createAnimation(name + "_duck", sprites);
            a_duck.addFrame(1, 0, Animation_SPEED);
            PancakeEngine::Animation& a_jump = PancakeEngine::AssetsManager::createAnimation(name + "_jump", sprites);
            a_jump.addFrame(2, 0, Animation_SPEED);
            PancakeEngine::Animation& a_hurt = PancakeEngine::AssetsManager::createAnimation(name + "_hurt", sprites);
            a_hurt.addFrame(3, 0, Animation_SPEED);
            PancakeEngine::Animation& a_walk = PancakeEngine::AssetsManager::createAnimation(name + "_walk", sprites);
            a_walk.addFrame(0, 1, Animation_SPEED);
            a_walk.addFrame(0, 2, Animation_SPEED);
            PancakeEngine::Animation& a_swing = PancakeEngine::AssetsManager::createAnimation(name + "_swing", sprites);
            a_swing.addFrame(1, 1, Animation_SPEED*2);
            a_swing.addFrame(1, 2, Animation_SPEED*2);
            PancakeEngine::Animation& a_climb = PancakeEngine::AssetsManager::createAnimation(name + "_climb", sprites);
            a_climb.addFrame(2, 1, Animation_SPEED*2);
            a_climb.addFrame(2, 2, Animation_SPEED*2);
            PancakeEngine::Animation& a_front = PancakeEngine::AssetsManager::createAnimation(name + "_front", sprites);
            a_front.addFrame(3, 1, Animation_SPEED);

            PancakeEngine::Animator& ar = addComponent<PancakeEngine::Animator>();
            ar.addAnimation("idle", a_idle, handler);
            ar.addAnimation("duck", a_duck, handler);
            ar.addAnimation("jump", a_jump, handler);
            ar.addAnimation("hurt", a_hurt, handler);
            ar.addAnimation("walk", a_walk, handler);
            ar.addAnimation("swing", a_swing, handler);
            ar.addAnimation("climb", a_climb, handler);
            ar.addAnimation("front", a_front, handler);
        }
    };

    class Player1 : public Player { public: Player1() : Player("player1") {} };
    class Player2 : public Player { public: Player2() : Player("player2") {} };
    class Player3 : public Player { public: Player3() : Player("player3") {} };
    class Player4 : public Player { public: Player4() : Player("player4") {} };
    class Player5 : public Player { public: Player5() : Player("player5") {} };


#endif //PANCAKE_PLAYER_HPP
