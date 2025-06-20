#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.h"
#include <math.h>


class Ball :public sf::CircleShape {
private:
    sf::Vector2f speed;
    sf::Vector2f startPosition;
    float speedValue;

public:
    Ball(sf::Vector2f position, float radius);
    void update(sf::Time dt, sf::RenderWindow& window, Platform& player, Platform& bot);
    void respawn();
    sf::Vector2f calculateCollision(sf::RenderWindow& window);
};
