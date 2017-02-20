//
// Created by virgil on 31/01/17.
//

#include <Parser/SceneFactory.hpp>
#include <User/Player.hpp>
#include <User/Coin.hpp>
#include <User/Ground.hpp>
#include <User/Box.hpp>

namespace PancakeEngine{
    SceneFactory::SceneFactory() {

    }
    void setAnimation(GameObject& gameObject,const Tmx::Tile* tile,const Tmx::Tileset* ts){
        const std::vector<Tmx::AnimationFrame> &frames = tile->GetFrames();
        unsigned i,j;
        std::string source = ts->GetImage()->GetSource();
        Animation &a = AssetsManager::createAnimation(gameObject.name + "AnimationMove", gameObject.name);

        for (std::vector<Tmx::AnimationFrame>::const_iterator it =
                frames.begin(); it != frames.end(); it++)
        {
            i = (it->GetTileID() / (ts->GetImage()->GetWidth()/ts->GetTileWidth()));
            j = (it->GetTileID() % (ts->GetImage()->GetWidth()/ts->GetTileWidth()));
            it->GetTileID();
            a.addFrame(i,j,it->GetDuration());
        }
            AnimationRenderer &ar = gameObject.addComponent<AnimationRenderer>();
            ar.setAnimation(a);
            ar.start();
            ar.loop();
            ar.play();
    }
    void setCollider(GameObject& gameObject,const Tmx::Tile* tile){
        std::vector<Tmx::Object*> objectList = tile->GetObjects();
        for(unsigned k = 0 ; k < objectList.size();k++){
            if(objectList[k]->GetEllipse() != NULL){
                CircleCollider& cc = gameObject.addComponent<CircleCollider>();
                cc.radius = objectList[k]->GetEllipse()->GetRadiusX();
                cc.isTrigger = true;
            }
            else{
                BoxCollider& bcGroundingBox = gameObject.addComponent<BoxCollider>();
                bcGroundingBox.width = objectList[k]->GetWidth();
                bcGroundingBox.height = objectList[k]->GetHeight();
            }
        }
    }

    void setGOComponent(unsigned int gid, Tmx::Map * map,GameObject& gameObject){
        unsigned int i,j;
        SpriteRenderer& spriteRenderer = gameObject.addComponent<SpriteRenderer>();
        int nbTileset = map->GetNumTilesets();
        for(unsigned k = 0; k < nbTileset; k++) {
            const Tmx::Tileset *ts = map->GetTileset(k);
            int count = ts->GetFirstGid() + ts->GetColumns();
            if((ts->GetFirstGid() <= gid) && count > gid){
                std::string source = ts->GetImage()->GetSource();
                i = ((gid - ts->GetFirstGid()) / (ts->GetImage()->GetWidth()/ts->GetTileWidth()));
                j = ((gid - ts->GetFirstGid()) % (ts->GetImage()->GetWidth()/ts->GetTileWidth()));
                SpriteSheet& spriteSheet =  AssetsManager::createSpriteSheet(gameObject.name,source,(unsigned ) ts->GetTileWidth(),(unsigned )ts->GetTileHeight());
                if(ts->GetTiles().size() > 0){
                    const Tmx::Tile *tile = *(ts->GetTiles().begin());
                    if(tile->IsAnimated())
                        setAnimation(gameObject,tile,ts);
                    else
                        spriteRenderer.setSprite(spriteSheet,i,j);
                    setCollider(gameObject,tile);
                }
                else
                    spriteRenderer.setSprite(spriteSheet,i,j);
            }
        }
    }
    void SceneFactory::loadObject(Scene& scene,Tmx::Object object, Tmx::Map * map) {
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
        if(object.GetName() == "Player"){
            Player& player = scene.addGameObject<Player>();
            v2f.x = object.GetX();
            v2f.y = object.GetY();
            player.transform.setPosition(v2f);
        }
        else if(object.GetName() == "Coin"){
            Coin& coin = scene.addGameObject<Coin>();
            v2f.x = object.GetX();
            v2f.y = object.GetY();
            coin.transform.setPosition(v2f);
            setGOComponent(object.GetGid(),map,coin);
        }
        else{
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

    }
    Scene SceneFactory::loadAllGameObject(const char* filename) {
        Scene scene(filename);
        Parser* myParser = new Parser(filename);
        /*factory_map["Player"] = &(scene.addGameObject<Player>());
        factory_map["Coin"] = &(scene.addGameObject<Coin>());*/


        myParser->loadMapInfo();
        std::vector<Tmx::Object> objectList = myParser->loadObjectGroups();
        for(unsigned i = 0; i < objectList.size();i++){
            loadObject(scene,objectList[i],myParser->map);
        }

        return scene;
    }
}

