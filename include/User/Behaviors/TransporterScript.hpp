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
 * \file        TransporterScript.hpp
 * \author      Virgil Pia - virgil.pia@gmail.com
 */

#ifndef PANCAKE_TRANSPORTERSCRIPT_HPP
#define PANCAKE_TRANSPORTERSCRIPT_HPP

#include <GameLogic.hpp>

/**
 * @class TransporterScript
 * @brief Create a component for transporter object
 */
class TransporterScript : public PancakeEngine::Behavior {
 public:
  bool isMoved = false;
  PancakeEngine::GameObject *gameObjectCollided{};
  /**!
   * @brief Get collision between two game objects
   * @param collision component collide
   */
  void OnCollisionEnter(const PancakeEngine::Collision &collision) override {
    isMoved = true;
    gameObjectCollided = collision.otherCollider.gameObject;
  };
  /**!
   * @brief Change gameObjectCollided position after physics
   */
  void update() override {
    if (isMoved) {
      if (gameObject->name == "Transporter1") {
        PancakeEngine::GameObject const *go = PancakeEngine::SceneManager::findByName("Transporter2");
        if (go != nullptr) {
          sf::Vector2f v2f = go->transform.getWorldPosition();
          v2f.x += 70;
          gameObjectCollided->transform.setPosition(v2f);
        }

      } else if (gameObject->name == "Transporter2") {
        PancakeEngine::GameObject const *go = PancakeEngine::SceneManager::findByName("Transporter3");
        if (go != nullptr) {
          sf::Vector2f v2f = go->transform.getWorldPosition();
          v2f.x += 70;
          gameObjectCollided->transform.setPosition(v2f);
        }

      } else if (gameObject->name == "Transporter3") {
        const PancakeEngine::GameObject *go = PancakeEngine::SceneManager::findByName("Transporter1");
        if (go != nullptr) {
          sf::Vector2f v2f = go->transform.getWorldPosition();
          v2f.x += 70;
          gameObjectCollided->transform.setPosition(v2f);
        }
      }
      isMoved = false;
    }
  };
};

#endif  // PANCAKE_TRANSPORTERSCRIPT_HPP
