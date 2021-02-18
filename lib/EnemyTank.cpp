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

bool EnemyTank::collision(Sprite* collided) {
    Bullet* bullet = dynamic_cast<Bullet*>(collided);

    if (bullet) {
        cout << "Enemy Tank Hit!" << endl;
    } else {
        cout << "eefefe";
    }
    return false;
}

void PeriodicFire::update(sf::RenderWindow& window, sf::Event& event, vector<shared_ptr<Sprite>>&  allSprites, sf::Clock& clock) {

    sf::Time currentTime = clock.getElapsedTime();
    if ((currentTime - lastMoved).asSeconds() > period) {
        lastMoved = currentTime;
        setRotation(static_cast<int>(rotation + 90) % 360);
    }
    fire(allSprites, clock);
    window.draw(sprite);
}

