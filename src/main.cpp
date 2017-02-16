#include <Engine.hpp>
#include <User/Sandbox.hpp>

using namespace PancakeEngine;

int main() {
    Engine * app = new Engine();
    app->sceneManager.loadScene(new Sandbox());

    InputManager::createButton("Jump", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Space}));
    InputManager::createButton("Left", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Q}));
    InputManager::createButton("Right", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::D}));
    InputManager::createButton("Duck", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::S}));

    InputManager::createButton("ShowDebugInfo", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::F1}), Debug::switchEnableDebugGUI);
    
    app->run();
    delete app;

    return EXIT_SUCCESS;
}
