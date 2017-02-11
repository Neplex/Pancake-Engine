//
// Created by kelle on 08/02/2017.
//

#ifndef PANCAKE_CONSOLE_HPP
#define PANCAKE_CONSOLE_HPP

#include <vector>
#include <string>
#include <Debug/Commands/Command.hpp>
#include <Imgui/imgui.h>
#include <map>

namespace PancakeEngine {
    class Console {
    public:
        Console();
        ~Console();

        void clear();
        void print(const char *fmt, ...) IM_PRINTFARGS(2);
        void printErr(const char *fmt, ...) IM_PRINTFARGS(2);
        void exec(std::string command);

        template <class T>
        void addCommand(std::string name) {
            T* command = new T(*this);
            commands[name] = command;
        }

        void draw(const char *title, bool *p_open);
        int handleEvent(ImGuiTextEditCallbackData *data);
        
    private:
        friend class CommandHelp;
        friend class CommandClear;

        char inputBuf[256];
        bool scrollToBottom;
        long historyPos;
        std::map<std::string, Command*> commands;
        std::vector<std::string> items;
        std::vector<std::string> history;
    };
}
#endif // PANCAKE_CONSOLE_HPP
