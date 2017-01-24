#include "../include/SpriteRenderer.hpp"
#include "../include/Window.hpp"
#include "../include/Camera.hpp"
#include "../include/Engine.hpp"

int main() {
    Engine * engine = new Engine();
    engine->run();
    delete engine;
    return EXIT_SUCCESS;
}