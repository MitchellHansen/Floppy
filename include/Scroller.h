#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class Scroller {

public:

    Scroller(double scroll_speed);
    ~Scroller();

    /* Perform animation / movement in relation to the elapsed delta_time of the frame */
    void update(double delta_time);

    /* Render the sprite to the RenderWindow. Optionally allow the sprite
     * to take care of tiling across the screen e.g the background */
    void render(sf::RenderWindow &window, bool tiling);

    /* Check to see if the incoming rectangle collides with the sprites rectangle */
    bool collides(sf::FloatRect rectangle);

    /* The sprite isn't bound to a texture in the constructor. So we must initialize it here */
    void setSprite(std::string asset_path, sf::Vector2f sprite_pos, sf::Vector2f sprite_scale);

private:

    sf::Sprite sprite;
    sf::Vector2f normalized_position;

    /* Speed at which the sprite will scroll across the screen. May be set negative
     * to scroll in the rightward direction */
    double scroll_speed;

    /* Pipes will be deleted as they scroll off screen and re instanced randomly
     * again on the right. Reloading the texture each time would be bad so lets keep a cache */
    static std::unordered_map<std::string, sf::Texture> texture_cache;
};