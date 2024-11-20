/*
     Copyright (C) 2016-2017 Nicolas Hiot - nicolashiot@hotmail.com

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

/**
 * \file        Console.hpp
 * \author      Nicolas Hiot - nicolashiot@hotmail.com
 */

#ifndef PANCAKE_CONSOLE_HPP
#define PANCAKE_CONSOLE_HPP

#include <imgui.h>

#include <Debug/Commands/Command.hpp>
#include <map>
#include <string>
#include <vector>

namespace PancakeEngine {

/**
 * @class Console
 * @brief A debug console with command.
 * @details A console can execute command and display the result.
 * @sa Command
 */
class Console {
 public:
  Console();
  ~Console();

  /**
   * @brief Clear the console
   */
  void clear();

  /**
   * @brief Print formatted data to the console
   * @param fmt the format (look printf documentation)
   * @param ... additional arguments
   */
  void print(const char *fmt, ...);  // IM_PRINTFARGS(2);

  /**
   * @brief Print formatted data to the console (with error label)
   * @param fmt the format (look printf documentation)
   * @param ... additional arguments
   */
  void printErr(const char *fmt, ...);  // IM_PRINTFARGS(2);

  /**
   * @brief execute the command line from a string
   * @param command
   */
  void exec(const std::string &command);

  /**
   * @brief Add a new command
   * @tparam T the command class
   * @param name the name of the command (ex: help)
   * @sa Command
   */
  template <class T>
  void addCommand(std::string const &name) {
    auto *command = new T(*this);
    commands[name] = command;
  }

  /**
   * Draw the console
   * @param title the title of the window
   * @param p_open Boolean 'is open'
   */
  void draw(const char *title, bool *p_open);

  /**
   * @brief Handle event data
   * @param data The event data
   * @return Error code, 0 is ok
   * @sa ImGuiTextEditCallbackData
   */
  int handleEvent(ImGuiTextEditCallbackData *data);

 private:
  friend class CommandHelp;
  friend class CommandClear;

  char inputBuf[256]{};  ///< The buffer for the input text area
  bool scrollToBottom{};
  long historyPos;  ///< The position in the history

  std::map<std::string, Command *> commands;  ///< List of commands
  std::vector<std::string> items;             ///< List of log
  std::vector<std::string> history;           ///< List of commands executed
};
}  // namespace PancakeEngine
#endif  // PANCAKE_CONSOLE_HPP
