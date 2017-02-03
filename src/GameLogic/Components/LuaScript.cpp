//
// Created by nicolas on 03/02/17.
//

#include "../../../include/GameLogic/Components/LuaScript.hpp"
#include <sstream>

#define CALL_FUNCTION(L, name)                                                 \
  lua_getglobal(L, name);                                                      \
  if (lua_isfunction(L, -1))                                                   \
    lua_call(L, 0, 0);                                                         \
  lua_pop(L, 1);

#define THROW_ERROR(L, msg)                                                    \
  lua_pushstring(L, msg);                                                      \
  lua_error(L);

using namespace PancakeEngine;

LuaScript::LuaScript() {
    Debug::log("Lua", "[C++] Init lua");
    L = luaL_newstate();

    Debug::log("Lua", "[C++] Load libs");
    luaopen_base(L);
    luaopen_math(L);
    // luaopen_io(L);
}

LuaScript::~LuaScript() {
    Debug::log("Lua", "[C++] Close lua");
    lua_close(L);
}

void LuaScript::setScript(std::string uri) {
    Debug::log("Lua", "[C++] Clear stack");
    lua_settop(L, 0);

    bindFunctions();

    Debug::log("Lua", "[C++] Load script");
    luaL_dofile(L, uri.c_str());
}

// Called function
void LuaScript::awake() { CALL_FUNCTION(L, "awake") }
void LuaScript::start() { CALL_FUNCTION(L, "start") }
void LuaScript::update() { CALL_FUNCTION(L, "update") }
void LuaScript::lateUpdate() { CALL_FUNCTION(L, "lateUpdate") }

// Binding functions
int luaPrint(lua_State *L) {
    std::stringstream ss;
    ss << "[Lua] " << lua_tostring(L, 1);
    Debug::log("Lua", ss.str());
    return 0;
}

void LuaScript::bindFunctions() {
    Debug::log("Lua", "[C++] Bind functions");

    lua_register(L, "print", luaPrint);
}
