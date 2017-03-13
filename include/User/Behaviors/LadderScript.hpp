//
// Created by Darenn on 13/03/2017.
//

#ifndef PANCAKE_LADDERSCRIPT_HPP
#define PANCAKE_LADDERSCRIPT_HPP

#include <GameLogic.hpp>
#include <cmath>
#include "PlayerController.hpp"

namespace PancakeEngine {

    class LadderScript : public Behavior {
    public:
        float maxSpeed = 5;

        void OnTriggerEnter(const Collider &triggered, const Collider &other) override {
            PlayerController* pc =  other.gameObject->getComponent<PlayerController>();
            Rigidbody* rb = other.gameObject->getComponent<Rigidbody>();
            if (rb != nullptr && pc != nullptr) {
                rb->setVelocity(sf::Vector2f(0, 0));
                rb->setGravityScale(0);
                climbers.push_back(rb);
                pc->climbing = true;
            }
        }

        void update() override {
            for(int i = 0; i < climbers.size(); i++) {
                if (std::abs(climbers[i]->getVelocity().x) > maxSpeed) {
                    if (climbers[i]->getVelocity().x < 0) {
                        climbers[i]->setVelocity(sf::Vector2f(-maxSpeed, climbers[i]->getVelocity().y));
                    }
                }
                if (std::abs(climbers[i]->getVelocity().y) > maxSpeed) {
                    if (climbers[i]->getVelocity().y < 0) {
                        climbers[i]->setVelocity(sf::Vector2f(climbers[i]->getVelocity().x, -maxSpeed));
                    }
                }
            }
        }

        //TODO careful, maybe the base gravityScale was'nt 1, make a map to remember.

        void OnTriggerExit(const Collider &triggered, const Collider &other) override {
            PlayerController* pc =  other.gameObject->getComponent<PlayerController>();
            Rigidbody* rb = other.gameObject->getComponent<Rigidbody>();
            if (rb != nullptr && pc != nullptr) {
                rb->setGravityScale(1);
                pc->climbing = false;
                for(int i = 0; i < climbers.size(); i++) {
                    if (climbers[i] == rb) {
                        climbers.erase(climbers.begin() + i);
                    }
                }
            }
        }
    private:
        std::vector<Rigidbody*> climbers;
    };
}

#endif //PANCAKE_LADDERSCRIPT_HPP
