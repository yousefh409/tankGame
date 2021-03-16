#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "Sprite.h"
#include "Tank.h"
#include "Bullet.h"
#include "EnemyTank.h"


using namespace std;

void Tank::update(sf::RenderWindow* window, sf::Event& /*event*/, vector<shared_ptr<Sprite>>&  /*allSprites*/, sf::Clock& /*clock*/) {
    sf::RectangleShape healthBar;
    healthBar.setSize(sf::Vector2f(80.f, 15.f));
    EnemyTank* enemyPtr = dynamic_cast<EnemyTank*>(this);
    if (enemyPtr) {
        healthBar.setFillColor(sf::Color::Red);
    } else {
        healthBar.setFillColor(sf::Color::Green);
    }
    healthBar.setPosition(getPosition().x - 40, getPosition().y + 40);

    float hpPercent = getHealth() / origHealth;
    healthBar.setSize(sf::Vector2f(80.f * hpPercent, healthBar.getSize().y));
    window->draw(healthBar);
}


void Tank::fire(vector<shared_ptr<Sprite>>& allSprites , sf::Clock& clock, double damage) {
    sf::Time currentTime = clock.getElapsedTime();
    if ((currentTime - lastFired).asMilliseconds() > firePeriod) {
        lastFired = currentTime;

        sf::Vector2f rotationVector = rotationToVector(rotation, 90);

        sf::Vector2f bulletPos = sf::Vector2f(sprite.getPosition().x + rotationVector.y * 60, sprite.getPosition().y + rotationVector.x * -60);
        if (static_cast<int>(rotation) % 90 != 0) {
            bulletPos = sf::Vector2f(sprite.getPosition().x + rotationVector.y * 100 * (0.75 + scale), sprite.getPosition().y + rotationVector.x * -100 * (0.75 + scale));
        }

        Bullet bullet(this->getPrefix() + "bullet.png", bulletPos, sprite.getRotation() + 90, 0.08, this->getPrefix());
        bullet.setDamage(damage);
        allSprites.push_back(make_shared<Bullet>(bullet));
    }
}

void Tank::fireBig(vector<shared_ptr<Sprite>>& allSprites, sf::Clock& clock, sf::RenderWindow* window) {
    sf::Time currentTime = clock.getElapsedTime();
    if ((currentTime - lastFired).asMilliseconds() > firePeriod) {
        lastFired = currentTime;

        sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y) - (sprite.getPosition());

        double bullRotation = vectorToRotation(mousePos);
        if (bullRotation < 0) {
            bullRotation = 360 + bullRotation;
        }
        if (mousePos.x < 0) {
            bullRotation = bullRotation + 180;
        }
        bullRotation = static_cast<int>(bullRotation + 90) % 360;

        sf::Vector2f rotationVector = rotationToVector(bullRotation, 0);

        sf::Vector2f bulletPos = sf::Vector2f(sprite.getPosition().x + rotationVector.y * 60, sprite.getPosition().y + rotationVector.x * -60);
        if (static_cast<int>(bullRotation) % 90 != 0) {
            bulletPos = sf::Vector2f(sprite.getPosition().x + rotationVector.y * 100, sprite.getPosition().y + rotationVector.x * -100);
        }

        BigBullet bullet(this->filePrefix + "bulletBig.png", bulletPos, bullRotation, 0.3, this->filePrefix);
        allSprites.push_back(make_shared<BigBullet>(bullet));
    }
}

void Tank::fireLaser(vector<shared_ptr<Sprite>>& allSprites, sf::Clock& clock, sf::RenderWindow* /*window*/) {
    sf::Time currentTime = clock.getElapsedTime();
    if ((currentTime - lastFired).asMilliseconds() > firePeriod) {
        lastFired = currentTime;

        sf::Vector2f rotationVector = rotationToVector(rotation, 90);

        sf::Vector2f bulletPos = sf::Vector2f(sprite.getPosition().x + rotationVector.y * 60, sprite.getPosition().y + rotationVector.x * -60);
        if (static_cast<int>(rotation) % 90 != 0) {
            bulletPos = sf::Vector2f(sprite.getPosition().x + rotationVector.y * 100 * (0.75 + scale), sprite.getPosition().y + rotationVector.x * -100 * (0.75 + scale));
        }

        LaserBullet bullet(this->filePrefix + "laserBullet.png", bulletPos, sprite.getRotation() + 90, 0.3, this->filePrefix);
        this->health -= 10;
        allSprites.push_back(make_shared<LaserBullet>(bullet));
    }
}

void Tank::fireBouncing(vector<shared_ptr<Sprite>>& allSprites, sf::Clock& clock, sf::RenderWindow* window) {
    sf::Time currentTime = clock.getElapsedTime();
    if ((currentTime - lastFired).asMilliseconds() > firePeriod) {
        lastFired = currentTime;

        sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y) - (sprite.getPosition());

        double bullRotation = vectorToRotation(mousePos);
        if (bullRotation < 0) {
            bullRotation = 360 + bullRotation;
        }
        if (mousePos.x < 0) {
            bullRotation = bullRotation + 180;
        }
        bullRotation = static_cast<int>(bullRotation + 90) % 360;

        sf::Vector2f rotationVector = rotationToVector(bullRotation, 0);

        sf::Vector2f bulletPos = sf::Vector2f(sprite.getPosition().x + rotationVector.y * 60, sprite.getPosition().y + rotationVector.x * -60);
        if (static_cast<int>(bullRotation) % 90 != 0) {
            bulletPos = sf::Vector2f(sprite.getPosition().x + rotationVector.y * 80, sprite.getPosition().y + rotationVector.x * -80);
        }

        BouncingBullet bullet(this->filePrefix + "bouncingBullet.png", bulletPos, bullRotation, 0.3, this->filePrefix);
        allSprites.push_back(make_shared<BouncingBullet>(bullet));
    }
}

