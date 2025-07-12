#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#define WINDOW_X 800
#define WINDOW_y 600
const float ball_radius = 10.f;

/* 
1. There are a bunch of parameters here which could be encapsulated in a class and initialized in a 
constructor. This also gives you control over the way each object is destroyed in the constructor(this could
be unnecessary but good to know generally).

2. There is a bunch of repeated code: 

    topLine.setSize(sf::Vector2f(width - 2 * margin, 2));
    topLine.setPosition(margin, margin);
    topLine.setFillColor(sf::Color::Black);

    bottomLine.setSize(sf::Vector2f(width - 2 * margin, 2));
    bottomLine.setPosition(margin, height - margin);
    bottomLine.setFillColor(sf::Color::Black);

These are doing the same thing on the same type, but with slightly different parameters. It could be
benifical to have a static method or function which takes in the respective parameters and reduces all 
these repeated initializations in a single function call.

Also in C++ you can check out constexpr and generally avoid macros. The main issue with macros(which are 
used widely in C) is that it's basically direct text substitution so no type checking no compiler help, just
a fuck you if you screw something up. A big help in C++ is the compiler type checking, use that as much as 
possible - unlike C, in C++ not everything is a fucking int.

3. A fun thing you can try to do, which I'm not 100% sure applicable hear at all, but one time I was developing 
an embedded space invaders on a fuckass LCD display, the issue was that updating the entire display every iteration
in my while loop was too expensive and the LCD display was bugging. To fix this I first checked what exactly on the display
has changed and only redrew that part - not 100% sure how the game works, but for example instead of redrawing the entire display
only change the color of the pixels in accordance to where the new position of the pong ball is(same goes for the paddles).

4.Also I think that some of the functionalities in the while loop can be encapsulated in the game class.

5. The Score 1 and Score 2 seem repetitive, this doesn't necessarily mean that this should be encapsulated in 
class, but it seems reasonable given that there is a state(the score represents the state of the Score class), 
and put the repetitive initialization in a constructor and add a method for incremention. You could even put the
condition(whether the score should be incremented at all) check in this class, or keep it outside. You can think
about how you should do that, with my understanding(or lack thereof) of the code I don't think either is a mistake.

6. Also: 
    const int width = WINDOW_X;
    const int height = WINDOW_y;
, it might be better for this to be either a global constexpr or even better use the macro itself(if you decide
not to use constexpr), there isn't much point in having a macro or global contexpr and then saying, oh hey this
const int is equal to this macro or constexpr - you're just doing the same thing twice, and it's a but confusing 
when reading the code.

7. What the fuck is going on here:
    sf::Text timer;
    float overall_time = 0.0f;
    timer.setFont(font);
    timer.setString("Time: " + std::to_string(static_cast<int>(overall_time)));
Here's what a normal person sees: we have float, which is then statically casted to an int, this is actually not 
a bad practice, because static cast gives you some compile time protections unlike c-style casts(dynamic_cast I 
think is similar to c-style casts but I'm not 100% if they're exactly the same). But then we use that
in a to_string, when to_string supports floats, if there are issues with formatting, then use std::format.

8. I don't see anything else as of right now, I'll take another look tmrw morning and create a new pull request or
add a commit to this one.


*/
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
    score_p1.setCharacterSize(30);
    sf::FloatRect bounds1 = score_p1.getLocalBounds();
    score_p1.setOrigin(bounds1.left + bounds1.width / 2.f, 0.f);
    score_p1.setPosition(WINDOW_X * 1.f / 4.f, margin_botop);
    score_p1.setFillColor(sf::Color(73, 71, 91, 100));

    // Score 2 — center in the right half
    sf::Text score_p2;
    int score_2=0;
    score_p2.setFont(font);
    score_p2.setString("Score 2: " + std::to_string(score_2));
    score_p2.setCharacterSize(30);
    sf::FloatRect bounds2 = score_p2.getLocalBounds();
    score_p2.setOrigin(bounds2.left + bounds2.width / 2.f, 0.f);
    score_p2.setPosition(WINDOW_X * 3.f / 4.f, margin_botop);
    score_p2.setFillColor(sf::Color(73, 71, 91, 100));

    sf::Text timer;
    float overall_time = 0.0f;
    timer.setFont(font);
    timer.setString("Time: " + std::to_string(static_cast<int>(overall_time)));
    timer.setCharacterSize(30);
    sf::FloatRect bounds3 = timer.getLocalBounds();
    timer.setOrigin(bounds3.left + bounds3.width / 2.f, 0.f);
    timer.setPosition(WINDOW_X/2+bounds3.left, WINDOW_y* 3/4);
    timer.setFillColor(sf::Color(73, 71, 91, 100));

    initGameObjects(topLine, bottomLine, leftLine, rightLine, centerline,
                    player_1, player_2, ball,margin_botop);

    float speed_player=0.2f;
    float x_speed_ball=0.08f;
    float y_speed_ball=0.08f;
    float acceleration = 0.03f; // adjust to taste
    //implement game time
    sf::Clock clock;
    float round_time = 0.0f;
    bool game_started=false;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&game_started==false&&window.hasFocus())
        {   
            game_started = true;
            clock.restart(); // restart the timer as the round starts
        }
        if(game_started){
            round_time = clock.getElapsedTime().asSeconds();
            float time_factor = 1.0f + acceleration * round_time;
            float adjusted_x_speed = x_speed_ball * time_factor;
            float adjusted_y_speed = y_speed_ball * time_factor;
            timer.setString("Time: " + std::to_string(static_cast<int>(overall_time+round_time )));
            // printf("%2f\n",adjusted_x_speed);
            ball.move(adjusted_x_speed, adjusted_y_speed);
            //ball collision with points
            if(ball.getGlobalBounds().intersects(rightLine.getGlobalBounds())){
                ball.setPosition(WINDOW_X / 2 - ball_radius, WINDOW_y / 2 - ball_radius);
                x_speed_ball=-x_speed_ball;
                game_started=false;

                round_time = clock.getElapsedTime().asSeconds();
                overall_time += round_time;
                // printf("⏱ Round duration: %.2f seconds | 🕒 Total time: %.2f seconds\n", round_time, overall_time);
                score_1++;
                score_p1.setString("Score 1: " + std::to_string(score_1));
            }
            if(ball.getGlobalBounds().intersects(leftLine.getGlobalBounds())){
                ball.setPosition(WINDOW_X / 2 - ball_radius, WINDOW_y / 2 - ball_radius);
                x_speed_ball=-x_speed_ball;
                game_started=false;
                round_time = clock.getElapsedTime().asSeconds();
                overall_time += round_time;
                printf("Round duration: %.2f seconds |  Total time: %.2f seconds\n", round_time, overall_time);
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

        }else{
            round_time = 0.0f;
        }
        // Movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && window.hasFocus()) {
            if (player_1.getPosition().y > topLine.getPosition().y + topLine.getSize().y + margin_botop) {
                player_1.move(0, -speed_player);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && window.hasFocus()) {
            if (player_1.getPosition().y + player_1.getSize().y < bottomLine.getPosition().y + bottomLine.getSize().y - margin_botop) {
                player_1.move(0, speed_player);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && window.hasFocus()) {
            if (player_2.getPosition().y > topLine.getPosition().y + topLine.getSize().y + margin_botop) {
                player_2.move(0, -speed_player);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && window.hasFocus()) {
            if (player_2.getPosition().y + player_2.getSize().y < bottomLine.getPosition().y + bottomLine.getSize().y - margin_botop) {
                player_2.move(0, speed_player);
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
        window.draw(timer);
        window.display();
    }

    return 0;
}
