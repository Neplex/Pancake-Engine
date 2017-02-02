//
// Created by virgil on 31/01/17.
//

#ifndef PANCAKE_SCENEFACTORY_HPP
#define PANCAKE_SCENEFACTORY_HPP

#include "../GameLogic/GameObject.hpp"
#include "../GameLogic/Scene.hpp"
#include "../Parser/TmxParser.hpp"
/**!
 * Create a scene from a TMX file
 */
namespace PancakeEngine {
    class SceneFactory {
    public:
        /**!
         * Load a gameObject from an object map
         * @param object
         * @return pointer on a gameObject
         */
        static void loadGameObject(Scene scene, std::map<std::string, TMX::Parser::Object> object);
        /**!
         * load all game object of a file
         * @param filename file to parse
         * @return scene of the file
         */
        static Scene loadAllGameObject(const char* filename);
    private:
        SceneFactory();
    };

}
#endif //PANCAKE_SCENEFACTORY_HPP
