//
// Created by nicolas on 02/02/17.
//

#ifndef PANCAKE_LUASCRIPT_HPP
#define PANCAKE_LUASCRIPT_HPP

#include "Component.hpp"
#include "../../Debug/Debug.hpp"
#include <iostream>
#include <sstream>
#include <lua.hpp>
#include <lauxlib.h>
#include <lualib.h>

namespace PancakeEngine {
    class LuaScript : public Component {
        void awake() {
            Debug::addLogger("Lua");

            Debug::log("Lua", "[C++] Init lua");
            lua_State *lua = luaL_newstate();

            Debug::log("Lua", "[C++] Load libs");
            luaopen_base(lua);
            luaopen_math(lua);
            luaopen_io(lua);

            Debug::log("Lua", "[C++] Clear stack");
            lua_settop(lua, 0);

            Debug::log("Lua", "[C++] Load script");
            if (luaL_loadfile (lua, "../resources/scripts/test.lua") == 0) {
                Debug::log("Lua", "[C++] Run awake function");
                lua_setglobal(lua, "awake");
                lua_pcall(lua, 0, 0, 0);
            }

            Debug::log("Lua", "[C++] Close lua");
            lua_close(lua);
        }
    };
}

#endif //PANCAKE_LUASCRIPT_HPP
