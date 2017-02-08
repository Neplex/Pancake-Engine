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
 * \file        Engine.hpp
 * \author      Darenn Keller - keller.darenn@gmail.com
 */

#ifndef PANCAKE_ENGINE_HPP
#define PANCAKE_ENGINE_HPP


#include "SceneManager.hpp"
#include "Graphics/Window.hpp"
#include "Physics/PhysicsEngine.hpp"
#include "Time.hpp"
#include "Inputs/InputManager.hpp"

namespace PancakeEngine {

    /**
     * @class Engine
     * @brief It is the engine itself.
     * @details Build an instance to init the engine.
     * You can after that run the engine.
     * Engine is a friend of many classes.
     * The engine handle inputs at full speed, call the engine render at full speed, but update with a fixed timestep.
     */
    class Engine {

    public:
        const double SECONDS_PER_UPDATE = 1.0/100.0; ///< Time between two updates

        /**
         * @brief Init the engine.
         */
        Engine();
        ~Engine() {
            InputManager::destroyButtons();
            delete sceneManager.getCurrentScene();
        }

        /**
         * @brief Run the game loop of the engine.
         */
        void run();

        SceneManager sceneManager;
        Window window;
        PhysicsEngine physicsEngine;
        Time time;

    private:

        /**
         * @brief Update the engine (physics and logic) with a fixed timestep.
         */
        void update();
    };

}

#endif //PANCAKE_ENGINE_HPP
