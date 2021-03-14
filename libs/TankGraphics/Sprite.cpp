#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cmath>
#include "Sprite.h"

using namespace std;


Sprite::Sprite(string newUrl, sf::Vector2f newPosition, double newRotation, double newScale, string newPref) {
    position = newPosition;
    imageUrl = newUrl;
    filePrefix = newPref;
    rotation = newRotation;
    scale = newScale;

    texture = make_shared<sf::Texture>(sf::Texture());
	texture->loadFromFile(imageUrl);
	sprite = sf::Sprite(*texture);

	sprite.setScale(scale, scale);
	sprite.setPosition(position);

    sf::Vector2f spriteSize(texture->getSize().x * scale, texture->getSize().y * scale);
    sf::Vector2f center(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);
	sprite.setOrigin(center);

	sprite.setRotation(rotation);
}


Sprite::Sprite(const Sprite& toCopy) {
    position = toCopy.position;
    imageUrl = toCopy.imageUrl;
    rotation = toCopy.rotation;
    filePrefix = toCopy.filePrefix;
    scale = toCopy.scale;
    health = toCopy.health;
    texture = make_shared<sf::Texture>(sf::Texture());
	texture->loadFromFile(imageUrl);
	sprite = sf::Sprite(*texture);

	sprite.setScale(scale, scale);
	sprite.setPosition(position);

    sf::Vector2f spriteSize(texture->getSize().x * scale, texture->getSize().y * scale);
    sf::Vector2f center(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);
	sprite.setOrigin(center);

	sprite.setRotation(rotation);
}


void Sprite::setPosition(sf::Vector2f newPosition, vector<shared_ptr<Sprite>>& allSprites, bool avoidCollision) {
    sf::Vector2f oldPosition = position;
    position = newPosition;
    sprite.setPosition(position);
    if (avoidCollision) {
        for (auto iter = allSprites.begin(); iter < allSprites.end(); iter++) {
            if ((iter->get() != this) && isIntersect(iter->get())) {
                 position = oldPosition;
                sprite.setPosition(oldPosition);
                return;
            }
        }
    }

}

void Sprite::setUrl(string newUrl) {

    imageUrl = newUrl;

    texture = make_shared<sf::Texture>(sf::Texture());
	texture->loadFromFile(imageUrl);

	sprite = sf::Sprite(*texture);

	sprite.setScale(scale, scale);
	sprite.setPosition(position);


    sf::Vector2f spriteSize(texture->getSize().x * scale, texture->getSize().y * scale);
    sf::Vector2f center(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);
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

sf::Vector2f Sprite::rotationToVector(double rot, double offset) const {
    double radians = (rot + offset) * (3.14159 / 180.0);
    sf::Vector2f rotationVector(cos(radians), sin(radians));

    return rotationVector;

}

double Sprite::vectorToRotation(sf::Vector2f& orig) const {
    return atan(orig.y / orig.x) * (180.0 / 3.14159);
}

bool Sprite::isIntersect(Sprite* other) {
    return sprite.getGlobalBounds().intersects(other->sprite.getGlobalBounds());
}

bool Sprite::collision(Sprite* /*collided*/) {
    numFrames = 0;
    currentFrame = 0;

    return false;
}

bool Sprite::isExploded(sf::Clock clock) {
    if (numFrames == currentFrame) {
        return true;
    } else {
        sf::Time currentTime = clock.getElapsedTime();
        if ((currentTime - lastAnimated).asMilliseconds() > 100) {
            currentFrame++;
            string newImg = filePrefix + "explosionFrame" + to_string(currentFrame) + ".png";
            setScale(0.9);
            setUrl(newImg);
            lastAnimated = currentTime;
        }
        return false;
    }
}

void Sprite::update(sf::RenderWindow* window, sf::Event& /*event*/, vector<shared_ptr<Sprite>>& /*allSprites*/, sf::Clock& /*clock*/) {
    window->draw(sprite);

}





