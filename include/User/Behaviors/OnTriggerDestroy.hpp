//
// Created by kelle on 12/02/2017.
//

#ifndef PANCAKE_ONTRIGGERDESTROY_HPP
#define PANCAKE_ONTRIGGERDESTROY_HPP

#include <Debug/Debug.hpp>
#include <GameLogic/Components/Behavior.hpp>

class OnTriggerDestroy : public PancakeEngine::Behavior {
 public:
  std::string target;

  void OnTriggerEnter(const PancakeEngine::Collider &triggered, const PancakeEngine::Collider &other) override {
    if (target.empty() || target == other.gameObject->name) {
      destroy(*gameObject);
    }

    PancakeEngine::Debug::log("Foo", "On trigger destroy called !");
  }
};

#endif  // PANCAKE_ONTRIGGERDESTROY_HPP
