#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Birb {

public:

    Birb(sf::Vector2i window_size);
    ~Birb();

    // Game state
    void start();
    void reset();
    void click();

    // Updating / querying
    void render(sf::RenderWindow &window);
    void update(double delta_time);
    bool collisions(sf::Sprite top_pipe, sf::Sprite bottom_pipe, sf::Sprite ground);


    sf::Vector2f getPosition() {return sprite.getPosition();};

private:

    double speed = 0.0;
    double gravity = 7.2;
    double momentum = 0.0;
    sf::Sprite sprite;
    std::vector<sf::Texture> textures;
    sf::Vector2i window_size;

};
