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


    for (int i = 0; i < 3; i++){
        score.emplace_back(sf::Sprite());
        score.back().setPosition(sf::Vector2f(100, 100));
    }

    for (int i = 0; i < 3; i++){
        best_score.emplace_back(sf::Sprite());
        best_score.back().setPosition(sf::Vector2f(100, 100));
    }

    board_texture.loadFromFile("../Assets/scoreboard.png");
    board.setTexture(board_texture);
    board.setScale(2.4, 2.4);
    board.setPosition(5, 50);

    replay_texture.loadFromFile("../Assets/replay.png");
    replay.setTexture(replay_texture);
    replay.setScale(1.7, 1.7);
    replay.setPosition(150, 600);

}

Scoreboard::~Scoreboard() {

}

void Scoreboard::render(sf::RenderWindow &window) {

    if (visible) {

        window.draw(board);
        window.draw(medal);

        for(auto sprite: score){
            window.draw(sprite);
        }

        for(auto sprite: best_score){
            window.draw(sprite);
        }

        window.draw(replay);
    }
}

void Scoreboard::update(double delta_time) {

}

bool Scoreboard::is_visible() {
    return visible;
}

bool Scoreboard::click() {
    if (visible){
        visible = false;
    }
}

void Scoreboard::show(int score) {

    int mod = 10;

    for (int i = 0; i < 3, score > 10; i++){
        int val = score % mod;
        score /= 10;
        best_score[i].setTexture(small_font[val]);
    }

    visible = true;
}
