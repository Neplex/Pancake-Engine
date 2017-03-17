//
// Created by Darenn on 15/03/2017.
//

#ifndef PANCAKE_CHECKPOINTOBJECT_HPP
#define PANCAKE_CHECKPOINTOBJECT_HPP

#include <GameLogic.hpp>
#include <User/Behaviors/CheckPointScript.hpp>

class CheckPoint : public PancakeEngine::GameObject {
public:
    CheckPoint(std::string n) {
        name = n;
        addComponent<CheckPointScript>();
        PancakeEngine::BoxCollider& bc = addComponent<PancakeEngine::BoxCollider>();
        bc.width = 60;
        bc.height = 70;
        bc.isTrigger = true;
    }
};
class CheckPoint1 : public CheckPoint { public: CheckPoint1() : CheckPoint("CheckPoint1") {addComponent<PancakeEngine::SpriteRenderer>().setSprite(
                PancakeEngine::AssetsManager::getSpriteSheet("items"), 7, 2);
    }
};
class CheckPoint2 : public CheckPoint { public: CheckPoint2() : CheckPoint("CheckPoint2") {addComponent<PancakeEngine::SpriteRenderer>().setSprite(
                PancakeEngine::AssetsManager::getSpriteSheet("items"), 7, 1
        );} };
class CheckPoint3 : public CheckPoint { public: CheckPoint3() : CheckPoint("CheckPoint3") {addComponent<PancakeEngine::SpriteRenderer>().setSprite(
                PancakeEngine::AssetsManager::getSpriteSheet("items"), 7, 3
        );} };
class CheckPoint4 : public CheckPoint { public: CheckPoint4() : CheckPoint("CheckPoint4") {addComponent<PancakeEngine::SpriteRenderer>().setSprite(
                PancakeEngine::AssetsManager::getSpriteSheet("items"), 7, 4
        );} };
#endif //PANCAKE_CHECKPOINTOBJECT_HPP
