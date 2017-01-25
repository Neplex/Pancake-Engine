//
// Created by nicolas on 25/01/17.
//

#include "../include/AnimationRenderer.hpp"
#include "../include/Time.hpp"

AnimationRenderer::AnimationRenderer(Animation& a) : animation(a), isRun(false), currentTime(0), currentFrame(0) {
    sprite.setTexture(animation.spriteSheet.texture);
    sprite.setTextureRect(animation.frames[currentFrame].rect);
    sprite.setOrigin(animation.spriteSheet.tile_width/2, animation.spriteSheet.tile_height/2);
}

void AnimationRenderer::update() {
    if (isRun) {
        currentTime += Time::getDeltaTime() * 1000;
        if (currentTime > animation.frames[currentFrame].time) {
            currentTime -= animation.frames[currentFrame].time;
            currentFrame = (currentFrame+1)%animation.frames.size();
            sprite.setTextureRect(animation.frames[currentFrame].rect);
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