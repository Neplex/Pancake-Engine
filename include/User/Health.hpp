//
// Created by Darenn on 14/03/2017.
//

#ifndef PANCAKE_HEALTH_HPP
#define PANCAKE_HEALTH_HPP

#include <GameLogic.hpp>

class Health : public PancakeEngine::Behavior {
 public:
  Health() : Behavior() { this->hp = this->maxHp = 6; }

  void start() override {}

  bool isDead() const { return dead; }

  unsigned getHp() const { return hp; }

  void kill() {
    dead = true;
    hp = 0;
  }

  void reSpawn() {
    hp = maxHp;
    dead = false;
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

#endif  // PANCAKE_HEALTH_HPP
