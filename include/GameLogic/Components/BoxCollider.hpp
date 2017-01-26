//
// Created by kelle on 23/01/2017.
//

#ifndef PANCAKE_BOXCOLLIDER_HPP
#define PANCAKE_BOXCOLLIDER_HPP


#include <SFML/System.hpp>
#include "Collider.hpp"

class BoxCollider : public Collider {

public:
    // The total height of the collider
    float height;
    // The total width of the collider
    float width;
};


#endif //PANCAKE_BOXCOLLIDER_HPP
