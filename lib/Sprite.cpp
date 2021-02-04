#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include "Sprite.h"

using namespace std;


Sprite::Sprite(string newUrl, sf::Vector2f newPosition, double newRotation, double newScale) {
    position = newPosition;
    imageUrl = newUrl;
    rotation = newRotation;
    scale = newScale;
	texture.loadFromFile(imageUrl);

	sprite = sf::Sprite(texture);

	sprite.setScale(scale, scale);
	sprite.setPosition(position);

    sf::Vector2f spriteSize(texture.getSize().x * scale, texture.getSize().y * scale);
    sf::Vector2f center(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);
	sprite.setOrigin(center);

	sprite.setRotation(rotation);
}

void Sprite::setPosition(sf::Vector2f newPosition) {
    position = newPosition;
    sprite.setPosition(position);

}

void Sprite::setUrl(string newUrl) {
    imageUrl = newUrl;

    sf::Texture texture;
	texture.loadFromFile(imageUrl);

	sprite = sf::Sprite(texture);

	sprite.setScale(scale, scale);
	sprite.setPosition(position);


    sf::Vector2f spriteSize(texture.getSize().x * scale, texture.getSize().y * scale);
    sf::Vector2f center(spriteSize.x / 2, spriteSize.y / 2);
	sprite.setOrigin(center);

	sprite.setRotation(rotation);

}

void Sprite::setRotation(double newRotation) {
    rotation = newRotation;
    sprite.setRotation(rotation);

}

void Sprite::setScale(double newScale) {
    scale = newScale;
    sprite.setScale(scale, scale);

}

void Sprite::update(sf::RenderWindow& window, sf::Event& event) {
    window.draw(sprite);
}
