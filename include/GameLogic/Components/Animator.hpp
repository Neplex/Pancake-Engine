//
// Created by nicolas on 28/01/17.
//

#ifndef PANCAKE_ANIMATOR_HPP
#define PANCAKE_ANIMATOR_HPP

#include <map>
#include "AnimationRenderer.hpp"

namespace PancakeEngine {

    class Animator : public Component {
    public:
        /**
         * Add animation
         * @param name the name of the state
         * @param animation the animation of the state
         * @param handler the handler of the state
         */
        void addAnimation(std::string name, Animation& animation, std::string (*handler)());
        /**
         * Get the animation associate with the current GameObject state
         * @return the current animation
         */
        AnimationRenderer& getCurrentAnimation() const;

        void update();

    private:
        struct State {
            AnimationRenderer * animation;
            std::string (*handler)();
        };
        std::map<std::string, State> states;
        std::string currentState = "";
    };
}

#endif //PANCAKE_ANIMATOR_HPP
