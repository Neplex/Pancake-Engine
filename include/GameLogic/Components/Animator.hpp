//
// Created by nicolas on 28/01/17.
//

#ifndef PANCAKE_ANIMATOR_HPP
#define PANCAKE_ANIMATOR_HPP


#include "../../Graphics/AnimatorState.hpp"

class Animator {
public:
    AnimationRenderer& getCurrentAnimation();
    void handle();

private:
    AnimatorState& currentAnimation;
};


#endif //PANCAKE_ANIMATOR_HPP
