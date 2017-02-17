#include <Engine.hpp>
#include <User/Sandbox.hpp>

using namespace PancakeEngine;

int main() {
    Engine * app = new Engine();
    app->sceneManager.loadScene(new Sandbox());

    InputManager::createButton("player1_jump", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Z}));
    InputManager::createButton("player1_right", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::D}));
    InputManager::createButton("player1_left", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Q}));
    InputManager::createButton("player1_duck", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::S}));

    InputManager::createButton("player2_jump", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Up}));
    InputManager::createButton("player2_right", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Right}));
    InputManager::createButton("player2_left", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Left}));
    InputManager::createButton("player2_duck", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::Down}));

    InputManager::createButton("player3_jump", std::vector<sf::Keyboard::Key> ({}));
    InputManager::createButton("player3_right", std::vector<sf::Keyboard::Key> ({}));
    InputManager::createButton("player3_left", std::vector<sf::Keyboard::Key> ({}));
    InputManager::createButton("player3_duck", std::vector<sf::Keyboard::Key> ({}));

    InputManager::createButton("ShowDebugInfo", std::vector<sf::Keyboard::Key> ({sf::Keyboard::Key::F1}), Debug::switchEnableDebugGUI);
    
    app->run();
    delete app;

    return EXIT_SUCCESS;
}
