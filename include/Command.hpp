//
// Created by nicolas on 22/01/17.
//

#ifndef PANCAKE_COMMAND_HPP
#define PANCAKE_COMMAND_HPP

/**
 * Command interface
 */
class Command {
public:
    virtual ~Command() {}

    /**
     * Call when a button is pressed
     */
    virtual void execute() = 0;

    /**
     * Call when a position is update (mouse move)
     * @param x
     * @param y
     */
    virtual void execute(int x, int y) {};
};

#endif //PANCAKE_COMMAND_HPP
