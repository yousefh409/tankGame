#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "Sprite.h"
#include "Tank.h"

using namespace std;

class EnemyTank : public Tank {
public:
    EnemyTank(string newUrl, sf::Vector2f newPosition, double newRotation, double newScale) : Tank(newUrl, newPosition, newRotation, newScale) {}
    virtual void update(sf::RenderWindow& window, sf::Event& event, vector<shared_ptr<Sprite>>&  allSprites, sf::Clock& clock) override {};
    virtual bool collision(Sprite* collided) override;
};


class PeriodicFire : public EnemyTank {
protected:
    double period;
    sf::Time lastMoved;
public:
    PeriodicFire(string newUrl, sf::Vector2f newPosition, double newRotation, double newScale, double newPeriod) : EnemyTank(newUrl, newPosition, newRotation, newScale), period(newPeriod) { firePeriod = 1000; }
    virtual void update(sf::RenderWindow& window, sf::Event& event, vector<shared_ptr<Sprite>>&  allSprites, sf::Clock& clock) override;
};
