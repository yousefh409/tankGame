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
    EnemyTank(string newUrl, sf::Vector2f newPosition, double newRotation, double newScale, int health) : Tank(newUrl, newPosition, newRotation, newScale) { this->origHealth = this->health = health; }
    virtual void update(sf::RenderWindow* window, sf::Event& event, vector<shared_ptr<Sprite>>&  allSprites, sf::Clock& clock) override;
    virtual bool collision(Sprite* collided) override;
};

class PeriodicFire : public EnemyTank {
protected:
    double period;
    sf::Vector2f currentDirection;
    sf::Time lastMoved;
public:
    PeriodicFire(string newUrl, sf::Vector2f newPosition, double newRotation, double newScale, double newPeriod, int health) : EnemyTank(newUrl, newPosition, newRotation, newScale, health), period(newPeriod) {}
    virtual void update(sf::RenderWindow* window, sf::Event& event, vector<shared_ptr<Sprite>>& allSprites, sf::Clock& clock) override;
};