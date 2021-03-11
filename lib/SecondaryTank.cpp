#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "Sprite.h"
#include "Bullet.h"
#include "SecondaryTank.h"


void SecondaryTank::update(sf::RenderWindow* window, sf::Event& event, vector<shared_ptr<Sprite>>&  allSprites, sf::Clock& clock) {
        sf::Vector2f delta = sf::Vector2f(window->getSize().x / 1500.f, window->getSize().y / 1500.f);

        float totalRotation = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            setPosition(sf::Vector2f(position.x, position.y - delta.y), allSprites);
            totalRotation = 270;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                totalRotation -= 45;
                setPosition(sf::Vector2f(position.x - delta.x, position.y), allSprites);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                totalRotation += 45;
                setPosition(sf::Vector2f(position.x + delta.x, position.y), allSprites);
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            setPosition(sf::Vector2f(position.x, position.y + delta.y), allSprites);
            totalRotation = 90;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                totalRotation += 45;
                setPosition(sf::Vector2f(position.x - delta.x, position.y), allSprites);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                totalRotation -= 45;
                setPosition(sf::Vector2f(position.x + delta.x, position.y), allSprites);
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            setPosition(sf::Vector2f(position.x - delta.x, position.y), allSprites);
            totalRotation = 180;
        }
       else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            setPosition(sf::Vector2f(position.x + delta.x, position.y), allSprites);
            totalRotation = 0;
            setRotation(totalRotation);
        }
        if (totalRotation) {
            setRotation(totalRotation);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
            fire(allSprites, clock, 10);
        }

    window->draw(sprite);
}

bool SecondaryTank::collision(Sprite* collided) {
    Bullet* bullet = dynamic_cast<Bullet*>(collided);

    if (bullet) {
        health -= bullet->getDamage();
    }
    if (health <= 0) {
        return true;
    } else {
        return false;
    }
}

