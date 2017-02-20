//
// Created by virgil on 24/01/17.
//

#ifndef PANCAKE_TMXPARSER_HPP
#define PANCAKE_TMXPARSER_HPP
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <Tmx.h>
#include "iostream"

class Parser
{
public:
    Parser( const char* filename ){load( filename );};
    Parser(){};
    virtual ~Parser(){delete map;};

    bool load( const char* filename );
    bool loadMapInfo();
    std::vector<Tmx::Tileset> loadTileset();
    bool loadLayer();
    bool loadImage();
    Tmx::Map * map;
    std::vector<Tmx::Object> loadObjectGroups();

};


#endif //PANCAKE_TMXPARSER_HPP
