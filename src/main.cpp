#include <iostream>
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Bot.h"
#include "Player.h"



int main()
{
    sf::Clock timer;
    timer.restart();
    srand(time(NULL));
    sf::VertexArray line(sf::Lines, 2);

    sf::RenderWindow window(sf::VideoMode(600,600),"balls");


    line[0].position = sf::Vector2f(window.getSize().x / 2, 0);
    line[1].position = sf::Vector2f(window.getSize().x / 2,window.getSize().y);

    line[0].color = { 255,255,255,50 };
    line[1].color = { 255,255,255,50 };

    Player player(sf::Vector2f(0, window.getSize().y / 2), Player::LEFT);
    Bot bot(sf::Vector2f(window.getSize().x-5, window.getSize().y / 2));


    sf::Font font;
#ifdef _WIN32    
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
#elif __linux__
    font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
#endif

    sf::Text playerScore("0",font);
    sf::Text botScore("0",font);

    playerScore.setPosition(window.getSize().x / 2 - 100,100);
    botScore.setPosition(window.getSize().x / 2 + 100, 100);

    playerScore.setCharacterSize(20);
    botScore.setCharacterSize(20);

    sf::Vector2u size = window.getSize();
    Ball ball(sf::Vector2f(size.x / 2,size.y / 2), 6);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        sf::Time dt = timer.restart();

        window.clear();

        ball.update(dt,window,player,bot);

        player.update(dt);
        bot.ballCollisionPosition = ball.calculateCollision(window);
        bot.update(dt);

        botScore.setString(std::to_string(bot.getScore()));
        playerScore.setString(std::to_string(player.getScore()));

        window.draw(ball);
        window.draw(player);
        window.draw(bot);
        window.draw(line);
        window.draw(playerScore);
        window.draw(botScore);
        
        window.display();
    }

    return 0;
}

