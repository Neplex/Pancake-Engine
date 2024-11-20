//
// Created by nicolas on 28/01/17.
//

#include <GameLogic/Components/Animator.hpp>
#include <Inputs/Input.hpp>

using namespace PancakeEngine;

Animator::~Animator() {
  for (auto const &s : states) {
    delete s.second.animation;
  }
}

void Animator::addAnimation(const std::string &name, Animation &animation,
                            const std::function<std::string(GameObject &)> &handler) {
  State state;
  state.animation = new AnimationRenderer();
  state.animation->setAnimation(animation);
  state.animation->loop();
  state.handler = handler;
  states[name] = state;

  if (currentState.empty()) {
    currentState = name;
    states[name].animation->play();
  }
}

void Animator::flip(bool b) { isFlip = b; }

const AnimationRenderer *Animator::getCurrentAnimation() const {
  if (states.empty()) return nullptr;
  return states.at(currentState).animation;
}

void Animator::update() {
  if (!states.empty()) {
    const std::string state = states[currentState].handler(*gameObject);
    states[currentState].animation->flip(isFlip);

    if (state == currentState) {
      states[currentState].animation->update();

    } else if (states.find(state) != states.end()) {
      states[currentState].animation->stop();
      currentState = state;
      states[currentState].animation->play();
    }
  }
}

sf::Sprite Animator::getSprite() const {
  const AnimationRenderer *animationRenderer;
  if ((animationRenderer = getCurrentAnimation()) == nullptr) {
    return AssetsManager::getDefaultSpriteSheet().getSprite(0, 0);
  }
  return animationRenderer->getSprite();
}
