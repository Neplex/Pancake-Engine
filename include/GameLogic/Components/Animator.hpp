//
// Created by nicolas on 28/01/17.
//

#ifndef PANCAKE_ANIMATOR_HPP
#define PANCAKE_ANIMATOR_HPP

#include "AnimationRenderer.hpp"
namespace PancakeEngine {

    struct State {
        AnimationRenderer* animation;

        std::string (* handler)();
    };

    class Animator : public Component {
    public:
        void addAnimation(std::string name, Animation animation, std::string (* handler)());

        /**
         * Get the animation associate with the current GameObject state
         * @return the current animation
         */
        AnimationRenderer* getCurrentAnimation() const;

        void update();

    private:
        std::map<std::string, State> states;
        std::string currentState;
    };
}

#endif //PANCAKE_ANIMATOR_HPP
