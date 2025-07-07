#include <SFML/Graphics.hpp>
#define WINDOW_X 800
#define WINDOW_y 600
int main() {
    sf::Color beige(203, 190, 179); //background
    sf::Color reddish(209, 73, 91); //player_1
    sf::Color grey(73, 71, 91); //player_2
    sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_y), "My 2D Game");

        // Create the border lines
    sf::RectangleShape topLine(sf::Vector2f(WINDOW_X-2*10, 2));
    topLine.setPosition(10, 10);
    topLine.setFillColor(sf::Color::Black);

    sf::RectangleShape bottomLine(sf::Vector2f(WINDOW_X-2*10, 2));
    bottomLine.setPosition(10, WINDOW_y-10);
    bottomLine.setFillColor(sf::Color::Black);

    sf::RectangleShape leftLine(sf::Vector2f(2, WINDOW_y-2*10));
    leftLine.setPosition(10, 10);
    leftLine.setFillColor(sf::Color::Black);

    sf::RectangleShape rightLine(sf::Vector2f(2, WINDOW_y-2*10));
    rightLine.setPosition(WINDOW_X-10, 10);
    rightLine.setFillColor(sf::Color::Black);

    sf::RectangleShape centerline;
    centerline.setSize(sf::Vector2f(2, WINDOW_y - 2*10));
    centerline.setPosition(((WINDOW_X - 2) / 2) + 4, 10);
    centerline.setFillColor(sf::Color::Black);

    sf::CircleShape centercircle;
    centercircle.setRadius(100);
    centercircle.setPosition(WINDOW_X /2 -95, WINDOW_y / 2 -98 );
    centercircle.setOutlineThickness(2);
    centercircle.setOutlineColor(sf::Color::Black);
    centercircle.setFillColor(sf::Color::Transparent);


    sf::RectangleShape player_1(sf::Vector2f(20.f, 150.f));//width xheight
    // sf::CircleShape player_1(25.0f); // Simple player_1 circle
    player_1.setFillColor(reddish);
    player_1.setPosition(5, 10);

    sf::RectangleShape player_2(sf::Vector2f(20.f, 150.f));//width xheight
    player_2.setFillColor(grey);
    player_2.setPosition(WINDOW_X-5, 0);

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
            player_1.move(0, -0.1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            player_1.move(0,  0.1);
        }

        window.clear(beige);
    
        window.draw(topLine);
        window.draw(bottomLine);
        window.draw(leftLine);
        window.draw(rightLine);
        window.draw(centercircle);
        window.draw(centerline);

        window.draw(player_1);
        window.draw(player_2);
        window.draw(ball);//order of draw matters
        window.display();
    }

    return 0;
}