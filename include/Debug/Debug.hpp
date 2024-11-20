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
 * \file        Debug.hpp
 * \author      Darenn Keller - keller.darenn@gmail.com
 */

#ifndef PANCAKE_DEBUG_HPP
#define PANCAKE_DEBUG_HPP

#include <imgui-SFML.h>
#include <Debug/FixedOverlayDebug.hpp>
#include <Debug/MainDebugMenu.hpp>
#include <Graphics/Window.hpp>

namespace PancakeEngine {

    /**
     * @class Debug
     * @brief Manage and display on a given window all debug data using ImGui.
     * @details Used to create loggers, add logs to them.
     */
    class Debug {
    public:

        /**
         * @brief Add a log to the given logger.
         * @param loggerName The logger to log.
         * @param message The message to log.
         */
        static void log(std::string loggerName, std::string message)
        {
            if (initialized)
                mainDebugMenu.logLogger(loggerName, message+"\n");
        }

        /**
         * @brief Create a new logger.
         * @details The logger will be added in the loggers menu of #mainDebugMenu.
         * @param name The name of the logger. Will be used to log to it.
         */
        static void addLogger(std::string name)
        {
            if (initialized)
                mainDebugMenu.addLogger(name);
        }

        /**
         * @brief Enable or disable the Debug GUI.
         * @detail The GUI will no longer be drawn but the debug is still active.
         * @param activate If true active the gui.
         */
        static void setEnableDebugGUI(bool activate)
        {
            if (initialized) {
                displayDebug = activate;
                window->setDebug(activate);
            }

        }

        /**
         * @brief Switch the enabled state of GUI.
         * @details If gui is enabled, disable it, vice versa.
         * Is sed by buttons callback.
         */
        static void switchEnableDebugGUI()
        {
            if (initialized) {
                displayDebug = !displayDebug;
                window->setDebug(displayDebug);
            }
        }

    private:
        friend class Engine; ///< The engine will be the one to init, update, and shut down the debug system.

        friend class InputManager; ///< The input manager will call the processEvent.

        friend class Window; ///< The window will call the render method.

        static MainDebugMenu mainDebugMenu; ///< the main debug menu of the debug, will be drawn on the given window.
        static FixedOverlayDebug fixedOverlayDebug; ///< A little windows to display some debug info.
        static bool displayDebug; ///< the debug gui is displayed if set to true.

        static Window* window; ///< The windows to set debug flags
        static sf::RenderWindow* renderWindow; ///< The window where ImGui is drawing.
        static bool initialized; ///< Set to true if debug was initialized.
        static sf::Clock clock; ///< To get the delta time.

        /**
         * @brief Initiate ImGui to display debugs content.
         * @param window The window that will be used to init.
         * @attention Debug does not draw itself the gui. It's #window that should call the render method of Debug.
         * But if another window that #window is used to init calls render, don't know what will arrive...
         * @todo resolve this problem with rendering, the debug should draw itself on the window.
         * @see Window
         */
        static void init(sf::RenderWindow& window, Window& win);

        /**
         * @brief Update ImGui.
         * @details Should be called at each game update by the engine
         * @see Engine.
         */
        static void update();

        /**
         * @brief Let ImGui Process an SFML event to get inputs.
         * @details Should be called by InputManager.
         * @see InputManager
         */
        static void processEvent(sf::Event event);

        /**
         * @brief Render ImGui things.
         * @details Should be called by window.
         * @see Window
         */
        static void render();

        /**
         * @brief Shutdown ImGui.
         * @details Should be called at the end of the program by the engine.
         * @see Engine
         */
        static void shutDown();
    };
}

#endif //PANCAKE_DEBUG_HPP
