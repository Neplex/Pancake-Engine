//
// Created by kelle on 28/01/2017.
//

#include <SFML/Window/Event.hpp>
#include <Debug/Widgets/Console.hpp>
#include "Debug/Debug.hpp"
#include "Imgui/imgui_internal.h"

using namespace PancakeEngine;

bool Debug::initialized = false;
sf::RenderWindow * Debug::renderWindow = nullptr;
Window* Debug::window = nullptr;
sf::Clock Debug::clock = sf::Clock();
MainDebugMenu Debug::mainDebugMenu;
FixedOverlayDebug Debug::fixedOverlayDebug;
bool Debug::displayDebug = false;

void Debug::init(sf::RenderWindow& rwin, Window& win) {
    ImGui::SFML::Init(rwin);
    window = &win;
    //win.setDebug(true);
    renderWindow = &rwin;
    initialized = true;
}

void Debug::update()
{
    if (initialized) {
        ImGui::SFML::Update(*renderWindow, clock.restart());
    }
}

void Debug::render()
{
    if (!initialized)
        return;
    //ImGui::ShowTestWindow();
    if (displayDebug) {
        mainDebugMenu.draw();
        fixedOverlayDebug.draw(nullptr);
    }
    ImGui::Render();
}

void Debug::shutDown()
{
    if (initialized)
        ImGui::SFML::Shutdown();
}

void Debug::processEvent(sf::Event event)
{
    if (initialized)
        ImGui::SFML::ProcessEvent(event);
}

