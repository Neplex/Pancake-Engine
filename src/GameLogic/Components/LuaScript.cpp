//
// Created by nicolas on 03/02/17.
//

#include "../../../include/GameLogic/Components/LuaScript.hpp"
#include "../../../include/GameLogic/Components/SpriteRenderer.hpp"
#include "../../../include/GameLogic/Components/AnimationRenderer.hpp"
#include "../../../include/Graphics/AssetsManager.hpp"
#include "../../../include/Inputs/Input.hpp"
#include "../../../include/Time.hpp"
#include <GameLogic/Components/Camera.hpp>
#include <sstream>

#define GAME_OBJECT "GameObject"
#define SPRITE_SHEET "SpriteSheet"
#define ANIMATION "Animation"
#define SPRITE_RENDERER "SpriteRenderer"
#define CAMERA "Camera"
#define ANIMATION_RENDERER "AnimationRenderer"
#define RIGIDBODY "Rigidbody"

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

#define NEW_LUA_TYPE(L, name, methods)                                         \
  {                                                                            \
    luaL_newmetatable(L, name);                                                \
    luaL_setfuncs(L, methods, 0);                                              \
    lua_setfield(L, -1, "__index");                                            \
  }

#define GET_COMPONENT(typeName, className)                                     \
  if (type == typeName) {                                                      \
    *ptr = (*go)->getComponent<className>();                                   \
    luaL_setmetatable(L, typeName);                                            \
    if (*ptr == NULL) *ptr = &(*go)->addComponent<className>();                \
  } else

using namespace PancakeEngine;

LuaScript::LuaScript() : Behavior() {
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

int input_getButtonHeld(lua_State *L) {
    if (lua_gettop(L) != 1) THROW_ERROR(L,
                                        "invalid number of argument in 'getButtonHeld'");
    lua_pushboolean(L, Input::getButtonHeld(luaL_checklstring(L, 1, NULL)));
    return 1;
}

int time_getDeltaTime(lua_State *L) {
    if (lua_gettop(L) != 0)
    THROW_ERROR(L, "invalid number of argument in 'getDeltaTime'");
    lua_pushnumber(L, Time::getDeltaTime());
    return 1;
}

int assetsManager_getSpriteSheet(lua_State *L) {
    if (lua_gettop(L) != 1)
    THROW_ERROR(L, "invalid number of argument in 'getSpriteSheet'");
    std::string name = luaL_checklstring(L, -1, NULL);
    SpriteSheet **ss = (SpriteSheet **)lua_newuserdata(L, sizeof(SpriteSheet *));
    *ss = &AssetsManager::getSpriteSheet(name);
    luaL_setmetatable(L, SPRITE_SHEET);
    return 1;
}

int assetsManager_getDefaultSpriteSheet(lua_State *L) {
    if (lua_gettop(L) != 0)
    THROW_ERROR(L, "invalid number of argument in 'getDefaultSpriteSheet'");
    SpriteSheet **ss = (SpriteSheet **)lua_newuserdata(L, sizeof(SpriteSheet *));
    *ss = &AssetsManager::getDefaultSpriteSheet();
    luaL_setmetatable(L, SPRITE_SHEET);
    return 1;
}

int assetsManager_getAnimation(lua_State *L) {
    if (lua_gettop(L) != 1)
    THROW_ERROR(L, "invalid number of argument in 'getAnimation'");
    std::string name = luaL_checklstring(L, -1, NULL);
    Animation **ss = (Animation **)lua_newuserdata(L, sizeof(Animation *));
    *ss = &AssetsManager::getAnimation(name);
    luaL_setmetatable(L, ANIMATION);
    return 1;
}

int assetsManager_getDefaultAnimation(lua_State *L) {
    if (lua_gettop(L) != 0)
    THROW_ERROR(L, "invalid number of argument in 'getDefaultAnimation'");
    Animation **ss = (Animation **)lua_newuserdata(L, sizeof(Animation *));
    *ss = &AssetsManager::getDefaultAnimation();
    luaL_setmetatable(L, ANIMATION);
    return 1;
}

int spriteSheet_new(lua_State *L) {
    if (lua_gettop(L) != 4)
    THROW_ERROR(L, "invalid number of argument in constructor of 'SpriteSheet(name, uri, width, height)'");
    std::string name = luaL_checklstring(L, -4, NULL);
    std::string uri = luaL_checklstring(L, -3, NULL);
    unsigned w = (unsigned)luaL_checkinteger(L, -2);
    unsigned h = (unsigned)luaL_checkinteger(L, -1);
    SpriteSheet **ss = (SpriteSheet **)lua_newuserdata(L, sizeof(SpriteSheet *));
    *ss = &AssetsManager::createSpriteSheet(name, uri, w, h);
    luaL_setmetatable(L, SPRITE_SHEET);
    return 1;
}

int animation_new(lua_State *L) {
    if (lua_gettop(L) != 2)
    THROW_ERROR(L, "invalid number of argument in constructor of 'Animation(name, spriteSheet)'");
    std::string name = luaL_checklstring(L, -2, NULL);
    SpriteSheet **ss = (SpriteSheet **)luaL_checkudata(L, -1, SPRITE_SHEET);
    Animation **an = (Animation **)lua_newuserdata(L, sizeof(Animation *));
    *an = &AssetsManager::createAnimation(name, **ss);
    luaL_setmetatable(L, ANIMATION);
    return 1;
}

int animation_addFrame(lua_State *L) {
    if (lua_gettop(L) != 4)
    THROW_ERROR(L, "invalid number of argument in 'addFrame'");
    Animation **a = (Animation **)luaL_checkudata(L, -4, ANIMATION);
    unsigned i = (unsigned)luaL_checkinteger(L, -3);
    unsigned j = (unsigned)luaL_checkinteger(L, -2);
    unsigned t = (unsigned)luaL_checkinteger(L, -1);
    (*a)->addFrame(i, j, t);
    return 0;
}

int gameObject_new(lua_State *L) {
    if (lua_gettop(L) != 0)
    THROW_ERROR(L, "invalid number of argument in constructor of 'GameObject()'");
    GameObject **go = (GameObject **)lua_newuserdata(L, sizeof(GameObject *));
    *go = NULL; // TODO: add new GameObject to the current scene
    luaL_setmetatable(L, GAME_OBJECT);
    return 1;
}

int gameObject_getName(lua_State *L) {
    if (lua_gettop(L) != 1)
    THROW_ERROR(L, "invalid number of argument in 'getName'");
    GameObject **go = (GameObject **)luaL_checkudata(L, -1, GAME_OBJECT);
    lua_pushstring(L, (*go)->name.c_str());
    return 1;
}

int gameObject_getPosition(lua_State *L) {
    if (lua_gettop(L) != 1)
    THROW_ERROR(L, "invalid number of argument in 'getPosition'");
    GameObject **go = (GameObject **)luaL_checkudata(L, -1, GAME_OBJECT);
    sf::Vector2f pos = (*go)->transform.getPosition();
    lua_pushnumber(L, pos.x);
    lua_pushnumber(L, pos.y);
    return 2;
}

int gameObject_setPosition(lua_State *L) {
    if (lua_gettop(L) != 3)
    THROW_ERROR(L, "invalid number of argument in 'setPosition'");
    GameObject **go = (GameObject **)luaL_checkudata(L, -3, GAME_OBJECT);
    float x = (float)luaL_checknumber(L, -2);
    float y = (float)luaL_checknumber(L, -1);
    (*go)->transform.setPosition(sf::Vector2f(x, y));
    return 0;
}

int gameObject_getRotation(lua_State *L) {
    if (lua_gettop(L) != 1)
    THROW_ERROR(L, "invalid number of argument in 'getPosition'");
    GameObject **go = (GameObject **)luaL_checkudata(L, -1, GAME_OBJECT);
    lua_pushnumber(L, (*go)->transform.getRotation());
    return 1;
}

int gameObject_setRotation(lua_State *L) {
    if (lua_gettop(L) != 2)
    THROW_ERROR(L, "invalid number of argument in 'setRotation'");
    GameObject **go = (GameObject **)luaL_checkudata(L, -2, GAME_OBJECT);
    float a = (float)luaL_checknumber(L, -1);
    (*go)->transform.setRotation(a);
    return 0;
}

int gameObject_getComponent(lua_State *L) {
    if (lua_gettop(L) != 2)
    THROW_ERROR(L, "invalid number of argument in 'getComponent'");
    GameObject **go = (GameObject **)luaL_checkudata(L, -2, GAME_OBJECT);
    std::string type = luaL_checklstring(L, -1, NULL);
    void **ptr = (void **)lua_newuserdata(L, sizeof(void *));

    GET_COMPONENT(SPRITE_RENDERER, SpriteRenderer)
    GET_COMPONENT(ANIMATION_RENDERER, AnimationRenderer)
    GET_COMPONENT(CAMERA, Camera)
    GET_COMPONENT(RIGIDBODY, Rigidbody)
    {
        std::stringstream err;
        err << "invalid component type '" << type.c_str() << "'";
        THROW_ERROR(L, err.str().c_str());
    }
    return 1;
}

int spriteRenderer_setSprite(lua_State *L) {
    if (lua_gettop(L) != 4)
    THROW_ERROR(L, "invalid number of argument in 'setSprite'");
    SpriteRenderer **sr = (SpriteRenderer **)luaL_checkudata(L, -4, SPRITE_RENDERER);
    SpriteSheet **ss = (SpriteSheet **)luaL_checkudata(L, -3, SPRITE_SHEET);
    unsigned i = (unsigned)luaL_checkinteger(L, -2);
    unsigned j = (unsigned)luaL_checkinteger(L, -1);
    (*sr)->setSprite(**ss, i, j);
    return 0;
}

int camera_zoom(lua_State *L) {
    if (lua_gettop(L) != 2)
    THROW_ERROR(L, "invalid number of argument in 'zoom'");
    Camera **c = (Camera **)luaL_checkudata(L, -2, CAMERA);
    float f = (float)luaL_checknumber(L, -1);
    (*c)->zoom(f);
    return 0;
}

int animationRenderer_setAnimation(lua_State *L) {
    if (lua_gettop(L) != 2)
    THROW_ERROR(L, "invalid number of argument in 'setAnimation'");
    AnimationRenderer **ar = (AnimationRenderer **)luaL_checkudata(L, -2, ANIMATION_RENDERER);
    Animation **a = (Animation **)luaL_checkudata(L, -1, ANIMATION);
    (*ar)->setAnimation(**a);
    return 0;
}

int animationRenderer_play(lua_State *L) {
    if (lua_gettop(L) != 1)
    THROW_ERROR(L, "invalid number of argument in 'play'");
    AnimationRenderer **ar = (AnimationRenderer **)luaL_checkudata(L, -1, ANIMATION_RENDERER);
    (*ar)->play();
    return 0;
}

int animationRenderer_pause(lua_State *L) {
    if (lua_gettop(L) != 1)
    THROW_ERROR(L, "invalid number of argument in 'pause'");
    AnimationRenderer **ar = (AnimationRenderer **)luaL_checkudata(L, -1, ANIMATION_RENDERER);
    (*ar)->pause();
    return 0;
}

int animationRenderer_stop(lua_State *L) {
    if (lua_gettop(L) != 1)
    THROW_ERROR(L, "invalid number of argument in 'stop'");
    AnimationRenderer **ar = (AnimationRenderer **)luaL_checkudata(L, -1, ANIMATION_RENDERER);
    (*ar)->stop();
    return 0;
}

int animationRenderer_loop(lua_State *L) {
    if (lua_gettop(L) < 1 && lua_gettop(L) > 2)
    THROW_ERROR(L, "invalid number of argument in 'loop'");
    if (lua_gettop(L) == 1) {
        AnimationRenderer **ar = (AnimationRenderer **)luaL_checkudata(L, -1, ANIMATION_RENDERER);
        (*ar)->loop();
    } else {
        AnimationRenderer **ar = (AnimationRenderer **)luaL_checkudata(L, -2, ANIMATION_RENDERER);
        if (!lua_isboolean(L, -1))
        THROW_ERROR(L, "second argument must be a boolean in 'loop'");
        bool b = (bool)lua_toboolean(L, -1);
        (*ar)->loop(b);
    }
    return 0;
}

int rigidbody_getVelocity(lua_State *L) {
    if (lua_gettop(L) != 1) THROW_ERROR(L,
                                        "invalid number of argument in 'getVelocity'");
    Rigidbody **rb = (Rigidbody **) luaL_checkudata(L, -1, RIGIDBODY);
    lua_pushnumber(L, (*rb)->getVelocity().x);
    lua_pushnumber(L, (*rb)->getVelocity().y);
    return 2;
}

int rigidbody_applyLinearImpulse(lua_State *L) {
    if (lua_gettop(L) != 3) THROW_ERROR(L,
                                        "invalid number of argument in 'applyLinearImpulse'");
    Rigidbody **rb = (Rigidbody **) luaL_checkudata(L, -3, RIGIDBODY);
    float x = (float) luaL_checknumber(L, -2);
    float y = (float) luaL_checknumber(L, -1);
    (*rb)->applyLinearImpulse(sf::Vector2f(x, y));
    return 0;
}

int rigidbody_getMass(lua_State *L) {
    if (lua_gettop(L) != 1) THROW_ERROR(L,
                                        "invalid number of argument in 'getMass'");
    Rigidbody **rb = (Rigidbody **) luaL_checkudata(L, -1, RIGIDBODY);
    lua_pushnumber(L, (*rb)->getMass());
    return 0;
}

void LuaScript::bindFunctions() {
    Debug::log("Lua", "[C++] Bind functions");

    lua_register(L, "print", lua_print);
    lua_register(L, "getButtonPressed", input_getButtonPressed);
    lua_register(L, "getButtonHeld", input_getButtonHeld);
    lua_register(L, "getDeltaTime", time_getDeltaTime);
    lua_register(L, "getSpriteSheet", assetsManager_getSpriteSheet);
    lua_register(L, "getDefaultSpriteSheet", assetsManager_getDefaultSpriteSheet);
    lua_register(L, "getAnimation", assetsManager_getAnimation);
    lua_register(L, "getDefaultAnimation", assetsManager_getDefaultAnimation);

    // SpriteSheet type
    static const luaL_Reg spriteSheet_methods[] = {
            {NULL, NULL}
    };
    NEW_LUA_TYPE(L, SPRITE_SHEET, spriteSheet_methods);
    lua_register(L, SPRITE_SHEET, spriteSheet_new);

    // Animation type
    static const luaL_Reg animation_methods[] = {
            {"addFrame", animation_addFrame},
            {NULL, NULL}
    };
    NEW_LUA_TYPE(L, ANIMATION, animation_methods);
    lua_register(L, ANIMATION, animation_new);

    // SpriteRenderer type
    static const luaL_Reg spriteRenderer_methods[] = {
            {"setSprite", spriteRenderer_setSprite},
            {NULL, NULL}
    };
    NEW_LUA_TYPE(L, SPRITE_RENDERER, spriteRenderer_methods);

    // AnimationRenderer type
    static const luaL_Reg animationRenderer_methods[] = {
            {"setAnimation", animationRenderer_setAnimation},
            {"play", animationRenderer_play},
            {"pause", animationRenderer_pause},
            {"stop", animationRenderer_stop},
            {"loop", animationRenderer_loop},
            {NULL, NULL}
    };
    NEW_LUA_TYPE(L, ANIMATION_RENDERER, animationRenderer_methods);

    // Camera type
    static const luaL_Reg camera_methods[] = {
            {"zoom", camera_zoom},
            {NULL, NULL}
    };
    NEW_LUA_TYPE(L, CAMERA, camera_methods);

    // Rigidbody type
    static const luaL_Reg rigidbody_methods[] = {
            {"getVelocity",        rigidbody_getVelocity},
            {"applyLinearImpulse", rigidbody_applyLinearImpulse},
            {"getMass",            rigidbody_getMass},
            {NULL, NULL}
    };
    NEW_LUA_TYPE(L, RIGIDBODY, rigidbody_methods);

    // GameObject type
    static const luaL_Reg gameObject_methods[] = {
            {"getName", gameObject_getName},
            {"getPosition", gameObject_getPosition},
            {"setPosition", gameObject_setPosition},
            {"getRotation", gameObject_getRotation},
            {"setRotation", gameObject_setRotation},
            {"getComponent", gameObject_getComponent},
            {NULL, NULL}
    };
    NEW_LUA_TYPE(L, GAME_OBJECT, gameObject_methods);
    lua_register(L, GAME_OBJECT, gameObject_new);

    GameObject **go = (GameObject **)lua_newuserdata(L, sizeof(GameObject *));
    *go = gameObject;
    luaL_setmetatable(L, GAME_OBJECT);
    lua_setglobal(L, "this");
}
