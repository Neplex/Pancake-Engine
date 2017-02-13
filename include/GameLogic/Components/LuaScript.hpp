//
// Created by nicolas on 02/02/17.
//

#ifndef PANCAKE_LUASCRIPT_HPP
#define PANCAKE_LUASCRIPT_HPP

#include "../../Debug/Debug.hpp"
#include "Component.hpp"
#include <lua.hpp>
#include <lualib.h>
#include <lauxlib.h>
#include <lua.h>

namespace PancakeEngine {
    /**
     * @brief Component that can run a lua script
     * All component methods will call the lua function with the same name in the current script
     */
    class LuaScript : public Component {
    public:
        /**
         * @brief Set an run a new script
         * @param uri the uri of the script
         */
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
