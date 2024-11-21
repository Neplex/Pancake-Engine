//
// Created by nicolas on 11/02/17.
//

#ifndef PANCAKE_COMMANDCLEAR_HPP
#define PANCAKE_COMMANDCLEAR_HPP

#include <Debug/Commands/Command.hpp>
#include <Debug/Widgets/Console.hpp>
#include <string>
#include <vector>

namespace PancakeEngine {
class CommandClear : public Command {
 public:
  explicit CommandClear(Console &c) : Command(c) { description = help = "Clear screen"; }

  void execute(std::vector<std::string> &args) override { console.clear(); }
};
}  // namespace PancakeEngine

#endif  // PANCAKE_COMMANDCLEAR_HPP
