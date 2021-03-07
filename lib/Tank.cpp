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

void Tank::update(sf::RenderWindow* window, sf::Event& event, vector<shared_ptr<Sprite>>&  allSprites, sf::Clock& clock) {
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


void Tank::fire(vector<shared_ptr<Sprite>>& allSprites , sf::Clock& clock) {
    sf::Time currentTime = clock.getElapsedTime();
    if ((currentTime - lastFired).asMilliseconds() > firePeriod) {
        lastFired = currentTime;

        sf::Vector2f rotationVector = rotationToVector(rotation, 90);

        sf::Vector2f bulletPos = sf::Vector2f(sprite.getPosition().x + rotationVector.y * 60, sprite.getPosition().y + rotationVector.x * -60);
        if (static_cast<int>(rotation) % 90 != 0) {
            bulletPos = sf::Vector2f(sprite.getPosition().x + rotationVector.y * 100, sprite.getPosition().y + rotationVector.x * -100);
        }

        Bullet bullet("images/bullet.png", bulletPos, sprite.getRotation() + 90, 0.08);
        allSprites.push_back(make_shared<Bullet>(bullet));
    }
}

void Tank::fireBig(vector<shared_ptr<Sprite>>& allSprites, sf::Clock& clock, sf::RenderWindow* window) {
    sf::Time currentTime = clock.getElapsedTime();
    if ((currentTime - lastFired).asMilliseconds() > firePeriod) {
        lastFired = currentTime;

        sf::Vector2f origin = sf::Vector2f(window->getSize().x / 2.0, window->getSize().y / 2.0);
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

        BigBullet bullet("images/bulletBig.png", bulletPos, bullRotation, 0.3);
        allSprites.push_back(make_shared<Bullet>(bullet));
    }
}

