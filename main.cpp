#include <SFML/Graphics.hpp>
#define WINDOW_X 800
#define WINDOW_y 600
void initGameObjects(sf::RectangleShape& topLine,
                     sf::RectangleShape& bottomLine,
                     sf::RectangleShape& leftLine,
                     sf::RectangleShape& rightLine,
                     sf::RectangleShape& centerline,
                     sf::RectangleShape& player_1,
                     sf::RectangleShape& player_2,
                     sf::CircleShape& ball)
{
    const int margin = 10;
    const int width = WINDOW_X;
    const int height = WINDOW_y;
    const float ball_radius = 10.f;

    // Border lines
    topLine.setSize(sf::Vector2f(width - 2 * margin, 2));
    topLine.setPosition(margin, margin);
    topLine.setFillColor(sf::Color::Black);

    bottomLine.setSize(sf::Vector2f(width - 2 * margin, 2));
    bottomLine.setPosition(margin, height - margin);
    bottomLine.setFillColor(sf::Color::Black);

    leftLine.setSize(sf::Vector2f(2, height - 2 * margin));
    leftLine.setPosition(margin, margin);
    leftLine.setFillColor(sf::Color::Black);

    rightLine.setSize(sf::Vector2f(2, height - 2 * margin));
    rightLine.setPosition(width - margin, margin);
    rightLine.setFillColor(sf::Color::Black);

    centerline.setSize(sf::Vector2f(2, height - 2 * margin));
    centerline.setPosition((width / 2) - 1, margin); // center-adjusted
    centerline.setFillColor(sf::Color::Black);

    player_1.setSize(sf::Vector2f(20.f, 150.f));
    player_1.setFillColor(sf::Color(209, 73, 91)); // reddish
    player_1.setPosition(margin * 2, margin);

    player_2.setSize(sf::Vector2f(20.f, 150.f));
    player_2.setFillColor(sf::Color(73, 71, 91)); // grey
    player_2.setPosition(width - (margin * 4), margin);

    ball.setRadius(ball_radius);
    ball.setFillColor(sf::Color::Green);
    ball.setPosition(width / 2 - ball_radius, height / 2 - ball_radius);

}
int main() {
    sf::Color beige(203, 190, 179); //background
    sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_y), "My 2D Game");
    sf::RectangleShape topLine, bottomLine, leftLine, rightLine, centerline;
    sf::RectangleShape player_1, player_2;
    sf::CircleShape ball;
    initGameObjects(topLine, bottomLine, leftLine, rightLine, centerline,
                    player_1, player_2, ball);
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            player_2.move(0, -0.1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            player_2.move(0,  0.1);
        }
        
        window.clear(beige);
        window.draw(topLine);
        window.draw(bottomLine);
        window.draw(leftLine);
        window.draw(rightLine);
        window.draw(centerline);
        window.draw(player_1);
        window.draw(player_2);
        window.draw(ball);//order of draw matters
        window.display();
    }

    return 0;
}