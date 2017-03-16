//
// Created by Darenn on 15/03/2017.
//

#ifndef PANCAKE_BULLETOBJECT_HPP
#define PANCAKE_BULLETOBJECT_HPP

#include <GameLogic.hpp>
#include <User/Behaviors/Bullet.hpp>

class BulletObject : public PancakeEngine::GameObject {
public:
    BulletObject() { addComponent<PancakeEngine::Rigidbody>(); // todo problem if put after colliders
        PancakeEngine::CircleCollider& cc = addComponent<PancakeEngine::CircleCollider>();
        cc.radius = 4;
        cc.isTrigger = true;

        addComponent<Bullet>();
        addComponent<PancakeEngine::SpriteRenderer>().setSprite(
                PancakeEngine::AssetsManager::getSpriteSheet("miscs"), 7, 0
        );
    }
};

#endif //PANCAKE_BULLETOBJECT_HPP
