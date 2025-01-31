#ifndef SECONDARYTANK_H
#define SECONDARYTANK_H
#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "Sprite.h"
#include "Tank.h"

using namespace std;

class SecondaryTank : public Tank {
public:
    SecondaryTank(string newUrl, sf::Vector2f newPosition, double newRotation, double newScale, string newPref) : Tank(newUrl, newPosition, newRotation, newScale, newPref) { health = 100; }
    virtual bool collision(Sprite* collided) override;
    void update(sf::RenderWindow* window, sf::Event& event, vector<shared_ptr<Sprite>>&  allSprites, sf::Clock& clock) override;
};
#endif
