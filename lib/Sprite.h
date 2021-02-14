#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <vector>
#include<memory>

using namespace std;

class Sprite {
public:
    sf::Sprite sprite;
    shared_ptr<sf::Texture> texture;

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

    sf::Vector2f getVectorRotation(double offset) const;

    bool isCollision(Sprite other);

    virtual void update(sf::RenderWindow& window, sf::Event& event, vector<shared_ptr<Sprite>>& allSprites, sf::Clock& clock);
};
