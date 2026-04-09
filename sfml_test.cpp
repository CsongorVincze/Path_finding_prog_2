#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

int main() {
    // SFML 3.x uses Vector2u for VideoMode dimensions
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML Test Works!");
    window.setFramerateLimit(60);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition({350.f, 250.f}); // SFML 3.x uses Vector2f for position

    while (window.isOpen()) {
        // Event processing for SFML 3
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    std::cout << "SFML window closed successfully!" << std::endl;
    return 0;
}
