#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include "Sprite.h"
#include "MainTank.h"

void MainTank::update(sf::RenderWindow& window, sf::Event& event) {
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
    }

    window.draw(sprite);
}
