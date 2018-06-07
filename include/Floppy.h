#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class Floppy {

public:

    // scaled coords based on a 9:16 (900:1600 pixel) screen space
    static sf::Vector2f getScaledCoords(sf::Vector2f normalized_position);
    static void setScreenScale(float percentage);

    static std::shared_ptr<Floppy> getInstace();

    void loop();
    void render();
    void update(double delta_time);

private:

    Floppy();
    ~Floppy(){};

    static float elapsed_time();

    static std::shared_ptr<Floppy> instance;
    static const sf::Vector2i BASE_WINDOW_SIZE;
    static const sf::Vector2i DEFAULT_SCREEN_SCALE;

    sf::RenderWindow window;
    sf::Vector2i window_size;

    Birb birb;
    Splash splash;
    Scoreboard scoreboard;

    Scroller background;
    Scroller ground;

    std::vector<Scroller> pipes;
};
