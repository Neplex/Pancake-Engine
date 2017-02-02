//
// Created by virgil on 31/01/17.
//

#include "../../include/Parser/SceneFactory.hpp"
#include <iterator>
#include <list>

namespace PancakeEngine{

    Scene SceneFactory::loadAllGameObject(const char* filename) {

        Scene scene(filename);
        std::map<std::string,TMX::Parser::ObjectGroup>::iterator itObjectGroupMap;
        TMX::Parser myParser = TMX::Parser(filename);

        myParser.loadObjects();

        for(itObjectGroupMap=myParser.objectGroup.begin();itObjectGroupMap!=myParser.objectGroup.end();++itObjectGroupMap) {
            loadGameObject(scene,itObjectGroupMap->second.object);
        }
        return scene;
    }

    void SceneFactory::loadGameObject(Scene scene, std::map<std::string, TMX::Parser::Object> object) {
        GameObject* gameObject = scene.addGameObject();
        sf::Vector2f v2f;

        std::map<std::string, TMX::Parser::Object>::iterator itObject;
        for(itObject = object.begin();itObject != object.end();++itObject) {
            itObject->second.name;
            v2f.x = itObject->second.x;
            v2f.y = itObject->second.y;
            gameObject->transform.setPosition(v2f);
            gameObject->name = itObject->second.name;
            //Component* component = gameObject->addComponent();
        }
    }
}

