//
// Created by virgil on 31/01/17.
//

#include <Parser/SceneFactory.hpp>
#include <sstream>

#define for_left(width) for (unsigned k = 0; k < width; k++)
#define for_right(width) for (int k = width - 1; k >= 0; --k)
#define for_down(height) for (int j = height - 1; j >= 0; j--)
#define for_up(height) for (unsigned j = 0; j < height; j++)
// Macro to call setTile Function
#define tileMacro(layer, k, j)                \
  unsigned tileGid = layer->GetTileGid(k, j); \
  if (tileGid != 0) setTile(tileGid, myParser->map, tileMap, k, j);
// Macros for orientation map loop
#define leftdownOrder(height, width, layer)    \
  for_down(height) {                           \
    for_left(width) { tileMacro(layer, k, j) } \
  }
#define leftupOrder(height, width, layer)      \
  for_up(height) {                             \
    for_left(width) { tileMacro(layer, k, j) } \
  }
#define rightdownOrder(height, width, layer)    \
  for_down(height) {                            \
    for_right(width) { tileMacro(layer, k, j) } \
  }
#define rightupOrder(height, width, layer)      \
  for_up(height) {                              \
    for_right(width) { tileMacro(layer, k, j) } \
  }

namespace PancakeEngine {
GameObjectFactory SceneFactory::factorySystem;

// Set animation of a gameObject
void setAnimation(GameObject &gameObject, const Tmx::Tile *tile, const Tmx::Tileset *ts) {
  std::string source = ts->GetImage()->GetSource();
  Animation &a = AssetsManager::createAnimation(gameObject.name + "AnimationMove", gameObject.name);

  for (auto frame : tile->GetFrames()) {
    // Compute position in the tile
    const unsigned i = frame.GetTileID() / (ts->GetImage()->GetWidth() / ts->GetTileWidth());
    const unsigned j = frame.GetTileID() % (ts->GetImage()->GetWidth() / ts->GetTileWidth());
    a.addFrame(i, j, frame.GetDuration());
  }

  auto &ar = gameObject.addComponent<AnimationRenderer>();
  ar.setAnimation(a);
  ar.start();
  ar.loop();
  ar.play();
}

void setCollider(GameObject &gameObject, const Tmx::Tile *tile) {
  for (const auto &k : tile->GetObjects()) {
    if (k->GetEllipse() != nullptr) {
      auto &cc = gameObject.addComponent<CircleCollider>();
      cc.radius = k->GetEllipse()->GetRadiusX();
      cc.isTrigger = true;

    } else {
      auto &bcGroundingBox = gameObject.addComponent<BoxCollider>();
      bcGroundingBox.width = k->GetWidth();
      bcGroundingBox.height = k->GetHeight();
    }
  }
}

void setTile(const unsigned gid, const Tmx::Map *map, TileMap &tileMap, const unsigned x, const unsigned y) {
  // Get tileset list
  for (const auto ts : map->GetTilesets()) {
    const int tileCount =
        ts->GetImage()->GetWidth() / ts->GetTileWidth() * (ts->GetImage()->GetHeight() / ts->GetTileHeight());
    const int maxGid = ts->GetFirstGid() + tileCount;

    if (ts->GetFirstGid() <= gid && gid < maxGid) {
      // Compute position in the tileset
      const unsigned posJ = (gid - ts->GetFirstGid()) / (ts->GetImage()->GetWidth() / ts->GetTileWidth());
      const unsigned posI = (gid - ts->GetFirstGid()) % (ts->GetImage()->GetWidth() / ts->GetTileWidth());

      const std::string source = ts->GetImage()->GetSource();
      SpriteSheet &spriteSheet = AssetsManager::createSpriteSheet(ts->GetName(), source, ts->GetTileWidth(),
                                                                  ts->GetTileHeight(), ts->GetMargin());
      tileMap.addTile(spriteSheet, posI, posJ, x, y);
      break;
    }
  }
}

void setGOComponent(const unsigned gid, const Tmx::Map *map, GameObject &gameObject) {
  auto &spriteRenderer = gameObject.addComponent<SpriteRenderer>();

  for (unsigned k = 0; k < map->GetNumTilesets(); k++) {
    const Tmx::Tileset *ts = map->GetTileset(k);

    // Get nb tile in the tileset
    int tileCount =
        ts->GetImage()->GetWidth() / ts->GetTileWidth() * (ts->GetImage()->GetHeight() / ts->GetTileHeight());
    int count = ts->GetFirstGid() + tileCount;

    if (ts->GetFirstGid() <= gid && count > gid) {
      // Compute position in the tileset
      const unsigned int j = (gid - ts->GetFirstGid()) / (ts->GetImage()->GetWidth() / ts->GetTileWidth());
      const unsigned int i = (gid - ts->GetFirstGid()) % (ts->GetImage()->GetWidth() / ts->GetTileWidth());

      const std::string source = ts->GetImage()->GetSource();
      SpriteSheet &spriteSheet =
          AssetsManager::createSpriteSheet(gameObject.name, source, ts->GetTileWidth(), ts->GetTileHeight());

      if (!ts->GetTiles().empty()) {
        // Get tile if there is animation or specific collider
        const Tmx::Tile *tile = *(ts->GetTiles().begin());

        // Add properties in a Data storage component
        if (tile->IsAnimated()) {
          setAnimation(gameObject, tile, ts);
        } else {
          spriteRenderer.setSprite(spriteSheet, i, j);
        }

        setCollider(gameObject, tile);

      } else {
        spriteRenderer.setSprite(spriteSheet, i, j);
      }
      break;
    }
  }
}

sf::Vector2f CalculGOPosition(const Tmx::Object &object) {
  sf::Vector2f v2f;
  const double radAngle = object.GetRot() * 0.017;
  double px;
  double py;
  double ox;
  double oy;

  if (object.GetGid() > 0) {
    ox = object.GetX();
    oy = object.GetY();
    px = ox + object.GetWidth() / 2.0;
    py = oy + object.GetHeight() / 2.0 - object.GetHeight();
  } else {
    ox = object.GetX();
    oy = object.GetY();
    px = ox + object.GetWidth() / 2.0;
    py = oy + object.GetHeight() / 2.0;
  }

  v2f.x = cos(radAngle) * (px - ox) - sin(radAngle) * (py - oy) + ox;
  v2f.y = sin(radAngle) * (px - ox) + cos(radAngle) * (py - oy) + oy;
  return v2f;
}
/**!
 * @brief load a GameObject
 * @param object parse from tmx file
 * @param map being parse
 */
void SceneFactory::loadObject(const Tmx::Object &object, const Tmx::Map *map) const {
  const sf::Vector2f v2f = CalculGOPosition(object);
  GameObject *gameObject;

  // Check if gameObject is in the prefabs list
  if (!factorySystem.find(object.GetName())) {
    gameObject = &scene->addGameObject<GameObject>(2);
    gameObject->name = object.GetName();
    if (object.GetName() != "MapCollider") setGOComponent(object.GetGid(), map, *gameObject);

    auto &bcGroundingBox = gameObject->addComponent<BoxCollider>();
    bcGroundingBox.width = object.GetWidth();
    bcGroundingBox.height = object.GetHeight();

  } else {
    gameObject = factorySystem.CreateNew(scene, 2, object.GetName());
  }

  gameObject->transform.setRotation(object.GetRot());
  gameObject->transform.setPosition(v2f);

  // Add properties in a Data storage component
  auto &ds = gameObject->addComponent<DataStorage>();
  ds.set("height", object.GetHeight());
  ds.set("width", object.GetWidth());

  for (const auto &pair : object.GetProperties().GetList()) {
    double d = 0;
    bool boolean = false;
    std::stringstream ss(pair.second);

    if (ss >> d) {
      ds.set(pair.first, d);
    } else if (ss >> boolean) {
      ds.set(pair.first, boolean);
    } else {
      ds.set(pair.first, pair.second);
    }
  }
}
/**!
 * @brief load a TileMap layer
 * @param layer parse from tmx file
 */
void SceneFactory::loadLayer(const Tmx::TileLayer *layer) const {
  const std::string &s = layer->GetName();
  const std::string newString = s.substr(s.find(' ') + 1);
  const unsigned nbLayer = std::stoi(newString);
  const unsigned height = layer->GetHeight();
  const unsigned width = layer->GetWidth();
  const unsigned tileWidth = myParser->map->GetTileWidth();
  const unsigned tileHeight = myParser->map->GetTileHeight();

  TileMap &tileMap = AssetsManager::createTileMap(layer->GetName() + myParser->map->GetFilename(), tileWidth,
                                                  tileHeight, width, height);

  auto &tmr = scene->addGameObject<GameObject>(nbLayer);
  sf::Vector2f v2f;
  v2f.x = width * tileWidth / 2;
  v2f.y = height * tileHeight / 2;
  tmr.transform.setPosition(v2f);
  tmr.name = layer->GetName();

  if (myParser->map->GetRenderOrder() == Tmx::MapRenderOrder::TMX_LEFT_DOWN) {
    leftdownOrder(height, width, layer);
  } else if (myParser->map->GetRenderOrder() == Tmx::MapRenderOrder::TMX_LEFT_UP) {
    leftupOrder(height, width, layer);
  } else if (myParser->map->GetRenderOrder() == Tmx::MapRenderOrder::TMX_RIGHT_DOWN) {
    rightdownOrder(height, width, layer);
  } else
    rightupOrder(height, width, layer);

  auto &t = tmr.addComponent<TileMapRenderer>();
  t.setTileMap(tileMap);
}

Scene *SceneFactory::loadAllSceneObject(const char *filename) {
  delete scene;
  delete myParser;

  scene = new Scene(filename);
  myParser = new Parser(filename);
  std::vector<Tmx::TileLayer *> layerList = myParser->loadLayer();

  if (!layerList.empty()) {
    for (auto &i : layerList) {
      loadLayer(i);
    }
  }

  std::vector<Tmx::Object> objectList = myParser->loadObjectGroups();
  if (!objectList.empty()) {
    for (const auto &i : objectList) {
      loadObject(i, myParser->map);
    }
  }

  delete myParser;
  myParser = nullptr;

  return scene;
}

}  // namespace PancakeEngine
