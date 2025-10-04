#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode({400, 400}), "SFML Test");
    sf::CircleShape shape(50);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        // pollEvent returns std::optional<sf::Event>
        while (auto eventOpt = window.pollEvent()) {
            auto& event = *eventOpt;
            
            // SFML 3.x uses .index() with std::variant, or can use visit:
            if (event.is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
