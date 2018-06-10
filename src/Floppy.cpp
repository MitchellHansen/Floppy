#include <chrono>
#include <Birb.h>
#include <Splash.h>
#include <Scoreboard.h>
#include <Scroller.h>
#include "Floppy.h"


Floppy::Floppy() :
        window_size(BASE_WINDOW_SIZE * DEFAULT_SCREEN_SCALE),
        window(sf::VideoMode(window_size.x, window_size.y), "Floppy"),
        birb(window_size),
        background(window_size, 10.0),
        ground(window_size, 10.0)
{
    background.setSprite("../Assets/sky.png", sf::Vector2f(0, 0), sf::Vector2f(8, 8));
    ground.setSprite("../Assets/land.png", sf::Vector2f(0, window_size.y - 30), sf::Vector2f(3, 2));

    pipes.emplace_back(Scroller(window_size, 150.0));
    pipes.back().setSprite("../Assets/pipe-up.png", sf::Vector2f(30, 700), sf::Vector2f(1.1,1.1));
    pipes.emplace_back(Scroller(window_size, 150.0));
    pipes.back().setSprite("../Assets/pipe-down.png", sf::Vector2f(30, -300), sf::Vector2f(1.1,1.1));
}

float Floppy::elapsed_time(){
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

sf::Vector2f Floppy::getScaledCoords(sf::Vector2f normalized_position) {
    return sf::Vector2f();
}

void Floppy::setScreenScale(float percentage) {
    //window.setSize();
}


sf::Vector2i Floppy::BASE_WINDOW_SIZE(900, 1600);
sf::Vector2f Floppy::DEFAULT_SCREEN_SCALE(0.5,0.5);

std::shared_ptr<Floppy> Floppy::getInstance() {
    if (!instance)
        instance = new Floppy();
    return instance;
}

void Floppy::loop() {


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
                    splash.click();
                    scoreboard.click();
                    birb.click();
                }
            }
        }

        // Update this frames time values
        elapsed_time = elapsed_time();
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
            background.update(step_size);
            ground.update(step_size);

            for (Scroller &pipe: pipes){
                pipe.update(step_size);
            }

            // Check collisions
            bool collision = false;
            if (ground.collides(birb.getBounds()))
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


    }
}

void Floppy::render() {

    background.render(window, false);

    for (auto pipe: pipes){
        pipe.render(window, false);
    }

    ground.render(window, false);
    birb.render(window);
    splash.render(window);
    scoreboard.render(window);

    window.display();
}

void Floppy::update(double delta_time) {

}


