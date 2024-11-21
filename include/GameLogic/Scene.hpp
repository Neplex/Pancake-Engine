//
// Created by Darenn on 13/01/2017.
//

#ifndef PANCAKE_SCENE_HPP
#define PANCAKE_SCENE_HPP

#include <GameLogic/GameObject.hpp>
#include <utility>
#include <vector>

namespace PancakeEngine {

class Scene {
 public:
  std::string name;
  std::vector<GameObject *> layers;
  GameObject *gui;

  explicit Scene(std::string name) : name(std::move(name)), layers() { gui = new GameObject(); }

  ~Scene() {
    for (const GameObject *l : layers) delete l;
    delete gui;
  }

  /**
   * @brief Add the given game object to the scene (after the others) in the
   * corresponding layer.
   * @tparam T the type of gameObject.
   * @param layer the layer index (draw over lower index).
   * @return the created gameObject
   */
  template <class T>
  T &addGameObject(unsigned layer) {
    while (layers.size() <= layer) {
      layers.push_back(new GameObject());
    }

    auto *gameObject = new T();
    layers.at(layer)->addChild(*gameObject);
    toAwake.push_back(gameObject);
    return *gameObject;
  }

  /**
   * @brief Add the given game object to the scene (after the others) in the
   * corresponding layer.
   * @tparam T the type of gameObject.
   * @return the created gameObject
   */
  template <class T>
  T &addGameObjectToGui() {
    auto *gameObject = new T();
    gui->addChild(*gameObject);
    return *gameObject;
  }

  /**
   * Awake is used to initialize any variables or game state before the game
   * starts.
   */
  void awake();

  /**
   * Called just before the first Update call.
   * Call the same method on all game objects in order.
   */
  void start();

  /**
   * Called at each frame before physics.
   * Call the same method on all game objects in order.
   */
  void update();

  /**
   * Called at each frame after physics.
   * Call the same method on all game objects in order.
   */
  void lateUpdate();

 private:
  std::vector<GameObject *> toDestroy;
  std::vector<GameObject *> toAwake;
  void destroyGameObjects();
};
}  // namespace PancakeEngine

#endif  // PANCAKE_SCENE_HPP
