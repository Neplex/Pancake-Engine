//
// Created by nicolas on 15/02/17.
//

#ifndef PANCAKE_SANDBOX_HPP
#define PANCAKE_SANDBOX_HPP

#include <GameLogic.hpp>
#include <User/Ground.hpp>
#include <User/Player.hpp>

namespace PancakeEngine {

    class Sandbox : public Scene {
    public:
        Sandbox() : Scene("Sandbox") {
            addGameObject<Ground>();
            addGameObject<Player>();
        }
    };
}

#endif //PANCAKE_SANDBOX_HPP
