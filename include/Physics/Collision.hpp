/*
     Copyright (C) 2016-2017 Keller Darenn - keller.darenn@gmail.com

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

/**
 * \file        Collision.hpp
 * \author      Darenn Keller - keller.darenn@gmail.com
 */

#ifndef PANCAKE_COLLISION_HPP
#define PANCAKE_COLLISION_HPP

#include "../GameLogic/Components/Collider.hpp"

namespace PancakeEngine {

/**
 * @class Collision
 * @brief Describes a collision.
 */
    class Collision {

    public:

        Collision(Collider& collided, Collider& other, float rest, float fric, float ts) : collidedCollider(collided),
                                                                                           otherCollider(other),
                                                                                           restitution(rest),
                                                                                           friction(fric),
                                                                                           tangentSpeed(ts) {}

        const Collider& collidedCollider; ///< The collider of the gameobject.
        const Collider& otherCollider; ///< The collider of the other gameobject.
        const float restitution; ///< The restitution of the collision
        const float friction; ///< The friction of the collision
        const float tangentSpeed; ///< The tangentSpeed of the collision
    };
}


#endif //PANCAKE_COLLISION_HPP
