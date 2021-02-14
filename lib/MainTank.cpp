#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "Sprite.h"
#include "Bullet.h"
#include "MainTank.h"


void MainTank::update(sf::RenderWindow& window, sf::Event& event, vector<shared_ptr<Sprite>>&  allSprites, sf::Clock& clock) {
    if (event.type == sf::Event::KeyPressed) {
        sf::Vector2f delta = sf::Vector2f(window.getSize().x / 100.f, window.getSize().y / 100.f);

        float totalRotation = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            setPosition(sf::Vector2f(position.x, position.y - delta.y));
            totalRotation = 270;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                totalRotation -= 45;
                setPosition(sf::Vector2f(position.x - delta.x, position.y));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                totalRotation += 45;
                setPosition(sf::Vector2f(position.x + delta.x, position.y));
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            setPosition(sf::Vector2f(position.x, position.y + delta.y));
            totalRotation = 90;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                totalRotation += 45;
                setPosition(sf::Vector2f(position.x - delta.x, position.y));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                totalRotation -= 45;
                setPosition(sf::Vector2f(position.x + delta.x, position.y));
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            setPosition(sf::Vector2f(position.x - delta.x, position.y));
            totalRotation = 180;
        }
       else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            setPosition(sf::Vector2f(position.x + delta.x, position.y));
            totalRotation = 0;
        }
        setRotation(totalRotation);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            fire(allSprites, clock);
        }
    }

    window.draw(sprite);
}

void MainTank::fire(vector<shared_ptr<Sprite>>& allSprites , sf::Clock& clock) {
    sf::Time currentTime = clock.getElapsedTime();
    if ((currentTime - lastFired).asMilliseconds() > 0) {
        lastFired = currentTime;
        sf::Vector2f bulletPos = sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y);
        Bullet bullet("../images/bullet.png", bulletPos, sprite.getRotation() + 90, 0.1);
        allSprites.push_back(make_shared<Bullet>(bullet));
    }
}
