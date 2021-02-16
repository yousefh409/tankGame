#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "Sprite.h"
#include "Bullet.h"
#include "Wall.h"
#include "MainTank.h"


void MainTank::update(sf::RenderWindow& window, sf::Event& event, vector<shared_ptr<Sprite>>&  allSprites, sf::Clock& clock) {

        sf::Vector2f delta = sf::Vector2f(window.getSize().x / 1500.f, window.getSize().y / 1500.f);

        float totalRotation = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            setPosition(sf::Vector2f(position.x, position.y - delta.y), allSprites);
            totalRotation = 270;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                totalRotation -= 45;
                setPosition(sf::Vector2f(position.x - delta.x, position.y), allSprites);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                totalRotation += 45;
                setPosition(sf::Vector2f(position.x + delta.x, position.y), allSprites);
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            setPosition(sf::Vector2f(position.x, position.y + delta.y), allSprites);
            totalRotation = 90;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                totalRotation += 45;
                setPosition(sf::Vector2f(position.x - delta.x, position.y), allSprites);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                totalRotation -= 45;
                setPosition(sf::Vector2f(position.x + delta.x, position.y), allSprites);
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            setPosition(sf::Vector2f(position.x - delta.x, position.y), allSprites);
            totalRotation = 180;
        }
       else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            setPosition(sf::Vector2f(position.x + delta.x, position.y), allSprites);
            totalRotation = 0;
            setRotation(totalRotation);
        }
        if (totalRotation) {
            setRotation(totalRotation);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            fire(allSprites, clock);
        }

    window.draw(sprite);
}

void MainTank::fire(vector<shared_ptr<Sprite>>& allSprites , sf::Clock& clock) {
    sf::Time currentTime = clock.getElapsedTime();
    if ((currentTime - lastFired).asMilliseconds() > 200) {
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

bool MainTank::collision(Sprite* collided) {
    Bullet* bullet = dynamic_cast<Bullet*>(collided);

    if (bullet) {
        cout << "Tank 1 Hit!" << endl;
    } else {

    }

    return false;
}
