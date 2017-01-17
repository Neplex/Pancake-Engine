#include <SFML/Graphics.hpp>
#include "../include/Scene.hpp"

int main() {
    Scene s = Scene("TestScene");
    GameObject go = GameObject("Bajiru");
    s.addGameObject(&go);
    s.awake();
    s.start();

    s.update();
    /*while (true) {
        s.update();
        // box2D.updateWorld(time)
        s.lateUpdate();
    }*/
    return 0;
}