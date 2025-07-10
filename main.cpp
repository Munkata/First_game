#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#define WINDOW_X 800
#define WINDOW_y 600
const float ball_radius = 10.f;
void initGameObjects(sf::RectangleShape& topLine,
                     sf::RectangleShape& bottomLine,
                     sf::RectangleShape& leftLine,
                     sf::RectangleShape& rightLine,
                     sf::RectangleShape& centerline,
                     sf::RectangleShape& player_1,
                     sf::RectangleShape& player_2,
                     sf::CircleShape& ball,
                    float margin_botop)
{
    const int margin = 10;
    const int width = WINDOW_X;
    const int height = WINDOW_y;

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
    player_1.setPosition(margin * 2, margin+margin_botop);

    player_2.setSize(sf::Vector2f(20.f, 150.f));
    player_2.setFillColor(sf::Color(73, 71, 91)); // grey
    player_2.setPosition(width - (margin * 4), margin+margin_botop);

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
    float margin_botop=5;
    sf::Font font;
    if (!font.loadFromFile("/Users/marchuchu/Mario/code_1/First_game/FiraCodeNerdFontMono-SemiBold.ttf"))
    {
        printf ("Error loading font\n");
        return -1;
    }
    sf::Text pressSpace;
    pressSpace.setFont(font);
    pressSpace.setString("Press Space to \nPlay the game!");
    pressSpace.setCharacterSize(80);
    // 1. Get the text bounds
    sf::FloatRect textBounds = pressSpace.getLocalBounds();

    // 2. Set the origin to the center of the text
    pressSpace.setOrigin(textBounds.left + textBounds.width / 2.0f,
                     textBounds.top + textBounds.height / 2.0f);

    // 3. Position it at the center of the window
    pressSpace.setPosition(WINDOW_X / 2.0f, WINDOW_y / 2.0f);

    // 4. Optional: Make it semi-transparent white
    pressSpace.setFillColor(sf::Color(255, 255, 255, 128));
// Score 1 — center in the left half
    sf::Text score_p1;
    int score_1=0;
    score_p1.setFont(font);
    score_p1.setString("Score 1: " + std::to_string(score_1));
    score_p1.setCharacterSize(40);
    sf::FloatRect bounds1 = score_p1.getLocalBounds();
    score_p1.setOrigin(bounds1.left + bounds1.width / 2.f, 0.f);
    score_p1.setPosition(WINDOW_X * 1.f / 4.f, margin_botop);
    score_p1.setFillColor(sf::Color(255, 255, 255, 128));

    // Score 2 — center in the right half
    sf::Text score_p2;
    int score_2=0;
    score_p2.setFont(font);
    score_p2.setString("Score 2: " + std::to_string(score_2));
    score_p2.setCharacterSize(40);
    sf::FloatRect bounds2 = score_p2.getLocalBounds();
    score_p2.setOrigin(bounds2.left + bounds2.width / 2.f, 0.f);
    score_p2.setPosition(WINDOW_X * 3.f / 4.f, margin_botop);
    score_p2.setFillColor(sf::Color(255, 255, 255, 128));
    initGameObjects(topLine, bottomLine, leftLine, rightLine, centerline,
                    player_1, player_2, ball,margin_botop);
    float speed_player=0.2f;
    float x_speed_ball=0.08f;
    //implement game time
    float y_speed_ball=0.08f;
    bool game_started=false;
    while (window.isOpen()) {
        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            game_started = true;
        }
        if(game_started){
            ball.move(x_speed_ball,y_speed_ball);
            // printf("speed_x:%2f speed_y:%2f\n",x_speed_ball,y_speed_ball);
            //ball collision with points
            if(ball.getGlobalBounds().intersects(rightLine.getGlobalBounds())){
                ball.setPosition(WINDOW_X / 2 - ball_radius, WINDOW_y / 2 - ball_radius);
                x_speed_ball=-x_speed_ball;
                game_started=false;
                score_1++;
                score_p1.setString("Score 1: " + std::to_string(score_1));
            }
            if(ball.getGlobalBounds().intersects(leftLine.getGlobalBounds())){
                ball.setPosition(WINDOW_X / 2 - ball_radius, WINDOW_y / 2 - ball_radius);
                x_speed_ball=-x_speed_ball;
                game_started=false;
                score_2++;
                score_p2.setString("Score 2: " + std::to_string(score_2));
            }
            //ball collison with walls 
            if(ball.getPosition().y <= topLine.getPosition().y + topLine.getSize().y
            ||ball.getPosition().y + ball.getGlobalBounds().height+1>= bottomLine.getPosition().y + bottomLine.getSize().y){
                    y_speed_ball=-y_speed_ball;
                    // std::this_thread::sleep_for(std::chrono::milliseconds(3000)); // sleep for 1 second testing
            }
            //ball collison with player
            if (ball.getGlobalBounds().intersects(player_2.getGlobalBounds())||ball.getGlobalBounds().intersects(player_1.getGlobalBounds())){
                    x_speed_ball=-x_speed_ball;
                    // std::this_thread::sleep_for(std::chrono::milliseconds(3000)); // sleep for 1 second testing
            }

        }
        // Movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            if(player_1.getPosition().y > topLine.getPosition().y + topLine.getSize().y + margin_botop){
                player_1.move(0, -speed_player);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            if(player_1.getPosition().y +player_1.getSize().y< bottomLine.getPosition().y + bottomLine.getSize().y -  margin_botop){
                player_1.move(0,  speed_player);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if(player_2.getPosition().y > topLine.getPosition().y + topLine.getSize().y + margin_botop){
                player_2.move(0, -speed_player);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if(player_2.getPosition().y +player_2.getSize().y< bottomLine.getPosition().y + bottomLine.getSize().y - margin_botop){
                player_2.move(0,  speed_player);
            }
        }
    
        //display stuff
        window.clear(beige);
        window.draw(topLine);
        window.draw(bottomLine);
        window.draw(leftLine);
        window.draw(rightLine);
        window.draw(centerline);
        window.draw(player_1);
        window.draw(player_2);
        window.draw(ball);//order of draw matters
        if(!game_started)
        {
            window.draw(pressSpace);
        }
        window.draw(score_p1);
        window.draw(score_p2);
        window.display();
    }

    return 0;
}