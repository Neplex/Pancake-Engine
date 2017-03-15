//
// Created by Darenn on 15/03/2017.
//

#ifndef PANCAKE_CHECKPOINTOBJECT_HPP
#define PANCAKE_CHECKPOINTOBJECT_HPP

#include <GameLogic.hpp>
#include <User/Behaviors/CheckPoint.hpp>

class CheckPointObject : public PancakeEngine::GameObject {
public:
    CheckPointObject(std::string n) {
        name = n;
        addComponent<CheckPoint>();
        PancakeEngine::BoxCollider& bc = addComponent<PancakeEngine::BoxCollider>();
        bc.width = 60;
        bc.height = 70;
        bc.isTrigger = true;
    }
};
class CheckPointObject1 : public CheckPointObject { public: CheckPointObject1() : CheckPointObject("CheckPoint1") {addComponent<PancakeEngine::SpriteRenderer>().setSprite(
                PancakeEngine::AssetsManager::getSpriteSheet("items"), 7, 2);
    }
};
class CheckPointObject2 : public CheckPointObject { public: CheckPointObject2() : CheckPointObject("CheckPoint2") {addComponent<PancakeEngine::SpriteRenderer>().setSprite(
                PancakeEngine::AssetsManager::getSpriteSheet("items"), 7, 1
        );} };
class CheckPointObject3 : public CheckPointObject { public: CheckPointObject3() : CheckPointObject("CheckPoint3") {addComponent<PancakeEngine::SpriteRenderer>().setSprite(
                PancakeEngine::AssetsManager::getSpriteSheet("items"), 7, 3
        );} };
class CheckPointObject4 : public CheckPointObject { public: CheckPointObject4() : CheckPointObject("CheckPoint4") {addComponent<PancakeEngine::SpriteRenderer>().setSprite(
                PancakeEngine::AssetsManager::getSpriteSheet("items"), 7, 4
        );} };
#endif //PANCAKE_CHECKPOINTOBJECT_HPP
