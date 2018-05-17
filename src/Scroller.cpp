#include <Scroller.h>

Scroller::Scroller(sf::Vector2i window_size, double scroll_speed) : window_size(window_size), scroll_speed(scroll_speed){

}

Scroller::~Scroller() {

}

void Scroller::setSprite(std::string asset_path, sf::Vector2f sprite_pos, sf::Vector2f sprite_scale)  {

    texture.loadFromFile(asset_path);
    sprite.setTexture(texture, true);

    sprite.setPosition(sprite_pos);
    sprite.setScale(sprite_scale);

}

void Scroller::render(sf::RenderWindow &window) {

    // Take sprite and shift right until x + width past screen edge

    // Tile left until x past left screen edge

    window.draw(sprite);

}

void Scroller::update(double delta_time) {

    if (sprite.getPosition().x + sprite.getGlobalBounds().width < window_size.x)
        sprite.setPosition(0, 0);
    else
        sprite.setPosition(sprite.getPosition().x - delta_time * scroll_speed, sprite.getPosition().y);

}

bool Scroller::collides(sf::FloatRect rectangle) {

    sf::FloatRect rect2 = sprite.getGlobalBounds();
    return rectangle.intersects(rect2);
}


