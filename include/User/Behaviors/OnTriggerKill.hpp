//
// Created by Darenn on 15/03/2017.
//

#ifndef PANCAKE_ONTRIGGERKILL_HPP
#define PANCAKE_ONTRIGGERKILL_HPP

#include <GameLogic.hpp>
#include <User/Health.hpp>

class OnTriggerKill : public PancakeEngine::Behavior {
public:

    void OnTriggerEnter(const PancakeEngine::Collider &triggered, const PancakeEngine::Collider &other) override {
        Health* h = other.gameObject->getComponent<Health>();
        if (h) {
            h->kill();
        }
    }

};

#endif //PANCAKE_ONTRIGGERKILL_HPP
