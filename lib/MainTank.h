#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include "Sprite.h"

using namespace std;

class MainTank : public Sprite {
public:
    MainTank(string newUrl, sf::Vector2f newPosition, double newRotation, double newScale) : Sprite(newUrl, newPosition, newRotation, newScale) {};
    void update(sf::RenderWindow& window, sf::Event& event) override;

};
