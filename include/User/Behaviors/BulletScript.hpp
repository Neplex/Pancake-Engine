//
// Created by Darenn on 15/03/2017.
//

#ifndef PANCAKE_BULLET_HPP
#define PANCAKE_BULLET_HPP

#include <GameLogic.hpp>
#include <User/Health.hpp>

class BulletScript : public PancakeEngine::Behavior {
public:
    int direction = 1;
    std::string owner = "";

    void awake() override
    {
        rb = gameObject->getComponent<PancakeEngine::Rigidbody>();
    }

    void OnTriggerEnter(const PancakeEngine::Collider& triggered, const PancakeEngine::Collider& other) override
    {
        if (!exploded && other.gameObject->name != owner) {
            Health* h = other.gameObject->getComponent<Health>();
            if (h) h->makeDamages(1);
            exploded = true;
        }

    }

    void update() override
    {
        rb->setVelocity(sf::Vector2f(15 * direction,0));
        if(exploded) destroy(*gameObject);
    }

private:
    PancakeEngine::Rigidbody* rb;
    bool exploded = false;
};

#endif //PANCAKE_BULLET_HPP
