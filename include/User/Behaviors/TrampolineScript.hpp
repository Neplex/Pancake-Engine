//
// Created by virgil on 14/03/17.
//

#ifndef PANCAKE_TRAMPOLINESCRIPT_HPP
#define PANCAKE_TRAMPOLINESCRIPT_HPP

#include <GameLogic.hpp>
namespace PancakeEngine {

    class TrampolineScript : public Behavior {
    public:
        void OnCollisionEnter(const Collision& collision) override{
            SpriteSheet& ss = AssetsManager::getSpriteSheet("items");
            gameObject->getComponent<SpriteRenderer>()->setSprite(ss,0,5);
        };
        void OnCollisionExit(const Collision& collision) override {
            SpriteSheet& ss = AssetsManager::getSpriteSheet("items");
            gameObject->getComponent<SpriteRenderer>()->setSprite(ss,0,6);
        };
    };
}
#endif //PANCAKE_TRAMPOLINESCRIPT_HPP
