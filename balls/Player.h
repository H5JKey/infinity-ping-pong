#pragma once
#include "Platform.h"


class Player :public Platform {
public:
    Player(sf::Vector2f position) :Platform(position) {}

    virtual void update(sf::Time dt) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            move(0, -speed * dt.asSeconds());
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            move(0, speed * dt.asSeconds());

    }
};

