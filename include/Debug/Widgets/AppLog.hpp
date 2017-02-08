//
// Created by kelle on 28/01/2017.
//

#ifndef PANCAKE_APPLOG_HPP
#define PANCAKE_APPLOG_HPP

#include "Imgui/imgui.h"

/**
 * @struct AppLog Represents a logger used in debug.
 * @brief It uses the ImGui library and is based on the examples of @file imgui_demo.cpp .
 * @details Use the draw function in between ImGui update and render to draw the logger.
 * Add a log with the AddLog function.
 * @example
 * @code
 * static AppLog my_log;
 * my_log.AddLog("Hello %d world\n", 123);
 * my_log.Draw("title");
 * @endcode
 */
struct AppLog
{
    ImGuiTextBuffer     Buf;
    ImGuiTextFilter     Filter;
    ImVector<int>       LineOffsets;        // Index to lines offset
    bool                ScrollToBottom;

    AppLog() : Buf(), Filter(), LineOffsets(), ScrollToBottom(){
    }

    /**
     * @brief Clear the logger from logs.
     */
    void Clear()     {
        Buf.clear();
        LineOffsets.clear();
    }

    /**
     * @brief Add a log to the logger.
     * @param fmt The message formated.
     * @param ... Args
     */
    void AddLog(const char* fmt, ...) IM_PRINTFARGS(2)
    {
        int old_size = Buf.size();
        va_list args;
        va_start(args, fmt);
        Buf.appendv(fmt, args);
        va_end(args);
        for (int new_size = Buf.size(); old_size < new_size; old_size++)
            if (Buf[old_size] == '\n')
                LineOffsets.push_back(old_size);
        ScrollToBottom = true;
    }

    /**
     * @brief Draw the logger.
     * @details Should be called between ImGui update and render to draw the logger.
     * @param title The title of the logger
     * @param p_open A pointer to the boolean that indicates if the logger should be drawn or not.
     */
    void    Draw(const char* title, bool* p_open = NULL)
    {
        ImGui::SetNextWindowSize(ImVec2(500,400), ImGuiSetCond_FirstUseEver);
        ImGui::Begin(title, p_open);
        if (ImGui::Button("Clear")) Clear();
        ImGui::SameLine();
        bool copy = ImGui::Button("Copy");
        ImGui::SameLine();
        Filter.Draw("Filter", -100.0f);
        ImGui::Separator();
        ImGui::BeginChild("scrolling", ImVec2(0,0), false, ImGuiWindowFlags_HorizontalScrollbar);
        if (copy) ImGui::LogToClipboard();

        if (Filter.IsActive())
        {
            const char* buf_begin = Buf.begin();
            const char* line = buf_begin;
            for (int line_no = 0; line != NULL; line_no++)
            {
                const char* line_end = (line_no < LineOffsets.Size) ? buf_begin + LineOffsets[line_no] : NULL;
                if (Filter.PassFilter(line, line_end))
                    ImGui::TextUnformatted(line, line_end);
                line = line_end && line_end[1] ? line_end + 1 : NULL;
            }
        }
        else
        {
            ImGui::TextUnformatted(Buf.begin());
        }

        if (ScrollToBottom)
            ImGui::SetScrollHere(1.0f);
        ScrollToBottom = false;
        ImGui::EndChild();
        ImGui::End();
    }
};

#endif //PANCAKE_APPLOG_HPP
