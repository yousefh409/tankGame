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
    // cout << (*allSprites.front()).getPosition().x << " " << (*allSprites.front()).getPosition().y << endl;
    double x_offset = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 200));
    double y_offset = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 200));
    double angle = (atan2((*allSprites.front()).getPosition().y - sprite.getPosition().y, (*allSprites.front()).getPosition().x - sprite.getPosition().x) * 180 / 3.14159265);
    setRotation(angle);

    float x_pos = sprite.getPosition().x;
    float y_pos = sprite.getPosition().y;
    setPosition(sf::Vector2f(x_pos + currentDirection.x, y_pos + currentDirection.y), allSprites);

    sf::Time currentTime = clock.getElapsedTime();
    if ((currentTime - lastMoved).asSeconds() > 1) {
        lastMoved = currentTime;
        currentDirection.x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 10)) - 5;
        currentDirection.y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 10)) - 5;
    }

    fire(allSprites, clock);
    EnemyTank::update(window, event, allSprites, clock);
    window->draw(sprite);
}

