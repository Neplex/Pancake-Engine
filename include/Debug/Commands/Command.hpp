//
// Created by nicolas on 09/02/17.
//

#ifndef PANCAKE_COMMAND_HPP
#define PANCAKE_COMMAND_HPP

#include <iostream>
#include <Debug/Widgets/Console.hpp>

namespace PancakeEngine {
    class Console;
    class Command {
    public:
        std::string description;
        std::string help;

        virtual void execute(std::vector<std::string>& args) = 0;

        Command(Console& c) : console(c) {}
        virtual ~Command() {}

    protected:
        Console& console;
    };
}

#endif // PANCAKE_COMMAND_HPP
