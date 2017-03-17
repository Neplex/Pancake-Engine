//
// Created by nicolas on 16/03/17.
//

#ifndef PANCAKE_LASERBUTTONSCRIPT_HPP
#define PANCAKE_LASERBUTTONSCRIPT_HPP


#include <GameLogic/Components/Behavior.hpp>
#include <SceneManager.hpp>
#include <GameLogic/Components/SpriteRenderer.hpp>
#include <Graphics/AssetsManager.hpp>

class LaserButtonScript : public PancakeEngine::Behavior {
public:
    PancakeEngine::GameObject* laser;
    bool active = false;

    void start() override {
        laser = PancakeEngine::SceneManager::findByName("Laser");
    }

    void OnTriggerEnter(const PancakeEngine::Collider &triggered, const PancakeEngine::Collider &other) override {
        if (!active && other.gameObject->name == "player1") {
            gameObject->getComponent<PancakeEngine::SpriteRenderer>()->setSprite(
                    PancakeEngine::AssetsManager::getSpriteSheet("miscs"),
                    2, 6
            );
            active = true;
            destroy(*laser);
        }
    }
};


#endif //PANCAKE_LASERBUTTONSCRIPT_HPP
