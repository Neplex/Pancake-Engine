//
// Created by nicolas on 28/01/17.
//

#include "../../../include/GameLogic/Components/Animator.hpp"

AnimationRenderer& Animator::getCurrentAnimation() {
    return currentAnimation.animation;
}

void Animator::handle() {
    AnimatorState* state = currentAnimation.handle();
    if (state != NULL) {
        delete currentAnimation;
        currentAnimation = *state;
    }
}
