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

#include "Component.hpp"
#include "../../Physics/Collision.hpp"

namespace PancakeEngine {

    /**
     * @class Behavior
     * @brief Behavior is the base class from which every scripts should derives.
     */
    class Behavior : Component {

    public:

        virtual void OnCollisionEnter(Collision collision);
        virtual void OnCollisionExit(Collision collision);

    };

}

#endif //PANCAKE_BEHAVIOR_HPP
