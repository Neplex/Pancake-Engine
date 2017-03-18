//
// Created by virgil on 17/03/17.
//

#ifndef PANCAKE_USER_HPP
#define PANCAKE_USER_HPP
#include <User/Items/Rock.hpp>
#include <User/Items/Ladder.hpp>
#include <User/Items/Transporter.hpp>
#include <User/Items/Trampoline.hpp>
#include <User/Items/Water.hpp>
#include <User/GameControllerSoloObject.hpp>
#include <User/CheckPoint.hpp>
#include <User/Items/Laser.hpp>
#include <User/DeathZone.hpp>
#include <User/Enemy.hpp>
#include <User/Items/LaserButton.hpp>
#include <Parser/SceneFactory.hpp>
#include <User/Items/Coin.hpp>
#include <User/Player.hpp>
#include <User/Items/Box.hpp>
#include <User/Items/ExitNotice.hpp>

/**
 * @defgroup User User
 * Contains all classes concerning the User Prefab object.
 */
/**
 * @brief create all spritesheet, prefab and input for player
 */
void CreatePrefabAndSpriteAndInput();

#endif //PANCAKE_USER_HPP
