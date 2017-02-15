//
// Created by nicolas on 25/01/17.
//

#include "../../../include/GameLogic/Components/AnimationRenderer.hpp"
#include "../../../include/Time.hpp"

using namespace PancakeEngine;

AnimationRenderer::AnimationRenderer() : sprite(), animation(NULL), isRun(false), isLoop(false), isFlip(false), currentTime(0), currentFrame(0) {}

void AnimationRenderer::update() {
    if (isRun && animation != NULL) {
        currentTime += Time::getDeltaTime() * 1000;
        if (currentTime >= animation->frames.at(currentFrame).time) {
            currentTime -= animation->frames.at(currentFrame).time;
            if (++currentFrame >= animation->frames.size()) {
                if (isLoop) currentFrame = 0;
                else {
                    pause();
                    currentFrame--;
                }
            }
            sprite.setTextureRect(animation->frames.at(currentFrame).rect);
        }
    }
}

void AnimationRenderer::play() {
    isRun = true;
}

void AnimationRenderer::pause() {
    isRun = false;
}

void AnimationRenderer::stop() {
    pause();
    reset();
}

void AnimationRenderer::reset() {
    currentFrame = 0;
    currentTime = 0;
}

void AnimationRenderer::loop(bool b) {
    isLoop = b;
}

void AnimationRenderer::flip(bool b) {
    isFlip = b;
    if (isFlip) sprite.setScale(-1, 1);
    else sprite.setScale(1, 1);
}

void AnimationRenderer::setAnimation(Animation &a) {
    animation = &a;
    sprite.setTexture(animation->spriteSheet.texture);
    sprite.setTextureRect(animation->frames[currentFrame].rect);
    sprite.setOrigin(animation->spriteSheet.tile_width/2, animation->spriteSheet.tile_height/2);
}
