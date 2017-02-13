//
// Created by kelle on 12/02/2017.
//

#ifndef PANCAKE_ONTRIGGERDESTROY_HPP
#define PANCAKE_ONTRIGGERDESTROY_HPP

#include <GameLogic/Components/Behavior.hpp>
#include <Debug/Debug.hpp>

namespace PancakeEngine {

    class OnTriggerDestroy : public Behavior {

    public:
        void OnTriggerEnter(const Collider &triggered, const Collider &other) override {
            destroy(*gameObject);
            Debug::log("Foo", "On trigger destroy called !");
        }
    };
}

#endif //PANCAKE_ONTRIGGERDESTROY_HPP
