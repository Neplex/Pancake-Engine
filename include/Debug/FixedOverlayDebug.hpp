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
 * \file        FixedOverlayDebug.hpp
 * \author      Darenn Keller - keller.darenn@gmail.com
 */

#ifndef PANCAKE_FIXEDOVERLAY_HPP
#define PANCAKE_FIXEDOVERLAY_HPP

#include "../imgui/imgui.h"

namespace PancakeEngine {

    /**
     * @class FixedOverlayDebug
     * @brief A simple window that you can draw.
     */
    class FixedOverlayDebug {
    public:
        /**
         * @brief Draw the overlay.
         * @param p_open Display the window if true.
         */
        void draw(bool* p_open)
        {
            ImGui::SetNextWindowPos(ImVec2(10, 20));
            if (!ImGui::Begin("Debug Overlay", p_open, ImVec2(0, 0), 0.3f,
                    ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
                            | ImGuiWindowFlags_NoSavedSettings)) {
                ImGui::End();
                return;
            }
            ImGui::Text("FPS : %.0f", ImGui::GetIO().Framerate);
            ImGui::Text("Display Size : %.0fx%.0f", ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y);
            ImGui::Text("Active Allocations : %d", ImGui::GetIO().MetricsAllocs);
            ImGui::Text("Vertices Rendered : %d", ImGui::GetIO().MetricsRenderVertices);
            ImGui::Separator();
            ImGui::Text("Mouse Position: (%.0f,%.0f)", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
            ImGui::End();
        }
    };
}
#endif //PANCAKE_FIXEDOVERLAY_HPP
