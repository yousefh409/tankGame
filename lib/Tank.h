#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "Sprite.h"

using namespace std;

class Tank : public Sprite {
protected:
    sf::Time lastFired;
    int firePeriod = 300;
    double origHealth;
public:
    Tank(string newUrl, sf::Vector2f newPosition, double newRotation, double newScale) : Sprite(newUrl, newPosition, newRotation, newScale), lastFired(sf::seconds(0)), origHealth(0) { health = 0; }

    virtual void update(sf::RenderWindow* window, sf::Event& event, vector<shared_ptr<Sprite>>&  allSprites, sf::Clock& clock);
    virtual bool collision(Sprite* collided) = 0;
    virtual void fire(vector<shared_ptr<Sprite>>& allSprites, sf::Clock& clock);
    virtual void fireBig(vector<shared_ptr<Sprite>>& allSprites, sf::Clock& clock, sf::RenderWindow* window);
};
