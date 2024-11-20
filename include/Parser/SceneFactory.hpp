/*
     Copyright (C) 2016-2017 Pia Virgil - virgil.pia@gmail.com

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

/**
 * \file        SceneFactory.hpp
 * \author      Virgil Pia - virgil.pia@gmail.com
 */

#ifndef PANCAKE_SCENEFACTORY_HPP
#define PANCAKE_SCENEFACTORY_HPP

#include <Tmx.h>

#include <GameLogic.hpp>
#include <Parser/TmxParser.hpp>

namespace PancakeEngine {
/**
 * @class GOFactory
 * @brief Interface to create GameObjectFactory
 */
class GOFactory {
 public:
  virtual ~GOFactory() = default;

  virtual GameObject *CreateNew(Scene *scene, unsigned layer) const = 0;
};

template <typename T>
class Factory : public GOFactory {
 public:
  T *CreateNew(Scene *scene, unsigned layer) const override { return &(scene->addGameObject<T>(layer)); }
};
/**
 * @class GameObjectFactory
 * @brief Use to create prefab map
 */
class GameObjectFactory {
  using FactoryMap = std::map<std::string, GOFactory *>;

  FactoryMap factoryMap;  // Map which contains all prefabs

 public:
  /**!
   * @brief Destroy a GameObjectFactory object
   * Clear factoryMap objects
   */
  ~GameObjectFactory() {
    for (FactoryMap::const_iterator map_item = factoryMap.begin(); map_item != factoryMap.end(); ++map_item) {
      delete map_item->second;
    }
    factoryMap.clear();
  }
  /**!
   * @brief Add a prefab to the factoryMap
   * @param name of the prefab object
   */
  template <typename T>
  void AddFactory(const std::string &name) {
    delete factoryMap[name];
    factoryMap[name] = new Factory<T>();
  }
  /**!
   * @brief find a prefab in the map
   * @param name of the prefab object
   */
  bool find(std::string const &name) {
    auto search = factoryMap.find(name);
    return search != factoryMap.end();
  }
  /**!
   * @brief Create a new prefab in the map
   * @param scene where to create the prefab
   * @param layer which layer is the object
   * @param name of the prefab
   */
  GameObject *CreateNew(Scene *scene, const unsigned layer, const std::string &name) const {
    auto found = factoryMap.find(name);
    return found != factoryMap.end() ? found->second->CreateNew(scene, layer) : nullptr;
  }
};

/**
 * @class SceneFactory
 * @brief Use to create a scene from a file.
 */
class SceneFactory {
 public:
  template <class T>

  static void addPrefab(const std::string &param) {
    factorySystem.AddFactory<T>(param);
  }

  /**!
   * @brief load all objects of a TMX file
   * @param filename file to parse
   * @return scene of the file
   */
  Scene *loadAllSceneObject(const char *filename);
  /**!
   * @brief load a GameObject
   * @param object parse from tmx file
   * @param map being parse
   */
  void loadObject(const Tmx::Object &object, const Tmx::Map *map) const;
  /**!
   * @brief load a TileMap layer
   * @param layer parse from tmx file
   */
  void loadLayer(const Tmx::TileLayer *layer) const;
  static GameObjectFactory factorySystem;  ///< the factory for prefab objects

 private:
  Scene *scene = nullptr;      ///< the scene being created
  Parser *myParser = nullptr;  ///< the parser to parse the file
};

}  // namespace PancakeEngine
#endif  // PANCAKE_SCENEFACTORY_HPP
