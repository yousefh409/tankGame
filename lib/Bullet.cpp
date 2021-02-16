#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "Sprite.h"
#include "Bullet.h"



using namespace std;

void Bullet::update(sf::RenderWindow& window, sf::Event& event, vector<shared_ptr<Sprite>>&  allSprites, sf::Clock& clock) {

    sf::Time currentTime = clock.getElapsedTime();
    if ((currentTime - lastMoved).asMilliseconds() > 20) {
        lastMoved = currentTime;
        sf::Vector2f rotationVector = getVectorRotation(-90);

        sf::Vector2f delta = sf::Vector2f((window.getSize().x / 50.f) * rotationVector.x, (window.getSize().y / 50.f) * rotationVector.y);

        setPosition(sf::Vector2f(position.x + delta.x, position.y + delta.y), allSprites, false);

    }
    window.draw(sprite);
}

bool Bullet::collision(Sprite* collided) {

    return true;
}

