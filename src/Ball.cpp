#include "Ball.h"

Ball::Ball(sf::Vector2f position, float radius) : CircleShape(radius) {
    startPosition = position;
    setOrigin(radius, radius);
    setFillColor(sf::Color::Transparent);
    setOutlineThickness(3);
    speedValue = 750;
    respawn();
}

void Ball::respawn() {
    setPosition(startPosition);
    float angle = rand() % (60)-30;
    if (rand() % 2 == 0)
        angle = 180 - angle;
    angle = (angle / 180) * (3.141592);
    speed.x = speedValue * cos(angle);
    speed.y = speedValue * sin(angle);
}

void Ball::update(sf::Time dt, const sf::RenderWindow& window, Platform& player, Platform& bot) {
    move(dt.asSeconds() * speed);
    float x = getPosition().x;
    float y = getPosition().y;

    if ((x - getRadius() < player.getSize().x) && (y - getRadius() > player.getPosition().y) && (y + getRadius() < player.getPosition().y + player.getSize().y))
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

sf::Vector2f Ball::calculateCollision(const sf::RenderWindow& window) {
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