#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "Sprite.h"

using namespace std;

class Bullet : public Sprite {
protected:
    sf::Time lastMoved;
    double damage;
    int speedPeriod;
public:
    Bullet(string newUrl, sf::Vector2f newPosition, double newRotation, double newScale) : Sprite(newUrl, newPosition, newRotation, newScale), lastMoved(sf::seconds(0)), damage(10), speedPeriod(20) {};
    void update(sf::RenderWindow* window, sf::Event& event, vector<shared_ptr<Sprite>>& allSprites, sf::Clock& clock) override;
    virtual bool collision(Sprite* collided) override;

    double getDamage() const { return damage; }
};

class BigBullet : public Bullet {
public:
      BigBullet(string newUrl, sf::Vector2f newPosition, double newRotation, double newScale);
};
