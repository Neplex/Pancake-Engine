//
// Created by virgil on 24/01/17.
//

#ifndef PANCAKE_TMXPARSER_HPP
#define PANCAKE_TMXPARSER_HPP
#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>
#include <string>
#include <vector>
#include <utility>
#include <map>

#define VERSION "1.0"

#include "iostream"
namespace TMX
{

    class Parser
    {
    public:
        Parser( const char* filename );
        Parser();
        virtual ~Parser();

        bool load( const char* filename );
        bool loadMapInfo();
        void loadTileset();
        bool loadLayer();
        bool loadObjects();
        bool loadImage();
        struct Map {
            std::string version;
            std::string orientation;
            unsigned int width;
            unsigned int height;
            unsigned int tileWidth;
            unsigned int tileHeight;
            std::string backgroundColor;
            std::map<std::string, std::string> property;
        };



        struct Data {
            std::string encoding;
            std::string compression;
            std::string contents;
        };

        struct TileLayer {
            std::string name;
            bool visible;
            float opacity;
            Data data;
            std::map<std::string, std::string> property;
        };

        struct Object {
            std::string name;
            std::string type;
            int x;
            int y;
            unsigned int id;
            unsigned int width;
            unsigned int height;
            unsigned int gid;
            bool visible;
            std::map<std::string, std::string> property;
        };

        struct ObjectGroup {
            std::string color;
            std::string name;
            float opacity;
            bool visible;
            std::map<unsigned int, Object> object;
            std::map<std::string, std::string> property;
        };

        struct Image {
            std::string source;
            std::string transparencyColor;
        };

        struct ImageLayer {
            std::string name;
            float opacity;
            bool visible;
            std::map<std::string, std::string> property;
            Image image;
        };

        struct Frame{
            unsigned int tileid;
            unsigned int duration;
        };
        struct Animation {
            std::vector<Frame> listFrame;
        };
        struct Tileset {
            std::string name;
            unsigned int width;
            unsigned int height;
            unsigned int tileCount;
            unsigned int firstGID;
            std::string source;
            unsigned int id;
            unsigned int column;
            Animation a;
        };

        Map mapInfo;
        std::vector<Tileset> tilesetList;
        std::map<std::string, TileLayer> tileLayer;
        std::map<std::string, ObjectGroup> objectGroup;
        std::map<std::string, ImageLayer> imageLayer;
    protected:
    private:
        rapidxml::xml_node<>* root_node;
        rapidxml::xml_document<> doc;
    };

}

#endif //PANCAKE_TMXPARSER_HPP
