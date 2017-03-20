//
// Created by nicolas on 07/03/17.
//

#include <cmath>
#include <GameLogic/Components/TileMapRenderer.hpp>
#include <Graphics/AssetsManager.hpp>

using namespace PancakeEngine;

TileMapRenderer::TileMapRenderer() {
    setTileMap(AssetsManager::getDefaultTileMap());
}

TileMapRenderer::~TileMapRenderer() {
    clearGrid();
}

void TileMapRenderer::clearGrid() {
    if (textureGrid != NULL) {
        for (int i = 0; i < nb_column; ++i) {
            for (int j = 0; j < nb_row; ++j) {
                delete textureGrid[i][j];
            }
            delete[] textureGrid[i];
        }
        delete[] textureGrid;

        textureGrid = NULL;
        chunk_width = chunk_height = nb_column = nb_row = marge_x = marge_y = 0;
    }
}

void TileMapRenderer::setTileMap(TileMap &map) {
    // Remove old map
    clearGrid();

    // Init (build the matrix of chunks)
    chunk_width  = (unsigned) floor(CHUNK_SIZE / map.tile_width ) * map.tile_width;
    chunk_height = (unsigned) floor(CHUNK_SIZE / map.tile_height) * map.tile_height;

    nb_column = map.width  * map.tile_width  / chunk_width  + 1;
    nb_row    = map.height * map.tile_height / chunk_height + 1;

    marge_x = (nb_column * chunk_width ) - (map.width  * map.tile_width );
    marge_y = (nb_row    * chunk_height) - (map.height * map.tile_height);

    textureGrid = new sf::RenderTexture** [nb_column];
    for (int i = 0; i < nb_column; ++i) {
        textureGrid[i] = new sf::RenderTexture* [nb_row];
        for (int j = 0; j < nb_row; ++j) {
            textureGrid[i][j] = new sf::RenderTexture();
            textureGrid[i][j]->create(chunk_width, chunk_height);
            textureGrid[i][j]->clear(sf::Color::Transparent);
            textureGrid[i][j]->setSmooth(true);
        }
    }

    // Draw tiles in the good chunk
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

std::vector<sf::Sprite> TileMapRenderer::getChunksSprites() {
    std::vector<sf::Sprite> sprites;
    for (int i = 0; i < nb_column; ++i) {
        for (int j = 0; j < nb_row; ++j) {
            sf::Sprite sprite(textureGrid[i][j]->getTexture());
            // Set position corresponding to the matrix position
            sprite.setPosition(
                    i * chunk_width  - (nb_column / 2.0 * chunk_width ) + marge_x / 2,
                    j * chunk_height - (nb_row    / 2.0 * chunk_height) + marge_y / 2
            );
            sprites.push_back(sprite);
        }
    }
    return sprites;
}