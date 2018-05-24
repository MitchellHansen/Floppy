#include "Splash.h"

Splash::Splash() {

    texture.loadFromFile("../Assets/splash.png");
    sprite.setTexture(texture,true);
    sprite.setScale(2.7, 2.7);
}

Splash::~Splash() {

}

void Splash::render(sf::RenderWindow &window) {
    if (is_visible)
        window.draw(sprite);
}

void Splash::update(double delta_time) {

}

void Splash::click() {
    is_visible = false;
}

bool Splash::visible() {
    return is_visible;
}
