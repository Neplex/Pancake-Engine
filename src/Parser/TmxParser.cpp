//
// Created by virgil on 25/01/17.
//
#include "../../include/Parser/TmxParser.hpp"
namespace TMX {

    Parser::Parser( const char* filename ) {
        load( filename );
    }

    Parser::Parser(){}

    Parser::~Parser() {}

    bool Parser::load( const char* filename ) {
        std::string version = VERSION;
        rapidxml::file<> file(filename);
        doc.parse<0>(file.data());
        //get root nodes
        root_node = doc.first_node("map");

        //load map element
        if (root_node->first_attribute("version")->value() != version) {
            return false;
        }
    }
    bool Parser::loadMapInfo() {
        mapInfo.version = root_node->first_attribute("version")->value();
        mapInfo.orientation = root_node->first_attribute("orientation")->value();
        mapInfo.width = (unsigned int) std::atoi(root_node->first_attribute("width")->value());
        mapInfo.height = (unsigned int) std::atoi(root_node->first_attribute("height")->value());
        mapInfo.tileWidth = (unsigned int) std::atoi(root_node->first_attribute("tilewidth")->value());
        mapInfo.tileHeight = (unsigned int) std::atoi(root_node->first_attribute("tileheight")->value());

        if (root_node->first_attribute("backgroundcolor")->value() != 0) {
            mapInfo.backgroundColor = root_node->first_attribute("backgroundcolor")->value();
        }

        if (root_node->first_node("properties") != 0) {
            for (rapidxml::xml_node<> *properties_node = root_node->first_node("properties")->first_node(
                    "property"); properties_node; properties_node = properties_node->next_sibling()) {
                mapInfo.property[properties_node->first_attribute("name")->value()] = properties_node->first_attribute(
                        "value")->value();
            }
        }
        return true;
    }
    void Parser::loadTileset() {
        Tileset tmpTileset;
        for (rapidxml::xml_node<> *tileset_node = root_node->first_node(
                "tileset"); tileset_node; tileset_node = tileset_node->next_sibling("tileset")) {
            tmpTileset.firstGID = (unsigned int) std::atoi(tileset_node->first_attribute("firstgid")->value());
            tmpTileset.source = tileset_node->first_attribute("source")->value();
            tilesetList.push_back(tmpTileset);
        }
    }
    bool Parser::loadLayer() {
        for (rapidxml::xml_node<> *layer_node = root_node->first_node(
                "layer"); layer_node; layer_node = layer_node->next_sibling("layer")) {
            TileLayer layer;
            layer.name = layer_node->first_attribute("name")->value();

            if (layer_node->first_node("properties") != 0) {
                for (rapidxml::xml_node<> *properties_node = layer_node->first_node("properties")->first_node(
                        "property"); properties_node; properties_node = properties_node->next_sibling()) {
                    layer.property[properties_node->first_attribute(
                            "name")->value()] = properties_node->first_attribute("value")->value();
                }
                for (std::map<std::string, std::string>::iterator it = mapInfo.property.begin();
                     it != mapInfo.property.end(); ++it) {
                }
            }

            rapidxml::xml_node<> *data_node = layer_node->first_node("data");
            layer.data.encoding = data_node->first_attribute("encoding")->value();
            if (data_node->first_attribute("compression") > 0) {
                layer.data.compression = data_node->first_attribute("compression")->value();
            }
            layer.data.contents = data_node->value();
            tileLayer[layer.name] = layer;
        }
        return true;
    }
    bool Parser::loadObjects() {
        for (rapidxml::xml_node<> *oGroup_node = root_node->first_node(
                "objectgroup"); oGroup_node; oGroup_node = oGroup_node->next_sibling("objectgroup")) {
            ObjectGroup oGroup;
            oGroup.color = oGroup_node->first_attribute("color")->value();
            oGroup.name = oGroup_node->first_attribute("name")->value();
            oGroup.opacity = (float) std::atof(oGroup_node->first_attribute("opacity")->value());
            oGroup.visible =  (bool) std::atoi(oGroup_node->first_attribute("visible")->value());
            if (oGroup_node->first_node("properties") != 0) {
                for (rapidxml::xml_node<> *properties_node = oGroup_node->first_node("properties")->first_node(
                        "property"); properties_node; properties_node = properties_node->next_sibling()) {
                    oGroup.property[properties_node->first_attribute(
                            "name")->value()] = properties_node->first_attribute("value")->value();
                }
            }

            objectGroup[oGroup.name] = oGroup;
        }
        return true;
    }
    bool Parser::loadImage(){
        for( rapidxml::xml_node<>* image_node = root_node->first_node( "imagelayer" ); image_node; image_node = image_node->next_sibling( "imagelayer" ) ) {
            ImageLayer imgLayer;
            imgLayer.name = image_node->first_attribute( "name" )->value();
            if( image_node->first_attribute( "opacity" ) != 0 ) {
                imgLayer.opacity = (float) std::atof(image_node->first_attribute("opacity" )->value() );
            }

            imgLayer.visible = (unsigned int) std::atoi( image_node->first_attribute( "visible" )->value() );

            imgLayer.image.source = image_node->first_node( "image" )->first_attribute( "source" )->value();

            if( image_node->first_node( "image" )->first_attribute( "trans" ) != 0 ) {
                imgLayer.image.transparencyColor = image_node->first_node( "image" )->first_attribute( "trans" )->value();
            }

            if( image_node->first_node( "properties" ) != 0 ) {
                for( rapidxml::xml_node<>* properties_node = image_node->first_node( "properties" )->first_node( "property" ); properties_node; properties_node = properties_node->next_sibling( "property" ) ) {
                    imgLayer.property[properties_node->first_attribute( "name" )->value()] = properties_node->first_attribute( "value" )->value();
                }

                for( std::map<std::string, std::string>::iterator it = imgLayer.property.begin(); it != imgLayer.property.end(); ++it ) {
                    std::cout << "-> " << it->first << " : " << it->second << std::endl;
                }
            }

            imageLayer[imgLayer.name] = imgLayer;
        }

        return true;
    }
}
