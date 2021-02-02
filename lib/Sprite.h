#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>

using namespace std;

class Sprite {
protected:
    sf::Sprite sprite;
    sf::Texture texture;

    string imageUrl;
    sf::Vector2f position;
    double rotation;
    double scale;

public:
    Sprite(string newUrl, sf::Vector2f newPosition, double newRotation, double newScale);

    void setPosition(sf::Vector2f newPosition);
    void setUrl(string newUrl);
    void setRotation(double newRotation);
    void setScale(double newScale);

    virtual void update(sf::RenderWindow& window, sf::Event& event);
};
