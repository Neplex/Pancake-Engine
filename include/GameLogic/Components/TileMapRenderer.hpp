//
// Created by nicolas on 22/02/17.
//

#ifndef PANCAKE_TILEMAPRENDERER_HPP
#define PANCAKE_TILEMAPRENDERER_HPP

#include <GameLogic/Components/Component.hpp>
#include <Graphics/TileMap.hpp>
#include <cmath>

#define CHUNK_SIZE 512

namespace PancakeEngine {

    class TileMapRenderer : public Component {
    public:

        TileMapRenderer() {
            setTileMap(AssetsManager::getDefaultTileMap());
        }

        ~TileMapRenderer() {
            clearGrid();
        }

        void clearGrid() {
            if (textureGrid != NULL) {
                for (int i = 0; i < nb_column; ++i) {
                    for (int j = 0; j < nb_row; ++j) {
                        delete textureGrid[i][j];
                    }
                    delete textureGrid[i];
                }
                delete textureGrid;

                textureGrid = NULL;
                chunk_width = chunk_height = nb_column = nb_row = marge_x = marge_y = 0;
            }
        }

        void setTileMap(TileMap& map) {
            // Remove old map
            clearGrid();

            // Init
            chunk_width  = (unsigned) floor(CHUNK_SIZE / map.tile_width ) * map.tile_width;
            chunk_height = (unsigned) floor(CHUNK_SIZE / map.tile_height) * map.tile_height;

            nb_column = map.width  * map.tile_width  / chunk_width  + 1;
            nb_row    = map.height * map.tile_height / chunk_height + 1;

            marge_x = (nb_column * chunk_width ) - (map.width  * map.tile_width );
            marge_y = (nb_row    * chunk_height) - (map.height * map.tile_height);

            textureGrid = new sf::RenderTexture** [nb_column];
            for (int i = 0; i < nb_column; ++i) {
                textureGrid[i] = new sf::RenderTexture* [nb_column];
                for (int j = 0; j < nb_row; ++j) {
                    textureGrid[i][j] = new sf::RenderTexture();
                    textureGrid[i][j]->create(chunk_width, chunk_height);
                    textureGrid[i][j]->clear(sf::Color::Transparent);
                    textureGrid[i][j]->setSmooth(true);
                }
            }

            // Draw tiles
            for (TileMap::Tile t : map.map) {
                unsigned chunk_x = t.x / (chunk_width  / map.tile_width );
                unsigned chunk_y = t.y / (chunk_height / map.tile_height);
                sf::Sprite s = t.sheet->getSprite(t.i, t.j);
                s.setPosition(
                        t.x * map.tile_width  - (chunk_x * chunk_width ) + map.tile_width  / 2,
                        t.y * map.tile_height - (chunk_y * chunk_height) + map.tile_height / 2
                );
                textureGrid[chunk_x][chunk_y]->draw(s);
            }

            // Display textures
            for (int i = 0; i < nb_column; ++i) {
                for (int j = 0; j < nb_row; ++j) {
                    textureGrid[i][j]->display();
                }
            }
        }

        std::vector<sf::Sprite> getChunksSprites() {
            std::vector<sf::Sprite> sprites;
            for (int i = 0; i < nb_column; ++i) {
                for (int j = 0; j < nb_row; ++j) {
                    sf::Sprite sprite(textureGrid[i][j]->getTexture());
                    sprite.setPosition(
                            i * chunk_width  - (nb_column / 2.0 * chunk_width ) + marge_x / 2,
                            j * chunk_height - (nb_row    / 2.0 * chunk_height) + marge_y / 2
                    );
                    sprites.push_back(sprite);
                }
            }
            return sprites;
        }

    private:
        sf::RenderTexture*** textureGrid = NULL;
        unsigned chunk_width, chunk_height, nb_column, nb_row, marge_x, marge_y;
    };

}

#endif //PANCAKE_TILEMAPRENDERER_HPP