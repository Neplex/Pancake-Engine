//
// Created by kelle on 02/02/2017.
//

#ifndef PANCAKE_PLAYERCONTROLLER_HPP
#define PANCAKE_PLAYERCONTROLLER_HPP


#include "GameLogic.hpp"
#include "Inputs.hpp"

class PlayerController : public PancakeEngine::Behavior {
public:
    bool climbing = false;
    bool swiming = false;
    PancakeEngine::Collider* topCollider;

    void update() {
        topCollider->setSleep(false);
        float velocityXDesired = 0;
        float velocityYDesired = 0;
        PancakeEngine::Rigidbody* rb = gameObject->getComponent<PancakeEngine::Rigidbody>();
        if (PancakeEngine::Input::getButtonHeld(gameObject->name + "_jump")) {
            if (climbing || swiming) {
                velocityYDesired = -5;
            }
        }
        if (rb->getVelocity().y < 0.1 && rb->getVelocity().y > -0.1 && PancakeEngine::Input::getButtonPressed(gameObject->name + "_jump")) {
            gameObject->getComponent<PancakeEngine::Rigidbody>()->applyLinearImpulse(sf::Vector2f(0, -11));
        }
        if (PancakeEngine::Input::getButtonHeld(gameObject->name + "_duck")) {
            velocityYDesired = 5;
            if (! climbing && ! swiming) {
                topCollider->setSleep(true);
            }
        }
        if (PancakeEngine::Input::getButtonHeld(gameObject->name + "_right")) {
            velocityXDesired = 5;
        }
        if (PancakeEngine::Input::getButtonHeld(gameObject->name + "_left")) {
            velocityXDesired = -5;
        }
        float velYChange = velocityYDesired - rb->getVelocity().y;
        float velXChange = velocityXDesired - rb->getVelocity().x;
        float impulseY = rb->getMass() * velYChange;
        float impulseX = rb->getMass() * velXChange; //disregard time factor
        rb->applyLinearImpulse(sf::Vector2f(impulseX,0));
        if (climbing || swiming) {
            rb->applyLinearImpulse(sf::Vector2f(0,impulseY));
        }
    }
};


#endif //PANCAKE_PLAYERCONTROLLER_HPP
