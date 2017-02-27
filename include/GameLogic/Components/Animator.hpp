/*
     Copyright (C) 2016-2017 Nicolas Hiot - nicolashiot@hotmail.com

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

/**
 * \file        Animator.hpp
 * \author      Nicolas Hiot - nicolashiot@hotmail.com
 */

#ifndef PANCAKE_ANIMATOR_HPP
#define PANCAKE_ANIMATOR_HPP

#include <map>
#include "AnimationRenderer.hpp"

namespace PancakeEngine {

    /**
     * @class Animator
     * @brief An animator display a list of animations and switch between.
     * @sa Component Animation
     */
    class Animator : public Renderer {
    public:
        ~Animator();

        /**
         * @brief Add animation
         * @param name the name of the state
         * @param animation the animation of the state
         * @param handler the handler of the state
         */
        void addAnimation(std::string name, Animation& animation, std::string (*handler)(GameObject&));

        /**
         * @brief Flip the animation
         * @param b True to flip animation
         */
        void flip(bool b = true);

        /**
         * @brief Get the animation associate with the current GameObject state
         * @return the current animation
         */
        const AnimationRenderer* getCurrentAnimation() const;

        void update() override;

        const sf::Sprite getSprite() const override;

    private:
        /**
         * @brief Structure use to store an animator state
         */
        struct State {
            AnimationRenderer * animation;
            std::string (*handler)(GameObject&);
        };
        std::map<std::string, State> states; ///< The list of states
        std::string currentState = ""; ///< Name of the current state
        bool isFlip = false;
    };
}

#endif //PANCAKE_ANIMATOR_HPP
