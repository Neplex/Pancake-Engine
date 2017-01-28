//
// Created by kelle on 28/01/2017.
//

#include <SFML/Window/Event.hpp>
#include <iostream>
#include "../include/Debug.hpp"
#include "../include/imgui/imgui.h"
#include "../include/imgui/imgui_internal.h"

bool Debug::initialized = false;
sf::RenderWindow * Debug::renderWindow = nullptr;
sf::Clock Debug::clock = sf::Clock();

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
    ImGui::Begin("Hello, world!");
    if (ImGui::Button("Look at this pretty button")) {
        std::cout << "ahah";
    }
    ImGui::End();
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
