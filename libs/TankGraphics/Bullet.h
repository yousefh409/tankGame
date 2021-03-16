#ifndef BULLET_H
#define BULLET_H
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
    Bullet(string newUrl, sf::Vector2f newPosition, double newRotation, double newScale, string newPref) : Sprite(newUrl, newPosition, newRotation, newScale, newPref), lastMoved(sf::seconds(0)), damage(10), speedPeriod(20) {};
    void update(sf::RenderWindow* window, sf::Event& event, vector<shared_ptr<Sprite>>& allSprites, sf::Clock& clock) override;
    virtual bool collision(Sprite* collided) override;

    double getDamage() const { return damage; }
    void setDamage(double damage) { this->damage = damage; }
};

class BigBullet : public Bullet {
public:
      BigBullet(string newUrl, sf::Vector2f newPosition, double newRotation, double newScale, string newPref);
};

class BouncingBullet : public Bullet {
private:
    int totalBounces;
    sf::Clock clock;
    sf::Time lastHit;
public:
      BouncingBullet(string newUrl, sf::Vector2f newPosition, double newRotation, double newScale, string newPref);
      bool collision(Sprite* collided) override;
};

class LaserBullet : public Bullet {
public:
      LaserBullet(string newUrl, sf::Vector2f newPosition, double newRotation, double newScale, string newPref);
};
#endif
