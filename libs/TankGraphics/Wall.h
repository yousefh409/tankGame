#ifndef WALL_H
#define WALL_H
#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "Sprite.h"

using namespace std;

class Wall : public Sprite {
private:
    int health; //TODO
public:
    Wall(string newUrl, sf::Vector2f newPosition, double newRotation, double newScale, string newPref) : Sprite(newUrl, newPosition, newRotation, newScale, newPref), health(100) {};

    virtual bool collision(Sprite* /*collided*/) override { return false; };
};
#endif // WALL_H
