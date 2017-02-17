//
// Created by kelle on 02/02/2017.
//

#ifndef PANCAKE_PLAYERCONTROLLER_HPP
#define PANCAKE_PLAYERCONTROLLER_HPP


#include "GameLogic.hpp"
#include "Inputs.hpp"

class PlayerController : public PancakeEngine::Behavior {
public:
    void update() {

        float velocityDesired = 0;
        PancakeEngine::Rigidbody* rb = gameObject->getComponent<PancakeEngine::Rigidbody>();
        if (PancakeEngine::Input::getButtonPressed(gameObject->name + "_jump") && rb->getVelocity().y < 0.1 && rb->getVelocity().y > -0.1) {
            gameObject->getComponent<PancakeEngine::Rigidbody>()->applyLinearImpulse(sf::Vector2f(0, -7));
        }
        if (PancakeEngine::Input::getButtonHeld(gameObject->name + "_right")) {
            velocityDesired = 5;
        }
        if (PancakeEngine::Input::getButtonHeld(gameObject->name + "_left")) {
            velocityDesired = -5;
        }

        float velChange = velocityDesired - rb->getVelocity().x;
        float impulse = rb->getMass() * velChange; //disregard time factor
        rb->applyLinearImpulse(sf::Vector2f(impulse,0));
    }
};


#endif //PANCAKE_PLAYERCONTROLLER_HPP
