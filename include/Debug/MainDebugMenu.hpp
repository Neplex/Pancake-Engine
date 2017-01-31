//
// Created by kelle on 28/01/2017.
//

#ifndef PANCAKE_MAINDEBUGMENU_HPP
#define PANCAKE_MAINDEBUGMENU_HPP

#include <map>
#include "../imgui/imgui.h"
#include "Widgets/AppLog.hpp"

namespace PancakeEngine {

    class MainDebugMenu {
    public:

        void draw()
        {
            // Draw the main bar
            if (ImGui::BeginMainMenuBar()) {
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
                    loggers[it->first].Draw(it->first.c_str());
                }
            }
        }

        void logLogger(std::string name, std::string message)
        {
            loggers[name].AddLog(message.c_str());
        }

        void addLogger(const std::string& name)
        {
            AppLog logger;
            loggers.emplace(name, logger);
            loggersToggled.emplace(name, false);
        }

    private:
        std::map<const std::string, AppLog> loggers; ///< The name of the logger associated to the logger
        std::map<const std::string, bool> loggersToggled; ///< Associate a bool to each logger, if the menu item  of a logger is toggled, set the associated bool to true;
    };
}

#endif //PANCAKE_MAINDEBUGMENU_HPP
