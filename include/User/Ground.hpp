//
// Created by kelle on 26/01/2017.
//

#ifndef PANCAKE_GROUND_HPP
#define PANCAKE_GROUND_HPP


#include "../GameLogic/GameObject.hpp"
#include "../GameLogic/Components/BoxCollider.hpp"

namespace PancakeEngine {
    class Ground : public GameObject {
    public:
        Ground()
                :GameObject()
        {
                BoxCollider& bcGroundingBox = addComponent<BoxCollider>();
                bcGroundingBox.height = 72;
                bcGroundingBox.width = 72*8;
                transform.setPosition(sf::Vector2f(200, 300));
        }

    };
}

#endif //PANCAKE_GROUND_HPP
