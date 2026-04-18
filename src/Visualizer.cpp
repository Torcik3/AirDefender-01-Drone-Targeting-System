
#include "include/Visualizer.h"
#include <SFML/Graphics.hpp>

void Visualizer::run(World& world) {
    sf::RenderWindow window(sf::VideoMode(1000,1000), "Radar");
    window.setFramerateLimit(60);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }
        window.clear(sf::Color::Black);
        {
            std::lock_guard<std::mutex> lock(world.mtx);
            float zoom = 0.01f;
            float offsetX = 400.0f;
            float offsetY = 400.0f;
            for (const auto& t : world.targets) {
                sf::CircleShape target(5.0f);
                target.setFillColor(sf::Color::Blue);
                target.setPosition((t->getPosition().x * zoom) + offsetX, (t->getPosition().y * zoom) + offsetY);
                window.draw(target);
            }

            for (const auto& d : world.drones) {
                sf::CircleShape drone(5.0f);
                drone.setFillColor(sf::Color::Red);
                drone.setPosition((d->getPosition().x * zoom) + offsetX, (d->getPosition().y * zoom) + offsetY);
                window.draw(drone);
            }
        }
        window.display();
        }
    }
