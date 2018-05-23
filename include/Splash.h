#pragma once
#include <SFML/Graphics.hpp>


class Splash {


public:

    Splash();
    ~Splash();

    void render(sf::RenderWindow &window);
    void update(double delta_time);
    void click();
    bool visible();

private:

    sf::Texture texture;
    sf::Sprite sprite;

    bool is_visible = true;

};
