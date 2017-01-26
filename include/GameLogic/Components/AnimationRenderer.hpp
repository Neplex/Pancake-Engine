//
// Created by nicolas on 25/01/17.
//

#ifndef PANCAKE_ANIMATIONRENDERER_HPP
#define PANCAKE_ANIMATIONRENDERER_HPP


#include "Component.hpp"
#include "../../Graphics/Animation.hpp"

class AnimationRenderer : public Component {
public:
    AnimationRenderer(Animation& a);

    void play();
    void pause();
    void stop();

    void update();

private:
    friend class Window;

    sf::Sprite sprite;
    Animation& animation;
    bool isRun;
    double currentTime;
    unsigned int currentFrame;

    void reset();
};


#endif //PANCAKE_ANIMATIONRENDERER_HPP
