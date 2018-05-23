#include "Scoreboard.h"

Scoreboard::Scoreboard() {

    for (int i = 0; i < 10; i++){
        small_font.emplace_back(sf::Texture());
        small_font.back().loadFromFile("../Assets/font_small_" + std::to_string(i) + ".png");
    }

    for (int i = 0; i < 10; i++){
        large_font.emplace_back(sf::Texture());
        large_font.back().loadFromFile("../Assets/font_big_" + std::to_string(i) + ".png");
    }

    medals["bronze"].loadFromFile("../Assets/medal_bronze.png");
    medals["gold"].loadFromFile("../Assets/medal_gold.png");
    medals["platinum"].loadFromFile("../Assets/medal_platinum.png");
    medals["silver"].loadFromFile("../Assets/medal_silver.png");

}

Scoreboard::~Scoreboard() {

}

void Scoreboard::render(sf::RenderWindow &window) {

}

void Scoreboard::update(double delta_time) {

}

bool Scoreboard::is_visible() {
    return is_visible;
}
