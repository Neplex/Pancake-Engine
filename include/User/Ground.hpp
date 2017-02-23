//
// Created by kelle on 26/01/2017.
//

#ifndef PANCAKE_GROUND_HPP
#define PANCAKE_GROUND_HPP

#include <GameLogic.hpp>
#include <Graphics.hpp>

#define SIZE 70
#define WIDTH 60
#define HEIGHT 6

namespace PancakeEngine {
    class Ground : public GameObject {
    public:
        Ground() : GameObject() {
            name = "Ground";

            BoxCollider& collider = addComponent<BoxCollider>();
            collider.height = HEIGHT * SIZE;
            collider.width = SIZE * WIDTH;

            SpriteSheet& sheet = AssetsManager::getSpriteSheet("tiles");

            TileMap& tileMap = AssetsManager::createTileMap("ground", SIZE, SIZE, WIDTH, HEIGHT);
            for (unsigned x = 0; x < WIDTH; ++x) tileMap.addTile(sheet, 2, 6, x, 0);
            for (unsigned x = 0; x < WIDTH; ++x)
                for (unsigned y = 1; y < HEIGHT; ++y) tileMap.addTile(sheet, 4, 7, x, y);

            addComponent<TileMapRenderer>().setTileMap(tileMap);
        }

    };
}

#endif //PANCAKE_GROUND_HPP
