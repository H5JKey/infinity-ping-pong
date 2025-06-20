#pragma once
#include "Platform.h"


class Player : public Platform {
public:
    enum Type {
        LEFT, RIGHT
    };
    Type type;

    Player(sf::Vector2f position, Type type) : Platform(position) {this->type=type;}

    virtual void update(sf::Time dt) {
        if (type==LEFT) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                move(0, -speed * dt.asSeconds());
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                move(0, speed * dt.asSeconds());
        }
        else if (type==RIGHT) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                move(0, -speed * dt.asSeconds());
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                move(0, speed * dt.asSeconds());
        }
    }
};

