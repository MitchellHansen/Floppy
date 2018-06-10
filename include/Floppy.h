#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Scoreboard.h"
#include "Scroller.h"
#include "Splash.h"
#include "Birb.h"

class Floppy {

public:

    /* Create new instance or return current one */
    static std::shared_ptr<Floppy> getInstance();

    /* Given coords based on a 9:16 (900:1600 pixel) screen, scale to
     * whatever window_scale the program is at
     */
    static sf::Vector2f getScaledCoords(sf::Vector2f normalized_position);
    static sf::Vector2i getScaledCoords(sf::Vector2i normalized_position);
    static sf::Vector2u getScaledCoords(sf::Vector2u normalized_position);

    /* Each sprite will have a different scaling, but we need to keep
     * these consistent with the window_scale that the program has */
    static sf::Vector2f getScaledScale(sf::Vector2f scale);
    static sf::Vector2i getScaledScale(sf::Vector2i scale);
    static sf::Vector2u getScaledScale(sf::Vector2u scale);

    /* Set the new scaling percentage and resize the window.
     * Sprites will scale on each render call */
    void setScreenScale(sf::Vector2f scale);

    /* Loop which exits when the user closes the window */
    void loop();

    /* All update operations happen during this step.
     * delta_time being the time since the last frame */
    void update(double delta_time);

    /* All rendering operations happen during this step */
    void render();

private:

    /* Since we're doing a singleton type pattern, we need to
     * keep these hidden from the user */
    Floppy();
    ~Floppy(){};

    /* Returns the time since the first invocation in seconds */
    static float elapsedTime();

    /* The current instance, populated during the first getInstance() call */
    static std::shared_ptr<Floppy> instance;

    /* Default initializers for the screen size */
    static const sf::Vector2i BASE_WINDOW_SIZE;
    static const sf::Vector2f DEFAULT_SCREEN_SCALE;

    /* Percentage of the normalized window */
    static sf::Vector2f window_scale = DEFAULT_SCREEN_SCALE;

    /* Using the window scale, set the size of the window on alloc */
    sf::Vector2i window_size = getScaledCoords(BASE_WINDOW_SIZE);

    sf::RenderWindow window;

    /* Sprite wrappers which implement their unique functionality */
    Birb birb;
    Splash splash;
    Scoreboard scoreboard;
    Scroller background;
    Scroller ground;
    std::vector<Scroller> pipes;
};
