#pragma once
#include <SFML/Graphics.hpp>


class Platform : public sf::RectangleShape {
protected:
    float speed;
    int score;
public:
    Platform(sf::Vector2f position) :RectangleShape() {
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






