#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <list>
#include <Splash.h>
#include <Scoreboard.h>
#include "Scroller.h"
#include "Birb.h"

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
    // Program State
	std::mt19937 rng(time(NULL));
	std::uniform_int_distribution<int> rgen(100, 400);

	sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "flappy");
    sf::Vector2i window_size(WINDOW_X, WINDOW_Y);


    // Sprite States
    Birb birb(window_size);
    Splash splash_screen;
    Scoreboard scoreboard;

    Scroller background_scroller(window_size, 10.0);
    background_scroller.setSprite("../Assets/sky.png", sf::Vector2f(0, 0), sf::Vector2f(8, 8));

    Scroller land_scroller(window_size, 10.0);
    land_scroller.setSprite("../Assets/land.png", sf::Vector2f(0, window_size.y - 30), sf::Vector2f(3, 2));

    std::list<Scroller> pipes;

    pipes.emplace_back(Scroller(window_size, 150.0));
    pipes.back().setSprite("../Assets/pipe-up.png", sf::Vector2f(30, 700), sf::Vector2f(1.1,1.1));
    pipes.emplace_back(Scroller(window_size, 150.0));
    pipes.back().setSprite("../Assets/pipe-down.png", sf::Vector2f(30, -300), sf::Vector2f(1.1,1.1));


    // Render Loop
	float step_size = 0.005f;
	double  elapsed_time = 0.0, delta_time = 0.0, accumulator_time = 0.0, current_time = 0.0;

	while (window.isOpen())
	{
		sf::Event event; // Handle input
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) 
				window.close();
			if(event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space)
                    birb.click();
                if (event.key.code == sf::Keyboard::Escape)
                    birb.click();
            }
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left){
                    splash_screen.click();
                    scoreboard.click();
					birb.click();
                }
			}
		}

        // Update this frames time values
		elapsed_time = elap_time();
		delta_time = elapsed_time - current_time;
		current_time = elapsed_time;
		if (delta_time > 0.02f)
			delta_time = 0.02f;
		accumulator_time += delta_time;

        // While the frame has sim time, update
		while ((accumulator_time - step_size) >= step_size) {

            accumulator_time -= step_size;

            // Scroll according to the step size
            birb.update(step_size);
            background_scroller.update(step_size);
            land_scroller.update(step_size);
            for (Scroller &pipe: pipes){
                pipe.update(step_size);
            }

            // Check collisions
            bool collision = false;
            if (land_scroller.collides(birb.getBounds()))
                collision = true;
            for (Scroller &pipe: pipes){
                if (pipe.collides(birb.getBounds()))
                    collision = true;
            }

            if (collision){
                birb.reset();
                scoreboard.show(100);
            }
		}


        background_scroller.render(window, false);

        for (auto pipe: pipes){
            pipe.render(window, false);
        }

        land_scroller.render(window, false);

        birb.render(window);

        splash_screen.render(window);
        scoreboard.render(window);

		window.display();
	}
	return 0;
}

