/*
     Copyright (C) 2016-2017 Nicolas Hiot - nicolashiot@hotmail.com

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
 * \file        Window.hpp
 * \author      Nicolas Hiot - nicolashiot@hotmail.com
 */

#ifndef PANCAKE_WINDOW_HPP
#define PANCAKE_WINDOW_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SceneManager.hpp>
#include <GameLogic/Components/BoxCollider.hpp>
#include <GameLogic/Components/CircleCollider.hpp>
#include <GameLogic/Components/Renderer.hpp>

namespace PancakeEngine {

    /**
     * @class Window
     * @brief The game window.
     */
    class Window {
    public:
        /**
         * @brief Construct a window.
         * @param s a scene manager.
         * @sa SceneManager
         */
        Window();

        /**
         * @brief Return the state of the window (open/close)
         * @return True if the window is closed, else return False
         */
        bool isClosed() { return !window.isOpen(); }

        /**
         * @brief Render one frame
         */
        void render();

        /**
         * @brief Set debug display to True or False
         * Display colider
         * @param val
         */
        void setDebug(bool val = true);

        /**
         * @brief Set the framerate. (FPS: frames per second)
         * @param framerate The new framerate in FPS.
         */
        void setFrameRate(float framerate);

    private:
        friend class Engine;

        sf::RenderWindow window;
        bool debug;
        float FPS;
        sf::Time timeBetweenTwoFrames;
        sf::Clock clock; ///< Used to limit the FPS

        /**
         * @brief Draw all elements (Renderer) of the current scene
         */
        void drawScene();

        void draw(const GameObject* gameObject);
        // Debug
        void draw(const BoxCollider* collider, sf::RenderStates renderStates);
        void draw(const CircleCollider* collider, sf::RenderStates renderStates);

        sf::Color getColor(const Collider* collider);
    };
}

#endif //PANCAKE_WINDOW_HPP
