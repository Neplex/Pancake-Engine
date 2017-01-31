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
        MainCamera()
                :GameObject()
        {
            Camera& cm = addComponent<Camera>();
            cm.zoom(1.2);
        }
    };
}

#endif //PANCAKE_MAINCAMERA_HPP
