//
// Created by virgil on 31/01/17.
//

#include <Parser/SceneFactory.hpp>
#include <User/Player.hpp>
#include <User/Ground.hpp>

namespace PancakeEngine{
    void CalculPositionInSprite(unsigned int gid, unsigned int firstGID, unsigned int column, unsigned int* i, unsigned int * j){
            *i = ((gid - firstGID) / column);
            *j = ((gid - firstGID) % (column));
    }
    std::string shIdle(GameObject& gameObject) {
        if(gameObject.getComponent<Rigidbody>()->getVelocity().x == 0)
            return "idle";
        else
            return "move";
    };
    void setAnimation(unsigned gid,std::vector<TMX::Parser::Tileset>::iterator itTileset,GameObject& gameObject,SpriteSheet& spriteSheet){
        Animation& animation = AssetsManager::createAnimation(itTileset->source,spriteSheet);
        std::vector<TMX::Parser::Frame> listFrame = itTileset->a.listFrame;
        //for (unsigned i = 0;  i < listFrame.size(); ++i) {
        unsigned int j, k;
        unsigned i = 0;
            k = listFrame[i].tileid / itTileset->column;
            j = listFrame[i].tileid % itTileset->column;
            animation.addFrame(k, j, listFrame[i].duration);
        //}
        Animator& ar = gameObject.addComponent<Animator>();
        ar.addAnimation("move",animation,shIdle);
    }
    void findImageOfSprite(unsigned int gid, TMX::Parser* myParser,GameObject& gameObject){
        unsigned int i,j;
        SpriteRenderer& spriteRenderer = gameObject.addComponent<SpriteRenderer>();
        std::vector<TMX::Parser::Tileset>::iterator itTileset;
        for(itTileset=myParser->tilesetList.begin();itTileset!=myParser->tilesetList.end();++itTileset) {
            if((itTileset->firstGID <= gid) && (itTileset->firstGID + itTileset->tileCount) > gid){
                std::string source = itTileset->source;
                CalculPositionInSprite(gid,itTileset->firstGID,itTileset->column,&i,&j);
                SpriteSheet& spriteSheet =  AssetsManager::createSpriteSheet(gameObject.name,source,itTileset->width,itTileset->height);
                if(gameObject.name != "Player")
                    spriteRenderer.setSprite(spriteSheet,i,j);
            }
        }
    }

    Scene& SceneFactory::loadAllGameObject(const char* filename) {

        Scene* scene = new Scene(filename);
        std::map<std::string,TMX::Parser::ObjectGroup>::iterator itObjectGroupMap;
        TMX::Parser* myParser = new TMX::Parser(filename);
        myParser->loadMapInfo();
        myParser->loadTileset();
        myParser->loadObjects();


        for(itObjectGroupMap=myParser->objectGroup.begin();itObjectGroupMap!=myParser->objectGroup.end();++itObjectGroupMap) {
            loadGameObject(*scene,itObjectGroupMap->second.object,myParser);
        }
        return *scene;
    }

    void SceneFactory::loadGameObject(Scene& scene, std::map<unsigned int, TMX::Parser::Object> object,TMX::Parser *myParser) {
        sf::Vector2f v2f;
        unsigned int i,j;
        std::map<unsigned int, TMX::Parser::Object>::iterator itObject;
        for(itObject = object.begin();itObject != object.end();++itObject) {
            if(itObject->second.name == "Player"){
                Player& player = scene.addGameObject<Player>();
                v2f.x = itObject->second.x;
                v2f.y = itObject->second.y;
                BoxCollider& bcGroundingBox = player.addComponent<BoxCollider>();
                bcGroundingBox.width = itObject->second.width;
                bcGroundingBox.height = itObject->second.height;
                player.transform.setPosition(v2f);
                findImageOfSprite(itObject->second.gid, myParser,player);
                player.setAnimation();
            }
            else{
                GameObject &gameObject = scene.addGameObject<GameObject>();
                v2f.x = itObject->second.x;
                v2f.y = itObject->second.y;
                gameObject.transform.setPosition(v2f);
                gameObject.name = itObject->second.name;
                findImageOfSprite(itObject->second.gid, myParser,gameObject);
                BoxCollider& bcGroundingBox = gameObject.addComponent<BoxCollider>();
                bcGroundingBox.width = itObject->second.width;
                bcGroundingBox.height = itObject->second.height;
            }
        }
    }

}

