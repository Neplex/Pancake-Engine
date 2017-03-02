//
// Created by virgil on 31/01/17.
//

#include <Parser/SceneFactory.hpp>
#include <User/Player.hpp>
#include <User/Coin.hpp>


namespace PancakeEngine {
    SceneFactory::SceneFactory() {

    }

    void setAnimation(GameObject &gameObject, const Tmx::Tile *tile, const Tmx::Tileset *ts) {
        const std::vector<Tmx::AnimationFrame> &frames = tile->GetFrames();
        unsigned i, j;
        std::string source = ts->GetImage()->GetSource();
        Animation &a = AssetsManager::createAnimation(gameObject.name + "AnimationMove", gameObject.name);

        for (std::vector<Tmx::AnimationFrame>::const_iterator it =
                frames.begin(); it != frames.end(); it++) {
            i = (unsigned) (it->GetTileID() / (ts->GetImage()->GetWidth() / ts->GetTileWidth()));
            j = (unsigned) (it->GetTileID() % (ts->GetImage()->GetWidth() / ts->GetTileWidth()));
            it->GetTileID();
            a.addFrame(i, j, it->GetDuration());
        }
        AnimationRenderer &ar = gameObject.addComponent<AnimationRenderer>();
        ar.setAnimation(a);
        ar.start();
        ar.loop();
        ar.play();
    }

    void setCollider(GameObject &gameObject, const Tmx::Tile *tile) {
        std::vector<Tmx::Object *> objectList = tile->GetObjects();
        for (unsigned k = 0; k < objectList.size(); k++) {
            if (objectList[k]->GetEllipse() != NULL) {
                CircleCollider &cc = gameObject.addComponent<CircleCollider>();
                cc.radius = objectList[k]->GetEllipse()->GetRadiusX();
                cc.isTrigger = true;
            } else {
                BoxCollider &bcGroundingBox = gameObject.addComponent<BoxCollider>();
                bcGroundingBox.width = objectList[k]->GetWidth();
                bcGroundingBox.height = objectList[k]->GetHeight();
            }
        }
    }

    void setTile(unsigned gid, Tmx::Map *map, TileMap &tileMap, unsigned x, unsigned y, GameObject &gameObject) { ;
        std::vector<Tmx::Tileset *> tileSetList = map->GetTilesets();
        unsigned posI, posJ;
        for (unsigned i = 0; i < tileSetList.size(); ++i) {
            const Tmx::Tileset *ts = tileSetList[i];
            int tilecount = (ts->GetImage()->GetWidth() / ts->GetTileWidth()) *
                            (ts->GetImage()->GetHeight() / ts->GetTileHeight());
            int maxGid = ts->GetFirstGid() + tilecount;
            if (ts->GetFirstGid() <= gid && gid < maxGid) {
                std::string source = ts->GetImage()->GetSource();
                posI = ((gid - ts->GetFirstGid()) / (ts->GetImage()->GetWidth() / ts->GetTileWidth()));
                posJ = ((gid - ts->GetFirstGid()) % (ts->GetImage()->GetWidth() / ts->GetTileWidth()));
                SpriteSheet &spriteSheet = AssetsManager::createSpriteSheet(ts->GetName(), source,
                                                                            (unsigned) ts->GetTileWidth(),
                                                                            (unsigned) ts->GetTileHeight());
                tileMap.addTile(spriteSheet, posI, posJ, x, y);
                if (ts->GetTiles().size() > 0) {
                    const Tmx::Tile *tile = *(ts->GetTiles().begin());
                    setCollider(gameObject, tile);
                }
                break;
            }
        }
    }

    void setGOComponent(unsigned gid, Tmx::Map *map, GameObject &gameObject) {
        unsigned int i, j;
        SpriteRenderer &spriteRenderer = gameObject.addComponent<SpriteRenderer>();
        int nbTileset = map->GetNumTilesets();
        for (unsigned k = 0; k < nbTileset; k++) {
            const Tmx::Tileset *ts = map->GetTileset(k);
            int tilecount = (ts->GetImage()->GetWidth() / ts->GetTileWidth()) *
                            (ts->GetImage()->GetHeight() / ts->GetTileHeight());
            int count = ts->GetFirstGid() + tilecount;
            if ((ts->GetFirstGid() <= gid) && count > gid) {
                std::string source = ts->GetImage()->GetSource();
                i = ((gid - ts->GetFirstGid()) / (ts->GetImage()->GetWidth() / ts->GetTileWidth()));
                j = ((gid - ts->GetFirstGid()) % (ts->GetImage()->GetWidth() / ts->GetTileWidth()));
                SpriteSheet &spriteSheet = AssetsManager::createSpriteSheet(gameObject.name, source,
                                                                            (unsigned) ts->GetTileWidth(),
                                                                            (unsigned) ts->GetTileHeight());
                if (ts->GetTiles().size() > 0) {
                    const Tmx::Tile *tile = *(ts->GetTiles().begin());
                    if (tile->IsAnimated())
                        setAnimation(gameObject, tile, ts);
                    else
                        spriteRenderer.setSprite(spriteSheet, i, j);
                    setCollider(gameObject, tile);
                } else
                    spriteRenderer.setSprite(spriteSheet, i, j);
                break;
            }
        }
    }

    void loadObject(Scene &scene, Tmx::Object object, Tmx::Map *map) {
        sf::Vector2f v2f;
        /*if( factory_map.find(object.GetName()) == factory_map.end()){
            GameObject& gameObject = scene.addGameObject<GameObject>();
            v2f.x = object.GetX();
            v2f.y = object.GetY();
            gameObject.transform.setPosition(v2f);
            gameObject.name = object.GetName();
            setGOComponent(object.GetGid(), map, gameObject);
            BoxCollider &bcGroundingBox = gameObject.addComponent<BoxCollider>();
            bcGroundingBox.width = object.GetWidth();
            bcGroundingBox.height = object.GetHeight();
        }
        else{
            GameObject* gameObject = factory_map[object.GetName()];
            v2f.x = object.GetX();
            v2f.y = object.GetY();
            gameObject->transform.setPosition(v2f);
            if(object.GetName() == "Coin"){
                setGOComponent(object.GetGid(),map, *gameObject);
            }
        }*/
        if (object.GetName() == "Player") {
            Player &player = scene.addGameObject<Player1>(1);
            v2f.x = object.GetX();
            v2f.y = object.GetY();
            player.transform.setPosition(v2f);
        } else if (object.GetName() == "Coin") {
            Coin &coin = scene.addGameObject<Coin>(1);
            v2f.x = object.GetX();
            v2f.y = object.GetY();
            coin.transform.setPosition(v2f);
        }else if (object.GetName() == "MapCollider") {
            GameObject &go = scene.addGameObject<GameObject>(1);
            v2f.x = object.GetX();
            v2f.y = object.GetY();
            go.transform.setPosition(v2f);
            BoxCollider &bcGroundingBox = go.addComponent<BoxCollider>();
            bcGroundingBox.width = object.GetWidth();
            bcGroundingBox.height = object.GetHeight();
        } else {
            GameObject &gameObject = scene.addGameObject<GameObject>(1);
            v2f.x = object.GetX();
            v2f.y = object.GetY();
            gameObject.transform.setPosition(v2f);
            gameObject.name = object.GetName();
            setGOComponent((unsigned) object.GetGid(), map, gameObject);
            BoxCollider &bcGroundingBox = gameObject.addComponent<BoxCollider>();
            bcGroundingBox.width = object.GetWidth();
            bcGroundingBox.height = object.GetHeight();
        }

    }

    void loadLayer(Scene *scene, Tmx::TileLayer *layer, Parser *myParser) {
        int height = layer->GetHeight();
        int width = layer->GetWidth();
        TileMap &tileMap = AssetsManager::createTileMap(layer->GetName(), (unsigned) myParser->map->GetTileWidth(),
                                                        (unsigned) myParser->map->GetTileHeight(), (unsigned) height,
                                                        (unsigned) width);

        GameObject &tmr = scene->addGameObject<GameObject>(1);
        tmr.name  = layer->GetName();
        for (unsigned j = 0; j < height; ++j) {
            for (unsigned k = 0; k < width; ++k) {
                unsigned tileGid = layer->GetTileGid(k, j);
                if (tileGid > 0) {
                    setTile(tileGid, myParser->map, tileMap, k, j, tmr);
                }
            }
        }
        TileMapRenderer &t = tmr.addComponent<TileMapRenderer>();
        t.setTileMap(tileMap);
    }

/**!
     * load all objects of a TMX file
     * @param filename file to parse
     * @return scene of the file
    */
    Scene SceneFactory::loadAllSceneObject(const char *filename) {
        Scene scene(filename);
        Parser *myParser = new Parser(filename);
        /*factory_map["Player"] = &(scene.addGameObject<Player1>(1));
        factory_map["Coin"] = &(scene.addGameObject<Coin>(1));*/

        std::vector<Tmx::TileLayer *> layerList = myParser->loadLayer();
        /*if (!layerList.empty()) {
            for (unsigned i = 0; i < layerList.size(); ++i) {
                loadLayer(&scene, layerList[i], myParser);
            }
        }*/
        std::vector<Tmx::Object> objectList = myParser->loadObjectGroups();
        if (!objectList.empty()) {
            for (unsigned i = 0; i < objectList.size(); i++) {
                loadObject(scene, objectList[i], myParser->map);
            }
        }
        return scene;
    }

}
