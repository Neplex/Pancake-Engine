//
// Created by nicolas on 11/02/17.
//

#ifndef PANCAKE_COMMANDCLEAR_HPP
#define PANCAKE_COMMANDCLEAR_HPP

#include "Command.hpp"

namespace PancakeEngine {
    class CommandClear : public Command {
    public:
        CommandClear(Console& c) : Command(c) {
            description = help = "Clear screen";
        }

        void execute(std::vector<std::string> &args) override {
            console.clear();
        }
    };
}

#endif //PANCAKE_COMMANDCLEAR_HPP
