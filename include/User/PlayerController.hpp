//
// Created by kelle on 02/02/2017.
//

#ifndef PANCAKE_PLAYERCONTROLLER_HPP
#define PANCAKE_PLAYERCONTROLLER_HPP


#include "../GameLogic/Components/Component.hpp"
#include "../Inputs/Input.hpp"
#include "../GameLogic/Components/Rigidbody.hpp"
#include "../GameLogic/GameObject.hpp"

class PlayerController : public PancakeEngine::Behavior {
public:
    void OnCollisionEnter(const PancakeEngine::Collision &collision) override {
        PancakeEngine::Debug::log("Foo", "The player collides something !");
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

        float velocityDesired = 0;
        PancakeEngine::Rigidbody* rb = gameObject->getComponent<PancakeEngine::Rigidbody>();
        if (PancakeEngine::Input::getButtonPressed("Jump") && rb->getVelocity().y == 0) {
            gameObject->getComponent<PancakeEngine::Rigidbody>()->applyLinearImpulse(sf::Vector2f(0, -5));;
        }
        if (PancakeEngine::Input::getButtonHeld("Right")) {
            velocityDesired = 5;
        }
        if (PancakeEngine::Input::getButtonHeld("Left")) {
            velocityDesired = -5;
        }

        float velChange = velocityDesired - rb->getVelocity().x;
        float impulse = rb->getMass() * velChange; //disregard time factor
        rb->applyLinearImpulse(sf::Vector2f(impulse,0));
    }
};


#endif //PANCAKE_PLAYERCONTROLLER_HPP
