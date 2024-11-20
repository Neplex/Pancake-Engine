//
// Created by virgil on 25/01/17.
//

#include <Parser/TmxParser.hpp>

bool Parser::load(const char *filename) {
  map = new Tmx::Map();
  map->ParseFile(filename);
  if (map->HasError()) return map->GetErrorCode();
  return true;
}

std::vector<Tmx::TileLayer *> Parser::loadLayer() const { return map->GetTileLayers(); }

std::vector<Tmx::Object> Parser::loadObjectGroups() const {
  std::vector<Tmx::Object> objectList;

  for (const auto objectGroup : map->GetObjectGroups()) {
    std::map<unsigned int, Tmx::Object> mapObject;

    // Iterate through all objects in the object group.
    for (const auto object : objectGroup->GetObjects()) {
      objectList.push_back(*object);
    }
  }

  return objectList;
}
