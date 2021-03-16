#ifndef MAINTANK_H
#define MAINTANK_H
#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "Sprite.h"
#include "Tank.h"

using namespace std;

class MainTank : public Tank {
private:
    sf::Clock clock;
    sf::Time lastHit;
public:
    MainTank(string newUrl, sf::Vector2f newPosition, double newRotation, double newScale, string newPref) : Tank(newUrl, newPosition, newRotation, newScale, newPref), lastHit(clock.getElapsedTime()) { origHealth = health = 100; }
    virtual void update(sf::RenderWindow* window, sf::Event& event, vector<shared_ptr<Sprite>>&  allSprites, sf::Clock& clock) override;
    virtual bool collision(Sprite* collided) override;
};
#endif
