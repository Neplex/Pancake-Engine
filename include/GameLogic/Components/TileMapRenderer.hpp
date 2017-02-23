//
// Created by nicolas on 22/02/17.
//

#ifndef PANCAKE_TILEMAPRENDERER_HPP
#define PANCAKE_TILEMAPRENDERER_HPP

#include <GameLogic/Components/Renderer.hpp>
#include <Graphics/TileMap.hpp>

namespace PancakeEngine {

    class TileMapRenderer : public Renderer {
    public:

        TileMapRenderer() {
            texture = new sf::RenderTexture();
            setTileMap(AssetsManager::getDefaultTileMap());
        }

        ~TileMapRenderer() {
            delete texture;
        }

        void setTileMap(TileMap& map) {
            // Create texture
            // TODO: Use chunks in case of big map
            texture->create(map.width * map.tile_width, map.height * map.tile_height);
            texture->clear(sf::Color::Red);
            //texture->clear(sf::Color::Transparent);
            texture->setSmooth(true);

            // Draw tiles
            for (TileMap::Tile t : map.map) {
                sf::Sprite s = t.sheet->getSprite(t.i, t.j);
                s.setPosition(
                        t.x*map.tile_width  + map.tile_width/2,
                        t.y*map.tile_height + map.tile_height/2
                );
                texture->draw(s);
            }

            // Get sprite
            texture->display();
            sprite = sf::Sprite(texture->getTexture());
            sprite.setOrigin(sprite.getGlobalBounds().width/2, sprite.getGlobalBounds().height/2);
        }

    private:
        sf::RenderTexture* texture;
    };

}

#endif //PANCAKE_TILEMAPRENDERER_HPP
