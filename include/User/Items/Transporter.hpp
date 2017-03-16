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
 * \file        Transporter.hpp
 * \author      Virgil Pia - virgil.pia@gmail.com
 */

#ifndef PANCAKE_TRANSPORTER_HPP
#define PANCAKE_TRANSPORTER_HPP

#include <GameLogic.hpp>
#include <User/Behaviors/TransporterScript.hpp>

namespace PancakeEngine{
    /**
     * @class Transporter
     * @brief Create a prefab transporter
     */
    class Transporter : public GameObject{
    public:
        Transporter(std::string n) : GameObject(){
            name = n;
            BoxCollider& bc = addComponent<BoxCollider>();
            bc.width = 35;
            bc.height = 35;
            bc.offset = sf::Vector2f(0,30);
            addComponent<SpriteRenderer>().setSprite(
                    AssetsManager::getSpriteSheet("items"), 1, 3
            );
            addComponent<TransporterScript>();
        };
    };
    class Transporter1 : public Transporter { public: Transporter1() : Transporter("Transporter1") {} };
    class Transporter2 : public Transporter { public: Transporter2() : Transporter("Transporter2") {} };
    class Transporter3 : public Transporter { public: Transporter3() : Transporter("Transporter3") {} };
    class Transporter4 : public Transporter { public: Transporter4() : Transporter("Transporter4") {} };
}
#endif //PANCAKE_TRANSPORTER_HPP
