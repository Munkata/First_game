#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "My 2D Game");

    sf::CircleShape player(25.0f); // Simple player circle
    player.setFillColor(sf::Color::Green);
    player.setPosition(100, 100);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) player.move(0, -0.1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) player.move(0,  0.1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) player.move(-0.1, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) player.move( 0.1, 0);

        window.clear();
        window.draw(player);
        window.display();
    }

    return 0;
}