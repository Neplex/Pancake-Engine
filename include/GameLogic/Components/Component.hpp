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
 * @file        Component.hpp
 * @author      Darenn Keller - keller.darenn@gmail.com
 */

#ifndef PANCAKE_COMPONENT_HPP
#define PANCAKE_COMPONENT_HPP

namespace PancakeEngine {
    class GameObject;
    class Component {
    public:
        GameObject* gameObject;


        /**
         * Called at GameObject creation.
         */
        virtual void awake() { };

        /**
         * Called just before the first update call.
         */
        virtual void start() { };

        /**
         * Called at each frame before physics.
         */
        virtual void update() { };

        /**
         * Called at each frame update.
         */
        virtual void lateUpdate() { };

    protected:
        virtual ~Component() {};


    private:
        friend class Behavior; ///< To allow modify toDestroy flag
        friend class GameObject; ///< to destroy the component
        bool toDestroy = false;
    };
}

#endif //PANCAKE_COMPONENT_HPP
