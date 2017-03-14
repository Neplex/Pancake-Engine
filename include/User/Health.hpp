//
// Created by Darenn on 14/03/2017.
//

#ifndef PANCAKE_HEALTH_HPP
#define PANCAKE_HEALTH_HPP

#include <GameLogic.hpp>

class Health : public PancakeEngine::Behavior  {

public:

    Health() : PancakeEngine::Behavior(), maxHp(6), hp(6) {

    }

    void start() override {

    }

    bool isDead() {
        return dead;
    }

    unsigned getHp() {
        return hp;
    }

    void makeDamages(int amount) {
        hp -= amount;
        if (hp <= 0) {
            hp = 0;
            dead = true;
        }
    }

private:
    unsigned int maxHp;
    unsigned int hp;
    bool dead = false;
};

#endif //PANCAKE_HEALTH_HPP
