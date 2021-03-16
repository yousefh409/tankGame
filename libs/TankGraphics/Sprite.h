#ifndef SPRITE_H
#define SPRITE_H

#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <vector>
#include<memory>

using namespace std;

class Sprite {
protected:
    sf::Sprite sprite;
    shared_ptr<sf::Texture> texture;

    string imageUrl;
    string filePrefix;
    sf::Vector2f position;
    double rotation;
    double scale;
    double health = 0.0;
    int numFrames;
    int currentFrame = 0;

    sf::Time lastAnimated;

public:
    Sprite(string newUrl, sf::Vector2f newPosition, double newRotation, double newScale, string newPref);
    Sprite(const Sprite& toCopy);

    void setPosition(sf::Vector2f newPosition, vector<shared_ptr<Sprite>>& allSprites,  bool avoidCollision=true);
    void setUrl(string newUrl);
    void setRotation(double newRotation);
    void setScale(double newScale);

    sf::Vector2f getPosition() const { return position; }
    double getRotation() const { return rotation; }
    double getHealth() const { return health; }
    string getUrl() const { return imageUrl; }
    string getPrefix() const { return filePrefix; }

    sf::Vector2f rotationToVector(double rot, double offset) const;
    double vectorToRotation(sf::Vector2f& orig) const;


    bool isIntersect(Sprite* other);
    virtual bool collision(Sprite* collided);
    virtual bool isExploded(sf::Clock clock);

    virtual void update(sf::RenderWindow* window, sf::Event& event, vector<shared_ptr<Sprite>>& allSprites, sf::Clock& clock);
};
#endif
