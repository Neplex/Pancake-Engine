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
#include "User/Behaviors/PlayerController.hpp"
#include "../GameLogic/Components/LuaScript.hpp"
#include <string>

namespace PancakeEngine {

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

            SpriteSheet& s = AssetsManager::createSpriteSheet("sprites", "../resources/tiles_spritesheet.png", 72, 72);

            addComponent<SpriteRenderer>().setSprite(s, 0, 9);
        }
    };
}
#endif //PANCAKE_BOX_HPP
