//
// Created by nicolas on 11/02/17.
//

#ifndef PANCAKE_COMMANDHELP_HPP
#define PANCAKE_COMMANDHELP_HPP

#include <vector>
#include "Command.hpp"

namespace PancakeEngine {
    class CommandHelp : public Command {
    public:
        CommandHelp(Console& c) : Command(c) {
            description = "Show help";
            help = "show help of the command pass in parameter. Display all command available if no parameters.";
        }

        void execute(std::vector<std::string> &args) override {
            if (args.size() == 0) {
                for(const auto& kv : console.commands) {
                    console.print("- %s: %s", kv.first.c_str(), kv.second->description.c_str());
                }
            } else if (console.commands.find(args[0]) != console.commands.end()) {
                    console.print("%s", console.commands[args[0]]->help.c_str());
            } else {
                    console.printErr("Unknown command: '%s'", args[0].c_str());
            }
        }
    };
}

#endif //PANCAKE_COMMANDHELP_HPP
