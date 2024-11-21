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
 * \file        LuaScript.hpp
 * \author      Nicolas Hiot - nicolashiot@hotmail.com
 */

#ifndef PANCAKE_LUASCRIPT_HPP
#define PANCAKE_LUASCRIPT_HPP

#include <GameLogic/Components/Behavior.hpp>
#include <lua.hpp>

namespace PancakeEngine {

/**
 * @class LuaScript
 * @brief Component that can run a lua script.
 * @details All component methods will call the lua function with the same name
 * in the current script.
 * @sa Component Behavior
 */
class LuaScript : public Behavior {
 public:
  /**
   * @brief Set and run a new script
   * @param uri the uri of the script
   */
  void setScript(const std::string &uri) const;

  void awake() override;
  void start() override;
  void update() override;
  void lateUpdate() override;

  void OnCollisionEnter(const Collision &collision) override;
  void OnCollisionExit(const Collision &collision) override;
  void OnTriggerEnter(const Collider &triggered, const Collider &other) override;
  void OnTriggerExit(const Collider &triggered, const Collider &other) override;

 private:
  friend class GameObject;

  lua_State *L;  ///< Lua state machine.

  LuaScript();
  ~LuaScript() override;

  void bindFunctions() const;
};
}  // namespace PancakeEngine

#endif  // PANCAKE_LUASCRIPT_HPP
