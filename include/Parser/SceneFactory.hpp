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

#include <GameLogic/GameObject.hpp>
#include <GameLogic/Scene.hpp>
#include <Parser/TmxParser.hpp>
#include <User/Player.hpp>
#include <User/Coin.hpp>
#include <User/Box.hpp>

namespace PancakeEngine {

    class GOFactory
    {
    public:
        virtual GameObject* CreateNew(Scene* scene, unsigned layer) const = 0;
    };

    template <typename T>
    class Factory : public GOFactory
    {
    public:
        T* CreateNew(Scene* scene, unsigned layer) const { return &(scene->addGameObject<T>(layer)); }
    };

    class GameObjectFactory
    {
    private:
        typedef std::map<std::string, GOFactory*> FactoryMap;
        FactoryMap factoryMap;

    public:
        ~GameObjectFactory()
        {
            FactoryMap::const_iterator map_item = factoryMap.begin();
            for (; map_item != factoryMap.end(); ++map_item) delete map_item->second;
            factoryMap.clear();
        }

        template <typename T>
        void AddFactory(const std::string& name)
        {
            delete factoryMap[name];
            factoryMap[name] = new Factory<T>();
        }

        bool find(std::string name){
            auto search = factoryMap.find(name);
            return search != factoryMap.end();
        }
        GameObject* CreateNew(Scene* scene, unsigned layer,const std::string& name) const
        {
            FactoryMap::const_iterator found = factoryMap.find(name);
            if (found != factoryMap.end())
                return found->second->CreateNew(scene,layer);
            else
                return NULL;
        }
    };
    /**
     * @class SceneFactory
     * @brief Use to create a scene from a file.
     */
    class SceneFactory {
    public:
        template <class T>
        static void addPrefab(std::string param){
            SceneFactory::factorySystem.AddFactory<T>(param);
        };
        /**!
         * @brief Create a SceneFactory object
         * @param filename file to be parse
         */
        SceneFactory(){};
        /**!
         * @brief load all objects of a TMX file
         * @param filename file to parse
         * @return scene of the file
         */
        Scene *loadAllSceneObject(const char* filename);
        /**!
         * @brief load a GameObject
         * @param Tmx::Object object parse from tmx file
         * @param Tmx::Map map being parse
         */
        void loadObject(Tmx::Object object, Tmx::Map *map);
        /**!
         * @brief load a TileMap layer
         * @param Tmx::TileLayer layer parse from tmx file
         */
        void loadLayer(Tmx::TileLayer *layer);
        static GameObjectFactory factorySystem; ///< the factory for prefab objects

    private:
        Scene* scene=NULL; ///< the scene being created
        Parser *myParser = NULL; ///< the parser to parse the file

    };

}
#endif //PANCAKE_SCENEFACTORY_HPP
