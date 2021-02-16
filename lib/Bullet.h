#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "Sprite.h"

using namespace std;

class Bullet : public Sprite {
private:
    sf::Time lastMoved;
public:
    Bullet(string newUrl, sf::Vector2f newPosition, double newRotation, double newScale) : Sprite(newUrl, newPosition, newRotation, newScale), lastMoved(sf::seconds(0)) {};
    void update(sf::RenderWindow& window, sf::Event& event, vector<shared_ptr<Sprite>>& allSprites, sf::Clock& clock) override;
    virtual bool collision(Sprite* collided) override;
};
