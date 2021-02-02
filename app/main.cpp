#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include "Sprite.h"
#include "MainTank.h"

using namespace std;


int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Tank Game", sf::Style::Close);
    sf::Event event;

    sf::RectangleShape background(sf::Vector2f(1024.0f, 768.0f));
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile(std::string("../images/background.png"));
	background.setTexture(&backgroundTexture);

	MainTank mainTank = MainTank("../images/tank.png", sf::Vector2f(1024.0f/2, 768.0f/2), 0, 0.5);

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			default: ;
			}
            mainTank.update(window, event);
		}

		window.clear();
		window.draw(background);
		mainTank.update(window, event);
		window.display();
	}
}


