#ifndef ENEMYTANK_CPP
#define ENEMYTANK_CPP
#include "EnemyTank.h"

using namespace std;

enum class EnemyTypes {
    Basic,
    Hard,
    Stationary,
    Boss
};

EnemyTypes getEnemyType(string url, string filePrefix) {
    if (url == filePrefix + "enemyTank-hard.png") {
        return EnemyTypes::Hard;
    }
    if (url == filePrefix + "enemyTank-stationary.png") {
        return EnemyTypes::Stationary;
    }
    if (url == filePrefix + "enemyTank-boss.png") {
        return EnemyTypes::Boss;
    }
    else {
        return EnemyTypes::Basic;
    }
}

bool EnemyTank::collision(Sprite* collided) {
    currentFrame = 0;
    numFrames = 4;
    Bullet* bullet = dynamic_cast<Bullet*>(collided);

   sf::Time currentTime = clock.getElapsedTime();
    if (bullet && (currentTime - lastHit).asMilliseconds() > 100) {
        health -= bullet->getDamage();
        lastHit = currentTime;
    }
    if (health <= 0) {
        return true;
    }
    return false;
}

void EnemyTank::update(sf::RenderWindow* window, sf::Event& event, vector<shared_ptr<Sprite>>& allSprites, sf::Clock& clock) {
    switch (getEnemyType(getUrl(), this->filePrefix))
    {
        case EnemyTypes::Basic:
        {
            this->basicUpdate(window, event, allSprites, clock);
            break;
        }
        case EnemyTypes::Hard:
        {
            this->hardUpdate(window, event, allSprites, clock);
            break;
        }
        case EnemyTypes::Stationary:
        {
            this->stationaryUpdate(window, event, allSprites, clock);
            break;
        }
        case EnemyTypes::Boss:
        {
            this->bossUpdate(window, event, allSprites, clock);
            break;
        }
    }
}


void EnemyTank::basicUpdate(sf::RenderWindow* window, sf::Event& event, vector<shared_ptr<Sprite>>&  allSprites, sf::Clock& clock) {
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
    if (static_cast<int>(currentTime.asSeconds()) % 6 == 0) {
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
    Tank::update(window, event, allSprites, clock);
    window->draw(sprite);
}

void EnemyTank::hardUpdate(sf::RenderWindow* window, sf::Event& event, vector<shared_ptr<Sprite>>&  allSprites, sf::Clock& clock) {
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
    if (static_cast<int>(currentTime.asSeconds()) < currentTime.asSeconds() && currentTime.asSeconds() < static_cast<int>(currentTime.asSeconds()) + 0.005 && static_cast<int>(currentTime.asSeconds()) % 4 == 0) {
        setPosition(sf::Vector2f(rand() % 700, rand() % 800), allSprites, true);
    }

    fire(allSprites, clock, 10);
    Tank::update(window, event, allSprites, clock);
    window->draw(sprite);
}

void EnemyTank::stationaryUpdate(sf::RenderWindow* window, sf::Event& event, vector<shared_ptr<Sprite>>&  allSprites, sf::Clock& clock) {
    firePeriod = 100;
    double angle = getRotation() + 1;
    setRotation(angle);

    fire(allSprites, clock, 10);
    Tank::update(window, event, allSprites, clock);
    window->draw(sprite);
}

void EnemyTank::bossUpdate(sf::RenderWindow* window, sf::Event& event, vector<shared_ptr<Sprite>>&  allSprites, sf::Clock& clock) {
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
    if (static_cast<int>(currentTime.asSeconds()) < currentTime.asSeconds() && currentTime.asSeconds() < static_cast<int>(currentTime.asSeconds()) + 0.005 && (static_cast<int>(currentTime.asSeconds()) % 2 == 0)) {
        setPosition(sf::Vector2f(rand() % 700, rand() % 800), allSprites, true);
    }

    fire(allSprites, clock, 2);
    Tank::update(window, event, allSprites, clock);
    window->draw(sprite);
}
#endif
