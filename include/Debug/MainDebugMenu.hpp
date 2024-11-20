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
 * \file        MainDebugMenu.hpp
 * \author      Darenn Keller - keller.darenn@gmail.com
 */

#ifndef PANCAKE_MAINDEBUGMENU_HPP
#define PANCAKE_MAINDEBUGMENU_HPP

#include <map>
#include <Debug/Widgets/Console.hpp>
#include "imgui.h"
#include "Widgets/AppLog.hpp"

namespace PancakeEngine {

    /**
     * @class MainDebugMenu
     * @brief Display the debug menu bar in top of the screen and all other widgets.
     */
    class MainDebugMenu {
    public:
        MainDebugMenu() {
        }

        ~MainDebugMenu() {
            for (auto p : loggers) {
                delete p.second;
            }
        }
        /**
         * @brief Draw the main debug menu.
         */
        void draw()
        {
            // Draw the main bar
            if (ImGui::BeginMainMenuBar()) {
                if (ImGui::BeginMenu("Console")) {
                    ImGui::MenuItem("Console", NULL, &consoleToggled);
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Loggers")) {
                    auto it = loggers.begin();
                    for (; it!=loggers.end(); ++it) {
                        ImGui::MenuItem(it->first.c_str(), NULL, &loggersToggled[it->first]);
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndMainMenuBar();
            }

            // If a menu button is toggled, draw logger
            auto it = loggersToggled.begin();
            for (; it!=loggersToggled.end(); ++it) {
                if (it->second) {
                    loggers[it->first]->Draw(it->first.c_str());
                }
            }

            // if console is toggled
            static Console c;
            console = &c;
            if (consoleToggled) {
                console->draw("Console", &consoleToggled);
            }
        }

        /**
         * @brief Add the message to the given logger.
         * @param name The name of the logger.
         * @param message The log.
         */
        void logLogger(std::string name, std::string message)
        {
            loggers[name]->AddLog("%s", message.c_str());
        }

        /**
         * @brief Add an AppLog logger to the menu.
         * @param name The title of the AppLog and its identifier in #loggers.
         */
        void addLogger(const std::string& name)
        {
            AppLog* logger = new AppLog();
            loggers.emplace(name, logger);
            loggersToggled.emplace(name, false);
        }

    private:
        Console* console;
        bool consoleToggled = false;
        std::map<const std::string, AppLog*> loggers; ///< The name of the logger associated to the logger
        std::map<const std::string, bool> loggersToggled; ///< Associate a bool to each logger, if the menu item  of a logger is toggled, set the associated bool to true;
    };
}

#endif //PANCAKE_MAINDEBUGMENU_HPP
