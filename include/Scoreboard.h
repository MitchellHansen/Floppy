#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

class Scoreboard {

public:

    Scoreboard();
    ~Scoreboard();

    void render(sf::RenderWindow &window);
    void update(double delta_time);

    bool is_visible();

private:

    std::vector<sf::Texture> small_font;
    std::vector<sf::Texture> large_font;
    std::unordered_map<std::string, sf::Texture> medals;

    std::vector<sf::Sprite> score;
    std::vector<sf::Sprite> best_score;
    sf::Sprite board;
    sf::Sprite medal;

    bool is_visible = false;
};
