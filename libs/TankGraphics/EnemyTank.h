#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "Sprite.h"
#include "Bullet.h"
#include "Tank.h"

using namespace std;

class EnemyTank : public Tank {
protected:
    double period;
    sf::Vector2f currentDirection;
    sf::Time lastMoved;
    sf::Clock clock;
    sf::Time lastHit;

    void basicUpdate(sf::RenderWindow* window, sf::Event& event, vector<shared_ptr<Sprite>>&  allSprites, sf::Clock& clock);
    void hardUpdate(sf::RenderWindow* window, sf::Event& event, vector<shared_ptr<Sprite>>&  allSprites, sf::Clock& clock);
    void stationaryUpdate(sf::RenderWindow* window, sf::Event& event, vector<shared_ptr<Sprite>>&  allSprites, sf::Clock& clock);
    void bossUpdate(sf::RenderWindow* window, sf::Event& event, vector<shared_ptr<Sprite>>&  allSprites, sf::Clock& clock);

public:
    EnemyTank(string newUrl, sf::Vector2f newPosition, double newRotation, double newScale, double newPeriod, int health, string newPref) : Tank(newUrl, newPosition, newRotation, newScale, newPref), period(newPeriod) { this->origHealth = this->health = health; }
    virtual void update(sf::RenderWindow* window, sf::Event& event, vector<shared_ptr<Sprite>>&  allSprites, sf::Clock& clock) override;
    virtual bool collision(Sprite* collided) override;

    virtual shared_ptr<EnemyTank> clone() const { return make_shared<EnemyTank>(*this); }
};
