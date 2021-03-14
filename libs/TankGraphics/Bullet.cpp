#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "Sprite.h"
#include "Bullet.h"



using namespace std;

void Bullet::update(sf::RenderWindow* window, sf::Event& /*event*/, vector<shared_ptr<Sprite>>&  allSprites, sf::Clock& clock) {

    if (currentFrame == 0) {
        sf::Time currentTime = clock.getElapsedTime();
        if ((currentTime - lastMoved).asMilliseconds() > speedPeriod) {
            lastMoved = currentTime;
            sf::Vector2f rotationVector = rotationToVector(rotation, -90);

            sf::Vector2f delta = sf::Vector2f((window->getSize().x / 50.f) * rotationVector.x, (window->getSize().y / 50.f) * rotationVector.y);

            setPosition(sf::Vector2f(position.x + delta.x, position.y + delta.y), allSprites, false);

        }
    }
    window->draw(sprite);
}

bool Bullet::collision(Sprite* /*collided*/) {

    numFrames = 3;
    currentFrame = 0;

    return true;
}

BigBullet::BigBullet(string newUrl, sf::Vector2f newPosition, double newRotation, double newScale, string newPref) : Bullet(newUrl, newPosition, newRotation, newScale, newPref) {
    damage = 25;
    speedPeriod = 60;
}


LaserBullet::LaserBullet(string newUrl, sf::Vector2f newPosition, double newRotation, double newScale, string newPref) : Bullet(newUrl, newPosition, newRotation, newScale, newPref) {
    damage = 40;
    speedPeriod = 15;
}

BouncingBullet::BouncingBullet(string newUrl, sf::Vector2f newPosition, double newRotation, double newScale, string newPref) : Bullet(newUrl, newPosition, newRotation, newScale, newPref) {
    totalBounces = 0;
    damage = 20;
    speedPeriod = 60;
    lastHit = clock.getElapsedTime();
}

bool BouncingBullet::collision(Sprite* collided) {
    sf::Time currentTime = clock.getElapsedTime();
    if ((currentTime - lastHit).asMilliseconds() > 80) {
        totalBounces++;
        lastHit = currentTime;
        if (totalBounces == 3) {
            numFrames = 3;
            currentFrame = 0;
            return true;
        } else {
            sf::Vector2f diff = this->getPosition() - collided->getPosition();
            if (diff.y > 0 && diff.x > 0) {
                if (diff.x > diff.y) {
                    this->setRotation(static_cast<int>(360 - rotation) % 360);
                } else {
                    this->setRotation(static_cast<int>(180 - rotation) % 360);
                }
            } else if (diff.y < 0 && diff.x > 0) {
                this->setRotation(static_cast<int>(180 - rotation) % 360);
            } else if (diff.x < 0) {
                this->setRotation(static_cast<int>(360 - rotation) % 360);
            } else {
                this->setRotation(static_cast<int>(-rotation) % 360);
            }
        }

    }
    return false;
}
