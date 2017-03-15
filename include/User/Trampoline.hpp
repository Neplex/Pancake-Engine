/*
     Copyright (C) 2016-2017 Pia Virgil - virgil.pia@gmail.com

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
 * \file        Trampoline.hpp
 * \author      Virgil Pia - virgil.pia@gmail.com
 */

#ifndef PANCAKE_TRAMPOLINE_HPP
#define PANCAKE_TRAMPOLINE_HPP

#include <GameLogic.hpp>
#include <User/Behaviors/TrampolineScript.hpp>

namespace PancakeEngine{
    /**
     * @class Transporter
     * @brief Create a prefab trampoline
     */
    class Trampoline : public GameObject{
    public:
        Trampoline() : GameObject(){
            name = "Trampoline";
            BoxCollider& bcBottom = addComponent<BoxCollider>();
            bcBottom.width = 70;
            bcBottom.height = 30;
            bcBottom.offset = sf::Vector2f(0,20);
            bcBottom.density = 15;
            BoxCollider& bcTop = addComponent<BoxCollider>();
            bcTop.width = 60;
            bcTop.height = 10;
            bcTop.offset = sf::Vector2f(0,0);
            bcTop.density = 15;
            bcTop.bounciness = 1.1;
            transform.setPosition(sf::Vector2f(100, -100));
            transform.setRotation(0);

            addComponent<SpriteRenderer>().setSprite(
                    AssetsManager::getSpriteSheet("items"), 0, 6
            );
            addComponent<TrampolineScript>();
        }
    };
}
#endif //PANCAKE_TRAMPOLINE_HPP
