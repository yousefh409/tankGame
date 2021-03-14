#pragma once
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
    Wall(string newUrl, sf::Vector2f newPosition, double newRotation, double newScale) : Sprite(newUrl, newPosition, newRotation, newScale) {};

    virtual bool collision(Sprite* /*collided*/) override { return false; };
};

