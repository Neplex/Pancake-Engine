//
// Created by nicolas on 22/01/17.
//

#ifndef PANCAKE_COMMAND_HPP
#define PANCAKE_COMMAND_HPP

class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;
    virtual void execute(int x, int y) {};
};

#endif //PANCAKE_COMMAND_HPP
