//
// Created by kelle on 29/01/2017.
//

#ifndef PANCAKE_FIXEDOVERLAY_HPP
#define PANCAKE_FIXEDOVERLAY_HPP

#include "../imgui/imgui.h"

class FixedOverlayDebug {
public:
    void draw(bool* p_open) {
        ImGui::SetNextWindowPos(ImVec2(10,20));
        if (!ImGui::Begin("Debug Overlay", p_open, ImVec2(0,0), 0.3f, ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoSavedSettings))
        {
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

#endif //PANCAKE_FIXEDOVERLAY_HPP
