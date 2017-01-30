//
// Created by kelle on 26/01/2017.
//

#ifndef PANCAKE_MAINCAMERA_HPP
#define PANCAKE_MAINCAMERA_HPP

#include "../GameLogic/GameObject.hpp"
#include "../GameLogic/Components/Camera.hpp"

namespace PancakeEngine {
    class MainCamera : public GameObject {
    public:
        MainCamera(std::string name)
                :GameObject(name)
        {
            Camera* cm = new Camera();
            cm->zoom(1.2);
            addComponent(*cm);
        }
    };
}

#endif //PANCAKE_MAINCAMERA_HPP
