#include <SFML/Graphics.hpp>


class Scroller {

public:

    Scroller(sf::Vector2i window_size, double scroll_speed);
    ~Scroller();

    void update(double delta_time);
    void render(sf::RenderWindow &window);

    bool collides(sf::FloatRect rectangle);

    void setSprite(std::string asset_path, sf::Vector2f sprite_pos, sf::Vector2f sprite_scale);

private:

    sf::Texture texture;
    sf::Sprite sprite;

    sf::Vector2f window_size;
    double scroll_speed;
};