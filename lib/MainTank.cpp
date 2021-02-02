#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include "Sprite.h"
#include "MainTank.h"

void MainTank::update(sf::RenderWindow& window, sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        sf::Vector2f delta = sf::Vector2f(window.getSize().x / 100.f, window.getSize().y / 100.f);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            setPosition(sf::Vector2f(position.x, position.y - delta.y));
            setRotation(270);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            setPosition(sf::Vector2f(position.x, position.y + delta.y));
            setRotation(90);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            setPosition(sf::Vector2f(position.x - delta.x, position.y));
            setRotation(180);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            setPosition(sf::Vector2f(position.x + delta.x, position.y));
            setRotation(0);
        }
    }

    window.draw(sprite);
}
