#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "Sprite.h"
#include "MainTank.h"
#include "Bullet.h"

using namespace std;

//comment

void updateWindow(MainTank& mainTank, vector<shared_ptr<Sprite>>& allSprites, sf::RenderWindow& window, sf::Event& event, sf::Clock& clock);

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Tank Game", sf::Style::Close);
    sf::Event event;
    sf::Clock clock;

    sf::RectangleShape background(sf::Vector2f(1024.0f, 768.0f));
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile(std::string("../images/background.png"));
	background.setTexture(&backgroundTexture);

	MainTank mainTank = MainTank("../images/tank.png", sf::Vector2f(1024.0f/2, 768.0f/2), 0, 0.5);

	vector<shared_ptr<Sprite>> allSprites;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
            case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) window.close();
			default: ;
			}
            updateWindow(mainTank, allSprites, window, event, clock);

		}

		window.clear();
		window.draw(background);
		updateWindow(mainTank, allSprites, window, event, clock);
		window.display();
	}
}

void updateWindow(MainTank& mainTank, vector<shared_ptr<Sprite>>& allSprites, sf::RenderWindow& window, sf::Event& event, sf::Clock& clock) {
    mainTank.update(window, event, allSprites, clock);
    for (auto iter = allSprites.begin(); iter != allSprites.end(); iter++) {
        (*iter)->update(window, event, allSprites, clock);
    }
}
