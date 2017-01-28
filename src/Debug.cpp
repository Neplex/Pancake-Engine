//
// Created by kelle on 28/01/2017.
//

#include <SFML/Window/Event.hpp>
#include <iostream>
#include "../include/Debug.hpp"
#include "../include/imgui/imgui.h"
#include "../include/imgui/imgui_internal.h"
#include "../include/imgui/Widgets/AppLog.hpp"
#include "../include/Debug/MainDebugMenu.hpp"

bool Debug::initialized = false;
sf::RenderWindow * Debug::renderWindow = nullptr;
sf::Clock Debug::clock = sf::Clock();
MainDebugMenu Debug::mainDebugMenu;

void Debug::init(sf::RenderWindow& window) {
    ImGui::SFML::Init(window);
    renderWindow = &window;
    initialized = true;
}

void Debug::update()
{
    assert(initialized);
    ImGui::SFML::Update(*renderWindow, clock.restart());
}

void Debug::render()
{
    assert(initialized);
    //ImGui::ShowTestWindow();
    mainDebugMenu.draw();

    /*static AppLog log;
    bool * p_open; ///< will be set to true when the windows is close (i think)
    log.Draw("Example: Log", p_open);
    log.AddLog("Salut Vincent j'ai log ça pour toi ! :D\n");*/
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

