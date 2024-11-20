//
// Created by nicolas on 09/02/17.
//

#ifndef PANCAKE_COMMAND_HPP
#define PANCAKE_COMMAND_HPP

#include <string>
#include <vector>

namespace PancakeEngine {
class Console;
class Command {
 public:
  std::string description;
  std::string help;

  virtual void execute(std::vector<std::string> &args) = 0;

  explicit Command(Console &c) : console(c) {}
  virtual ~Command() = default;

 protected:
  Console &console;
};
}  // namespace PancakeEngine

#endif  // PANCAKE_COMMAND_HPP
