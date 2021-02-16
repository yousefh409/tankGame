#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "Sprite.h"
#include "MainTank.h"

using namespace std;

class SecondaryTank : public MainTank {
public:
    SecondaryTank(string newUrl, sf::Vector2f newPosition, double newRotation, double newScale) : MainTank(newUrl, newPosition, newRotation, newScale) {}
    virtual bool collision(Sprite* collided) override;
    void update(sf::RenderWindow& window, sf::Event& event, vector<shared_ptr<Sprite>>&  allSprites, sf::Clock& clock) override;
};