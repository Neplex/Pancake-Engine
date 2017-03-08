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
 * \file        Behavior.hpp
 * \author      Darenn Keller - keller.darenn@gmail.com
 */

#ifndef PANCAKE_BEHAVIOR_HPP
#define PANCAKE_BEHAVIOR_HPP

#include <GameLogic/Components/Component.hpp>
#include <Physics/Collision.hpp>

namespace PancakeEngine {

    /**
     * @class Behavior
     * @brief Behavior is the base class from which every scripts should derives.
     */
    class Behavior : public Component {

    public:

        virtual void OnCollisionEnter(const Collision& collision) {};
        virtual void OnCollisionExit(const Collision& collision) {};
        virtual void OnTriggerEnter(const Collider& triggered, const Collider& other) {};
        virtual void OnTriggerExit(const Collider& triggered, const Collider& other) {};
        /**
         * Destroy the game object after all updates or after all late update.
         * @param go The game object to destroy
         */
        void destroy(GameObject& go);

        /**
         * Destroy the component after all updates or after all late update.
         * @param c The component to destroy.
         */
        void destroy(Component& c);

    };


}

#endif //PANCAKE_BEHAVIOR_HPP
