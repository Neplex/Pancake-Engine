//
// Created by nicolas on 15/02/17.
//

#ifndef PANCAKE_PLAYER_HPP
#define PANCAKE_PLAYER_HPP

#include <GameLogic.hpp>
#include <User/Behaviors/PlayerController.hpp>

#define ANIMATION_SPEED 75

namespace PancakeEngine {
    class Player : public GameObject {
        static std::string handler(GameObject& go) {
            sf::Vector2f velocity = go.getComponent<Rigidbody>()->getVelocity();
            Animator* ar = go.getComponent<Animator>();

            if (velocity.x > .1) {
                ar->flip(false);
            } else if (velocity.x < -.1){
                ar->flip(true);
            }

            if (Input::getButtonHeld("Duck")) {
                return "duck";
            } else if (velocity.y < -.1 || velocity.y > .1) {
                return "jump";
            } else if (velocity.x < -.1 || velocity.x > .1) {
                return "walk";
            }
            return "idle";
        }
    public:
        Player () : GameObject() {
            name = "Player";

            addComponent<Rigidbody>().setFreezeRotation(true);
            // TODO: Add "capsule" collider
            CircleCollider& cl_top = addComponent<CircleCollider>();
            CircleCollider& cl_bottom = addComponent<CircleCollider>();
            cl_top.radius = cl_bottom.radius = 35;
            cl_top.offset = sf::Vector2f(0, -13);
            cl_bottom.offset = sf::Vector2f(0, 13);

            addComponent<LuaScript>().setScript("../resources/scripts/PlayerController.lua");
            addComponent<Camera>();

            SpriteSheet& sprites = AssetsManager::createSpriteSheet("player1", "../resources/player/player1.png", 73, 94);

            Animation& a_duck = AssetsManager::createAnimation("player_duck", sprites);
            a_duck.addFrame(0, 0, ANIMATION_SPEED);
            Animation& a_idle = AssetsManager::createAnimation("player_idle", sprites);
            a_idle.addFrame(1, 0, ANIMATION_SPEED);
            Animation& a_jump = AssetsManager::createAnimation("player_jump", sprites);
            a_jump.addFrame(2, 0, ANIMATION_SPEED);
            Animation& a_hurt = AssetsManager::createAnimation("player_hurt", sprites);
            a_hurt.addFrame(3, 0, ANIMATION_SPEED);
            Animation& a_walk = AssetsManager::createAnimation("player_walk", sprites);
            a_walk.addFrame(0, 1, ANIMATION_SPEED);
            a_walk.addFrame(1, 1, ANIMATION_SPEED);
            a_walk.addFrame(2, 1, ANIMATION_SPEED);
            a_walk.addFrame(3, 1, ANIMATION_SPEED);
            a_walk.addFrame(0, 2, ANIMATION_SPEED);
            a_walk.addFrame(1, 2, ANIMATION_SPEED);
            a_walk.addFrame(2, 2, ANIMATION_SPEED);
            a_walk.addFrame(3, 2, ANIMATION_SPEED);
            a_walk.addFrame(0, 3, ANIMATION_SPEED);
            a_walk.addFrame(1, 3, ANIMATION_SPEED);
            a_walk.addFrame(2, 3, ANIMATION_SPEED);
            Animation& a_front = AssetsManager::createAnimation("player_front", sprites);
            a_front.addFrame(3, 3, ANIMATION_SPEED);

            Animator& ar = addComponent<Animator>();
            ar.addAnimation("idle", a_idle, handler);
            ar.addAnimation("walk", a_walk, handler);
            ar.addAnimation("jump", a_jump, handler);
            ar.addAnimation("hurt", a_hurt, handler);
            ar.addAnimation("duck", a_duck, handler);
            ar.addAnimation("front", a_front, handler);
        }
    };
}

#endif //PANCAKE_PLAYER_HPP
