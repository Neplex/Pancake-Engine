//
// Created by nicolas on 28/01/17.
//

#include "../../../include/GameLogic/Components/Animator.hpp"

void Animator::addAnimation(std::string name, Animation animation, std::string (*handler)()) {
    State state;
    state.animation = new AnimationRenderer(animation);
    state.animation->loop();
    state.handler = handler;
    states[name] = state;
}

AnimationRenderer * Animator::getCurrentAnimation() const {
    return states.at(currentState).animation;
}

void Animator::update() {
    std::string state = states.at(currentState).handler();
    if (state == currentState)
        states.at(currentState).animation->update();
    else if (states.find(state) != states.end()) {
        states.at(currentState).animation->stop();
        currentState = state;
        states.at(currentState).animation->play();
    }
}
