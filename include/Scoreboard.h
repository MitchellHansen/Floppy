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
    void show(int score);

    bool is_visible();
    bool click();

private:

    // Textures
    std::vector<sf::Texture> small_font;
    std::vector<sf::Texture> large_font;
    std::unordered_map<std::string, sf::Texture> medals;
    sf::Texture board_texture;
    sf::Texture replay_texture;

    // Sprites
    std::vector<sf::Sprite> score;
    std::vector<sf::Sprite> best_score;
    sf::Sprite board;
    sf::Sprite medal;
    sf::Sprite replay;

    bool visible = false;
};
