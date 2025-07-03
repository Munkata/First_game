#include <SFML/Graphics.hpp>
#define WINDOW_X 800
#define WINDOW_y 600
int main() {
    sf::Color beige(203, 190, 179);
    sf::Color reddish(209, 73, 91);
    sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_y), "My 2D Game");
    sf::CircleShape player(25.0f); // Simple player circle
    player.setFillColor(reddish);
    float locationX=0;
    float locationY=0;
    player.setPosition(locationX, locationY);

    sf::CircleShape ball(10.0f);
    ball.setFillColor(sf::Color::Green);
    ball.setPosition(WINDOW_X/2, WINDOW_y/2);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            player.move(0, -0.1);
            locationY-=0.1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            player.move(0,  0.1);
            locationY+=0.1;
        
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            player.move(-0.1, 0);
            locationX-=0.1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            player.move(0.1, 0);
            locationX+=0.1;
        }
        printf("Location x:%.2f y:%.2f\n",locationX, locationY);
        window.clear(beige);
        window.draw(player);
        window.draw(ball);//order of draw matters
        window.display();
    }

    return 0;
}