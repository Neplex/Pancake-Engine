//
// Created by virgil on 31/01/17.
//

#include <Parser/SceneFactory.hpp>
#include <sstream>

#define for_left(width) for(unsigned k = 0; k < width; k++)
#define for_right(width) for(int k = width-1; k >= 0; --k)
#define for_down(height) for(int j = height -1; j >= 0; j--)
#define for_up(height) for(unsigned j = 0; j < height; j++)
//Macro to call setTile Function
#define tileMacro(layer,k,j) unsigned tileGid = layer->GetTileGid(k,j);\
                        if (tileGid != 0)\
                            setTile(tileGid, myParser->map, tileMap, k, j, tmr);
//Macros for orientation map loop
#define leftdownOrder(height,width,layer) for_down(height) {\
                        for_left(width) {\
                            tileMacro(layer,k,j)\
                        }\
                        }
#define leftupOrder(height,width,layer) for_up(height) {\
                        for_left(width) {\
                        tileMacro(layer,k,j)\
                        }\
                        }
#define rightdownOrder(height,width,layer) for_down(height) {\
                        for_right(width) {\
                            tileMacro(layer,k,j)\
                        }\
                        }
#define rightupOrder(height,width,layer) for_up(height) {\
                        for_right(width) {\
                            tileMacro(layer,k,j)\
                        }\
                        }

namespace PancakeEngine {
    GameObjectFactory SceneFactory::factorySystem;

    //Set animation of a gameObject
    void setAnimation(GameObject &gameObject, const Tmx::Tile *tile, const Tmx::Tileset *ts) {
        const std::vector<Tmx::AnimationFrame> &frames = tile->GetFrames();
        unsigned i, j;
        std::string source = ts->GetImage()->GetSource();
        Animation &a = AssetsManager::createAnimation(gameObject.name + "AnimationMove", gameObject.name);

        for (std::vector<Tmx::AnimationFrame>::const_iterator it =
                frames.begin(); it != frames.end(); it++) {
            //Calcul position in the tile
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

    void setTile(const unsigned gid,const Tmx::Map *map,TileMap &tileMap,const unsigned x,const unsigned y, GameObject &gameObject) {
        //Get tileset list
        std::vector<Tmx::Tileset *> tileSetList = map->GetTilesets();
        unsigned posI, posJ;
        for (unsigned i = 0; i < tileSetList.size(); ++i) {
            const Tmx::Tileset *ts = tileSetList[i];
            int tilecount = (ts->GetImage()->GetWidth() / ts->GetTileWidth()) *
                            (ts->GetImage()->GetHeight() / ts->GetTileHeight());
            int maxGid = ts->GetFirstGid() + tilecount;
            if (ts->GetFirstGid() <= gid && gid < maxGid) {
                std::string source = ts->GetImage()->GetSource();
                //Calcul position in the tileset
                posJ = ((gid - ts->GetFirstGid()) / (ts->GetImage()->GetWidth() / ts->GetTileWidth()));
                posI = ((gid - ts->GetFirstGid()) % (ts->GetImage()->GetWidth() / ts->GetTileWidth()));
                SpriteSheet &spriteSheet = AssetsManager::createSpriteSheet(ts->GetName(), source,
                                                                            (unsigned) ts->GetTileWidth(),
                                                                            (unsigned) ts->GetTileHeight(),(unsigned) ts->GetMargin());
                tileMap.addTile(spriteSheet, posI, posJ, x, y);
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
            //Get nb tile in the tileset
            int tilecount = (ts->GetImage()->GetWidth() / ts->GetTileWidth()) *
                            (ts->GetImage()->GetHeight() / ts->GetTileHeight());
            int count = ts->GetFirstGid() + tilecount;
            if ((ts->GetFirstGid() <= gid) && count > gid) {
                //Calcul position in the tileset
                std::string source = ts->GetImage()->GetSource();
                j = ((gid - ts->GetFirstGid()) / (ts->GetImage()->GetWidth() / ts->GetTileWidth()));
                i = ((gid - ts->GetFirstGid()) % (ts->GetImage()->GetWidth() / ts->GetTileWidth()));
                SpriteSheet &spriteSheet = AssetsManager::createSpriteSheet(gameObject.name, source,
                                                                            (unsigned) ts->GetTileWidth(),
                                                                            (unsigned) ts->GetTileHeight());

                if (ts->GetTiles().size() > 0) {
                    //Get tile if there is animation or specific collider
                    const Tmx::Tile *tile = *(ts->GetTiles().begin());
                    //Add properties in a Data storage component
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
    // Calcul position of a gameobject in the world
    sf::Vector2f CalculGOPosition(Tmx::Object object){
        sf::Vector2f v2f;
        float px,py,ox,oy;
        float radAngle =(float) object.GetRot()* (float)0.017;
        if(object.GetGid() > 0) {
            ox = object.GetX();
            oy = object.GetY();
            px = ox + (object.GetWidth()/2);
            py = oy + (object.GetHeight()/2) - object.GetHeight();
        }else{
            ox = object.GetX();
            oy = object.GetY();
            px = ox + (object.GetWidth()/2);
            py = oy + (object.GetHeight()/2);
        }
        v2f.x = (float)cos(radAngle) * (px - ox) - (float)sin(radAngle) * (py - oy) + ox;
        v2f.y = (float)sin(radAngle) * (px - ox) + (float)cos(radAngle) * (py - oy) + oy;
        return v2f;
    }
    /**!
     * @brief load a GameObject
     * @param Tmx::Object object parse from tmx file
     * @param Tmx::Map map being parse
     */
    void SceneFactory::loadObject(Tmx::Object object, Tmx::Map *map) {
        sf::Vector2f v2f = CalculGOPosition(object);
        //Check if gameObject is in the prefabs list
        if( !factorySystem.find(object.GetName())){
            GameObject& gameObject = scene->addGameObject<GameObject>(2);
            gameObject.transform.setRotation((float)object.GetRot());
            gameObject.transform.setPosition(v2f);
            gameObject.name = object.GetName();
            if(object.GetName() != "MapCollider")
                setGOComponent((unsigned)object.GetGid(), map, gameObject);
            BoxCollider &bcGroundingBox = gameObject.addComponent<BoxCollider>();
            bcGroundingBox.width = object.GetWidth();
            bcGroundingBox.height = object.GetHeight();

            //Add properties in a Data storage component
            std::map <std::string,std::string> listP = object.GetProperties().GetList();
            DataStorage& ds = gameObject.addComponent<DataStorage>();
            ds.set("height",object.GetHeight());
            ds.set("width",object.GetWidth());
            for(std::map<std::string,std::string>::iterator it=listP.begin() ; it!=listP.end() ; ++it)
            {
                double d = 0;
                bool boolean  = false;
                std::stringstream ss(it->second);
                if( ss >> d)
                    ds.set(it->first,d);
                else if(ss >> boolean)
                    ds.set(it->first,boolean);
                else
                    ds.set(it->first,it->second);
            }
        }
        else{
            GameObject* gameObject = factorySystem.CreateNew(scene,2,object.GetName());
            gameObject->transform.setPosition(v2f);
            gameObject->transform.setRotation((float)object.GetRot());
            //Add properties in a Data storage component

            std::map <std::string,std::string> listP = object.GetProperties().GetList();
            DataStorage& ds = gameObject->addComponent<DataStorage>();
            ds.set("height",object.GetHeight());
            ds.set("width",object.GetWidth());
            for(std::map<std::string,std::string>::iterator it=listP.begin() ; it!=listP.end() ; ++it)
            {
                double d = 0;
                bool boolean  = false;
                std::stringstream ss(it->second);
                if( ss >> d)
                    ds.set(it->first,d);
                else if(ss >> boolean)
                    ds.set(it->first,boolean);
                else
                    ds.set(it->first,it->second);
            }

        }
    }
    /**!
     * @brief load a TileMap layer
     * @param Tmx::TileLayer layer parse from tmx file
     */
    void SceneFactory::loadLayer(Tmx::TileLayer *layer) {
        std::string s = layer->GetName();
        std::string newString = s.substr(s.find(' ') + 1);
        unsigned Nblayer =(unsigned) std::stoi( newString );
        unsigned height =(unsigned) layer->GetHeight();
        unsigned width =(unsigned) layer->GetWidth();
        unsigned tileWidth = (unsigned) myParser->map->GetTileWidth();
        unsigned tileHeight = (unsigned) myParser->map->GetTileHeight();
        TileMap &tileMap = AssetsManager::createTileMap(layer->GetName(), tileWidth,tileHeight, width,height);
        GameObject &tmr = scene->addGameObject<GameObject>(Nblayer);
        sf::Vector2f v2f;
        v2f.x = (width*tileWidth)/2;
        v2f.y = (height*tileHeight)/2;
        tmr.transform.setPosition(v2f);
        tmr.name  = layer->GetName();
        if(myParser->map->GetRenderOrder() == Tmx::MapRenderOrder::TMX_LEFT_DOWN) {
            leftdownOrder(height, width, layer);
        }else if(myParser->map->GetRenderOrder() == Tmx::MapRenderOrder::TMX_LEFT_UP) {
            leftupOrder(height, width, layer);
        }else if(myParser->map->GetRenderOrder() == Tmx::MapRenderOrder::TMX_RIGHT_DOWN) {
            rightdownOrder(height, width, layer);
        }else
            rightupOrder(height,width,layer);
        TileMapRenderer &t = tmr.addComponent<TileMapRenderer>();
        t.setTileMap(tileMap);
    }

    Scene* SceneFactory::loadAllSceneObject(const char* filename) {
        if(scene != NULL) delete scene;
        if(myParser != NULL) delete myParser;
        scene = new Scene(filename);
        myParser = new Parser(filename);
        std::vector<Tmx::TileLayer *> layerList = myParser->loadLayer();
        if (!layerList.empty()) {
            for (unsigned i = 0; i < layerList.size(); ++i) {
                loadLayer(layerList[i]);
            }
        }
        std::vector<Tmx::Object> objectList = myParser->loadObjectGroups();
        if (!objectList.empty()) {
            for (unsigned i = 0; i < objectList.size(); i++) {
                loadObject(objectList[i], myParser->map);
            }
        }
        return scene;
    }

}
