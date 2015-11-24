#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <windows.h>

const float g = 7.8;
const int WINDOW_X = 600;
const int WINDOW_Y = 800;
const int pipe_dist = 200;

float elap_time() {
	static __int64 start = 0;
	static __int64 frequency = 0;

	if (start == 0) {
		QueryPerformanceCounter((LARGE_INTEGER*)&start);
		QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
		return 0.0f;
	}

	__int64 counter = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&counter);
	return (float)((counter - start) / double(frequency));
}

int main()
{
	std::mt19937 rng(time(NULL));
	std::uniform_int_distribution<int> rgen(100, 400);

	sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "flappy");
	
	// Init flappy
	sf::Texture flappy_texture[4] = { sf::Texture(), sf::Texture(), sf::Texture(), sf::Texture() };
	for (int i = 0; i < 4; i++) {
		flappy_texture[i].loadFromFile("Assets\\bird.png", sf::IntRect(0, i*12, 34, 24));
	}

	sf::RectangleShape flappy(sf::Vector2f(34, 24));
	flappy.setTexture(&flappy_texture[0],false);
	flappy.setPosition(WINDOW_X / 2, WINDOW_Y / 2);

	// Init world
	sf::Texture background = sf::Texture(); background.loadFromFile("Assets\\sky.png");
	sf::Sprite background_sprite = sf::Sprite(background); background_sprite.setPosition(0, 0); background_sprite.setScale(8, 8);
	sf::Texture land = sf::Texture(); land.loadFromFile("Assets\\land.png");
	sf::Sprite land_sprite = sf::Sprite(land); land_sprite.setPosition(0, WINDOW_Y - WINDOW_Y / 10); land_sprite.setScale(2, 2);
	sf::Texture pipe_up, pipe_down = sf::Texture(); pipe_down.loadFromFile("Assets\\pipe-down.png"); pipe_up.loadFromFile("Assets\\pipe-up.png");
	sf::Sprite pipe_up_sprite = sf::Sprite(pipe_up); sf::Sprite pipe_down_sprite = sf::Sprite(pipe_down);
	sf::Texture pipe_shaft = sf::Texture(); pipe_shaft.loadFromFile("Assets\\pipe.png");
	sf::Sprite pipe_shaft_sprite = sf::Sprite(pipe_shaft);

	double momentum = 0;
	float step_size = 0.005f;
	double frame_time = 0.0, instant_fps = 0.0, render_fps = 0.0, physics_fps = 0.0, elapsed_time = 0.0, delta_time = 0.0, accumulator_time = 0.0, current_time = 0.0;
	int render_frame_count = 0, physics_frame_count = 0;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		elapsed_time = elap_time();
		delta_time = elapsed_time - current_time;
		current_time = elapsed_time;
		if (delta_time > 0.02f)
			delta_time = 0.02f;
		accumulator_time += delta_time;

		while ((accumulator_time - step_size) >= step_size) {
			accumulator_time -= step_size;

			// Update logic
			// Move pipes, background, floor

			if (pipe_down_sprite.getPosition().x < -pipe_down_sprite.getGlobalBounds().width) {
				pipe_down_sprite.setPosition(WINDOW_X, rgen(rng));
				pipe_up_sprite.setPosition(WINDOW_X, pipe_down_sprite.getPosition().y + pipe_dist);
			}
			else {
				pipe_up_sprite.setPosition(pipe_up_sprite.getPosition().x - step_size * 250, pipe_up_sprite.getPosition().y);
				pipe_down_sprite.setPosition(pipe_down_sprite.getPosition().x - step_size * 250, pipe_down_sprite.getPosition().y);
			}

			if (background_sprite.getPosition().x + background_sprite.getGlobalBounds().width < WINDOW_X) {
				background_sprite.setPosition(0, 0);
			}
			else {
				background_sprite.setPosition(background_sprite.getPosition().x - step_size * 150, background_sprite.getPosition().y);
			}

			if (land_sprite.getPosition().x + 10 + land_sprite.getGlobalBounds().width < WINDOW_X) {
				land_sprite.setPosition(14, land_sprite.getPosition().y);
			}
			else {
				land_sprite.setPosition(land_sprite.getPosition().x - step_size * 250, land_sprite.getPosition().y);
			}

			// Check collisions
			if (flappy.getPosition().y > land_sprite.getPosition().y) {
				flappy.setPosition(WINDOW_X / 2, WINDOW_Y / 2);
				momentum = 0;
				std::cout << "dead\n";
			}

			sf::Vector2f f_pos = flappy.getPosition();
			sf::Vector2f p_pos = pipe_up_sprite.getPosition();

			if (((f_pos.x < p_pos.x + 26) && (f_pos.x > p_pos.x)) && ((f_pos.y > p_pos.y) || (f_pos.y < p_pos.y - pipe_dist))) {
				f_pos = sf::Vector2f(WINDOW_X / 2, WINDOW_Y / 2);
				momentum = 0;
				std::cout << "dead\n ";
			}

			// Get input
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				momentum = -2;
			}

			momentum += g * step_size;
			f_pos.y += momentum;
			flappy.setPosition(f_pos);

			physics_frame_count++;
		}


		window.clear(sf::Color::Black);
		window.draw(background_sprite);
		window.draw(land_sprite);
		window.draw(flappy);
		window.draw(pipe_up_sprite);
		window.draw(pipe_down_sprite);

		pipe_shaft_sprite.setPosition(pipe_up_sprite.getPosition());
		int y_pos = pipe_up_sprite.getPosition().y + pipe_up_sprite.getGlobalBounds().height;
		while (y_pos < WINDOW_Y) {
			pipe_shaft_sprite.setPosition(pipe_shaft_sprite.getPosition().x, y_pos);
			y_pos++;
			window.draw(pipe_shaft_sprite);
		}

		y_pos = pipe_down_sprite.getPosition().y;
		while (y_pos > 0) {
			pipe_shaft_sprite.setPosition(pipe_shaft_sprite.getPosition().x, y_pos);
			y_pos--;
			window.draw(pipe_shaft_sprite);
		}

		window.display();



	}
	return 0;

}

