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

#include "../../Debug/Debug.hpp"
#include "Component.hpp"
#include <lua.hpp>
#include <lualib.h>
#include <lauxlib.h>

namespace PancakeEngine {

    /**
     * @class LuaScript
     * @brief Component that can run a lua script.
     * @details All component methods will call the lua function with the same name in the current script.
     * @sa Component
     */
    class LuaScript : public Component {
    public:
        /**
         * @brief Set and run a new script
         * @param uri the uri of the script
         */
        void setScript(std::string uri);

        void awake();
        void start();
        void update();
        void lateUpdate();

    private:
        friend class GameObject;

        lua_State *L; ///< Lua state machine.

        LuaScript();
        ~LuaScript();

        void bindFunctions();
    };
}

#endif // PANCAKE_LUASCRIPT_HPP
