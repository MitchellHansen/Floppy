#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <chrono>
#include <list>
#include "Scroller.h"
#include "Birb.h"

#ifdef linux
#elif defined _WIN32
#elif defined TARGET_OS_MAC
#endif

const float g = 7.8;
const int WINDOW_X = 600;
const int WINDOW_Y = 800;

float elap_time() {
	static std::chrono::time_point<std::chrono::system_clock> start;
	static bool started = false;

	if (!started) {
		start = std::chrono::system_clock::now();
		started = true;
	}

	std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_time = now - start;
	return static_cast<float>(elapsed_time.count());
}

int main()
{
	std::mt19937 rng(time(NULL));
	std::uniform_int_distribution<int> rgen(100, 400);

	int pipe_dist = 200;

	sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "flappy");

    sf::Vector2i window_size(WINDOW_X, WINDOW_Y);

    Birb birb(window_size);

    Scroller background_scroller(window_size, 10.0);
    background_scroller.setSprite("../Assets/sky.png", sf::Vector2f(0, 0), sf::Vector2f(8, 8));
    Scroller land_scroller(window_size, 10.0);
    land_scroller.setSprite("../Assets/land.png", sf::Vector2f(0, window_size.y - 30), sf::Vector2f(3, 2));

    std::list<Scroller> pipes;

    pipes.emplace_back(Scroller(window_size, 100.0));
    pipes.back().setSprite("../Assets/pipe-up.png", sf::Vector2f(30, 30), sf::Vector2f(1.1,1.1));

	sf::Texture land = sf::Texture(); land.loadFromFile("../Assets/land.png");
	sf::Sprite land_sprite(land); 
    land_sprite.setPosition(0, WINDOW_Y - WINDOW_Y / 10);
    land_sprite.setScale(3, 2);
	sf::Texture pipe_up, pipe_down = sf::Texture(); pipe_down.loadFromFile("../Assets/pipe-down.png"); pipe_up.loadFromFile("../Assets/pipe-up.png");
	sf::Sprite pipe_up_sprite = sf::Sprite(pipe_up); sf::Sprite pipe_down_sprite = sf::Sprite(pipe_down);
	sf::Texture pipe_shaft = sf::Texture(); pipe_shaft.loadFromFile("../Assets/pipe.png");
	sf::Sprite pipe_shaft_sprite = sf::Sprite(pipe_shaft);


	float step_size = 0.005f;
	double frame_time = 0.0, elapsed_time = 0.0, delta_time = 0.0, accumulator_time = 0.0, current_time = 0.0;
	float speed = 250;

	while (window.isOpen())
	{
		sf::Event event; // Handle input
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) 
				window.close();
			if (event.type == sf::Event::MouseWheelScrolled)
				if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
					speed += event.mouseWheelScroll.delta * 20;
			if(event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Space)
					birb.click();
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Right)
					pipe_dist -= 10;
				if (event.mouseButton.button == sf::Mouse::Middle)
					pipe_dist += 10;
				if (event.mouseButton.button == sf::Mouse::Left)
					birb.click();
			}
		}

		elapsed_time = elap_time(); // Handle time
		delta_time = elapsed_time - current_time;
		current_time = elapsed_time;
		if (delta_time > 0.02f)
			delta_time = 0.02f;
		accumulator_time += delta_time;

		while ((accumulator_time - step_size) >= step_size) { // While the frame has sim time, update 
			accumulator_time -= step_size;

            birb.update(step_size);
            background_scroller.update(step_size);
            land_scroller.update(step_size);

            for (auto pipe: pipes){
                pipe.update(step_size);
            }

//            // place the top and bottom pipe heads
//			if (pipe_down_sprite.getPosition().x < -pipe_down_sprite.getGlobalBounds().width) {
//				pipe_down_sprite.setPosition(WINDOW_X, rgen(rng));
//				pipe_up_sprite.setPosition(WINDOW_X, pipe_down_sprite.getPosition().y + pipe_dist);
//			}
//			else {
//				pipe_up_sprite.setPosition(pipe_up_sprite.getPosition().x - step_size * speed, pipe_up_sprite.getPosition().y);
//				pipe_down_sprite.setPosition(pipe_down_sprite.getPosition().x - step_size * speed, pipe_down_sprite.getPosition().y);
//			}

            if (land_scroller.collides(birb.getBounds()))
                birb.reset();
		}


        background_scroller.render(window, false);

        for (auto pipe: pipes){
            pipe.render(window, false);
        }

        land_scroller.render(window, false);

        birb.render(window);

		//window.draw(pipe_up_sprite);
		//window.draw(pipe_down_sprite);
//
//		pipe_shaft_sprite.setPosition(pipe_up_sprite.getPosition()); // Render the bottom pipe
//		int y_pos = pipe_up_sprite.getPosition().y + pipe_up_sprite.getGlobalBounds().height;
//		while (y_pos < WINDOW_Y) {
//			pipe_shaft_sprite.setPosition(pipe_shaft_sprite.getPosition().x, y_pos);
//			y_pos++;
//			window.draw(pipe_shaft_sprite);
//		}
//
//		y_pos = pipe_down_sprite.getPosition().y; // Render the top pipe
//		while (y_pos > 0) {
//			pipe_shaft_sprite.setPosition(pipe_shaft_sprite.getPosition().x, y_pos);
//			y_pos--;
//			window.draw(pipe_shaft_sprite);
//		}

		window.display();



	}
	return 0;

}

