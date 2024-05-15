#include <iostream>
#include <SFML/Graphics.hpp>


class Platform : public sf::RectangleShape {
protected:
    float speed;
    int score;
public:
    Platform(sf::Vector2f position):RectangleShape() {
        setPosition(position);
        setFillColor(sf::Color::Transparent);
        setOutlineThickness(3);
        setSize({ 5, 120 });

        speed = 550;
        score = 0;
    }

    virtual int getScore() {
        return score;
    }

    virtual void addPointToScore() {
        score++;
    }

    virtual void update(sf::Time dt) = 0;
};

class Bot:public Platform {
public:
    sf::Vector2f ballCollisionPosition;
public:
    Bot(sf::Vector2f position) :Platform(position) {}

    virtual void update(sf::Time dt) {
        if (ballCollisionPosition.x == getPosition().x + getSize().x || ballCollisionPosition.x == getPosition().x) {
            if (ballCollisionPosition.y > getPosition().y + getSize().y / 2)
                move(0, speed * dt.asSeconds());
            if (ballCollisionPosition.y < getPosition().y + getSize().y / 2)
                move(0, -speed * dt.asSeconds());
        }
    }
    
};

class Player:public Platform {
public:
    Player(sf::Vector2f position) :Platform(position) {}

    virtual void update(sf::Time dt) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
            move(0, -speed * dt.asSeconds());
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            move(0, speed * dt.asSeconds());
        
    }
};



class Ball :public sf::CircleShape {
private:
    sf::Vector2f speed;

    sf::Vector2f startPosition;

public:
    Ball(sf::Vector2f position, float radius):CircleShape(radius) {
        startPosition = position;
        setOrigin(radius,radius);
        setFillColor(sf::Color::Transparent);
        setOutlineThickness(3);

        respawn();
    }

    void respawn() {
        setPosition(startPosition);
        speed.y = rand() % 1000 - 500;
        speed.x = 1050;
        if (rand() % 2 - 1 < 0)
            speed.x *= -1;
    }

    void update(sf::Time dt, const sf::RenderWindow& window, Platform& player, Platform& bot) {
        move(dt.asSeconds() * speed);
        float x = getPosition().x;
        float y = getPosition().y;

        if ((x-getRadius() < player.getSize().x) && (y-getRadius()>player.getPosition().y) && (y + getRadius() < player.getPosition().y + player.getSize().y))
            speed.x *= -1;
        if ((x + getRadius() > bot.getPosition().x) && (y - getRadius() > bot.getPosition().y) && (y + getRadius() < bot.getPosition().y + bot.getSize().y)) 
            speed.x *= -1;
        

        if (y - getRadius() < 0)
            speed.y *= -1;
        if (y + getRadius() > window.getSize().y)
            speed.y *= -1;
        
        if (x < 0) {
            bot.addPointToScore();
            respawn();
        }
        
        if (x > window.getSize().x) {
            player.addPointToScore();
            respawn();
        }

    }

    sf::Vector2f calculateCollision(const sf::RenderWindow& window) {
        float dy;
        float y = -1, x;
        if (speed.x > 0) {
            x = window.getSize().x;
            dy = ((window.getSize().x - getPosition().x) / abs(speed.x)) * abs(speed.y);
        }
        else {
            x = 0;
            dy = ((getPosition().x) / abs(speed.x)) * abs(speed.y);
        }
        if (speed.y < 0) {
            dy += window.getSize().y - getPosition().y;
            if ((int(dy) / window.getSize().y) % 2 == 1) {
                y = int(dy) % window.getSize().y;
            }
            else {
                y = window.getSize().y - int(dy) % window.getSize().y;
            }
        }
        else {
            dy += getPosition().y;
            if ((int(dy) / window.getSize().y) % 2 == 1) {
                y = window.getSize().y - int(dy) % window.getSize().y;
            }
            else {
                y = int(dy) % window.getSize().y;
            }
        }
        return { x,y };
    }
};

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

    Bot player(sf::Vector2f(0, window.getSize().y / 2 ));
    Bot bot(sf::Vector2f(window.getSize().x-5, window.getSize().y / 2));



    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");

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
        player.ballCollisionPosition = ball.calculateCollision(window);
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
}

