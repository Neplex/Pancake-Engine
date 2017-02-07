//
// Created by nicolas on 03/02/17.
//

#include "../../../include/GameLogic/Components/LuaScript.hpp"
#include "../../../include/GameLogic/GameObject.hpp"
#include "../../../include/Inputs/Input.hpp"
#include "../../../include/Time.hpp"
#include "../../../include/Engine.hpp"
#include "../../../include/Graphics/AssetsManager.hpp"
#include "../../../include/GameLogic/Components/SpriteRenderer.hpp"
#include <sstream>

#define GO "GameObject"
#define SS "SpriteSheet"
#define AN "Animation"

#define CALL_FUNCTION(L, name)                                                 \
  {                                                                            \
    lua_getglobal(L, name);                                                    \
    if (lua_isfunction(L, -1))                                                 \
      lua_call(L, 0, 0);                                                       \
  }

#define THROW_ERROR(L, msg)                                                    \
  {                                                                            \
    lua_pushstring(L, msg);                                                    \
    lua_error(L);                                                              \
  }

using namespace PancakeEngine;

LuaScript::LuaScript() : Component() {
    Debug::log("Lua", "[C++] Init lua");
    L = luaL_newstate();

    Debug::log("Lua", "[C++] Load libs");
    luaopen_base(L);
    luaopen_math(L);
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
void LuaScript::awake() { CALL_FUNCTION(L, "awake"); }
void LuaScript::start() { CALL_FUNCTION(L, "start"); }
void LuaScript::update() { CALL_FUNCTION(L, "update"); }
void LuaScript::lateUpdate() { CALL_FUNCTION(L, "lateUpdate"); }

// Binding functions
int lua_print(lua_State *L) {
    std::stringstream ss;
    ss << "[Lua]";
    for (int i = 1; i <= lua_gettop(L); i++)
        ss << " " << luaL_checklstring(L, i, NULL);
    Debug::log("Lua", ss.str());
    return 0;
}

int input_getButtonPressed(lua_State *L) {
    if (lua_gettop(L) != 1)
    THROW_ERROR(L, "invalid number of argument in 'getButtonPressed'");
    lua_pushboolean(L, Input::getButtonPressed(luaL_checklstring(L, 1, NULL)));
    return 1;
}

int time_getDeltaTime(lua_State *L) {
    if (lua_gettop(L) > 0)
    THROW_ERROR(L, "invalid number of argument in 'getDeltaTime'");
    lua_pushnumber(L, Time::getDeltaTime());
    return 1;
}

int go_new(lua_State *L) {
    if (lua_gettop(L) > 0)
    THROW_ERROR(L, "invalid number of argument in constructor of 'GameObject()'");
    GameObject** go = (GameObject**)lua_newuserdata(L, sizeof(GameObject*));
    *go = NULL;//TODO: add new GameObject to the current scene
    luaL_setmetatable(L, GO);
    return 1;
}

int go_getName(lua_State *L) {
    if (lua_gettop(L) != 1)
    THROW_ERROR(L, "invalid number of argument in 'getName'");
    GameObject **go = (GameObject**)luaL_checkudata(L, -1, GO);
    lua_pushstring(L, (*go)->name.c_str());
    return 1;
}

int go_getPosition(lua_State *L) {
    if (lua_gettop(L) != 1)
    THROW_ERROR(L, "invalid number of argument in 'getPosition'");
    GameObject **go = (GameObject**)luaL_checkudata(L, -1, GO);
    sf::Vector2f pos = (*go)->transform.getPosition();
    lua_pushnumber(L, pos.x);
    lua_pushnumber(L, pos.y);
    return 2;
}

int go_setPosition(lua_State *L) {
    if (lua_gettop(L) != 3)
    THROW_ERROR(L, "invalid number of argument in 'setPosition'");
    GameObject **go = (GameObject**)luaL_checkudata(L, -3, GO);
    float x = (float)luaL_checknumber(L, -2);
    float y = (float)luaL_checknumber(L, -1);
    (*go)->transform.setPosition(sf::Vector2f(x, y));
    return 0;
}

int go_getRotation(lua_State *L) {
    if (lua_gettop(L) != 1)
    THROW_ERROR(L, "invalid number of argument in 'getPosition'");
    GameObject **go = (GameObject**)luaL_checkudata(L, -1, GO);
    lua_pushnumber(L, (*go)->transform.getRotation());
    return 1;
}

int go_setRotation(lua_State *L) {
    if (lua_gettop(L) != 2)
    THROW_ERROR(L, "invalid number of argument in 'setRotation'");
    GameObject **go = (GameObject**)luaL_checkudata(L, -2, GO);
    float a = (float)luaL_checknumber(L, -1);
    (*go)->transform.setRotation(a);
    return 0;
}

int go_setSprite(lua_State *L) {
    if (lua_gettop(L) != 4)
    THROW_ERROR(L, "invalid number of argument in 'setSprite'");
    GameObject **go = (GameObject**)luaL_checkudata(L, -4, GO);
    SpriteSheet **ss = (SpriteSheet**)luaL_checkudata(L, -3, SS);
    unsigned i = (unsigned)luaL_checkinteger(L, -2);
    unsigned j = (unsigned)luaL_checkinteger(L, -1);
    SpriteRenderer* sr = (*go)->getComponent<SpriteRenderer>();
    if (sr != NULL) { sr->setSprite(**ss, i, j); }
    else { THROW_ERROR(L, "GameObject does not have 'SpriteRender' attached to it"); }
    return 0;
}

int ss_new(lua_State *L) {
    if (lua_gettop(L) != 4)
    THROW_ERROR(L, "invalid number of argument in constructor of 'SpriteSheet(name, uri, width, height)'");
    std::string name = luaL_checklstring(L, -4, NULL);
    std::string uri  = luaL_checklstring(L, -3, NULL);
    unsigned w = (unsigned)luaL_checkinteger(L, -2);
    unsigned h = (unsigned)luaL_checkinteger(L, -1);
    SpriteSheet** ss = (SpriteSheet**)lua_newuserdata(L, sizeof(SpriteSheet*));
    *ss = &AssetsManager::createSpriteSheet(name, uri, w, h);
    luaL_setmetatable(L, SS);
    return 1;
}

int an_new(lua_State *L) {
    if (lua_gettop(L) != 2)
    THROW_ERROR(L, "invalid number of argument in constructor of 'Animation(name, spriteSheet)'");
    std::string name = luaL_checklstring(L, -2, NULL);
    SpriteSheet** ss = (SpriteSheet**)luaL_checkudata(L, -1, SS);
    Animation** an = (Animation**)lua_newuserdata(L, sizeof(Animation*));
    *an = &AssetsManager::createAnimation(name, **ss);
    luaL_setmetatable(L, AN);
    return 1;
}

int assetsManager_getSpriteSheet(lua_State *L) {
    if (lua_gettop(L) != 1)
    THROW_ERROR(L, "invalid number of argument in 'getSpriteSheet'");
    std::string name = luaL_checklstring(L, -1, NULL);
    SpriteSheet** ss = (SpriteSheet**)lua_newuserdata(L, sizeof(SpriteSheet*));
    *ss = &AssetsManager::getSpriteSheet(name);
    luaL_setmetatable(L, SS);
    return 1;
}

int assetsManager_getDefaultSpriteSheet(lua_State *L) {
    if (lua_gettop(L) > 0)
    THROW_ERROR(L, "invalid number of argument in 'getDefaultSpriteSheet'");
    SpriteSheet** ss = (SpriteSheet**)lua_newuserdata(L, sizeof(SpriteSheet*));
    *ss = &AssetsManager::getDefaultSpriteSheet();
    luaL_setmetatable(L, SS);
    return 1;
}

int assetsManager_getAnimation(lua_State *L) {
    if (lua_gettop(L) != 1)
    THROW_ERROR(L, "invalid number of argument in 'getAnimation'");
    std::string name = luaL_checklstring(L, -1, NULL);
    Animation** ss = (Animation**)lua_newuserdata(L, sizeof(Animation*));
    *ss = &AssetsManager::getAnimation(name);
    luaL_setmetatable(L, AN);
    return 1;
}

int assetsManager_getDefaultAnimation(lua_State *L) {
    if (lua_gettop(L) > 0)
    THROW_ERROR(L, "invalid number of argument in 'getDefaultAnimation'");
    Animation** ss = (Animation**)lua_newuserdata(L, sizeof(Animation*));
    *ss = &AssetsManager::getDefaultAnimation();
    luaL_setmetatable(L, AN);
    return 1;
}

void LuaScript::bindFunctions() {
    Debug::log("Lua", "[C++] Bind functions");

    lua_register(L, "print", lua_print);
    lua_register(L, "getButtonPressed", input_getButtonPressed);
    lua_register(L, "getDeltaTime", time_getDeltaTime);
    lua_register(L, "getSpriteSheet", assetsManager_getSpriteSheet);
    lua_register(L, "getDefaultSpriteSheet", assetsManager_getDefaultSpriteSheet);
    lua_register(L, "getAnimation", assetsManager_getAnimation);
    lua_register(L, "getDefaultAnimation", assetsManager_getDefaultAnimation);

    // GameObject type
    static const luaL_Reg go_methods[] = {
            {"getName", go_getName},
            {"getPosition", go_getPosition},
            {"setPosition", go_setPosition},
            {"getRotation", go_getRotation},
            {"setRotation", go_setRotation},
            {"setSprite", go_setSprite},
            {NULL, NULL}
    };
    luaL_newmetatable(L, GO);
    luaL_setfuncs(L, go_methods, 0);
    lua_setfield(L, -1, "__index");
    lua_register(L, GO, go_new);

    GameObject** go = (GameObject**)lua_newuserdata(L, sizeof(GameObject*));
    *go = gameObject;
    luaL_setmetatable(L, GO);
    lua_setglobal(L, "this");

    // SpriteSheet type
    luaL_newmetatable(L, SS);
    lua_setfield(L, -1, "__index");
    lua_register(L, SS, ss_new);

    // Animation type
    luaL_newmetatable(L, AN);
    lua_setfield(L, -1, "__index");
    lua_register(L, AN, an_new);
}
