//
// Created by nicolas on 24/01/17.
//

#ifndef PANCAKE_CAMERA_HPP
#define PANCAKE_CAMERA_HPP

#include <SFML/Graphics/View.hpp>
#include "Component.hpp"
#include "../../Graphics/Window.hpp"

namespace PancakeEngine {

/**
 * Attach camera on a game object
 */
    class Camera : public Component {
    public:
        Camera();

        /**
         * Zoom view with factor
         * @param factor
         */
        void zoom(float factor);
        static Camera* mainCamera;

    private:
        friend class Window;
        sf::View view;

    };
}
#endif //PANCAKE_CAMERA_HPP
