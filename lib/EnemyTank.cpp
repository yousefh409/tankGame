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

enum class EnemyTypes {
    Basic,
    Hard,
    Stationary,
    Boss
};

EnemyTypes getEnemyType(string url) {
    if (url == "images/enemyTank-basic-1.png") return EnemyTypes::Basic;
    if (url == "images/enemyTank-basic-2.png") return EnemyTypes::Basic;
    if (url == "images/enemyTank-hard.png") return EnemyTypes::Hard;
    if (url == "images/enemyTank-stationary.png") return EnemyTypes::Stationary;
    if (url == "images/enemyTank-boss.png") return EnemyTypes::Boss;
}

void EnemyTank::update(sf::RenderWindow* window, sf::Event& event, vector<shared_ptr<Sprite>>&  allSprites, sf::Clock& clock) {
    Tank::update(window, event, allSprites, clock);
}

bool EnemyTank::collision(Sprite* collided) {
    currentFrame = 0;
    numFrames = 4;
    Bullet* bullet = dynamic_cast<Bullet*>(collided);

    if (bullet) {
        health -= bullet->getDamage();
    }
    if (health <= 0) {
        return true;
    }
    return false;
}

void PeriodicFire::update(sf::RenderWindow* window, sf::Event& event, vector<shared_ptr<Sprite>>& allSprites, sf::Clock& clock) {
    switch (getEnemyType(getUrl()))
    {
        case EnemyTypes::Basic:
        {
            firePeriod = 2000;
            double angle = (atan2((*allSprites.front()).getPosition().y - sprite.getPosition().y, (*allSprites.front()).getPosition().x - sprite.getPosition().x) * 180 / 3.14159265);
            setRotation(angle);

            float x_pos = sprite.getPosition().x;
            float y_pos = sprite.getPosition().y;
            setPosition(sf::Vector2f(x_pos + (currentDirection.x) / 10, y_pos + (currentDirection.y) / 10), allSprites, true);

            sf::Time currentTime = clock.getElapsedTime();
            if ((currentTime - lastMoved).asSeconds() > 3) {
                lastMoved = currentTime;
                currentDirection.x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 4)) - 2;
                currentDirection.y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 4)) - 2;
            }
            if ((int)currentTime.asSeconds() % 6 == 0) {
                if (x_pos > (*allSprites.front()).getPosition().x && y_pos > (*allSprites.front()).getPosition().y) {
                    currentDirection.x = currentDirection.y = -1;
                }
                else if (x_pos < (*allSprites.front()).getPosition().x && y_pos >(*allSprites.front()).getPosition().y) {
                    currentDirection.x = 1;
                    currentDirection.y = -1;
                }
                else if (x_pos < (*allSprites.front()).getPosition().x && y_pos < (*allSprites.front()).getPosition().y) {
                    currentDirection.x = currentDirection.y = 1;
                }
                else if (x_pos > (*allSprites.front()).getPosition().x && y_pos < (*allSprites.front()).getPosition().y) {
                    currentDirection.x = -1;
                    currentDirection.y = 1;
                }
            }

            fire(allSprites, clock, 10);
            EnemyTank::update(window, event, allSprites, clock);
            window->draw(sprite);
            break;
        }
        case EnemyTypes::Hard:
        {
            firePeriod = 1000;
            double angle = (atan2((*allSprites.front()).getPosition().y - sprite.getPosition().y, (*allSprites.front()).getPosition().x - sprite.getPosition().x) * 180 / 3.14159265);
            setRotation(angle);

            float x_pos = sprite.getPosition().x;
            float y_pos = sprite.getPosition().y;
            setPosition(sf::Vector2f(x_pos + (currentDirection.x) / 10, y_pos + (currentDirection.y) / 10), allSprites, true);

            sf::Time currentTime = clock.getElapsedTime();
            if ((currentTime - lastMoved).asSeconds() > 3) {
                lastMoved = currentTime;
                currentDirection.x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 4)) - 2;
                currentDirection.y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 4)) - 2;
            }
            if ((int)currentTime.asSeconds() < currentTime.asSeconds() && currentTime.asSeconds() < (int)currentTime.asSeconds() + 0.005 && (int)currentTime.asSeconds() % 4 == 0) {
                setPosition(sf::Vector2f(rand() % 700, rand() % 800), allSprites, true);
            }

            fire(allSprites, clock, 10);
            EnemyTank::update(window, event, allSprites, clock);
            window->draw(sprite);
            break;
        }
        case EnemyTypes::Stationary:
        {
            firePeriod = 100;
            double angle = getRotation() + 1;
            setRotation(angle);

            fire(allSprites, clock, 10);
            EnemyTank::update(window, event, allSprites, clock);
            window->draw(sprite);
            break;
        }
        case EnemyTypes::Boss:
        {
            firePeriod = 100;
            double angle = (atan2((*allSprites.front()).getPosition().y - sprite.getPosition().y, (*allSprites.front()).getPosition().x - sprite.getPosition().x) * 180 / 3.14159265);
            setRotation(angle);

            float x_pos = sprite.getPosition().x;
            float y_pos = sprite.getPosition().y;
            setPosition(sf::Vector2f(x_pos + (currentDirection.x) / 10, y_pos + (currentDirection.y) / 10), allSprites, true);

            sf::Time currentTime = clock.getElapsedTime();
            if ((currentTime - lastMoved).asSeconds() > 1) {
                lastMoved = currentTime;
                currentDirection.x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 4)) - 2;
                currentDirection.y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 4)) - 2;
            }
            if ((int)currentTime.asSeconds() < currentTime.asSeconds() && currentTime.asSeconds() < (int)currentTime.asSeconds() + 0.005 && (int)currentTime.asSeconds() % 2 == 0) {
                setPosition(sf::Vector2f(rand() % 700, rand() % 800), allSprites, true);
            }

            fire(allSprites, clock, 2);
            EnemyTank::update(window, event, allSprites, clock);
            window->draw(sprite);
            break;
        }
    }
}

