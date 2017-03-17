//
// Created by virgil on 16/03/17.
//

#ifndef PANCAKE_ENNEMYSCRIPT_HPP
#define PANCAKE_ENNEMYSCRIPT_HPP

#include <GameLogic.hpp>
#include <User/Health.hpp>

class EnemyScript : public PancakeEngine::Behavior {
public:
    void awake() override {
        rb = gameObject->getComponent<PancakeEngine::Rigidbody>();
        vector2f.x = 2;
        vector2f.y = 0;
    }
    void OnTriggerEnter(const PancakeEngine::Collider& triggered, const PancakeEngine::Collider& other) override
    {
        PancakeEngine::GameObject* goTriggered = triggered.gameObject;
        PancakeEngine::GameObject* goOther = other.gameObject;
        if(goOther->transform.getWorldPosition().y <= goTriggered->transform.getWorldPosition().y){
            exploded = true;
        }
        else{
            Health* h = other.gameObject->getComponent<Health>();
            if (h) h->makeDamages(1);
        }

    }
    void update() override
    {
        rb->setVelocity(vector2f);
        if(clock1.getElapsedTime().asSeconds() >= 2.0) {
            float velXChange = (rb->getVelocity().x) * -1;
            vector2f.x = velXChange;
            rb->setVelocity(vector2f);
            clock1.restart();
        }
        if(exploded) destroy(*gameObject);
    }
private:
    bool exploded = false;
    sf::Vector2f vector2f;
    sf::Clock clock1;
    PancakeEngine::Rigidbody* rb;
};
#endif //PANCAKE_ENNEMYSCRIPT_HPP
