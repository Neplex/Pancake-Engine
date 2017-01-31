//
// Created by nicolas on 25/01/17.
//

#ifndef PANCAKE_ANIMATIONRENDERER_HPP
#define PANCAKE_ANIMATIONRENDERER_HPP


#include "Component.hpp"
#include "../../Graphics/Animation.hpp"

namespace PancakeEngine {

    class AnimationRenderer : public Component {
    public:
        AnimationRenderer();

        void play();

        void pause();

        void stop();

        void loop(bool b = true);

        void update();

        void setAnimation(Animation& a);

    private:
        friend class Window;

        sf::Sprite sprite;
        Animation* animation;
        bool isRun;
        bool isLoop;
        double currentTime;
        unsigned int currentFrame;

        void reset();
    };
}

#endif //PANCAKE_ANIMATIONRENDERER_HPP
