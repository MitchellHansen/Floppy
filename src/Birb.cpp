#include <iostream>
#include "Birb.h"


Birb::Birb(sf::Vector2i window_size) : window_size(window_size), textures(4, sf::Texture()) {

    // Init flappy
    for (int i = 0; i < 4; i++) {
        textures[i].loadFromFile("../Assets/bird.png", sf::IntRect(0, i*24, 34, 24));
    }

    sprite.setTexture(textures[0],true);
    sprite.setOrigin(sprite.getTextureRect().width/2.0f, sprite.getTextureRect().width/2.0f);

    reset();
}

Birb::~Birb() {

}

void Birb::start() {
    running = true;
}

void Birb::reset() {
    sprite.setPosition(window_size.x / 2, window_size.y / 2);
    momentum = -2;
    running = false;
}

void Birb::click() {
    running = true;
    momentum = -2;
}

void Birb::render(sf::RenderWindow &window) {
    window.draw(sprite);
}

void Birb::update(double delta_time) {

    if (running) {
        momentum += gravity * delta_time; // Impart gravity

        sf::Vector2f f_pos = sprite.getPosition();
        f_pos.y += momentum;

        sprite.setPosition(f_pos);
        sprite.setRotation(momentum * 10);
    }
}

bool Birb::collisions(sf::Sprite top_pipe, sf::Sprite bottom_pipe, sf::Sprite ground) {

    sf::Vector2f f_pos = sprite.getPosition();
    sf::FloatRect f_rec = sprite.getGlobalBounds();
    sf::Vector2f b_pos = bottom_pipe.getPosition();
    sf::FloatRect b_rec = bottom_pipe.getGlobalBounds();
    sf::Vector2f t_pos = top_pipe.getPosition();
    sf::FloatRect t_rec = top_pipe.getGlobalBounds();

    bool collision = false;

    // Ground collision
    if (f_pos.y > ground.getPosition().y) {
        collision = true;
    }

    // Pipe collision
    if (b_pos.x + b_rec.width > f_pos.x  && // right side of pipe greater than left of floppy
        f_pos.x + f_rec.width > b_pos.x  && // right side of floppy greater than left of pipe
        (f_pos.y < t_pos.y - t_rec.height || // floppy top greater than top pipe
        b_pos.y < f_pos.y + f_rec.height )){ // floppy bottom less than bottom pipe

        collision = true;
    }

    if (collision)
        reset();

    return collision;
}
