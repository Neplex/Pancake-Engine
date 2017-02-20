//
// Created by virgil on 25/01/17.
//
#include <sstream>
#include "../../include/Parser/TmxParser.hpp"
 bool Parser::load( const char* filename ) {
        map = new Tmx::Map();
        map->ParseFile(filename);
        if (map->HasError())
        {
            printf("error code: %d\n", map->GetErrorCode());
            printf("error text: %s\n", map->GetErrorText().c_str());

            return map->GetErrorCode();
        }

    }
    bool Parser::loadMapInfo() {

    }

std::vector<Tmx::Tileset> Parser::loadTileset() {

    }
    bool Parser::loadLayer() {
    }
    bool Parser::loadImage(){
    }

    std::vector<Tmx::Object> Parser::loadObjectGroups(){
        std::vector<Tmx::Object> objectList;
        for (int i = 0; i < map->GetNumObjectGroups(); ++i) {
            const Tmx::ObjectGroup *objectGroup = map->GetObjectGroup(i);
            std::map<unsigned int, Tmx::Object> mapObject;
            // Iterate through all objects in the object group.
            for (int j = 0; j < objectGroup->GetNumObjects(); ++j) {
                // Get an object.
                const Tmx::Object *object = objectGroup->GetObject(j);
                objectList.push_back(*object);
            }
        }
        return objectList;
    }

