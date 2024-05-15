#pragma once
#include "Platform.h"


class Bot :public Platform {
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


