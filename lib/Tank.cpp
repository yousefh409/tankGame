#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "Sprite.h"
#include "Tank.h"
#include "Bullet.h"


using namespace std;

void Tank::fire(vector<shared_ptr<Sprite>>& allSprites , sf::Clock& clock) {
    sf::Time currentTime = clock.getElapsedTime();
    if ((currentTime - lastFired).asMilliseconds() > firePeriod) {
        lastFired = currentTime;

        sf::Vector2f rotationVector = getVectorRotation(90);

        sf::Vector2f bulletPos = sf::Vector2f(sprite.getPosition().x + rotationVector.y * 60, sprite.getPosition().y + rotationVector.x * -60);
        if (static_cast<int>(rotation) % 90 != 0) {
            bulletPos = sf::Vector2f(sprite.getPosition().x + rotationVector.y * 100, sprite.getPosition().y + rotationVector.x * -100);
        }
        Bullet bullet("../images/bullet.png", bulletPos, sprite.getRotation() + 90, 0.08);
        allSprites.push_back(make_shared<Bullet>(bullet));
    }
}
