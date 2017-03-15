//
// Created by nicolas on 14/03/17.
//

#ifndef PANCAKE_WATERSCRIPT_HPP
#define PANCAKE_WATERSCRIPT_HPP

#include <GameLogic/Components/Rigidbody.hpp>
#include <GameLogic/Components/Collider.hpp>
#include "PlayerController.hpp"

namespace PancakeEngine {
    class WaterScript : public Behavior {
    public:
        float maxSpeed = 5;

        void OnTriggerEnter(const Collider &triggered, const Collider &other) override {
            PlayerController* pc =  other.gameObject->getComponent<PlayerController>();
            Rigidbody* rb = other.gameObject->getComponent<Rigidbody>();
            if (rb != nullptr && pc != nullptr) {
                rb->setVelocity(sf::Vector2f(0, 0));
                rb->setGravityScale(0);
                swimers.push_back(rb);
                pc->swiming = true;
            }
        }

        void update() override {
            for(int i = 0; i < swimers.size(); i++) {
                if (std::abs(swimers[i]->getVelocity().x) > maxSpeed) {
                    if (swimers[i]->getVelocity().x < 0) {
                        swimers[i]->setVelocity(sf::Vector2f(-maxSpeed, swimers[i]->getVelocity().y));
                    }
                }
                if (std::abs(swimers[i]->getVelocity().y) > maxSpeed) {
                    if (swimers[i]->getVelocity().y < 0) {
                        swimers[i]->setVelocity(sf::Vector2f(swimers[i]->getVelocity().x, -maxSpeed));
                    }
                }
            }
        }

        void OnTriggerExit(const Collider &triggered, const Collider &other) override {
            PlayerController* pc =  other.gameObject->getComponent<PlayerController>();
            Rigidbody* rb = other.gameObject->getComponent<Rigidbody>();
            if (rb != nullptr && pc != nullptr) {
                rb->setGravityScale(1);
                pc->swiming = false;
                for(int i = 0; i < swimers.size(); i++) {
                    if (swimers[i] == rb) {
                        swimers.erase(swimers.begin() + i);
                    }
                }
            }
        }
    private:
        std::vector<Rigidbody*> swimers;
    };
}

#endif //PANCAKE_WATERSCRIPT_HPP
