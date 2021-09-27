#include <SFML/Window.hpp>
#include<SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML 2.5.1");

    sf::CircleShape shape(200.0f);
    shape.setFillColor(sf::Color::Blue);

    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(false);

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}