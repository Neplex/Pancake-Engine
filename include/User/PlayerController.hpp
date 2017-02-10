//
// Created by kelle on 02/02/2017.
//

#ifndef PANCAKE_PLAYERCONTROLLER_HPP
#define PANCAKE_PLAYERCONTROLLER_HPP


#include "../Inputs/Input.hpp"
#include "../GameLogic/Components/Rigidbody.hpp"
#include "../GameLogic/GameObject.hpp"

class PlayerController : public PancakeEngine::Behavior {
public:
    void OnCollisionEnter(const PancakeEngine::Collision &collision) override {
        PancakeEngine::Debug::log("Foo", "The player collides something !");
        //destroy(*collision.otherCollider.gameObject);
    }

    void OnCollisionExit(const PancakeEngine::Collision &collision) override {
        PancakeEngine::Debug::log("Foo", "The player exit collides something !");
    }

    void OnTriggerEnter(const PancakeEngine::Collider& triggered, const PancakeEngine::Collider& other) override {
        PancakeEngine::Debug::log("Foo", "The player triggers something !");
    }

    void OnTriggerExit(const PancakeEngine::Collider &triggered, const PancakeEngine::Collider &other) override {
        PancakeEngine::Debug::log("Foo", "The player exit trigger !");
    }


    void update() {
        if (PancakeEngine::Input::getButtonPressed("Jump")) {
            gameObject->getComponent<PancakeEngine::Rigidbody>()->applyLinearImpulse(sf::Vector2f(0, -5));;
        }
        if (PancakeEngine::Input::getButtonPressed("Right")) {
            gameObject->getComponent<PancakeEngine::Rigidbody>()->applyLinearImpulse(sf::Vector2f(5,0));
        }
        if (PancakeEngine::Input::getButtonPressed("Left")) {
            gameObject->getComponent<PancakeEngine::Rigidbody>()->applyLinearImpulse(sf::Vector2f(-5  ,0));
        }
    }
    void awake() {
        gameObject->getComponent<PancakeEngine::Rigidbody>()->setFreezeRotation(true);
    }
};


#endif //PANCAKE_PLAYERCONTROLLER_HPP
