#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "Sprite.h"

using namespace std;

class MainTank : public Sprite {
protected:
    sf::Time lastFired;
public:
    MainTank(string newUrl, sf::Vector2f newPosition, double newRotation, double newScale) : Sprite(newUrl, newPosition, newRotation, newScale), lastFired(sf::seconds(0)) {}
    virtual void update(sf::RenderWindow& window, sf::Event& event, vector<shared_ptr<Sprite>>&  allSprites, sf::Clock& clock) override;
    virtual bool collision(Sprite* collided) override;
    virtual void fire(vector<shared_ptr<Sprite>>& allSprites, sf::Clock& clock);
};
