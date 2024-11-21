//
// Created by Darenn on 15/03/2017.
//

#ifndef PANCAKE_ONTRIGGERKILL_HPP
#define PANCAKE_ONTRIGGERKILL_HPP

#include <GameLogic.hpp>
#include <User/Health.hpp>

class OnTriggerKill : public PancakeEngine::Behavior {
 public:
  // OnTriggerEnter is called when another collider enter the trigger of this object
  void OnTriggerEnter(const PancakeEngine::Collider &triggered, const PancakeEngine::Collider &other) override {
    // Health is another Behavior that gives the GameObject health and the possibility to die
    auto *h = other.gameObject->getComponent<Health>();
    if (h) {
      // Here we kill the object
      h->kill();
    }
  }
};

#endif  // PANCAKE_ONTRIGGERKILL_HPP
