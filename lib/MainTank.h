#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "Sprite.h"

using namespace std;

class MainTank : public Sprite {
private:
    sf::Time lastFired;
public:
    MainTank(string newUrl, sf::Vector2f newPosition, double newRotation, double newScale) : Sprite(newUrl, newPosition, newRotation, newScale), lastFired(sf::seconds(0)) {}
    void update(sf::RenderWindow& window, sf::Event& event, vector<shared_ptr<Sprite>>&  allSprites, sf::Clock& clock) override;
    void fire(vector<shared_ptr<Sprite>>& allSprites , sf::Clock& clock);
};
