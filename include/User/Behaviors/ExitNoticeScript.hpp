//
// Created by virgil on 18/03/17.
//

#ifndef PANCAKE_EXITNOTICESCRIPT_HPP
#define PANCAKE_EXITNOTICESCRIPT_HPP
#include <GameLogic.hpp>

class ExitNoticeScript : public PancakeEngine::Behavior {
public:
    void OnTriggerEnter(const PancakeEngine::Collider& triggered, const PancakeEngine::Collider& other) override
    {
        if(other.gameObject->name == "player1"){
            //DoSomething
        }
    }
};
#endif //PANCAKE_EXITNOTICESCRIPT_HPP
