//
// Created by kelle on 28/01/2017.
//

#ifndef PANCAKE_DEBUG_HPP
#define PANCAKE_DEBUG_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include "imgui/imgui-SFML.h"

class Debug {
public:

private:
    friend class Engine;
    friend class InputManager;
    friend class Window;

    static sf::RenderWindow * renderWindow; ///< The window where ImGui is drawing
    static bool initialized; ///< Set to true if debug was initialized
    static sf::Clock clock; ///< To get the delta time

    /**
     * Initiate ImGui to display debugs content.
     * @param window
     */
    static void init(sf::RenderWindow& window);
    /**
     * Update ImGui.
     */
    static void update();
    /**
     * Process an SFML event.
     * Should be called by InputManager.
     * @see InputManager
     */
    static void processEvent(sf::Event event);
    /**
     * Render ImGui things.
     */
    static void render();
    /**
     * Shutdown ImGui. Should be called at the end of the program.
     */
    static void shutDown();
};

#endif //PANCAKE_DEBUG_HPP
