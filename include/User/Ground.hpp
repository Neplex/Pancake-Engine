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

    class Ground : public PancakeEngine::GameObject {
    public:
        Ground() : GameObject() {
            name = "Ground";

            PancakeEngine::BoxCollider& collider = addComponent<PancakeEngine::BoxCollider>();
            collider.height = HEIGHT * SIZE;
            collider.width = SIZE * WIDTH;

            PancakeEngine::SpriteSheet& sheet = PancakeEngine::AssetsManager::getSpriteSheet("tiles");

            PancakeEngine::TileMap& tileMap = PancakeEngine::AssetsManager::createTileMap("ground", SIZE, SIZE, WIDTH, HEIGHT);
            for (unsigned x = 0; x < WIDTH; ++x) tileMap.addTile(sheet, 2, 6, x, 0);
            for (unsigned x = 0; x < WIDTH; ++x)
                for (unsigned y = 1; y < HEIGHT; ++y) tileMap.addTile(sheet, 4, 7, x, y);

            addComponent<PancakeEngine::TileMapRenderer>().setTileMap(tileMap);
        }

    };

#endif //PANCAKE_GROUND_HPP
