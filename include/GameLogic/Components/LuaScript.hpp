//
// Created by nicolas on 02/02/17.
//

#ifndef PANCAKE_LUASCRIPT_HPP
#define PANCAKE_LUASCRIPT_HPP

#include "../../Debug/Debug.hpp"
#include "Component.hpp"
#include <lauxlib.h>
#include <lua.hpp>
#include <lualib.h>

namespace PancakeEngine {
    class LuaScript : public Component {
    public:
        void setScript(std::string uri);

        void awake();
        void start();
        void update();
        void lateUpdate();

    private:
        friend class GameObject;

        lua_State *L;

        LuaScript();
        ~LuaScript();

        void bindFunctions();
    };
}

#endif // PANCAKE_LUASCRIPT_HPP
