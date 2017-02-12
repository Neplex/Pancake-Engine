//
// Created by nicolas on 09/02/17.
//

#include <Debug/Widgets/Console.hpp>
#include <Imgui/imgui_internal.h>
#include <Debug/Commands/CommandHelp.hpp>
#include <Debug/Commands/CommandClear.hpp>
#include <sstream>

#define BUFFER_SIZE 1024
#define ERROR_SYMBOL "[error]"
#define COMMAND_SYMBOL "# "

using namespace PancakeEngine;

Console::Console() : historyPos(-1) {
    clear();
    memset(inputBuf, 0, sizeof(inputBuf));
    addCommand<CommandHelp>("help");
    addCommand<CommandClear>("clear");
}

Console::~Console() {
    clear();
}

void Console::clear() {
    items.clear();
    scrollToBottom = true;
}

void Console::print(const char *fmt, ...) {
    char buf[BUFFER_SIZE];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, BUFFER_SIZE, fmt, args);
    buf[BUFFER_SIZE - 1] = 0;
    va_end(args);
    std::string s(buf);
    items.push_back(s);
    scrollToBottom = true;
}

void Console::printErr(const char *fmt, ...) {
    char buf[BUFFER_SIZE];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, BUFFER_SIZE, fmt, args);
    buf[BUFFER_SIZE - 1] = 0;
    va_end(args);
    std::string s(ERROR_SYMBOL);
    items.push_back(s + " " + buf);
    scrollToBottom = true;
}

void Console::exec(std::string command_line) {
    // Split command_line
    std::istringstream buf(command_line);
    std::vector<std::string> args;
    std::string word;
    while (buf >> word) args.push_back(word);

    if (args.size() > 0) {
        std::string command = args[0];
        args.erase(args.begin());

        history.push_back(command_line);
        print(COMMAND_SYMBOL"%s", command_line.c_str());

        if (commands.find(command) != commands.end()) {
            commands.at(command)->execute(args);
        } else {
            printErr("Unknown command: '%s'", command.c_str());
        }
    }
}

static int textEditCallbackStub(ImGuiTextEditCallbackData *data) {
    Console *console = (Console *) data->UserData;
    return console->handleEvent(data);
}

static void updateBuffer(ImGuiTextEditCallbackData *data, std::string text) {
    data->CursorPos = data->SelectionStart = data->SelectionEnd = data->BufTextLen = snprintf(data->Buf, (size_t) data->BufSize, "%s", text.c_str());
    data->BufDirty = true;
}

int Console::handleEvent(ImGuiTextEditCallbackData *data) {
    switch (data->EventFlag) {
        case ImGuiInputTextFlags_EnterReturnsTrue:
            break;

        case ImGuiInputTextFlags_CallbackCompletion:
            {
                std::vector<std::string> candidates;
                for (auto kv : commands) {
                    if (strcmp(kv.first.substr(0, data->BufTextLen).c_str(), data->Buf) == 0) {
                        candidates.push_back(kv.first);
                    }
                }

                if (candidates.size() == 0) {
                    print("No matching command");
                } else if (candidates.size() == 1) {
                    updateBuffer(data, candidates[0]);
                } else {
                    std::stringstream ss;
                    for (unsigned i=0; i < candidates.size()-1; i++)
                        ss << candidates[i].c_str() << ", ";
                    ss << candidates[candidates.size()-1];
                    print("Candidates: %s", ss.str().c_str());
                }
            }
            break;

        case ImGuiInputTextFlags_CallbackHistory:
            {
                const long prev_history_pos = historyPos;
                if (data->EventKey == ImGuiKey_UpArrow) {
                    if (historyPos == -1)
                        historyPos = history.size() - 1;
                    else if (historyPos > 0)
                        historyPos--;
                } else if (data->EventKey == ImGuiKey_DownArrow) {
                    if (historyPos != -1)
                        if (++historyPos >= history.size())
                            historyPos = -1;
                }

                if (prev_history_pos != historyPos) {
                    updateBuffer(data, (historyPos >= 0) ? history[historyPos].c_str() : "");
                }
            }
            break;

        default:
            return 1;
    }
    return 0;
}

void Console::draw(const char *title, bool *p_open) {
    ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiSetCond_FirstUseEver);
    if (!ImGui::Begin(title, p_open)) {
        ImGui::End();
        return;
    }

    ImGui::TextWrapped(
            "Enter 'help' for help, press TAB to use text completion.");

    /*if (ImGui::SmallButton("Clear")) clear();
    ImGui::SameLine();
    if (ImGui::SmallButton("Scroll to bottom")) scrollToBottom = true;
    ImGui::Separator();*/

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
    static ImGuiTextFilter filter;
    filter.Draw("Filter (\"incl,-excl\") (\"error\")", 180);
    ImGui::PopStyleVar();
    ImGui::Separator();

    ImGui::BeginChild("ScrollingRegion",
                      ImVec2(0, -ImGui::GetItemsLineHeightWithSpacing()), false,
                      ImGuiWindowFlags_HorizontalScrollbar);
    if (ImGui::BeginPopupContextWindow()) {
        if (ImGui::Selectable("Clear"))
            clear();
        ImGui::EndPopup();
    }

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1));
    for (int i = 0; i < items.size(); i++) {
        std::string item = items[i];
        if (!filter.PassFilter(item.c_str()))
            continue;
        ImVec4 col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        if (strstr(item.c_str(), ERROR_SYMBOL))
            col = ImColor(1.0f, 0.4f, 0.4f, 1.0f);
        else if (strncmp(item.c_str(), COMMAND_SYMBOL, 2) == 0)
            col = ImColor(1.0f, 0.78f, 0.58f, 1.0f);
        ImGui::PushStyleColor(ImGuiCol_Text, col);
        ImGui::TextUnformatted(item.c_str());
        ImGui::PopStyleColor();
    }
    if (scrollToBottom) ImGui::SetScrollHere();
    scrollToBottom = false;

    ImGui::PopStyleVar();
    ImGui::EndChild();
    ImGui::Separator();

    if (ImGui::InputText("", inputBuf, IM_ARRAYSIZE(inputBuf),
                         ImGuiInputTextFlags_EnterReturnsTrue |
                         ImGuiInputTextFlags_CallbackCompletion |
                         ImGuiInputTextFlags_CallbackHistory,
                         &textEditCallbackStub, (void *) this)) {
        exec(inputBuf);
        strcpy(inputBuf, "");
    }

    if (ImGui::IsItemHovered() ||
        (ImGui::IsRootWindowOrAnyChildFocused() &&
         !ImGui::IsAnyItemActive() &&
         !ImGui::IsMouseClicked(0)))
        ImGui::SetKeyboardFocusHere(-1);

    ImGui::End();
}